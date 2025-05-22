// ABEftAcctBal.cpp

#include "LOGDEF_AB.h"
#include "ABEftAcctBal.h"

char * ABEftAcctBal::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/
/*	// Change in Q207 wrong structure has been used to decode this message
	m_cPantype = pMlog->data.bt.accbal.pancap.typebu;
	memset( m_sPan, 0, sizeof( m_sPan ) );
	for( i=0; i<ACU_PAN_SIZE; i++ ) {
		m_sPan[i] = pMlog->data.bt.accbal.pancap.pans[i];
	}
	

	m_iEscEft = pMlog->data.bt.accbal.eft.esc1;

	m_iFundAva	= ( unsigned long )pMlog->data.bt.accbal.eft.aca.fundd;    // funds available
	m_iBankGd	= ( unsigned long )pMlog->data.bt.accbal.eft.aca.bankgd;   // bank guarentee
	m_iCurrDiv	= ( unsigned long )pMlog->data.bt.accbal.eft.aca.curDivd;  // unsettled dividend
	m_iPrevDiv	= ( unsigned long )pMlog->data.bt.accbal.eft.aca.prvDivd;  // previous dividend
	m_iFbPayFor	= ( unsigned long )pMlog->data.bt.accbal.eft.aca.sbPFtd;   // soccer fo payout forfeited

	m_cEftChanNo = pMlog->data.bt.accbal.chanbu;
	m_iGtwMsn = pMlog->data.bt.accbal.gtwmsnlu;

	AddField( m_cPantype, 0 );
	AddField( STORE_TYPE_STRING, m_sPan, 0 );
	AddField( m_iEscEft, 0 );
	AddField( m_iFundAva, 0 );
	AddField( m_iBankGd, 0 );
	AddField( m_iCurrDiv, 0 );
	AddField( m_iPrevDiv, 0 );
	AddField( m_iFbPayFor, 0 );
	AddField( m_cEftChanNo, 0 );
	AddField( m_iGtwMsn, 0 );
*/


	/************* Start to decode ************/
	for( i=0; i<8; i++ )
		m_sEpin[i] = pMlog->data.bt.eftmisc.cit.epinbu[i];
	for( i=0; i<27; i++ )
		m_sEkt[i] = pMlog->data.bt.eftmisc.cit.ektbu[i];

	m_cCitMsn = pMlog->data.bt.eftmisc.cit.msnbu;
	m_iCitNo = pMlog->data.bt.eftmisc.cit.citlu;


	m_iChannelMsn = pMlog->data.bt.eftmisc.eps.gtwmsnlu;
	m_iPsuedoNo = pMlog->data.bt.eftmisc.eps.psuedowu;
	m_iRetCode = pMlog->data.bt.eftmisc.eps.epsretwu;
	m_iEftSize = pMlog->data.bt.eftmisc.eps.eftSizewu;
	m_cChannelNo = pMlog->data.bt.eftmisc.eps.chanbu;
	m_cSubcode = pMlog->data.bt.eftmisc.eps.subCodebu;
	int iEftFlag = pMlog->data.bt.eftmisc.eps.eftFlagbu;
	int iEftPin = pMlog->data.bt.eftmisc.eps.eftPinbu;


    memset(m_sISN, 0, sizeof(m_sISN));
    memset(m_sBankNo, 0, sizeof(m_sBankNo));
    memset(m_sBankAcctNo, 0, sizeof(m_sBankAcctNo));
    memset(m_sEftReq, 0, sizeof(m_sEftReq));

	for( i=0; i<6; i++ )
		m_sISN[i] = pMlog->data.bt.cvi.eps.isnb[i];

	for( i=0; i<ACU_BANK_SIZE+1; i++ )
		m_sBankNo[i] = pMlog->data.bt.cvi.eps.banks[i];

	for( i=0; i<ACU_BANK_ACN_SIZE; i++ )
		m_sBankAcctNo[i] = pMlog->data.bt.cvi.eps.nbab[i];

	for( i=0; i<LOGAB_EFTMSG_MAX; i++ )
		m_sEftReq[i] = pMlog->data.bt.cvi.eps.eftb[i];
/*
	AddField( STORE_TYPE_STRING, m_sEpin, 0 );
	AddField( STORE_TYPE_STRING, m_sEkt, 0 );
*/
	AddField( 0, 0 );
	AddField( 0, 0 );

	AddField( m_cCitMsn, 0 );
	AddField( m_iCitNo, 0 );

	AddField( m_iChannelMsn, 0 );
	AddField( m_iPsuedoNo, 0 );
	AddField( m_iRetCode, 0 );
	AddField( m_iEftSize, 0 );
	AddField( m_cChannelNo, 0 );
	AddField( m_cSubcode, 0 );
/*
	AddField( STORE_TYPE_STRING, m_sISN, 0 );
	AddField( STORE_TYPE_STRING, m_sBankNo, 0 );
	AddField( STORE_TYPE_STRING, m_sBankAcctNo, 0 );
	AddField( STORE_TYPE_STRING, m_sEftReq, 0 );
*/
	AddField( 0, 0 );
	AddField( 0, 0 );
	AddField( 0, 0 );
	AddField( 0, 0 );

	AddField( iEftFlag, 0 );
	AddField( iEftPin, 0 );

	return buf;
}
