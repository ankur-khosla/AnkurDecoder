// CTBSystem.cpp: implementation of the ABSystem class.
//
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ABMsgDef.h"
#include "ABLogger.h"
#include "ABSystem.h"
//#include "Terminal.h"
#include "AllABMsg.h"
#include "ExtractMgr.h"
//#include "ABTextDB.h"
#include "LOGDEF.h"
#include "LOGDEF_AB.h"
#include "LOGRDCDEF.H"
#include "BDGWCMSGDEF.H"

#define TERM_POOL_SIZE 4096

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


ABSystem::ABSystem()
{
	m_pTBAccount	= new TBAccount;//[TERM_POOL_SIZE];

}

ABSystem::~ABSystem()
{
	delete [] m_pTBAccount;
}

char * ABSystem::DecMsg(const Msg *pMsg)
{
	ABMsgTranslator *pMsgTranslator=NULL;
	bool wcMsg = false;
	int wcMsgType = 0;
	bool sbcMsg = false;
	int sbcMsgType = 0;

	// long	lMsgType	= 	pMsg->BtoL((const unsigned char*)&pMsg->m_cpBuf[ABMsgTranslator::m_iMsgCodeOffset], ABMsgTranslator::m_iMsgCodeLen, 0, 0);
	long lMsgType = pMsg->m_iMsgCode;
	long lWcMsgType;
	long lSbcMsgType;

	switch (lMsgType)
	{
	//case LOGAB_CODE_DEVREPL:
	//	pMsgTranslator=new ABCitReplace();
	//	break;

	//case LOGAB_CODE_ACA:
	//case LOGAB_CODE_ACCT_BAL:	// Q406
	//	pMsgTranslator=new ABAcctAccess();
	//	break;
		
	case LOGAB_CODE_RAC:
		pMsgTranslator=new ABRace();
		break;

	case LOGAB_CODE_CAN:
	case LOGAB_CODE_DEPCAN:		// L6.1r1m
	case LOGAB_CODE_REVDEPCAN:  // L6.1r1m
		pMsgTranslator=new ABCancel();
		break;

	case LOGAB_CODE_DEP:
	case LOGAB_CODE_DEP_EFT_EMV:
	case LOGAB_CODE_REVDEP:		// L6.1r1m
		//pMsgTranslator=new ABDeposit();
		break;

	case LOGAB_CODE_WTW:
	case LOGAB_CODE_WTW_EFT_EMV: 
		//pMsgTranslator=new ABWithDraw();
		break;

	case LOGAB_CODE_ACCOPN:
		//pMsgTranslator=new ABAcctOpen();
		break;

	case LOGAB_CODE_ACCOPN_NBA:    //Q210
		//pMsgTranslator=new ABAcctOpenNew();
		break;

	case LOGAB_CODE_ACCUPD:
		//pMsgTranslator=new ABAcctDetail();
		break;

	case LOGAB_CODE_ACCUPD_ERT:		//Q210
		//pMsgTranslator=new ABAcctDetailNew();
		break;

	case LOGAB_CODE_CSCISSUE:		// CSC Card Issue (2011IBT)
		//pMsgTranslator=new ABCscIssue();
		break;

	case LOGAB_CODE_SB:
	{
		//pMsgTranslator=new ABSBBet();
		break;
	}
	case LOGAB_CODE_DEVISSUE:
		//pMsgTranslator=new ABCitIssue();
		break;

	case LOGAB_CODE_DEVCAN:
		//pMsgTranslator=new ABCitCancel();
		break;

	case LOGAB_CODE_ACR:
		//pMsgTranslator=new ABAcctRelease();
		break;

	case LOGAB_CODE_ACCCLS:
		//pMsgTranslator=new ABAcctClose();
		break;

	case LOGAB_CODE_SYSCLS:
		//pMsgTranslator=new ABSystemClose();
		break;

	case LOGAB_CODE_DEBIT:
	case LOGAB_CODE_CREDIT:
		//pMsgTranslator=new ABDrCrAdjust();
		break;

	case LOGAB_CODE_LOT:
		//pMsgTranslator=new ABLottery();
		break;

	case LOGAB_CODE_POL_BG:
		//pMsgTranslator=new ABPolBg();
		break;

	case LOGAB_CODE_POL_LOT:
		//pMsgTranslator=new ABPolLotterySI();
		break;

	case LOGAB_CODE_POL_WTW:
		//pMsgTranslator=new ABPolWtwSI();
		break;

	case LOGAB_CODE_SGN:
		//pMsgTranslator=new ABSignOn();
		break;

	case LOGAB_CODE_SGF:
		//pMsgTranslator=new ABSignOff();
		break;

	case LOGAB_CODE_CALTRF:
		//pMsgTranslator=new ABCallTransfer();
		break;
/*	L6.1r1m
	case LOGAB_CODE_REVDEP:
		pMsgTranslator=new ABRevDeposit();
		break;
*/
	case LOGAB_CODE_RCL:
		//pMsgTranslator=new ABRecall();
		break;

	case LOGAB_CODE_BAL:
		//pMsgTranslator=new ABEftAcctBal();
		break;

	case LOGAB_CODE_CV_EFT:
	case LOGAB_CODE_CV_EFT_EMV:
		//pMsgTranslator=new ABEftCvIssue();
		break;
	
	case LOGAB_CODE_EFT_MISC:
	case LOGAB_CODE_EFT_EMV_MISC:
		//pMsgTranslator=new ABEftMisc();
		break;

	case LOGAB_CODE_CARD_ISSUE:
		//pMsgTranslator=new ABIssueCard();
		break;

	case LOGAB_CODE_CARD_RET:
		//pMsgTranslator=new ABReturnCard();
		break;
/*	L6.1r1m
	case LOGAB_CODE_REVDEPCAN:
		pMsgTranslator=new ABRevCanDep();
		break;
*/
	case LOGAB_CODE_STMCHARGE:
		//pMsgTranslator=new ABStatCharge();
		break;

	case LOGAB_CODE_TXNENQ:
		//pMsgTranslator=new ABTxnEnquiry();
		break;

	case LOGAB_CODE_BATDEP:
		//pMsgTranslator=new ABBatchDep();
		break;

	case LOGAB_CODE_EOD_CR:
		//pMsgTranslator=new ABEodCrAdj();
		break;
// begin added for Q206
	case LOGAB_CODE_EOD_LOT:
		//pMsgTranslator=new ABEodLotDiv();
		break;

	case LOGAB_CODE_EOD_RAC2:
		//pMsgTranslator=new ABEodRaceDiv();
		break;

	case LOGAB_CODE_EOD_SB:
		//pMsgTranslator=new ABEodSBDiv();
		break;
// end Q206
	case LOGAB_CODE_EOD_DFT:
		//pMsgTranslator=new ABEodDivFor();
		break;
/*
	case LOGAB_CODE_EOD_DIVOS:
		pMsgTranslator=new ABEodEscTran();
		break;
*/
	case LOGAB_CODE_EOD_CANSI:
		//pMsgTranslator=new ABEodCanLotSI();
		break;

	case LOGAB_CODE_POL_DEBIT:
		//pMsgTranslator=new ABPolDrCrAdj();
		break;

	case LOGAB_CODE_POL_CREDIT:
		//pMsgTranslator=new ABPolDrCrAdj();
		break;

	case LOGAB_CODE_POL_PRGDEPRFD:
	case LOGAB_CODE_POL_DEPRFD:
	case LOGAB_CODE_POL_ANLFEEDED:
	case LOGAB_CODE_POL_ANLFEERFD:
	case LOGAB_CODE_POL_DEPDED:
	case LOGAB_CODE_POL_ESCDEPDED:
	case LOGAB_CODE_POL_ESCDEPRFD:
	case LOGAB_CODE_POL_DEPFFT:
	case LOGAB_CODE_POL_ESCDEPFFT:
		//pMsgTranslator=new ABPolLoyalty();
		break;
	
	case LOGAB_CODE_WC:
		struct LOGAB *pMlog;
		pMlog = (struct LOGAB *)pMsg->m_cpBuf;
		wcMsg = true;
		wcMsgType = pMlog->data.rdc.funcodewu;

		switch ( wcMsgType )
		{ 
			case WCMSG_CODE_POLRAD:
				//pMsgTranslator = new ABPoolStartPay();
				wcMsgType = 511;
				break;
			case WCMSG_CODE_POLRFD:
				//pMsgTranslator = new ABPoolRefund();
				wcMsgType = 512;
				break; 
			case WCMSG_CODE_MTGABN:
				//pMsgTranslator= new ABMeetingAbandon();
				wcMsgType = 513;
				break;			
			default:
				pMsgTranslator=new ABMsgTranslator();
				wcMsg = false;
				break;
		}
		break;
	case LOGAB_CODE_SBC:
		//pMsgTranslator=new ABSbcPoolDef();
		break;

	case LOGAB_CODE_TERM_BET:
		//pMsgTranslator=new ABTerminateBet();
		break;

	case LOGAB_CODE_SMSCHG:
	case LOGAB_CODE_SMSCHGRFD:
		//pMsgTranslator=new ABSbcPoolDef();
		break;

	case LOGAB_CODE_EFT_ACT:
		//pMsgTranslator=new ABEftAccAct();
		break;

	case LOGAB_CODE_EFT_ERT:
	case LOGAB_CODE_EFT_EMV_ERT:
		//pMsgTranslator=new ABEftErt();
		break;

	case LOGAB_CODE_CSCBAL:  //CSC Card Balance (201108PSR)
		//pMsgTranslator=new ABCscBalance();
		break;

	case LOGAB_CODE_CSCRPL:  //CSC Card Replace (2011IBT)
		//pMsgTranslator=new ABCscReplace();
		break;

	case LOGAB_CODE_CSCRET:  //CSC Card Return (2011IBT)
		//pMsgTranslator=new ABCscReturn();
		break;

	default:
		pMsgTranslator=new ABMsgTranslator();
		break;
	}

	pMsgTranslator->SetStorage(m_pStorage);
	pMsgTranslator->SetMsgKey(m_lLoggerTapeId, m_iLoggerMsgOrderNo);
	if ( lMsgType != 202 && lMsgType != 201  )
	{
		pMsgTranslator->SetTBAccount((TBAccount*)m_pTBAccount);		
		// Get Customer Session
		pMsgTranslator->m_iCustSession = GetCallSeq(lMsgType, pMsg);
		// Get terminal type
		pMsgTranslator->m_iTerminalType = GetTerminalType(pMsg, m_iTerminalType);
	}

	//int iRetVal=0;
	char *buf = NULL;
	if ( lMsgType == LOGAB_CODE_WC )
		buf = pMsgTranslator->Translate( LOGAB_CODE_WC, wcMsgType, pMsg);		
	else
		buf = pMsgTranslator->Translate(lMsgType, pMsg);

	char bufMsg[MSG_SIZE] = { 0 };
	strcpy_s(bufMsg, buf); // strcpy not working in release mode.

	//m_iLoggerMsgOrderNo++;

	delete pMsgTranslator;
	pMsgTranslator = NULL;

	return bufMsg;
}


