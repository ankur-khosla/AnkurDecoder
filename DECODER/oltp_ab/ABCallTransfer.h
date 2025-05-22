// ABCallTransfer.h

#if !defined(AFX_ABCALLTRANSFER_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCALLTRANSFER_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCallTransfer : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCallTransfer() {};
	virtual ~ABCallTransfer() {};	

private:

	unsigned int m_iAcctNo;
	unsigned char m_cAreaCode;

};

#endif // !defined(AFX_ABCALLTRANSFER_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
