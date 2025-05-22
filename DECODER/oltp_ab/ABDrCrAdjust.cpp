// ABDrCrAdjust.cpp

#include "LOGDEF_AB.h"
#include "ABDrCrAdjust.h"

char * ABDrCrAdjust::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	int i = 0;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	memset( m_sRemarks, 0, 100 );

	/***************** Start to decode *******************/

//	m_iAcctNo = pMlog->data.at.detcrt.req.accinfo.accnumlu;
	m_iReTrack = pMlog->data.at.detcrt.req.accinfo.rectrklu;
	m_cDrCrType = pMlog->data.at.detcrt.req.type1;
	m_cNegBal = pMlog->data.at.detcrt.req.negbal1;

	m_iAmount = (unsigned __int64) pMlog->data.at.detcrt.req.amtdu;
	m_iTxnType = pMlog->data.at.detcrt.req.txntypewu;

	for( i=0; i<AA_DRCR_RMK_LEN; i++ )
		m_sRemarks[i] = pMlog->data.at.detcrt.req.remarks[i];

	m_iFundAva	= pMlog->data.at.detcrt.rpy.tran.fundd;
	m_iBankGd	= pMlog->data.at.detcrt.rpy.tran.bankgd;
	m_iCurrDiv	= pMlog->data.at.detcrt.rpy.tran.curDivd;
	m_iPrevDiv	= pMlog->data.at.detcrt.rpy.tran.prvDivd;
	m_iFbPayFor	= pMlog->data.at.detcrt.rpy.tran.sbPFtd;
	

//	AddField( m_iAcctNo, 0 );
	AddField( m_iReTrack, 0 );
	AddField( m_cDrCrType, 0 );
	AddField( m_cNegBal, 0 );

	AddField64( m_iAmount, 0 );
	AddField( m_iTxnType, 0 );
	AddField( STORE_TYPE_STRING, m_sRemarks, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

	return buf;
}
