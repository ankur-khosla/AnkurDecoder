// CBrdt.cpp: implementation of the CBrdt class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBSysClose.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBSysClose::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOG *pMlog;
	pMlog						= (struct LOG *)pMsg->m_cpBuf;
	
	PackHeader("cb_system_close_sp", pMlog, pMsg);

	return buf;
}