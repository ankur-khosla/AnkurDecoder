// MsgTranslator.cpp: implementation of the MsgTranslator class.
//
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "MsgTranslator.h"
#include "LOGDEF.H"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MsgTranslator::MsgTranslator()
{
	m_cSQL[0] = NULL;
	m_pRcd=NULL;
	m_pStorage=NULL;
}

MsgTranslator::~MsgTranslator()
{
	ReleaseRecord();
}

char * MsgTranslator::TranslateHeader(const Msg *pMsg)
{
	return (char*)NOT_IMPLEMENTED;
}

void MsgTranslator::SetMsgKey(int iLoggerId, int iLoggerMsgOrderNo)
{
	m_lLoggerTapeId=iLoggerId;
	m_iLoggerMsgOrderNo=iLoggerMsgOrderNo;
}

void MsgTranslator::SetStorage(Storage *pStorage)
{
	m_pStorage = pStorage;
}

void MsgTranslator::NewRecord()
{
	ReleaseRecord();
	m_pRcd=new RecordDef;
}

void MsgTranslator::ReleaseRecord()
{
	if (m_pRcd!=NULL)
	{
		delete m_pRcd;
		m_pRcd=NULL;
	}
}

char * MsgTranslator::Translate(const long lMsgType, const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	if((TranslateHeader(pMsg))!=NO_TRANSLATE_ERR)
	{
		return (char*)(&iRetVal);
	}

	char *buf = TranslateAction( pMsg );

	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet, lMsgType )!=STORE_NO_ERR||lRet!=0)
	{
		return (char*)(&SQL_ERR);
	}

	return buf;
}