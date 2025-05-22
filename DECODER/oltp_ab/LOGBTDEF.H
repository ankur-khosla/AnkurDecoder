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
//    Author : Edward Hon                01-NOV-2000
//
//    Mod : 
//            LY01                       06-MAR-2002
//            Add structure to log invalid message format request
//                EC01                   15-APR-2002
//                Include the post-update bet image followed by the
//                pre-update image in the log record for pay/cancelled
//                and reversal of pay/cancelled operations.
//
//            RL02                       22-APR-2002
//            Add BCS message log sequence for illegal key pad cancel
//            to union LOGBTCCPD (cancel/payout detail)
//            PN04                       22-AUG-2002
//            Remove unsolicited terminal balance log record
//            EH05                       08-AUG-2002
//            soccer betting
//            RL06                       29-NOV-2002
//            Add SB bet sell error info
//            RL07                       13-FEB-2003
//            Add SB account type info for ESC
//            LY08                       13-MAY-2003
//            Add rejected message log
//            LY09                       20-JUN-2003
//            Add SB account type info in the log record
//            LY10                       03-JUL-2003
//            Add print bonus flag for SB log
//            LY11                       14-JUL-2003
//            New protocol between OLTP-CB & SB/BCS
//            PN12                       7-NOV-2003
//            Store terminal type in sign on message
//            LY13                       25-FEB-2004
//            New BT transaction - change password
//            More terminal status returned upon signon
//    Remark: All fields referring to other system index should be referenced
//            when othsys1 bit in logger header is set.
//            RL14                       09-MAR-2004
//            ( add new BT and ESC interface for OLTP-AB )
//            JC15                       06-AUG-2004
//            New BT transaction - terminal recall and ENQ from BT
//            RL16                       25-AUG-2005
//            add deposit amount for esc card issue
//

#ifndef LOGBTDEF_H
#define LOGBTDEF_H

//#include "ckpdef.h"
//#include "cbpardef.h"
#include "tsndef.h"
#include "betdef.h"
#include "bcsdef.h"
//#include "sbmsgdef.h"
//#include "sblogdef.h"

#define TEXT_FROM_BT_LEN 128
#define BTMSG_ILLTXT_LEN  20

//
// size of some record type
//
#define LOGBTESC_LEN_ID           16      // customer id
#define LOGBTESC_LEN_NAME         40      // customer name
#define LOGBTESC_LEN_ADDR         120     // customer address
#define LOGBTESC_LEN_PHONE        20      // phone number
#define LOGBTESC_LEN_DATE         8       // date
#define LOGBTESC_LEN_LOC          2       // Location ID
#define LOGBTESC_LEN_TEXT         30      // text field
#define LOGBTESC_LEN_ACTENQ_RPY   380     // max. esc account enq reply size
#define LOGBTESC_LEN_TXNENQ_RPY   380     // max. esc txn. enq. reply size
#define LOGBTESC_LEN_ACTRCL_RPY   512     // max. account recall details size


#pragma pack(1)

struct  LOGBTBCS                        // bcs system information
{
//  unsigned int          ismsnlu;        // inter-system msn LY11
  unsigned int          disable1:1;     // bcs service is disabled
  unsigned int          :7;             // unused
};

struct  LOGBTABS                        // account bet system information
{
// RL14..
  char                  sysb;           // account bet system index (this is 
                                        // meaningful only when othsys1 is set)
  unsigned int          busy4:4;        // ESC/OLTP-AB busy during to disable and not ready
  unsigned int          poll4:4;        // next ESC/OLTP-AB to poll
// ..RL14
  unsigned int          ismsnlu;        // inter-system msn
  unsigned LONGLONG     carddu;         // card number
};

struct  LOGBTRAC        // racing bet
{
  union TSN             tsn;            // tsn
  unsigned short        filewu;         // file #
  unsigned short        rdsidxwu;       // rds index
  unsigned char         locbu;          // meeting location
  unsigned char         daybu;          // meeting day
  unsigned char         errracbu;       // rejected race no. 
  unsigned char         errselbu;       // rejected selection number
  struct LOGBTABS       othsys;         // account bet system information
  struct BET            bet;
};

