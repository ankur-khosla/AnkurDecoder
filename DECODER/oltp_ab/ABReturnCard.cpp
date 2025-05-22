// ABReturnCard.cpp

#include "LOGDEF_AB.h"
#include "ABReturnCard.h"

char * ABReturnCard::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	memset( m_sCustId, 0, sizeof(m_sCustId) );

	/***************** Start to decode *******************/

	for( i=0; i<19; i++ )
		m_sCustId[i] = pMlog->data.bt.escret.cusidb[i];

	m_iForDep		= pMlog->data.bt.escret.fordep1;
	m_iEscCardNo	= (unsigned __int64) pMlog->data.bt.escret.escdu;

	m_iAnnFeeRefund = pMlog->data.bt.escret.rpy.annlfeereflu;
	m_iDepFeeRefund = pMlog->data.bt.escret.rpy.depfeelreflu;


	AddField( STORE_TYPE_STRING, m_sCustId, 0 );
	AddField( m_iForDep, 0 );
	AddField64( m_iEscCardNo, 0 );

	AddField( m_iAnnFeeRefund, 0 );
	AddField( m_iDepFeeRefund, 0 );

	return buf;
}
