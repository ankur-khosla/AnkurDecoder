// ABEodCrAdj.cpp

#include "LOGDEF_AB.h"
#include "ABEodCrAdj.h"

char * ABEodCrAdj::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	memset( m_sRemarks, 0, 100 );

	/***************** Start to decode *******************/

	m_iSize = pMlog->data.eod.drcr.h.sizewu;
	m_iTranCode = pMlog->data.eod.drcr.h.codewu;
	m_iTranNo = pMlog->data.eod.drcr.h.tranwu;
	m_iTranMerge = pMlog->data.eod.drcr.h.merge1;

	m_iAmount = pMlog->data.eod.drcr.body.amountdu;
	m_iAdjType = pMlog->data.eod.drcr.body.typelu;

	for( i=0; i<51; i++ )
		m_sRemarks[i] = pMlog->data.eod.drcr.body.remarks[i];

	m_sRemarks[52] = 0;

	AddField( m_iSize, 0 );
	AddField( m_iTranCode, 0 );
	AddField( m_iTranNo, 0 );
	AddField( m_iTranMerge, 0 );

	AddField64( m_iAmount, 0 );
	AddField( m_iAdjType, 0 );
	AddField( STORE_TYPE_STRING, m_sRemarks, 0 );


	return buf;
}
