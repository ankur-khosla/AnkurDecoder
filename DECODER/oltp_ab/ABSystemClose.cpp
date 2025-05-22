// ABSystemClose.cpp

#include "LOGDEF_AB.h"
#include "ABSystemClose.h"

char * ABSystemClose::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

	m_iClsEnq = pMlog->data.oth.syscls.clsenq1;

	AddField( m_iClsEnq, 0 );


	return buf;
}
