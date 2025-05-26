// ABRace.cpp

#include "LOGDEF_AB.h"
#include "ABRace.h"
#include "DeSelMap.h"
#include <MATH.H>
#include <string>
using namespace std;

char * ABRace::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;


	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);
	char	m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	/*struct tm *meet_t = _localtime32( &pMlog->data.bt.rac.tran.bet.dat );
	sprintf(m_sMeetDate, "%02d-%s-%d %02d:%02d:%02d", meet_t->tm_mday, m_sMonths[meet_t->tm_mon], meet_t->tm_year+1900, meet_t->tm_hour, meet_t->tm_min, meet_t->tm_sec);*/

	//m_cLoc = pMlog->data.bt.rac.tran.bet.locbu;
	//m_cDay = pMlog->data.bt.rac.tran.bet.daybu;

	m_itotalPay = ( unsigned __int64 )pMlog->data.bt.rac.tran.bet.d.hdr.totdu;

	m_iTotalCost = pMlog->data.bt.rac.tran.bet.d.hdr.costlu;

	//q308 changes
	m_iFlexiBetFlag = pMlog->data.bt.rac.tran.bet.d.hdr.betinvcomb.flexi.flexibet;
	
	if (m_iFlexiBetFlag == 0) 
	{
		m_iUnitBet = ( unsigned __int64 )pMlog->data.bt.rac.tran.bet.d.hdr.betinvcomb.flexi.baseinv;
		m_iUnitBetTenK = m_iUnitBet * 10000;  // new output field for unitbet x 10000
		m_iTotalNoOfCombinations = (unsigned int) (m_iTotalCost/100 )/ m_iUnitBet;
	}
	else
	{		
		m_iTotalNoOfCombinations = pMlog->data.bt.rac.tran.bet.d.hdr.betinvcomb.flexi.baseinv; 	
	
		// m_iTotalNoOfCombinations = pMlog->d.bt.rac.bet.d.hdr.betinvcomb.flexi.baseinv; 
		// first truncate to 5 decimal and then 4/5 rounding to 4 decimal
		// let say unit bet = 200/3 = 66.6666666
		// old unit bet = 66.6667
		// new unit bet = 666667
		
		double  a1 = m_iTotalCost;
		double  a2 = m_iTotalNoOfCombinations;

		double  tmp = a1*1000.0/a2; //6666666.6666-->6666666
		double  tmp1 = (tmp/10.0);	//666666.6
		__int64 tmp2 = floor (tmp1 +0.5);	//666667.3 -> 6666667  ; floor = round down

		m_iUnitBetTenK = tmp2;	
/*		
		m_iTotalNoOfCombinations = pMlog->data.bt.rac.tran.bet.d.hdr.betinvcomb.flexi.baseinv; 
		
		// first truncate to 5 decimal and then 4/5 rounding to 4 decimal
		// let say unit bet = 200/3 = 66.6666666
		// old unit bet = 66.6667
		// new unit bet = 666667

		unsigned __int64 tmp = m_iTotalCost*100000/100/m_iTotalNoOfCombinations; //6666666.6666-->6666666
		unsigned double tmp1 = (tmp/10);	//666666.6
		unsigned __int64 tmp2 = floor (tmp1 +0.5);	//666667.3 -> 6666667  ; floor = round down

		m_iUnitBetTenK = tmp2;		
*/
	}

	
	struct tm *sell_t = _localtime32(&pMsg->m_iMsgSellTime); //_localtime32( &pMlog->data.bt.rac.tran.bet.d.hdr.sellTime );
	sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", sell_t->tm_mday, m_sMonths[sell_t->tm_mon], sell_t->tm_year+1900, sell_t->tm_hour, sell_t->tm_min, sell_t->tm_sec);
	
	m_cBetType = pMlog->data.bt.rac.tran.bet.d.hdr.bettypebu;
	GetBetType(m_cBetType, m_sBetType);

	int a=0;
	struct tm *meet_t;
	char m_cSelections[1024];
	GetSel(pMlog, m_cBetType, m_cSelections);				// selection bitmap
	// For detail of GetSel(), please check DeSelMap.cpp


	char md[30] = { 0 };

	switch (m_cBetType)
	{
	case BETTYP_AUP:
		m_cNoOfEvt	= pMlog->data.bt.rac.tran.bet.d.var.a.evtbu;		// no of events
		m_cFormula	= pMlog->data.bt.rac.tran.bet.d.var.a.fmlbu;		// formula

		meet_t = _localtime32(&pMlog->data.bt.rac.tran.bet.d.var.a.md); // meeting date
		m_cLoc = pMlog->data.bt.rac.tran.bet.d.var.a.loc; // location
		m_cDay = pMlog->data.bt.rac.tran.bet.d.var.a.day; // day

		sprintf_s(md, "%d", pMlog->data.bt.rac.tran.bet.d.var.a.md);
		if (strlen(md) == 8)
		{
			string mdStr = md;
			string yy = mdStr.substr(0, 4);
			string mm = mdStr.substr(4, 2);
			string dd = mdStr.substr(6, 2);
			mdStr = yy + "-" + mm + "-" + dd + " 00:00:00";
			strcpy_s(m_sMeetDate, mdStr.c_str());
		}


		getForm(m_cFormula, m_sFormula);
		
		for (a=0; a<=5; a++)
		{
			m_cAllupPoolType[a]			= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].bettypebu;	// Allup Cross Pool Type
			m_iAllupRaceNo[a]			= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].racebu;	// race no
			m_cAllupBankerFlag[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].ind.bnk1;	// banker
			m_cAllupFieldFlag[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].ind.fld1;	// field
			m_cAllupMultiFlag[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].ind.mul1;	// multiple
			m_cAllupMultiBankerFlag[a]	= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].ind.mbk1;	// multiple banker
			m_cAllupRandomFlag[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].ind.rand1;	// randomly generated
			m_iNoOfCombination[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].comwu;		// no of combinations
			m_iPayFactor[a]				= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].pftrlu;	// pay factor
			m_iAllupBankerBitmap[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].sellu[0];		// selection bitmap
			m_iAllupSelectBitmap[a]		= pMlog->data.bt.rac.tran.bet.d.var.a.sel[a].sellu[1];
		}
		break;

	default:
		m_iRaceNo			= pMlog->data.bt.rac.tran.bet.d.var.es.racebu;		// race no
		m_cBankerFlag		= pMlog->data.bt.rac.tran.bet.d.var.es.ind.bnk1;	// banker flag
		m_cFieldFlag		= pMlog->data.bt.rac.tran.bet.d.var.es.ind.fld1;	// field flag
		m_cMultiFlag		= pMlog->data.bt.rac.tran.bet.d.var.es.ind.mul1;	// multi flag
		m_cMultiBankerFlag	= pMlog->data.bt.rac.tran.bet.d.var.es.ind.mbk1;	// multi banker flag
		m_cRandomFlag		= pMlog->data.bt.rac.tran.bet.d.var.es.ind.rand1;	// randomly generated
		for (a=0; a<=5; a++)
		{
			m_iBitmap[a]	= pMlog->data.bt.rac.tran.bet.d.var.es.sellu[a];	// selection bitmap
		}

		sprintf_s(md, "%d", pMlog->data.bt.rac.tran.bet.d.var.es.md);
		if (strlen(md) == 8)
		{
			string mdStr = md;
			string yy = mdStr.substr(0, 4);
			string mm = mdStr.substr(4, 2);
			string dd = mdStr.substr(6, 2);
			mdStr = yy + "-" + mm + "-" + dd + " 00:00:00";
			strcpy_s(m_sMeetDate, mdStr.c_str());
		}

		//char md[30] = { 0 };
		//__time32_t md_t = pMlog->data.bt.rac.tran.bet.d.var.es.md;
		//sprintf_s(md,"%d", md_t);

		//// convert "yyyyMMdd" to "yyyy-MM-dd 00:00:00"
		//if (strlen(md) == 6)
		//{
		//	string mdStr = md;
		//	string yy = mdStr.substr(0, 4);
		//	string mm = mdStr.substr(4, 2);
		//	string dd = mdStr.substr(6, 2);
		//	mdStr = yy + "-" + mm + "-" + dd + " 00:00:00";
		//	memcpy_s(m_sMeetDate, sizeof(mdStr), mdStr.c_str(), sizeof(mdStr));
		//}

		//meet_t = _localtime32(&pMlog->data.bt.rac.tran.bet.d.var.es.md); // meeting date
		m_cLoc = pMlog->data.bt.rac.tran.bet.d.var.es.loc;
		m_cDay = pMlog->data.bt.rac.tran.bet.d.var.es.day;

		break;
	}

	//sprintf(m_sMeetDate, "%02d-%s-%d %02d:%02d:%02d", meet_t->tm_mday, m_sMonths[meet_t->tm_mon], meet_t->tm_year + 1900, meet_t->tm_hour, meet_t->tm_min, meet_t->tm_sec);

	m_iAnonymous			= pMlog->hdr.anonymous1;  // Anonymous Account (2011IBT)
	m_iCscCard				= pMlog->data.bt.rac.tran.bet.csctrn;	// Transacion with CSC (201108PSR)

	// Output

	AddField(STORE_TYPE_STRING, m_sMeetDate, 0);
	AddField(m_cLoc, 0);
	AddField(m_cDay, 0);
	AddField64(m_itotalPay, 0);
	AddField64(m_iUnitBetTenK, 0);		// use new unit bet *10k field
	AddField64(m_iTotalCost, 0);			// total cost use signed int 64
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(STORE_TYPE_STRING, m_sBetType, 0);

	// cancel flag for EDW
	AddField(STORE_TYPE_STRING, " ", 0);
	

	switch (m_cBetType)
	{
	case BETTYP_AUP:
		AddField(m_cNoOfEvt, 0);
		AddField(STORE_TYPE_STRING, m_sFormula, 0);
		for (a=0; a<m_cNoOfEvt; a++)
		{
			GetBetType(m_cAllupPoolType[a], m_sAllupBettype);
			AddField(STORE_TYPE_STRING, m_sAllupBettype, 0);
			AddField(m_iAllupRaceNo[a], 0);
			AddField(m_cAllupBankerFlag[a], 0);
			AddField(m_cAllupFieldFlag[a], 0);
			AddField(m_cAllupMultiFlag[a], 0);
			AddField(m_cAllupMultiBankerFlag[a], 0);
			AddField(m_cAllupRandomFlag[a], 0);
			AddField(m_iNoOfCombination[a], 0);
			AddField(m_iPayFactor[a], 0);
		}
		for (a=m_cNoOfEvt; a<=5; a++)
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

	if (m_cBetType < BETTYP_AUP || m_cBetType >= BETTYP_FF)
	{
		int i=0, m_iNoOfBankers;
		for (i = 0; i<=2; i++)
		{
			m_iNoOfBankers=pMlog->data.bt.rac.tran.bet.d.var.es.betexbnk.bnkbu[i];
			AddField(m_iNoOfBankers, 0);
		}
		for(i = 0; i<=5; i++)
		{
			m_sBitmap[0] = 0;
			if (pMlog->data.bt.rac.tran.bet.d.var.es.sellu[i] > 65535)
			{
				sprintf(m_sBitmap, "0000");
			}
			else
			{
				sprintf(m_sBitmap, "%04X", pMlog->data.bt.rac.tran.bet.d.var.es.sellu[i]);
			}
			AddField(STORE_TYPE_STRING, m_sBitmap, 0);
		}
	}
	else // allup ticket
	{	
		AddField(0, 0);	// No of bankers for multi leg (non allup)
		AddField(0, 0);	// No of bankers for multi leg (non allup)
		AddField(0, 0);	// No of bankers for multi leg (non allup)

		char	temp[20];
		int i=0;
		for(i = 0; i<m_cNoOfEvt; i++)
		{
			m_sBitmap[0] = 0;

			if (pMlog->data.bt.rac.tran.bet.d.var.a.sel[i].sellu[0] > 65535) {
				sprintf(temp, "0000");
			}
			else {
				sprintf(temp, "%04X", pMlog->data.bt.rac.tran.bet.d.var.a.sel[i].sellu[0]);
			}
			strcat(m_sBitmap, temp);
			if (pMlog->data.bt.rac.tran.bet.d.var.a.sel[i].sellu[1] > 65535) {
				sprintf(temp, "0000");
			}
			else {
				sprintf(temp, "%04X", pMlog->data.bt.rac.tran.bet.d.var.a.sel[i].sellu[1]);
			}
			strcat(m_sBitmap, temp);
			AddField(STORE_TYPE_STRING, m_sBitmap, 0);
		}
		for (i=m_cNoOfEvt; i<=5; i++) {
			AddField(STORE_TYPE_STRING, "0000", 0);
		}
	}

	int m_iCrossSell = pMlog->data.bt.rac.crossSellFl;
	AddField(m_iCrossSell, 0);
	
	//q308 changes -  add 2 new field
	AddField(m_iFlexiBetFlag, 0);
	AddField(m_iTotalNoOfCombinations, 0);

	AddField(m_iAnonymous, 0);					// Anonymous Account (2011IBT)
	AddField(m_iCscCard, 0);					    // Transaction with CSC Card (201108PSR)
	
	return buf;
}

char* ABRace::GetBetType(char BetType, char Type[20])
{
	switch (BetType)
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
		
		case BETTYP_AWP:
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