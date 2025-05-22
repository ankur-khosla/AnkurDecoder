/////////////////////////////////////////////////////////////////////
//
// CBEftDep.h: interface for the CBEftDep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEFTDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEFTDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftDep : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftDep() {};
	virtual ~CBEftDep() {};
	
	int		m_iEftAmount;
	char	m_cPanType;
	char	m_sCustName[50];
	char	m_cNewEftMsgFlag;
	char	m_cKmIndex;
	char	m_sKT[20];
	char	m_sMac[10];
	int		m_iGatewayMsn;
	char	m_sBranchWin[10];
	char	m_sPan[10];
	char	m_sAmount[8];
	char	m_sBankPin[20];
	char	m_sAcctInd[5];
};

#endif // !defined(AFX_CBEftDep_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
