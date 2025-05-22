// CBBet.h: interface for the CBBet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBBET_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBBET_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeSelMap.h"
#include "CBMsgTranslator.h"


class CBBet : public DeSelMap
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	char* GetBetType(char BetType, char Type[20]);

	CBBet() {};
	virtual ~CBBet() {};
	
	short	m_iHighRecNo;
	unsigned LONGLONG		m_iLowRecNo;
	short	m_iLocation;
	short	m_iTsnBetType;
	short	m_iSaleSysNo;
	unsigned short	m_cNewTsnFlag;//char -> unsigned short
	unsigned int		m_iMeetingDayOfYear;
	int		m_iFileNo;
	int		m_iRdsIndex;
	char	m_cMeetLocat;
	char	m_cMeetingDay;
	int		m_iSellCentre;
	int		m_iSellWindow;
	struct tm *Time;
	char	m_cTickGenNo;
	int		m_iUnitBet;
	unsigned __int64	m_iUnitBetTenK;  //m_iUnitBet X10000

	__int64		m_iTotalCost;
	char	m_sSellTime[50];
	int		m_iBetType;
	char	m_sBetType[20];
	char	m_cEventNo;
	char	m_cFormula;
	int		a;
	char	m_sFormula[20];
	unsigned char m_cAllupPoolType[6];
	short	m_iAllupRaceNo[6];
	char	m_cAllupBankerFlag[6];
	char	m_cAllupFieldFlag[6];
	char	m_cAllupMultiFlag[6];
	char	m_cAllupMultiBankerFlag[6];
	char	m_cAllupRandomFlag[6];
	short	m_iNoOfCombination[6];
	int		m_iPayFactor[6];
	int		m_iAllupBankerBitmap[6];
	int		m_iAllupSelectBitmap[6];
	short	m_iRaceNo;
	char	m_cBankerFlag;
	char	m_cFieldFlag;
	char	m_cMultiFlag;
	char	m_cMultiBankerFlag;
	char	m_cRandomFlag;
	char	m_sSelections[1024];
	unsigned __int64		m_iBitmap[6];
	char	m_sBitmap[20];

	// for meeting date
	char	m_sMeetingDate[20];

	unsigned __int64		m_iPayChild;
	unsigned __int64		m_iPayParent;
	int		m_iCVSell;
	int		m_iCVPay;
	char	temp[20];
	char	m_cSelections[1024];
	char	m_cTempSelect[200];

	int		m_iFlexiBetFlag;		// q308 changes Flexi Bet Flag
	int		m_iTotalNoOfCombinations;  // q308 changes Total number of combination

};

#endif // !defined(AFX_CBBET_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
