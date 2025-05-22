// ABRecall.h

#if !defined(AFX_ABRECALL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABRECALL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABRecall : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABRecall() {};
	virtual ~ABRecall() {};	

private:

	unsigned char m_iRecallType;
	char m_sStatementDate[30];
	unsigned int m_iAcctNo;

	unsigned int m_iBlkNo;
	unsigned short m_iBlkOffset;
	unsigned short m_iTranOffset;
	unsigned short m_iFileNo;
	unsigned short m_iTranNo;

};

#endif // !defined(AFX_ABRECALL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
