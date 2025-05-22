// dllmain.cpp : Defines the entry point for the DLL application.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ExtractMgr.h"
#include "string"
using namespace std;

/*
The function is used to decode binary message from Solace. 2016.7.28 paul
	binArr: binary array;
	len: length of the array
*/
extern "C" __declspec(dllexport) char ** DecodeCBMsgs(unsigned char ** srMsg, int len, int &totalCount, int &errCount, char *logDir, int logLevel)
{
	ExtractMgr CBExtract;
	
	char **result = CBExtract.DecodeCBMsgs(srMsg, len, totalCount, errCount, logDir, logLevel);
	return result;
}

extern "C" __declspec(dllexport) void ReleaseCBMemory(char ** retMsg, int total)
{
	if (retMsg == NULL)
		return;
	for (int i = 0; i < total; i++)
	{
		delete[] retMsg[i];
	}

	delete[] retMsg;
}