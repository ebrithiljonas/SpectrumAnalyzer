#include <Arduino.h>
#include "arduinoFFT.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "settings.h"
#include "LED.h"
#include <stdlib.h>

// ----- Variables FFT -----

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

// ----- Variables FastLED -----

int amplitude = AMPLITUDE;
LED Bar;

// ----- Variables MQTT ------

WiFiClient espClient;
PubSubClient client(espClient);

// ----- General Variables ------

//=====================MQTT=========================

void parseMessage(String topic, String message)
{

	if (topic.equals(TOPIC_AMPLITUDE))
	{
		int b = message.toInt();
		Serial.println(b);
		amplitude = b;
	}
	else if (topic.equals(TOPIC_BRIGHTNESS))
	{
		int b = message.toInt();
		Serial.println(b);
		Bar.setBrightness(b);
	}
	else if (topic.equals(TOPIC_MODE))
	{
		int b = message.toInt();
		Bar.setMode(b);
	}
	else if (topic.equals(TOPIC_COLOR_1))
	{
		int b = strtol(message.c_str(), NULL, 16);
		Bar.setColor(b,0);
	}
	else if (topic.equals(TOPIC_COLOR_2))
	{
		int b = strtol(message.c_str(), NULL, 16);
		Bar.setColor(b,1);
	}
}

void callback(char *topic, byte *message, unsigned int length)
{
	Serial.print("Message arrived on topic: ");
	Serial.print(topic);
	Serial.print(". Message: ");
	String m;

	for (int i = 0; i < length; i++)
	{
		Serial.print((char)message[i]);
		m += (char)message[i];
	}
	Serial.println();

	String t = String(topic);

	parseMessage(t, m);
}

void setupWifi()
{
	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void subscribeTopics()
{
	client.subscribe(TOPIC_ROOT "+");
}

void reconnect()
{
	// Loop until we're reconnected
	while (!client.connected())
	{
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect(NAME, mqtt_server_user, mqtt_server_pw))
		{
			Serial.println("connected");
			// Subscribe
			subscribeTopics();
		}
		else
		{
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setupMQTT()
{
	client.setServer(mqtt_server_ip, mqtt_server_port);
	client.setCallback(callback);
}

//END==================MQTT=========================

//=====================FFT==========================

int ampLED[NUM_STRIPS];

void sampleAnalogIn()
{
	/*SAMPLING*/
	microseconds = micros();
	int max = 100;
	for (int i = 0; i < SAMPLES; i++)
	{
		vReal[i] = (analogRead(ADC_CHANNEL));
		vImag[i] = 0;
		if (vReal[i] > max)
			max = vReal[i];
		//Serial.println(vReal[i]);
		while (micros() - microseconds < sampling_period_us)
		{
			//empty loop
		}
		microseconds += sampling_period_us;
	}
	// Remove DC
	FFT.DCRemoval(vReal, SAMPLES);
	//Compute FFT
	FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
	FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
	FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
	//double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
	max = max + (max / 10);

	if (OUTPUT_FFT)
	{
		int h;
		for (int i = 0; i < SAMPLES; i++)
		{
			h = vReal[i];
			Serial.print(h);
			Serial.print(",");
		}
		Serial.println();
	}

	int numSamplesStrip[] = {1, 1, 1, 4, 5, 9, 15, 25, 43, 73, 124, 210};

#if OUTPUT_LED_DATA
	float amplitudeFactor[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
#else
	float amplitudeFactor[] = {37.21, 34.27, 36.73, 28.54, 18.42, 19.9, 11.65, 6.42, 12.6, 13.91, 4.37, 1.29};
#endif

	int oldIndex = 5;

	for (int i = 0; i < NUM_STRIPS; i++)
	{

		double tempAmplitude = 0;

		for (int t = 0; t < numSamplesStrip[i]; t++)
		{
			int index = oldIndex + t;
			tempAmplitude += vReal[index];
		}
		oldIndex += numSamplesStrip[i];
		int tempA = map(tempAmplitude, 0, amplitude * numSamplesStrip[i] * amplitudeFactor[i], 0, NUM_LEDS_PER_STRIP);
		if (!OUTPUT_LED_DATA)
		{
			tempA = constrain(tempA, 1, NUM_LEDS_PER_STRIP);
		}
		ampLED[i] = (int)tempA;
	}

	if (OUTPUT_LED_DATA)
	{
		for (int i = 0; i < NUM_STRIPS; i++)
		{
			Serial.print(ampLED[i]);
			Serial.print(",");
		}
		Serial.println();
	}
}

//END==================FFT==========================

void setupFFT()
{
	sampling_period_us = round((1000000.0 / SAMPLING_FREQUENCY));
}

void setup()
{
	setupFFT();
	Bar.setMode(0);
	if (USE_WLAN)
	{
		setupWifi();
		setupMQTT();
	}

	Serial.begin((512000));
}

void loop()
{

	sampleAnalogIn();
	Bar.refreshLED(ampLED);

	if (USE_WLAN)
	{

		if (!client.connected())
		{
			reconnect();
		}
		client.loop();
	}
}