/////////////////////////////////////////////////////////////////////
//
// CBEftErr.h: interface for the CBEftErr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEFTERR_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEFTERR_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftErr : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftErr() {};
	virtual ~CBEftErr() {};	
};

#endif // !defined(AFX_CBEftErr_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
