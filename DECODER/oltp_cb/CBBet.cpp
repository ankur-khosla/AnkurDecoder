////////////////////////////////////////////////////////////////////
//
// CBBet.cpp: implementation of the CBBet class.
//
/////////////////////////////////////////////////////////////////////
#include <string.h>
#include "LOGDEF.h"
#include "CBBet.h"
#include "LOGRDCDEF.h"
#include <stdlib.h>
#include <MATH.H>
#include "tsnvar.h"
#include <stdlib.h>

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBBet::TranslateAction(const Msg *pMsg)
{
	struct LOG *pMlog;
	pMlog					= (struct LOG *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	union TSN tsn= pMlog->d.bt.rac.raceinfo.tsninfo.tsn;

	m_cNewTsnFlag			= tsnVersionwu(&tsn);		// new tsn flag; sp3: function--tsnVersionwu	pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19n.w4.tsnver2;
	//m_iHighRecNo = tsnBetTypebu(tsn); // bet type
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type

	memset(m_sMeetingDate,0,sizeof(m_sMeetingDate));

	if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19t.w2.rech12;	// high order bits of record no //?
		m_iLocation				= pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		
		m_iHighRecNo			= m_iTsnBetType;		// high order bits of record no //sp3:ticket type? function--tsnBetTypebu:bettype
		//m_iLocation				= pMlog->d.bt.rac.bet.d.var.es.loc;		// location; ; sp3:pMlog->d.bt.rac.bet.d.var.es.loc;
		m_iLowRecNo				= pMsg->m_iMsgTktid;		// low order bits of record no; sp3:ticket id. tktid is missing in AP tsn. donot use tsn19NTicketDdu
		//m_iMeetingDayOfYear		= pMlog->d.bt.rac.bet.d.var.es.day;		// meeting day of year; sp3: pMlog->d.bt.rac.bet.d.var.es.md;

		//int m_iBetType = 0;
		m_iBetType = pMlog->d.bt.rac.bet.d.hdr.bettypebu;

		char md[30] = { 0 };

		if (m_iBetType == BETTYP_AUP)
		{
			m_iLocation = pMlog->d.bt.rac.bet.d.var.a.loc;
			m_iMeetingDayOfYear = pMlog->d.bt.rac.bet.d.var.a.day;
			//sprintf(m_sMeetingDate, "%u", &pMlog->d.bt.rac.bet.d.var.a.md);
			sprintf_s(md, "%d", pMlog->d.bt.rac.bet.d.var.a.md);

			//itoa(pMlog->d.bt.rac.bet.d.var.a.md, m_sMeetingDate, 10);
		}
		else // EXOSTD
		{
			m_iLocation = pMlog->d.bt.rac.bet.d.var.es.loc;
			m_iMeetingDayOfYear = pMlog->d.bt.rac.bet.d.var.es.day;
			//itoa(pMlog->d.bt.rac.bet.d.var.es.md, m_sMeetingDate, 10);
			sprintf_s(md, "%d", pMlog->d.bt.rac.bet.d.var.a.md);
			//sprintf(m_sMeetingDate, "%u", &pMlog->d.bt.rac.bet.d.var.a.md);
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
				m_iMeetingDayOfYear	= (diff_secs / 3600 / 24);
			}
			else
			{
				m_iMeetingDayOfYear = 0;
			}
		}
	}


	// pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);

	m_iFileNo				= pMlog->d.bt.rac.raceinfo.tsninfo.filewu;				// file no
	m_iRdsIndex				= pMlog->d.bt.rac.rdsidxwu;				// rds index
	m_cMeetLocat			= pMlog->d.bt.rac.locbu;				// meeting location
	m_cMeetingDay			= pMlog->d.bt.rac.daybu;				// meeting day
	m_iSellCentre			= pMlog->d.bt.rac.bet.h.sellCentrelu;	// selling centre
	m_iSellWindow			= pMlog->d.bt.rac.bet.h.sellWindowu;	// selling window
	char m_sMonths[12][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	m_cTickGenNo			= pMlog->d.bt.rac.bet.h.genbu;			// ticket generation nos

//Q308 changes. 	m_iUnitBet				= pMlog->d.bt.rac.bet.d.hdr.betinvcomb.baseinv;		// base investment in dollar
	
	m_iFlexiBetFlag = (int)pMlog->d.bt.rac.bet.d.hdr.betinvcomb.flexi.flexibet;
	m_iTotalCost			= pMlog->d.bt.rac.bet.d.hdr.costlu;		// total cost in cents
	

	if (m_iFlexiBetFlag == 0) 
	{
		m_iUnitBet = ( unsigned int ) pMlog->d.bt.rac.bet.d.hdr.betinvcomb.flexi.baseinv;
		m_iUnitBetTenK = ( unsigned int ) m_iUnitBet * 10000.0;  // new output field for unitbet x 10000
		m_iTotalNoOfCombinations = ( unsigned int ) (m_iTotalCost/100) / m_iUnitBet;
	}
	else
	{		
		m_iTotalNoOfCombinations = pMlog->d.bt.rac.bet.d.hdr.betinvcomb.flexi.baseinv;
		
		// first truncate to 5 decimal and then 4/5 rounding to 4 decimal
		// let say unit bet = 200/3 = 66.6666666
		// old unit bet = 66.6667
		// new unit bet = 666667
		

		double a1 = m_iTotalCost;
		double a2 = m_iTotalNoOfCombinations;

		double tmp = a1*1000.0/a2; //6666666.6666-->6666666
		double tmp1 = (tmp/10.0);	//666666.6
		__int64 tmp2 = floor (tmp1 +0.5);	//666667.3 -> 6666667  ; floor = round down

		m_iUnitBetTenK = tmp2;		
	}



	// Sell time
	__time32_t sellTime = pMsg->m_iMsgSellTime;//pMlog->d.bt.rac.bet.d.hdr.sellTime;
	Time					= _localtime32(&sellTime);
	sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", Time->tm_mday, m_sMonths[Time->tm_mon], Time->tm_year+1900, Time->tm_hour, Time->tm_min, Time->tm_sec);

	if (m_sMeetingDate == NULL)
	{
		if (Time->tm_year + 1900 > pMsg->m_iMsgYear || Time->tm_yday > m_iMeetingDayOfYear) {
			pMsg->DayToDate(pMsg->m_iMsgYear + 1, m_iMeetingDayOfYear, m_sMeetingDate);
		}
		else
		{
			pMsg->DayToDate(pMsg->m_iMsgYear, m_iMeetingDayOfYear, m_sMeetingDate);
		}
	}


	m_iBetType				= pMlog->d.bt.rac.bet.d.hdr.bettypebu;	// bet type
/*
	if (m_iBetType >= 18 && m_iBetType < 27) {
		m_iBetType = 30;	//30 = alup bettype see bettype.h
	}
*/
	GetBetType(m_iBetType, m_sBetType);

	m_iPayChild		= pMlog->d.bt.rac.bet.h.ptr.pay.paycb.fwdreclu;		// bet record # of child ticket
	m_iPayParent	= pMlog->d.bt.rac.bet.h.ptr.pay.bckreclu;		// bet record # of parent ticket
	m_iCVSell		= pMlog->d.bt.rac.bet.h.ptr.cv.selllogseqlu;	// log seq at selling
	m_iCVPay		= pMlog->d.bt.rac.bet.h.ptr.cv.paylogseqlu;		// log seq at payout

	unsigned short length = pMlog->d.bt.rac.bet.length;
	unsigned int   offset = pMlog->d.bt.rac.bet.offset;
	unsigned int   content = pMlog->d.bt.rac.bet.content;

	m_cSelections[0] = 0;
	GetSel(pMlog, m_iBetType, m_cSelections);				// selection bitmap
	// For detail of GetSel(), please check DeSelMap.cpp
	switch (m_iBetType)
	{
	case BETTYP_AUP:

		m_cEventNo			= pMlog->d.bt.rac.bet.d.var.a.evtbu;		// no of events
		m_cFormula			= pMlog->d.bt.rac.bet.d.var.a.fmlbu;		// formula
		getForm(m_cFormula, m_sFormula);
		for (a=0; a<=5; a++)
		{
			m_cAllupPoolType[a]			= pMlog->d.bt.rac.bet.d.var.a.sel[a].bettypebu;	// Allup cross pool type
			m_iAllupRaceNo[a]			= pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu;	// race no
			m_cAllupBankerFlag[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].ind.bnk1;	// banker
			m_cAllupFieldFlag[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].ind.fld1;	// field
			m_cAllupMultiFlag[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].ind.mul1;	// multiple
			m_cAllupMultiBankerFlag[a]	= pMlog->d.bt.rac.bet.d.var.a.sel[a].ind.mbk1;	// multiple banker
			m_cAllupRandomFlag[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].ind.rand1;	// randomly generated
			m_iNoOfCombination[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].comwu;		// no of combinations
			m_iPayFactor[a]				= pMlog->d.bt.rac.bet.d.var.a.sel[a].pftrlu;	// pay factor
			m_iAllupBankerBitmap[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].sellu[0];		// selection bitmap
			m_iAllupSelectBitmap[a]		= pMlog->d.bt.rac.bet.d.var.a.sel[a].sellu[1];
			
		}
		break;

	default:
		m_iRaceNo			= pMlog->d.bt.rac.bet.d.var.es.racebu;		// race no
		m_cBankerFlag		= pMlog->d.bt.rac.bet.d.var.es.ind.bnk1;	// banker flag
		m_cFieldFlag		= pMlog->d.bt.rac.bet.d.var.es.ind.fld1;	// field flag
		m_cMultiFlag		= pMlog->d.bt.rac.bet.d.var.es.ind.mul1;	// multi flag
		m_cMultiBankerFlag	= pMlog->d.bt.rac.bet.d.var.es.ind.mbk1;	// multi banker flag
		m_cRandomFlag		= pMlog->d.bt.rac.bet.d.var.es.ind.rand1;	// randomly generated
		for (a=0; a<=5; a++)
		{
			m_iBitmap[a]	= pMlog->d.bt.rac.bet.d.var.es.sellu[a];	// selection bitmap
		}
		break;
	}

	// Output

	//m_iMeetingDayOfYear = 0; // just for test. 2016.12.30

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
	AddField(m_iRdsIndex, 0);
	AddField(m_cMeetLocat, 0);
	AddField(m_cMeetingDay, 0);
	AddField(STORE_TYPE_STRING, m_sMeetingDate, 0);
	AddField(m_iSellCentre, 0);
	AddField(m_iSellWindow, 0);
	AddField(m_cTickGenNo, 0);
	AddField64(m_iUnitBetTenK, 0);
	AddField(m_iTotalCost, 0);
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(m_iBetType, 0);
	AddField(STORE_TYPE_STRING, m_sBetType, 0);
	AddField(m_iPayChild, 0);
	AddField(m_iPayParent, 0);
	AddField(m_iCVSell, 0);
	AddField(m_iCVPay, 0);

	// cancel flag for EDW
	AddField(STORE_TYPE_STRING, "", 0);
	

	switch (m_iBetType)
	{
	case BETTYP_AUP:

		AddField(m_cEventNo, 0);
		AddField(STORE_TYPE_STRING, m_sFormula, 0);
		for (a=0; a<m_cEventNo; a++)
		{	
			GetBetType(m_cAllupPoolType[a], m_sBetType);
			AddField(STORE_TYPE_STRING, m_sBetType, 0);
			AddField(m_iAllupRaceNo[a], 0);
			AddField(m_cAllupBankerFlag[a], 0);
			AddField(m_cAllupFieldFlag[a], 0);
			AddField(m_cAllupMultiFlag[a], 0);
			AddField(m_cAllupMultiBankerFlag[a], 0);
			AddField(m_cAllupRandomFlag[a], 0);
			AddField(m_iNoOfCombination[a], 0);
			AddField(m_iPayFactor[a], 0);
		}
		for (a=5; a>=m_cEventNo; a--)
		{
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
		}
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		AddField(0, 0);
		break;

	default:
		AddField(0, 0);
		AddField(0, 0);
		for (a=0; a<=5; a++)
		{
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
			AddField(0, 0);
		}
		AddField(m_iRaceNo, 0);
		AddField(m_cBankerFlag, 0);
		AddField(m_cFieldFlag, 0);
		AddField(m_cMultiFlag, 0);
		AddField(m_cMultiBankerFlag, 0);
		AddField(m_cRandomFlag, 0);

		break;
	}
	int len;
	len = strlen(m_cSelections);
	if(len > 1000)
	{
		char TrunSel[1000];
		memcpy(TrunSel, m_cSelections, 1000);
		AddField(STORE_TYPE_STRING, TrunSel, 0);
	}
	else
	{
		AddField(STORE_TYPE_STRING, m_cSelections, 0);
	}



	if (m_iBetType < BETTYP_ALUP || m_iBetType >= BETTYP_FF )
	{
		int m_iNoOfBankers,i=0;
		for (i = 0; i<=2; i++)
		{
			m_iNoOfBankers=pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[i];
			AddField(m_iNoOfBankers, 0);
		}
		for(i = 0; i<=5; i++)
		{
			memset(m_sBitmap,0, sizeof(m_sBitmap));
			if (pMlog->d.bt.rac.bet.d.var.es.sellu[i] > 65535)
			{
				sprintf(m_sBitmap, "0000");
			}
			else
			{
				sprintf(m_sBitmap, "%04X", pMlog->d.bt.rac.bet.d.var.es.sellu[i]);
			}
			AddField(STORE_TYPE_STRING, m_sBitmap, 0);
		}
	}
	else
	{
		AddField(0, 0);	// No of bankers for multi leg (non allup)
		AddField(0, 0);	// No of bankers for multi leg (non allup)
		AddField(0, 0);	// No of bankers for multi leg (non allup)


		char	temp[20];
		int i = 0;
		for(int i = 0; i<m_cEventNo; i++)
		{
			m_sBitmap[0] = 0;

			if (pMlog->d.bt.rac.bet.d.var.a.sel[i].sellu[0] > 65535) {
				sprintf(temp, "0000");
			}
			else {
				sprintf(temp, "%04X", pMlog->d.bt.rac.bet.d.var.a.sel[i].sellu[0]);
			}
			strcat(m_sBitmap, temp);
			if (pMlog->d.bt.rac.bet.d.var.a.sel[i].sellu[1] > 65535) {
				sprintf(temp, "0000");
			}
			else {
				sprintf(temp, "%04X", pMlog->d.bt.rac.bet.d.var.a.sel[i].sellu[1]);
			}
			strcat(m_sBitmap, temp);
			AddField(STORE_TYPE_STRING, m_sBitmap, 0);
		}
		for (i=m_cEventNo; i<=5; i++) {
			AddField(STORE_TYPE_STRING, "0000", 0);
		}
	}
	
	//q308 changes -  add 2 new field
	AddField(m_iFlexiBetFlag, 0);
	AddField(m_iTotalNoOfCombinations, 0);

	return buf;
}

