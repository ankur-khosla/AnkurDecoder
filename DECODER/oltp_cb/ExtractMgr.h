// ExtractMgr.h: interface for the ExtractMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXTRACTMGR_H__85B7D304_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_EXTRACTMGR_H__85B7D304_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "JCLogger.h"
#include "JCSystem.h"
#include "Storage.h"
#include "LOGDEF.h"
#include "string"
#include <vector>

#define FILE_NAME_SIZE 257

using namespace std;

extern std::vector<string> v_SimSel;

class ExtractMgr  
{
public:
	int Run();
	FILE *BasicInfo;
	void SetSystem(JCSystem *);
	void SetLogger(JCLogger *);
	void SetStorage(Storage *);
	void SetMsgTranslator( MsgTranslator *);
	char ** DecodeCBMsgs(unsigned char ** srMsg, int len, int &totalCount, int &errCount, char *logDir, int logLevel);

	virtual const Msg * GetMsgObj(unsigned char *binArr, struct PAYLOAD_HDR *pHdr, LOG *pMlog);

	virtual LOG * GetLogObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, short &binSize);

	__time32_t Convert64TmTo32Tm(__int64 time64_t);
	void WriteInfoLog(char* logDir, int level, const char* infoStr);
	//void WriteStdExceptLog(char* logDir, const exception& e, char *erStr, unsigned int system_id, unsigned __int64 activity_id);
	//void WriteOtherExceptLog(char* logDir, char *errStr, int level);
	//void WriteStattLog(char* logDir, char *errStr, int count);
	void WriteErrorLog(char* logDir, char *errStr, int level);

	void AddSolaceHdr(PAYLOAD_HDR *pHdr, char *buf, char *tmp, const char *hdrDelimiter);

	ExtractMgr();
	virtual ~ExtractMgr();

private:

	JCSystem *m_pSysMgr;

	char m_cpFileName[FILE_NAME_SIZE];
	char m_cDate[20];
	char ErrorLogFile[50];

	unsigned char *plHdr_Buf;//payload header 
	unsigned char *plExtData_Buf;//payload header buffer

protected:
	Msg *pMsg;
};

#endif // !defined(AFX_EXTRACTMGR_H__85B7D304_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
