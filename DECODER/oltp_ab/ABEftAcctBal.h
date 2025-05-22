// ABEftAcctBal.h

#if !defined(AFX_ABEFTACCTBAL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEFTACCTBAL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEftAcctBal : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEftAcctBal() {};
	virtual ~ABEftAcctBal() {};	

private:

	unsigned char m_cPantype;
	char m_sPan[30];
/*
	unsigned int m_iSecCode;
	unsigned int m_iEscEft;

	unsigned long m_iFundAva;
	unsigned long m_iBankGd;
	unsigned long m_iCurrDiv;
	unsigned long m_iPrevDiv;
	unsigned long m_iFbPayFor;

	unsigned char m_cEftChanNo;
	unsigned int m_iGtwMsn;
*/
	char m_sEpin[15];
	char m_sEkt[15];
	unsigned char m_cCitMsn;
	unsigned int m_iCitNo;

	unsigned int m_iChannelMsn;
	unsigned short m_iPsuedoNo;
	unsigned short m_iChannelNo;
	unsigned short m_iRetCode;
	unsigned short m_iEftSize;
	unsigned char m_cChannelNo;
	unsigned char m_cSubcode;
	char m_sISN[10];
	char m_sBankNo[ACU_BANK_SIZE+10];
	char m_sBankAcctNo[ACU_BANK_ACN_SIZE];
	char m_sEftReq[LOGAB_EFTMSG_MAX+10];
};

#endif // !defined(AFX_ABEFTACCTBAL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
