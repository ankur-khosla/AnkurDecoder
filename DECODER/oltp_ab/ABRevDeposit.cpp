// ABRevDeposit

#include "LOGDEF_AB.h"
#include "ABRevDeposit.h"

char * ABRevDeposit::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	char m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	m_iAmount		= ( unsigned long ) pMlog->data.bt.dep.tran.amountdu;
	m_iSvcCharge	= ( unsigned long ) pMlog->data.bt.dep.tran.chargedu;
	m_cDepType		= pMlog->data.bt.dep.tran.typebu;
	m_cWthHold		= pMlog->data.bt.dep.tran.hold1;
	m_cCancel		= pMlog->data.bt.dep.tran.cancel1;
	m_cReversed		= pMlog->data.bt.dep.tran.reversed1;
	m_cSrcDep		= pMlog->data.bt.dep.tran.srcbu;

	//**** Deposit Detail ****//
	// epsco info -- account related info
	// cit transaction
	int i=0;

	for( i=0; i<8; i++ )
		m_sEpin[8] = pMlog->data.bt.dep.data.eps.acc.cit.epinbu[i];
	for( i=0; i<9; i++ )
		m_sEkt[9] = pMlog->data.bt.dep.data.eps.acc.cit.ektbu[i];

	m_cCitMsn = pMlog->data.bt.dep.data.eps.acc.cit.msnbu;
	m_cCitNo = pMlog->data.bt.dep.data.eps.acc.cit.citlu;

	// eft transaction from cb
	m_iEscEftTran = pMlog->data.bt.dep.data.eps.acc.eft.esc1;

	memset( m_sEftAcctNo, 0, sizeof(m_sEftAcctNo) );

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

	memset( m_sISN, 0, sizeof(m_sISN) );
	memset( m_sBankNo, 0, sizeof(m_sBankNo) );

	if ( pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CB ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_CIT ||
		 pMlog->hdr.source.srcTypebu == LOGAB_SRC_EFT_EWIN )
	{
		for( i=0; i<6; i++ )
			m_sISN[i] = pMlog->data.bt.dep.data.eps.egw.isnb[i];
		for( i=0; i<ACU_BANK_ACN_SIZE; i++ )
			m_sBankNo[i] = pMlog->data.bt.dep.data.eps.egw.nbab[i];
	}

	// account access info
	m_iFundAva	= ( unsigned long )pMlog->data.bt.dep.data.tb.aca.fundd;
	m_iBankG		= ( unsigned long ) pMlog->data.bt.dep.data.tb.aca.bankgd;
	m_iCurDivd	= ( unsigned long ) pMlog->data.bt.dep.data.tb.aca.curDivd;
	m_iPrvDivd	= ( unsigned long ) pMlog->data.bt.dep.data.tb.aca.prvDivd;
	m_iSBPayout	= ( unsigned long ) pMlog->data.bt.dep.data.tb.aca.sbPFtd;

	AddField( m_iAmount, 0 );
	AddField( m_iSvcCharge, 0 );
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
	AddField( m_cCitNo, 0 );
	AddField( m_iEscEftTran, 0 );
	AddField( m_iChannelMsn, 0 );
	AddField( m_iRetCode, 0 );
	AddField( m_iEftSize, 0 );
	AddField( m_cChannelNo, 0 );
	AddField( m_cSubcode, 0 );

	AddField( STORE_TYPE_STRING, m_sISN, 0 );
	AddField( STORE_TYPE_STRING, m_sBankNo, 0 );

	AddField( m_iFundAva, 0 );
	AddField( m_iBankG, 0 );
	AddField( m_iCurDivd, 0 );
	AddField( m_iPrvDivd, 0 );
	AddField( m_iSBPayout, 0 );

	AddField( m_iEftPin, 0 );
	AddField( m_iEftFlag, 0 );
	AddField( STORE_TYPE_STRING, m_sEftAcctNo, 0 );

	return buf;
}
