// ABDrCrAdjust.h

#if !defined(AFX_ABDRCRADJUST_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABDRCRADJUST_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABDrCrAdjust : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABDrCrAdjust() {};
	virtual ~ABDrCrAdjust() {};	

private:

	unsigned int m_iAcctNo;
	unsigned int m_iReTrack;

	unsigned char m_cDrCrType;
	unsigned char m_cNegBal;

	unsigned __int64 m_iAmount;
	unsigned short m_iTxnType;
	char m_sRemarks[100];

	__int64 m_iFundAva;
	__int64 m_iBankGd;
	__int64 m_iCurrDiv;
	__int64 m_iPrevDiv;
	__int64 m_iFbPayFor;
};

#endif // !defined(AFX_ABDRCRADJUST_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
