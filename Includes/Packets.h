
//CrossPlatform Packet Definitions
struct SDalekMotorPacket
{
  byte byPacketSize = 7;
  byte byPacketVersion = 1;
  byte byPacketID;
  byte byDeviceID;
  byte byPacketDataX, byPacketDataY, byPacketDataZ;
  int i16PacketRC;
};
 
 void AddCRC(SDalekMotorPacket* pPacket)
 {
 
 }
 
 bool VerifyCRC(SDalekMotorPacket* pPacket)
 {
 
 }