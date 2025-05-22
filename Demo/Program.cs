using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

namespace CSharpDemo
{
    enum LogLevel
    {
        Debug = 0,
        Info = 1,
        Error = 2
    }
    //store result from C++
    class Program
    {

        static void Main(string[] args)
        {

            //int[] array1 = { 1, 2, 3 };
            //int[] array2 = { 4, 5, 6 };

            //var cartesianProduct = from x in array1
            //                       from y in array2
            //                       select new { x, y };
            //int a = 0;


            // If debug one or some messages, please choose 1. If you test the whole log file, please 2.

            #region 1. Test some messages


            //string solaceMsg = "EgAAAC14MwGXFQAAAAAAAAAAAAAAAwADABoAAAAh9AdVAAAAACH0B1UAAAAAlxUAAAAAAAC5AAcABQAh9AdVAAAAAAAAAAC4rgoAAQAAAAAAAXQDAAA7AEwgAAAAAABdNQAAdkAAAAAAAABKmDsYYqU1AAAAAAAAAAAAAAAALXgzAZcVAAAAAAAABgAAAAAAAABIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFIp5EQBP2QOMTkAAQIAAAAFAAAAAABADQMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==";
            //string solaceMsg = "FAAAAIl4MwECLQMAAAAAAAAAAAAACwANAB4ADwAnKiZVAAAAABABAAAAAAAAJyomVQAAAACJeDMBcAEGAA8AAL/iDQAZBAAAIUD7AgAAAAAAAAAAAAAAEAEnKiZViywDAAAAAABGSAAAASj8Tl0HAAAAAAABAIl4MwEAAAItAwAAAAAA1EAAAAAAAAAvAwAAAAAAAAAAAAAAAAAAAAAZBAAAAAAAAAAAAAAAAAAAAwAAAAEAAMYGAAAAAAAAAAAAAACAPgAAAAAAAAAAAACJeDMBAQAAAQWJeDMBAwBdj7rZCwEAAAAAAAAAAAAADgAAAAAAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=";
            string[] solaceMsg =new string[] 
                {
                    "FAAAAN5TMwGucAAAAAAAAAAAAAAAAQADABIAAADnTEdUAAAAAF4AAAAAAAAAkgALAAAAAAAAAADeAAAAIW0PAAAAAAAAAAAAAAAAXgCyTEdUqXAAAAAAAAAOAAAABFACAAAKAAAAEQABIN5TMwEAAK5wAAAAAAAAAAAAAAAAAACiAQAAAAAAAAAAAAAAAAAAAADeAAAAAAAAAAAAAADidkdUUMMAAAAAAAAAAAAAAAAAAAUABIVpnM1dB1wBYQc=",
                    "FAAAANxTMwE3YgAAAAAAAAAAAAAAAgACABIAAADG30RUAAAAAAQAAAAAAAAAeAEFAAAABAAAAAAAAAAA82kPAAAAAAAAAAAAAAAABACV30RUNmIAAAAAAAABAAAACFACAAAKAAAAEQJEoNxTMwEAADdiAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACEeQAAAAAAAAAAAABg6gAAAAAAAAAAAAAAAAAAAwUIAPH7CQAAAOH1BQAAAAAIAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEAAAD1AQAAgwAAKgIAAAAAAAAAAAAAAAAANTMwMjIzAAAAAAAgICAgICAgICAgICAgAAAAAAAAAAAAAAAAAAAAAABOMEUzMUVEODUyODc2RjBGMDhEMzFCMTU0M0FCRjdERjQ0RURDQjlEQUY0RkI1OTcyQjg4Njk4NEJGRjhFMDA1RDFBNzVBODk0RTM5MDAwNDA1OTIwMTA0OTIxMTEwMjA2OTY1NTk3ICAgMDAwMDA2MDAwMDAwMDEyMzQ1Njc4OTAxMg=="
                } ; //ab_deposit
            //byte[] byteMsg = new byte[binMsg.Length/8];

            string binMsgStr = "14000000817833018A0203010000000000000000016703F7030A00000011731C55000000001C5581783301020C000605827833010500866157D90B01000000000000000000000E0000000000200000005C0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                + ";140000003B78330128040300000000000000000001130018000A00000084211B550000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
            + ";1400000036783301915CCA0000000000000000000001000100120000009DE31355000000001202000000000000FF000800000000103E0E00C60A000048689900000000000000000000000012029DE31355905CCA00000000007E4700000116980A000000000000000120367833010000915CCA0000000000B1610000000000001D5C2100000000003B25F90D000000000000C60A0000000000000000000011022F0000000000000000000000000000000080DB1255013B25F90D0000000000000000000000000000000000000100000000450000000188130000000000000A000000881300008FE31355367833011001000F00440000004000A09B0B9AF4010000310600000000801F0000000000000000000000000000000000000000000000881300000000000005050500";
            //    + "14000000367833019E5CCA00000000000000000000010001001E000000D8E51355000000001302000000000000D8E513550000000036783301DB000700000000103E0E00C60A00004868990000000000000000000000001302D8E51355915CCA00000000007F4700000116980A0000000000000001203678330100009E5CCA0000000000B1610000000000001D5C21000000000000000000000000000000C60A00000000000000000000000005000001000000000100000000EE080000010000000000000000050000005C44000000000000367833011000000F00440000006000A09B0B9AF4010000310700000000801F0002000000000000000000000000000000000000000000000000000000000000050500;"
            //    + "14000000367833019F5CCA000000000000000000000100010012000000DDE51355000000001402000000000000FF000800000000103E0E00C60A00004868990000000000000000000000001402DDE513559E5CCA0000000000404800000116980A0000000000000001203678330100009F5CCA0000000000B1610000000000001D5C2100000000004925F90D000000000000C60A0000000000000000000013022F0000000000000000000000000000000080DB1255014925F90D0000000000000000000000000000000000000100000000EE080000015C44000000000000050000005C440000D8E51355367833011001000F00440000006000A09B0B9AF4010000310700000000801F00020000000000000000000000000000000000000000005C4400000000000005050500";

            //binMsgStr = "110000008FA133017306F6B2000000000000000000000000000000000001000100C7000000C9CED4570000000059ECD0570000000000000000000000004E6ED1B200000000859502008CA1330159ECD0577306F6B200000000C913D1B200000000FCA1D1B200000000E30300000700000000000000000000007E5C6600000000000000000000000000000000000000000000010000000000000000008FA13301C9CED457130000007306F6B20000000000000000000000000000000000000000720300001800000000009AA1330143C6330144C63301010000007306F6B2000000000100000000000000E100080004000000000092E415000000000009780E00060064000000047203000018005C000000000000511800004A4000000000000002E9189434FBFFFFFFFFFF00000000000000008FA1330192E4150000000000F65F0000000000000CE30000000000000000000000000000000000000000000000008619B8831E36695D50580D0000000000000000000000000000000000000006006400000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
            //binMsgStr = "1400000009B33401303BE3000000000085A30E00000000000000000000020005001E00000001AF0C6500000000900200000000000001AF0C650000000009B33401C20006000000000E7103003E06000013522F000000000000000000000000900201AF0C652F3BE300000000007662000005000000003E5414000000012009B3340100000000000000000000035003000000000085A30E0000000000000000000000000000003E060000000000000000000000000000000000000000006C0D00000500000000000000000A000000B80B00000000000009B33401010008010509B334010100952E9E981E01000000000000000000000C00000000006400000000000000";
            //binMsgStr = "140000000CB334010BA9E30000000000BEAE0E000000000000000000000100010012000000649E0F6500000000020000000000000098000B00000000A58601002D0A000063D82F0000000000000000000000000200649E0F6508A9E300000000006F4600000501000000105C1100000001200CB3340100000000000000000000A8C2030000000000BEAE0E0000000000000000000000000000002D0A000000000000000000008CC10F6538C99A3B0000000000000000000000000D010531323334353637383132333435363730";
            //binMsgStr = "14000000FFB23401116DDF000000000027F10D0000000000000000000001003600120000007892FF64000000003001000000000000B801050000000000000000000000008B512F00000000000000000000000030017892FF64000000000000000000000000140000000000000000000000A0FFB2340100000000000000000000000000000000000000000000000000000000000000000000000003350C000000000000000000834E0000000000000A00000000000000060814007F96980000000000781800000000000000000000000000000000000000000000000000000000000047000000C892020000000000010000006700000001303234003531373731353033373600000000000000000000000000000000017B22737461747573223A312C227265666572656E63654E6F223A3136383634382C2273656E646572223A37312C226163636F756E744E6F223A223033313031303637222C227265636569766572223A32302C227472616E73616374696F6E54797065223A322C226E6261496E64696361746F72223A312C22616D6F756E74223A32303039392C2262616E6B436F6465223A22303234222C226E6261223A2235313737313530333736222C2266707350726F634964223A312C226670734368616E6E656C4964223A3130332C22636861726765223A31307D";
            binMsgStr = "1400000000B33401918DDF000000000034F60D0000000000000000000007000A0012000000B2E3FF64000000001E00000000000000E6000800000000328A0C00040B000090F8D50100000000000000000000001E00B2E3FF64B98CDF00000000005C400000014D8A0C00000000000000012000B3340100000000000000000000DEBD03000000000034F60D000000000036EF1B00000000000000040B000000000000000000001B0027000000000000000000000000000000008039FF640136EF1B0000000000000000000000000000000000030000EF08000001000000000000000014000000D007000048E3FF6400B33401010108070300B33401050085B51D981E01000000000000000000000C00000000002000000000000000";
            List<byte[]> bMsg = new List<byte[]>();
            string[] msgArr = binMsgStr.Split(';');

            //string tktPath = "C:\\Work\\EDABI\\cb_cancel.txt";
            //StreamReader srTkt = new StreamReader(tktPath);

            //List<string> tktBin = new List<string>();
            //string lineTkt = srTkt.ReadLine();
            //while (!string.IsNullOrEmpty(lineTkt))
            //{
            //    tktBin.Add(lineTkt);
            //    lineTkt = srTkt.ReadLine();
            //}
            //srTkt.Close();

            //msgArr = tktBin.ToArray();

            foreach (string binMsg in msgArr)
            {
                byte[] byteMsg = Enumerable.Range(0, binMsg.Length)
                .Where(x => x % 2 == 0)
                .Select(x => Convert.ToByte(binMsg.Substring(x, 2), 16))
                .ToArray();

                //byte[] byteMsgArr = new byte[binMsg.Length / 2];
                //for (int i = 0; i < binMsg.Length; i++)
                //{
                //    if (i % 2 == 0)
                //    {
                //        string msg = binMsg[i].ToString() + binMsg[i + 1].ToString();
                //        byte byteMsg = Convert.ToByte(msg, 16);
                //        byteMsgArr[i / 2] = byteMsg;
                //    }

                //}


                bMsg.Add(byteMsg);
            }



            //StreamWriter sw = new StreamWriter("C:\\FO1\\fileCode_eod.txt", false);

            ////int k = 0;

            //FileStream fs = new FileStream("C:\\FO1\\BISCSB01.20110822", FileMode.Open, FileAccess.ReadWrite);
            ////fs.Seek(-1024*4*1024, SeekOrigin.End);


            //StreamReader sr = new StreamReader(fs);
            //string lineStr = sr.ReadLine();
            ////sw.WriteLine(lineStr);
            //StringBuilder sb = new StringBuilder();
            //while (lineStr != null && lineStr!="")
            //{
            //    if (lineStr.Length >= 3)
            //    {
            //        string fileCode = lineStr.Substring(0, 3);
            //        if (!sb.ToString().Contains(fileCode))
            //            sb.Append(fileCode+"\r\n");
            //        //sw.WriteLine();
            //    }

            //    lineStr = sr.ReadLine();
            //    //k++;
            //}

            //sw.WriteLine(sb.ToString());

            //sr.Close();
            //sw.Close();

            //string[] files = Directory.GetFiles("\\\\edabishare\\root\\edabi_data");
            //foreach (string file in files)
            //{
            //    string src = Path.GetDirectoryName(file) +"\\"+ Path.GetFileNameWithoutExtension(file);
            //    string newFile= src + ".20150318";
            //    if (!File.Exists(newFile))
            //    File.Move(file,src+ ".20150318");
            //    Path.ChangeExtension(file, "20150318");
            //}

            //List<int> binSize = new List<int>();
            ////List<byte[]> bMsg = new List<byte[]>();

            //string[] msgs = solaceMsg;

            //int msgLen = 0;
            //msgLen = msgs.Length;

            ////List<byte[]> bMsg = new List<byte[]>();

            //for (int i = 0; i < msgLen; i++)
            //{
            //    string strMsg = msgs[i];
            //    byte[] bs = new byte[strMsg.Length];

            //    bs = Convert.FromBase64String(strMsg);
            //    bMsg.Add(bs);
            //}

            //StringBuilder sizeSB = new StringBuilder();
            //    foreach (byte[] msg in bMsg)
            //    {
            //        sizeSB.Append(msg.Length + ",");
            //    }

            //    string sizeStr = string.Empty;

            //    if (sizeSB.Length > 1)
            //        sizeStr = sizeSB.Remove(sizeSB.Length - 1, 1).ToString();



            //bMsg.Add(byteMsg);

            //DateTime startTime = DateTime.Now;
            string[] messags = DecodeACPMsg(bMsg); // If ACP message, call the method
            //string[] messags = DecodeACPMsg(bMsg); // If AGP message, call the method


            //DateTime endTime = DateTime.Now;
            //TimeSpan elapsedTime = endTime - startTime;
            //double totalTime = Math.Round(elapsedTime.TotalMilliseconds / 1000, 2);
            //Console.WriteLine("Total time:"+ totalTime + "s \nSpeed:" + Math.Round(messags.Length / (totalTime)) + "/s\n");
            //Console.WriteLine("Press any key to exit.");
            //Console.ReadKey();

            //DecodeAGPMsg(bMsg); // If AGP message, call the method

            //FileStream fs = new FileStream("C:\\Work\\SAT_Files\\result.txt", FileMode.OpenOrCreate, FileAccess.ReadWrite);

            StreamWriter sw = new StreamWriter("C:\\Work\\SAT_Files\\result.txt", false);

            foreach (string msg in messags)
            {
                sw.WriteLine(msg);
            }
            sw.Flush();
            sw.Close();
            //fs.Close();

            #endregion

            #region 2. Test whole log file messages

            List<byte[]> listACPMsgDecode = new List<byte[]>();
            List<byte[]> listAGPMsgDecode = new List<byte[]>();

            string logFile = "C:\\Work\\SAT_Files\\ALL_Logs\\default\\QCEDABIAPP1_DEBUG_2017-02-10 093138.log";


            string sp_sysid = "SystemID:";
            string sp_actcode = "ActivityCode:";
            string sp_actid = "ActivityID:";
            string sp_bzd = "BusinessDate:";
            string sp_pl = "PayLoad(Base64):";
            string sp_end = " =>>";

            string[] lines = File.ReadAllLines(logFile);
            int pos = 0;
            foreach (string line in lines)
            {
                if (string.IsNullOrWhiteSpace(line))
                    continue;
                //line sample:
                //Time[2016-10-20 11:31:13,852]  Level[DEBUG] SystemID:17 ActivityCode:3 ActivityID:1 BusinessDate:20160712 PayLoad(Base64):EQAAAPmhMwEBAAAAAAAAAAAAAAAAMgA1ABoAAACqLwRYAAAAAKovBFgAAAAAMgAAAAAAAAAhAQMAAQAAAAAAAAAAAAAAAAClhgEAAAAAAAAAAR0CAAABAEAAAAAAAABAKAAAREAAAAAAAAADAQHoAwAAAAAAAAAAAAAAAAAA+aEzATIAAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAY/P///////wQBDcaAUU1UgFEAAAAAAQEAAAAAAAAAAAAAAAAAAACLAAAAAAAAAAAAAAAAABjVAAAAAAAAAAAAAB0CHQIBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAoAAADoAwAAqi8EWPmhMwEBAAABAc+eMwEBANWPuyEOAQAAAAAAAAAAAAAOAAAAAAAEAAAA =>> LoggerManager.HandleAutoMessageEvent
                int idx_sysid = line.IndexOf(sp_sysid);
                int idx_actcode = line.IndexOf(sp_actcode);
                int idx_actid = line.IndexOf(sp_actid);
                int idx_bzd = line.IndexOf(sp_bzd);
                int idx_pl = line.IndexOf(sp_pl);
                int idx_end = line.IndexOf(sp_end);

                string activityCode = line.Substring(idx_actcode + sp_actcode.Length, 3);

                if (activityCode == "507" || activityCode == "508" || activityCode == "509" || activityCode == "510" || activityCode == "511")
                    continue;

                if (idx_end <= 0)
                {
                    idx_end = line.Length;
                }

                if (idx_sysid > 0 && idx_actcode > 0 && idx_actid > 0 && idx_bzd > 0 && idx_pl > 0 && idx_end > 0)
                {
                    pos = idx_sysid + sp_sysid.Length;
                    string systemId = line.Substring(pos, 2);

                    pos = idx_actid + sp_actid.Length;
                    pos = idx_bzd + sp_bzd.Length;
                    pos = idx_actcode + sp_actcode.Length;
                    pos = idx_pl + sp_pl.Length;
                    byte[] msgContent = Convert.FromBase64String(line.Substring(pos, idx_end - pos));
                    if (systemId == "17" || systemId == "18" || systemId == "19")
                    {
                        listAGPMsgDecode.Add(msgContent);
                    }
                    else if (systemId == "20" || systemId == "21")
                    {
                        listACPMsgDecode.Add(msgContent);
                    }
                }
            }

            Task[] taskDecoders = new Task[2];

            List<string> msgList = new List<string>();

            DateTime startTime = DateTime.Now;
            taskDecoders[0] = Task.Factory.StartNew(() => { msgList.AddRange(DecodeACPMsg(listACPMsgDecode)); });
            taskDecoders[1] = Task.Factory.StartNew(() => { msgList.AddRange(DecodeAGPMsg(listAGPMsgDecode)); });

            Task.WaitAll(taskDecoders);
            #endregion

            string resultDir = "C:\\Decoder\\results";

            if (!Directory.Exists(resultDir))
                Directory.CreateDirectory(resultDir);

            string resultFile = resultDir + "\\" + "result_" + DateTime.Now.ToString("yyyy-MM-dd HHmmss") + ".txt";

            if (msgList.Count > 0)
            {
                WriteToFile(resultFile, msgList.ToArray());
            }

            DateTime endTime = DateTime.Now;
            TimeSpan elapsedTime = endTime - startTime;
            double totalTime = Math.Round(elapsedTime.TotalSeconds, 2);
            Console.WriteLine("Speed:" + Math.Round((listACPMsgDecode.Count + listAGPMsgDecode.Count) / (totalTime)) + "/s\n");
            Console.WriteLine("Press any key to exit.");
            Console.ReadKey();
        }

