// ABPoolStartPay.h: interface for the ABPoolRefund class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABPOOLSTARTPAY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOOLSTARTPAY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"


class ABPoolStartPay : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPoolStartPay() {};
	virtual ~ABPoolStartPay() {};	

private:
	char m_sBetType[20];
};

#endif // !defined(AFX_ABEODESCTRAN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
