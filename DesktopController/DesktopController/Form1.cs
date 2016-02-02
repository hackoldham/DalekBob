using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
namespace DesktopController
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}
        //Socket sNetSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.IPv4);
        UdpClient uClient = new UdpClient(8080, AddressFamily.InterNetwork);
        IPEndPoint ipEndPoint = new IPEndPoint(IPAddress.Parse("255.255.255.255"), 8080);
        byte byLMotor = 0;
        byte byRMotor = 0;
        void UpdateMotors()
		{
            byLMotor = 127;
            byRMotor = 127;
            if (sbDriveSpeed.Value != 0)
			{
				byLMotor = byRMotor = (byte)(255 - (sbDriveSpeed.Value+127));
			}
			else if (sbRotation.Value != 127)
			{
				byLMotor = ((byte)sbRotation.Value);
				byRMotor = (byte)(255 - sbRotation.Value);
			}
			if (byLMotor < 127)
			{
				pbMotorL.ForeColor = Color.Red;
				pbMotorL.Value = 255 - (byLMotor) * 2;
			}
			else if (byLMotor > 127)
			{
				pbMotorL.ForeColor = Color.Green;
				pbMotorL.Value = (byLMotor -127) * 2;
			}
			else
			{
				pbMotorL.Value = 0;
			}
			if (byRMotor < 127)
			{
				pbMotorR.ForeColor = Color.Red;
				pbMotorR.Value = 255 - (byRMotor) * 2;
			}
			else if (byRMotor > 127)
			{
				pbMotorR.ForeColor = Color.Green;
				pbMotorR.Value = (byRMotor -127) * 2;
			}
			else
				pbMotorR.Value = 0;
			
		}
		private void sbDriveSpeed_MouseLeave(object sender, EventArgs e)
		{
			sbDriveSpeed.Value = 0;
			UpdateMotors();
		}

		private void sbRotation_MouseLeave(object sender, EventArgs e)
		{
			sbRotation.Value = 127;
			UpdateMotors();
		}

		private void sbRotation_KeyUp(object sender, KeyEventArgs e)
		{
			
		}

		private void Form1_Load(object sender, EventArgs e)
		{
            uClient.EnableBroadcast = true;
        }

		private void sbRotation_ValueChanged(object sender, EventArgs e)
		{
			UpdateMotors();
		}

		private void sbDriveSpeed_VisibleChanged(object sender, EventArgs e)
		{

		}

		private void sbDriveSpeed_ValueChanged(object sender, EventArgs e)
		{
			UpdateMotors();
		}

		private void Form1_KeyUp(object sender, KeyEventArgs e)
		{
			sbRotation.Value= 0;
			sbDriveSpeed.Value = 0;
			UpdateMotors();
		}

		private void Form1_KeyPress(object sender, KeyPressEventArgs e)
		{
		}

		private void Form1_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.W || e.KeyCode == Keys.Up)
			{
				sbDriveSpeed.Value = -127;
			}
			else if (e.KeyCode == Keys.A || e.KeyCode == Keys.Left)
			{
				sbRotation.Value = 0;
			}
			else if (e.KeyCode == Keys.D || e.KeyCode == Keys.Right)
			{
				sbRotation.Value = 255;
			}
			else if (e.KeyCode == Keys.S || e.KeyCode == Keys.Down)
			{
				sbDriveSpeed.Value = 127;
			}
		}

		private void sbRotation_Scroll(object sender, ScrollEventArgs e)
		{

		}

        private void timer1_Tick(object sender, EventArgs e)
        {
            UpdateMotors();
            PacketAssembler nPacket = new PacketAssembler((Byte)(byLMotor+127), (Byte)(byRMotor+127), 0);
            if (rbBroadcast.Checked)
                uClient.Send(nPacket.getBytes(), nPacket.thisPacket.byPacketSize + 1, ipEndPoint);
            if (rbSerial.Checked)
            {
                if (!spUsbOut.IsOpen)
                    spUsbOut.Open();
                spUsbOut.Write(nPacket.getBytes(), 0, nPacket.thisPacket.byPacketSize + 1);
                while (spUsbOut.BytesToRead > 0)
                {
                    char c = (char)spUsbOut.ReadChar();
                    if (textBox1.Text.Contains("\r"))
                        textBox1.Text = "";
                    textBox1.Text += c;
                }
            }
        }
       // PortSelect pSelect;
        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            //pSelect = new PortSelect(this);
           // pSelect.Show(this);
        }
        public void UpdateSerialPort(System.IO.Ports.SerialPort sPort, string strPortID)
        {
            spUsbOut = sPort;
            txtOutput.Text = strPortID;
            try
            {
                spUsbOut.Open();
            }
            catch (Exception ex)
            {
                txtOutput.Text = ex.ToString();
            }
        }

        private void radioButton1_ClientSizeChanged(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged_1(object sender, EventArgs e)
        {

        }
    }
}
