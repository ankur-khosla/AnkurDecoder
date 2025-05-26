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
//    Mod : EC01		3-Jun-2002
//		Include bet details in LOGEFTCVI.
//          LY02       18-Mar-2003
//          Store the ISN from TB reply in the log record (Q16648)
//

#ifndef LOGEFTDEF_H
#define LOGEFTDEF_H

#include "udtypedef.h"
#include "tsndef.h"
#include "betdef.h"

#define LOGEFT_EPS_LEN          256     // maximum size of epsco data portion
#define LOGEFT_WND_LEN          3       // window number length
#define LOGEFT_LOC_LEN          5       // location number length
#define LOGEFT_TEXT_LEN         30      // text length
#define LOGEFT_STEXT_LEN        60      // severe error text length
#define LOGEFT_FWV_LEN          2       // firmware version length
#define LOGEFT_DATE_LEN         7       // date length (ddmmmyy)
#define LOGEFT_TIME_LEN         4       // time length (hhmm)
#define LOGEFT_MSN_LEN          4       // msn length
#define LOGEFT_STY_LEN          2       // sub-type length
#define LOGEFT_PAN_LEN          19      // pan length
#define LOGEFT_NAME_LEN         40      // customer name

#pragma pack(1)

struct LOGEFTTRMF                       // eft terminal flag
{
    unsigned char       close1:1;       // terminal in closed mode
    unsigned char       super1:1;       // terminal in superviosr mode
    unsigned char       test1:1;        // terminal in test mode
    unsigned char       pprlow1:1;      // paper low detected
    unsigned char       prtfai1:1;      // printer fails
    unsigned char       :1;             // unused
    unsigned char       bit6on:1;       // this will be always set
};

struct LOGEFTHDR                        // eft header information
{
  struct LOGEFTTRMF     eftflag;        // eft terminal flag
// LY03..
//  short                 portw;          // eft port no  
  unsigned short        reset1 : 1;	       // reset EFT counter flag
  unsigned short        tripledes1 : 1;   // 3des flag  RL05
  unsigned short        chipcard1 : 1;    // SP3D: chip card flag
  unsigned short        fallback1 : 1;    // SP3D: chip card fallback flag
  unsigned short        reversal1 : 1;    // SP3D: chip card reversal flag
  unsigned short : 11;            // unused
// ..LY03
  short                 sysidw;         // account betting system id
  unsigned short        chanwu;         // channel number
  unsigned int          ismsnlu;        // inter-system msn (eft msn will be
                                        // stored in logger header)
  unsigned LONGLONG     carddu;         // card number
  unsigned short        errorwu;        // eft error
    #define LOGEFT_ERR_BNKTMO   536     // bank timeout
  unsigned short        sizewu;         // size of epsco data portion
};

struct LOGEFTDEP                        // eft account deposit
{
  unsigned int          amtlu;          // total cost in cents
  unsigned char         pantypbu;       // pan type
    #define LOGEFT_PANTYP_CARD      0   // card pan
    #define LOGEFT_PANTYP_CAPTURED  1   // capture pan
  char                  names[LOGEFT_NAME_LEN];     // customer name
};

struct LOGEFTWTW                        // eft withdrawal
{
  unsigned int          amtlu;          // total cost in cents
  unsigned int          seclu;          // security code
  unsigned char         wtwtypbu;       // withdrawal type
    #define LOGEFT_WTWTYP_AUTO      0   // autopay (offline)
    #define LOGEFT_WTWTYP_CPTRPAN   1   // online to captured pan
    #define LOGEFT_WTWTYP_CARDPAN   2   // online to card pan
};

struct LOGEFTACB                                // account balance enquiry
{
  LONGLONG              balamtd;                // account cash balance
  unsigned int          seclu;                  // security code
  unsigned char         pantypbu;               // pan type
  char                  pans[LOGEFT_PAN_LEN];   // pan
};

struct LOGEFTCVI    // this structure is used for both cv issue and fund
                    // transfer for betting
{
  union  TSN            tsn;                    // tsn
  unsigned short        filewu;                 // file set used
  unsigned int          amtlu;                  // amount in cents
  char                  pans[LOGEFT_PAN_LEN];   // issuer & identifier and
                                                // pan
  struct BETCV		cv;			// EC01
};

