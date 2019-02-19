/*
  LED.cpp - LED functions for SpectrumAnalyzer
  Author: Jonas Halbeisen
*/

#include "LED.h"

//Constructor

LED::LED()
{

	// Pins: 13, 12, 14, 27 ,26, 25, 2, 4, 5, 18, 19, 21
	FastLED.addLeds<WS2811, 21, COLOR_ORDER>(leds[0], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 19, COLOR_ORDER>(leds[1], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 18, COLOR_ORDER>(leds[2], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 5, COLOR_ORDER>(leds[3], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 4, COLOR_ORDER>(leds[4], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 2, COLOR_ORDER>(leds[5], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 25, COLOR_ORDER>(leds[6], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 26, COLOR_ORDER>(leds[7], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 27, COLOR_ORDER>(leds[8], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 14, COLOR_ORDER>(leds[9], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 12, COLOR_ORDER>(leds[10], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
	FastLED.addLeds<WS2811, 13, COLOR_ORDER>(leds[11], NUM_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);

	FastLED.setBrightness(255);
}

void LED::off()
{
	for (int x = 0; x < NUM_STRIPS; x++) 
	{
		for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
		{
			leds[x][i] = CRGB::Black;
		}
	}
}

void LED::bars(int *amp, bool withMax)
{

	if (withMax)
	{
		unsigned long temp = millis();
		if ((temp - oldMillis) >= 100)
		{
			oldMillis = temp;
			for (int x = 0; x < NUM_STRIPS; x++)
			{
				maxLED[x] -= 1;
			}
		}
	}

	for (int x = 0; x < NUM_STRIPS; x++)
	{
		if (withMax)
		{
			if (amp[x] > maxLED[x])
			{
				maxLED[x] = amp[x];
			}
		}
		else
		{
			maxLED[x] = amp[x];
		}

		for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
		{
			if (i < amp[x] - 1)
			{ // LED under Amplitude
				leds[x][i] = colors[0];
			}
			else if (i == maxLED[x] - 1)
			{ // LED on Max Amplitude
				leds[x][i] = colors[1];
			}
			else
			{ // LED over Amplitude
				leds[x][i] = CRGB::Black;
			}
		}
	}
}

void LED::middeBars(int *amp, bool withMax) 
{

	int half = NUM_LEDS_PER_STRIP / 2;

	if (withMax)
	{
		unsigned long temp = millis();
		if ((temp - oldMillis) >= 100)
		{
			oldMillis = temp;
			for (int x = 0; x < NUM_STRIPS; x++)
			{
				maxLED[x] -= 1;
			}
		}
	}

	for (int x = 0; x < NUM_STRIPS; x++)
	{
		int newAmp = amp[x] / 2;
		if (withMax)
		{
			if (newAmp > maxLED[x])
			{
				maxLED[x] = newAmp;
			}
		}
		else
		{
			maxLED[x] = newAmp;
		}

		for (int i = 0; i < half; i++)
		{
			if (i < newAmp - 1)
			{ // LED under Amplitude
				leds[x][i + half - 1] = colors[0];
				leds[x][half - i - 1] = colors[0];
			}
			else if (i == maxLED[x] - 1)
			{ // LED on Max Amplitude
				leds[x][i + half - 1] = colors[1];
				leds[x][half - i - 1] = colors[1];
			}
			else
			{ // LED over Amplitude
				leds[x][i + half - 1] = CRGB::Black;
				leds[x][half - i - 1] = CRGB::Black;
			}
		}

	}

}

void LED::refreshLED(int *amp)
{
	switch (mode)
	{
	case 0:
		off();
		break;
	case 1:
		bars(amp, false);
		break;
	case 2:
		bars(amp, true);
		break;
	case 3:
		middeBars(amp, false);
		break;
	case 4:
		middeBars(amp, true);
		break;

	default:
		break;
	}
	FastLED.show();
}

void LED::setMode(int m)
{
	mode = m;
}

void LED::setBrightness(int b)
{
	FastLED.setBrightness(b);
}

void LED::setColor(int color, int index) 
{
	colors[index] = color;
}