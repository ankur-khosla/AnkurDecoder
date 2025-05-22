/////////////////////////////////////////////////////////////////////
//
// ExtractMgr.cpp: implementation of the ExtractMgr class.
//
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
//#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "CBMsgDef.h"
#include "ExtractMgr.h"
#include "JCLogger.h"
#include "JCSystem.h"
#include "MsgTranslator.h"

#include "CBLogger.h"
#include "CBSystem.h"
//#include "CBMsgTranslator.h"
#include "CBExtraData.h"

#include "vector";
#include "eh.h"
#include "typeinfo"
#include "time.h"
#include <string>
#include <direct.h>
#include <io.h>
//#include <afxmt.h>
#include <sys/timeb.h>

using namespace std;

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
	if (plHdr_Buf != NULL)
	{
		delete[] plHdr_Buf;
		plHdr_Buf = NULL;
	}

	if (plExtData_Buf != NULL)
	{
		delete[] plExtData_Buf;
		plExtData_Buf = NULL;
	}

	if (pMsg != NULL)
	{
		delete pMsg;
		pMsg = NULL;
	}
}

//vector<char*> ExtractMgr::v_SimSel;
vector<string> v_SimSel;
//extern unsigned short tsnSystemNumbu(const union TSN  tsnu);

void ExtractMgr::SetSystem(JCSystem *a_pSysMgr)
{
	m_pSysMgr	= a_pSysMgr;
}

