// ABTxnEnquiry.h

#if !defined(AFX_ABTXNENQUIRY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABTXNENQUIRY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABTxnEnquiry : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABTxnEnquiry() {};
	virtual ~ABTxnEnquiry() {};	

private:

	unsigned char m_iTermType;
	unsigned short m_iTranNo;
	unsigned short m_iLen;

};

#endif // !defined(AFX_ABTXNENQUIRY_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
