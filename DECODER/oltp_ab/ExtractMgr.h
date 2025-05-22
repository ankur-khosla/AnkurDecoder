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
#include "LOGDEF_AB.h"
#include <vector>

using namespace std;

extern std::vector<string> v_SimSel;
//static std::vector<char*> v_SimSel;

class ExtractMgr  
{
public:
	int Run();
	FILE *BasicInfo;
	void SetSystem(JCSystem *);
	void SetLogger(JCLogger *);
	void SetStorage(Storage *);
	void SetMsgTranslator( MsgTranslator *);
	char ** DecodeABMsgs(unsigned char ** srMsg, int len, int &totalCount, int &errCount, char *logDir, int logLevel);

	virtual const Msg * GetMsgObj(unsigned char *binArr, struct PAYLOAD_HDR *pHdr, LOGAB *pMlog);
	virtual const Msg * GetEODMsgObj(unsigned char *binArr, LOGAB *pMlog);
	virtual LOGAB * GetLogObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, short &binSize);
	virtual LOGAB * GetEODLogObj(unsigned char *binArr);
	virtual int GetBinarySize(unsigned char *binArr);

	__time32_t Convert64TmTo32Tm(__int64 time64_t);
	void WriteInfoLog(char* logDir, int level, const char* infoStr);
	void WriteErrorLog(char* logDir, char *errStr, int level);

	void AddSolaceHdr(PAYLOAD_HDR *pHdr, char *buf, char *tmp, const char *hdrDelimiter);

	char * GetLevelLogInfo(int level, const char *infoStr);

	/*static std::vector<char*> v_SimSel;*/


	ExtractMgr();
	virtual ~ExtractMgr();

private:

	Storage	 *m_pStoreMgr;
	JCSystem *m_pSysMgr;
	JCLogger *m_pLogMgr;
	//MsgTranslator	*m_pMsgTrltr;

	unsigned char *plHdr_Buf;//payload header buffer
	unsigned char *plExtData_Buf;//payload header buffer

public:
	MsgTranslator	*m_pMsgTrltr;
	Msg *pMsg;
};

#endif // !defined(AFX_EXTRACTMGR_H__85B7D304_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
