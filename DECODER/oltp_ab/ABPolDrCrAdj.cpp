// ABDrCrAdjust.cpp

#include "LOGDEF_AB.h"
#include "ABPolDrCrAdj.h"

char * ABPolDrCrAdj::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	memset( m_sRemarks, 0, 520 );

	/***************** Start to decode *******************/


	m_iFundAva	= pMlog->data.pol.detcdt.aca.fundd;
	m_iBankGd	= pMlog->data.pol.detcdt.aca.bankgd;
	m_iCurrDiv	= pMlog->data.pol.detcdt.aca.curDivd;
	m_iPrevDiv	= pMlog->data.pol.detcdt.aca.prvDivd;
	m_iFbPayFor	= pMlog->data.pol.detcdt.aca.sbPFtd;
	
	m_iAmount	= pMlog->data.pol.detcdt.data.amountdu;
	m_cDrCrType = pMlog->data.pol.detcdt.data.typelu;

	if( pMlog->data.pol.detcdt.data.negbalb )
		m_iNegBal = 1;
	else
		m_iNegBal = 0;

    memset(m_sRemarks, 0, sizeof(m_sRemarks));

	for( i=0; i<ABPOL_TXT_MAX+1; i++ )
		m_sRemarks[i] = pMlog->data.pol.detcdt.data.remarks[i];

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

	AddField( m_cDrCrType, 0 );
	AddField( m_iNegBal, 0 );
	AddField64( m_iAmount, 0 );
	AddField( STORE_TYPE_STRING, m_sRemarks, 0 );

	return buf;

}
