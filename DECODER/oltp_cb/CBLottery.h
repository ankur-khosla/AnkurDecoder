// CBLottery.h: interface for the CBLottery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBLOTTERY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBLOTTERY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeSelMap.h"
#include "CBMsgTranslator.h"


class CBLottery : public DeSelMap
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBLottery() {};
	virtual ~CBLottery() {};
	char* DeBitmap(unsigned char bitmap[], char temp[]);
	
	short	m_iHighRecNo;
	unsigned LONGLONG		m_iLowRecNo;
	short	m_iLocation;
	short	m_iTsnBetType;
	int		m_iLowSecCode;
	int		m_iCentreLowBit;
	int		m_iWindow;
	int		m_iCentreHighBit;
	int		m_iHighSecCode;
	short	m_iSaleSysNo;
	char	m_cNewTsnFlag;
	unsigned int		m_iMeetingDayOfYear;
	unsigned char		m_iFileNo;
	short	m_iLottIndex;
	short	m_iDrawYear;
	short	m_iDrawNo;
	char	m_cRejSelection;
	int		m_iAcctSysIndex;
	int		m_iInterMsn;
	int		m_iCardNo;
	int		m_iSellCentre;
	int		m_iSellWindow;
	int		m_iPrevPay;
	int		m_iPayCentre;
	__time32_t	m_tTemp;
	struct tm *Time;
	char	m_sPayTime[50];
	char	m_cPaySys;
	char	m_cTickGenNo;
	int		m_iTotalPayout;
	int		m_iUnitBet;
	int		m_iTotalCost;
	char	m_sSellTime[50];
	char	m_cBetType;
	char	m_sBetType[20];
	char	m_cCancelFlag;
	char	m_cPaidPartialFlag;
	char	m_cPaidFinalFlag;
	char	m_cDivcalFlag;
	char	m_cErrClaimFlag;
	char	m_cReleasePaidFlag;
	char	m_cOverflowFlag;
	char	m_cHoPayFlag;
	char	m_cBonusOverflowFlag;
	char	m_cMultiEntriesFlag;
	char	m_cRandomFlag;
	char	m_cFieldFlag;
	char	m_cGameType;
	short	m_iNoOfBanker;
	short	m_iNoOfOthers;
	unsigned char	m_cBankerBitmap[8];
	char	m_sBankerBitmap[256];
	unsigned char	m_cOthersBitmap[8];
	char	m_sOthersBitmap[256];
	char	temp[5];
	short	m_iNoOfPowerBall;
	char	m_cPowerBase;
	unsigned char	m_cPowerBitmap[8];
	char	m_sPowerBitmap[256];
	short	m_iNoOfEntries;
	char	m_sMultiEntriesBitmap[10][6];
	unsigned char	m_cAddonSelection[8];
	short	m_iAddonInvest;
	__int64	m_iOnlineDividend;
	char	m_sOnlineDividend[50];
	short	m_iNoOfDrawRefund;
	short	m_iNoOfDrawSelected;
	short	m_iNoOfDrawRemain;
	short	m_iNoOfDrawOnlineDivcal;
	char	m_sSelections[1024];

	int		EntriesLevel;
	int		BitmapPos;

	char	m_cPartialUnitBet;

};

#endif // !defined(AFX_CBLOTTERY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
