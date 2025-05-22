// ABCardReplace.cpp

#include "LOGDEF_AB.h"
#include "ABCardReplace.h"

char * ABCardReplace::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	char m_sCustId[20];

	unsigned long m_iOEscCardNo = ( unsigned long )pMlog->data.bt.escrep.oldEscdu;
	unsigned long m_iNEscCardNo	= ( unsigned long )pMlog->data.bt.escrep.newEscdu;
	sprintf( m_sCustId, "%s", pMlog->data.bt.escrep.cusidb );
//	unsigned int m_iSecCode		= pMlog->data.bt.escrep.seculu;
	unsigned int m_iForDep		= pMlog->data.bt.escrep.fordep1;
	unsigned int m_iWavDep		= pMlog->data.bt.escrep.wavdep1;

	unsigned long m_iFundAva	= ( unsigned long )pMlog->data.bt.escrep.tran.fundd;    // funds available
	unsigned long m_iBankGd		= ( unsigned long )pMlog->data.bt.escrep.tran.bankgd;   // bank guarentee
	unsigned long m_iCurrDiv	= ( unsigned long )pMlog->data.bt.escrep.tran.curDivd;  // unsettled dividend
	unsigned long m_iPrevDiv	= ( unsigned long )pMlog->data.bt.escrep.tran.prvDivd;  // previous dividend
	unsigned long m_iFbPayFor	= ( unsigned long )pMlog->data.bt.escrep.tran.sbPFtd;   // soccer fo payout forfeited
	
	AddField( m_iOEscCardNo, 0 );
	AddField( m_iNEscCardNo, 0 );
	AddField( STORE_TYPE_STRING, m_sCustId, 0 );
//	AddField( m_iSecCode, 0 );
	AddField( m_iForDep, 0 );
	AddField( m_iWavDep, 0 );
	AddField( m_iFundAva, 0 );
	AddField( m_iBankGd, 0 );
	AddField( m_iCurrDiv, 0 );
	AddField( m_iPrevDiv, 0 );
	AddField( m_iFbPayFor, 0 );

	return buf;
}
