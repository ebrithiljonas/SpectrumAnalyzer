/*
  LED.h - LED functions for SpectrumAnalyzer
  Author: Jonas Halbeisen
*/


#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#ifndef LED_h
#define LED_h

#define COLOR_ORDER GRB
#define NUM_STRIPS 12
#define NUM_LEDS_PER_STRIP 25

class LED
{
    public:
        //Constructor
        LED();
        void refreshLED(int *amp);
        void setMode(int m);
        void setBrightness(int b);
        void setColor(int color, int index) ;

    private:
        CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
        unsigned long oldMillis = 0;
        int maxLED[NUM_STRIPS];
        int mode = 1;
        CRGB colors[2]= {CRGB::Green, CRGB::Red};
        // Modes:
        void off(); // Mode 0
        void bars(int *amp, bool withMax); // Mode 1: without falling max, Mode 2: with falling max
        void middeBars(int *amp, bool withMax); // Mode 3: without falling max, Mode 4: with falling max

};









#endif