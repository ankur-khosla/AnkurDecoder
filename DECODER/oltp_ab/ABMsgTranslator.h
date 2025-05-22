// ABMsgTranslator.h: interface for the ABMsgTranslator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABMsgTRANSLATOR_H__0EBEEA31_EB20_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_ABMsgTRANSLATOR_H__0EBEEA31_EB20_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory.h>
#include <string.h>
#include "MsgTranslator.h"
#include "JCLogger.h"
#include "ABLogger.h"
#include "ABMsgDef.h"
#include "TBAccount.h"
#include <vector>

#define DATETIMELEN 21
#define BUF_SIZE 8000 // size of per output result message
class Msg;
class ABMsgTranslator : public MsgTranslator
{
public:
	char * Translate(const long lMsgType, const Msg *pMsg);
	char * Translate(long lWCMsg, const long lWcMsgType, const Msg *pMsg);
	char* GetWCBetType(char BetType, char Type[20]);
	virtual char * TranslateAction(const Msg *pMsg);
	virtual void SetTBAccount(TBAccount *pTerm);
	virtual	void DecErrHandler( int, const Msg*, Storage*);
	void pidToAsc(/* [in] */ unsigned short pidwu,/* [out]*/ char *pidstrs);

	ABMsgTranslator();
	virtual ~ABMsgTranslator();

	static const int m_iMsgCodeOffset;
	static const int m_iMsgCodeLen;

	void AddField(unsigned long lVal, int iOutput);
	void AddField(unsigned int lVal, int iOutput);
	void AddField(long lVal, int iOutput);
	void AddField(int lVal, int iOutput);
	void AddField(long lVal, int iDec, int iOutput);
	void AddField64(unsigned _int64 lVal, int iOutput);
	void AddField64(_int64 lVal, int iOutput);
	void AddField(int iType, char *cpStr, int iOutput);

	//TBAccount *m_pTBAccount;
	//static std::vector<char*> v_SimSel;

protected:
	virtual int Msn(unsigned char cMsgCode, const unsigned char *cp);
	virtual void PackHeader(char *cpStoreProcName, struct LOGAB *pMlog, const Msg *pMsg);
	virtual char * TranslateHeader(const Msg *pMsg);
	// wc header
	virtual void WCHeader(char *cpStoreProcName, struct LOGAB *pMlog, const Msg *pMsg);

	// Error 
	virtual void GetError(struct LOGAB *pMlog, const Msg *pMsg);

	short	m_iSysNo;
	int		m_iMsgOrderNo;
	char	m_sSellingDate[20];
	char	m_sSysName[10];
	TBAccount *m_pTBAccount;

	unsigned int		m_iMsgSize;
	unsigned int		m_iMsgCode;
	unsigned int		m_iErrCode;			// error code
	unsigned char		m_iTrapCode;		// Trap message code for BCS
	unsigned int		m_iStaffNo;			// staff number
	unsigned int		m_iLogTermNo;		// logical terminal number
	unsigned int		m_iAcctNo;			// account number
	unsigned char		m_iFileNo;			// file # of account file [0=overflow]
	unsigned int		m_iBlockNo;			// block # of account file
	unsigned int		m_iOverflowNo;		// overflow block # if overflow required
	unsigned int		m_iOffsetUnit;		// offset to account unit
	unsigned int		m_iTranNo;			// transaction number
	unsigned int        m_iLastLogSeq;      // last log sequence
	unsigned int        m_iMsnNo;			// msn
  
	unsigned char       m_iExtSysType;		// external request type
	unsigned short      m_iCatchUp;			// catch up previous transaction required
											// during recovery
	unsigned short      m_iBtExcept;		// bt exception transaction, do not update
											// last activity of corresponding tdtbt
											// entry (this include late reply, reverse
											// reply, non-msn protect transaction,
											// unsolicited transaction done for
											// corresponding bt, etc. )
	unsigned short      m_iOtherSys;		// message to other system
	unsigned short      m_iPreLog;			// pre-log
	unsigned short      m_iTimeout;			// external request timeout
	unsigned short      m_iLateReply;		// late reply (reverse is required, msnlu
											// saves the transaction id to be reversed)
	unsigned short      m_iBcsMsg;			// upadte bcsmsg.dat flag
	unsigned short      m_iRcvMsg;			// update rcvmsg.dat 
	unsigned short      m_iOverFlow;		// overflow required
	unsigned short      m_iEscRel;			// CB local account released flag
	unsigned short      m_iNoFlush;			// no need to flush for account release. this
											// happens when no solid tran. appended
	unsigned short      m_iTrainAcct;       // trainning account
	unsigned char		m_iSourceType;      // source type
	struct				tm *tm_time;
	char				m_sTime[50];		// time

	unsigned long		m_iMatNo;
	unsigned short		m_iBatchDep;
	char				m_cMatNo[15];

	unsigned char		m_cVoiceFENo;
	unsigned short		m_iVoiceTermNo;
	unsigned int		m_iVoiceLocId;

	unsigned int		m_iDidCitNo;
	unsigned char		m_cDidPseTermNo;
	unsigned char		m_cDidFENo;
	unsigned char		m_cDidCitType;

	unsigned int		m_iCBCenterNo;
	unsigned short		m_iCBWindowNo;
	unsigned short		m_iCBLogTermNo;
	unsigned char		m_cCBSysNo;

	unsigned int		m_iOldCenterNo;
	unsigned short		m_iOldWindowNo;
	unsigned short		m_iOldChanNo;
	unsigned char		m_cOldSysNo;

	unsigned char		m_cPolFileNo;
	unsigned int		m_iPolOffsetNo;

	__int64				m_iCallSeq;
	unsigned short		m_iSessionInfo;	

	char buf[BUF_SIZE];
};

#endif // !defined(AFX_ABMsgTRANSLATOR_H__0EBEEA31_EB20_11D3_B3BD_00C04F79D485__INCLUDED_)
