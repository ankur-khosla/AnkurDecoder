// ABCitCancel.h
#if !defined(AFX_ABCITCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCITCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCitCancel : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCitCancel() {};
	virtual ~ABCitCancel() {};	

private:

	unsigned char m_cDevType;
	unsigned __int64 m_iDevNo;
	unsigned char m_cForDep;

	__int64 m_iFundAva;
	__int64 m_iBankGd;
	__int64 m_iCurrDiv;
	__int64 m_iPrevDiv;
	__int64 m_iFbPayFor;

//	unsigned char m_cDisable;

	unsigned int m_iAnnFeeRefund;
	unsigned int m_iDepFeeRefund;
};

#endif // !defined(AFX_ABCITCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
