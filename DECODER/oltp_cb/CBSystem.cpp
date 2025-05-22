// CTBSystem.cpp: implementation of the CBSystem class.
//
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CBMsgDef.h"
#include "CBLogger.h"
#include "CBSystem.h"
#include "Terminal.h"
#include "AllCBMsg.h"
#include "ExtractMgr.h"

#define TERM_POOL_SIZE 4096

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CBSystem::CBSystem()
{
	int i, j;

	// L42R1c_BK02 -- (by ben koo 16 Jan 2004)
	// temporaily change from 1000 to 10000 for window number
	// because sometime user was WRONGLY input 4 digits window number.
	for(i=0; i<10000; i++)
		for(j=0; j<1000; j++)
		{
			CustSessionTable[i][j] = 0;
			TerminalType[i][j][TERM_TYPE] = 0;
			TerminalType[i][j][OPT_MODE] = 0;
		}
}

CBSystem::~CBSystem()
{
}

char * CBSystem::DecMsg(const Msg *pMsg)
{
	CBMsgTranslator *pMsgTranslator=NULL;

	//long	lMsgType	= 	pMsg->BtoL((const unsigned char*)&pMsg->m_cpBuf[CBMsgTranslator::m_iMsgCodeOffset], CBMsgTranslator::m_iMsgCodeLen, 0, 0);
	long lMsgType = pMsg->m_iMsgCode;

	switch (lMsgType)
	{

		case LOG_SGN_C:
			pMsgTranslator=new CBSignOn();
			SetTerminalStatus(pMsg);
			break;

		case LOG_BET_C:
			pMsgTranslator=new CBBet();
			break;
		
		case LOG_SB_C:
			pMsgTranslator=new CBSBBet();
			break;

		case LOG_LOT_C:
			pMsgTranslator=new CBLottery();
			break;

		case LOG_CSHI_C:
			pMsgTranslator=new CBCashIn();
			break;

		case LOG_CSHO_C:
			pMsgTranslator=new CBCashOut();
			break;

		case LOG_CAN_C:
			pMsgTranslator=new CBCancel();
			break;

		case LOG_SGF_C:
			pMsgTranslator=new CBSignOff();
			break;

		case LOG_PAY_C:
		case LOG_REVPC_C:
			pMsgTranslator=new CBPayout();
			break;

		case LOG_TBD_C:
			pMsgTranslator=new CBTBDep();
			break;

		case LOG_CVI_C:
			pMsgTranslator=new CBCVIssue();
			break;

		case LOG_CVC_C:
 			pMsgTranslator=new CBCVCash();
			break;
	// comment start
			// EFT
		case LOG_EFTDEP_C:
			pMsgTranslator=new CBEftDep();
			break;

		case LOG_EFTWTW_C:
			pMsgTranslator=new CBEftWith();
			break;

		case LOG_EFTACB_C:
			pMsgTranslator=new CBEftBal();
			break;

		case LOG_EFTCVI_C:
		case LOG_EFTEMVCVI_C:
			pMsgTranslator=new CBEftCV();
			break;

		case LOG_EFTBKB_C:
			pMsgTranslator=new CBEftBal();
			break;

		case LOG_EFTXBT_C:
			pMsgTranslator=new CBEftFund();
			break;

		case LOG_EFTSTSP_C:
			pMsgTranslator=new CBEftSts();
			break;

		case LOG_EFTSER_C:
			pMsgTranslator=new CBEftErr();
			break;

		case LOG_RELTRM_C:
			pMsgTranslator=new CBRelease();
			break;

		case LOG_STPPAY_C:
			pMsgTranslator=new CBStopPay();
			break;

		case LOG_RLSTPY_C:
			pMsgTranslator=new CBStopPay();
			break;

		case LOG_SYSCLS_C:
			pMsgTranslator=new CBSysClose();
			break;

		case LOG_WC_C:
			pMsgTranslator=new CBPoolStartPay();
			break;

		case LOG_MSG_SBC:
			pMsgTranslator=new CBSbcPoolDef();
 			break;

		case LOG_DEP_C:
			pMsgTranslator=new CBEscCash();
 			break;

		default:
			pMsgTranslator=new CBMsgTranslator();
			break;
	}


	//pMsgTranslator->SetTerminalSet((CBTerminal*)m_pTerminal, TERM_POOL_SIZE);
	pMsgTranslator->SetMsgKey(m_lLoggerTapeId, m_iLoggerMsgOrderNo);

	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;

	short m_iTerminalType, m_iOperateMode;
	int session = 0;

	// if it is the same customer in the same center and same window number
	if (pMlog->hdr.btflagbu.samecus1 == 0)
		CustSessionTable[pMlog->hdr.centrelu][pMlog->hdr.windowwu]++;

	session = CustSessionTable[pMlog->hdr.centrelu][pMlog->hdr.windowwu];
	
	// Get Customer Session
	pMsgTranslator->m_iCustSession = session;
	// Get terminal type

	m_iTerminalType = TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][TERM_TYPE]; // get opt mode from sign on
	m_iOperateMode = TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][OPT_MODE]; // get opt mode from sign on
	
	pMsgTranslator->m_iTerminalType = m_iTerminalType;
	pMsgTranslator->m_iOperateMode = m_iOperateMode;
	
	char bufMsg[MSG_SIZE] = {0};
	char *buf = pMsgTranslator->Translate(lMsgType, pMsg);

	//memcpy(bufMsg,buf,sizeof(buf));
	strcpy_s(bufMsg,buf); // strcpy not working in release mode.
	//strcpy(bufMsg,buf);

	//m_iLoggerMsgOrderNo++;

	delete pMsgTranslator;
	pMsgTranslator = NULL;

	return bufMsg;
}

