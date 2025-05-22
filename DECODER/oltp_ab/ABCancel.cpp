// ABCancel.cpp

#include "LOGDEF_AB.h"
#include "ABCancel.h"

#include <string>
using namespace std;

char * ABCancel::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	const char m_cMonths[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	/************ Start to decode *******************/
	///Q308 changes
	int m_iErrorCode = pMsg->m_iMsgErrwu;//pMlog->hdr.errorwu;


	m_iTranNo = pMlog->data.bt.can.tranwu;
	m_iCanCode = pMlog->data.bt.can.codewu;
	m_cFileNo = pMlog->data.bt.can.filebu;
	m_iBlkNo = pMlog->data.bt.can.blocklu;
	m_cOffUnit = pMlog->data.bt.can.offwu;
	m_cOthUnit = pMlog->data.bt.can.otherUnit1;
	m_cEarCall = pMlog->data.bt.can.canprv1;
	m_cTsnFlag = pMlog->data.bt.can.byTsn1;
	m_cCanPrevDay = pMlog->data.bt.can.canPrevDay;
	
	AddField(m_iTranNo, 0);
	AddField(m_iCanCode, 0);
	AddField(m_cFileNo, 0);
	AddField(m_iBlkNo, 0);
	AddField(m_cOffUnit, 0);
	AddField(m_cOthUnit, 0);
	AddField(m_cEarCall, 0);
	AddField(m_cTsnFlag, 0);

	memset(m_sTranDate, 0, sizeof(m_sTranDate));

	struct tm *m_tdate;
	m_tdate	= _localtime32( &pMlog->data.bt.can.businessDate ); // it should 14145xxxxx, not yyyyMMdd
	sprintf(m_sTranDate, "%d-%s-%d", m_tdate->tm_mday, m_cMonths[m_tdate->tm_mon], 1900+m_tdate->tm_year);

	/*char md[30] = { 0 };

	sprintf_s(md, "%d", pMlog->hdr.bizdatelu);
	if (strlen(md) == 8)
	{
		string mdStr = md;
		sprintf(m_sTranDate, "%s-%s-%s", mdStr.substr(6, 2).c_str(), m_cMonths[atoi(mdStr.substr(4, 2).c_str())-1], mdStr.substr(0, 4).c_str());
	}*/

	// Cancel Lottery
	if ( m_iCanCode == ACU_CODE_LOT || m_iCanCode == ACU_CODE_LOT2 || 
		 m_iCanCode == ACU_CODE_AB_LOT_MD || m_iCanCode == ACU_CODE_ESC_LOT_MD  ) {
		m_iLIndex = pMlog->data.bt.can.data.lot.indexwu;
		m_iLErrSel = pMlog->data.bt.can.data.lot.selwu;
		m_iLOffset = pMlog->data.bt.can.data.lot.offsetlu;
		m_cLSrcSell = pMlog->data.bt.can.data.lot.tran.bet.srcbu;
		m_iLDrawYr = pMlog->data.bt.can.data.lot.tran.bet.d.var.lot.yearwu;
		m_iLDrawNo = pMlog->data.bt.can.data.lot.tran.bet.d.var.lot.drawwu;
		m_iLDrawType = pMlog->data.bt.can.data.lot.tran.bet.d.var.lot.typewu;
		m_iLUnitBet = pMlog->data.bt.can.data.lot.tran.bet.d.hdr.betinvcomb.flexi.baseinv;  //Q308 changes
		m_iLTtlCost = pMlog->data.bt.can.data.lot.tran.bet.d.hdr.costlu;
		m_iLMultiDraw = pMlog->data.bt.can.data.lot.multidraw;

		if ( m_iLDrawYr < 50 )
			m_iLDrawYr = m_iLDrawYr + 2000;
		else
			m_iLDrawYr = m_iLDrawYr + 1900;


		m_cMultiEntriesFlag		= pMlog->data.bt.can.data.lot.tran.bet.d.var.lot.n.multi1;	// multi-entry


		//struct BETLOT *pLOT;
//		pLOT = (struct BETLOT *)((char *)pMlog + sizeof(pMlog->data.bt.can.data.lot.tran.bet.d.var.lot));
		//pLOT = (struct BETLOT *)((char *)pMlog + 125);
		struct BETLOTVAR *pLOTVAR;

		union BETLTON *pLTON;
		pLTON = (union BETLTON *)&pMlog->data.bt.can.data.lot.tran.bet.d.var.lot.n.sel;

		if (m_cMultiEntriesFlag == 0)
		{

		//pLOTVAR = (struct BETLOTVAR *) ((char *) pLOT+2+25);
			//pLOTVAR = (struct BETLOTVAR *) ((char *) pMlog+125+2+25);
			pLOTVAR = (struct BETLOTVAR *) ((char *) pLTON + 25);
			
			if ( m_iLMultiDraw == 1 )
			{
				m_iNoOfDrawSelected = pLOTVAR->md.drselbu;
				m_iNoOfDrawRemain = pLOTVAR->md.drrembu;
			}
			else
			{
				m_iNoOfDrawSelected = 1;
				m_iNoOfDrawRemain = 1;
			}

		}
		else
		{

			m_iNoOfEntries			= pMlog->data.bt.can.data.lot.tran.bet.d.var.lot.n.sel.multi.entbu;	

			
			if (m_iNoOfEntries <=4)
				pLOTVAR = (struct BETLOTVAR *) ((char *) pLTON +1+(4 * 6));
			else 
				pLOTVAR = (struct BETLOTVAR *) ((char *) pLTON +1+(m_iNoOfEntries * 6));

			if ( m_iLMultiDraw == 1 )
			{
				m_iNoOfDrawSelected = pLOTVAR->md.drselbu;
				m_iNoOfDrawRemain = pLOTVAR->md.drrembu;
			}
			else
			{
				m_iNoOfDrawSelected = 1;
				m_iNoOfDrawRemain = 1;
			}
		}
	
	}
	else {
		m_iLIndex = 0;
		m_iLErrSel = 0;
		m_iLOffset = 0;
		m_cLSrcSell = 0;
		m_iLDrawYr = 0;
		m_iLDrawNo = 0;
		m_iLDrawType = 0;
		m_iLUnitBet = 0;
		m_iLTtlCost = 0;
		m_iLMultiDraw = 0;
		m_iNoOfDrawSelected = 0;
		m_iNoOfDrawRemain = 0;
	}

	AddField(m_iLIndex, 0);
	AddField(m_iLErrSel, 0);
	AddField(m_iLOffset, 0);
	AddField(m_cLSrcSell, 0);
	AddField(m_iLDrawYr, 0);
	AddField(m_iLDrawNo, 0);
	AddField(m_iLDrawType, 0);
	AddField(m_iLUnitBet, 0);
	AddField(m_iLTtlCost, 0);

	m_iRMeetIndex = 0; // init to avoid random value
	m_cRErrRaceNo = 0; // init to avoid random value
	m_cRErrSel = 0; // init to avoid random value

	// Cancel Racing
	if ( m_iCanCode == ACU_CODE_RAC || m_iCanCode == ACU_CODE_RAC2 ) {
	
		// Q308 changes
		if (m_iErrorCode == 0 )
		{
			m_iROffset		= pMlog->data.bt.can.data.rac.betinfo.raceinfo.offsetlu;	//2011IBT Changes
		}
		else 
		{		
			m_iRMeetIndex	= pMlog->data.bt.can.data.rac.indexwu;
			m_cRErrRaceNo	= pMlog->data.bt.can.data.rac.betinfo.errorinfo.racebu;
			m_cRErrSel		= pMlog->data.bt.can.data.rac.betinfo.errorinfo.selbu;
		}
		
		m_cRSrcSell		= pMlog->data.bt.can.data.rac.tran.bet.srcbu;


		struct tm *m_date;

		char m_cBetType = pMlog->data.bt.can.data.rac.tran.bet.d.hdr.bettypebu;

		sprintf(m_sRMeetDate, "%s", "01-Jan-1900");
		char md[30] = { 0 };

		if (m_cBetType == BETTYP_AUP)
		{
			sprintf_s(md, "%d", pMlog->data.bt.can.data.rac.tran.bet.d.var.a.md);

			//m_date = _localtime32(&pMlog->data.bt.can.data.rac.tran.bet.d.var.a.md); // meeting date
			m_cRLoc = pMlog->data.bt.rac.tran.bet.d.var.a.loc; // location
			m_cRDay = pMlog->data.bt.rac.tran.bet.d.var.a.day; // day

		}
		else // BETEXOSTD
		{
			sprintf_s(md, "%d", pMlog->data.bt.can.data.rac.tran.bet.d.var.es.md);
			//m_date = _localtime32(&pMlog->data.bt.can.data.rac.tran.bet.d.var.es.md); // meeting date
			m_cRLoc = pMlog->data.bt.can.data.rac.tran.bet.d.var.es.loc;
			m_cRDay = pMlog->data.bt.can.data.rac.tran.bet.d.var.es.day;
		}

		if (strlen(md) == 8)
		{
			string mdStr = md;
			string yy = mdStr.substr(0, 4);
			string mm = mdStr.substr(4, 2);
			string dd = mdStr.substr(6, 2);
			mdStr = yy + "-" + mm + "-" + dd + " 00:00:00";
			strcpy_s(m_sRMeetDate,mdStr.c_str());
		}

		/*if (m_date)
			sprintf(m_sRMeetDate, "%d-%s-%d", m_date->tm_mday, m_cMonths[m_date->tm_mon], 1900 + m_date->tm_year);
		else
			sprintf(m_sRMeetDate, "%s", "01-Jan-1900");*/
		
		/*m_cRLoc		= pMlog->data.bt.can.data.rac.tran.bet.locbu;
		m_cRDay		= pMlog->data.bt.can.data.rac.tran.bet.daybu;*/
		m_cRType	= pMlog->data.bt.can.data.rac.tran.bet.d.hdr.bettypebu;
		m_iRUnitBet = pMlog->data.bt.can.data.rac.tran.bet.d.hdr.betinvcomb.flexi.baseinv;  //q308 ; non-flexbet, actual baseinv; flexbet, no of combinations
		m_iRTtlCost = pMlog->data.bt.can.data.rac.tran.bet.d.hdr.costlu;
	}
	else {
		memset(m_sRMeetDate,0, sizeof(m_sRMeetDate));
		m_iRMeetIndex	= 0;
		m_cRErrRaceNo	= 0;
		m_cRErrSel		= 0;
		m_iROffset		= 0;
		m_cRSrcSell		= 0;
		m_cRLoc		= 0;
		m_cRDay		= 0;
		m_cRType	= 0;
		m_iRUnitBet = 0;
		m_iRTtlCost = 0;
	}

	AddField(m_iRMeetIndex, 0);
	AddField(m_cRErrRaceNo, 0);
	AddField(m_cRErrSel, 0);
	AddField(m_iROffset, 0);
	AddField(m_cRSrcSell, 0);
	AddField(STORE_TYPE_STRING, m_sRMeetDate, 0);
	AddField(m_cRLoc, 0);
	AddField(m_cRDay, 0);
	AddField(m_cRType, 0);
	AddField(m_iRUnitBet, 0);
	AddField(m_iRTtlCost, 0);

	// Cancel Withdrawl
	if ( m_iCanCode == ACU_CODE_WTW ) {
		m_iWAmount		= pMlog->data.bt.can.data.wtw.tran.amountd;
		m_iWSvcCharge	= pMlog->data.bt.can.data.wtw.tran.chargedu;
		m_iWType		= pMlog->data.bt.can.data.wtw.tran.typebu;
		m_cWActBy		= pMlog->data.bt.can.data.wtw.tran.actBybu;
		m_cWSrcType		= pMlog->data.bt.can.data.wtw.tran.srcbu;
		m_cWCanFlag		= pMlog->data.bt.can.data.wtw.tran.cancel1;		
	}
	else {
		m_iWAmount		= 0;
		m_iWSvcCharge	= 0;
		m_iWType		= 0;
		m_cWActBy		= 0;
		m_cWSrcType		= 0;
		m_cWCanFlag		= 0;
	}

	AddField64(m_iWAmount, 0);
	AddField64(m_iWSvcCharge, 0);
	AddField(m_iWType, 0);
	AddField(m_cWActBy, 0);
	AddField(m_cWSrcType, 0);
	AddField(m_cWCanFlag, 0);

	// Cancel SB
	if ( m_iCanCode == ACU_CODE_SB || m_iCanCode == ACU_CODE_SB2 ) {
		m_iSSrcSell = pMlog->data.bt.can.data.sb.bet.tran.srcbu;
		m_iSUnitBet = pMlog->data.bt.can.data.sb.bet.tran.bet.hdr.betinvcomb.flexi.baseinv; //q308, changes
		m_iSTtlCost = pMlog->data.bt.can.data.sb.bet.tran.bet.hdr.costlu;

		tm* s_time;
		s_time = _localtime32( &pMlog->data.bt.can.data.sb.bet.tran.bet.hdr.sellTime );

		if( s_time )
			sprintf(m_sSSelltime, "%d-%s-%d", s_time->tm_mday, m_cMonths[s_time->tm_mon], 1900+s_time->tm_year);
		else
			sprintf(m_sSSelltime, "%s", "01-Jan-1900");

		m_cSBetType = pMlog->data.bt.can.data.sb.bet.tran.bet.hdr.bettypebu;
	}
	else {
		m_iSSrcSell = 0;
		m_iSUnitBet = 0;
		m_iSTtlCost = 0;
		m_cSBetType = 0;
		memset( m_sSSelltime, 0, sizeof( m_sSSelltime ) );
	}

	AddField(m_iSSrcSell, 0);
	AddField(m_iSUnitBet, 0);
	AddField(m_iSTtlCost, 0);
	AddField(STORE_TYPE_STRING, m_sSSelltime, 0);
	AddField(m_cSBetType, 0);


	// Cancel Deposit
	if ( m_iCanCode == ACU_CODE_DEP || m_iCanCode == ACU_CODE_DEP_TSN2 ) {
		tm* h_time;
		h_time = _localtime32( &pMlog->data.bt.can.data.dep.tran.holdtime );
		sprintf(m_sDHoldTime, "%d-%s-%d", h_time->tm_mday, m_cMonths[h_time->tm_mon], 1900+h_time->tm_year);

		m_iDAmount			= pMlog->data.bt.can.data.dep.tran.amountdu;
		m_iDSvcCharge		= pMlog->data.bt.can.data.dep.tran.chargedu;
		m_cDType			= pMlog->data.bt.can.data.dep.tran.typebu;
		m_iDWithHoldFlag	= pMlog->data.bt.can.data.dep.tran.hold1;
		m_iDCancelFlag		= pMlog->data.bt.can.data.dep.tran.cancel1;
		m_iDRevFlag			= pMlog->data.bt.can.data.dep.tran.reversed1;
		m_cDSrcDep			= pMlog->data.bt.can.data.dep.tran.srcbu;
	}
	else {
		memset( m_sDHoldTime, 0, sizeof( m_sDHoldTime ) );
		m_iDAmount			= 0;
		m_iDSvcCharge		= 0;
		m_cDType			= 0;
		m_iDWithHoldFlag	= 0;
		m_iDCancelFlag		= 0;
		m_iDRevFlag			= 0;
		m_cDSrcDep			= 0;
	}

	//struct tm *m_tdate;
	//m_tdate = _localtime32(&pMlog->data.bt.can.businessDate);
	//sprintf(m_sTranDate, "%d-%s-%d", m_tdate->tm_mday, m_cMonths[m_tdate->tm_mon], 1900 + m_tdate->tm_year);

	AddField(STORE_TYPE_STRING, m_sDHoldTime, 0);
	AddField64(m_iDAmount, 0);
	AddField64(m_iDSvcCharge, 0);
	AddField(m_cDType, 0);
	AddField(m_iDWithHoldFlag, 0);
	AddField(m_iDCancelFlag, 0);
	AddField(m_iDRevFlag, 0);
	AddField(m_cDSrcDep, 0);

	AddField(m_iLMultiDraw, 0);
	AddField(m_iNoOfDrawSelected, 0);
	AddField(m_iNoOfDrawRemain, 0);
	AddField(m_cCanPrevDay, 0);
	AddField(STORE_TYPE_STRING, m_sTranDate, 0);


	return buf;
}