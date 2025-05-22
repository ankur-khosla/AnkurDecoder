// ABRecall.cpp

#include "LOGDEF_AB.h"
#include "ABRecall.h"

char * ABRecall::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	char m_cMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/********* Start to decode ****************/

	struct tm *state_d;
	memset( m_sStatementDate, 0, sizeof(m_sStatementDate));
	if ( pMlog->data.bt.rcl.typebu == 3 )
	{
		state_d	= _localtime32( &pMlog->data.bt.rcl.data.rstaSta.date );
		sprintf(m_sStatementDate, "%d-%s-%d", state_d->tm_mday, m_cMonths[state_d->tm_mon], 1900+state_d->tm_year);
	}
	m_iRecallType	= pMlog->data.bt.rcl.typebu;
	m_iAcctNo		= pMlog->data.bt.rcl.data.rstaSta.acclu;
	m_iBlkNo		= pMlog->data.bt.rcl.data.rstaCon.blocklu;
	m_iBlkOffset	= pMlog->data.bt.rcl.data.rstaCon.blkOffwu;
	m_iTranOffset	= pMlog->data.bt.rcl.data.rstaCon.trnOffwu;
	m_iFileNo		= pMlog->data.bt.rcl.data.rstaCon.filewu;
	m_iTranNo		= pMlog->data.bt.rcl.data.rstaTxn.tranwu;  //Changed 201108PSR

	AddField( m_iRecallType, 0 );
	AddField( STORE_TYPE_STRING, m_sStatementDate, 0 );
	AddField( m_iAcctNo, 0 );
//	AddField( m_iBlkNo, 0 );
//	AddField( m_iBlkOffset, 0 );
//	AddField( m_iTranOffset, 0 );
//	AddField( m_iFileNo, 0 );
	AddField( m_iTranNo, 0 );


	return buf;
}
