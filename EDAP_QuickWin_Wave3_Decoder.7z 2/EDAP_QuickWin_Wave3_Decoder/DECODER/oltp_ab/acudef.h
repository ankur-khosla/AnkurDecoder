//    *******************************************************************
//    *                                                                 *
//    *   © COPYRIGHT.  The Hong Kong Jockey Club                       *
//    *                                                                 *
//    *   This software, which contains confidential material, is       *
//    *   private and confidential and is the property and copyright    *
//    *   of The Hong Kong Jockey Club (the Club). No part of this      *
//    *   document may be reproduced, stored in a retrieval system      *
//    *   or transmitted in any form or by any means, electronic,       *
//    *   mechanical, chemical, photocopy, recording or otherwise       *
//    *   without the prior written permission of the Club              *
//    *                                                                 *
//    *******************************************************************
//
//  Function:   Header file for account file.  It stores home unit of each
//              account.  Each home unit consists of static block and 
//              transaction block.
//
//  Author  :   Edward Hon          Dec-2002
//
//  Mod     :   HL01 18-Jun-2003
//                   Add transaction flag to Cancel transaction to show which
//                   kind of transaction to be canceled.
//
//              KL02 03-Nov-2003
//                   change the type of ACU_TRAN_DRCR.typebu to
//                   ACU_TRAN_DRCR.typelu
//
//              FT03 5-NOV-2003
//                   Add transactions 
//                      - ACU_TRAN_DFT (dividend forfeited) 
//                      - ACU_TRAN_AFR (cit annual fee reverse)
//                      - ACU_TRAN_RCR (reimbursement crediting)
//                   These transactions are previously handled as 
//                   dr/cr transaction with specific sub-type.
//
//              FT04 17-DEC-2003
//                   Add a/c status ACU_STATUS_DORMANT
//                      - eod will change a/c status from open to dormant
//                        when no. of inactive days > abparcom.todormantwu
//
//              RL05 09-JAN-2004
//                   Add flags for ESC account merging
//                      - Merge outstanding ESC transaction in progress flag
//                        (set during pairs of account for merging)
//                      - Flag to indicate an account carrys other account txn.
//                        (set only in integrated accounts with merging)
//                      - Steal a bit from txn # of account record header to
//                        indicates it is in merging stage
//
//              FT06 13-JAN-2004
//                   Delete transaction ACU_TRAN_RCR (reimbursement crediting)
//                   (replaced it by ACU_TRAN_DRCR with typelu = DRCR_AUTO_REIM)
//
//              FT07 16-JAN-2004
//                   - Add transaction code ACU_CODE_DIV_OS for dividend from
//                     outstanding esc transaction. It will use the same tran
//                     structure as ACU_CODE_DIV, ie. ACU_TRAN_DIV
//                   - Modify modification RL05 such that
//                     - Add outstanding ESC transaction flag in home block
//                       for closed account but with outstanding esc tran.
//                       Accounts with this flag set is responsible for 
//                       history update only but no a/c balance update.
//                     - For every transaction transferred from other account,
//                       set a merge1 flag. No history update is 
//                       needed for transactions with this flag set.
//
//              CS08 3-FEB-2004
//                   - fix bug as no define for ACU_STATUS_MAX.
//      
//              HL09 4-FEB-2004
//                   - Uuse likes to have these credit debit adjustment items
//          
//              FT10 9-FEB-2004
//                   - Add transaction details to structure ACU_TRAN_DIV_PUR
//
//              FT11 19-FEB-2004
//                  - add history offset of last a/c access record to 
//                    struct ACU_TRAN_EXTRA
//                    ( for looking of a/c access info when writing exception
//                      bet details record '664' & '666')
//
//              HL12 20-FEB-2004
//                  - add 7 credit debit adjustment reason codes 900 - 906
//                    for old TB systems during migration because these 
//                    codes are not existed in AB credit debit adjustments. 
//
//              FT13 12-MAR-2004
//                  - add define for max. value of auto dr/cr tran 
//                    ACU_DRCR_AUTO_MAX   
//
//              HL14 15-March-2004
//                  - add credit adjustment others and debit adjustment others
//
//              PN15 31-MAR-2004
//              - add a union data structure for all data portion
//
//              HL16 1-April-2004
//                  - add system generated debit adjustment for 
//                      Forfeited Deposit Fee By System
//
//              PW16 6-APRIL-04
//                   - add more data structure to the union data structure
//
//              Huang17 14-APR-2004
//                   - Add a constant for account range change
//
//              FT18    15-APR-2004
//              - add div. type in structure ACU_TRAN_DIV
//                ( meeting & lottery div. will be grouped under PM type)
//
//              FT19    19-APR-2004
//              - add individual code ACU_CODE_CIT_PDRFD for progressive
//                CIT deposit refund and it will use structure ACU_TRAN_CIT 
//                (ACU_CODE_CIT_DEPRFD was used before)
//
//              PN20    29-APR-2004
//              ( add structure to store any miscellaneous transaction
//                from legacy system for database conversion )
//
//              HL21	29-MAY-2004
//              - New set of credit and debit adjustment reason codes
//                from legacy system for database conversion )
//
//              PW22    05-AUG-2004
//              - remove ACU_DEBIT_REV 900 and ACU_CREDIT_CRV 902, use
//                other instead
//
//              RL23    17-AUG-2004
//              - performance improvement.
//                change from 4 to 6 disk blocks for transaction unit
//
#ifndef ACUDEF_H
#define ACUDEF_H

