/////////////////////////////////////////////////////////////////////
//
// ExtractMgr.cpp: implementation of the ExtractMgr class.
//
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ExtractMgr.h"
#include "JCLogger.h"
#include "JCSystem.h"
#include "MsgTranslator.h"
#include "TextDB.h"

#include "ABLogger.h"
#include "ABSystem.h"
#include "ABMsgTranslator.h"
#include "ABTextDB.h"
#include "Storage.h"
#include "vector";
#include "eh.h"
#include "typeinfo"
#include "time.h"
#include "commdef.h"
#include <direct.h>
#include <io.h>
#include <sys/timeb.h>

using namespace std;

class	ABLogger;
class	ABSystem;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExtractMgr::ExtractMgr()
{
	pMsg = NULL;
	pMsg = new Msg(BINARY_MAX_SIZE);

	plHdr_Buf = new unsigned char[PAYLOAD_HDR_SIZE];
	plExtData_Buf = new unsigned char[PAYLOAD_EXT_SIZE];
}

ExtractMgr::~ExtractMgr()
{
	if( m_pStoreMgr )
		m_pStoreMgr = 0;
	if( m_pSysMgr )
		m_pSysMgr = 0;
	if( m_pLogMgr )
		m_pLogMgr = 0;

	delete m_pStoreMgr;
	delete m_pSysMgr;
	delete m_pLogMgr;

	if (plHdr_Buf != NULL)
		delete[] plHdr_Buf;
}

//vector<char*> ExtractMgr::v_SimSel;
//vector<char*> v_SimSel;
vector<string> v_SimSel;


void ExtractMgr::SetMsgTranslator(MsgTranslator *a_pMsgTrltr)
{
	m_pMsgTrltr	= a_pMsgTrltr;
}

void ExtractMgr::SetSystem(JCSystem *a_pSysMgr)
{
	m_pSysMgr	= a_pSysMgr;
}

void ExtractMgr::SetLogger(JCLogger *a_pLogMgr)
{
	m_pLogMgr	= a_pLogMgr;
}

void ExtractMgr::SetStorage(Storage *a_pStorage)
{
	m_pStoreMgr	= a_pStorage;
}

