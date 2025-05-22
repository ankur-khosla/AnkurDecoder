// ABSBBet.cpp: implementation of the ABSBBet class.
//
//////////////////////////////////////////////////////////////////////

#include "ABSBBet.h"
#include <string.h>
#include "betdef.h"
#include <stddef.h>
#include "afmvar.h"
#include "ExtractMgr.h"
#include <math.h>
#include <string>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ABSBBet::ABSBBet() : m_pSB(0)
{}

const int ABSBBet::m_iFlagOffset = 46;
const int ABSBBet::m_iOddFlagOffset = 47;
typedef char* STR;
int selNum = 0;
const int simSelMsgCodeOffSet = 15; // Add the hard string "50015@|@" at first position in "m_cData" below.
string sm;

char * ABSBBet::TranslateAction(const Msg *pMsg)
{
	char m_cFormulaList[70][10];

	sprintf(m_cFormulaList[0],  "2x1" );	// 2X1      No. of events = 2
    sprintf(m_cFormulaList[1],  "2x3" );	// 2X3
    sprintf(m_cFormulaList[2],  "3x1" );	// 3X1      No. of events = 3
    sprintf(m_cFormulaList[3],  "3x3" );	// 3X3
    sprintf(m_cFormulaList[4],  "3x4" );	// 3X4
    sprintf(m_cFormulaList[5],  "3x6" );	// 3X6          
	sprintf(m_cFormulaList[6],  "3x7" );	// 3X7  
	sprintf(m_cFormulaList[7],  "4x1" );	// 4X1      No. of events = 4   
	sprintf(m_cFormulaList[8],  "4x4" );	// 4X4  
	sprintf(m_cFormulaList[9],  "4x5" );	// 4X5   
	sprintf(m_cFormulaList[10], "4x6" );	// 4X6  
	sprintf(m_cFormulaList[11], "4x10");	// 4X10  
	sprintf(m_cFormulaList[12], "4x11");	// 4X11  
	sprintf(m_cFormulaList[13], "4x14");	// 4X14
	sprintf(m_cFormulaList[14], "4x15");	// 4X15  
	sprintf(m_cFormulaList[15], "5x1" );	// 5X1      No. of events = 5   
	sprintf(m_cFormulaList[16], "5x5" );	// 5X5    
	sprintf(m_cFormulaList[17], "5x6" );	// 5X6   
	sprintf(m_cFormulaList[18], "5x10");	// 5X10   
	sprintf(m_cFormulaList[19], "5x15");	// 5X15
	sprintf(m_cFormulaList[20], "5x16");	// 5X16    
	sprintf(m_cFormulaList[21], "5x20");	// 5X20   
	sprintf(m_cFormulaList[22], "5x25");	// 5X25    
	sprintf(m_cFormulaList[23], "5x26");	// 5X26    
	sprintf(m_cFormulaList[24], "5x30");	// 5X30   
	sprintf(m_cFormulaList[25], "5x31");	// 5X31    
	sprintf(m_cFormulaList[26], "6x1" );	// 6X1      No. of events = 6   
	sprintf(m_cFormulaList[27], "6x6" );	// 6X6   
	sprintf(m_cFormulaList[28], "6x7" );	// 6X7  
	sprintf(m_cFormulaList[29], "6x15");	// 6X15  
	sprintf(m_cFormulaList[30], "6x20");	// 6X20   
	sprintf(m_cFormulaList[31], "6x21");	// 6X21   
	sprintf(m_cFormulaList[32], "6x22");	// 6X22    
	sprintf(m_cFormulaList[33], "6x35");	// 6X35    
	sprintf(m_cFormulaList[34], "6x41");	// 6X41    
	sprintf(m_cFormulaList[35], "6x42");	// 6X42	
	sprintf(m_cFormulaList[36], "6x50");	// 6X50  
	sprintf(m_cFormulaList[37], "6x56");	// 6X56   
	sprintf(m_cFormulaList[38], "6x57");	// 6X57   
	sprintf(m_cFormulaList[39], "6x62");	// 6X62  
	sprintf(m_cFormulaList[40], "6x63");	// 6X63  
	sprintf(m_cFormulaList[41], "7x1" );	// 7X1      No. of events = 7    
	sprintf(m_cFormulaList[42], "7x7" );	// 7X7    
	sprintf(m_cFormulaList[43], "7x8" );	// 7X8  
	sprintf(m_cFormulaList[44], "7x21");	// 7X21		
	sprintf(m_cFormulaList[45], "7x28");	// 7X28    
	sprintf(m_cFormulaList[46], "7x29");	// 7X29    
	sprintf(m_cFormulaList[47], "7x35");	// 7X35    
	sprintf(m_cFormulaList[48], "7x56");	// 7X56    
	sprintf(m_cFormulaList[49], "7x63");	// 7X63    
	sprintf(m_cFormulaList[50], "7x64");	// 7X64    
	sprintf(m_cFormulaList[51], "7x70");	// 7X70    
	sprintf(m_cFormulaList[52], "7x91");	// 7X91    
	sprintf(m_cFormulaList[53], "7x98");	// 7X98    
	sprintf(m_cFormulaList[54], "7x99");	// 7X99    
	sprintf(m_cFormulaList[55], "7x112");	// 7X112    
	sprintf(m_cFormulaList[56], "7x119");	// 7X119    
	sprintf(m_cFormulaList[57], "7x120");	// 7X120 	
	sprintf(m_cFormulaList[58], "7x126");	// 7X126    
	sprintf(m_cFormulaList[59], "7x127");	// 7X127
	sprintf(m_cFormulaList[60], "8x1");		// 8X1
	sprintf(m_cFormulaList[61], "8x8");		// 8X8
	sprintf(m_cFormulaList[62], "8x9");		// 8X9
	sprintf(m_cFormulaList[63], "8x28");	// 8X28
	sprintf(m_cFormulaList[64], "8x56");	// 8X56
	sprintf(m_cFormulaList[65], "8x70");	// 8X70
	sprintf(m_cFormulaList[66], "8x247");	// 8X247
	sprintf(m_cFormulaList[67], "8x255");	// 8X255


	
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMSB;
	pMSB = (struct LOGAB *)pMsg->m_cpBuf;

	PackHeader("", pMSB, pMsg);

	int selection_no = 0; // for indicating which selection. 
	m_iLegNo = 1;
	m_iEntryNo = 0;

	// if the ErrorCode !=0, there is an error, and it will not continue to decode
	int ErrPoolCode = pMsg->m_iMsgErrwu;//pMSB->hdr.errorwu;
	if( ErrPoolCode != 0 )
		return (char*)NOT_IMPLEMENTED;

	// Find odd out-date flag (Add on 09-04-2002 by Lawrence Leung)
	////////////////////////////////////////////////////////////////

	if (pMsg->m_cpBuf[m_iOddFlagOffset] == 1)
	{
		sprintf(m_sOddsFlag, "Odds Outdated");
	}
	else if (pMsg->m_cpBuf[m_iOddFlagOffset] == 2)
	{
		sprintf(m_sOddsFlag, "No Odds Req");
	}
	else
	{
		sprintf(m_sOddsFlag, "");
	}

	AddField(STORE_TYPE_STRING, m_sOddsFlag, 0);

	////////////////////////////////////////////////////////////////

//	struct BETDATA *pMSB;
//	pMSB = (struct BETDATA *)m_tBuf;

	unsigned int m_iUnitBet		= pMSB->data.bt.sb.bet.tran.bet.hdr.betinvcomb.flexi.baseinv;		// unit bet
	unsigned int m_iTotalCost	= pMSB->data.bt.sb.bet.tran.bet.hdr.costlu;		// total cost
	__time32_t		 m_iTime = pMSB->data.bt.sb.bet.tran.bet.hdr.sellTime; // pMsg->m_iMsgSellTime; //pMSB->data.bt.sb.bet.tran.bet.hdr.sellTime;	// sell time
	struct tm *newtime;
	newtime = _localtime32( &m_iTime);
	int m_iYear = 1900+newtime->tm_year;
	const char m_cMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int m_iDay					= newtime->tm_mday;
	char day[12];
	sprintf(day, "%d-%s-%d", m_iDay, m_cMonths[newtime->tm_mon], m_iYear);

	char time[9];
	sprintf(time, "%02d:%02d:%02d", newtime->tm_hour, newtime->tm_min, newtime->tm_sec);
	unsigned char m_iBetType	= pMSB->data.bt.sb.bet.tran.bet.hdr.bettypebu;	// bet type

	unsigned int m_iBonusPcent	= pMSB->data.bt.sb.bet.tran.bet.var.sb.sctbonus.bonuspcentwu;// before div-in: bonus % for non-allup after div-in: total bonus in cents
	unsigned int m_iRefund		= pMSB->data.bt.sb.bet.tran.bet.var.sb.refundlu;	// refund in cents
	unsigned char m_iSimplePool	= pMSB->data.bt.sb.bet.tran.bet.var.sb.numbu;		// # of simple pool
	unsigned char m_cFormula	= pMSB->data.bt.sb.bet.tran.bet.var.sb.fmlentbu;		// all-up formula
	unsigned short m_iBonusCent = pMSB->data.bt.sb.bet.tran.bet.var.sb.bonuslu;		// total bonus in cents

	if ( m_iBetType == 25 )
		m_cSetNumber	= pMSB->data.bt.sb.bet.tran.bet.var.sb.sctbonus.sctid.setbu;   // Section Bet set id
	else
		m_cSetNumber = 0;
	m_iReqConfirm	= pMSB->data.bt.sb.bet.rconfirm1;
	m_iUnitBetChg	= pMSB->data.bt.sb.bet.chgubet1;
	m_iIntercept	= pMSB->data.bt.sb.bet.intercept1;
	m_iUserAbort	= pMSB->data.bt.sb.bet.abort1;
	m_iSettle		= pMSB->data.bt.sb.bet.confirm1;
	m_cErrPool		= pMSB->data.bt.sb.bet.err.poolbu;

	GetType(m_iBetType, m_sBetType);

	AddField(m_iBetType, 0);
	AddField(STORE_TYPE_STRING, m_sBetType, 0);
	AddField(m_iBonusPcent, 0);
	AddField(m_iSimplePool, 0);

	if (m_iBetType <= BETTYP_SB_EXO && m_iBetType >= BETTYP_SB_PM)	// Single SB
	{
		m_iTotalEntry = m_cFormula;
		AddField(m_cFormula, 0);
	}
	else if (m_iBetType <= BETTYP_SB_MIX_FO && m_iBetType >= BETTYP_SB_AUP_PM)	// Allup SB
	{
		AddField(STORE_TYPE_STRING, m_cFormulaList[m_cFormula], 0);
		if ( m_cFormula > 60 )
			int a = 1;
	}

	if (m_iBetType == BETTYP_SB_AUP_FO_CTL)
	{
		m_iCtrlFlag = 1;
	}
	else
	{
		m_iCtrlFlag = 0;
	}

	AddField(m_iCtrlFlag, 0);		// Control Flag

	AddField(m_iUnitBet, 0);
	AddField(m_iTotalCost, 0);
	AddField(m_iBonusCent, 0);

	AddField(STORE_TYPE_STRING, time, 0);

	char temp2[200];
	char score[10];
	char temp3[100];
	m_cField2 = 0; // for simple_selection table
	sprintf(temp3, "%s", "");

	struct BETSB_SIMPLE *pMSim;
	pMSim = (struct BETSB_SIMPLE *)pMSB->data.bt.sb.bet.tran.bet.var.sb.vbu;

	m_cField = pMSim->fld1;	// field indicator (added on stage-2)

	m_iRandGen = 0;
	if(m_iBetType == BETTYP_SB_PM)
	{
		m_iRandGen = pMSim->sel.non.pm.ind.rand1;
	}
	else if(m_iBetType == BETTYP_SB_AUP_PM)
	{
		m_iRandGen = pMSim->sel.aup.sel.pm.ind.rand1;
	}

	AddField(m_cField, 0);
	AddField(m_iRandGen, 0);  // random generator (added on stage 2)

	// Add in M7D
	AddField(m_cSetNumber, 0);   
	AddField(m_iReqConfirm, 0);
	AddField(m_iUnitBetChg, 0); 
	if ( m_iIntercept !=0 ) {
		if ( (pMSB->data.bt.sb.bet.settle1 == 1) && (pMSB->data.bt.sb.bet.rconfirm1 != 1))
			m_iIntercept = 0;
		else
			m_iIntercept = m_iIntercept;
	}
	AddField(m_iIntercept, 0);
	AddField(m_iUserAbort, 0);
	AddField(m_iSettle, 0);
	AddField(m_cErrPool, 0);

	// Add in Q405
	unsigned __int64 m_iTotalPayout		= pMSB->data.bt.sb.bet.tran.bet.hdr.totdu; 
	unsigned int m_iForfeitFlag 	    = pMSB->data.bt.sb.bet.tran.bet.hdr.sts.forfeitfl;
	AddField64(m_iTotalPayout, 0);
	AddField(m_iForfeitFlag, 0);


	// L51_R0_BenKoo_2
	// added on 29-Mar-2004, by Ben Koo
	// if the pool is NOT SPC, the date default will be 01-01-1900
	sprintf(m_sSpcCreateDate, "");
	int simSelMsgCode = LOGAB_CODE_SIMPLE_SEL;

	if (m_iBetType	== BETTYP_SB_PM				//bettype 19	Pari-mutuel collated soccer bet
		|| m_iBetType == BETTYP_SB_FO			// bettype 20	Fix-odds collated soccer bet
		|| m_iBetType == BETTYP_SB_EXO )		// bettype 21	Exotic soccer bet
	{
		unsigned char m_cDay		= pMSim->daybu;			// day of week/round
		unsigned char m_cMatch		= pMSim->matchbu;		// match of the day/ league #
		__time32_t m_iDate				= pMSim->date;			// match / championship date
		struct tm *matchtime;
		matchtime = _localtime32( &m_iDate);
		m_iYear = 1900+matchtime->tm_year;
		m_iDay					= matchtime->tm_mday;
		sprintf(day, "%d-%s-%d", m_iDay, m_cMonths[matchtime->tm_mon], m_iYear);
		sprintf(time, "%02d:%02d:%02d", matchtime->tm_hour, matchtime->tm_min, matchtime->tm_sec);
		unsigned char m_cPool		= pMSim->poolbu;		// pool type #
		unsigned char m_cLiveBet	= pMSim->livebu;		// live bet indicator
		unsigned char m_cExtraBet	= pMSim->extrabu;		// extra time bet indicator //q407
		unsigned short m_iHome		= pMSim->info.team.homewu;		// home team #
		unsigned short m_iAway		= pMSim->info.team.awaywu;		// away team #
		unsigned char m_cNoSelection	= pMSim->numbu;			// # of selections

		if (m_iBetType == BETTYP_SB_FO) // fixed odd
		{
			unsigned char m_cScore;
			unsigned char m_cScore2;


			unsigned short m_corn_cScore;
			unsigned short m_corn_cScore2;

			unsigned int m_cLineSlotNo;   // multiple line


			m_cScore2 = 0;
			m_corn_cScore2 = 0;
			m_cLineSlotNo =0;

			char m_iHandGoal1;
			char m_iHandGoal2;
			char m_iNoOfGoal;

			m_cField2 = pMSim->fld1;
			m_iEntryNo = 1;
			m_iGroupNum = 0;

			int spc_ttl_item = m_iSimplePool; // total number of selected Item(s)
			int k =0;

			//L51_R0_BenKoo_2
			if(m_cPool == SB_SPC_MATCH || m_cPool == SB_SPC_TRN)
			{
				for(k=0; k < spc_ttl_item; k++)
				{
					m_cDay			= pMSim->daybu;   // item no
					m_cMatch		= pMSim->matchbu; // special pool type no	
					m_cNoSelection	= pMSim->numbu;	  // no. of selections

					m_iEntryNo = k+1; // for muti-items selected
					
					int i=0;
					for(i=0; i<m_cNoSelection; i++)
					{
						selection_no = i+1;  // for muti-selections

						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d",simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);

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
						sprintf(m_sSpcCreateDate, "%d-%s-%d", m_iSPCDay, m_cMonths[spctime->tm_mon], m_iSPCYear);

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
//					sprintf(m_cData,"%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);

					
//		CT - 2015ML



					if (m_cPool == SB_OOU || m_cPool == SB_FHLO || m_cPool == SB_CHLO) 
					{

										sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d",simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection);
					}
					else
					{
					
										sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~1~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);
					
					}

//		end CT - 2015ML 
					if (m_cPool == SB_FGS)
					{
						unsigned char m_iSelNo	= pMSim->sel.non.fo1[i].selbu;	// team # [champion] / player 
						unsigned int m_iOdd		= pMSim->sel.non.fo1[i].odds.value14;	// odds * 20
						unsigned short m_iOddMulti = pMSim->sel.non.fo1[i].odds.chkdigit2;		// New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}
						
						sprintf(temp2, "~|~%d~|~%d", m_iOdd, m_iSelNo);
						strcat(m_cData, temp2);
// ???						//strcat(m_cData, "~|~0~|~0~|~0");
						sprintf(temp3, "~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);
					}
					else if (m_cPool == SB_1X2 || m_cPool == SB_OES || m_cPool == SB_TOS || m_cPool == SB_FHAD || m_cPool == SB_TQL||m_cPool == SB_FTS)
					{	// MAR2011
						unsigned int m_iOdd		   = pMSim->sel.non.fo2[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.fo2[i].odds.chkdigit2; // New Odds structure

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						unsigned char m_cSel	= pMSim->sel.non.fo2[i].selbu;		// selecion
					
						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						
						sprintf(temp3, "~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp3);

					}
					else if (m_cPool == SB_OOU || m_cPool == SB_FHLO)   //L2.23 R0  support FHLO
					{
						
						m_cScore	= pMSim->sel.non.hilo.sel[i].line1;		// handicap goal [1]
						m_cScore2	= pMSim->sel.non.hilo.sel[i].line2;		// handicap goal [2]
						m_cLineSlotNo =  pMSim->sel.non.hilo.sel[i].lineslot+1;  // line slot#



						//m_cScore	= pMSim->sel.non.hilo.goal1;		// score to compared
						//m_cScore2	= pMSim->sel.non.hilo.goal2;		// score to compared
						unsigned int m_iOdd		   = pMSim->sel.non.hilo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.hilo.sel[i].odds.chkdigit2;
						unsigned char m_cSel	= pMSim->sel.non.hilo.sel[i].selbu;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}
						
						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d", m_cLineSlotNo,selection_no, m_iOdd, m_cSel);   //CT - 2015ML
						strcat(m_cData, temp2);
						//sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d\n", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet );
						strcat(m_cData, temp2);
					}



					else if (m_cPool == SB_CHLO)   //L2.29 R0  support CHLO
					{


						m_corn_cScore	= pMSim->sel.non.chlo.sel[i].line1;		// handicap goal [1]
						m_corn_cScore2	= pMSim->sel.non.chlo.sel[i].line2;		// handicap goal [2]

						
						m_corn_cScore2 = (m_corn_cScore2 << 6) | ((m_corn_cScore >> 10) & 0x3F);
						m_corn_cScore  = (m_corn_cScore & 0x3FF);

						m_cLineSlotNo =  pMSim->sel.non.chlo.sel[i].lineslot+1;  // line slot#
//						m_corn_cScore	= pMSim->sel.non.chlo.goal1;		// score to compared
//						m_corn_cScore2	= pMSim->sel.non.chlo.goal2;		// score to compared
						unsigned int m_iOdd		   = pMSim->sel.non.chlo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.chlo.sel[i].odds.chkdigit2;
						unsigned char m_cSel	= pMSim->sel.non.chlo.sel[i].selbu;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}
						
						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d", m_cLineSlotNo,selection_no, m_iOdd, m_cSel);   //CT - 2015ML
						strcat(m_cData, temp2);
						//sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d\n", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_corn_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_corn_cScore2, m_cExtraBet );
						strcat(m_cData, temp2);
					}



// Q408 support NTS, ETS
					else if (m_cPool == SB_NTS || m_cPool == SB_ETS)
					{
						m_iNoOfGoal	= pMSim->sel.non.foNts.noofgoal;
						
						unsigned int m_iOdd		   = pMSim->sel.non.foNts.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.non.foNts.sel[i].odds.chkdigit2;
						unsigned char m_cSel	= pMSim->sel.non.foNts.sel[i].selbu;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}
						
						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						//sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d\n", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet, m_iNoOfGoal );
						strcat(m_cData, temp2);
					}




					//else if (m_cPool == SB_DBR || m_cPool == SB_COS || m_cPool == SB_GPF) //L51_R0_BenKoo_2
					else if (m_cPool == SB_DBR || m_cPool == SB_COS || m_cPool == SB_GPF || m_cPool == SB_FCRS) //2012MAR
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
						else if(m_cPool == SB_FCRS)// 2012MAR
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
					else if (m_cPool == SB_CHP || m_cPool == SB_GPW || m_cPool == SB_TPS) //L51_R0_BenKoo_2		 
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

				} // end for-loop
			} // end if
		}
		else if (m_iBetType == BETTYP_SB_PM)// pari-mutuel
		{
			unsigned char m_cScore;
			unsigned char m_cScore2;
			//unsigned short m_corn_cScore;
		//	unsigned short m_corn_cScore2;


			m_cScore2=0;
			//m_corn_cScore2=0;
			m_cField2 = pMSim->fld1;
			m_iEntryNo = 1;
			m_iGroupNum = 0;
			m_iLegNo = 1;

			//if(m_cPool == SB_FGS || m_cPool == SB_COS)
			if(m_cPool == SB_FGS || m_cPool == SB_COS || m_cPool == SB_FCRS) // 2012MAR
			{
				for(int i=0; i<m_cNoSelection; i++)
				{
					selection_no = i+1;

					sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, selection_no);




					if (m_cPool == SB_FGS)
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
					else if (m_cPool == SB_FCRS) // 2012MAR
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
				
				if(m_cPool == SB_1X2 || m_cPool == SB_FHAD || m_cPool == SB_TQL)
					HADBitmap(m_cSel, sel, ttl);
				else if(m_cPool == SB_OES)
					OESBitmap(m_cSel, sel, ttl);
				else if(m_cPool == SB_TOS)
					TOSBitmap(m_cSel, sel, ttl);

				for(i=0; i<ttl; i++)
				{
					s_no = i+1;
					sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttl, s_no);
					sprintf(temp2, "~|~0~|~%s", sel[i]);
					strcat(m_cData, temp2);
					strcat(m_cData, "~|~0~|~0~|~0");
					sprintf(temp3, "~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp3);

					SimpleSelection(m_cData);
				}
			}
			else if (m_cPool == SB_OOU || m_cPool == SB_FHLO|| m_cPool == SB_CHLO || m_cPool == SB_HDC || m_cPool == SB_HHAD  || m_cPool == SB_CHLO)
			{
				m_cScore = pMSim->sel.non.pm.det.sel.compb;
				unsigned char m_cSel = pMSim->sel.non.pm.det.sel.selbu;

				char sel[10];
				int ttl=0, s_no=0, i=0;
				
				if (m_cPool == SB_OOU || m_cPool == SB_FHLO || m_cPool == SB_CHLO)
				{
					OOUBitmap(m_cSel, sel, ttl);

					for(i=0; i<ttl; i++)
					{
						s_no = i+1;
						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttl, s_no);
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
						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttl, s_no);
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

				GetHaFu(m_iHafuSel, HafuSel, ttlHafuSel);

				for(int h=0; h<ttlHafuSel; h++)
				{
					hafu_sel_no = h+1;
					sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlHafuSel, hafu_sel_no);
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
				
				GetHCS(m_iHalf, m_iFull, HFCombination, ttlSel);

				unsigned int chkHalfField = m_iHalf;
				unsigned int chkFullField = m_iFull;
			
				for(int k=0; k<ttlSel; k++)
				{
					hcs_sel_no = k+1;
					sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlSel, hcs_sel_no);
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
					sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_iNumSel1, chpp_sel_no);
					sprintf(temp2, "~|~0~|~%d~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iFirstArr[i], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp2);	
					SimpleSelection(m_cData);
				}

				for(j=0; j<m_iNumSel2; j++)
				{
					m_iGroupNum = 2; // First Runner Up Group
					chpp_sel_no = j+1;
					sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_iNumSel1, chpp_sel_no);
					sprintf(temp2, "~|~0~|~%d~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iSecArr[j], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
					strcat(m_cData, temp2);	
					SimpleSelection(m_cData);
				}
				
			}

		}
		else if (m_iBetType == BETTYP_SB_EXO )		// bettype 21	Exotic soccer bet
		{
			m_iGroupNum = 0;
			m_iLegNo = 1;
			int m_cScore2 = 0;

			if(m_cPool == SB_HFM || m_cPool == SB_THF)			
			{
				int x=0, y=0;
				
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
						
						m_iEntryNo		= y+1;					// entry no
						m_iLegNo		= x+1;					// leg_no
						//m_cPool			= pMSim->poolbu;		// pool type #
						m_cNoSelection	= pMSim->numbu;			// # of selections
						m_cField2		= pMSim->fld1;			// field indicator
						m_iThfSel		= pMSim->sel.non.pm.det.sel1wu[y]; // selections for this entry

						GetHaFu(m_iThfSel, THFSel, ttlThfSel);

						for(int h=0; h<ttlThfSel; h++)
						{
							thf_sel_no = h+1;
							sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlThfSel, thf_sel_no);
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

					pMSim = (struct BETSB_SIMPLE *)pMSB->data.bt.sb.bet.tran.bet.var.sb.vbu;
				}

			}
			else if (m_cPool == SB_FINP) // L50R0_BK03 -- Implement new pool types
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
						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~1~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_iNumSel, qftp_sel_no);
						sprintf(temp2, "~|~0~|~%d~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_iFINPArr[i][j], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet);
						strcat(m_cData, temp2);	
						SimpleSelection(m_cData);
					}
					m_iNumSel=0; // reset to zero, to calculate next group.
				}

			}
			else if (m_cPool == SB_HCSD) // L50R0_BK04 -- Implement new pool types
			{
				int m_cScore2 = 0;
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
					sprintf(day, "%d-%s-%d", m_iDay, m_cMonths[matchtime->tm_mon], m_iYear);
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
						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlSel, hcs_sel_no);
						sprintf(temp2, "~|~0~|~%s~|~0~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", HFCombination[k], m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet	);
						strcat(m_cData, temp2);	

						SimpleSelection(m_cData);
					}

					if ( ttlSel == 0 ) {
						hcs_sel_no = k+1;
						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~0~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~0~|~0~|~0~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, ttlSel, hcs_sel_no);
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
		}
	}

	if (m_iBetType == BETTYP_SB_AUP_PM				// bettype 22	All-up soccer bet parimutuel
		|| m_iBetType == BETTYP_SB_AUP_FO_CTL		// bettype 23	Controlled fixed odds allup bet
		|| m_iBetType == BETTYP_SB_AUP_FO_NON		// bettype 24	Non-controlled fixed odds allup bet
		|| m_iBetType == BETTYP_SB_SCT_FO )			// bettype 25	section bet      PN03
	{

		m_iGroupNum = 0;

		for (m_iLegNo = 1; m_iLegNo <= m_iSimplePool; m_iLegNo++)
		{
			unsigned char m_cDay		= pMSim->daybu;			// day of week/round
			unsigned char m_cMatch		= pMSim->matchbu;		// match of the day/ league #
			__time32_t m_iDate				= pMSim->date;			// match / championship date
			struct tm *matchtime;
			matchtime = _localtime32( &m_iDate);
			m_iYear = 1900+matchtime->tm_year;
			m_iDay					= matchtime->tm_mday;
			sprintf(day, "%d-%s-%d", m_iDay, m_cMonths[matchtime->tm_mon], m_iYear);
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
			m_cField2 = pMSim->fld1;

			if (m_iBetType == BETTYP_SB_AUP_FO_CTL || 
				m_iBetType == BETTYP_SB_AUP_FO_NON || 
				m_iBetType == BETTYP_SB_SCT_FO )
			{
				unsigned char m_cScore;
				unsigned char m_cScore2;


				unsigned short m_corn_cScore;
				unsigned short m_corn_cScore2;

				unsigned char m_cLineSlotNo;   // multiple line

				m_cScore2=0;
				m_corn_cScore2=0;

				m_cLineSlotNo =0;

				char m_iHandGoal1;
				char m_iHandGoal2;
				char m_iNoOfGoal;
		

				m_iEntryNo = 1;
				
				for(int i=0; i<m_cNoSelection; i++)
				{
					selection_no = i+1;

//					sprintf(m_cData,"%s~|~%d~|~%s~|~1~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d", m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, m_iPayFact, m_iFirstBonus, m_iLevelBonus, selection_no);



//		CT - 2015ML



					if (m_cPool == SB_OOU || m_cPool == SB_FHLO || m_cPool == SB_CHLO) 
					{

							sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~1~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection);
					}
					else
					{
					
						
						sprintf(m_cData,"%d@|@%s~|~%d~|~%s~|~1~|~%d~|~%d~|~%d~|~%s~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d~|~%d", simSelMsgCode, m_sSysName, m_iLoggerMsgOrderNo, m_sSellingDate, m_iEntryNo, m_iLegNo, m_cDay, day, m_cMatch, m_sBetType, m_cPool, m_iHome, m_iAway, m_cNoSelection, m_iPayFact, m_iFirstBonus, m_iLevelBonus, selection_no);
					}

//		end CT - 2015ML 



					if (m_cPool == SB_FGS)
					{
						unsigned char m_iSelNo	= pMSim->sel.aup.sel.fo1[i].selbu;	// team # [champion] / player 
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
					else if (m_cPool == SB_1X2 || m_cPool == SB_OES || m_cPool == SB_TOS || m_cPool == SB_GPW || m_cPool == SB_FHAD || m_cPool == SB_TQL||m_cPool == SB_FTS)
					{		// MAR 2011
						unsigned char m_cSel	= pMSim->sel.aup.sel.fo2[i].selbu;		// selecton
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

// Q408 -- 
					else if (m_cPool == SB_NTS || m_cPool == SB_ETS)
					{

						m_iNoOfGoal	= pMSim->sel.aup.sel.foNts.noofgoal;
						
						unsigned char m_cSel	= pMSim->sel.aup.sel.foNts.sel[i].selbu;
						unsigned int m_iOdd		   = pMSim->sel.aup.sel.foNts.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.foNts.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~%d", m_iOdd, m_cSel);
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~%d", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet, m_iNoOfGoal ); 
						strcat(m_cData, temp2);

						if (i == m_cNoSelection - 1)
							pMSim = (struct BETSB_SIMPLE *)((char *) pMSim + ( 8 + sizeof(BETSB_SIMPLE_S)+8+1+(sizeof(BETSB_SEL_FO_2))*m_cNoSelection) );

					}

					else if (m_cPool == SB_OOU || m_cPool == SB_FHLO)
					{


						m_cScore	= pMSim->sel.aup.sel.hilo.sel[i].line1;		// handicap goal [1]
						m_cScore2	= pMSim->sel.aup.sel.hilo.sel[i].line2;		// handicap goal [2]
						m_cLineSlotNo =  pMSim->sel.aup.sel.hilo.sel[i].lineslot+1;  // line slot#
						
						unsigned char m_cSel	= pMSim->sel.aup.sel.hilo.sel[i].selbu;
						unsigned int m_iOdd		   = pMSim->sel.aup.sel.hilo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.hilo.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d",  m_cLineSlotNo,selection_no,m_iOdd, m_cSel);  //CT - 2015ML
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_cScore2, m_cExtraBet ); // score2
						strcat(m_cData, temp2);

						// L42R1b_BK1 - fix the problem on selections.
//						if (i == m_cNoSelection - 1)
//							pMSim = (struct BETSB_SIMPLE *)((char *) pMSim + ( 8 + sizeof(BETSB_SIMPLE_S)+8+3+(sizeof(BETSB_SEL_FO_2))*m_cNoSelection) );

						if (i == m_cNoSelection - 1)
							pMSim = (struct BETSB_SIMPLE *)((char *) pMSim + ( 8 + sizeof(BETSB_SIMPLE_S)+8+1+(sizeof(BETSB_SEL_FO_2G))*m_cNoSelection) );



					}
					

					
					else if (m_cPool == SB_CHLO )
					{

						m_corn_cScore	= pMSim->sel.aup.sel.chlo.sel[i].line1;		// score to compared
						m_corn_cScore2   = pMSim->sel.aup.sel.chlo.sel[i].line2;		// score to compared


						m_corn_cScore2 = (m_corn_cScore2 << 6) | ((m_corn_cScore >> 10) & 0x3F);
						m_corn_cScore  = (m_corn_cScore & 0x3FF);


						m_cLineSlotNo =  pMSim->sel.aup.sel.chlo.sel[i].lineslot+1;  // line slot#

						unsigned char m_cSel	= pMSim->sel.aup.sel.chlo.sel[i].selbu;
						unsigned int m_iOdd		   = pMSim->sel.aup.sel.chlo.sel[i].odds.value14;
						unsigned short m_iOddMulti = pMSim->sel.aup.sel.chlo.sel[i].odds.chkdigit2;

						if ( m_iOddMulti <= 2 ) {
							m_iOdd = (unsigned short) pow(10.0, m_iOddMulti) *m_iOdd;
							m_iOdd = m_iOdd * 10;
						}

						sprintf(temp2,"~|~%d~|~0~|~0~|~%d~|~%d~|~%d",  m_cLineSlotNo,selection_no,m_iOdd, m_cSel);  //CT - 2015ML
						strcat(m_cData, temp2);
						sprintf(temp2, "~|~%d~|~0~|~0~|~%d~|~%d~|~%s~|~%d~|~%d~|~%d~|~0", m_corn_cScore, m_cField2, m_iGroupNum, m_sSpcCreateDate, m_cLiveBet, m_corn_cScore2, m_cExtraBet ); // score2
						strcat(m_cData, temp2);

						// L42R1b_BK1 - fix the problem on selections.
						if (i == m_cNoSelection - 1)
							pMSim = (struct BETSB_SIMPLE *)((char *) pMSim + ( 8 + sizeof(BETSB_SIMPLE_S)+8+4+(sizeof(BETSB_SEL_FO_2C))*m_cNoSelection) );

					}
					
					



					//else if (m_cPool == SB_DBR || m_cPool == SB_COS) 
					else if (m_cPool == SB_DBR || m_cPool == SB_COS || m_cPool == SB_FCRS)// 2012 MAR
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

						if (i == m_cNoSelection -1)
							pMSim = (struct BETSB_SIMPLE *)((char *)pMSim+(8+sizeof(BETSB_SIMPLE_S)+8+2+(sizeof(BETSB_SEL_FO_2)*m_cNoSelection)));
					}
					else if (m_cPool == SB_GPF) // L50R0_BK05 -- Implement new pool types
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

	
	int m_iCrossSell = pMSB->data.bt.sb.bet.crossSellFl;
	AddField(m_iCrossSell, 0);

	// Anonymous Account (2011IBT)
	m_iAnonymous = pMSB->hdr.anonymous1;  
	AddField(m_iAnonymous, 0);					

	// Transaction with CSC Card (201108PSR)
	m_iCscCard = pMSB->data.bt.sb.bet.tran.csctrn;
	AddField(m_iCscCard , 0);					

	/*strcat(buf,"$|$");
	strcat(buf, sm.c_str());*/
	
	//fclose(fp);
	return buf;


}

void ABSBBet::SimpleSelection(char* smStr)
{
	//char * simSel = new char[MSG_SIZE];//generate new address every time
	//memset(simSel,0,MSG_SIZE);
	//memcpy(simSel,smStr,strlen(smStr));

	v_SimSel.push_back(string(smStr));
	//delete simSel;

}


ABSBBet::~ABSBBet()
{
	if ( m_pSB )
		delete m_pSB;
}

void ABSBBet::GetHCS(unsigned int half, unsigned int full, char**& HFCombination, int& total_sel)
{
	char halfArray[32];
	char fullArray[32];
	char HScoreArray[32][10];
	char FScoreArray[32][10];
	char m_sHScore[20];
	char m_sFScore[20];
	int i=0, j=0, k=0, halfLen=0, fullLen=0, len=0, pos=0, y=0;
	char tmpScore[10];
	HFCombination = new STR[400];
	bool isField = false;
	sprintf(HScoreArray[i], "%s", "");
	sprintf(FScoreArray[i], "%s", "");
	
	// find the set-bit position(s) of Half-Time
	Dec2Binary(half, halfArray);

	for(i=0; i<32; i++)
	{
		
		if(halfArray[0] == '1')
			isField = true;

		if(isField)
		{
			for(y=0; y<28; y++)
			{
				pos = y;
				CalScore(pos, m_sHScore);
				sprintf(HScoreArray[j], "%s", m_sHScore);
				j++;
			}
			break;
		}
		else
		{
			if(halfArray[i] == '1')
			{
				pos = 31-i;
				CalScore(pos, m_sHScore);
				sprintf(HScoreArray[j], "%s", m_sHScore);
				j++;
			}
		}	
	}

	if(isField)
		halfLen = 28;
	else
		halfLen = j;

	// find the set-bit position(s) of Full-Time
	isField = false;
	j=0;
	y=0;

	Dec2Binary(full, fullArray);

	for(i=0; i<32; i++)
	{
		if(fullArray[0] == '1')
			isField = true;	

		if(isField)
		{
			for(y=0; y<28; y++)
			{
				pos = y;
				CalScore(pos, m_sFScore);
				sprintf(FScoreArray[j], "%s", m_sFScore);
				j++;
			}
			break;
		}
		else
		{
			if(fullArray[i] == '1')
			{
				pos = 31-i;
				CalScore(pos, m_sFScore);
				sprintf(FScoreArray[j], "%s", m_sFScore);
				j++;
			}
		}
	}

	if(isField)
		fullLen = 28;
	else 
		fullLen = j;


char* pHdest;
char* pFdest;
int resultH, resultF;
int ihalfhome, ifullhome, ihalfaway, ifullaway;
bool printflag1 = false;
bool printflag2 = false;
char cHalfhome, cHalfaway, cFullhome, cFullaway;
char tHalfhome[3];
char tHalfaway[3];
char tFullhome[3];
char tFullaway[3];

	for(i=0; i<halfLen; i++)
	{
		for(j=0; j<fullLen; j++)
		{
			printflag1 = false;
			printflag2 = false;

			pHdest = strchr( HScoreArray[i], ':' );
		    resultH = pHdest - HScoreArray[i];

			pFdest = strchr( FScoreArray[j], ':' );
		    resultF = pFdest - FScoreArray[j];

			if(resultH == 1)
			{
				cHalfhome = HScoreArray[i][0];				
				sprintf(tHalfhome, "%c", cHalfhome);
				ihalfhome = atoi(tHalfhome);

				cHalfaway = HScoreArray[i][strlen(HScoreArray[i])-1];
				sprintf(tHalfaway, "%c", cHalfaway);
				ihalfaway = atoi(tHalfaway);
			}
			else
			{
				printflag1 = true;
			}

			if(resultF == 1)
			{
				cFullhome = FScoreArray[j][0];				
				sprintf(tFullhome, "%c", cFullhome);
				ifullhome = atoi(tFullhome);

				cFullaway = FScoreArray[j][strlen(FScoreArray[j])-1];
				sprintf(tFullaway, "%c", cFullaway);
				ifullaway = atoi(tFullaway);
			}
			else
			{
				printflag1 = true;
			}
			
			if(!printflag1)
			{
				if((ihalfhome <= ifullhome) && (ihalfaway <= ifullaway))
					printflag2 = true;
			}

			if(resultH > 1 && resultF == 1)
				printflag1 = false;

			if(printflag1 || printflag2)
			{
				sprintf(tmpScore, "%s/%s", HScoreArray[i], FScoreArray[j]);
				HFCombination[k] = strdup(tmpScore);
				k++;
				if(k == 15)
					k=15;
			}
		}
	}

	total_sel = k;
	
}

char* ABSBBet::Dec2Binary(unsigned int decimal, char* BArray) {
	
	int i, y;
	unsigned int x;
	char z[2];

	sprintf(BArray, "%s", "");
	memset(z,0,sizeof(z));
	for (i=31;i>=0;i--) {
		x = (unsigned int) pow(2.0,i);
		y = ((decimal & x) == x) ? 1: 0;
		sprintf(z, "%u", y);
		strcat(BArray, z) ;
	}

	BArray[32] = '\0';

	return BArray;
}


/*
char* ABSBBet::Dec2Binary(unsigned int decimal, char* BArray)
{
	unsigned int remainder = 0;
	unsigned int dividend = 0;
	int len = 0, i = 0, j = 0;
	char tmpArray[128];
	char sRemainder[2];

	sprintf(tmpArray, "%s", "");
	sprintf(BArray, "%s", "");

	dividend = decimal;

	while (dividend > 1)
	{
		remainder = dividend%2;
		dividend = dividend/2;
		_itoa(remainder, sRemainder, 10);
		strcat(tmpArray, sRemainder);
	}
	_itoa(dividend, sRemainder, 10);
	strcat(tmpArray, sRemainder);

	len = strlen(tmpArray);

	sprintf(BArray, "%s", "");

	int diff = 32-len;

	for(i=0; i<diff; i++)
		strcat(BArray, "0");

	for(j=i; j<32; j++)
		BArray[j] = tmpArray[31-j];

	BArray[32] = '\0';

	return BArray;
}
*/
char* ABSBBet::CalScore(int position, char* score)
{
	int away_score=0;

	sprintf(score, "%s", "");

	if(position >= 0 && position <=4)
	{
		away_score = position - 0;
		sprintf(score, "0:%d", away_score);
	}
	else if(position >= 5 && position <=9)
	{
		away_score = position - 5;
		sprintf(score, "1:%d", away_score);
	}
	else if(position >= 10 && position <=14)
	{
		away_score = position - 10;
		sprintf(score, "2:%d", away_score);
	}
	else if(position >= 15 && position <=19)
	{
		away_score = position - 15;
		sprintf(score, "3:%d", away_score);
	}
	else if(position >= 20 && position <=24)
	{
		away_score = position - 20;
		sprintf(score, "4:%d", away_score);
	}
	else if(position == 25) // home other
	{
		sprintf(score, "%s", "255:0");
	}
	else if(position == 26) // away other
	{
		sprintf(score, "%s", "255:1");
	}
	else if(position == 27) // draw other
	{	
		sprintf(score, "%s", "255:2");
	}
	else if(position == 31)
	{
		sprintf(score, "%s", "F");
	}

		return score;
}


int ABSBBet::GetTotalSel()
{
	return ttlSel;
}

void ABSBBet::SetTotalSel(int ttlCom)
{
	ttlSel = ttlCom;
}

char* ABSBBet::GetType(int m_iBetType, char m_sBetType[20])
{
	switch(m_iBetType)
	{
	case 19:
		sprintf(m_sBetType, "SB_PM");
		break;

	case 20:
		sprintf(m_sBetType, "SB_FO");
		break;

	case 21:
		sprintf(m_sBetType, "SB_EXO");
		break;

	case 22:
		sprintf(m_sBetType, "SB_AUP_PM");
		break;

	case 23:
		sprintf(m_sBetType, "SB_AUP_FO_CTL");
		break;

	case 24:
		sprintf(m_sBetType, "SB_AUP_FO_NON");
		break;

	case 25:
		sprintf(m_sBetType, "SB_SEC_BET");
		break;

	default:
		sprintf(m_sBetType, "NOT_SB");
		break;
	}
	
	return (m_sBetType);
}