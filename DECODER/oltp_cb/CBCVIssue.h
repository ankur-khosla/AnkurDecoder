// CBCVIssue.h: interface for the CBCVIssue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBCVISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBCVISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"
#include <ctype.h>
#include "udtypedef.h"
#include "rdsdef.h"
#include "DeSelMap.h"
#include <string.h>

class CBCVIssue : public DeSelMap  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

	CBCVIssue() {
		// <Marco Lui, 20050120>
		m_iOriginalEftAmount	= 0;
		m_iRemainingEftAmount	= 0;
		// </Marco Lui, 20050120>
	};
	virtual ~CBCVIssue() {};	

	int		m_iMethod;
	short	m_iHighRecNo;
	unsigned LONGLONG		m_iLowRecNo;
	short	m_iLocation;
	short	m_iTsnBetType;
	int		m_iCentreLowBit;
	int		m_iWindow;
	int		m_iCentreHighBit;
	unsigned short	m_iSaleSysNo;
	char	m_cNewTsnFlag;
	unsigned int		m_iMeetingDayOfYear;
	int		m_iCancelSysNo;
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
	struct tm *tm_SellTime;
	char	m_sSellTime[50];
	int		m_iBetType;
	char	m_cBetType;
	char	m_sBetType[20];
	char	m_sSelections[256];
	int		m_iUnitBet;
	int		m_iTotalCost;
	char	m_cIssueFlag;
	unsigned __int64		m_iCVSell;
	unsigned __int64		m_iCVPay;

};

#endif // !defined(AFX_CBCVIssue_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
