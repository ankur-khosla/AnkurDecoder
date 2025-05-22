// CBSBBetDetail.h: interface for the CBSBBetDetail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBSBBetDetail_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBSBBetDetail_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CBMsgTranslator.h"
#include <string.h>
#include "LOGDEF.h"
#include <stdlib.h>
#include <stdio.h>


class CBSBBetDetail : public CBMsgTranslator
{
public:

	char* GetType (int m_iBetType, char m_sBetType[20]);
	char* GetFormula (int m_iFormula, char m_sFormula[10]);
//	int GetPoolTypeNo(int PoolNoInput);
	int GetTotalSel();
	

protected:
	void GetHCS(unsigned int half, unsigned int full, char**& HFCombination, int& total_sel);
	void GetDHCP(unsigned __int64 half, unsigned __int64 full, char**& HFCombination, unsigned char &cField, int& total_sel);
	char* Dec2Binary(unsigned int decimal, char* BArray);
	char* Dec2Binary2(__int64 decimal, char* BArray);
	char* CalScore(int position, char* score);
	char* CalScore1(int position, char* score);
	void SetTotalSel(int ttlCom);

	int ttlSel;
};

#endif // !defined(AFX_CBSBBetDetail_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
