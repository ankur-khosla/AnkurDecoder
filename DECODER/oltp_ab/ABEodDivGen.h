// ABEodDivGen.h

#if !defined(AFX_ABEODDIVGEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEODDIVGEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEodDivGen : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEodDivGen() {};
	virtual ~ABEodDivGen() {};	

private:

	unsigned long m_iPMRacDiv;
	unsigned long m_iPMLotDiv;
	unsigned long m_iPMSbDiv;
	unsigned long m_iPMCanMk6SI;
	unsigned char m_cPMDivType;

	unsigned long m_iFORacDiv;
	unsigned long m_iFOLotDiv;
	unsigned long m_iFOSbDiv;
	unsigned long m_iFOCanMk6SI;
	unsigned char m_cFODivType;

	unsigned long m_iNextSodBal;
};

#endif // !defined(AFX_ABEODDIVGEN_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
