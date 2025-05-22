// JCLogger.h: interface for the JCLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JCLOGGER_H__85B7D305_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_JCLOGGER_H__85B7D305_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include "commdef.h"

const	int	NO_ERR			= 0;
const	int OPEN_LOG_ERR	= 1;
const	int READ_LOG_ERR	= 2;
const	int END_OF_LOGGER	= 3;
const	int MSG_SIZE_ERR	= 4;

const	int NAME_SIZE		= 256;
#define BLOCK_SIZE			512;
#define LOG_UNIT_SIZE		50;		//New logger setting
const	int MSG_SIZE		= 8000; // size of per output result message
const	int PAYLOAD_HDR_SIZE = 35; // payload header size. 27 > 35 (add the field cust_session_id of 8 bytes)
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

class LogUnit
{
public:
	LogUnit(int iBlkSize, int iUnitSize);
	virtual ~LogUnit();

	int m_iBlkSize;
	int m_iUnitSize;
	int m_iBufSize;
	int m_iCurrentIdx;
	unsigned char *m_cpBuf;
};

struct CVRelMsg
{
	unsigned __int64		tktid;	 // Ticket id; BET.ticketiddu
	unsigned int			verifier; // Verifier; BET.content
	unsigned int			businessDate; // create business date; BET.d.hdr.businessDate
	int						sellTime; //create time; 4 bytes; BET.d.hdr.sellTime
	unsigned __int64		selllogseqlu; // create activity id; BET.h.ptr.cv.selllogseqlu
	unsigned __int64		terseid; // terminal session id; 
	unsigned __int64		custoseid; // customer session id; 
	unsigned int			sellCentrelu; // create center no; BET.h.sellCentrelu
	unsigned int			sellWindowu; // create window no; BET.h.sellWindowu
	unsigned int			methodbu; // create method; BET.d.var.cv.methodbu
	unsigned int			currencyId; // currency id
	unsigned __int64		costlu; // CV amount; BET.d.hdr.costlu
	unsigned __int64		originallu; // CV original eft amount; BET.h.prveft.eft.originallu
	unsigned __int64		remainlu; // CV remain eft amount; BET.h.prveft.eft.remainlu
	unsigned char			claim1;		 // claimed flag; BET.d.hdr.sts.claim1
	unsigned char			paidfinal1;		 // paid flag; BET.d.hdr.sts.paidfinal1
	unsigned char			hdOfficeF;		 // head office flag
	unsigned __int64		retcenno;	// release to centre no
	unsigned int			payDate;  // paid bizdate; BET.h.payDate
	unsigned int			payTime; // paid time; BET.h.payTime
	unsigned int			paySysb; // paid system id; BET.h.paySysb
	unsigned __int64		paylogseqlu; // paid activity id; BET.h.ptr.cv.paylogseqlu
	unsigned __int64		paidTerseid; // paid terminal session id
	unsigned __int64		paidCustSessid; // paid customers session id
	unsigned int			payCentrelu; // paid centre no; BET.h.payCentrelu
	unsigned int			paidWinNo; // paid window no
	unsigned short			paidMethod;	   //paid method
	unsigned int			retdate;  // retention bizdate; BET.h.retdate
	unsigned int			payExpBizDate;  // payout expired bizdate
	unsigned int			purgedate;  // purge bizdate; BET.h.purgedate
	unsigned int			sts;  // ticket status; BET.d.h.sts
	unsigned __int64		lastactid; // last activity id
	unsigned __int64		rowver; // row version; BET.rowver
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
	int m_iMsgErr;
	int m_iBufSize;
	unsigned char *m_cpBuf;
	short m_iSysNo;
	int m_iCustSession;
	char SellingDate[20];
	unsigned short m_iMsgCode;
	unsigned short m_iMsgErrwu; // activity error code
	__time32_t		   m_iMsgTime = 0;	 // activity timestamp
	__time32_t		   m_iMsgSellTime = 0;  // bet selling time
	unsigned __int64		m_iMsgTktid;	// TSN ticket id
	struct CVRelMsg cvRel = {0};
	char m_iSysName[10];

};

class JCLogger 	
{
public:	
	short GetSysNo();
	virtual void SetMsgSize(int iMsgSize);
	inline void SetMsgLenUnit(int iMsgLenUnitinByte)
	{
		m_iMsgLenUnitinByte = iMsgLenUnitinByte;
	}

	JCLogger();
	virtual ~JCLogger();
	CtrlBlk *m_pCtrlBlk;
	virtual void FreeMsg();//move it from protected

	/*virtual const Msg * GetMsgObj(unsigned char *binArr, struct PAYLOAD_HDR *pHdr, int exLen);*/



protected:

protected:
	Msg *m_pMsg;
	LogUnit *m_pLogUnit;
//	CtrlBlk *m_pCtrlBlk;
	FILE *m_fpLogFile;
	int m_iLogStatus;
	static int	m_iMsgLenUnitinByte;
};


#endif // !defined(AFX_JCLOGGER_H__85B7D305_E5D1_11D3_B3BD_00C04F79D485__INCLUDED_)
