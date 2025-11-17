#ifndef FFT_H
#define FFT_H

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdint.h>
#endif
#include <cmath>

class FFT
{

public:
    int16_t *buffer;
    int16_t bufferIndex;
    int16_t bufferSize;
    volatile boolean readyFlag;

    FFT(int16_t bufferSize);
    float *attemptExecuteFFT();
    void updateBuffer(int16_t *data, int16_t size);

private:
    float *exectuteFFT();
};

#endif
