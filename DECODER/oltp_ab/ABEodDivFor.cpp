// ABEodDivFor.cpp

#include "LOGDEF_AB.h"
#include "ABEodDivFor.h"

char * ABEodDivFor::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

	m_iSize			= pMlog->data.eod.dft.h.sizewu;
	m_iTranCode		= pMlog->data.eod.dft.h.codewu;
	m_iTranNo		= pMlog->data.eod.dft.h.tranwu;
	m_iTranMerge	= pMlog->data.eod.dft.h.merge1;

	m_iForFeitAmt	= (unsigned __int64) pMlog->data.eod.dft.body.amountdu;

	AddField( m_iSize, 0 );
	AddField( m_iTranCode, 0 );
	AddField( m_iTranNo, 0 );
	AddField( m_iTranMerge, 0 );
	AddField64( m_iForFeitAmt, 0 );

	return buf;
}
