
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

 #define PIN_BRAKEA 12
 #define PIN_BRAKEB 11

CMotor cmLeftMotor(2,4,3,5);
CMotor cmRightMotor(7,8,6,9);
  
// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
unsigned long ulLastPacket;

unsigned long ulLastMessageTime;
SDalekMotorPacket LastRecievedPacket;
char cBytesOfCurrentPacketObtained;
SDalekMotorPacket CurrentAssemblingPacket;

void setup() {
    pinMode(PIN_BRAKEA,OUTPUT);
    pinMode(PIN_BRAKEB,OUTPUT);
    digitalWrite(PIN_BRAKEA,0);
    digitalWrite(PIN_BRAKEB,0);

  Serial.begin(115200);
  cmLeftMotor.SetMotorSpeed(0);
  cmRightMotor.SetMotorSpeed(0);
  cBytesOfCurrentPacketObtained = 0;
  
}
char rgcBuf[50];

void loop() {
	unsigned long ulThisLoopTime = millis();

	if (Serial.available()) 
	{

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
			if (CurrentAssemblingPacket.byDeviceID == eDevice_MotorControl)
			{
				cmLeftMotor.SetMotorSpeed(CurrentAssemblingPacket.byPacketDataX);
				cmRightMotor.SetMotorSpeed(CurrentAssemblingPacket.byPacketDataY);
				digitalWrite(PIN_BRAKEA, LastRecievedPacket.byPacketDataX == 127);
				digitalWrite(PIN_BRAKEB, LastRecievedPacket.byPacketDataY == 127);
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
  
	  if (ulThisLoopTime > (unsigned long)50)
	  {
		  //If we have no data for 0.5s, lock everything down
		  if (ulThisLoopTime - ulLastPacket > ((unsigned long)500))
		  {
			  ulLastPacket = ulThisLoopTime;
			  cmLeftMotor.SetMotorSpeed(127);
			  cmRightMotor.SetMotorSpeed(127);
			  digitalWrite(PIN_BRAKEA, 0);
			  digitalWrite(PIN_BRAKEB, 0);
			  Serial.write("Recieve timeout: Motor Shutdown\n\r");
		  }
	  }
	  delay(10);
}
