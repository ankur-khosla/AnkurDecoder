// CBEscCash.h: interface for the CBEscCash class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBESCCASH_H__7033B022_8561_4350_A14A_A40CE301634A__INCLUDED_)
#define AFX_CBESCCASH_H__7033B022_8561_4350_A14A_A40CE301634A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBEscCash : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

};

#endif // !defined(AFX_CBESCCASH_H__7033B022_8561_4350_A14A_A40CE301634A__INCLUDED_)
