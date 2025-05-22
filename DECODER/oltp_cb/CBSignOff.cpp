// CBSignOff.cpp: implementation of the CBSignOff class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBSignOff.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBSignOff::TranslateAction(const Msg *pMsg)
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
	
	PackHeader("cb_sign_off_insert_sp", pMlog, pMsg);

//	m_iInterMsn			= pMlog->d.bt.sgf.othsys.ismsnlu;		// inter-system msn
//	m_iInterMsn = 0;
	m_cDisBcsFlag		= pMlog->d.bt.sgf.othsys.disable1;		// bcs service is disable
	memcpy(m_cStCount, pMlog->d.bt.sgf.statwu, LOGBTSGF_CNT*2);			// stats. counters

	//struct CKPCSH
	m_iRaceSale			= pMlog->d.bt.sgf.cash.raclu;			// total racing sale (gross)
	m_iCVSale			= pMlog->d.bt.sgf.cash.cvlu;			// total cash voucher sale (gross)
	m_iLottSale			= pMlog->d.bt.sgf.cash.lotlu;			// total lottery sale (gross)
	m_iTBSale			= pMlog->d.bt.sgf.cash.tbdlu;			// total tb deposit (gross)
	m_iCancelR			= pMlog->d.bt.sgf.cash.canraclu;		// total cancelled racing ticket
	m_iCancelCV			= pMlog->d.bt.sgf.cash.cancvlu;			// total cancelled cash voucher sale
	m_iCancelLot		= pMlog->d.bt.sgf.cash.canlotlu;		// total cancelled lottery sale
	m_iCancelTB			= pMlog->d.bt.sgf.cash.cantbdlu;		// total cancelled tb deposit
	m_iPayout			= pMlog->d.bt.sgf.cash.payd;			// total payout
	m_iPayDep			= pMlog->d.bt.sgf.cash.paydeplu;		// payout deposit
	m_iEscDep			= pMlog->d.bt.sgf.cash.esccdeplu;		// esc cash deposit
	m_iEscWith			= pMlog->d.bt.sgf.cash.esccwtwlu;		// esc cash withdrawal

	// struct BCS_SHROFF_BAL
	m_iTotalSale		= pMlog->d.bt.sgf.shrfbal.totsaledu;		// total sales in cents
	m_iTolPayout		= pMlog->d.bt.sgf.shrfbal.totpaydu;			// total pay-out in cents
	m_iTolCancel		= pMlog->d.bt.sgf.shrfbal.totcandu;			// total cancels in cents
	m_iNetBal			= pMlog->d.bt.sgf.shrfbal.netbald;			// net balance in cents
	m_iEscBal			= pMlog->d.bt.sgf.shrfbal.escnetd;			// esc net balance in cents
	m_iCashIn			= pMlog->d.bt.sgf.shrfbal.cashindu;			// cash in (in cents)
	m_iCashOut			= pMlog->d.bt.sgf.shrfbal.cashoutdu;		// cash out (in cents)
	m_iMSR				= pMlog->d.bt.sgf.shrfbal.msrdu;			// MSR in cents
	m_iMSP				= pMlog->d.bt.sgf.shrfbal.mspdu;			// MSP in cents

	m_cStaffSgfFlag		= pMlog->d.bt.sgf.sgf1;						// staff sign off
	
	// Output
//	AddField(m_iInterMsn, 0);
	AddField(m_cDisBcsFlag, 0);
	for (int i=0; i<(LOGBTSGF_CNT); i++)
	{
		AddField(m_cStCount[i], 0);
	}
	AddField(m_iRaceSale, 0);
	AddField(m_iCVSale, 0);
	AddField(m_iLottSale, 0);
	AddField(m_iTBSale, 0);
	AddField(m_iCancelR, 0);
	AddField(m_iCancelCV, 0);
	AddField(m_iCancelLot, 0);
	AddField(m_iCancelTB, 0);
	AddField(m_iPayout, 0);
	AddField(m_iPayDep, 0);
	AddField(m_iEscDep, 0);
	AddField(m_iEscWith, 0);
	AddField(m_iTotalSale, 0);
	AddField(m_iTolPayout, 0);
	AddField(m_iTolCancel, 0);
	AddField(m_iNetBal, 0);
	AddField(m_iEscBal, 0);
	AddField(m_iCashIn, 0);
	AddField(m_iCashOut, 0);
	AddField(m_iMSR, 0);
	AddField(m_iMSP, 0);
	AddField(m_cStaffSgfFlag, 0);

	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
