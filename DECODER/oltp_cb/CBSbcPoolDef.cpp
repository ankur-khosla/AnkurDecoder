// CBSbcPoolDef.cpp: implementation of the CBSbcPoolDef class.
//
//////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBSbcPoolDef.h"
#include "..\oltp_ab\SimpleSbcDef.h"
#include "..\oltp_ab\PoolType.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


char * CBSbcPoolDef::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;

	int m_iSbcMsgCode = pMlog->d.sbc.h.codewu;

	if ( m_iSbcMsgCode != 147 && m_iSbcMsgCode != 109 && m_iSbcMsgCode != 108 )
		return (char*)(&NOT_IMPLEMENTED);
	
	const char m_sMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	WCHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

	long m_iPoolType		= 0;
	char m_cPoolType[10];	
	char m_sTournamentDate[30];
	char m_sSpcMatchDate[30];
	memset( m_cPoolType, 0, sizeof( m_cPoolType ) );
	memset( m_sTournamentDate, 0, sizeof( m_sTournamentDate ) );
	memset( m_sSpcMatchDate, 0, sizeof( m_sSpcMatchDate ) );

	long m_iFoPmFlag		= 0;
	long m_iPrimId			= 0;
	long m_iSubId			= 0;
	long m_iItemNo			= 0;
	long m_iIndex			= 0;

	if ( m_iSbcMsgCode == 108 || m_iSbcMsgCode == 109 )
	{
		m_iPoolType		= pMlog->d.sbc.d.tinp.id.ptypebu;
		m_iFoPmFlag		= pMlog->d.sbc.d.tinp.id.pmbu;
		m_iPrimId		= pMlog->d.sbc.d.tinp.id.pidbu;
		m_iSubId		= pMlog->d.sbc.d.tinp.id.subidbu;

		if ( m_iPoolType == SB_POOL_SPC_MATCH || m_iPoolType == SB_POOL_SPC_TRN  )
		{
			m_iItemNo		= pMlog->d.sbc.d.tinp.id.itembu;
			m_iIndex		= pMlog->d.sbc.d.tinp.id.idxwu;
		}
		struct tm *tourn_t		= _localtime32( &pMlog->d.sbc.d.tinp.tDate );
		sprintf(m_sTournamentDate, "%02d-%s-%d %02d:%02d:%02d", tourn_t->tm_mday, m_sMonths[tourn_t->tm_mon], tourn_t->tm_year+1900, tourn_t->tm_hour, tourn_t->tm_min, tourn_t->tm_sec);

	}
	else
	{
		m_iPoolType		= pMlog->d.sbc.d.poolNew.poolType;
		m_iPrimId		= pMlog->d.sbc.d.poolNew.matchId;
	}

	GetFbBetType( m_iPoolType, m_cPoolType );
	AddField( m_iPoolType, 0);
	AddField( STORE_TYPE_STRING, m_cPoolType, 0);
	AddField(STORE_TYPE_STRING, m_sTournamentDate, 0);
	AddField( m_iFoPmFlag, 0 );
	AddField( m_iPrimId, 0 );
	AddField( m_iSubId, 0 );
	AddField( m_iItemNo, 0 );
	AddField( m_iIndex, 0 );

	return buf;
}

