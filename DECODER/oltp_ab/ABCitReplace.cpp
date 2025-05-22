// ABCitReplace.cpp

#include "LOGDEF_AB.h"
#include "ABCitReplace.h"

char * ABCitReplace::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	m_cODevType	= pMlog->data.bt.devrepl.olddevbu;
	m_iODevNo	= pMlog->data.bt.devrepl.olddevdu;
	m_iNDevType	= pMlog->data.bt.devrepl.newdevbu;
	m_iNDevNo	= pMlog->data.bt.devrepl.newdevdu;
	m_cNCitVer	= pMlog->data.bt.devrepl.newverbu;
	m_cUpdDep	= pMlog->data.bt.devrepl.upddep1;
	m_cForDep	= pMlog->data.bt.devrepl.fordep1;
	m_cVerSCode	= pMlog->data.bt.devrepl.versecu1;


	m_iFundAva	= pMlog->data.bt.devrepl.tran.fundd;    // funds available
	m_iBankGd	= pMlog->data.bt.devrepl.tran.bankgd;   // bank guarentee
	m_iCurrDiv	= pMlog->data.bt.devrepl.tran.curDivd;  // unsettled dividend
	m_iPrevDiv	= pMlog->data.bt.devrepl.tran.prvDivd;  // previous dividend
	m_iFbPayFor	= pMlog->data.bt.devrepl.tran.sbPFtd;   // soccer fo payout forfeited
	

	m_iDisable = pMlog->data.bt.devrepl.bcs.disable1;

	m_iAnnFeeDe = pMlog->data.bt.devrepl.rpy.annlfeededlu;
	m_iDepFeeDe = pMlog->data.bt.devrepl.rpy.depfeededlu;
	m_iAnnFeeRe = pMlog->data.bt.devrepl.rpy.annlfeereflu;
	m_iDepFeeRe = pMlog->data.bt.devrepl.rpy.depfeelreflu;

	AddField( m_cODevType, 0 );
	AddField64( m_iODevNo, 0 );
	AddField( m_iNDevType, 0 );
	AddField64( m_iNDevNo, 0 );
	AddField( m_cNCitVer, 0 );
	AddField( m_cUpdDep, 0 );
	AddField( m_cForDep, 0 );
	AddField( m_cVerSCode, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

	AddField( m_iDisable, 0 );

	AddField( m_iAnnFeeDe, 0 );
	AddField( m_iDepFeeDe, 0 );
	AddField( m_iAnnFeeRe, 0 );
	AddField( m_iDepFeeRe, 0 );

	return buf;
}
