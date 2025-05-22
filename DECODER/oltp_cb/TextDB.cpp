// TextDB.cpp: implementation of the TextDB class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <string.h>

//#include "ADO_CLASS.h"
#include "TextDB.h"

/////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void TextDB::ErrHandler( int a_iErrVal, const char *a_pMsg )
{
	if(a_iErrVal&TXT_COM_INIT_ERR)
	{
		printf("Error : Storage - COM initialize failed!\n");
	}

	if(a_iErrVal&TXT_CREATE_CONN_ERR)
	{
		printf("Error : Storage - connection object creation failed!\n");
	}

	if(a_iErrVal&TXT_CREATE_CMD_ERR)
	{
		printf("Error : Storage - command object creation failed!\n");
	}
}


TextDB::TextDB()
{
	Init();
	m_bRecovery = FALSE;
}


TextDB::TextDB( bool a_bRecovery )
{
	Init();
	m_bRecovery = a_bRecovery;
}

TextDB::~TextDB()
{
	Uninit();
}

void TextDB::Init()
{
	m_pExceptMsg=NULL;
	m_iConnected=0;
	m_iComInited=0;
	SetProvider("SQLOLEDB");
	SetServer("");
	SetDefaDB("");
	SetUser("");
	SetPasswd("");
	UnSetTrustConn();
	m_iErrStatus=0;

	RecordDef	rd;
	rd.SetDelimiter ( "~|~" );

	for (int i=0; i<100; i++)
		m_iMsgCounter[i] = 0;
}



void TextDB::Uninit()
{
	Disconnect();
	ClearExceptMsg();
}




int TextDB::GetErrStatus()
{
	return m_iErrStatus;
}

void TextDB::SetServer(const char *cp)
{
	if(cp !=NULL)
	{
		sprintf(m_cServer, "Data Source=%s;", cp);
	} else {
		sprintf(m_cServer, "");
	}
}

void TextDB::SetUser(const char *cp)
{
	if(cp != NULL)
	{
		sprintf(m_cUser, "User Id=%s;", cp);
	} else {
		sprintf(m_cUser, "");
	}
}

void TextDB::SetDefaDB(char *cp)
{
	if(cp !=NULL&&cp[0]!=NULL)
	{
		sprintf(m_cDefaDB, "Initial Catalog=%s;", cp);
	} else {
		sprintf(m_cDefaDB, "");
	}
}

void TextDB::SetPasswd(const char *cp)
{
	if(cp !=NULL)
	{
		sprintf(m_cPasswd, "Password=%s;", cp);
	} else {
		sprintf(m_cPasswd, "");
	}
}

char * const TextDB::GetMsgType(int iMsg)
{

	if (iMsg < m_iMaxMsg)
		return m_msgFileMap[iMsg].msgName ;
	else
		return m_msgFileMap[0].msgName ;
}

void TextDB::SetConnectOpt(long lopt)
{
	m_lConnOpt=lopt;
}

int TextDB::Connect()
{
	return STORE_NO_ERR;
}

int TextDB::CheckPoint()
{
	for (int i=0; i<m_iMaxMsg; i++)
	{
		if (m_msgFileMap[i].fp)
			fflush( m_msgFileMap[i].fp );
	}
	return STORE_NO_ERR;
}


int TextDB::Disconnect()
{
	for (int i=0; i<m_iMaxMsg; i++)
	{
		if (m_msgFileMap[i].fp)
			fclose( m_msgFileMap[i].fp );
	}
	return STORE_NO_ERR;
}



int TextDB::ExecStoreProc(RecordDef *pRcdDef, long &lRetVal, long iStoreProcType)
{
	if (iStoreProcType >= m_iMaxMsg )
	{
		lRetVal = 0;
		return STORE_NO_ERR;
	}

//	char	buf[1024];
	char	buf[8192];
	
	int		inCol = pRcdDef->GetDelimitedText ( buf );
//	printf("%s", buf);
	if ( inCol > 0 )
	{
		if(iStoreProcType == 0)
			iStoreProcType = 0;
		if (!m_msgFileMap[iStoreProcType].fp)
		{
			if ( (m_msgFileMap[iStoreProcType].fp = fopen( m_msgFileMap[iStoreProcType].fileName, m_bRecovery? "w+" : "w" )) == NULL )
			{
				return TXT_CMD_EXEC_ERR;
			}
		}

		m_iMsgCounter[iStoreProcType]++;

		int temp=fprintf( m_msgFileMap[iStoreProcType].fp, "%s\n", buf );
		
		if ( m_iMsgCounter[iStoreProcType] % 100 == 0 )
			CheckPoint();
	}
	lRetVal = 0;
	return STORE_NO_ERR;
}


int TextDB::ExecStoreProc(RecordDef *pRcdDef, long &lRetVal)
{
	lRetVal = 0;
	return STORE_NO_ERR;
}

int TextDB::ExecSQL(const char *cp)
{
	return STORE_NO_ERR;
}


void TextDB::ClearExceptMsg()
{
	if(m_pExceptMsg != NULL)
	{
		delete m_pExceptMsg;
		m_pExceptMsg = NULL;
	}
}

const DB_ExceptMsg * TextDB::GetExceptMsg()
{
	return m_pExceptMsg;
}

void TextDB::SetProvider(const char *cp)
{
	if (cp!=NULL&&cp[0]!=NULL)
	{
		sprintf(m_cProvider, "Provider=%s;", cp);
	} else {
		sprintf(m_cProvider, "Provider=SQLOLEDB;");
	}
}

RecordDef * TextDB::GetRecord()
{
	
	return NULL;
}

void TextDB::MoveFirstRec()
{
	/*
	try
	{
		m_adopObjs->m_adoRs->MoveFirst();
	} catch (_com_error &e) {
		TrapExceptMsg(e);
	}
	*/
}

void TextDB::MoveToRec(int iIdx)
{
	/*
	if(iIdx<=0)
	{
		return;
	}

	try
	{
		if(m_adopObjs->m_adoRs->EndOfFile)
		{
			return;
		}

		m_adopObjs->m_adoRs->Move(iIdx);
	} catch (_com_error &e) {
		TrapExceptMsg(e);
	}
	*/
}

void TextDB::SetTrustConn()
{
	sprintf(m_cSecurity, "Integrated Security=SSPI");
}

void TextDB::UnSetTrustConn()
{
	m_cSecurity[0]=NULL;
}

void TextDB::MakeConnStr()
{
	if(m_cSecurity[0]==NULL)
	{
		sprintf(m_cConnStr, "%s%s%s%s%s", m_cProvider, m_cServer, m_cDefaDB, m_cUser, m_cPasswd);
	} else {
		sprintf(m_cConnStr, "%s%s%s%s", m_cProvider, m_cServer, m_cDefaDB, m_cSecurity);
	}
}

FILE *fp = NULL;
int TextDB::Get_SB_Select(char* string)
{
	char c[1024];
	strcpy(c, string);
/*	int SB_Selection_Code = 58;
	if (0)
		{
			if ( (m_msgFileMap[SB_Selection_Code].fp = fopen( "cb_sb_simple_selections.txt", "a+")) == NULL )
			{
				return TXT_CMD_EXEC_ERR;
			}
		}
*/	if ( fp == NULL)
	if ( (fp = fopen( "cb_sb_simple_selections.txt", "a+")) == NULL )
	{
		return TXT_CMD_EXEC_ERR;
	}
			
	fprintf(fp, "%s", string);
	fflush(fp);

	return(0);

}