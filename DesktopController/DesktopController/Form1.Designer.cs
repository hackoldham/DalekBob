﻿namespace DesktopController
{
	partial class Form1
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.sbDriveSpeed = new System.Windows.Forms.VScrollBar();
			this.sbRotation = new System.Windows.Forms.HScrollBar();
			this.pbMotorL = new System.Windows.Forms.ProgressBar();
			this.pbMotorR = new System.Windows.Forms.ProgressBar();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label6 = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// sbDriveSpeed
			// 
			this.sbDriveSpeed.Location = new System.Drawing.Point(9, 9);
			this.sbDriveSpeed.Maximum = 127;
			this.sbDriveSpeed.Minimum = -128;
			this.sbDriveSpeed.Name = "sbDriveSpeed";
			this.sbDriveSpeed.Size = new System.Drawing.Size(21, 240);
			this.sbDriveSpeed.TabIndex = 0;
			this.sbDriveSpeed.ValueChanged += new System.EventHandler(this.sbDriveSpeed_ValueChanged);
			this.sbDriveSpeed.VisibleChanged += new System.EventHandler(this.sbDriveSpeed_VisibleChanged);
			this.sbDriveSpeed.MouseLeave += new System.EventHandler(this.sbDriveSpeed_MouseLeave);
			// 
			// sbRotation
			// 
			this.sbRotation.Location = new System.Drawing.Point(39, 118);
			this.sbRotation.Maximum = 127;
			this.sbRotation.Minimum = -128;
			this.sbRotation.Name = "sbRotation";
			this.sbRotation.Size = new System.Drawing.Size(218, 23);
			this.sbRotation.TabIndex = 1;
			this.sbRotation.ValueChanged += new System.EventHandler(this.sbRotation_ValueChanged);
			this.sbRotation.KeyUp += new System.Windows.Forms.KeyEventHandler(this.sbRotation_KeyUp);
			this.sbRotation.MouseLeave += new System.EventHandler(this.sbRotation_MouseLeave);
			// 
			// pbMotorL
			// 
			this.pbMotorL.Location = new System.Drawing.Point(157, 12);
			this.pbMotorL.Maximum = 128;
			this.pbMotorL.Name = "pbMotorL";
			this.pbMotorL.Size = new System.Drawing.Size(100, 23);
			this.pbMotorL.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
			this.pbMotorL.TabIndex = 2;
			// 
			// pbMotorR
			// 
			this.pbMotorR.Location = new System.Drawing.Point(157, 53);
			this.pbMotorR.Maximum = 128;
			this.pbMotorR.Name = "pbMotorR";
			this.pbMotorR.Size = new System.Drawing.Size(100, 23);
			this.pbMotorR.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
			this.pbMotorR.TabIndex = 3;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(96, 12);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(55, 13);
			this.label1.TabIndex = 4;
			this.label1.Text = "Left Motor";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(89, 63);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(62, 13);
			this.label2.TabIndex = 5;
			this.label2.Text = "Right Motor";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(39, 13);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(45, 13);
			this.label3.TabIndex = 6;
			this.label3.Text = "Forward";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(33, 236);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(47, 13);
			this.label4.TabIndex = 7;
			this.label4.Text = "Reverse";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(39, 105);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(25, 13);
			this.label5.TabIndex = 8;
			this.label5.Text = "Left";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(225, 105);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(32, 13);
			this.label6.TabIndex = 9;
			this.label6.Text = "Right";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(512, 268);
			this.Controls.Add(this.label6);
			this.Controls.Add(this.label5);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.pbMotorR);
			this.Controls.Add(this.pbMotorL);
			this.Controls.Add(this.sbRotation);
			this.Controls.Add(this.sbDriveSpeed);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.VScrollBar sbDriveSpeed;
		private System.Windows.Forms.HScrollBar sbRotation;
		private System.Windows.Forms.ProgressBar pbMotorL;
		private System.Windows.Forms.ProgressBar pbMotorR;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.Label label6;
	}
}
