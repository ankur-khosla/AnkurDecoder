/////////////////////////////////////////////////////////////////////
// CBCVCash.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBCVCash.h"

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBCVCash::TranslateAction(const Msg *pMsg)
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

	m_iMethod			= pMlog->d.bt.ccp.methodwu;			// method

	union TSN tsn = pMlog->d.bt.ccp.tsn;

	m_cNewTsnFlag = tsnVersionwu(&tsn);		// new tsn flag; sp3: function--tsnVersionwu	pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19n.w4.tsnver2;
	m_iHighRecNo = tsnBetTypebu(tsn); // bet type
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no
	m_iTsnBetType = tsnBetTypebu(tsn);		// bet type

	if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.ccp.d.bet.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.ccp.d.bet.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.ccp.d.bet.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.bt.ccp.d.bet.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iHighRecNo = tsnBetTypebu(tsn); // bet type

		m_iLocation = 0; // No location and meeting concept. set it to 0. 2017.1.6 paul ou
		m_iMeetingDayOfYear = 0; //No location and meeting concept. set it to 0. 2017.1.6 paul ou

		m_iLowRecNo				= tsn19NTicketIDdu(tsn);		// low order bits of record no
	}

	m_iCancelSysNo		= pMlog->d.bt.ccp.d.bet.sysw;				// system no [-1 local], this is used for internal index
	//if (m_iCancelSysNo == -1)
	m_iCancelSysNo = pMsg->m_iSysNo;
	sprintf(m_sCancelSysNo, "%d", m_iCancelSysNo);
	m_iCrossSysChanNo	= 0; //pMlog->d.bt.ccp.d.bet.chanwu;				// cross system channel no
	m_iCrossSysMsn		= 0; // pMlog->d.bt.ccp.d.bet.msnwu;				// cross system msn
	m_iFileNo			= 0;// pMlog->d.bt.ccp.d.bet.filew;				// file no
	m_iBfcIndex			= 0; //pMlog->d.bt.ccp.d.bet.sbfcidxw;			// bfc index for shrink bet file
	m_iMeetingDrawIndex = 0; // pMlog->d.bt.ccp.d.bet.midxw;				// meeting/draw index for cancel

	m_iUnitBet			= 0; // pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet // q308 changes

	if (m_iSaleSysNo == pMsg->m_iSysNo)
	{
		m_iTotalCost = pMsg->cvRel.costlu; // pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.totdu;		// total cost

		m_iSellCentre = pMsg->cvRel.sellCentrelu;//pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellCentrelu;	// sell centre
		m_iSellWindow = pMsg->cvRel.sellWindowu;//pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellWindowu;	// sell window

		// <Marco Lui, 20050120>
		m_iOriginalEftAmount = pMsg->cvRel.originallu;//pMlog->d.bt.ccp.d.bet.bet.newbet.h.prveft.eft.originallu;
		m_iRemainingEftAmount = pMsg->cvRel.remainlu;//pMlog->d.bt.ccp.d.bet.bet.newbet.h.prveft.eft.remainlu;
		// </Marco Lui, 20050120>

		__time32_t sellTime = pMsg->cvRel.sellTime; //pMsg->m_iMsgSellTime;  
		tm_SellTime = _localtime32(&sellTime);	// sell time
		char	m_sMonths[13][4] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		if (sellTime < 0)//pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime
		{
			sprintf(m_sSellTime, "01-01-1900");
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon + 1], tm_SellTime->tm_year + 1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
		}


		m_iCVSell = pMsg->cvRel.selllogseqlu;//pMlog->d.bt.ccp.d.bet.bet.newbet.h.ptr.cv.selllogseqlu;	// log seq at selling
		m_iCVPay = pMsg->cvRel.paylogseqlu;//pMlog->d.bt.ccp.d.bet.bet.newbet.h.ptr.cv.paylogseqlu;	// log seq at payout
	}
	else //cross system
	{
		m_iTotalCost = pMlog->d.bt.ccp.d.bet.payoutdu;		// total cost

		m_iSellCentre = pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellCentrelu;	// sell centre
		m_iSellWindow = pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellWindowu;	// sell window

		// <Marco Lui, 20050120>
		m_iOriginalEftAmount = pMlog->d.bt.ccp.d.bet.bet.newbet.h.prveft.eft.originallu;
		m_iRemainingEftAmount = pMlog->d.bt.ccp.d.bet.bet.newbet.h.prveft.eft.remainlu;
		// </Marco Lui, 20050120>

		__time32_t sellTime = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime; //pMsg->m_iMsgSellTime; 
		tm_SellTime = _localtime32(&sellTime);	// sell time
		char	m_sMonths[13][4] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

		if (sellTime < 0)//pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime
		{
			sprintf(m_sSellTime, "01-01-1900");
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon + 1], tm_SellTime->tm_year + 1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
		}


		m_iCVSell = pMlog->d.bt.ccp.d.bet.bet.newbet.h.ptr.cv.selllogseqlu;	// log seq at selling
		m_iCVPay = pMlog->d.bt.ccp.d.bet.bet.newbet.h.ptr.cv.paylogseqlu;	// log seq at payout
	}
	

	//m_iMeetingDayOfYear = 0; // just for test. 2016.12.30

	// Output
	AddField(m_iMethod, 0);
	AddField(m_iHighRecNo, 0);
	AddField64(m_iLowRecNo, 0);
	AddField(m_iLocation, 0);
	AddField(m_iTsnBetType, 0);
	AddField(m_iSaleSysNo, 0);
	// oltp output new_tsn_flag=0,tsn_bet_type=8, BIS and EDW is using this logic.
	// in PMU1 version, EDABI converts new_tsn_flag=1 to new_tsn_flag=0 during output.
	// if the new_tsn_flag has any update in future, BIS and EDW shoud be aligned with it,
	// downstream should exclude this logic in the next release. ---changed on 11/02/2017
	if (m_cNewTsnFlag == 1)
		AddField(0, 0);
	else
		AddField(m_cNewTsnFlag, 0);
	AddField(m_iMeetingDayOfYear, 0);
	AddField(STORE_TYPE_STRING, m_sCancelSysNo, 0);
	AddField(m_iCrossSysChanNo, 0);
	AddField(m_iCrossSysMsn, 0);
	AddField(m_iFileNo, 0);
	AddField(m_iBfcIndex, 0);
	AddField(m_iMeetingDrawIndex, 0);
	AddField(m_iUnitBet, 0);
	AddField(m_iTotalCost, 0);
	AddField(m_iSellCentre, 0);
	AddField(m_iSellWindow, 0);
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(m_iCVSell, 0);
	AddField(m_iCVPay, 0);
	// <Marco Lui, 20050120>
	AddField(m_iOriginalEftAmount, 0);
	AddField(m_iRemainingEftAmount, 0);
	// </Marco Lui, 20050120>

	return buf;
}