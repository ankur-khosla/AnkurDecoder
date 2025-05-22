// ABMeetingAbandon.h: interface for the ABMeetingAbandon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABMEETINGABANDON_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABMEETINGABANDON_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
#include "BDGWCMSGDEF.H"

class ABMeetingAbandon : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);

private:
	char m_sBetType[20];
};

#endif // !defined(AFX_ABMEETINGABANDON_H__EF2A5CE9_83B7_40E4_9807_07252396E0C2__INCLUDED_)
