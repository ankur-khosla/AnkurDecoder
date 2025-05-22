/////////////////////////////////////////////////////////////////////
//
// CBEftCV.cpp: implementation of the CBEftCV class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBEftCV.h"
#include <stdlib.h>

#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBEftCV::TranslateAction(const Msg *pMsg)
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

	m_cNewTsnFlag = tsnVersionwu(&tsn);		// new tsn flag; sp3: function--tsnVersionwu	pMlog->d.bt.rac.raceinfo.tsninfo.tsn.s19n.w4.tsnver2;
	m_iSaleSys = tsnSystemNumbu(tsn); // sale system no
	m_iType = tsnBetTypebu(tsn); // bet type

	if ( m_cNewTsnFlag == TSN_OLTP) // new 19 digit tsn
	{
		m_cHighRecNo			= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.w2.rech12;		// high order bits of record no
		m_iLocat				= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.w1.loc3;		// location
		m_iLowRecNo				= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.reclwu;		// low order bits of record no
		m_iMeetingDayOfYear		= pMlog->d.eft.body.eps.data.cvi.tsn.s19t.w4.day9;		// meeting day of year
	}
	else
	{
		m_cHighRecNo = tsnBetTypebu(tsn); // bet type

		short msgCode = pMlog->hdr.codewu;		// message code
		m_iLocat = 0; // set to 0.2017.1.2
		m_iMeetDay = 0;
		m_iMeetingDayOfYear = 0;

		m_iLowRecNo				= tsn19NTicketIDdu(tsn);		// low order bits of record no
	}

	m_iFileNo			= pMlog->d.eft.body.eps.data.cvi.filewu;			// file no
	m_iAmount		= pMlog->d.eft.body.eps.data.cvi.amtlu;					// amount in cents
	char m_sAmount[30];
	sprintf(m_sAmount, "%u", m_iAmount);
	sprintf(m_sPan, "%s", pMlog->d.eft.body.eps.data.cvi.pans);					// pan
	char temp[2];
	sprintf(temp, "%c", pMlog->d.eft.body.eps.data.cvi.cv.d.methodbu);			// method
//	m_cIssueFlag = pMlog->d.eft.body.eps.data.cvi.cv.d.methodbu;
	int IssueFlag = atoi(temp);
	m_iCVSell		= pMlog->d.eft.body.eps.data.cvi.cv.cbh.ptr.cv.selllogseqlu;	// log seq at selling
	m_iCVPay		= pMlog->d.eft.body.eps.data.cvi.cv.cbh.ptr.cv.paylogseqlu;		// log seq at payout

	// <Marco Lui, 20050120>
	m_iOriginalEftAmount	= pMlog->d.eft.body.eps.data.cvi.cv.cbh.prveft.eft.originallu;
	m_iRemainingEftAmount	= pMlog->d.eft.body.eps.data.cvi.cv.cbh.prveft.eft.remainlu;
	// </Marco Lui, 20050120>

	//m_iMeetingDayOfYear = 0; // just for test. 2016.12.30

	AddField(m_cHighRecNo,0);
	AddField64(m_iLowRecNo,0);
	AddField(m_iLocat,0);
	AddField(m_iType,0);
	AddField(m_iSaleSys,0);
	// oltp output new_tsn_flag=0,tsn_bet_type=8, BIS and EDW is using this logic.
	// in PMU1 version, EDABI converts new_tsn_flag=1 to new_tsn_flag=0 during output.
	// if the new_tsn_flag has any update in future, BIS and EDW shoud be aligned with it,
	// downstream should exclude this logic in the next release. ---changed on 11/02/2017
	if (m_cNewTsnFlag == 1)
		AddField(0, 0);
	else
		AddField(m_cNewTsnFlag, 0);
	AddField(m_iMeetingDayOfYear,0);
	AddField(m_iFileNo, 0);
	AddField(STORE_TYPE_STRING, m_sAmount, 0);
	AddField(IssueFlag, 0);		// IssueFlag
	AddField(m_iCVSell, 0);
	AddField(m_iCVPay, 0);
	// <Marco Lui, 20050120>
	AddField(m_iOriginalEftAmount, 0);
	AddField(m_iRemainingEftAmount, 0);
	// </Marco Lui, 20050120>

	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
