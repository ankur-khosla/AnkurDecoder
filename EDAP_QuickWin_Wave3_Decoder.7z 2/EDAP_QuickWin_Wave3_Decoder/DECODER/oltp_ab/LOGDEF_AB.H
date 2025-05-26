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
//  Function:   Header file for logger record in OLTP-AB.
//
//  Author  :   Edward Hon          Dec-2002
//
//  Mod.    :   FT01                29-JUL-2003
//              - add EOD transaction codes
//
//              VC02                29-JUL-2003
//              - add DEPHNDR log request defines
//
//              FT03                6-NOV-2003
//              - add new EOD transaction codes
// 
//              DJ04                18-20-2003
//              - Delete dup pol codes
//
//              KL05                05-01-2004
//              - Delete LOGAB_BGREINB
//
//              FT06                14-JAN-2004
//              - Replace code LOGAB_CODE_EOD_RCR by LOGAB_CODE_EOD_CR
//              
//              EH07                09-FEB-2004
//              - tidy up eft-gateway related data
//
//              KL08                17-FEB-2004
//              - remove remSizebu from LOGAB_DETCDT
//
//              FT09                17-FEB-2004
//              - delete code LOGAB_CODE_EOD_AFR (reverse cit annual fee)
//              - add code LOGAB_CODE_EOD_DIVOS, LOGAB_CODE_EOD_CANSI
//
//              KL10                04-MAR-2004
//              - New structures and Log code for AA
//
//              HL11                15-JULY-2004
//              - add new logger code account statement request, previously
//                treated as recall
//
//              RL12                07-SEP-2004
//              - ECV feature
//

#ifndef LOGDEF_AB_H
#define LOGDEF_AB_H

#include <time.h>
#include "udtypedef.h"
#include "aadef.h"
#include "acudef.h"
#include "abpoldef.h"
#include "logrdcdef.h"
//#include "logsbcdef.h"
#include "simplesbcdef.h"
#include "logothdef.h"
#include "sblogdef.h"
#include "logdepdef.h"              // VC02
#include "eodtrndef.h"

#pragma pack(1)

#define LOGAB_TRMREQ_MAX    512     // size of terminal request
#define LOGAB_EFTMSG_MAX    1800     // size of eft request/reply


#define DEV_TYP_MPB           1     // MPB (Mobile phone/cit2)
#define DEV_TYP_CIT3          2     // CIT3
#define DEV_TYP_CIT3A         3     // CIT3a
#define DEV_TYP_CIT5          4     // CIT5
#define DEV_TYP_CIT6          5     // CIT6
#define DEV_TYP_TWM           6     // TWM
#define DEV_TYP_CITPDA        7     // CIT PDA
#define DEV_TYP_ESC           8     // ESC
#define DEV_TYP_INET          9     // INTERNET
#define DEV_TYP_CIT8         10     // CIT8
#define DEV_TYP_JCBW         11     // JCBW, Jockey club betting WEB
#define DEV_TYP_AMBS         12     // AMBS, Advance mobile betting service
#define DEV_TYP_WLPDA        13     // WLPDA, Wireless PDA
#define DEV_TYP_IPPHONE      14     // IP-PHONE Q107
#define DEV_TYP_JCBWEKBA     17     // JCBW (eKBA)
#define DEV_TYP_MBSN		 19     // MBSN -->> APINOW
#define DEV_TYP_IOSBS		 20     // iPhone (MSR201103)
#define DEV_TYP_JCMOW		 21     // MOBILE WEB (MSR201103)
#define DEV_TYP_IBT			 22     // IBT (2011IBT)
#define DEV_TYP_AOSBS		 23     // AOSBS (2011NOV)
#define DEV_TYP_APISMC		 24     // APISMC (2011NOV)
#define DEV_TYP_APITD		 25     // APITD (2011NOV)
#define DEV_TYP_IBUT		 26     // IBUT (2013MAR)
#define DEV_TYP_API3HK		 27     // API3HK (2013AUG) -->> APIWC
#define DEV_TYP_IBUA		 28     // IBUA (2014NOV)
#define DEV_TYP_WOSBS		 29     // Window Phone (MSR2015)
#define DEV_TYP_MASBAI		 30		// MASBAI (APR2021)
#define DEV_TYP_MASBAA		 31		// MASBAA (APR2021)


struct LOGAB_SOURCE_VOICE
{
  unsigned char   febu;    // frontend #
  unsigned short  termwu;  // terminal #
  unsigned int    locidlu; // location id
  unsigned char train1 : 1;     // training mode flag RL64
};
struct LOGAB_SOURCE_DID
{
 unsigned int    citlu;     // cit #
  unsigned char   termbu;    // pseudo terminal #
  unsigned char   febu;      // frontend #
  unsigned char   citTypebu; // cit type
};
struct LOGAB_SOURCE_CBBT
{
  //unsigned int    centrelu; 
  unsigned int    centrelu:24;  // centre number (Changed 201108PSR)
  unsigned int    csctrn:1;     // Transaction with CSC Card  (Added 201108PSR)
  unsigned int    ewallettrn : 1;     // eWallet for SP21a
  unsigned int    unused:6;		// Unused  (Added 201108PSR)
  unsigned short  windowwu;  // window number
  unsigned short  ltnwu;     // logical terminal #
  unsigned char   cbbu;      // cb system #
};
struct LOGAB_SOURCE_OLD
{
  unsigned int    centrelu;  // centre number
  unsigned short  windowwu;  // window number
  unsigned short  chanwu;    // channel #
  unsigned char   cbbu;      // cb system #
};
struct LOGAB_SOURCE_POL
{
  unsigned char   filebu;    // file number
  unsigned int    offsetlu;  // offsetlu;
  unsigned int    skpAca1:1; // no auto acc. access generation flag
};
union LOGAB_SOURCE_DATA
{
  struct LOGAB_SOURCE_VOICE  voice;
  struct LOGAB_SOURCE_DID    did;
  unsigned int               matlu;
  struct LOGAB_SOURCE_CBBT   cbBt;
  struct LOGAB_SOURCE_OLD    old;
  unsigned short             tbwu;  // batch deposit
  struct LOGAB_SOURCE_POL    pol;
};
struct LOGAB_SOURCE
{
  unsigned char             srcTypebu;  // source type
    #define LOGAB_SRC_VOICE      1     // voice
    #define LOGAB_SRC_CIT        2     // cit, use LOGAB_SOURCE_DID
    #define LOGAB_SRC_MAT        3     // mat
    #define LOGAB_SRC_CB_BT      4     // cb bt
    #define LOGAB_SRC_EWIN       5     // ewin, use LOGAB_SOURCE_DID
    #define LOGAB_SRC_OLD        6     // old protocol by channel and system
    #define LOGAB_SRC_BAT_DEP    7     // batch deposit - tb #
    #define LOGAB_SRC_EFT_CB     8     // eft from cb, use LOGAB_SOURCE_CBBT
    #define LOGAB_SRC_EFT_CIT    9     // eft from cit, use LOGAB_SOURCE_DID
    #define LOGAB_SRC_SBC       10    // soccer betting control
    #define LOGAB_SRC_AUTO      11    // system generated
    #define LOGAB_SRC_EOD       12    // eod generated
    #define LOGAB_SRC_WC        13    // wagering control
    #define LOGAB_SRC_POL       14    // pre-online
    #define LOGAB_SRC_OPR       15    // operator
    #define LOGAB_SRC_EFT_EWIN  16     // eft from ewin, use LOGAB_SOURCE_DID
    #define LOGAB_SRC_TBASD     17    //  TBASD Added Q407
    #define LOGAB_SRC_EFT_TBASD 18    // TBASD Added Q407
	#define LOGAB_SRC_CB_EWAL   19    // eWallet added for SP21a
	#define LOGAB_SRC_EFT_FPS   20    // FPS added for SP21a
	#define LOGAB_SRC_MAX       29    // max type
  union LOGAB_SOURCE_DATA   data;
};
struct LOGAB_HDR
{
  short                 sizew;          // message size in byte
  unsigned short        codewu;         // message code
// BT transaction
    #define LOGAB_CODE_SGN                1 // sign on
    #define LOGAB_CODE_SGF                2 // sign off
    #define LOGAB_CODE_ACA                3 // account access via voice
    #define LOGAB_CODE_ACR                4 // account release
        // special handling must be taken for operator emergency a/c release
        // for such release:
        // source.srcTypebu = LOGAB_SRC_OPR and source.data = target BT source data
        // target BT source type is stored in log.data.bt.acr.errStrokebu
    #define LOGAB_CODE_WTW                5 // withdrawal
    #define LOGAB_CODE_RAC                6 // racing bet
    #define LOGAB_CODE_LOT                7 // lottery bet
    #define LOGAB_CODE_CAN                8 // cancel
    #define LOGAB_CODE_RCL                9 // recall
    #define LOGAB_CODE_OLS               10 // MAT on-line statement request
    #define LOGAB_CODE_DEP               11 // deposit/deposit cit
    #define LOGAB_CODE_RAC_TOT           12 // racing bet total enquiry
    #define LOGAB_CODE_LOT_TOT           13 // lottery bet total enquiry
    #define LOGAB_CODE_ADTENQ            14 // account detail enquiry
    #define LOGAB_CODE_SB                15 // soccer bet
    #define LOGAB_CODE_SB_ENQ            16 // soccer bet enquiry
//    #define LOGAB_CODE_CARD_REPL         17 // card replace
    #define LOGAB_CODE_ESC_CAN_DEP       17 // esc cancel deposit q407
    #define LOGAB_CODE_CARD_ISSUE        18 // card issue
    #define LOGAB_CODE_CARD_RET          19 // return esc card
    #define LOGAB_CODE_DEVISSUE          20 // device issue
    #define LOGAB_CODE_DEVREPL           21 // device replace
    #define LOGAB_CODE_DEVCAN            22 // device cancel
    #define LOGAB_CODE_BAL               23 // account balance via EFT
    #define LOGAB_CODE_BNKBAL_DID        24 // bank balance via DID
    #define LOGAB_CODE_CV_EFT            25 // cv via EFT
    #define LOGAB_CODE_PANCAP            26 // pan capture
    #define LOGAB_CODE_EFT_LTEST         27 // EFT link test
    #define LOGAB_CODE_EFT_MISC          28 // EFT miscellaneous (EFT Terminal)
    #define LOGAB_CODE_DEPCAN            29 // cancel AB deposit
    #define LOGAB_CODE_REVDEP            30 // reverse AB deposit
    #define LOGAB_CODE_REVDEPCAN         31 // reverse cancel AB deposit
    #define LOGAB_CODE_CHGSCD            32 // BT change security code
    #define LOGAB_CODE_TXNENQ            33 // transaction enquiry (ticket enquiry)
//    #define LOGAB_CODE_RDT               34 // race day table
//    #define LOGAB_CODE_NRDT              35 // new race day table
    #define LOGAB_CODE_AUTHVER           36 // authority verification 
    #define LOGAB_CODE_ACSTATM           37 // BT account statement request // HL11
//    #define LOGAB_CODE_ECV_ISSUE         38 // ECV issue
//    #define LOGAB_CODE_ECV_RET           39 // ECV return
//    #define LOGAB_CODE_ECV_CLSENQ        40 // ECV close enquiry
	#define LOGAB_CODE_ACCT_BAL			 41
	#define LOGAB_CODE_TERM_BET			 42 // Terminate bet
	#define LOGAB_CODE_SMSCHG			 43 // SMS Charge
	#define LOGAB_CODE_SMSCHGRFD		 44
	#define LOGAB_CODE_EFT_ACT			 45 // Q108 ..CH
	#define LOGAB_CODE_EFT_ERT			 46 // Q210 EFT ERT
//    #define LOGAB_CODE_ACA_NBA			 48 // Q210 Account access (with NBA information in logger)
    #define LOGAB_CODE_CSCBAL			 49 // 201108PSR CSC Card BALANCE
    #define LOGAB_CODE_CSCRPL			 50 // 2011IBT CSC Card Replace
    #define LOGAB_CODE_CSCRET			 51 // 2011IBT CSC Card Return

