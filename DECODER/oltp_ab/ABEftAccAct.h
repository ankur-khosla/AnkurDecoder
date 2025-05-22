// ABEftAccAct.h: interface for the ABEftAccAct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABEFTACCACT_H__D731763E_63C1_4B09_A3B6_F5710493FFF0__INCLUDED_)
#define AFX_ABEFTACCACT_H__D731763E_63C1_4B09_A3B6_F5710493FFF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEftAccAct : public ABMsgTranslator  
{
public:
	ABEftAccAct();
	virtual ~ABEftAccAct();
	virtual char * TranslateAction(const Msg *pMsg);

private:
	int m_iAcctNum;
	char m_sActivationDate[30];

};

#endif // !defined(AFX_ABEFTACCACT_H__D731763E_63C1_4B09_A3B6_F5710493FFF0__INCLUDED_)
