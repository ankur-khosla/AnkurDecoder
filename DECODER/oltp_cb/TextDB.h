// TextDB.h: interface for the TextDB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TextDB_H__80370B94_FE25_11D3_B3C2_00C04F79D485__INCLUDED_)
#define AFX_TextDB_H__80370B94_FE25_11D3_B3C2_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include "Storage.h"

typedef	struct	_msgFileMap
{
	char	*msgName;
	char	*fileName;
	FILE	*fp;
}	MsgFileMap;



const	long TXT_COM_INIT_ERR		=	0x00000010;

const	long TXT_CREATE_CONN_ERR	=	0x00001000;
const	long TXT_CONNECT_ERR		=	0x00001100;

const	long TXT_CREATE_CMD_ERR		=	0x00100000;
const	long TXT_CMD_EXEC_ERR		=	0x00110000;

const	long TXT_CREATE_RS_ERR		=	0x10000000;



class TextDB :  public Storage
{
public:
	void MakeConnStr();
	virtual void UnSetTrustConn();
	virtual void SetTrustConn();
	virtual void MoveToRec(int iIdx);
	virtual void MoveFirstRec();
	virtual RecordDef * GetRecord();
	virtual const DB_ExceptMsg * GetExceptMsg();
	virtual void ClearExceptMsg();
	virtual int ExecStoreProc(RecordDef *pRcdDef, long &lRetVal);
	virtual int ExecStoreProc(RecordDef *pRcdDef, long &lRetVal, long iStoreProcType);
	virtual int ExecSQL(const char *cp);
	virtual int Disconnect();
	virtual int Connect();
	virtual void SetConnectOpt(long lopt);
	virtual void SetPasswd(const char*cp);
	virtual void SetUser(const char *cp);
	virtual void SetServer(const char *cp);
	virtual void SetProvider(const char *cp);
	virtual void SetDefaDB(char *cp);
	virtual int GetErrStatus();
	virtual	void ErrHandler( int, const char *);
	virtual	char * const GetMsgType(int);

	int Get_SB_Select(char* string);

	TextDB();
	TextDB( bool m_bRecovery );
	virtual ~TextDB();

	virtual	int	CheckPoint();
protected:
	int		m_iMaxMsg;
	bool	m_bRecovery;	// Recovery Mode
//	virtual long TrapExceptMsg(_com_error &e);
//	virtual void UninitADO();
	virtual void Uninit();
//	virtual void InitADO();
	void	Init();

protected:
	int m_iConnected;
	int m_iComInited;

//	ADO_CLASS *m_adopObjs;
	char m_cProvider[128];
	char m_cServer[128];
	char m_cUser[128];
	char m_cPasswd[128];
	char m_cDefaDB[128];
	char m_cConnStr[257];
	char m_cSecurity[25];

	long m_lConnOpt;

	RecordDef m_recRec;

	static	MsgFileMap	m_msgFileMap[];
	long	m_iMsgCounter[100];
};





#endif // !defined(AFX_TextDB_H__80370B94_FE25_11D3_B3C2_00C04F79D485__INCLUDED_)
