
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
#include "Packets.h"
  
// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
unsigned long ulThisLoopTime;
SDalekMotorPacket sdPacket;
void setup() {
  Serial.begin(115200);
  ulThisLoopTime  = millis();
  sdPacket.byPacketDataX = 0;
  sdPacket.byPacketDataY = 0;
  sdPacket.byPacketDataZ = 0;
  sdPacket.byPacketID = millis();
  sdPacket.byDeviceID = 0;
}


void loop() {
	delay(100);
	
	sdPacket.byPacketDataX+=5;
	if (sdPacket.byPacketDataX == 255)
	{
		sdPacket.byPacketDataX = 0;
		sdPacket.byPacketDataY += 5;
	}
	if (sdPacket.byPacketDataY == 255)
	{
		sdPacket.byPacketDataY = 0;
		++sdPacket.byPacketDataZ;
	}
	sdPacket.byPacketID = millis();
	sdPacket.byDeviceID = 0;
	AddCRC(&sdPacket);
	Serial.write((uint8_t*)&sdPacket, 9);
	
}
