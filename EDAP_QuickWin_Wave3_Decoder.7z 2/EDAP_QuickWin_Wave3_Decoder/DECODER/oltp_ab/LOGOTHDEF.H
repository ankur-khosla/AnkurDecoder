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
//    Function: This is logger record defines for other miscellaneous
//              transaction type.
//
//    Author  : Pauline Ng               13-DEC-2000
//
//    Mod     : RL01                     29-DEC-2002
//              ( OLTP-CB with SB. remove force close down structure )
//              RL02                     12-OCT-2004
//              ( add close for enquiry flag to AB system close logger )
//
#ifndef LOGOTHDEF_H
#define LOGOTHDEF_H
#include "lotdef.h"

#pragma pack(1)

struct  LOGOTHSRV               // enable / disable service
{
    unsigned short syswu;       // system number of corresponding system
    unsigned short bupsyswu;    // back up system number for bcs when it is
                                // disabled
    unsigned char enable1:1;   // enable flag
    unsigned char :7;          // unused
};

struct LOGOTHAPS                // allup pass done record
{
    unsigned short indexwu;     // meeting index
    unsigned short racewu;      // race number
};

struct LOGOTHLWPS               // lotter winner pass record
{
    unsigned short lotidxwu;    // lottery index in lotcom
    unsigned short bfcidxwu;    // lottery index in bfccom
    unsigned LONGLONG nxtinvdu[LOT_MAXGAME];
                                // collations
};

struct LOGOTHEFTGW              // change EFTGW
{
  unsigned char sysbu;          // system to use (1 or 2)
};

// RL02..
struct LOGOTHSYSCLS             // system close
{
    unsigned short  clsenq1:1;      // system close for enquiry
};
// ..RL02

union LOGOTH
{
    struct LOGOTHSRV     service;
    struct LOGOTHAPS     auppss;
    struct LOGOTHLWPS    lotwpss;
    struct LOGOTHEFTGW   eftgw;
    struct LOGOTHSYSCLS  syscls;    // RL02
};

#pragma pack()

#endif
