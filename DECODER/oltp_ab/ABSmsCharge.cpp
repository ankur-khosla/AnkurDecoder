// ABSmsCharge.cpp: implementation of the ABSmsCharge class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABSmsCharge.h"
#include "LOGDEF_AB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ABSmsCharge::ABSmsCharge()
{

}

ABSmsCharge::~ABSmsCharge()
{

}


char * ABSmsCharge::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	int m_iAmount = pMlog->data.bt.smscharge.amount;
	int m_iReasonCode = pMlog->data.bt.smscharge.reasonCode;

	AddField( m_iAmount, 0 );
	AddField( m_iReasonCode, 0 );

	return buf;
}
