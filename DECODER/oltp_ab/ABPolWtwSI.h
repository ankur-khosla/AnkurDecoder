// ABPolWtwSI.h

#if !defined(AFX_ABPOLWTWSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOLWTWSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABPolWtwSI : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPolWtwSI() {};
	virtual ~ABPolWtwSI() {};	

private:

	unsigned long m_iRemainBal;

	// withdrawal transaction in account file
	long m_iAmount;
	unsigned long m_iSvcCharge;
	unsigned char m_cWtwType;
	unsigned char m_cActBy;
	unsigned char m_cSrcWtw;
	unsigned char m_cCancel;

	unsigned long m_iFundAva;
	unsigned long m_iBankGd;
	unsigned long m_iCurrDiv;
	unsigned long m_iPrevDiv;
	unsigned long m_iFbPayFor;

};

#endif // !defined(AFX_ABPOLWTWSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
