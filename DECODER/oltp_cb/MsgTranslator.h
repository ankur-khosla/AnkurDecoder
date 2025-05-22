// MsgTranslator.h: interface for the MsgTranslator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGTRANSLATOR_H__5EE3F099_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_MSGTRANSLATOR_H__5EE3F099_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const	int NO_TRANSLATE_ERR	= 0;
const	int TRANSLATE_ERR		= 1;
const	int NOT_IMPLEMENTED		= 2;
const	int SQL_ERR				= 3;
const	int NO_STORAGE_DEFINED	= 4;
const	int NO_TERMINAL_DEFINED	= 5;
const   int MSG_ERR				= 6;  // Added on 19/7/00. Error code in the msg hdr is not zero

#include "JCLogger.h"
#include "Storage.h"

class MsgTranslator
{
public:
	virtual void SetStorage(Storage *pStorage);
	virtual void SetMsgKey(int iLoggerId, int iLoggerMsgOrderNo);
	char * Translate(const long lMsgType, const Msg *pMsg);
	virtual char * TranslateAction(const Msg *pMsg)=0;

	MsgTranslator();
	virtual ~MsgTranslator();
	int m_iTerminalType;	//	dm9, dm2000, mtbt, ngbt
	int m_iOperateMode;		//	0-opt 1-svt 2-mtbt
	int m_iCustSession;
	RecordDef *m_pRcd;	    //remove it from protected area. 2016.8.1

protected:
	virtual void ReleaseRecord();
	virtual void NewRecord();
	virtual void PackHeader(char *cpStoreProcName, struct LOG *pMlog, const Msg *pMsg) =0;
	virtual char * TranslateHeader(const Msg *pMsg)=0;
	// eft header
	virtual void EftHeader(struct LOG *pMlog, const Msg *pMsg) =0;

	char m_cSQL[1024];
	Storage *m_pStorage;

	long m_lLoggerTapeId;
	long m_iLoggerMsgOrderNo;
	
};

#endif // !defined(AFX_MSGTRANSLATOR_H__5EE3F099_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