char * GetLogFile(char *logPath, const char *logDir)
{
	strcat(logPath, logDir);
	if (access(logPath, 0) == -1)
		mkdir(logPath);

	time_t t = time(NULL);
	tm tm = *localtime(&t);

	char logFile[50];
	sprintf(logFile, "ACP_DECODE_%d-%02d-%02d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	strcat(logPath, logFile);

	return logPath;
}

void GetSystemTime(char *timeStr, int len)
{
	//time_t t = time(NULL);
	//strftime(timeStr, len, "%Y-%m-%d %X ", localtime(&t));
	struct timeb tb;
	ftime(&tb);
	tm tm = *localtime(&tb.time);
	sprintf(timeStr, "Time[%d-%02d-%02d %02d:%02d:%02d,%03d]", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,tm.tm_min,tm.tm_sec,tb.millitm);
}

void AddHeaderField(char *buf, char *tmp, const char m_sDelimiter[])
{
	strcat(buf, tmp);
	strcat(buf, m_sDelimiter);
}

//Note: Add the macros "_USE_32BIT_TIME_T" for 32 bit __time32_t

/*
The function is used to decode binary message from Solace. 2016.7.28 paul
	srMsg: 2D binary array;
	len: length of the array;
	resMsg: store decoded result
*/
char ** ExtractMgr::DecodeABMsgs(unsigned char ** srMsg, int len, int &totalCount, int &errCount, char *logDir, int logLevel)
{
	/*if(logLevel<=1)
		WriteInfoLog(logDir, 1, " --------Decode starts-------- ");*/

	//initial
	JCSystem	*pABSystem = new ABSystem();
	SetSystem(pABSystem);


	unsigned __int64 activityId = 0;
	unsigned int systemId = 0;

	const char hdrDelimiter[] = "@|@";// Delimiter for header fields

	char tmp[30] = { 0 };
	char buf[MSG_SIZE] = { 0 }; 
	const Msg *tmpMsg;
	struct LOGAB *pMlog;
	char *msgStr = NULL;
	struct PAYLOAD_HDR *pHdr;

	char info[512] = { 0 };

	//itoa(len, tmp, 10);

	if (logLevel <= 1)
	{
		//sprintf(tmp, "%d", len);
		sprintf(info, "total messages to be decoded:%d", len);
		WriteInfoLog(logDir, 1, info);
	}

	int smCount = 0; // total simple selections for all messages

	vector<string> v_msg;

	//Decode messages one by one
	for (int i = 0; i < len; i++)
	{
		try
		{
			memset(buf, 0, sizeof(buf));
			memset(pMsg->m_cpBuf, 0, BINARY_MAX_SIZE);
			memcpy(plHdr_Buf, srMsg[i], PAYLOAD_HDR_SIZE);//1.Get payload header: byte size is 35.
			pHdr = (struct PAYLOAD_HDR*)plHdr_Buf;//maped to payload header

			//Add solace payload header: the sixth element is activityCode that is for EDABI.
			sprintf(tmp, "%d", pHdr->system_id);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pHdr->business_date);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%I64u", pHdr->activity_id);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pHdr->enquiry_status);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pHdr->activity_nature);

			AddHeaderField(buf, tmp, hdrDelimiter);

			if (logLevel <= 0)
			{
				sprintf(info, "Payload header:%s", buf);
				WriteInfoLog(logDir, 0, info);
			}

			activityId = pHdr->activity_id;
			systemId = pHdr->system_id;
			
			if (logLevel <= 0)
			{
				sprintf(info, "Message info: system id:%d; activity id:%I64u", pHdr->system_id, activityId);
				WriteInfoLog(logDir, 0, info);// log info for test mode; turn it off when released
			}

			short binSize = 0;
			pMlog = GetLogObj(srMsg[i], pHdr, binSize); // get the whole message

			pMlog->hdr.custSessIdd = pHdr->cust_session_id; // assign cust_session_id from payload header to message header

			// Write ERROR if total size > 8192
			if (binSize + PAYLOAD_HDR_SIZE + pHdr->extra_data_len > BINARY_MAX_SIZE)
			{
				if (logLevel <= 2)
				{
					sprintf(info, "Incorrect length of binary: greater than %d. system id:%d; activity id:%I64u; binary size:%d", BINARY_MAX_SIZE, pHdr->system_id, activityId, binSize + PAYLOAD_HDR_SIZE + pHdr->extra_data_len);
					WriteErrorLog(logDir, info, 2);
				}
			}

			if (pMlog == NULL) // No payload body
			{
				sprintf(tmp, "%d", 3); // 0: success; 1: not implemented; 2: obsoleted; 3: payload body is null; 9: exception
				AddHeaderField(buf, tmp, hdrDelimiter);

				sprintf(tmp, "%d", LOGAB_CODE_ERR);
				AddHeaderField(buf, tmp, hdrDelimiter);

				if (logLevel <= 2)
				{
					sprintf(info, "Incorrect length of binary. system id:%d; activity id:%I64u; binary size:%d; LOGAB_HDR size:%d; LOGAB size: %d", pHdr->system_id, activityId, binSize, sizeof(LOGAB_HDR), sizeof(LOGAB));
					WriteErrorLog(logDir, info, 2);
				}
			}

			else
			{
				tmpMsg = GetMsgObj(srMsg[i], pHdr, pMlog);// 3. Get Msg and extra data

				if (tmpMsg->m_iMsgCode == LOGAB_CODE_SB)
				{
					struct BETSB_SIMPLE *pMSim;
					pMSim = (struct BETSB_SIMPLE *)pMlog->data.bt.sb.bet.tran.bet.var.sb.vbu;

					if (logLevel <= 0)
					{
						sprintf(info, "ACP SB Bet: pool type:%d; match no:%d", pMSim->poolbu, pMSim->matchbu);
						WriteInfoLog(logDir, 0, info);
					}
				}


				if (pMlog->hdr.prelog1 == 0) // 'prelog1 = 1' means the message should be obsoleted
				{
					if (logLevel <= 0)
					{
						sprintf(info, "Start decoding message:system id:%d; activity id:%I64u", pHdr->system_id, activityId);
						WriteInfoLog(logDir, 0, info);// log info for test mode; turn it off when released
					}

					if ((((tmpMsg->m_iMsgCode == LOGAB_CODE_WTW_EFT_EMV && (((struct LOGAB *)tmpMsg->m_cpBuf)->data.bt.wtw.eps.egw.fallback1 == 0))
						|| (tmpMsg->m_iMsgCode == LOGAB_CODE_DEP_EFT_EMV && (((struct LOGAB *)tmpMsg->m_cpBuf)->data.bt.dep.data.eps.egw.fallback1 == 0))
						|| (tmpMsg->m_iMsgCode == LOGAB_CODE_CV_EFT_EMV && (((struct LOGAB *)tmpMsg->m_cpBuf)->data.bt.cvi.eps.fallback1 == 0)))

						&& (pMlog->hdr.blocklu != LOGAB_EFT_EMV_ACK))
						)
						//Unwanted interactive message
					{
						sprintf(tmp, "%d", 6); // 0: success; 1: not implemented; 2: obsoleted; 6:unwanted(EFT_EMV); 9: exception
						AddHeaderField(buf, tmp, hdrDelimiter);

						sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
						AddHeaderField(buf, tmp, hdrDelimiter);

						if (logLevel <= 0)
						{
							sprintf(info, "Skip the message:system id:%d; activity id:%I64u;", pHdr->system_id, activityId);
							WriteInfoLog(logDir, 0, info);
						}
					}
					else
					{

						msgStr = m_pSysMgr->DecMsg(tmpMsg);//4.Decode message and get text message

						if (0 != strcmp(msgStr, (char*)(&NOT_IMPLEMENTED)) && 0 != strcmp(msgStr, (char*)(&NO_STORAGE_DEFINED)))
						{

							sprintf(tmp, "%d", 0); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
							AddHeaderField(buf, tmp, hdrDelimiter);

							strcat_s(buf, msgStr);

							//if (logLevel <= 0)
							//	WriteInfoLog(logDir, 0, "Add result message--normal message in buffer");

						}

						else
						{
							//if (logLevel <= 0)
							//	WriteInfoLog(logDir, 0, "Add result message--not implemented message in buffer");

							sprintf(tmp, "%d", 1); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
							AddHeaderField(buf, tmp, hdrDelimiter);

							sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
							AddHeaderField(buf, tmp, hdrDelimiter);
						}
						
						if (logLevel <= 0)
						{
							sprintf(info, "Finished decoding message:system id:%d; activity id:%I64u", pHdr->system_id, activityId);
							WriteInfoLog(logDir, 0, info);
						}
					}

				}
				else // prelog=1
				{

					if (logLevel <= 0)
					{
						sprintf(info, "Skip the message:system id:%d; activity id:%I64u", pHdr->system_id, activityId);
						WriteInfoLog(logDir, 0, info);
					}

					sprintf(tmp, "%d", 2); // 0: success; 1: not implemented; 2: obsoleted; 3: payload body is null; 9: exception
					AddHeaderField(buf, tmp, hdrDelimiter);

					sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
					AddHeaderField(buf, tmp, hdrDelimiter);

				}
			}		

			if (logLevel <= 0)
				WriteInfoLog(logDir, 0, ("Copy result message:" + string(buf)).c_str());

			v_msg.insert(v_msg.end(),string(buf));

			int simSelSize = v_SimSel.size();//simple selection count
			smCount = smCount + simSelSize;

			
			if (logLevel <= 0)
			{
				sprintf(info, "Total simple selections:%d", simSelSize);
				WriteInfoLog(logDir, 0, info);
			}

			//Add simple selection records in result
			for (int n = 0; n < simSelSize; n++)
			{
				memset(buf,0,sizeof(buf));
				AddSolaceHdr(pHdr, buf, tmp, hdrDelimiter);

				sprintf(tmp, "%d", 0); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
				AddHeaderField(buf, tmp, hdrDelimiter);

				strcat_s(buf, v_SimSel[n].c_str());

				int index = i + (smCount - simSelSize) + n + 1;

				v_msg.insert(v_msg.end(),string(buf));

			}

			if (simSelSize > 0)
			{
				//release the static vector
				v_SimSel.clear();//clear elements
				vector<string>().swap(v_SimSel);//empty capacity; free memeory
			}

		}

		catch (const std::invalid_argument& e)
		{
			sprintf(tmp, "%d", 9); // 0: success; 1: not implemented; 9: exception
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pMlog->hdr.codewu);
			AddHeaderField(buf, tmp, hdrDelimiter);

			v_msg.insert(v_msg.end(), string(buf));

			errCount++;

			if (logLevel <= 2)
			{
				sprintf(info, "Exception occurred:%s %s. system id:%d; activity id:%I64u", e.what(), typeid(e).name(), pHdr->system_id, activityId);
				WriteErrorLog(logDir, info, 2);
			}

			continue;
		}

		catch (exception& e)// grab standard exceptions
		{
			sprintf(tmp, "%d", 9); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pMlog->hdr.codewu);
			AddHeaderField(buf, tmp, hdrDelimiter);

			v_msg.insert(v_msg.end(), string(buf));

			errCount++;

			if (logLevel <= 2)
			{
				sprintf(info, "Exception occurred:%s %s. system id:%d; activity id:%I64u", e.what(), typeid(e).name(), pHdr->system_id, activityId);
				WriteErrorLog(logDir, info, 2);
			}

			continue;
		}
		catch (...)//all other exceptions
		{
			sprintf(tmp, "%d", 9); // 9: exception
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pMlog->hdr.codewu);
			AddHeaderField(buf, tmp, hdrDelimiter);

			v_msg.insert(v_msg.end(), string(buf));

			errCount++;

			if (logLevel <= 2)
			{
				sprintf(info, "Exception occurred:system id:%d; activity id:%I64u", pHdr->system_id, activityId);
				WriteErrorLog(logDir, info, 2);
			}

			continue;
		}

	}

	totalCount = v_msg.size();
	
	char ** retMsg = new char*[totalCount];

	for (int k = 0; k < len + smCount; k++)
	{
		retMsg[k] = new char[MSG_SIZE];
		memset(retMsg[k],0, MSG_SIZE);

		memcpy(retMsg[k], v_msg[k].c_str(),strlen(v_msg[k].c_str()));
	}

	if (totalCount > 0)
	{
		//release the static vector
		v_msg.clear();//clear elements
		vector<string>().swap(v_msg);//empty capacity; free memeory
	}

	if (errCount > 0)
	{
		sprintf(info, "%d messages were not decoded due to exception.", errCount);
		WriteErrorLog(logDir, info, 2);
	}

	delete pABSystem;
	pABSystem = NULL;

	if (logLevel <= 1)
	{
		sprintf(info, "Total result messages:%d(including %d simple selections)", totalCount, smCount);
		WriteInfoLog(logDir, 1, info);
	}

	/*if (logLevel <= 1)
		WriteInfoLog(logDir, 1, " --------Decode ends-------- ");*/

	return retMsg;
	
}

