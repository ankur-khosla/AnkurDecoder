// ABEodLotDiv.h

#if !defined(AFX_ABEODRACEDIV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEODRACEDIV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEodRaceDiv : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEodRaceDiv() {};
	virtual ~ABEodRaceDiv() {};	

private:

	unsigned short m_iSize;
	unsigned short m_iTranCode;
	unsigned short m_iTranNo;
	unsigned short m_iTranMerge;

	unsigned __int64 m_iDividend;
	unsigned int m_iBaseInvestAmt;
	unsigned int m_iTotalCost;
	unsigned char m_cBetType;
	__time32_t m_iSellTime;
	struct tm *sellTime;
	int m_iYear;
	int m_iDay;
	char daytime[50];
};

#endif // !defined(AFX_ABEODDIVGEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
