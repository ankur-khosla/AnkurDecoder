// ABStatCharge.cpp

#include "LOGDEF_AB.h"
#include "ABStatCharge.h"

char * ABStatCharge::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	memset( m_sFromDate, 0, 20 );
	memset( m_sToDate, 0, 20 );
	char m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

//	m_iAcctNo = pMlog->data.at.stmchg.req.accinfo.accnumlu;
	m_iReTrack = pMlog->data.at.stmchg.req.accinfo.rectrklu;
	m_iChargeAmt = (unsigned long) pMlog->data.at.stmchg.req.amtdu;

	m_cFromDay = pMlog->data.at.stmchg.req.fromdate.day;
	m_cFromMon = pMlog->data.at.stmchg.req.fromdate.month;
	m_iFromYear = pMlog->data.at.stmchg.req.fromdate.year;
	m_cToDay = pMlog->data.at.stmchg.req.todate.day;
	m_cToMon = pMlog->data.at.stmchg.req.todate.month;
	m_iToYear = pMlog->data.at.stmchg.req.todate.year;

	sprintf( m_sFromDate, "%d-%s-%d", m_cFromDay, m_sMonths[m_cFromMon-1], m_iFromYear );
	sprintf( m_sToDate, "%d-%s-%d", m_cToDay, m_sMonths[m_cToMon-1], m_iToYear );

	m_iFundAva	= (unsigned long) pMlog->data.at.stmchg.rpy.tran.fundd;
	m_iBankGd	= (unsigned long) pMlog->data.at.stmchg.rpy.tran.bankgd;
	m_iCurrDiv	= (unsigned long) pMlog->data.at.stmchg.rpy.tran.curDivd;
	m_iPrevDiv	= (unsigned long) pMlog->data.at.stmchg.rpy.tran.prvDivd;
	m_iFbPayFor	= (unsigned long) pMlog->data.at.stmchg.rpy.tran.sbPFtd;
	

//	AddField( m_iAcctNo, 0 );
	AddField( m_iReTrack, 0 );
	AddField( m_iChargeAmt, 0 );

	AddField( STORE_TYPE_STRING, m_sFromDate, 0 );
	AddField( STORE_TYPE_STRING, m_sToDate, 0 );

	AddField( m_iFundAva, 0 );
	AddField( m_iBankGd, 0 );
	AddField( m_iCurrDiv, 0 );
	AddField( m_iPrevDiv, 0 );
	AddField( m_iFbPayFor, 0 );

	return buf;
}
