// Storage.h: interface for the Storage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORAGE_H__85B7D307_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_STORAGE_H__85B7D307_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const	int SQLSTATEMNT			= 0;
const	int STOREPROC			= 1;

const	int	STORE_NO_ERR		= 0;

const	int STORE_TYPE_NULL		= 0;
const	int STORE_TYPE_SP_NAME	= 1;
const	int STORE_TYPE_INTEGER	= 2;
const	int STORE_TYPE_STRING	= 3;
const	int STORE_TYPE_DATETIME	= 4;
const	int STORE_TYPE_NUMBER	= 5;
const	int STORE_TYPE_CHAR	= 6;

class ColDef
{
public:
	ColDef * GetNxtPtr(int iIdx);
	int IsOuputCol();
	ColDef * GetNxt();
	void AddNode(int iType, char *cpStr, int iOutput);
	void AddNode(long lVal, int iOutput);
	void AddNode(char cChar, int iOutput);
	char * GetVal();
	int GetType();
	ColDef(long lVal, int iOutput);
	ColDef(char *cpStr, int iOutput);
	ColDef(char cChar, int iOutput);
	ColDef(int iType, char *cpStr, int iOutput);
	virtual ~ColDef();

private:
	void init(int iType, char *cpStr, int iOutput);
	int m_iType;
	int m_iOutput;
	char m_cStr[1024];
	ColDef *m_pNxt;
};

class RecordDef
{
public:
	int	GetDelimitedText( char *);
	int GetColCount();
	void RedefineCol();
	ColDef * GetColPtr(int iIdx);
	void AddCol(long lVal, int iDec, int iOutput);
	void MoveNxt();
	ColDef * GetColDef();
	void MoveFirst();
	void AddCol1(unsigned long lVal, int iOutput);
	void AddCol164(unsigned _int64 lVal, int iOutput);
	void AddCol1(int iType, char *cpStr, int iOutput);
	RecordDef();
	virtual ~RecordDef();
	void	SetDelimiter( char *);

private:
	void Init();

	static char	m_sDelimiter[10];
	int m_iCount;
	ColDef *m_pCol;
	ColDef *m_pColIdx;
};

class DB_ExceptMsg
{
public:
	long m_lCode;
	char m_cCodeMean[128];
	char m_cSrc[128];
	char m_cDesc[256];
};

class Storage  
{
public:
	virtual void MoveToRec(int iIdx)=0;
	virtual void MoveFirstRec()=0;
	virtual RecordDef * GetRecord()=0;
	virtual int GetErrStatus()=0 {};
	virtual const DB_ExceptMsg * GetExceptMsg()=0 {};
	virtual void ClearExceptMsg()=0 {};
	virtual int ExecStoreProc(RecordDef *pRcdDef, long &lRetVal)=0 {};
	virtual int ExecStoreProc(RecordDef *pRcdDef, long &lRetVal, long StoreProcType)=0 {};
	virtual int ExecSQL(const char *cp)=0 {};
	virtual int Disconnect()=0 {};
	virtual int Connect()=0 {};
	virtual void SetPasswd(const char*cp)=0 {};
	virtual void SetUser(const char *cp)=0 {};
	virtual void SetServer(const char *cp)=0 {};
	virtual void SetProvider(const char *cp)=0 {};
	virtual void ErrHandler( int, const char *Msg )=0 {};

	Storage() {};
	virtual ~Storage() {};

protected:
	int m_iErrStatus;
	DB_ExceptMsg *m_pExceptMsg;

};

#endif // !defined(AFX_STORAGE_H__85B7D307_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
