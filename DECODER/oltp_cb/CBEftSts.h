/////////////////////////////////////////////////////////////////////
//
// CBEftSts.h: interface for the CBEftSts class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEFTSTS_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEFTSTS_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftSts : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftSts() {};
	virtual ~CBEftSts() {};	

	char			m_cAtcFlag;
	char			m_cReplyFlag;
	char			m_cFirVer[3];
	char			m_cDate[20];
	char			m_cCurMsn[20];
	char			m_cCurIsn[20];
	char			m_cSubType[3];
	char			m_cModeFlag;			
	char			m_cCloseFlag;
	char			m_cKeyPos;
	char			m_cCustSts;
	unsigned char	m_cDep;
	unsigned char	m_cWtw;
	unsigned char	m_cBal;
	unsigned char	m_cBank;
	unsigned char	m_cCV;
	char			m_cPowFail;

};

#endif // !defined(AFX_CBEftSts_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
