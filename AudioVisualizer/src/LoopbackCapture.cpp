#include <LoopbackCapture.h>
#include <shlobj.h>
#include <wchar.h>
#include <iostream>
#include <audioclientactivationparams.h>
#include <fftw3.h>
#include <winsock.h>
#include <cstdlib> 
#include <algorithm>
#include <vector>
#include <cmath>



#define BITS_PER_BYTE 8
#define SHORT_MAX 32767
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16
#define N_CHANNELS 2
#define FRAMES_PER_BUFFER SAMPLE_RATE / 100 // 256 (ish) frequency bins

#define SPECTRO_FREQ_START 20  // Lower bound of the displayed spectrogram (Hz)
#define SPECTRO_FREQ_END 20000 // Upper bound of the displayed spectrogram (Hz)

#define OUTPUT_FREQ_COUNT 5 // its currently not good at distinguishing separate low frequency bands, particularly below 5
#define ROLLING_AVG_ITERATIONS 32

HRESULT CLoopbackCapture::SetDeviceStateErrorIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        m_DeviceState = DeviceState::Error;
    }
    return hr;
}

HRESULT CLoopbackCapture::InitializeLoopbackCapture()
{
    // Create events for sample ready or user stop
    RETURN_IF_FAILED(m_SampleReadyEvent.create(wil::EventOptions::None));

    // Initialize MF
    RETURN_IF_FAILED(MFStartup(MF_VERSION, MFSTARTUP_LITE));

    // Register MMCSS work queue
    DWORD dwTaskID = 0;
    RETURN_IF_FAILED(MFLockSharedWorkQueue(L"Capture", 0, &dwTaskID, &m_dwQueueID));

    // Set the capture event work queue to use the MMCSS queue
    m_xSampleReady.SetQueueID(m_dwQueueID);

    // Create the completion event as auto-reset
    RETURN_IF_FAILED(m_hActivateCompleted.create(wil::EventOptions::None));

    // Create the capture-stopped event as auto-reset
    RETURN_IF_FAILED(m_hCaptureStopped.create(wil::EventOptions::None));

    return S_OK;
}

CLoopbackCapture::~CLoopbackCapture()
{
    if (m_dwQueueID != 0)
    {
        MFUnlockWorkQueue(m_dwQueueID);
    }
}

HRESULT CLoopbackCapture::ActivateAudioInterface(DWORD processId)
{
    return SetDeviceStateErrorIfFailed([&]() -> HRESULT
        {
            AUDIOCLIENT_ACTIVATION_PARAMS audioclientActivationParams = {};
            audioclientActivationParams.ActivationType = AUDIOCLIENT_ACTIVATION_TYPE_PROCESS_LOOPBACK;
            audioclientActivationParams.ProcessLoopbackParams.ProcessLoopbackMode = PROCESS_LOOPBACK_MODE_INCLUDE_TARGET_PROCESS_TREE;
            audioclientActivationParams.ProcessLoopbackParams.TargetProcessId = processId;

            PROPVARIANT activateParams = {};
            activateParams.vt = VT_BLOB;
            activateParams.blob.cbSize = sizeof(audioclientActivationParams);
            activateParams.blob.pBlobData = (BYTE*)&audioclientActivationParams;

            wil::com_ptr_nothrow<IActivateAudioInterfaceAsyncOperation> asyncOp;
            RETURN_IF_FAILED(ActivateAudioInterfaceAsync(VIRTUAL_AUDIO_DEVICE_PROCESS_LOOPBACK, __uuidof(IAudioClient), &activateParams, this, &asyncOp));

            // Wait for activation completion
            m_hActivateCompleted.wait();

            return m_activateResult;
        }());
}

