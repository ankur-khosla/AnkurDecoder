/////////////////////////////////////////////////////////////////////
//
// CBEftWith.h: interface for the CBEftWith class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEftWith_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEftWith_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftWith : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftWith() {};
	virtual ~CBEftWith() {};
	
	unsigned int m_iTotCost;
	unsigned short m_iWithType;

};

#endif // !defined(AFX_CBEftWith_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
