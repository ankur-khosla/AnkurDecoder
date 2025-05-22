// CBSbcPoolDef.h: interface for the CBSbcPoolDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBSBCPOOLDEF_H__60F7FC15_0DCB_49B0_95F2_FCCC1C8D4B4C__INCLUDED_)
#define AFX_CBSBCPOOLDEF_H__60F7FC15_0DCB_49B0_95F2_FCCC1C8D4B4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"

class CBSbcPoolDef : public CBMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

};

#endif // !defined(AFX_CBSBCPOOLDEF_H__60F7FC15_0DCB_49B0_95F2_FCCC1C8D4B4C__INCLUDED_)
