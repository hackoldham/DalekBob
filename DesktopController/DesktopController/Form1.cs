using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace DesktopController
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

        byte byLMotor = 0;
        byte byRMotor = 0;
        void UpdateMotors()
		{
            byLMotor = 0;
            byRMotor = 0;
            if (sbDriveSpeed.Value != 0)
			{
				byLMotor = byRMotor = (byte)sbDriveSpeed.Value;
				if (sbDriveSpeed.Value > 0)
				{
					pbMotorL.ForeColor = Color.Red;
					pbMotorR.ForeColor = Color.Red;
				}
				else
				{
					pbMotorL.ForeColor = Color.Green;
					pbMotorR.ForeColor = Color.Green;
				}
				pbMotorL.Value = Math.Max(sbDriveSpeed.Value, sbDriveSpeed.Value * -1);
				pbMotorR.Value = Math.Max(sbDriveSpeed.Value, sbDriveSpeed.Value * -1);
			}
			else if (sbRotation.Value != 0)
			{
				byLMotor = (byte)sbRotation.Value;
				byRMotor = (byte)(sbRotation.Value * -1);
				if (sbRotation.Value > 0)
				{
					pbMotorL.ForeColor = Color.Green;
					pbMotorR.ForeColor = Color.Red;
					
				}
				else
				{
					pbMotorL.ForeColor = Color.Red;
					pbMotorR.ForeColor = Color.Green;
				}
				pbMotorL.Value = Math.Max(sbRotation.Value, sbRotation.Value * -1);
				pbMotorR.Value = Math.Max(sbRotation.Value, sbRotation.Value * -1);
			}
			else
			{
				pbMotorL.Value = 0;
				pbMotorR.Value = 0;
	
			}
			
		}
		private void sbDriveSpeed_MouseLeave(object sender, EventArgs e)
		{
			sbDriveSpeed.Value = 0;
			UpdateMotors();
		}

		private void sbRotation_MouseLeave(object sender, EventArgs e)
		{
			sbRotation.Value = 0;
			UpdateMotors();
		}

		private void sbRotation_KeyUp(object sender, KeyEventArgs e)
		{
			
		}

		private void Form1_Load(object sender, EventArgs e)
		{

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
				sbRotation.Value = -127;
			}
			else if (e.KeyCode == Keys.D || e.KeyCode == Keys.Right)
			{
				sbRotation.Value = 127;
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
}
