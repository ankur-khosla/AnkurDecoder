// ABEftErt.cpp: implementation of the ABEftErt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ABEftErt.h"
#include "LOGDEF_AB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
ABEftErt::ABEftErt()
{

}

ABEftErt::~ABEftErt()
{

}*/
char * ABEftErt::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	int i = 0;


	PackHeader("", pMlog, pMsg);

	/************** Start to decode **************/
	
	m_cNBANo1		= pMlog->data.bt.eftert.nbainfo1.nbatype;
	m_cPinType1		= pMlog->data.bt.eftert.nbainfo1.channeltype;
	m_cNBANo2		= pMlog->data.bt.eftert.nbainfo2.nbatype;
	m_cPinType2		= pMlog->data.bt.eftert.nbainfo2.channeltype;
	m_cEftSubCode	= pMlog->data.bt.eftert.epstb.egw.subCodebu;

	if (m_cNBANo1 >0)
    {
		AddField( m_cNBANo1, 0 );
		AddField( m_cPinType1, 0 );
	}
	else
	{
		AddField( m_cNBANo2, 0 );
		AddField( m_cPinType2, 0 );
	}

		AddField( m_cEftSubCode, 0 );

	return buf;
}