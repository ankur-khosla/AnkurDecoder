/////////////////////////////////////////////////////////////////////
// CBPayout.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.H"
#include "CBPayout.h"

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBPayout::TranslateAction(const Msg *pMsg)
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

	m_cNewTsnFlag = tsnVersionwu(&tsn); // tsn version
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no

	memset(m_sMeetingDate,0,sizeof(m_sMeetingDate));
	sprintf(m_sMeetingDate, "01-01-1900"); // not concern meeting date, set default value

	if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.ccp.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.ccp.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.ccp.tsn.s19t.reclwu;		// low order bits of record no; new: ticketid
		m_iMeetingDayOfYear		= pMlog->d.bt.ccp.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		int m_iBetType = 0;
		m_iBetType = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.bettypebu;

		char md[30] = { 0 };

		if (m_iBetType == BETTYP_AUP)
		{
			m_iLocation = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.loc;
			//m_iMeetingDayOfYear = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.day;

			sprintf_s(md, "%d", pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.md);
		}
		else // EXOSTD
		{
			m_iLocation = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.es.loc;
			//m_iMeetingDayOfYear = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.es.day;

			sprintf_s(md, "%d", pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.es.md);
		}

		tm start_tm = {0};
		tm end_tm = {0};

		if (strlen(md) == 8)
		{
			string mdStr = md;
			string yy = mdStr.substr(0, 4);
			string mm = mdStr.substr(4, 2);
			string dd = mdStr.substr(6, 2);
			mdStr = yy + "-" + mm + "-" + dd;
			strcpy_s(m_sMeetingDate, mdStr.c_str());

			end_tm.tm_year = atoi(yy.c_str()) - 1900;
			end_tm.tm_mon = atoi(mm.c_str()) - 1;
			end_tm.tm_mday = atoi(dd.c_str());;
		}

		start_tm.tm_year = pMsg->m_iMsgYear - 1900;
		start_tm.tm_mon = 1-1; //0-11
		start_tm.tm_mday = 1;

		__time32_t s_date = _mktime32(&start_tm); //start date
		__time32_t e_date = _mktime32(&end_tm); // current date

		if (e_date >= s_date)
		{
			double diff_secs = _difftime32(e_date, s_date);
			if (diff_secs > 0)
			{
				m_iMeetingDayOfYear = (diff_secs / 3600 / 24);
			}
			else
			{
				m_iMeetingDayOfYear = 0;
			}
		}

		m_iHighRecNo			= m_iTsnBetType;// tsnBetTypebu(tsn);		// high order bits of record no 
		m_iLowRecNo				= tsn19NTicketIDdu(tsn);		// low order bits of record no;
	}

		//init
		m_iOrgDrawYear  =0;
		m_iOrgDrawNo    =0;

		tsn = pMlog->d.bt.ccp.d.bet.tsn;

		m_iNewTsnBetType = tsnBetTypebu(tsn);	// bet type
		m_iNewSaleSysNo = tsnSystemNumbu(tsn);

		if (m_cNewTsnFlag == TSN_OLTP)
		{
			if (pMlog->d.bt.ccp.d.bet.tsn.s19t.w1.type5 != 0)	// patial pay Q406
			{
				m_iNewHighRecNo = pMlog->d.bt.ccp.d.bet.tsn.s19t.w2.rech12;		// high order bits of record no
				m_iNewLowRecNo = pMlog->d.bt.ccp.d.bet.tsn.s19t.reclwu;		// low order bits of record no
			}
			else
			{
				m_iNewHighRecNo = 0;
				m_iNewLowRecNo = 0;
				m_iNewTsnBetType = 0;
				m_iNewSaleSysNo = 0;
			}
		}
		else 
		{
			if (pMlog->d.bt.ccp.d.bet.tsn.s19n.w1.type5 != 0)
			{
				m_iNewHighRecNo = tsnBetTypebu(tsn);		// high order bits of record no
				m_iNewLowRecNo = pMsg->m_iMsgTktid;		// low order bits of record no. use child tsn for partial pay
			}
			else
			{
				m_iNewHighRecNo = 0;
				m_iNewLowRecNo = 0;
				m_iNewTsnBetType = 0;
				m_iNewSaleSysNo = 0;
			}
		}
