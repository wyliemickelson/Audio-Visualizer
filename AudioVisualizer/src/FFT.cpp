#include "FFT.h"

FFT::FFT(int16_t bufferSize)
{
    buffer = new int16_t[bufferSize];
    bufferIndex = 0;
    this->bufferSize = bufferSize;
    __atomic_store_n(&readyFlag, false, __ATOMIC_RELEASE);
}

// should be called in a loop. automatically checks if the buffer is ready and then executes when it is.
// if nullptr is returned, fft did not occur -- nothing needs to be updated
// TODO this feels like a bad solution, discuss with groupmates on understandability
float *FFT::attemptExecuteFFT()
{
    // check if the readyFlag is flipped across all threads
    if (__atomic_load_n(&readyFlag, __ATOMIC_ACQUIRE))
    {
        __atomic_store_n(&readyFlag, false, __ATOMIC_RELEASE);
        return exectuteFFT();
    }
    return nullptr;
}

// update a buffer to ensure a specific amount of data is stored in the fft. If its full, the data will be passed
// TODO: this may cause issues with how data is cut off. make sure this works!!
void FFT::updateBuffer(int16_t *data, int16_t size)
{
    for (int i = 0; i < size; i++)
    {
        // check the ready flag
        if (!__atomic_load_n(&readyFlag, __ATOMIC_ACQUIRE))
        {
            buffer[bufferIndex] = data[i];
            bufferIndex++;

            if (bufferIndex > bufferSize)
            {
                bufferIndex = 0;
                // set the ready flag to true if the buffer is full
                __atomic_store_n(&readyFlag, true, __ATOMIC_RELEASE);
            }
        }
    }
}
 
// recurisve function to execute the fft
float *FFT::exectuteFFT()
{
    float *result = new float[bufferSize];
    for (int k = 0; k < bufferSize; k+=2)
    {
        float subResultReal = 0;
        float subResultImaginary = 0;
        for (int n = 0; n < bufferSize; n++)
        {
            float exponent = -6.2831853071 * float(k) * float(n) / float(bufferSize);
            float realResult = buffer[n] * cos(exponent);
            float imaginaryResult = buffer[n] * sin(exponent);
            subResultReal += realResult;
            subResultImaginary += imaginaryResult;
        }
        result[k/2] = sqrt(subResultReal * subResultReal + subResultImaginary * subResultImaginary) / (bufferSize * 128.5);
    }
    return result;
}
