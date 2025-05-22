// dllmain.cpp : Defines the entry point for the DLL application.
#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include <stdlib.h>

#include "ExtractMgr.h"

/*
The function is used to decode binary message from Solace. 2016.7.28 paul
	binArr: binary array;
	len: length of the array
*/
extern "C" __declspec(dllexport) char ** DecodeABMsgs(unsigned char ** srMsg, int len, int &totalCount, int &errCount, char *logDir, int logLevel)
{
	ExtractMgr ABExtract;
	
	char **result  = ABExtract.DecodeABMsgs(srMsg, len, totalCount, errCount, logDir, logLevel);

	return result;
}

extern "C" __declspec(dllexport) void ReleaseABMemory(char ** retMsg, int total)
{
	if (retMsg == NULL)
		return;
	for (int i = 0; i < total; i++)
	{
		delete[] retMsg[i];
	}

	delete[] retMsg;
}