struct  LOGBTLOT        // lottery bet
{
  union TSN             tsn;            // tsn
  unsigned short        filewu;         // file #
  unsigned short        lotidxwu;       // lot index
  unsigned short        yearwu;         // year
  unsigned short        drawwu;         // draw #
  unsigned char         errselbu;       // rejected selection number
  unsigned char			versionbu;		// version number
  struct LOGBTABS       othsys;         // account bet system information
  struct BET            bet;
};

struct  LOGBTCV         // CV
{
  union TSN             tsn;            // tsn
  unsigned short        filewu;         // file #
  struct BET            bet;
};

union LOGBTBCHG         // detail of bet change after payout
{
  unsigned int          pftrlu[BET_AUP_MAXEVT];     // all up pay factor
  struct BETLOTMD       md;                         // multi-draw lottery extra
};

union LOGBTCBET_BET     // updated image of bet followed by original image
{                       // EC01
//  struct BET            new;
  char                  bufb[sizeof(struct BET)*2];
};

struct  LOGBTCBET       // cancel/cash voucher cashing/payout details
{
  union TSN             tsn;            // new tsn of partial pay [0 means it
                                        // is not a partial pay]
  short                 sysw;           // system # [-1 local], this is used
                                        // for internal index to TDTCOM and is 
                                        // different from the one in PARDEF.H
  unsigned short        chanwu;         // cross system channel #
  unsigned short        msnwu;          // cross system msn
  unsigned short        offwu;          // offset into block
  short                 filew;          // file # [-1 means shrink bfc index]
  short                 sbfcidxw;       // bfc index for shrink bet file
  short                 midxw;          // meeting/draw index for cancel;
                                        // if it is payout transaction for
                                        // multi-draw lottery, it will be
                                        // draw index for first draw to be
                                        // refunded
  unsigned int          blocklu;        // block # of ticket
  unsigned LONGLONG     payoutdu;       // total payout in cents (this is the
                                        // amount to be paid in this pay/cancel
                                        // transaction)
  struct LOGBTABS       othsys;         // account bet system information
                                        // ( this is used for payout deposit
                                        // purpose, -1=>no comm. with account
                                        // bet system )
  union LOGBTBCHG       bchg;           // bet changed detail
  short                 lenw;           // size of bet record in bytes   EC01
  union LOGBTCBET_BET   bet;            // post-update image followed by pre-
                                        // update image of the bets -
                                        // variable length               EC01
};

struct  LOGBTTBD        // tb deposit (using pseudo terminal approach)
{
  short                 sysw;           // system #
  unsigned short        chanwu;         // channel #
  unsigned int          ismsnlu;        // inter-system msn
  unsigned short        trnwu;          // transaction #
  unsigned int          amtlu;          // amount
  char                  names[LOGBTESC_LEN_NAME];   // customer name
};

struct LOGBTABTRN       // account betting transaction cancel info.
{
  struct LOGBTABS       othsys;         // account bet system information
  int                   amtl;           // amount
};

struct LOGBTPCSB_BET_INFO   // sb bet pay/cancel detail
{
  union TSN             tsn;            // new tsn of partial pay [0 means it
                                        // is not a partial pay]
  unsigned LONGLONG     payoutdu;       // total payout in cents (this is the
                                        // amount to be paid in this pay/cancel
                                        // transaction)
  struct BETSB_CB       bet;            // sb bet detail
};

union LOGBTPCSB_ERR_INFO    // sb bet pay/cancel reject detail
{
  unsigned LONGLONG     payoutdu;       // total payout in cents
  unsigned int          centrelu;       // centre # of released ticket
};

union LOGBTPCSB_INFO    // sb bet pay/cancel detail
{
  struct LOGBTPCSB_BET_INFO     bet;    // bet pay/cancel detail
  union LOGBTPCSB_ERR_INFO      err;    // error information
};

struct LOGBTPCSB        // sb bet pay/cancel
{
//  unsigned int          ismsnlu;        // inter-system msn between OLTP-SB LY11
  struct LOGBTABS       othsys;         // account bet system information
                                        // ( this is used for payout deposit
                                        // purpose, -1=>no comm. with account
                                        // bet system )
  union LOGBTPCSB_INFO  info;           // info on pay/cancel transaction
};

union   LOGBTCCPD       // cancel/payout detail
{
  struct LOGBTCBET      bet;            // bet
  struct LOGBTTBD       tbd;            // cancel tb deposit
  struct LOGBTABTRN     actx;           // account transaction
  struct LOGBTPCSB      sb;             // pay/cancel sb bet
};

