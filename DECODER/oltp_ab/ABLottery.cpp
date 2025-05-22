////////////////////////////////////////////////////////////////////
//
// CBLottery.cpp: implementation of the CBLottery class.
//
/////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <string.h>
#include "LOGDEF_AB.h"
#include "ABLottery.h"
#include "LOGRDCDEF.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typedef char* STR;

char * ABLottery::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog					= (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	m_iLottIndex	= pMlog->data.bt.lot.indexwu;
	m_iErrorSel		= pMlog->data.bt.lot.selwu;
	m_iOffset		= pMlog->data.bt.lot.offsetlu;
	m_cSrcSell		= pMlog->data.bt.lot.tran.bet.srcbu;
	m_iDrawYear		= pMlog->data.bt.lot.tran.bet.d.var.lot.yearwu;	// draw year
	m_iDrawYear		= m_iDrawYear + 1900;

	if (m_iDrawYear < pMsg->m_iMsgYear)
		m_iDrawYear = m_iDrawYear + 100;
	
	m_iDrawNo				= pMlog->data.bt.lot.tran.bet.d.var.lot.drawwu;	// draw no
	m_iLotType				= pMlog->data.bt.lot.tran.bet.d.var.lot.typewu;

	m_iUnitBet				= pMlog->data.bt.lot.tran.bet.d.hdr.betinvcomb.flexi.baseinv;		// base investment in dollar
	m_iTotalCost			= pMlog->data.bt.lot.tran.bet.d.hdr.costlu;		// total cost in cents
	m_tTemp					= pMsg->m_iMsgSellTime; //pMlog->data.bt.lot.tran.bet.d.hdr.sellTime;	// Sell time
	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	Time					= _localtime32(&m_tTemp);
	sprintf(m_sSellTime, "%02d-%s-%d %02d:%02d:%02d", Time->tm_mday, m_sMonths[Time->tm_mon+1], Time->tm_year+1900, Time->tm_hour, Time->tm_min, Time->tm_sec);
	m_cBetType				= pMlog->data.bt.lot.tran.bet.d.hdr.bettypebu;	// bet type
	GetType(m_cBetType, m_sBetType);

	m_cMultiEntriesFlag		= pMlog->data.bt.lot.tran.bet.d.var.lot.n.multi1;	// multi-entry
	m_cRandomFlag			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.rand1;	// randomly generated
	m_cFieldFlag			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.field1;	// field bet
	m_cAddOn				= pMlog->data.bt.lot.tran.bet.d.var.lot.n.addon1;   // Add On
	m_cSpecialFlag			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.spc1;   // Add On
	m_cGameType				= pMlog->data.bt.lot.tran.bet.d.var.lot.n.gamebu;	// game type
	m_cPartialUnitBet		= pMlog->data.bt.lot.tran.bet.d.var.lot.n.pub1;      // Q310 Partial unit bet

	m_iAnonymous			= pMlog->hdr.anonymous1;  // Anonymous Account (2011IBT)

	m_iCscCard				= pMlog->data.bt.lot.tran.bet.csctrn;  //Transaction with CSC Card (201108PSR)

	char AddonTemp;
	char m_sAddonSelection[255];
	m_sAddonSelection[0] = 0;
	m_iAddonInvest = 0;


	// change the pointer position since variable selections
		// start from 4 -> 10 selections
		
	struct BETLOT *pLOT;
	//pLOT = (struct BETLOT *)((char *)pMlog+ sizeof(pMlog->data.bt.lot.tran.bet.d.var.lot));
	pLOT = (struct BETLOT *)&pMlog->data.bt.lot.tran.bet.d.var.lot;

	struct BETLOTVAR *pLOTVAR;
	
	union BETLTON *pLTON;
	pLTON = (union BETLTON *)&pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel;

	// For Single entry		(by Lawrence Leung add on 20-2-2003)
	if (m_cMultiEntriesFlag == 0)
	{
		m_iNoOfBanker			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.nbnkbu;	// no of bankers
		m_iNoOfOthers				= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.nothbu;	// no of others
		int a=0;
		for (a=0; a<=6; a++)
		{
			m_cBankerBitmap[a]	= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.bnkmbu[a];	// banker bitmap
			m_cOthersBitmap[a]	= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.othmbu[a];	// other bitamp
			m_cPowerBitmap[a]	= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.pcmbu[a];	// powerball bitmap
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
		m_iNoOfPowerBall		= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.npwbbu;	// no fo powerball selections
		m_cPowerBase			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.single.pbasbu;	// powerball base
		
		m_iNoOfEntries			= 0;	// For multi entries only


		// change the pointer 
		if ( ( m_cGameType == 1 )  || ( pMlog->data.bt.lot.multidraw == 1 ))
				/*pLOTVAR = (struct BETLOTVAR *) ((char *) pLOT+ 2 + 1 + 24);*/
			pLOTVAR = (struct BETLOTVAR *) ((char *)pLTON + 1 + 24);


		if ( m_cGameType == 1 ) 
		{
		
			for (int a = 0; a < 3; a++)
			{
				AddonTemp = pLOTVAR->aon.aselbu[a];	// add-on selections
				
				sprintf(temp, "%02d+", AddonTemp);
				strcat(m_sAddonSelection, temp);
			}
			m_sAddonSelection[strlen(m_sAddonSelection)-1] = 0;

			m_iAddonInvest			= pLOTVAR->aon.abaswu;			// add-on investment
				
		}

		if ( pMlog->data.bt.lot.multidraw == 1 )
		{
			m_iOnlineDividend		= (__int64) pLOTVAR->md.odivdu;  // // online div
			//m_iOnlineDividend		= 0;
			m_iNoOfDrawRefund		= pLOTVAR->md.drrfdbu; // no of draw refund
			m_iNoOfDrawSelected		= pLOTVAR->md.drselbu; //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drselbu;			// no of draw selected
			m_iNoOfDrawRemain		= pLOTVAR->md.drrembu; //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drrembu;			// no of draw remaining
			m_iNoOfDrawOnlineDivcal	= pLOTVAR->md.drdivbu; //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drdivbu;			// no of draw online divcal'd
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
		
		m_iNoOfEntries			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.multi.entbu;		// no of entries
		// for mult-entries, at least 4 entries in logger, there need to loop 4 times.
		if (m_iNoOfEntries <= 4)

		{

			for (EntriesLevel=0; EntriesLevel<=3; EntriesLevel++)     
			{
				for (BitmapPos=0; BitmapPos<6; BitmapPos++)
				{
					m_sMultiEntriesBitmap[EntriesLevel][BitmapPos] = pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.multi.selbu[EntriesLevel][BitmapPos];	// binary selection
				}
			}
		}
		else // if more 4 , selection will loop to m_iNoOfEntries
		{
			for (EntriesLevel=0; EntriesLevel<= (m_iNoOfEntries-1); EntriesLevel++)     
			{
				for (BitmapPos=0; BitmapPos<6; BitmapPos++)
				{
					m_sMultiEntriesBitmap[EntriesLevel][BitmapPos] = pMlog->data.bt.lot.tran.bet.d.var.lot.n.sel.multi.selbu[EntriesLevel][BitmapPos];	// binary selection
				}
			}
		}

		if (m_iNoOfEntries <=4)
			//pLOTVAR = (struct BETLOTVAR *) ((char *) pLOT+ 2 + 1 + 24);
			pLOTVAR = (struct BETLOTVAR *) ((char *)pLTON + 1 + 24);
		else 
			//pLOTVAR = (struct BETLOTVAR *) ((char *) pLOT+ 2 + 1+ (6 * m_iNoOfEntries));
			pLOTVAR = (struct BETLOTVAR *) ((char *)pLTON + 1 + (6 * m_iNoOfEntries));


	if ( m_cGameType == 1 ) 
	{
		
		for (int a = 0; a < 3; a++)
		{
			//AddonTemp = pMlog->data.bt.lot.tran.bet.d.var.lot.n.aselbu[a];	// add-on selections
			AddonTemp = pLOTVAR->aon.aselbu[a];

			sprintf(temp, "%02d+", AddonTemp);
			strcat(m_sAddonSelection, temp);
		}
		m_sAddonSelection[strlen(m_sAddonSelection)-1] = 0;

		//m_iAddonInvest			= pMlog->data.bt.lot.tran.bet.d.var.lot.n.abaswu;			// add-on investment
			m_iAddonInvest = pLOTVAR->aon.abaswu;

	}



	if ( pMlog->data.bt.lot.multidraw == 1 )
	{
		//m_iOnlineDividend		= (__int64) pLOTVAR->md.odivdu ; 
		m_iOnlineDividend		= 0 ; 
		m_iNoOfDrawRefund		= pLOTVAR->md.drrfdbu;  //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drrfdbu;			// no of draw refunded
		m_iNoOfDrawSelected		= pLOTVAR->md.drselbu; //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drselbu;			// no of draw selected
		m_iNoOfDrawRemain		= pLOTVAR->md.drrembu; //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drrembu;			// no of draw remaining
		m_iNoOfDrawOnlineDivcal	= 0;//pLOTVAR->md.drdivbu; //pMlog->data.bt.lot.tran.bet.d.var.lot.md.drdivbu;			// no of draw online divcal'd
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


	


	
	m_sSelections[0] = 0;


	char sSubGameType[100];
	sSubGameType[0] = 0;
	int MaxGame;

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
	//		unsigned char tempBitmap[8];
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

	int m_iCrossSell = pMlog->data.bt.lot.crossSellFl;
	if ( m_iCrossSell == 1 )
		int a =0;

	


// end Q207

	// Output
	AddField(m_iUnitBet, 0);
	AddField64(m_iTotalCost, 0);
	
	AddField(m_iLottIndex, 0);
	AddField(m_iErrorSel, 0);
	AddField(m_iOffset, 0);
	AddField(m_cSrcSell, 0);
	AddField(m_iDrawYear, 0);
	AddField(m_iDrawNo, 0);
	AddField(m_iLotType, 0);	

//	AddField(STORE_TYPE_STRING, m_sSellTime, 0);
//	AddField(m_cBetType, 0);
//	AddField(STORE_TYPE_STRING, m_sBetType, 0);

	AddField(m_cMultiEntriesFlag, 0);
	AddField(m_cRandomFlag, 0);
	AddField(m_cFieldFlag, 0);
	AddField(m_cAddOn, 0);
	AddField(m_cGameType, 0);
	AddField(m_iNoOfEntries, 0);
	AddField(STORE_TYPE_STRING, m_sSelections, 0);
	AddField(m_iNoOfBanker, 0);
	AddField(m_iNoOfOthers, 0);
	AddField(STORE_TYPE_STRING, m_sBankerBitmap, 0);
	AddField(STORE_TYPE_STRING, m_sOthersBitmap, 0);
	AddField(m_iNoOfPowerBall, 0);
	AddField(m_cPowerBase, 0);
	AddField(STORE_TYPE_STRING, m_sPowerBitmap, 0);
	AddField(STORE_TYPE_STRING, m_sAddonSelection, 0);		// addon selections
	AddField(m_iAddonInvest, 0);
	AddField64(m_iOnlineDividend, 0);
	AddField(m_iNoOfDrawRefund, 0);
	AddField(m_iNoOfDrawSelected, 0);
	AddField(m_iNoOfDrawRemain, 0);
	AddField(m_iNoOfDrawOnlineDivcal, 0);
	AddField(STORE_TYPE_STRING, sSubGameType, 0);
	AddField(m_cSpecialFlag, 0);
	AddField(m_iCrossSell, 0);
	AddField(m_cPartialUnitBet, 0);					//Q310
	AddField(m_iAnonymous, 0);					// Anonymous Account (2011IBT)
	AddField(m_iCscCard, 0);					// Transaction with CSC Card (201108PSR)

	return buf;
}

char* ABLottery::DeBitmap(unsigned char bitmap[], char sSelections[])
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
