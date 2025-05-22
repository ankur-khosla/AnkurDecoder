/////////////////////////////////////////////////////////////
// CBSBSelBitmap.h: interface for the CBSBSelBitmap class.
/////////////////////////////////////////////////////////////

#if !defined(AFX_CBSBSelBitmap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_CBSBSelBitmap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "LOGDEF.h"



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


class CBSBSelBitmap  
{
public:
	char* OESBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* TOSBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* HADBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* OOUBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* HDCBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel);
	char* HaFuBitmap(unsigned short m_cSel, char m_sSel[20]);
	char* CHPBitmap(unsigned long m_iSel, char* m_cSel);

protected:
	void GetCOS(unsigned int full, char**& COSSel, unsigned short& total_sel);
	void GetHaFu(unsigned short m_iSel, char m_sHafu[10][10], unsigned short& total_sel);
	char* Dec2Binary(unsigned int decimal, char* BArray, int len);
	char* CalScore(int position, char* score);
	char* CalHaFu(int position, char* res);
	void GetCHPP(unsigned char m_iCHPSel, int* SelArr, int len, int numSel);
};

#endif // !defined(AFX_CBSBSelBitmap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
