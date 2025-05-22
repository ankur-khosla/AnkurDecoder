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
//      DD01    17-APR-2002
//      - remove unnecessary variable in struct LOGATRCL; add customer total
//        for recall & CV tracking

#ifndef LOGATDEF_H
#define LOGATDEF_H

#include "tsndef.h"
#include "bcsdef.h"
#include "loghdrdef.h"
#include "logbtdef.h"
#include "logeftdef.h"
#include "logrdcdef.h"
#include "logothdef.h"

#pragma pack(1)

/***********************************

Structures defined in this file will be used by MATHNDR to set up log records 
for different MAT transactions. Usually data fields will be filled in by 
MATHNDR, unless otherwise stated (marked by "Filled in by BTHNDR")

Data in log record header to be filled in by MATHNDR:
    sizew, codewu, stfl, ltn, trmtypbu, centrelu, windowwu, hwidlu, msnlu, 
    errwu, custotd

    NOTE that if errwu is non-zero, BTHNDR is required to log it only; custotd 
              is only meaningful for recall customer session transaction.
              Other fields are initialized to zeros by MATHNDR.

Data in log record header to be filled in by BTHNDR:
    timelu, lgsl

***********************************/

#define LOG_INITBY_EFO      0
#define LOG_INITBY_REL      1

#define LOG_EFOMSG_SIZ      57

struct LOGATEFO         // EFT open
{
    char                    efomsgs[LOG_EFOMSG_SIZ];
            // efo request less the followings:
            // message header: from terminal # to the slash after ddmmmyy
            // end of Club data: the back slash
    short                   numentw;        // # of entry in wdw list
    struct BCS_EFO_REQ      req;            // BCS request
};

struct LOGATSVTSGN      // SVT sign on
{
    short                   numentw;        // # of entry in wdw list
    struct BCS_SVTSGN_REQ   req;            // BCS request
};

struct LOGATENDSCV      // enable/disable CV ops
{
    struct BCS_ENDSCV_REQ   ctrl;           // BCS request: cv control flags
    unsigned int            lgslu;          // RCV message last log sequence
                                            // Filled in by BTHNDR
};

struct LOGATWDWLIST     // for efc, efs & svt sign off request
{
    short                   numentw;        // # of entry in wdw list
    struct BCS_WDWLIST_REQ  req;            // BCS request
};

struct LOGATHVCV        // enable/disable terminal high value CV request
{
    unsigned int            lgslu;          // RCV message last log sequence
                                            // Filled in by BTHNDR
    short                   numentw;        // # of entry in wdw list in req
    struct BCS_TMHVCV_REQ   req;            // BCS request
};

struct LOGATTMPAYO      // enable/disable terminal payout request
{
    unsigned int            lgslu;          // RCV message last log sequence
                                            // Filled in by BTHNDR
    short                   numentw;        // # of entry in loc list in req
    struct BCS_TMPAYO_REQ   req;           // branch payout request
};

// centre on message will only be used between emergency MAT & OLTP
struct LOGATCON         // centre on
{
    struct BCS_CON_REQ  req;        // branch payout control
    unsigned int        lgslu;      // RCV message last log sequence
                                    // Filled in by BTHNDR
};

struct  LOGATEFTREL     // release EFT
{
    unsigned int    loclu;      // centre #
    unsigned short  wdwwu;      // window #
    unsigned int    trmidlu;    // physical terminal ID
    unsigned int    reltrmlu;   // ltn # of the released terminal
                                // Filled in by BTHNDR
    char            flagb;      // initiated by EFO or EFTREL
                                // LOG_INITBY_EFO or LOG_INITBY_REL
};

// the following structures are used to avoid referring struct LOG in union 
// LOGAT which causes LOGDEF.H & LOGATDEF.H including each other and results 
// in error during compilation
union   LOGRCLDATA      // log data for RCL
{
    union LOGBT         bt;
    struct LOGEFT       eft;
    struct LOGRDC       rdc;
    union  LOGOTH       oth;
};

struct  LOGRCLREC       // log record for RCL
{
    struct LOGHDR       hdr;
    union LOGRCLDATA    d;
};

struct LOGATREFT        // recall EFT transaction
{
    unsigned int        loclu;      // centre #
    unsigned short      wdwwu;      // window #
    unsigned int        trmidlu;    // physical terminal ID
    struct LOGRCLREC    logrec;     // recalled log record
};

