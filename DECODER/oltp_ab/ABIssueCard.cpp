// ABIssueCard.cpp

#include "LOGDEF_AB.h"
#include "ABIssueCard.h"

char * ABIssueCard::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	memset( m_sCustId, 0, sizeof(m_sCustId) );

	/***************** Start to decode *******************/

	for( i=0; i<19; i++ )
		m_sCustId[i] = pMlog->data.bt.esciss.cusidb[i];

	m_iWaiveFlag	= pMlog->data.bt.esciss.wavflg1;
	m_iEscCardNo	= (unsigned __int64) pMlog->data.bt.esciss.escdu;
	m_iDepAmt		= pMlog->data.bt.esciss.depAmtdu;


	m_iFundAva		= pMlog->data.bt.esciss.tran.fundd;
	m_iBankGd		= pMlog->data.bt.esciss.tran.bankgd;
	m_iCurrDiv		= pMlog->data.bt.esciss.tran.curDivd;
	m_iPrevDiv		= pMlog->data.bt.esciss.tran.prvDivd;
	m_iFbPayFor		= pMlog->data.bt.esciss.tran.sbPFtd;

	m_iAnnFeeDeduct = pMlog->data.bt.esciss.rpy.annlfeededlu;
	m_iDepFeeDeduct = pMlog->data.bt.esciss.rpy.depfeededlu;

	AddField( STORE_TYPE_STRING, m_sCustId, 0 );
	AddField( m_iWaiveFlag, 0 );
	AddField64( m_iEscCardNo, 0 );
	AddField64( m_iDepAmt, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

	AddField( m_iAnnFeeDeduct, 0 );
	AddField( m_iDepFeeDeduct, 0 );

	return buf;
}
