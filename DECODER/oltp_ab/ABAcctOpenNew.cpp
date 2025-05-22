// ABAcctOpenNew.cpp

#include "LOGDEF_AB.h"
#include "ABAcctOpenNew.h"

char * ABAcctOpenNew::TranslateAction(const Msg *pMsg)
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
	memset( m_sBankNo2, 0, 10 );
	memset( m_sBranchNo2, 0, 10 );
	memset( m_sBankAcctNo2, 0, 20 );


	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

//	m_iAcctNo = pMlog->data.at.accopen.req.accinfo.accnumlu;
	m_iReTrack = pMlog->data.at.accopennew.req.accinfo.rectrklu;
	m_cCustSal = pMlog->data.at.accopennew.req.cusinfo.cussalbu;

    memset(m_sSureName, 0, sizeof(m_sSureName));
    memset(m_sOthName, 0, sizeof(m_sOthName));
    memset(m_sChiSureName, 0, sizeof(m_sChiSureName));
    memset(m_sChiOthName, 0, sizeof(m_sChiOthName));

	for( i=0; i<AA_SURNAME_LEN; i++ )
		m_sSureName[i] = pMlog->data.at.accopennew.req.cusinfo.surnames[i];

	for( i=0; i<AA_OTHNAME_LEN; i++ )
		m_sOthName[i] = pMlog->data.at.accopennew.req.cusinfo.othnames[i];

	for( i=0; i<AA_CHNSURNAME_LEN; i++ )
		m_sChiSureName[i] = pMlog->data.at.accopennew.req.cusinfo.chnsurnames[i];

	for( i=0; i<AA_CHNOTHNAME_LEN; i++ )
		m_sChiOthName[i] = pMlog->data.at.accopennew.req.cusinfo.chnothnames[i];


	m_cCustType = pMlog->data.at.accopennew.req.cusinfo.custypebu;
	m_cRaceBetFlag = pMlog->data.at.accopennew.req.cusinfo.rac1;
	m_cLotBetFlag = pMlog->data.at.accopennew.req.cusinfo.lot1;
	m_cSBBetFlag = pMlog->data.at.accopennew.req.cusinfo.sb1;
	m_cFBAcctType = pMlog->data.at.accopennew.req.cusinfo.fbtypebu;
	m_cLang = pMlog->data.at.accopennew.req.cusinfo.langbu;
	
    memset(m_sBankNo, 0, sizeof(m_sBankNo));
    memset(m_sBranchNo, 0, sizeof(m_sBranchNo));
    memset(m_sBankAcctNo, 0, sizeof(m_sBankAcctNo));
    memset(m_sBankNo2, 0, sizeof(m_sBankNo2));
    memset(m_sBranchNo2, 0, sizeof(m_sBranchNo2));
    memset(m_sBankAcctNo2, 0, sizeof(m_sBankAcctNo2));

	for( i=0; i<AA_BNKNUM_LEN; i++ )
		m_sBankNo[i] = pMlog->data.at.accopennew.req.nba1.bnknums[i];
	for( i=0; i<AA_BCHNUM_LEN; i++ )
		m_sBranchNo[i] = pMlog->data.at.accopennew.req.nba1.bchnums[i];
	for( i=0; i<AA_BNKACCNUM_LEN; i++ )
		m_sBankAcctNo[i] = pMlog->data.at.accopennew.req.nba1.bnkaccnums[i];

// new nba2 info
	for( i=0; i<AA_BNKNUM_LEN; i++ )
		m_sBankNo2[i] = pMlog->data.at.accopennew.req.nba2.bnknums[i];
	for( i=0; i<AA_BCHNUM_LEN; i++ )
		m_sBranchNo2[i] = pMlog->data.at.accopennew.req.nba2.bchnums[i];
	for( i=0; i<AA_BNKACCNUM_LEN; i++ )
		m_sBankAcctNo2[i] = pMlog->data.at.accopennew.req.nba2.bnkaccnums[i];

//	m_iSecCode = pMlog->data.at.accopen.req.seccodelu;
	m_cChgCode = pMlog->data.at.accopennew.req.forcebu;

//	AddField( m_iAcctNo, 0 );
	AddField( m_iReTrack, 0 );
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
	AddField( STORE_TYPE_STRING, m_sBankNo, 0 );
	AddField( STORE_TYPE_STRING, m_sBranchNo, 0 );
	AddField( STORE_TYPE_STRING, m_sBankAcctNo, 0 );
	AddField( STORE_TYPE_STRING, m_sBankNo2, 0 );
	AddField( STORE_TYPE_STRING, m_sBranchNo2, 0 );
	AddField( STORE_TYPE_STRING, m_sBankAcctNo2, 0 );
//	AddField( m_iSecCode, 0 );
	AddField( m_cChgCode, 0 );

	return buf;
}
