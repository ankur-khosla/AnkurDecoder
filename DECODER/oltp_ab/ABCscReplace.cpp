// ABCscReplace.cpp

#include "LOGDEF_AB.h"
#include "ABCscReplace.h"

char * ABCscReplace::TranslateAction(const Msg *pMsg)
{
	int iRetVal=NO_TRANSLATE_ERR;

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)pMsg->m_cpBuf;
	
	PackHeader("", pMlog, pMsg);


	/***************** Start to decode *******************/

	m_iOldCscId	= (unsigned __int64) pMlog->data.bt.cscrpl.req.oldcscid;  //Old CSC card id 
	m_iNewCscId	= (unsigned __int64) pMlog->data.bt.cscrpl.req.newcscid;  //New CSC card id

	m_cForfeitDep = pMlog->data.bt.cscrpl.req.fdepfee;  //Forfeit Deposit (0=False, 1=True)
	m_cWaiveDep	= pMlog->data.bt.cscrpl.req.wdepfee;  //Waive Deposit (0=False, 1=True)

	m_iRefAmt = pMlog->data.bt.cscrpl.rpy.refamt;  //Refund Amount
	m_iDepAmt = pMlog->data.bt.cscrpl.rpy.depamt;  //Deposit Amount

	/***************** Output *******************/
	AddField64( m_iOldCscId, 0 );
	AddField64( m_iNewCscId, 0 );
	AddField( m_cForfeitDep, 0 );
	AddField( m_cWaiveDep, 0 );
	AddField64( m_iRefAmt, 0 );
	AddField64( m_iDepAmt, 0 );

	return buf;
}
