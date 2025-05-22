/////////////////////////////////////////////////////////////////////
//
// CBStopPay.h: interface for the CBStopPay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBStopPay_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBStopPay_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBStopPay : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBStopPay() {};
	virtual ~CBStopPay() {};	


};

#endif // !defined(AFX_CBStopPay_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
