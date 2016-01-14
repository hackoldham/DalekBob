﻿using System;
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
		void UpdateMotors()
		{
			if (sbDriveSpeed.Value != 0)
			{
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
	}
}