struct  LOGBTCCP        // cancel/cash voucher cashing/payout complete details
{
  union TSN             tsn;            // tsn of cancel/pay ticket
  unsigned short        methodwu;       // method
    #define LOGBTCCP_METHOD_READER      0       // reader
    #define LOGBTCCP_METHOD_KEY         1       // keyed
    #define LOGBTCCP_METHOD_HIGH        2       // high value pay
    #define LOGBTCCP_METHOD_ESC         3       // esc
  union LOGBTCCPD       d;                      // details
};

struct  LOGBTCIO        // cash in/out
{
  struct LOGBTBCS   othsys;         // bcs system info.
  unsigned int      amtlu;          // amount in cents
  unsigned int      cstflu;         // cashier #
  unsigned int      cpwdlu;         // cashier password
  char              ccodb[2];       // cashier code
};

#define LOGBTSGF_CNT    20      // # of signoff statistics counters

struct  LOGBTSGF        // bt sign-off
{
//  struct LOGBTBCS       othsys;                 // bcs system info.
//  unsigned short        statwu[LOGBTSGF_CNT];   // stats. counters
//  struct CKPCSH         cash;                   // cash counters (in cents)
  struct BCS_SHROFF_BAL shrfbal;                // shroff balance
  unsigned int          sgf1:1;                 // staff sign-off
};

struct  LOGBTSGN        // sign on
{
  struct LOGBTBCS       othsys;         // bcs system info.
  unsigned int          pwdlu;          // password
  unsigned int          sstflu;         // supervisor #
  unsigned int          spwdlu;         // supervisor password
  unsigned int          authlevellu;    // authority level bitmap
  unsigned int          ctron1:1;       // centre on
  unsigned int          highcv1:1;      // high cv terminal
  unsigned int          keycan1:1;      // keypad cancel terminal
  unsigned int          dsbpay1:1;      // disable payout
  unsigned int          hoterm1:1;      // h.o. terminal
  unsigned int          onc1:1;         // on course terminal
  unsigned int          xtote1:1;       // x tote branch flag   LY13
  unsigned int          dsblot1:1;      // disable lottery      LY13
  unsigned int          dsbsb1:1;       // disable sb           LY13
  unsigned int          dsbcv1:1;       // disable cv           LY13
  unsigned int          dsbrace1:1;     // disable racing       LY13
  unsigned int          dsbtb1:1;       // disable tb deposit   LY13
  unsigned int          :20;            // unused               LY13
  unsigned char         cntbu;          // no. of times shroff sign on (to all
                                        // terminals)
  __time32_t                dat;            // terminal date
//  struct CBPARBT        btv;            // bt version #
  unsigned char         flagbu;         // terminal flag [1=svt]
    #define LOGSGN_TRM_OPT  0   // operator terminal
    #define LOGSGN_TRM_SVT  1   // svt terminal
  unsigned char         ttypebu;        // terminal type        PN12..
    #define LOGSGN_TRM_DM5  0   // DM 5/7/9
    #define LOGSGN_TRM_DM2K 1   // DM 2000
    #define LOGSGN_TRM_MTBT 2   // MTBT                         ..PN12
};

//
// Message received from bt. This includes svt warning message and
// severe message
//
struct  LOGBTMSG
{
  char text[TEXT_FROM_BT_LEN];  // text from betting terminal
};

struct LOGBTFSGF                    // force sign off terminal
{
  struct LOGBTBCS   othsys;         // bcs system info.
//  struct CKPCSH     cash;           // terminal balance
};

struct  LOGBTTBDI           // tb deposit issue (via pseudo terminal)
{
  union TSN             tsn;            // tsn 
  struct LOGBTTBD       data;           // deposit details
};

// LY13..
struct LOGBTCHGPWD                  // change staff password
{
    struct LOGBTBCS     othsys;     // bcs system info.
    unsigned int        stafflu;    // staff pin
    unsigned int        oldpinlu;   // old pin
    unsigned int        newpinlu;   // new pin
};
// ..LY13

//
// Message formats for ESC log data
//

//
//  Account type
//
#define LOGBTESC_ACT_NAMED       '0'     // Named
#define LOGBTESC_ACT_ANONYMOUS   '1'     // Anonymous

//
//  Language type
//
#define LOGBTESC_LANG_ENG        '0'     // English
#define LOGBTESC_LANG_CHN        '1'     // Chinese

