/////////////////////////////////////////////////////////////////////
//
// CBStopPay.cpp: implementation of the CBStopPay class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBStopPay.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBStopPay::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	/*
	if((iRetVal=TranslateHeader(pMsg))!=NO_TRANSLATE_ERR)
	{
		return iRetVal;
	}
	*/

	struct LOG *pMlog;
	pMlog						= (struct LOG *)pMsg->m_cpBuf;

	PackHeader("cb_stop_pay_insert_sp", pMlog, pMsg);

	return buf;
}
