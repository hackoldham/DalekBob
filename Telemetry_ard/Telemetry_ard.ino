
/*
 * NativeSdk by Simon Peter
 * Access functionality from the Espressif ESP8266 SDK
 * This example code is in the public domain
 * 
 * This is for advanced users.
 * Note that this makes your code dependent on the ESP8266, which is generally
 * a bad idea. So you should try to use esp8266/Arduino functionality
 * where possible instead, in order to abstract away the hardware dependency.
 */
#include <Wire.h>
#include "Adafruit_ADS1015.h"
#include "Packets.h"
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
unsigned long ulLastMessageTime;
SDalekMotorPacket LastRecievedPacket;
float   fVoltMultiplier = 0.0078125;    /* ADS1015 @ +/- 6.144V gain (12-bit results) */
										//float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */
float   fAmpMultiplier = 0.0078125;//mv drop

void setup() {
	Serial.begin(115200);
	Serial.println("Hello!");

	Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
	Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

	// The ADC input range (or gain) can be changed via the following
	// functions, but be careful never to exceed VDD +0.3V max, or to
	// exceed the upper and lower limits if you adjust the input range!
	// Setting these values incorrectly may destroy your ADC!
	//                                                         ADS1115
	//                                                        -------
	// ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V    0.1875mV (default)
	// ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  0.125mV
	//ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  0.0625mV
	// ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  0.03125mV
	// ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  0.015625mV
	ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  0.0078125mV
	fAmpMultiplier *= 100; //Amp shunt rating
	fAmpMultiplier /= 75; //shunt mv rating
	ads.begin();
}
char rgcBuf[50];

	
void loop() {
	int16_t iResultV;
	int16_t iResultA;

	
	
	iResultV = ads.readADC_Differential_0_1();
	iResultA = ads.readADC_Differential_2_3();
	Serial.print("{\n\r'mvRaw': '");
	Serial.print(iResultV); 
	Serial.print("',\n\r 'mvDisplay': '");
	Serial.print(iResultV * fVoltMultiplier); 
	Serial.print("mV',\n\r 'ARaw': '");
	Serial.print(iResultA); 
	Serial.print("',\n\r 'ADisplay': '");
	Serial.print(iResultA * fVoltMultiplier); Serial.println("A'\n\r}");
	delay(250);
}