const Msg * ExtractMgr::GetMsgObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, LOGAB *pMlog)
{
	char md[30] = { 0 };

	sprintf_s(md, "%d", pMlog->hdr.bizdatelu);
	if (strlen(md) == 8)
	{
		string mdStr = md;
		pMsg->m_iMsgYear = atoi(mdStr.substr(0, 4).c_str());
		pMsg->m_iMsgMonth = atoi(mdStr.substr(4, 2).c_str());
		pMsg->m_iMsgDay = atoi(mdStr.substr(6, 2).c_str());
	}

	switch (pHdr->system_id)
	{
	case ACP01:
		strcpy(pMsg->m_iSysName, "ACP01");
		break;
	case ACP02:
		strcpy(pMsg->m_iSysName, "ACP02");
		break;
	default:
		strcpy(pMsg->m_iSysName, "Unknown");
		break;
	}

	pMsg->m_iSysNo = pHdr->system_id;
	sprintf(pMsg->SellingDate, "%d", pHdr->business_date);

	pMsg->m_iMsgSize = pMlog->hdr.sizew;
	pMsg->m_iMsgCode = pMlog->hdr.codewu;


	memcpy(plExtData_Buf, (binArr + PAYLOAD_HDR_SIZE), pHdr->extra_data_len);//2.Get payload extra data

	switch (pMsg->m_iMsgCode)
	{
	case LOGAB_CODE_RAC:
	case LOGAB_CODE_LOT:
	case LOGAB_CODE_SB:

		struct EXTDTRLS *extDTRLS;
		extDTRLS = (struct EXTDTRLS*)plExtData_Buf;
		pMsg->m_iMsgErrwu = extDTRLS->extDTAB.extdtcomm.acterrwu;

		pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTRLS->extDTAB.extdtcomm.actts);
		pMsg->txnidd = extDTRLS->extDTAB.txnidd;
		pMsg->m_iMsgSellTime = Convert64TmTo32Tm(extDTRLS->sellTime);
		pMsg->m_MsgBizDate = extDTRLS->bizdatelu;

		sprintf_s(md, "%d", extDTRLS->bizdatelu);
		if (strlen(md) == 8)
		{
			string mdStr = md;
			pMsg->m_iMsgYear = atoi(mdStr.substr(0, 4).c_str());
			pMsg->m_iMsgMonth = atoi(mdStr.substr(4, 2).c_str());
			pMsg->m_iMsgDay = atoi(mdStr.substr(6, 2).c_str());
		}

		break;

	case LOGAB_CODE_ACA:
	case LOGAB_CODE_ACR:
	case LOGAB_CODE_WTW:
	case LOGAB_CODE_DEP:
	case LOGAB_CODE_CAN:
	case LOGAB_CODE_RCL:
	case LOGAB_CODE_CARD_ISSUE:
	case LOGAB_CODE_CARD_RET:
	case LOGAB_CODE_DEVISSUE:
	case LOGAB_CODE_DEVREPL:
	case LOGAB_CODE_DEVCAN:
	case LOGAB_CODE_RELTRM:
	case LOGAB_CODE_SMSCHG:

		struct EXTDTAB *extDTAB;
		extDTAB = (struct EXTDTAB*)plExtData_Buf;
		pMsg->m_iMsgErrwu = extDTAB->extdtcomm.acterrwu;

		pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTAB->extdtcomm.actts);
		pMsg->txnidd = extDTAB->txnidd;

		break;
	
	default:
		// General extra data
		struct EXTDTCOMMAB *extDTComm;
		extDTComm = (struct EXTDTCOMMAB*)plExtData_Buf;
		pMsg->m_iMsgErrwu = extDTComm->acterrwu;
		pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTComm->actts);

		break;
	}

	return pMsg;
}

