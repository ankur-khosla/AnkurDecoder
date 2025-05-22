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
//      BCSDEF.H
//
//      This file defines structures for BCS data
// 
//    Author : Eddie Chu        Jan 15, 20001
//
//    Mod : 
//

#ifndef BCSDEF_H
#define BCSDEF_H

#include "udtypedef.h"

#pragma pack(1)

struct  BCS_DATE
{
    char    day;
    char    month;
    short   year;
};

struct BCS_TIME
{
    char    hour;
    char    minute;
    char    second;
};

#define BCS_MAXAT           1000    // # of at
#define BCS_MAX_TRMSTAT     20      // # of sign off terminal statistic counter
#define BCS_FIELD_SEP       0x1C    // seperator for fields of BCS messages

// guarantee from BA that a window list that requires more than one packet will
// be chopped into messages in single packets, i.e. multiple msgtxid (vs
// multiple packets with single msgtxid)
#define BCS_MAX_WDWLIST     (1500 / BCS_WDWENTSIZ)  
                                    // max # of window structure entry in msg

#define BCS_WDWENTSIZ       (sizeof (struct BCS_WDW_ENTRY))
                                    // size of a window entry (loc + wdw)

#define BCS_MAX_LOCLIST     (1500 / sizeof (unsigned int))
                                    // max # of location entry in msg

#define BCS_ACCNUM_LEN      16      // length of ascii acc field
#define BCS_TERMID_SIZ      8       // size of ascii terminal field
#define BCS_TSN_SIZ         17      // size of ascii rtsn field

#define BCS_REQ_ALL         0       // request for all centre or window
                                    // indicator

//
// defines for RCL
//
#define BCS_SESSION_END     0       // end of session (to be used in conidl)
#define BCS_CURRENT_SESS    0       // continue with current session
#define BCS_PREVIOUS_SESS   1       // skip to previous session

// defines for CV tracking
#define BCS_CVSTS_UNKNOWN   0       // unknown or not even a CV
#define BCS_CVSTS_PAY       1       // pay tx of a CV
#define BCS_CVSTS_SELL      2       // sell tx of a CV

struct BCS_WDW_ENTRY
{
    unsigned int     loclu;       // aka centre #, 0 = all
    unsigned short   wdwwu;       // 0 = all
};

struct BCS_EFO_REQ      // efo request
{
    unsigned short            accdep1:1;
    unsigned short            accwtw1:1;
    unsigned short            accbal1:1;
    unsigned short            bnkbal1:1;
    unsigned short            cvissu1:1;
    unsigned short            :11;
    BOOL                    rstmsnt;    // TRUE = reset required
    struct BCS_WDW_ENTRY    wdw[BCS_MAX_WDWLIST];
};

struct BCS_WDWLIST_REQ     // for efc, efs & svt sign off request
{
    struct BCS_WDW_ENTRY   wdw[BCS_MAX_WDWLIST];
};

struct BCS_SVTSGN_REQ       // svt sign on request
{
    BOOL                    rstmsnt;    // TRUE = reset required
    struct BCS_WDW_ENTRY    wdw[BCS_MAX_WDWLIST];
};

// CON is only available between emergency MAT and OLTP. It is implemented as
// a background message.
struct BCS_CON_REQ       // centre on request
{
    unsigned int        loclu;      // 0 for all
};

struct BCS_ENDSCV_REQ       // enable/disable CV ops request
{
    short   issue1:1;
    short   payout1:1;
    short   cashing1:1;
    short   :13;
};

struct BCS_TMHVCV_REQ       // enable/disable terminal high value CV request
{
    BOOL                    enablet;     // TRUE = enable
    struct BCS_WDW_ENTRY    wdw[BCS_MAX_WDWLIST];
};

struct BCS_TMPAYO_REQ       // enable/disable terminal payout request
{
    BOOL            enablet;        // TRUE = enable
    unsigned int    locidlu[BCS_MAX_LOCLIST];
};

struct BCS_RELTRM_REQ       // release term request
{
    unsigned int        loclu;       // aka centre #
    unsigned short      wdwwu;       // window
    char                termids[BCS_TERMID_SIZ];
};

struct BCS_EFTREL_REQ       // release eft
{
    unsigned int        loclu;       // aka centre #
    unsigned short      wdwwu;       // window
    char                termids[BCS_TERMID_SIZ];
};

struct BCS_EFTRCL_REQ       // recall eft
{
    unsigned int        loclu;       // aka centre #
    unsigned short      wdwwu;       // window
    char                termids[BCS_TERMID_SIZ];
};

struct BCS_TSN_REQ     // for stop pay, release stop pay, cancel release payout
                        // to branch, ticket enquiry, all-up explosion request
{
    char    rtsns[BCS_TSN_SIZ];
};

struct BCS_RPO_REQ      // release payout to branch request
{
    char            rtsns[BCS_TSN_SIZ];   
    unsigned int    locidlu;
};

struct BCS_RCL_REQ      // recall customer session request
{
    unsigned int        locidlu;
    unsigned short      wdwnumwu;
    char                termids[BCS_TERMID_SIZ];
    unsigned char       sessflagbu;
    unsigned char       numtxnbu;
    int                 conidl;
    char                logsysb;        // logging system
};

struct BCS_CVTREK_REQ   // CV tracking request
{
    char            rtsns[BCS_TSN_SIZ];
    unsigned char   statusbu;       // 0, 1 or 2 (see BCS_CVSTS_* defines)
    unsigned char   maxtxnbu;
    int             conidl;
    char            logsysb;        // logging system
};

struct BCS_CSH_CNTR     // cash counters structure
{
    unsigned int    raclu;          // gross racing sales
    unsigned int    lotlu;          // gross lottery sales
    unsigned int    cvlu;           // gross CV sales
    unsigned int    paylu;          // total payout
    unsigned int    canraclu;       // total racing cancel
    unsigned int    canlotlu;       // total lottery cancel
    unsigned int    cancvlu;        // total CV cancel
    int             tbdl;           // net TB dep
    unsigned int    esccdeplu;      // total ESC dep
    unsigned int    paydeplu;       // total payout deposit
    unsigned int    escwtwlu;       // total esc withdrawal
};

struct BCS_SHROFF_BAL       // shroff balance
{
  unsigned LONGLONG  totsaledu;      // total sales in cents
  unsigned LONGLONG  totpaydu;       // total pay-out in cents
  unsigned LONGLONG  totcandu;       // total cancels in cents
  LONGLONG           netbald;        // net balance in cents
  LONGLONG           escnetd;        // esc net balance in cents
  unsigned LONGLONG  cashindu;       // cash in (in cents)
  unsigned LONGLONG  cashoutdu;      // cash out (in cents)
  unsigned LONGLONG  msrdu;          // MSR in cents
  unsigned LONGLONG  mspdu;          // MSP in cents
};

#pragma pack()

#endif