//	pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
//	if (m_iSaleSysNo == 0 && m_cNewTsnFlag ==1)
//  m_iTsnBetType == 4, racing
//  m_iTsnBetType == 8, soccer betting
	if ( m_iTsnBetType == 8)////????(m_iSaleSysNo == 0 && m_cNewTsnFlag == 1 && m_iTsnBetType == 4 ) || 
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
		
		__time32_t sellTime = pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime; //pMsg->m_iMsgSellTime;//
		tm_SellTime			= _localtime32(&sellTime);
		if (pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime < 0)//
		{	
			sprintf(m_sSellTime,"01-01-1900");
			pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon+1], tm_SellTime->tm_year+1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
			/*if ( tm_SellTime->tm_yday > m_iMeetingDayOfYear ) 
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear + 1, m_sMeetingDate);
			}
			else
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
			}*/
		}	

		sprintf(m_sMeetingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear); // meeting date = selling date (business date)
		

		m_cBetType			= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.bettypebu;// bet type

		m_iUnitBet			= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet //q308 changes
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

		__time32_t payTime = pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payTime; // pMsg->m_iMsgSellTime; //;
		tm_PayTime			= _localtime32(&payTime);
		if (pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payTime < 0)
		{	
			sprintf(m_sPayTime,"01-01-1900");
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

		m_iOrgNoOfBankers = 0;
		m_iOrgNoOfOthers = 0;
		m_iOrgRandomFlag = 0;
		m_iOrgNoOfEntries = 0;
		m_iOrgNoOfDrawSelected = 0;
		m_cIsPartialFlag =0;
		m_iLocation = 0; // SB has no location
		m_iMeetingDayOfYear = 0; // SB has no meeting

	}
	else if (  m_iTsnBetType == 1  || m_iTsnBetType == 7 )  // lottery
	{
		if (m_cNewTsnFlag == TSN_OLTP)
			m_iOrgDrawNo = pMlog->d.bt.ccp.tsn.s19t.w4.day9;
		else
		{
			m_iOrgDrawNo = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.drawwu; // get draw no
			m_iOrgDrawYear = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.yearwu; // get draw year. format yy,eg:12

			m_iOrgDrawYear = m_iOrgDrawYear + 1900;
			if (m_iOrgDrawYear < pMsg->m_iMsgYear)
			{
				m_iOrgDrawYear = m_iOrgDrawYear + 100; //yyyy
			}
		}

		m_iLocation = 0; // No location concept. 
		m_iMeetingDayOfYear = 0; // No meeting concept.
		
		m_iCancelSysNo		= pMlog->d.bt.ccp.d.bet.sysw;				// system no [-1 local], this is used for internal index
		//if (m_iCancelSysNo == -1)
		m_iCancelSysNo = pMsg->m_iSysNo;
		sprintf(m_sCancelSysNo, "%d", m_iCancelSysNo);
		m_iCrossSysChanNo	= pMlog->d.bt.ccp.d.bet.chanwu;				// cross system channel no
		m_iCrossSysMsn		= pMlog->d.bt.ccp.d.bet.msnwu;				// cross system msn
		//m_iFileNo			= pMlog->d.bt.ccp.d.bet.filew;				// file no
		m_iFileNo = 0;													// No file
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
		__time32_t sellTime = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime; //pMsg->m_iMsgSellTime;//
		tm_SellTime			= _localtime32(&sellTime);
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime < 0)//
		{
			sprintf(m_sSellTime,"01-01-1900");
			//pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon+1], tm_SellTime->tm_year+1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
			/*if ( tm_SellTime->tm_yday > m_iMeetingDayOfYear )
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear + 1, m_sMeetingDate);
			}
			else
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
			}*/
		}	
		
		sprintf(m_sMeetingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear); // meeting date=selling date

		GetType(m_cBetType, m_sBetType);

		m_iUnitBet			= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet //q308 changes
		m_iTotalCost		= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.costlu;		// total cost  // Q310 changes 

		m_iTotalPay			= pMlog->d.bt.ccp.d.bet.payoutdu;					// total payout

		m_iBetSysIndex		= pMlog->d.bt.ccp.d.bet.othsys.syswu;				// account bet system index
		sprintf(m_sBetSysIndex, "%d", m_iBetSysIndex);
		m_iInterMsn			= pMlog->d.bt.ccp.d.bet.othsys.ismsnlu;				// inter system msn
		m_iCardNo			= pMlog->d.bt.ccp.d.bet.othsys.carddu;				// card no

		if (m_cBetType == 17 || m_cBetType == 16) // 16=mk6, 17=gbl
		{
			m_iNoOfRefund = pMlog->d.bt.ccp.d.bet.bchg.md.drrfdbu;		// no. of draw refund
			m_iDrawNo = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.drawwu;
			m_iOrgRandomFlag = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.n.rand1;		// random flag
			m_cIsPartialFlag = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.n.pub1;	// partial unit bet q310
			

			if (m_iTsnBetType == 1 ) // single
			{
				m_iOrgNoOfDrawSelected =1;
			}
			else    //multple draw
			{	
				m_iOrgNoOfDrawSelected = pMlog->d.bt.ccp.d.bet.bchg.md.drselbu; // no. of draw selected drselbu
			}

			if (pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.n.multi1 == 0)  //CT: single_entry ==1
			{	
				m_iOrgNoOfBankers = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.n.sel.single.nbnkbu;	// no. of bankers
				m_iOrgNoOfOthers = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.n.sel.single.nothbu; // # of other selections [0=non-banker]
				m_iOrgNoOfEntries = 1;
			
			}
			else 
			{
				m_iOrgNoOfBankers = 0;	// no. of bankers
				m_iOrgNoOfOthers = 0; // # of other selections [0=non-banker]
				m_iOrgNoOfEntries = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.n.sel.multi.entbu; // number of entries
			}


		}
		else
		{
			m_iNoOfRefund = 0;
			m_iDrawNo = 0;
		}

		m_iPayCentre		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.payCentrelu;		// payout centre
		
		__time32_t payTime = pMsg->m_iMsgTime;// pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime;  //pMsg->m_iMsgSellTime;
		tm_PayTime			= _localtime32(&payTime);
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime < 0)
		{	
			sprintf(m_sPayTime,"01-01-1900");
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


	else if (m_iTsnBetType== TSN_BTYPE_CV) // CV payout
	{
		m_iCancelSysNo = pMsg->m_iSysNo;
		sprintf(m_sCancelSysNo, "%d", m_iCancelSysNo);
		m_iSellCentre = pMsg->cvRel.sellCentrelu;
		m_iSellWindow = pMsg->cvRel.sellWindowu;
		m_iOriginalEftAmount = pMsg->cvRel.originallu;
		m_iRemainingEftAmount = pMsg->cvRel.remainlu;
		m_iTotalCost = pMsg->cvRel.costlu;
		m_iMethod = pMsg->cvRel.methodbu;
		m_iPayCentre = pMsg->cvRel.payCentrelu;
		m_iPaySys = pMsg->cvRel.paySysb;
		m_cPaidFinalFlag = pMsg->cvRel.paidfinal1;

		char	m_sMonths[13][4] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		
		__time32_t sellTime = pMsg->cvRel.sellTime;
		if(pMlog->hdr.othsys1 == 1)
			sellTime = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime; //pMsg->m_iMsgSellTime;//

		tm_SellTime = _localtime32(&sellTime);
		if (sellTime < 0)//pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime
		{
			sprintf(m_sSellTime, "01-01-1900");
			//pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon + 1], tm_SellTime->tm_year + 1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);

			/*if (tm_SellTime->tm_yday > m_iMeetingDayOfYear)
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear + 1, m_sMeetingDate);
			}
			else
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
			}*/
		}

		strcpy_s(m_sMeetingDate, "2000-01-01"); // hard code for CV pauout


		__time32_t payTime = pMsg->cvRel.payTime; // pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime;		
		if(pMlog->hdr.othsys1 == 1)
			payTime = pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime;
		
		tm_PayTime = _localtime32(&payTime);
		if (payTime < 0)
		{
			sprintf(m_sPayTime, "01-01-1900");
		}
		else
		{
			sprintf(m_sPayTime, "%02d-%s-%d %02d:%02d:%02d", tm_PayTime->tm_mday, m_sMonths[tm_PayTime->tm_mon + 1], tm_PayTime->tm_year + 1900, tm_PayTime->tm_hour, tm_PayTime->tm_min, tm_PayTime->tm_sec);
		}

		m_iFileNo = 0;
		m_iUnitBet = 0;
		m_iTotalPay = 0;

		m_iPayChild = 0;
		m_uiConsolation = 0;

		m_iOrgNoOfBankers = 0;
		m_iOrgNoOfOthers = 0;
		m_iOrgRandomFlag = 0;
		m_iOrgNoOfEntries = 0;
		m_iOrgNoOfDrawSelected = 0;
		m_cIsPartialFlag = 0;

		m_iBfcIndex = 0;				// bfc index for shrink bet file
		m_iMeetingDrawIndex = 0;				// meeting/draw index for cancel

		m_iCrossSysChanNo = 0;
		m_iCrossSysMsn = 0;
		m_cBetType = BETTYP_CV; // hard code
		GetType(m_cBetType, m_sBetType);
		m_iBetSysIndex = 0;
		m_iInterMsn = 0;
		m_iCardNo = 0;
		m_iNoOfRefund = 0;
		m_iGenNo = 0;
		m_iPayParent = 0;
		m_cPaidPartialFlag = 0;
		m_cDivCalFlag = 0;
		m_cReleasePaidFlag = 0;
		m_cOverflowFlag = 0;
		m_cHoPaymentFlag = 0;
		m_iNewLowRecNo = 0;
		m_iLocation = 0; // CV has no location
		m_iMeetingDayOfYear = 0; // CV has no meeting

		if (m_cPaidFinalFlag == 1)
		{
			m_cPaidPartialFlag = 0;
		}
		else
		{
			m_cPaidPartialFlag = 1;
		}
	}

	else   // others old code
	{
		m_iCancelSysNo		= pMlog->d.bt.ccp.d.bet.sysw;				// system no [-1 local], this is used for internal index
		//if (m_iCancelSysNo == -1)
		m_iCancelSysNo = pMsg->m_iSysNo;
		sprintf(m_sCancelSysNo, "%d", m_iCancelSysNo);
		m_iCrossSysChanNo	= pMlog->d.bt.ccp.d.bet.chanwu;				// cross system channel no
		m_iCrossSysMsn		= pMlog->d.bt.ccp.d.bet.msnwu;				// cross system msn
		//m_iFileNo			= pMlog->d.bt.ccp.d.bet.filew;				// file no
		m_iFileNo = 0;
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
		__time32_t sellTime = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime; //pMsg->m_iMsgTime;  //pMsg->m_iMsgSellTime;//
		tm_SellTime			= _localtime32(&sellTime);
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime < 0)//
		{
			sprintf(m_sSellTime,"01-01-1900");
			//pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", tm_SellTime->tm_mday, m_sMonths[tm_SellTime->tm_mon+1], tm_SellTime->tm_year+1900, tm_SellTime->tm_hour, tm_SellTime->tm_min, tm_SellTime->tm_sec);
			/*if ( tm_SellTime->tm_yday > m_iMeetingDayOfYear )
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear + 1, m_sMeetingDate);
			}
			else
			{
				pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
			}*/
		}	

		if (pMlog->hdr.ticket_type == TICKET_TYPE_RACING) //recing
		{
			char md[30] = { 0 };

			if (m_iBetType == BETTYP_AUP)
			{
				sprintf_s(md, "%d", pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.md);
			}
			else // EXOSTD
			{

				sprintf_s(md, "%d", pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.es.md);
			}

			if (strlen(md) == 8)
			{
				string mdStr = md;
				string yy = mdStr.substr(0, 4);
				string mm = mdStr.substr(4, 2);
				string dd = mdStr.substr(6, 2);
				mdStr = yy + "-" + mm + "-" + dd;
				strcpy_s(m_sMeetingDate, mdStr.c_str());
			}
		}
		else if (pMlog->hdr.ticket_type == TICKET_TYPE_LOTTERY) // Lottery
		{
			m_iLocation = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.drawwu;
			m_iMeetingDayOfYear = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.yearwu;
		}
		else
		{
			sprintf(m_sMeetingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear); // meeting date=selling date
		}
		
		GetType(m_cBetType, m_sBetType);

		m_iUnitBet			= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet //q308 changes
		m_iTotalCost		= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.totdu;		// total cost

		m_iTotalPay			= pMlog->d.bt.ccp.d.bet.payoutdu;					 // total payout

		m_iBetSysIndex		= pMlog->d.bt.ccp.d.bet.othsys.syswu;				// account bet system index
		sprintf(m_sBetSysIndex, "%d", m_iBetSysIndex);
		m_iInterMsn			= pMlog->d.bt.ccp.d.bet.othsys.ismsnlu;				// inter system msn
		m_iCardNo			= pMlog->d.bt.ccp.d.bet.othsys.carddu;				// card no

		if (m_cBetType == 17 || m_cBetType == 16) // 16=mk6, 17=gbl
		{
		//	m_iNoOfRefund = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.lot.md.drrfdbu;	// no. of draw refund
			m_iNoOfRefund = pMlog->d.bt.ccp.d.bet.bchg.md.drrfdbu;	// no. of draw refund
			m_iDrawNo = m_iMeetingDayOfYear;
		}
		else
		{
			m_iNoOfRefund = 0;
			m_iDrawNo = 0;
		}

		m_iPayCentre		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.payCentrelu;		// payout centre
		
		__time32_t payTime = pMsg->m_iMsgTime; //pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime; //pMsg->m_iMsgSellTime; // 
		tm_PayTime			= _localtime32(&payTime);
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime < 0)
		{	
			sprintf(m_sPayTime,"01-01-1900");
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


		m_iOrgNoOfBankers = 0;
		m_iOrgNoOfOthers = 0;
		m_iOrgRandomFlag = 0;
		m_iOrgNoOfEntries = 0;
		m_iOrgNoOfDrawSelected = 0;
		m_cIsPartialFlag= 0;
	}

	//m_iMeetingDayOfYear = 0; // just for test. 2016.12.30

	// output
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
	if ( m_cBetType == BETTYP_MK6)
		m_sMeetingDate[0] = 0;
	AddField(STORE_TYPE_STRING, m_sMeetingDate, 0);
	//CT Q310 
	if (m_iCancelSysNo<0)
		m_iCancelSysNo =0;

	AddField(m_iCancelSysNo, 0);
	AddField(m_iCrossSysChanNo, 0);
	AddField(m_iCrossSysMsn, 0);
	AddField(m_iFileNo, 0);
	AddField(m_iBfcIndex, 0);
	AddField(m_iMeetingDrawIndex, 0);
	AddField(m_iSellCentre, 0);
	AddField(m_iSellWindow, 0);
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(m_cBetType, 0);
	AddField(STORE_TYPE_STRING, m_sBetType, 0);
	AddField(m_iUnitBet, 0);
	AddField(m_iTotalCost, 0);
	AddField(m_iTotalPay, 0);
	AddField(m_iBetSysIndex, 0);
	AddField(m_iInterMsn, 0);
	AddField(m_iCardNo, 0);
	AddField(m_iNoOfRefund, 0);
	AddField(m_iPayCentre, 0);
	AddField(STORE_TYPE_STRING, m_sPayTime, 0);
	AddField(m_iPaySys, 0);
	AddField(m_iGenNo, 0);
	AddField(m_iPayChild, 0);
	AddField(m_iPayParent, 0);
	AddField(m_cPaidPartialFlag, 0);
	AddField(m_cPaidFinalFlag, 0);
	AddField(m_cDivCalFlag, 0);
	AddField(m_cReleasePaidFlag, 0);
	AddField(m_cOverflowFlag, 0);
	AddField(m_cHoPaymentFlag, 0);
	// <Marco Lui, 20050120>
	AddField(m_iOriginalEftAmount, 0);
	AddField(m_iRemainingEftAmount, 0);
	// </Marco Lui, 20050120>
	AddField(m_uiConsolation, 0);

	// q406
	AddField(m_iNewHighRecNo, 0);
	AddField64(m_iNewLowRecNo, 0);
	AddField(m_iNewTsnBetType, 0);
	AddField(m_iNewSaleSysNo, 0);
	// q406

	//Q310 CT  20100518
	AddField(m_iOrgNoOfBankers, 0);
	AddField(m_iOrgNoOfOthers, 0);
	AddField(m_iOrgRandomFlag, 0);
	AddField(m_iOrgNoOfEntries, 0);
	AddField(m_iOrgNoOfDrawSelected, 0);

	AddField(m_iOrgDrawYear , 0);
	AddField(m_iOrgDrawNo , 0);

	AddField(m_cIsPartialFlag , 0);

	

	return buf;
}