// ABCscReturn.cpp

#include "LOGDEF_AB.h"
#include "ABCscReturn.h"

char * ABCscReturn::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

	m_cWithdrawType	= pMlog->data.bt.cscret.wdtype;  //Withdraw type (1=Autopay, 2=Cheque, 4=Cash)
	
	m_iCscId = (unsigned __int64) pMlog->data.bt.cscret.req.cscid;  //CSC card id 

	m_cForfeitDep = pMlog->data.bt.cscret.req.fordep;  //Forfeit Deposit (0=False, 1=True)

	m_iAcctBal = pMlog->data.bt.cscret.req.accbal;  //Account Balance (in cents)
	m_iRefAmt = pMlog->data.bt.cscret.rpy.refamt;  //Refund Amount (in cents)

	/***************** Output *******************/
	AddField(m_cWithdrawType, 0 );
	AddField64(m_iCscId, 0 );
	AddField(m_cForfeitDep, 0 );
	AddField64(m_iAcctBal, 0 );
	AddField64(m_iRefAmt, 0 );

	return buf;
}
