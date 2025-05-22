// ABEodCrAdj.h

#if !defined(AFX_ABEODCRADJ_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEODCRADJ_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEodCrAdj : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEodCrAdj() {};
	virtual ~ABEodCrAdj() {};	

private:

	unsigned short m_iSize;
	unsigned short m_iTranCode;

	unsigned short m_iTranNo;
	unsigned short m_iTranMerge;

	unsigned __int64 m_iAmount;
	unsigned short m_iAdjType;
	char m_sRemarks[100];

};

#endif // !defined(AFX_ABEODCRADJ_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
