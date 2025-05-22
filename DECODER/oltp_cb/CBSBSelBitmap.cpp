#include "CBSBSelBitmap.h"


typedef char* STR;

char* CBSBSelBitmap::OESBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
{
	sprintf(m_sSel, "%s", "");
	ttlSel = 0;

	if(m_cSel & OES_EVEN)
	{
		strcat(m_sSel, "0");
		ttlSel++;
	}
	if(m_cSel & OES_ODD)
	{
		strcat(m_sSel, "1");
		ttlSel++;
	}

	return m_sSel;
}

char* CBSBSelBitmap::TOSBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
{
	sprintf(m_sSel, "%s", "");
	ttlSel = 0;

	if(m_cSel & TOS_0)
	{
		strcat(m_sSel, "0");
		ttlSel++;
	}
	if(m_cSel & TOS_1)
	{
		strcat(m_sSel, "1");
		ttlSel++;
	}
	if(m_cSel & TOS_2)
	{
		strcat(m_sSel, "2");
		ttlSel++;
	}
	if(m_cSel & TOS_3)
	{
		strcat(m_sSel, "3");
		ttlSel++;
	}
	if(m_cSel & TOS_4)
	{
		strcat(m_sSel, "4");
		ttlSel++;
	}
	if(m_cSel & TOS_5)
	{
		strcat(m_sSel, "5");
		ttlSel++;
	}
	if(m_cSel & TOS_6)
	{
		strcat(m_sSel, "6");
		ttlSel++;
	}
	if(m_cSel & TOS_OTHERS)
	{
		strcat(m_sSel, "255");
		ttlSel++;
	}

	return m_sSel;
}

char* CBSBSelBitmap::HADBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
{
	sprintf(m_sSel, "%s", "");
	ttlSel = 0;

	if(m_cSel & HAD_HOME)
	{
		strcat(m_sSel, "0");
		ttlSel++;
	}
	if(m_cSel & HAD_AWAY)
	{
		strcat(m_sSel, "1");
		ttlSel++;
	}
	if(m_cSel & HAD_DRAW)
	{
		strcat(m_sSel, "2");
		ttlSel++;
	}

	return m_sSel;
}

char* CBSBSelBitmap::OOUBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
{
	sprintf(m_sSel, "%s", "");
	ttlSel = 0;

	if(m_cSel & OOU_OVER)
	{
		sprintf(m_sSel, "0");
		ttlSel++;
	}
	if(m_cSel & OOU_UNDER)
	{
		sprintf(m_sSel, "1");
		ttlSel++;
	}
	
	return m_sSel;
}

char* CBSBSelBitmap::HDCBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
{
	sprintf(m_sSel, "%s", "");
	ttlSel = 0;

	if(m_cSel & HDC_HOME)
	{
		sprintf(m_sSel, "0");
		ttlSel++;
	}
	if(m_cSel & HDC_AWAY)
	{
		sprintf(m_sSel, "1");
		ttlSel++;
	}
	if(m_cSel & HDC_DRAW)
	{
		sprintf(m_sSel, "2");
		ttlSel++;
	}

	return m_sSel;
}

void CBSBSelBitmap::GetHaFu(unsigned short m_iSel, char m_sHafu[10][10], unsigned short& total_sel)
{
	char bitArray[20];
	char m_sHafuRes[20];
	int i=0, j=0, pos=0;
	// m_sHafu = new STR[10];
	bool isField = false;
	int bitLen = 16;

	// find the set-bit position(s) of Full-Time

	Dec2Binary(m_iSel, bitArray, bitLen);

	for(i=15; i>=7; i--)
	{		
		if(bitArray[i] == '1')
		{
			pos = 15-i;
			CalHaFu(pos, m_sHafuRes);
			// m_sHafu[j] = strdup(m_sHafuRes);
			sprintf( m_sHafu[j], "%s", m_sHafuRes);
			j++;
		}
	}

	if(isField)
		total_sel = 9;
	else 
		total_sel = j;

	if ( total_sel == 0 ) {
		total_sel = 1;
//		m_sHafu[j] = strdup("V-V");
		sprintf( m_sHafu[j], "%s", "V-V");
	}

}

char* CBSBSelBitmap::CalHaFu(int position, char* res)
{
	int full_res=0;

	sprintf(res, "%s", "");

	if(position >= 0 && position <=2)
	{
		full_res = position;
		sprintf(res, "0-%d", full_res);
	}
	else if(position >= 3 && position <=5)
	{
		full_res = position - 3;
		sprintf(res, "1-%d", full_res);
	}
	else if(position >= 6 && position <=8)
	{
		full_res = position - 6;
		sprintf(res, "2-%d", full_res);
	}

	return res;
}

