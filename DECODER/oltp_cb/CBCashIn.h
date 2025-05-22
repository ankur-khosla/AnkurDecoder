// CBCashIn.h: interface for the CBCashIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBCASHIN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBCASHIN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBCashIn : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBCashIn() {};
	virtual ~CBCashIn() {};	

//	unsigned int m_iInterSys;				// inter-system msn
	unsigned int m_iDisable;				// bcs service is disabled
	unsigned int m_iAmount;					// amount in cent
	unsigned int m_iCashierNo;				// cashier #
	unsigned int m_iCashPass;				// cashier password
	char m_cCashCode[5];
};

#endif // !defined(AFX_CBCASHIN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
