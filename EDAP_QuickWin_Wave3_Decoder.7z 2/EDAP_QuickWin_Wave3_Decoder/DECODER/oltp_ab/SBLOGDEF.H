//    *******************************************************************
//    *                                                                 *
//    *   (c) COPYRIGHT.  The Hong Kong Jockey Club                     *
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
//  Function:   This files define the structure used in logger file of 
//              OLTP-SB.
//
//  Author  :   Edward Hon      20-Aug-2001
//
//  Mod     :   PN01            24-JAN-2002
//              ( For Delta phase 2: Add message code for odds/bet total 
//                enquire.  Log record content is same as selling transaction. )
//              PN02            21-FEB-2002
//              ( store both after update image and before update image of 
//                a bet for cancel/payout transaction )
//              LY03            25-FEB-2002
//              (in case of LOG_ERR_INVMSG error, log the incoming terminal
//               data for the ease of trouble shooting)
//
//              eh04            08-aug-2002
//              cashbet
//              PN05            26-AUG-2002
//              ( add error information for rejected sell transaction )
//              LY06            22-OCT-2002
//              for OLTP-CB with SB
//              PW07            22-OCT-2002
//              for LOG AT message in SB
//              LY08            26-NOV-2002
//              for enhanced error messages with more details
//              RL09            19-DEC-2002
//              add enable/disable BCS logger.
//              enhance error messages with more detail
//              PN10            28-JAN-2003
//              add approval code for bet intercept
//              LY11            11-MAR-2003
//              add approval code entry no. for faster recovery
//              RL12            18-MAR-2003
//              expand log sequence range
//              PN13            9-JUN-2003
//              support large bet intercept to RM, remove approval code
//              LY14            26-JUN-2003
//              add selling area of CB
//              LY15            03-JUL-2003
//              add print bonus information flag
//              LY16            14-JUL-2003
//              remove norpy1 flag, no need of it with new communication
//              protocol
//              LY17            11-AUG-2003
//              store terminal type for both CB and TB bets
//              LY18            12-JAN-2004
//              stage 3
//              LY19            26-MAR-2004
//              stage 3A
//              LY20            10-SEP-2004
//              Q105, handle intercept
//

#ifndef SBLOGDEF_H
#define SBLOGDEF_H

#include <time.h>
#include "tsndef.h"
#include "betdef.h"
#include "sblogatdef.h"   //PW07
//#include "logsbcdef.h"
//#include "logothdef.h"    //RL09

#pragma pack(1)

struct SBLOGBTID                    // unique betting terminal id   LY06..
{
  unsigned char     sysbu;              // remote system #
  unsigned int      sysltnlu;           // remote system logical terminal #
};

union SBLOGTRMID                    // terminal id
{
  struct SBLOGBTID  btid;               // bt logical terminal id
  unsigned int      hwidlu;             // MAT hardware id
};                                      // ..LY06

struct SBLOGHDR         // log header
{
  short                 sizew;          // size in byte
  unsigned short        codewu;         // message code
    #define SBLOG_MSG_SELL      0       // sell
    #define SBLOG_MSG_CANCEL    1       // cancel
    #define SBLOG_MSG_UNDO_SELL 2       // undo sell
    #define SBLOG_MSG_UNDO_CAN  3       // undo cancel
    #define SBLOG_MSG_SBC       4       // soccer betting control req
    #define SBLOG_MSG_SYSCLS    5       // system close
    #define SBLOG_MSG_OBTENQ    6       // enquire odds and bet total   PN01
    #define SBLOG_MSG_STPPAY    7       // stop pay ticket
    #define SBLOG_MSG_RLSTPY    8       // release stop pay ticket
    #define SBLOG_MSG_RLPBRH    9       // release payout to branch
    #define SBLOG_MSG_CRPBRH    10      // cancel release payout to branch
    #define SBLOG_MSG_TKTENQ    11      // ticket enquiry
    #define SBLOG_MSG_AUPXPO    12      // all-up explosion
    #define SBLOG_MSG_PAY       13      // payout
    #define SBLOG_MSG_UNDO_PAY  14      // undo payout
    #define SBLOG_MSG_ENABCS    15      // enable/disable bcs service
    #define SBLOG_MSG_STSENQ    16      // status enquiry

