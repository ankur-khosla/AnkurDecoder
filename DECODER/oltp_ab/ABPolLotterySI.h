// ABPolLotterySI.h

#if !defined(AFX_ABPOLLOTTERYSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOLLOTTERYSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABPolLotterySI : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPolLotterySI() {};
	virtual ~ABPolLotterySI() {};	
	char* DeBitmap(unsigned char bitmap[], char temp[]);

private:

	unsigned int m_iSiEntryNo;
	unsigned char m_cLotType;
	char m_sDrawDate[30];

	unsigned int m_iDrawYear;
	unsigned int m_iDrawNo;
	unsigned int m_iUnitCost;  
	unsigned int m_iTotalCost; 
	unsigned int m_iLotBetType;

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
	char	m_sMultiEntriesBitmap[4][6];
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

#endif // !defined(AFX_ABPOLLOTTERYSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