void CBSBSelBitmap::GetCOS(unsigned int full, char**& COSSel, unsigned short& total_sel)
{
	char fullArray[32];
	char m_sFScore[20];
	int i=0, j=0, k=0, fullLen=0, len=0, pos=0, y=0, bitlen=32;
	COSSel = new STR[400];
	bool isField = false;

	// find the set-bit position(s) of Full-Time

	Dec2Binary(full, fullArray, bitlen);

	for(i=0; i<32; i++)
	{
		if(fullArray[0] == '1')
			isField = true;	

		if(isField)
		{
			for(y=0; y<28; y++)
			{
				pos = y;
				CalScore(pos, m_sFScore);
				COSSel[j] = strdup(m_sFScore);
				j++;
			}
			break;
		}
		else
		{
			if(fullArray[i] == '1')
			{
				pos = 31-i;
				CalScore(pos, m_sFScore);
				COSSel[j] = strdup(m_sFScore);
				j++;
			}
		}
	}

	if(isField)
		total_sel = 28;
	else 
		total_sel = j;

}

char* CBSBSelBitmap::Dec2Binary(unsigned int decimal, char* BArray, int len) 
{
	
	int i, y;
	unsigned int x;
	char z[2]; // Include end character '\0'

	sprintf(BArray, "%s", "");
	memset(z,0,sizeof(z));
	for (i=len-1;i>=0;i--) {
		x = (unsigned int) pow(2.0,i);
		y = ((decimal & x) == x) ? 1: 0;
		sprintf(z, "%u", y);
		strcat(BArray, z) ;
	}

	BArray[len] = '\0';

	return BArray;
}


/*
char* CBSBSelBitmap::Dec2Binary(unsigned int decimal, char* BArray, int size)
{
	unsigned int remainder = 0;
	unsigned int dividend = 0;
	int len = 0, i = 0, j = 0;
	char tmpArray[128];
	char sRemainder[2];

	sprintf(tmpArray, "%s", "");
	sprintf(BArray, "%s", "");

	dividend = decimal;

	while (dividend > 1)
	{
		remainder = dividend%2;
		dividend = dividend/2;
		_itoa(remainder, sRemainder, 10);
		strcat(tmpArray, sRemainder);
	}
	_itoa(dividend, sRemainder, 10);
	strcat(tmpArray, sRemainder);

	len = strlen(tmpArray);

	sprintf(BArray, "%s", "");

	int diff = size-len;

	for(i=0; i<diff; i++)
		strcat(BArray, "0");

	for(j=i; j<size; j++)
		BArray[j] = tmpArray[size-j-1];

	BArray[size] = '\0';

	return BArray;
}
*/

char* CBSBSelBitmap::CalScore(int position, char* score)
{
	int away_score=0;

	sprintf(score, "%s", "");

	if(position >= 0 && position <=4)
	{
		away_score = position - 0;
		sprintf(score, "0:%d", away_score);
	}
	else if(position >= 5 && position <=9)
	{
		away_score = position - 5;
		sprintf(score, "1:%d", away_score);
	}
	else if(position >= 10 && position <=14)
	{
		away_score = position - 10;
		sprintf(score, "2:%d", away_score);
	}
	else if(position >= 15 && position <=19)
	{
		away_score = position - 15;
		sprintf(score, "3:%d", away_score);
	}
	else if(position >= 20 && position <=24)
	{
		away_score = position - 20;
		sprintf(score, "4:%d", away_score);
	}
	else if(position == 25) // home other
	{
		sprintf(score, "%s", "255:0");
	}
	else if(position == 26) // away other
	{
		sprintf(score, "%s", "255:1");
	}
	else if(position == 27) // draw other
	{	
		sprintf(score, "%s", "255:2");
	}
	else if(position == 31)
	{
		sprintf(score, "%s", "F");
	}

		return score;
}

void CBSBSelBitmap::GetCHPP(unsigned char m_iCHPSel, int* SelArr, int len, int numSel)
{
	int bitLen=0, i=0, j=0;
	unsigned long x=0;

	bitLen=len;
	memset(SelArr, 0, bitLen);

	// if i is set, i+1 team is selected.
	// if 0 bit is set, field selection.
	for (i=bitLen-1;i>=0;i--) {
		x = (unsigned long) pow(2.0,i);
		if((m_iCHPSel & x) == x)
		{
			SelArr[j] = i+1;
			j++;
		}
	}
	numSel=j;
}

char* CBSBSelBitmap::CHPBitmap(unsigned long m_iSel, char* m_cSel)
{
	return m_cSel;
}