int CBSystem::SetInfo(const CtrlBlk *pCtrlBlk, char Date[20])
{
	if(!JCSystem::SetInfo(pCtrlBlk, Date))
	{
		return 0;
	}

	if(m_pStorage==NULL)
	{
		return 0;
	}

	int compare;
	compare = strcmp(pCtrlBlk->m_sBusiness_date, Date);
	if (compare != 0)
	{
		printf("Error - logger: Date mismatch (Input : %s, logger date :%s)\n", Date, pCtrlBlk->m_sBusiness_date);
		return(1);
	}

	FILE *stream;
	char temp[200];
	char name[50];
	sprintf(name, "bisc_interface_control.txt");

	if ((stream = fopen(name, "w"))!=NULL)
	{
		int type=0;
		if (m_pCtrlBlk->m_iSysNo == 1)
		{
			type = 101;
		}
		else if (m_pCtrlBlk->m_iSysNo == 2)
		{
			type = 102;
		}
		else if (m_pCtrlBlk->m_iSysNo == 3)
		{
			type = 103;
		}
		else if (m_pCtrlBlk->m_iSysNo == 4)
		{
			type = 104;
		}
		else
		{
			printf("Error of system no.\n");
			return(1);
		}

		char cMonth[13][4] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

		struct tm *loadtime;
		time_t aclock;
		time( &aclock );
		loadtime = localtime( &aclock );
		char cLoadTime[21];
		sprintf(cLoadTime, "%02d-%s-%d %02d:%02d:%02d", loadtime->tm_mday, cMonth[loadtime->tm_mon+1], loadtime->tm_year+1900, loadtime->tm_hour, loadtime->tm_min, loadtime->tm_sec);

		sprintf(temp, "%02d-%s-%d~|~%s~|~%d~|~1~|~0\n", m_pCtrlBlk->m_iDay, cMonth[m_pCtrlBlk->m_iMonth], m_pCtrlBlk->m_iYear, cLoadTime, type);
		fputs(temp, stream);
		fclose(stream);
	}

	return 0;
}

int CBSystem::GetTerminalType(const Msg *pMsg)
{
	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;
	short m_iTerminalType;

	m_iTerminalType = TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][TERM_TYPE]; // get opt mode from sign on
	return(m_iTerminalType);
}

int CBSystem::GetOptMode(const Msg *pMsg)
{
	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;
	short m_iTerminalType;

	m_iTerminalType = TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][OPT_MODE]; // get opt mode from sign on
	return(m_iTerminalType);
}

// USE when signon message to record the terminal status
void CBSystem::SetTerminalStatus(const Msg *pMsg)
{
	struct LOG *pMlog;
	short m_iTerminalType;
	pMlog					= (struct LOG *)pMsg->m_cpBuf;
	if (pMlog->hdr.centrelu>999 || pMlog->hdr.windowwu > 99)
	{
		return;
	}
	else
	{
		if (pMlog->hdr.codewu == 1) // Sign on message
		{
			TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][TERM_TYPE] = pMlog->d.bt.sgn.ttypebu;
			TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][OPT_MODE] = pMlog->d.bt.sgn.flagbu; // input Opt mode

			if (pMlog->d.bt.sgn.ttypebu == 2) // MTBT from terminal type
			{
				TerminalType[pMlog->hdr.centrelu][pMlog->hdr.windowwu][OPT_MODE] = 2;
			}
		}
	}
}

int CBSystem::CustSession(const Msg *pMsg)
{
	struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;
	int returnSession = 0;

	// if it is the same customer in the same center and same window number
	if (pMlog->hdr.btflagbu.samecus1 == 0) 
		CustSessionTable[pMlog->hdr.centrelu][pMlog->hdr.windowwu]++;
	
	returnSession = CustSessionTable[pMlog->hdr.centrelu][pMlog->hdr.windowwu];
	

	return (returnSession);
}

