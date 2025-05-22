// ABTrnSpcDefine.cpp: implementation of the ABTrnSpcDefine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABSbcPoolDef.h"
#include "LOGDEF_AB.h"
#include "SimpleSbcDef.H"
#include "PoolType.h"

char * ABSbcPoolDef::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;

	int m_iSbcMsgCode = pMlog->data.sbc.h.codewu;

	if ( m_iSbcMsgCode != 109 && m_iSbcMsgCode != 108  ) // m_iSbcMsgCode != 147 && )
		return (char*)(&NO_STORAGE_DEFINED);
	
	const char m_sMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	WCHeader("CBSbcPoolDef", pMlog, pMsg);

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
		m_iPoolType		= pMlog->data.sbc.d.tinp.id.ptypebu;
		m_iFoPmFlag		= pMlog->data.sbc.d.tinp.id.pmbu;
		m_iPrimId		= pMlog->data.sbc.d.tinp.id.pidbu;
		m_iSubId		= pMlog->data.sbc.d.tinp.id.subidbu;

		struct tm *tourn_t		= _localtime32( &pMlog->data.sbc.d.tinp.tDate );
		sprintf(m_sTournamentDate, "%02d-%s-%d %02d:%02d:%02d", tourn_t->tm_mday, m_sMonths[tourn_t->tm_mon], tourn_t->tm_year+1900, tourn_t->tm_hour, tourn_t->tm_min, tourn_t->tm_sec);


		if ( m_iPoolType == SB_POOL_SPC_MATCH || m_iPoolType == SB_POOL_SPC_TRN  )
		{
			m_iItemNo		= pMlog->data.sbc.d.tinp.id.itembu;
			m_iIndex		= pMlog->data.sbc.d.tinp.id.idxwu;
		}

	}
	else
	{
		m_iPoolType		= pMlog->data.sbc.d.poolNew.poolType;
		m_iPrimId		= pMlog->data.sbc.d.poolNew.matchId;
	}

	GetFbBetType( m_iPoolType, m_cPoolType );

	AddField( m_iPoolType, 0 );
	AddField( STORE_TYPE_STRING, m_cPoolType, 0);
	AddField(STORE_TYPE_STRING, m_sTournamentDate, 0);
	AddField( m_iFoPmFlag, 0 );
	AddField( m_iPrimId, 0 );
	AddField( m_iSubId, 0 );
	AddField( m_iItemNo, 0 );
	AddField( m_iIndex, 0 );

	return buf;
}

