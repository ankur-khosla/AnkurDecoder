// Terminal.h: interface for the Terminal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERMINAL_H__5EE3F09A_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_TERMINAL_H__5EE3F09A_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Terminal  
{
public:
	Terminal();
	virtual ~Terminal();
	virtual void init()=0;
};

class CBTerminal : public Terminal
{
public:
	virtual void init();
	CBTerminal();
	virtual ~CBTerminal();

	static const int m_iSttTerm;
	static const int m_iSvtTerm;

	char m_cPhyTermNo[10];
	int m_iCentreNo;
	int	m_iWndNo;
	int m_iTermType;
	int m_iBatch_Seq;
	char CustSec[10000];
};

#endif // !defined(AFX_TERMINAL_H__5EE3F09A_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
