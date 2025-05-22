// Account.cpp: implementation of the Account class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "TBAccount.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Account::Account()
{

}

Account::~Account()
{

}

void Account::init()
{

}

const int TBAccount::m_iSttTerm=32;
const int TBAccount::m_iSvtTerm=34;

TBAccount::TBAccount()
{
	init();
}

TBAccount::~TBAccount()
{

}

void TBAccount::init()
{
	m_cPhyTermNo[0]=NULL;
	m_sAccountNo[0]=NULL;
	m_iCentreNo=0;
	m_iWndNo=0;
	m_iTermType=0;
	m_iBatch_Seq=0;
	m_iCustNo=0;
	m_iLoop=0;
	m_iTtlAcct=0;
	m_iSame=0;

for (long i=0; i<100000000; i++)
	{
		m_iCallSeq[i]=0;
	}
}

void TBAccount::AsCallSeq(long acctno)	// increase call sequence (TBMsgTranslator.cpp)
{
	m_iCallSeq[acctno]++;
}


int TBAccount::GetCallSeq(long acctno)	// get call sequence (TBMsgTranslator.cpp)
{
	return (m_iCallSeq[acctno]);
}

