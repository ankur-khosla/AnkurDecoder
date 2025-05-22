// JCSystem.cpp: implementation of the JCSystem class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "JCSystem.h"
#include "JCLogger.h"
#include "MsgTranslator.h"
#include "Terminal.h"
#include "CBMsgTranslator.h"

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

JCSystem::JCSystem()
{
	m_pStorage=NULL;
	m_pCtrlBlk=NULL;

	m_lLoggerTapeId=0;
	m_iLoggerMsgOrderNo=0;
	m_iCustSession=1;
}

JCSystem::~JCSystem()
{
}

char * JCSystem::DecMsg(const Msg *pMsg)
{
	return NULL;
}


void JCSystem::SetStorage(Storage *pStorage)
{
	m_pStorage = pStorage;
}

int JCSystem::SetInfo(const CtrlBlk *pCtrlBlk, char Date[20])
{
	if(pCtrlBlk!=NULL)
	{
		m_pCtrlBlk=pCtrlBlk;
		return 1;
	} else {
		return 0;
	}
}
