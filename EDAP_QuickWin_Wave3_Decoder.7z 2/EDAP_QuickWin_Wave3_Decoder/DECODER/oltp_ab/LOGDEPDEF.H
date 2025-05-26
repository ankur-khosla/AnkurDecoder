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
//    LOGDEPDEF.H - Defines the structures of DEPHNDR Logger records
//
//    Author    :   Vicki Chung
//
//    Date      :   29 July, 2003
//
//    Mod :     :   PN01        9-NOV-2004
//                  ( add defines for batch file conversion completion )
//                  RL02       15-MAR-2005
//                  SQ#24662
//                  ( add bankcode to logger for formatting report, exception... )
//
#ifndef LOGDEPDEF_H
#define LOGDEPDEF_H 1

#include "aadef.h"

#pragma pack(1)

struct LOGDEPTRAN                           // Reject or posting request
{
    struct AA_REJBATDEPSUB      data;       // Mail data
    unsigned int                feelu;      // recharge fee (in cents)
    unsigned int                seqlu;      // internal seq. #
    unsigned char               chanbu;     // channel #
    char                        bankcode[3];// Bank code (can be space)  // RL02
};

struct LOGDEPCOMPCNV
{
    __time32_t              valdat;     // value date
    __time32_t              caldat;     // calender date
    unsigned char       typebu;     // batch deposit work file type
    unsigned int        batnumlu;   // batch number
    unsigned int        firreclu;   // first record number converted
    unsigned int        lastreclu;  // last record number converted
};

// PN01..
union LOGDEPCOMPD
{
    struct LOGDEPCOMPCNV        start;  // conversion complete and start posting
    struct AA_OLTP_BATDEPSUM    end;    // end of posting result
};
// ..PN01

struct LOGDEPCOMP                           // Complete Summary
{
    BOOL                        startt;     // Flag to indicate posting of this
                                            // file will begin (conversion has
                                            // finished)
    unsigned int                filidxlu;   // File index in DEPCTL (start fr 0)
    union LOGDEPCOMPD           sum;        // summary log details      PN01
};

union LOGDEP                                // DEPHNDR Logger record
{
    struct LOGDEPTRAN           tran;       // DEPHNDR reject or posting request
    struct LOGDEPCOMP           comp;       // DEPHNDR complete summary
};

#pragma pack(1)

#endif
