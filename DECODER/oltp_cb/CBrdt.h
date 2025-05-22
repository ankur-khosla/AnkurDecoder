// CBrdt.h: interface for the CBrdt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBRDT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBRDT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBrdt : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBrdt() {};
	virtual ~CBrdt() {};	
};

#endif // !defined(AFX_CBrdt_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
