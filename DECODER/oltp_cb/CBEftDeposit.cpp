// CBEftDeposit.cpp: implementation of the CBEftDeposit class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBEftDep.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBEftDep::TranslateAction(const Msg *pMsg)
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
	
	PackHeader("", pMlog, pMsg);
	EftHeader(pMlog, pMsg);
	m_iEftAmount	= pMlog->d.eft.body.eps.data.dep.amtlu;		// total cost in cents
	m_cPanType		= pMlog->d.eft.body.eps.data.dep.pantypbu;	// pan type
	sprintf(m_sCustName, "%s", pMlog->d.eft.body.eps.data.dep.names);		// customer name

	AddField(m_iEftAmount, 0);
	AddField(m_cPanType, 0);
	AddField(STORE_TYPE_STRING, m_sCustName, 0);

	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
