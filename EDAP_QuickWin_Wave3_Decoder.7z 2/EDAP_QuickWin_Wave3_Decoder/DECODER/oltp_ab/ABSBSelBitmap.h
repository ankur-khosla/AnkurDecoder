/////////////////////////////////////////////////////////////
// ABSBSelBitmap.h: interface for the ABSBSelBitmap class.
/////////////////////////////////////////////////////////////

#if !defined(AFX_ABSBSelBitmap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_ABSBSelBitmap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ABMsgTranslator.h"
//#include "LOGDEF.h"



#define OES_EVEN	1
#define OES_ODD		2

#define TOS_0		1
#define TOS_1		2
#define TOS_2		4
#define TOS_3		8
#define TOS_4		16
#define TOS_5		32
#define TOS_6		64
#define TOS_OTHERS	128

#define HAD_HOME		1
#define HAD_AWAY		2
#define HAD_DRAW		4

#define HDC_HOME		1
#define HDC_AWAY		2
#define HDC_DRAW		4

#define OOU_OVER		1
#define OOU_UNDER		2

#define HAFU_HH		1
#define HAFU_HD		2	
#define HAFU_HA		4
#define HAFU_DH		8
#define HAFU_DD		16
#define HAFU_DA		32
#define HAFU_AH		64
#define HAFU_AD		128
#define HAFU_AA		256


class ABSBSelBitmap : public ABMsgTranslator 
{
public:
	char* OESBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* TOSBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* HADBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* OOUBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* HDCBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* HaFuBitmap(unsigned short m_cSel, char m_sSel[20]);

protected:
	void GetCOS(unsigned int full, char**& COSSel, unsigned short& total_sel);
	void GetHaFu(unsigned short m_iSel, char m_sHafu[10][10], unsigned short& total_sel);
	char* Dec2Binary(unsigned int decimal, char* BArray, int size);
	char* CalScore(int position, char* score);
	char* CalHaFu(int position, char* res);
	char* Dec2Binary2(__int64 decimal, char* BArray);
	void GetDHCP(unsigned __int64 half, unsigned __int64 full, char**& HFCombination, unsigned char &cField, int& total_sel);
	char* CalScore1(int position, char* score);

};

#endif // !defined(AFX_ABSBSelBitmap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