	#define LOGAB_CODE_WTW_EFT_EMV       56 // EFT EMV withdrawal
	#define LOGAB_CODE_DEP_EFT_EMV       57 // EFT EMV depositdeposit cit
	#define LOGAB_CODE_CV_EFT_EMV        58 // CV via EFT EMV
	#define LOGAB_CODE_EFT_EMV_MISC      59 // EFT EMV miscellaneous
	#define LOGAB_CODE_EFT_EMV_ERT       60 // ERT EMV Functions

	#define LOGAB_CODE_STSENQ            98 // Status enquiry
    #define LOGAB_CODE_ILLMSG            99 // illegal message code
// MAT transaction
    #define LOGAB_CODE_ACCOPN           101 // account open
    #define LOGAB_CODE_ACCCLS           102 // account close
    #define LOGAB_CODE_DEBIT            103 // debit
    #define LOGAB_CODE_CREDIT           104 // credit
    #define LOGAB_CODE_ACCUPD           105 // Account Details Update
    #define LOGAB_CODE_CHGSEC           106 // Change of Security Code
    #define LOGAB_CODE_VALBET           107 // Validate Bet
//    #define LOGAB_CODE_UNSATLOTSI       108 // Unsatisfied Lottery SI Posting
    #define LOGAB_CODE_UNSETTXNRET      109 // Unsettled transaction retrieval
//    #define LOGAB_CODE_REJBGREIMB       110 // Rejected Bank Guarantee Reimbursement
    #define LOGAB_CODE_ALLUPEXP         111 // All-up Explosion
    #define LOGAB_CODE_CALTRF           112 // Call Transfer Request
    #define LOGAB_CODE_RELTRM           113 // Release Terminal
    #define LOGAB_CODE_ACCBETPARA       114 // Account Bet Parameter
    #define LOGAB_CODE_BANKGT           115 // Generate Bank Guarantee
    #define LOGAB_CODE_BGREINB          116 // Reimburse bank guarantee request
//    #define LOGAB_CODE_REVANLFEE        117 // Reverse Annual Fee
    #define LOGAB_CODE_RESETPAN         118 // Reset PAN Capature
    #define LOGAB_CODE_FUNDANALY        119 // Account Fund Analysis
    #define LOGAB_CODE_ACCMONITOR       120 // Account monitor
    #define LOGAB_CODE_ACCPARAM         121 // Account parameter
    #define LOGAB_CODE_ACCSTATUS        122 // Account status
    #define LOGAB_CODE_STMCHARGE        123 // Statement charge
    #define LOGAB_CODE_ACCRANGE         124 // Account Range Request
    #define LOGAB_CODE_ACCFBLMT         125 // Account FB Limit // KL10..
    #define LOGAB_CODE_EXTOLS           126 // Extended on-line statement
    #define LOGAB_CODE_EXTALLUPEXP      127 // Extended All-up Explosion // ..KL10
    #define LOGAB_CODE_CHANLOCK         128 // Channel Lock
    
	#define LOGAB_CODE_ACCOPN_NBA       137 // Account open with NBA2 info Q210
    #define LOGAB_CODE_ACCUPD_ERT       138 // Account update wiht ERT info Q210

