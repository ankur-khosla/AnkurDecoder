// ABCscIssue.cpp

#include "LOGDEF_AB.h"
#include "ABCscIssue.h"

char * ABCscIssue::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

	m_iCscCardId = (unsigned __int64) pMlog->data.at.csciss.req.csccardid;  //CSC Card ID
	m_iCscDepFee = pMlog->data.at.csciss.req.cscdepfee;  //CSC Deposit Fee

	/***************** Output *******************/
	AddField64( m_iCscCardId, 0 );
	AddField64( m_iCscDepFee, 0 );

	return buf;
}
