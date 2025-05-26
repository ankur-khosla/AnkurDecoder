//
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
//    LOGHDRDEF.H - defines logger header; it is extracted from logdef.h
//      so that logatdef.h can include this file instead of logdef.h;
//      having logatdef.h to include logdef.h results in compilation error 
//      of having 2 files including each other.
//
//    Author : Eddie Chu        27-Jan-2001
//
//    Mod : PN01            12-AUG-2002
//          ( remove unsolicited terminal balance log message code for OLTP-CB )
//          EH02            08-aug-2002  
//          ( soccer betting )
//          RL03            18-MAR-2003
//          ( expand log sequence range )
//          LY04            13-MAY-2003
//          ( add new rejected message code )
//          PW05            23-AUG-2003
//          ( add new status enquiry message code )
//          PN06            7-NOV-2003
//          ( fix bug in getting dll package number as terminal type )
//          LY07            25-FEB-2004
//          ( add new change password message code )
//          RL08            09-MAR-2004
//          ( add BT and ESC interface for OLTP-AB )
//          RL09            28-JUN-2004
//          ( .service improvement when BCS-BA is disabled
//            .add logger code for centre off
//            .add logger code for assign head office branch )
//          LY10            16-AUG-2004
//          ( add new BT transactions )
//

#ifndef LOGHDRDEF_H
#define LOGHDRDEF_H

#include "udtypedef.h"
#include <time.h>

#pragma pack(1)

struct LOGPCH                   // pseudo channel used in inter-system
                                // communication
{
  unsigned short       syswu;   // system number
  unsigned short       chanwu;  // channel number
};

union LOGLTN                    // logical terminal number in logger file
{
  unsigned int          trmlu;  // logical terminal number
  struct LOGPCH         iscom;  // inter-system communication channel  
};

struct  LOGTRMFLG       // terminal flag in request (8 bits)
{
  unsigned char     loop1:1;    // loop back mode
  unsigned char     retry1:1;   // retry flag
  unsigned char     samecus1:1; // same customer 
  unsigned char     dllpkt3:3;  // dll package number           PN06..
    #define LOG_DLL_OPT     1   // package # for operator bt
    #define LOG_DLL_SVT     3   // package # for svt or dm5/7/9 bet gen
  unsigned char     bit61:1;    // bit 6 always set             ..PN06
  unsigned char     :1;         // dummy
};

struct  LOGHDR          // log header
{
  short                 sizew;          // size in byte
  unsigned short        codewu;         // message code
                                        // transaction from betting terminal
    #define LOG_MSG_ILL         0       // Illegal message code
    #define LOG_MSG_SGN         1       // sign on
    #define LOG_MSG_SGF         2       // sign off
    #define LOG_MSG_BET         3       // bet
    #define LOG_MSG_LOT         4       // lottery
    #define LOG_MSG_CSHI        5       // cash in
    #define LOG_MSG_CSHO        6       // cash out
    #define LOG_MSG_CAN         7       // cancel
    #define LOG_MSG_PAY         8       // payout
    #define LOG_MSG_RDT         9       // rdt request
    #define LOG_MSG_TBD         10      // telebet deposit
    #define LOG_MSG_CVI         11      // cv issue
    #define LOG_MSG_CVC         12      // cv cash
    #define LOG_MSG_ACA         13      // account access
    #define LOG_MSG_ACR         14      // account release
    #define LOG_MSG_DEP         15      // deposit (after account access)
    #define LOG_MSG_WTW         16      // withdrawal
    #define LOG_MSG_RCL         17      // account recall
    #define LOG_MSG_ENQ         18      // transaction enquiry
    #define LOG_MSG_ACOPEN      19      // account open / card issue
    #define LOG_MSG_CRDREP      20      // card replacement
    #define LOG_MSG_CLS         21      // account close
    #define LOG_MSG_DTLUPD      22      // account details update
    #define LOG_MSG_DTLENQ      23      // account details enquiry
    #define LOG_MSG_SVTWNR      24      // unsolicited svt warning message
    #define LOG_MSG_SVTSER      25      // unsolicited svt severe error message
    #define LOG_MSG_SB          26      // soccer betting
    #define LOG_MSG_SBENQ       27      // soccer betting total enquiry
    #define LOG_MSG_REJMSG      28      // rejected message
    #define LOG_MSG_CHGPWD      29      // change password LY07

                                        // transaction from eft terminal
    #define LOG_MSG_EFTSTR      30      // start of eft transaction number
    #define LOG_MSG_EFTDEP      30      // eft deposit
    #define LOG_MSG_EFTWTW      31      // eft withdrawal
    #define LOG_MSG_EFTACB      32      // eft account balance enquiry
    #define LOG_MSG_EFTCVI      33      // eft cv issue request
    #define LOG_MSG_EFTBKB      34      // eft bank balance enquiry
    #define LOG_MSG_EFTXBT      35      // eft transfer for betting
    #define LOG_MSG_EFTINI      36      // eft terminal initialisation
    #define LOG_MSG_EFTSTSP     37      // eft status reply 
    #define LOG_MSG_EFTSER      38      // eft severe error 
    #define LOG_MSG_EFTUNK      39      // unknown eft transaction type
    #define LOG_MSG_EFTEND      39      // end of eft transaction number

    #define LOG_MSG_BTTRMRCL    40      // terminal recall from BT        LY10
    #define LOG_MSG_BTTKTENQ    41      // ticket enquiry from BT         LY10

    // transactions for OLTP-AB
    #define LOG_MSG_CANTRN      50      // cancel by transaction number   RL08
    #define LOG_MSG_STM         51      // account statement request      RL08
    #define LOG_MSG_CHGSCD      52      // account security code change   RL08
    #define LOG_MSG_ESCISS      53      // integrated account ESC issue   RL08
    #define LOG_MSG_ESCREP      54      // integrated account ESC replace RL08
    #define LOG_MSG_ESCRET      55      // integrated account ESC return  RL08

