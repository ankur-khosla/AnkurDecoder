// ABSystem.h: interface for the ABSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSYSTEM_H__5EE3F09B_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_ABSYSTEM_H__5EE3F09B_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "JCSystem.h"
#include "TBAccount.h"
#include "ABMsgTranslator.h"

class ABSystem  : public JCSystem
{
public:
	virtual char * DecMsg(const Msg *pMsg);
	int GetTerminalType(const Msg *pMsg, short m_iTerminalType);
	int GetCallSeq(long lMsgType, const Msg *pMsg);

	ABSystem();
	virtual ~ABSystem();
	short m_iTerminalType;
	TBAccount *m_pTBAccount;

protected:
	Terminal	*m_pTerminal;
	short TerminalType[1000][100];
	short CustSessionTable[10000][1000];
};

#endif // !defined(AFX_ABSYSTEM_H__5EE3F09B_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