char * GetLogFile(char *logPath,const char *logDir)
{
	strcat(logPath, logDir);
	if (access(logPath, 0) == -1)
		mkdir(logPath);

	time_t t = time(NULL);
	tm tm = *localtime(&t);

	char logFile[50];
	sprintf(logFile, "AGP_DECODE_%d-%02d-%02d.log", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	strcat(logPath, logFile);

	return logPath;
}

void AddHeaderField(char *buf,char *tmp,const char m_sDelimiter[])
{
	strcat(buf, tmp);
	strcat(buf, m_sDelimiter);
}

void GetSystemTime(char *timeStr,int len)
{
	/*time_t t = time(NULL);
	strftime(timeStr, len, "%Y-%m-%d %X ", localtime(&t));*/

	struct timeb tb;
	ftime(&tb);
	tm tm = *localtime(&tb.time);
	sprintf(timeStr, "Time[%d-%02d-%02d %02d:%02d:%02d,%03d]", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, tb.millitm);
}


//Note: byte size of long type in windows 64-bit is still 4
/*
The function is used to decode binary message from Solace. 2016.7.28 paul
srMsg: 2D pointer to store binary array;
len: length of the array;
resMsg: store decoded result;
errCount: exception count
*/
char ** ExtractMgr::DecodeCBMsgs(unsigned char ** srMsg, int len, int &totalCount, int &errCount, char *logDir, int logLevel)
{
	/*if(logLevel <=1)
		WriteInfoLog(logDir,1, " --------Decode starts-------- ");*/
	//initial
	JCSystem	*pCBSystem = new CBSystem();
	SetSystem(pCBSystem);

	unsigned __int64 activityId = 0;
	unsigned int systemId = 0;

	const char hdrDelimiter[] = "@|@";// for header

	char tmp[30] = { 0 };
	char buf[MSG_SIZE] = { 0 }; //8000
	const Msg *tmpMsg;
	struct LOG *pMlog;
	char *msgStr = NULL;
	struct PAYLOAD_HDR *pHdr;

	char info[512] = { 0 };

	if (logLevel <= 1)
	{
		sprintf(info, "total messages to be decoded:%d", len);
		WriteInfoLog(logDir, 1, info);
	}

	int smCount = 0; // total simple selections for all messages

	vector<string> v_msg; // store all decoded messages

	// loop---decode messsages one by one
	for (int i = 0; i < len; i++)
	{
		try
		{	
			msgStr = NULL;
			memcpy(plHdr_Buf, srMsg[i], PAYLOAD_HDR_SIZE);//1.Get payload header: size is 35 bytes
			pHdr = (struct PAYLOAD_HDR*)plHdr_Buf;//2.maped to payload header

			memset(buf, 0, sizeof(buf));
			memset(pMsg->m_cpBuf, 0, BINARY_MAX_SIZE);

			//Add solace payload header: the sixth element is activityCode that is for EDABI.
			sprintf(tmp, "%d", pHdr->system_id);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pHdr->business_date);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%I64u", pHdr->activity_id);
			AddHeaderField(buf, tmp, hdrDelimiter);

			sprintf(tmp, "%d", pHdr->enquiry_status);
			AddHeaderField(buf, tmp, hdrDelimiter);

			if (pHdr->activity_nature == '\0')
				sprintf(tmp, "%d", 0);
			else
				sprintf(tmp, "%s", pHdr->activity_nature);
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
				sprintf(info, "system id:%d; activity id:%I64u", pHdr->system_id, activityId);
				WriteInfoLog(logDir, 0, info);// log info for test mode; turn it off when released
			}

			short binSize = 0;
 			pMlog = GetLogObj(srMsg[i], pHdr, binSize); // get the whole message

			pMlog->hdr.custoseid = pHdr->cust_session_id; // assign cust_session_id from payload header to message header

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
					sprintf(info, "Incorrect length of binary. system id:%d; activity id:%I64u; binary size:%d; LOGHDR size:%d; LOG size: %d", pHdr->system_id, activityId, binSize, sizeof(LOGHDR), sizeof(LOG));
					WriteErrorLog(logDir, info, 2);
				}
			}
			else
			{
				tmpMsg = GetMsgObj(srMsg[i], pHdr, pMlog);// 3. Get Msg and extra data 

				if (tmpMsg->m_iMsgCode == LOG_SB_C)
				{
					// for cb_sb_simple_selections
					struct BETSB_SIMPLE *pMSim;
					pMSim = (struct BETSB_SIMPLE *)pMlog->d.bt.sb.d.bet.bet.var.sb.vbu;

					if (logLevel <= 0)
					{
						sprintf(info, "AGP SB Bet: pool type:%d; match no:%d", pMSim->poolbu, pMSim->matchbu);
						WriteInfoLog(logDir, 0, info);
					}

				}

				//msgStr = m_pSysMgr->DecMsg(pMsg);//4.Decode message and get text message

				if (pMlog->hdr.prelog1 == 0)// not prelog
				{

					if (logLevel <= 0)
					{
						sprintf(info, "Start decoding message:system id:%d; activity id:%I64u", pHdr->system_id, activityId);
						WriteInfoLog(logDir, 0, info);// log info for test mode; turn it off when released
					}

					CBMsgTranslator cbMsgTranslator;
					union TSN tsn = pMlog->d.bt.ccp.tsn;
					int sales_sys_no = cbMsgTranslator.tsnSystemNumbu(tsn); // get tsn owner

					if (tmpMsg->m_iMsgCode == LOG_CAN_C && sales_sys_no != pHdr->system_id && (pMlog->hdr.ticket_type == TICKET_TYPE_RACING || pMlog->hdr.ticket_type == TICKET_TYPE_LOTTERY)) // DEC2019 support cross system cancel for racing & lottery. Filter cancel message which system_id <> sales_sys_no (systrem id of sales system), keep cancel message which system_id = sales_sys_no 
					{
						if (logLevel <= 0)
						{
							sprintf(info, "Cross system cancel ticket. skip it:system id:%d; activity id:%I64u; activity code:%d", pHdr->system_id, activityId, pMsg->m_iMsgCode);
							WriteInfoLog(logDir, 0, info);
						}

						sprintf(tmp, "%d", 7); // 0: success; 1: not implemented; 2: obsoleted; 3: payload body is null; 4: ESC transaction--not Payout/Cancel; 5: ESC transaction--Payout/Cancel,tsn owner is not the system; 6: EFT_EMV (used in ACP decoder); 7: cross system cancel ticket; 9: exception
						AddHeaderField(buf, tmp, hdrDelimiter);

						sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
						AddHeaderField(buf, tmp, hdrDelimiter);
					}
					else
					{
						if (pMlog->hdr.accmod1 == 0)
						{
							msgStr = m_pSysMgr->DecMsg(tmpMsg);//4.Decode message and get text message

							if (msgStr != NULL)
							{
								if (0 != strcmp(msgStr, (char*)(&NOT_IMPLEMENTED)))
								{
									sprintf(tmp, "%d", 0); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
									AddHeaderField(buf, tmp, hdrDelimiter);

									strcat_s(buf, msgStr);

									if (logLevel <= 0)
										WriteInfoLog(logDir, 0, "Add result message--normal message in buffer");
								}
								else
								{
									if (logLevel <= 0)
										WriteInfoLog(logDir, 0, "Add result message--not implemented message in buffer");

									sprintf(tmp, "%d", 1); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
									AddHeaderField(buf, tmp, hdrDelimiter);

									sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
									AddHeaderField(buf, tmp, hdrDelimiter);
								}
							}
						}

						//ESC transaction:hdr.accmod1=1
						else if (tmpMsg->m_iMsgCode == LOG_CAN_C || tmpMsg->m_iMsgCode == LOG_PAY_C)
						{
							int tsnSysOwner = cbMsgTranslator.tsnSystemNumbu(tsn); // get tsn owner
							short tsnBetType = cbMsgTranslator.tsnBetTypebu(tsn); // bet type

							// tsn owner is the current system
							if ((tsnSysOwner == pHdr->system_id || tsnBetType == TSN_BTYPE_SB) && pMlog->hdr.paydep1 == 0) //exclude cancel/payout deposit
							{
								msgStr = m_pSysMgr->DecMsg(tmpMsg);//4.Decode message and get text message

								if (msgStr != NULL)
								{
									if (0 != strcmp(msgStr, (char*)(&NOT_IMPLEMENTED)))
									{
										sprintf(tmp, "%d", 0); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
										AddHeaderField(buf, tmp, hdrDelimiter);

										strcat_s(buf, msgStr);

										if (logLevel <= 0)
											WriteInfoLog(logDir, 0, "Add result message--normal message in buffer");
									}
									else
									{
										if (logLevel <= 0)
											WriteInfoLog(logDir, 0, "Add result message--not implemented message in buffer");

										sprintf(tmp, "%d", 1); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
										AddHeaderField(buf, tmp, hdrDelimiter);

										sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
										AddHeaderField(buf, tmp, hdrDelimiter);
									}
								}
							}
							else  //Skip ESC transaction which is Payout/Cancel, but tsn owner is not the current system
							{
								if (logLevel <= 0)
								{
									sprintf(info, "ESC Transaction, Payout or Cancel, but tsn owner is not current system: skip it:system id:%d; activity id:%I64u; activity code:%d", pHdr->system_id, activityId, pMsg->m_iMsgCode);
									WriteInfoLog(logDir, 0, info);
								}

								sprintf(tmp, "%d", 4); // 0: success; 1: not implemented; 2: obsoleted; 3: payload body is null; 4: ESC transaction--not Payout/Cancel; 5: ESC transaction--Payout/Cancel,tsn owner is not the system;9: exception
								AddHeaderField(buf, tmp, hdrDelimiter);

								sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
								AddHeaderField(buf, tmp, hdrDelimiter);
							}

						}
						else //Skip ESC transaction which is not Payout/Cancel
						{
							if (logLevel <= 0)
							{
								sprintf(info, "ESC Transaction, but not Payout/Cancel: skip it:system id:%d; activity id:%I64u; activity code:%d", pHdr->system_id, activityId, pMsg->m_iMsgCode);
								WriteInfoLog(logDir, 0, info);
							}

							sprintf(tmp, "%d", 5); // 0: success; 1: not implemented; 2: obsoleted; 3: payload body is null; 4: ESC transaction--not Payout/Cancel; 5: ESC transaction--Payout/Cancel,tsn owner is not the system;9: exception
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
				else // Skip prelog
				{
					if (logLevel <= 0)
					{
						sprintf(info, "Prelog message: skip it:system id:%d; activity id:%I64u", pHdr->system_id, activityId);
						WriteInfoLog(logDir, 0, info);
					}

					sprintf(tmp, "%d", 2); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
					AddHeaderField(buf, tmp, hdrDelimiter);

					sprintf(tmp, "%d", tmpMsg->m_iMsgCode);
					AddHeaderField(buf, tmp, hdrDelimiter);
				}
			}

			if (logLevel <= 0)
			{
				sprintf(info, "Message Info:system id:%d; activity id:%I64u; activity code:%d", pHdr->system_id, activityId, tmpMsg->m_iMsgCode);
				WriteInfoLog(logDir, 0, info);
			}

			if (logLevel <= 0)
				WriteInfoLog(logDir,0, ("Copy result message:"+string(buf)).c_str());

			v_msg.insert(v_msg.end(), string(buf));

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
				memset(buf, 0, sizeof(buf));
				AddSolaceHdr(pHdr, buf, tmp, hdrDelimiter);

				sprintf(tmp, "%d", 0); // 0: success; 1: not implemented; 2: obsoleted; 9: exception
				AddHeaderField(buf, tmp, hdrDelimiter);

				strcat_s(buf, v_SimSel[n].c_str());

				int index = i + (smCount - simSelSize) + n + 1;

				v_msg.insert(v_msg.end(), string(buf));
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

		catch (const exception& e)// grab standard exceptions: logic_error, runtime_error...
		{

			sprintf(tmp, "%d", 9); // 0: success; 1: failure
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
			sprintf(tmp, "%d", 9); // 9999: exception
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
		memset(retMsg[k], 0, MSG_SIZE);

		memcpy(retMsg[k], v_msg[k].c_str(), strlen(v_msg[k].c_str()));

		char logPath[512] = "C:\\work\\SAT_Files\\result.txt";

		FILE *fp;

		if ((fp = fopen(logPath, "a")) != NULL)
		{
			fprintf(fp, "%s\n", v_msg[k].c_str());
			fclose(fp);
		}
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
		WriteErrorLog(logDir, info, 0);
	}

	delete pCBSystem;
	pCBSystem = NULL;

	if (logLevel <= 1)
	{
		sprintf(info, "Total result messages:%d(including %d simple selections)", totalCount, smCount);
		WriteInfoLog(logDir, 1, info);
	}

	/*if(logLevel <= 1)
		WriteInfoLog(logDir, 1, " --------Decode ends-------- ");*/

	return retMsg;

}

void ExtractMgr::AddSolaceHdr(PAYLOAD_HDR *pHdr,char *buf,char *tmp,const char *hdrDelimiter)
{
	//Add solace payload header: the sixth element is activityCode that is for EDABI.
	sprintf(tmp, "%d", pHdr->system_id);
	AddHeaderField(buf, tmp, hdrDelimiter);

	sprintf(tmp, "%d", pHdr->business_date);
	AddHeaderField(buf, tmp, hdrDelimiter);

	sprintf(tmp, "%I64u", pHdr->activity_id);
	AddHeaderField(buf, tmp, hdrDelimiter);

	sprintf(tmp, "%d", pHdr->enquiry_status);
	AddHeaderField(buf, tmp, hdrDelimiter);

	if (pHdr->activity_nature == '\0')
		sprintf(tmp, "%d", 0);
	else
		sprintf(tmp, "%s", pHdr->activity_nature);
	AddHeaderField(buf, tmp, hdrDelimiter);

	//return buf;
}

void ExtractMgr::WriteInfoLog(char* logDir, int level, const char* infoStr)
{
	if (infoStr == NULL)
		return;

	char logLevel[20] = { 0 };
	switch (level)
	{
	case 0:
		strcpy(logLevel," Level[DEBUG] ");
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

	int infoLen = strlen(infoStr) + strlen(logLevel) +1;

	char *infoTmp = new char[infoLen];

	sprintf(infoTmp,logLevel);

	//strcat(infoTmp,logLevel);
	strcat(infoTmp, infoStr);

	//getcwd(fullPath, sizeof(fullPath));
	//_getcwd(fullPath, sizeof(fullPath));

	//const char logDir[] = "\\LOG\\AGP_Decode\\"; // log directory
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

const Msg * ExtractMgr::GetMsgObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, LOG *pMlog)
{
	switch (pHdr->system_id)
	{
		case AGP01:
			strcpy(pMsg->m_iSysName, "AGP01");
			break;
		case AGP02:
			strcpy(pMsg->m_iSysName, "AGP02");
			break;
		case AGP03:
			strcpy(pMsg->m_iSysName, "AGP03");
			break;
		case AGP04:
			strcpy(pMsg->m_iSysName, "AGP04");
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
		case LOG_BET_C:
		case LOG_LOT_C:
		case LOG_CVI_C:
			struct EXTRADATARLC *extD;
			extD = (struct EXTRADATARLC*)plExtData_Buf;
			pMsg->m_iMsgErrwu = extD->acterrwu;
			
			pMsg->m_iMsgSellTime = Convert64TmTo32Tm(extD->btsellt);			
			pMsg->m_iMsgTime = Convert64TmTo32Tm(extD->actts);

			pMsg->m_iMsgTktid = extD->tsntktid;
			break;

		case LOG_CAN_C:
		//case LOG_PAY_C:
			struct EXTRADATACCP *extDTCCP;
			extDTCCP = NULL;
			extDTCCP = (struct EXTRADATACCP*)plExtData_Buf;

			pMsg->m_iMsgErrwu = extDTCCP->acterrwu;
			
			if (extDTCCP->btsellt < 0)
				extDTCCP->btsellt = 0;

			pMsg->m_iMsgSellTime = Convert64TmTo32Tm(extDTCCP->btsellt);// use new selltime of extra data
			pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTCCP->actts);// use new selltime of extra data

			pMsg->m_iMsgTktid = extDTCCP->tsninfo.tktid; //ticket id

			break;

		case LOG_PAY_C:

			short tktType;
			tktType = pMlog->hdr.ticket_type;	// bet type

			if (tktType != TICKET_TYPE_CV)
			{
				struct EXTRADATACCP *extDTCCP;
				extDTCCP = NULL;
				extDTCCP = (struct EXTRADATACCP*)plExtData_Buf;

				pMsg->m_iMsgErrwu = extDTCCP->acterrwu;

				if (extDTCCP->btsellt < 0)
					extDTCCP->btsellt = 0;

				pMsg->m_iMsgSellTime = Convert64TmTo32Tm(extDTCCP->btsellt);// use new selltime of extra data
				pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTCCP->actts);// use new selltime of extra data

				pMsg->m_iMsgTktid = extDTCCP->tsninfo.tktid; //ticket id
			}
			else
			{
				struct EXTRADATACV *extDTCV;
				extDTCV = (struct EXTRADATACV*)plExtData_Buf;

				pMsg->m_iMsgErrwu = extDTCV->acterrwu;
				pMsg->m_iMsgTime = extDTCV->actts;

				pMsg->m_iMsgSellTime = Convert64TmTo32Tm(extDTCV->btsellt);// use new selltime of extra data
				pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTCV->actts);// use new selltime of extra data

				pMsg->m_iMsgTktid = extDTCV->tsninfo.tktid;
				
				//memcpy(&pMsg->cvRel, &extDTCV->cvRelinfo, sizeof(CVRelInfo));
				
				pMsg->cvRel.businessDate = extDTCV->cvRelinfo.businessDate;
				pMsg->cvRel.claim1 = extDTCV->cvRelinfo.claim1;
				pMsg->cvRel.costlu = extDTCV->cvRelinfo.costlu;
				pMsg->cvRel.currencyId = extDTCV->cvRelinfo.currencyId;
				pMsg->cvRel.custoseid = extDTCV->cvRelinfo.custoseid;
				pMsg->cvRel.hdOfficeF = extDTCV->cvRelinfo.hdOfficeF;
				pMsg->cvRel.lastactid = extDTCV->cvRelinfo.lastactid;
				pMsg->cvRel.methodbu = extDTCV->cvRelinfo.methodbu;
				pMsg->cvRel.originallu = extDTCV->cvRelinfo.originallu;
				pMsg->cvRel.paidCustSessid = extDTCV->cvRelinfo.paidCustSessid;

				pMsg->cvRel.paidfinal1 = extDTCV->cvRelinfo.paidfinal1;
				pMsg->cvRel.paidMethod = extDTCV->cvRelinfo.paidMethod;
				pMsg->cvRel.paidTerseid = extDTCV->cvRelinfo.paidTerseid;
				pMsg->cvRel.paidWinNo = extDTCV->cvRelinfo.paidWinNo;
				pMsg->cvRel.payCentrelu = extDTCV->cvRelinfo.payCentrelu;
				pMsg->cvRel.payDate = extDTCV->cvRelinfo.payDate;
				pMsg->cvRel.payExpBizDate = extDTCV->cvRelinfo.payExpBizDate;
				pMsg->cvRel.paylogseqlu = extDTCV->cvRelinfo.paylogseqlu;
				pMsg->cvRel.paySysb = extDTCV->cvRelinfo.paySysb > 99 ? 99 : extDTCV->cvRelinfo.paySysb; //support reversed cb pay without extra data case in Winter 2024

				if (pMsg->cvRel.paySysb == 99)
					pMsg->m_iMsgErrwu = 99; //treat cv_pay with incorrect pay_system as error msg

				pMsg->cvRel.payTime = extDTCV->cvRelinfo.payTime;

				pMsg->cvRel.purgedate = extDTCV->cvRelinfo.purgedate;
				pMsg->cvRel.remainlu = extDTCV->cvRelinfo.remainlu;
				pMsg->cvRel.retcenno = extDTCV->cvRelinfo.retcenno;
				pMsg->cvRel.retdate = extDTCV->cvRelinfo.retdate;
				pMsg->cvRel.rowver = extDTCV->cvRelinfo.rowver;
				pMsg->cvRel.sellCentrelu = extDTCV->cvRelinfo.sellCentrelu;
				pMsg->cvRel.selllogseqlu = extDTCV->cvRelinfo.selllogseqlu;
				pMsg->cvRel.sellTime = extDTCV->cvRelinfo.sellTime;
				pMsg->cvRel.sellWindowu = extDTCV->cvRelinfo.sellWindowu;
				pMsg->cvRel.sts = extDTCV->cvRelinfo.sts;
				pMsg->cvRel.terseid = extDTCV->cvRelinfo.terseid;
				pMsg->cvRel.tktid = extDTCV->cvRelinfo.tktid;
				pMsg->cvRel.verifier = extDTCV->cvRelinfo.verifier;
			}

			break;

		case LOG_CVC_C:

			struct EXTRADATACV *extDTCV;
			extDTCV = (struct EXTRADATACV*)plExtData_Buf;

			pMsg->m_iMsgErrwu = extDTCV->acterrwu;
			pMsg->m_iMsgTime = extDTCV->actts;

			pMsg->m_iMsgSellTime = Convert64TmTo32Tm(extDTCV->btsellt);// use new selltime of extra data
			pMsg->m_iMsgTime = Convert64TmTo32Tm(extDTCV->actts);// use new selltime of extra data

			pMsg->m_iMsgTktid = extDTCV->tsninfo.tktid;

			//memcpy(&pMsg->cvRel, &extDTCV->cvRelinfo, sizeof(extDTCV->cvRelinfo));

			pMsg->cvRel.businessDate = extDTCV->cvRelinfo.businessDate;
			pMsg->cvRel.claim1 = extDTCV->cvRelinfo.claim1;
			pMsg->cvRel.costlu = extDTCV->cvRelinfo.costlu;
			pMsg->cvRel.currencyId = extDTCV->cvRelinfo.currencyId;
			pMsg->cvRel.custoseid = extDTCV->cvRelinfo.custoseid;
			pMsg->cvRel.hdOfficeF = extDTCV->cvRelinfo.hdOfficeF;
			pMsg->cvRel.lastactid = extDTCV->cvRelinfo.lastactid;
			pMsg->cvRel.methodbu = extDTCV->cvRelinfo.methodbu;
			pMsg->cvRel.originallu = extDTCV->cvRelinfo.originallu;
			pMsg->cvRel.paidCustSessid = extDTCV->cvRelinfo.paidCustSessid;

			pMsg->cvRel.paidfinal1 = extDTCV->cvRelinfo.paidfinal1;
			pMsg->cvRel.paidMethod = extDTCV->cvRelinfo.paidMethod;
			pMsg->cvRel.paidTerseid = extDTCV->cvRelinfo.paidTerseid;
			pMsg->cvRel.paidWinNo = extDTCV->cvRelinfo.paidWinNo;
			pMsg->cvRel.payCentrelu = extDTCV->cvRelinfo.payCentrelu;
			pMsg->cvRel.payDate = extDTCV->cvRelinfo.payDate;
			pMsg->cvRel.payExpBizDate = extDTCV->cvRelinfo.payExpBizDate;
			pMsg->cvRel.paylogseqlu = extDTCV->cvRelinfo.paylogseqlu;
			pMsg->cvRel.paySysb = extDTCV->cvRelinfo.paySysb;
			pMsg->cvRel.payTime = extDTCV->cvRelinfo.payTime;

			pMsg->cvRel.purgedate = extDTCV->cvRelinfo.purgedate;
			pMsg->cvRel.remainlu = extDTCV->cvRelinfo.remainlu;
			pMsg->cvRel.retcenno = extDTCV->cvRelinfo.retcenno;
			pMsg->cvRel.retdate = extDTCV->cvRelinfo.retdate;
			pMsg->cvRel.rowver = extDTCV->cvRelinfo.rowver;
			pMsg->cvRel.sellCentrelu = extDTCV->cvRelinfo.sellCentrelu;
			pMsg->cvRel.selllogseqlu = extDTCV->cvRelinfo.selllogseqlu;
			pMsg->cvRel.sellTime = extDTCV->cvRelinfo.sellTime;
			pMsg->cvRel.sellWindowu = extDTCV->cvRelinfo.sellWindowu;
			pMsg->cvRel.sts = extDTCV->cvRelinfo.sts;
			pMsg->cvRel.terseid = extDTCV->cvRelinfo.terseid;
			pMsg->cvRel.tktid = extDTCV->cvRelinfo.tktid;
			pMsg->cvRel.verifier = extDTCV->cvRelinfo.verifier;

			break;

		case LOG_TBD_C:

			struct EXTRADATADE *extDE;
			extDE = (struct EXTRADATADE*)plExtData_Buf;

			pMsg->m_iMsgErrwu = extDE->extdcomm.acterrwu;

			pMsg->m_iMsgTime = Convert64TmTo32Tm(extDE->extdcomm.actts);
			pMsg->m_iMsgTktid = extDE->tsninfo.tktid;

			break;

		default: // General extra data
			struct EXTRADATACOMM *extDCOMM;
			extDCOMM = (struct EXTRADATACOMM*)plExtData_Buf;
			pMsg->m_iMsgErrwu = extDCOMM->acterrwu;
			pMsg->m_iMsgTime = Convert64TmTo32Tm(extDCOMM->actts);
			break;
	}

	/*struct tm *B_day;
                                                                	
	__time32_t msgTime = pMsg->m_iMsgTime;
	B_day= _localtime32(&msgTime);

	if (B_day != NULL)
	{
		pMsg->m_iMsgDay = B_day->tm_mday;
		pMsg->m_iMsgMonth = B_day->tm_mon + 1;
		pMsg->m_iMsgYear = B_day->tm_year + 1900;
	}*/

	char md[30] = { 0 };

	sprintf_s(md, "%d", pMlog->hdr.bussdate);
	if (strlen(md) == 8)
	{
		string mdStr = md;
		pMsg->m_iMsgYear = atoi(mdStr.substr(0, 4).c_str());
		pMsg->m_iMsgMonth = atoi(mdStr.substr(4, 2).c_str());
		pMsg->m_iMsgDay = atoi(mdStr.substr(6, 2).c_str());
	}

	return pMsg;
}

