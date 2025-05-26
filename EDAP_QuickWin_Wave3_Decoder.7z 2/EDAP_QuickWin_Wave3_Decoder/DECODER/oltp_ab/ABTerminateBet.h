// ABTerminateBet.h: interface for the ABTerminateBet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABTERMINATEBET_H__BBB2FB1A_960E_4F12_8CBD_C93280902232__INCLUDED_)
#define AFX_ABTERMINATEBET_H__BBB2FB1A_960E_4F12_8CBD_C93280902232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABTerminateBet : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABTerminateBet();
	virtual ~ABTerminateBet();
};

#endif // !defined(AFX_ABTERMINATEBET_H__BBB2FB1A_960E_4F12_8CBD_C93280902232__INCLUDED_)
