// ABSignOn.h

#if !defined(AFX_ABSIGNON_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABSIGNON_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABSignOn : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABSignOn() {};
	virtual ~ABSignOn() {};	

private:


};

#endif // !defined(AFX_ABSIGNON_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