#include <time.h>
#include "udtypedef.h"
#include "betdef.h"
#include "tsndef.h"

#pragma pack(1)

#define ACU_PAN_SIZE       19
#define ACU_BANK_ACN_SIZE  26
#define ACU_BANK_SIZE      3
#define ACU_BRANCH_SIZE    3
#define ACU_BNKACCNUM_SIZE 12

#define ACU_CLUSTER_NUM 25  // no. of account per account cluster (tb_cluster_c)
#define ACU_ACCFIL_NUM 4    // max. no. of acc. packs per Televax (tb_maxpck_c)
#define ACU_ACC_STRVBN 2    // Start vbn of home units

#define ACU_MAX_TRAN   9999 // max. transaction number


struct ACU_PAR
{
  unsigned char   onlWtwMin1:1;  // Enable/disable flag for onlWtwMind
  unsigned char   onlWtwMax1:1;  // Enable/disable flag for onlWtwMaxd
  unsigned char   onlWtwCnt1:1;  // Enable/disable flag for onlWtwCntbu
  unsigned char   cshWtwMax1:1;  // Enable/disable flag for cshWtwMaxd
  unsigned char   cshWtwCnt1:1;  // Enable/disable flag for cshWtwCntbu
  unsigned char   :3;            // unused

  LONGLONG       onlWtwMind;  // Minimum online withdrawal amount in cents (per tran.)
  LONGLONG       onlWtwMaxd;  // Maximum daily online withdrawal amount in cents
  unsigned char  onlWtwCntbu; // Maximum daily online withdrawal count
  LONGLONG       cshWtwMaxd;  // Maximum daily cash withdrawal amount in cents
  unsigned char  cshWtwCntbu; // Maximum daily cash withdrawal count
};

struct ACU_PAN
{
  unsigned char  panTypebu; // pan type
  char           pans[ACU_PAN_SIZE+1];              // pan
};

struct ACU_BANKACCNUM
{
  // char           bankAcns[ACU_BANK_ACN_SIZE+1];  // bank account #
  char           banks[ACU_BANK_SIZE+1];            // bank code
  char           branchs[ACU_BRANCH_SIZE+1];        // branch code
  char           bankAccNums[ACU_BNKACCNUM_SIZE+1]; // bank account #
};

struct ACU_HOME_STR
{
  unsigned int   accountlu; // account #
  LONGLONG       balanced;  // current balance
  LONGLONG       bankgd;    // bank guarantee
  __time32_t         openDate;  // account open date
  __time32_t         lastDate;  // last activity date
  unsigned int   seculu;    // security code
  unsigned char  saluatebu; // salutation
  struct ACU_PAN        pan;    // pan
  struct ACU_BANKACCNUM bank;   // bank account number
  unsigned char  xfrAreabu; // transfer call area
    #define ACU_XFR_NONE        0
    #define ACU_XFR_SERVICE     1
    #define ACU_XFR_ENQUIRY     2
    #define ACU_XFR_ESC_ADMIN   3
    #define ACU_XFR_BOCC        4
    #define ACU_XFR_HOTLINE     5
  unsigned char  langbu;    // language
    #define ACU_LANG_ENGLISH    1
    #define ACU_LANG_MANDARIN   2
    #define ACU_LANG_CANTONESE  3
  unsigned char  statusbu;  // status
    #define ACU_STATUS_NOT_USED  0   // not used [must be 0]
    #define ACU_STATUS_OPEN      1   // open
    #define ACU_STATUS_DORMANT   2   // dormant
    #define ACU_STATUS_FROZEN    3   // frozen
    #define ACU_STATUS_CLOSED    4   // closed
    #define ACU_STATUS_CLSEOD    5   // closed and after eod
    #define ACU_STATUS_MAX       5   // max. status         // CS08
  unsigned char  typebu;    // customer type
    #define ACU_TYPE_NORMAL      0   // normal
    #define ACU_TYPE_KEY         1   // key
    #define ACU_TYPE_SUPER       2   // super-key
    #define ACU_TYPE_LOT         3   // lottery only 
    #define ACU_TYPE_MAX         5
  unsigned char  siWithTypebu;  // si withdrawal type
    #define ACU_SIW_NONE         0
    #define ACU_SIW_CHEQUE       1
    #define ACU_SIW_AUTOPAY      2
  unsigned char  socTypebu; // soccer account type
  unsigned char  bgTypebu;  // bank gaurantee type
  char           surnames[20+1];      // surname
  char           othnames[40+1];      // other name
  char           chisurnames[10+2];   // chinese surname
  char           chiothnames[10+2];   // chinese other name
  struct ACU_PAR par;       // account parameter
  unsigned short   pan1:1;        // pan captured
  unsigned short   bank1:1;       // bank account # entered
  unsigned short   lottery1:1;    // allow lottery selling
  unsigned short   racing1:1;     // allow racing
  unsigned short   soccer1:1;     // allow soccer
  unsigned short   :1;            // filler
  unsigned short   monvoice1:1;   // monitor voice betting access
  unsigned short   escoutstd1:1;  // has esc outstanding transaction flag !FT07
  unsigned short   chgSecu1:1;    // force to change security code
                                // when set, all transction requires security
                                // code match fails, except change security code
  unsigned short   lockVbt1:1;    // reject voice betting terminal access
  unsigned short   pan21:1;       // pan captured
  unsigned short   bank21:1;      // bank account # entered
  unsigned short   pan31:1;       // pan captured
  unsigned short   bank31:1;      // bank account # entered
  unsigned short   :2;            // unused

