// ABWithDraw.cpp

#include "LOGDEF_AB.h"
#include "ABWithDraw.h"

char * ABWithDraw::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i=0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	m_iAmount = ( unsigned long ) pMlog->data.bt.wtw.tran.amountd;
	//For FPS Transaction, If empty = 0. Refer to DV017 - EDABI SIS FY1920 R1 V1.5.doc
	if ((pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS) &&
		(pMlog->data.bt.wtw.tran.typebu == ACU_WTW_FPS) && (m_iAmount == '\0'))
	{
		m_iAmount = 0;
	}

	m_iCharge = ( unsigned long )pMlog->data.bt.wtw.tran.chargedu;
	m_cWithType = pMlog->data.bt.wtw.tran.typebu;
	m_cActiveBy = pMlog->data.bt.wtw.tran.actBybu;
	m_cSrcWith = pMlog->data.bt.wtw.tran.srcbu;
	m_cCancel = pMlog->data.bt.wtw.tran.cancel1;

	AddField( m_iAmount, 0 );
	AddField( m_iCharge, 0 );
	AddField( m_cWithType, 0 );
	AddField( m_cActiveBy, 0 );
	AddField( m_cSrcWith, 0 );
	AddField( m_cCancel, 0 );

	// m_iSecCode = pMlog->data.bt.wtw.eps.acc.eft.seculu;
	memset( m_sISN, 0, 10 );
	memset( m_sBankAcct, 0, sizeof(m_sBankAcct) );
	memset( m_sEftReReply, 0, sizeof(m_sEftReReply) );
	memset( m_sEftAcctNo, 0, sizeof(m_sEftAcctNo) );

	//CHANGED 201108PSR 
	//FILTER OUT THOSE ANONYMOUS ACCOUNTS
	if ((pMlog->hdr.anonymous1 == 0) && (pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CB ||
										 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CIT ||
										 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_EWIN||
										 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS))
	{
		//**** account/CIT related info ****//
		m_cCitMsn = pMlog->data.bt.wtw.eps.acc.cit.msnbu;
		m_iCitNo = pMlog->data.bt.wtw.eps.acc.cit.citlu;

		//**** eft gateway info ****//
		m_iEftChlMsn = pMlog->data.bt.wtw.eps.egw.gtwmsnlu;
		m_iEpsCode = pMlog->data.bt.wtw.eps.egw.epsretwu;
		m_iEftSize = pMlog->data.bt.wtw.eps.egw.eftSizewu;
		m_iEftNo = pMlog->data.bt.wtw.eps.egw.chanbu;
		m_iEftSub = pMlog->data.bt.wtw.eps.egw.subCodebu;


		for( i=0; i<6; i++ )
			m_sISN[i] = pMlog->data.bt.wtw.eps.egw.isnb[i];
	
		// sprintf( m_sISN+6, "%s", "\0" );

		for( i=0; i<ACU_BANK_ACN_SIZE; i++ )
			m_sBankAcct[i] = pMlog->data.bt.wtw.eps.egw.nbab[i];

		// sprintf( m_sBankAcct + ACU_BANK_ACN_SIZE + 1, "%s", "\0" );

		m_iEftPin = pMlog->data.bt.wtw.eps.egw.eftPinbu;
		m_iEftFlag = pMlog->data.bt.wtw.eps.egw.eftFlagbu;

		for( i=0; i<12; i++ )
			m_sEftAcctNo[i] = pMlog->data.bt.wtw.eps.egw.eftAccNo[i];
		
	}
	else
	{
		// account related info in cit tran
		m_cCitMsn = 0;
		m_iCitNo = 0;

		//**** eft gateway info ****//
		m_iEftChlMsn = 0;
		m_iEpsCode = 0;
		m_iEftSize = 0;
		m_iEftNo = 0;
		m_iEftSub = 0;
		m_iEftPin = 0;
		m_iEftFlag = 0;
	}

	// epin and ekt is no longer needed  -- calvin 2005-02-01
	AddField(0, 0);
	AddField(0, 0);

	AddField( m_cCitMsn, 0 );
	AddField( m_iCitNo, 0 );

	// account related info in eft tran
	//CHANGED 201108PSR 
	//FILTER OUT THOSE ANONYMOUS ACCOUNTS

	if ( pMlog->hdr.anonymous1 == 0 )
	{
		if ( pMlog->data.bt.wtw.eps.acc.eft.esc1 == 0 )
		{
			m_cEscEft = pMlog->data.bt.wtw.eps.acc.eft.esc1;
			//FPS
			if (pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS && pMlog->data.bt.wtw.tran.typebu == ACU_WTW_FPS)
			{
				m_iFundAva = (unsigned long)pMlog->data.bt.wtw.fps.aca.fundd;
				m_iBG = (unsigned long)pMlog->data.bt.wtw.fps.aca.bankgd;
				m_iCurDiv = (unsigned long)pMlog->data.bt.wtw.fps.aca.curDivd;
				m_iPreDiv = (unsigned long)pMlog->data.bt.wtw.fps.aca.prvDivd;
				m_iSbPay = (unsigned long)pMlog->data.bt.wtw.fps.aca.sbPFtd;
			}
			else
			{
				m_iFundAva = (unsigned long)pMlog->data.bt.wtw.eps.acc.eft.aca.fundd;
				m_iBG = (unsigned long)pMlog->data.bt.wtw.eps.acc.eft.aca.bankgd;
				m_iCurDiv = (unsigned long)pMlog->data.bt.wtw.eps.acc.eft.aca.curDivd;
				m_iPreDiv = (unsigned long)pMlog->data.bt.wtw.eps.acc.eft.aca.prvDivd;
				m_iSbPay = (unsigned long)pMlog->data.bt.wtw.eps.acc.eft.aca.sbPFtd;
			}

		}
		else {
			m_cEscEft = pMlog->data.bt.wtw.eps.acc.eft.esc1;
			m_iFundAva = 0;
			m_iBG = 0;
			m_iCurDiv = 0;
			m_iPreDiv = 0;
			m_iSbPay = 0;
		}
	}
	else {
		m_cEscEft = 0;
		m_iFundAva = 0;
		m_iBG = 0;
		m_iCurDiv = 0;
		m_iPreDiv = 0;
		m_iSbPay = 0;
	}

	//Added 201108PSR
	m_iAnonymous			= pMlog->hdr.anonymous1;  //Anonymous Account
	m_iCscCard				= pMlog->data.bt.wtw.tran.csctrn;  //Transaction with CSC Card 

	//FPS (6) for SP21a
	memset(m_iBankCode, 0, sizeof(m_iBankCode));
	if (pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_FPS && pMlog->data.bt.wtw.tran.typebu == ACU_WTW_FPS)
	{
		m_iFpsProcessId = pMlog->data.bt.wtw.fps.fpsinf.fpsprocessid;
		m_iChannelId = pMlog->data.bt.wtw.fps.fpsinf.channelid;
		m_iNbaNo = pMlog->data.bt.wtw.fps.fpsinf.nbano;
		for (i = 0; i<4; i++)
			m_iBankCode[i] = pMlog->data.bt.wtw.fps.fpsinf.bankcode[i];
		m_iActionType = pMlog->data.bt.wtw.fps.fpsinf.actiontype;
		m_iRefNo = pMlog->data.bt.wtw.fps.fpsinf.refno;
	}
	else
	{
		m_iFpsProcessId = 0;
		m_iChannelId = 0;
		m_iNbaNo = 0; //same as ab_deposit
		m_iBankCode[0] = '\0';
		m_iActionType = 0;
		m_iRefNo = 0;
	}

