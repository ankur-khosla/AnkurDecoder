// ABDeposit



#include "LOGDEF_AB.h"
#include "ABDeposit.h"

char * ABDeposit::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	const char m_cMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	tm* r_time;
	r_time = _localtime32( &pMlog->data.bt.dep.tran.holdtime );
	sprintf(m_sRelTime, "%d-%s-%d", r_time->tm_mday, m_cMonths[r_time->tm_mon], 1900+r_time->tm_year);

	m_iAmount		= pMlog->data.bt.dep.tran.amountdu;
	//For FPS Transaction, If empty = 0. Refer to DV017 - EDABI SIS FY1920 R1 V1.5.doc
	if ((pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS) &&
		(pMlog->data.bt.dep.tran.typebu == ACU_DEP_FPS) && (m_iAmount == '\0'))
	{
		m_iAmount = 0;
	}
	m_iSvcCharge	= pMlog->data.bt.dep.tran.chargedu;
	m_cDepType		= pMlog->data.bt.dep.tran.typebu;
	m_cWthHold		= pMlog->data.bt.dep.tran.hold1;
	m_cCancel		= pMlog->data.bt.dep.tran.cancel1;
	m_cReversed		= pMlog->data.bt.dep.tran.reversed1;
	m_cSrcDep		= pMlog->data.bt.dep.tran.srcbu;
	m_iAnonymous    = pMlog->hdr.anonymous1;  // Anonymous account (2011IBT)
	m_iCscCard      = pMlog->data.bt.dep.tran.csctrn;  //Transaction with CSC Card (201108PSR)
