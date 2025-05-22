// CBEscCash.cpp: implementation of the CBEscCash class.
//
//////////////////////////////////////////////////////////////////////

#include "CBEscCash.h"
#include "LOGDEF.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

char * CBEscCash::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	// struct LOGEFTWTW
	int m_iTotCost = pMlog->d.bt.esc.d.dep.req.amtl;		// total cost in cents

	AddField(m_iTotCost, 0);

	return buf;
}
