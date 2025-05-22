// CBSignOn.cpp: implementation of the CBRecallLastTran class.
//
/////////////////////////////////////////////////////////////////////

#include "LOGDEF.h"
#include "CBSignOn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



char * CBSignOn::TranslateAction(const Msg *pMsg)
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
	
	PackHeader("cb_sign_on_insert_sp", pMlog, pMsg);

//	m_iInterMsn			= pMlog->d.bt.sgn.othsys.ismsnlu;	// inter-system msn
//	m_iInterMsn = 0;
	m_cDisBcsFlag		= pMlog->d.bt.sgn.othsys.disable1;	// disable bcs flag
	m_iPassword			= pMlog->d.bt.sgn.pwdlu;			// password
	m_iSuperNo			= pMlog->d.bt.sgn.sstflu;			// supervisor no
	m_iSuperPassword	= pMlog->d.bt.sgn.spwdlu;			// supervisor password
	m_iAutLevelBitmap	= pMlog->d.bt.sgn.authlevellu;		// authority level bitmap
	if (m_iAutLevelBitmap == -1)
		m_iAutLevelBitmap = 0; // reset to 0, otherwise DB (tinyint) will report an error
	m_iCentreNo			= pMlog->d.bt.sgn.ctron1;			// centre no
	m_cHighCV			= pMlog->d.bt.sgn.highcv1;			// high cv terminal
	m_cKeyCan			= pMlog->d.bt.sgn.keycan1;			// keypad cancel terminal
	m_cDisPay			= pMlog->d.bt.sgn.dsbpay1;			// disable payout
	m_cHOTerm			= pMlog->d.bt.sgn.hoterm1;			// h. o. terminal
	m_cOnCoTerm			= pMlog->d.bt.sgn.onc1;				// on course terminal


	// L51_R0_BenKoo_3
	// modified by Ben Koo (2 Apr 2004)
	// support new betting terminal function
	m_cToteFlag			= pMlog->d.bt.sgn.xtote1;			// x tote branch flag 
	m_cDisableLottery	= pMlog->d.bt.sgn.dsblot1;			// disable lottery
	m_cDisableSB		= pMlog->d.bt.sgn.dsbsb1;			// disable sb
	m_cDisableCV		= pMlog->d.bt.sgn.dsbcv1;			// disable cv
	m_cDisableRace		= pMlog->d.bt.sgn.dsbrace1;			// disable racing
	m_cDisableDep		= pMlog->d.bt.sgn.dsbtb1;			// disable tb deposit 

	m_cShroffSignOn		= pMlog->d.bt.sgn.cntbu;			// no of times shroff sign on
	char	m_sMonths[13][4]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	struct tm *tm_TermDate;
	__time32_t terDat = pMlog->d.bt.sgn.dat;
	if (terDat == 0)
	{
		terDat = pMsg->m_iMsgTime;
		tm_TermDate = _localtime32(&terDat);			// terminal date
		sprintf(m_sTermDate, "%02d-%s-%d %02d:%02d:%02d", tm_TermDate->tm_mday, m_sMonths[tm_TermDate->tm_mon], tm_TermDate->tm_year+1900, tm_TermDate->tm_hour, tm_TermDate->tm_min, tm_TermDate->tm_sec);
	}
	else
	{
		tm_TermDate = _localtime32(&terDat);			// terminal date
		sprintf(m_sTermDate, "%02d-%s-%d %02d:%02d:%02d", tm_TermDate->tm_mday, m_sMonths[tm_TermDate->tm_mon], tm_TermDate->tm_year, tm_TermDate->tm_hour, tm_TermDate->tm_min, tm_TermDate->tm_sec);
	}

	m_cRam				= pMlog->d.bt.sgn.btv.ramb;			// BT ROM version no.
	m_cRom				= pMlog->d.bt.sgn.btv.romb;			// BT RAM version no.
	m_cPrinter			= pMlog->d.bt.sgn.btv.printerb;		// BT Printer version no.
	m_cTermFlag			= pMlog->d.bt.sgn.flagbu;			// terminal flag [1=svt]		

	// Output
//	AddField(m_iInterMsn, 0);
	AddField(m_cDisBcsFlag, 0);
	AddField(m_iPassword, 0);
	AddField(m_iSuperNo, 0);
	AddField(m_iSuperPassword, 0);
	AddField(m_iAutLevelBitmap, 0);
	AddField(m_iCentreNo, 0);
	AddField(m_cHighCV, 0);
	AddField(m_cKeyCan, 0);
	AddField(m_cDisPay, 0);
	AddField(m_cHOTerm, 0);
	AddField(m_cOnCoTerm, 0);
	AddField(m_cShroffSignOn, 0);
	AddField(STORE_TYPE_STRING, m_sTermDate, 0);
	AddField(m_cPrinter, 0);
	AddField(m_cRam, 0);
	AddField(m_cRom, 0);
	AddField(m_cTermFlag, 0);

	AddField(m_cToteFlag, 0);
	AddField(m_cDisableLottery, 0);
	AddField(m_cDisableSB, 0);
	AddField(m_cDisableCV, 0);
	AddField(m_cDisableRace, 0);
	AddField(m_cDisableDep, 0);


	/*
	long lRet;
	if(m_pStorage->ExecStoreProc(m_pRcd, lRet)!=STORE_NO_ERR||lRet!=0)
	{
		return SQL_ERR;
	}
	*/
	return buf;
}
