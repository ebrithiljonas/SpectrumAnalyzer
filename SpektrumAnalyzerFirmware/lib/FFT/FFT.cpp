/*
  FFT.cpp - FFT functions for SpectrumAnalyzer
  Author: Jonas Halbeisen
*/

#include "FFT.h"

// Contructor
FFT::FFT(int pin, int samples_in, int samplingFrequency_in, int amplitude_in, int numStrips_in, int numLEDPerStrip_in) {
    samples = samples_in;
    samplingFrequency = samplingFrequency_in;
    amplitude = amplitude_in;
    adcChannel = pin;
    numStrips = numStrips_in;
    numLEDPerStrip = numLEDPerStrip_in;

    fourier = arduinoFFT();
}

void FFT::sampleAnalogIn(int *arr, double data[]) {
  /*SAMPLING*/

/*

    double vImag[samples];
    double vReal[samples];

    int numSamplesStrip = samples / numStrips;

    for(int i=0; i< samples; i++)
    {
        vReal[i] = data[i];
    }
    
    fourier.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    fourier.Compute(vReal, vImag, samples, FFT_FORWARD);
    fourier.ComplexToMagnitude(vReal, vImag, samples);

    for(int i=0; i<numStrips; i++) {

        double tempAmplitude = 0;
        for(int t=0; t < numSamplesStrip; t++) {
            int index = (numSamplesStrip * i) + t;
            tempAmplitude += vReal[index];
        }
        int tempA = map(tempAmplitude, 0, amplitude * numSamplesStrip, 0, numLEDPerStrip);
        tempA = constrain(tempA, 0, numLEDPerStrip);
        arr[i] = (int)tempA;
    }
    
    */

}