                                        // transaction from MAT via BCS
    #define LOG_MSG_EFTOPN     101      // open eft
    #define LOG_MSG_EFTCLS     102      // close eft
    #define LOG_MSG_EFTSTS     103      // request eft status
    #define LOG_MSG_SVTSGN     104      // SVT sign on request
    #define LOG_MSG_SVTSGF     105      // SVT sign off request
    #define LOG_MSG_ENADCV     106      // enable/disable cash voucher
    #define LOG_MSG_TMHVCV     107      // enable/disable terminal high value CV
    #define LOG_MSG_TMPAYO     108      // enable/disable terminal payout
    #define LOG_MSG_RELTRM     109      // release betting terminal
    #define LOG_MSG_EFTREL     110      // release eft
    #define LOG_MSG_EFTRCL     111      // eft recall
    #define LOG_MSG_STPPAY     112      // stop pay ticket
    #define LOG_MSG_RLSTPY     113      // release stop pay ticket
    #define LOG_MSG_RLPBRH     114      // release payout to branch
    #define LOG_MSG_CRPBRH     115      // cancel release payout to branch
    #define LOG_MSG_TRMRCL     116      // terminal recall
    #define LOG_MSG_CVTREK     117      // CV tracking
    #define LOG_MSG_TKTENQ     118      // ticket enquiry
    #define LOG_MSG_AUPXPO     119      // all-up explosion
    #define LOG_MSG_TRMBAL     120      // request terminal balance
    #define LOG_MSG_KEYCAN     121      // key pad cancel
    #define LOG_MSG_CON        122      // centre on
    #define LOG_MSG_COF        123      // centre off             RL09
    #define LOG_MSG_HOTERM     124      // assign H.O terminal    RL09

                                        // other log transaction
    #define LOG_MSG_REVPC      201      // reverse pay/cancel
    #define LOG_MSG_SYSCLS     202      // system close
    #define LOG_MSG_ENAESC     203      // enable/disable esc service
    #define LOG_MSG_ENABCS     204      // enable/disable bcs service
    #define LOG_MSG_WC         205      // wagering control transaction
    #define LOG_MSG_REVBCS     206      // reverse bcs request reply
    #define LOG_MSG_FRCSGF     207      // forced sign off
    #define LOG_MSG_APSDONE    208      // all-up post race pass done
    #define LOG_MSG_BCSCLS     209      // bcs system close
    #define LOG_MSG_ENAEFT     210      // enable eft service
    #define LOG_MSG_LOTWPS     211      // lottery winner pass
    #define LOG_MSG_SBC        212      // sb control transaction
    #define LOG_MSG_REVSB      213      // reverse sb transaction
    #define LOG_MSG_ENASB      214      // enable/disable sb service
    #define LOG_MSG_SBCLS      215      // sb system close
    #define LOG_MSG_STSENQ     216      // status enquiry

    #define LOG_MSG_PADDER     999      // padder log record

  __time32_t                timelu;         // time
  unsigned int          lgslu;          // last log sequence for BT/MAT
                                        // terminal type; for other terminal
                                        // type, this field may be used to
                                        // store the corresponding log message
                                        // of rcvmsg.dat - RL03
  unsigned int          stfl;           // staff #
  union LOGLTN          ltn;            // logical terminal number
  unsigned short        errwu;          // error - see logcomdef.h
  unsigned char         trmtypbu;       // terminal type - see logcomdef.h
  unsigned int          centrelu;       // centre number
  unsigned short        windowwu;       // window number
  struct LOGTRMFLG      btflagbu;       // betting terminal flag in request
  unsigned int          prelog1:1;      // prelog
  unsigned int          laterpy1:1;     // late reply (reverse is required,
                                        // msnlu saves the transaction id
                                        // to be reversed)
  unsigned int          timeout1:1;     // external request timeout (for bcs
                                        // request, lgslu is the transaction id
                                        // to be enquired / reversed)
  unsigned int          rcvmsg1:1;      // update rcvmsg.dat flag
  unsigned int          btexc1:1;       // bt exception transaction, do not
                                        // update last activity of
                                        // corresponding tdtbt entry (this
                                        // include late reply, reverse reply,
                                        // non-msn protect transaction,
                                        // unsolicited transaction done for
                                        // corresponding bt, etc. )
  unsigned int          othsys1:1;      // reply from other system, we need to
                                        // update corresponding last log
                                        // sequence
  unsigned int          bcsmsg1:1;      // update bcsmsg.dat flag
  unsigned int          accmod1:1;      // account is accessed flag (set when
                                        // account access is successful, clear
                                        // this bit in the account release
                                        // or release terminal log record)
  unsigned int          paydep1:1;      // payout deposit flag (this is used
                                        // to distinguish whether the pre-log
                                        // transaction is for cross-cashing or
                                        // payout deposit to account bet system
  unsigned int          fakrej1:1;      // fake reject transaction for eft
  unsigned int          sb1:1;          // to SB system
  unsigned int          :5;             // unused bit (for future expansion)
  unsigned int          acclu;          // account #
  unsigned int          hwidlu;         // hardware id
  unsigned int          msnlu;          // msn/tran-id
  unsigned int          trxnlu;         // transaction number in account
  unsigned char         febu;           // frontend #
  unsigned char         linebu;         // line #
  unsigned char         dropbu;         // drop address
  LONGLONG              custotd;        // customer total
  LONGLONG              acctotd;        // account toal
};

#define LOG_HDR_SIZE sizeof( struct LOGHDR )

#pragma pack()

#endif
