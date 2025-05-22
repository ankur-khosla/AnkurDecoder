// ABTerminateBet.cpp: implementation of the ABTerminateBet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LOGDEF_AB.h"
#include "ABTerminateBet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ABTerminateBet::ABTerminateBet()
{

}

ABTerminateBet::~ABTerminateBet()
{

}

char * ABTerminateBet::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);
	char	m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	char	m_sMeetDate[30];
	memset( m_sMeetDate, 0, sizeof(m_sMeetDate ) );

	struct tm *meet_t = _localtime32( &pMlog->data.bt.termb.businessDate );
	sprintf(m_sMeetDate, "%02d-%s-%d %02d:%02d:%02d", meet_t->tm_mday, m_sMonths[meet_t->tm_mon], meet_t->tm_year+1900, meet_t->tm_hour, meet_t->tm_min, meet_t->tm_sec);

	int m_iTermTranNO = pMlog->data.bt.termb.termTranNo;
	int m_iTermTranCode = pMlog->data.bt.termb.termTranCode;
	int m_iAcctFileNo = pMlog->data.bt.termb.acctFileNo;
	int m_iAcctBlkNo = pMlog->data.bt.termb.acctBlkNo;
	int m_iOffset = pMlog->data.bt.termb.offset;
	int m_iToken = pMlog->data.bt.termb.token;
	__int64 m_iDividend = pMlog->data.bt.termb.dividend;
	__int64 m_iRefund = pMlog->data.bt.termb.refund;
	__int64 m_iForfeitSbDiv = pMlog->data.bt.termb.forfSbDiv;
	int m_iTermOthUnit = pMlog->data.bt.termb.termOtherUnit;
	int m_iTermPrevDate = pMlog->data.bt.termb.termPrevDate;

	AddField( m_iTermTranNO, 0 );
	AddField( m_iTermTranCode, 0 );
//	AddField( m_iAcctFileNo, 0 );
//	AddField( m_iAcctBlkNo, 0 );
//	AddField( m_iOffset, 0 );
//	AddField( m_iToken, 0 );
	AddField( STORE_TYPE_STRING, m_sMeetDate, 0 );
	AddField64( m_iDividend, 0 );
	AddField64( m_iRefund, 0 );
	AddField64( m_iForfeitSbDiv, 0 );
	AddField( m_iTermOthUnit, 0 );
	AddField( m_iTermPrevDate, 0 );
	

	return buf;
}
