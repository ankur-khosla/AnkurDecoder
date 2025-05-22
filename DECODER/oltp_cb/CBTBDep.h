// CBTBDep.h: interface for the CBTBDep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBTBDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBTBDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBTBDep : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBTBDep() {};
	virtual ~CBTBDep() {};	

	int		m_iMethod;
	short	m_iHighRecNo;
	int		m_iLowRecNo;
	short	m_iLocation;
	short	m_iTsnBetType;
	int		m_iCentreLowBit;
	int		m_iWindow;
	int		m_iCentreHighBit;
	short	m_iSaleSysNo;
	char	m_cNewTsnFlag;
	int		m_iMeetingDayOfYear;
	int		m_iCancelSysNo;
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
	char	m_cBetType;
	char	m_sBetType[20];
	char	m_sSelections[256];
	int		m_iUnitBet;
	int		m_iTotalCost;
	int		m_iDepSysNo;
	int		m_iDepChanNo;
	int		m_iInterMsn;
	int		m_iTranNo;
	int		m_iAmount;
	char	m_sCustName[50];
};

#endif // !defined(AFX_CBTBDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
