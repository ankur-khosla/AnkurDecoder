// CBMsgTranslator.cpp: implementation of the CBMsgTranslator class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "CBMsgTranslator.h"
#include "main.h"
#include "LOGDEF.h"
#include "loghdrdef.h"
#include "JCLogger.h"
#include "tsnvar.h"
#include "tsndef.h"
#include "ExtractMgr.h";

char m_cStr[1024] = "";
const char m_sDelimiter[] = "~|~";
const char m_sDelimiter_SimSel[] = "@|@";// for simple selection
int m_iCount = 0;

////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CBMsgTranslator::pidToAsc(	/* [in] */ unsigned short pidwu,
								/* [out]*/ char *pidstrs)
{
    unsigned int resultlu = 0;
    
    if(pidwu!= 0)
    {
/*
        resultlu = ((pidwu & 0x3F00) >> 2) + (pidwu & 0x003F);
        if((pidwu & 0x0040)==0)
            resultlu = resultlu | 0x1000;
        if((pidwu & 0x4000)==0)
            resultlu = resultlu | 0x2000;
*/
		struct BIN *bin = ( struct BIN * ) &resultlu;
		struct PID *pid = ( struct PID * ) &pidwu;

		bin->bit05 = pid->bit05;
		bin->bit611 = pid->bit813;
		bin->bit12 = ~pid->bit6;
		bin->bit13 = ~pid->bit14;
		bin->bit14 = pid->bit7;
		bin->bit15 = pid->bit15;

    }

    sprintf(pidstrs, "%04X", resultlu);
}

const int CBMsgTranslator::m_iMsgCodeOffset			= 2; 
const int CBMsgTranslator::m_iMsgCodeLen			= 1;



CBMsgTranslator::CBMsgTranslator()
		:	MsgTranslator()
{
	m_iCount = 0;
	memset(buf, 0, BUF_SIZE);
}


CBMsgTranslator::~CBMsgTranslator()
{
	//delete[] buf;
}


int CBMsgTranslator::Msn(unsigned char cMsgCode, const unsigned char *cp)
{
	int iMsn=0;
	if(cp!=NULL)
	{
		char cHigh;
		char cLow;
		if(cMsgCode<LOG_EFTSTS_C||cMsgCode>LOG_EFTDEP_C)
		{
			cHigh=cp[1];
			cLow=cp[0];
		} else {
			const unsigned char cMSNMask=0x3f;
			cHigh=cp[1]&cMSNMask;
			cLow=cp[0]&cMSNMask;
		}
		iMsn=cHigh*0x40+cLow;
	}
	return iMsn;
}

char * CBMsgTranslator::TranslateHeader(const Msg *pMsg)
{
	/*if(m_pStorage==NULL)
	{
		return (char*)(&NO_STORAGE_DEFINED);
	}*/

	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;
	
	if (pMsg->m_iMsgErrwu != 0)
	{

		GetError(pMlog, pMsg);

		return buf;
	}

	// check if the bet is from esc card, if so the message will not be decoded
	if (pMlog->hdr.accmod1 != 0)
	{
		if (pMlog->hdr.codewu != 7)
		{
			int accmod1 = pMlog->hdr.accmod1;
			return (char*)(&accmod1);
		}
		else
		{
			if (pMlog->hdr.trxnlu != 0)
			{
				return (char*)(&pMlog->hdr.trxnlu);
			}
		}
	}

	if (pMlog->hdr.prelog1 !=0)
	{
		return (char*)(&TRANSLATE_ERR);
	}
	/*	if(m_pTerminal==NULL)
	{
		return NO_TERMINAL_DEFINED;
	}
	*/
	/*char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	tm_time = localtime( &pMlog->hdr.timelu);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);*/

	return buf;

}


char * CBMsgTranslator::TranslateAction(const Msg *pMsg)
{
	char *hdrErr = TranslateHeader(pMsg);

	if (strlen(hdrErr) != 0 && strstr(hdrErr,m_sDelimiter)!=NULL)
	{
		return hdrErr;//error message
	}
	
	return (char*)(&NOT_IMPLEMENTED); // if the function is called, then message is not decoded. 
}

