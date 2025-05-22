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
//  Function:   This files define the AT message structure used in logger 
//              file of OLTP-SB.
//
//  Author  :   Philip Woo      22-Oct-2002
//
//  Mod     :   
//

#ifndef SBATLOGDEF_H
#define SBATLOGDEF_H

#include "tsndef.h"
#include "betdef.h"

#pragma pack(1)

struct  SBLOGATENQ        // ticket enquiry
{
    union TSN       tsn;        // tsn
    unsigned char   tsnindbu;   // tsn or ref indicator
    struct BETSB    bet;        // bet record of the ticket
    BOOL            claimt;     // FALSE if no claimed dividend
    LONGLONG        claimdivd;  // claimed dividend
};

struct SBLOGATRPO         // release payout to branch
{
    unsigned char       tsnindbu;       // tsn or ref indicator
    union TSN           tsn;            // tsn
    unsigned int        locidlu;        // location id, aka centre #
    struct BETSTS       sts;            // new bet status
                                        // Filled in by BTHNDR
    unsigned int        blocklu;        // block no. in bet file
    unsigned short      offwu;          // byte offset within block
    short               filew;          // file # (-1 means shrunk bfc index)
    struct BETSB        bet;            // bet record 
                                        // Filled in by BTHNDR
};

struct SBLOGATTSN       // for stop pay, release stop pay, cancel release
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
    struct BETSB        bet;            // bet record 
                                        // Filled in by BTHNDR
};

union SBLOGATD     // AT transaction data
{
    struct SBLOGATTSN     tsnref; // stop pay, cancel stop pay, cancel release 
    struct SBLOGATENQ     enq;    // ticket enquiry, allup explosion
    struct SBLOGATRPO     rpo;    // release pay
};

#pragma pack()

#endif


