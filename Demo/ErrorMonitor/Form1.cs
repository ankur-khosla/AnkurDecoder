using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace ErrorMonitor
{
    enum LogLevel
    {
        Debug = 0,
        Info = 1,
        Error = 2
    }

    public partial class Form1 : Form
    {
        #region global variables

        private System.Windows.Forms.Timer timerMonitor = new System.Windows.Forms.Timer();
        string timePattern = "Time[yyyy-MM-dd HH:mm:ss,fff]";
        private string lastLogTimeFile = AppDomain.CurrentDomain.BaseDirectory + "LastLogTime.txt"; // record last time for edabi & decoder log
        private string lastLogTimeFile4Old = AppDomain.CurrentDomain.BaseDirectory + "LastLogTimeForOld.txt"; // record last time for edabi & decoder log
        private string ScannedLogFiles = AppDomain.CurrentDomain.BaseDirectory + "ScannedLogFiles.txt"; // record last time for edabi & decoder log


        private string debugLevel = "Level[DEBUG]";
        private string infoLevel = "Level[INFO]";
        private string errorLevel = "Level[ERROR]";
        private string warnLevel = "Level[WARN]";

        //Last log time
        private string lghdLastLogTime = string.Empty;
        private string decodeAGPLastLogTime = string.Empty;
        private string decodeACPLastLogTime = string.Empty;
        private string dbLastLogTime = string.Empty;
        private string defaultLastLogTime = string.Empty;
        private string solaceLastLogTime = string.Empty;
        private string salesLastLogTime = string.Empty;
        private string eodLastLogTime = string.Empty;
        private string msgLastLogTime = string.Empty;

        //Last log time for old log files
        private string lghdLastLogTime4Old = string.Empty;
        private string decodeAGPLastLogTime4Old = string.Empty;
        private string decodeACPLastLogTime4Old = string.Empty;
        private string dbLastLogTime4Old = string.Empty;
        private string defaultLastLogTime4Old = string.Empty;
        private string solaceLastLogTime4Old = string.Empty;
        private string salesLastLogTime4Old = string.Empty;
        private string eodLastLogTime4Old = string.Empty;

        private int clickCount = 0;
        //private string resultFile = string.Empty;

        //Log directory
        private static readonly string agpLogDir = "\\ACP_Decode\\";
        private static readonly string acpLogDir = "\\AGP_Decode\\";
        private static readonly string lghdLogDir = "\\logger\\";
        private static readonly string dbLogDir = "\\database\\";
        private static readonly string defaultLogDir = "\\default\\";
        private static readonly string solaceLogDir = "\\solace\\";
        private static readonly string salesLogDir = "\\sales\\";
        private static readonly string eodLogDir = "\\eod\\";
        private static readonly string msgLogDir = "\\message\\";

        //Log files
        private static readonly string agpLog = "AGP_DECODE";
        private static readonly string acpLog = "ACP_DECODE";
        private static readonly string lghdLog = "_EDABI_LGHD_";
        private static readonly string dbLog = "_EDABI_DB_";
        private static readonly string defaultLog = "_DEBUG_";
        private static readonly string solaceLog = "_EDABI_SOLACE_";
        private static readonly string salesLog = "_EDABI_SLHD_";
        private static readonly string eodLog = "_EDABI_EOD_";
        private static readonly string messageLog = "_EDABI_MGHD_";

        //Last log time
        private static readonly string lghdLLT = "LghdLastLogTime";
        private static readonly string decodeACPLLT = "DecodeACPLastLogTime";
        private static readonly string decodeAGPLLT = "DecodeAGPLastLogTime";
        private static readonly string dbLLT = "DBLastLogTime";
        private static readonly string defaultLLT = "DefaultLastLogTime";
        private static readonly string solaceLLT = "SolaceLastLogTime";
        private static readonly string salesLLT = "SalesLastLogTime";
        private static readonly string eodLLT = "EodLastLogTime";
        private static readonly string msgLLT = "MsgLastLogTime";

        // Delimiters
        private static readonly string delimiterEqual = "=";
        private static readonly string delimiterComb = "]-";
        private static readonly string delimiterLeftBracket = "[";
        private static readonly string delimiterTime = "Time[";
        private static readonly char delimiterLine = '_';

        private static readonly string noHeader = "NoHeader";

        private static readonly string defaultArchiveFolder = "Error_Archive";

        private static string defaultArchiveDir = AppDomain.CurrentDomain.BaseDirectory + defaultArchiveFolder;

        private static string defaultLodDir="O:\\edabi_bin\\Log";

        private Task taskMonitor = null;
        private Task task4OldLog = null;
        private static CancellationTokenSource cancelToken = null;

        #endregion

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string defaultFolder = defaultArchiveDir;

            if (!string.IsNullOrEmpty(FileTB.Text.Trim()))
                defaultFolder = FileTB.Text.Trim();

            if (FileORFolderCB.SelectedIndex == 0)
            {
                OpenFileDialog fileDlg = new OpenFileDialog();
                fileDlg.InitialDirectory = defaultFolder;

                if (fileDlg.ShowDialog() == DialogResult.OK)
                {
                    FileInfo fileInfo = new FileInfo(fileDlg.FileName);
                    FileTB.Text = fileInfo.FullName;
                }
            }
            else if (FileORFolderCB.SelectedIndex == 1)
            {
                FolderBrowserDialog fbD = new FolderBrowserDialog();
                fbD.Description = "Please select folder";
                fbD.SelectedPath = defaultFolder;

                if (fbD.ShowDialog() == DialogResult.OK)
                {
                    FileTB.Text = fbD.SelectedPath;
                }
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FileORFolderCB.SelectedIndex = 1;
            TipLB.Visible = false;
            //GoLB.Visible = false;
            FileORFolderCB.DropDownStyle = ComboBoxStyle.DropDownList;

            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.LBCompleteTime.Visible = false;

            if (Directory.Exists(defaultLodDir))
                FileTB.Text = defaultLodDir;

            if (!Directory.Exists(defaultArchiveDir))
                Directory.CreateDirectory(defaultArchiveDir);

            ArchiveFolderTB.Text = defaultArchiveDir;

            GoLB.Visible = true;

            TimingTB.Text = "5";

        }

        private async void button2_Click(object sender, EventArgs e)
        {
            //Cursor.Current = Cursors.WaitCursor;
            //TipLB.Cursor = Cursors.WaitCursor;

            if (!string.IsNullOrEmpty(ArchiveFolderTB.Text.Trim()))
                defaultArchiveDir = ArchiveFolderTB.Text.Trim();

            if (!Directory.Exists(defaultArchiveDir))
            {
                Directory.CreateDirectory(defaultArchiveDir);
                GoLB.Visible = true;
            }

            if ((taskMonitor != null && taskMonitor.Status == TaskStatus.Running) || (task4OldLog != null && task4OldLog.Status == TaskStatus.Running) || timerMonitor.Enabled)
            {
                if ((taskMonitor != null && taskMonitor.Status == TaskStatus.Running))
                {
                    cancelToken.Cancel();

                }

                if ((task4OldLog != null && task4OldLog.Status == TaskStatus.Running))
                {
                    cancelToken.Cancel();

                }


                timerMonitor.Stop();
                MonitorBtn.Text = "Start";

                //TipLB.Visible = false;
                SelectFileBtn.Enabled = true;
                FileORFolderCB.Enabled = true;
                FileTB.ReadOnly = false;
                SelectOutputFolderBtn.Enabled = true;
                ArchiveFolderTB.ReadOnly = false;
                //ArchiveFolderTB.Enabled = true;
                TimingTB.ReadOnly = false;

                TipLB.Text = "Stoppped";

                this.MonitorBtn.Invoke(new Action(() => { MonitorBtn.Text = "Start"; }));

                //Application.DoEvents();
                return;
            }
            else
            {
                string filePath = FileTB.Text.Trim();

                if (string.IsNullOrEmpty(filePath))
                {
                    if (FileORFolderCB.SelectedIndex == 0)
                        MessageBox.Show("Please select one log file \n incluing Base64 messages!");
                    else if (FileORFolderCB.SelectedIndex == 1)
                        MessageBox.Show("Please select one log folder!");
                    return;
                }

                string secStr = TimingTB.Text.Trim();
                if (!Regex.IsMatch(secStr, @"^[0-9]{1,}$"))
                {
                    MessageBox.Show("Please intput a number for timing!");
                    return;
                }
                int minus = 0;
                Int32.TryParse(TimingTB.Text.Trim(), out minus);

                if (minus == 0)
                {
                    MessageBox.Show("Time should be greater than 0!");
                    return;
                }

                TipLB.Visible = true;
                TipLB.Text = "Running...";
                SelectFileBtn.Enabled = false;
                FileORFolderCB.Enabled = false;
                FileTB.ReadOnly = true;
                SelectOutputFolderBtn.Enabled = false;
                ArchiveFolderTB.ReadOnly = true;
                //ArchiveFolderTB.Enabled = false;
                TimingTB.ReadOnly = true;
                //GoLB.Visible = false;


                //resultFile = GenerateResultFile();

                MonitorBtn.Text = "Stop";


                cancelToken = new CancellationTokenSource();
                taskMonitor = Task.Factory.StartNew(() =>
                {
                    CollectErrors();

                }, cancelToken.Token);


                task4OldLog = Task.Factory.StartNew(() =>
                {
                    CollectOldErrors();

                }, cancelToken.Token);

                await taskMonitor;
                await task4OldLog;

                if (this.LBCompleteTime.InvokeRequired)
                {
                    this.LBCompleteTime.Invoke(new Action(() =>
                    {

                        GoLB.Visible = true;

                        LBCompleteTime.Visible = true;
                        LBCompleteTime.Text = "Last Completion time: " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
                    }));
                }

                else
                {


                    LBCompleteTime.Visible = true;
                    LBCompleteTime.Text = "Last Completion time: " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
                    GoLB.Visible = true;
                }

                timerMonitor.Start();

                StartTimerMonitor(minus); // Run timingly

                if (cancelToken.Token.IsCancellationRequested == true)
                {
                    cancelToken.Dispose();
                    timerMonitor.Stop();
                }

                if (taskMonitor.IsCanceled || taskMonitor.IsCompleted)
                    taskMonitor.Dispose();

                if (task4OldLog.IsCanceled || task4OldLog.IsCompleted)
                    task4OldLog.Dispose();

                //clickCount++;
            }

            //Cursor.Current = Cursors.AppStarting;
        }

        /// <summary>
        /// to be write message to DB, per interval sec
        /// </summary>
        private void StartTimerMonitor(int minus)
        {
            //init timer
            timerMonitor.Interval = 1000 * minus * 60;// 
            EventArgs args = new EventArgs();
            timerMonitor.Tick += new System.EventHandler(OnTimerMonitorElapsedEvent);
            timerMonitor.Start();
        }

        private void OnTimerMonitorElapsedEvent(object sender, EventArgs e)
        {
            int SelectedIndex = 0;

            if (this.FileORFolderCB.InvokeRequired)
            {
                this.FileORFolderCB.Invoke(new Action(() =>
                {

                    SelectedIndex = FileORFolderCB.SelectedIndex;
                }));
            }
            else
            {
                SelectedIndex = FileORFolderCB.SelectedIndex;
            }

            string fileorFolder = string.Empty;

            if (this.FileTB.InvokeRequired)
            {
                this.FileTB.Invoke(new Action(() =>
                {

                    fileorFolder = FileTB.Text.Trim();
                }));
            }
            else
            {
                fileorFolder = FileTB.Text.Trim();
            }

            if (SelectedIndex == 0)
            {
                if (!IsFileInUse(fileorFolder))
                {
                    bool isSkip = SkipOldLogFiles(fileorFolder);// Skip other files and old log files that had been collected
                    if (isSkip)
                        return;

                    GetNewErrorContent(fileorFolder);
                }

            }
            else if (SelectedIndex == 1)
            {

                GetErrorsOfLastLogFile(fileorFolder);
                RecordLastLogTime();
                //GetAllErrors(fileorFolder, dcLogTime);

            }

         
            if (this.LBCompleteTime.InvokeRequired)
            {
                this.LBCompleteTime.Invoke(new Action(() =>
                {

                    GoLB.Visible = true;

                    LBCompleteTime.Visible = true;
                    LBCompleteTime.Text = "Last Completion time: " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
                }));
            }

            else
            {
                

                LBCompleteTime.Visible = true;
                LBCompleteTime.Text = "Last Completion time: " + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
                GoLB.Visible = true;
            }

        }

        private void CollectErrors()
        {
            int SelectedIndex = 0;

            if (this.FileORFolderCB.InvokeRequired)
            {
                this.FileORFolderCB.Invoke(new Action(() =>
                {

                    SelectedIndex = this.FileORFolderCB.SelectedIndex;
                }));
            }
            else
            {
                SelectedIndex = FileORFolderCB.SelectedIndex;
            }

            string fileorFolder = string.Empty;

            if (this.FileTB.InvokeRequired)
            {
                this.FileTB.Invoke(new Action(() =>
                {

                    fileorFolder = FileTB.Text.Trim();
                }));
            }
            else
            {
                fileorFolder = FileTB.Text.Trim();
            }

            

            if (SelectedIndex == 0)
            {
                if (!IsFileInUse(fileorFolder))
                {

                    //bool isSkip = SkipOldLogFiles(fileorFolder, dcLogTime);// Skip other files and old log files that had been collected
                    //if (!isSkip)
                        GetNewErrorContent(fileorFolder);
                }

            }
            else if (SelectedIndex == 1)
            {
                GetErrorsOfLastLogFile(fileorFolder); // First, get errors of latest log file
                RecordLastLogTime();

                //GetErrorsOfOldLogFile(fileorFolder); // Second, get errors of old log files

            }


            //RecordLastLogTime();

        }

        private void CollectOldErrors()
        {
         
            int SelectedIndex = 0;

            if (this.FileORFolderCB.InvokeRequired)
            {
                this.FileORFolderCB.Invoke(new Action(() =>
                {

                    SelectedIndex = this.FileORFolderCB.SelectedIndex;
                }));
            }
            else
            {
                SelectedIndex = FileORFolderCB.SelectedIndex;
            }

            string fileorFolder = string.Empty;

            if (this.FileTB.InvokeRequired)
            {
                this.FileTB.Invoke(new Action(() =>
                {

                    fileorFolder = FileTB.Text.Trim();
                }));
            }
            else
            {
                fileorFolder = FileTB.Text.Trim();
            }

            if (SelectedIndex == 1)
            {
                GetErrorsOfOldLogFile(fileorFolder); // Second, get errors of old log files

                //RecordLastLogTime4Old();

            }

        }

        public void WriteToFile(string file, string[] errors)
        {
            if (errors == null && errors.Length <= 0)
                return;

            string resultFile =  GenerateResultFile(file);

            //if (!File.Exists(resultFile))
            //    File.Create(resultFile);

            string lghdLastTime = string.Empty;
            string decodeAGPLastTime = string.Empty;
            string decodeACPLastTime = string.Empty;
            string defaultLastTime = string.Empty;
            string dbLastTime = string.Empty;
            string salesLastTime = string.Empty;
            string solaceLastTime = string.Empty;
            string eodLastTime = string.Empty;
            string msgLastTime = string.Empty;

            if (File.Exists(lastLogTimeFile))
            {
                string[] logTimes = File.ReadAllLines(lastLogTimeFile);

                string logFile = string.Empty;
                string logTime = string.Empty;

                for (int i = 0; i < logTimes.Length; i++)
                {
                    if (string.IsNullOrEmpty(logTimes[i]) || logTimes[i].Length == 0)
                        continue;
                    logFile = logTimes[i].Split(delimiterEqual.ToCharArray())[0];
                    logTime = logTimes[i].Split(delimiterEqual.ToCharArray())[1];

                    if (logFile == lghdLLT)
                        lghdLastTime = logTime;
                    else if (logFile == defaultLLT)
                        defaultLastTime = logTime;
                    else if (logFile == decodeAGPLLT)
                        decodeAGPLastTime = logTime;
                    else if (logFile == decodeACPLLT)
                        decodeACPLastTime = logTime;
                    else if (logFile == dbLLT)
                        dbLastTime = logTime;
                    else if (logFile == solaceLLT)
                        solaceLastTime = logTime;
                    else if (logFile == salesLLT)
                        salesLastTime = logTime;
                    else if (logFile == eodLLT)
                        eodLastTime = logTime;
                    else if (logFile == msgLLT)
                        msgLastTime = logTime;

                }

            }


            long fLen = 0;
            if (File.Exists(resultFile))
            {
                FileInfo fi = new FileInfo(resultFile);
                fLen = fi.Length;
            }


            StreamWriter sw = new StreamWriter(resultFile, true);

            bool hasContent = false;

            foreach (string error in errors)
            {
                string[] errorStr = error.Split(new string[] { delimiterComb }, StringSplitOptions.None);
                if (errorStr.Length < 2)
                    continue;

                string logTime = errorStr[1].Substring(0, timePattern.Length);
                if (error.Contains(agpLog))
                {
                    if (string.Compare(logTime, decodeAGPLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if(fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }

                }
                else if (error.Contains(acpLog))
                {
                    if (string.Compare(logTime, decodeACPLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }

                }
                else if (error.Contains(defaultLog))
                {
                    if (string.Compare(logTime, defaultLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }
                else if (error.Contains(solaceLog))
                {
                    if (string.Compare(logTime, solaceLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }
                else if (error.Contains(salesLog))
                {
                    if (string.Compare(logTime, salesLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }

                else if (error.Contains(dbLog))
                {
                    if (string.Compare(logTime, dbLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }
                else if (error.Contains(lghdLog))
                {
                    if (string.Compare(logTime, lghdLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }
                else if (error.Contains(eodLog))
                {
                    if (string.Compare(logTime, eodLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }
                else if (error.Contains(messageLog))
                {
                    if (string.Compare(logTime, msgLastTime) > 0)
                    {
                        if (errorStr[1].Contains(noHeader))
                            sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                        else
                        {
                            if (fLen > timePattern.Length || hasContent)
                                sw.Write("\r\n");
                            sw.WriteLine(error);
                        }

                        hasContent = true;
                    }
                }

            }

            sw.Flush();
            sw.Close();

            //if (File.Exists(path))
            //{
            //    FileInfo fileInfo = new FileInfo(path);
            //    if (fileInfo.Length == 0)
            //        File.Delete(path);
            //}
        }

        public void WriteToFile4Old(string file, string[] errors)
        {
            if (errors == null && errors.Length <= 0)
                return;

            string resultFile = GenerateResultFile(file);

            string lghdLastTime4Old = string.Empty;
            string decodeAGPLastTime4Old = string.Empty;
            string decodeACPLastTime4Old = string.Empty;
            string defaultLastTime4Old = string.Empty;
            string dbLastTime4Old = string.Empty;
            string salesLastTime4Old = string.Empty;
            string solaceLastTime4Old = string.Empty;
            string eodLastTime4Old = string.Empty;

            //if (File.Exists(lastLogTimeFile4Old))
            //{
            //    string[] logTimes = File.ReadAllLines(lastLogTimeFile4Old);

            //    string logFile = string.Empty;
            //    string logTime = string.Empty;

            //    for (int i = 0; i < logTimes.Length; i++)
            //    {
            //        logFile = logTimes[i].Split(delimiterEqual.ToCharArray())[0];
            //        logTime = logTimes[i].Split(delimiterEqual.ToCharArray())[1];

            //        if (logFile == lghdLLT)
            //            lghdLastTime4Old = logTime;
            //        else if (logFile == defaultLLT)
            //            defaultLastTime4Old = logTime;
            //        else if (logFile == decodeAGPLLT)
            //            decodeAGPLastTime4Old = logTime;
            //        else if (logFile == decodeACPLLT)
            //            decodeACPLastTime4Old = logTime;
            //        else if (logFile == dbLLT)
            //            dbLastTime4Old = logTime;
            //        else if (logFile == solaceLLT)
            //            solaceLastTime4Old = logTime;
            //        else if (logFile == salesLLT)
            //            salesLastTime4Old = logTime;
            //        else if (logFile == eodLLT)
            //            eodLastTime4Old = logTime;

            //    }
            //}

            //if (file.Contains(acpLog) && !string.IsNullOrEmpty(decodeACPLastTime4Old))
            //    return;
            //if (file.Contains(agpLog) && !string.IsNullOrEmpty(decodeAGPLastTime4Old))
            //    return;
            //if (file.Contains(defaultLog) && !string.IsNullOrEmpty(defaultLastTime4Old))
            //    return;
            //if (file.Contains(lghdLog) && !string.IsNullOrEmpty(lghdLastTime4Old))
            //    return;
            //if (file.Contains(salesLog) && !string.IsNullOrEmpty(salesLastTime4Old))
            //    return;
            //if (file.Contains(eodLog) && !string.IsNullOrEmpty(eodLastTime4Old))
            //    return;
            //if (file.Contains(dbLog) && !string.IsNullOrEmpty(dbLastTime4Old))
            //    return;
            //if (file.Contains(solaceLog) && !string.IsNullOrEmpty(salesLastTime4Old))
            //    return;


            long fLen = 0;
            if (File.Exists(resultFile))
            {
                FileInfo fi = new FileInfo(resultFile);
                fLen = fi.Length;
            }


            StreamWriter sw = new StreamWriter(resultFile, true);

            bool hasContent = false;

            foreach (string error in errors)
            {
                string[] errorStr = error.Split(new string[] { delimiterComb }, StringSplitOptions.None);
                if (errorStr.Length < 2)
                    continue;

                string logTime = errorStr[1].Substring(0, timePattern.Length);
                if (error.Contains(agpLog) || error.Contains(acpLog) || error.Contains(defaultLog) || error.Contains(solaceLog)
                    || error.Contains(salesLog) || error.Contains(lghdLog) || error.Contains(eodLog) || error.Contains(dbLog)
                    || error.Contains(messageLog))
                {
                    if (errorStr[1].Contains(noHeader))
                        sw.WriteLine(errorStr[1].Substring(timePattern.Length + noHeader.Length));
                    else
                    {
                        if (fLen > timePattern.Length || hasContent)
                            sw.Write("\r\n");
                        sw.WriteLine(error);
                    }

                    hasContent = true;

                }
               
            }

            sw.Flush();
            sw.Close();
        }


        private void button1_Click_1(object sender, EventArgs e)
        {
            SelectFileBtn.Enabled = false;
            FolderBrowserDialog fbD = new FolderBrowserDialog();
            fbD.Description = "Please select folder";

            if (fbD.ShowDialog() == DialogResult.OK)
            {

            }
        }

        private string[] getAllFiles(string path)
        {

            if (Directory.Exists(path))
            {
                return Directory.GetFiles(path);
            }
            return null;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (FileORFolderCB.SelectedIndex == 0)
            {

                SelectFileBtn.Text = "Select File";
            }
            else if (FileORFolderCB.SelectedIndex == 1)
            {
                SelectFileBtn.Text = "Select Folder";
            }
        }

        private void SelectOutputFolderBtn_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbD = new FolderBrowserDialog();
            fbD.Description = "Please select one output folder";
            fbD.SelectedPath = defaultArchiveDir;

            if (fbD.ShowDialog() == DialogResult.OK)
            {
                ArchiveFolderTB.Text = fbD.SelectedPath;
            }
        }

        private void GetNewErrorContent(string file)
        {
            if (cancelToken.Token.IsCancellationRequested == true)
            {
                RecordLastLogTime();
                return;
            }


            List<string> errors = new List<string>();

            FileStream fs = new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            StreamReader sr = new StreamReader(fs);

            string tmpLogTime = string.Empty;

            string line;

            DateTime startTime = DateTime.Now;

            while ((line = sr.ReadLine()) != null)
            {
                if (cancelToken.Token.IsCancellationRequested == true)
                {
                    DeleteResultFile(file);
                    return;
                }

                //Error message sample:

                /*Time[2017-02-10 12:54:09,559] Level[ERROR] FBDividend exception: System.IndexOutOfRangeException: Cannot find table 0.
                     at System.Data.DataTableCollection.get_Item(Int32 index)
                     at COM.HKJC.ES.BIS.Eda.EdaSalesHandler.DivCal.FBDividend(String sys, Int32 business_date, Boolean close_business)
                  Time[2017-02-10 12:54:09,559] Level[ERROR] FBDividend exception: System.IndexOutOfRangeException: Cannot find table 0.
                     at System.Data.DataTableCollection.get_Item(Int32 index)
                     at COM.HKJC.ES.BIS.Eda.EdaSalesHandler.DivCal.FBDividend(String sys, Int32 business_date, Boolean close_business)
                */

                if (string.IsNullOrEmpty(line.Trim()))
                    continue;

                int idx_logLevel = line.IndexOf(errorLevel);


                // Level[ERROR]
                if (idx_logLevel > 0)
                {
                    errors.Add(delimiterLeftBracket + file + delimiterComb + line);
                    tmpLogTime = line.Substring(0, timePattern.Length);
                    if (file.Contains(agpLog) && string.Compare(tmpLogTime, decodeAGPLastLogTime) >= 0)
                        decodeAGPLastLogTime = tmpLogTime;
                    else if (file.Contains(acpLog) && string.Compare(tmpLogTime, decodeACPLastLogTime) >= 0)
                        decodeACPLastLogTime = tmpLogTime;
                    else if (file.Contains(defaultLog) && string.Compare(tmpLogTime, defaultLastLogTime) >= 0)
                        defaultLastLogTime = tmpLogTime;
                    else if (file.Contains(solaceLog) && string.Compare(tmpLogTime, solaceLastLogTime) >= 0)
                        solaceLastLogTime = tmpLogTime;
                    else if (file.Contains(salesLog) && string.Compare(tmpLogTime, salesLastLogTime) >= 0)
                        salesLastLogTime = tmpLogTime;
                    else if (file.Contains(dbLog) && string.Compare(tmpLogTime, dbLastLogTime) >= 0)
                        dbLastLogTime = tmpLogTime;
                    else if (file.Contains(lghdLog) && string.Compare(tmpLogTime, lghdLastLogTime) >= 0)
                        lghdLastLogTime = tmpLogTime;
                    else if (file.Contains(eodLog) && string.Compare(tmpLogTime, eodLastLogTime) >= 0)
                        eodLastLogTime = tmpLogTime;
                    else if (file.Contains(messageLog) && string.Compare(tmpLogTime, msgLastLogTime) >= 0)
                        msgLastLogTime = tmpLogTime;
                }

                else if (line.Contains(debugLevel) || line.Contains(infoLevel) || line.Contains(warnLevel))
                {
                    tmpLogTime = string.Empty;
                }

                // "at System.Data..." not DEBUG and INFO, belongs to ERROR
                if (!(line.Contains(debugLevel) || line.Contains(infoLevel) || line.Contains(errorLevel) || line.Contains(warnLevel)) && !string.IsNullOrEmpty(tmpLogTime))
                    errors.Add(delimiterLeftBracket + file + delimiterComb + tmpLogTime + noHeader + line);
                    //errors.Add(tmpLogTime+line);

                //line = sr.ReadLine();

                DateTime endTime = DateTime.Now;
                TimeSpan elapsedTime = endTime - startTime;
                double totalTime = Math.Round(elapsedTime.TotalSeconds, 2);

                int minus = 0;

                if (this.TimingTB.InvokeRequired)
                {
                    this.TimingTB.Invoke(new Action(() =>
                    {

                        Int32.TryParse(TimingTB.Text.Trim(), out minus);
                    }));
                }
                else
                {
                    Int32.TryParse(TimingTB.Text.Trim(), out minus);
                }

                //Int32.TryParse(TimingTB.Text.Trim(), out minus);

                // write errors after 10 seconds
                if (errors.Count > 0 && totalTime >= 10)
                {
                    if (cancelToken.Token.IsCancellationRequested == true)
                    {
                        DeleteResultFile(file);
                        return;
                    }

                    WriteToFile(file, errors.ToArray()); // Write errors
                    errors.Clear();
                }
            }

            sr.Close();
            fs.Close();


            if (cancelToken.Token.IsCancellationRequested == true)
            {
                DeleteResultFile(file);
                return;
            }

            if (errors.Count > 0)
                WriteToFile(file, errors.ToArray()); // Write errors

            if (File.Exists(ScannedLogFiles))
            {
                string[] logFiles = File.ReadAllLines(ScannedLogFiles);
                if (logFiles.Length > 0)
                {
                    
                    //string file_Date = GetFileDate(file);
                    if (!logFiles.Contains(Path.GetFileName(file)))
                    {
                        FileStream fs4SLF = new FileStream(ScannedLogFiles, FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
                        StreamWriter sw4SLF = new StreamWriter(fs4SLF);
                        
                        sw4SLF.WriteLine(Path.GetFileName(file));
                        sw4SLF.Close();
                        fs4SLF.Close();
                    }
                }

            }

        }

        private void GetOldErrorContent(string file)
        {
            if (cancelToken.Token.IsCancellationRequested == true)
            {
                return;
            }


            List<string> errors = new List<string>();

            FileStream fs = new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            StreamReader sr = new StreamReader(fs);

            string tmpLogTime = string.Empty;

            string line;

            DateTime startTime = DateTime.Now;

            while ((line = sr.ReadLine()) != null)
            {
                if (cancelToken.Token.IsCancellationRequested == true)
                {
                    DeleteResultFile(file);
                    return;
                }

                //Error message sample:

                /*Time[2017-02-10 12:54:09,559] Level[ERROR] FBDividend exception: System.IndexOutOfRangeException: Cannot find table 0.
                     at System.Data.DataTableCollection.get_Item(Int32 index)
                     at COM.HKJC.ES.BIS.Eda.EdaSalesHandler.DivCal.FBDividend(String sys, Int32 business_date, Boolean close_business)
                  Time[2017-02-10 12:54:09,559] Level[ERROR] FBDividend exception: System.IndexOutOfRangeException: Cannot find table 0.
                     at System.Data.DataTableCollection.get_Item(Int32 index)
                     at COM.HKJC.ES.BIS.Eda.EdaSalesHandler.DivCal.FBDividend(String sys, Int32 business_date, Boolean close_business)
                */

                if (string.IsNullOrEmpty(line.Trim()))
                    continue;

                int idx_logLevel = line.IndexOf(errorLevel);

                if (line.Contains(debugLevel) || line.Contains(infoLevel) || line.Contains(errorLevel) || line.Contains(warnLevel))
                {
                    tmpLogTime = line.Substring(0, timePattern.Length);
                    //if (file.Contains(agpLog) && string.Compare(tmpLogTime, decodeAGPLastLogTime4Old) >= 0)
                    //    decodeAGPLastLogTime4Old = tmpLogTime;
                    //else if (file.Contains(acpLog) && string.Compare(tmpLogTime, decodeACPLastLogTime4Old) >= 0)
                    //    decodeACPLastLogTime4Old = tmpLogTime;
                    //else if (file.Contains(defaultLog) && string.Compare(tmpLogTime, defaultLastLogTime4Old) >= 0)
                    //    defaultLastLogTime4Old = tmpLogTime;
                    //else if (file.Contains(solaceLog) && string.Compare(tmpLogTime, solaceLastLogTime4Old) >= 0)
                    //    solaceLastLogTime = tmpLogTime;
                    //else if (file.Contains(salesLog) && string.Compare(tmpLogTime, salesLastLogTime4Old) >= 0)
                    //    salesLastLogTime4Old = tmpLogTime;
                    //else if (file.Contains(dbLog) && string.Compare(tmpLogTime, dbLastLogTime4Old) >= 0)
                    //    dbLastLogTime4Old = tmpLogTime;
                    //else if (file.Contains(lghdLog) && string.Compare(tmpLogTime, lghdLastLogTime4Old) >= 0)
                    //    lghdLastLogTime4Old = tmpLogTime;
                    //else if (file.Contains(eodLog) && string.Compare(tmpLogTime, eodLastLogTime4Old) >= 0)
                    //    eodLastLogTime4Old = tmpLogTime;
                }


                // Level[ERROR]
                if (idx_logLevel > 0)
                {
                    errors.Add(delimiterLeftBracket + file + delimiterComb + line);
                }

                else if (line.Contains(debugLevel) || line.Contains(infoLevel) || line.Contains(warnLevel))
                {
                    tmpLogTime = string.Empty;
                }

                // "at System.Data..." not DEBUG and INFO, belongs to ERROR
                if (!(line.Contains(debugLevel) || line.Contains(infoLevel) || line.Contains(errorLevel) || line.Contains(warnLevel)) && !string.IsNullOrEmpty(tmpLogTime))
                    errors.Add(delimiterLeftBracket + file + delimiterComb + tmpLogTime + noHeader + line);
                //errors.Add(tmpLogTime+line);

                //line = sr.ReadLine();

                DateTime endTime = DateTime.Now;
                TimeSpan elapsedTime = endTime - startTime;
                double totalTime = Math.Round(elapsedTime.TotalSeconds, 2);

                int minus = 0;

                if (this.TimingTB.InvokeRequired)
                {
                    this.TimingTB.Invoke(new Action(() =>
                    {

                        Int32.TryParse(TimingTB.Text.Trim(), out minus);
                    }));
                }
                else
                {
                    Int32.TryParse(TimingTB.Text.Trim(), out minus);
                }

                //Int32.TryParse(TimingTB.Text.Trim(), out minus);

                // write errors after 10 seconds
                if (errors.Count > 0 && totalTime >= 10)
                {
                    if (cancelToken.Token.IsCancellationRequested == true)
                    {
                        DeleteResultFile(file);
                        return;
                    }
                    //WriteToFile(file, errors.ToArray()); // Write errors
                    WriteToFile4Old(file, errors.ToArray());
                    errors.Clear();
                }
            }

            sr.Close();
            fs.Close();

            if (cancelToken.Token.IsCancellationRequested == true)
            {
                DeleteResultFile(file);
                return;
            }

            if (errors.Count > 0)
                //WriteToFile(file, errors.ToArray()); // Write errors
                WriteToFile4Old(file, errors.ToArray());

            FileStream fs4SLF = new FileStream(ScannedLogFiles, FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
            StreamWriter sw4SLF = new StreamWriter(fs4SLF);
            string logType = string.Empty;
            //if (file.Contains(acpLog))
            //    logType = "acp_decoder";
            //else if (file.Contains(agpLog))
            //    logType = "agp_decoder";
            //else if (file.Contains(defaultLog))
            //    logType = "default";
            //else if (file.Contains(solaceLog))
            //    logType = "solace";
            //else if (file.Contains(salesLog))
            //    logType = "sales";
            //else if (file.Contains(dbLog))
            //    logType = "db";
            //else if (file.Contains(lghdLog))
            //    logType = "lhgd";
            //else if (file.Contains(eodLog))
            //    logType = "eod";
            //else if (file.Contains(messageLog))
            //    logType = "message";

            //string fileDate = GetFileDate(file);

            sw4SLF.WriteLine(Path.GetFileName(file));
            sw4SLF.Close();
            fs4SLF.Close();
        }

        private void GetErrorsOfOldLogFile(string filePath)
        {
            if (cancelToken.Token.IsCancellationRequested == true)
                return;


            string[] dirs = Directory.GetDirectories(filePath);
            string[] files = Directory.GetFiles(filePath);

            //FileInfo[] fi = files.Select(x => new FileInfo(x)).OrderBy(x => x.LastWriteTime).ToArray();

            string lastLogFile = string.Empty;
            if (files.Length > 0)
            {
                lastLogFile = files.Select(x => new FileInfo(x)).OrderBy(x => x.Name).Last().FullName;

            }

            foreach (string file in files)
            {
                if (cancelToken.Token.IsCancellationRequested == true)
                    break;

                if (file == lastLogFile)
                    continue;

                bool isSkip = SkipOldLogFiles(file);// Skip other files and old log files that had been collected
                if (isSkip)
                    continue;

                //GetErrorContent(file);
                GetOldErrorContent(file);
            }

            foreach (string dir in dirs)
            {
                if (cancelToken.Token.IsCancellationRequested == true)
                    break;
                GetErrorsOfOldLogFile(dir);
            }
        }

        private void GetErrorsOfLastLogFile(string filePath)
        {
            if (cancelToken.Token.IsCancellationRequested == true)
                return;


            string[] dirs = Directory.GetDirectories(filePath);
            string[] files = Directory.GetFiles(filePath);

            if (files.Length > 0)
            {
                string lastLogFile = files.Select(x => new FileInfo(x)).OrderBy(x => x.Name).Last().FullName;

                //bool isSkip = SkipOldLogFiles(lastLogFile);// Skip other files and old log files that had been collected
                //if (isSkip)
                //    return;
                GetNewErrorContent(lastLogFile);
            }


            // \default\, \logger\, \eod\, \database\,\solace\,\sales\
            foreach (string dir in dirs)
            {
                if (cancelToken.Token.IsCancellationRequested == true)
                    break;
                GetErrorsOfLastLogFile(dir);
            }
        }

        private bool SkipOldLogFiles(string file)
        {
            //string lghdLastTime4Old = string.Empty;
            //string decodeAGPLastTime4Old = string.Empty;
            //string decodeACPLastTime4Old = string.Empty;
            //string defaultLastTime4Old = string.Empty;
            //string dbLastTime4Old = string.Empty;
            //string salesLastTime4Old = string.Empty;
            //string solaceLastTime4Old = string.Empty;
            //string eodLastTime4Old = string.Empty;

            //if (File.Exists(lastLogTimeFile4Old))
            //{
            //    string[] logTimes = File.ReadAllLines(lastLogTimeFile4Old);

            //    string logFile = string.Empty;
            //    string logTime = string.Empty;

            //    for (int i = 0; i < logTimes.Length; i++)
            //    {
            //        logFile = logTimes[i].Split(delimiterEqual.ToCharArray())[0];
            //        logTime = logTimes[i].Split(delimiterEqual.ToCharArray())[1];

            //        if (logFile == lghdLLT)
            //            lghdLastTime4Old = logTime;
            //        else if (logFile == defaultLLT)
            //            defaultLastTime4Old = logTime;
            //        else if (logFile == decodeAGPLLT)
            //            decodeAGPLastTime4Old = logTime;
            //        else if (logFile == decodeACPLLT)
            //            decodeACPLastTime4Old = logTime;
            //        else if (logFile == dbLLT)
            //            dbLastTime4Old = logTime;
            //        else if (logFile == solaceLLT)
            //            solaceLastTime4Old = logTime;
            //        else if (logFile == salesLLT)
            //            salesLastTime4Old = logTime;
            //        else if (logFile == eodLLT)
            //            eodLastTime4Old = logTime;

            //    }

            //    //if (file.Contains(acpLog) && !string.IsNullOrEmpty(decodeACPLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(agpLog) && !string.IsNullOrEmpty(decodeAGPLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(defaultLog) && !string.IsNullOrEmpty(defaultLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(lghdLog) && !string.IsNullOrEmpty(lghdLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(salesLog) && !string.IsNullOrEmpty(salesLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(eodLog) && !string.IsNullOrEmpty(eodLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(dbLog) && !string.IsNullOrEmpty(dbLastTime4Old))
            //    //    return true;
            //    //if (file.Contains(solaceLog) && !string.IsNullOrEmpty(salesLastTime4Old))
            //    //    return true;
            //}

            //string resultFile = GenerateResultFile(file);
            //if (File.Exists(resultFile))
            //{
            //    return true;
            //}

            if (File.Exists(ScannedLogFiles))
            {
                string[] logFiles = File.ReadAllLines(ScannedLogFiles);
                if (logFiles.Length>0)
                {
                    //string logType = string.Empty;

                    //if (file.Contains(acpLog))
                    //    logType = "acp_decoder";
                    //else if (file.Contains(agpLog))
                    //    logType = "agp_decoder";
                    //else if (file.Contains(defaultLog))
                    //    logType = "default";
                    //else if (file.Contains(solaceLog))
                    //    logType = "solace";
                    //else if (file.Contains(salesLog))
                    //    logType = "sales";
                    //else if (file.Contains(dbLog))
                    //    logType = "db";
                    //else if (file.Contains(lghdLog))
                    //    logType = "lhgd";
                    //else if (file.Contains(eodLog))
                    //    logType = "eod";

                    //string file_Date = GetFileDate(file);
                    if (logFiles.Contains(Path.GetFileName(file)))
                    {
                        return true;
                    }
                }

            }
            
            //string fileName = Path.GetFileName(file);

            //if (!fileName.Contains(lghdLog) && !fileName.Contains(defaultLog) && !fileName.Contains(acpLog) && !fileName.Contains(agpLog)
            //    && !fileName.Contains(dbLog) && !fileName.Contains(salesLog) && !fileName.Contains(solaceLog) && !fileName.Contains(messageLog))
            //    return true;

            //string fileDate = string.Empty;

            //if (fileName.Contains(lghdLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
            //    {
            //        fileDate = fileParts[3].Substring(0, 10); //QCEDABIAPP1_EDABI_LGHD_2017-01-17 123602.log
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)  // QCEDABIAPP1_EDABI_LGHD_2017-01-17 123602.log2017-01-18
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(lghdLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}
            //else if (fileName.Contains(defaultLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
            //    {
            //        fileDate = fileParts[2].Substring(0, 10);
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(defaultLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}
            //else if (fileName.Contains(acpLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
            //    {
            //        fileDate = Path.GetExtension(fileName).Substring(0, 10);
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(decodeACPLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}
            //else if (fileName.Contains(agpLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
            //    {
            //        fileDate = fileParts[2].Substring(0, 10);
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(decodeAGPLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}
            //else if (fileName.Contains(dbLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
            //    {
            //        fileDate = fileParts[3].Substring(0, 10);
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(dbLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}

            //else if (fileName.Contains(salesLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
            //    {
            //        fileDate = fileParts[3].Substring(0, 10);
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(salesLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}

            //else if (fileName.Contains(solaceLog))
            //{
            //    string[] fileParts = fileName.Split(delimiterLine);
            //    if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
            //    {
            //        fileDate = fileParts[3].Substring(0, 10);
            //        string ext = Path.GetExtension(fileName);
            //        if (ext.Length > 4)
            //            fileDate = ext.Substring(4);
            //        if (string.Compare(solaceLastTime4Old, fileDate) > 0)
            //            return true;
            //    }
            //}

            //resultFile = GenerateResultFile(fileDate);

            //if (!File.Exists(resultFile))
            //    File.Create(resultFile);

            return false;
        }

        private void TimingTB_TextChanged(object sender, EventArgs e)
        {

        }

        private void TimingTB_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!Char.IsNumber(e.KeyChar) && e.KeyChar != (char)8)
            {
                e.Handled = true;
            }
        }

        private bool IsFileInUse(string file)
        {
            bool isUse = true;

            FileStream fs = null;

            try
            {
                fs = new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.None);
                isUse = false;
            }
            catch (Exception)
            {
                isUse = true;
            }
            finally
            {
                if (fs != null)
                {
                    fs.Close();
                }
            }

            return isUse;
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo("Explorer.exe");
            string argFolder = defaultArchiveDir;

            if (!string.IsNullOrEmpty(ArchiveFolderTB.Text.Trim()))
                argFolder = ArchiveFolderTB.Text.Trim();

            //psi.Arguments = "/e,/select," + archiveFolder;
            psi.Arguments = argFolder;
            System.Diagnostics.Process.Start(psi);
        }

        private string GenerateResultFile(string filePath)
        {
            string fileName = Path.GetFileName(filePath);
            string fileDate = string.Empty;

            if (fileName.Contains(lghdLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10); //QCEDABIAPP1_EDABI_LGHD_2017-01-17 123602.log
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)  // QCEDABIAPP1_EDABI_LGHD_2017-01-17 123602.log2017-01-18
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(defaultLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
                {
                    fileDate = fileParts[2].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(acpLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
                {
                    fileDate = fileParts[2].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(agpLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
                {
                    fileDate = fileParts[2].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(dbLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }

            else if (fileName.Contains(salesLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }

            else if (fileName.Contains(solaceLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }

            else if (fileName.Contains(messageLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }


            string resultDir = ArchiveFolderTB.Text.Trim();

            if (string.IsNullOrEmpty(resultDir))
                resultDir = AppDomain.CurrentDomain.BaseDirectory + defaultArchiveFolder;

            if (!Directory.Exists(resultDir))
                Directory.CreateDirectory(resultDir);

            string hostName = System.Net.Dns.GetHostName();

            string resultFile = resultDir + "\\" + "Error_" + hostName + "_" + fileDate.Replace("-", "") + ".log";

            //string resultFile = resultDir + "\\" + "Error_" + hostName + "_" + fileDate + ".log";


            return resultFile;

        }

        private void RecordLastLogTime()
        {
            string lghdLastTime = string.Empty;
            string decodeAGPLastTime = string.Empty;
            string decodeACPLastTime = string.Empty;
            string defaultLastTime = string.Empty;
            string dbLastTime = string.Empty;
            string salesLastTime = string.Empty;
            string solaceLastTime = string.Empty;
            string eodLastTime = string.Empty;
            string msgLastTime = string.Empty;


            if (File.Exists(lastLogTimeFile))
            {
                string[] logTimes = File.ReadAllLines(lastLogTimeFile);

                string logFile = string.Empty;
                string logTime = string.Empty;

                for (int i = 0; i < logTimes.Length; i++)
                {
                    string[] logFileTime = logTimes[i].Split(delimiterEqual.ToCharArray());
                    if (logFileTime != null && logFileTime.Length == 2)
                    {
                        logFile = logFileTime[0];
                        logTime = logFileTime[1];

                        if (logFile == lghdLLT)
                        {
                            if (!string.IsNullOrEmpty(lghdLastLogTime))
                            {
                                if (string.Compare(lghdLastLogTime, logTime) >= 0)
                                    lghdLastTime = lghdLastLogTime;
                                else
                                    lghdLastTime = logTime;
                            }

                        }

                        else if (logFile == defaultLLT)
                        {
                            if (!string.IsNullOrEmpty(defaultLastLogTime))
                            {
                                if (string.Compare(defaultLastLogTime, logTime) >= 0)
                                    defaultLastTime = defaultLastLogTime;
                                else
                                    defaultLastTime = logTime;
                            }
                        }

                        else if (logFile == decodeAGPLLT)
                        {
                            if (!string.IsNullOrEmpty(decodeAGPLastLogTime))
                            {
                                if (string.Compare(decodeAGPLastLogTime, logTime) >= 0)
                                    decodeAGPLastTime = decodeAGPLastLogTime;
                                else
                                    decodeAGPLastTime = logTime;
                            }
                        }
                        else if (logFile == decodeACPLLT)
                        {
                            if (!string.IsNullOrEmpty(decodeACPLastLogTime))
                            {
                                if (string.Compare(decodeACPLastLogTime, logTime) >= 0)
                                    decodeACPLastTime = decodeACPLastLogTime;
                                else
                                    decodeACPLastTime = logTime;
                            }
                        }

                        else if (logFile == dbLLT)
                        {
                            if (!string.IsNullOrEmpty(dbLastLogTime))
                            {
                                if (string.Compare(dbLastLogTime, logTime) >= 0)
                                    dbLastTime = dbLastLogTime;
                                else
                                    dbLastTime = logTime;
                            }
                        }
                        else if (logFile == solaceLLT)
                        {
                            if (!string.IsNullOrEmpty(solaceLastLogTime))
                            {
                                if (string.Compare(solaceLastLogTime, logTime) >= 0)
                                    solaceLastTime = solaceLastLogTime;
                                else
                                    solaceLastTime = logTime;
                            }
                        }
                        else if (logFile == salesLLT)
                        {
                            if (!string.IsNullOrEmpty(salesLastLogTime))
                            {
                                if (string.Compare(salesLastLogTime, logTime) >= 0)
                                    salesLastTime = salesLastLogTime;
                                else
                                    salesLastTime = logTime;
                            }
                        }
                        else if (logFile == eodLLT)
                        {
                            if (!string.IsNullOrEmpty(eodLastLogTime))
                            {
                                if (string.Compare(eodLastLogTime, logTime) >= 0)
                                    eodLastTime = eodLastLogTime;
                                else
                                    eodLastTime = logTime;
                            }
                        }

                        else if (logFile == msgLLT)
                        {
                            if (!string.IsNullOrEmpty(msgLastLogTime))
                            {
                                if (string.Compare(msgLastLogTime, logTime) >= 0)
                                    msgLastTime = msgLastLogTime;
                                else
                                    msgLastTime = logTime;
                            }
                        }

                    }


                }

            }

            FileStream fs = new FileStream(lastLogTimeFile, FileMode.OpenOrCreate, FileAccess.Write);

            StreamWriter sw = new StreamWriter(fs);

            //StreamWriter sw = new StreamWriter(lastLogTimeFile, false);

            // record last log time
            sw.WriteLine(lghdLLT + delimiterEqual + lghdLastLogTime);
            sw.WriteLine(decodeAGPLLT + delimiterEqual + decodeAGPLastLogTime);
            sw.WriteLine(decodeACPLLT + delimiterEqual + decodeACPLastLogTime);
            sw.WriteLine(defaultLLT + delimiterEqual + defaultLastLogTime);
            sw.WriteLine(dbLLT + delimiterEqual + dbLastLogTime);
            sw.WriteLine(solaceLLT + delimiterEqual + solaceLastLogTime);
            sw.WriteLine(salesLLT + delimiterEqual + salesLastLogTime);
            sw.WriteLine(eodLLT + delimiterEqual + eodLastLogTime);
            sw.WriteLine(msgLLT + delimiterEqual + msgLastLogTime);

            sw.Flush();
            sw.Close();
            fs.Close();
        }

        private void RecordLastLogTime4Old()
        {
            #region last log time for old log files

            string lghdLastTime4Old = string.Empty;
            string decodeAGPLastTime4Old = string.Empty;
            string decodeACPLastTime4Old = string.Empty;
            string defaultLastTime4Old = string.Empty;
            string dbLastTime4Old = string.Empty;
            string salesLastTime4Old = string.Empty;
            string solaceLastTime4Old = string.Empty;
            string eodLastTime4Old = string.Empty;



            if (File.Exists(lastLogTimeFile4Old))
            {
                string[] logTimes = File.ReadAllLines(lastLogTimeFile4Old);

                string logFile = string.Empty;
                string logTime = string.Empty;

                for (int i = 0; i < logTimes.Length; i++)
                {
                    string[] logFileTime = logTimes[i].Split(delimiterEqual.ToCharArray());
                    if (logFileTime != null && logFileTime.Length == 2)
                    {
                        logFile = logFileTime[0];
                        logTime = logFileTime[1];

                        if (logFile == lghdLLT)
                            lghdLastTime4Old = logTime;
                        else if (logFile == defaultLLT)
                            defaultLastTime4Old = logTime;
                        else if (logFile == decodeAGPLLT)
                            decodeAGPLastTime4Old = logTime;
                        else if (logFile == decodeACPLLT)
                            decodeACPLastTime4Old = logTime;
                        else if (logFile == dbLLT)
                            dbLastTime4Old = logTime;
                        else if (logFile == solaceLLT)
                            solaceLastTime4Old = logTime;
                        else if (logFile == salesLLT)
                            salesLastTime4Old = logTime;
                        else if (logFile == eodLLT)
                            eodLastTime4Old = logTime;

                    }


                }

            }

            //StreamWriter sw4Old = new StreamWriter(lastLogTimeFile4Old, false);

            FileStream fs4Old = new FileStream(lastLogTimeFile4Old, FileMode.OpenOrCreate, FileAccess.ReadWrite);
            StreamWriter sw4Old = new StreamWriter(fs4Old);

            // record last log time
            if (!string.IsNullOrEmpty(lghdLastLogTime4Old))
            {
                if (string.Compare(lghdLastLogTime4Old, lghdLastTime4Old) >= 0)
                    sw4Old.WriteLine(lghdLLT + delimiterEqual + lghdLastLogTime4Old);
            }

            if (!string.IsNullOrEmpty(decodeAGPLastLogTime4Old))
            {
                if (string.Compare(decodeAGPLastLogTime4Old, decodeAGPLastTime4Old) >= 0)
                    sw4Old.WriteLine(decodeAGPLLT + delimiterEqual + decodeAGPLastLogTime4Old);
            }

            if (!string.IsNullOrEmpty(decodeACPLastLogTime4Old))
            {
                if (string.Compare(decodeACPLastLogTime4Old, decodeACPLastTime4Old) >= 0)
                    sw4Old.WriteLine(decodeACPLLT + delimiterEqual + decodeACPLastLogTime4Old);
            }

            if (!string.IsNullOrEmpty(defaultLastLogTime4Old))
            {
                if (string.Compare(defaultLastLogTime4Old, defaultLastTime4Old) >= 0)
                    sw4Old.WriteLine(defaultLLT + delimiterEqual + defaultLastLogTime4Old);
            }

            if (!string.IsNullOrEmpty(dbLastLogTime4Old))
            {
                if (string.Compare(dbLastLogTime4Old, dbLastTime4Old) >= 0)
                    sw4Old.WriteLine(dbLLT + delimiterEqual + dbLastLogTime4Old);
            }

            if (!string.IsNullOrEmpty(solaceLastLogTime4Old))
            {
                if (string.Compare(solaceLastLogTime4Old, solaceLastTime4Old) >= 0)
                    sw4Old.WriteLine(solaceLLT + delimiterEqual + solaceLastLogTime4Old);
            }

            if (!string.IsNullOrEmpty(salesLastLogTime4Old))
            {
                if (string.Compare(salesLastLogTime4Old, salesLastTime4Old) >= 0)
                    sw4Old.WriteLine(salesLLT + delimiterEqual + salesLastLogTime4Old);
            }
            if (!string.IsNullOrEmpty(eodLastLogTime4Old))
            {
                if (string.Compare(salesLastLogTime4Old, salesLastTime4Old) >= 0)
                    sw4Old.WriteLine(eodLLT + delimiterEqual + eodLastLogTime4Old);
            }

            sw4Old.Flush();
            sw4Old.Close();
            fs4Old.Close();

            #endregion
        }

        private void DeleteResultFile(string file)
        {
            string resultFile = GenerateResultFile(file);
            if (File.Exists(resultFile))
            {
                File.Delete(resultFile);
            }
        }

        private string GetFileDate(string filePath)
        {
            string fileName = Path.GetFileName(filePath);
            string fileDate = string.Empty;

            if (fileName.Contains(lghdLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10); //QCEDABIAPP1_EDABI_LGHD_2017-01-17 123602.log
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)  // QCEDABIAPP1_EDABI_LGHD_2017-01-17 123602.log2017-01-18
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(defaultLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
                {
                    fileDate = fileParts[2].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(acpLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
                {
                    fileDate = Path.GetExtension(fileName).Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(agpLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 3 && fileParts[2].Length >= 10)
                {
                    fileDate = fileParts[2].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }
            else if (fileName.Contains(dbLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }

            else if (fileName.Contains(salesLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }

            else if (fileName.Contains(solaceLog))
            {
                string[] fileParts = fileName.Split(delimiterLine);
                if (fileParts.Length >= 4 && fileParts[3].Length >= 10)
                {
                    fileDate = fileParts[3].Substring(0, 10);
                    string ext = Path.GetExtension(fileName);
                    if (ext.Length > 4)
                        fileDate = ext.Substring(4);
                }
            }

            return fileDate;
        }
    }
}