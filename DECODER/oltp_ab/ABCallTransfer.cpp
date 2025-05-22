// ABCallTransfer.cpp

#include "LOGDEF_AB.h"
#include "ABCallTransfer.h"

char * ABCallTransfer::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

//	m_iAcctNo = pMlog->data.at.caltrf.req.accnumlu;
	m_cAreaCode = pMlog->data.at.caltrf.req.trfareabu;

//	AddField( m_iAcctNo, 0 );
	AddField( m_cAreaCode, 0 );


	return buf;
}