    #define LOGAB_CODE_CSCISSUE         139 // CSC associate card and open account (2011IBT)

// Control message
    #define LOGAB_CODE_SBC              201 // sb control
    #define LOGAB_CODE_WC               202 // WC messages
    #define LOGAB_CODE_ENABCS           203 // enable/disable bcs service
    #define LOGAB_CODE_BCSCLS           204 // close bcs
    #define LOGAB_CODE_ENASB            205 // enable/disable sb service
    #define LOGAB_CODE_SBCLS            206 // close sb
    #define LOGAB_CODE_ENAEPO           207 // enable EPOST service
    #define LOGAB_CODE_EFTGW            208 // change EFTGW
    #define LOGAB_CODE_LOTWPS           209 // lottery winner pass done
    #define LOGAB_CODE_SYSCLS           210 // system close
    #define LOGAB_CODE_APSDONE          211 // all-up post race pass done
// Batch deposit transaction
    #define LOGAB_CODE_BATDEP           301 // Batch deposit
    #define LOGAB_CODE_BATDEPSUM        302 // Batch deposit summary
// POL
    #define LOGAB_CODE_POL_CKP          401 // pre-online checkpoint request
    #define LOGAB_CODE_POL_BG           402 // change bank gaurantee
    #define LOGAB_CODE_POL_STS          403 // change account status
    #define LOGAB_CODE_POL_LOTACA       404 // s.i. lottery account access
    #define LOGAB_CODE_POL_LOT          405 // s.i. lottery post
    #define LOGAB_CODE_POL_LOTACR       406 // s.i. lottery account release
    #define LOGAB_CODE_POL_WTW          407 // s.i. withdrawal
//    #define LOGAB_CODE_POL_DEP          408 // cheque deposit
    #define LOGAB_CODE_POL_PRGDEPRFD    409 // progressive device deposit refund
    #define LOGAB_CODE_POL_DEPRFD       410 // device deposit refund
    #define LOGAB_CODE_POL_ANLFEEDED    411 // device annual fee deduction
    #define LOGAB_CODE_POL_ANLFEERFD    412 // device annual fee refund
    #define LOGAB_CODE_POL_DEPDED       413 // deposit deduction
    #define LOGAB_CODE_POL_ESCDEPDED    414 // esc deposit deduction
    #define LOGAB_CODE_POL_ESCDEPRFD    415 // esc deposit refund
    #define LOGAB_CODE_POL_DEBIT        416 // pre-online debit
    #define LOGAB_CODE_POL_CREDIT       417 // pre-online credit
    #define LOGAB_CODE_POL_DEPFFT       418 // pre-online cit deposit forfeit
    #define LOGAB_CODE_POL_ESCDEPFFT    419 // pre-online esc deposit forfeit
// EOD  !FT01...
//    #define LOGAB_CODE_EOD_DIV          501 // dividend generated tonight!FT19
    #define LOGAB_CODE_EOD_DIVPUR       502 // dividend purged 
    #define LOGAB_CODE_EOD_DFT          503 // dividend forfeited        !FT03
//    #define LOGAB_CODE_EOD_DIVOS        504 // div from o/s esc tran!FT09 FT19
    #define LOGAB_CODE_EOD_CR           505 // credit adjustment         !FT06
    #define LOGAB_CODE_EOD_CANSI        506 // cancel m6 si              !FT09
    #define LOGAB_CODE_EOD_LOT          507 // settled lottery bet       !FT19
    #define LOGAB_CODE_EOD_RAC2         508 // settled racing bet        !FT19
    #define LOGAB_CODE_EOD_SB           509 // settled SB bet            !FT19
    #define LOGAB_CODE_EOD_DIVPUR2      510 // dividend purged type 2    !FT19
// ... FT01
// Others
    #define LOGAB_CODE_PADDER           999 // padder log record
	#define LOGAB_CODE_OTHER_BASE       50000 // temporary code for C#

	#define LOGAB_CODE_ERR				50001 // code for error message
	#define LOGAB_CODE_SIMPLE_SEL       50002 // code for simple selections
	#define LOGAB_CODE_FILE_HDR		    50003 // code for file_header
	#define LOGAB_CODE_BISC_INTER_CTRL		    50004 // code for bisc_interface_control

  unsigned short        errorwu;        // error code
  unsigned char         trapcodebu;     // Trap message code for BCS
  unsigned int          stafflu;        // staff number
  unsigned int          ltnlu;          // logical terminal number
  unsigned int          acclu;          // account number
  unsigned char         filebu;       // file # of account file [0=overflow]
										// IW2016: log seq will not be supported to 16G to minimize the change
  unsigned int          blocklu;        // block # of account file
	#define LOGAB_EFT_EMV_ACK          1
	#define LOGAB_EFT_EMV_AUTO_REV     2
  unsigned int          overflowlu;     // overflow block # if overflow required
  unsigned short        offwu;          // offset to account unit
  unsigned short        tranwu;         // transaction number
  __time32_t                timelu;         // time
  LONGLONG          lgslu;          // last log sequence
  unsigned int          msnlu;          // msn
  struct LOGAB_SOURCE   source;         // source
  unsigned char         extSysTypebu;   // external request type
    #define LOGAB_EXT_AA           1
    #define LOGAB_EXT_EFT_EGW      2
    #define LOGAB_EXT_EFT_CIT      3
    #define LOGAB_EXT_SB           4
  unsigned short          catchup1:1;     // catch up previous transaction required
                                        // during recovery
  unsigned short          btexc1:1;       // bt exception transaction, do not update
                                        // last activity of corresponding tdtbt
                                        // entry (this include late reply, reverse
                                        // reply, non-msn protect transaction,
                                        // unsolicited transaction done for
                                        // corresponding bt, etc. )
  unsigned short          othsys1:1;      // message to other system
  unsigned short          prelog1:1;      // pre-log
  unsigned short          timeout1:1;     // external request timeout
  unsigned short          laterpy1:1;     // late reply (reverse is required, msnlu
                                        // saves the transaction id to be reversed)
  unsigned short          bcsmsg1:1;      // upadte bcsmsg.dat flag
  unsigned short          rcvmsg1:1;      // update rcvmsg.dat 
  unsigned short          overflow1:1;    // overflow required
  unsigned short          escRel1:1;      // CB local account released flag
  unsigned short          noFlush1:1;     // no need to flush for account release. this
                                        // happens when no solid tran. appended
  unsigned short          train1:1;       // trainning account
  unsigned short          sessionInfo1:1; // account session information appended
  unsigned short          uptacc1:1; // Update account file (2011IBT change)
  unsigned short          anonymous1:1; // Anonymous account (2011IBT change)
  unsigned short          :1;             // unused (2011IBT change)
  unsigned int 			bizdatelu;		// sp3 business date
  unsigned short 		ticketTypewu;	// sp3 ticket type
  LONGLONG				activityIdd;  	// sp3 activity id
  LONGLONG              termSessIdd;    // sp3 terminal session id
  LONGLONG              custSessIdd;	// customer session id
  LONGLONG				txnidd;			// sp3 transaction id
  unsigned short  		txnCodewu;		// sp3 transaction code
  unsigned int          globalltnlu;          // logical terminal number
  LONGLONG              canceltxnidd = 0;   // sp3: transaction Id created by cancellation
};
struct LOGBCSAA                 // BCS-AA system information
{
  unsigned char          disable1:1;     // bcs service is disabled
  unsigned char          :7;             // unused
};
struct LOGAB_ILL                // illegal code
{
  unsigned char     codebu;                     // request code
  unsigned short    sizewu;                     // size of data
  char              datab[LOGAB_TRMREQ_MAX];    // request data
};
struct LOGAB_SGN                // sign-on
{
  unsigned int              passwordlu;         // password
  unsigned char             pwdLenbu;           // password length
  struct LOGBCSAA           bcs;                // bcs info
  struct AA_BCS_BTSGNRPY    rpy;                // bcs reply
};
struct LOGAB_SGF                // sign-off
{
  struct LOGBCSAA   bcs;            // bcs info
		};
