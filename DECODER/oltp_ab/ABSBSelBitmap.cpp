#include "ABSBSelBitmap.h"
#include <math.h>

typedef char* STR;

char* ABSBSelBitmap::OESBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
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

char* ABSBSelBitmap::TOSBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
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

char* ABSBSelBitmap::HADBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
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

char* ABSBSelBitmap::OOUBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
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

char* ABSBSelBitmap::HDCBitmap(unsigned char m_cSel, char m_sSel[10], int& ttlSel)
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

void ABSBSelBitmap::GetHaFu(unsigned short m_iSel, char m_sHafu[10][10], unsigned short& total_sel)
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
		// m_sHafu[j] = strdup("V-V");
		sprintf( m_sHafu[j], "%s", "V-V");
	}

}

char* ABSBSelBitmap::CalHaFu(int position, char* res)
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

void ABSBSelBitmap::GetCOS(unsigned int full, char**& COSSel, unsigned short& total_sel)
{
	char fullArray[32];
	char m_sFScore[20];
	int i=0, j=0, k=0, fullLen=0, len=0, pos=0, y=0;
	COSSel = new STR[400];
	bool isField = false;

	// find the set-bit position(s) of Full-Time

	Dec2Binary(full, fullArray, 32);

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


char* ABSBSelBitmap::Dec2Binary(unsigned int decimal, char* BArray, int size)
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

char* ABSBSelBitmap::CalScore(int position, char* score)
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


void ABSBSelBitmap::GetDHCP(unsigned __int64 half, unsigned __int64 full, char**& HFCombination, unsigned char &cField, int& total_sel)
{
	char halfArray[42];
	char fullArray[42];
	char HScoreArray[42][40];
	char FScoreArray[42][40];
	char m_sHScore[20];
	char m_sFScore[20];
	int i=0, j=0, k=0, halfLen=0, fullLen=0, len=0, pos=0, y=0;
	char tmpScore[10];
	HFCombination = new STR[400];
	bool isField = false;
	sprintf(HScoreArray[i], "%s", "");
	sprintf(FScoreArray[i], "%s", "");
	
	// find the set-bit position(s) of Half-Time
	memset( halfArray, 0, sizeof(halfArray ));
	Dec2Binary2(half, halfArray);

	if(halfArray[39] == '1')
		isField = true;

	for(i=38; i>=0; i--)
	{
		
		if(halfArray[i] == '1')
		{
			pos = 39-i;
			CalScore1(pos, m_sHScore);
			sprintf(HScoreArray[j], "%s", m_sHScore);
			j++;
		}
	}

	if(isField)
		halfLen = 31;
	else
		halfLen = j;

	// find the set-bit position(s) of Full-Time
	isField = false;
	j=0;
	y=0;

	memset( halfArray, 0, sizeof(halfArray ));
	Dec2Binary2(full, fullArray);

	if(fullArray[39] == '1')
		isField = true;	

	for(i=38; i>=0; i--)
	{
		if(fullArray[i] == '1')
		{
			pos = 39-i;
			CalScore1(pos, m_sFScore);
			sprintf(FScoreArray[j], "%s", m_sFScore);
			j++;
		}
	}

	if(isField)
		fullLen = 31;
	else 
		fullLen = j;


char* pHdest;
char* pFdest;
int resultH, resultF;
int ihalfhome, ifullhome, ihalfaway, ifullaway;
bool printflag1 = false;
bool printflag2 = false;
char cHalfhome, cHalfaway, cFullhome, cFullaway;
char tHalfhome[3];
char tHalfaway[3];
char tFullhome[3];
char tFullaway[3];

	for(i=0; i<halfLen; i++)
	{
		for(j=0; j<fullLen; j++)
		{
			printflag1 = false;
			printflag2 = false;

			pHdest = strchr( HScoreArray[i], ':' );
		    resultH = pHdest - HScoreArray[i];

			pFdest = strchr( FScoreArray[j], ':' );
		    resultF = pFdest - FScoreArray[j];

			if(resultH == 1)
			{
				cHalfhome = HScoreArray[i][0];				
				sprintf(tHalfhome, "%c", cHalfhome);
				ihalfhome = atoi(tHalfhome);

				cHalfaway = HScoreArray[i][strlen(HScoreArray[i])-1];
				sprintf(tHalfaway, "%c", cHalfaway);
				ihalfaway = atoi(tHalfaway);
			}
			else
			{
				printflag1 = true;
			}

			if(resultF == 1)
			{
				cFullhome = FScoreArray[j][0];				
				sprintf(tFullhome, "%c", cFullhome);
				ifullhome = atoi(tFullhome);

				cFullaway = FScoreArray[j][strlen(FScoreArray[j])-1];
				sprintf(tFullaway, "%c", cFullaway);
				ifullaway = atoi(tFullaway);
			}
			else
			{
				printflag1 = true;
			}
			
			if(!printflag1)
			{
				if((ihalfhome <= ifullhome) && (ihalfaway <= ifullaway))
					printflag2 = true;
			}

			if(resultH > 1 && resultF == 1)
				printflag1 = false;

			if(printflag1 || printflag2)
			{
				sprintf(tmpScore, "%s/%s", HScoreArray[i], FScoreArray[j]);
				HFCombination[k] = strdup(tmpScore);
				k++;
				if(k == 70)
					k=70;
			}
		}
	}

	total_sel = k;
	
}

char* ABSBSelBitmap::Dec2Binary2(__int64 decimal, char* BArray) {
	
	int i, y;
	unsigned __int64 x;
	char z[2]; // Include end character '\0'

	sprintf(BArray, "%s", "");
	memset(z,0,sizeof(z));
	for (i=39;i>=0;i--) {
		x = (unsigned __int64) pow(2.0,i);
		y = ((decimal & x) == x) ? 1: 0;
		sprintf(z, "%u", y);
		strcat(BArray, z) ;
	}

	BArray[40] = '\0';

	return BArray;
}

char* ABSBSelBitmap::CalScore1(int position, char* score)
{
	int away_score=0;

	sprintf(score, "%s", "");

	if(position >= 1 && position <=6)
	{
		away_score = position - 1;
		sprintf(score, "0:%d", away_score);
	}
	else if(position >= 7 && position <=12)
	{
		away_score = position - 7;
		sprintf(score, "1:%d", away_score);
	}
	else if(position >= 13 && position <=18)
	{
		away_score = position - 13;
		sprintf(score, "2:%d", away_score);
	}
	else if(position >= 19 && position <=24)
	{
		away_score = position - 19;
		sprintf(score, "3:%d", away_score);
	}
	else if(position >= 25 && position <=30)
	{
		away_score = position - 25;
		sprintf(score, "4:%d", away_score);
	}
	else if(position >= 31 && position <=36)
	{
		away_score = position - 31;
		sprintf(score, "5:%d", away_score);
	}
	else if(position == 37) // home other
	{
		sprintf(score, "%s", "255:0");
	}
	else if(position == 38) // away other
	{
		sprintf(score, "%s", "255:1");
	}
	else if(position == 39) // draw other
	{	
		sprintf(score, "%s", "255:2");
	}
	else if(position == 40)
	{
		sprintf(score, "%s", "F");
	}

		return score;
}

