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
//      Defines System Parameters explicitly used by CB.
//
//    Author : Edward Hon                01-NOV-2000
//
//    Mod : PN01                        14-JUN-2002
//          ( remove unused variable )

#ifndef   CBPARDEF_H
#define   CBPARDEF_H

#include "bstypedef.h"
#include "udtypedef.h"

#pragma pack(1)

struct CBPARBT                          // [SYSBVERB] BT version no.
{
    char               romb;        // BT ROM version no.
    char               ramb;        // BT RAM version no.
    char               printerb;    // BT Printer version no.
};

struct CBPARTBD
{
  unsigned LONGLONG     minamtdu;       // min. telebet deposit amt (PARMTBDR)
  struct BSTTIMRNG      time[2];        // Telebet dep time duration (PARSTBDW, 
                                        // PARETBDW) stored in __time32_t 
                                        // structure.  Date stored in this 
                                        // variable will be ignored for
                                        // validation.  Since user can enter
                                        // time > 24:00, we use two element
                                        // to store the range e.g.
                                        // 0800 to 2030 
                                        // => time[0].start = 08:00:00
                                        //    time[0].end   = 20:30:00
                                        //    time[1].start = 00:00:01
                                        //    time[1].end   = 00:00:00
                                        // 0800 to 2630
                                        // => time[0].start = 08:00:00
                                        //    time[0].end   = 23:59:59
                                        //    time[1].start = 00:00:00
                                        //    time[1].end   = 02:30:00
                                        // 0800 to 2400
                                        // => time[0].start = 08:00:00
                                        //    time[0].end   = 23:59:59
                                        //    time[1].start = 00:00:00
                                        //    time[1].end   = 00:00:00
};

// structure declarations

struct CBPAR 
{
        unsigned LONGLONG  phldu;   // pay at head office limit (PARPHLR)
        unsigned LONGLONG  pocdu;   // pay at original centre limit(PARPOCR)
        unsigned LONGLONG  mcvvdu;  // max. normal CV value (PARMCVVR)
        unsigned LONGLONG  msvcvdu; // svt max. cv amount (PARMSVCVR)
        unsigned LONGLONG  opcvdu;  // opt max. cv amount (PARMOPCVR)
        unsigned int       remcvlu; // raceday EFT min.cv limit($)(PAREMCVW) 
        unsigned int       nremcvlu;// non-raceday EFT min.cv limit($)(PAREMCVW)
        BOOL               cret;      // cv issue enable flag (PARCRET)
        BOOL               cvpayet; // cv payout disable flag
        BOOL               cvcshet; // cv cashiing disable flag
        char               secshtb; // eft tb security code shift
        struct CBPARTBD    tbdep;   // telebet deposit, this should be 
                                    // removed and validated by OLTP-AB after
                                    // migration of all legacy account betting 
                                    // system completes.
};

#pragma pack()

#endif // CBPARDEF_H
