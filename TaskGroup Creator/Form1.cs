using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Windows.Forms;
using System.Diagnostics;
using Newtonsoft.Json;
using IniParser;
using IniParser.Model;
using System.Text;
using System.Drawing;

namespace TaskGroupCreator
{
    public partial class Form1 : Form
    {
        public enum InfoType { Default, Error, ComponentWarning, VersionWarning}

        public class Settings
        {
            public int LanguageIndex { get; set; }
            public string TargetPath { get; set; }
            public string LastGroup { get; set; }
        }

        private Settings settings;

        string curDir;
        List<string> files = new List<string>() { "pt4taskmaker.def", "pt4taskmaker.cpp", "pt4taskmaker.h", "pt4taskmakerX.cpp", "pt4taskmakerX.h",
            "__grouptemplate__.cpp", "linqcpp.h", "__grouptemplate__-x64.bat", "__grouptemplate__-x86.bat",
            ".vscode/c_cpp_properties.json", ".vscode/launch.json", ".vscode/settings.json", ".vscode/tasks.json"};

        string english = "/english/";
        string russian = "/russian/";

        string ptPath = "C:/Program Files (x86)/PT4";
        string ptIni = "PT.INI";
        string settingsPath = "settings.json";

        string targetPath = "C:/PT4Work";

        string gppCompiler = "C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/bin/g++.exe";
        string gppCompilerFolder = "C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/bin";
        string gppCompilerIncludes = "C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/**";
        string vsCode = "code";

        bool is_ruen_version = false;
        bool pt4_found = false;
        bool vscode_found = false;
        bool gpp_found = false;

        string MsgGppFound => $"Path to g++ compiler:\n  \"{gppCompiler}\"";
        string MsgGppNotFound => $"g++ compiler was not found.";
        string MsgPT4NotFound => $"Programming Taskbook was not found.";
        string MsgVSCodeFound => $"Path to Visual Studio Code:\n  \"{vsCode}\"";
        string MsgVSCodeNotFound => $"Visual Studio Code was not found. The TaskGroup directory will open in Windows Explorer.";
        string MsgPT4VersionWarning => $"Programming Taskbook version does not support changing the group locale. The group will be created without the locale suffix.";

        public Form1()
        {
            InitializeComponent();
            curDir = Directory.GetCurrentDirectory().Replace('\\','/');
            cb_language.SelectedIndex = 0;
            textBox1.Text = "NewGroup";
            textBox2.Text = targetPath;
            rtb_info.Text = "";
            rtb_info.ContentsResized += Rtb_info_ContentsResized;
            LoadSettings();

            if (CheckPT4())
            {
                LoadPtIni();
                if (CheckGpp())
                {
                    AddInfo(MsgGppFound);

                    if (CheckVSCode())
                        AddInfo(MsgVSCodeFound);
                    else
                        AddInfo(MsgVSCodeNotFound, InfoType.ComponentWarning);
                    if (!CheckRuEnVersion())
                        AddInfo(MsgPT4VersionWarning, InfoType.VersionWarning);
                    CheckData();
                }
                else
                {
                    DisableAllControls();
                    AddInfo(MsgGppNotFound, InfoType.Error);
                    if (!CheckVSCode())
                        AddInfo(MsgVSCodeNotFound, InfoType.ComponentWarning);
                    if (!CheckRuEnVersion())
                        AddInfo(MsgPT4VersionWarning, InfoType.VersionWarning);
                }
            }
            else
            {
                DisableAllControls();
                AddInfo(MsgPT4NotFound, InfoType.Error);
                if (!CheckGpp())
                    AddInfo(MsgGppNotFound, InfoType.Error);
                if (!CheckVSCode())
                    AddInfo(MsgVSCodeNotFound, InfoType.ComponentWarning);
                if (!CheckRuEnVersion())
                    AddInfo(MsgPT4VersionWarning, InfoType.VersionWarning);
            }
        }

        private void DisableAllControls()
        {
            cb_language.Enabled = false;
            textBox1.Enabled = false;
            textBox2.Enabled = false;
            bt_create.Enabled = false;
            bt_folder.Enabled = false;
        }

        private void Rtb_info_ContentsResized(object sender, ContentsResizedEventArgs e)
        {
            this.Height += e.NewRectangle.Height - rtb_info.Height;
            tlp_info.Height += e.NewRectangle.Height - rtb_info.Height;
            rtb_info.Height = e.NewRectangle.Height;
        }

