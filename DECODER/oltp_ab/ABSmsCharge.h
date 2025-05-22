// ABSmsCharge.h: interface for the ABSmsCharge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSMSCHARGE_H__23E7F3F6_0D52_4F6D_BBD7_19FD8738610C__INCLUDED_)
#define AFX_ABSMSCHARGE_H__23E7F3F6_0D52_4F6D_BBD7_19FD8738610C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABSmsCharge : public ABMsgTranslator  
{
public:
	ABSmsCharge();
	virtual ~ABSmsCharge();
	virtual char * TranslateAction(const Msg *pMsg);
};

#endif // !defined(AFX_ABSMSCHARGE_H__23E7F3F6_0D52_4F6D_BBD7_19FD8738610C__INCLUDED_)
