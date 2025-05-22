// ABEodDivGen.cpp

#include "LOGDEF_AB.h"
#include "ABEodLotDiv.h"

char * ABEodLotDiv::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);
	const char m_cMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	/***************** Start to decode *******************/
	m_iSize			= pMlog->data.eod.lot.h.sizewu;
	m_iTranCode		= pMlog->data.eod.lot.h.codewu;
	m_iTranNo		= pMlog->data.eod.lot.h.tranwu;
	m_iTranMerge	= pMlog->data.eod.lot.h.merge1;


	if ( m_iTranCode == ACU_CODE_LOT )
	{
		m_iDividend			= (unsigned __int64) pMlog->data.eod.lot.body.bet.d.hdr.totdu;
		m_iBaseInvestAmt	= pMlog->data.eod.lot.body.bet.d.hdr.betinvcomb.flexi.baseinv;
		m_iTotalCost		= pMlog->data.eod.lot.body.bet.d.hdr.costlu;
		m_iSellTime			= pMlog->data.eod.lot.body.bet.d.hdr.sellTime;
		m_cBetType			= pMlog->data.eod.lot.body.bet.d.hdr.bettypebu;
	}
	else
	{
		m_iDividend			= (unsigned __int64) pMlog->data.eod.lot2.body.bet.d.hdr.totdu;
		m_iBaseInvestAmt	= pMlog->data.eod.lot2.body.bet.d.hdr.betinvcomb.flexi.baseinv;
		m_iTotalCost		= pMlog->data.eod.lot2.body.bet.d.hdr.costlu;
		m_iSellTime			= pMlog->data.eod.lot2.body.bet.d.hdr.sellTime;
		m_cBetType			= pMlog->data.eod.lot2.body.bet.d.hdr.bettypebu;
	}
	struct tm *sellTime;
	sellTime	= _localtime32( &m_iSellTime);
	int m_iYear = 1900+sellTime->tm_year;
	int m_iDay	= sellTime->tm_mday;
	char daytime[50];
	sprintf(daytime, "%d-%s-%d %02d:%02d:%02d", m_iDay, m_cMonths[sellTime->tm_mon], m_iYear,
												sellTime->tm_hour, sellTime->tm_min, sellTime->tm_sec);

	AddField( m_iSize, 0 );
	AddField( m_iTranCode, 0 );
	AddField( m_iTranNo, 0 );
	AddField( m_iTranMerge, 0 );
	AddField64( m_iDividend, 0 );
	AddField( m_iBaseInvestAmt, 0 );
	AddField( m_iTotalCost, 0 );
	AddField(STORE_TYPE_STRING, daytime, 0);
	AddField(m_cBetType, 0);

	return buf;
}
