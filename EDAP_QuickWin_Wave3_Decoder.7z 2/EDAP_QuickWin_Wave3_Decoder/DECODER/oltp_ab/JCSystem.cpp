// JCSystem.cpp: implementation of the JCSystem class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "JCSystem.h"
#include "JCLogger.h"
#include "MsgTranslator.h"
#include "ABMsgTranslator.h"
//#include "Terminal.h"

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

