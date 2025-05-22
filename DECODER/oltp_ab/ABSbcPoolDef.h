// ABSbcPoolDef.h: interface for the ABSbcPoolDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSBCPOOLDEF_H__91587668_1C5C_4D43_98F2_557333DDD065__INCLUDED_)
#define AFX_ABSBCPOOLDEF_H__91587668_1C5C_4D43_98F2_557333DDD065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"

class ABSbcPoolDef : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

};

#endif // !defined(AFX_ABSBCPOOLDEF_H__91587668_1C5C_4D43_98F2_557333DDD065__INCLUDED_)
