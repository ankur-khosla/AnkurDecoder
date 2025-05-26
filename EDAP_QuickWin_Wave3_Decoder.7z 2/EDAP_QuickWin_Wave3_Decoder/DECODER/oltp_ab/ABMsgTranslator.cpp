// ABMsgTranslator.cpp: implementation of the ABMsgTranslator class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include <stdlib.h>
#include "ABMsgTranslator.h"
//#include "main.h"
#include "LOGDEF.h"
#include "LOGDEF_AB.h"
//#include "loghdrdef.h"
#include "JCLogger.h"
#include "TBAccount.h"
#include "BDGWCMSGDEF.H"
#include <string>
using namespace std;


char m_cStr[1024]="";
const char m_sDelimiter [] = "~|~";
const char m_sDelimiter_SimSel [] = "@|@";// for simple selection
int m_iCount = 0;

////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void ABMsgTranslator::pidToAsc(	/* [in] */ unsigned short pidwu,
								/* [out]*/ char *pidstrs)
{
    unsigned int resultlu = 0;
	unsigned int firstCharlu = 0;
	unsigned char secondCharlu = 0;
	unsigned int finalPosition = 0;
    
    if(pidwu!= 0)
    {
/*
        resultlu = ((pidwu & 0x3F00) >> 2) + (pidwu & 0x003F);
        if((pidwu & 0x0040)==0)
            resultlu = resultlu | 0x1000;
        if((pidwu & 0x4000)==0)
            resultlu = resultlu | 0x2000;
*/
		firstCharlu = pidwu / 2600;
		secondCharlu = ((pidwu - firstCharlu * 2600) / 100) + 65;
		finalPosition = (pidwu - firstCharlu * 2600) - ((secondCharlu - 65) * 100);
	}

    sprintf(pidstrs, "%d%c%02d", firstCharlu, secondCharlu, finalPosition);
}

const int ABMsgTranslator::m_iMsgCodeOffset			= 2; 
const int ABMsgTranslator::m_iMsgCodeLen			= 1;

void	ABMsgTranslator::DecErrHandler( int iDecErr, const Msg* pMsg, Storage* a_pStoreMgr)
{

}


ABMsgTranslator::ABMsgTranslator() : MsgTranslator()
{
	m_iCount = 0;
	memset(buf, 0, BUF_SIZE);
}

ABMsgTranslator::~ABMsgTranslator()
{
}

//void ABMsgTranslator::SetTerminalSet(ABTerminal *pTerm, int iPoolSize)
//{
//	m_pTerminal = pTerm;
//	m_iNoOfTerminals = iPoolSize;
//}

int ABMsgTranslator::Msn(unsigned char cMsgCode, const unsigned char *cp)
{
	int iMsn=0;
/*	if(cp!=NULL)
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
*/
	return iMsn;
}

char * ABMsgTranslator::TranslateHeader(const Msg *pMsg)
{
	/*if(m_pStorage==NULL)
	{
		return (char*)(&NO_STORAGE_DEFINED);
	}*/

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	if ((pMsg->m_iMsgErrwu != 0) && ( pMlog->hdr.codewu != LOGAB_CODE_ACA ))
	{	
		GetError(pMlog, pMsg);

		//return (char*)(&TRANSLATE_ERR);
	}
	else
	{
		if( pMlog->hdr.prelog1 != 0 || 
			pMlog->hdr.laterpy1 != 0 || 
			pMlog->hdr.timeout1 != 0 ||
			pMlog->hdr.train1 != 0 )
		{

			GetError(pMlog, pMsg);

			//return (char*)(&TRANSLATE_ERR);
		}

	}

//	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
//	tm_time = localtime( &pMlog->hdr.timelu);
//	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

	return buf;

}

// if the function is called, then means message is not decoded
char * ABMsgTranslator::TranslateAction(const Msg *pMsg)
{
	char *hdrErr = TranslateHeader(pMsg);

	if (strlen(hdrErr) != 0 && strstr(hdrErr, m_sDelimiter) != NULL)
	{
		return hdrErr;//error message
	}
	

	return (char*)(&NOT_IMPLEMENTED); 
}

char * ABMsgTranslator::Translate(const long lMsgType, const Msg *pMsg)
{
	char *hdrErr = TranslateHeader(pMsg);

	if (strlen(hdrErr)!=0 && strstr(hdrErr, m_sDelimiter) != NULL)
	{
		return hdrErr;//error message
	}
	char *bufMsg = TranslateAction(pMsg);

	return bufMsg;
}

char * ABMsgTranslator::Translate(long lWCMsg, const long lWcMsgType, const Msg *pMsg)
{
	char *hdrErr = TranslateHeader(pMsg);

	if (strlen(hdrErr) != 0 && strstr(hdrErr, m_sDelimiter) != NULL)
	{
		return hdrErr;//error message
	}

	char *bufMsg = TranslateAction( pMsg);

	return bufMsg;
}

