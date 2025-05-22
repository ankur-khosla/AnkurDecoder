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
//  Function: This is a header file for checkpoint files in OLTP-CB system.
//            Four files will be checkpointed by BTHNDR during checkpoint 
//            processing:
//              COLLAT.DAT - collation information
//              CKPMAT.DAT - TDT information for MAT
//              CKPBT.DAT  - TDT information for BT
//              CKPCTL.DAT - control information for checkpoint
//              
//            All files have two records to ensure that there is always
//            a complete set of information of last checkpoint.  CKPCTL.DAT
//            will be the last one to checkpoint.  Time field in CKPCTL.DAT
//            determines which record is the latest one for recovery.
//            
//
//  Author  : Pauline Ng        23-OCT-2000
//  Mod     : RL01              21-AUG-2002
//            . cash counter total pay out changed to 64 bits
//

#ifndef CKPDEF_H
#define CKPDEF_H

// info from MARKER

#include <time.h>
#include "cbdef.h"
// #include "abdef.h"
#include "lotdef.h"
// #include "bfcdef.h"

#pragma pack(1)

struct  CKPCSH                  // cash counters (in cents) for individual 
{                               // terminal session
  unsigned int  raclu;          // total racing sale (gross)
  unsigned int  cvlu;           // total cash voucher sale (gross)
  unsigned int  lotlu;          // total lottery sale (gross)
  unsigned int  tbdlu;          // total tb deposit (gross)
  unsigned int  canraclu;       // total cancelled racing ticket
  unsigned int  cancvlu;        // total cancelled cash voucher sale
  unsigned int  canlotlu;       // total cancelled lottery sale
  unsigned int  cantbdlu;       // total cancelled tb deposit
  LONGLONG      payd;           // total payout
  unsigned int  paydeplu;       // payout deposit
  unsigned int  esccdeplu;      // esc cash deposit
  unsigned int  esccwtwlu;      // esc cash withdrawal
};
/*
struct  CKPBT           // bt checkpoint info record
{
  int                   lgsl;   // Last log sequence for all transactions
                                // with reply sent back to terminal.  This
                                // will be updated for all types of
                                // transaction sent to bt such as eft, esc,
                                // and bt transaction.  Exception is not
                                // included.
  int                   btlgsl; // last log sequence for reply message sent
                                // to bt ( excluding eft transaction and 
                                // exception ).
                                // [<0 released] 
  int                   eftlgsl;// last log sequence for eft tran
  int                   esclgsl;// last log sequence for esc tran
  int                   bcslgsl;// last log sequence for bcs tran
  int                   stflgsl;// last log sequence for shroff sign on
                                // (this is used for recovery for staff info.)
  struct CKPCSH         csh;    // cash positions
  unsigned int          ismsnlu[AB_MAXSYS]; // intersystem msn per account bet
                                            // system
};
*/
struct  CKPAT           // at checkpoint info record
{
  int           lgsl;   // last log sequence [<0 released]
  int           lotl;   // net lottery sale
};

struct  CKPXCHD         // cross cashing detail
{
  int                 lgsl;     // last log sequence [<0 reversed]
  unsigned LONGLONG   candu;    // cancel amount (in cents)
  unsigned LONGLONG   paydu;    // payout amount (in cents)
};

struct  CKPXCH          // cross cashing info
{
  struct CKPXCHD      to;       // to other system (update by payout initiator)
  struct CKPXCHD      from;     // from other system (update by payout 
                                // processor)
};

struct  CKPTBD          // tb deposit info
{
  int                 lgsl;     // last log sequence
  unsigned LONGLONG   tbddu;    // sell amount (in cents)
  unsigned LONGLONG   candu;    // cancel amount (in cents)
};

struct  CKPEFT          // eft
{
  int                 lgsl;     // last log sequence
  unsigned LONGLONG   acddu;    // instant account deposit done (in dollar)
  unsigned LONGLONG   acwdu;    // instant account withdrawal done (in dollar)
  unsigned LONGLONG   cvdu;     // cv done (in dollar)
};

struct CKPESC
{
  unsigned int  paydeplu;       // payout deposit (in cents)
  unsigned int  esccdeplu;      // esc cash deposit (in cents)
  unsigned int  esccwtwlu;      // esc cash withdrawal (in cents)
  unsigned char  enable1:1;     // esc service enable flag
  unsigned char  :7;            // unused
  unsigned short rejpaydepwu;   // no. of rejected esc payout deposits
};

//
// This structure defines the information required to checkpoint for those
// background message sending to BCS. Log sequence is used to derive the
// location of a message.  Block number = Log sequence / 512, offset in
// the block = Log sequence % 512.  Log sequence of first record will be
// 1024.  
//
struct CKPBCS
{
  int   nxtlgsl;        // log sequence of next message to be put in BCSMSG.DAT.
                        // This variable will be updated after log complete of
                        // any log record have message to be sent to BCS.

  int   sndlgsl;        // log sequence of next message in BCSMSG.DAT to 
                        // be sent to bcs (those messages with log sequence 
                        // < this variable are already acknowledged by bcs)
                        // This variable will be updated by BCSHNDR and
                        // checkpointed by BTHNDR.
};
/*
struct  CKPCTL  // checkpoint control record format [should be written last]
{
  unsigned int          btnlu;  // # of bt
  unsigned int          atnlu;  // # of at
  int                   rcvlgsl;// last log sequence of message in RCVMSG.DAT
  struct CKPBCS         bcsmsg; // message to BCS
  struct CKPESC         ckpesc[AB_MAXSYS];  // esc service information
  struct CKPXCH         xch[CB_MAXSYS][CB_MAXXCHCHAN];// cross cashing
  struct CKPTBD         tbd[AB_MAXSYS][CB_MAXTBDCHAN];// tb deposit
  struct CKPEFT         eft[AB_MAXSYS][CB_MAXEFTCHAN];// eft
  struct BFCLASTREC     bet;    // last bet record checkpointed to disk
  unsigned int          eftena1:1;// eft enabled today
  unsigned int          :15;    // unused
  __time32_t                timelu; // time
  int                   lgsl;   // last log sequence of the checkpoint
};
*/
//
// size of single checkpoint record
//
#define CKP_MAT_REC_SIZE ((sizeof(struct CKPAT)*CB_MAXAT+511)/512) 
#define CKP_BT_REC_SIZE  ((sizeof(struct CKPBT)*CB_MAXBT+511)/512)
#define CKP_CTL_REC_SIZE ((sizeof(struct CKPCTL)+511)/512)

//
// size of corresponding checkpoint file
//
#define CKP_MAT_FIL_SIZE (2*CKP_MAT_REC_SIZE+1)
#define CKP_BT_FIL_SIZE  (2*CKP_BT_REC_SIZE+1)
#define CKP_CTL_FIL_SIZE (2*CKP_CTL_REC_SIZE+1)

#pragma pack()

#endif