        bool CheckPT4() => pt4_found = Directory.Exists(ptPath);
        bool CheckGpp() => gpp_found = File.Exists(gppCompiler);
        bool CheckVSCode()
        {
            if (File.Exists(vsCode))
            {
                vscode_found = true;
            }
            else
            {
                string vscodePath = Environment.GetEnvironmentVariable("PATH");
                if (!string.IsNullOrEmpty(vscodePath))
                {
                    string[] paths = vscodePath.Split(';');
                    foreach (string path in paths)
                    {
                        string vscodeExe = Path.Combine(path, "code");
                        if (File.Exists(vscodeExe))
                        {
                            vsCode = vscodeExe.Replace('\\', '/');
                            vscode_found = true;
                            break;
                        }
                    }
                }
            }
            return vscode_found;
        }
        bool CheckRuEnVersion() => is_ruen_version = File.Exists(ptPath + "/LIB/PT4RMix_en.dll");

        string GetSuffix() => is_ruen_version ? (cb_language.SelectedIndex == 0 ? "_en" : "_ru") : "";
        void SaveSettings()
        {
            settings = new Settings
            {
                LanguageIndex = cb_language.SelectedIndex,
                TargetPath = targetPath,
                LastGroup = textBox1.Text
            };

            string json = JsonConvert.SerializeObject(settings);
            File.WriteAllText(settingsPath, json);
        }

        void LoadSettings()
        {
            if (File.Exists(settingsPath))
            {
                string json = File.ReadAllText(settingsPath);
                settings = JsonConvert.DeserializeObject<Settings>(json);

                cb_language.SelectedIndex = settings.LanguageIndex;
                if (settings.TargetPath != "")
                {
                    targetPath = settings.TargetPath;
                    textBox2.Text = targetPath;
                }
                if (settings.LastGroup != "")
                    textBox1.Text = settings.LastGroup;
            }
        }

        void LoadPtIni()
        {
            var parser = new FileIniDataParser();
            IniData iniData;

            try
            {
                iniData = parser.ReadFile(ptPath + "/" + ptIni);
            }
            catch (Exception ex)
            {
                AddInfo($"Cannot be read {ptIni}.\n  Error: {ex.Message}", InfoType.ComponentWarning);
                return;
            }

            if (iniData.Sections.ContainsSection("EXE files") && iniData["EXE files"].ContainsKey("CPPCODE1"))
                vsCode = iniData["EXE files"]["CPPCODE1"].Replace('\\', '/');
            else
                AddInfo($"{ptIni} do not contains [EXE files][CPPCODE1]", InfoType.ComponentWarning);

            if (iniData.Sections.ContainsSection("Additions") && iniData["Additions"].ContainsKey("CPPCODE1"))
            {
                gppCompiler = iniData["Additions"]["CPPCODE1"].Replace('\\','/');
                gppCompilerFolder = Path.GetDirectoryName(gppCompiler).Replace('\\', '/'); ;
                gppCompilerIncludes = Path.Combine(Directory.GetParent(gppCompilerFolder).FullName, "**").Replace('\\', '/');
            }
            else
                AddInfo($"{ptIni} do not contains [Additions][CPPCODE1]", InfoType.ComponentWarning);

            if (iniData.Sections.ContainsSection("Work Directory") && iniData["Work Directory"].ContainsKey("Path"))
                targetPath = iniData["Work Directory"]["Path"].Replace('\\', '/');
            else
                AddInfo($"{ptIni} do not contains [Work Directory][Path]", InfoType.ComponentWarning);
        }

