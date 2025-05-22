//	*****************************************************************
//	*																*
//	*  Aim : This class is to format bet details for SB Bet			*
//	*																*	
//	*****************************************************************

#include "CBSBBetDetail.h"
#include "math.h"

typedef char* STR;
char* CBSBBetDetail::GetType(int m_iBetType, char m_sBetType[20])
{
	switch(m_iBetType)
	{
	case 19:
		sprintf(m_sBetType, "SB_PM");
		break;

	case 20:
		sprintf(m_sBetType, "SB_FO");
		break;

	case 21:
		sprintf(m_sBetType, "SB_EXO");
		break;

	case 22:
		sprintf(m_sBetType, "SB_AUP_PM");
		break;

	case 23:
		sprintf(m_sBetType, "SB_AUP_FO_CTL");
		break;

	case 24:
		sprintf(m_sBetType, "SB_AUP_FO_NON");
		break;

	case 25:
		sprintf(m_sBetType, "SB_SEC_BET");
		break;

	default:
		sprintf(m_sBetType, "NOT_SB");
		break;
	}
	
	return (m_sBetType);
}

char* CBSBBetDetail::GetFormula(int m_iFormula, char m_sFormula[10])
{
	switch (m_iFormula)
	{
	case 0:
		sprintf(m_sFormula, "2x1");
		break;

	case 1:
		sprintf(m_sFormula, "2x3");
		break;

	case 2:
		sprintf(m_sFormula, "3x1");
		break;

	case 3:
		sprintf(m_sFormula, "3x3");
		break;

	case 4:
		sprintf(m_sFormula, "3x4");
		break;

	case 5:
		sprintf(m_sFormula, "3x6");
		break;

	case 6:
		sprintf(m_sFormula, "3x7");
		break;

	case 7:
		sprintf(m_sFormula, "4x1");
		break;

	case 8:
		sprintf(m_sFormula, "4x4");
		break;

	case 9:
		sprintf(m_sFormula, "4x5");
		break;

	case 10:
		sprintf(m_sFormula, "4x6");
		break;

	case 11:
		sprintf(m_sFormula, "4x10");
		break;

	case 12:
		sprintf(m_sFormula, "4x11");
		break;

	case 13:
		sprintf(m_sFormula, "4x14");
		break;

	case 14:
		sprintf(m_sFormula, "4x15");
		break;

	case 15:
		sprintf(m_sFormula, "5x1");
		break;

	case 16:
		sprintf(m_sFormula, "5x5");
		break;

	case 17:
		sprintf(m_sFormula, "5x6");
		break;

	case 18:
		sprintf(m_sFormula, "5x10");
		break;

	case 19:
		sprintf(m_sFormula, "5x15");
		break;

	case 20:
		sprintf(m_sFormula, "5x16");
		break;

	case 21:
		sprintf(m_sFormula, "5x20");
		break;

	case 22:
		sprintf(m_sFormula, "5x25");
		break;

	case 23:
		sprintf(m_sFormula, "5x26");
		break;

	case 24:
		sprintf(m_sFormula, "5x30");
		break;

	case 25:
		sprintf(m_sFormula, "5x31");
		break;

	case 26:
		sprintf(m_sFormula, "6x1");
		break;

	case 27:
		sprintf(m_sFormula, "6x6");
		break;

	case 28:
		sprintf(m_sFormula, "6x7");
		break;

	case 29:
		sprintf(m_sFormula, "6x15");
		break;

	case 30:
		sprintf(m_sFormula, "6x20");
		break;

	case 31:
		sprintf(m_sFormula, "6x21");
		break;

	case 32:
		sprintf(m_sFormula, "6x22");
		break;

	case 33:
		sprintf(m_sFormula, "6x35");
		break;

	case 34:
		sprintf(m_sFormula, "6x41");
		break;

	case 35:
		sprintf(m_sFormula, "6x42");
		break;

	case 36:
		sprintf(m_sFormula, "6x50");
		break;

	case 37:
		sprintf(m_sFormula, "6x56");
		break;

	case 38:
		sprintf(m_sFormula, "6x57");
		break;

	case 39:
		sprintf(m_sFormula, "6x62");
		break;

	case 40:
		sprintf(m_sFormula, "6x63");
		break;

	case 41:
		sprintf(m_sFormula, "7x1");
		break;

	case 42:
		sprintf(m_sFormula, "7x7");
		break;

	case 43:
		sprintf(m_sFormula, "7x8");
		break;

	case 44:
		sprintf(m_sFormula, "7x21");
		break;

	case 45:
		sprintf(m_sFormula, "7x28");
		break;

	case 46:
		sprintf(m_sFormula, "7x29");
		break;

	case 47:
		sprintf(m_sFormula, "7x35");
		break;

	case 48:
		sprintf(m_sFormula, "7x56");
		break;

	case 49:
		sprintf(m_sFormula, "7x63");
		break;

	case 50:
		sprintf(m_sFormula, "7x64");
		break;

	case 51:
		sprintf(m_sFormula, "7x70");
		break;

	case 52:
		sprintf(m_sFormula, "7x91");
		break;

	case 53:
		sprintf(m_sFormula, "7x98");
		break;

	case 54:
		sprintf(m_sFormula, "7x99");
		break;

	case 55:
		sprintf(m_sFormula, "7x112");
		break;

	case 56:
		sprintf(m_sFormula, "7x119");
		break;

	case 57:
		sprintf(m_sFormula, "7x120");
		break;

	case 58:
		sprintf(m_sFormula, "7x126");
		break;

	case 59:
		sprintf(m_sFormula, "7x127");
		break;

	case 60:
		sprintf(m_sFormula, "8x1");
		break;

	case 61:
		sprintf(m_sFormula, "8x8");
		break;

	case 62:
		sprintf(m_sFormula, "8x9");
		break;

	case 63:
		sprintf(m_sFormula, "8x28");
		break;

	case 64:
		sprintf(m_sFormula, "8x56");
		break;

	case 65:
		sprintf(m_sFormula, "8x70");
		break;

	case 66:
		sprintf(m_sFormula, "8x247");
		break;

	case 67:
		sprintf(m_sFormula, "8x255");
		break;

	default:
		sprintf(m_sFormula, "Err");
		break;

	}
	return(m_sFormula);
}

