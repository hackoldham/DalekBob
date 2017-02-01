
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
#include "MotorDriver.h"
#include "DFPlayer_Mini_Mp3.h"
#include <SoftwareSerial.h>
// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
unsigned long ulLastPacket;

unsigned long ulLastMessageTime;
SDalekMotorPacket CurrentAssemblingPacket;

SoftwareSerial DFPlayerComms(10,9);
void WaitForSD()
{
	while (true)
	{
		mp3_get_state();
		uint16_t res = mp3_wait_state();
		uint8_t RetType = res & 0xFF;
		uint8_t Val = res >> 8;
		if(Val == 2)	
		{ 
			Serial.print("Card inserted: Found ");
			Serial.println(RetType);
			break;
		}
		else
		{
			Serial.print("Waiting - ");
			Serial.print(Val);
			Serial.print(",");
			Serial.println(RetType);
			delay(100);
		}
	}
}
void setup() {

	Serial.begin(115200);
	DFPlayerComms.begin(9600);
	mp3_set_serial(DFPlayerComms);
	Serial.println("Device Reset");
	PlaySample(1, 20);
	PlaySample(2, 20);
	PlaySample(3, 20);
	PlaySample(4, 20);
	PlaySample(5, 20);
	PlaySample(6, 20);
	PlaySample(7, 20);
}
char rgcBuf[50];
void PlaySample(uint16_t cSample, uint16_t cVolume)
{
	//Play sample X
	Serial.print("About to play sample ");
	Serial.print(cSample);
	Serial.print(" At volume ");
	Serial.println(cVolume);
	Serial.println("Setting volume");
	mp3_set_volume(cVolume);
	Serial.println("volume set");
	delay(100);
	while (digitalRead(2))
	{
		Serial.print("Play attempt\n\r");
		mp3_play(cSample);
		delay(100);
	}
	byte byCurVal = 0;
	Serial.print("Play started\n\r");
	while (!digitalRead(2))
	{
		++byCurVal;
		if (byCurVal < 128)
			byCurVal = 128;
		analogWrite(3, byCurVal);
		delay(5);
	}
	mp3_stop();
	Serial.write("\Done");
	analogWrite(3, 0);
}
void loop() {
	unsigned long ulThisLoopTime = millis();
	uint8_t vol = 0;
	
	if (Serial.available()) {

		bool bWasReadOK = false;
		char inByte = Serial.read();
		char* pcBuffer = (char*)(&CurrentAssemblingPacket);
		pcBuffer[8] = inByte;
		//Store the recieved CRC
		uint16_t packetCRC = CurrentAssemblingPacket.i16PacketRC;
		//Recalculate the CRC based on recieved data
		AddCRC(&CurrentAssemblingPacket);
		//If the calculated matched the one we recieved
		if (CurrentAssemblingPacket.i16PacketRC == packetCRC)
		{
			bWasReadOK = true;
			ulLastPacket = ulThisLoopTime;
			if (CurrentAssemblingPacket.byDeviceID == eDevice_SoundRequest)
			{
				PlaySample(CurrentAssemblingPacket.byPacketDataX, CurrentAssemblingPacket.byPacketDataY);
			}
			else
			{
				//Data for another device recieved
			}
		}
		else
		{
			//Restore the old byte
			CurrentAssemblingPacket.i16PacketRC = packetCRC;
		}
			//Move all bytes up 1 so the new data gets added to the end
		char iTarget = 0;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 1;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 2;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 3;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 4;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 5;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 6;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
		iTarget = 7;
		((char*)(&CurrentAssemblingPacket))[iTarget] = ((char*)(&CurrentAssemblingPacket))[iTarget + 1];
	}
	delay(1);
}
