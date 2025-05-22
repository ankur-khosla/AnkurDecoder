// ABPolLotterySI.cpp

#include "LOGDEF_AB.h"
#include "ABPolLotterySI.h"

char * ABPolLotterySI::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	const char m_cMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	/***************** Start to decode *******************/

	m_iSiEntryNo = pMlog->data.pol.lot.siEntrylu;
	m_cLotType = pMlog->data.pol.lot.lotTypebu;

	struct tm *draw_d;
	draw_d	= _localtime32( &pMlog->data.pol.lot.drawdate );
	sprintf(m_sDrawDate, "%d-%s-%d", draw_d->tm_mday, m_cMonths[draw_d->tm_mon], 1900+draw_d->tm_year);

	m_iSiEntryNo = pMlog->data.pol.lot.siEntrylu;
	m_cLotType = pMlog->data.pol.lot.lotTypebu;

	AddField( m_iSiEntryNo, 0 );
	AddField( m_cLotType, 0 );
	AddField( STORE_TYPE_STRING, m_sDrawDate, 0 );

	m_iDrawYear = pMlog->data.pol.lot.lot.tran.bet.d.var.lot.yearwu;
	m_iDrawNo = pMlog->data.pol.lot.lot.tran.bet.d.var.lot.drawwu;
	
	m_iDrawYear		= m_iDrawYear + 1900;
	if (m_iDrawYear < pMsg->m_iMsgYear)
		m_iDrawYear = m_iDrawYear + 100;

	AddField( m_iDrawYear, 0 );
	AddField( m_iDrawNo, 0 );

	m_iUnitCost = pMlog->data.pol.lot.lot.tran.bet.d.hdr.betinvcomb.flexi.baseinv;
	m_iTotalCost = pMlog->data.pol.lot.lot.tran.bet.d.hdr.costlu;
	m_iLotBetType = pMlog->data.pol.lot.lot.tran.bet.d.hdr.bettypebu;

	AddField( m_iUnitCost, 0 );
	AddField( m_iTotalCost, 0 );
	AddField( m_iLotBetType, 0 );

	m_iNoOfBanker	= pMlog->data.pol.lot.lot.tran.bet.d.var.lot.n.sel.single.nbnkbu;	// no of bankers
	m_iNoOfOthers	= pMlog->data.pol.lot.lot.tran.bet.d.var.lot.n.sel.single.nothbu;	// no of others

	AddField(m_iNoOfBanker, 0);
	AddField(m_iNoOfOthers, 0);

	m_cPartialUnitBet		= pMlog->data.pol.lot.lot.tran.bet.d.var.lot.n.pub1;      // Q310 Partial unit bet

	AddField(m_cPartialUnitBet, 0);					//Q310


	return buf;
}