char * CBMsgTranslator::Translate(const long lMsgType, const Msg *pMsg)
{

	char *hdrErr = TranslateHeader(pMsg);

	if (strlen(hdrErr) != 0 && strstr(hdrErr, m_sDelimiter) != NULL)
	{
		return hdrErr;//error message
	}

	char *buf	= TranslateAction( pMsg);

	return buf;
}


void CBMsgTranslator::PackHeader(char *cpStoreProcName, struct LOG *pMlog, const Msg *pMsg)
{
	//Translator header
	m_iSysNo					= pMsg->m_iSysNo;
	m_iMsgOrderNo				= m_iLoggerMsgOrderNo;

	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	sprintf(m_sSellingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear);

// m_iCustomerSession

	m_iMsgSize = pMlog->hdr.sizew;		// size in byte
	m_iMsgCode = pMlog->hdr.codewu;		// message code
	__time32_t timelu = pMsg->m_iMsgTime; //pMlog->hdr.timelu;
	tm_time = _localtime32( &timelu);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

	strcpy(m_sSysName, pMsg->m_iSysName);
	
	m_iLastLogSeq		= pMlog->hdr.lgslu;					// last log sequence for BT/MAT
	sprintf(m_sLastLogSeq, "%d", m_iLastLogSeq);
	
	m_iStaffNo			= pMlog->hdr.stfl;					// staff no
	m_iLogTermNo		= pMlog->hdr.ltn.trmlu;				// logical terminal no
	m_iSysNo2			= pMlog->hdr.ltn.iscom.syswu;		// system no
	m_iChannelNo		= pMlog->hdr.ltn.iscom.chanwu;		// inter-system communication channel
// need to be 0 ?
	m_iErrorCode		= pMsg->m_iMsgErrwu; //pMlog->hdr.errwu;					// error
	m_cTermType			= pMlog->hdr.trmtypbu;				// terminal type
	m_iCentreNo			= pMlog->hdr.centrelu;				// centre no
	m_iWindowNo			= pMlog->hdr.windowwu;				// window no
	m_cRetryFlag		= pMlog->hdr.btflagbu.retry1;		// retry flag
	m_cSameFlag			= pMlog->hdr.btflagbu.samecus1;		// same coustomer
	m_cTermType2		= pMlog->hdr.btflagbu.dllpkt3;		// terminal type
	m_cPrelogFlag		= pMlog->hdr.prelog1;				// prelog
	m_cLateReplyFlag	= pMlog->hdr.laterpy1;				// late reply
	m_cTimeoutFlag		= pMlog->hdr.timeout1;				// external request timeout
	m_cUpdateRcmsgFlag	= pMlog->hdr.rcvmsg1;				// update rcvmsg.dat flag
	m_cBtExcpFlag		= pMlog->hdr.btexc1;				//bt exception transaction
	m_cOthsysFlag		= pMlog->hdr.othsys1;				// reply from other system
	m_cBcsmsgFlag		= pMlog->hdr.bcsmsg1;				// update bcsmsg.dat flag
	m_cAccmodFlag		= pMlog->hdr.accmod1;				// account is access flag
	m_cPayDepFlag		= pMlog->hdr.paydep1;				// payout deposit flag
	m_cFakeRejFlag		= pMlog->hdr.fakrej1;				// fake reject transaction flag
	m_iAcctNo			= pMlog->hdr.acclu;					// account no
	m_iHardwareId		= pMlog->hdr.hwidlu;				// hardware id
	char m_sHardwareId[10];
	sprintf(m_sHardwareId, "%04X", m_iHardwareId);
	if(strncmp( m_sHardwareId, "BA", 2) != 0 )
	{
		pidToAsc(m_iHardwareId, m_sHardwareId);
	}
	else {
		if ( strlen( m_sHardwareId ) > 9 )
			sprintf( &m_sHardwareId[9], "%s", "" ); // replace "\" with ""
	}

	m_iMsn				= pMlog->hdr.msnlu;					// msn/tran-id
	m_iTrxnNo			= pMlog->hdr.trxnlu;				// transaxtion no in account
	m_cFrontEndNo		= pMlog->hdr.febu;					// frontend no
	sprintf(m_sFrontEndNo, "%d", m_cFrontEndNo);
	m_cLineNo			= pMlog->hdr.linebu;				// line no
	sprintf(m_sLineNo, "%d", m_cLineNo);
	m_cDropAddress		= pMlog->hdr.dropbu;				// drop address
	m_iCustomerTotal	= pMlog->hdr.custotd;				// customer total
	m_iAccountTotal		= pMlog->hdr.acctotd;				// account total

	m_iCustSessionId = pMlog->hdr.custoseid;				// customer session id

	// Output header
	AddField(0, 0);
	AddField(m_iMsgCode, 0);//Again, add messsage code at first position for simple selection 
	AddField(m_iSysNo, 0);
	AddField(STORE_TYPE_STRING, m_sSysName, 0);
	AddField(STORE_TYPE_STRING, m_sSellingDate, 0);
	AddField(m_iMsgOrderNo, 0);
	
	//AddField(m_iCustSession, 0);	// Get form CBSystem, for details please see CBSystem.cpp line 166

	AddField64(m_iCustSessionId, 0); //customer session id for CV Enhancement in EDW
	
	AddField(m_iMsgSize, 0);
	AddField(m_iMsgCode, 0);
	AddField(STORE_TYPE_STRING, m_sTime, 0);
	AddField(STORE_TYPE_STRING, m_sLastLogSeq, 0);
	AddField(m_iStaffNo, 0);
	AddField(m_iLogTermNo, 0);
	AddField(m_iChannelNo, 0);
	AddField(m_iTerminalType, 0); // q407
	AddField(m_iCentreNo, 0);
	AddField(m_iWindowNo, 0);
	AddField(m_cRetryFlag, 0);
	AddField(m_cSameFlag, 0);
	AddField(m_cTermType2, 0);
	AddField(m_cPrelogFlag, 0);
	AddField(m_cLateReplyFlag, 0);
	AddField(m_cTimeoutFlag, 0);
	AddField(m_cUpdateRcmsgFlag, 0);
	AddField(m_cBtExcpFlag, 0);
	AddField(m_cOthsysFlag, 0);
	AddField(m_cBcsmsgFlag, 0);
	AddField(m_cAccmodFlag, 0);	// to indicate esc transaction
	AddField(m_cPayDepFlag, 0);
	AddField(m_cFakeRejFlag, 0);
	char m_sAccountNo[20];
	if (m_iAcctNo < 9999999)
	{
		sprintf(m_sAccountNo, "%07d", m_iAcctNo);
	}
	else
	{
		sprintf(m_sAccountNo, "%08d", m_iAcctNo);
	}
	AddField(STORE_TYPE_STRING, m_sAccountNo, 0);
	AddField(STORE_TYPE_STRING, m_sHardwareId, 0);
	AddField(m_iMsn, 0);
	AddField(m_iTrxnNo, 0);
	AddField(STORE_TYPE_STRING, m_sFrontEndNo, 0);
	AddField(STORE_TYPE_STRING, m_sLineNo, 0);
	AddField(m_cDropAddress, 0);

	AddField(m_iOperateMode, 0);		// Get from sign on for details please see CBSystem.cpp line 169

}

