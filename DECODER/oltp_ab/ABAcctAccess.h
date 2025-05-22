// ABAcctAccess.h

#if !defined(AFX_ABACCTACCESS_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABACCTACCESS_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABAcctAccess : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABAcctAccess() {};
	virtual ~ABAcctAccess() {};	

private:
	unsigned int m_iDevVRecTrk;
	unsigned char m_iDevSecCodeOvr;

	// Device - DID
	unsigned char m_iDevDidCitType;
	unsigned char m_iDevDidOthCit;

	//Device - CB
	unsigned __int64 m_iDevCBEscNo;
	unsigned short m_iDevCBCMSRej;
	unsigned char m_iDevCBSvt;
	unsigned char m_iDevCBOnCourse;


	// Data - Terminal accessing account for account active error

	unsigned char m_iSrcType;


	// source data - voice
	unsigned char m_iSrcVFEndNo;
	unsigned short m_iSrcVTermNo;
	unsigned int m_iSrcVLoc;

	// source data - DID
	unsigned int m_iSrcDidCitNo;
	unsigned int m_iSrcDidTermNo;
	unsigned int m_iSrcDidFEndNo;
	unsigned int m_iSrcDidCitType;


	// source data - CB BT
	unsigned int m_iSrcCBCentNo;
	unsigned int m_iSrcCBWinNo;
	unsigned int m_iSrcCBTermNo;
	unsigned int m_iSrcCBSysNo;

	// source data - OLD CB System
	unsigned int m_iSrcOldCentNo;
	unsigned int m_iSrcOldWinNo;
	unsigned int m_iSrcOldTermNo;
	unsigned int m_iSrcOldSysNo;

	// source data - Pre-Online
	unsigned int m_iSrcPolFileNo;
	unsigned int m_iSrcPolOffNo;
	unsigned long m_iMatNo;
	unsigned short m_iBatchDep;
	
	// Data - for okay or other error

	
	unsigned __int64 m_iNOVDivd;   // for Q208:  novelty dividend
	unsigned __int64 m_iNOVInv;		// for Q208: novelty investment
	unsigned __int64 m_iSBFoDivd;
	unsigned __int64 m_iSBInv;
	unsigned __int64 m_iDepWtw;
	unsigned __int64 m_iExp;
	unsigned __int64 m_iOnlWtwd;
	unsigned __int64 m_iCashWtwd;
	unsigned char m_iOnlWtwCnt;
	unsigned char m_iCashWtwCnt;
	unsigned short m_iSodTranNo;

	__int64 m_iFundAva;    // funds available
	__int64 m_iBankGd;   // bank guarentee
	__int64 m_iCurrDiv;  // unsettled dividend
	__int64 m_iPrevDiv;  // previous dividend
	__int64 m_iFbPayFor;   // soccer fo payout forfeited

	// Added (201108PSR)
	unsigned short      m_iAnonymous;			//Anonymous Account
	unsigned short      m_iCscCard;			    //Tranaction with CSC Card

};

#endif // !defined(AFX_ABAcctAccess_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
