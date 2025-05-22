// Account.h: interface for the Account class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Account_H__5EE3F09A_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_Account_H__5EE3F09A_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef long* LONG;

class Account  
{
public:
	Account();
	virtual ~Account();
	virtual void init()=0;
};

class TBAccount : public Account
{
public:
	virtual void init();
	TBAccount();
	virtual ~TBAccount();
	void AsCallSeq(long acctno);
	int GetCallSeq(long acctno);

	static const int m_iSttTerm;
	static const int m_iSvtTerm;

	char m_sAccountNo[20];
	char m_cPhyTermNo[10];
	int m_iCentreNo;
	int	m_iWndNo;
	int m_iTermType;
	int m_iBatch_Seq;
	int m_iCustNo;
	int m_iLoop;
//	char m_sCallSeq[500000][10];
//	int m_iCallSeq;
	short m_iCallSeq[100000000];
	int m_iSame;
	int m_iTtlAcct;
};


#endif // !defined(AFX_Account_H__5EE3F09A_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
