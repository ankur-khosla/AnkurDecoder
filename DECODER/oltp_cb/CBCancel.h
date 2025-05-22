// CBCancel.h: interface for the CBCancel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"
#include <ctype.h>
#include "udtypedef.h"
#include "rdsdef.h"
#include "DeSelMap.h"
#include <string.h>

class CBCancel : public DeSelMap  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

	CBCancel() {};
	virtual ~CBCancel() {};	

	int		m_iMethod;
	short	m_iHighRecNo;
	unsigned LONGLONG		m_iLowRecNo;
	short	m_iLocation;
	short	m_i
		BetType;
	int		m_iCentreLowBit;
	int		m_iWindow;
	int		m_iCentreHighBit;
	short	m_iSaleSysNo;
	char	m_cNewTsnFlag;
	unsigned int		m_iMeetingDayOfYear;
	char	m_sMeetingDate[20];
	int		m_iCancelSysNo;
	char	m_sCancelSysNo[5];
	int		m_iCrossSysChanNo;
	int		m_iCrossSysMsn;
	int		m_iFileNo;
	int		m_iBfcIndex;
	int		m_iMeetingDrawIndex;
	int		m_iSellCentre;
	int		m_iSellWindow;
	struct tm *tm_SellTime;
	char	m_sSellTime[50];
	int		m_iBetType;
	unsigned char	m_cBetType;
	char	m_sBetType[20];
	char	m_sSelections[256];
	int		m_iUnitBet;
	int		m_iTotalCost;

	// Cancel TB Deposit
	int m_iTBAmount;

};

#define BETTYP_SB_PM			90      // pari-mutuel collated soccer bet
#define BETTYP_SB_FO			91      // fix-odds collated soccer bet
#define BETTYP_SB_EXO			92      // exotic soccer bet
#define BETTYP_SB_AUP_PM        93      // all-up soccer bet parimutuel
#define BETTYP_SB_AUP_FO_CTL    94      // controlled fixed odds allup bet
                                        // => an allup set is associated, need
                                        // to look up by first pool selected
#define BETTYP_SB_AUP_FO_NON    95      // Non-controlled fixed odds allup bet
#define BETTYP_SB_SEC_BET	    96      // SB section bet

#endif // !defined(AFX_CBCancel_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
