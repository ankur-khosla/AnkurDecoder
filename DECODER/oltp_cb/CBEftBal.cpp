/////////////////////////////////////////////////////////////////////
//
// CBEftBal.cpp: implementation of the CBEftBal class.
//
/////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "LOGDEF.h"
#include "CBEftBal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBEftBal::TranslateAction(const Msg *pMsg)
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
	
	PackHeader("cb_eft_balance_sp", pMlog, pMsg);
	EftHeader(pMlog, pMsg);

	m_iBalance = pMlog->d.eft.body.eps.data.bal.balamtd;		// account cash balance
	sprintf(m_sBalance, "%d", m_iBalance);

	AddField(STORE_TYPE_STRING, m_sBalance, 0);



	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
