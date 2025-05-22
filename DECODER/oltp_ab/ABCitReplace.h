// ABCitReplace.h
#if !defined(AFX_ABCITREPLACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCITREPLACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCitReplace : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCitReplace() {};
	virtual ~ABCitReplace() {};	

private:
	unsigned int m_iSecCode;
	unsigned char m_cODevType;
	unsigned __int64 m_iODevNo;
	unsigned char m_iNDevType;
	unsigned __int64 m_iNDevNo;
	unsigned char m_cNCitVer;
	unsigned char m_cUpdDep;
	unsigned char m_cForDep;
	unsigned char m_cVerSCode;


	__int64 m_iFundAva;
	__int64 m_iBankGd;
	__int64 m_iCurrDiv;
	__int64 m_iPrevDiv;
	__int64 m_iFbPayFor;
	
	unsigned char m_iDisable;

	unsigned int m_iAnnFeeDe;
	unsigned int m_iDepFeeDe;
	unsigned int m_iAnnFeeRe;
	unsigned int m_iDepFeeRe;

};

#endif // !defined(AFX_ABCITREPLACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
