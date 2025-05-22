// ABSignOn.cpp

#include "LOGDEF_AB.h"
#include "ABSignOn.h"

char * ABSignOn::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	return buf;
}