void CBMsgTranslator::AddField(unsigned long lVal, int iOutput)
{
	char cStr[30];
	unsigned int rVal;
	rVal = lVal;
	if (lVal > 2147483647)
		rVal = 2147483647;

	sprintf(cStr, "%u", rVal);
	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void CBMsgTranslator::AddField64(unsigned __int64 lVal, int iOutput)
{
	char cStr[60];
	//sprintf(cStr, "%u", itoa(lVal,cStr);
	_ui64toa(lVal, cStr, 10);

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void CBMsgTranslator::AddField(int iType, char *cpStr, int iOutput)
{
	sprintf(m_cStr, "%s", cpStr);
	if (m_iCount == 2)
		strcat(buf, m_sDelimiter_SimSel);
	else if (m_iCount > 2)
		strcat(buf, m_sDelimiter);
	if (m_iCount >= 1)
		strcat(buf, m_cStr);

	m_iCount++;
}

void CBMsgTranslator::WCHeader(char *cpStoreProcName, struct LOG *pMlog, const Msg *pMsg)
{
	//Translator header
	m_iSysNo					= pMsg->m_iSysNo;
	m_iMsgOrderNo				= m_iLoggerMsgOrderNo;	
	m_iMsgCode					= pMlog->hdr.codewu;

	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	sprintf(m_sSellingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear);

// m_iCustomerSession

	m_iMsgSize = pMlog->hdr.sizew;		// size in byte
	m_iMsgCode = pMlog->hdr.codewu;		// message code
	__time32_t timelu = pMsg->m_iMsgTime; //pMlog->hdr.timelu;
	tm_time = _localtime32( &timelu);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

	strcpy(m_sSysName, pMsg->m_iSysName);
	
	m_iLastLogSeq		= pMlog->hdr.lgslu;					// last log sequence for BT/MAT
	sprintf(m_sLastLogSeq, "%d", m_iLastLogSeq);
	
	// Output header
	AddField(0, 0);
	AddField(m_iMsgCode, 0);//Again, add messsage code at first position for simple selection 
	AddField(STORE_TYPE_STRING, m_sSysName, 0);
	AddField(STORE_TYPE_STRING, m_sSellingDate, 0);
	AddField(m_iMsgOrderNo, 0);
	__time32_t timelu_t = pMsg->m_iMsgTime; //pMlog->hdr.timelu;
	tm *tm_time		= _localtime32( &timelu_t);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
	AddField(STORE_TYPE_STRING, m_sTime, 0);
}

void CBMsgTranslator::EftHeader(struct LOG *pMlog, const Msg *pMsg)
{
	m_cCloseMode	= pMlog->d.eft.hdr.eftflag.close1;		// terminal in closed mode
	m_cSuperMode	= pMlog->d.eft.hdr.eftflag.super1;		// terminal in superviosr mode
	m_cTestMode		= pMlog->d.eft.hdr.eftflag.test1;		// terminal in test mode
	m_cPaperLow		= pMlog->d.eft.hdr.eftflag.pprlow1;		// paper low detected
	m_cPrinterFail	= pMlog->d.eft.hdr.eftflag.prtfai1;		// printer fails
	//m_iEftPort		= pMlog->d.eft.hdr.portw;				// eft port no.
	m_iEftPort		= 0;				// q408 eft port no = 0
	m_iEftSysId		= pMlog->d.eft.hdr.sysidw;				// account betting system id
	m_iEftChannelNo	= pMlog->d.eft.hdr.chanwu;				// channel no.
	m_iEftInterMsn	= pMlog->d.eft.hdr.ismsnlu;				// inter-system msn
	m_iEftCardNo	= pMlog->d.eft.hdr.carddu;				// card no.
	m_iEftError		= pMsg->m_iMsgErrwu;//pMlog->d.eft.hdr.errorwu;				// eft error
	m_iMsgCode		= pMlog->hdr.codewu;

	// Output
	//AddField(0, 0);//Added by paul ou 2016.9.1, for consistent output
	//AddField(m_iMsgCode, 0);//Again, add messsage code at first position for simple selection 
	AddField(m_cCloseMode, 0);
	AddField(m_cSuperMode, 0);
	AddField(m_cTestMode, 0);
	AddField(m_cPaperLow, 0);
	AddField(m_cPrinterFail, 0);
	AddField(m_iEftPort, 0);
	AddField(m_iEftSysId, 0);
	AddField(m_iEftChannelNo, 0);
	AddField(m_iEftInterMsn, 0);
	AddField(m_iEftCardNo, 0);
	AddField(m_iEftError, 0);
}

void CBMsgTranslator::GetError(struct LOG *pMlog, const Msg *pMsg)
{
	//Translator header
	m_iSysNo					= pMsg->m_iSysNo;
	m_iMsgOrderNo				= m_iLoggerMsgOrderNo;
	//m_iMsgCode					= pMlog->hdr.codewu;
	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	sprintf(m_sSellingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear);
	m_iMsgSize = pMlog->hdr.sizew;		// size in byte
	m_iMsgCode = pMlog->hdr.codewu; //LOGAB_CODE_ERR;//pMlog->hdr.codewu;		// message code
	__time32_t timelu = pMsg->m_iMsgTime; //pMlog->hdr.timelu;
	tm_time = _localtime32( &timelu);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

	strcpy(m_sSysName, pMsg->m_iSysName);
	
	m_iLastLogSeq		= pMlog->hdr.lgslu;					// last log sequence for BT/MAT
	sprintf(m_sLastLogSeq, "%d", m_iLastLogSeq);
	
	m_iStaffNo			= pMlog->hdr.stfl;					// staff no
	m_iLogTermNo		= pMlog->hdr.ltn.trmlu;				// logical terminal no
	m_iSysNo2			= pMlog->hdr.ltn.iscom.syswu;		// system no
	m_iChannelNo		= pMlog->hdr.ltn.iscom.chanwu;		// inter-system communication channel
// need to be 0 ?
	m_iErrorCode		= pMsg->m_iMsgErrwu;//pMlog->hdr.errwu;					// error
	m_cTermType			= pMlog->hdr.trmtypbu;				// terminal type
	m_iCentreNo			= pMlog->hdr.centrelu;				// centre no
	m_iWindowNo			= pMlog->hdr.windowwu;				// window no
	m_cRetryFlag		= pMlog->hdr.btflagbu.retry1;		// retry flag
	m_cSameFlag			= pMlog->hdr.btflagbu.samecus1;		// same coustomer
	m_cTermType2		= pMlog->hdr.btflagbu.dllpkt3;		// terminal type
	m_cPrelogFlag		= pMlog->hdr.prelog1;				// prelog
	m_cLateReplyFlag	= pMlog->hdr.laterpy1;				// late reply
	m_cTimeoutFlag		= pMlog->hdr.timeout1;				// external request timeout
	m_cUpdateRcmsgFlag	= pMlog->hdr.rcvmsg1;				// update rcvmsg.dat flag
	m_cBtExcpFlag		= pMlog->hdr.btexc1;				//bt exception transaction
	m_cOthsysFlag		= pMlog->hdr.othsys1;				// reply from other system
	m_cBcsmsgFlag		= pMlog->hdr.bcsmsg1;				// update bcsmsg.dat flag
	m_cAccmodFlag		= pMlog->hdr.accmod1;				// account is access flag
	m_cPayDepFlag		= pMlog->hdr.paydep1;				// payout deposit flag
	m_cFakeRejFlag		= pMlog->hdr.fakrej1;				// fake reject transaction flag
	m_iAcctNo			= pMlog->hdr.acclu;					// account no
	m_iHardwareId		= pMlog->hdr.hwidlu;				// hardware id
	char m_sHardwareId[10];
	sprintf(m_sHardwareId, "%04X", m_iHardwareId);
	if(strncmp( m_sHardwareId, "BA", 2) != 0 )
	{
		pidToAsc(m_iHardwareId, m_sHardwareId);
	}
	else {
		if ( strlen( m_sHardwareId ) > 9 )
			sprintf( &m_sHardwareId[9], "%s", "" );
	}
	m_iMsn				= pMlog->hdr.msnlu;					// msn/tran-id
	m_iTrxnNo			= pMlog->hdr.trxnlu;				// transaxtion no in account
	m_cFrontEndNo		= pMlog->hdr.febu;					// frontend no
	sprintf(m_sFrontEndNo, "%d", m_cFrontEndNo);
	m_cLineNo			= pMlog->hdr.linebu;				// line no
	sprintf(m_sLineNo, "%d", m_cLineNo);
	m_cDropAddress		= pMlog->hdr.dropbu;				// drop address
	m_iCustomerTotal	= pMlog->hdr.custotd;				// customer total
	m_iAccountTotal		= pMlog->hdr.acctotd;				// account total

	m_iCustSessionId = pMlog->hdr.custoseid;				// customer session id

	m_cBetType = 99; // init to 99 to avoid random value
	m_iTotalCost = 0;  // init to -99 to avoid random value
		
	//Q310
	if (m_iMsgCode == 3) //racing bet
	{
		m_cBetType			= pMlog->d.bt.rac.bet.d.hdr.bettypebu;	// bet type
		m_iTotalCost		= pMlog->d.bt.rac.bet.d.hdr.costlu;		// total cost in cents
	}
	else if (m_iMsgCode == 4 ) // lottery 
	{
		m_cBetType			= pMlog->d.bt.lot.bet.d.hdr.bettypebu;	// bet type
		m_iTotalCost		= pMlog->d.bt.lot.bet.d.hdr.costlu;		// total cost in cents
	}
	else if (m_iMsgCode == 26  )  // sb 
	{
		m_cBetType			= pMlog->d.bt.sb.d.bet.bet.hdr.bettypebu;	// bet type
		m_iTotalCost		= pMlog->d.bt.sb.d.bet.bet.hdr.costlu;		// total cost in cents
		
		if (m_cBetType == 19)
		{
			m_cBetType = BETTYP_SB_PM;      // pari-mutuel collated soccer bet
			//sprintf(m_sBetType,"SB_PM");
		}
		else if (m_cBetType == 20)
		{
			m_cBetType = BETTYP_SB_FO;		// fix-odds collated soccer bet
			//sprintf(m_sBetType, "SB_FO");
		}
		else if (m_cBetType == 21)
		{
			m_cBetType = BETTYP_SB_EXO;		// exotic soccer bet
			//sprintf(m_sBetType, "SB_EXO");
		}
		else if (m_cBetType == 22)
		{
			m_cBetType = BETTYP_SB_AUP_PM;  // all-up soccer bet parimutuel
			//sprintf(m_sBetType, "SB_AUP_PM");
		}
		else if (m_cBetType == 23)
		{
			m_cBetType = BETTYP_SB_AUP_FO_CTL;  // controlled fixed odds allup bet
											// => an allup set is associated, need
											// to look up by first pool selected
			//sprintf(m_sBetType, "SB_AUP_FO_CTL");
		}
		else if (m_cBetType == 24)
		{
			m_cBetType = BETTYP_SB_AUP_FO_NON;  // Non-controlled fixed odds allup bet
			//sprintf(m_sBetType, "SB_AUP_FO_NON");
		}
		else if (m_cBetType == 25)
		{
			m_cBetType = BETTYP_SB_SCT_FO;  // SECTION BET
			//sprintf(m_sBetType, "SB_SEC_BET");
		}
//		else
//		{
			//sprintf(m_sBetType, "UNKNOW_SB");
//		}

	}



	// Output header
	AddField(0, 0);
	AddField(LOGAB_CODE_ERR, 0);//50001; Again, add messsage code at first position for simple selection 
	AddField(m_iSysNo, 0);
	AddField(STORE_TYPE_STRING, m_sSysName, 0);
	AddField(STORE_TYPE_STRING, m_sSellingDate, 0);
	AddField(m_iMsgOrderNo, 0);
	AddField(m_iErrorCode, 0);
	//AddField(m_iCustSession, 0);	// Get form CBSystem, for details please see CBSystem.cpp line 166

	AddField64(m_iCustSessionId, 0); //customer session id for CV Enhancement in EDW
	
	AddField(m_iMsgSize, 0);
	AddField(m_iMsgCode, 0);
	AddField(STORE_TYPE_STRING, m_sTime, 0);
	AddField(STORE_TYPE_STRING, m_sLastLogSeq, 0);
	AddField(m_iStaffNo, 0);
	AddField(m_iLogTermNo, 0);
	AddField(m_iChannelNo, 0);
	AddField(m_iTerminalType, 0);	// q407
	AddField(m_iCentreNo, 0);
	AddField(m_iWindowNo, 0);
	AddField(m_cRetryFlag, 0);
	AddField(m_cSameFlag, 0);
	AddField(m_cTermType2, 0);
	AddField(m_cPrelogFlag, 0);
	AddField(m_cLateReplyFlag, 0);
	AddField(m_cTimeoutFlag, 0);
	AddField(m_cUpdateRcmsgFlag, 0);
	AddField(m_cBtExcpFlag, 0);
	AddField(m_cOthsysFlag, 0);
	AddField(m_cBcsmsgFlag, 0);
	AddField(m_cAccmodFlag, 0);	// to indicate esc transaction
	AddField(m_cPayDepFlag, 0);
	AddField(m_cFakeRejFlag, 0);
	char m_sAccountNo[20];
	if (m_iAcctNo < 9999999)
	{
		sprintf(m_sAccountNo, "%07d", m_iAcctNo);
	}
	else
	{
		sprintf(m_sAccountNo, "%08d", m_iAcctNo);
	}
	AddField(STORE_TYPE_STRING, m_sAccountNo, 0);
	AddField(STORE_TYPE_STRING, m_sHardwareId, 0);
	AddField(m_iMsn, 0);
	AddField(m_iTrxnNo, 0);
	AddField(STORE_TYPE_STRING, m_sFrontEndNo, 0);
	AddField(STORE_TYPE_STRING, m_sLineNo, 0);
	AddField(m_cDropAddress, 0);

	AddField(m_iOperateMode, 0);		// Get from sign on for details please see CBSystem.cpp line 169

	int payment_flag=0;
	long new_high_rec_no=0;
	long new_low_rec_no=0;
	long new_tsn_bet_type=0;
	long new_sales_sys_no=0;
	int		m_iMeetingDayOfYear;
	char	m_sMeetingDate[20];
	char    m_sPayTime[20];

	memset( m_sMeetingDate, 0, sizeof( m_sMeetingDate ) );
	memset( m_sPayTime, 0, sizeof( m_sPayTime ) );

	if ( m_iMsgCode == LOG_PAY_C )
	{
		union TSN tsn = pMlog->d.bt.ccp.tsn;

		int m_cNewTsnFlag = tsnVersionwu(&tsn); // tsn version
		new_tsn_bet_type = tsnBetTypebu(tsn); // bet type
		new_sales_sys_no = tsnSystemNumbu(tsn); // sale system no
		new_high_rec_no = new_tsn_bet_type;

		//int m_cNewTsnFlag			= pMlog->d.bt.ccp.tsn.s19t.w4.tsn16;		// new tsn flag
		if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
		{
			new_high_rec_no			= pMlog->d.bt.ccp.tsn.s19t.w2.rech12;		// high order bits of record no
			//new_tsn_bet_type		= pMlog->d.bt.ccp.tsn.s19t.w1.type5;	// bet type
			new_low_rec_no			= pMlog->d.bt.ccp.tsn.s19t.reclwu;		// low order bits of record no
			//new_sales_sys_no		= pMlog->d.bt.ccp.tsn.s19t.w1.sys3;		// sale system no
			m_iMeetingDayOfYear		= pMlog->d.bt.ccp.tsn.s19t.w4.day9;		// meeting day of year
		}
		else
		{
			new_low_rec_no = tsn19NTicketIDdu(tsn);			
		}	

		char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
		struct	tm *tm_PayTime;

		if ( (new_sales_sys_no == 0 && m_cNewTsnFlag == 1 && new_tsn_bet_type == 4 ) || new_tsn_bet_type == 8)
		{
			__time32_t payTime = pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payTime;
			tm_PayTime			= _localtime32(&payTime);
			if (pMlog->d.bt.ccp.d.sb.info.bet.bet.hdr.payTime > 0)
			{
				sprintf(m_sPayTime, "%02d-%s-%d %02d:%02d:%02d", tm_PayTime->tm_mday, m_sMonths[tm_PayTime->tm_mon+1], tm_PayTime->tm_year+1900, tm_PayTime->tm_hour, tm_PayTime->tm_min, tm_PayTime->tm_sec);
			}
		}
		else
		{
			__time32_t payTime = pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime;
			tm_PayTime			= _localtime32(&payTime);
			if (pMlog->d.bt.ccp.d.bet.bet.newbet.h.payTime > 0)
			{
				sprintf(m_sPayTime, "%02d-%s-%d %02d:%02d:%02d", tm_PayTime->tm_mday, m_sMonths[tm_PayTime->tm_mon+1], tm_PayTime->tm_year+1900, tm_PayTime->tm_hour, tm_PayTime->tm_min, tm_PayTime->tm_sec);
			}
		}

	}

	AddField(payment_flag, 0);
	AddField(STORE_TYPE_STRING, m_sPayTime, 0);
	AddField(new_high_rec_no, 0);
	AddField(new_low_rec_no, 0);
	AddField(new_tsn_bet_type, 0);
	AddField(new_sales_sys_no, 0);
	AddField(m_cBetType, 0);  // new in q310
	AddField(m_iTotalCost, 0);   // new in q310
}
