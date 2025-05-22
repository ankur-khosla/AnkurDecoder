/////////////////////////////////////////////////////////////////////
// CBCVIssue.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBCVIssue.h"

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBCVIssue::TranslateAction(const Msg *pMsg)
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

	PackHeader("cb_cv_issue_insert_sp", pMlog, pMsg);

	union TSN tsn = pMlog->d.bt.cv.tsn;

	m_cNewTsnFlag = tsnVersionwu(&tsn);		// new tsn flag; sp3: function--tsnVersionwu	pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19n.w4.tsnver2;
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type

	if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.cv.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.cv.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.cv.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.bt.cv.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iHighRecNo = m_iTsnBetType; // high order bits of record no

		int m_iBetType = 0;
		m_iBetType = pMlog->d.bt.cv.bet.d.hdr.bettypebu;

		m_iLocation = 0; // No location and meeting concept. set it to 0. 2017.1.6 paul ou
		m_iMeetingDayOfYear = 0; //No location and meeting concept. set it to 0. 2017.1.6 paul ou

		m_iLowRecNo		= pMsg->m_iMsgTktid; //tsn19NTicketIDdu(tsn);		// low order bits of record no
	}

	m_iFileNo			= pMlog->d.bt.cv.filewu;			// file no

	m_iUnitBet			= pMlog->d.bt.cv.bet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet  //q308 changes
	m_iTotalCost		= pMlog->d.bt.cv.bet.d.hdr.costlu;	// total cost

	// <Marco Lui, 20050120>
	m_iOriginalEftAmount	= pMlog->d.bt.cv.bet.h.prveft.eft.originallu;
	m_iRemainingEftAmount	= pMlog->d.bt.cv.bet.h.prveft.eft.remainlu;
	// </Marco Lui, 20050120>

	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	__time32_t sellTime = pMsg->m_iMsgSellTime; //pMlog->d.bt.cv.bet.d.hdr.sellTime;
	tm_SellTime			= _localtime32(&sellTime);
	sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon+1], tm_SellTime->tm_year+1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);

	m_cIssueFlag		= pMlog->d.bt.cv.bet.d.var.cv.methodbu;	// method

	m_iCVSell			= pMlog->d.bt.cv.bet.h.ptr.cv.selllogseqlu;	// log seq at selling
	m_iCVPay			= pMlog->d.bt.cv.bet.h.ptr.cv.paylogseqlu;	// log seq at payout

	//m_iMeetingDayOfYear = 0; // just for test. 2016.12.30

	// Output
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
	AddField(m_iFileNo, 0);
	AddField(m_iUnitBet, 0);
	AddField(m_iTotalCost, 0);
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(m_cIssueFlag, 0);
	AddField(m_iCVSell, 0);
	AddField(m_iCVPay, 0);
	AddField(m_iOriginalEftAmount, 0);
	AddField(m_iRemainingEftAmount, 0);

	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}