const Msg * ExtractMgr::GetEODMsgObj(unsigned char *binArr, LOGAB *pMlog)
{
	pMsg->m_iMsgSize = pMlog->hdr.sizew;
	pMsg->m_iMsgCode = pMlog->hdr.codewu;

	return pMsg;
}

LOGAB * ExtractMgr::GetLogObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, short &binSize)
{
	short msgSize = 0;
	memcpy(&msgSize, binArr + (PAYLOAD_HDR_SIZE + pHdr->extra_data_len), 2);//get message size: first 2 bytes of one whole message --assume the binary has at least 2 bytes, but binary may be null.
	binSize = msgSize;

	if (msgSize == 0 || msgSize<sizeof(LOGAB_HDR)) // except message tytes which size = sizeof(LOGAB_HDR):eg:sign on/off 
	{
		return NULL; // set to null if size is incorrect
	}
	//fix decoding error for the case that payload size > struct size in prod
	if (msgSize > sizeof(LOGAB))
	{
		msgSize = sizeof(LOGAB) - 1;
	}

	memcpy(pMsg->m_cpBuf, binArr + (PAYLOAD_HDR_SIZE + pHdr->extra_data_len), msgSize); //copy from the specified index: payload header size (35) + extra data length.


	return (struct LOGAB *)pMsg->m_cpBuf;
}