struct LOGATTSN         // for stop pay, release stop pay, cancel release
                        // payout to branch, ticket enquiry, all-up explosion
                        // request
{
    unsigned char       tsnindbu;       // tsn or ref indicator
    union TSN           tsn;            // tsn
    struct BETSTS       sts;            // new bet status
                                        // Filled in by BTHNDR
    unsigned int        blocklu;        // block no. in bet file
    unsigned short      offwu;          // byte offset within block
    short               filew;          // file # (-1 means shrunk bfc index)
    struct BET          bet;            // bet record 
                                        // Filled in by BTHNDR
};

struct LOGATRPO         // release payout to branch
{
    unsigned char       tsnindbu;       // tsn or ref indicator
    union TSN           tsn;            // tsn
    unsigned int        locidlu;        // location id, aka centre #
    struct BETSTS       sts;            // new bet status
                                        // Filled in by BTHNDR
    unsigned int        blocklu;        // block no. in bet file
    unsigned short      offwu;          // byte offset within block
    short               filew;          // file # (-1 means shrunk bfc index)
    struct BET          bet;            // bet record 
                                        // Filled in by BTHNDR
};

struct LOGATRCL         // recall customer session
{
    unsigned int        reqloclu;       // centre #
    unsigned short      reqwdwwu;       // window #
    unsigned int        reqtrmidlu;     // physical terminal id
    unsigned char       reqsessflagbu;  // session flag: 0 for current
                                        //               1 for previous
    unsigned char       reqnumtxnbu;    // number of transactions required
    unsigned int        reqconidlu;     // requested continue id
    char                reqlogsysb;     // logging system
    unsigned int        conidlu;    // continue id (for next request)
    char                logsysb;    // logging system (for next request)
    BOOL                samesesst; // flag for start session or middle session
    LONGLONG            custotd;        // DD01
};

struct LOGATCVTREK      // CV tracking
{
    union TSN       tsn;            // tsn
    unsigned char   tsnindbu;       // tsn or ref indicator
    unsigned char   reqstatusbu;    // status
    unsigned char   reqmaxtxnbu;    // max transaction required
    unsigned int    reqconidlu;     // requested continue id
    char            reqlogsysb;     // logging system
    unsigned int    conidlu;     // continue id (for next request)
    char            logsysb;    // logging system (for next request)
    LONGLONG        custotd;        // DD01
};

struct  LOGATENQ        // ticket enquiry
{
    union TSN       tsn;        // tsn
    unsigned char   tsnindbu;   // tsn or ref indicator
    struct BET      bet;        // bet record of the ticket
    BOOL            claimt;     // FALSE if no claimed dividend
    LONGLONG        claimdivd;  // claimed dividend
};

struct LOGATTRMBAL      // terminal balance
{
//  struct BCS_WDW_ENTRY    req;        // BCS request
//    struct BCS_TRMBAL_REQ   req;        // BCS request
	__int64					sessid;	  // session id
    struct CKPCSH           cash;               // cash counters
};

union LOGAT
{
    struct LOGATEFO         efo;        // eft open
    struct LOGATWDWLIST     wlist;  // eft close, eft statys, svt signoff
    struct LOGATSVTSGN      svtsgn;     // svt signon
    struct LOGATENDSCV      cv;     // cv activity control
    struct LOGATHVCV        hvcv;       // high value cv terminal
    struct LOGATHVCV        keycan; // keypad cancel terminal
    struct LOGATTMPAYO      pay;        // branch payout control
    struct LOGBTREL         rel;        // release bt
    struct LOGATEFTREL      eftrel;     // release eft
    struct LOGATREFT        eftrcl;     // recall eft
    struct LOGATTSN         tsnref; // stop pay, cancel stop pay, cancel release pay
    struct LOGATRPO         rpo;        // release pay
    struct LOGATRCL         rcl;        // recall bt
    struct LOGATCVTREK      cvtrk;      // cv tracking
    struct LOGATENQ         enq;    // ticket enquiry, allup explosion
    struct LOGATTRMBAL      trmbal;     // terminal balance
    struct LOGATCON         con;    // terminal balance
};

#pragma pack(1)

#endif
