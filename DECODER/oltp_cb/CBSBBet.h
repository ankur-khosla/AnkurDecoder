// CBSBBet.h: interface for the CBSBBet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBSBBet_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBSBBet_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "LOGDEF.h"
#include "TextDB.h"
#include "sbdef.h"
#include "sblogdef.h"
#include "CBSBBetDetail.h"
#include "CBSBSelBitmap.h"


class CBSBBet : public CBSBSelBitmap, public CBSBBetDetail
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	
	void SimpleSelection(char* string);
	CBSBBet();
	virtual ~CBSBBet();

// Football Betting Pool Type
#define SB_1X2		0
#define SB_HDC		1
#define SB_COS		2
#define SB_DBR		3
#define SB_TOS		4
#define SB_OOU		5
#define SB_OES		6
#define SB_FGS		7
#define SB_HCS		8   // half time full time correct score
#define SB_HHAD		9
#define SB_FHAD		10
#define SB_TQL		11	// TQL Q407
#define SB_FTS		12	// MAR 2011
#define SB_FHLO		13	// NOV 2011

#define SB_FCRS		14 // 2012 MAR

#define SB_CHLO		15	// Aug 2013

//#define SB_CFG		14  // configurable pool
#define SB_NTS		16	// Q408
#define SB_ETS		17  // Q408


#define SB_SPC_MATCH	18 // special pool (match related)
#define	SB_SPC_TRN		19	// special pool (tournament related)
#define SB_THF		20  // treble half time/full time correct score 
#define SB_HFM		21	// mulitple half time/full time result
#define SB_HCSD		22  // half/full time correct score doubled
#define	SB_BNG		23  // Bingo
#define SB_CHP		40  // Championship
#define	SB_CHPP		41	// Tournament Forcast
#define	SB_FINP		42  // Advance Team
#define	SB_GPF		43  // Group Forcast
#define SB_GPW		44	// Group Winner
#define SB_TPS		45	// Top Scorer/Team

// Football Betting Bet Type
#define BETTYP_SB_PM			19      // pari-mutuel collated soccer bet
#define BETTYP_SB_FO			20      // fix-odds collated soccer bet
#define BETTYP_SB_EXO			21      // exotic soccer bet
#define BETTYP_SB_AUP_PM        22      // all-up soccer bet parimutuel
#define BETTYP_SB_AUP_FO_CTL    23      // controlled fixed odds allup bet
                                        // => an allup set is associated, need
                                        // to look up by first pool selected
#define BETTYP_SB_AUP_FO_NON    24      // Non-controlled fixed odds allup bet
#define BETTYP_SB_SEC_BET		25		// Mix Bet Type

// define the max selection for each pool -- Field
#define COS_MAX_SEL		28  // max no of selection for correct score
#define FGS_MAX_SEL		43  // max no of selection for first goal soccers


	char	m_cData[2056];
	int		m_iOddsOut;
	int		m_iHighRecNo;
	int		m_iLocation;
	int		m_iTsnBetType;
	unsigned LONGLONG		m_iLowRecNo;
	int		m_iHighSecCode;
	int		m_iSaleSysNo;
	char	m_cNewTsnFlag;
	int		m_iFileNo;
	int		m_iRdsIndex;
	char	m_cMeetLocat;
	char	m_cMeetingDay;
	int		m_iInterMsn;
	int		m_iSellCentre;
	int		m_iSellWindow;
	int		m_cTickGenNo;
	int		m_iUnitBet;
	unsigned int m_iTotalCost;
	int		m_iBetType;
	struct tm *Time;
	char m_sSellTime[50];
	char m_sBetType[20];
	char m_cBonusOverflowFlag;
	int m_iBonusPcent;
	int m_iSimplePool;
	int m_cFormula;
	int m_iBonusCent;
	char m_sFormula[10];
	short m_iCtrlFlag;
	unsigned int m_iMeetingDayOfYear;
	char m_sMeetingDate[20];

	char temp2[200];
	char temp3[30];

	char score[10];
	int m_iYear;
	int m_iDay;
	char day[20];
	char time[20];
	int m_iLegNo;
	char m_sSellDate[20];
	int m_iPoolTypeNum;

	// new variables defined for stage 2
	int m_iTotalEntry;
	unsigned char m_cField;
	unsigned char m_cField2;
	unsigned int m_iRandGen;
	unsigned int m_iEntryNo;

	// new variables defined for stage 3 (benkoo - 2/2/2004)
	unsigned char m_iGroupNum; // Group number 
	
	// new variables defined for stage 3A (benkoo - 29-Mar-2004)
	char m_sSpcCreateDate[20];
	int m_iSPCYear;
	int m_iSPCDay;

	// Add in M7D 
	unsigned char m_cSetNumber;		// only for section bet

protected:
	TextDB *m_pSB;

};

#endif // !defined(AFX_CBSBBet_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
