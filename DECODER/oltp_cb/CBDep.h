// CBDep.h: interface for the CBDep class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBDep : public CBMsgTranslator  
{
public:
	virtual int TranslateAction(const Msg *pMsg);
	CBDep() {};
	virtual ~CBDep() {};	
};

#endif // !defined(AFX_CBDep_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