//
//  ActivateCompleted()
//
//  Callback implementation of ActivateAudioInterfaceAsync function.  This will be called on MTA thread
//  when results of the activation are available.
//
HRESULT CLoopbackCapture::ActivateCompleted(IActivateAudioInterfaceAsyncOperation* operation)
{
    m_activateResult = SetDeviceStateErrorIfFailed([&]()->HRESULT
        {
            // Check for a successful activation result
            HRESULT hrActivateResult = E_UNEXPECTED;
            wil::com_ptr_nothrow<IUnknown> punkAudioInterface;
            RETURN_IF_FAILED(operation->GetActivateResult(&hrActivateResult, &punkAudioInterface));
            RETURN_IF_FAILED(hrActivateResult);

            // Get the pointer for the Audio Client
            RETURN_IF_FAILED(punkAudioInterface.copy_to(&m_AudioClient));

            // The app can also call m_AudioClient->GetMixFormat instead to get the capture format.
            // 16 - bit PCM format.
            m_CaptureFormat.wFormatTag = WAVE_FORMAT_PCM;
            m_CaptureFormat.nChannels = N_CHANNELS;
            m_CaptureFormat.nSamplesPerSec = SAMPLE_RATE;
            m_CaptureFormat.wBitsPerSample = BITS_PER_SAMPLE;
            m_CaptureFormat.nBlockAlign = m_CaptureFormat.nChannels * m_CaptureFormat.wBitsPerSample / BITS_PER_BYTE;
            m_CaptureFormat.nAvgBytesPerSec = m_CaptureFormat.nSamplesPerSec * m_CaptureFormat.nBlockAlign;

            InitializeFFT(); // setup fft variables for use

            // Initialize the AudioClient in Shared Mode with the user specified buffer
            RETURN_IF_FAILED(m_AudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,
                AUDCLNT_STREAMFLAGS_LOOPBACK | AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
                200000,
                AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM,
                &m_CaptureFormat,
                nullptr));

            // Get the maximum size of the AudioClient Buffer
            RETURN_IF_FAILED(m_AudioClient->GetBufferSize(&m_BufferFrames));

            // Get the capture client
            RETURN_IF_FAILED(m_AudioClient->GetService(IID_PPV_ARGS(&m_AudioCaptureClient)));

            // Create Async callback for sample events
            RETURN_IF_FAILED(MFCreateAsyncResult(nullptr, &m_xSampleReady, nullptr, &m_SampleReadyAsyncResult));

            // Tell the system which event handle it should signal when an audio buffer is ready to be processed by the client
            RETURN_IF_FAILED(m_AudioClient->SetEventHandle(m_SampleReadyEvent.get()));

            // Everything is ready.
            m_DeviceState = DeviceState::Initialized;

            return S_OK;
        }());

    // Let ActivateAudioInterface know that m_activateResult has the result of the activation attempt.
    m_hActivateCompleted.SetEvent();
    return S_OK;
}

HRESULT CLoopbackCapture::StartCaptureAsync(DWORD processId, VisualizerWindow* visualizerContainer)
{
    visualizer = visualizerContainer;

    RETURN_IF_FAILED(InitializeLoopbackCapture());
    RETURN_IF_FAILED(ActivateAudioInterface(processId));

    // We should be in the initialzied state if this is the first time through getting ready to capture.
    if (m_DeviceState == DeviceState::Initialized)
    {
        m_DeviceState = DeviceState::Starting;
        return MFPutWorkItem2(MFASYNC_CALLBACK_QUEUE_MULTITHREADED, 0, &m_xStartCapture, nullptr);
    }

    return S_OK;
}

//
//  OnStartCapture()
//
//  Callback method to start capture
//
HRESULT CLoopbackCapture::OnStartCapture(IMFAsyncResult* pResult)
{
    return SetDeviceStateErrorIfFailed([&]()->HRESULT
        {
            // Start the capture
            RETURN_IF_FAILED(m_AudioClient->Start());

            m_DeviceState = DeviceState::Capturing;
            MFPutWaitingWorkItem(m_SampleReadyEvent.get(), 0, m_SampleReadyAsyncResult.get(), &m_SampleReadyKey);

            return S_OK;
        }());
}


