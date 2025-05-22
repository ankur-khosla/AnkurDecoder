// ABCitIssue.cpp


#include "LOGDEF_AB.h"
#include "ABCitCancel.h"

char * ABCitCancel::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	m_cDevType	= pMlog->data.bt.devcan.devbu;
	m_iDevNo	= pMlog->data.bt.devcan.devdu;
	m_cForDep	= pMlog->data.bt.devcan.fordep1;

	m_iFundAva	= pMlog->data.bt.devcan.tran.fundd;    // funds available
	m_iBankGd	= pMlog->data.bt.devcan.tran.bankgd;   // bank guarentee
	m_iCurrDiv	= pMlog->data.bt.devcan.tran.curDivd;  // unsettled dividend
	m_iPrevDiv	= pMlog->data.bt.devcan.tran.prvDivd;  // previous dividend
	m_iFbPayFor	= pMlog->data.bt.devcan.tran.sbPFtd;   // soccer fo payout forfeited
	
//	m_cDisable = pMlog->data.bt.devcan.bcs.disable1;

	m_iAnnFeeRefund = pMlog->data.bt.devcan.rpy.annlfeereflu;
	m_iDepFeeRefund = pMlog->data.bt.devcan.rpy.depfeelreflu;


	AddField( m_cDevType, 0 );
	AddField64( m_iDevNo, 0 );
	AddField( m_cForDep, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

//	AddField( m_cDisable, 0 );

	AddField( m_iAnnFeeRefund, 0 );
	AddField( m_iDepFeeRefund, 0 );

	return buf;
}