    #define SBLOG_MSG_PADDER    999     // padder log record
  unsigned short        errwu;          // error code
  __time32_t                time;           // time
  unsigned int          lgslu;          // log sequence of rcvmsg.dat
  unsigned int          msnlu;          // msn                             RL12
  unsigned char         trmtypbu;       // terminal type
  union SBLOGTRMID      trmid;          // terminal id              LY06
  unsigned int          ltnlu;          // logical terminal #
  unsigned char          rcvmsg1:1;      // update rcvmsg.dat flag
//  unsigned int          norpy1:1;       // no reply to source system flag LY16
  unsigned char          reversed1:1;    // last transaction reversed flag  RL12
  unsigned char          prelog1:1;      // prelog flag                  PN13
  unsigned char          rm1:1;          // to RM system                 PN13
  unsigned char          :4;             // unused                       PN13 LY16
};

// PN05..
// LY18..
struct SBLOG_BET_ERR         // selling reject error info.          LY08
{
    unsigned char           poolbu;     // pool type
//ben    struct  SB_MATCH_ID     id;         // match ID
// ben add the following unsigned char
    unsigned char         daybu;                    // day of week
    unsigned char         matchbu;                  // match # within day
    unsigned short          selwu[2];   // selection                LY08
	unsigned int		  minibetval;
	unsigned char           levbu;      // the aup level number of reject max bet       // JC31
};
// ..LY18

struct SBLOG_BET_UPD        // bet file update information
{
  union TSN             tsn;
  unsigned int          blocklu;        // start block # to unit
  unsigned short        offwu;          // byte offset to bet in unit
  unsigned short        filewu;         // bet file # 
  unsigned char          oddsold1:1;     // odds out of date
  unsigned char          chgodds1:1;     // odds changed             PN13
  unsigned char          chgubet1:1;     // unit bet changed         PN13
  unsigned int          obinvlu;        // original base investment in dollar 
                                        // if unit bet is locally changed by
                                        // OLTP-SB
  unsigned char			:5;		// add by ben
};

// PN13..
struct SBLOG_IBET_CB
{
  LONGLONG              custotd;        // customer total
  LONGLONG              selltotd;       // shroff sell amount
};

struct SBLOG_IBET_AB
{
  LONGLONG              custotd;        // funds available for betting
  LONGLONG              foinvd;         // daily fixed odds investment  
};
union SBLOG_IBET_DETAIL
{
  struct SBLOG_IBET_CB cb;              // CB related information
  struct SBLOG_IBET_AB ab;              // AB related information
};

struct SBLOG_IBET           // information in prelog for intercept bet
{
  unsigned char         eventbu;        // all-up event # trigger the intercept
  union SBLOG_IBET_DETAIL detail;       // detail information
};
// ..PN13

union SBLOG_BET_INFO        // sell bet information
{
  struct SBLOG_BET_UPD  betupd;         // bet update information
  struct SBLOG_BET_ERR  err;            // error information        LY08
  struct SBLOG_IBET     ibet;           // intercept bet info. in prelog   PN13
};
    
struct SBLOG_BET_AC        // sell bet account information      PN13..
{
  unsigned char         sbtypbu;        // account sb type 
  unsigned char         actypbu;        // account type             
};

struct SBLOG_BET_CB         // CB sell bet information          LY14
{
  unsigned char         areabu;         // selling area
//  unsigned int          svt1:1;         // svt terminal       LY17
  unsigned char          hoterm1:1;      // ho terminal
  unsigned char          :7;      // add by ben
};

union SBLOG_BET_REQ
{
  struct SBLOG_BET_AC   acreq;          // account bet request information
  struct SBLOG_BET_CB   cbreq;          // cash bet request information LY14
};