struct LOGAB_ACA_NORMAL
{
  LONGLONG              novfodivd;   // novelty bet dividend  (added Q208)
  LONGLONG              novinvd;     // novelty bet investment	(added Q208)
  LONGLONG              sbfodivd;   // soccer fo bet dividend
  LONGLONG              sbinvd;     // soccer bet investment
  LONGLONG              depholdd;   // deposit withheld from withdrawal
  LONGLONG              expd;       // daily expenditure
  LONGLONG				dailyWtwd;  // daily withdrawal amount              // CS52
  LONGLONG              onlWtwd;    // daily online withdrawal amount
  LONGLONG              cshWtwd;    // daily cash withdrawal amount
  unsigned char         wtwbu;		// daily withdrawal count
  unsigned char         onlWtwbu;   // daily online withdrawal count
  unsigned char         cshWtwbu;   // daily cash withdrawal count
  unsigned short        sodTranwu;  // sod transaction #
  struct ACU_TRAN_ACA   tran;
  unsigned int          outstand1:1;    // outstanding transaction flag
  struct ACU_BANKACCNUM	nbaacct1;	//primary nba bank account number	
  unsigned char         nbachannel1;   // primary nba channel activated
  struct ACU_BANKACCNUM	nbaacct2;	//second nba bank account number
  unsigned char         nbachannel2;   // second nba channel activated
};
union LOGAB_ACA_DATA
{
  struct LOGAB_SOURCE       busySrc;    // terminal accessing account for account active error
  struct LOGAB_ACA_NORMAL   normal;     // for okay or other error
};
struct LOGAB_ACA_VOICE
{
  unsigned int          recTrklu;       // recorder track
  unsigned int          seculu;         // security code
  unsigned char          secu1:1;        // security code override
  unsigned char          :7;
};
struct LOGAB_ACA_DID
{
  unsigned char         citbu;          // device type, check DEV_TYP
  unsigned char          oth1:1;         // other cit
  unsigned char          :7;
  unsigned int          seculu;         // security code
};
struct LOGAB_ACA_CB
{
  unsigned LONGLONG     escdu;          // esc #
  unsigned short        rejcodwu;       // CMS reject code
  unsigned char          svt1:1;
  unsigned char          oncourse1:1;
  unsigned char          :6;
};
struct LOGAB_ACA_PINVER   //Account PIN Verification (Added 201108PSR)
{
  unsigned char          balreq:1;		//Bit 0 = Balance required for the reply to caller
  unsigned char          :7;			//Unused
  unsigned int           seculu;        //security code
};
union LOGAB_ACA_DEV             // device info of account access
{
  struct LOGAB_ACA_VOICE    voice;
  struct LOGAB_ACA_DID      did;
  struct LOGAB_ACA_CB       cb;
  struct LOGAB_ACA_PINVER   pinver;  //Account PIN Verification (Added 201108PSR)
};
struct LOGAB_ACA
{
  unsigned char         reqfromchannel:1;  // Q210 request from channel
  union LOGAB_ACA_DEV   dev;            // device specific info.
  union LOGAB_ACA_DATA  data;
};
struct LOGAB_ACR                // account release
{
  unsigned short        keyStrokewu;    // key stroke count
  unsigned char         errStrokebu;    // error stroke count
  unsigned char         relcodbu;       // release code
    #define ACR_CODE_NONESC     0       // non ESC account release
    #define ACR_CODE_CRDRM      2       // initiated by terminal due to card removal
    #define ACR_CODE_EFTTO      3       // initiated by terminal due to timeout or unposted
    #define ACR_CODE_ATREL      4       // CB-AT requests the a/c release
    #define ACR_CODE_EMERG    100       // Emergency account release
  LONGLONG              bankgd;         // bank guarentee
  LONGLONG              curDivd;        // unsettled dividend
  LONGLONG              sbPFtd;         // soccer fo payout forfeited
  struct ACU_TRAN_ACR   tran;
  LONGLONG              divBal;     // Dividend pocket balance for IBT anonymous a/c (In cents <settle + unsettle>) 2011IBT
};
struct LOGAB_RCL_STA
{
  __time32_t                date;       // date - statement start
  unsigned int          acclu;      // account #
  unsigned int          trnbitmap;  // Transaction Filter Bitmap (Added 201108PSR)  (No Decode Yet)
};
struct LOGAB_RCL_INF
{
  unsigned int          blocklu;    // block #
  unsigned short        blkOffwu;   // block offset
  unsigned short        trnOffwu;   // transaction offset
  unsigned short        filewu;     // file #
  unsigned int          trnbitmap;  // Transaction Filter Bitmap (Added 201108PSR)  (No Decode Yet)
};
struct LOGAB_RCL_TXN  //Recall transaction (Added 201108PSR)
{
  unsigned short        tranwu;   // Transaction number
  unsigned int          token;   // Continuation token
};
union LOGAB_RCL_DATA            // request specific recall data
{
  struct LOGAB_RCL_STA  rstaSta;    // statement start
  struct LOGAB_RCL_INF  rstaCon;    // statement continue
  struct LOGAB_RCL_TXN  rstaTxn;	// Recall transaction (Added 201108PSR)
  //unsigned short        tranwu;     // transaction number - recall continue (Removed from 201108PSR)
};
struct LOGAB_RCL
{
  unsigned char         typebu;     // recall type
    #define LOGAB_RCL_START   1     // recall start - no specific data
    #define LOGAB_RCL_CON     2     // recall continue
    #define LOGAB_RSTA_STA    3     // statement start
    #define LOGAB_RSTA_CON    4     // statement continue
  union LOGAB_RCL_DATA  data;       // request specific data
  //struct LOGAB_RCL_INF  start;      // points to start of current recall, (Removed from 201108PSR)
};

struct LOGAB_EPS_CIT            // account related info in cit tran
{
  unsigned char         epinbu[8];  // epin
  unsigned char         ektbu[27];   // ekt
  unsigned char         msnbu;      // cit msn
  unsigned int          citlu;      // cit #
};
                                                                  // EH07...
struct LOGAB_EPS_EFT            // account related info in eft tran
{
  unsigned int          seculu;     // security code
  unsigned char         esc1:1;     // ESC EFT transaction
  struct ACU_TRAN_ACA   aca;        // account access information
};

union LOGAB_EPS_ACC                 // account/CIT related info
{
    struct LOGAB_EPS_CIT    cit;    // cit transaction
    struct LOGAB_EPS_EFT    eft;    // eft transaction from cb
};

struct LOGAB_EPS_EGW            // gateway information
{
  unsigned int          gtwmsnlu;                   // eft channel msn
  unsigned short        psuedowu;                   // EPSCO psuedo channel #
  unsigned short        epsretwu;                   // EPSCO return code
  unsigned short        eftSizewu;                  // size of eft portion
  unsigned char         chanbu;                     // eft channel #
  unsigned char         subCodebu;                  // eft sub-code from terminal
  unsigned char			eftPinbu:1;					// eft pin		-- Q405
  unsigned char			DESFlagbu:1;				// 3DES Flag	-- Q107
  unsigned char			reqfromchannel:1;			// Q210 request from channel
  unsigned char			regnocapture:1;				// registration number to be captured
  unsigned char			indnba:1;					// indicate bacnk number below is NBA
  unsigned char			chipcard1:1;				// indicate EMV Chip card
  unsigned char			fallback1:1;				// indicate EMV fallback
  unsigned char			reversal1:1;				// indicate EMV reversal
  unsigned char			eftFlagbu;					// eft flag		-- Q405 1 - bank pin, 2 - ATM pin
  char					eftAccNo[12];				// eft account no. -- Q405
  char                  isnb[6];                    // ISN
  unsigned char			nbano;						// NBA # 1=Pri, 2=Sec Q210

  char                  banks[ACU_BANK_SIZE+1];     // bank code
  char                  nbab[ACU_BANK_ACN_SIZE];    // nominated bank acc #
  __time32_t				acttime;					// filler
  char                  eftb[LOGAB_EFTMSG_MAX];     // variable eft request/reply
};

struct LOGAB_EPS_TB             // epsco info involving account/CIT
{
  union LOGAB_EPS_ACC   acc;        // account related info
  struct LOGAB_EPS_EGW  egw;        // eft gateway info [omitted if no
};                                  // transmission to eft gateway]
                                                                   //...EH07
struct LOGAB_TB_DEP
{
  union TSN             tsn;        // TSN
  struct ACU_TRAN_ACA   aca;        // account access information    
};

struct LOGAB_FPS
{
	struct ACU_TRAN_ACA aca;
	struct LOGAB_FPS_INFO fpsinf;
};

union LOGAB_DEP_DATA
{
  struct LOGAB_EPS_TB   eps;        // epsco info.
  struct LOGAB_TB_DEP   tb;
  struct LOGAB_FPS		fps;		//FPS
};

struct LOGAB_DEP
{
  struct ACU_TRAN_DEP   tran;       // transaction in account file
  union LOGAB_DEP_DATA  data;       // deposit detail
};

//2011IBT changes.
struct LOGABRAC_BET_UPD
{
	unsigned int				offsetlu;   //offset of bet in file		
	unsigned int				tranamt;    //Transferred amount (In cents) (201108PSR - changed from short to int)
};

//Q308 changes.
//2011IBT change the name (LOGAB_ERROR_INFO --> LOGABRAC_BET_ERR)
struct LOGABRAC_BET_ERR
{
	unsigned int	   minbettot;      // Minimum bet total in cents on error "total min. investment not met"    
	unsigned char      racebu;     // error race number
    unsigned char      selbu;      // error selection
};

union LOGABRAC_BET_INFO
{
	struct LOGABRAC_BET_UPD		raceinfo;   // Race Sell Bet info (2011IBT Changes)
	struct LOGABRAC_BET_ERR		errorinfo;	// error info  
};

struct LOGAB_RAC
{
  union LOGABRAC_BET_INFO betinfo;
  unsigned short        indexwu;    // meeting index
  unsigned char			crossSellFl:1; // cross sell indicator
  unsigned char			:7;
  struct ACU_TRAN_RAC2   tran;
};
struct LOGAB_LOT
{
  unsigned short        indexwu;    // lottery index
  unsigned char			ndrawbu;		// number of draw
  unsigned short        selwu;      // error selection
  unsigned char			versionbu;	// version number
  unsigned int          offsetlu;   // offset of bet in file
  unsigned char			multidraw:1;  // multi-draw flag q207
  unsigned char			crossSellFl:1;  // cross sell indicator 
  unsigned char			test:6;
  unsigned int          mintktcost;   // (201108PSR, Reject=min total ticket;Success=Transfer Amt;Other Situation=0)
  struct ACU_TRAN_LOT2   tran;
};

