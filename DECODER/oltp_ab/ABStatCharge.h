// ABStatCharge.h

#if !defined(AFX_ABSTATCHARGE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABSTATCHARGE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABStatCharge : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABStatCharge() {};
	virtual ~ABStatCharge() {};	

private:

	unsigned int m_iAcctNo;
	unsigned int m_iReTrack;

	unsigned long m_iChargeAmt;

	unsigned char m_cFromDay;
	unsigned char m_cFromMon;
	unsigned short m_iFromYear;
	unsigned char m_cToDay;
	unsigned char m_cToMon;
	unsigned short m_iToYear;

	char m_sFromDate[20];
	char m_sToDate[20];
	
	unsigned long m_iFundAva;
	unsigned long m_iBankGd;
	unsigned long m_iCurrDiv;
	unsigned long m_iPrevDiv;
	unsigned long m_iFbPayFor;
};

#endif // !defined(AFX_ABSTATCHARGE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
