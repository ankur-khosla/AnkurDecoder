// Terminal.cpp: implementation of the Terminal class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include "Terminal.h"

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Terminal::Terminal()
{

}

Terminal::~Terminal()
{

}

void Terminal::init()
{

}

const int CBTerminal::m_iSttTerm=32;
const int CBTerminal::m_iSvtTerm=34;

CBTerminal::CBTerminal()
{
	init();
}

CBTerminal::~CBTerminal()
{

}

void CBTerminal::init()
{
	m_cPhyTermNo[0]=NULL;
	m_iCentreNo=0;
	m_iWndNo=0;
	m_iTermType=0;
	m_iBatch_Seq=0;
	int i;
	for (i=0; i<10000; i++)
	{
		CustSec[i]=0;
	}
}
