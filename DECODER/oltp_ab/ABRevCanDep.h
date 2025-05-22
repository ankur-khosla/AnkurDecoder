// ABRevCanDep.h


#if !defined(AFX_ABREVCANDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABREVCANDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABRevCanDep : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABRevCanDep() {};
	virtual ~ABRevCanDep() {};

private:
	char m_sRelTime[30];
	unsigned long m_iAmount;
	unsigned long m_iSvcCharge;
	unsigned char m_cDepType;
	unsigned char m_cWthHold;
	unsigned char m_cCancel;
	unsigned char m_cReversed;
	unsigned char m_cSrcDep;

	//**** Deposit Detail ****//
	// epsco info -- account related info
	// cit transaction
	char m_sEpin[15];
	char m_sEkt[15];
	unsigned char m_cCitMsn;
	unsigned char m_cCitNo;

	// eft transaction from cb
	unsigned int m_iSecCode;
	unsigned int m_iEscEftTran;

	// epsco info -- eft gateway info
	unsigned int m_iChannelMsn;
	unsigned short m_iRetCode;
	unsigned short m_iEftSize;
	unsigned char m_cChannelNo;
	unsigned char m_cSubcode;
	char m_sISN[10];
	char m_sBankNo[ACU_BANK_ACN_SIZE];
	
	// account access info
	unsigned long m_iFundAva;
	unsigned long m_iBankG;
	unsigned long m_iCurDivd;
	unsigned long m_iPrvDivd;
	unsigned long m_iSBPayout;

};

#endif // !defined(AFX_ABREVCANDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