void ABMsgTranslator::PackHeader(char *cpStoreProcName, struct LOGAB *pMlog, const Msg *pMsg)
{

	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	m_iSysNo		= pMsg->m_iSysNo;
	m_iMsgOrderNo	= m_iLoggerMsgOrderNo;

	strcpy(m_sSysName, pMsg->m_iSysName);

	sprintf(m_sSellingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear);

	m_iMsgSize		= pMlog->hdr.sizew;
	m_iMsgCode		= pMlog->hdr.codewu;
	m_iErrCode		= pMsg->m_iMsgErrwu;//pMlog->hdr.errorwu;
	if ( m_iErrCode != 0 ) 
		m_iErrCode = 1;
	m_iTrapCode		= pMlog->hdr.trapcodebu;
	m_iStaffNo		= pMlog->hdr.stafflu;			
	m_iLogTermNo	= pMlog->hdr.ltnlu;		
	m_iAcctNo		= pMlog->hdr.acclu;			
	m_iFileNo		= pMlog->hdr.filebu;			
	m_iBlockNo		= pMlog->hdr.blocklu;			
	m_iOverflowNo	= pMlog->hdr.overflowlu;		
	m_iOffsetUnit	= pMlog->hdr.offwu;		
	m_iTranNo		= pMlog->hdr.tranwu;			
	m_iLastLogSeq	= pMlog->hdr.lgslu;      
	m_iMsnNo		= pMlog->hdr.msnlu;			
	m_iExtSysType	= pMlog->hdr.extSysTypebu;		
	m_iCatchUp		= pMlog->hdr.catchup1;
	m_iBtExcept		= pMlog->hdr.btexc1;		
	m_iOtherSys		= pMlog->hdr.othsys1;		
	m_iPreLog		= pMlog->hdr.prelog1;			
	m_iTimeout		= pMlog->hdr.timeout1;			
	m_iLateReply	= pMlog->hdr.laterpy1;		
	m_iBcsMsg		= pMlog->hdr.bcsmsg1;			
	m_iRcvMsg		= pMlog->hdr.rcvmsg1;			
	m_iOverFlow		= pMlog->hdr.overflow1;		
	m_iEscRel		= pMlog->hdr.escRel1;			
	m_iNoFlush		= pMlog->hdr.noFlush1;			
	m_iTrainAcct	= pMlog->hdr.train1;
	m_iSessionInfo	= pMlog->hdr.sessionInfo1;
	m_iSourceType	= pMlog->hdr.source.srcTypebu;     
	tm *tm_time		= _localtime32( &pMsg->m_iMsgTime ); //&pMlog->hdr.timelu
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

	// voice
	char m_sTerminalNo[12];
	if ( m_iSourceType == LOGAB_SRC_VOICE ) {
		m_cVoiceFENo = pMlog->hdr.source.data.voice.febu;
		m_iVoiceTermNo = pMlog->hdr.source.data.voice.termwu;
		m_iVoiceLocId = pMlog->hdr.source.data.voice.locidlu;
		if ( m_iVoiceTermNo >= 30000 )
			sprintf( m_sTerminalNo, "TBAS%04d", m_iVoiceTermNo - 30000 );
		else
			pidToAsc(m_iVoiceTermNo, m_sTerminalNo);
	}
	else {
		m_cVoiceFENo = 0;
		m_iVoiceTermNo = 0;
		m_iVoiceLocId = 0;
		sprintf( &m_sTerminalNo[0], "%s", "" ); // replace "\0" with ""
	}

	// cit   //Q310 MBSN   //MAR2011  //2011IBT	//NOV2011 MR // MSR Mar 2013	//APR2021
	char m_cCitType[100][10] = {"MPB", "CIT-3", "CIT-3A", "CIT-5", "CIT-6", "TWM", "CIT-PDA", "ESC", "EWIN", "CIT-8", "JCBW", "AMBS", "WLPDA","IP-PHONE", "ITV", "WLPDA", "JCBWEKBA", "ITV", "APINOW", "IOSBS", "JCMOW", "IBT", "AOSBS", "APISMC", "APITD", "IBUT", "APIWC", "IBUA", "WOSBS", "MASBAI", "MASBAA"};
	//"CHATBOT" is added in DEC2022 for ECBP.CC, code 37 (statement) and 41 (balance enquiry) will include the new deviceType 100
	memcpy(m_cCitType[99], "ECBPCC", 10);
	char m_sDidCitType[10];

	if ( (m_iSourceType == LOGAB_SRC_CIT) || 
		 (m_iSourceType == LOGAB_SRC_EFT_CIT) )
	{

		m_iDidCitNo = pMlog->hdr.source.data.did.citlu;
		m_cDidPseTermNo = pMlog->hdr.source.data.did.termbu;
		m_cDidFENo = pMlog->hdr.source.data.did.febu;
		if ( pMlog->hdr.source.data.did.citTypebu > 0 ) 
			sprintf( m_sDidCitType, "%s", m_cCitType[pMlog->hdr.source.data.did.citTypebu - 1] );
		else
			sprintf( m_sDidCitType, "%s", "" );
	}
	// ewin
	else if ( (m_iSourceType == LOGAB_SRC_EWIN) || (m_iSourceType == LOGAB_SRC_EFT_EWIN) ) 
	{
		m_iDidCitNo = pMlog->hdr.source.data.did.citlu;
		m_cDidPseTermNo = pMlog->hdr.source.data.did.termbu;
		m_cDidFENo = pMlog->hdr.source.data.did.febu;
		if ( pMlog->hdr.source.data.did.citTypebu > 0 ) 
			sprintf( m_sDidCitType, "%s", m_cCitType[pMlog->hdr.source.data.did.citTypebu - 1] );
		else
			sprintf( m_sDidCitType, "%s", "" );

	}
	else
	{
		m_iDidCitNo = 0;
		m_cDidPseTermNo = 0;
		m_cDidFENo = 0;
		sprintf( m_sDidCitType, "%s", "" );
	}

	// initial
		m_iCBCenterNo = 0;
		m_iCBWindowNo = 0;
		m_iCBLogTermNo = 0;
		m_cCBSysNo = 0;

		m_iOldCenterNo = 0;
		m_iOldWindowNo = 0;
		m_iOldChanNo = 0;
		m_cOldSysNo = 0;

	// esc
	if ( (m_iSourceType == LOGAB_SRC_CB_BT) || 
		 (m_iSourceType == LOGAB_SRC_EFT_CB) ||
		 (m_iSourceType == LOGAB_SRC_OLD) ||
		(m_iSourceType == LOGAB_SRC_CB_EWAL))
	{
		m_iCBCenterNo = pMlog->hdr.source.data.cbBt.centrelu;
		m_iCBWindowNo = pMlog->hdr.source.data.cbBt.windowwu;
		m_iCBLogTermNo = pMlog->hdr.source.data.cbBt.ltnwu;
		m_cCBSysNo = pMlog->hdr.source.data.cbBt.cbbu;

		m_iOldCenterNo = pMlog->hdr.source.data.old.centrelu;
		m_iOldWindowNo = pMlog->hdr.source.data.old.windowwu;
		m_iOldChanNo = pMlog->hdr.source.data.old.chanwu;
		m_cOldSysNo = pMlog->hdr.source.data.old.cbbu;
	}
	else if ((m_iSourceType == LOGAB_SRC_EWIN) || (m_iSourceType == LOGAB_SRC_EFT_EWIN) )
	{
		// 2011 NOV move the following logic to here !!!
			// 2011IBT
			// Separate IBT Number into Location, Table and Terminal for Anonymous Account Only
			if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IBT ) {
				m_iCBCenterNo = (unsigned int) m_iDidCitNo / 100000 ;
				//m_iCBWindowNo = (unsigned int) (m_iDidCitNo - (m_iCBCenterNo * 100000)) / 100 ;
				//m_iCBLogTermNo = (unsigned int) m_iDidCitNo - (m_iCBCenterNo * 100000) - (m_iCBWindowNo*100) ;
				m_iCBWindowNo = 0;
				m_iCBLogTermNo = 0;
			}
			//End of 2011IBT
	}
	else
	{
		m_iCBCenterNo = 0;
		m_iCBWindowNo = 0;
		m_iCBLogTermNo = 0;
		m_cCBSysNo = 0;

		m_iOldCenterNo = 0;
		m_iOldWindowNo = 0;
		m_iOldChanNo = 0;
		m_cOldSysNo = 0;
	}

	if ( m_iSourceType == LOGAB_SRC_POL ) {
		m_cPolFileNo = pMlog->hdr.source.data.pol.filebu;
		m_iPolOffsetNo = pMlog->hdr.source.data.pol.offsetlu;
	}
	else {
		m_cPolFileNo = 0;
		m_iPolOffsetNo = 0;
	}

	
	if ( m_iSourceType == LOGAB_SRC_MAT ) {
		m_iMatNo = pMlog->hdr.source.data.matlu;
		sprintf( m_cMatNo, "%X", m_iMatNo );
	}
	else {
		m_iMatNo = 0;
		m_cMatNo[0] = 0;
	}

	if ( m_iSourceType == LOGAB_SRC_BAT_DEP )
		m_iBatchDep = pMlog->hdr.source.data.tbwu;						
	else
		m_iBatchDep = 0;

	/************** Add Record ********************/
	AddField(0, 0);
	AddField(m_iMsgCode, 0);//Again, add messsage code at first position for simple selection 
	AddField(STORE_TYPE_STRING, m_sSysName, 0);
	AddField(m_iMsgOrderNo, 0);
	AddField(STORE_TYPE_STRING, m_sSellingDate, 0);
	AddField(m_iMsgSize, 0);
	AddField(m_iMsgCode, 0);
	AddField(m_iErrCode, 0);
	AddField(m_iTrapCode, 0);
	AddField(m_iStaffNo, 0);
	AddField(m_iLogTermNo, 0);
	AddField(m_iAcctNo, 0);
	AddField(m_iFileNo, 0);
	AddField(m_iBlockNo, 0);
	AddField(m_iOverflowNo, 0);
	AddField(m_iOffsetUnit, 0);
	AddField(m_iTranNo, 0);
	AddField(STORE_TYPE_STRING, m_sTime, 0);
	AddField(m_iLastLogSeq, 0);
	AddField(m_iMsnNo, 0);
	AddField(m_iExtSysType, 0);
	AddField(m_iCatchUp, 0);
	AddField(m_iBtExcept, 0);
	AddField(m_iOtherSys, 0);
	AddField(m_iPreLog, 0);
	AddField(m_iTimeout, 0);
	AddField(m_iLateReply, 0);
	AddField(m_iBcsMsg, 0);
	AddField(m_iRcvMsg, 0);
	AddField(m_iOverFlow, 0);
	AddField(m_iEscRel, 0);
	AddField(m_iNoFlush, 0);
	AddField(m_iTrainAcct, 0);
	AddField(m_iSessionInfo, 0);
	AddField(m_iSourceType, 0);
	AddField(m_cVoiceFENo, 0);
	AddField(STORE_TYPE_STRING, m_sTerminalNo, 0); // comment after
	// AddField(m_iVoiceTermNo, 0);
	AddField(m_iVoiceLocId, 0);
	AddField(m_iDidCitNo, 0);
	AddField(m_cDidPseTermNo, 0);
	AddField(m_cDidFENo, 0);
	AddField(STORE_TYPE_STRING, m_sDidCitType, 0);
	AddField(m_iCBCenterNo, 0);
	AddField(m_iCBWindowNo, 0);
	AddField(m_iCBLogTermNo, 0);
	AddField(m_cCBSysNo, 0);
	AddField(m_iOldCenterNo, 0);
	AddField(m_iOldWindowNo, 0);
	AddField(m_iOldChanNo, 0);
	AddField(m_cOldSysNo, 0);
	AddField(m_cPolFileNo, 0);
	AddField(m_iPolOffsetNo, 0);
	AddField(STORE_TYPE_STRING, m_cMatNo, 0);
	AddField(m_iBatchDep, 0);
