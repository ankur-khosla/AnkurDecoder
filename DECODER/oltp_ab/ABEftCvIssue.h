// ABEftAcctBal.h

#if !defined(AFX_ABEFTCVISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEFTCVISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEftCvIssue : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEftCvIssue() {};
	virtual ~ABEftCvIssue() {};	

private:

	unsigned int m_iAmount;

	unsigned int m_iChannelMsn;
	unsigned short m_iPsuedoNo;
	unsigned short m_iChannelNo;
	unsigned short m_iRetCode;
	unsigned short m_iEftSize;
	unsigned char m_cChannelNo;
	unsigned char m_cSubcode;
	char m_sISN[10];
	char m_sBankNo[ACU_BANK_SIZE+10];
	char m_sBankAcctNo[ACU_BANK_ACN_SIZE+10];
	char m_sEftReq[LOGAB_EFTMSG_MAX+10];

	// Added 201710EFTEMV
	unsigned short m_iChipCard;
};

#endif // !defined(AFX_ABEFTCVISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
