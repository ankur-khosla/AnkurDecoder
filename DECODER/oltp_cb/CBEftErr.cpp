/////////////////////////////////////////////////////////////////////
//
// CBEftErr.cpp: implementation of the CBEftErr class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBEftErr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBEftErr::TranslateAction(const Msg *pMsg)
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


	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}



