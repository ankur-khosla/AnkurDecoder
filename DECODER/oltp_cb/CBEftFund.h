/////////////////////////////////////////////////////////////////////
//
// CBEftFund.h: interface for the CBEftFund class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEFTFUND_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEFTFUND_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftFund : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftFund() {};
	virtual ~CBEftFund() {};	

	unsigned char   m_iHighRecNo;
	unsigned LONGLONG	m_iLowRecNo;
	unsigned char   m_iLocRacTicket;
	unsigned char	m_iTsnBetType;
	unsigned short	m_iSaleSysNo;
	unsigned short	m_iNewTsnFlag;
	unsigned short	m_iDayOfYear;
	
	unsigned int	m_iFileNo;			
	unsigned int	m_iAmount;					
	char m_sPan[19];
	
};

#endif // !defined(AFX_CBEFTFUND_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
