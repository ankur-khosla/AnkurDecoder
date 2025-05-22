using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using CSharpDemo;
using System.Runtime.ExceptionServices;

namespace CSharpDemo
{
    public class CppDll
    {
        [DllImport("VCDllDemo.dll",CharSet =  CharSet.Auto,CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add (int x, int y);

        [DllImport("VCDllDemo.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        public static extern byte TestByteArray(IntPtr msg, int len);

        [DllImport("VCDllDemo.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr TestString();

        [DllImport("VCDllDemo.dll", CharSet = CharSet.Auto, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr TestArrayOut(ref double[] Output, out int size);

        [DllImport("VCDllDemo.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr TestByteArrayAndReturnStr(IntPtr msg, int len);

        [DllImport("oltp_ab.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr DecodeABMsg(IntPtr msg, int len, int which);

        [DllImport("oltp_ab.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Init();

        [DllImport("oltp_cb.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr DecodeCBMsg(IntPtr msg, int len);

        //[HandleProcessCorruptedStateExceptions]
        [DllImport("oltp_ab.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr DecodeABMsgs(IntPtr msg, int len,  ref int totalCount,  ref int errCount,string logDir,int logLevel);

        [HandleProcessCorruptedStateExceptions]
        [DllImport("oltp_cb.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr DecodeCBMsgs(IntPtr msg, int len, ref int totalCount, ref int errCount, string logDir, int logLevel);

        [HandleProcessCorruptedStateExceptions]
        [DllImport("oltp_ab.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReleaseABMemory(IntPtr pRet, int total);

        [HandleProcessCorruptedStateExceptions]
        [DllImport("oltp_cb.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReleaseCBMemory(IntPtr pRet, int total);
    }
}
