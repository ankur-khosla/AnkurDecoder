// ABPolLoyalty.cpp

#include "LOGDEF_AB.h"
#include "ABPolLoyalty.h"

char * ABPolLoyalty::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/
	unsigned long m_iAmount;
	unsigned long m_iCitNo;
	unsigned char m_cCitType;

	int m_iNegBal;

	memset( m_sRemarks, 0, 100 );

	m_iFundAva	= (unsigned long) pMlog->data.pol.loyalty.aca.fundd;
	m_iBankGd	= (unsigned long) pMlog->data.pol.loyalty.aca.bankgd;
	m_iCurrDiv	= (unsigned long) pMlog->data.pol.loyalty.aca.curDivd;
	m_iPrevDiv	= (unsigned long) pMlog->data.pol.loyalty.aca.prvDivd;
	m_iFbPayFor	= (unsigned long) pMlog->data.pol.loyalty.aca.sbPFtd;
	
	m_iAmount	= (unsigned long) pMlog->data.pol.loyalty.data.amountdu;
	m_iCitNo	= (unsigned long) pMlog->data.pol.loyalty.data.citdu;
	m_cCitType	= pMlog->data.pol.loyalty.data.cittypbu;
		
	for( i=0; i<ABPOL_TXT_MAX+1; i++ )
		m_sRemarks[i] = pMlog->data.pol.loyalty.data.remarks[i];

	m_iNegBal =  pMlog->data.pol.loyalty.negbal1;

	AddField( m_iFundAva, 0 );
	AddField( m_iBankGd, 0 );
	AddField( m_iCurrDiv, 0 );
	AddField( m_iPrevDiv, 0 );
	AddField( m_iFbPayFor, 0 );

	AddField( m_iAmount, 0 );
	AddField( m_iCitNo, 0 );
	AddField( m_cCitType, 0 );
	AddField( STORE_TYPE_STRING, m_sRemarks, 0 );

	AddField( m_iNegBal, 0 );

	return buf;

}
