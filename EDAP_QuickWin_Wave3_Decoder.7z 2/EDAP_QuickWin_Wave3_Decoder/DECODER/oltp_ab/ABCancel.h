// ABCancel.h

#if !defined(AFX_ABCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABCANCEL_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
//#include "acudef.h"

class ABCancel : public ABMsgTranslator  
{
public:
	virtual char * TranslateAction(const Msg *pMsg);
	ABCancel() {};
	virtual ~ABCancel() {};

private:
	unsigned short m_iTranNo;
	unsigned short m_iCanCode;
	unsigned char m_cFileNo;
	unsigned int m_iBlkNo;
	unsigned short m_cOffUnit;
	unsigned int m_cOthUnit;
	unsigned int m_cEarCall;
	unsigned int m_cTsnFlag;
	unsigned int m_cCanPrevDay;

	//**** Cancel type ****//

	// Lottery
	unsigned short m_iLIndex;
	unsigned short m_iLErrSel;
	unsigned int m_iLOffset;
	unsigned char m_cLSrcSell;
	unsigned int m_iLDrawYr;
	unsigned int m_iLDrawNo;
	unsigned int m_iLDrawType;
	unsigned int m_iLUnitBet;
	unsigned int m_iLTtlCost;
	unsigned int m_iLMultiDraw;
	unsigned int m_iNoOfDrawSelected;
	unsigned int m_iNoOfDrawRemain;

	// cancel racing bet
	unsigned short m_iRMeetIndex;
	unsigned char m_cRErrRaceNo;
	unsigned char m_cRErrSel;
	unsigned char m_iROffset;
	unsigned char m_cRSrcSell;
	unsigned long m_iRUnitBet;
	unsigned int m_iRTtlCost;
	char m_cRLoc;
	char m_cRDay;
	char m_cRType;
	char m_sRMeetDate[30];
	char m_sTranDate[30];
	
	// cancel withdrawal
	__int64 m_iWAmount;
	unsigned __int64 m_iWSvcCharge;
	unsigned char m_iWType;
	unsigned char m_cWActBy;
	unsigned char m_cWSrcType;
	unsigned char m_cWCanFlag;
	

	// cancel SB
	unsigned char m_iSSrcSell;
	unsigned long m_iSUnitBet;
	unsigned int m_iSTtlCost;
	char m_sSSelltime[30];
	unsigned char m_cSBetType;

	// cancel deposit
	char m_sDHoldTime[30];
	unsigned __int64 m_iDAmount;
	unsigned __int64 m_iDSvcCharge;
	unsigned char m_cDType;
	unsigned int m_iDWithHoldFlag;
	unsigned int m_iDCancelFlag;
	unsigned int m_iDRevFlag;
	unsigned char m_cDSrcDep;

	short	m_iNoOfEntries;
	char	m_cMultiEntriesFlag;

};

#endif // !defined(AFX_ABWITHDRAW_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