/* 
	if (m_iMsgCode == 3)	// when message is account access
	{
		m_pTBAccount->AsCallSeq(m_iAcctNo);	// increase call sequence (TBAccount.cpp)
	}
*/
	//if ( m_iAcctNo != 0 && (m_iAcctNo < 100000000))//"m_iAcctNo < 100000000" added by paul ou 2016.8.24
	//	m_iCallSeq = m_pTBAccount->GetCallSeq(m_iAcctNo);	// get call sequence (TBAccount.cpp)
	//else
	//	m_iCallSeq = 0;
	m_iCallSeq = pMlog->hdr.custSessIdd;				// customer session id for SP13 EDW

	if ( m_iErrCode == 0 ) 
		AddField64(m_iCallSeq, 0);
	else
		AddField(0, 0);

	if ( m_iMsgCode == 202 )
		AddField(0, 0);
	else
		AddField(m_iTerminalType, 0);		// Get from sign on for details please see CBSystem.cpp line 169

}

void ABMsgTranslator:: AddField(unsigned long lVal, int iOutput)
{
	char cStr[30];
	unsigned long rVal;
	rVal = lVal;
	if (lVal > 2147483647)
		rVal = 2147483647;	

	sprintf(cStr, "%u", rVal);

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ABMsgTranslator:: AddField(long lVal, int iOutput)
{
	char cStr[30];
	long rVal;
	rVal = lVal;
	if (lVal > 2147483647)
		rVal = 2147483647;	
	if (lVal < -2147483647)
		rVal = -2147483647;	

	sprintf(cStr, "%d", rVal);

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ABMsgTranslator:: AddField(unsigned int lVal, int iOutput)
{
	char cStr[30];
	unsigned int rVal;
	rVal = lVal;
	if (lVal > 2147483647)
		rVal = 2147483647;	

	sprintf(cStr, "%u", rVal);

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ABMsgTranslator:: AddField(int lVal, int iOutput)
{
	char cStr[30];
	int rVal;
	rVal = lVal;
	if (lVal > 2147483647)
		rVal = 2147483647;	
	if (lVal < -2147483647)
		rVal = -2147483647;	
	
	sprintf(cStr, "%d", rVal);

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ABMsgTranslator::  AddField64(unsigned __int64 lVal, int iOutput)
{
	char cStr[60];
	_ui64toa( lVal, cStr, 10 );

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ABMsgTranslator:: AddField64(__int64 lVal, int iOutput)
{
	char cStr[60];
	_i64toa( lVal, cStr, 10 );

	AddField(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ABMsgTranslator::AddField(int iType, char *cpStr, int iOutput)
{
	if (iType==STORE_TYPE_CHAR)
	{
		char cStr[2];
		sprintf(cStr, "%c", cpStr);
		sprintf(m_cStr, "%s", cpStr);
		if (m_iCount == 2)
			strcat(buf, m_sDelimiter_SimSel);
		else if ( m_iCount > 2 )
			strcat( buf, m_sDelimiter );
		if ( m_iCount >= 1)
			strcat( buf, cStr );
	} 
	else 
	{
		sprintf(m_cStr, "%s", cpStr);
		if (m_iCount == 2)
			strcat(buf, m_sDelimiter_SimSel);
		else if ( m_iCount > 2 )
			strcat( buf, m_sDelimiter );
		if ( m_iCount >= 1)
			strcat( buf, m_cStr );
	}
	m_iCount++;
}

void ABMsgTranslator::WCHeader(char *cpStoreProcName, struct LOGAB *pMlog, const Msg *pMsg)
{
	m_iCount = 0;
	//Translator header
	m_iSysNo					= pMsg->m_iSysNo;
	m_iMsgOrderNo				= m_iLoggerMsgOrderNo;
	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	sprintf(m_sSellingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear);

// m_iCustomerSession

	m_iMsgSize = pMlog->hdr.sizew;		// size in byte
	m_iMsgCode = pMlog->hdr.codewu;		// message code
	tm_time = _localtime32( &pMsg->m_iMsgTime);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
	/*if (strcmp(m_sTime, "06-Jan-1991 15:11:52")==0)
	{
		int z = 0;
	}*/
	
	strcpy(m_sSysName, pMsg->m_iSysName);
		
	// Output header
	AddField(0, 0);
	AddField(m_iMsgCode, 0);//Again, add messsage code at first position for simple selection 
	AddField(STORE_TYPE_STRING, m_sSysName, 0);
	AddField(STORE_TYPE_STRING, m_sSellingDate, 0);
	AddField(m_iMsgOrderNo, 0);
	tm *tm_time		= _localtime32( &pMsg->m_iMsgTime);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
	AddField(STORE_TYPE_STRING, m_sTime, 0);
}


void ABMsgTranslator::GetError(struct LOGAB *pMlog, const Msg *pMsg)
{
	//NewRecord();

	char	m_sMonths[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	m_iSysNo		= pMsg->m_iSysNo;
	m_iMsgOrderNo	= m_iLoggerMsgOrderNo;

	strcpy(m_sSysName, pMsg->m_iSysName);

	sprintf(m_sSellingDate, "%02d-%s-%d", pMsg->m_iMsgDay, m_sMonths[pMsg->m_iMsgMonth], pMsg->m_iMsgYear);

	m_iMsgSize		= pMlog->hdr.sizew;
	m_iMsgCode		= pMlog->hdr.codewu;// LOGAB_CODE_ERR;// pMlog->hdr.codewu;
	m_iErrCode		= pMsg->m_iMsgErrwu;// pMsg->m_iMsgErr;// pMlog->hdr.errorwu;
	m_iTrapCode		= pMlog->hdr.trapcodebu;
	m_iStaffNo		= pMlog->hdr.stafflu;			
	m_iLogTermNo	= pMlog->hdr.ltnlu;		
	m_iAcctNo		= pMlog->hdr.acclu;			
	m_iFileNo		= pMlog->hdr.filebu;			
	m_iBlockNo		= pMlog->hdr.blocklu;			
	m_iOverflowNo	= pMlog->hdr.overflowlu;		
	m_iOffsetUnit	= pMlog->hdr.offwu;		
	m_iTranNo		= pMlog->hdr.tranwu;			
	m_iLastLogSeq	= pMlog->hdr.lgslu;      
	m_iMsnNo		= pMlog->hdr.msnlu;			
	m_iExtSysType	= pMlog->hdr.extSysTypebu;		
	m_iCatchUp		= pMlog->hdr.catchup1;
	m_iBtExcept		= pMlog->hdr.btexc1;		
	m_iOtherSys		= pMlog->hdr.othsys1;		
	m_iPreLog		= pMlog->hdr.prelog1;			
	m_iTimeout		= pMlog->hdr.timeout1;			
	m_iLateReply	= pMlog->hdr.laterpy1;		
	m_iBcsMsg		= pMlog->hdr.bcsmsg1;			
	m_iRcvMsg		= pMlog->hdr.rcvmsg1;			
	m_iOverFlow		= pMlog->hdr.overflow1;		
	m_iEscRel		= pMlog->hdr.escRel1;			
	m_iNoFlush		= pMlog->hdr.noFlush1;			
	m_iTrainAcct	= pMlog->hdr.train1;
	m_iSessionInfo	= pMlog->hdr.sessionInfo1;
	m_iSourceType	= pMlog->hdr.source.srcTypebu;     
	tm *tm_time		= _localtime32( &pMsg->m_iMsgTime);
	sprintf(m_sTime, "%02d-%s-%d %02d:%02d:%02d", tm_time->tm_mday, m_sMonths[tm_time->tm_mon+1], tm_time->tm_year+1900, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);
	
	// voice
	char m_sTerminalNo[10];
	if ( m_iSourceType == LOGAB_SRC_VOICE ) {
		m_cVoiceFENo = pMlog->hdr.source.data.voice.febu;
		m_iVoiceTermNo = pMlog->hdr.source.data.voice.termwu;
		m_iVoiceLocId = pMlog->hdr.source.data.voice.locidlu;

		sprintf(m_sTerminalNo, "%04X", m_iVoiceTermNo);
		if(m_sTerminalNo[0]!='B' && m_sTerminalNo[1]!='A')
		{
			pidToAsc(m_iVoiceTermNo, m_sTerminalNo);
		}
		else {
			if ( strlen( m_sTerminalNo ) > 9 )
				sprintf( &m_sTerminalNo[9], "%s", "" );
		}
	}
	else {
		m_cVoiceFENo = 0;
		m_iVoiceTermNo = 0;
		m_iVoiceLocId = 0;
		sprintf( &m_sTerminalNo[0], "%s", "" );
	}

	// cit  //Q310 MBSN		// MAR2011  //2011IBT	//NOV2011 MR  //MAR2013 MSR		//APR2021
	char m_cCitType[100][10] = {"MPB", "CIT-3", "CIT-3A", "CIT-5", "CIT-6", "TWM", "CIT-PDA", "ESC", "EWIN", "CIT-8", "JCBW", "AMBS", "WLPDA","IP-PHONE", "ITV", "WLPDA", "JCBWEKBA", "ITV", "APINOW", "IOSBS", "JCMOW", "IBT", "AOSBS", "APISMC", "APITD", "IBUT", "APIWC", "IBUA", "WOSBS", "MASBAI", "MASBAA"};
	//"CHATBOT" is added in DEC2022 for ECBP.CC, code 37 (statement) and 41 (balance enquiry) will include the new deviceType 100
	memcpy(m_cCitType[99], "ECBPCC", 10);
	char m_sDidCitType[10];

	if ( (m_iSourceType == LOGAB_SRC_CIT) || 
		 (m_iSourceType == LOGAB_SRC_EFT_CIT) )
	{
		m_iDidCitNo = pMlog->hdr.source.data.did.citlu;
		m_cDidPseTermNo = pMlog->hdr.source.data.did.termbu;
		m_cDidFENo = pMlog->hdr.source.data.did.febu;
		sprintf( m_sDidCitType, "%s", m_cCitType[pMlog->hdr.source.data.did.citTypebu - 1] );
	}
	// ewin
	else if ( (m_iSourceType == LOGAB_SRC_EWIN) || (m_iSourceType == LOGAB_SRC_EFT_EWIN) ) 
	{
		m_iDidCitNo = pMlog->hdr.source.data.did.citlu;
		m_cDidPseTermNo = pMlog->hdr.source.data.did.termbu;
		m_cDidFENo = pMlog->hdr.source.data.did.febu;
		if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_INET ) 
			sprintf( m_sDidCitType, "%s", "EWIN"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_JCBW ) 
			sprintf( m_sDidCitType, "%s", "JCBW"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_JCBWEKBA ) 
			sprintf( m_sDidCitType, "%s", "JCBWEKBA"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_AMBS ) 
			sprintf( m_sDidCitType, "%s", "AMBS"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_WLPDA ) 
			sprintf( m_sDidCitType, "%s", "WLPDA"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IPPHONE ) 
			sprintf( m_sDidCitType, "%s", "IP-PHONE"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_MBSN ) 
			sprintf( m_sDidCitType, "%s", "APINOW"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IOSBS ) 
			sprintf( m_sDidCitType, "%s", "IOSBS"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_JCMOW ) 
			sprintf( m_sDidCitType, "%s", "JCMOW"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IBT ) //2011IBT
			sprintf( m_sDidCitType, "%s", "IBT"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_AOSBS ) //2011NOV
			sprintf( m_sDidCitType, "%s", "AOSBS"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_APISMC ) //2011NOV
			sprintf( m_sDidCitType, "%s", "APISMC"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_APITD ) //2011NOV
			sprintf( m_sDidCitType, "%s", "APITD"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IBUT ) //2013MAR
			sprintf( m_sDidCitType, "%s", "IBUT"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IBUA ) //2014NOV
			sprintf( m_sDidCitType, "%s", "IBUA"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_API3HK ) //2013MAR
			sprintf( m_sDidCitType, "%s", "APIWC"  );
		else if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_WOSBS ) //2015 MSR
			sprintf( m_sDidCitType, "%s", "WOSBS"  );		
		else if (pMlog->hdr.source.data.did.citTypebu == DEV_TYP_MASBAI) //APR2021
			sprintf(m_sDidCitType, "%s", "MASBAI");
		else if (pMlog->hdr.source.data.did.citTypebu == DEV_TYP_MASBAA) //APR2021
			sprintf(m_sDidCitType, "%s", "MASBAA");


		else 
			sprintf( m_sDidCitType, "%s", "UDF"  );
	}
	else
	{
		m_iDidCitNo = 0;
		m_cDidPseTermNo = 0;
		m_cDidFENo = 0;
		sprintf( m_sDidCitType, "%s", "" );
	}


	//inital

		m_iCBCenterNo = 0;
		m_iCBWindowNo = 0;
		m_iCBLogTermNo = 0;
		m_cCBSysNo = 0;

		m_iOldCenterNo = 0;
		m_iOldWindowNo = 0;
		m_iOldChanNo = 0;
		m_cOldSysNo = 0;

	// esc
	if ( (m_iSourceType == LOGAB_SRC_CB_BT) || 
		 (m_iSourceType == LOGAB_SRC_EFT_CB) ||
		(m_iSourceType == LOGAB_SRC_CB_EWAL))
	{
		m_iCBCenterNo = pMlog->hdr.source.data.cbBt.centrelu;
		m_iCBWindowNo = pMlog->hdr.source.data.cbBt.windowwu;
		m_iCBLogTermNo = pMlog->hdr.source.data.cbBt.ltnwu;
		m_cCBSysNo = pMlog->hdr.source.data.cbBt.cbbu;

		m_iOldCenterNo = pMlog->hdr.source.data.old.centrelu;
		m_iOldWindowNo = pMlog->hdr.source.data.old.windowwu;
		m_iOldChanNo = pMlog->hdr.source.data.old.chanwu;
		m_cOldSysNo = pMlog->hdr.source.data.old.cbbu;
	}
	else if ( (m_iSourceType == LOGAB_SRC_EWIN) || (m_iSourceType == LOGAB_SRC_EFT_EWIN) ) 
	{
		// 2011IBT
		// Separate IBT Number into Location, Table and Terminal for Anonymous Account Only
		if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IBT ) {
			m_iCBCenterNo = (unsigned int) m_iDidCitNo / 100000 ;
			//m_iCBWindowNo = (unsigned int) (m_iDidCitNo - (m_iCBCenterNo * 100000)) / 100 ;
			//m_iCBLogTermNo = (unsigned int) m_iDidCitNo - (m_iCBCenterNo * 100000) - (m_iCBWindowNo*100) ;
			m_iCBWindowNo = 0;
			m_iCBLogTermNo = 0;
		}
		//End of 2011IBT
	}
	else
	{
		m_iCBCenterNo = 0;
		m_iCBWindowNo = 0;
		m_iCBLogTermNo = 0;
		m_cCBSysNo = 0;

		m_iOldCenterNo = 0;
		m_iOldWindowNo = 0;
		m_iOldChanNo = 0;
		m_cOldSysNo = 0;
	}


	m_cPolFileNo = pMlog->hdr.source.data.pol.filebu;
	m_iPolOffsetNo = pMlog->hdr.source.data.pol.offsetlu;

	
	if ( m_iSourceType == LOGAB_SRC_MAT ) {
		m_iMatNo = pMlog->hdr.source.data.matlu;
		sprintf( m_cMatNo, "%X", m_iMatNo );
	}
	else {
		m_iMatNo = 0;
		m_cMatNo[0] = 0;
	}

	if ( m_iSourceType == LOGAB_SRC_BAT_DEP )
		m_iBatchDep = pMlog->hdr.source.data.tbwu;						
	else
		m_iBatchDep = 0;


	/************** Add Record ********************/
	AddField(0, 0);
	AddField(LOGAB_CODE_ERR, 0);//Again, add custom  internal code at first position
	AddField(STORE_TYPE_STRING, m_sSysName, 0);
	AddField(m_iMsgOrderNo, 0);
	AddField(STORE_TYPE_STRING, m_sSellingDate, 0);
	AddField(m_iMsgSize, 0);
	AddField(m_iMsgCode, 0);
	AddField(m_iErrCode, 0);
	AddField(m_iTrapCode, 0);
	AddField(m_iStaffNo, 0);
	AddField(m_iLogTermNo, 0);
	AddField(m_iAcctNo, 0);
	AddField(m_iFileNo, 0);
	AddField(m_iBlockNo, 0);
	AddField(m_iOverflowNo, 0);
	AddField(m_iOffsetUnit, 0);
	AddField(m_iTranNo, 0);
	AddField(STORE_TYPE_STRING, m_sTime, 0);
	AddField(m_iLastLogSeq, 0);
	AddField(m_iMsnNo, 0);
	AddField(m_iExtSysType, 0);
	AddField(m_iCatchUp, 0);
	AddField(m_iBtExcept, 0);
	AddField(m_iOtherSys, 0);
	AddField(m_iPreLog, 0);
	AddField(m_iTimeout, 0);
	AddField(m_iLateReply, 0);
	AddField(m_iBcsMsg, 0);
	AddField(m_iRcvMsg, 0);
	AddField(m_iOverFlow, 0);
	AddField(m_iEscRel, 0);
	AddField(m_iNoFlush, 0);
	AddField(m_iTrainAcct, 0);
	AddField(m_iSessionInfo, 0);
	AddField(m_iSourceType, 0);
	AddField(m_cVoiceFENo, 0);
	AddField(STORE_TYPE_STRING, m_sTerminalNo, 0); 
	//AddField(m_iVoiceTermNo, 0);
	AddField(m_iVoiceLocId, 0);
	AddField(m_iDidCitNo, 0);
	AddField(m_cDidPseTermNo, 0);
	AddField(m_cDidFENo, 0);
	//AddField(m_cDidCitType, 0);
	AddField(STORE_TYPE_STRING, m_sDidCitType, 0);
	AddField(m_iCBCenterNo, 0);
	AddField(m_iCBWindowNo, 0);
	AddField(m_iCBLogTermNo, 0);
	AddField(m_cCBSysNo, 0);
	AddField(m_iOldCenterNo, 0);
	AddField(m_iOldWindowNo, 0);
	AddField(m_iOldChanNo, 0);
	AddField(m_cOldSysNo, 0);
	AddField(m_cPolFileNo, 0);
	AddField(m_iPolOffsetNo, 0);
	AddField(STORE_TYPE_STRING, m_cMatNo, 0);
	AddField(m_iBatchDep, 0);
/*
	if (m_iMsgCode == 3)	// when message is account access
	{
		// m_pTBAccount->AsCallSeq(m_iAcctNo);	// increase call sequence (TBAccount.cpp)
		int a = 0;
	}
*/

	//201108PSR
	//bypass get call sequence if Account Number is Zero

	//if ( m_iAcctNo == 0 || (m_iAcctNo >= 100000000))//"m_iAcctNo >= 100000000" added by paul ou 2016.8.24
	//{
	//    m_iCallSeq = 0;
	//}
	//else
	//{
	//    m_iCallSeq = m_pTBAccount->GetCallSeq(m_iAcctNo);	// get call sequence (TBAccount.cpp)
	//}

	m_iCallSeq = pMlog->hdr.custSessIdd;				// customer session id for SP13 EDW

	AddField64(m_iCallSeq, 0);
	AddField(m_iTerminalType, 0);		// Get from sign on for details please see CBSystem.cpp line 169


	__int64 iTotalAmt = 0;
	unsigned char m_iBetType = 0;

	switch( m_iMsgCode )
	{
		case LOGAB_CODE_LOT:
			iTotalAmt = (__int64) pMlog->data.bt.lot.tran.bet.d.hdr.costlu;
			m_iBetType	= pMlog->data.bt.lot.tran.bet.d.hdr.bettypebu;
			break;
		case LOGAB_CODE_RAC:
			iTotalAmt = (__int64) pMlog->data.bt.rac.tran.bet.d.hdr.costlu;
			m_iBetType	= pMlog->data.bt.rac.tran.bet.d.hdr.bettypebu;
			break;
		case LOGAB_CODE_SB:
			iTotalAmt = (__int64) pMlog->data.bt.sb.bet.tran.bet.hdr.costlu;
			m_iBetType = pMlog->data.bt.sb.bet.tran.bet.hdr.bettypebu;
			break;
		case LOGAB_CODE_DEP:
			iTotalAmt = (__int64) pMlog->data.bt.dep.tran.amountdu;
			break;
		case LOGAB_CODE_BATDEP:
			iTotalAmt = (__int64) pMlog->data.deph.data.tran.data.amtdu;
			break;
		case LOGAB_CODE_EFT_MISC:
			//iTotalAmt = (__int64) pMlog->data.bt.eftmisc.eps.
			break;
		default:
			iTotalAmt = 0;
	}
	AddField(m_iBetType, 0);
	AddField64(iTotalAmt, 0);
}


void ABMsgTranslator::SetTBAccount(TBAccount *pTBAccount)
{
	m_pTBAccount = pTBAccount;
}


char* ABMsgTranslator::GetWCBetType(char BetType, char Type[20])
{
	// wc bet type is different from the one defined in betdef.h
	// 2016.03.24, checked it is not run in the script below.  
	//  however, below ID should syn with WC, therefore, it will be corrected.
	switch (BetType)
	{	
		case 0:
			sprintf(Type, "WIN");
			break;
		
		case 1:
			sprintf(Type, "PLA");
			break;

		case 2:
			sprintf(Type, "QIN");
			break;

		case 3:
			sprintf(Type, "QPL");
			break;

		case 4:
			sprintf(Type, "TRI");
			break;

		case 5:
			sprintf(Type, "TCE");
			break;

		case 6:
			sprintf(Type, "QTT");
			break;

		case 7:
			sprintf(Type, "DBL");
			break;

		case 8:
			sprintf(Type, "D-Q");
			break;

		case 9:
			sprintf(Type, "TBL");
			break;

		case 10:
			sprintf(Type, "T-T");
			break;

		case 11:
			sprintf(Type, "6UP");
			break;

		case 12:
			sprintf(Type, "D-T");
			break;

		case 13:
			sprintf(Type, "F-F");
			break;

		case 14:
			sprintf(Type, "BWA");
			break;

		case 15:
			sprintf(Type, "CWA");
			break;

		case 16:
			sprintf(Type, "CWB");
			break;

		case 17:
			sprintf(Type, "CWC");
			break;

		case 18:
			sprintf(Type, "IWN");
			break;

		default:
			sprintf(Type, "XXXX");
			break;
	}

	return(Type);
}