//
//  StopCaptureAsync()
//
//  Stop capture asynchronously via MF Work Item
//
HRESULT CLoopbackCapture::StopCaptureAsync()
{
    RETURN_HR_IF(E_NOT_VALID_STATE, (m_DeviceState != DeviceState::Capturing) &&
        (m_DeviceState != DeviceState::Error));

    m_DeviceState = DeviceState::Stopping;

    RETURN_IF_FAILED(MFPutWorkItem2(MFASYNC_CALLBACK_QUEUE_MULTITHREADED, 0, &m_xStopCapture, nullptr));

    // Wait for capture to stop
    m_hCaptureStopped.wait();

    return S_OK;
}

//
//  OnStopCapture()
//
//  Callback method to stop capture
//
HRESULT CLoopbackCapture::OnStopCapture(IMFAsyncResult* pResult)
{
    // Stop capture by cancelling Work Item
    // Cancel the queued work item (if any)
    if (0 != m_SampleReadyKey)
    {
        MFCancelWorkItem(m_SampleReadyKey);
        m_SampleReadyKey = 0;
    }

    m_AudioClient->Stop();
    m_SampleReadyAsyncResult.reset();

    return FinishCaptureAsync();
}

//
//  FinishCaptureAsync()
//
//  Finalizes WAV file on a separate thread via MF Work Item
//
HRESULT CLoopbackCapture::FinishCaptureAsync()
{
    // We should be flushing when this is called
    return MFPutWorkItem2(MFASYNC_CALLBACK_QUEUE_MULTITHREADED, 0, &m_xFinishCapture, nullptr);
}

//
//  OnFinishCapture()
//
//  Because of the asynchronous nature of the MF Work Queues and the DataWriter, there could still be
//  a sample processing.  So this will get called to finalize the WAV header.
//
HRESULT CLoopbackCapture::OnFinishCapture(IMFAsyncResult* pResult)
{
    m_DeviceState = DeviceState::Stopped;

    // Free allocated resources used for FFT calculation
    fftw_destroy_plan(fft_data_left->p);
    fftw_free(fft_data_left->in);
    fftw_free(fft_data_left->out);
    free(fft_data_left);

    fftw_destroy_plan(fft_data_right->p);
    fftw_free(fft_data_right->in);
    fftw_free(fft_data_right->out);
    free(fft_data_right);

    m_hCaptureStopped.SetEvent();

    return S_OK;
}

//
//  OnSampleReady()
//
//  Callback method when ready to fill sample buffer
//
HRESULT CLoopbackCapture::OnSampleReady(IMFAsyncResult* pResult)
{
    if (SUCCEEDED(OnAudioSampleRequested()))
    {
        // Re-queue work item for next sample
        if (m_DeviceState == DeviceState::Capturing)
        {
            // Re-queue work item for next sample
            return MFPutWaitingWorkItem(m_SampleReadyEvent.get(), 0, m_SampleReadyAsyncResult.get(), &m_SampleReadyKey);
        }
    }
    else
    {
        m_DeviceState = DeviceState::Error;
    }

    return S_OK;
}

