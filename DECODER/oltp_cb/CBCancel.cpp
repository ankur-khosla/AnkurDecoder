/////////////////////////////////////////////////////////////////////
// CBCancel.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBCancel.h"

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBCancel::TranslateAction(const Msg *pMsg)
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

	m_iMethod			= pMlog->d.bt.ccp.methodwu;					// method

	union TSN tsn = pMlog->d.bt.ccp.tsn;

	m_cNewTsnFlag = tsnVersionwu(&tsn); // tsn version
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no

	short msgCode = pMlog->hdr.codewu;		// message code
	
	if ( m_cNewTsnFlag == TSN_OLTP ) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.ccp.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.ccp.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.ccp.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.bt.ccp.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iHighRecNo			= tsnBetTypebu(tsn);		// high order bits of record no

		int m_iBetType = 0;
		m_iBetType = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.bettypebu;

		char md[30] = { 0 };

		if (m_iBetType == BETTYP_AUP)
		{
			m_iLocation = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.loc;
			m_iMeetingDayOfYear = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.day;
			sprintf_s(md, "%d", pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.a.md);
		}
		else // EXOSTD
		{
			m_iLocation = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.es.loc;
			m_iMeetingDayOfYear = pMlog->d.bt.ccp.d.bet.bet.newbet.d.var.es.day;

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
			end_tm.tm_mon = atoi(mm.c_str()) -1 ;
			end_tm.tm_mday = atoi(dd.c_str());
		}

		start_tm.tm_year = pMsg->m_iMsgYear - 1900;
		start_tm.tm_mon = 1-1;//0-11
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

		m_iLowRecNo				= tsn19NTicketIDdu(tsn);		// low order bits of record no
	}

	// cancel SB bet
	if ( (m_iSaleSysNo == 0 && m_cNewTsnFlag == 1 && m_iTsnBetType == 4 ) || m_iTsnBetType == 8)
	{
		m_iCancelSysNo		= 0;									// system no [-1 local], this is used for internal index
		m_iCrossSysChanNo	= 0;									// cross system channel no
		m_iCrossSysMsn		= 0;									// cross system msn
		m_iFileNo			= 0;									// file no
		m_iBfcIndex			= 0;									// bfc index for shrink bet file
		m_iMeetingDrawIndex	= 0;									// meeting/draw index for cancel
		m_iSellCentre		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.sellCentrelu;		// selling centre
		m_iSellWindow		= pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.sellWindowu;		// selling window
		char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
		if (pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime < 0)//pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime
		{
			sprintf(m_sSellTime, "01-01-1900");
			//pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			__time32_t sellTime = pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime; //pMsg->m_iMsgSellTime;// pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.sellTime;
			tm_SellTime			= _localtime32(&sellTime);
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

		m_cBetType			= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.bettypebu;	// bet type
		unsigned char bettype2 = pMlog->d.bt.sb.d.bet.bet.hdr.bettypebu;							 
		// convert SB bet type (by Lawrence Leung on 11/03/2003)
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
			m_cBetType = BETTYP_SB_SEC_BET;		// SE Section Bet
			sprintf(m_sBetType, "SB_SEC_BET");
		}
		else
		{
			sprintf(m_sBetType, "UNKNOW_SB");
		}

		m_iUnitBet			= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet //q308 changes
		m_iTotalCost		= pMlog->d.bt.ccp.d.sb.info.bet.bet.d.hdr.totdu;		// total cost
		unsigned int unitbet2 = pMlog->d.bt.sb.d.bet.bet.hdr.betinvcomb.flexi.baseinv;
		unsigned int ttlcost2 = pMlog->d.bt.sb.d.bet.bet.hdr.totdu;

		m_iLocation = 0; // SB has no location
		m_iMeetingDayOfYear = 0; // SB has no meeting
	}

	// cancel others
	else
	{
		m_iCancelSysNo		= pMlog->d.bt.ccp.d.bet.sysw;				// system no [-1 local], this is used for internal index
		//if (m_iCancelSysNo == -1)
		m_iCancelSysNo = pMsg->m_iSysNo; // set it to current system id; downstream will use the value
		m_iCrossSysChanNo	= pMlog->d.bt.ccp.d.bet.chanwu;				// cross system channel no
		m_iCrossSysMsn		= pMlog->d.bt.ccp.d.bet.msnwu;				// cross system msn
		m_iFileNo			= pMlog->d.bt.ccp.d.bet.filew;				// file no
		m_iBfcIndex			= pMlog->d.bt.ccp.d.bet.sbfcidxw;			// bfc index for shrink bet file
		m_iMeetingDrawIndex	= pMlog->d.bt.ccp.d.bet.midxw;				// meeting/draw index for cancel
		//int isize			= pMlog->d.bt.ccp.d.bet.lenw;	
		m_iSellCentre		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellCentrelu;	// selling centre
		m_iSellWindow		= pMlog->d.bt.ccp.d.bet.bet.newbet.h.sellWindowu;	// selling window

		char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
		if (pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime < 0)//pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime
		{
			sprintf(m_sSellTime, "01-01-1900");	
			//pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			__time32_t sellTime = pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime;//pMsg->m_iMsgSellTime; //pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.sellTime;
			tm_SellTime			= _localtime32(&sellTime);
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

		if (pMlog->hdr.ticket_type == TICKET_TYPE_RACING) //racing
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
			m_iLocation = 0; // No location concept.
			m_iMeetingDayOfYear = 0; // No meeting concept concept.
		}
		else
		{
			sprintf(m_sMeetingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear); // meeting date = selling date (business date)
		}

		m_cBetType			= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.bettypebu;	// bet type
		if (m_cBetType == 18)
		{
			m_cBetType = BETTYP_ALUP;
		}

		if (pMlog->hdr.ticket_type == TICKET_TYPE_TBD)
		{
			m_cBetType = 255; // Max value. No bet type for TBD
		}
		
		GetType(m_cBetType, m_sBetType);

		m_iUnitBet			= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.betinvcomb.flexi.baseinv;	// unit bet
		m_iTotalCost		= pMlog->d.bt.ccp.d.bet.bet.newbet.d.hdr.totdu;		// total cost

		// For TBD cancel
		if (pMlog->hdr.ticket_type == TICKET_TYPE_TBD)
		{
			m_iLocation = 0; // No location concept.
			m_iMeetingDayOfYear = 0; // No meeting concept concept.

			m_iSellCentre = pMlog->hdr.centrelu;	// selling centre
			m_iSellWindow = pMlog->hdr.windowwu;	// selling window

			m_iUnitBet = 0;
			m_iTotalCost = pMlog->d.bt.ccp.d.tbd.amtlu;
			m_iCrossSysChanNo = pMlog->d.bt.ccp.d.tbd.chanwu;
			m_iCrossSysMsn = pMlog->d.bt.ccp.d.tbd.ismsnlu;				// cross system msn
			m_iFileNo = 0;				// file no
			m_iBfcIndex = 0;			// bfc index for shrink bet file
			m_iMeetingDrawIndex = 0;				// No meeting concept

			sprintf(m_sSellTime, "01-01-1900");
			sprintf(m_sMeetingDate, "01-01-1900");
		}
	}
	// For cancel tb deposit

	//m_iMeetingDayOfYear = 0;//just for test. 2016-12-30

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
	if ( m_cBetType == BETTYP_MK6 )
		m_sMeetingDate[0] = 0;
	AddField(STORE_TYPE_STRING, m_sMeetingDate, 0);
	AddField(m_iCancelSysNo, 0);
	
	// Cancel TB Deposit
	if (m_iAcctNo != 0 && m_iTsnBetType == 5) //TSN bet type indicate deposit
	{
		m_iTBAmount			= pMlog->d.bt.ccp.d.tbd.amtlu;						// amount
		
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(STORE_TYPE_STRING, "01-01-1900", 0);
		AddField(0, 0);
		AddField(STORE_TYPE_STRING, "TBD", 0);
		AddField(m_iTBAmount, 0);
		AddField(m_iTBAmount, 0);
		return buf;
	}
	
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

	return buf;
}