// ABCscReturn.h

#if !defined(AFX_ABCSCRETURN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCSCRETURN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCscReturn : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCscReturn () {};
	virtual ~ABCscReturn () {};	

private:

	unsigned char m_cWithdrawType; //Withdraw type (1=Autopay, 2=Cheque, 4=Cash)

	unsigned __int64 m_iCscId;  //CSC card id 

	unsigned char m_cForfeitDep; //Forfeit Deposit (0=False, 1=True)

	unsigned __int64 m_iAcctBal;  //Account Balance (in cents)
	unsigned __int64 m_iRefAmt;  //Refund Amount (in cents)


};

#endif // !defined(AFX_ABCSCRETURN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
