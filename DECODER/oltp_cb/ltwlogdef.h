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
//      LTWLOGDEF.H   -   lottery winner log record layout
//
//      Author : Edward Hon                01-NOV-2000
//
//      Mod :
//
#ifndef LTWLOGDEF_H

#define LTWLOGDEF_H 1

// info from EXWLOG

#include <time.h>

#include "udtypedef.h"
#include "mailwcdef.h"
#include "betdef.h"
#include "rdsdef.h"
#include "lotdef.h"

#pragma nomember_alignment


struct  LTWKEY      // lottery key
    {
    unsigned short      typewu;             // lottery type
    unsigned short      drawwu;             // draw #
    unsigned short      yearwu;             // year
    struct LOTDNO       res[LOT_MAXDNO];    // result
    };

struct  LTWSUBGAME              // per sub-game type info
    {
    unsigned LONGLONG   invdu;  // investment in cents to this draw
    unsigned LONGLONG   nxtinvdu;       // investment in cents
                                                // to next draw due to multi-draw ticket
    };

struct  LTWWIN      // lottery winning
    {
    unsigned LONGLONG   tktdu;      // # of tickets
    unsigned LONGLONG   windu[LOT_MAXPRZ];      // winning investment in cents
    struct LTWSUBGAME   subgame[LOT_MAXSUBGAME];        // per sub-game information
    };

struct LTWWLIST    // winner list
    {
    unsigned int        numlu;          // # of winners
    struct BET          winner[MAIL_EXW_MAXWIN];
    };

struct  LTWREC          // winner record
    {
    time_t              reqtim;     // time stamp for exotic winer req.
    struct LTWKEY       key;
    struct LTWWIN       win;
    struct LTWWLIST     wlis;       // winner list
    };

// No. of blocks to be read in one qio to ltwlog
#define LTW_READLOGBLKSIZ (sizeof(struct LTWREC)) // No. of bytes read in one
                                                  // qio
#define LTW_READLOGBLK ( (LTW_READLOGBLKSIZ + 511 ) / 512 )

#pragma member_alignment

#endif
