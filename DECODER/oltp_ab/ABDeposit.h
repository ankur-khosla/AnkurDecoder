// ABDeposit


#if !defined(AFX_ABDEPOSIT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABDEPOSIT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
//#include "acudef.h"

class ABDeposit : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABDeposit() {};
	virtual ~ABDeposit() {};

private:
	char m_sRelTime[30];
	unsigned __int64 m_iAmount;
	unsigned __int64 m_iSvcCharge;
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
	unsigned int m_iCitNo;

	// eft transaction from cb
	unsigned int m_iSecCode;
	unsigned int m_iEscEftTran;

	// epsco info -- eft gateway info
	unsigned int m_iChannelMsn;
	unsigned short m_iRetCode;
	unsigned short m_iEftSize;
	unsigned char m_cChannelNo;
	unsigned char m_cSubcode;
	char m_sISN[7];
	char m_sBankNo[ACU_BANK_ACN_SIZE];
	// added in q405
	unsigned char m_iEftPin;
	unsigned char m_iEftFlag;
	char m_sEftAcctNo[15];

	// account access info
	__int64 m_iFundAva;
	__int64 m_iBankG;
	__int64 m_iCurDivd;
	__int64 m_iPrvDivd;
	__int64 m_iSBPayout;

	unsigned char m_cNBANo;
	unsigned short m_iAnonymous;   // Anonymous account (2011IBT)
	unsigned short m_iCscCard;     // Transaction with CSC Card (201108PSR)

	// Added 201710EFTEMV
	unsigned short m_iChipCard;

	//FPS for SP21a
	LONGLONG  m_iRefNo;					//Reference No.
	unsigned int m_iFpsProcessId;				//FPS process ID
	unsigned int m_iChannelId;				//Channel ID
	//unsigned char m_iNbaNo;				//NBA #, 1=primary, 2=secondary
	char m_iBankCode[4];						//Bank Code
	char m_iActionType;							//Action, 1=Request, 2=Undo
};

#endif // !defined(AFX_ABDEPOSIT_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
