// JCLogger.cpp: implementation of the JCLogger class.
//
//////////////////////////////////////////////////////////////////////

#include <string.h>
#include "JCLogger.h"
#include "LOGDEF.H"
#include "LOGDEF_AB.H"

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Msg::Msg(int iBufSize)
{
	m_iBufSize=iBufSize;
	if (m_iBufSize <= 0)
	{
		m_iBufSize=MSG_SIZE;
	}
	m_cpBuf=new unsigned char[m_iBufSize];
	m_iMsgErr=NO_ERR;
}

Msg::~Msg()
{
	if (m_cpBuf!=NULL)
		delete [] m_cpBuf;
}

long Msg::BtoL(const unsigned char *cp, int iSize, char HighByteFirst, char Signed) const 
{
	unsigned long Num=0;

	if((cp!=NULL)&&(iSize <=4)&&(iSize>=1))
	{
		if(HighByteFirst)
		{
			for(int i=0;i<iSize;i++)
			{
				Num=Num*256+cp[i];
			}
		} else {
			for(int i=iSize-1;i>=0;i--)
			{
				Num=Num*256+cp[i];
			}
		}

		if((Signed) && (iSize<4) && (iSize>0))
		{
			if(iSize==1)
			{
				if(Num & 0x00000080)
				{
					Num += 0xffffff00;
				}
			} else if (iSize==2) {
				if(Num & 0x00008000)
				{
					Num += 0xffff0000;
				}
			} else if (iSize==3) {
				if(Num & 0x0080000)
				{
					Num += 0xff000000;
				}
			}
		}
	}

	return Num;
}

int Msg::BtoAscHex(unsigned char *cpSrc, int iSize, char *cpDest, int iLen) const
{


	if ((iLen < (iSize*2+1)) || (cpDest == NULL) || (iSize <=0) || (cpSrc == NULL))
	{
		return 1;
	}

	int j=0;
	for(int i=0;i<iSize;i++, j+=2)
	{
		sprintf(&cpDest[j], "%02X", cpSrc[i]);
	}
	cpDest[iSize*2]=NULL;
	return NO_ERR;
}

long Msg::AscHextoLong(unsigned char *cp, int iSize) const
{
	long lVal=0;
	if (cp!=NULL&&iSize>0)
	{
		for(int i=0;(i<iSize&&*cp!=NULL);i++, cp++)
		{
			if(*cp>='A'&&*cp<='F')
			{
				lVal=(lVal*16)+((*cp-'A')+10);
			} else if(*cp>='a'&&*cp<='f') {
				lVal=(lVal*16)+((*cp-'a')+10);
			} else if(*cp>='0'&&*cp<='9') {
				lVal=(lVal*16)+(*cp-'0');
			} else {
				lVal=0;
				break;
			}
		}
	}
	return lVal;
}

char Msg::IsLeapYr(int Year) const
{
	if(!(Year%400))
	{ // This year is a Leap Year
		return 1;
	} else if(!(Year%100)) { // This year is not a Leap Year
		return 0;
	} else if(!(Year%4)) { // This year is a Leap Year
		return 1;
	} else { // This year is not a Leap Year
		return 0;
	}
}

