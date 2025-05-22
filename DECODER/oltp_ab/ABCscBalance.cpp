// ABCscBalance.cpp

#include "LOGDEF_AB.h"
#include "ABCscBalance.h"

char * ABCscBalance::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

	m_iDailyExp = pMlog->data.bt.cscbal.amt;  //Daily expenditure
	m_iTtlDiv = pMlog->data.bt.cscbal.div;  //Total dividend

	/***************** Output *******************/
	AddField64( m_iDailyExp, 0 );
	AddField64( m_iTtlDiv, 0 );

	return buf;
}