  struct ACU_PAN        pan2;   // 2nd pan
  struct ACU_BANKACCNUM bank2;  // 2nd bank account number
  struct ACU_PAN        pan3;   // 3rd pan
  struct ACU_BANKACCNUM bank3;  // 3rd bank account number
};
union ACU_HOME
{
  struct ACU_HOME_STR  str;
  char                   b[512];
};
struct ACU_COMMON
{
  unsigned int  blocklu;        // current block number
  unsigned int  prevlu;         // previous unit block number
  unsigned int  nextlu;         // next unit block number
  char          varb[6*512-12]; // variable part
};
struct ACU
{
  union ACU_HOME     home;    // home portion
  struct ACU_COMMON  common;  // common portion
};
struct ACU_TRAN_HDR
{
  unsigned short  sizewu;  // size of transaction
                           // transaction ends with size field
  unsigned short  codewu;  // transaction code, pls update acudatvar.h as well
    #define ACU_CODE_LOT         1  // lottery
    #define ACU_CODE_RAC         2  // racing
    #define ACU_CODE_WTW         3  // withdrawal
    #define ACU_CODE_CAN         4  // cancel
    #define ACU_CODE_SB          5  // soccer bet
    #define ACU_CODE_ACA_CB      6  // CB account access
    #define ACU_CODE_ACA_VOICE   7  // voice account access
    #define ACU_CODE_ACA_CIT     8  // cit account access
    #define ACU_CODE_ACA_MAT     9  // MAT account access
    #define ACU_CODE_ACA_AUTO   10  // auto account access
    #define ACU_CODE_CIT_DEP    11  // CIT/esc deposit
    #define ACU_CODE_CIT_DEPRFD 12  // cit/esc deposit refund
    #define ACU_CODE_CIT_FEE    13  // cit annual fee
    #define ACU_CODE_CIT_FEERFD 14  // cit annual fee refund
    #define ACU_CODE_DEP_TSN    15  // CB deposit with tsn, including payout deposit
    #define ACU_CODE_DEP_ATM    16  // Batch deposit
    #define ACU_CODE_DEP        17  // non-cash deposit [without tsn]
    #define ACU_CODE_HSTACC     18  // history account sod
    #define ACU_CODE_DEBIT      19  // debit adjustment
    #define ACU_CODE_CREDIT     20  // credit adjustment
    #define ACU_CODE_ACR        21  // account release
    #define ACU_CODE_SOD        22  // sod
    #define ACU_CODE_RIM        23  // bank guarantee reimbursement outstanding
    #define ACU_CODE_DIV        24  // dividend settled tonight
    #define ACU_CODE_DIV_PUR    25  // dividend of purged transaction
    #define ACU_CODE_LOT_SI     26  // unsatifised si lottery
    #define ACU_CODE_PANCAP     27  // PAN capture
                                    // same format as ACU_CODE_LOT
    #define ACU_CODE_DFT        28  // dividend forfeited       ! FT03
    #define ACU_CODE_AFR        29  // cit annual fee reverse   ! FT03
    #define ACU_CODE_CHARGE     30  // service charge
    #define ACU_CODE_DIV_OS     31  // dividend from o/s esc transaction
    #define ACU_CODE_STMCHG     32  // statement charge
    #define ACU_CODE_CIT_PDRFD  33  // progressive cit deposit refund !FT19
    #define ACU_CODE_OLDTB      34  // legacy system tranasction    PN20
    #define ACU_CODE_CIT_DEPFFT 35  // CIT/esc deposit forfeit
    #define ACU_CODE_HSTRAC2    36  // tran ACU_CODE_RAC in history file !FT27
                                    //      use structre ACU_TRAN_HSTRAC2
    #define ACU_CODE_DIV_PUR2   37  // purged transaction after Q206

	#define ACU_CODE_LOT2		38  // used by esc
	#define ACU_CODE_RAC2		39  // used by esc
	#define ACU_CODE_SB2		40  // used by esc
	#define ACU_CODE_DEP_TSN2	41  // used by esc
	#define ACU_CODE_HSTRAC3	42  // used by esc

	#define ACU_CODE_AB_LOT_MD	46
    #define ACU_CODE_ESC_LOT_MD	47


  #define ACU_MAX_CODE ACU_CODE_DIV_PUR2                           // FT27

  unsigned short  tranwu:15;    // transaction number
  unsigned short  merge1:1;     // transaction in merge stage
  unsigned LONGLONG txnidd;		// transaction id
  unsigned int bizdatelu;		// business date
};
struct ACU_TRAN_LOT
{
  struct BETABLOT  bet;
};

struct ACU_TRAN_LOT2
{
  unsigned int     content;
  struct BETABLOT  bet;
};