        static int counter = 0;
        static object locked = new object();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="bMsg"></param>
        /// <param name="sysemType">0=acp,1=agp</param>
        /// <returns></returns>
        private static string[] DecodeACPMsg(List<byte[]> bMsg)
        {
            int msgCount = bMsg.Count;
            int msgSize = 8000;// max size of per message
            string[] message = null;

            List<IntPtr> pList = new List<IntPtr>();
            List<IntPtr> pSizeList = new List<IntPtr>();
            List<int> sizeList = new List<int>();
            //convert mamaged data (C#) to unmanaged(C++)
            foreach (byte[] m in bMsg)
            {
                IntPtr p = Marshal.AllocHGlobal(m.Length);
                Marshal.Copy(m, 0, p, m.Length);
                pList.Add(p);

                //IntPtr pSize = Marshal.AllocHGlobal(4);
                //byte[] bSize = BitConverter.GetBytes(m.Length);
                sizeList.Add(m.Length);
                //Marshal.Copy(new int[] { m.Length }, 0, pSize, 1);
                //pSizeList.Add(pSize);
            }

            //Allocate memory: source
            IntPtr pSource = Marshal.AllocHGlobal(msgCount * (Marshal.SizeOf(typeof(IntPtr))));
            Marshal.Copy(pList.ToArray(), 0, pSource, msgCount);

            int totalCount = 0;
            int errCount = 0;

            string logDir = AppDomain.CurrentDomain.BaseDirectory + "ACP_Decode\\";

            //call C++
            //the C++ may to add more return value to handle exceptions(e.g. out int error_msg_count)

            IntPtr pResult = CppDll.DecodeABMsgs(pSource, bMsg.Count, ref totalCount, ref errCount, logDir, (int)LogLevel.Info);


            //Result result = (Result)Marshal.PtrToStructure(pResult1, typeof(Result));
            // init result byte array
            byte[][] bResult = new byte[totalCount][];
            for (int i = 0; i < totalCount; i++)
            {
                bResult[i] = new byte[8000];
            }

            // string array to store decoded messages
            message = new string[totalCount];

            // get memery data from C++
            IntPtr[] pRet = new IntPtr[totalCount];
            Marshal.Copy(pResult, pRet, 0, totalCount);

            for (int i = 0; i < totalCount; i++)
            {
                Marshal.Copy(pRet[i], bResult[i], 0, msgSize);
                message[i] = Encoding.Default.GetString(bResult[i]).TrimEnd('\0');
            }

            //must free memory!!

            Marshal.FreeHGlobal(pSource);//source

            foreach (IntPtr p in pList)
            {
                Marshal.FreeHGlobal(p);
            }
            pSource = IntPtr.Zero;

            sizeList = null;

            // free result memory
            CppDll.ReleaseABMemory(pResult, totalCount);

            return message;

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="bMsg"></param>
        /// <param name="sysemType">0=acp,1=agp</param>
        /// <returns></returns>
        private static string[] DecodeAGPMsg(List<byte[]> bMsg)
        {
            int msgCount = bMsg.Count;
            int msgSize = 8000;// max size of per message
            string[] message = null;

            List<IntPtr> pList = new List<IntPtr>();
            //convert mamaged data (C#) to unmanaged(C++)
            foreach (byte[] m in bMsg)
            {
                IntPtr p = Marshal.AllocHGlobal(m.Length);
                Marshal.Copy(m, 0, p, m.Length);
                pList.Add(p);
            }

            //Allocate memory: source
            IntPtr pSource = Marshal.AllocHGlobal(msgCount * (Marshal.SizeOf(typeof(IntPtr))));
            Marshal.Copy(pList.ToArray(), 0, pSource, msgCount);

            int totalCount = 0;
            int errCount = 0;
            string logDir = AppDomain.CurrentDomain.BaseDirectory + "AGP_Decode\\";
            //call C++
            //the C++ may to add more return value to handle exceptions(e.g. out int error_msg_count)

            IntPtr pResult = CppDll.DecodeCBMsgs(pSource, bMsg.Count, ref totalCount, ref errCount, logDir, (int)LogLevel.Debug);

            // init result byte array
            byte[][] bResult = new byte[totalCount][];
            for (int i = 0; i < totalCount; i++)
            {
                bResult[i] = new byte[8000];
            }

            // string array to store decoded messages
            message = new string[totalCount];

            // get memery data from C++
            IntPtr[] pRet = new IntPtr[totalCount];
            Marshal.Copy(pResult, pRet, 0, totalCount);

            for (int i = 0; i < totalCount; i++)
            {
                Marshal.Copy(pRet[i], bResult[i], 0, msgSize);
                message[i] = Encoding.Default.GetString(bResult[i]).TrimEnd('\0');
            }

            //must free memory!!

            Marshal.FreeHGlobal(pSource);//source

            foreach (IntPtr p in pList)
            {
                Marshal.FreeHGlobal(p);
            }
            pSource = IntPtr.Zero;

            CppDll.ReleaseCBMemory(pResult, totalCount);

            return message;

        }

        public static void WriteToFile(string path, string[] msgArr)
        {
            if (msgArr == null && msgArr.Length <= 0)
                return;

            StreamWriter sw = new StreamWriter(path, false);

            foreach (string msg in msgArr)
            {
                sw.WriteLine(msg);
            }
            sw.Flush();
            sw.Close();
        }
    }
}
