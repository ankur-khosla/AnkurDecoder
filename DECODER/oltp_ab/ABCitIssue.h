// ABCitIssue.h
#if !defined(AFX_ABCITISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCITISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCitIssue : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCitIssue() {};
	virtual ~ABCitIssue() {};	

private:
	unsigned int m_iSecCode;
	unsigned char m_cDevType;
	unsigned __int64 m_iDevNo;
	unsigned char m_cCitVer;

	__int64 m_iFundAva;
	__int64 m_iBankGd;
	__int64 m_iCurrDiv;
	__int64 m_iPrevDiv;
	__int64 m_iFbPayFor;

	unsigned char m_cDisable;

	unsigned int m_iAnnFeeDeduct;
	unsigned int m_iDepFeeDeduct;
};

#endif // !defined(AFX_ABCITISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
