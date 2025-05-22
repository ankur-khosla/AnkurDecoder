// ABEodDivGen.cpp

#include "LOGDEF_AB.h"
#include "ABEodSBDiv.h"

char * ABEodSBDiv::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
		
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	const char m_cMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/
	m_iSize			= pMlog->data.eod.sb.h.sizewu;
	m_iTranCode		= pMlog->data.eod.sb.h.codewu;
	m_iTranNo		= pMlog->data.eod.sb.h.tranwu;
	m_iTranMerge	= pMlog->data.eod.sb.h.merge1;

	if ( m_iTranCode == ACU_CODE_SB )
	{
		m_iDividend	= (unsigned __int64) pMlog->data.eod.sb.body.bet.hdr.totdu;
		m_iBaseInvestAmt	= pMlog->data.eod.sb.body.bet.hdr.betinvcomb.flexi.baseinv;
		m_iTotalCost		= pMlog->data.eod.sb.body.bet.hdr.costlu;
		m_iSellTime	= pMlog->data.eod.sb.body.bet.hdr.sellTime;
		m_cBetType		= pMlog->data.eod.sb.body.bet.hdr.bettypebu;
	}
	else
	{
		m_iDividend	= (unsigned __int64) pMlog->data.eod.sb2.body.bet.hdr.totdu;
		m_iBaseInvestAmt	= pMlog->data.eod.sb2.body.bet.hdr.betinvcomb.flexi.baseinv;
		m_iTotalCost		= pMlog->data.eod.sb2.body.bet.hdr.costlu;
		m_iSellTime			= pMlog->data.eod.sb2.body.bet.hdr.sellTime;
		m_cBetType			= pMlog->data.eod.sb2.body.bet.hdr.bettypebu;
	}

	sellTime	= _localtime32( &m_iSellTime);
	m_iYear = 1900+sellTime->tm_year;
	m_iDay	= sellTime->tm_mday;
	daytime[50];
	sprintf(daytime, "%d-%s-%d %02d:%02d:%02d", m_iDay, m_cMonths[sellTime->tm_mon], m_iYear,
												sellTime->tm_hour, sellTime->tm_min, sellTime->tm_sec);

	if ( m_iLoggerMsgOrderNo == 33 )
	{
		int a = 0;
		a = 1;
	}

	AddField( m_iSize, 0 );
	AddField( m_iTranCode, 0 );
	AddField( m_iTranNo, 0 );
	AddField( m_iTranMerge, 0 );
	AddField64( m_iDividend, 0 );
	AddField( m_iBaseInvestAmt, 0 );
	AddField( m_iTotalCost, 0 );
	AddField(STORE_TYPE_STRING, daytime, 0);
	AddField( m_cBetType, 0);

	return buf;
}

