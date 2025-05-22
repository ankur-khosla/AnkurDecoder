// ABBatchDep.h


#if !defined(AFX_ABBATCHDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABBATCHDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
//#include "acudef.h"

class ABBatchDep : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABBatchDep() {};
	virtual ~ABBatchDep() {};

private:
	unsigned char m_cValDay;
	unsigned char m_cValMon;
	unsigned short m_iValYear;
	unsigned char m_cCalDay;
	unsigned char m_cCalMon;
	unsigned short m_iCalYear;
	
	char m_sValueDate[20];
	char m_sCalDate[20];

	unsigned char m_cDepSendType; // deposit sender type
	unsigned int m_iBatchAcctNo;

	unsigned short m_iBankCode;
	char m_sBankCode[5];
	char m_sBankAcctNo[20];
	unsigned int m_iInputSeqNo;
	unsigned int m_iClubAcctNo;
	char m_sReqAcctNo[30];
	unsigned __int64 m_iAmount;
	
	unsigned int m_iReFee;
	unsigned int m_iIntSeqNo;
	unsigned char m_cChannelNo;
	
	__int64 m_iFundAva;
	__int64 m_iBankG;
	__int64 m_iCurDivd;
	__int64 m_iPrvDivd;
	__int64 m_iSBPayout;

	unsigned char m_cNBANo;


};

#endif // !defined(AFX_ABBATCHDEP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
