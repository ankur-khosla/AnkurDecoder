/////////////////////////////////////////////////////////////////////
//
// CBEftFund.cpp: implementation of the CBEftFund class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBEftFund.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBEftFund::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	/*
	if((iRetVal=TranslateHeader(pMsg))!=NO_TRANSLATE_ERR)
	{
		return iRetVal;
	}
	*/

	struct LOG *pMlog;
	pMlog						= (struct LOG *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);
	EftHeader(pMlog, pMsg);

	union TSN tsn = pMlog->d.eft.body.eps.data.cvi.tsn;

	m_iNewTsnFlag = tsnVersionwu(&tsn);		// new tsn flag; sp3: function--tsnVersionwu	pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19n.w4.tsnver2;
	m_iSaleSysNo = tsnSystemNumbu(tsn); // sale system no
	m_iTsnBetType = tsnBetTypebu(tsn); // bet type

	if ( m_iNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_iHighRecNo		= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocRacTicket		= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo			= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.reclwu;		// low order bits of record no
		m_iDayOfYear		= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_iHighRecNo = tsnBetTypebu(tsn); // bet type

		m_iLocRacTicket = 0;
		m_iDayOfYear = 0;

		m_iLowRecNo			= tsn19NTicketIDdu(tsn);		// low order bits of record no
	}

	m_iFileNo		= pMlog->d.eft.body.eps.data.cvi.filewu;			// file no
	m_iAmount		= pMlog->d.eft.body.eps.data.cvi.amtlu;				// amount in cents
	memset(m_sPan, 0, 20);
//	memcpy(m_sPan, pMlog->d.eft.body.eps.data.cvi.pans, 19);			// pans

	char m_sAmount[30];
	sprintf(m_sAmount, "%u", m_iAmount);

	AddField(m_iHighRecNo, 0);
	AddField64(m_iLowRecNo, 0);
	AddField(m_iLocRacTicket, 0);
	AddField(m_iTsnBetType, 0);
	AddField(m_iSaleSysNo, 0);
	// oltp output new_tsn_flag=0,tsn_bet_type=8, BIS and EDW is using this logic.
	// in PMU1 version, EDABI converts new_tsn_flag=1 to new_tsn_flag=0 during output.
	// if the new_tsn_flag has any update in future, BIS and EDW shoud be aligned with it,
	// downstream should exclude this logic in the next release. ---changed on 11/02/2017
	if (m_iNewTsnFlag == 1)
		AddField(0, 0);
	else
		AddField(m_iNewTsnFlag, 0);
	AddField(m_iDayOfYear, 0);

	AddField(m_iFileNo, 0);
	AddField(STORE_TYPE_STRING, m_sAmount, 0);
	AddField(STORE_TYPE_STRING, m_sPan, 0);

	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
