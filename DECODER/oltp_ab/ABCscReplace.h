// ABCscReplace.h

#if !defined(AFX_ABCSCREPLACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCSCREPLACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCscReplace : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCscReplace () {};
	virtual ~ABCscReplace () {};	

private:

	unsigned __int64 m_iOldCscId;  //Old CSC card id 
	unsigned __int64 m_iNewCscId;  //New CSC card id

	unsigned char m_cForfeitDep; //Forfeit Deposit Indicator (0=False, 1=True)
	unsigned char m_cWaiveDep;  //Waive Deposit Indicator (0=False, 1=True)

	unsigned __int64 m_iRefAmt;  //Refund Amount
	unsigned __int64 m_iDepAmt;  //Deposit Amount

};

#endif // !defined(AFX_ABCSCREPLACE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