        void CheckData()
        {
            string englishDir = curDir + english;
            string russianDir = curDir + russian;
            if (!Directory.Exists(englishDir))
            {
                AddError($"Directory {englishDir} not found");
                return;
            }
            if (!Directory.Exists(russianDir))
            {
                AddError($"Directory {russianDir} not found");
                return;
            }
            if (!Directory.Exists($"{curDir}/.vscode"))
            {
                AddError($"Directory {curDir}/.vscode not found");
                return;
            }
            switch (cb_language.SelectedIndex)
            {
                case 0: // English
                    {
                        foreach (var file in Directory.GetFiles(englishDir))
                        {
                            string fileName = Path.GetFileName(file);
                            File.Copy(file, curDir + "/" + fileName, true);
                        }
                        break;
                    }
                case 1: // Russian
                    {
                        foreach (var file in Directory.GetFiles(russianDir))
                        {
                            string fileName = Path.GetFileName(file);
                            File.Copy(file, curDir + "/" + fileName, true);
                        }
                        break;
                    }
            }

            tb_errors.Clear();
            foreach (var file in files) 
            {
                if (!File.Exists(curDir + "/" + file))
                {
                    AddError($"File {curDir + "/" + file} not found");
                    return;
                }
            }
            string s = textBox1.Text.Trim();
            if (s == "")
                AddError("Group name is empty");
            else if (s.Length > 9)
                AddError("Length of the group name is greater than 9");
            else if (char.IsDigit(s.Last()))
                AddError("Group name ends by digit");
            else if (s.Any(c => !(char.IsDigit(c) || c >='A' && c <= 'Z'
                || c >= 'a' && c <= 'z')))
                AddError("Group name contains illegal symbols");
            string s2 = textBox2.Text.Trim();
            if (s2 == "")
                AddError("Directory name is empty");
            else if (File.Exists(s2 + "/" + s + ".cpp") || 
                File.Exists(s2 + "/" + s + "_ru.cpp") || 
                File.Exists(s2 + "/" + s + "_en.cpp"))
                bt_create.Text = "Open";
            else
                bt_create.Text = "Create";

            if (tb_errors.Text.Length == 0)
            {
                bt_create.Enabled = true;
                tb_errors.ForeColor = Color.Green;
                tb_errors.Clear();
                tb_errors.AppendText("Group name and directory are correct");
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            targetPath = textBox2.Text;
            CheckData();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string s = textBox1.Text.Trim();
            string s2 = textBox2.Text.Trim();
            string group = $"{s2}/{s}.cpp";
            string groupRu = $"{s2}/{s}_ru.cpp";
            string groupEn = $"{s2}/{s}_en.cpp";
            string groupCurrent = $"{s2}/{s+GetSuffix()}.cpp";

            if (!Directory.Exists(s2))
                Directory.CreateDirectory(s2);

            if (!Directory.Exists(s2 + "/.vscode"))
                Directory.CreateDirectory(s2 + "/.vscode");


            if (File.Exists(group) ||
                File.Exists(groupRu) ||
                File.Exists(groupEn))
            {
                files.Remove("__grouptemplate__.cpp");
                if (!File.Exists(groupCurrent))
                {
                    var groupSource = cb_language.SelectedIndex == 0 ? groupRu : groupEn;
                    if (File.Exists(groupSource))
                        File.Copy(groupSource, groupCurrent);
                    else
                        File.Copy(group, groupCurrent);
                }
            }

            foreach (var file in files)
            {
                string s3 = s2 + "/" + file.Replace("__grouptemplate__", s + GetSuffix());
                File.Copy(curDir + "/" + file, s3, true);
                if (file.Contains("__grouptemplate__") || file.Contains("tasks.json") || file.Contains("c_cpp_properties.json"))
                {
                    string data = File.ReadAllText(s3, Encoding.GetEncoding("windows-1251")).Replace("__grouptemplate__", s + GetSuffix());
                    data = data.Replace("__compiler__", gppCompiler).Replace("__compilerfolder__", gppCompilerFolder).Replace("__compilerincludes__", gppCompilerIncludes);
                    File.WriteAllText(s3, data, Encoding.GetEncoding("windows-1251"));
                }
            }

            if (vscode_found)
                Process.Start(vsCode, $"-g \"{s2}/{s+GetSuffix()}.cpp\" \"{s2}\"");
            else
                Process.Start("explorer.exe", $"/select,\"{s2}/{s + GetSuffix()}.cpp\"");
            Close();
        }
        public void AddError(string message)
        {
            tb_errors.Clear();
            tb_errors.ForeColor = Color.Red;
            tb_errors.AppendText(message);
            bt_create.Enabled = false;
        }
        public void AddInfo(string text, InfoType type = InfoType.Default)
        {
            rtb_info.SelectionStart = rtb_info.TextLength;
            rtb_info.SelectionLength = 0;
            Color color;
            switch(type)
            {
                case InfoType.ComponentWarning: color = Color.Brown; break;
                case InfoType.VersionWarning: color = Color.Brown; break;
                case InfoType.Error: color = Color.Red; break;
                default: color = Color.Black; break;
            }
            if (rtb_info.Text != "")
            {
                rtb_info.AppendText(Environment.NewLine);
                rtb_info.AppendText(Environment.NewLine);
            }
            rtb_info.SelectionColor = color;
            rtb_info.AppendText("- " + text);
            rtb_info.SelectionColor = rtb_info.ForeColor;
            if (type == InfoType.Error || type == InfoType.ComponentWarning)
                l_ptsetup.Visible = true;
            if (type == InfoType.VersionWarning)
                l_ptupdate.Visible = true;
            if (type == InfoType.Error)
            {
                AddError("Please fix all problems and restart the application");
            }
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Escape)
                Close();
        }

        private void bt_folder_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog())
            {
                folderBrowserDialog.Description = "Select a folder to save the group to";
                folderBrowserDialog.SelectedPath = targetPath;

                if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
                {
                    targetPath = folderBrowserDialog.SelectedPath.Replace('\\','/');
                    textBox2.Text = targetPath;
                    CheckData();
                }
            }
        }

        private void cb_language_SelectedIndexChanged(object sender, EventArgs e) => CheckData();
        private void Form1_FormClosing(object sender, FormClosingEventArgs e) => SaveSettings();
    }
}