char* Msg::DayToDate(int Year, int Day, char Date[]) const
{
	int iDD;
	int iMM;
	int iYY;

	const char cMonth[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	int iCalDay [12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	iYY=Year;
	if(IsLeapYr(iYY))
	{
		iCalDay[1]=29;
	} else {
		iCalDay[1]=28;
	}

	iDD=Day;
	for(iMM=0;iMM<12;iMM++)
	{
		if((Day-=iCalDay[iMM])>0)
		{
			iDD=Day;
		} else {
			iMM++;
			break;
		}                
	}
	sprintf(Date, "%02d-%s-%04d", iDD, cMonth[iMM], iYY);
	return (Date);
}

long Msg::DateToDay(unsigned long Date) const
{
	int iDD;
	int iMM;
	int iYY;

	int iCalDay [12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(!(iYY=Date/10000)) return 0;
	if(IsLeapYr(iYY))
	{
		iCalDay[1]=29;
	} else {
		iCalDay[1]=28;
	}

	iMM=(Date%10000)/100;
	if(iMM<1||iMM>12) return 0;
	iDD=(Date%10000)%100;
	for(int i=0;i<iMM-1;i++)
	{
		iDD+=iCalDay[i];
	}
	return (iDD);

}

void Msg::TrnxDateTime(int iSeconds, char *cpDateTime) const
{
	int iLogYear=m_iMsgYear;
	int iLogMonth=m_iMsgMonth;
	int iLogDay=m_iMsgDay;

	int iHour=iSeconds/3600;
	int iMin=(iSeconds%3600)/60;
	int iSec=(iSeconds%3600)%60;

	int iMonthDaysMap[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const char cMonth[13][4]={"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	if(IsLeapYr(iLogYear))
	{
		iMonthDaysMap[2]=29;
	}

	while(iHour>23)
	{
		iHour=iHour-24;
		iLogDay++;
	}

	if(iLogDay>iMonthDaysMap[iLogMonth])
	{
		iLogDay=iLogDay-iMonthDaysMap[iLogMonth];
		iLogMonth++;
	}

	if(iLogMonth>12)
	{
		iLogMonth=iLogMonth-12;
		iLogYear++;
	}
	sprintf(cpDateTime, "%04d-%s-%02d %02d:%02d:%02d", iLogYear, cMonth[iLogMonth], iLogDay, iHour, iMin, iSec);
}

void Msg::TranslateDate(int iNumber, char *OutputDate) const
{

	int Year;
	int Month;
	int Day;
	int Temp1, Temp2, Temp3;
	char* aMonth;

	if(iNumber > 0){
	Temp1 = iNumber;
	Temp1 = Temp1 >> 9;
	Year = Temp1;

	Temp2 = iNumber;
	Temp2 = Temp2 << 7;
	Temp2 = Temp2 >> 12;
	Temp2 = Temp2 & 15;
	Month = Temp2;

	Temp3 = iNumber;
	Temp3 = Temp3 << 11;
	Temp3 = Temp3 >> 11;
	Temp3 = Temp3 & 31;
	Day = Temp3;

//	if(Year>=20)
//	{ // Temporary fixing the year 2000 problem
		Year = Year + 1900;
//	} else {
//		Year = Year + 2000;
//	}

	switch(Temp2)
	{
		case 1:
			aMonth = "Jan";
			break;

		case 2:
			aMonth = "Feb";
			break;
		case 3:
			aMonth = "Mar";
			break;

		case 4:
			aMonth = "Apr";
			break;

		case 5:
			aMonth = "May";
			break;

		case 6:
			aMonth = "Jun";
			break;

		case 7:
			aMonth = "Jul";
			break;

		case 8:
			aMonth = "Aug";
			break;

		case 9:
			aMonth = "Sep";
			break;

		case 10:
			aMonth = "Oct";
			break;

		case 11:
			aMonth = "Nov";
			break;

		case 12:
			aMonth = "Dec";
			break;

		default:
			break;

	}
	}
	else{
		Year = 1900;
		aMonth = "Jan";
		Day = 1;
	}

	sprintf(OutputDate, "%04d-%s-%02d", Year, aMonth, Day);
}





int Msg::RestoreBitmap(const unsigned char *cpSrc, int iUnitLen, int iSize, unsigned char *cpDes) const
{
	if ((cpSrc==NULL)||((iSize%iUnitLen)!=0)||(cpDes==NULL))
	{
		return 0;
	}

	int iIdx=0;
	const unsigned char *cp;
	while(iIdx<iSize)
	{
		cp = &cpSrc[iIdx+iUnitLen-1];
		int iDesIdx=0;
		while(cp >= &cpSrc[iIdx])
		{
			cpDes[iIdx+iDesIdx]=*cp;
			iDesIdx++;
			cp--;
		}
		iIdx += iUnitLen;
	}

	return 1;
}

CtrlBlk::CtrlBlk()
{
	m_sBusiness_date[0] = 0;
	m_iSysNo=-1;
	*m_cpSysName=NULL;
	m_iDay = 0;
	m_iMonth = 0;
	m_iYear = 0;
}

CtrlBlk::~CtrlBlk()
{
}

int JCLogger::m_iMsgLenUnitinByte	= 1;

JCLogger::JCLogger()
{
	m_pMsg = NULL;
	m_pCtrlBlk = NULL;
	m_iLogStatus=END_OF_LOGGER;
}

JCLogger::~JCLogger()
{
	FreeMsg();
}

void JCLogger::SetMsgSize(int iMsgSize)
{
	FreeMsg();
	m_pMsg = new Msg(iMsgSize);
}

void JCLogger::FreeMsg()
{
	if (m_pMsg!=NULL)
	{
		delete m_pMsg;
		m_pMsg=NULL;
	}
}

const Msg * JCLogger::GetMsgObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, int exLen)
{
	short msgSize = 0;

	memcpy(&msgSize, binArr + (PAYLOAD_HDR_SIZE + exLen),2);//get message size: first 2 bytes of one whole message --LOGAB.hdr.sizew
	memcpy(m_pMsg->m_cpBuf,binArr+(PAYLOAD_HDR_SIZE +exLen), msgSize); //copy from the specified index: payload header size (27) + extra data length.

	struct LOGAB *pMlog;
	pMlog = (struct LOGAB *)m_pMsg->m_cpBuf;


	m_pMsg->m_iSysNo = pHdr->system_id;
	sprintf(m_pMsg->SellingDate, "%d", pHdr->business_date);

	m_pMsg->m_iMsgSize = pMlog->hdr.sizew;
	m_pMsg->m_iMsgCode = pMlog->hdr.codewu;

	struct tm *B_day;
 	B_day = _localtime32(&pMlog->hdr.timelu);

	unsigned int iDay		= B_day->tm_mday;
	unsigned int iMonth		= B_day->tm_mon+1;
	unsigned int iYr		= B_day->tm_year+1900;

	m_pMsg->m_iMsgMonth = iMonth;
	m_pMsg->m_iMsgDay	= iDay;
	m_pMsg->m_iMsgYear	= iYr;

	return m_pMsg;
}

int Msg::GetCustSession(int CustSession)
{
	CustSession = m_iCustSession;
	m_iCustSession ++;
	return CustSession;
}
