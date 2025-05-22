// CBMsgTranslator.h: interface for the CBMsgTranslator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBMSGTRANSLATOR_H__0EBEEA31_EB20_11D3_B3BD_00C04F79D485__INCLUDED_)
#define AFX_CBMSGTRANSLATOR_H__0EBEEA31_EB20_11D3_B3BD_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <memory.h>
#include "MsgTranslator.h"
#include "CBMsgDef.h"
#include "Terminal.h"
#include "JCLogger.h"
#include "CBLogger.h"
#include <vector>
#include "udtypedef.h"

#define DATETIMELEN 21
#define BUF_SIZE 8000 // size of per output result message

class Msg;
class CBMsgTranslator : public MsgTranslator
{
public:
	char * Translate(const long lMsgType, const Msg *pMsg);
	virtual char * TranslateAction(const Msg *pMsg);
	
	void pidToAsc(/* [in] */ unsigned short pidwu,
              /* [out]*/ char *pidstrs);

	void AddField(unsigned long lVal, int iOutput);
	void AddField64(unsigned _int64 lVal, int iOutput);
	void AddField(int iType, char *cpStr, int iOutput);

	short  
		BetTypebu(const union TSN  tsnu);
	unsigned int tsn19NVerifierlu(const union TSN tsnu);
	unsigned char tsnLocationbu(const union TSN  tsnu);
	unsigned short tsnCentrew(const union TSN  tsnu);
	const unsigned short tsnSysID2ParID(BOOL aptsnt, unsigned char sysidbu);
	unsigned short tsnSystemNumbu(const union TSN  tsnu);
	short tsnMtgDayw(const union TSN  tsnu);
	short tsnLotDraww(const union TSN  tsnu);
	short tsnTranDayw(const union TSN  tsnu);
	short tsnSwpDraww(const union TSN  tsnu);
	int tsnAccountl(const union TSN  tsnu);
	short tsnTranNumw(const union TSN  tsnu);
	unsigned short tsnWindowwu(const union TSN  tsnu);
	unsigned LONGLONG tsn19NTicketIDdu(const union TSN tsnu);

	CBMsgTranslator();
	virtual ~CBMsgTranslator();

	static const int m_iMsgCodeOffset;
	static const int m_iMsgCodeLen;

	unsigned short tsnVersionwu(const union TSN *tsn);

protected:
	virtual int Msn(unsigned char cMsgCode, const unsigned char *cp);
	virtual void PackHeader(char *cpStoreProcName, struct LOG *pMlog, const Msg *pMsg);

	// wc header
	virtual void WCHeader(char *cpStoreProcName, struct LOG *pMlog, const Msg *pMsg);

	// eft header
	virtual void EftHeader(struct LOG *pMlog, const Msg *pMsg);
	virtual char * TranslateHeader(const Msg *pMsg);
	// Error 
	virtual void GetError(struct LOG *pMlog, const Msg *pMsg);

	short	m_iSysNo;
	int		m_iMsgOrderNo;
	char	m_sSellingDate[20];
	char	m_sSysName[10];
	
	// Header members
	int		m_iMsgSize;
	int	m_iMsgCode;
	char	m_sTime[50];
	int		m_iLastLogSeq;
	char	m_sLastLogSeq[20];
	int		m_iStaffNo;
	int		m_iLogTermNo;
	short	m_iSysNo2;
	int		m_iChannelNo;
	short	m_iErrorCode;
	char	m_cTermType;
	int		m_iCentreNo;
	short	m_iWindowNo;
	char	m_cRetryFlag;
	char	m_cSameFlag;
	char	m_cTermType2;
	char	m_cPrelogFlag;
	char	m_cLateReplyFlag;
	char	m_cTimeoutFlag;
	char	m_cUpdateRcmsgFlag;
	char	m_cBtExcpFlag;
	char	m_cOthsysFlag;
	char	m_cBcsmsgFlag;
	char	m_cAccmodFlag;
	char	m_cPayDepFlag;
	char	m_cFakeRejFlag;
	int		m_iAcctNo;
	unsigned int m_iHardwareId;
	int		m_iMsn;
	int		m_iTrxnNo;
	unsigned char	m_cFrontEndNo;
	char	m_sFrontEndNo[10];
	unsigned char	m_cLineNo;
	char	m_sLineNo[10];
	unsigned char	m_cDropAddress;
	__int64		m_iCustomerTotal;
	__int64		m_iAccountTotal;

	// members of eft header
	char	m_cCloseMode;
	char	m_cSuperMode;
	char	m_cTestMode;
	char	m_cPaperLow;
	char	m_cPrinterFail;
	int		m_iEftPort;
	int		m_iEftSysId;
	int		m_iEftChannelNo;
	int		m_iEftInterMsn;
	__int64	m_iEftCardNo;
	int		m_iEftError;

	struct tm *tm_time;


	//q310 for bettype in cb_error
	char	m_cBetType;
	int		m_iTotalCost;

	//customer session id for CV Enhancement in EDW
	__int64 m_iCustSessionId;

	#define BETTYP_SB_PM			90      // pari-mutuel collated soccer bet
	#define BETTYP_SB_FO			91      // fix-odds collated soccer bet
	#define BETTYP_SB_EXO			92      // exotic soccer bet
	#define BETTYP_SB_AUP_PM        93      // all-up soccer bet parimutuel
	#define BETTYP_SB_AUP_FO_CTL    94      // controlled fixed odds allup bet
											// => an allup set is associated, need
											// to look up by first pool selected
	#define BETTYP_SB_AUP_FO_NON    95      // Non-controlled fixed odds allup bet
	#define BETTYP_SB_SEC_BET	    96      // SB section bet

	char buf[BUF_SIZE];


};

#endif // !defined(AFX_CBMSGTRANSLATOR_H__0EBEEA31_EB20_11D3_B3BD_00C04F79D485__INCLUDED_)