struct LOGAB_WTW
{   
  struct ACU_TRAN_WTW   tran;       // withdrawal transaction in account file
  union {
	  struct LOGAB_EPS_TB   eps;      // eps information                 // EH07
	  struct LOGAB_FPS		fps;		// FPS
	  unsigned int			divprocddtlu;  // Amount in dollar deducted from dividend pocket;0=normal a/c> 0 for IBT anonymous a / c only
  };
};
struct LOGAB_SBMSG
{
  unsigned int		minTktTot;                   // Q310 Minimun Ticket Total 
  unsigned short        lenwu;                      // terminal data length
  unsigned char         trmDatabu[450];  // terminal data [variable]
};
struct LOGAB_SBBET
{
  unsigned short          oddOut1:1;      // odds outdated
  unsigned short          woodds1:1;      // selling without odds
  unsigned short          bonus1:1;       // bonus flag
  unsigned short          rconfirm1:1;    // require confirm by customer
  unsigned short          chgodds1:1;     // odds changed
  unsigned short          chgubet1:1;     // unit bet changed
  unsigned short          intercept1:1;   // bet intercept at rm
  unsigned short          settle1:1;      // bet settled with SB
  unsigned short          abort1:1;       // user abort request recieved
  unsigned short          confirm1:1;     // user confirmed request
  unsigned short		  crossSellFl:1; // cross sell indicator
  unsigned short          :5;
  struct SBLOG_BET_ERR  err;            // sb account type for some error (Reviewed 201108PSR)
  unsigned char         sbtypbu;        // sb account type
  unsigned char			sbmsgver;		// sb message version no.	Q405
  unsigned short        lenwu;          // sb bet size
  struct ACU_TRAN_SB2    tran;
};
union LOGAB_SB
{
  struct LOGAB_SBMSG   msg;         // terminal message
  struct LOGAB_SBBET   bet;         // reply
};
union LOGAB_CAN_DATA
{
  struct LOGAB_LOT    lot;
  struct LOGAB_RAC    rac;
  struct LOGAB_WTW    wtw;
  union  LOGAB_SB     sb;
  struct LOGAB_DEP    dep;
};
struct LOGAB_CAN
{
  unsigned short        tranwu;         // cancelled transaction number
  unsigned short        codewu;         // cancelled transaction code ACU_CODE_...
  unsigned char         filebu;         // file # of account file [0=overflow]
  unsigned int          blocklu;        // block # of account file
  unsigned short        offwu;          // offset to account unit
  LONGLONG				rcltokend;		// token obtain from recall for cancel

  //unsigned int			token;			// q207
  __time32_t				businessDate;	// q207

  unsigned char         otherUnit1:1;   // cancel on other unit
  unsigned char         canprv1:1;      // cancel earlier call
  unsigned char         byTsn1:1;       // cancel by TSN (ESC mode only)
  unsigned char			canPrevDay:1;	// cancel previous day q207
  LONGLONG				txnidd;			// SP3:cancelled transaction id
  unsigned int			verifierlu;		// SP3: segregate from block / offset

  union LOGAB_CAN_DATA  data;
};
struct LOGAB_CVI                // CV issue via EFT
{
  unsigned int          amountlu;       // amount in cents
  struct LOGAB_EPS_EGW  eps;                                        // EH07
};
struct LOGAB_EFT_MISC           // miscellaneous EFT activity
{
// unsigned char                 nbano;      // NBA number 1=pri, 2=sec
//  unsigned char         regno1:1;      // registration number to be captured
  struct LOGAB_EPS_CIT   cit;
  struct LOGAB_EPS_EGW   eps;                                       // EH07
};
struct LOGAB_PANCAP
{
  unsigned char  typebu;                // pan type
  char           pans[ACU_PAN_SIZE];    // pan
};
struct LOGAB_ACCBAL             // account balance via EFT, PAN capture
{
  struct LOGAB_PANCAP       pancap;
  struct LOGAB_EPS_EFT      eft;                                    // EH07
  unsigned char             chanbu;     // eft chanel #             // EH07
  unsigned int              gtwmsnlu;   // gateway msn
};

struct LOGAB_TERMBET             // account balance via EFT, PAN capture
{
  unsigned short			termTranNo;		// terminated transaction no
  unsigned short			termTranCode;	// terminated transaction no
  unsigned char				acctFileNo;		// 
  unsigned int				acctBlkNo;		// 
  unsigned short			offset;			// 
  LONGLONG				token;			// token
  unsigned __int64			dividend;		// dividend paid at termination
  unsigned __int64			refund;			// refund paid at termination
  unsigned __int64			forfSbDiv;		// forfeited sb dividend
  __time32_t					businessDate;	// 
  unsigned char             termOtherUnit:1; // 1 - terminate previous date
  unsigned char             termPrevDate:1;  // 1 - terminate previous date
  unsigned char				:7;				 // unused
  struct LOGAB_SBBET		sbbet;
};
struct LOGAB_SMSCHG             // account balance via EFT, PAN capture
{
  //unsigned int				amount;		// Amount  (Changed at 2011IBT)
  //unsigned int				nouse;		//  MAR2011 skipped  (Changed at 2011IBT)
  unsigned int				amount;		// Amount(In cents) (Changed at 2011IBT)
  BOOL						version;    // New version	0 = FALSE 1 = TRUE (Changed at 2011IBT)
  char						nouse[3];	// unused (Changed at 2011IBT)
  unsigned short			reasonCode;	// Reason of charge
  LONGLONG				    amt;  //Amount in cents. Anonymous acc only (201108PSR)
};

struct LOGAB_EFT_ACC_ACT            // eft activation q108
{
  unsigned int				acctNo;		// account number 
  struct BCS_DATE			activateDate;	// activation date
  struct ACU_BANKACCNUM		nbaacct;	//primary nba bank account number	
  unsigned char				request:1;			// Q210 request from channel
  unsigned char				regno:1;			// registration number
  char						eftRegNo[13];		// eft registration no. 
};

struct LOGAB_EFT_LTEST      // link test request on EFT channel
{
  unsigned char     chanbu;
  unsigned int      gtwmsnlu;
};

struct LOGAB_NBA_INFO
{
  unsigned char				nbatype;		// NBA type1=pri,2=sec
  struct ACU_BANKACCNUM		nbaacct;		// nba bank account number	
  unsigned char				channeltype;	// channel type (pin type) 0=no channel,1=IS,2=TB,3=BOTH
  char						RegNo[13];		// registration no. 

};

//Q210 EFT change
struct LOGAB_EFT_ERT      
{
  struct LOGAB_NBA_INFO	nbainfo1;	//nba bank info 1
  struct LOGAB_NBA_INFO	nbainfo2;	//nba bank info 2	
  unsigned char			clearreg:1;   // registration nuber in databse to be cleared
  unsigned char			nba1status;   // primary nba status
  unsigned char			nba2status;   // secondary nba status
  struct LOGAB_EPS_TB	epstb;	//EPS information	
};

// CSC Card Balance (201108PSR)
struct LOGAB_CSCBAL
{
  struct ACU_TRAN_ACA   tran;   //Account Access details
  unsigned char			lang;   //Language
  unsigned char			calltran;   //Call transfer (0=FALSE 1=TRUE)
  unsigned char			acctype;   //FB account type
  LONGLONG				amt;    //Current day expenditure amount (In cents)
  LONGLONG				div;    //Total dividend (In cents)
  unsigned char         staffbet:1;    // staff betting a/c
  unsigned char         :7;    // not used
  //struct LOGAB_SOURCE   source;  //This is for error only; no need to deocde for 201108PSR
};


// CSC Card Replace (2011IBT)
struct LOGAB_CSCRPL
{
  struct ACU_TRAN_ACA   tran;   //Account Access details
  //struct LOGAB_SOURCE   source;  //This is for error only; no need to deocde for 2011IBT
  struct AA_OLTP_CSCRPLREQ   req;  //CSC Card Replace Request
  struct LOGBCSAA           bcs;  // bcs info
  struct AA_OLTP_CSCRPLRPY rpy;  //CSC Card Replace Reply
};

// CSC Card Return (2011IBT)
struct LOGAB_CSCRET     
{
  struct ACU_TRAN_ACA   tran;   //Account Access details
  unsigned char			wdtype;   // Withdrawal type
  struct AA_OLTP_CSCRETREQ   req;  //CSC Card Return Request
  struct LOGBCSAA           bcs;  // bcs info
  struct AA_OLTP_CSCRETRPY rpy;  //CSC Card Return Reply
};

