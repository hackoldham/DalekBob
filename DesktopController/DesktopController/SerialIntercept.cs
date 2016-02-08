using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace DesktopController
{
	public partial class SerialIntercept : Form
	{
		public SerialIntercept()
		{
			InitializeComponent();
		}

		private void timer1_Tick(object sender, EventArgs e)
		{
			if (!serialPort1.IsOpen)
				serialPort1.Open();
			if (serialPort1.BytesToRead >= 9)
			{
				byte[] buffer = new byte[9];
				serialPort1.Read(buffer, 0,9);
				PacketAssembler packet = new PacketAssembler(buffer);
				textBox1.Text = "byPacketSize: " + packet.thisPacket.byPacketSize.ToString("X2");
				textBox2.Text = "byPacketVersion: " + packet.thisPacket.byPacketVersion.ToString("X2");
				textBox3.Text = "byPacketID: " + packet.thisPacket.byPacketID.ToString("X2");
				textBox4.Text = "byDeviceID: " + packet.thisPacket.byDeviceID.ToString("X2");
				textBox5.Text = "byPacketDataX: " + packet.thisPacket.byPacketDataX.ToString("X2");
				textBox6.Text = "byPacketDataY: " + packet.thisPacket.byPacketDataY.ToString("X2");
				textBox7.Text = "byPacketDataZ: " + packet.thisPacket.byPacketDataZ.ToString("X2");
				textBox8.Text = "i16PacketRC: " + packet.thisPacket.i16PacketRC.ToString("X4");
				UInt16 oldCRC = packet.thisPacket.i16PacketRC;
				packet.AddCRC();
				textBox9.Text = "i16PacketRCExpected: " + packet.thisPacket.i16PacketRC.ToString("X4");
				if (oldCRC == packet.thisPacket.i16PacketRC)
					textBox9.ForeColor = Color.Green;
				else
					textBox9.ForeColor = Color.Red;
				if (pictureBox1.BackColor == Color.Green)
					pictureBox1.BackColor = Color.White;
				else
					pictureBox1.BackColor = Color.Green;
				while (serialPort1.BytesToRead > 0)
					serialPort1.ReadByte();
			}
			/*public struct SDalekMotorPacket
		{
			public byte byPacketSize;
			public byte byPacketVersion;
			public byte byPacketID;
			public byte byDeviceID;
			public byte byPacketDataX, byPacketDataY, byPacketDataZ;
			public UInt16 i16PacketRC;
		}*/
		}

		private void SerialIntercept_Load(object sender, EventArgs e)
		{

		}
	}
}
