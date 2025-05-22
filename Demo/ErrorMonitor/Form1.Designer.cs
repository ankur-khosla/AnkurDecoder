namespace ErrorMonitor
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
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.SelectFileBtn = new System.Windows.Forms.Button();
            this.FileTB = new System.Windows.Forms.TextBox();
            this.MonitorBtn = new System.Windows.Forms.Button();
            this.FileORFolderCB = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.SelectOutputFolderBtn = new System.Windows.Forms.Button();
            this.ArchiveFolderTB = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.TimingTB = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.TipLB = new System.Windows.Forms.Label();
            this.GoLB = new System.Windows.Forms.LinkLabel();
            this.label5 = new System.Windows.Forms.Label();
            this.LBCompleteTime = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // SelectFileBtn
            // 
            this.SelectFileBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SelectFileBtn.Location = new System.Drawing.Point(61, 90);
            this.SelectFileBtn.Name = "SelectFileBtn";
            this.SelectFileBtn.Size = new System.Drawing.Size(97, 34);
            this.SelectFileBtn.TabIndex = 0;
            this.SelectFileBtn.Text = "Select File";
            this.SelectFileBtn.UseVisualStyleBackColor = true;
            this.SelectFileBtn.Click += new System.EventHandler(this.button1_Click);
            // 
            // FileTB
            // 
            this.FileTB.Location = new System.Drawing.Point(235, 98);
            this.FileTB.Name = "FileTB";
            this.FileTB.Size = new System.Drawing.Size(472, 20);
            this.FileTB.TabIndex = 1;
            // 
            // MonitorBtn
            // 
            this.MonitorBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MonitorBtn.Location = new System.Drawing.Point(336, 346);
            this.MonitorBtn.Name = "MonitorBtn";
            this.MonitorBtn.Size = new System.Drawing.Size(90, 39);
            this.MonitorBtn.TabIndex = 2;
            this.MonitorBtn.Text = "Start";
            this.MonitorBtn.UseVisualStyleBackColor = true;
            this.MonitorBtn.Click += new System.EventHandler(this.button2_Click);
            // 
            // FileORFolderCB
            // 
            this.FileORFolderCB.FormattingEnabled = true;
            this.FileORFolderCB.Items.AddRange(new object[] {
            "From file",
            "From folder"});
            this.FileORFolderCB.Location = new System.Drawing.Point(235, 33);
            this.FileORFolderCB.Name = "FileORFolderCB";
            this.FileORFolderCB.Size = new System.Drawing.Size(121, 21);
            this.FileORFolderCB.TabIndex = 7;
            this.FileORFolderCB.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(67, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Log Source";
            // 
            // SelectOutputFolderBtn
            // 
            this.SelectOutputFolderBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SelectOutputFolderBtn.Location = new System.Drawing.Point(61, 173);
            this.SelectOutputFolderBtn.Name = "SelectOutputFolderBtn";
            this.SelectOutputFolderBtn.Size = new System.Drawing.Size(97, 37);
            this.SelectOutputFolderBtn.TabIndex = 9;
            this.SelectOutputFolderBtn.Text = "Archive Folder";
            this.SelectOutputFolderBtn.UseVisualStyleBackColor = true;
            this.SelectOutputFolderBtn.Click += new System.EventHandler(this.SelectOutputFolderBtn_Click);
            // 
            // ArchiveFolderTB
            // 
            this.ArchiveFolderTB.Location = new System.Drawing.Point(235, 182);
            this.ArchiveFolderTB.Name = "ArchiveFolderTB";
            this.ArchiveFolderTB.Size = new System.Drawing.Size(472, 20);
            this.ArchiveFolderTB.TabIndex = 10;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(495, 40);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(81, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Timing (mins)";
            // 
            // TimingTB
            // 
            this.TimingTB.Location = new System.Drawing.Point(619, 37);
            this.TimingTB.Name = "TimingTB";
            this.TimingTB.Size = new System.Drawing.Size(130, 20);
            this.TimingTB.TabIndex = 12;
            this.TimingTB.TextChanged += new System.EventHandler(this.TimingTB_TextChanged);
            this.TimingTB.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.TimingTB_KeyPress);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(58, 239);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(183, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Default archive folder: \\Error_Archive";
            // 
            // TipLB
            // 
            this.TipLB.AutoSize = true;
            this.TipLB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TipLB.ForeColor = System.Drawing.Color.Red;
            this.TipLB.Location = new System.Drawing.Point(335, 221);
            this.TipLB.Name = "TipLB";
            this.TipLB.Size = new System.Drawing.Size(91, 20);
            this.TipLB.TabIndex = 14;
            this.TipLB.Text = "Running...";
            // 
            // GoLB
            // 
            this.GoLB.AutoSize = true;
            this.GoLB.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GoLB.Location = new System.Drawing.Point(744, 186);
            this.GoLB.Name = "GoLB";
            this.GoLB.Size = new System.Drawing.Size(56, 16);
            this.GoLB.TabIndex = 15;
            this.GoLB.TabStop = true;
            this.GoLB.Text = "Enter >>";
            this.GoLB.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(12, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(0, 13);
            this.label5.TabIndex = 16;
            // 
            // LBCompleteTime
            // 
            this.LBCompleteTime.AutoSize = true;
            this.LBCompleteTime.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LBCompleteTime.ForeColor = System.Drawing.Color.Green;
            this.LBCompleteTime.Location = new System.Drawing.Point(336, 270);
            this.LBCompleteTime.Name = "LBCompleteTime";
            this.LBCompleteTime.Size = new System.Drawing.Size(45, 16);
            this.LBCompleteTime.TabIndex = 17;
            this.LBCompleteTime.Text = "label6";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(828, 446);
            this.Controls.Add(this.LBCompleteTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.GoLB);
            this.Controls.Add(this.TipLB);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.TimingTB);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.ArchiveFolderTB);
            this.Controls.Add(this.SelectOutputFolderBtn);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.FileORFolderCB);
            this.Controls.Add(this.MonitorBtn);
            this.Controls.Add(this.FileTB);
            this.Controls.Add(this.SelectFileBtn);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ErrorMonitor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button SelectFileBtn;
        private System.Windows.Forms.TextBox FileTB;
        private System.Windows.Forms.Button MonitorBtn;
        private System.Windows.Forms.ComboBox FileORFolderCB;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button SelectOutputFolderBtn;
        private System.Windows.Forms.TextBox ArchiveFolderTB;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox TimingTB;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label TipLB;
        private System.Windows.Forms.LinkLabel GoLB;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label LBCompleteTime;
    }
}

