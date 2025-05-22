// ABBatchDep.h


#include "LOGDEF_AB.h"
#include "ABBatchDep.h"

char * ABBatchDep::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	int i = 0;
	memset( m_sBankCode, 0, 5 );
	memset( m_sBankAcctNo, 0, 20 );
	memset( m_sReqAcctNo, 0, 30 );
	memset( m_sValueDate, 0, 20 );
	memset( m_sCalDate, 0, 20 );
	char m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	PackHeader("", pMlog, pMsg);

	/************** Start to decode **************/

	m_cValDay		= pMlog->data.deph.data.tran.data.valdate.day;
	m_cValMon		= pMlog->data.deph.data.tran.data.valdate.month;
	m_iValYear		= pMlog->data.deph.data.tran.data.valdate.year;
	m_cCalDay		= pMlog->data.deph.data.tran.data.caldate.day;
	m_cCalMon		= pMlog->data.deph.data.tran.data.caldate.month;
	m_iCalYear		= pMlog->data.deph.data.tran.data.caldate.year;
	m_cDepSendType	= pMlog->data.deph.data.tran.data.typebu;
	m_iBatchAcctNo	= pMlog->data.deph.data.tran.data.batnumlu; 




	if ( m_iValYear != 0 ) 
		sprintf( m_sValueDate, "%d-%s-%d", m_cValDay, m_sMonths[m_cValMon-1], m_iValYear );
	else
		sprintf( m_sValueDate, "");

	sprintf( m_sCalDate, "%d-%s-%d", m_cCalDay, m_sMonths[m_cCalMon-1], m_iCalYear );

	
    memset(m_sBankCode, 0, sizeof(m_sBankCode));
    memset(m_sBankAcctNo, 0, sizeof(m_sBankAcctNo));
    memset(m_sReqAcctNo, 0, sizeof(m_sReqAcctNo));
/*
	for( i=0; i<AA_BANKCODE_LEN; i++ )
		m_sBankCode[i] = pMlog->data.deph.data.tran.data.bankcode[i];
*/
	m_iBankCode = pMlog->data.deph.data.tran.data.bankcodewu;
	for( i=0; i<BCS_ACCNUM_LEN; i++ )
		m_sBankAcctNo[i] = pMlog->data.deph.data.tran.data.bankacc[i];

	m_iInputSeqNo = pMlog->data.deph.data.tran.data.seqnumlu;
	m_iClubAcctNo = pMlog->data.deph.data.tran.data.clubaccnumlu;

	for( i=0; i<AA_REQACCNUM_LEN; i++ )
		m_sReqAcctNo[i] = pMlog->data.deph.data.tran.data.reqclubaccnumacc[i];

	m_iAmount = (__int64) pMlog->data.deph.data.tran.data.amtdu;

	m_iReFee = pMlog->data.deph.data.tran.feelu;
	m_iIntSeqNo = pMlog->data.deph.data.tran.seqlu;
	m_cChannelNo = pMlog->data.deph.data.tran.chanbu;

	// account access info
	m_iFundAva	= pMlog->data.deph.tran.fundd;
	m_iBankG	= pMlog->data.deph.tran.bankgd;
	m_iCurDivd	= pMlog->data.deph.tran.curDivd;
	m_iPrvDivd	= pMlog->data.deph.tran.prvDivd;
	m_iSBPayout	= pMlog->data.deph.tran.sbPFtd;

	m_cNBANo = pMlog->data.bt.dep.data.eps.egw.nbano;
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

	AddField( STORE_TYPE_STRING, m_sValueDate, 0 );
	AddField( STORE_TYPE_STRING, m_sCalDate, 0 );
	AddField( m_cDepSendType, 0 );
	AddField( m_iBatchAcctNo, 0 );
	AddField( m_iBankCode, 0 );
	AddField( STORE_TYPE_STRING, m_sBankAcctNo, 0 );
	AddField( m_iInputSeqNo, 0 );
	AddField( m_iClubAcctNo, 0 );

	AddField( STORE_TYPE_STRING, m_sReqAcctNo, 0 );
	AddField64( m_iAmount, 0 );
	AddField( m_iReFee, 0 );
	AddField( m_iIntSeqNo, 0 );
	AddField( m_cChannelNo, 0 );


	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankG, 0 );
	AddField64( m_iCurDivd, 0 );
	AddField64( m_iPrvDivd, 0 );
	AddField64( m_iSBPayout, 0 );

	AddField( m_cNBANo, 0 );   // add in Q210 nba_no

	return buf;
}
