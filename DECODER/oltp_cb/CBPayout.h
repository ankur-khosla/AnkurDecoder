// CBPayout.h: interface for the CBCancel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBPAYOUT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBPAYOUT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"
#include <ctype.h>
#include "udtypedef.h"
#include "rdsdef.h"
#include "DeSelMap.h"
#include <string.h>
#include <stdio.h>


class CBPayout : public DeSelMap  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

	CBPayout() {
		// <Marco Lui, 20050120>
		m_iOriginalEftAmount	= 0;
		m_iRemainingEftAmount	= 0;
		// </Marco Lui, 20050120>
	};
	virtual ~CBPayout() {};	

	int		m_iMethod;
	short	m_iHighRecNo;
	unsigned LONGLONG		m_iLowRecNo;
	short	m_iLocation;
	short	m_i
		BetType;
	short	m_iSaleSysNo;
	char	m_cNew
		Flag;
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
	// <Marco Lui, 20050120>
	int		m_iOriginalEftAmount;
	int		m_iRemainingEftAmount;
	// </Marco Lui, 20050120>
	int		m_iBetType;
	char	m_cBetType;
	char	m_sBetType[20];
	char	m_sSelections[256];
	int		m_iUnitBet;
	unsigned LONGLONG		m_iTotalCost;
	struct	tm *tm_SellTime;
	char	m_sSellTime[50];
	__int64	m_iTotalPay;
	int		m_iBetSysIndex;
	int		m_iInterMsn;
	int		m_iCardNo;
	int		m_iNoOfRefund;
	int		m_iDrawYear;
	unsigned int		m_iDrawNo;
	char	m_sBetSysIndex[20];
	char	m_sFileNo[20];

	int		m_iPayCentre;
	int		m_iPayTime;
	int		m_iPaySys;
	int		m_iGenNo;
	int		m_iPayChild;
	int		m_iPayParent;
	unsigned int m_uiConsolation;
	char	m_cPaidPartialFlag;
	char	m_cPaidFinalFlag;
	char	m_cDivCalFlag;
	char	m_cReleasePaidFlag;
	char	m_cOverflowFlag;
	char	m_cHoPaymentFlag;
	struct	tm *tm_PayTime;
	char	m_sPayTime[50];

	short	m_iNewHighRecNo;
	unsigned LONGLONG		m_iNewLowRecNo;
	short	m_iNewLocation;
	short	m_iNewTsnBetType;
	short	m_iNewSaleSysNo;

	short	m_iOrgNoOfBankers;
	short	m_iOrgNoOfOthers;
	short	m_iOrgRandomFlag;
	short	m_iOrgNoOfEntries;
	short	m_iOrgNoOfDrawSelected;

	int		m_iOrgDrawYear;
	short	m_iOrgDrawNo;
	char	m_cIsPartialFlag;


#define BETTYP_SB_PM			90      // pari-mutuel collated soccer bet
#define BETTYP_SB_FO			91      // fix-odds collated soccer bet
#define BETTYP_SB_EXO			92      // exotic soccer bet
#define BETTYP_SB_AUP_PM        93      // all-up soccer bet parimutuel
#define BETTYP_SB_AUP_FO_CTL    94      // controlled fixed odds allup bet
                                        // => an allup set is associated, need
                                        // to look up by first pool selected
#define BETTYP_SB_AUP_FO_NON    95      // Non-controlled fixed odds allup bet
};

#endif // !defined(AFX_CBPayout_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
