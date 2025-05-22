/////////////////////////////////////////////////////////////////////
//
// CBEftBal.h: interface for the CBEftBal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEFTBAL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEFTBAL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftBal : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftBal() {};
	virtual ~CBEftBal() {};	

	__int64 m_iBalance;
	char	m_sBalance[50];

};

#endif // !defined(AFX_CBEftBal_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
