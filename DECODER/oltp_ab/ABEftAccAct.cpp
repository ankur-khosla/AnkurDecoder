// ABEftAccAct.cpp: implementation of the ABEftAccAct class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABEftAccAct.h"
#include "LOGDEF_AB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ABEftAccAct::ABEftAccAct()
{

}

ABEftAccAct::~ABEftAccAct()
{

}
char * ABEftAccAct::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	int i = 0;

	char m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	PackHeader("", pMlog, pMsg);

	/************** Start to decode **************/
	unsigned char m_cValDay;
	unsigned char m_cValMon;
	unsigned short m_iValYear;

	m_cValDay		= pMlog->data.bt.eftAccAct.activateDate.day;
	m_cValMon		= pMlog->data.bt.eftAccAct.activateDate.month;
	m_iValYear		= pMlog->data.bt.eftAccAct.activateDate.year;

	if ( m_iValYear != 0 ) 
		sprintf( m_sActivationDate, "%d-%s-%d", m_cValDay, m_sMonths[m_cValMon-1], m_iValYear );
	else
		sprintf( m_sActivationDate, "");

	m_iAcctNum	= pMlog->data.bt.eftAccAct.acctNo;

	AddField( m_iAcctNum, 0 );
	AddField( STORE_TYPE_STRING, m_sActivationDate, 0 );

	return buf;
}