
// CBSBBet.cpp: implementation of the CBSBBet class.
//
/////////////////////////////////////////////////////////////////////

#include "CBSBBet.h"
#include "math.h"
#include "ExtractMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typedef char* STR;

CBSBBet::CBSBBet() : m_pSB(0)
{}

const int simSelMsgCodeOffSet = 15; // Add the hard string "50015@|@" at first position in "m_cData" below.

char * CBSBBet::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	m_iEntryNo = 0; // add for stage 2
	int selection_no = 0; // for indicating which selection. 
	m_cField2 = 0; // for simple_selection table
	sprintf(temp3, "%s", "");

	struct LOG *pMlog;
	pMlog						= (struct LOG *)pMsg->m_cpBuf;

	PackHeader("", pMlog, pMsg);

	union TSN tsn = pMlog->d.bt.sb.d.bet.tsn;

	m_cNewTsnFlag = tsnVersionwu(&tsn); // tsn version
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no

	if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.sb.d.bet.tsn.s19t.w2.rech12;	// high order bits of record no
		m_iLocation				= pMlog->d.bt.sb.d.bet.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.sb.d.bet.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.bt.sb.d.bet.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iHighRecNo			= m_iTsnBetType;				// high order bits of record no
		m_iLocation				= 0; // no location concept.
		m_iLowRecNo				= tsn19NTicketIDdu(tsn);				// low order bits of record no
		m_iMeetingDayOfYear		= 0;		// // no location concept.
	}

	m_iUnitBet				= pMlog->d.bt.sb.d.bet.bet.hdr.betinvcomb.flexi.baseinv;				// base investment in dollar //q308 changes
	m_iTotalCost			= pMlog->d.bt.sb.d.bet.bet.hdr.costlu;				// total cost in cents

	// Sell time
	__time32_t sellTime = pMlog->d.bt.sb.d.bet.bet.hdr.sellTime;
	Time					= _localtime32(&sellTime);
	char	m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", Time->tm_mday, m_sMonths[Time->tm_mon], Time->tm_year+1900, Time->tm_hour, Time->tm_min, Time->tm_sec);
	sprintf(m_sSellDate, "%02d-%s-%d", Time->tm_mday, m_sMonths[Time->tm_mon], Time->tm_year);
	m_iBetType				= pMlog->d.bt.sb.d.bet.bet.hdr.bettypebu;			// bet type
	GetType(m_iBetType, m_sBetType);

