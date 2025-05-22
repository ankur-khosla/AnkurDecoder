// ABAcctAccess.cpp

#include "LOGDEF_AB.h"
#include "ABAcctAccess.h"

char * ABAcctAccess::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;

	PackHeader("", pMlog, pMsg);
	int m_iSourceType	= pMlog->hdr.source.srcTypebu;     

	// Device - Voice
	if ( m_iSourceType == LOGAB_SRC_VOICE ) 
	{
		m_iDevVRecTrk		= pMlog->data.bt.aca.dev.voice.recTrklu;
		m_iDevSecCodeOvr	= pMlog->data.bt.aca.dev.voice.secu1;
	}
	else 
	{
		m_iDevVRecTrk		= 0;
		m_iDevSecCodeOvr	= 0;
	}

	//for 41, set other fields to 0
	if (pMsg->m_iMsgCode == 41)
	{
		m_iDevVRecTrk = 0;
		m_iDevSecCodeOvr = 0;
	}

	AddField( m_iDevVRecTrk, 0 );
	AddField( m_iDevSecCodeOvr, 0 );

	// Device - DID
	if ( (m_iSourceType == LOGAB_SRC_CIT)	  || 
		 (m_iSourceType == LOGAB_SRC_EFT_CIT) ||
		 (m_iSourceType == LOGAB_SRC_EWIN)    || 
		 (m_iSourceType == LOGAB_SRC_EFT_EWIN) )
	{
		m_iDevDidCitType	= pMlog->data.bt.aca.dev.did.citbu;
		m_iDevDidOthCit		= pMlog->data.bt.aca.dev.did.oth1;
	}
	else {
		m_iDevDidCitType	= 0;
		m_iDevDidOthCit		= 0;
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iDevDidCitType = 0;
		m_iDevDidOthCit = 0;
	}

	AddField( m_iDevDidCitType, 0 );
	AddField( m_iDevDidOthCit, 0 );

	if ( (m_iSourceType == LOGAB_SRC_CB_BT) || 
		 (m_iSourceType == LOGAB_SRC_EFT_CB) ||
		 (m_iSourceType == LOGAB_SRC_OLD) )
	{

		//Device - CB
		m_iDevCBEscNo		= pMlog->data.bt.aca.dev.cb.escdu;
		m_iDevCBCMSRej		= pMlog->data.bt.aca.dev.cb.rejcodwu;
		m_iDevCBSvt			= pMlog->data.bt.aca.dev.cb.svt1;
		m_iDevCBOnCourse	= pMlog->data.bt.aca.dev.cb.oncourse1;
	}
	else 
	{
		m_iDevCBEscNo		= 0;
		m_iDevCBCMSRej		= 0;
		m_iDevCBSvt			= 0;
		m_iDevCBOnCourse	= 0;		
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iDevCBEscNo = 0;
		m_iDevCBCMSRej = 0;
		m_iDevCBSvt = 0;
		m_iDevCBOnCourse = 0;
	}

	AddField64( m_iDevCBEscNo, 0 );
	AddField( m_iDevCBCMSRej, 0 );
	AddField( m_iDevCBSvt, 0 );
	AddField( m_iDevCBOnCourse, 0 );

	// Data - Terminal accessing account for account active error

	m_iSrcType = pMlog->data.bt.aca.data.busySrc.srcTypebu;

	if (pMsg->m_iMsgCode == 41)
	{
		m_iSrcType = 0;
	}

	AddField( m_iSrcType, 0 );

	// source data - voice
	// Device - Voice
	if ( m_iSourceType == LOGAB_SRC_VOICE ) 
	{
		m_iSrcVFEndNo		= pMlog->data.bt.aca.data.busySrc.data.voice.febu;
		m_iSrcVTermNo		= pMlog->data.bt.aca.data.busySrc.data.voice.termwu;
		m_iSrcVLoc			= pMlog->data.bt.aca.data.busySrc.data.voice.locidlu;

	}
	else
	{
		m_iSrcVFEndNo		= 0;
		m_iSrcVTermNo		= 0;
		m_iSrcVLoc			= 0;
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iSrcVFEndNo = 0;
		m_iSrcVTermNo = 0;
		m_iSrcVLoc = 0;
	}

	AddField( m_iSrcVFEndNo, 0 );
	AddField( m_iSrcVTermNo, 0 );
	AddField( m_iSrcVLoc, 0 );

	// source data - DID

	// Device - DID
	if ( (m_iSourceType == LOGAB_SRC_CIT)	  || 
		 (m_iSourceType == LOGAB_SRC_EFT_CIT) ||
		 (m_iSourceType == LOGAB_SRC_EWIN)    || 
		 (m_iSourceType == LOGAB_SRC_EFT_EWIN) )
	{
		m_iSrcDidCitNo		= pMlog->data.bt.aca.data.busySrc.data.did.citlu;
		m_iSrcDidTermNo		= pMlog->data.bt.aca.data.busySrc.data.did.termbu;
		m_iSrcDidFEndNo		= pMlog->data.bt.aca.data.busySrc.data.did.febu;
		m_iSrcDidCitType	= pMlog->data.bt.aca.data.busySrc.data.did.citTypebu;
	}
	else
	{
		m_iSrcDidCitNo		= 0;
		m_iSrcDidTermNo		= 0;
		m_iSrcDidFEndNo		= 0;
		m_iSrcDidCitType	= 0;
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iSrcDidCitNo = 0;
		m_iSrcDidTermNo = 0;
		m_iSrcDidFEndNo = 0;
		m_iSrcDidCitType = 0;
	}

	AddField( m_iSrcDidCitNo, 0 );
	AddField( m_iSrcDidTermNo, 0 );
	AddField( m_iSrcDidFEndNo, 0 );
	AddField( m_iSrcDidCitType, 0 );


	// source data - CB BT
	if ( (m_iSourceType == LOGAB_SRC_CB_BT) || 
		 (m_iSourceType == LOGAB_SRC_EFT_CB) )
	{
		m_iSrcCBCentNo		= pMlog->data.bt.aca.data.busySrc.data.cbBt.centrelu;
		m_iSrcCBWinNo		= pMlog->data.bt.aca.data.busySrc.data.cbBt.windowwu;
		m_iSrcCBTermNo		= pMlog->data.bt.aca.data.busySrc.data.cbBt.ltnwu;
		m_iSrcCBSysNo		= pMlog->data.bt.aca.data.busySrc.data.cbBt.cbbu;

		m_iCscCard			= pMlog->data.bt.wtw.tran.csctrn;  //Transaction with CSC Card (Added 201108PSR)

	}
	else
	{
		m_iSrcCBCentNo		= 0;
		m_iSrcCBWinNo		= 0;
		m_iSrcCBTermNo		= 0;
		m_iSrcCBSysNo		= 0;

		m_iCscCard			= 0;  //Transaction with CSC Card (Added 201108PSR)
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iSrcCBCentNo = 0;
		m_iSrcCBWinNo = 0;
		m_iSrcCBTermNo = 0;
		m_iSrcCBSysNo = 0;

		m_iCscCard = 0;  //Transaction with CSC Card (Added 201108PSR)
	}

	AddField( m_iSrcCBCentNo, 0 );
	AddField( m_iSrcCBWinNo, 0 );
	AddField( m_iSrcCBTermNo, 0 );
	AddField( m_iSrcCBSysNo, 0 );


	// source data - OLD CB System
	if (m_iSourceType == LOGAB_SRC_OLD)
	{
		m_iSrcOldCentNo		= pMlog->data.bt.aca.data.busySrc.data.old.centrelu;
		m_iSrcOldWinNo		= pMlog->data.bt.aca.data.busySrc.data.old.windowwu;
		m_iSrcOldTermNo		= pMlog->data.bt.aca.data.busySrc.data.old.chanwu;
		m_iSrcOldSysNo		= pMlog->data.bt.aca.data.busySrc.data.old.cbbu;
	}
	else
	{
		m_iSrcOldCentNo		= 0;
		m_iSrcOldWinNo		= 0;
		m_iSrcOldTermNo		= 0;
		m_iSrcOldSysNo		= 0;
	}


	if (pMsg->m_iMsgCode == 41)
	{
		m_iSrcOldCentNo = 0;
		m_iSrcOldWinNo = 0;
		m_iSrcOldTermNo = 0;
		m_iSrcOldSysNo = 0;
	}

	AddField( m_iSrcOldCentNo, 0 );
	AddField( m_iSrcOldWinNo, 0 );
	AddField( m_iSrcOldTermNo, 0 );
	AddField( m_iSrcOldSysNo, 0 );

	// source data - Pre-Online
	if ( m_iSourceType == LOGAB_SRC_POL ) 
	{
		m_iSrcPolFileNo		= pMlog->data.bt.aca.data.busySrc.data.pol.filebu;
		m_iSrcPolOffNo		= pMlog->data.bt.aca.data.busySrc.data.pol.offsetlu;
	}
	else
	{
		m_iSrcPolFileNo		= 0;
		m_iSrcPolOffNo		= 0;
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iSrcPolFileNo = 0;
		m_iSrcPolOffNo = 0;
	}

	AddField( m_iSrcPolFileNo, 0 );
	AddField( m_iSrcPolOffNo, 0 );

	m_iMatNo = 0; // init to 0 to avoid random value
	m_iBatchDep = 0; //init to 0 to avoid random value

	if ( m_iSourceType == LOGAB_SRC_MAT ) 
	{
		m_iMatNo = pMlog->data.bt.aca.data.busySrc.data.matlu;
		m_iBatchDep = pMlog->data.bt.aca.data.busySrc.data.tbwu;
	}

	if (pMsg->m_iMsgCode == 41)
	{
		m_iMatNo = 0;
		m_iBatchDep = 0;
	}

	AddField( m_iMatNo, 0 );
	AddField( m_iBatchDep, 0 );
	
	// Data - for okay or other error

	m_iSBFoDivd		= pMlog->data.bt.aca.data.normal.sbfodivd;
	m_iSBInv		= pMlog->data.bt.aca.data.normal.sbinvd;
	m_iDepWtw		= pMlog->data.bt.aca.data.normal.depholdd;
	m_iExp			= pMlog->data.bt.aca.data.normal.expd;
	m_iOnlWtwd		= pMlog->data.bt.aca.data.normal.onlWtwd;
	m_iCashWtwd		= pMlog->data.bt.aca.data.normal.cshWtwd;
	m_iOnlWtwCnt	= pMlog->data.bt.aca.data.normal.onlWtwbu;
	m_iCashWtwCnt	= pMlog->data.bt.aca.data.normal.cshWtwbu;
	m_iSodTranNo	= pMlog->data.bt.aca.data.normal.sodTranwu;

	m_iFundAva		= pMlog->data.bt.aca.data.normal.tran.fundd;    // funds available
	m_iBankGd		= pMlog->data.bt.aca.data.normal.tran.bankgd;   // bank guarentee
	m_iCurrDiv		= pMlog->data.bt.aca.data.normal.tran.curDivd;  // unsettled dividend
	m_iPrevDiv		= pMlog->data.bt.aca.data.normal.tran.prvDivd;  // previous dividend
	m_iFbPayFor		= pMlog->data.bt.aca.data.normal.tran.sbPFtd;   // soccer fo payout forfeited
	
	m_iNOVDivd		= pMlog->data.bt.aca.data.normal.novfodivd;    // novelty dividend
	m_iNOVInv		= pMlog->data.bt.aca.data.normal.novinvd;		// novelty investment

	//Added 201108PSR
	m_iAnonymous = pMlog->hdr.anonymous1;  //Anonymous Account

	if ( pMlog->hdr.source.data.did.citTypebu == DEV_TYP_IBT ) 
	{
		m_iCscCard = 1;  //is_Csc_Card flag is true for IBT ACCESS
	}
	//End of added 201108PSR

	if (pMsg->m_iMsgCode == LOGAB_CODE_ACCT_BAL)
	{
		m_iSBFoDivd = 0;
		m_iSBInv = 0;
		m_iDepWtw = 0;
		m_iExp = 0;
		m_iOnlWtwd = 0;
		m_iCashWtwd = 0;
		m_iOnlWtwCnt = 0;
		m_iCashWtwCnt = 0;
		m_iSodTranNo = 0;
		m_iFundAva = 0;

		m_iBankGd = 0;
		m_iCurrDiv = 0;
		m_iPrevDiv = 0;
		m_iFbPayFor = 0;
		m_iNOVDivd = 0;
		m_iNOVInv = 0;
		m_iAnonymous = 0;
		m_iCscCard = 0;
	}

	if (pMsg->m_iMsgErrwu != 0 && pMlog->hdr.codewu== LOGAB_CODE_ACA) // set to 0 if result code!=0
	{
		m_iSBFoDivd = 0;
		m_iSBInv = 0;
		m_iDepWtw = 0;
		m_iExp = 0;
		m_iOnlWtwd = 0;
		m_iCashWtwd = 0;
		m_iOnlWtwCnt = 0;
		m_iCashWtwCnt = 0;

		m_iFundAva = 0;
		m_iBankGd = 0;
		m_iCurrDiv = 0;
		m_iPrevDiv = 0;
		m_iFbPayFor = 0;
		m_iNOVDivd = 0;
		m_iNOVInv = 0;
	}

	AddField64( m_iSBFoDivd, 0 );
	AddField64( m_iSBInv, 0 );
	AddField64( m_iDepWtw, 0 );
	AddField64( m_iExp, 0 );
	AddField64( m_iOnlWtwd, 0 );
	AddField64( m_iCashWtwd, 0 );
	AddField( m_iOnlWtwCnt, 0 );
	AddField( m_iCashWtwCnt, 0 );
	AddField( m_iSodTranNo, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );
// added in Q208
	AddField64( m_iNOVDivd, 0 );
	AddField64( m_iNOVInv, 0 );

	// added 201108PSR
	AddField( m_iAnonymous, 0 );  //Anonymous Account
	AddField( m_iCscCard, 0 );    //Transaction with CSC Card

	//char *p = buf;

	return buf;
}