struct LOGAB_ADTLENQ        // account detail enquiry
{
  unsigned char             reqtypebu;  // request type
    #define ADTLENQ_ID      1           // id
    #define ADTLENQ_SEXNAME 2           // sex and name
    #define ADTLENQ_ECVFEE  3           // ECV deposit fee
  struct LOGBCSAA           bcs;        // bcs info
  union AA_BCS_ACCDETRPY    rpy;        // BCS-AA reply
};
struct LOGAB_DEVISS         // device issue
{
  unsigned int                  seculu;     // security code
  unsigned char                 devbu;      // device type, check DEV_TYP

  unsigned char                 ver1:1;  // Q210 - Q309 version 
  
  unsigned LONGLONG             devdu;      // device #
  unsigned char                 verbu;      // cit version (ascii)
  struct ACU_TRAN_ACA           tran;
  struct LOGBCSAA               bcs;        // bcs info
  struct AA_BCS_DEVISSUERPY     rpy;        // reply
};
struct LOGAB_DEVREPL        // device replace
{
  unsigned int                  seculu;     // security code
  unsigned char                 olddevbu;   // old device type, check DEV_TYP
  unsigned char                  olddevver1:1;  // old device Q309 version
  unsigned LONGLONG             olddevdu;   // old device #
  unsigned char                 newdevbu;   // new device type, check DEV_TYP
  unsigned char                  newdevver1:1;  // old device Q309 version
  unsigned LONGLONG             newdevdu;   // new device #
  unsigned char                 newverbu;   // new cit version (ascii)
  unsigned char                  upddep1:1;  // update deposit
  unsigned char                  fordep1:1;  // forfeit deposit
  unsigned char                  versecu1:1; // verify security code
  unsigned char                  :5;         // unused
  struct ACU_TRAN_ACA           tran;
  struct LOGBCSAA               bcs;        // bcs info
  struct AA_BCS_DEVREPRPY       rpy;        // reply
};
struct LOGAB_DEVCAN         // device cancel
{
  unsigned char                 devbu;      // device type, check DEV_TYP
  unsigned char                  ver1:1;  // Q309 version - Q210 
  unsigned LONGLONG             devdu;      // device #
  unsigned char                  fordep1:1;  // forfeit deposit
  unsigned char                  :7;         // unused
  struct ACU_TRAN_ACA           tran;
  struct LOGBCSAA               bcs;        // bcs info
  struct AA_BCS_DEVCANRPY       rpy;        // reply
};
struct LOGAB_CARDISS        // issue esc card
{
  char                          cusidb[20]; // customer id
  unsigned int                  seculu;     // security code
  unsigned char                 wavflg1:1;  // waive card deposit fee flag
  unsigned char                 withHold1:1;  // witholdable
  unsigned char                 :6;			  // unused
  __time32_t						reltime;
  unsigned LONGLONG             escdu;      // esc card #
  unsigned LONGLONG             depAmtdu;   // deposit amount
  struct ACU_TRAN_ACA           tran;
  struct LOGBCSAA               bcs;        // bcs info
  struct AA_BCS_DEVISSUERPY     rpy;        // reply
};
struct LOGAB_CARDREPL       // replace esc card
{
  unsigned LONGLONG             oldEscdu;   // old esc card #
  unsigned LONGLONG             newEscdu;   // new esc card number
  char                          cusidb[20]; // customer id.
  unsigned int                  seculu;     // security code
  unsigned char                 fordep1:1;  // forfeit deposit flag [0=no forfeit]
  unsigned char                 wavdep1:1;  // wavie deposit flag [0=not waive]
  struct ACU_TRAN_ACA           tran;
  struct LOGBCSAA               bcs;        // bcs info
  struct AA_BCS_DEVREPRPY       rpy;        // reply
};
struct LOGAB_CARDRET        // return esc card
{
  char                      cusidb[20];     // customer id.
  unsigned char             fordep1:1;      // forfeit deposit flag [0=no forfeit]
  unsigned LONGLONG         escdu;          // esc card #
  struct LOGBCSAA           bcs;            // bcs info
  struct AA_BCS_DEVCANRPY   rpy;            // reply
};
struct LOGAB_ECVISS         // ECV issue
{
  unsigned LONGLONG         escdu;              // ECV card #
  unsigned LONGLONG         depAmtdu;           // deposit amount for opening balance
  unsigned char             accTypebu;          // account type (0=named account,1=anonymous)
  unsigned char             langbu;             // language (see acudef.h)
  char                      cusidb[20];         // customer id.
  char                      surnames[20+1];     // surname
  char                      othnames[40+1];     // other name
  char                      addrs[120+1];       // address
  char                      phones[2][20+1];    // phone #
  char                      sexb;               // 'F' / 'M'
  char                      locationb;          // location
  unsigned int              wavflg1:1;          // waive card deposit fee flag
  struct BCS_DATE           dob;                // date of birth
  struct LOGBCSAA           bcs;                // bcs info
  struct AA_BCS_ECVCARDISSRPY   rpy;            // reply
};
struct LOGAB_ECVRET         // ECV return
{
  unsigned LONGLONG         escdu;              // esc card #
  unsigned LONGLONG         wtwAmtdu;           // withdrawal amount
  unsigned int              depRfdlu;           // deposit refund amount
  unsigned char             wtwTypebu;          // withdrawal type
  char                      cusidb[20];         // customer id.
  char                      reasons[30+1];      // reason
  unsigned int              fordep1:1;          // forfeit deposit flag [0=no forfeit]
  struct ACU_TRAN_ACA       tran;
  struct LOGBCSAA           bcs;                // bcs info
  struct AA_BCS_ECVCARDCANRPY   rpy;            // reply
};
struct LOGAB_ECVCLSENQ      // ECV close enquiry
{
  unsigned LONGLONG         escdu;              // esc card #
  unsigned char             accStatusbu;        // account status
  unsigned int              outstand1:1;        // outstanding transaction flag
  struct LOGAB_ADTLENQ      enq;                // account detail enquiry
};
struct LOGAB_CHGSCD         // bt charge security code
{
  char                      cusidb[20];     // customer id.
  unsigned int              oldSeculu;      // old security code
  unsigned int              newSeculu;      // new security code
  struct LOGBCSAA           bcs;            // bcs info
  struct AA_BCS_CHGSECRPY   rpy;            // reply
};
struct LOGAB_AUTHVER        // authority verification 
{
  unsigned int      stafflu;            // staff to verify
  unsigned int      passwordlu;         // password
  unsigned char     pwdLenbu;           // password length
  unsigned char     funcCodebu;         // function code
    #define AUTHVER_CODE_BET_SELL     1     // large bet selling
  struct LOGBCSAA   bcs;                // bcs info
};
struct LOGAB_DEPATM         // batch deposit
{
  union  LOGDEP         data;
  struct ACU_TRAN_ACA   tran;
};
struct LOGAB_TXNENQ
{
    char                termtypeb;
    unsigned short      tranwu;
	LONGLONG			tokend;	// token of the retrieved transaction
    unsigned short      lenwu;
    char                bufb[512];
};