//	m_iBonusPcent			= pMlog->d.bt.sb.d.bet.bet.var.sb.bonusPcentwu;	// before div-in: bonus % for non-allup after div-in: total bonus in cents

	m_iBonusPcent			= pMlog->d.bt.sb.d.bet.bet.var.sb.sctbonus.bonuspcentwu;
	m_iSimplePool			= pMlog->d.bt.sb.d.bet.bet.var.sb.numbu;		// # of simple pool
	m_cFormula				= pMlog->d.bt.sb.d.bet.bet.var.sb.fmlentbu;		// all-up formula
	m_iBonusCent			= pMlog->d.bt.sb.d.bet.bet.var.sb.bonuslu;		// total bonus in cents
	
	m_cSetNumber			= pMlog->d.bt.sb.d.bet.bet.var.sb.sctbonus.sctid.setbu;		//
	// clearing section number when bet is section bet
	if ( m_iBetType != BETTYP_SB_SEC_BET ) {
		m_cSetNumber = 0;
	}

	if (m_iBetType == BETTYP_SB_AUP_FO_CTL)
		m_iCtrlFlag = 1;
	else
		m_iCtrlFlag = 0;

	// initialize empty string
	sprintf(m_sFormula, "%s", "");
	m_iTotalEntry = 0;

	if (m_iBetType >= BETTYP_SB_AUP_PM && m_iBetType <= BETTYP_SB_SEC_BET)		// section bet
		GetFormula(m_cFormula, m_sFormula);
	else
		m_iTotalEntry = m_cFormula;

	m_cBonusOverflowFlag	= pMlog->d.bt.sb.d.bet.bet.hdr.sts.bonusovfl1;		// bonus overflow

	AddField(m_iHighRecNo, 0);
	AddField64(m_iLowRecNo, 0);
	AddField(m_iTsnBetType, 0);
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(m_iUnitBet, 0);
	AddField(m_iTotalCost, 0);
	AddField(m_iBetType, 0);
	AddField(STORE_TYPE_STRING, m_sBetType, 0);
	AddField(m_cBonusOverflowFlag, 0);
	AddField(m_iBonusPcent, 0);
	AddField(m_iSimplePool, 0);

	// please be reminded that all-up formula only happened on ALL UP pool.
	// all-up pari-mutuel, all-up fixed odds and all-up with control fixed odds.
	// otherwise, there are no all-up formula, but the variable "m_cFormula" only 
	// store total # of entry.
	if (m_iBetType >= BETTYP_SB_AUP_PM && m_iBetType <= BETTYP_SB_SEC_BET)
		AddField(STORE_TYPE_STRING, m_sFormula, 0);
	else
		AddField(m_iTotalEntry, 0);

	AddField(m_iCtrlFlag, 0);
	AddField(m_iBonusCent, 0);

	m_iOddsOut = pMlog->d.bt.sb.d.bet.oddsold1;	// odds out of date flag
	if (m_iOddsOut == 1)
	{
		AddField(STORE_TYPE_STRING, "Odds Outdated", 0);
	}
	else
	{
		AddField(STORE_TYPE_STRING, "No Odds Req", 0);
	}

	// for cb_sb_simple_selections
	struct BETSB_SIMPLE *pMSim;

	pMSim = (struct BETSB_SIMPLE *)pMlog->d.bt.sb.d.bet.bet.var.sb.vbu;

	m_cField = pMSim->fld1;	// field indicator (added on stage-2)

	m_iRandGen = 0;
	if(m_iBetType == BETTYP_SB_PM || m_iBetType == BETTYP_SB_EXO)
	{
		m_iRandGen = pMSim->sel.non.pm.ind.rand1;
	}
	else if(m_iBetType == BETTYP_SB_AUP_PM)
	{
		m_iRandGen = pMSim->sel.aup.sel.pm.ind.rand1;
	}
	else
	{
		m_iRandGen = 0;
	}

	AddField(m_cField, 0);
	AddField(m_iRandGen, 0);  // random generator (added on stage 2)

	// new Added in M7D
	AddField(m_cSetNumber, 0);


	// Add in Q405
	unsigned __int64 m_iTotalPayout		= pMlog->d.bt.sb.d.bet.bet.hdr.totdu;
	unsigned int m_iForfeitFlag 	    = pMlog->d.bt.sb.d.bet.bet.hdr.sts.forfeitfl;
	AddField64(m_iTotalPayout, 0);
	AddField(m_iForfeitFlag, 0);


	// L51_R0_BenKoo_2
	// added on 29-Mar-2004, by Ben Koo
	// if the pool is NOT SPC, the date default will be 01-01-1900
	sprintf(m_sSpcCreateDate, "");
	sprintf(day, "");

	int simSelMsgCode = LOGAB_CODE_SIMPLE_SEL;
								
	if (m_iBetType	== BETTYP_SB_PM				// bettype 19	Pari-mutuel collated soccer bet
		|| m_iBetType == BETTYP_SB_FO			// bettype 20	Fix-odds collated soccer bet
		|| m_iBetType == BETTYP_SB_EXO )		// bettype 21 	Exotic soccer bet
	{
		unsigned char m_cDay		= pMSim->daybu;			// day of week/round 
															// or event # for GFTP/group # for GWP
		unsigned char m_cMatch		= pMSim->matchbu;		// match of the day/ league # /tournament #
		__time32_t m_iDate				= pMSim->date;			// match / championship date
		struct tm *matchtime;
		matchtime = _localtime32( &m_iDate);
		m_iYear = 1900+matchtime->tm_year;
		m_iDay	= matchtime->tm_mday;
		sprintf(day, "%d-%s-%d", m_iDay, m_sMonths[matchtime->tm_mon], m_iYear);
		sprintf(time, "%02d:%02d:%02d", matchtime->tm_hour, matchtime->tm_min, matchtime->tm_sec);
		unsigned char m_cPool			= pMSim->poolbu;			// pool type #
		unsigned char m_cLiveBet	= pMSim->livebu;		// live bet indicator
		unsigned char m_cExtraBet	= pMSim->extrabu;		// extra time bet indicator //q407
		unsigned short m_iHome			= pMSim->info.team.homewu;	// home team #
		unsigned short m_iAway			= pMSim->info.team.awaywu;	// away team #
		unsigned char m_cNoSelection	= pMSim->numbu;				// # of selections

		// we need to translate the Pool Type Code
		// since the pool type code is different 
		// according to different systems or environments
		// such as FBIS. please refer to the code define at sbdef.h
		//m_iPoolTypeNum = GetPoolTypeNo(m_cPool);
			
		if (m_iBetType == BETTYP_SB_FO) // fixed odd BetType 20
		{
			unsigned char m_cScore;
			unsigned char m_cScore2;

			unsigned short m_corn_cScore;
			unsigned short m_corn_cScore2;


			unsigned char m_cLineSlotNo;   // multiple line

			m_cScore2 = 0;
			m_corn_cScore2 = 0;
			m_cLineSlotNo =0;

			char m_iHandGoal1;
			char m_iHandGoal2;
			char m_iNoOfGoal;
			m_cField2 = pMSim->fld1;
			m_iEntryNo = 1;
			m_iGroupNum = 0;
			m_iLegNo = 1;

			// L51_R0_BenKoo_2
			int spc_ttl_item = m_iSimplePool; // total number of selected Item(s)
			int k =0;

			if(m_cPool == SB_SPC_MATCH || m_cPool == SB_SPC_TRN)
			{
				for(k=0; k < spc_ttl_item; k++)
				{
					m_cDay			= pMSim->daybu;   // item no
					m_cMatch		= pMSim->matchbu; // special pool type no	
					m_cNoSelection	= pMSim->numbu;	  // no. of selections

					m_iEntryNo = k+1; // for muti-items selected

					int i = 0;
					for(i=0; i<m_cNoSelection; i++)
					{
						selection_no = i+1;  // for muti-selections

						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);

						unsigned char m_iSelNo	= pMSim->sel.non.fo2[i].selbu;	// player 
						unsigned int m_iOdd		= pMSim->sel.non.fo2[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.fo2[i].odds.chkdigit2;	// New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						__time32_t m_iSPCDate = pMSim->info.cdate; // spc creation date
						struct tm *spctime;
						spctime = _localtime32( &m_iSPCDate);
						m_iSPCYear = 1900+spctime->tm_year;
						m_iSPCDay	= spctime->tm_mday;
						sprintf(m_sSpcCreateDate, "%d-%s-%d", m_iSPCDay, m_sMonths[spctime->tm_mon], m_iSPCYear);

						sprintf(temp2, "~|~%d~|~%d", m_iOdd, m_iSelNo);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

						


						SimpleSelection(m_cData);
					}

					if (i == m_cNoSelection)
						pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+(sizeof(BETSB_SEL_FO_2)*m_cNoSelection)));

				}
			}
			else
			{
				for(int i=0; i<m_cNoSelection; i++)
				{
					selection_no = i+1;


					
					 if (m_cPool == SB_OOU || m_cPool == SB_FHLO|| m_cPool ==SB_CHLO)
					 {
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection);
					 }
					 else 
					 {
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);

					 }

					if (m_cPool == SB_FGS)
					{
						unsigned char m_iSelNo	= pMSim->sel.non.fo1[i].selbu;	// player 
						unsigned int m_iOdd		= pMSim->sel.non.fo1[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.fo1[i].odds.chkdigit2;	// New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2, "~|~%d~|~%d", m_iOdd, m_iSelNo);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

					}

// Q408 NTS/ETS
					else if (m_cPool == SB_NTS || m_cPool == SB_ETS)
					{
						m_iNoOfGoal	= pMSim->sel.non.foNts.noofgoal;	// # of goal 
						unsigned char m_cSel	= pMSim->sel.non.foNts.sel[i].selbu;	//	selection
						unsigned int m_iOdd		= pMSim->sel.non.foNts.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.foNts.sel[i].odds.chkdigit2;	// New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2, "~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet, m_iNoOfGoal);
						strcat(m_cData, temp3);

					}


					else if (m_cPool == SB_1X2 || m_cPool == SB_OES || m_cPool == SB_TOS || m_cPool == SB_FHAD || m_cPool == SB_TQL || m_cPool==SB_FTS)
					{	// MAR 2011   add FTS
						unsigned int m_iOdd		   = pMSim->sel.non.fo2[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.fo2[i].odds.chkdigit2; // New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						unsigned char m_cSel	= pMSim->sel.non.fo2[i].selbu;		// selecion
						
						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}
					else if (m_cPool == SB_OOU || m_cPool == SB_FHLO)
					{
						
						m_cScore	= pMSim->sel.non.hilo.sel[i].line1;	//handicap goal [1]
						m_cScore2	= pMSim->sel.non.hilo.sel[i].line2; //handicap goal [2]

						m_cLineSlotNo = pMSim->sel.non.hilo.sel[i].lineslot+1;  //lineslot;


						//m_cScore	= pMSim->sel.non.hilo.goal1;		// score to compared
						//m_cScore2	= pMSim->sel.non.hilo.goal2;		// score to compared 2


						unsigned int m_iOdd		   = pMSim->sel.non.hilo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.hilo.sel[i].odds.chkdigit2;
						unsigned char m_cSel	= pMSim->sel.non.hilo.sel[i].selbu;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}



						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d", m_cLineSlotNo, selection_no,m_iOdd, m_cSel);  //CT- ML2015
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);  //score2
						strcat(m_cData, temp2);
					}

					else if ( m_cPool == SB_CHLO)
					{
						
						
//						m_corn_cScore	= pMSim->sel.non.chlo.goal1;		// score to compared
//						m_corn_cScore2	= pMSim->sel.non.chlo.goal2;		// score to compared 2

						m_corn_cScore	= pMSim->sel.non.chlo.sel[i].line1;	//handicap goal [1]
						m_corn_cScore2	= pMSim->sel.non.chlo.sel[i].line2; //handicap goal [2]

						m_corn_cScore2 = (m_corn_cScore2 << 6) | ((m_corn_cScore >> 10) & 0x3F);
						m_corn_cScore  = (m_corn_cScore & 0x3FF);

						m_cLineSlotNo = pMSim->sel.non.chlo.sel[i].lineslot+1;  //lineslot;

						
						unsigned int m_iOdd		   = pMSim->sel.non.chlo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.chlo.sel[i].odds.chkdigit2;
						unsigned char m_cSel	= pMSim->sel.non.chlo.sel[i].selbu;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d", m_cLineSlotNo, selection_no,m_iOdd, m_cSel);  //CT- ML2015
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_corn_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_corn_cScore2, m_cExtraBet);  //score2
						strcat(m_cData, temp2);
					}



					//else if (m_cPool == SB_DBR || m_cPool == SB_COS || m_cPool == SB_GPF)
					else if (m_cPool == SB_DBR || m_cPool == SB_COS || m_cPool == SB_GPF || m_cPool == SB_FCRS) // 2012MAR
					{
						unsigned char m_cSel1	= pMSim->sel.non.fo3[i].selbu[0];		// selection 1
						unsigned char m_cSel2	= pMSim->sel.non.fo3[i].selbu[1];
						unsigned int m_iOdd	       = pMSim->sel.non.fo3[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.fo3[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						if(m_cPool == SB_DBR)
							sprintf(score, "%d-%d", m_cSel1, m_cSel2);
						else if(m_cPool == SB_COS)
							sprintf(score, "%d:%d", m_cSel1, m_cSel2);
						else if(m_cPool == SB_FCRS) // 2012MAR
							sprintf(score, "%d:%d", m_cSel1, m_cSel2);
						else if(m_cPool == SB_GPF)
						{
							sprintf(score, "%d,%d", m_cSel1, m_cSel2);
							m_iGroupNum = m_cDay;
						}


						sprintf(temp2,"~|~%d~|~%s", m_iOdd, score);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}
					else if (m_cPool == SB_HDC || m_cPool == SB_HHAD)
					{
						m_iHandGoal1		= pMSim->sel.non.foHdc.goal1b;		// handicap goal 1
						m_iHandGoal2		= pMSim->sel.non.foHdc.goal2b;		// handicap goal 2

						if(m_cPool == SB_HHAD)
							m_iHandGoal2 = 0; // no split goal on HHAD type

						unsigned int m_iOdd	= pMSim->sel.non.foHdc.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.foHdc.sel[i].odds.chkdigit2;
						unsigned char m_iSel	= pMSim->sel.non.foHdc.sel[i].selbu;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}
							
						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_iSel);
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~0~|~%d~|~%d~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iHandGoal1, m_iHandGoal2, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);
					}
					else if (m_cPool == SB_CHP || m_cPool == SB_GPW || m_cPool == SB_TPS) // L51_R0_BenKoo_2
					{
						unsigned char m_iSelNo	= pMSim->sel.non.fo2[i].selbu;	// player 
						unsigned int m_iOdd		= pMSim->sel.non.fo2[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.fo2[i].odds.chkdigit2;	// New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						if(m_cPool == SB_GPW)
							m_iGroupNum = m_cDay;

						sprintf(temp2, "~|~%d~|~%d", m_iOdd, m_iSelNo);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}
					
					SimpleSelection(m_cData);
				}
			}
			
		}
		else if (m_iBetType == BETTYP_SB_PM)// pari-mutuel BetType 19
		{
			unsigned char m_cScore;
			unsigned char m_cScore2=0;

			m_cField2 = pMSim->fld1;
			m_iGroupNum = 0;
			m_iLegNo = 1;

			//if(m_cPool == SB_FGS || m_cPool == SB_COS)
			if(m_cPool == SB_FGS || m_cPool == SB_COS || m_cPool == SB_FCRS) // 2012 MAR
			{
				for(int i=0; i<m_cNoSelection; i++)
				{
					selection_no = i+1;
					m_iEntryNo = 1;

					sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);

					if (m_cPool == SB_FGS) // no change for stage-2
					{
						unsigned char m_iSelNo = pMSim->sel.non.pm.det.pm1[i].selbu;

						sprintf(temp2, "~|~0~|~%d", m_iSelNo);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}
					else if (m_cPool == SB_COS)
					{
						unsigned char m_cSel1 = pMSim->sel.non.pm.det.sel2bu[i][0];
						unsigned char m_cSel2 = pMSim->sel.non.pm.det.sel2bu[i][1];

						sprintf(score, "%d:%d", m_cSel1, m_cSel2);

						sprintf(temp2, "~|~0~|~%s", score);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}
					else if (m_cPool == SB_FCRS) //2012 MAR
					{
						unsigned char m_cSel1 = pMSim->sel.non.pm.det.sel2bu[i][0];
						unsigned char m_cSel2 = pMSim->sel.non.pm.det.sel2bu[i][1];

						sprintf(score, "%d:%d", m_cSel1, m_cSel2);

						sprintf(temp2, "~|~0~|~%s", score);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}


					SimpleSelection(m_cData);
				}
			}


			if (m_cPool == SB_1X2 || m_cPool == SB_OES || m_cPool == SB_TOS || m_cPool == SB_FHAD || m_cPool == SB_TQL)
			{
				unsigned char m_cSel = pMSim->sel.non.pm.det.sel1bu;

				char sel[10];
				int ttl=0, s_no=0, i=0;
				m_iEntryNo = 1;
				
				if(m_cPool == SB_1X2 || m_cPool == SB_FHAD || m_cPool == SB_TQL)
					HADBitmap(m_cSel, sel, ttl);
				else if(m_cPool == SB_OES)
					OESBitmap(m_cSel, sel, ttl);
				else if(m_cPool == SB_TOS)
					TOSBitmap(m_cSel, sel, ttl);

				for(i=0; i<ttl; i++)
				{
					s_no = i+1;
					sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttl, s_no);
					sprintf(temp2, "~|~0~|~%s", sel[i]);
					strcat(m_cData, temp2);
					strcat(m_cData, "~|~0~|~0~|~0");
					sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp3);

					SimpleSelection(m_cData);
				}
			}
			else if (m_cPool == SB_OOU || m_cPool == SB_FHLO || m_cPool == SB_HDC || m_cPool == SB_HHAD)
			{
				m_cScore = pMSim->sel.non.pm.det.sel.compb;
				unsigned char m_cSel = pMSim->sel.non.pm.det.sel.selbu;

				char sel[10];
				int ttl=0, s_no=0, i=0;
				m_iEntryNo = 1;
				
				if (m_cPool == SB_OOU || m_cPool == SB_FHLO )
				{
					OOUBitmap(m_cSel, sel, ttl);

					for(i=0; i<ttl; i++)
					{
						s_no = i+1;
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttl, s_no);
						sprintf(temp2, "~|~0~|~%s", sel[i]);					
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);

						SimpleSelection(m_cData);
					}
				}
				else if (m_cPool == SB_HDC || m_cPool == SB_HHAD) // no split handicap goal in PM
				{
					
					HDCBitmap(m_cSel, sel, ttl); // same translation for HHAD and HDC

					for(i=0; i<ttl; i++)
					{
						s_no = i+1;
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttl, s_no);
						sprintf(temp2, "~|~0~|~%s", sel[i]);					
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~0~|~%d~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);

						SimpleSelection(m_cData);
					}
				}
			}
			else if (m_cPool == SB_DBR)		 // half/full time
			{
				// assume this is single entry
				unsigned short m_iHafuSel = pMSim->sel.non.pm.det.sel1wu[0];
				unsigned short ttlHafuSel = 0;
				int hafu_sel_no = 0;
				char HafuSel[10][10];
				m_iEntryNo = 1;

				GetHaFu(m_iHafuSel, HafuSel, ttlHafuSel);

				for(int h=0; h<ttlHafuSel; h++)
				{
					hafu_sel_no = h+1;
					sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlHafuSel, hafu_sel_no);
					sprintf(temp2, "~|~0~|~%s~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", HafuSel[h], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp2);	

					SimpleSelection(m_cData);
				}

			}
			else if (m_cPool == SB_POOL_HCS) // half/full correct score
			{
				unsigned int m_iHalf = pMSim->sel.non.pm.det.sellu[0];
				unsigned int m_iFull = pMSim->sel.non.pm.det.sellu[1];
				int hcs_sel_no=0;
				STR* HFCombination;
				m_iEntryNo = 1;

				GetHCS(m_iHalf, m_iFull, HFCombination, ttlSel);

				unsigned int chkHalfField = m_iHalf;
				unsigned int chkFullField = m_iFull;

				for(int k=0; k<ttlSel; k++)
				{
					hcs_sel_no = k+1;
					sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlSel, hcs_sel_no);
					sprintf(temp2, "~|~0~|~%s~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", HFCombination[k], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp2);	

					SimpleSelection(m_cData);
				}
				
				if(HFCombination)
				{
					delete HFCombination;
					HFCombination = 0;
				}

			}
			else if (m_cPool == SB_CHPP) // L50R0_BK02 -- Implement new pool types
			{
				struct BETSB_SEL_PM_TRN_GRP *pTRNGrp;
				pTRNGrp = (struct BETSB_SEL_PM_TRN_GRP *)pMSim->sel.non.pm.det.trnsel.vbu;

				int chpp_sel_no=0, i=0, j=0, k=0, pos=0;
				int m_iNumSel1=0, m_iNumSel2=0;
				int bitLen = 8;
				int m_iFirstArr[100];
				int m_iSecArr[100];
				unsigned short ttlChppSel = 0;
				unsigned char m_iCHPSel1;
				unsigned char m_iCHPSel2;
				unsigned long x=0;
				m_iEntryNo = 1;
				m_iLegNo = 1;

				memset(m_iFirstArr, 0, 100);
				memset(m_iSecArr, 0, 100);

				unsigned char numOfGrp = pMSim->sel.non.pm.det.trnsel.ngrpbu; // total number of group
				unsigned char sizeOfGrp = pMSim->sel.non.pm.det.trnsel.gsizbu; // size of each group (in byte)
				unsigned char minSel = pMSim->sel.non.pm.det.trnsel.minbu; // min. number of selection in each group
				unsigned char maxSel = pMSim->sel.non.pm.det.trnsel.maxbu; // max. number of selection in each group

				for(i=0; i<sizeOfGrp; i++)
				{
					m_iCHPSel1 = pTRNGrp->selbu[i]; // champion

					if(m_iCHPSel1 != 0)
					{
						for (j=0;j<=7;j++) {
							x = (unsigned long) pow(2.0,j);
							if((m_iCHPSel1 & x) == x)
							{
								if(i==0 && j==0){}								
								else
								{
									pos = (i*8) + j;  // since i means group number
									m_iFirstArr[k] = pos;
									k++;
								}
							}
						}
					}
				}

				m_iNumSel1 = k;
				k=0;
				pos=0;
				
				pTRNGrp = (struct BETSB_SEL_PM_TRN_GRP *)((char *)pTRNGrp+sizeOfGrp);

				for(i=0; i<sizeOfGrp; i++)
				{
					m_iCHPSel2 = pTRNGrp->selbu[i]; // first runner up

					if(m_iCHPSel2 != 0 )
					{
						for (j=0;j<=7;j++) {
							x = (unsigned long) pow(2.0,j);
							if((m_iCHPSel2 & x) == x)
							{
								if(i==0 && j==0){}
								else
								{
									pos = (i*8) + j;  // since i means group number
									m_iSecArr[k] = pos;
									k++;
								}
							}
						}
					}
				}

				m_iNumSel2 = k;
				
				for(i=0; i<m_iNumSel1; i++)
				{
					m_iGroupNum = 1; // Champion Group
					chpp_sel_no = i+1;
					sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_iNumSel1, chpp_sel_no);
					sprintf(temp2, "~|~0~|~%d~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iFirstArr[i], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp2);	
					SimpleSelection(m_cData);
				}

				for(j=0; j<m_iNumSel2; j++)
				{
					m_iGroupNum = 2; // First Runner Up Group
					chpp_sel_no = j+1;
					sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_iNumSel2, chpp_sel_no);
					sprintf(temp2, "~|~0~|~%d~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iSecArr[j], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp2);	
					SimpleSelection(m_cData);
				}
				
			}

		}
		else if (m_iBetType == BETTYP_SB_EXO) // treble half/full time
		{

			m_iGroupNum = 0;
			m_iLegNo = 1;
			int m_cScore2 = 0;

			if(m_cPool == SB_HFM || m_cPool == SB_THF)			
			{
				int x=0, y=0;
				int m_cScore2=0;
				
				unsigned short m_iThfSel = 0;
				unsigned short ttlThfSel = 0;
				int thf_sel_no = 0;
				int entryLoop = 0;

				if(m_iTotalEntry == 0) // single entry
					entryLoop = 1;
				else
					entryLoop = m_iTotalEntry;

				for(y=0; y<entryLoop; y++)
				{
					for(x=0; x<m_iSimplePool; x++)
					{
						m_iThfSel = 0;
						ttlThfSel = 0;
						char THFSel[10][10];
						
						m_iEntryNo		= y+1;
						m_iLegNo		= x+1;					// leg_no
						//m_cPool			= pMSim->poolbu;		// pool type #
						m_cNoSelection	= pMSim->numbu;			// # of selections
						m_cField2		= pMSim->fld1;			// field indicator
						m_iThfSel		= pMSim->sel.non.pm.det.sel1wu[y]; // selections for this entry

						GetHaFu(m_iThfSel, THFSel, ttlThfSel);

						for(int h=0; h<ttlThfSel; h++)
						{
							thf_sel_no = h+1;
							sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlThfSel, thf_sel_no);
							sprintf(temp2, "~|~0~|~%s~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", THFSel[h], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
							strcat(m_cData, temp2);	

							SimpleSelection(m_cData);
						}

						// L50R1a_benkoo:  since quick pick has two entries, 
						//we need to correct the corresponding position.

						if(m_iTotalEntry == 0) // Single Entry
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+8+sizeof(BETSB_SIMPLE_S)+sizeof(BETSBIND)+2);
						else  // Quick Pick
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+8+sizeof(BETSB_SIMPLE_S)+sizeof(BETSBIND)+(2*m_iTotalEntry));

					}

					pMSim = (struct BETSB_SIMPLE *)pMlog->d.bt.sb.d.bet.bet.var.sb.vbu;
				}

			}
			else if (m_cPool == SB_FINP)
			{
				struct BETSB_SEL_PM_TRN_GRP *pTRNGrp;
				pTRNGrp = (struct BETSB_SEL_PM_TRN_GRP *)pMSim->sel.non.pm.det.trnsel.vbu;

				int qftp_sel_no=0, i=0, j=0, k=0, m=0, pos=0;
				int m_iNumSel=0;
				int bitLen = 8;
				unsigned char m_iFINPArr[SB_MAX_TRN_BUF][100]; //160*64
				unsigned char m_iFINPSel;
				unsigned long x=0;
				m_iEntryNo = 1;

				for(i=0; i<SB_MAX_TRN_BUF; i++)
					memset(m_iFINPArr[i], 0, 100);

				unsigned char numOfGrp = pMSim->sel.non.pm.det.trnsel.ngrpbu; // total number of group
				unsigned char sizeOfGrp = pMSim->sel.non.pm.det.trnsel.gsizbu; // size of each group (in byte)
				unsigned char minSel = pMSim->sel.non.pm.det.trnsel.minbu; // min. number of selection in each group
				unsigned char maxSel = pMSim->sel.non.pm.det.trnsel.maxbu; // max. number of selection in each group
				
				for(i=0; i<numOfGrp; i++)
				{
					for(j=0; j<sizeOfGrp; j++)
					{
						m_iFINPSel = pTRNGrp->selbu[j];

						if(m_iFINPSel != 0)
						{
							for (k=0;k<=7;k++) {
								x = (unsigned long) pow(2.0,k);
								if((m_iFINPSel & x) == x)
								{
									if(j==0 && k==0){}
									else
									{
										pos = (j*8) + k;  // since i means group number
										m_iFINPArr[i][m] = pos;
										m++;
									}
								}
							}
						}
					}
					m=0;
					pTRNGrp = (struct BETSB_SEL_PM_TRN_GRP *)((char *)pTRNGrp+sizeOfGrp);
				}

				for(i=0; i<numOfGrp; i++)
				{
					for(m=0; m<100; m++)
					{
						if(m_iFINPArr[i][m] != 0)
							m_iNumSel++; // total number of selections in EACH group.
					}

					for(j=0; j<m_iNumSel; j++)
					{
						m_iGroupNum = i+1;
						qftp_sel_no = j+1;
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_iNumSel, qftp_sel_no);
						sprintf(temp2, "~|~0~|~%d~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iFINPArr[i][j], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);	
						SimpleSelection(m_cData);
					}
					m_iNumSel=0; // reset to zero, to calculate next group.
				}

			}
			else if (m_cPool == SB_HCSD)	// double half time full time correct score
			{
				int totalLeg = 2;  // Since it is doubled.

				for(int i=0; i<totalLeg; i++)
				{
					m_cNoSelection	= pMSim->numbu;				// # of selections
					m_cField2		= pMSim->fld1;
					unsigned char m_cDay		= pMSim->daybu;			// day of week/round 
																		// or event # for GFTP/group # for GWP
					unsigned char m_cMatch		= pMSim->matchbu;		// match of the day/ league # /tournament #
					__time32_t m_iDate				= pMSim->date;			// match / championship date
					struct tm *matchtime;
					matchtime = _localtime32( &m_iDate);
					m_iYear = 1900+matchtime->tm_year;
					m_iDay	= matchtime->tm_mday;
					sprintf(day, "%d-%s-%d", m_iDay, m_sMonths[matchtime->tm_mon], m_iYear);
					sprintf(time, "%02d:%02d:%02d", matchtime->tm_hour, matchtime->tm_min, matchtime->tm_sec);
					unsigned short m_iHome			= pMSim->info.team.homewu;	// home team #
					unsigned short m_iAway			= pMSim->info.team.awaywu;	// away team #

					unsigned __int64 m_cHalf = 0;
					unsigned __int64 m_cFull = 0;
					memcpy( &m_cHalf, pMSim->sel.non.pm.det.crs.vbu, 5);
					memcpy( &m_cFull, pMSim->sel.non.pm.det.crs.vbu + 5, 5);

					int hcs_sel_no=0;
					STR* HFCombination;
					m_iEntryNo = 1;
					m_iLegNo = i+1;

					GetDHCP(m_cHalf, m_cFull, HFCombination, m_cField2, ttlSel);
					
					int k=0;
					for(k=0; k<ttlSel; k++)
					{
						hcs_sel_no = k+1;
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlSel, hcs_sel_no);
						sprintf(temp2, "~|~0~|~%s~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", HFCombination[k], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);	

						SimpleSelection(m_cData);
					}

					if ( ttlSel == 0 ) {
						hcs_sel_no = k+1;
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlSel, hcs_sel_no);
						sprintf(temp2, "~|~0~|~%s~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", "V:V/V:V", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);	

						SimpleSelection(m_cData);
					}

					pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+7+sizeof(BETSB_SIMPLE_TEAM)+1+sizeof(BETSBIND)+sizeof(BETSB_SEL_PM_CRS2));

					if(HFCombination)
					{
						delete HFCombination;
						HFCombination = 0;
					}
				}
			}

		} // end else if (m_iBetType == BETTYP_SB_EXO)
	}

	if (m_iBetType == BETTYP_SB_AUP_PM				// bettype 22	All-up soccer bet parimutuel
		|| m_iBetType == BETTYP_SB_AUP_FO_CTL		// bettype 23	Controlled fixed odds allup bet
		|| m_iBetType == BETTYP_SB_AUP_FO_NON		// bettype 24	Non-controlled fixed odds allup bet
		|| m_iBetType == BETTYP_SB_SEC_BET)			// bettype 25	Section bet
	{

		m_iGroupNum = 1;

		for (m_iLegNo = 1; m_iLegNo <= m_iSimplePool; m_iLegNo++)
		{
			unsigned char m_cDay		= pMSim->daybu;			// day of week/round
			unsigned char m_cMatch		= pMSim->matchbu;		// match of the day/ league #
			__time32_t m_iDate				= pMSim->date;			// match / championship date
			struct tm *matchtime;
			matchtime = _localtime32( &m_iDate);
			m_iYear = 1900+matchtime->tm_year;
			m_iDay					= matchtime->tm_mday;
			sprintf(day, "%d-%s-%d", m_iDay, m_sMonths[matchtime->tm_mon], m_iYear);
			sprintf(time, "%02d:%02d:%02d", matchtime->tm_hour, matchtime->tm_min, matchtime->tm_sec);
			unsigned char m_cPool		= pMSim->poolbu;		// pool type #
			unsigned char m_cLiveBet	= pMSim->livebu;		// live bet indicator
			unsigned char m_cExtraBet	= pMSim->extrabu;		// extra time bet indicator //q407
			unsigned short m_iHome		= pMSim->info.team.homewu;		// home team #
			unsigned short m_iAway		= pMSim->info.team.awaywu;		// away team #
			unsigned char m_cNoSelection	= pMSim->numbu;			// # of selections
			//unsigned int m_iPayFact			= pMSim->sel.aup.pftrlu;		// pay factor
			unsigned int m_iPayFact			= 0;		// pay factor
			unsigned short m_iFirstBonus	= pMSim->sel.aup.bonuswu;		// bonus % for first level
			unsigned short m_iLevelBonus	= pMSim->sel.aup.levelbonwu;	// per-level bonus % (first one is not used)
			m_cField2		= pMSim->fld1;			// field indicator

			m_iEntryNo = 1;
			
			if (m_iBetType == BETTYP_SB_AUP_FO_CTL || m_iBetType == BETTYP_SB_AUP_FO_NON  || m_iBetType == BETTYP_SB_SEC_BET)
			{
				unsigned char m_cScore;
				unsigned char m_cScore2;

				unsigned short m_corn_cScore;
				unsigned short m_corn_cScore2;

				unsigned char m_cLineSlotNo;   // multiple line
				m_cLineSlotNo =0;
				char m_iHandGoal1;
				char m_iHandGoal2;	
				char m_iNoOfGoal;

				for(int i=0; i<m_cNoSelection; i++)
				{
					selection_no = i+1;
					
//ML2015
					if (m_cPool == SB_OOU || m_cPool == SB_FHLO || m_cPool == SB_CHLO)
					{
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~1~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection);

					}
					else 
					{
						
						sprintf(m_cData,"%d@|@%d~|~%s~|~%d~|~%s~|~1~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d", simSelMsgCode, pMsg->m_iSysNo, pMsg->m_iSysName,  m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, m_iPayFact, m_iFirstBonus, m_iLevelBonus, selection_no);

					}

					if (m_cPool == SB_FGS)
					{
						unsigned char m_iSelNo	= pMSim->sel.aup.sel.fo1[i].selbu;	// player 
						unsigned int m_iOdd		   = pMSim->sel.aup.sel.fo1[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.fo1[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2, "~|~%d~|~%d", m_iOdd, m_iSelNo);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

						if (i == m_cNoSelection-1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+(sizeof(BETSB_ODDS)+3)*m_cNoSelection));
					}
					else if (m_cPool == SB_1X2 || m_cPool == SB_OES || m_cPool == SB_TOS || m_cPool == SB_GPW || m_cPool == SB_FHAD || m_cPool == SB_TQL  || m_cPool==SB_FTS)
					{   //  MAR 2011
						unsigned char m_cSel	= pMSim->sel.aup.sel.fo2[i].selbu;		// selection
						unsigned int m_iOdd		   = pMSim->sel.aup.sel.fo2[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.fo2[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						if(m_cPool == SB_GPW)
							m_iGroupNum = m_cDay;
						
						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

						if (i == m_cNoSelection-1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+(sizeof(BETSB_ODDS)+1)*m_cNoSelection));
					}

// Q408 NTS/ETS
					else if (m_cPool == SB_NTS || m_cPool == SB_ETS )
					{
					
						m_iNoOfGoal	= pMSim->sel.aup.sel.foNts.noofgoal;	// # of goal 


						unsigned char m_cSel	= pMSim->sel.aup.sel.foNts.sel[i].selbu;

						unsigned int m_iOdd		   = pMSim->sel.aup.sel.foNts.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.foNts.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						sprintf(temp3, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2 , m_cExtraBet, m_iNoOfGoal);
						strcat(m_cData, temp3);

						if (i == m_cNoSelection - 1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+1+((sizeof(BETSB_SEL_FO_2))*m_cNoSelection)));
					}


					//  it is the structure of HILO , OOU is outdated. But still using the SB_OOU = SB_HILO
					else if (m_cPool == SB_OOU || m_cPool == SB_FHLO)
					{
						//m_cScore	= pMSim->sel.aup.sel.hilo.goal1;		// score to compared
						//m_cScore2	= pMSim->sel.aup.sel.hilo.goal2;		// score to compared 2


						m_cScore	= pMSim->sel.aup.sel.hilo.sel[i].line1;		// score to compared
						m_cScore2	= pMSim->sel.aup.sel.hilo.sel[i].line2;	// score to compared 2

						
						m_cLineSlotNo = pMSim->sel.aup.sel.hilo.sel[i].lineslot+1; //slot number

						unsigned char m_cSel	= pMSim->sel.aup.sel.hilo.sel[i].selbu;

						unsigned int m_iOdd		   = pMSim->sel.aup.sel.hilo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.hilo.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d", m_cLineSlotNo,selection_no, m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2 , m_cExtraBet);
						strcat(m_cData, temp2);

//  ML2015						if (i == m_cNoSelection - 1)
//							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+3+((sizeof(BETSB_SEL_FO_2))*m_cNoSelection)));

						if (i == m_cNoSelection - 1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+1+((sizeof(BETSB_SEL_FO_2G))*m_cNoSelection)));


					}

					//  CHILO
					else if (m_cPool == SB_CHLO)
					{
						//m_corn_cScore	= pMSim->sel.aup.sel.chlo.goal1;		// score to compared
						//m_corn_cScore2	= pMSim->sel.aup.sel.chlo.goal2;		// score to compared 2


						m_corn_cScore	= pMSim->sel.aup.sel.chlo.sel[i].line1;		// score to compared
						m_corn_cScore2	= pMSim->sel.aup.sel.chlo.sel[i].line2;		// score to compared 2


						m_corn_cScore2 = (m_corn_cScore2 << 6) | ((m_corn_cScore >> 10) & 0x3F);
						m_corn_cScore  = (m_corn_cScore & 0x3FF);

						m_cLineSlotNo = pMSim->sel.aup.sel.chlo.sel[i].lineslot+1; //slot number


						unsigned char m_cSel	= pMSim->sel.aup.sel.chlo.sel[i].selbu;

						unsigned int m_iOdd		   = pMSim->sel.aup.sel.chlo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.chlo.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d", m_cLineSlotNo,selection_no, m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_corn_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_corn_cScore2 , m_cExtraBet);
						strcat(m_cData, temp2);

//	 ML2015					if (i == m_cNoSelection - 1)
//							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+4+((sizeof(BETSB_SEL_FO_2))*m_cNoSelection)));


						if (i == m_cNoSelection - 1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+4+((sizeof(BETSB_SEL_FO_2C))*m_cNoSelection)));

					}
					
					
					//else if (m_cPool == SB_DBR || m_cPool == SB_COS)
					else if (m_cPool == SB_DBR || m_cPool == SB_COS || m_cPool == SB_FCRS) //2012 MAR
					{
						unsigned char m_cSel1	= pMSim->sel.aup.sel.fo3[i].selbu[0];		// selection 1
						unsigned char m_cSel2	= pMSim->sel.aup.sel.fo3[i].selbu[1];
						unsigned int m_iOdd		   = pMSim->sel.aup.sel.fo3[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.fo3[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						if(m_cPool == SB_DBR)
							sprintf(score, "%d-%d", m_cSel1, m_cSel2);
						else
							sprintf(score, "%d:%d", m_cSel1, m_cSel2);

						sprintf(temp2,"~|~%d~|~%s", m_iOdd, score);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

						if (i == m_cNoSelection-1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+(sizeof(BETSB_SEL_FO_3)*m_cNoSelection)));
					}
					else if (m_cPool == SB_HDC || m_cPool == SB_HHAD)
					{
						m_iHandGoal1		= pMSim->sel.aup.sel.foHdc.goal1b;		// handicap goal 1
						m_iHandGoal2		= pMSim->sel.aup.sel.foHdc.goal2b;		// handicap goal 2

						if(m_cPool == SB_HHAD)
							m_iHandGoal2 = 0;

						unsigned char m_iSel	= pMSim->sel.aup.sel.foHdc.sel[i].selbu;
						unsigned int m_iOdd	       = pMSim->sel.aup.sel.foHdc.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.foHdc.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_iSel);
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~0~|~%d~|~%d~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iHandGoal1, m_iHandGoal2, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);

						if (i == m_cNoSelection-1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+2+(sizeof(BETSB_SEL_FO_2)*m_cNoSelection)));
					}
					else if (m_cPool == SB_GPF)
					{
						unsigned char m_cWinSel	= pMSim->sel.aup.sel.fo3[i].selbu[0];
						unsigned char m_cRunSel	= pMSim->sel.aup.sel.fo3[i].selbu[1];

						sprintf(score, "%d,%d", m_cWinSel, m_cRunSel);
					
						unsigned int m_iOdd	       = pMSim->sel.aup.sel.fo3[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.fo3[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						m_iGroupNum = m_cDay;

						sprintf(temp2,"~|~%d~|~%s", m_iOdd, score);
						strcat(m_cData, temp2);
						strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

						if (i == m_cNoSelection-1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+(sizeof(BETSB_SEL_FO_3)*m_cNoSelection)));
					}

					SimpleSelection(m_cData);

				} // end for-loop no_of_selection
			}
			else // pari-mutuel
			{
				// champopn /fgs selection
				unsigned short m_iSel	= pMSim->sel.aup.sel.pm.det.pm1[0].selwu;
				// oes / tos / 1X2 selection
				//unsigned char m_cSel	= pMSim->sel.aup.sel.pm.det.selbu;
				// oou / hdc selection
				char m_cComp			= pMSim->sel.aup.sel.pm.det.sel.compb;	// score to compared [oou] with or handicap goal [hdc]
				//unsigned char m_cSelection1	= pMSim->sel.aup.sel.pm.det.sel.selbu[0];
				//unsigned char m_cSelection2 = pMSim->sel.aup.sel.pm.det.sel.selbu[1];
				// sbr / cos
				unsigned char m_cSel1		= pMSim->sel.aup.sel.pm.det.sel2bu[0][0];
				unsigned char m_cSel2		= pMSim->sel.aup.sel.pm.det.sel2bu[0][1];
			}
		} // end for-loop no_of_Leg
	}

	return buf;
}

void CBSBBet::SimpleSelection(char* smStr)
{
	v_SimSel.push_back(string(smStr));
}

CBSBBet::~CBSBBet() 
{
	if ( m_pSB )
		delete m_pSB;
}

