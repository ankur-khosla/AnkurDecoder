// ABPolLoyalty.h

#if !defined(AFX_ABPOLLOYALTY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOLLOYALTY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABPolLoyalty : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPolLoyalty() {};
	virtual ~ABPolLoyalty() {};	

private:

	unsigned long m_iFundAva;
	unsigned long m_iBankGd;
	unsigned long m_iCurrDiv;
	unsigned long m_iPrevDiv;
	unsigned long m_iFbPayFor;

	unsigned long m_iAmount;
	unsigned long m_iCitNo;
	unsigned char m_cCitType;
	char m_sRemarks[520];
	int m_iNegBal;

};

#endif // !defined(AFX_ABPOLLOYALTY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
