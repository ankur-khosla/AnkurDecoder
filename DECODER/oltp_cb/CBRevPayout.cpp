/////////////////////////////////////////////////////////////////////
// CBPayout.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.H"
#include "CBRevPayout.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 

int CBRevPayout::TranslateAction(const Msg *pMsg)
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

	PackHeader("cb_payout_insert_sp", pMlog, pMsg);

	m_iMethod			= pMlog->d.bt.ccp.methodwu;			// method

	m_cNewTsnFlag			= pMlog->d.bt.ccp.tsn.s19t.w4.tsn16;		// new tsn flag
	if ( m_cNewTsnFlag == 0 ) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.ccp.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.ccp.tsn.s19t.w1.loc3;		// location
		m_iTsnBetType			= pMlog->d.bt.ccp.tsn.s19t.w1.type5;	// bet type
		m_iLowRecNo				= pMlog->d.bt.ccp.tsn.s19t.reclwu;		// low order bits of record no
		m_iSaleSysNo			= pMlog->d.bt.ccp.tsn.s19t.w1.sys3;		// sale system no
		m_cNewTsnFlag			= pMlog->d.bt.ccp.tsn.s19t.w4.tsn16;	// tsn 16 flag
		m_iMeetingDayOfYear		= pMlog->d.bt.ccp.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iHighRecNo			= pMlog->d.bt.ccp.tsn.s.w12.rechb;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.ccp.tsn.s.w12.loc3;		// location
		m_iTsnBetType			= pMlog->d.bt.ccp.tsn.s.w12.type3;		// bet type
		m_iLowRecNo				= pMlog->d.bt.ccp.tsn.s.w12.reclw;		// low order bits of record no
		m_iSaleSysNo			= pMlog->d.bt.ccp.tsn.s.w4.sys3;		// sale system no
		m_cNewTsnFlag			= pMlog->d.bt.ccp.tsn.s.w4.new1;		// new tsn flag
		m_iMeetingDayOfYear		= pMlog->d.bt.ccp.tsn.s.w4.day9;		// meeting day of year
	}
/*
	m_iHighRecNo		= pMlog->d.bt.ccp.tsn.s.w12.rechb;	// high order bits of record no
	m_iLowRecNo			= pMlog->d.bt.ccp.tsn.s.w12.reclw;	// low order bits of record no
	m_iLocation			= pMlog->d.bt.ccp.tsn.s.w12.loc3;	// location
	m_iTsnBetType		= pMlog->d.bt.ccp.tsn.s.w12.type3;	// tsn bet type
	m_iSaleSysNo		= pMlog->d.bt.ccp.tsn.s.w4.sys3;	// sale system no
	m_cNewTsnFlag		= pMlog->d.bt.ccp.tsn.s.w4.new1;	// new tsn flag
	m_iMeetingDayOfYear	= pMlog->d.bt.ccp.tsn.s.w4.day9;	// meeting day of year [racing] draw no [lottery] or transaction day
*/

	if ( pMlog->d.bt.ccp.d.bet.tsn.s19t.w1.type5 != 0 )	// patial pay Q406
	{
		m_iNewHighRecNo			= pMlog->d.bt.ccp.d.bet.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iNewLowRecNo			= pMlog->d.bt.ccp.d.bet.tsn.s19t.reclwu;		// low order bits of record no
		m_iNewTsnBetType		= pMlog->d.bt.ccp.d.bet.tsn.s19t.w1.type5;	// bet type
		m_iNewSaleSysNo			= pMlog->d.bt.ccp.d.bet.tsn.s19t.w1.sys3;		// sale system no
	}
	else
	{
		m_iNewHighRecNo		= 0;
		m_iNewLowRecNo		= 0;
		m_iNewTsnBetType	= 0;
		m_iNewSaleSysNo		= 0;
	}

