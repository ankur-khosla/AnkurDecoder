// ABReturnCard.h

#if !defined(AFX_ABRETURNCARD_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABRETURNCARD_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABReturnCard : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABReturnCard() {};
	virtual ~ABReturnCard() {};	

private:

	char m_sCustId[21];
	unsigned int m_iForDep;
	unsigned __int64 m_iEscCardNo;

	unsigned int m_iAnnFeeRefund;
	unsigned int m_iDepFeeRefund;
};

#endif // !defined(AFX_ABRETURNCARD_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
