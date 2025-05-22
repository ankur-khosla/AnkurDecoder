// CBSystem.h: interface for the CBSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSYSTEM_H__5EE3F09B_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_BSYSTEM_H__5EE3F09B_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "JCSystem.h"
#include "CBMsgTranslator.h"
#define TERM_TYPE 0
#define OPT_MODE 1

class CBSystem  : public JCSystem
{
public:
	virtual int SetInfo(const CtrlBlk *pCtrlBlk, char Date[20]);
	virtual char * DecMsg(const Msg *pMsg);
	void SetTerminalStatus(const Msg *pMsg);
	int GetTerminalType(const Msg *pMsg);
	int GetOptMode(const Msg *pMsg);
	int CustSession(const Msg *pMsg);

	CBSystem();
	virtual ~CBSystem();
	short m_iTerminalType;
	short m_iOptMode;

protected:
	Terminal	*m_pTerminal;
	short TerminalType[1000][100][2];
	short CustSessionTable[10000][1000];
};

#endif // !defined(AFX_BSYSTEM_H__5EE3F09B_E9CF_11D3_B3BD_00C04F79D485__INCLUDED_)
