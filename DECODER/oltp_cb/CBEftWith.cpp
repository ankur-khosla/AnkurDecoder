/////////////////////////////////////////////////////////////////////
//
// CBEftWith.cpp: implementation of the CBEftWith class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBEftWith.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBEftWith::TranslateAction(const Msg *pMsg)
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

	// struct LOGEFTWTW
	m_iTotCost		= pMlog->d.eft.body.eps.data.wtw.amtlu;		// total cost in cents
	m_iWithType		= pMlog->d.eft.body.eps.data.wtw.wtwtypbu;	// withdrawal type

	AddField(m_iTotCost, 0);
	AddField(m_iWithType, 0);


	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}