void CBSBBetDetail::GetHCS(unsigned int half, unsigned int full, char**& HFCombination, int& total_sel)
{
	char halfArray[32];
	char fullArray[32];
	char HScoreArray[32][10];
	char FScoreArray[32][10];
	char m_sHScore[20];
	char m_sFScore[20];
	int i=0, j=0, k=0, halfLen=0, fullLen=0, len=0, pos=0, y=0;
	char tmpScore[10];
	HFCombination = new STR[400];
	bool isField = false;
	sprintf(HScoreArray[i], "%s", "");
	sprintf(FScoreArray[i], "%s", "");
	
	// find the set-bit position(s) of Half-Time
	Dec2Binary(half, halfArray);

	for(i=0; i<32; i++)
	{
		
		if(halfArray[0] == '1')
			isField = true;

		if(isField)
		{
			for(y=0; y<28; y++)
			{
				pos = y;
				CalScore(pos, m_sHScore);
				sprintf(HScoreArray[j], "%s", m_sHScore);
				j++;
			}
			break;
		}
		else
		{
			if(halfArray[i] == '1')
			{
				pos = 31-i;
				CalScore(pos, m_sHScore);
				sprintf(HScoreArray[j], "%s", m_sHScore);
				j++;
			}
		}	
	}

	if(isField)
		halfLen = 28;
	else
		halfLen = j;

	// find the set-bit position(s) of Full-Time
	isField = false;
	j=0;
	y=0;

	Dec2Binary(full, fullArray);

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
				sprintf(FScoreArray[j], "%s", m_sFScore);
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
				sprintf(FScoreArray[j], "%s", m_sFScore);
				j++;
			}
		}
	}

	if(isField)
		fullLen = 28;
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


char* CBSBBetDetail::Dec2Binary(unsigned int decimal, char* BArray) {
	
	int i, y;
	unsigned int x;
	char z[2];

	sprintf(BArray, "%s", "");
	memset(z,0,sizeof(z));
	for (i=31;i>=0;i--) {
		x = (unsigned int) pow(2.0,i);
		y = ((decimal & x) == x) ? 1: 0;
		sprintf(z, "%u", y);
		strcat(BArray, z) ;
	}

	BArray[32] = '\0';

	return BArray;
}


void CBSBBetDetail::GetDHCP(unsigned __int64 half, unsigned __int64 full, char**& HFCombination, unsigned char &cField, int& total_sel)
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

char* CBSBBetDetail::Dec2Binary2(__int64 decimal, char* BArray) {
	
	int i, y;
	unsigned __int64 x;
	char z[2];

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

/*
char* CBSBBetDetail::Dec2Binary(unsigned int decimal, char* BArray)
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

	int diff = 32-len;

	for(i=0; i<diff; i++)
		strcat(BArray, "0");

	for(j=i; j<32; j++)
		BArray[j] = tmpArray[31-j];

	BArray[32] = '\0';

	return BArray;
}
*/

char* CBSBBetDetail::CalScore(int position, char* score)
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

char* CBSBBetDetail::CalScore1(int position, char* score)
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


int CBSBBetDetail::GetTotalSel()
{
	return ttlSel;
}

void CBSBBetDetail::SetTotalSel(int ttlCom)
{
	ttlSel = ttlCom;
}


