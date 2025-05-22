// ABWithDraw.h

#if !defined(AFX_ABWITHDRAW_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABWITHDRAW_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
#include "acudef.h"

class ABWithDraw : public ABMsgTranslator
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABWithDraw() {};
	virtual ~ABWithDraw() {};

private:
	unsigned long m_iAmount;
	unsigned long m_iCharge;
	unsigned char m_cWithType;
	unsigned char m_cActiveBy;
	unsigned char m_cSrcWith;
	unsigned char m_cCancel;

	//**** account/CIT related info ****//
	// account related info in cit tran
	char m_sEpin[8];
	char m_sEkt[9];
	unsigned char m_cCitMsn;
	unsigned int m_iCitNo;

	// account related info in eft tran
	unsigned int m_iSecCode;
	unsigned char m_cEscEft;
	unsigned long m_iFundAva;
	unsigned long m_iBG;
	unsigned long m_iCurDiv;
	unsigned long m_iPreDiv;
	unsigned long m_iSbPay;

	//**** eft gateway info ****//
	unsigned int m_iEftChlMsn;
	unsigned short m_iEpsCode;
	unsigned short m_iEftSize;
	unsigned char m_iEftNo;
	unsigned char m_iEftSub;
	char m_sISN[10];
	char m_sBankAcct[30];
	char m_sEftReReply[520];
	// added in q405
	unsigned char m_iEftPin;
	unsigned char m_iEftFlag;
	char m_sEftAcctNo[15];

	// Added (201108PSR)
	unsigned short      m_iAnonymous;			//Anonymous Account
	unsigned short      m_iCscCard;			    //Tranaction with CSC Card

	// Added 201710EFTEMV)
	unsigned short m_iChipCard;

	//FPS for SP21a
	LONGLONG  m_iRefNo;					//Reference No.
	unsigned int m_iFpsProcessId;				//FPS process ID
	unsigned int m_iChannelId;			//Channel ID
	char m_iNbaNo;					//NBA #, 1=primary, 2=secondary
	char m_iBankCode[4];				//Bank Code
	char m_iActionType;				//Action, 1=Request, 2=Undo
};

#endif // !defined(AFX_ABWITHDRAW_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
