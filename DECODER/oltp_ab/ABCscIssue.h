// ABCscIssue.h

#if !defined(AFX_ABCSCISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCSCISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABCscIssue : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCscIssue () {};
	virtual ~ABCscIssue () {};	

private:


	unsigned __int64 m_iCscCardId;   //CSC Card ID
	unsigned __int64 m_iCscDepFee;   // Card deposit fee


};

#endif // !defined(AFX_ABCSCISSUE_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