//	pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
//	if (m_iSaleSysNo == 0 && m_cNewTsnFlag ==1)

	if ( (m_iSaleSysNo == 0 && m_cNewTsnFlag == 1 && m_iTsnBetType == 4 ) || m_iTsnBetType == 8)
	{
		m_iHighRecNo		= pMlog->d.bt.ccp.tsn.sb.w1.rech10;		// high rec no for SB
		m_iLowRecNo			= pMlog->d.bt.ccp.tsn.sb.reclwu;		// low rec no for SB

		m_iNewHighRecNo		= 0;
		m_iNewLowRecNo		= 0;
		m_iNewTsnBetType	= 0;
		m_iNewSaleSysNo		= 0;

		m_iCancelSysNo		= 0;				// system no [-1 local], this is used for internal index
		m_iCrossSysChanNo	= 0;				// cross system channel no
		m_iCrossSysMsn		= 0;				// cross system msn
		m_iFileNo			= 0;				// file no
		m_iBfcIndex			= 0;				// bfc index for shrink bet file
		m_iMeetingDrawIndex	= 0;				// meeting/draw index for cancel

		m_iSellCentre		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.sellCentrelu;	// selling centre
		m_iSellWindow		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.sellWindowu;	// selling window
		// <Marco Lui, 20050120>
		m_iOriginalEftAmount	= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.prveft.eft.originallu;
		m_iRemainingEftAmount	= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.prveft.eft.remainlu;
		// </Marco Lui, 20050120>
		char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		
		tm_SellTime			= localtime(&pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime);
		if (pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime < 0)
		{	
			sprintf(m_sSellTime,"01-01-1900");
			pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon+1], tm_SellTime->tm_year+1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
			if ( tm_SellTime->tm_yday > m_iMeetingDayOfYear ) 
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear + 1, m_sMeetingDate);
			}
			else
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
			}
		}	


		m_cBetType			= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.bettypebu;// bet type

		m_iUnitBet			= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.binvlu;	// unit bet
		m_iTotalCost		= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.totdu;	// total cost

		m_iTotalPay			= pMlog->d.bt.ccp.d.sb.info.bet.payoutdu;			// total payout

		m_iBetSysIndex		= pMlog->d.bt.ccp.d.sb.othsys.syswu;				// account bet system index
		char m_sBetSysIndex[20];
		sprintf(m_sBetSysIndex, "%d", m_iBetSysIndex);
		m_iInterMsn			= pMlog->d.bt.ccp.d.sb.othsys.ismsnlu;				// inter system msn
		m_iCardNo			= pMlog->d.bt.ccp.d.sb.othsys.carddu;				// card no

		m_iNoOfRefund = 0;
		m_iDrawNo = 0;

		m_iPayCentre		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payCentrelu;		// payout centre

		tm_PayTime			= localtime(&pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payTime);
		if (pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payTime < 0)
		{	
			sprintf(m_sSellTime,"01-01-1900");
		}
		else
		{
			sprintf(m_sPayTime, "%02d-%s-%d %02d:%02d:%02d", tm_PayTime->tm_mday, m_sMonths[tm_PayTime->tm_mon+1], tm_PayTime->tm_year+1900, tm_PayTime->tm_hour, tm_PayTime->tm_min, tm_PayTime->tm_sec);
		}
		m_cPaidPartialFlag	= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sts.paidpart1;	// paid - partial
		m_cPaidFinalFlag	= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sts.paidfinal1;	// paid - final
		m_cDivCalFlag		= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sts.divcal1;		// divcal
		m_cReleasePaidFlag	= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sts.released1;	// released to be paid at centre payCentrelu
		m_cOverflowFlag		= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sts.overflow1;	// overflow
		m_cHoPaymentFlag	= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sts.hop1;			// ho payment
		m_iPaySys			= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.paySysb;			// payout system
		m_iGenNo			= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.genbu;				// ticke generation number
		m_iPayChild			= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.ptr.pay.paycb.fwdreclu;	// bet record # of child ticket
		m_iPayParent		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.ptr.pay.bckreclu;	// bet record # of parent ticket
			
		if (m_cBetType == 19)
		{
			m_cBetType = BETTYP_SB_PM;      // pari-mutuel collated soccer bet
			sprintf(m_sBetType,"SB_PM");
		}
		else if (m_cBetType == 20)
		{
			m_cBetType = BETTYP_SB_FO;		// fix-odds collated soccer bet
			sprintf(m_sBetType, "SB_FO");
		}
		else if (m_cBetType == 21)
		{
			m_cBetType = BETTYP_SB_EXO;		// exotic soccer bet
			sprintf(m_sBetType, "SB_EXO");
		}
		else if (m_cBetType == 22)
		{
			m_cBetType = BETTYP_SB_AUP_PM;  // all-up soccer bet parimutuel
			sprintf(m_sBetType, "SB_AUP_PM");
		}
		else if (m_cBetType == 23)
		{
			m_cBetType = BETTYP_SB_AUP_FO_CTL;  // controlled fixed odds allup bet
											// => an allup set is associated, need
											// to look up by first pool selected
			sprintf(m_sBetType, "SB_AUP_FO_CTL");
		}
		else if (m_cBetType == 24)
		{
			m_cBetType = BETTYP_SB_AUP_FO_NON;  // Non-controlled fixed odds allup bet
			sprintf(m_sBetType, "SB_AUP_FO_NON");
		}
		else if (m_cBetType == 25)
		{
			m_cBetType = BETTYP_SB_SCT_FO;  // SECTION BET
			sprintf(m_sBetType, "SB_SEC_BET");
		}
		else
		{
			sprintf(m_sBetType, "UNKNOW_SB");
		}

		m_iPayChild		= 0;
		m_uiConsolation = 0;
	}
	else
	{
		m_iCancelSysNo		= pMlog->d.bt.ccp.d.bet.sysw;				// system no [-1 local], this is used for internal index
		sprintf(m_sCancelSysNo, "%d", m_iCancelSysNo);
		m_iCrossSysChanNo	= pMlog->d.bt.ccp.d.bet.chanwu;				// cross system channel no
		m_iCrossSysMsn		= pMlog->d.bt.ccp.d.bet.msnwu;				// cross system msn
		m_iFileNo			= pMlog->d.bt.ccp.d.bet.filew;				// file no
		sprintf(m_sFileNo, "%d", m_iFileNo);
		m_iBfcIndex			= pMlog->d.bt.ccp.d.bet.sbfcidxw;			// bfc index for shrink bet file
		m_iMeetingDrawIndex	= pMlog->d.bt.ccp.d.bet.midxw;				// meeting/draw index for cancel

		m_iSellCentre		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellCentrelu;	// selling centre
		m_iSellWindow		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellWindowu;	// selling window
		// <Marco Lui, 20050120>
		m_iOriginalEftAmount	= pMlog->d.bt.ccp.d.bet.bet.newbet.h.prveft.eft.originallu;
		m_iRemainingEftAmount	= pMlog->d.bt.ccp.d.bet.bet.newbet.h.prveft.eft.remainlu;
		// </Marco Lui, 20050120>

		m_cBetType			= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.bettypebu;	// bet type

		char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		tm_SellTime			= localtime(&pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime);
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime < 0)
		{
			sprintf(m_sSellTime,"01-01-1900");
			pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon+1], tm_SellTime->tm_year+1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
			if ( tm_SellTime->tm_yday > m_iMeetingDayOfYear )
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear + 1, m_sMeetingDate);
			}
			else
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
			}
		}	
		
		GetType(m_cBetType, m_sBetType);

		m_iUnitBet			= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.binvlu;	// unit bet
		m_iTotalCost		= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.totdu;		// total cost

		m_iTotalPay			= pMlog->d.bt.ccp.d.bet.payoutdu;					// total payout

		m_iBetSysIndex		= pMlog->d.bt.ccp.d.bet.othsys.syswu;				// account bet system index
		sprintf(m_sBetSysIndex, "%d", m_iBetSysIndex);
		m_iInterMsn			= pMlog->d.bt.ccp.d.bet.othsys.ismsnlu;				// inter system msn
		m_iCardNo			= pMlog->d.bt.ccp.d.bet.othsys.carddu;				// card no

		if (m_cBetType == 17 || m_cBetType == 16)
		{
			m_iNoOfRefund = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.md.drrfdbu;	// no. of draw refund
			m_iDrawNo = pMlog->d.bt.ccp.tsn.s.w4.day9;
		}
		else
		{
			m_iNoOfRefund = 0;
			m_iDrawNo = 0;
		}

		m_iPayCentre		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.payCentrelu;		// payout centre
		
		tm_PayTime			= localtime(&pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime);
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime < 0)
		{	
			sprintf(m_sSellTime,"01-01-1900");
		}
		else
		{
			sprintf(m_sPayTime, "%02d-%s-%d %02d:%02d:%02d", tm_PayTime->tm_mday, m_sMonths[tm_PayTime->tm_mon+1], tm_PayTime->tm_year+1900, tm_PayTime->tm_hour, tm_PayTime->tm_min, tm_PayTime->tm_sec);
		}
		
		m_iPaySys			= pMlog->d.bt.ccp.d.bet.bet.newbet.h.paySysb;			// payout system
		m_iGenNo			= pMlog->d.bt.ccp.d.bet.bet.newbet.h.genbu;				// ticke generation number
