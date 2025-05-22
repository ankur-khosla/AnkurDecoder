// CBCV.h: interface for the CBCV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBCV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBCV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBCV : public CBMsgTranslator  
{
public:
	virtual int TranslateAction(const Msg *pMsg);
	CBCV() {};
	virtual ~CBCV() {};	
};

#endif // !defined(AFX_CBCV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
