// ABPolBg.h

#if !defined(AFX_ABPOLBG_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOLBG_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABPolBg : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPolBg() {};
	virtual ~ABPolBg() {};	

private:

	__int64 m_iOBGAmt;
	unsigned char m_cOBGType;

	__int64 m_iNBGAmt;
	unsigned char m_cNBGType;

};

#endif // !defined(AFX_ABPOLBG_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