//
// Forfeit flag
//
#define LOGBTESC_NO_FORFEIT      '0'     // No forfeit
#define LOGBTESC_FORFEIT         '1'     // Forfeit

//
// Fee waive flag
//
#define LOGBTESC_NO_WAIVE        '0'     // No waive
#define LOGBTESC_WAIVE           '1'     // Waive

//
// Call transfer flag
//
#define LOGBTESC_CX_NIL          '0'     // nil
#define LOGBTESC_CX_BOCC         '1'     // to BOCC
#define LOGBTESC_CX_HOTLINE      '2'     // to hot line
#define LOGBTESC_CX_ADMIN        '3'     // to ESC admin

//
// Terminal type
//
#define LOGBTESC_TRM_ET          '0'     // enquiry terminal
#define LOGBTESC_TRM_CST         '1'     // customer service terminal

// 
// Account release code
//
#define LOGBTESC_RELCD_NORMAL    0x40    // normal (user request via terminal)
#define LOGBTESC_RELCD_CRDRM     0x41    // initiated by terminal due to card removal
#define LOGBTESC_RELCD_EFTTO     0x42    // initiated by terminal due to timeout or
                                    // or unposted
//
// Withdrawal type
//
#define LOGBTESC_WTD_CASH        '0'     // cash
#define LOGBTESC_WTD_AUTO        '1'     // autopay
#define LOGBTESC_WTD_CHEQUE      '2'     // cheque

//
// Account status code
//
#define LOGBTESC_ACS_UNUSED      '0'     // unused 
#define LOGBTESC_ACS_OPEN        '1'     // opened
#define LOGBTESC_ACS_FROZEN      '2'     // frozen
#define LOGBTESC_ACS_CLOSE       '3'     // closed
#define LOGBTESC_ACS_REUSABLE    '4'     // reusable

struct LOGBTACAQ                // account access request
{
  unsigned short    rejcodewu;          // CMS reject code
};

struct LOGBTACAP                // account access reply
{
  char           langb;         // language
  char           cxflagb;       // call transfer flag
  char           fbtypeb;       // FB account type - RL07
  LONGLONG       totdivd;       // accumulated dividend amount
  LONGLONG       curexpamtd;    // current day's expenditure amount
};

struct LOGBTACA                 // log data for esc account access
{
  struct LOGBTACAQ  req;
  struct LOGBTACAP  rpy;
};

struct LOGBTACRQ                // account release request
{
  unsigned char     relcodebu;  // release code
};

struct LOGBTACR                 // account release
{
  struct LOGBTACRQ  req;
};

struct LOGBTCDEPQ               // cash deposit to esc account - request
{
    int         amtl;       // deposit amount
};

struct LOGBTCDEP                // log data for cash deposit to esc account
{
  struct LOGBTCDEPQ req;
};

struct LOGBTWTWQ                // withdrawal from esc account - request
{
  char              wtdtypeb;   // withdrawal type
  int               amtl;       // withdrawal amount
};

struct LOGBTWTW                 // log data for withdrawal from esc account
{
  struct LOGBTWTWQ  req;
};

struct LOGBTACRCLQ                  // account recall request
{
  char              trmtypeb;       // terminal type
  long              txnnuml;        // trxn no. to start recall
  short             trnlrclw;       // no. of trxn recalled by last recall
};

struct LOGBTACRCLP                  // account recall reply 
{
  short             nxttxnw;        // next trxn no. to continue recall
  short             tottxnw;        // total no. of trxns recalled
  char              details[LOGBTESC_LEN_ACTRCL_RPY];     // recall details
};

struct LOGBTACRCL                   // log data for account recall
{
  struct LOGBTACRCLQ  req;
  struct LOGBTACRCLP  rpy;
};

struct LOGBTTXENQQ                  // transaction enquiry request
{
  char              trmtypeb;       // terminal type
  int               trxnuml;        // trxn no. of trxn to be enquired
};

struct LOGBTTXENQP                  // transaction enquiry reply
{
  char              details[LOGBTESC_LEN_TXNENQ_RPY];     // transaction details
};

struct LOGBTTXENQ                   // log data for transaction enquiry
{
  struct LOGBTTXENQQ    req;
  struct LOGBTTXENQP    rpy;
};

