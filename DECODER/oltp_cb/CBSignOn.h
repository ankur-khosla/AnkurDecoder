// CBSignOn.h: interface for the CBSignOn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBSIGNON_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBSignOn_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBSignOn : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBSignOn() {};
	virtual ~CBSignOn() {};

protected:
//	int		m_iInterMsn;
	char	m_cDisBcsFlag;
	int		m_iPassword;
	int		m_iSuperNo;
	int		m_iSuperPassword;
	int		m_iAutLevelBitmap;
	int		m_iCentreNo;
	char	m_cHighCV;
	char	m_cKeyCan;
	char	m_cDisPay;
	char	m_cHOTerm;
	char	m_cOnCoTerm;
	char	m_cShroffSignOn;
	char	m_sTermDate[50];
	char	m_cRam;
	char	m_cRom;
	char	m_cPrinter;
	char	m_cTermFlag;

	char	m_cToteFlag;
	char	m_cDisableLottery;
	char	m_cDisableSB;
	char	m_cDisableCV;
	char	m_cDisableRace;
	char	m_cDisableDep;

};

#endif // !defined(AFX_CBSignOn_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
