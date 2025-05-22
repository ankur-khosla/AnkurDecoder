// ABSBBet.h: interface for the ABSBBet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSBBET_H__063203E6_5EAD_11D4_A461_00C04F72C914__INCLUDED_)
#define AFX_ABSBBET_H__063203E6_5EAD_11D4_A461_00C04F72C914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "TBEsc.h"
#include "bettypdef.h"
#include "TextDB.h"
#include "sbdef.h"
#include "ABSBSelBitmap.h"
#include "LOGDEF_AB.h"

// Football Betting Pool Type
#define SB_1X2	0	// HAD
#define SB_HDC	1	// Handicap
#define SB_COS	2	// correct score
#define SB_DBR	3	// half time full time
#define SB_TOS  4	// total goal
#define SB_OOU  5	// high low
#define SB_OES  6	// odd even goal
#define SB_FGS  7	// first scorer
#define SB_HCS  8   // half time full time correct score
#define SB_HHAD 9	// Handicap goal with Home/Draw/Away
#define SB_FHAD 10	// Half Time HAD
#define SB_TQL  11	// TQL Q407
#define SB_FTS	12	// FTS	MAR2011
#define SB_FHLO  13 	// First half high low

//#define SB_CFG  14  // configurable pool // Commented for FCRS
#define SB_FCRS		14 // First Half Correct Score (2012MAR)

#define SB_CHLO  15 	// Corner high low

#define SB_NTS		16	// Q408
#define SB_ETS		17  // Q408

#define SB_SPC_MATCH	18 // special pool (match related)
#define	SB_SPC_TRN		19	// special pool (tournament related)
#define SB_THF  20  // treble half time/full time correct score 
#define SB_HFM	21	// mulitple half time/full time result
#define SB_HCSD 22  // half/full time correct score doubled
#define	SB_BNG  23  // Bingo
#define SB_CHP  40  // Championship
#define	SB_CHPP 41	// Champion and First Runner Up
#define	SB_FINP 42  // Finalist
#define	SB_GPF		43  // Group Forcast
#define SB_GPW		44	// Group Winner
#define SB_TPS		45	// Top Scorer/Team



// Football Betting Bet Type
#define BETTYP_SB_PM    19      // pari-mutuel collated soccer bet
#define BETTYP_SB_FO    20      // fix-odds collated soccer bet
#define BETTYP_SB_EXO   21      // exotic soccer bet
#define BETTYP_SB_AUP_PM        22      // all-up soccer bet parimutuel
#define BETTYP_SB_AUP_FO_CTL    23      // controlled fixed odds allup bet
                                        // => an allup set is associated, need
                                        // to look up by first pool selected
#define BETTYP_SB_AUP_FO_NON    24      // Non-controlled fixed odds allup bet
#define BETTYP_SB_MIX			25		// Mix Bet Type

#define COS_MAX_SEL		28  // max no of selection for correct score
#define FGS_MAX_SEL		43  // max no of selection for first goal soccers

class ABSBBet : public ABSBSelBitmap
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABSBBet();
	virtual ~ABSBBet();
	void SimpleSelection(char* string);

	static const int m_iFlagOffset;
	static const int m_iOddFlagOffset;

protected:

	char m_cData[2048];
	char m_tBuf[2048];
	TextDB *m_pSB;
	char m_sOddsFlag[20];
	int m_iCtrlFlag;

private:
	char* CalScore(int position, char* score);
	int GetTotalSel();
	void SetTotalSel(int ttlCom);
	char* Dec2Binary(unsigned int decimal, char* BArray);
	void GetHCS(unsigned int half, unsigned int full, char**& HFCombination, int& total_sel);
	char* GetType(int m_iBetType, char m_sBetType[20]);
//	void GetDHCP(unsigned __int64 half, unsigned __int64 full, char**& HFCombination, unsigned char &cField, int& total_sel);
	char* Dec2Binary2(__int64 decimal, char* BArray);
	char* CalScore1(int position, char* score);

	int ttlSel;
	int m_iLegNo;
	char m_sBetType[20];

	// new vairables defined for stage 2
	unsigned int m_iTotalEntry;
	unsigned char m_cField;
	unsigned char m_cField2;
	unsigned int m_iRandGen;
	unsigned int m_iEntryNo;

	// Add in M7D 
	unsigned char m_cSetNumber;		// only for section bet
	unsigned short m_iReqConfirm;   // use for intercept pool
	unsigned short m_iUnitBetChg;   // use for intercept pool
	unsigned short m_iIntercept;	// use for intercept pool
	unsigned short m_iUserAbort;	// use for intercept pool
	unsigned short m_iSettle;	// use for intercept pool
	unsigned short m_cErrPool;		// use for intercept pool


	// new variables defined for stage 3 (benkoo - 2/2/2004)
	unsigned char m_iGroupNum; // Group number 

	// new variables defined for stage 3A (benkoo - 29-Mar-2004)
	char m_sSpcCreateDate[20];
	int m_iSPCYear;
	int m_iSPCDay;

	// Anonymous account (2011IBT)
	unsigned short      m_iAnonymous;		
	unsigned short      m_iCscCard;			//Transaction with CSC Card (201108PSR)

};

#endif // !defined(AFX_ABSBBet_H__063203E6_5EAD_11D4_A461_00C04F72C914__INCLUDED_)