struct LOGBTCISSQ                   // card issue request
{
  char              acttypebu;                        // account type
  char              cusids[LOGBTESC_LEN_ID];          // customer id
  char              cusnames[LOGBTESC_LEN_NAME];      // customer name
  char              cusaddrs[LOGBTESC_LEN_ADDR];      // customer address
  char              cusdphones[LOGBTESC_LEN_PHONE];   // day phone no.
  char              cusnphones[LOGBTESC_LEN_PHONE];   // night phone no.
  char              langb;                            // language
  char              sexb;                             // sex ('M'/'F')
  char              birthdates[LOGBTESC_LEN_DATE];    // date of birth
  char              locations[LOGBTESC_LEN_LOC];      // location (district code)
  unsigned char     crdfwflgbu;                       // card deposit fee waive flag
  int               amtl;                             // deposit amount for 
                                                      // opening balance
};

struct LOGBTCISSP               // card issue reply
{
  int               crdfeel;    // card deposit fee deducted
};

struct LOGBTCISS                // log data for card issue
{
  struct LOGBTCISSQ req;
  struct LOGBTCISSP rpy;
};


struct LOGBTCREPQ               // card replacement request
{
  unsigned LONGLONG newcrddu;               // new card number
  char              cusids[LOGBTESC_LEN_ID];  // customer id
  unsigned char     crdffflgbu;             // card deposit fee forfeit flag
  unsigned char     crdfwflgbu;             // card deposit fee waive flag
  int               amtl;                   // deposit amount for card replace
};

struct LOGBTCREPP               // card replacement reply
{
  LONGLONG      divamtd;        // accumulated dividend amount
  int           crdfeerfdl;     // card deposit fee refunded
  int           crdfeeddtl;     // card deposit fee deducted
};

struct LOGBTCREP                // log data for card replacement
{
  struct LOGBTCREPQ req;
  struct LOGBTCREPP rpy;
};

struct LOGBTDTLUQ               // customer details update request
{
  char              acttypeb;                         // account type
  char              cusids[LOGBTESC_LEN_ID];          // customer id
  char              cusnames[LOGBTESC_LEN_NAME];      // customer name
  char              cusaddrs[LOGBTESC_LEN_ADDR];      // customer address
  char              cusdphones[LOGBTESC_LEN_PHONE];   // day phone no.
  char              cusnphones[LOGBTESC_LEN_PHONE];   // night phone no.
  char              langb;                            // language
  char              sexb;                             // sex ('M'/'F')
  char              birthdates[LOGBTESC_LEN_DATE];    // date of birth
  char              locations[LOGBTESC_LEN_LOC];      // location (district code)
};

struct LOGBTDTLU                // log data for customer details update
{
  struct LOGBTDTLUQ req;
};

struct LOGBTCLSQ                // account close request
{
  char              cusids[LOGBTESC_LEN_ID];      // customer id
  unsigned char     crdffflgbu;                 // card deposit fee forfeit flag
  char              wthtypeb;                   // withdrawal type
  char              reasons[LOGBTESC_LEN_TEXT];   // reason text
  int               amtl;                       // withdrawal amount
};

struct LOGBTCLSP                // account close reply
{
  int               crdfeerfdl; // card deposit fee refunded
};

struct LOGBTCLS                 // log data account close
{
  struct LOGBTCLSQ  req;
  struct LOGBTCLSP  rpy;
};

struct LOGBTACENQP              // account enquiry reply
{
  char          langb;          // language
  char          cxflagb;        // call transfer flag
  char          fbtypeb;        // FB account type - RL07
  LONGLONG      totdivd;        // accumulated dividend amount
  LONGLONG      curexpamtd;     // current day's expenditure amount
  int           crddepamtl;     // card deposit fee
  char          actstsb;        // account status
  unsigned char ostxn1:1;       // outstanding trxn flag
  unsigned char mmbac1:1;       // member account
  unsigned char mk6si1:1;       // mark6 si account
  unsigned char wthsi1:1;       // withdrawal si
  unsigned char bnkgr1:1;       // bank guarantee 
  unsigned char nmibk1:1;       // nominated bank account
  char          memos[LOGBTESC_LEN_TEXT];      // memorandum
};

struct LOGBTACENQ               // log data for account details enquiry
{
  struct LOGBTACENQP rpy;
};

// RL14..
struct LOGBTSTM                 // log data for account statement request/reply
{
  unsigned short    lenwu;                          // length of terminal data
  char              datab[LOGBTESC_LEN_ACTRCL_RPY]; // terminal data/reply
};

