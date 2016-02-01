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
//const char* ssidClient = "HackOldham-2G";
//const char* passClient = "Decafbad001";
const char* ssidClient = "VM22843224";
const char* passClient = "qtzczbwj";
WiFiUDP broadcastListener;
SDalekMotorPacket packetStorage;

void setup() {
  //Debug output
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  //Data output
  Serial1.begin(115200);

  //Host Wifi network
  //WiFi.softAP(ssid, password);
  WiFi.begin(ssidClient, passClient);
  //Listen for UDP Packets
  broadcastListener.begin(8080);

  Serial.write("Serial 0 out");
  Serial1.write("Serial 1 out");
  SDalekMotorPacket crcChecker;
  crcChecker.byPacketSize = 8;
  crcChecker.byPacketVersion = 1;
  crcChecker.byPacketID = 0;
  crcChecker.byDeviceID = 0;
  crcChecker.byPacketDataX = 127;
  crcChecker.byPacketDataY = 127;
  crcChecker.byPacketDataZ = 0;
  crcChecker.i16PacketRC = 0;
  AddCRC(&crcChecker);
  char rgc[64];
  sprintf(rgc, "Crc recorded is 0x%04X", crcChecker.i16PacketRC);
  Serial.write(rgc);
}

void loop() {
	if (broadcastListener.parsePacket())
	{
		char string[60];
		char UDPBuf[20];
		broadcastListener.read(UDPBuf, 20);
		
		sprintf(string, "Read Data: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%04X\n",
			packetStorage.byPacketSize = UDPBuf[0],
			packetStorage.byPacketVersion = UDPBuf[1],
			packetStorage.byPacketID = UDPBuf[2],
			packetStorage.byDeviceID = UDPBuf[3],
			packetStorage.byPacketDataX = UDPBuf[4],
			packetStorage.byPacketDataY = UDPBuf[5],
			packetStorage.byPacketDataZ = UDPBuf[6],
			packetStorage.i16PacketRC = ((uint16)UDPBuf[8]) << 8 | UDPBuf[7]);
		Serial.write(string);

		sprintf(string, "\nCRC in packet: 0x%04X\n", packetStorage.i16PacketRC);
		Serial.write(string);
		uint16_t i16CurrentCRC = packetStorage.i16PacketRC;
		AddCRC(&packetStorage);
		
		sprintf(string, "CRC Calculated: 0x%04X\n", i16CurrentCRC, packetStorage.i16PacketRC);
		Serial.write(string);
		
		if (packetStorage.i16PacketRC != i16CurrentCRC)
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