//
//  OnAudioSampleRequested()
//
//  Called when audio device fires m_SampleReadyEvent
//
HRESULT CLoopbackCapture::OnAudioSampleRequested()
{
    UINT32 FramesAvailable = 0;
    BYTE* Data = nullptr;
    DWORD dwCaptureFlags;
    UINT64 u64DevicePosition = 0;
    UINT64 u64QPCPosition = 0;
    DWORD cbBytesToCapture = 0;

    auto lock = m_CritSec.lock();

    // If this flag is set, we have already queued up the async call to finialize the WAV header
    // So we don't want to grab or write any more data that would possibly give us an invalid size
    if (m_DeviceState == DeviceState::Stopping)
    {
        return S_OK;
    }

    // A word on why we have a loop here;
    // Suppose it has been 10 milliseconds or so since the last time
    // this routine was invoked, and that we're capturing 48000 samples per second.
    //
    // The audio engine can be reasonably expected to have accumulated about that much
    // audio data - that is, about 480 samples.
    //
    // However, the audio engine is free to accumulate this in various ways:
    // a. as a single packet of 480 samples, OR
    // b. as a packet of 80 samples plus a packet of 400 samples, OR
    // c. as 48 packets of 10 samples each.
    //
    // In particular, there is no guarantee that this routine will be
    // run once for each packet.
    //
    // So every time this routine runs, we need to read ALL the packets
    // that are now available;
    //
    // We do this by calling IAudioCaptureClient::GetNextPacketSize
    // over and over again until it indicates there are no more packets remaining.
    while (SUCCEEDED(m_AudioCaptureClient->GetNextPacketSize(&FramesAvailable)) && FramesAvailable > 0)
    {
        cbBytesToCapture = FramesAvailable * m_CaptureFormat.nBlockAlign;

        // Get sample buffer
        RETURN_IF_FAILED(m_AudioCaptureClient->GetBuffer(&Data, &FramesAvailable, &dwCaptureFlags, &u64DevicePosition, &u64QPCPosition));
        // reset cursor to write over previous output
        printf("\r"); // cursor to beginning of current line

        printf("\n"); // whitespace
        SpectrogramVisualizer(FramesAvailable, Data);
        //printf("\n\n"); // separate two visualizers
        //VolumeVisualizer(FramesAvailable, Data);
        FreqData freqDatas[OUTPUT_FREQ_COUNT]{};
        for (int i = 0; i < OUTPUT_FREQ_COUNT; ++i)
        {
            FreqData data{};
            data.stereo_pos = outputDataDirection[i];
            float mag = outputDataMagnitude[i];
            data.size = mag;

            data.color = Color(0.0f, 0.0f, 0.0f, 1.0f);
            

            freqDatas[i] = data;
        }
        VisualizerCanvas::UpdateVizualizerData(freqDatas, OUTPUT_FREQ_COUNT);

        //printf("\033[1A\033[1A\033[1A"); // cursor back three lines

        // Release buffer back
        m_AudioCaptureClient->ReleaseBuffer(FramesAvailable);

        // Increase the size of our 'data' chunk.  m_cbDataSize needs to be accurate
        m_cbDataSize += cbBytesToCapture;
    }

    return S_OK;
}

