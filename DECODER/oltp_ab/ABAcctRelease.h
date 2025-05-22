// ABAcctRelease.h

#if !defined(AFX_ABACCTRELEASE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABACCTRELEASE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABAcctRelease : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABAcctRelease() {};
	virtual ~ABAcctRelease() {};	

private:

	unsigned short m_iKeyStrCnt;
	unsigned char m_cErrStrCnt;
	unsigned char m_cRelCode;
	__int64 m_iBankGd;
	__int64 m_iCurrdiv;
	__int64 m_iPayFor;

	__int64 m_iFundAva;

};

#endif // !defined(AFX_ABACCTRELEASE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
