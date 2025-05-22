// ABRace.h

#if !defined(AFX_ABRACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABRACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
#include "bettypdef.h"
#include "DeSelMap.h"

class ABRace : public DeSelMap 
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	char* GetBetType(char BetType, char Type[20]);
	ABRace() {};
	virtual ~ABRace() {};
	
private:
	
	char m_sMeetDate[30];
	unsigned char m_cLoc;
	unsigned char m_cDay;
	unsigned __int64 m_itotalPay;
	unsigned __int64 m_iUnitBet;    //q308  int->__int64
	unsigned __int64 m_iUnitBetTenK;  // m_iUnitBet x 10000
	__int64 m_iTotalCost;
	char m_sSellTime[40];
	//char m_sBetType[20];
	char m_cBetType;
	char m_sBetType[20];

	unsigned char m_cNoOfEvt;
	unsigned char m_cFormula;
	char m_sFormula[15];
	unsigned char m_cAllupPoolType[6];
	short	m_iAllupRaceNo[6];
	char	m_cAllupBankerFlag[6];
	char	m_cAllupFieldFlag[6];
	char	m_cAllupMultiFlag[6];
	char	m_cAllupMultiBankerFlag[6];
	char	m_cAllupRandomFlag[6];
	short	m_iNoOfCombination[6];
    int		m_iPayFactor[6];
	unsigned __int64		m_iAllupBankerBitmap[6];
	unsigned __int64		m_iAllupSelectBitmap[6];
	short	m_iRaceNo;
	char	m_cBankerFlag;
	char	m_cFieldFlag;
	char	m_cMultiFlag;
	char	m_cMultiBankerFlag;
	char	m_cRandomFlag;
	char	m_sSelections[1024];
	unsigned __int64	m_iBitmap[6];
	char	m_sBitmap[20];
	char	m_sAllupBettype[10];
	int		m_iFlexiBetFlag;		// q308 changes Flexi Bet Flag
	int		m_iTotalNoOfCombinations;  // q308 changes Total number of combination
	unsigned short      m_iAnonymous;			// Anonymous account (2011IBT)
	unsigned short		m_iCscCard;				// Transaction with CSC Card (201108PSR)

};

#endif // !defined(AFX_ABRACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
