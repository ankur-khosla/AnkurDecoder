// ABAcctDetail.cpp

#include "LOGDEF_AB.h"
#include "ABAcctDetail.h"

char * ABAcctDetail::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i=0;

	memset( m_sSureName, 0, 50 );
	memset( m_sOthName, 0, 50 );
	memset( m_sChiSureName, 0, 50 );
	memset( m_sChiOthName, 0, 50 );
	memset( m_sBankNo, 0, 10 );
	memset( m_sBranchNo, 0, 10 );
	memset( m_sBankAcctNo, 0, 20 );

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

//	m_iAcctNo = pMlog->data.at.accupd.req.accinfo.accnumlu;
	m_iReTrack = pMlog->data.at.accupd.req.accinfo.rectrklu;
	m_cAcctDetType = pMlog->data.at.accupd.req.acctypebu;

    memset(m_sSureName, 0, sizeof(m_sSureName));
    memset(m_sOthName, 0, sizeof(m_sOthName));
    memset(m_sChiSureName, 0, sizeof(m_sChiSureName));
    memset(m_sChiOthName, 0, sizeof(m_sChiOthName));

	memset(m_sBankNo, 0, sizeof(m_sBankNo));
	memset(m_sBranchNo, 0, sizeof(m_sBranchNo));
	memset(m_sBankAcctNo, 0, sizeof(m_sBankAcctNo));

	if ( m_cAcctDetType == 1 )
	{
		m_cCustSal = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.cussalbu;

		for( i=0; i<AA_SURNAME_LEN; i++ )
			m_sSureName[i] = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.surnames[i];

		for( i=0; i<AA_OTHNAME_LEN; i++ )
			m_sOthName[i] = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.othnames[i];

		for( i=0; i<AA_CHNSURNAME_LEN; i++ )
			m_sChiSureName[i] = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.chnsurnames[i];

		for( i=0; i<AA_CHNOTHNAME_LEN; i++ )
			m_sChiOthName[i] = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.chnothnames[i];


		m_cCustType = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.custypebu;
		m_cRaceBetFlag = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.rac1;
		m_cLotBetFlag = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.lot1;
		m_cSBBetFlag = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.sb1;
		m_cFBAcctType = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.fbtypebu;
		m_cLang = pMlog->data.at.accupd.req.accdet.accsinfo.cusinfo.langbu;

		m_cAcctStatus = pMlog->data.at.accupd.req.accdet.accsinfo.accstatusbu;
	}
	else
	{
		m_cCustSal = 0;
		m_cCustType = 0;
		m_cRaceBetFlag = 0;
		m_cLotBetFlag = 0;
		m_cSBBetFlag = 0;
		m_cFBAcctType = 0;
		m_cLang = 0;
		m_cAcctStatus = 0;

		for( i=0; i<AA_BNKNUM_LEN; i++ )
			m_sBankNo[i] = pMlog->data.at.accupd.req.accdet.nba.bnknums[i];
		for( i=0; i<AA_BCHNUM_LEN; i++ )
			m_sBranchNo[i] = pMlog->data.at.accupd.req.accdet.nba.bchnums[i];
		for( i=0; i<AA_BNKACCNUM_LEN; i++ )
			m_sBankAcctNo[i] = pMlog->data.at.accupd.req.accdet.nba.bnkaccnums[i];
	}

	m_iAcctBal = pMlog->data.at.accupd.rpy.rpy.balanced;

//	AddField( m_iAcctNo, 0 );
	AddField( m_iReTrack, 0 );
	AddField( m_cAcctDetType, 0 );
	AddField( m_cCustSal, 0 );
	AddField( STORE_TYPE_STRING, m_sSureName, 0 );
	AddField( STORE_TYPE_STRING, m_sOthName, 0 );
	AddField( STORE_TYPE_STRING, m_sChiSureName, 0 );
	AddField( STORE_TYPE_STRING, m_sChiOthName, 0 );
	AddField( m_cCustType, 0 );
	AddField( m_cRaceBetFlag, 0 );
	AddField( m_cLotBetFlag, 0 );
	AddField( m_cSBBetFlag, 0 );
	AddField( m_cFBAcctType, 0 );
	AddField( m_cLang, 0 );
	AddField( m_cAcctStatus, 0 );
	AddField( STORE_TYPE_STRING, m_sBankNo, 0 );
	AddField( STORE_TYPE_STRING, m_sBranchNo, 0 );
	AddField( STORE_TYPE_STRING, m_sBankAcctNo, 0 );
	AddField64( m_iAcctBal, 0 );

	return buf;
}
