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
// Function : This is a header file for common data type defines for
//            OLTP betting system.
//
// Author   : Pauline Ng        29-NOV-2000
//
// Mod.     : PN01              12-SEP-2002
//            ( define area code )
//            LY02              26-NOV-2002
//            for enhanced error messages with more details
//            PN03              9-JUN-2003
//            ( move partial unit bet structure from rdsdef.h to this header
//              file )
//            LY04              26-FEB-2004
//            ( add more status flag to terminal )
//
//            JC05              13-APR-2004
//            split BST_AREA_DID(1) to BST_AREA_CIT(1) and BST_AREA_EWIN(6)
//            PN06              29-NOV-2005
//            ( add dynamic memory buffer allocation pointer data structure )
//
#ifndef BSTYPEDEF_H
#define BSTYPEDEF_H

#include <time.h>

#pragma pack(1)

struct BSTCBTSTA                // cb terminal status
{
  unsigned int signon1:1;       // sign on
  unsigned int ctron1:1;        // centre on
  unsigned int svt1:1;          // svt
  unsigned int onc1:1;          // on-course
  unsigned int highcv1:1;       // high value cv 
  unsigned int btbusy1:1;       // bt transaction busy flag
  unsigned int eftbusy1:1;      // eft transaction busy flag
  unsigned int keycan1:1;       // key pad cancel allowed 
  unsigned int dsbpay1:1;       // disable payout flag
  unsigned int hoterm1:1;       // ho terminal flag
  unsigned int xtote1:1;        // x tote branch flag       LY04
  unsigned int dsblot1:1;       // disable lottery flag     LY04
  unsigned int dsbsb1:1;        // disable sb flag          LY04
  unsigned int dsbcv1:1;        // disable cv flag          LY04
  unsigned int dsbrace1:1;      // disable racing flag      LY04
  unsigned int dsbtbd1:1;       // disable tb deposit flag  LY04
};

struct  MTGPZSTS        // meeting prize status
{
    unsigned int        div1:1;                 // div in
    unsigned int        ovfl1:1;                // overflow
    unsigned int        clm1:1;                 // claim
    unsigned int        dfix1:1;                // div fixed
    unsigned int        part1:1;                // dividend in partial unit
    unsigned int        unoff1:1;               // unofficial dividend
    unsigned int        :12;                    // unused
};

struct  LOTPZSTS        // lottery prize status
{
    unsigned int        div1:1;                 // div in
    unsigned int        ovfl1:1;                // overflow
    unsigned int        clm1:1;                 // claim
    unsigned int        dfix1:1;                // div fixed
    unsigned int        na1:1;                  // prize not applicable 
    unsigned int        :11;                    // unused
};

struct BSTTIMRNG        // time range
{
    __time32_t  start;                  // start time
    __time32_t  end;                    // end time
};

struct BSTDATE          // Date format
{
    char   day;         // Day of month, 1-31
    char   month;       // Month, 1-12
    short  year;        // Year, 9999
};

// PN01..
// defines for area code            
#define BST_AREA_VOICE   0              // TB voice
#define BST_AREA_CIT     1              // CIT                              // JC05
#define BST_AREA_ESC     2              // ESC
#define BST_AREA_ONC     3              // on-course
#define BST_AREA_OFC     4              // off-course
#define BST_AREA_EWIN    5              // eWin                             // JC05
#define BST_AREA_CUR     6              // max. # of betting area in use    // JC05
#define BST_AREA_MAX     10             // max. # of betting area

struct BSTPOLAREA                       // area control of pool
{
    unsigned int def1:1;                // pool defined
    unsigned int sel1:1;                // pool in selling
    unsigned int sold1:1;               // pool has been on sale    LY02
    unsigned int :5;                    // unused                   LY02
};
// ..PN01
// PN03..
struct  BSTPUBET                // partial unit bet control parameter
{
    unsigned int mtotcstlu;     // minimum total cost in cents
    unsigned int munitlu;       // minimum bet unit in $
};
// ..PN03

#pragma pack(1)

// PN06..
struct  BSTMEMPTR               // dynamic memory buffer pointer
{
    unsigned int    startlu;    // memory buffer start in byte
    unsigned int    sizelu;     // memory buffer size in byte
};
// ..PN06

#endif
