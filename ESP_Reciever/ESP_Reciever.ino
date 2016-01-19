/*
  WiFiTelnetToSerial - Example Transparent UART to Telnet Server for esp8266

  Copyright (c) 2015 Hristo Gochkov. All rights reserved.
  This file is part of the ESP8266WiFi library for Arduino environment.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Packets.h"

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 1
const char* ssid = "DalekBob";
const char* password = "Exterminate";

WiFiUDP broadcastListener;
SDalekMotorPacket packetStorage;

void setup() {
  //Debug output
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  //Data output
  Serial1.begin(115200);

  //Host Wifi network
  WiFi.softAP(ssid, password);
  //Listen for UDP Packets
  broadcastListener.begin(8080);

}

void loop() {
  if (broadcastListener.available() >= sizeof(SDalekMotorPacket))
  {
    broadcastListener.read((char*)&packetStorage, sizeof(SDalekMotorPacket));
    int i16CurrentCRC = packetStorage.i16PacketRC;
    AddCRC(&packetStorage);
    if (packetStorage.i16PacketRC)
    {
      Serial.print("Packet failed checksum!\n\r");
      //Dump all the things
      while (broadcastListener.available())
        broadcastListener.read();
    }
    else
    {
      Serial.print("Packet passed checksum!\n\r");
      packetStorage.i16PacketRC = i16CurrentCRC;
      Serial1.write((char*)&packetStorage, sizeof(SDalekMotorPacket));
    }
  }
}