struct ACU_TRAN_RAC
{
  struct BETABRAC  bet;
};

struct ACU_TRAN_RAC2
{
  unsigned int     content;
  struct BETABRAC  bet;
};

// RL26..   FT27..   FT29...
//struct ACU_TRAN_RAC_EXTRA
//{
//  unsigned short   lenwu;
//  unsigned int     lscnlu;      // losing consolation in cents     
//                                // only available when final paid or div cal bit is set.  
  // more attributes can be added here in future
//};    
struct ACU_TRAN_HSTRAC2
{
    struct BETABRAC2           rac2;
//  struct ACU_TRAN_RAC_EXTRA  extra;
//  struct BETABRAC            bet;
};

struct ACU_TRAN_HSTRAC3
{
	unsigned int			   content;
    struct BETABRAC2           rac2;
};

// ..RL26   ..FT27  ...FT29
struct ACU_TRAN_WTW
{
  LONGLONG           amountd;   // amount
  unsigned LONGLONG  chargedu;  // service charge
  unsigned char      typebu;    // withdrawal type  
    #define ACU_WTW_AUTOPAY  1
    #define ACU_WTW_CHEQUE   2
    #define ACU_WTW_BANK     3  // online 
    #define ACU_WTW_CASH     4
	#define ACU_WTW_FPS		 6	//FPS
  unsigned char      actBybu;   // activated by
    #define ACU_WTW_TBTR     1
    #define ACU_WTW_MAT      2
    #define ACU_WTW_SI       3
    #define ACU_WTW_AUTO     4
    #define ACU_WTW_MPT      5
    #define ACU_WTW_CIT      6
    #define ACU_WTW_CB       7
    #define ACU_WTW_ITN      8  // internet
  unsigned char      srcbu;     // source of withdrawal; defined in LOGDEF_AB.H
  unsigned char       cancel1:1; // cancelled
 // unsigned char       ertcaptured1:1; // ERT registration number captured
  unsigned char       csctrn:1;  // Transaction with CSC Card (Added 201108PSR)
  unsigned char       undo :1; //undo added for sp21a
  unsigned char       :5;        // Unused (Changed 201108PSR)
};
struct ACU_TRAN_CAN
{
  unsigned LONGLONG  amountdu;  // cancel amount
  unsigned short     tranwu;    // cancel transaction #
  unsigned char      typebu;    // transaction type
    #define ACU_CAN_RAC      1  // cancel race bet
    #define ACU_CAN_MK6      2  // cancel mark 6
    #define ACU_CAN_GBL      3  // cancel gold ball
    #define ACU_CAN_SB       4  // cancel soccer bet
    #define ACU_CAN_WTW      5  // cancel withdrawal
    #define ACU_CAN_DEP      6  // cancel deposit (up to now, only for AB deposit)

  // RL: these fields are used for catch up cancel after account access catch up.
  // During catch up cancel phase, these indicates where target canncelled
  // transaction is in same/different account unit. Note in this phase, log records
  // are not available.
  unsigned char   filebu;       // file # of account file [0=overflow]
  unsigned int    blocklu;      // block # of account file
  unsigned short  offwu;        // offset to account unit

  unsigned char    canprv1:1;    // cancel earlier call
  unsigned char    otherUnit1:1; // cancel on other unit
  unsigned char    reversed1:1;  // reversed (only for reverse AB deposit)
  unsigned char    spare:5;
};

struct ACU_TRAN_SB
{
  union  TSN      tsn;
  unsigned char   srcbu:7;    // source of sell (Changed 201108PSR)
  unsigned char   csctrn:1;  // Transaction with CSC Card (Added 201108PSR)
  struct BETDATA  bet;
};

struct ACU_TRAN_SB2
{
  union  TSN      tsn;
  unsigned char   srcbu:7;    // source of sell (Changed 201108PSR)
  unsigned char   csctrn:1;  // Transaction with CSC Card (Added 201108PSR)
  struct BETDATA  bet;
};

struct TSB_SB
{
	unsigned __int64 tsnsb;
};

struct ACU_TRAN_ACA
{
  LONGLONG      fundd;    // funds available
  //LONGLONG      bankgd;   // bank guarentee
  LONGLONG		dpflag1 : 1;// bankgd stores dividend pocket (DP) instead of BG   // JC50
  LONGLONG		cscflag1 : 1;// CSC account access                                // CS52
  LONGLONG		ewalletflag1 : 1;// eWallet account access						  //SP21a
  LONGLONG		reserved : 13;                                                    // JC50
  LONGLONG      bankgd : 48;// bank guarentee (BG) or settled divdend pocket (DP) // JC50
  LONGLONG      curDivd;  // unsettled dividend
  LONGLONG      prvDivd;  // previous dividend
  LONGLONG      sbPFtd;   // soccer fo payout forfeited
};

struct LOGAB_FPS_INFO
{
	unsigned int		fpsgwsysid;			//FPS gateway system ID
	LONGLONG			refno;				//Reference No.
	unsigned int		fpsprocessid;		//FPS process ID
	unsigned int		channelid;			//Channel ID
	//char				custname[256];	    //CustomerName
	char				nbano;				//NBA #, 1=primary, 2=secondary
	char				bankcode[4];		//Bank Code
	char				nombankacc[26];		//Nominated bank acc #
	char				actiontype;			//Action, 1=Request, 2=Undo
	char				jsonMsg[700];		//Request message(JSON) from FPS gateway
};