struct LOGBTCHGSCD              // change account security code request
{
  char              cusidb[LOGBTESC_LEN_ID];    // customer id
  unsigned int      oldSeculu;                  // old security code
  unsigned int      newSeculu;                  // new security code
};

struct LOGBTESCISSQ
{
  char              cusidb[LOGBTESC_LEN_ID];    // customer id
  unsigned int      seculu;                     // security code
  unsigned int      wavflg1:1;                  // waive card deposit fee flag
  unsigned int      depAmtlu;                   // deposit amount         RL16
};

struct LOGBTESCISSP
{
  unsigned int      crdfeelu;                   // card deposit fee deducted
};

struct LOGBTESCISS              // issue esc card
{
  struct LOGBTESCISSQ   req;
  struct LOGBTESCISSP   rpy;
};

struct LOGBTESCREPQ
{
  unsigned LONGLONG newEscdu;                   // new esc card number
  char              cusidb[LOGBTESC_LEN_ID];    // customer id.
  unsigned int      seculu;                     // security code
  unsigned int      fftdep1:1;                  // forfeit deposit flag [0=no forfeit]
  unsigned int      wavdep1:1;                  // wavie deposit flag [0=not waive]
};

struct LOGBTESCREPP
{
  unsigned LONGLONG divamtdu;                   // accumulated dividend amount
  unsigned int      crdfeerfdlu;                // card deposit fee refunded
  unsigned int      crdfeeddtlu;                // card deposit fee deducted
};

struct LOGBTESCREP              // replace esc card
{
  struct LOGBTESCREPQ   req;
  struct LOGBTESCREPP   rpy;
};

struct LOGBTESCRETQ
{
  char              cusidb[LOGBTESC_LEN_ID];    // customer id.
  unsigned int      fftdep1:1;                  // forfeit deposit flag [0=no forfeit]
};

struct LOGBTESCRETP
{
  unsigned int      crdfeerfdlu;                // card deposit fee refunded
};

struct LOGBTESCRET              // return esc card
{
  struct LOGBTESCRETQ   req;
  struct LOGBTESCRETP   rpy;
};

union LOGBTESCD        // esc
{
  struct LOGBTACA       acc;
  struct LOGBTACR       acr;
  struct LOGBTCDEP      dep;
  struct LOGBTWTW       wth;
  struct LOGBTACRCL     rcl;
  struct LOGBTTXENQ     enq;
  struct LOGBTCISS      open;
  struct LOGBTCREP      repl;
  struct LOGBTDTLU      cupd;
  struct LOGBTCLS       cls;
  struct LOGBTACENQ     acenq;
  struct LOGBTSTM       stm;
  struct LOGBTCHGSCD    chgscd;
  struct LOGBTESCISS    esciss;
  struct LOGBTESCREP    escrep;
  struct LOGBTESCRET    escret;
};  
// ..RL14
    
struct LOGBTESC
{
  struct LOGBTABS   othsys;     // account bet system information
  union  LOGBTESCD  d;          // data
};

struct  LOGBTREL        // release terminal
{
    unsigned int            loclu;      // location id
    unsigned short          wdwwu;      // window #
    unsigned int            trmidlu;    // physical term #
    unsigned int            reltrmlu;   // ltn # of the released terminal
                                        // Filled in by BTHNDR
    unsigned int            stafflu;    // staff on released terminal
                                        // Filled in by BTHNDR
//    struct CKPCSH           cash;       // cash counters
                                        // Filled in by BTHNDR
    unsigned int            acclu;      // account #
    struct LOGBTABS         escinfo;    // account bet system information
                                        // (only valid when acclu >= 0)
    struct LOGBTBCS         othsys;     // bcs system information
    unsigned int            bcsact1:1;  // bcsrt post log completed action flag
    unsigned int            escact1:1;  // esc post log completed action flag
    unsigned int            relexc1:1;  // exception, do not update terminal
};

// LY01
// Invalid message terminal data log
// This structure is used in logging the incoming request in case of 
// LOG_ERR_INVMSG error occurs.
// The program logs at most the sizeof(union LOGBT) - sizeof(offsetwu)
// bytes of data in buf[].
struct LOGBTINVMSG          
{
    unsigned short          offsetwu;   // offset to data buffer where error
                                        // occurs
//    unsigned char           buf[];      // message buffer
};

