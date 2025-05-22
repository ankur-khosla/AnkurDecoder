// ABTxnEnquiry.cpp

#include "LOGDEF_AB.h"
#include "ABTxnEnquiry.h"

char * ABTxnEnquiry::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

	m_iTermType = pMlog->data.bt.txnenq.termtypeb;
	m_iTranNo = pMlog->data.bt.txnenq.tranwu;
	m_iLen =  pMlog->data.bt.txnenq.lenwu;


	AddField( m_iTermType, 0 );
	AddField( m_iTranNo, 0 );
	AddField( m_iLen, 0 );

	return buf;
}