struct LOGEFTSTS    // eft status reply from terminal
{
  char                  prtflgs;                // atc print flag
  char                  unsflgs;                // unsolicited reply flag
    #define LOGEFT_UNSFLG_USN   '0'     // unsolicited status reply
    #define LOGEFT_UNSFLG_OPN   '1'     // solicited reply to open message
    #define LOGEFT_UNSFLG_CLS   '2'     // solicited reply to close message
    #define LOGEFT_UNSFLG_STS   '3'     // solicited reply to status request
  char                  fwvers[LOGEFT_FWV_LEN]; // firmware version
  char                  dates[LOGEFT_DATE_LEN]; // data in ddmmmyy
  char                  times[LOGEFT_TIME_LEN]; // time in hhmm
  char                  curmsns[LOGEFT_MSN_LEN];// current msn
  char                  curisns[LOGEFT_MSN_LEN];// current isn
  char                  subtyps[LOGEFT_STY_LEN];// transaction sub-type
    #define LOGEFT_STP_TBDEP    "01"    // TB-DEP
    #define LOGEFT_STP_TBWTH    "02"    // TB-WTH
    #define LOGEFT_STP_TBBAL    "03"    // TB-BAL
    #define LOGEFT_STP_CASHV    "04"    // CASH-V
    #define LOGEFT_STP_BKBAL    "05"    // BK-BAL
    #define LOGEFT_STP_XFBET    "06"    // XF-BET
    #define LOGEFT_STP_RECAP    "10"    // RECAP
    #define LOGEFT_STP_IRCAP    "11"    // I-RCAP
    #define LOGEFT_STP_CHMEK    "12"    // CH-MEK
    #define LOGEFT_STP_VEMEK    "13"    // VE-MEK
    #define LOGEFT_STP_RQPEK    "14"    // RQPEK
    #define LOGEFT_STP_TINIT    "15"    // T-INIT
    #define LOGEFT_STP_LOOBK    "20"    // LOOP BACK
    #define LOGEFT_STP_STATU    "32"    // STATUS
    #define LOGEFT_STP_SEVER    "33"    // SEVERE
    #define LOGEFT_STP_IDLNG    "  "    // IDLING

  char                  modes;                  // mode flag
  char                  closedbys;              // closed by flag
  char                  keyswtchs;              // keyswitch position
  char                  txstatus;               // customer transaction status
  // current functions provided to customer
  unsigned char         accdep1:1;              // deposit
  unsigned char         accwtw1:1;              // withdrawal
  unsigned char         accbal1:1;              // account balance
  unsigned char         bnkbal1:1;              // bank balance
  unsigned char         cv1:1;                  // cash voucher
  char                  pwrfails;               // power failure
  char                  badpars;                // uninit./corrupted parameters
  char                  mekerrs;                // mek error
  char                  badchks;                // program checksum failed
  char                  badrams;                // ram check failed
  char                  badstts;                // status/switch inconsistency
                                                // at power recovery
  char                  pdsroffs;               // primary channel dsr off
  char                  sdsroffs;               // secondary channel dsr off
  char                  ptrsts;                 // printer status
  char                  tstocks;                // ticket stock status
  char                  prtsts;                 // print status
  char                  tprtflags;              // ticket printed flag
  char                  issflags;               // issued to customer flag
  char                  trmrtvs;                // retrieved by terminal flag
  char                  text[LOGEFT_TEXT_LEN];  // text
};

