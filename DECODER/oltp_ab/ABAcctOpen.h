// ABAcctOpen.h

#if !defined(AFX_ABACCTOPEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABACCTOPEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABAcctOpen : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABAcctOpen() {};
	virtual ~ABAcctOpen() {};	

private:

	unsigned int m_iAcctNo;
	unsigned int m_iReTrack;

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

	char m_sBankNo[10];
	char m_sBranchNo[10];
	char m_sBankAcctNo[20];
	unsigned int m_iSecCode;
	unsigned char m_cChgCode;

};

#endif // !defined(AFX_ABACCTOPEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
