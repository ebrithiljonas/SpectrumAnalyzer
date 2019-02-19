
// ----- Debug-MODES -----

#define USE_WLAN true
#define OUTPUT_FFT false
#define OUTPUT_LED_DATA false

// ----- Settings FFT -----

#define SAMPLES 512*2            // Must be a power of 2
#define SAMPLING_FREQUENCY 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE 4000 // Depending on your audio source level, you may need to increase this value
#define ADC_CHANNEL 34

// ----- Settings FastLED -----


#define NUM_STRIPS 12
#define NUM_LEDS_PER_STRIP 25

// ----- Settings MQTT -----

#define NAME "SpectrumAnalyzer"

const char* ssid = "EbrithilHome";
const char* password = "x13ml57b";
const char* mqtt_server_ip   = "10.0.1.109";
const int   mqtt_server_port = 1883;
const char* mqtt_server_user = "devices";
const char* mqtt_server_pw   = "tXj8LWmjnN97tcdpG6Vu";

// ----- Settings MQTT Topics-----

#define TOPIC_ROOT "Displays/Inside/SpectrumAnalyzer/"
#define TOPIC_AMPLITUDE TOPIC_ROOT "Amplitude"
#define TOPIC_BRIGHTNESS TOPIC_ROOT "Brightness"
#define TOPIC_MODE TOPIC_ROOT "Mode"
#define TOPIC_COLOR_1 TOPIC_ROOT "Color_1"
#define TOPIC_COLOR_2 TOPIC_ROOT "Color_2"