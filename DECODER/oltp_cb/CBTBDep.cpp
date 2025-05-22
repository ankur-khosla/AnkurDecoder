/////////////////////////////////////////////////////////////////////
//
// CBTBDep.cpp: implementation of the CBTBDep class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBTBDep.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

char * CBTBDep::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOG *pMlog;
	pMlog						= (struct LOG *)pMsg->m_cpBuf;

	PackHeader("", pMlog, pMsg);

	// all the below tsn info are set to 0 (because only the obsolete struct TSN_A was used here before)
	m_iHighRecNo		= 0;	// high order bits of record no
	m_iLowRecNo			= 0;	// low order bits of record no
	m_iLocation			= 0;		// location
	m_iTsnBetType		= 0;	// tsn bet type
	m_iCentreHighBit	= 0;	// centre/eft high order bits
	m_iCentreLowBit		= 0;	// centre/eft low order bits
	m_iWindow			= 0;		// window [eft=0]
	m_iSaleSysNo		= 0;			// sale system no
	m_cNewTsnFlag		= 0;			// new tsn flag
	m_iMeetingDayOfYear	= 0;		// meeting day of year [racing] draw no [lottery] or transaction day

	m_iDepSysNo			= pMlog->d.bt.tbd.data.sysw;			// system no
	m_iDepChanNo		= pMlog->d.bt.tbd.data.chanwu;			// channel no
	m_iInterMsn			= pMlog->d.bt.tbd.data.ismsnlu;			// inter system msn
	m_iTranNo			= pMlog->d.bt.tbd.data.trnwu;			// transaction no
	m_iAmount			= pMlog->d.bt.tbd.data.amtlu;			// amount
	sprintf(m_sCustName, "%s", pMlog->d.bt.tbd.data.names);		// customer name

	// Output
	AddField(m_iHighRecNo, 0);
	AddField(m_iLowRecNo, 0);
	AddField(m_iLocation, 0);
	AddField(m_iTsnBetType, 0);
	AddField(m_iSaleSysNo, 0);
	AddField(m_cNewTsnFlag, 0);
	AddField(m_iMeetingDayOfYear, 0);
	AddField(m_iDepSysNo, 0);
	AddField(m_iDepChanNo, 0);
	AddField(m_iInterMsn, 0);
	AddField(m_iTranNo, 0);
	AddField(m_iAmount, 0);
	AddField(STORE_TYPE_STRING, m_sCustName, 0);

	
	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
