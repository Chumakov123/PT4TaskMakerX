namespace TaskGroupCreator
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.bt_create = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.cb_language = new System.Windows.Forms.ComboBox();
            this.bt_folder = new System.Windows.Forms.Button();
            this.tb_errors = new System.Windows.Forms.TextBox();
            this.l_ptupdate = new System.Windows.Forms.Label();
            this.l_ptsetup = new System.Windows.Forms.Label();
            this.tlp_info = new System.Windows.Forms.TableLayoutPanel();
            this.rtb_info = new System.Windows.Forms.RichTextBox();
            this.tlp_info.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 18);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(67, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Group Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(21, 47);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Directory";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(100, 16);
            this.textBox1.Margin = new System.Windows.Forms.Padding(2);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(215, 20);
            this.textBox1.TabIndex = 1;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(100, 45);
            this.textBox2.Margin = new System.Windows.Forms.Padding(2);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(215, 20);
            this.textBox2.TabIndex = 3;
            this.textBox2.Text = "C:\\PT4Work";
            this.textBox2.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // bt_create
            // 
            this.bt_create.Enabled = false;
            this.bt_create.Location = new System.Drawing.Point(339, 14);
            this.bt_create.Margin = new System.Windows.Forms.Padding(2);
            this.bt_create.Name = "bt_create";
            this.bt_create.Size = new System.Drawing.Size(75, 23);
            this.bt_create.TabIndex = 2;
            this.bt_create.Text = "Create";
            this.bt_create.UseVisualStyleBackColor = true;
            this.bt_create.Click += new System.EventHandler(this.button1_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(21, 77);
            this.label5.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(39, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "Locale";
            // 
            // cb_language
            // 
            this.cb_language.FormattingEnabled = true;
            this.cb_language.Items.AddRange(new object[] {
            "English",
            "Русский"});
            this.cb_language.Location = new System.Drawing.Point(100, 74);
            this.cb_language.Name = "cb_language";
            this.cb_language.Size = new System.Drawing.Size(126, 21);
            this.cb_language.TabIndex = 5;
            this.cb_language.SelectedIndexChanged += new System.EventHandler(this.cb_language_SelectedIndexChanged);
            // 
            // bt_folder
            // 
            this.bt_folder.Location = new System.Drawing.Point(339, 43);
            this.bt_folder.Name = "bt_folder";
            this.bt_folder.Size = new System.Drawing.Size(75, 23);
            this.bt_folder.TabIndex = 4;
            this.bt_folder.Text = "Select folder";
            this.bt_folder.UseVisualStyleBackColor = true;
            this.bt_folder.Click += new System.EventHandler(this.bt_folder_Click);
            // 
            // tb_errors
            // 
            this.tb_errors.BackColor = System.Drawing.SystemColors.Control;
            this.tb_errors.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tb_errors.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.tb_errors.ForeColor = System.Drawing.Color.Red;
            this.tb_errors.Location = new System.Drawing.Point(0, 254);
            this.tb_errors.Name = "tb_errors";
            this.tb_errors.ReadOnly = true;
            this.tb_errors.Size = new System.Drawing.Size(436, 20);
            this.tb_errors.TabIndex = 9;
            this.tb_errors.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // l_ptupdate
            // 
            this.l_ptupdate.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.l_ptupdate.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.l_ptupdate.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.l_ptupdate.Location = new System.Drawing.Point(0, 230);
            this.l_ptupdate.Name = "l_ptupdate";
            this.l_ptupdate.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.l_ptupdate.Size = new System.Drawing.Size(436, 24);
            this.l_ptupdate.TabIndex = 8;
            this.l_ptupdate.Text = "You should update to the latest version of Programming Taskbook";
            this.l_ptupdate.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.l_ptupdate.Visible = false;
            // 
            // l_ptsetup
            // 
            this.l_ptsetup.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.l_ptsetup.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.l_ptsetup.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.l_ptsetup.Location = new System.Drawing.Point(0, 206);
            this.l_ptsetup.Name = "l_ptsetup";
            this.l_ptsetup.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.l_ptsetup.Size = new System.Drawing.Size(436, 24);
            this.l_ptsetup.TabIndex = 7;
            this.l_ptsetup.Text = "You should install the missing components using PT4Setup";
            this.l_ptsetup.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.l_ptsetup.Visible = false;
            // 
            // tlp_info
            // 
            this.tlp_info.ColumnCount = 2;
            this.tlp_info.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 2.981651F));
            this.tlp_info.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 97.01835F));
            this.tlp_info.Controls.Add(this.rtb_info, 1, 0);
            this.tlp_info.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.tlp_info.Location = new System.Drawing.Point(0, 123);
            this.tlp_info.Name = "tlp_info";
            this.tlp_info.RowCount = 1;
            this.tlp_info.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tlp_info.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tlp_info.Size = new System.Drawing.Size(436, 83);
            this.tlp_info.TabIndex = 22;
            // 
            // rtb_info
            // 
            this.rtb_info.BackColor = System.Drawing.SystemColors.Control;
            this.rtb_info.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.rtb_info.ForeColor = System.Drawing.SystemColors.WindowText;
            this.rtb_info.Location = new System.Drawing.Point(15, 3);
            this.rtb_info.Name = "rtb_info";
            this.rtb_info.ReadOnly = true;
            this.rtb_info.ScrollBars = System.Windows.Forms.RichTextBoxScrollBars.Vertical;
            this.rtb_info.Size = new System.Drawing.Size(407, 71);
            this.rtb_info.TabIndex = 6;
            this.rtb_info.Text = resources.GetString("rtb_info.Text");
            // 
            // Form1
            // 
            this.AcceptButton = this.bt_create;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(436, 274);
            this.Controls.Add(this.tlp_info);
            this.Controls.Add(this.l_ptsetup);
            this.Controls.Add(this.l_ptupdate);
            this.Controls.Add(this.tb_errors);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.cb_language);
            this.Controls.Add(this.bt_folder);
            this.Controls.Add(this.bt_create);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.KeyPreview = true;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "TaskGroup Creator";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.tlp_info.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button bt_create;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cb_language;
        private System.Windows.Forms.Button bt_folder;
        private System.Windows.Forms.TextBox tb_errors;
        private System.Windows.Forms.Label l_ptupdate;
        private System.Windows.Forms.Label l_ptsetup;
        private System.Windows.Forms.TableLayoutPanel tlp_info;
        private System.Windows.Forms.RichTextBox rtb_info;
    }
}

