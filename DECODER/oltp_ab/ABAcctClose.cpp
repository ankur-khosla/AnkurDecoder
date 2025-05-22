// ABAcctClose.cpp

#include "LOGDEF_AB.h"
#include "ABAcctClose.h"

char * ABAcctClose::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

//	m_iAcctNo = pMlog->data.at.acccls.req.accinfo.accnumlu;
	m_iReTrack = pMlog->data.at.acccls.req.accinfo.rectrklu;
	m_iWtwAmt =  pMlog->data.at.acccls.req.wdamtdu;
	m_cWtwType = pMlog->data.at.acccls.req.wdtypebu;

	m_iFundAva	= pMlog->data.at.acccls.rpy.tran.fundd;
	m_iBankGd	= pMlog->data.at.acccls.rpy.tran.bankgd;
	m_iCurrDiv	= pMlog->data.at.acccls.rpy.tran.curDivd;
	m_iPrevDiv	= pMlog->data.at.acccls.rpy.tran.prvDivd;
	m_iFbPayFor	= pMlog->data.at.acccls.rpy.tran.sbPFtd;
	

//	AddField( m_iAcctNo, 0 );
	AddField( m_iReTrack, 0 );
	AddField64( m_iWtwAmt, 0 );
	AddField( m_cWtwType, 0 );

	AddField64( m_iFundAva, 0 );
	AddField64( m_iBankGd, 0 );
	AddField64( m_iCurrDiv, 0 );
	AddField64( m_iPrevDiv, 0 );
	AddField64( m_iFbPayFor, 0 );

	return buf;
}