//
//  SpectrogramVisualizer()
//
//  Displays frequency data of a single audio buffer in the terminal
//
void CLoopbackCapture::SpectrogramVisualizer(UINT32 FramesAvailable, BYTE* Data)
{
    // Declare a double array of the same size
    double* fullSamples = (double*)malloc(FramesAvailable * 2 * sizeof(double)); // name subject to change, but "in" was confusing
    INT16* inSamples = (INT16*)Data;

    // Convert UINT16 data to doubles for FTT
    for (int i = 0; i < FRAMES_PER_BUFFER * 2; i++) {
        fullSamples[i] = (double)(inSamples[i]) / SHORT_MAX;
    }

    // Copy audio sample to FFTW's input buffer
    for (int i = 0; i < FRAMES_PER_BUFFER; i++) {
        fft_data_left->in[i] = fullSamples[i * 2]; // split the two channels
        fft_data_right->in[i] = fullSamples[(i * 2) + 1];
    }

    // Perform FFT on fft_data->in (results will be stored in fft_data->out)
    fftw_execute(fft_data_left->p);
    fftw_execute(fft_data_right->p);

    // offsets determines the frequency range between each output index
    int offsets =2;
    int freqDivision = 0;

    // starting with a naive approach of just averaging the values per bin 
    // This should be changed in the future, but for now it gives a functional starting point 
    double freqMagnitudeSum = 0;
    double freqDirectionSum = 0; 


    int outputIndex = 0; // indexes the output arrays

    double sum; 
    double diff; 
    double direction;
    double leftMagnitude;
    double rightMagnitude;
    int di;
    // give some separation between the different fft iterations
    std::cout << std::string(10, '\n');

    for (int k = 0; k < FRAMES_PER_BUFFER; k++) {
        
        if (freqDivision == offsets || k == FRAMES_PER_BUFFER-1) {
            if (outputIndex >= OUTPUT_FREQ_COUNT) {
                break;
            }


            bufferDataDirection[bufferIndex][outputIndex] = freqDirectionSum / offsets;
            bufferDataMagnitude[bufferIndex][outputIndex] = freqMagnitudeSum / offsets;

            // average the sums and store them in the output arrays
            double rollingSumDirection = 0;
            double rollingSumMagnitude = 0;

            for (int x = 0; x < ROLLING_AVG_ITERATIONS; x++) {
                rollingSumDirection += bufferDataDirection[x][outputIndex];
                rollingSumMagnitude += bufferDataMagnitude[x][outputIndex];

            }
            outputDataMagnitude[outputIndex] = rollingSumMagnitude / (ROLLING_AVG_ITERATIONS / 2);
            //outputDataMagnitude[outputIndex] = freqMagnitudeSum / offsets; // Averaging the total magnitude reduces it by a lot no averaging for right now

            // outputDataDirection values range from -1(left) to 1 (right) - 0 means centered
            outputDataDirection[outputIndex] = rollingSumDirection/ (ROLLING_AVG_ITERATIONS/4);


            bufferIndex = (bufferIndex + 1)% ROLLING_AVG_ITERATIONS;

            //// ////////////////////////////////////////////////////////////////////////////////////////////
            // This section is just for the sake of printing to the console
            //printf("%f ", freqDirectionSum/offsets);
            di = int(outputDataDirection[outputIndex] * 100 + 100);

            //printf("%d", di);
            // print a bunch of spaces to offset the symbol
            //std::cout << std::string(di, ' ');

            // display full block characters with heights based on frequency intensity
   /*         if (outputDataMagnitude[outputIndex] < 0.125) {
                printf(" \n");
            }
            else if (outputDataMagnitude[outputIndex] < 0.25) {
                printf(" \n");
            }
            else if (outputDataMagnitude[outputIndex] < 0.375) {
                printf("-\n");
            }
            else if (outputDataMagnitude[outputIndex] < 0.5) {
                printf("=\n");
            }
            else if (outputDataMagnitude[outputIndex] < 0.625) {
                printf("o\n");
            }
            else if (outputDataMagnitude[outputIndex] < 0.75) {
                printf("O\n");
            }
            else if (outputDataMagnitude[outputIndex] < 0.875) {
                printf("0\n");
            }
            else {
                printf("#\n");
            }*/
            ////////////////////////////////////////////////////////////////////////////////////

            // this is still important for resetting variables for the next loop!

            freqDivision = 0;
            freqDirectionSum = 0;
            freqMagnitudeSum = 0;
            // alter offsets exponentially to align the frequency ranges with human perception
            //TODO: This function runs into issues when the count gets too big. instead just add to the offsets or something
            offsets = FRAMES_PER_BUFFER * (std::pow(1.3, outputIndex - OUTPUT_FREQ_COUNT));
            outputIndex++;
        }

        // calculate the magnitude and direction for each frequency bin
        leftMagnitude = std::abs(fft_data_left->out[k]);
        rightMagnitude = std::abs(fft_data_right->out[k]);

        sum = (leftMagnitude + rightMagnitude)/2;
        diff = rightMagnitude - leftMagnitude;
        
        direction = diff / sum/2;
        // if they are equal, potential for a divide by zero error - it would be in the center so set direction to zero
        if (isnan(direction) || isinf(direction)) {
            direction = 0;
        }
        freqMagnitudeSum += sum;
        freqDirectionSum += direction;

        freqDivision++;
        
  
    }
    
    // Display the buffered changes to stdout in the terminal
    fflush(stdout);

    free(fullSamples);
    return;
}