struct ACU_TRAN_ACA_CB
{
  __time32_t               time;      // time
  unsigned short       centrewu;  // centre #
  unsigned short       windowwu;  // window #
  unsigned LONGLONG    escdu;     // esc #
  struct ACU_TRAN_ACA  aca;
};
struct ACU_TRAN_ACA_VOICE
{
  __time32_t               time;      // time
  unsigned int         stafflu;   // staff #
  unsigned short       poswu;     // position #
  unsigned int         recTrklu;  // record track
  struct ACU_TRAN_ACA  aca;
};
struct ACU_TRAN_ACA_CIT
{
  __time32_t               time;      // time
  unsigned int         citlu;     // cit #
  unsigned char        citTypebu; // cit type
    #define ACU_CIT_ITN           1   // internet      
    #define ACU_CIT_CIT3          2   // CIT3
    #define ACU_CIT_CIT3A         3   // CIT3A
    #define ACU_CIT_CIT5          4   // CIT5
    #define ACU_CIT_CIT6          5   // CIT6
    #define ACU_CIT_TWM           6   // TWM
    #define ACU_CIT_PDA           7   // CIT PDA
    #define ACU_CIT_MPB           8   // Mobile betting
    #define ACU_CIT_ESC           9   // ESC
    #define ACU_CIT_CIT8         10   // CIT8
  struct ACU_TRAN_ACA  aca;
};
struct ACU_TRAN_ACA_MAT
{
  __time32_t               time;      // time
  unsigned int         matlu;     // mat #
  unsigned int         recTrklu;  // record track
  unsigned int         stafflu;   // staff #         
  struct ACU_TRAN_ACA  aca;
};
struct ACU_TRAN_ACA_AUTO
{
  __time32_t               time;      // time
  unsigned char        typebu;    // auto account access type
      #define  ACU_AACA_OTH    0  // general auto account access
      #define  ACU_AACA_ATM    1  // ATM auto account access
      #define  ACU_AACA_EOD    2  // EOD auto account access
      #define  ACU_AACA_POL    3  // POL auto account access
  struct ACU_TRAN_ACA  aca;
};
struct ACU_TRAN_CIT    // cit deposit/fee or deposit/fee refund/dep deduct'n/dep forfeit
{
  unsigned LONGLONG    amountdu;   // amount
  unsigned LONGLONG    citdu;      // cit # or esc #
  unsigned char        citTypebu;  // cit type
  char                 remarks[256+1];  // variable length remark field
};
struct ACU_TRAN_DEP
{
  __time32_t             holdtime;      // release time for withdrawal
  unsigned LONGLONG  amountdu;      // amount
  unsigned LONGLONG  chargedu;      // service charge
  unsigned char      typebu;        // deposit type
    #define ACU_DEP_CASH  1
    #define ACU_DEP_CIT   2
    #define ACU_DEP_MPT   3
    #define ACU_DEP_ATM   4
    #define ACU_DEP_PAY   5         // payout deposit
    #define ACU_DEP_CHQ   6         // cheque
    #define ACU_DEP_ITN   7         // internet
	#define ACU_DEP_FPS   22         // FPS
  unsigned char       hold1:1;       // withholdable
  unsigned char       cancel1:1;     // cancelled
  unsigned char       reversed1:1;   // reversed
  unsigned char       released1:1;   // released (ignore hold time)
  //unsigned char       secondnba1:1;   // Transaction on secondary NBA
  //unsigned char       ertregno1:1;   // ERT registration number captured
  unsigned char       csctrn:1;   // Transaction by CSC (Added 201108PSR)
  unsigned char      srcbu;         // source of deposit; defined in LOGDEF_AB.H
};
struct ACU_TRAN_DEP_TSN
{
  union TSN            tsn;
  struct ACU_TRAN_DEP  common;
};
struct ACU_TRAN_DEP_ATM
{
  unsigned char        sysbu;       // System number
  unsigned char        senderbu;    // Sender type: HSBC = 0, EPS = 1, BOC=2
    #define ACU_ATM_SENDER_HSBC     0
    #define ACU_ATM_SENDER_EPS      1
    #define ACU_ATM_SENDER_BOC      2
  unsigned int         batchlu;     // Batch Number
  unsigned int         seqnumlu;    // Input sequence number
  char                 fillerb;     // used
  struct ACU_TRAN_DEP  common;
  __time32_t               caldate;     // calendar date                        // RL24
  unsigned short       bankcodewu;  // bank code                            // RL25
};
struct ACU_TRAN_HSTACC      // account header in history file
{
  LONGLONG       balanced;  // start of day balance
  unsigned int   acclu;     // account number
  __time32_t         openDate;  // account open date
};
struct ACU_TRAN_DRCR        // debit credit adjustmen
{
  unsigned LONGLONG  amountdu;  // amount
  unsigned int       typelu;    // type // KL02 refer to drcrtxndef.h
//HL21...
    #define ACU_DEBIT_CDC	    1   // CASH DEPOSIT CLAIM
    #define ACU_DEBIT_SACCDCS	2   // SUSPENSE A/C TO CASH DEPOSIT 
				                    //	CLAIM SETTLEMENT
    #define ACU_DEBIT_EFTDC	    3   // EFT DEPOSIT CLAIM
    #define ACU_DEBIT_SACEFTDCS	4   // SUSPENSE A/C TO EFT DEPOSIT CLAIM 
				                    //	SETTLEMENT
    #define ACU_DEBIT_DBS	    5   // DEPOSIT BAD SALES
    #define ACU_DEBIT_DSHCQ     6   // DISHONOURED CHEQUE
    #define ACU_DEBIT_RBGIM     7   // REJECTED BG REIMBURSEMENT
    #define ACU_DEBIT_DFCCA	    8   // DEBIT FROM CHEQUE CONTROL ACCOUNT
    #define ACU_DEBIT_DCACWO	9   // DORMANT CONTROL A/C W/OUT
    #define ACU_DEBIT_EWUPS     10  // EFT WITHDRAWAL NOT POSTED
    #define ACU_DEBIT_EWTMO     11  // EFT BANK TIME OUT WITHDRAWAL
    #define ACU_DEBIT_CITWNP	12  // CIT WITHDRAWAL NOT POSTED
    #define ACU_DEBIT_CITBTOW	13  // CIT BANK TIME OUT WITHDRAWAL
    #define ACU_DEBIT_ESCEWNP	14  // ESC EFT WITHDRAWAL NOT POSTED
    #define ACU_DEBIT_ESCEBTO	15  // ESC EFT BANK TIME OUT
    #define ACU_DEBIT_UBSDIV	16  // UBS DIVIDEND
    #define ACU_DEBIT_BOFLTF	17  // BALANCE OVERFLOW TRANSFER
    #define ACU_DEBIT_EACEODR	18  // EMERGENCY A/C EOD REVERSING ENTRY 
				                    //	(RACEDAY ONLY)
    #define ACU_DEBIT_CITAF     19  // CIT ANNUAL FEE
    #define ACU_DEBIT_CITDF	    20  // CIT DEPOSIT FORFEITED
    #define ACU_DEBIT_CITPDAD	21  // CIT / PDA DEPOSIT
    #define ACU_DEBIT_CITRMC	22  // CIT R & M CHARGES
    #define ACU_DEBIT_BCFPDA	23  // BATTERY CHARGES FOR PDA
    #define ACU_DEBIT_DFAFFT	24  // DEBIT GFBC ACCCOUNT FOR FUND TRANSFER
    #define ACU_DEBIT_ESCDF     25  // ESC DEPOSIT FEE
    #define ACU_DEBIT_ESCFDF	26  // ESC FORFEITED DEPOSIT FEE
    #define ACU_DEBIT_BDWRI     27  // BAD DEBT WRITE IN
    #define ACU_DEBIT_SACWO     28  // SUSPENSE A/C WRITE OUT
    #define ACU_DEBIT_OUTDC	    29  // OUTSTANDING DR/CR FOR DORMANT A/C REJ W/D
    #define ACU_DEBIT_DIPFRS	30  // DIVIDEND PROFIT - RS
    #define ACU_DEBIT_DIPFFS	31  // DIVIDEND PROFIT - FS
    #define ACU_DEBIT_DIPFLS	32  // DIVIDEND PROFIT - LS
    #define ACU_DEBIT_REVENT	33  // REVERSING ENTRY
    #define ACU_DEBIT_OTHERS	34  // DEBIT ADJUSTMENT - OTHERS

