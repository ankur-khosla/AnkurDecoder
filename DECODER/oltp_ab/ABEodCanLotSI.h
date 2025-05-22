// ABEodCanLotSI.h

#if !defined(AFX_ABEODCANLOTSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEODCANLOTSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEodCanLotSI : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEodCanLotSI() {};
	virtual ~ABEodCanLotSI() {};	

private:

	unsigned short m_iSize;
	unsigned short m_iTranCode;
	unsigned short m_iTranNo;
	unsigned short m_iTranMerge;

	unsigned char m_iSrcSell;
	unsigned int m_iDrawYear;
	unsigned int m_iDrawNo;
	unsigned int m_iLotType;

	unsigned int m_iLUnitBet;
	unsigned int m_iLTtlCost;
};

#endif // !defined(AFX_ABEODCANLOTSI_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
