// ABEodCanLotSI.cpp

#include "LOGDEF_AB.h"
#include "ABEodCanLotSI.h"

char * ABEodCanLotSI::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

	int m_iNoOfBanker = 0;
	int m_iNoOfOthers = 0;

	m_iSize = pMlog->data.eod.lot.h.sizewu;
	m_iTranCode = pMlog->data.eod.lot.h.codewu;
	m_iTranNo = pMlog->data.eod.lot.h.tranwu;
	m_iTranMerge = pMlog->data.eod.lot.h.merge1;

	if ( m_iTranCode == ACU_CODE_LOT )
	{
		m_iSrcSell = pMlog->data.eod.lot.body.bet.srcbu;
		m_iDrawYear = pMlog->data.eod.lot.body.bet.d.var.lot.yearwu;
		m_iDrawNo = pMlog->data.eod.lot.body.bet.d.var.lot.drawwu;
		m_iLotType = pMlog->data.eod.lot.body.bet.d.var.lot.typewu;
		m_iLUnitBet = pMlog->data.eod.lot.body.bet.d.hdr.betinvcomb.flexi.baseinv;
		m_iLTtlCost = pMlog->data.eod.lot.body.bet.d.hdr.costlu;
		m_iNoOfBanker = pMlog->data.eod.lot.body.bet.d.var.lot.n.sel.single.nbnkbu;
		m_iNoOfOthers = pMlog->data.eod.lot.body.bet.d.var.lot.n.sel.single.nothbu;
	}
	else
	{
		m_iSrcSell = pMlog->data.eod.lot2.body.bet.srcbu;
		m_iDrawYear = pMlog->data.eod.lot2.body.bet.d.var.lot.yearwu;
		m_iDrawNo = pMlog->data.eod.lot2.body.bet.d.var.lot.drawwu;
		m_iLotType = pMlog->data.eod.lot2.body.bet.d.var.lot.typewu;
		m_iLUnitBet = pMlog->data.eod.lot2.body.bet.d.hdr.betinvcomb.flexi.baseinv;
		m_iLTtlCost = pMlog->data.eod.lot2.body.bet.d.hdr.costlu;
		m_iNoOfBanker = pMlog->data.eod.lot2.body.bet.d.var.lot.n.sel.single.nbnkbu;
		m_iNoOfOthers = pMlog->data.eod.lot2.body.bet.d.var.lot.n.sel.single.nothbu;
	}

	m_iDrawYear		= m_iDrawYear + 1900;
	if (m_iDrawYear < pMsg->m_iMsgYear)
		m_iDrawYear = m_iDrawYear + 100;

	AddField( m_iSize, 0 );
	AddField( m_iTranCode, 0 );
	AddField( m_iTranNo, 0 );
	AddField( m_iTranMerge, 0 );

	AddField( m_iSrcSell, 0 );
	AddField( m_iDrawYear, 0 );
	AddField( m_iDrawNo, 0 );
	AddField( m_iLotType, 0 );

	AddField( m_iLUnitBet, 0 );
	AddField( m_iLTtlCost, 0 );

	AddField( m_iNoOfBanker, 0 );
	AddField( m_iNoOfOthers, 0 );

	return buf;
}