    #define ACU_CREDIT_CDCTSAC	35  // CREDIT CASH DEPOSIT CLAIM TO 
				                    //	SUSPENSE A/C
    #define ACU_CREDIT_CDCS	    36  // CASH DEPOSIT CLAIM SETTLEMENT
    #define ACU_CREDIT_EFTDCTSA	37  // CREDIT EFT DEPOSIT CLAIM TO SUSPENSE A/C
    #define ACU_CREDIT_EFTDCS	38  // EFT DEPOSIT CLAIM SETTLEMENT
    #define ACU_CREDIT_CQDHOC	39  // CHEQUE DEPOSIT - H.Q. / ON-COURSE
    #define ACU_CREDIT_CDHOC	40  // CASH DEPOSIT - HQ / ON-COURSE
    #define ACU_CREDIT_CCQWD	41  // CANCELLED CHEQUE W/D
    #define ACU_CREDIT_CCQDTAC	42  // CREDIT CHEQUE DEPOSIT TO RELEVANT A/C
    #define ACU_CREDIT_EWUPS    43  // EFT WITHDRAWAL NOT POSTED
    #define ACU_CREDIT_EFTBTOS	44  // EFT BANK TIME OUT SETTLEMENT
    #define ACU_CREDIT_CITDNP	45  // CIT DEPOSIT NOT POSTED
    #define ACU_CREDIT_CITBTOS	46  // CIT BANK TIME OUT SETTLEMENT
    #define ACU_CREDIT_ESCEDNP  47  // ESC EFT DEPOSIT NOT POSTED
    #define ACU_CREDIT_ESCWP	48  // ESC EFT WITHDRAWAL POSTED
    #define ACU_CREDIT_UBSRF	49  // UBS REFUND
    #define ACU_CREDIT_BOFLTF	50  // BALANCE OVERFLOW TRANSFER
    #define ACU_CREDIT_EACSODR	51  // EMERGENCY A/C SOD REVERSING ENTRY 
				                    //	(RACEDAY ONLY)
    #define ACU_CREDIT_CITAFR	52  // CIT ANNUAL FEE REFUND
    #define ACU_CREDIT_RCITD	53  // REINSTATE CIT DEPOSIT
    #define ACU_CREDIT_CITPDADR	54  // CIT / PDA DEPOSIT REFUND
    #define ACU_CREDIT_CITRMCR	55  // CIT R & M CHARGES REFUND
    #define ACU_CREDIT_CITDRP	56  // CIT DEPOSIT REFUND - PROGRESSIVE
    #define ACU_CREDIT_TAFCITD	57  // TRANSFER ADJUSTMENT FOR CIT DEPOSIT
    #define ACU_CREDIT_TADJ	58      // TRANSFER ADJUSTMENT
    #define ACU_CREDIT_ESCDR    59  // ESC DEPOSIT FEE REFUND
    #define ACU_CREDIT_FTTGFBC	60  // FUND TRANSFER TO GFBC ACCOUNT
    #define ACU_CREDIT_BDWRO    61  // BAD DEBT WRITE OUT
    #define ACU_CREDIT_SACWIDC  62  // SUSPENSE A/C WRITE IN - DEPOSIT CLAIM
    #define ACU_CREDIT_SACWICD  63  // SUSPENSE A/C WRITE IN - CIT DEPOSIT
    #define ACU_CREDIT_RWDDAC   64  // REJ. W/D DORMANT A/C
    #define ACU_CREDIT_REJWTW   65  // REJECTED WITHDRAWAL
    #define ACU_CREDIT_RWFCAC	66  // REJECTED WITHDRAWAL FROM CLOSED ACCOUNT
    #define ACU_CREDIT_ABFN	    67  // ABFN
    #define ACU_CREDIT_OCUBRS	68  // OVER COLLATION/UNACTIONED BAD SALES - RS
    #define ACU_CREDIT_OCUBFS	69  // OVER COLLATION/UNACTIONED BAD SALES - FS
    #define ACU_CREDIT_OCUBLS	70  // OVER COLLATION/UNACTIONED BAD SALES - LS
    #define ACU_CREDIT_EXGPRS	71  // EXGRATIA PAYMENT - RS
    #define ACU_CREDIT_EXGPFS	72  // EXGRATIA PAYMENT - FS
    #define ACU_CREDIT_EXGPLS	73  // EXGRATIA PAYMENT - LS
    #define ACU_CREDIT_MBGRIN	74  // MANUAL BG REIMBURSEMENT
    #define ACU_CREDIT_REVENT	75  // REVERSING ENTRY
    #define ACU_CREDIT_OTHERS	76  // CREDIT ADJUSTMENT - OTHERS
    #define ACU_DRCR_MAT_MAX    76  // Max number that Mathndr allows
//...HL21
//HL12...
    #define ACU_CREDIT_XGR      901 // exgratia payment
    #define ACU_CREDIT_AFR      903 // CIT annual fee refund
    #define ACU_DEBIT_NAF       904 // annual fee for new cit type
    #define ACU_CREDIT_AFW      905 // cit annual fee waived
    #define ACU_CREDIT_PDR      906 // progressive deposit refund
// ...HL12

// The following are system generated credit debit adjustment
    #define ACU_CREDIT_FESCB    1000// Balance Transferred From ESC
    #define ACU_DEBIT_TVOIB     1001// Balance Transferred To Voice
    #define ACU_CREDIT_BGRIM    1002// Bank Gaurantee Reimbursement 
    #define ACU_DEBIT_SYSFOFDF  1003// Forfeited Deposit Fee By System //HL16
    #define ACU_DRCR_AUTO_MAX   1003// max. auto drcr tran code !FT13
//...HL09
  char           remarks[50+1];     // remark variable length
};
struct ACU_TRAN_ACR
{
  LONGLONG      fundd;    // funds available
};
struct ACU_TRAN_SOD
{
  __time32_t         date;      // date
  LONGLONG       balanced;  // balance
};
//struct ACU_TRAN_PANCAP      // PAN capture
//{
//  unsigned char  typebu;                // pan type
//  char           pans[ACU_PAN_SIZE];    // pan
//};
struct ACU_TRAN_RIM         // outstanding bank guarantee reimbursement
{
  LONGLONG       amountd;   // amount
  unsigned char  typebu;    // bank guarantee type
  __time32_t         date;      // date of generation
  unsigned int   rej1:1;    // rejected transaction
};
struct ACU_TRAN_DIV
{
  LONGLONG       racingd;   // racing dividend
  LONGLONG       lotteryd;  // lottery dividend
  LONGLONG       soccerd;   // soccer dividend
  LONGLONG       cansid;    // cancelled m6 si
  unsigned char  typebu;    // dividend type
    #define ACU_DIV_MAX     2   // 2 types of div
    #define ACU_DIV_PM      0   // pari-mutual 
    #define ACU_DIV_FO      1   // fixed odds
};
struct ACU_TRAN_DIV_PUR     // dividend for purged transaction
{
  LONGLONG              divd;      // dividend
  unsigned short        tranwu;    // transaction number of purged transaction
  struct ACU_TRAN_SB    det;       // SB tran details   !FT10
};
// FT21...
union ACU_TRAN_PURDET       // purged transaction details
{
    struct ACU_TRAN_SB  sb;         // SB tran details
    struct ACU_TRAN_LOT lot;        // LOT tran details
};
struct ACU_TRAN_DIV_PUR2    // dividend for purged transaction
{
  unsigned LONGLONG     divdu;     // dividend
  unsigned short        tranwu;    // transaction number of purged transaction
  unsigned char         typebu;    // transaction type
    #define ACU_PUR_SB  0               // SB tran
    #define ACU_PUR_LOT 1               // lottery tran
  union ACU_TRAN_PURDET det;       // SB tran details  
};
// ...FT21
struct ACU_TRAN_EXTRA       // extra info for unsettled transaction in
{                           // transaction file
  unsigned char   histFilebu;   // history file number
  unsigned int    histOfflu;    // offset to transaction in history file
  unsigned int    acaOfflu;     // offset of last a/c access in hist file !FT11
};

