/////////////////////////////////////////////////////////////////////
//
// CBRelease.h: interface for the CBRelease class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBRELEASE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBRELEASE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBRelease : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBRelease() {};
	virtual ~CBRelease() {};	

	int m_iLocationId;
	short m_iWinNo;
	int m_iPhyTermNo;
	int m_iRelLtn;
	int m_iStaffNo;
	int m_iRaceSale;
	int m_iCVSale;
	int m_iLottSale;
	int m_iTBSale;
	int m_iCancelR;
	int m_iCancelCV;
	int m_iCancelLot;
	int m_iCancelTB;
	__int64 m_iPayout;
	char m_sPayout[20];
	int m_iPayDep;
	int m_iEscDep;
	int m_iEscWith;

};

#endif // !defined(AFX_CBRelease_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
