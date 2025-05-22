// ABAcctDetail.h

#if !defined(AFX_ABACCTDETAIL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABACCTDETAIL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABAcctDetail : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABAcctDetail() {};
	virtual ~ABAcctDetail() {};	

private:
	unsigned int m_iAcctNo;
	unsigned int m_iReTrack;
	unsigned char m_cAcctDetType;

	unsigned char m_cCustSal;
	char m_sSureName[50];
	char m_sOthName[50];
	char m_sChiSureName[50];
	char m_sChiOthName[50];

	unsigned char m_cCustType;
	unsigned char m_cRaceBetFlag;
	unsigned char m_cLotBetFlag;
	unsigned char m_cSBBetFlag;
	unsigned char m_cFBAcctType;
	unsigned char m_cLang;

	unsigned char m_cAcctStatus;

	char	m_sBankNo[10];   // Bank number
    char	m_sBranchNo[10];   // Branch number
    char	m_sBankAcctNo[20];// Bank account number

	__int64 m_iAcctBal;
};

#endif // !defined(AFX_ABACCTDETAIL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
