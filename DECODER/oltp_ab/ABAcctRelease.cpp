// ABAcctRelease.cpp

#include "LOGDEF_AB.h"
#include "ABAcctRelease.h"

char * ABAcctRelease::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

	m_iKeyStrCnt = pMlog->data.bt.acr.keyStrokewu;
	m_cErrStrCnt = pMlog->data.bt.acr.errStrokebu;
	m_cRelCode = pMlog->data.bt.acr.relcodbu;

	m_iBankGd	= pMlog->data.bt.acr.bankgd;
	m_iCurrdiv	= pMlog->data.bt.acr.curDivd;
	m_iPayFor	= pMlog->data.bt.acr.sbPFtd;
	m_iFundAva	= pMlog->data.bt.acr.tran.fundd;

	AddField( m_iKeyStrCnt, 0 );
	AddField( m_cErrStrCnt, 0 );
	AddField( m_cRelCode, 0 );

	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrdiv, 0 );
	AddField64( m_iPayFor, 0 );
	AddField64( m_iFundAva, 0 );

	return buf;
}