int ABSystem::GetTerminalType(const Msg *pMsg, short m_iTerminalType)
{
	struct LOGAB *pMlog;
	pMlog					= (struct LOGAB *)pMsg->m_cpBuf;
	if (pMlog->hdr.source.srcTypebu != LOGAB_SRC_CB_BT )
	{
		return(0);
	}
	else
	{
		if (pMlog->hdr.codewu == LOGAB_CODE_ACA) // account access
		{
			TerminalType[pMlog->hdr.source.data.cbBt.centrelu][pMlog->hdr.source.data.cbBt.windowwu] = pMlog->data.bt.aca.dev.cb.svt1; // input Opt mode
		}

		m_iTerminalType = TerminalType[pMlog->hdr.source.data.cbBt.centrelu][pMlog->hdr.source.data.cbBt.windowwu]; // get opt mode from sign on
		if (m_iTerminalType == 0) // OPT
		{
			m_iTerminalType = m_iTerminalType;
		}
		else if (m_iTerminalType == 1) // SVT
		{
			m_iTerminalType = m_iTerminalType;
		}
		else //others
		{
			m_iTerminalType = 2;
		}
		return(m_iTerminalType);
	}
}

int ABSystem::GetCallSeq(long lMsgType, const Msg *pMsg)
{
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	int seqNo = 0;

	if (pMsg->m_iMsgErrwu == 0 && pMlog->hdr.codewu == LOGAB_CODE_ACA)
		m_pTBAccount->AsCallSeq(pMlog->hdr.acclu);
	
	if ( pMlog->hdr.acclu < 100000000 )
		return 	m_pTBAccount->GetCallSeq(pMlog->hdr.acclu);
	else
		return 0;
}

