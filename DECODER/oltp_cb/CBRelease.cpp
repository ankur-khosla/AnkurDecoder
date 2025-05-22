/////////////////////////////////////////////////////////////////////
//
// CBRelease.cpp: implementation of the CBRelease class.
//
/////////////////////////////////////////////////////////////////////

#include <memory.h>
#include "LOGDEF.h"
#include "CBRelease.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBRelease::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	/*
	if((iRetVal=TranslateHeader(pMsg))!=NO_TRANSLATE_ERR)
	{
		return iRetVal;
	}
	*/

	struct LOG *pMlog;
	pMlog						= (struct LOG *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	m_iLocationId		= pMlog->d.bt.rel.loclu;
	m_iWinNo			= pMlog->d.bt.rel.wdwwu;
	m_iPhyTermNo		= pMlog->d.bt.rel.trmidlu;
	char m_sPhyTermNo[5];
	pidToAsc(m_iPhyTermNo, m_sPhyTermNo);
//	sprintf(m_sPhyTermNo, "%04X", m_iPhyTermNo);
	m_iRelLtn			= pMlog->d.bt.rel.reltrmlu;
	m_iStaffNo			= pMlog->d.bt.rel.stafflu;

	m_iRaceSale			= pMlog->d.bt.rel.cash.raclu;			// total racing sale (gross)
	m_iCVSale			= pMlog->d.bt.rel.cash.cvlu;			// total cash voucher sale (gross)
	m_iLottSale			= pMlog->d.bt.rel.cash.lotlu;			// total lottery sale (gross)
	m_iTBSale			= pMlog->d.bt.rel.cash.tbdlu;			// total tb deposit (gross)
	m_iCancelR			= pMlog->d.bt.rel.cash.canraclu;		// total cancelled racing ticket
	m_iCancelCV			= pMlog->d.bt.rel.cash.cancvlu;			// total cancelled cash voucher sale
	m_iCancelLot		= pMlog->d.bt.rel.cash.canlotlu;		// total cancelled lottery sale
	m_iCancelTB			= pMlog->d.bt.rel.cash.cantbdlu;		// total cancelled tb deposit
	m_iPayout			= pMlog->d.bt.rel.cash.payd;			// total payout
	sprintf(m_sPayout, "%d", m_iPayout);
	m_iPayDep			= pMlog->d.bt.rel.cash.paydeplu;		// payout deposit
	m_iEscDep			= pMlog->d.bt.rel.cash.esccdeplu;		// esc cash deposit
	m_iEscWith			= pMlog->d.bt.rel.cash.esccwtwlu;		// esc cash withdrawal

	AddField(m_iLocationId, 0);
	AddField(m_iWinNo, 0);
	AddField(STORE_TYPE_STRING, m_sPhyTermNo, 0);
	AddField(m_iRelLtn, 0);

	AddField(m_iRaceSale, 0);
	AddField(m_iCVSale, 0);
	AddField(m_iLottSale, 0);
	AddField(m_iTBSale, 0);
	AddField(m_iCancelR, 0);
	AddField(m_iCancelCV, 0);
	AddField(m_iCancelLot, 0);
	AddField(m_iCancelTB, 0);
	AddField(STORE_TYPE_STRING, m_sPayout, 0);
	AddField(m_iPayDep, 0);
	AddField(m_iEscDep, 0);
	AddField(m_iEscWith, 0);
	AddField(m_iStaffNo, 0);
	return buf;
}
