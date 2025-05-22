// ABPolDrCrAdj.h

#if !defined(AFX_ABPOLDRCRADJ_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABPOLDRCRADJ_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABPolDrCrAdj : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABPolDrCrAdj() {};
	virtual ~ABPolDrCrAdj() {};	

private:

	 __int64 m_iFundAva;
	 __int64 m_iBankGd;
	 __int64 m_iCurrDiv;
	 __int64 m_iPrevDiv;
	 __int64 m_iFbPayFor;

	unsigned __int64 m_iAmount;
	unsigned char m_cDrCrType;
	int m_iNegBal;
	char m_sRemarks[520];

};

#endif // !defined(AFX_ABPOLDRCRADJ_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