LOGAB * ExtractMgr::GetEODLogObj(unsigned char *binArr)
{
	short msgSize = 0;

	memcpy(&msgSize, binArr, 2);//get message size: first 2 bytes of one whole message
	memcpy(pMsg->m_cpBuf, binArr, msgSize); //copy from the specified index: payload header size (35) + extra data length.

	return (struct LOGAB *)pMsg->m_cpBuf;
}

int ExtractMgr::GetBinarySize(unsigned char *binArr)
{
	int len = 0;
	while (*binArr != 0)
	{
		len++;
		binArr++;
	}

	return len;
}

__time32_t ExtractMgr::Convert64TmTo32Tm(__int64 time64_t)throw(exception)
{
	struct tm * tm = _localtime64(&time64_t);
	if (tm == NULL)
		throw std::invalid_argument("NULL pointer for time.");
	__time32_t time32_t = _mktime32(tm);
	return time32_t;

}

void ExtractMgr::AddSolaceHdr(PAYLOAD_HDR *pHdr, char *buf, char *tmp, const char *hdrDelimiter)
{
	//memset(buf, 0, sizeof(buf));

	//Add solace payload header: the sixth element is activityCode that is for EDABI.
	sprintf(tmp, "%d", pHdr->system_id);
	AddHeaderField(buf, tmp, hdrDelimiter);

	sprintf(tmp, "%d", pHdr->business_date);
	AddHeaderField(buf, tmp, hdrDelimiter);

	sprintf(tmp, "%I64u", pHdr->activity_id);
	AddHeaderField(buf, tmp, hdrDelimiter);

	sprintf(tmp, "%d", pHdr->enquiry_status);
	AddHeaderField(buf, tmp, hdrDelimiter);

	/*if (pHdr->activity_nature == '\0')
		sprintf(tmp, "%d", 0);
	else
		sprintf(tmp, "%s", pHdr->activity_nature);*/
	sprintf(tmp, "%d", pHdr->activity_nature);
	AddHeaderField(buf, tmp, hdrDelimiter);
}

