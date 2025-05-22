// ABLottery.h: interface for the CBLottery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABLOTTERY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABLOTTERY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DeSelMap.h"
#include "ABMsgTranslator.h"


class ABLottery : public DeSelMap
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABLottery() {};
	virtual ~ABLottery() {};
	char* DeBitmap(unsigned char bitmap[], char temp[]);
	
	unsigned short	m_iLottIndex;
	unsigned short	m_iErrorSel;
	unsigned int	m_iOffset;
	unsigned char	m_cSrcSell;
	unsigned short	m_iDrawYear;
	unsigned int	m_iDrawNo;
	unsigned int	m_iLotType;

	unsigned char 	m_cAddOn;
	unsigned char   m_cSpecialFlag;

	
	__time32_t	m_tTemp;
	struct tm *Time;
	int		m_iTotalPayout;
	int		m_iUnitBet;
	unsigned __int64		m_iTotalCost;
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
	unsigned short      m_iAnonymous;			// Anonymous account (2011IBT)
	unsigned short      m_iCscCard;			    // Transaction with CSC Card (201108PSR)

};

#endif // !defined(AFX_ABLOTTERY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
