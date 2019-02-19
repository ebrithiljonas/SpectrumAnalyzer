/*
  FFT.h - FFT functions for SpectrumAnalyzer
  Author: Jonas Halbeisen
*/

#ifndef FFT_h
#define FFT_h

#include <arduinoFFT.h>

#define COLOR_ORDER GRB

class FFT
{
    public:
        FFT(int pin, int samples_in, int samplingFrequency_in, int amplitude_in, int numStrips_in, int numLEDPerStrip_in);
        void sampleAnalogIn(int *arr, double data[]);

    private:
        int samples;
        int samplingFrequency;
        int amplitude;
        int adcChannel;
        int numStrips;
        int numLEDPerStrip;
        arduinoFFT fourier;

};


#endif