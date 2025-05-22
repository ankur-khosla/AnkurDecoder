// ABCitIssue.cpp


#include "LOGDEF_AB.h"
#include "ABCitIssue.h"

char * ABCitIssue::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	m_cDevType	= pMlog->data.bt.deviss.devbu;
	m_iDevNo	= pMlog->data.bt.deviss.devdu;
	m_cCitVer	= pMlog->data.bt.deviss.verbu;

	m_iFundAva	= pMlog->data.bt.deviss.tran.fundd;    // funds available
	m_iBankGd	= pMlog->data.bt.deviss.tran.bankgd;   // bank guarentee
	m_iCurrDiv	= pMlog->data.bt.deviss.tran.curDivd;  // unsettled dividend
	m_iPrevDiv	= pMlog->data.bt.deviss.tran.prvDivd;  // previous dividend
	m_iFbPayFor	= pMlog->data.bt.deviss.tran.sbPFtd;   // soccer fo payout forfeited
	
	m_cDisable = pMlog->data.bt.deviss.bcs.disable1;

	m_iAnnFeeDeduct = pMlog->data.bt.deviss.rpy.annlfeededlu;
	m_iDepFeeDeduct = pMlog->data.bt.deviss.rpy.depfeededlu;

	AddField( m_cDevType, 0 );
	AddField64( m_iDevNo, 0 );
	AddField( m_cCitVer, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

	AddField( m_cDisable, 0 );

	AddField( m_iAnnFeeDeduct, 0 );
	AddField( m_iDepFeeDeduct, 0 );

	return buf;
}
