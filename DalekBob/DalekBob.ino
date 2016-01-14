
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
  // Call Espressif SDK functionality - wrapped in ifdef so that it still
  // compiles on other platforms
   if (Serial.available()) {
    ulLastMessageTime = ulThisLoopTime;
    char inByte = Serial.read();
    
    ((unsigned char*)&CurrentAssemblingPacket)[cBytesOfCurrentPacketObtained] = inByte;
    if(++cBytesOfCurrentPacketObtained == sizeof(SDalekMotorPacket))
    {
      cBytesOfCurrentPacketObtained = 0;
      LastRecievedPacket = CurrentAssemblingPacket;
      AddCRC(&LastRecievedPacket);
      if(LastRecievedPacket.i16PacketRC == 0)
      {
        Serial.write("Packet recieved, passed CRC\n\r ");
        cmLeftMotor.SetMotorSpeed(LastRecievedPacket.byPacketDataX);
        cmRightMotor.SetMotorSpeed(LastRecievedPacket.byPacketDataY);
      }
      else
      {
        Serial.write("Packet recieved, failed CRC\n\r ");
        //Dump out anything in the serial port, to clear anything trashed
        while(Serial.available())
          Serial.read();
      }
    }
    
  }
  if(ulThisLoopTime > (unsigned long)5000)
  if(ulLastMessageTime < ulThisLoopTime - ((unsigned long)5000))
  {
    ulLastMessageTime = ulThisLoopTime;
    cBytesOfCurrentPacketObtained = 0;
    cmLeftMotor.SetMotorSpeed(0);
    cmRightMotor.SetMotorSpeed(0);
    Serial.write("Recieve timeout");
    Serial.write("\n\r");
  }
  delay(10);
}