// LY08
// For rejected messages.
// Rejected messages are those from the terminal with the logical terminal
// no. marked as problematic in BTHNDRCOM.
struct LOGBTREJMSG
{
    unsigned char           tidbu;      // PCL tid
 //   unsigned char           buf[];      // message buffer
};

struct LOGBTSBBET
{
  union TSN             tsn;            // tsn
  unsigned int          oddsold1:1;     // odds out of date flag
  unsigned int          woodds1:1;      // selling without odds
  unsigned int          bonus1:1;       // print bonus information LY10
//  struct SBLOG_BET_ERR  err;            // error information  RL06
  unsigned char         sbtypbu;        // sb account type 
                                        // (only used in some error cases) LY09
  struct BETDATA        bet;            // bet detail
};

union LOGBTSBD
{
  struct LOGBTSBBET     bet;                        // bet/enquiry data
//  unsigned char         trmDatabu[SB_MAX_TRMDATA];  // terminal data [variable]
};

struct  LOGBTSB                         // soccer bet
{
  struct LOGBTABS       othsys;         // account bet system information
  union LOGBTSBD        d;              // raw data or sell bet reply
};

struct LOGBTRCL         // recall customer session
{
    unsigned int        reqloclu;       // centre #
    unsigned short      reqwdwwu;       // window #
    unsigned int        reqtrmidlu;     // physical terminal id
    unsigned char       reqsessflagbu;  // session flag: 0 for current, 1 for previous
    unsigned char       reqnumtxnbu;    // number of transactions required
    unsigned int        reqconidlu;     // requested continue id
    char                reqlogsysb;     // logging system
    unsigned int        conidlu;        // continue id (for next request)
    char                logsysb;        // logging system (for next request)
    BOOL                samesesst;      // flag for start session or middle session
    LONGLONG            custotd;
};

struct  LOGBTENQ        // ticket enquiry           // JC15
{
    union TSN       tsn;        // tsn
    unsigned char   tsnindbu;   // tsn or ref indicator
    struct BET      bet;        // bet record of the ticket
    BOOL            claimt;     // FALSE if no claimed dividend
    LONGLONG        claimdivd;  // claimed dividend
};

union   LOGBT
{
  struct LOGBTRAC       rac;
  struct LOGBTLOT       lot;
  struct LOGBTCV        cv;
  struct LOGBTCIO       cio;
  struct LOGBTCCP       ccp;
  struct LOGBTSGF       sgf;
  struct LOGBTSGN       sgn;
  struct LOGBTMSG       msg;
  struct LOGBTFSGF      fsgf;
  struct LOGBTTBDI      tbd;
  struct LOGBTESC       esc;
  struct LOGBTREL       rel;        // terminal release
  struct LOGBTINVMSG    invmsg;
  struct LOGBTSB        sb;
  struct LOGBTCHGPWD    chgpwd;     // LY13
  struct LOGBTREJMSG    rejmsg;     // LY08
  struct LOGBTENQ       enq;        // ENQ from BT  // JC15
  struct LOGBTRCL       rcl;        // RCL from BT  // JC15
  unsigned char         illmsgbu[BTMSG_ILLTXT_LEN];  // illegal message stream
};



#define LOGBTAUP_SIZE    (   sizeof(struct LOGHDR) + sizeof(struct LOGBTRAC)  \
                           - sizeof(union  BETVAR) + sizeof(struct BETAUP   ))
#define LOGBTEXOSTD_SIZE (   sizeof(struct LOGHDR) + sizeof(struct LOGBTRAC)  \
                           - sizeof(union  BETVAR) + sizeof(struct BETEXOSTD))
#define LOGBTLOTSD_SIZE  (   sizeof(struct LOGHDR) + sizeof(struct LOGBTLOT)  \
                           - sizeof(union  BETVAR) + sizeof(struct BETLOTFIX))
#define LOGBTLOTMD_SIZE  (   sizeof(struct LOGHDR) + sizeof(struct LOGBTLOT)  \
                           - sizeof(union BETVAR)  + sizeof(struct BETLOT   )) 
#define LOGBTDEP_SIZE    (   sizeof(struct LOGHDR) + sizeof(struct LOGBTCV )  \
                           - sizeof(union  BETVAR) + sizeof(struct BETDEP   ))

#pragma pack()

#endif