//		m_iPayChild			= pMlog->d.bt.ccp.d.bet.bet.newbet.h.ptr.pay.fwdreclu;	// bet record # of child ticket
		m_iPayParent		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.ptr.pay.bckreclu;	// bet record # of parent ticket
		m_cPaidPartialFlag	= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sts.paidpart1;	// paid - partial
		m_cPaidFinalFlag	= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sts.paidfinal1;// paid - final
		m_cDivCalFlag		= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sts.divcal1;	// divcal
		m_cReleasePaidFlag	= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sts.released1;	// released to be paid at centre payCentrelu
		m_cOverflowFlag		= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sts.overflow1;	// overflow
		m_cHoPaymentFlag	= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sts.hop1;		// ho payment

// start q106 
		if ( m_cPaidFinalFlag == 1 )
		{
			m_uiConsolation	= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.ptr.pay.paycb.consolationlu;	// bet record # of child ticket
			m_iPayChild = 0;
		}
		else
		{
			m_iPayChild		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.ptr.pay.paycb.fwdreclu;	// bet record # of child ticket			
			m_uiConsolation = 0;
		}
// end q106
	}
	
	// output
	m_pRcd->AddCol(m_iMethod, 0);
	m_pRcd->AddCol(m_iHighRecNo, 0);
	m_pRcd->AddCol(m_iLowRecNo, 0);
	m_pRcd->AddCol(m_iLocation, 0);
	m_pRcd->AddCol(m_iTsnBetType, 0);
	m_pRcd->AddCol(m_iSaleSysNo, 0);
	m_pRcd->AddCol(m_cNewTsnFlag, 0);
	m_pRcd->AddCol(m_iMeetingDayOfYear, 0);
	if ( m_cBetType == BETTYP_MK6 )
		m_sMeetingDate[0] = 0;
	m_pRcd->AddCol(STORE_TYPE_STRING, m_sMeetingDate, 0);
	m_pRcd->AddCol(m_iCancelSysNo, 0);
	m_pRcd->AddCol(m_iCrossSysChanNo, 0);
	m_pRcd->AddCol(m_iCrossSysMsn, 0);
	m_pRcd->AddCol(m_iFileNo, 0);
	m_pRcd->AddCol(m_iBfcIndex, 0);
	m_pRcd->AddCol(m_iMeetingDrawIndex, 0);
	m_pRcd->AddCol(m_iSellCentre, 0);
	m_pRcd->AddCol(m_iSellWindow, 0);
	m_pRcd->AddCol(STORE_TYPE_STRING, m_sSellTime, 0);
	m_pRcd->AddCol(m_cBetType, 0);
	m_pRcd->AddCol(STORE_TYPE_STRING, m_sBetType, 0);
	m_pRcd->AddCol(m_iUnitBet, 0);
	m_pRcd->AddCol(m_iTotalCost, 0);
	m_pRcd->AddCol(m_iTotalPay, 0);
	m_pRcd->AddCol(m_iBetSysIndex, 0);
	m_pRcd->AddCol(m_iInterMsn, 0);
	m_pRcd->AddCol(m_iCardNo, 0);
	m_pRcd->AddCol(m_iNoOfRefund, 0);
	m_pRcd->AddCol(m_iPayCentre, 0);
	m_pRcd->AddCol(STORE_TYPE_STRING, m_sPayTime, 0);
	m_pRcd->AddCol(m_iPaySys, 0);
	m_pRcd->AddCol(m_iGenNo, 0);
	m_pRcd->AddCol(m_iPayChild, 0);
	m_pRcd->AddCol(m_iPayParent, 0);
	m_pRcd->AddCol(m_cPaidPartialFlag, 0);
	m_pRcd->AddCol(m_cPaidFinalFlag, 0);
	m_pRcd->AddCol(m_cDivCalFlag, 0);
	m_pRcd->AddCol(m_cReleasePaidFlag, 0);
	m_pRcd->AddCol(m_cOverflowFlag, 0);
	m_pRcd->AddCol(m_cHoPaymentFlag, 0);
	// <Marco Lui, 20050120>
	m_pRcd->AddCol(m_iOriginalEftAmount, 0);
	m_pRcd->AddCol(m_iRemainingEftAmount, 0);
	// </Marco Lui, 20050120>
	m_pRcd->AddCol(m_uiConsolation, 0);

	// q406
	m_pRcd->AddCol(m_iNewHighRecNo, 0);
	m_pRcd->AddCol(m_iNewLowRecNo, 0);
	m_pRcd->AddCol(m_iNewTsnBetType, 0);
	m_pRcd->AddCol(m_iNewSaleSysNo, 0);
	// q406

	return NO_TRANSLATE_ERR;
}