//	AddField( m_iSecCode, 0 );
	AddField( m_cEscEft, 0 );
	AddField( m_iFundAva, 0 );
	AddField( m_iBG, 0 );
	AddField( m_iCurDiv, 0 );
	AddField( m_iPreDiv, 0 );
	AddField( m_iSbPay, 0 );

	AddField( m_iEftChlMsn, 0 );
	AddField( m_iEpsCode, 0 );
	AddField( m_iEftSize, 0 );
	AddField( m_iEftNo, 0 );
	AddField( m_iEftSub, 0 );

	//char m_sEftReReply[LOGAB_EFTMSG_MAX] = pMlog->data.bt.wtw.eps.egw.eft;
	AddField( STORE_TYPE_STRING, m_sISN, 0 );
	AddField( STORE_TYPE_STRING, m_sBankAcct, 0 );

	// added for q405
	AddField( m_iEftPin, 0 );
	AddField( m_iEftFlag, 0 );
	AddField( STORE_TYPE_STRING, m_sEftAcctNo, 0 );

	// added 201108PSR
	AddField( m_iAnonymous, 0 );  //Anonymous Account
	AddField( m_iCscCard, 0 );    //Transaction with CSC Card

	// Added 201710EFTEMV
	m_iChipCard = 0;
	if (pMlog->hdr.codewu==LOGAB_CODE_WTW_EFT_EMV && pMlog->hdr.blocklu==LOGAB_EFT_EMV_ACK)
	{
		m_iChipCard = 1;
	}
	AddField( m_iChipCard, 0 ); 

	//FPS
	AddField(m_iFpsProcessId, 0);
	AddField(m_iChannelId, 0);
	AddField(m_iNbaNo, 0);
	AddField(STORE_TYPE_STRING,m_iBankCode, 0);
	AddField(m_iActionType, 0);
	AddField64(m_iRefNo, 0);

	return buf;
}