LOG * ExtractMgr::GetLogObj(unsigned char *binArr, PAYLOAD_HDR *pHdr, short &binSize)
{
	short msgSize = 0;
	memcpy(&msgSize, binArr + (PAYLOAD_HDR_SIZE + pHdr->extra_data_len), 2);//get message size: first 2 bytes of one whole message--assume the binary has at least 2 bytes, but binary may be null.
	binSize = msgSize;

	if (msgSize <= 0 || msgSize < sizeof(struct LOGHDR))//except message tytes which size = sizeof(LOGAB_HDR) : eg : sign on / off
	{
		return NULL; // set to null if size is incorrect
	}

	memcpy(pMsg->m_cpBuf, binArr + (PAYLOAD_HDR_SIZE + pHdr->extra_data_len), msgSize); //copy from the specified index: payload header size (35) + extra data length.

	/*struct LOG *pMlog;
	pMlog = (struct LOG *)pMsg->m_cpBuf;*/

	return (struct LOG *)pMsg->m_cpBuf;
}

__time32_t ExtractMgr::Convert64TmTo32Tm(__int64 time64_t)throw(exception)
{
	struct tm * tm = _localtime64(&time64_t);
	if (tm == NULL)
		throw std::invalid_argument("NULL pointer for time.");
	__time32_t time32_t = _mktime32(tm);
	return time32_t;

}


