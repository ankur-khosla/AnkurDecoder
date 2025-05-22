// ABPoolRefund.cpp: implementation of the ABPoolRefund class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABPoolRefund.h"
#include "LOGDEF_AB.h"
#include "LOGRDCDEF.H"
#include "stdlib.h";

char * ABPoolRefund::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	//char error[1];
	//itoa(2,error,10);

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	if ( pMlog->data.rdc.funcodewu != WCMSG_CODE_POLRFD )
		return (char*)(&NO_STORAGE_DEFINED);

	char m_sMeetDate[30];
	const char m_sMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	WCHeader("ABPoolStartPay", pMlog, pMsg);

	/***************** Start to decode *******************/
	long m_iRace			= pMlog->data.rdc.i.r.racewu;
	int  m_iMeetingLoc		= pMlog->data.rdc.i.r.locbu;
	short m_iPoolCode		= pMlog->data.rdc.i.r.poolw;
	struct tm *meet_t		= _localtime32( &pMlog->data.rdc.i.r.mdate );
	sprintf(m_sMeetDate, "%02d-%s-%d %02d:%02d:%02d", meet_t->tm_mday, m_sMonths[meet_t->tm_mon], meet_t->tm_year+1900, meet_t->tm_hour, meet_t->tm_min, meet_t->tm_sec);

	AddField(STORE_TYPE_STRING, m_sMeetDate, 0);
	AddField( m_iMeetingLoc, 0);
	AddField( m_iRace, 0 );
	GetWCBetType(m_iPoolCode, m_sBetType);
	AddField( STORE_TYPE_STRING, m_sBetType, 0);

	return buf;
}