/*
Write log info.
level: 0--Info,1--Debug,2--Error/Exception
*/

void ExtractMgr::WriteErrorLog(char* logDir, char *errStr, int level)
{
	char logLevel[20] = { 0 };
	switch (level)
	{
	case 0:
		strcpy(logLevel, " Level[DEBUG] ");
		break;
	case 1:
		strcpy(logLevel, " Level[INFO] ");
		break;
	case 2:
		strcpy(logLevel, " Level[ERROR] ");
		break;
	default:
		break;
	}

	int infoLen = strlen(errStr) + strlen(logLevel) + 1;
	char *infoTmp = new char[infoLen];

	sprintf(infoTmp, logLevel);
	strcat(infoTmp, errStr);

	char logPath[100] = { 0 }; // log file path
	char timeStr[64] = { 0 }; // systerm time

	FILE *fp;

	char *logFile = GetLogFile(logPath, logDir);
	GetSystemTime(timeStr, sizeof(timeStr));

	if ((fp = fopen(logPath, "a")) != NULL)
	{
		fprintf(fp, "%s %s\n", timeStr, infoTmp);
		fclose(fp);
	}

	delete[] infoTmp;
	infoTmp = NULL;
}

void ExtractMgr::WriteInfoLog(char* logDir, int level, const char* infoStr)
{
	if (infoStr == NULL)
		return;

	char logLevel[20] = { 0 };
	switch (level)
	{
	case 0:
		strcpy(logLevel, " Level[DEBUG] ");
		break;
	case 1:
		strcpy(logLevel, " Level[INFO] ");
		break;
	case 2:
		strcpy(logLevel, " Level[ERROR] ");
		break;
	default:
		break;
	}

	int infoLen = strlen(infoStr) + strlen(logLevel) + 1;
	char *infoTmp = new char[infoLen];

	sprintf(infoTmp, logLevel);
	strcat(infoTmp, infoStr);

	//const char logDir[] = "\\LOG\\ACP_Decode\\"; // log directory
	char logPath[512] = { 0 }; // log file path
	char timeStr[64] = { 0 }; // systerm time

	//_getcwd(logPath, sizeof(logPath));

	char *logFile = GetLogFile(logPath, logDir);
	GetSystemTime(timeStr, sizeof(timeStr));

	FILE *fp;

	if ((fp = fopen(logPath, "a")) != NULL)
	{
		fprintf(fp, "%s %s\n", timeStr, infoTmp);
		fclose(fp);
	}

	delete[] infoTmp;
	infoTmp = NULL;
}