////////////////////////////////////////////////////////////////////
//
// CBLottery.cpp: implementation of the CBLottery class.
//
/////////////////////////////////////////////////////////////////////
#include <string.h>
#include "LOGDEF.h"
#include "CBLottery.h"
#include "LOGRDCDEF.h"

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBLottery::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	/*
	if((iRetVal=TranslateHeader(pMsg))!=NO_TRANSLATE_ERR)
	{
		return iRetVal;
	}
	*/

	struct LOG *pMlog;
	pMlog					= (struct LOG *)pMsg->m_cpBuf;
	
	PackHeader("cb_lottery_insert_sp", pMlog, pMsg);

	union TSN tsn = pMlog->d.bt.lot.tsn; // new tsn

	m_cNewTsnFlag = tsnVersionwu(&tsn); // tsn version
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no

	if ( m_cNewTsnFlag == TSN_OLTP ) // new 19 digit tsn
	{
		m_iHighRecNo			= pMlog->d.bt.lot.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocation				= pMlog->d.bt.lot.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.bt.lot.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.bt.lot.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iLocation = 0; // No location concept.
		m_iMeetingDayOfYear = 0; // No meeting concept.

		m_iHighRecNo			= tsnBetTypebu(tsn);		// high order bits of record no
		m_iLowRecNo				= pMsg->m_iMsgTktid; //tsn19NTicketIDdu(tsn);		// low order bits of record no
	}


	m_iFileNo				= pMlog->d.bt.lot.nomuldr;				// file no; change "filewu" -> "nomuldr"
	m_iLottIndex			= pMlog->d.bt.lot.lotidxwu;				// lottery index
	m_iDrawYear				= pMlog->d.bt.lot.yearwu;				// draw year
	m_iDrawYear = m_iDrawYear + 1900;
	if (m_iDrawYear < pMsg->m_iMsgYear)
	{
		m_iDrawYear = m_iDrawYear + 100;
	}
	m_iDrawNo				= pMlog->d.bt.lot.drawwu;				// draw no
	m_cRejSelection			= pMlog->d.bt.lot.errselbu;				// rejected selection no

	m_iAcctSysIndex			= pMlog->d.bt.lot.othsys.syswu;			// account bet system index
	m_iInterMsn				= pMlog->d.bt.lot.othsys.ismsnlu;		// inter msn
	m_iCardNo				= pMlog->d.bt.lot.othsys.carddu;		// card no

	m_iSellCentre			= pMlog->d.bt.lot.bet.h.sellCentrelu;	// selling centre
	m_iSellWindow			= pMlog->d.bt.lot.bet.h.sellWindowu;	// selling window
	m_cTickGenNo			= pMlog->d.bt.lot.bet.h.genbu;			// ticket generation no

	m_iUnitBet				= pMlog->d.bt.lot.bet.d.hdr.betinvcomb.flexi.baseinv;		// base investment in dollar //Q308 changes
	m_iTotalCost			= pMlog->d.bt.lot.bet.d.hdr.costlu;		// total cost in cents
	m_tTemp					= pMsg->m_iMsgSellTime;//pMlog->d.bt.lot.bet.d.hdr.sellTime;	// Sell time
	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	__time32_t tTemp = m_tTemp;
	Time					= _localtime32(&tTemp);
	sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", Time->tm_mday, m_sMonths[Time->tm_mon+1], Time->tm_year+1900, Time->tm_hour, Time->tm_min, Time->tm_sec);
	m_cBetType				= pMlog->d.bt.lot.bet.d.hdr.bettypebu;	// bet type
	GetType(m_cBetType, m_sBetType);

	m_cMultiEntriesFlag		= pMlog->d.bt.lot.bet.d.var.lot.n.multi1;	// multi-entry
	m_cRandomFlag			= pMlog->d.bt.lot.bet.d.var.lot.n.rand1;	// randomly generated
	m_cFieldFlag			= pMlog->d.bt.lot.bet.d.var.lot.n.field1;	// field bet
	m_cGameType				= pMlog->d.bt.lot.bet.d.var.lot.n.gamebu;	// game type
	char m_cSpecial			= pMlog->d.bt.lot.bet.d.var.lot.n.spc1;		// special flag
	m_cPartialUnitBet		= pMlog->d.bt.lot.bet.d.var.lot.n.pub1;		// partial unit bet   , Q310

	
	// calvin v6.2r0
	char m_sAddonSelection[255];
	m_sAddonSelection[0] = 0;
	m_iAddonInvest = 0;
	m_sSelections[0] = 0;
	
	char sSubGameType[100];
	sSubGameType[0] = 0;
	int MaxGame;

		// change the pointer position since variable selections
		// start from 4 -> 10 selections
		
		//struct BETLOT *pLOT;
		//pLOT = (struct BETLOT *)&pMlog->d.bt.lot.bet.d.var.lot;
		struct BETLOTVAR *pLOTVAR;

		union BETLTON *pLTON;
		pLTON = (union BETLTON *)&pMlog->d.bt.lot.bet.d.var.lot.n.sel;

	// For Single entry		(by Lawrence Leung add on 20-2-2003)
	if (m_cMultiEntriesFlag == 0)
	{
		m_iNoOfBanker			= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.nbnkbu;	// no of bankers
		m_iNoOfOthers				= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.nothbu;	// no of others

		int a=0;
		for (a=0; a<=6; a++)
		{
			m_cBankerBitmap[a]	= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.bnkmbu[a];	// banker bitmap
			m_cOthersBitmap[a]	= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.othmbu[a];	// other bitamp
			m_cPowerBitmap[a]	= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.pcmbu[a];	// powerball bitmap
		}

		m_sBankerBitmap[0]=0;
		m_sOthersBitmap[0]=0;
		m_sPowerBitmap[0]=0;
		for (a=0; a<=6; a++)
		{
			sprintf(temp, "%04X", m_cBankerBitmap[a]);
			strcat(m_sBankerBitmap, temp);
			sprintf(temp, "%04X", m_cOthersBitmap[a]);
			strcat(m_sOthersBitmap, temp);
			sprintf(temp, "%04X", m_cPowerBitmap[a]);
			strcat(m_sPowerBitmap, temp);
		}
		m_iNoOfPowerBall		= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.npwbbu;	// no fo powerball selections
		m_cPowerBase			= pMlog->d.bt.lot.bet.d.var.lot.n.sel.single.pbasbu;	// powerball base
		
		m_iNoOfEntries			= 0;	// For multi entries only


		if ( ( m_cGameType == 1 ) ||( m_iTsnBetType == TSN_TYPE_MD ))
			pLOTVAR = (struct BETLOTVAR *) ((char *)pLTON + 1+24);

		if ( m_cGameType == 1 ) 
		{
			char AddonTemp;
			for (int a = 0; a < 3; a++)
			{
				AddonTemp = pLOTVAR->aon.aselbu[a];	// add-on selections
				sprintf(temp, "%02d+", AddonTemp);
				strcat(m_sAddonSelection, temp);
			}
			m_sAddonSelection[strlen(m_sAddonSelection)-1] = 0;

			m_iAddonInvest			= pLOTVAR->aon.abaswu;			// add-on investment
		}
	
		if ( m_iTsnBetType == TSN_TYPE_MD )
		{
			m_iOnlineDividend		=0;// pMlog->d.bt.lot.bet.d.var.lot.var.md.odivdu;			// online dividend
			m_iNoOfDrawRefund		= pLOTVAR->md.drrfdbu; //pMlog->d.bt.lot.bet.d.var.lot.var.md.drrfdbu;			// no of draw refunded
			m_iNoOfDrawSelected		= pLOTVAR->md.drselbu; //pMlog->d.bt.lot.bet.d.var.lot.var.md.drselbu;			// no of draw selected
			m_iNoOfDrawRemain		= pLOTVAR->md.drrembu; //pMlog->d.bt.lot.bet.d.var.lot.var.md.drrembu;			// no of draw remaining
			m_iNoOfDrawOnlineDivcal	=0; //pMlog->d.bt.lot.bet.d.var.lot.var.md.drdivbu;			// no of draw online divcal'd
		}
		else
		{
			m_iOnlineDividend		= 0;
			m_iNoOfDrawRefund		= 0;
			m_iNoOfDrawSelected		= 1;
			m_iNoOfDrawRemain		= 1;
			m_iNoOfDrawOnlineDivcal	= 0;
		}	
	
	
	
	}
	// For Multi entries	(by Lawrence Leung add on 20-2-2003)
	else
	{
		m_iNoOfBanker = 0;		// For single entry only
		m_iNoOfOthers = 0;		// For single entry only
		m_sBankerBitmap[0] = 0;	// For single entry only
		m_sOthersBitmap[0] = 0;	// For single entry only
		m_sPowerBitmap[0] = 0;	// For single entry only
		m_iNoOfPowerBall = 0;	// For single entry only
		m_cPowerBase = 0;		// For single entry only
		
		m_iNoOfEntries			= pMlog->d.bt.lot.bet.d.var.lot.n.sel.multi.entbu;		// no of entries
	
		// for mult-entries, at least 4 entries in logger, there need to loop 4 times.
		if (m_iNoOfEntries <= 4)
		{
			for (EntriesLevel=0; EntriesLevel<=3; EntriesLevel++)
			{
				for (BitmapPos=0; BitmapPos<6; BitmapPos++)
				{
					m_sMultiEntriesBitmap[EntriesLevel][BitmapPos] = pMlog->d.bt.lot.bet.d.var.lot.n.sel.multi.selbu[EntriesLevel][BitmapPos];	// binary selection
				}
			}
		}
		else // if more 4 , selection will loop to m_iNoOfEntries
		{
			for (EntriesLevel=0; EntriesLevel<=(m_iNoOfEntries-1); EntriesLevel++)
			{
				for (BitmapPos=0; BitmapPos<6; BitmapPos++)
				{
					m_sMultiEntriesBitmap[EntriesLevel][BitmapPos] = pMlog->d.bt.lot.bet.d.var.lot.n.sel.multi.selbu[EntriesLevel][BitmapPos];	// binary selection
				}
			}
		}



		if (m_iNoOfEntries <=4)
			pLOTVAR = (struct BETLOTVAR *) ((char *)pLTON + 1+ 24);
		else 
			pLOTVAR = (struct BETLOTVAR *) ((char *)pLTON + 1+(6*m_iNoOfEntries));


		if ( m_cGameType == 1 ) 
		{
			char AddonTemp;
			for (int a = 0; a < 3; a++)
			{
				AddonTemp = pLOTVAR->aon.aselbu[a];	// add-on selections
				sprintf(temp, "%02d+", AddonTemp);
				strcat(m_sAddonSelection, temp);
			}
			m_sAddonSelection[strlen(m_sAddonSelection)-1] = 0;

			m_iAddonInvest			= pLOTVAR->aon.abaswu;			// add-on investment
		}



		if ( m_iTsnBetType == TSN_TYPE_MD )
		{
			m_iOnlineDividend		= pLOTVAR->md.odivdu;			// online dividend
			m_iNoOfDrawRefund		= pLOTVAR->md.drrfdbu;			// no of draw refunded
			m_iNoOfDrawSelected		= pLOTVAR->md.drselbu;			// no of draw selected
			m_iNoOfDrawRemain		= pLOTVAR->md.drrembu;			// no of draw remaining
			m_iNoOfDrawOnlineDivcal	= pLOTVAR->md.drdivbu;			// no of draw online divcal'd
		}
		else
		{
			m_iOnlineDividend		= 0;
			m_iNoOfDrawRefund		= 0;
			m_iNoOfDrawSelected		= 1;
			m_iNoOfDrawRemain		= 1;
			m_iNoOfDrawOnlineDivcal	= 0;
		}




	}
	

	

	
	if ( m_cGameType != LOT_GAME_NOR && m_cGameType != LOT_GAME_AON ) {
		char tmpStr[6];
		char subGameLabel[4];

		unsigned char subGame;

		if ( m_cGameType == LOT_GAME_OEG ) 
			sprintf( subGameLabel, "%s", "EOC" );
		else if ( m_cGameType == LOT_GAME_MHG ) 
			sprintf( subGameLabel, "%s", "MHG" );
		else if ( m_cGameType == LOT_GAME_EXN ) 
			sprintf( subGameLabel, "%s", "EXN" );
		else if ( m_cGameType == LOT_GAME_OUG ) 
			sprintf( subGameLabel, "%s", "OUG" );

		for ( int j=0; j<=6; j++) {
			subGame = m_cPowerBitmap[j];
			for ( int i=0; i<=7; i++ ) {
				if ( subGame & 0x01 ) {
					sprintf( tmpStr, "%s-%d,", subGameLabel, i + j*8 );
					strcat( sSubGameType, tmpStr);
					MaxGame = i;
				}
				subGame >>= 1;
			}
		}
		sSubGameType[strlen( sSubGameType ) -1] = 0;
	}

	// odd even game
	if ( m_cGameType == LOT_GAME_OEG ) {	
		for ( int i=0; i<MaxGame; i++ ) {
			if ( m_cBankerBitmap[i] == 0 ) 
				strcat( m_sSelections, "E+" );
			else
				strcat( m_sSelections, "O+" );
		}
		m_sSelections[strlen( m_sSelections ) -1] = 0;
	}
	else {
		if (m_cMultiEntriesFlag == 0)
		{
			if (m_iNoOfBanker != 0)
			{
				DeBitmap(m_cBankerBitmap, m_sSelections);
				strcat(m_sSelections, ">");
				DeBitmap(m_cOthersBitmap, m_sSelections);
			}
			else
			{
				DeBitmap(m_cOthersBitmap, m_sSelections);
			}
		}
		else
		{
			unsigned char tempBitmap[8];
			char tempNo[10];
			for (int a = 0; a < m_iNoOfEntries; a++)
			{
				for (BitmapPos = 0; BitmapPos < 6; BitmapPos++)
				{
					sprintf(tempNo, "%02d+", m_sMultiEntriesBitmap[a][BitmapPos]);
					strcat(m_sSelections, tempNo);
				}
				m_sSelections[strlen(m_sSelections)-1] = 0;
				strcat(m_sSelections, "/");
			}
			m_sSelections[strlen(m_sSelections)-1] = 0;
		}
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
	AddField(m_iLottIndex, 0);
	AddField(m_iDrawYear, 0);
	AddField(m_iDrawNo, 0);
	AddField(m_iSellCentre, 0);
	AddField(m_iSellWindow, 0);
	AddField(m_cTickGenNo, 0);
	AddField(m_iUnitBet, 0);
	AddField(m_iTotalCost, 0);
	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
	AddField(m_cBetType, 0);
	AddField(STORE_TYPE_STRING, m_sBetType, 0);	
	AddField(STORE_TYPE_STRING, "", 0);	// cancel flag for EDW
	AddField(m_cMultiEntriesFlag, 0);
	AddField(m_cRandomFlag, 0);
	AddField(m_cFieldFlag, 0);
	AddField(m_cGameType, 0);
	AddField(m_iNoOfBanker, 0);
	AddField(m_iNoOfOthers, 0);
	AddField(STORE_TYPE_STRING, m_sBankerBitmap, 0);
	AddField(STORE_TYPE_STRING, m_sOthersBitmap, 0);
	AddField(m_iNoOfPowerBall, 0);
	AddField(m_cPowerBase, 0);
	AddField(STORE_TYPE_STRING, m_sPowerBitmap, 0);
	AddField(m_iNoOfEntries, 0);
	AddField(STORE_TYPE_STRING, m_sAddonSelection, 0);		// addon selections
	AddField(m_iAddonInvest, 0);
	AddField(STORE_TYPE_STRING, m_sSelections, 0);
	AddField(m_iNoOfDrawRefund, 0);
	AddField(m_iNoOfDrawSelected, 0);
	AddField(m_iNoOfDrawRemain, 0);
	AddField(m_iNoOfDrawOnlineDivcal, 0);
	AddField(STORE_TYPE_STRING, sSubGameType, 0);
	AddField(m_cSpecial, 0);
	AddField(m_cPartialUnitBet, 0);

	return buf;
}

char* CBLottery::DeBitmap(unsigned char bitmap[], char sSelections[])
{
	int i = 0;
    int j = 0;
	char tempb[4];
    unsigned char bitmapbu = 0;    
    unsigned short lotnumwu = 0;            // Actual lottery number in binary 

	for (i = 0; i < BET_LOT_MAXSMAP; i++)
	{
		bitmapbu = bitmap[i];
		j = 0;
        
		while (bitmapbu)
		{
			if (bitmapbu & 0x01)
			{
				/*	powerball
				if (pwbbasenumwu != 0)
                // Get actual lottery number
                lotnumwu = i * 8 + j + pwbbasenumwu;
                else
                // Get actual lottery number
				*/
                lotnumwu = i * 8 + j;
				sprintf(tempb, "%02d+", lotnumwu);
				strcat(sSelections, tempb);
			}                       
			bitmapbu >>= 1;
			j++;
		}
	} 

	sSelections[strlen(sSelections)-1] = 0;
	return sSelections;
}
