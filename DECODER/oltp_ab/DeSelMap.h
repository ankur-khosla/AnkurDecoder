// DeSelMap.h: interface for the DeSelMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DESELMAP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
#define AFX_DESELMAP_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ABMsgTranslator.h"
#include <ctype.h>
#include "udtypedef.h"
#include "rdsdef.h"
#include <string.h>
#include "LOGDEF_AB.h"
#include "LOGRDCDEF.h"

// Symbols used in formatting lottery bet record
#define BET_BNKSYM_C '>'            // Banker symbol
#define BET_FLDSYM_C 'F'            // Field symbol
#define BET_NUMSEP_C '+'            // Number separator symbol
#define BET_PWBSEP_C '#'            // Powerball selection set separator symbol
#define BET_ENTSEP_C '/'            // Multi-entry separator symbol
#define BET_RDGIND_C "RG"           // Random Generation indicator
#define BET_MULDRW_C "MD"           // Multi-Draw indicator
#define TSN_ASC_LENGTH 21           // TSN ASCII length

class DeSelMap : public ABMsgTranslator  
{
public:
	char* GetType	(char m_cType, char Type[10]);

	char* GetFormula(int m_iFormula, char m_sFormula[15]);

	void GetSel		(const struct LOGAB * pMlog, unsigned char m_cType, char bufs[1024]);
	
	void fmtAup		(const struct LOGAB * pMlog, char sels[1024]);
	
	void fmtMk6		(const struct LOGAB * pMlog, unsigned int m_iType, char sels[300]);
	
	void fmtNrm		(const struct LOGAB *pMlog, char sels[1024]);
	
	void fmtInd		(const struct LOGAB *pMlog, const bool allupt, // true if allup
						const unsigned short idwu, // id no. for allup array
						char sels[200]); // selections
	
	void fmtQin		(const struct LOGAB *pMlog, const unsigned short numofbnk, // num of bankers
						const unsigned short numofbmp, // num of bitmaps
						const unsigned short bmpposwu, // bitmap position
						const bool allupt, // true if allup
						const unsigned short idwu, // id no. of allup array
						char sels[]); // selections

	void fmtQin2	(const struct LOGAB *pMlog, const unsigned short numofbnk, // num of bankers
						const unsigned short numofbmp, // num of bitmaps
						const unsigned short bmpposwu, // bitmap position
						const bool allupt, // true if allup
						const unsigned short idwu, // id no. of allup array
						char sels[]); // selections

	void fmtSln		(const struct LOGAB *pMlog, const unsigned short bmppos, // bitmap position 
						const bool allupt, // true if allup
						const unsigned short idwu, // id no. for allup array
						char sels[]); // selections

	void fmtSln2	(const struct LOGAB *pMlog, const unsigned short bmppos, // bitmap position 
						const bool allupt, // true if allup
						const unsigned short idwu, // id no. for allup array
						char sels[]); // selections
	
	void fmtExt		(const struct LOGAB *pMlog, const unsigned short numofbmp, // number of bitmap
						const unsigned short numofbnk, // number of banker
						char sels[]); // selections

	void fmtExtAup(const struct LOGAB *pMlog, const unsigned short numofbmp, // number of bitmap
		const unsigned short idwu, // id no. of allup array
		char sels[]); // selections
	
	void fmtbet_aon (const unsigned char mapbu[],  // Addon selection bitmap
						const unsigned short baswu,   // Addon base investment
						unsigned short *offsetwu, // position offset
						char betb[]); // selections
	
	void fmtbet_oeg (const unsigned char bettypebu,       // bet type
						const unsigned char nselbu,   // # of selections
						const unsigned char mapbu[],  // Selection bitmap
						unsigned short *offsetwu, // Offset
						char sels[]); // selections
	
	void fmtMk6Sln	(const unsigned short pwbbasenumwu, // gbl base no.
						const bool lott, // true if lottery select
						const unsigned char mapbu[8], // lottery bitmap
						unsigned short *offsetwu, // position offset
						char betb[]); // selections
	
	void ltrimzero	(char * instrs); // input amount string
	
	void fmtbet_ccg (const unsigned char bettypebu,       // bet type
						const unsigned char gamebu,       // Subgame type
						const unsigned char mapbu[],      // Subgame map    
						unsigned short *offsetwu,  // Offset
						char sels[]); // selections

	bool editD		(char *outstrs, const char *inmasks, const LONGLONG valued );

	bool editNL		(char *outstrs,
						const char *inmasks,
						const char *incvtstrs,
						const bool negt);

	bool editBadOutput(char *outstrs,
						const short lenw );

	unsigned short stdExoBetType2LegCnt(const unsigned char  bet_typebu );

	unsigned char bet2PoolType( const unsigned char bet_typebu, unsigned char pool_typebu[] );


	char* osi_atrim	( /* [in|out] */  char  *strs );

	char* osi_ltrim	( /* [in|out] */  char  *strs );

	char* osi_rtrim	( /* [in|out] */  char  *strs );

	void BtoHex		(unsigned char *cpSrc, int iSize, char *cpDest) const;

	char* getForm	(unsigned char index, char legs[5]);

	DeSelMap() {};
	virtual ~DeSelMap() {};

};

#endif // !defined(AFX_DeSelMap_H__537261C3_03C6_11D4_B3C4_00C04F79D485__INCLUDED_)
