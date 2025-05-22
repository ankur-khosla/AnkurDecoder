// CBSignOff.h: interface for the CBSignOff class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBSIGNOFF_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBSignOff_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBSignOff : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBSignOff() {};
	virtual ~CBSignOff() {};
	
private:
//	int						m_iInterMsn;
	char					m_cDisBcsFlag;
	short					m_cStCount[LOGBTSGF_CNT];
	int						m_iRaceSale;
	int						m_iCVSale;
	int						m_iLottSale;
	int						m_iTBSale;
	int						m_iCancelR;
	int						m_iCancelCV;
	int						m_iCancelLot;
	int						m_iCancelTB;
	int						m_iPayout;
	int						m_iPayDep;
	int						m_iEscDep;
	int						m_iEscWith;
	unsigned __int64		m_iTotalSale;
	unsigned __int64		m_iTolPayout;
	unsigned __int64		m_iTolCancel;
	__int64					m_iNetBal;
	__int64					m_iEscBal;
	unsigned __int64		m_iCashIn;
	unsigned __int64		m_iCashOut;
	unsigned __int64		m_iMSR;
	unsigned __int64		m_iMSP;
	char					m_cStaffSgfFlag;
};

#endif // !defined(AFX_CBSIGNOFF_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
