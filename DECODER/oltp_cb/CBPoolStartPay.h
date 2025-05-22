// CBPoolStartPay.h: interface for the CCBPoolStartPay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBPOOLSTARTPAY_H__753ACE1E_DBDA_4F60_B21D_F9E87E337654__INCLUDED_)
#define AFX_CBPOOLSTARTPAY_H__753ACE1E_DBDA_4F60_B21D_F9E87E337654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBPoolStartPay : public CBMsgTranslator  
{
public:
	CBPoolStartPay();
	virtual ~CBPoolStartPay();
	virtual char * TranslateAction(const Msg *pMsg);
	char* GetBetType(char BetType, char Type[20]);
};

#endif // !defined(AFX_CBPOOLSTARTPAY_H__753ACE1E_DBDA_4F60_B21D_F9E87E337654__INCLUDED_)
