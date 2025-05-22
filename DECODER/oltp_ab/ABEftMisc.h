// ABEftMisc.h


#if !defined(AFX_ABEFTMISC_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEFTMISC_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEftMisc : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEftMisc() {};
	virtual ~ABEftMisc() {};

private:

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

	// Added 201710EFTEMV
	unsigned short m_iChipCard;
};

#endif // !defined(AFX_ABEFTMISC_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
