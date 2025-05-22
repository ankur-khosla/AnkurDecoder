// CBrdt.h: interface for the CBrdt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBSYSCLOSE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBSYSCLOSE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBSysClose : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBSysClose() {};
	virtual ~CBSysClose() {};	
};

#endif // !defined(AFX_CBSYSCLOSE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
