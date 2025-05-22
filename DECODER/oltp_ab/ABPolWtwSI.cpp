// ABPolWtwSI.cpp

#include "LOGDEF_AB.h"
#include "ABPolWtwSI.h"

char * ABPolWtwSI::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;
	
	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);

	/***************** Start to decode *******************/

	m_iRemainBal	= ( unsigned long )pMlog->data.pol.wtw.remBaldu;
	m_iAmount		= ( long )pMlog->data.pol.wtw.wtw.amountd;
	m_iSvcCharge	= ( unsigned long )pMlog->data.pol.wtw.wtw.chargedu;
	m_cWtwType		= pMlog->data.pol.wtw.wtw.typebu;
	m_cActBy		= pMlog->data.pol.wtw.wtw.actBybu;
	m_cSrcWtw		= pMlog->data.pol.wtw.wtw.srcbu;
	m_cCancel		= pMlog->data.pol.wtw.wtw.cancel1;

	m_iFundAva		= ( unsigned long )pMlog->data.pol.wtw.aca.fundd;    // funds available
	m_iBankGd		= ( unsigned long )pMlog->data.pol.wtw.aca.bankgd;   // bank guarentee
	m_iCurrDiv		= ( unsigned long )pMlog->data.pol.wtw.aca.curDivd;  // unsettled dividend
	m_iPrevDiv		= ( unsigned long )pMlog->data.pol.wtw.aca.prvDivd;  // previous dividend
	m_iFbPayFor		= ( unsigned long )pMlog->data.pol.wtw.aca.sbPFtd;   // soccer fo payout forfeited
	
	AddField( m_iRemainBal, 0 );
	AddField( m_iAmount, 0 );
	AddField( m_iSvcCharge, 0 );
	AddField( m_cWtwType, 0 );
	AddField( m_cActBy, 0 );
	AddField( m_cSrcWtw, 0 );
	AddField( m_cCancel, 0 );

	AddField( m_iFundAva, 0 );
	AddField( m_iBankGd, 0 );
	AddField( m_iCurrDiv, 0 );
	AddField( m_iPrevDiv, 0 );
	AddField( m_iFbPayFor, 0 );

	return buf;
}