// MAT transaction
struct LOGAB_ACCBETPARA     // Account Bet Parameter
{
    struct AA_BCS_ACCBETPARA    req;
};
union LOGAB_ACCCLSRPY
{
    struct ACU_TRAN_ACA         tran;
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_ACCCLS         // account close
{
    struct AA_BCS_ACCCLSREQ     req;        // Account close request
    // fill in by BTHNDR
    union LOGAB_ACCCLSRPY       rpy;
};
struct LOGAB_ACCFBLMT       // Account FB Limit // KL10
{
    struct AA_BCS_ACCFBLMTREQ   req;
    // fill in by MATHNDR
    struct AA_OLTP_ACCFBLMTRPY  rpy;
};
union LOGAB_ACCFUNDRPY
{
    struct AA_OLTP_ACCFUNDRPY   rpy;
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_ACCFUND        // Account Fund Analysis
{
    struct AA_BCS_ACCFUNDREQ    req;
    // fill in by BTHNDR
    union LOGAB_ACCFUNDRPY      rpy;
};
union LOGAB_ACCUPDRPY
{
    struct AA_BCS_ACCUPDRPY     rpy;        // Account Details Update reply
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_ACCUPD         // Account Details Update (before Q210)
{
    struct AA_BCS_ACCUPDREQ     req;        // Account Details Update request
    // fill in by BTHNDR
    union LOGAB_ACCUPDRPY       rpy;        // reply
};
struct LOGAB_ACCUPDNEW         // Account Details Update (after Q210)
{
    struct AA_BCS_ACUNEWREQ     req;        // Account Details Update request
    // fill in by BTHNDR
    union LOGAB_ACCUPDRPY       rpy;        // reply
};

struct LOGAB_ACCOPEN        // Account Open Request  (Q210)
{
    struct AA_BCS_ACCOPENREQ    req;
};

struct LOGAB_ACCOPENNEW        // Account Open Request  (Q210)
{
    struct AA_BCS_ACONEWREQ    req;
};


struct LOGAB_ACCPARA        // Account parameter
{
    struct AA_BCS_ACCPARAREQ    req;
    // fill in by BTHNDR
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_ALLUPEXP       // All-up Explosion
{
    struct AA_BCS_ALLUPEXPREQ   req;
};
struct LOGAB_BANKGT         // Generate Bank Guarantee
{
    struct AA_BCS_BANKGT        req;
};
struct LOGAB_CALTRF         // Call Transfer Request
{
    struct AA_BCS_CALTRFREQ     req;
    // fill in by BTHNDR on error
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_CHANLOCK       // Channel lock
{
    struct AA_BCS_CHANLOCKREQ   req;
    // fill in by BTHNDR
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_CHGACCSTATUS   // Change of Account Status
{
    struct AA_BCS_NEWACCSTATUSREQ   req;
    // fill in by BTHNDR
    unsigned char                reopen1:1;
    unsigned char                :7;
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_CHGSEC         // Change security code
{
    struct AA_BCS_CHGSECREQ     req;
    // fill in by BTHNDR on error
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
union LOGAB_DETCDTRPY
{
    struct ACU_TRAN_ACA     tran;
    struct LOGAB_SOURCE     busySrc;        // terminal accessing account for account active error
};
struct LOGAB_DETCDT         // debit/credit adjustment
{
    struct AA_BCS_DETCDTREQ  req;           // debit/credit adjustment request
    // fill in by BTHNDR
	LONGLONG				 amt;  //Amount in cents. Anonymous acc only (201108PSR)
    union LOGAB_DETCDTRPY    rpy;
};
struct LOGAB_FORACCREL      // Forced Account Release
{
    struct AA_BCS_FORACCRELREQ  req;
};
struct LOGAB_MONIACC        // Monitor account
{
    struct AA_BCS_MONIACCREQ    req;
    // fill in by BTHNDR
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_OLSTAT         // Online statement
{
    struct AA_BCS_OLSTATREQ     req;
};
struct LOGAB_REJBGR         // Rejected Bank Guarantee Reimbursement
{
    struct AA_BCS_REJBGREIMBREQ     req;
    // fill in by BTHNDR
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_RELTRM         // Release Terminal
{
    struct AA_BCS_RELTERMREQ    req;        // Release Terminal request
    // following is filled in by BTHNDR
    int                         ltnl;       // logical terminal # of BT (-1 => no such terminal)
    unsigned int                stafflu;    // staff on released terminal
    LONGLONG                    bankgd;     // bank guarentee
    LONGLONG                    curDivd;    // unsettled dividend
    LONGLONG                    sbPFtd;     // soccer fo payout forfeited
    struct ACU_TRAN_ACR         tran;       // fund available at time of release
    LONGLONG                    divBal;     // Dividend pocket balance for IBT anonymous a/c (in cents) 2011IBT
};
struct LOGAB_RESETPAN       // Reset PAN Capture
{
    struct AA_BCS_RESETPANREQ   req;
    // fill in by BTHNDR
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_REVANLFEE      // Reverse Annual Fee
{
    struct AA_BCS_REVANLFEE     req;
};
union LOGAB_STMCHGRPY
{
    struct ACU_TRAN_ACA         tran;
    struct LOGAB_SOURCE         busySrc;    // terminal accessing account for account active error
};
struct LOGAB_STMCHG         // Statement charge
{
    struct AA_BCS_STMCHRGREQ    req;        // Statement charge request
    // fill in by BTHNDR
	LONGLONG				    amt;  //Amount in cents. Anonymous acc only (201108PSR)
    union LOGAB_STMCHGRPY       rpy;
};
struct LOGAB_UNSETTXNRET    // Unsettled transaction retrieval
{
    struct AA_BCS_UNSETTXNRETREQ    req;
};
union LOGAB_VALBET          // Validat Bet
{
    struct AA_BCS_VALBETREQ     req;        // Validate Bet request
    struct BETDATA              bet;        // result if okay
};
struct LOGAB_BGREINB        // Credit Bank Guarantee Reimbursement
{
    struct AA_BCS_BGREINB  req;         // Credit Bank Guarantee Reimbursement
    unsigned char          entryb;      // update entry
};
//struct LOGAB_UNSATLOTSI     // Unsatisfied Lottery SI Posting
//{
//    struct AA_BCS_UNSATLOTSIREQ  req;
//};
struct LOGAB_CSCISS        // CSC Card Issue (2011IBT)
{
    struct AA_BCS_CSCISSREQ  req;         
};

union LOGAT_AB
{
    struct LOGAB_ACCBETPARA     accbetpara;     // Account Bet Parameter
    struct LOGAB_ACCCLS         acccls;         // Account close
    struct LOGAB_ACCFBLMT       accfblmt;       // Account FB Limit // KL10
    struct LOGAB_ACCFUND        fanalysis;      // Account Fund Analysis
    struct LOGAB_ACCUPD         accupd;         // Account Details Update
	struct LOGAB_ACCUPDNEW      accupdnew;      // Account Details Update New (Q210)
    struct LOGAB_ACCOPEN        accopen;        // Account Open Request
	struct LOGAB_ACCOPENNEW     accopennew;     // Account Open Request New (Q210)
    struct LOGAB_ACCPARA        accpara;        // Account parameter
    struct LOGAB_ALLUPEXP       allupexp;       // All-up Explosion
    struct LOGAB_BANKGT         bankgt;         // Generate Bank Guarantee
    struct LOGAB_CALTRF         caltrf;         // Call Transfer Request
    struct LOGAB_CHANLOCK       chanlock;       // Channel lock
    struct LOGAB_CHGACCSTATUS   chgaccstatus;   // Change of Account Status
    struct LOGAB_CHGSEC         chgsec;         // Change of Security Code
    struct LOGAB_DETCDT         detcrt;         // Debit/Credit Transaction
    struct LOGAB_FORACCREL      foraccrel;      // Forced Account Release
    struct LOGAB_MONIACC        moniacc;        // Monitor account
    struct LOGAB_OLSTAT         olstat;         // Online statement
    struct LOGAB_REJBGR         rejbgr;         // Rejected Bank Guarantee Reimbursement
    struct LOGAB_RELTRM         relterm;        // Release Terminal
    struct LOGAB_RESETPAN       resetpan;       // Reset PAN Capture
    struct LOGAB_REVANLFEE      revanlfee;      // Reverse Annual Fee
    struct LOGAB_STMCHG         stmchg;         // Statement charge
    struct LOGAB_UNSETTXNRET    unsettxnret;    // Unsettled transaction retrieval
    union  LOGAB_VALBET         valbet;         // Validat Bet
    struct LOGAB_BGREINB        bgreinb;        // Credit Bank Guarantee Reimbursement
//  struct LOGAB_UNSATLOTSI     unsatlotsi;     // Unsatisfied Lottery SI Posting
    struct LOGAB_CSCISS         csciss;         // CSC Card Issue (2011IBT)
};

// Pre-online transaction
struct LOGAB_POL_CKP        // pre-online checkpoint request
{
  struct ABPOL_STATUS   oldStatus;   // old pre-online status
  struct ABPOL_CKP      status;      // new pre-online status
};
struct LOGAB_POL_BG         // pre-online bank guarantee
{
  struct ABPOL_BG       oldBg;      // old bank guarantee information
  struct ABPOL_BG       newBg;      // new bank guarantee information
};
struct LOGAB_POL_CHGSTS     // pre-online change account status
{
  struct ABPOL_STS      chg;
  struct ACU_TRAN_ACA   tran;       // Account Balance
};
struct LOGAB_SILOT_ACA      // pre-online account access
{
  struct ABPOL_LOTACA   lot;        // check information
  __time32_t                drawdate;   // lottery draw date
  union LOGAB_ACA_DATA  data;
};
struct LOGAB_SILOT          // pre-online s.i. lottery post
{
  unsigned int          siEntrylu;  // SI entry number
  unsigned char         lotTypebu;  // lottery type
  __time32_t                drawdate;   // lottery draw date
  struct LOGAB_LOT      lot;        // lottery details
};
struct LOGAB_SIWTW          // pre-online s.i. withdrawal
{
  unsigned LONGLONG     remBaldu;   // remaining balance
  struct ACU_TRAN_WTW   wtw;        // withdrawal transaction in account file
  struct ACU_TRAN_ACA   aca;
};
struct LOGAB_LOYALTY        // CMS (loyality system)
{
  struct ACU_TRAN_ACA   aca;        // fill in by BTHNDR
  unsigned char          negbal1:1;  // cause negative balance flag
  struct ABPOL_LOYALTY  data;       // fee refund/deduction

};
struct LOGAB_POL_DETCDT     // pre-online debit/credit adjustment
{
  struct ACU_TRAN_ACA   aca;        // fill in by BTHNDR
  struct ABPOL_DCR_ADJ  data;       // debit/credit adjustment request
};
union LOGAB_POL             // pre-online general
{
  struct LOGAB_POL_CKP     ckp;     // pre-online checkpoint request
  struct LOGAB_POL_BG      bg;      // pre-online bank guarantee
  struct LOGAB_POL_CHGSTS  sts;     // pre-online change account status
  struct LOGAB_SILOT_ACA   lotaca;  // pre-online account access
  struct LOGAB_SILOT       lot;     // pre-online s.i. lottery post
  struct LOGAB_SIWTW       wtw;     // pre-online s.i. withdrawal
  struct LOGAB_LOYALTY     loyalty; // loyalty device fee refund/deduction
  struct LOGAB_ACR         acr;     // pre-online account release
  struct LOGAB_POL_DETCDT  detcdt;  // debit/credit adjustment
};

// Overflow block additional appended information for catch up
struct LOGAB_OVR_DEV_DID
{
  unsigned char         devbu;      // device type, check DEV_TYP
  unsigned int          devlu;      // device number
};
struct LOGAB_OVR_DEV_CB
{
  unsigned LONGLONG     escdu;      // esc #
  unsigned char          svt1:1;
  unsigned char          oncourse1:1;
  unsigned char          :6;
};
union LOGAB_OVR_DEV
{
    struct LOGAB_OVR_DEV_DID    did;
    struct LOGAB_OVR_DEV_CB     cb;
};
struct LOGAB_OVR            // fixed size additional data to append to end of logger
{
  // account static block info
  LONGLONG              fundd;      // funds available
  LONGLONG              bankgd;     // bank guarentee
  // tdt area info
  LONGLONG              curDivd;    // current unsettled dividend
  LONGLONG              prvDivd;    // previous unsettled dividend
  LONGLONG              depHoldd;   // deposit withheld
  LONGLONG				novBetInv;	// novelty bet fixed odds investment  (new Q208)
  LONGLONG              sbInvd;     // soccer bet investment (fixed odds)
  LONGLONG              sbPFtd;     // soccer (and novelty) fo payout forfeited <new Q208>
  LONGLONG              onlWtwd;    // daily online withdrawal amount
  LONGLONG              cshWtwd;    // daily cash withdrawal amount
  unsigned char         wtwbu;		// daily  withdrawal count  MAR2011
  unsigned char         onlWtwbu;   // daily online withdrawal count
  unsigned char         cshWtwbu;   // daily cash withdrawal count
  unsigned short        tranSodwu;  // sod transaction number
  unsigned short        tranAcswu;  // current account access transaction number
  union LOGAB_OVR_DEV   dev;        // device info
  unsigned char          newTran1:1; // new transaction appended after account access
  unsigned char          outstand1:1;// outstanding transaction flag
  unsigned char          :6;         // unused
  LONGLONG              ttlDiv;      // Dividend total (In cents = 0 for Normal a/c, > 0 for anonymous a/c) 2011IBT
};

// BT transactions
union LOGBT_AB
{
  struct LOGAB_SGN          sgn;        // signon
  struct LOGAB_SGF          sgf;        // signoff
  struct LOGAB_ACA          aca;        // account access
  struct LOGAB_ACR          acr;        // account release
  struct LOGAB_RAC          rac;        // race bet/enquiry
  struct LOGAB_LOT          lot;        // lottery bet/enquiry
  struct LOGAB_WTW          wtw;        // withdrawal
  struct LOGAB_DEP          dep;        // deposit
  struct LOGAB_CAN          can;        // cancel
  struct LOGAB_RCL          rcl;        // recall
  union  LOGAB_SB           sb;         // football bet/enquiry
  struct LOGAB_ADTLENQ      adtlenq;    // account detail enquiry
  struct LOGAB_CARDISS      esciss;     // issue esc card
  struct LOGAB_CARDREPL     escrep;     // replace esc card
  struct LOGAB_CARDRET      escret;     // return esc card
  struct LOGAB_CHGSCD       chgscd;     // bt charge security code
  struct LOGAB_AUTHVER      authver;    // authority verification 
  struct LOGAB_DEVISS       deviss;     // device issue
  struct LOGAB_DEVREPL      devrepl;    // device replace
  struct LOGAB_DEVCAN       devcan;     // device cancel
  struct LOGAB_ECVISS       ecviss;     // ECV issue
  struct LOGAB_ECVRET       ecvret;     // ECV return
  struct LOGAB_ECVCLSENQ    ecvclsenq;  // ECV close enquiry
  struct LOGAB_EFT_MISC     eftmisc;    // initialize EFT terminal
  struct LOGAB_EFT_LTEST    ltest;      // EFT link test
  struct LOGAB_CVI          cvi;        // CV issue via EFT
  struct LOGAB_ACCBAL       accbal;     // account balance via EFT, PAN capture
  struct LOGAB_RELTRM       reltrm;     // Release Terminal
  struct LOGAB_TXNENQ       txnenq;     // ticket enquiry
  struct LOGAB_ILL          ill;        // illegal message
  struct LOGAB_TERMBET		termb;		// terminate bet
  struct LOGAB_SMSCHG		smscharge;	// sms charge
  struct LOGAB_EFT_ACC_ACT	eftAccAct;	// sms charge
  struct LOGAB_EFT_ERT		eftert;		// EFT Ert
  struct LOGAB_CSCBAL		cscbal;		// CSC card balance (201108PSR)
  struct LOGAB_CSCRPL		cscrpl;		// CSC card replace (2011IBT)
  struct LOGAB_CSCRET		cscret;		// CSC card return (2011IBT)
};

// Log data structure
union LOGAB_DATA
{
  union  LOGBT_AB       bt;     // BT Txn
  union  LOGAT_AB       at;     // AT Txn
  union  LOGAB_POL      pol;    // pre-online
  union  LOGOTH         oth;    // others
  union  EODTRN_LOG     eod;    // eod tran   ! FT01
  struct LOGAB_DEPATM   deph;   // DEPHNDR log requests ! VC02
  struct LOGRDC         rdc;    // RDC message
  struct LOGSBC         sbc;    // SBC message
};

// Log record structure
struct LOGAB
{
  struct LOGAB_HDR   hdr;   // header
  union LOGAB_DATA   data;  // data
};

//new solace header 
struct PAYLOAD_HDR
{
	unsigned int system_id;
	unsigned int business_date;
	unsigned __int64 activity_id;
	unsigned __int64 cust_session_id; // customer session id. added in DEC2022 R1a for EDW
	unsigned int enquiry_status;
	unsigned char activity_nature;
	unsigned short sequence_num;
	unsigned short activity_total_num;
	unsigned short extra_data_len;
};

// Genaral Extra Data.
// Sign-On/Sign-Off; Account Detail Enquiry; BT Change Security Code; Authority Verification; 
// initialise EFT Terminal/Bank Balance; EFT link Test; CV Issue via EFT; Account Balance via EFT/PAN Capture;
// Ticket Enquiry; Terminal Bet; Illegal Message; EFT Activation from TBAS; EFT ERT; Bank Account Number;
// NBA Information; AT Transaction; Log others
struct EXTDTCOMMAB
{
	unsigned short		acterrwu;	// Activity error code; LOG.LOGHDR.errwu
	LONGLONG				actts;		// Activity timesstamp;  LOG.LOGHDR.timelu
};

// General extra data for ACU_TRAN
struct EXTDT4ACUTXN
{
	unsigned LONGLONG txnidd;	// transaction id
	unsigned int bizdatelu;		// business date
};
// Extra data.
// Account Access; Account Release;  Withdrawal; Deposit; Cancel; Recall;
// SB; Issue ESC Card; replace ESC Card; Return ESC Card;Device Issue; Device Replace; Device Cancel;
// Release Terminal; SMS Charge;
struct EXTDTAB
{
	EXTDTCOMMAB extdtcomm;
	unsigned LONGLONG txnidd;	// transaction id. LOG.LOGHDR.txnidd;
};

// Race Bet; Lottery Bet; SB;
struct EXTDTRLS
{
	EXTDTAB extDTAB;
	LONGLONG	  sellTime; // selling time
	unsigned int bizdatelu; // business date

};

#pragma pack()

#endif
