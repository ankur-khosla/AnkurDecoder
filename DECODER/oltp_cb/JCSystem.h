// JCSystem.h: interface for the JCSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JCSYSTEM_H__85B7D306_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_JCSYSTEM_H__85B7D306_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MsgTranslator;
class Terminal;
class Msg;
class Storage;
class CtrlBlk;
class CBMsgTranslator;

class JCSystem
{
public:
	virtual int SetInfo(const CtrlBlk *pCtrlBlk, char Date[20])=0;
	virtual void SetStorage(Storage *pStorage);
	virtual char * DecMsg(const Msg *pMsg)=NULL;
	JCSystem();
	virtual ~JCSystem();

protected:
	Storage *m_pStorage;
	const CtrlBlk *m_pCtrlBlk;
	long m_lLoggerTapeId;
	int m_iLoggerMsgOrderNo;
	int m_iCustSession;
};

#endif // !defined(AFX_JCSYSTEM_H__85B7D306_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
