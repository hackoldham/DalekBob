
//CrossPlatform Packet Definitions
struct SDalekMotorPacket
{
  byte byPacketSize = 7;
  byte byPacketVersion = 1;
  byte byPacketCheckSum;
  byte byPacketID;
  byte byDeviceID;
  byte byPacketDataX, byPacketDataY, byPacketDataZ;
};
 