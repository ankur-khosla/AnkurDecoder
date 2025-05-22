// ABRaceClose.cpp: implementation of the ABRaceClose class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABMeetingAbandon.h"
#include "LOGDEF_AB.h"
#include "LOGRDCDEF.H"

char * ABMeetingAbandon::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	if ( pMlog->data.rdc.funcodewu != WCMSG_CODE_MTGABN )
		return (char*)(&NO_STORAGE_DEFINED);

	char m_sMeetDate[30];
	const char m_sMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	WCHeader("ABPoolStartPay", pMlog, pMsg);

	return buf;
}
