// ABEftMisc.cpp


#include "LOGDEF_AB.h"
#include "ABEftMisc.h"

char * ABEftMisc::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

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
	AddField( m_cChannelNo, 0 );
	AddField( m_iEftSize, 0 );
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

	// Added 201710EFTEMV
	m_iChipCard = 0;
	if (pMlog->hdr.codewu == LOGAB_CODE_EFT_EMV_MISC)
	{
		m_iChipCard = 1;
	}
	AddField(m_iChipCard, 0 );

	return buf;
}
