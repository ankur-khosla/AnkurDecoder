/////////////////////////////////////////////////////////////////////
//
// CBEftCV.h: interface for the CBEftCV class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBEFTCV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBEFTCV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEftCV : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	CBEftCV() {
		// <Marco Lui, 20050120>
		m_iOriginalEftAmount	= 0;
		m_iRemainingEftAmount	= 0;
		// </Marco Lui, 20050120>
	};
	virtual ~CBEftCV() {};	

	unsigned char	m_cHighRecNo;		
	unsigned int	m_iLocat;		
	unsigned int	m_iType;		
	unsigned int	m_iSecCode;		
	unsigned LONGLONG	m_iLowRecNo;		
	
	unsigned int	m_iCentreHighBit;	
	unsigned int	m_iCentreLowBit;	
	unsigned int	m_iWindow;		
	unsigned int	m_iSaleSysNo;			
	unsigned int	m_cNewTsnFlag;			
	unsigned int	m_iMeetingDayOfYear;	
	unsigned int	m_iSaleSys;	
	unsigned int	m_iNew;		
	unsigned int	m_iMeetDay;		
	unsigned int	m_iFileNo;			
	unsigned int	m_iAmount;					
	char m_sPan[20];
	unsigned char	m_cIssueFlag;			
	unsigned int	m_iCVSell;
	unsigned int	m_iCVPay;
	// <Marco Lui, 20050120>
	int		m_iOriginalEftAmount;
	int		m_iRemainingEftAmount;
	// </Marco Lui, 20050120>

};

#endif // !defined(AFX_CBEftCV_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
