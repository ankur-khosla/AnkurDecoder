// CBPoolStartPay.cpp: implementation of the CCBPoolStartPay class.
//
//////////////////////////////////////////////////////////////////////

#include "CBPoolStartPay.h"
#include "LOGDEF.h"
#include "LOGRDCDEF.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBPoolStartPay::CBPoolStartPay()
{

}

CBPoolStartPay::~CBPoolStartPay()
{

}


char * CBPoolStartPay::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;
	
	if ( pMlog->d.rdc.funcodewu != 317 )
		return (char*)(&NOT_IMPLEMENTED);

	char m_sMeetDate[30];
	const char m_sMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	WCHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/
	long m_iRace			= pMlog->d.rdc.i.r.racewu;
	int  m_iMeetingLoc		= pMlog->d.rdc.i.r.locbu;
	char m_iPoolCode		= pMlog->d.rdc.i.r.poolw;
	__time32_t mdate = pMlog->d.rdc.i.r.mdate;
	struct tm *meet_t		= _localtime32( &mdate);
	sprintf(m_sMeetDate, "%02d-%s-%d %02d:%02d:%02d", meet_t->tm_mday, m_sMonths[meet_t->tm_mon], meet_t->tm_year+1900, meet_t->tm_hour, meet_t->tm_min, meet_t->tm_sec);


	int	 m_iNoOfResult		= pMlog->d.rdc.d.rad.nowu;
	char m_iSubstitude		= pMlog->d.rdc.d.rad.sflgbu;
	char m_iOverflow		= pMlog->d.rdc.d.rad.ovfl1;
	char m_iClaim			= pMlog->d.rdc.d.rad.clm1;
	char m_iUnofficial		= pMlog->d.rdc.d.rad.unoff1;
	char m_sBetType[20] = {0};


	AddField(STORE_TYPE_STRING, m_sMeetDate, 0);
	AddField( m_iMeetingLoc, 0);
	AddField( m_iRace, 0 );
	GetBetType(m_iPoolCode, m_sBetType);
	AddField( STORE_TYPE_STRING, m_sBetType, 0);
	AddField( m_iNoOfResult, 0 );
	AddField( m_iSubstitude, 0 );
	AddField( m_iOverflow, 0 );
	AddField( m_iClaim, 0 );
	AddField( m_iUnofficial, 0 );
	return buf;
}

char* CBPoolStartPay::GetBetType(char BetType, char Type[20])
{
	// wc bet type is different from the one defined in betdef.h

	switch (BetType)
	{	
		case 0:
			sprintf(Type, "WIN");
			break;
		
		case 1:
			sprintf(Type, "PLA");
			break;

		case 2:
			sprintf(Type, "QIN");
			break;

		case 3:
			sprintf(Type, "QPL");
			break;

		case 4:
			sprintf(Type, "TRI");
			break;

		case 5:
			sprintf(Type, "TCE");
			break;

		case 6:
			sprintf(Type, "QTT");
			break;

		case 7:
			sprintf(Type, "DBL");
			break;

		case 8:
			sprintf(Type, "D-Q");
			break;

		case 9:
			sprintf(Type, "TBL");
			break;

		case 10:
			sprintf(Type, "T-T");
			break;

		case 11:
			sprintf(Type, "6UP");
			break;

		case 12:
			sprintf(Type, "D-T");
			break;

		case 13:
			sprintf(Type, "F-F");
			break;

		case 14:
			sprintf(Type, "BWA");
			break;

		case 15:
			sprintf(Type, "CWA");
			break;

		case 16:
			sprintf(Type, "CWB");
			break;

		case 17:
			sprintf(Type, "CWC");
			break;

		case 18:
			sprintf(Type, "IWN");
			break;

		default:
			sprintf(Type, "XXXX");
			break;
	}

	return(Type);
}