struct SBLOG_BET        // sell details
{
  unsigned char          bonus1:1;       // print bonus information LY15
  unsigned char          svt1:1;         // svt terminal            LY17
  unsigned char          intercept1:1;   // intercept bet
  unsigned char          confirmed1:1;   // confirmed by customer
  unsigned char          rconfirm1:1;    // required to be confirmed by customer
  unsigned char          abort1:1;       // aborted by customer     LY20
  unsigned char          :2;             // unused                  LY17
  union SBLOG_BET_REQ   rinfo;          // request information          ..PN13
  union SBLOG_BET_INFO  info;           // info. on sell transaction  ..PN05
  struct BETSB          bet;            // bet record
};

struct SBLOG_CBET_REQ_CB        // extra request info. of cancel/pay req from cb
{
    unsigned char        svt1:1;     // SVT      LY06
    unsigned char        hoterm1:1;  // ho terminal flag
    unsigned char        hvpay1:1;   // high-value pay flag
    unsigned char        xtote1:1;   // external tote LY19
    unsigned char        :4;         // unused
    LONGLONG            shroffamtd; // shroff amount
    unsigned int        centrelu;   // pay/cancel centre
    LONGLONG            maxcvd;     // max. cv amount
    LONGLONG            payorid;    // pay at original centre limit LY06
};

union SBLOG_CBET_REQ
{
    struct SBLOG_CBET_REQ_CB    cb; // cb request
};                                                 

// PN02..
//
// This structure defines the bet stored in pay/cancel record.  After update
// image of the bet record is stored first, and immediately followed by the 
// before update image.
//
union SBLOG_CBET_BET
{
  struct BETSB          new1;            // updated image of bet record
  char                  bufb[sizeof(struct BETSB)*2];   
};

//..PN02

struct SBLOG_CBET       // cancel/payout
{
  union TSN             tsn;
  union TSN             newtsn;         // new tsn of partial pay [0 means it
                                        // is not a partial pay]
  unsigned int          blocklu;        // start block # to unit
  unsigned short        offwu;          // byte offset to bet in unit
  short                 filew;          // bet file number (-1 => shrink bet)
  unsigned LONGLONG     payoutdu;       // total payout in cents (this is the
                                        // amont to be paid in this
                                        // transaction)
  LONGLONG              custotd;        // funds available for betting/customer
                                        // total
  unsigned char          account1:1;     // account related cancel
  unsigned char          :7;             // unused
  union SBLOG_CBET_REQ  req;            // request information
  union SBLOG_CBET_BET  bet;            // after update image and before  PN02
                                        // update image of the bets       PN02
};

// LY03 start
struct SBLOG_ERR        // for logging incoming request in case of invalid
                        // msg format
{
  unsigned short        offsetwu;                   // offset of data when
                                                    // error occurs
  unsigned char         trmDatabu[450];  // incoming terminal data
};
// LY03 end

union SBLOGBTD          // bt transaction data
{
  struct SBLOG_BET      bet;        // selling/undo selling record
  struct SBLOG_CBET     ccp;        // cancel/pay/undo cancel/pay record
  // LY02
  struct SBLOG_ERR      error;      // error log in case of invalid msg format
};

// PW07 start

struct SBLOG_AT
{
  struct SBLOGHDR       hdr;        // standard header
  union  SBLOGATD       d;          // at transaction
};

// PW07 end

struct SBLOG_BT
{
  struct SBLOGHDR       hdr;        // standard header
  union  SBLOGBTD       d;          // data portion
};

union SBLOGDATA
{
  union  SBLOGBTD       bt;         // bt transaction
  union  SBLOGATD       at;         // at transaction        //PW07
//  struct LOGSBC         sbc;        // sbc transaction
  union  LOGOTH         oth;        // other transaction     //RL09
};

struct SBLOG
{
  struct SBLOGHDR       hdr;        // standard header
  union  SBLOGDATA      d;          // data
};

#pragma pack()

#endif
