
// CBCashOut.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBCashOut.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBCashOut::TranslateAction(const Msg *pMsg)
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

	PackHeader("cb_cash_out_insert_sp", pMlog, pMsg);

	//struct LOGBTBCS
//	m_iInterSys		= pMlog->d.bt.cio.othsys.ismsnlu;		// inter-system msn
//	m_iInterSys = 0;
	m_iDisable		= pMlog->d.bt.cio.othsys.disable1;		// bcs service is disabled

	m_iAmount		= pMlog->d.bt.cio.amtlu;				// amount in cent
	m_iCashierNo	= pMlog->d.bt.cio.cstflu;				// cashier #
	m_iCashPass		= pMlog->d.bt.cio.cpwdlu;				// cashier password
	char temp[2];
	sprintf(temp, "%c", pMlog->d.bt.cio.ccodb[1]);		// cashier code
	sprintf(m_cCashCode, "%c", pMlog->d.bt.cio.ccodb[0]);
	strcat(m_cCashCode, temp);

	//Output
//	AddField(m_iInterSys, 0);
	AddField(m_iDisable, 0);
	AddField(m_iAmount, 0);
	AddField(m_iCashierNo, 0);
	AddField(m_iCashPass, 0);
	AddField(STORE_TYPE_STRING, m_cCashCode, 0);


	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