char* CBBet::GetBetType(char m_cType, char Type[10])
{
	switch (m_cType)
	{
	case BETTYP_WINPLA:
		sprintf(Type, "W-P");
		break;

	case BETTYP_WIN:
		sprintf(Type, "WIN");
		break;

	case BETTYP_PLA:
		sprintf(Type, "PLA");
		break;

	case BETTYP_QIN:
		sprintf(Type, "QIN");
		break;

	case BETTYP_QPL:
		sprintf(Type, "QPL");
		break;

	case BETTYP_DBL:
		sprintf(Type, "DBL");
		break;

	case BETTYP_TCE:
		sprintf(Type, "TCE");
		break;

	case BETTYP_FCT:
		sprintf(Type, "FCT");
		break;

	case BETTYP_QTT:
		sprintf(Type, "QTT");
		break;

	case BETTYP_DQN:
		sprintf(Type, "D-Q");
		break;

	case BETTYP_TBL:
		sprintf(Type, "TBL");
		break;

	case BETTYP_TTR:
		sprintf(Type, "T-T");
		break;

	case BETTYP_6UP:
		sprintf(Type, "6UP");
		break;

	case BETTYP_DTR:
		sprintf(Type, "D-T");
		break;

	case BETTYP_TRIO:
		sprintf(Type, "TRI");
		break;

	case BETTYP_QINQPL:
		sprintf(Type, "QQP");
		break;

	case BETTYP_CV:
		sprintf(Type, "CV");
		break;

	case BETTYP_MK6:
		sprintf(Type, "MK6");
		break;

	case BETTYP_PWB:
		sprintf(Type, "PWB");
		break;

	case BETTYP_ALUP:
		sprintf(Type, "ALUP");
		break;

	case BETTYP_FF:
		sprintf(Type, "F-F");
		break;

	case BETTYP_BWA:
		sprintf(Type, "BWA");
		break;

	case BETTYP_CWA:
		sprintf(Type, "CWA");
		break;

	case BETTYP_CWB:
		sprintf(Type, "CWB");
		break;

	case BETTYP_CWC:
		sprintf(Type, "CWC");
		break;

	case BETTYP_IWN:
		sprintf(Type, "IWN");
		break;
	default:
		sprintf(Type, "XXXX");
		break;
	}

	return(Type);
}