// ABPolBg.cpp

#include "LOGDEF_AB.h"
#include "ABPolBg.h"

char * ABPolBg::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

	m_iOBGAmt = pMlog->data.pol.bg.newBg.bankgd;
	m_cOBGType = pMlog->data.pol.bg.newBg.bgTypebu;
	m_iNBGAmt = pMlog->data.pol.bg.oldBg.bankgd;
	m_cNBGType = pMlog->data.pol.bg.oldBg.bgTypebu;

	AddField64( m_iOBGAmt, 0 );
	AddField( m_cOBGType, 0 );
	AddField64( m_iNBGAmt, 0 );
	AddField( m_cNBGType, 0 );

	return buf;
}
