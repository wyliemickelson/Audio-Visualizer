#pragma once

#include <VisualizerWindow.h>
#include <AudioClient.h>
#include <mmdeviceapi.h>
#include <initguid.h>
#include <guiddef.h>
#include <mfapi.h>

#include <wrl\implements.h>
#include <wil\com.h>
#include <wil\result.h>

#include <fftw3.h>
#include "Common.h"

#define BITS_PER_BYTE 8
#define SHORT_MAX 32767
#define SAMPLE_RATE 44100
#define BITS_PER_SAMPLE 16
#define N_CHANNELS 2
#define FRAMES_PER_BUFFER SAMPLE_RATE / 100 // 256 (ish) frequency bins

#define SPECTRO_FREQ_START 20  // Lower bound of the displayed spectrogram (Hz)
#define SPECTRO_FREQ_END 20000 // Upper bound of the displayed spectrogram (Hz)

#define OUTPUT_FREQ_COUNT 6 // its currently not good at distinguishing separate low frequency bands, particularly below 5
#define PROCESSING_FREQ_CLIP 1 // the super low frequencies arent exactly helpful - clip off the bottom few bins and combine them with the first index
#define PROCESSING_FREQ_COUNT OUTPUT_FREQ_COUNT + PROCESSING_FREQ_CLIP
#define ROLLING_AVG_ITERATIONS 16

using namespace Microsoft::WRL;

typedef struct {
    double* in;
    double* out;
    fftw_plan p;
    int startIndex;
    int spectroSize;
}fft_callback_data;

static fft_callback_data* fft_data_left;
static fft_callback_data* fft_data_right;
static double* outputDataDirection;
static double* outputDataMagnitude;

static double** bufferDataDirection;
static double** bufferDataMagnitude;

static int bufferIndex; 


class CLoopbackCapture :
    public RuntimeClass< RuntimeClassFlags< ClassicCom >, FtmBase, IActivateAudioInterfaceCompletionHandler >
{
public:
    CLoopbackCapture() = default;
    ~CLoopbackCapture();

    HRESULT StartCaptureAsync(DWORD processId, VisualizerWindow* visualizerContainer);
    HRESULT StopCaptureAsync();

    METHODASYNCCALLBACK(CLoopbackCapture, StartCapture, OnStartCapture);
    METHODASYNCCALLBACK(CLoopbackCapture, StopCapture, OnStopCapture);
    METHODASYNCCALLBACK(CLoopbackCapture, SampleReady, OnSampleReady);
    METHODASYNCCALLBACK(CLoopbackCapture, FinishCapture, OnFinishCapture);

    // IActivateAudioInterfaceCompletionHandler
    STDMETHOD(ActivateCompleted)(IActivateAudioInterfaceAsyncOperation* operation);

private:
    // NB: All states >= Initialized will allow some methods
        // to be called successfully on the Audio Client
    enum class DeviceState
    {
        Uninitialized,
        Error,
        Initialized,
        Starting,
        Capturing,
        Stopping,
        Stopped,
    };

    VisualizerWindow* visualizer;

    HRESULT OnStartCapture(IMFAsyncResult* pResult);
    HRESULT OnStopCapture(IMFAsyncResult* pResult);
    HRESULT OnFinishCapture(IMFAsyncResult* pResult);
    HRESULT OnSampleReady(IMFAsyncResult* pResult);

    HRESULT InitializeLoopbackCapture();
    HRESULT OnAudioSampleRequested();

    HRESULT ActivateAudioInterface(DWORD processId);
    HRESULT FinishCaptureAsync();

    void CircularVisualizer(UINT32 FramesAvailable, BYTE* Data);
    void SpectrogramVisualizer(UINT32 FramesAvailable, BYTE* Data);
    void VolumeVisualizer(UINT32 FramesAvailable, BYTE* Data);
    void InitializeFFT();

    HRESULT SetDeviceStateErrorIfFailed(HRESULT hr);

    wil::com_ptr_nothrow<IAudioClient> m_AudioClient;
    WAVEFORMATEX m_CaptureFormat{};
    UINT32 m_BufferFrames = 0;
    wil::com_ptr_nothrow<IAudioCaptureClient> m_AudioCaptureClient;
    wil::com_ptr_nothrow<IMFAsyncResult> m_SampleReadyAsyncResult;

    wil::unique_event_nothrow m_SampleReadyEvent;
    MFWORKITEM_KEY m_SampleReadyKey = 0;
    wil::unique_hfile m_hFile;
    wil::critical_section m_CritSec;
    DWORD m_dwQueueID = 0;

    // used to communicate between the main thread
    // and the ActivateCompleted callback.
    HRESULT m_activateResult = E_UNEXPECTED;

    DeviceState m_DeviceState{ DeviceState::Uninitialized };
    wil::unique_event_nothrow m_hActivateCompleted;
    wil::unique_event_nothrow m_hCaptureStopped;
};