// FT03...
struct ACU_TRAN_DFT         // dividend forfeited
{
  unsigned LONGLONG  amountdu;  // forfeited amount
};

struct ACU_TRAN_AFR         // cit annual fee reverse
{
  unsigned LONGLONG  amountdu;  // annual fee reversed 
  unsigned char      typebu;    // device type
};
// ...FT03
struct ACU_TRAN_CHG         // service charge
{
  unsigned LONGLONG  chargedu;  // amount
  unsigned short     codewu;    // transaction code
  unsigned char      typebu;    // type (see ACU_WTW_... or ACU_DEP_...)
  unsigned char      actBybu;   // activated by (see ACU_WTW_...)
  unsigned char      wtwdepbu;  // charge type (see AB_WTWDEP_...)
};

struct ACU_TRAN_STMCHG      // statement charge
{
  unsigned LONGLONG  amountdu;  // amount
  __time32_t             fromdate;  // from date
  __time32_t             todate;    // to date
};

// PN20..
struct ACU_TRAN_OLDTB   // legacy tb transaction
{
  unsigned char trcdbu;     // statement transaction code referred to aadef.h
  LONGLONG      amountd;    // transaction amount if required
  char          texts[256]; // description with null terminated
};
// ..PN20

// PN15..
union ACU_TRAN_DATA
{
  struct ACU_TRAN_LOT       lot;
  struct ACU_TRAN_RAC       rac;
  struct ACU_TRAN_WTW       wtw;
  struct ACU_TRAN_CAN       can;
  struct ACU_TRAN_SB        sb;
  struct ACU_TRAN_ACA_CB    acacb;
  struct ACU_TRAN_ACA_VOICE acav;
  struct ACU_TRAN_ACA_CIT   acacit;
  struct ACU_TRAN_ACA_MAT   acam;
  struct ACU_TRAN_ACA_AUTO  acaa;
  struct ACU_TRAN_CIT       citf;
  struct ACU_TRAN_DEP       dep;
  struct ACU_TRAN_DEP_TSN   dept;
  struct ACU_TRAN_DEP_ATM   depa;
  struct ACU_TRAN_HSTACC    hacc;
  struct ACU_TRAN_DRCR      dcr;
  struct ACU_TRAN_ACR       acr;
  struct ACU_TRAN_SOD       sod;
  // struct ACU_TRAN_PANCAP    pan;
  struct ACU_TRAN_RIM       rim;
  struct ACU_TRAN_DIV       div;
  struct ACU_TRAN_DIV_PUR   divp;
  struct ACU_TRAN_DFT       divf;
  struct ACU_TRAN_CHG       chg;
  struct ACU_TRAN_STMCHG    stmc;
  struct ACU_TRAN_AFR       afr;                //PW16
  struct ACU_TRAN_OLDTB     oldtb;              // PN20
  struct ACU_TRAN_HSTRAC2   rac2;               // RL26
  struct ACU_TRAN_DIV_PUR2  pur2;               // FT21
};

struct ACU_TRAN
{
  struct ACU_TRAN_HDR   h;      // transaction header
  union  ACU_TRAN_DATA  d;      // transaction data
  // Following two fields should not be as reference.  We put it here just
  // for the sake for allocate a maximum size of a record in transaction
  // blocks.
  struct ACU_TRAN_EXTRA p;        // previous date
  unsigned short        sizewu;   // trailing size
};
// ..PN15


#define ACU_ACC_UNISIZ      (NUNIT(sizeof(struct ACU),512)) // blocks per a/c
#define ACU_CLUSTER_BLK     (ACU_CLUSTER_NUM * ACU_ACC_UNISIZ)
#define ACU_ACCRNG_UNIT     (ACU_CLUSTER_NUM * ACU_ACCFIL_NUM)      // Huang17
#define ACU_RND_CLUSBLK(n)   (((n) - FILE_DBLK_VBN + ACU_CLUSTER_BLK -1) / \
                             ACU_CLUSTER_BLK * ACU_CLUSTER_BLK + FILE_DBLK_VBN)

#pragma pack()

#endif
