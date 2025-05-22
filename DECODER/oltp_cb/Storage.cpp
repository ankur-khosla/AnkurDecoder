// Storage.cpp: implementation of the Storage class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Storage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
/////////////////////////////////////////////////////////////////////

ColDef::ColDef(long lVal, int iOutput)
{
	char cStr[30];
	sprintf(cStr, "%d", lVal);
	init(STORE_TYPE_INTEGER, cStr, iOutput);
}

ColDef::ColDef(char *cpStr, int iOutput)
{
	init(STORE_TYPE_STRING, cpStr, iOutput);
}

ColDef::ColDef(char cChar, int iOutput)
{
	char cStr[2];
	sprintf(cStr, "%c", cChar);
	init(STORE_TYPE_CHAR, cStr, iOutput);
}

ColDef::ColDef(int iType, char *cpStr, int iOutput)
{
	init(iType, cpStr, iOutput);
}

ColDef::~ColDef()
{
	if(m_pNxt!=NULL)
	{
		delete m_pNxt;
	}
}
void ColDef::init(int iType, char *cpStr, int iOutput)
{
	m_iType = iType;
	sprintf(m_cStr, "%s", cpStr);
	m_iOutput = iOutput;
	m_pNxt=NULL;
}

void ColDef::AddNode(int iType, char *cpStr, int iOutput)
{
	if (m_pNxt==NULL)
	{
		m_pNxt=new ColDef(iType, cpStr, iOutput);
	} else {
		m_pNxt->AddNode(iType, cpStr, iOutput);
	}
}

void ColDef::AddNode(long lVal, int iOutput)
{
	char cStr[30];
	sprintf(cStr, "%d", lVal);
	AddNode(STORE_TYPE_INTEGER, cStr, iOutput);
}

void ColDef::AddNode(char cChar, int iOutput)
{
	char cStr[2];
	sprintf(cStr, "%c", cChar);
	AddNode(STORE_TYPE_CHAR, cStr, iOutput);
}

ColDef * ColDef::GetNxt()
{
	return m_pNxt;
}

ColDef * ColDef::GetNxtPtr(int iIdx)
{
	if((m_pNxt==NULL&&iIdx>0)||iIdx<0)
	{
		return NULL;
	}

	if(iIdx==0)
	{
		return this;
	} else {
		return m_pNxt->GetNxtPtr(iIdx-1);
	}
}

int ColDef::GetType()
{
	return m_iType;
	
}

char * ColDef::GetVal()
{
	return m_cStr;
}

int ColDef::IsOuputCol()
{
	return m_iOutput;
}

RecordDef::RecordDef()
{
	Init();
}

RecordDef::~RecordDef()
{
	if (m_pCol!=NULL)
	{
		delete m_pCol;
	}
}

void RecordDef::AddCol1(int iType, char *cpStr, int iOutput)
{
	if (iType==STORE_TYPE_CHAR)
	{
		if(m_pCol==NULL)
		{
			m_pCol = new ColDef((char)cpStr, iOutput);
		} else {
			m_pCol->AddNode((char)cpStr, iOutput);
		}
		m_iCount++;
	} else {
		if(m_pCol==NULL)
		{
			m_pCol = new ColDef(iType, cpStr, iOutput);
		} else {
			m_pCol->AddNode(iType, cpStr, iOutput);
		}
		m_iCount++;
	}
}

void RecordDef::AddCol1(unsigned long lVal, int iOutput)
{
	char cStr[30];
	unsigned int rVal;
	rVal = lVal;
	if (lVal > 2147483647)
		rVal = 2147483647;	

	sprintf(cStr, "%u", rVal);
	AddCol1(STORE_TYPE_INTEGER, cStr, iOutput);
}

void RecordDef::AddCol164(unsigned __int64 lVal, int iOutput)
{
	char cStr[60];
	//sprintf(cStr, "%u", itoa(lVal,cStr);
	_ui64toa( lVal, cStr, 10 );

	AddCol1(STORE_TYPE_INTEGER, cStr, iOutput);
}

void RecordDef::MoveFirst()
{
	m_pColIdx=m_pCol;
}

void RecordDef::MoveNxt()
{
	m_pColIdx = m_pColIdx->GetNxt();
}

ColDef * RecordDef::GetColDef()
{
	return m_pColIdx;
}

ColDef * RecordDef::GetColPtr(int iIdx)
{
	return m_pCol->GetNxtPtr(iIdx);
}

void RecordDef::AddCol(long lVal, int iDec, int iOutput)
{
	char cStr[20];
	char cTmpl[10];

	__int64 lPlace=1;

	for(int i=0; i<iDec;i++)
	{
		lPlace = lPlace*10;
	}

	__int64 lIntegerPart=(__int64)lVal/lPlace;
	__int64 lDecimalPart=(__int64)lVal%lPlace;

	sprintf(cTmpl, "%%d.%%0%dd", iDec);
	sprintf(cStr, cTmpl, lIntegerPart, lDecimalPart);
	AddCol1(STORE_TYPE_NUMBER, cStr, iOutput);
}

void RecordDef::RedefineCol()
{
	if(m_pCol!=NULL)
	{
		delete m_pCol;
		Init();
	}
}

int	RecordDef::GetDelimitedText( char * buf )
{
	char *sStr;
	strcpy(buf, "");

	if (m_iCount>0)
	{
		MoveFirst();
		MoveNxt();
		for (int i=1; i<m_iCount; i++)
		{
			if ( i > 1 )
				strcat( buf, m_sDelimiter );

			ColDef * cd = GetColDef();
			sStr = cd->GetVal();

			strcat( buf, sStr );
			MoveNxt();
		}
	}
	return m_iCount;
}

void RecordDef::Init()
{
	m_pCol=NULL;
	m_pColIdx=NULL;
	m_iCount=0;
}

int RecordDef::GetColCount()
{
	return m_iCount;
}

void RecordDef::SetDelimiter( char *a_sDelimiter )
{
	strcpy( m_sDelimiter, a_sDelimiter );
}

char RecordDef::m_sDelimiter [] = "";
