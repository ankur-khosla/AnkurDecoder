// CBCVCash.h: interface for the CBCVCash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBCVCASH_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBCVCASH_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"
#include <ctype.h>
#include "udtypedef.h"
#include "rdsdef.h"
#include "DeSelMap.h"
#include <string.h>

class CBCVCash : public DeSelMap  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

	CBCVCash() {
		// <Marco Lui, 20050120>
		m_iOriginalEftAmount	= 0;
		m_iRemainingEftAmount	= 0;
		// </Marco Lui, 20050120>
	};
	virtual ~CBCVCash() {};	

	int		m_iMethod;
	short	m_iHighRecNo;
	unsigned LONGLONG	m_iLowRecNo;
	short	m_iLocation;
	short	m_i
		BetType;
	int		m_iCentreLowBit;
	int		m_iWindow;
	int		m_iCentreHighBit;
	short	m_iSaleSysNo;
	char	m_cNewTsnFlag;
	unsigned int		m_iMeetingDayOfYear;
	int		m_iCancelSysNo;
	char	m_sCancelSysNo[5];
	int		m_iCrossSysChanNo;
	int		m_iCrossSysMsn;
	int		m_iFileNo;
	int		m_iBfcIndex;
	int		m_iMeetingDrawIndex;
	unsigned int		m_iSellCentre;
	unsigned int		m_iSellWindow;
	// <Marco Lui, 20050120>
	unsigned __int64		m_iOriginalEftAmount;
	unsigned __int64		m_iRemainingEftAmount;
	// </Marco Lui, 20050120>
	struct tm *tm_SellTime;
	char	m_sSellTime[50];
	int		m_iBetType;
	char	m_cBetType;
	char	m_sBetType[20];
	int		m_iUnitBet;
	int		m_iTotalCost;
	unsigned __int64		m_iCVSell;
	unsigned __int64		m_iCVPay;

};

#endif // !defined(AFX_CBCVCASH_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
