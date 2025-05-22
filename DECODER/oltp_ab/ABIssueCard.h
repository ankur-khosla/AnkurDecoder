// ABIssueCard.h

#if !defined(AFX_ABISSUECARD_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABISSUECARD_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABIssueCard : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABIssueCard() {};
	virtual ~ABIssueCard() {};	

private:

	char m_sCustId[21];
	unsigned int m_iSecCode;
	unsigned int m_iWaiveFlag;
	unsigned __int64 m_iEscCardNo;
	unsigned __int64 m_iDepAmt;

	__int64 m_iFundAva;
	__int64 m_iBankGd;
	__int64 m_iCurrDiv;
	__int64 m_iPrevDiv;
	__int64 m_iFbPayFor;
	
	unsigned int m_iAnnFeeDeduct;
	unsigned int m_iDepFeeDeduct;
};

#endif // !defined(AFX_ABISSUECARD_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
