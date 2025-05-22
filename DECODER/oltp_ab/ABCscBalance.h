// ABCscBalance.h

#if !defined(AFX_ABCSCBALANCE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCSCBALANCE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCscBalance : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCscBalance () {};
	virtual ~ABCscBalance () {};	

private:


	unsigned __int64 m_iDailyExp;  //Daily expenditure (in cent)
	__int64 m_iTtlDiv;   //total dividend (in cent)


};

#endif // !defined(AFX_ABCSCBALANCE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
