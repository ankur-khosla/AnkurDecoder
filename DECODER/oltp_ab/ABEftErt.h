// ABEftErt.h

#if !defined(AFX_ABEftErt_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABEftErt_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABEftErt : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABEftErt() {};
	virtual ~ABEftErt() {};	

private:

	unsigned char m_cNBANo1;
	unsigned char m_cPinType1;
	
	unsigned char m_cNBANo2;
	unsigned char m_cPinType2;

	unsigned char m_cEftSubCode;


};

#endif // !defined(AFX_ABEftErt_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
