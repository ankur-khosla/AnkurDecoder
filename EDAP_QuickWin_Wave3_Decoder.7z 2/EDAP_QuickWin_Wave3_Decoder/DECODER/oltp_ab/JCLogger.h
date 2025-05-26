// JCLogger.h: interface for the JCLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JCLOGGER_H__85B7D305_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_JCLOGGER_H__85B7D305_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

const	int	NO_ERR			= 0;
const	int OPEN_LOG_ERR	= 1;
const	int READ_LOG_ERR	= 2;
const	int END_OF_LOGGER	= 3;
const	int MSG_SIZE_ERR	= 4;

const	int NAME_SIZE		= 256;
#define BLOCK_SIZE			512;
#define LOG_UNIT_SIZE		50;		//New logger setting
const	int MSG_SIZE		= 8000; // size of per output result message
const	int PAYLOAD_HDR_SIZE = 35;  // payload header size. 27 > 35 (add the field cust_session_id of 8 bytes)
const	int PAYLOAD_EXT_SIZE = 512; // payload extra data size
const	int BINARY_MAX_SIZE = 8192; // payload extra data size

class CtrlBlk
{
public:
	CtrlBlk();
	virtual ~CtrlBlk();

	char m_sBusiness_date[20];
	int m_iSysNo;
	char m_cpSysName[30];
	int m_iDay;
	int m_iMonth;
	int m_iYear;
};

class Msg
{
public:
	int RestoreBitmap(const unsigned char *cpSrc, int iUnitLen, int iSize, unsigned char *cpDes) const;
	void TrnxDateTime(int iSeconds, char *cpDateTime) const;
	void TranslateDate(int iNumber, char *OutputDate) const;
	long DateToDay(unsigned long Date) const;
	char* DayToDate(int Year, int Day, char Date[]) const;
	char IsLeapYr(int Year) const;
	long AscHextoLong(unsigned char *cp, int iSize) const;
	long BtoL(const unsigned char *cp, int iSize, char HighByteFirst, char Signed) const;
	int BtoAscHex(unsigned char *cpSrc, int iSize, char *cpDest, int iLen) const;
	int GetCustSession(int CustSession);
	
	void Msg::Dump(char *buf, char *mt, char *ts, char *sf, char *ac, int iPoolCode, char *bline) const;

	Msg(int iMsgSize);
	virtual ~Msg();
	int m_iMsgSize;
	int m_iMsgYear;
	int m_iMsgMonth;
	int m_iMsgDay;
	unsigned short m_iMsgErr;
	int m_iBufSize;
	unsigned short m_iMsgCode;
	unsigned char *m_cpBuf;
	short m_iSysNo;
	int m_iCustSession;
	char SellingDate[20];
	unsigned short m_iMsgErrwu; // activity error code
	__time32_t		   m_iMsgTime;	 // activity timestamp
	unsigned __int64 txnidd = 0;	// transaction id. LOG.LOGHDR.txnidd;
	__time32_t		   m_iMsgSellTime;  // bet selling time
	unsigned int m_MsgBizDate;		// business date
	//unsigned __int64		m_iMsgTktid;	// TSN ticket id
	char m_iSysName[10];

	//unsigned short m_iAnonymous;  //Anonymous Flag (2011IBT)  (Removed 201108PSR)
	//char *msgBuf;
};

class JCLogger 	
{
public:	
	virtual void SetMsgSize(int iMsgSize);
	virtual const Msg * GetMsgObj(unsigned char *binArr, struct PAYLOAD_HDR *pHdr, int exLen);
	inline void SetMsgLenUnit(int iMsgLenUnitinByte)
	{
		m_iMsgLenUnitinByte = iMsgLenUnitinByte;
	}

	JCLogger();
	virtual ~JCLogger();
	CtrlBlk *m_pCtrlBlk;
	virtual void FreeMsg();//move it from protected

protected:
	Msg *m_pMsg;
//	CtrlBlk *m_pCtrlBlk;
	int m_iLogStatus;
	static int	m_iMsgLenUnitinByte;
};


#endif // !defined(AFX_JCLOGGER_H__85B7D305_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