//
//  VolumeVisualizer()
//
//  Displays signal data for a single audio buffer in the terminal for two channels
//
void CLoopbackCapture::VolumeVisualizer(UINT32 FramesAvailable, BYTE* Data)
{
    // volume visualizer
    INT16* in = (INT16*)Data;

    printf("\33[?25l");

    int vol_l = 0;
    int vol_r = 0;

    for (unsigned long i = 0; i < FramesAvailable * 2; i += 2) {
        vol_l = std::max(vol_l, std::abs(in[i]));
        vol_r = std::max(vol_r, std::abs(in[i + 1]));
    }
    //printf("left: %d, right: %d\n", vol_l, vol_r);

    int dispsize = 100;
    float volume_multiplier = 2;

    float vol_l_proportion = vol_l / (float)SHORT_MAX * volume_multiplier;
    float vol_r_proportion = vol_r / (float)SHORT_MAX * volume_multiplier;

    for (int i = 0; i < dispsize; i++) {
        float barproportion = i / (float)dispsize;
        if (barproportion <= vol_l_proportion && barproportion <= vol_r_proportion) {
            printf("█");
        }
        else if (barproportion <= vol_l_proportion) {
            printf("▀");
        }
        else if (barproportion <= vol_r_proportion) {
            printf("▄");
        }
        else {
            printf(" ");
        }
    }

    fflush(stdout);

    return;
}


//
//  InitializeFFT()
//
//  Initialize fft_data object for FFT and spectrogram use
//
void CLoopbackCapture::InitializeFFT()
{   
    // initialize data object used for fft
    fft_data_left = (fft_callback_data*)malloc(sizeof(fft_callback_data));
    fft_data_right = (fft_callback_data*)malloc(sizeof(fft_callback_data));


    outputDataDirection = (double*)malloc(sizeof(double) * OUTPUT_FREQ_COUNT);
    outputDataMagnitude = (double*)malloc(sizeof(double) * OUTPUT_FREQ_COUNT);

    bufferDataDirection = (double**)malloc(sizeof(double*) * ROLLING_AVG_ITERATIONS);
    bufferDataMagnitude = (double**)malloc(sizeof(double*) * ROLLING_AVG_ITERATIONS);


    for (int x = 0; x < ROLLING_AVG_ITERATIONS; x++) {
        bufferDataDirection[x] = (double*)calloc( OUTPUT_FREQ_COUNT, sizeof(double));
        bufferDataMagnitude[x] = (double*)calloc(OUTPUT_FREQ_COUNT, sizeof(double));

    }

    bufferIndex = 0;

    // allocate memory for fft buffers
    fft_data_left->in = (double*)malloc(sizeof(double) * FRAMES_PER_BUFFER);
    fft_data_left->out = (double*)malloc(sizeof(double) * FRAMES_PER_BUFFER);

    fft_data_right->in = (double*)malloc(sizeof(double) * FRAMES_PER_BUFFER);
    fft_data_right->out = (double*)malloc(sizeof(double) * FRAMES_PER_BUFFER);

    // initialize spectrograph variables
    double sampleRatio = FRAMES_PER_BUFFER / (SAMPLE_RATE * 1.0);
    fft_data_left->startIndex = std::ceil(sampleRatio * SPECTRO_FREQ_START);
    fft_data_left->spectroSize = std::min(
        std::ceil(sampleRatio * SPECTRO_FREQ_END),
        FRAMES_PER_BUFFER / 2.0
    ) - fft_data_left->startIndex;

    fft_data_right->startIndex = std::ceil(sampleRatio * SPECTRO_FREQ_START);
    fft_data_right->spectroSize = std::min(
        std::ceil(sampleRatio * SPECTRO_FREQ_END),
        FRAMES_PER_BUFFER / 2.0
    ) - fft_data_right->startIndex;

    // set up fftw plan
    fft_data_left->p = fftw_plan_r2r_1d(
        FRAMES_PER_BUFFER, fft_data_left->in, fft_data_left->out, FFTW_R2HC, FFTW_ESTIMATE
    );

    fft_data_right->p = fftw_plan_r2r_1d(
        FRAMES_PER_BUFFER, fft_data_right->in, fft_data_right->out, FFTW_R2HC, FFTW_ESTIMATE
    );

    return;
}
