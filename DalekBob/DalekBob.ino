
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


CMotor cmLeftMotor(2,4,3,5);
CMotor cmRightMotor(7,8,6,9);
  
// Expose Espressif SDK functionality - wrapped in ifdef so that it still
// compiles on other platforms
unsigned long ulLastData;
unsigned long ulLastPacket;

unsigned long ulLastMessageTime;
SDalekMotorPacket LastRecievedPacket;
char cBytesOfCurrentPacketObtained;
SDalekMotorPacket CurrentAssemblingPacket;

void setup() {
  Serial.begin(115200);
  cmLeftMotor.SetMotorSpeed(0);
  cmRightMotor.SetMotorSpeed(0);
  cBytesOfCurrentPacketObtained = 0;
}


void loop() {
  unsigned long ulThisLoopTime = millis();

  if (Serial.available()) {
    ulLastData = ulThisLoopTime;
  
    char inByte = Serial.read();
    ((unsigned char*)&CurrentAssemblingPacket)[cBytesOfCurrentPacketObtained] = inByte;
    
    if(++cBytesOfCurrentPacketObtained == sizeof(SDalekMotorPacket))
    {
      cBytesOfCurrentPacketObtained = 0;
      LastRecievedPacket = CurrentAssemblingPacket;
	  uint16_t packetCRC = LastRecievedPacket.i16PacketRC;
	  AddCRC(&LastRecievedPacket);
	  if (LastRecievedPacket.i16PacketRC == packetCRC)
      {
        ulLastPacket = ulThisLoopTime;
        Serial.write("Packet recieved, passed CRC\n\r");
        cmLeftMotor.SetMotorSpeed(LastRecievedPacket.byPacketDataX);
        cmRightMotor.SetMotorSpeed(LastRecievedPacket.byPacketDataY);
      }
      else
      {
		  
		  char rgcBuf[50];
		  sprintf(rgcBuf, "Packet recieved, failed CRC 0x%02X, 0x%02X\n\r",LastRecievedPacket.i16PacketRC,packetCRC);
		  Serial.write(rgcBuf);
        //Dump out anything in the serial port, to clear anything trashed
        while(Serial.available())
          Serial.read();
      }
    }
    
  }
  
  if(ulThisLoopTime > (unsigned long)5000)
  if(ulThisLoopTime - ulLastData > ((unsigned long)50))
  {
    cBytesOfCurrentPacketObtained = 0;
  }
  if(ulThisLoopTime - ulLastPacket > ((unsigned long) 500))
  {
      ulLastData  = ulLastPacket = ulThisLoopTime;
      cmLeftMotor.SetMotorSpeed(0);
      cmRightMotor.SetMotorSpeed(0);
      Serial.write("Recieve timeout: Motor Shutdown\n\r");
  }
  delay(10);
}
