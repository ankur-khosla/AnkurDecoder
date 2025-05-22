// ABAcctClose.h

#if !defined(AFX_ABSYSTEMCLOSE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABSYSTEMCLOSE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABSystemClose : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABSystemClose() {};
	virtual ~ABSystemClose() {};	

private:
	unsigned short m_iClsEnq;

};

#endif // !defined(AFX_ABSYSTEMCLOSE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
