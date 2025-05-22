// ABEodDivFor.h

#if !defined(AFX_ABEODDIVFOR_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEODDIVFOR_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEodDivFor : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEodDivFor() {};
	virtual ~ABEodDivFor() {};	

private:

	unsigned short m_iSize;
	unsigned short m_iTranCode;
	unsigned short m_iTranNo;
	unsigned short m_iTranMerge;

	unsigned __int64 m_iForFeitAmt;
};

#endif // !defined(AFX_ABEODDIVGEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