/*
	if ( pMlog->data.bt.dep.tran.secondnba1 == 1)
	{
		m_cNBANo		= 2;	// second NBA
	} 
	else
	{
		m_cNBANo		= 1;	// first NBA
	}
*/	


	//**** Deposit Detail ****//
	// epsco info -- account related info
	// cit transaction
	int i=0;
	// 
	for( i=0; i<8; i++ )
		m_sEpin[i] = pMlog->data.bt.dep.data.eps.acc.cit.epinbu[i];
	for( i=0; i<9; i++ )
		m_sEkt[i] = pMlog->data.bt.dep.data.eps.acc.cit.ektbu[i];

	m_cCitMsn = pMlog->data.bt.dep.data.eps.acc.cit.msnbu;
	m_iCitNo = pMlog->data.bt.dep.data.eps.acc.cit.citlu;

	// eft transaction from cb
	m_iEscEftTran = pMlog->data.bt.dep.data.eps.acc.eft.esc1;

	memset( m_sEftAcctNo, 0, sizeof(m_sEftAcctNo) );
	memset( m_sISN, 0, sizeof(m_sISN) );
	memset( m_sBankNo, 0, sizeof(m_sBankNo) );

	if ( pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CB ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CIT ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_EWIN ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS)
	{
		// epsco info -- eft gateway info
		m_iChannelMsn = pMlog->data.bt.dep.data.eps.egw.gtwmsnlu;
		m_iRetCode = pMlog->data.bt.dep.data.eps.egw.epsretwu;
		m_iEftSize = pMlog->data.bt.dep.data.eps.egw.eftSizewu;
		m_cChannelNo = pMlog->data.bt.dep.data.eps.egw.chanbu;
		m_cSubcode = pMlog->data.bt.dep.data.eps.egw.subCodebu;
		m_iEftPin = pMlog->data.bt.dep.data.eps.egw.eftPinbu;
		m_iEftFlag = pMlog->data.bt.dep.data.eps.egw.eftFlagbu;

		for( i=0; i<12; i++ )
			m_sEftAcctNo[i] = pMlog->data.bt.dep.data.eps.egw.eftAccNo[i];

		for( i=0; i<6; i++ )
			m_sISN[i] = pMlog->data.bt.dep.data.eps.egw.isnb[i];
		for( i=0; i<ACU_BANK_ACN_SIZE; i++ )
			m_sBankNo[i] = pMlog->data.bt.dep.data.eps.egw.nbab[i];
	
	}
	else
	{
		m_iChannelMsn = 0;
		m_iRetCode = 0;
		m_iEftSize = 0;
		m_cChannelNo = 0;
		m_cSubcode = 0;
		m_iEftPin = 0;
		m_iEftFlag = 0;
		m_cNBANo = 0;  //q310  nba no

	}

	if ( pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_TBASD ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CIT ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_EWIN )
	{	
		m_cNBANo = pMlog->data.bt.dep.data.eps.egw.nbano;   // q310 nba no
	}

	// account access info
	if ( m_iEscEftTran == 1 && pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CB )
	{
		m_iFundAva = pMlog->data.bt.dep.data.eps.acc.eft.aca.fundd;
		m_iBankG = pMlog->data.bt.dep.data.eps.acc.eft.aca.bankgd;
		m_iCurDivd = pMlog->data.bt.dep.data.eps.acc.eft.aca.curDivd;
		m_iPrvDivd = pMlog->data.bt.dep.data.eps.acc.eft.aca.prvDivd;
		m_iSBPayout = pMlog->data.bt.dep.data.eps.acc.eft.aca.sbPFtd;
	}
	else if (pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS && m_cDepType == ACU_DEP_FPS) //FPS
	{
		m_iFundAva = pMlog->data.bt.dep.data.fps.aca.fundd;
		m_iBankG = pMlog->data.bt.dep.data.fps.aca.bankgd;
		m_iCurDivd = pMlog->data.bt.dep.data.fps.aca.curDivd;
		m_iPrvDivd = pMlog->data.bt.dep.data.fps.aca.prvDivd;
		m_iSBPayout = pMlog->data.bt.dep.data.fps.aca.sbPFtd;
	}
	else {
		m_iFundAva = 0;
		m_iBankG = 0;
		m_iCurDivd = 0;
		m_iPrvDivd = 0;
		m_iSBPayout = 0;
	}

	//FPS (22) for SP21a
	memset(m_iBankCode, 0, sizeof(m_iBankCode));
	if (pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS && m_cDepType == ACU_DEP_FPS)
	{
		m_iFpsProcessId = pMlog->data.bt.dep.data.fps.fpsinf.fpsprocessid;
		m_iChannelId = pMlog->data.bt.dep.data.fps.fpsinf.channelid;
		m_cNBANo = pMlog->data.bt.dep.data.fps.fpsinf.nbano;
		for (i = 0; i<4; i++)
			m_iBankCode[i] = pMlog->data.bt.dep.data.fps.fpsinf.bankcode[i];
		m_iActionType = pMlog->data.bt.dep.data.fps.fpsinf.actiontype;
		m_iRefNo = pMlog->data.bt.dep.data.fps.fpsinf.refno;
	}
	else
	{
		m_iFpsProcessId = 0;
		m_iChannelId = 0;
		if (pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_TBASD ||
			pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CIT ||
			pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_EWIN)
		{
			m_cNBANo = pMlog->data.bt.dep.data.eps.egw.nbano;
		}
		else
		{
			m_cNBANo = 0; 
		}

		m_iBankCode[0] = '\0';
		m_iActionType = 0;
		m_iRefNo = 0;
	}

	AddField( STORE_TYPE_STRING, m_sRelTime, 0 );
	AddField64( m_iAmount, 0 );
	AddField64( m_iSvcCharge, 0 );
	AddField( m_cDepType, 0 );
	AddField( m_cWthHold, 0 );
	AddField( m_cCancel, 0 );
	AddField( m_cReversed, 0 );
	AddField( m_cSrcDep, 0 );
	// L6.1r1f add 0 to epin and ekt
	/*
	AddField( STORE_TYPE_STRING, m_sEpin, 0 );
	AddField( STORE_TYPE_STRING, m_sEkt, 0 );
	*/
	AddField( 0, 0 );
	AddField( 0, 0 );
	AddField( m_cCitMsn, 0 );
	AddField( m_iCitNo, 0 );
	AddField( m_iEscEftTran, 0 );
	AddField( m_iChannelMsn, 0 );
	AddField( m_iRetCode, 0 );
	AddField( m_iEftSize, 0 );
	AddField( m_cChannelNo, 0 );
	AddField( m_cSubcode, 0 );

	AddField( STORE_TYPE_STRING, m_sISN, 0 );
	AddField( STORE_TYPE_STRING, m_sBankNo, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankG, 0 );
	AddField64( m_iCurDivd, 0 );
	AddField64( m_iPrvDivd, 0 );
	AddField64( m_iSBPayout, 0 );

	AddField( m_iEftPin, 0 );
	AddField( m_iEftFlag, 0 );
	AddField( STORE_TYPE_STRING, m_sEftAcctNo, 0 );

	//The 3 fields are only for ABDeposit (11)
	if (pMsg->m_iMsgCode == LOGAB_CODE_DEP || pMlog->hdr.codewu == LOGAB_CODE_DEP_EFT_EMV)
	{
		AddField(m_cNBANo, 0);   // add in Q210 nba_no
		AddField(m_iAnonymous, 0);     //Anonymous Account (2011IBT)
		AddField(m_iCscCard, 0);     //Transaction with CSC Card (201108PSR)

		// Added 201710EFTEMV
		m_iChipCard = 0;
		if (pMlog->hdr.codewu == LOGAB_CODE_DEP_EFT_EMV && pMlog->hdr.blocklu == LOGAB_EFT_EMV_ACK)
		{
			m_iChipCard = 1;
		}
		AddField(m_iChipCard, 0);
	}
	else
	{
		AddField(0, 0);
		AddField(0, 0);     
		AddField(0, 0);  
		AddField(0, 0);
	}

	//FPS
	AddField(m_iFpsProcessId, 0);
	AddField(m_iChannelId, 0);
	AddField(STORE_TYPE_STRING,m_iBankCode ,0);
	AddField(m_iActionType, 0);
	AddField64(m_iRefNo, 0);


	return buf;
}