struct LOGEFTSER        // severe error message
{
  char                  prtflgs;                // atc print flag
  char                  dates[LOGEFT_DATE_LEN]; // data in ddmmmyy
  char                  times[LOGEFT_TIME_LEN]; // time in hhmm
  char                  errmsns[LOGEFT_MSN_LEN];// msn of error tx
  char                  errisns[LOGEFT_MSN_LEN];// isn of error tx
  char                  subtyps[LOGEFT_STY_LEN];// transaction sub-type
  char                  pwrfails;               // power failure
  char                  mekerrs;                // mek error
  char                  rtyabds;                // retry abandoned by open flag
  char                  cverrs;                 // cv error flag
  char                  frejrcds;               // fake reject rec'd after 
                                                // terminal timeout to close
                                                // mode flag
  char                  tstocks;                // ticket stock status
    #define LOGEFT_TSTOCK_NORM  '0'             // Normal
    #define LOGEFT_TSTOCK_LOW   '1'             // low
    #define LOGEFT_TSTOCK_OUT   '2'             // out
                                                // print status
  unsigned char         psnosb1:1;              // no print status block
  unsigned char         psfeed1:1;              // feed failure
  unsigned char         pstmer1:1;              // ticket motion error
  unsigned char         pstjam1:1;              // ticket jam
  unsigned char         pspoor1:1;              // poor print
  unsigned char         psfull1:1;              // capture hopper full
  char                  tprtflags;              // ticket printed flag
  char                  issflags;               // issued to customer flag
  char                  trmrtvs;                // retrieved by terminal flag
  char                  pans[LOGEFT_PAN_LEN];   // issuer & identifier and
                                                // PAN
  char                  text[LOGEFT_STEXT_LEN]; // severe error text 
};

union LOGEFTEPSDATA             // club data portion
{
    struct LOGEFTDEP    dep;    // deposit
    struct LOGEFTWTW    wtw;    // withdrawal
    struct LOGEFTCVI    cvi;    // cv issue / fund transfer for betting
    struct LOGEFTACB    bal;    // account balance enquiry
};

#define LOGEFT_EPS_KT_LEN       16
#define LOGEFT_EPS_MAC_LEN      8
#define LOGEFT_EPS_MSG_LEN      2
#define LOGEFT_EPS_GMSN_LEN     4
#define LOGEFT_EPS_BRAWDW_LEN   7
#define LOGEFT_EPS_AMT_LEN      8
#define LOGEFT_EPS_BNKPIN_LEN   16
#define LOGEFT_EPS_ACNTID_LEN   3
#define LOGEFT_EPS_TRKDATA_LEN  112

#define LOGEFT_EPS_ISN_LEN      6       // LY02

struct LOGEFTEPSB
{
    char    mflgb;      //new eft msg flag
    char    kmidxs;     //km index      
    char    kts[LOGEFT_EPS_KT_LEN];     // KT
    char    macs[LOGEFT_EPS_MAC_LEN];   // MAC
    char    msls[LOGEFT_EPS_MSG_LEN];   // msg length
    char    gwmsns[LOGEFT_EPS_GMSN_LEN];// gateway msn
    char    brawdws[LOGEFT_EPS_BRAWDW_LEN]; // branch/window
    char    pans[LOGEFT_PAN_LEN];       // pan 
    char    amts[LOGEFT_EPS_AMT_LEN];   // amount
    char    bnkpins[LOGEFT_EPS_BNKPIN_LEN]; // bank pin
    char    acntids[LOGEFT_EPS_ACNTID_LEN]; // account indicator
    char    trkdats[LOGEFT_EPS_TRKDATA_LEN];// track data
};

union   LOGEFTEPSBODY
{
    struct LOGEFTEPSB   epsbody;
    unsigned char       epsbu[LOGEFT_EPS_LEN];  // epsco data portion
};    

struct LOGEFTEPS                // transaction type with epsco data
{
    char                isns[LOGEFT_EPS_ISN_LEN];   // ISN LY02
    union LOGEFTEPSDATA data;
    union LOGEFTEPSBODY body;
};

union LOGEFTBODY
{
    struct LOGEFTEPS    eps;        // transaction with epsco data
    struct LOGEFTSTS    sts;        // eft status
    struct LOGEFTSER    ser;        // eft severe error
    char                scodes[LOGEFT_STY_LEN]; //  invalid eft subcode
};

struct LOGEFT
{
    struct LOGEFTHDR    hdr;        // eft transaction header information
    union LOGEFTBODY    body;       // eft transaction body information
};

#pragma pack()

#endif
