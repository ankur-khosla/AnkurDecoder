// ABPoolRefund.h: interface for the ABPoolRefund class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABPOOLREFUND_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOOLREFUND_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
#include "BDGWCMSGDEF.H"

class ABPoolRefund : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPoolRefund() {};
	virtual ~ABPoolRefund() {};	

private:
	char m_sBetType[20];
};

#endif // !defined(AFX_ABPOOLREFUND_H__035CEDBF_1D87_495B_8DC9_F584601BCE79__INCLUDED_)
