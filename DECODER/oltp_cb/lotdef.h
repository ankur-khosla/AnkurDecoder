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
//    LOTDEF.H   -   lottery common defines
//
//    Author : Edward Hon                01-NOV-2000
//
//    Mod :
//
//      EH01 - lottery 7th prize
//
//      FT02    31-JAN-2002
//      - add define LOT_MAXGAME_CUR
//
//      JC03    08-MAY-2002
//      add define for no. of prizes of goldball normal game
//
//      FT04    26-JUL-2002
//      add unsettled liability by lottery type
//
//      FT05    4-SEP-2002
//      - remove conclude bit from lotcom
//        (the conclude bit will never been set since once a draw is
//         concluded at eod, the whole lotcom area will be init to 0)
//      PN06    12-SEP-2002
//      ( use area control structure for pool defined and selling )
//
//      RL07    08-NOV-2002
//      ( add lottery ccg min/max selection range defines )
//
//      FT08    18-NOV-2002
//      ( add lottery winner pass done flag
//        - this flag will be set by BTHNDR when BTHNDR receives winner pass
//          done reply from LOTWPS
//        - at system close, the close process will check if a draw is
//          result in but winner pass not yet done, then close process
//          will be aborted. This is to make sure multi draw next draw 
//          investment is updated properly by winner pass before system close)
//
//      PN09    16-MAR-200
//      ( remove unreferenced variable )
//
//      JC10    27-SEP-2004
//      add game started pay flag
//
//      AL11    29-NOV-2005
//      change LOT_MAXMDRAW from 10 to 30 in Q206
//
//      CS12    03-NOV-2005
//      modify to support advanced snowball draw selling
//      - define flag for indicate snowball draw, master draw and slave draw
//      - add master and slave draw index
//        if slave draw merge to master draw, update master draw index no. in 
//        slave draw with draw index + 1, as index no. initialize with 0 
//        when not used. So if both index = 0, no draw merged.
//      - add index number of description reference table map
//      - add variable for draw's short name
//      - add default snowball draw index
//      - add define for max. no. of subgame per game
//
#ifndef LOTDEF_H
#define LOTDEF_H

// info from RDSCOM.DAT/RDSCHL

#include <time.h>

#include "udtypedef.h"
#include "bstypedef.h"

#define LOT_MAXDNO  10  // # of result
#define LOT_NODNO   6       // no. of drawn nos.
#define LOT_NOENO   1       // no. of extra no.

#define LOT_MAXPRZ  100 // # of prizes
#define LOT_PRZ_NOR1    0   // normal 1st prize
#define LOT_PRZ_NOR2    1   // normal 2nd prize
#define LOT_PRZ_NOR3    2   // normal 3rd prize
#define LOT_PRZ_NOR4    3   // normal 4th prize
#define LOT_PRZ_NOR5    4   // normal 5th prize
#define LOT_PRZ_NOR6    5   // normal 6th prize
#define LOT_PRZ_AON1    6   // addon prize
#define LOT_PRZ_OEG2    7   // odd-even 2-row prize
#define LOT_PRZ_OEG3    8   // odd-even 3-row prize
#define LOT_PRZ_OEG4    9   // odd-even 4-row prize
#define LOT_PRZ_OEG5    10  // odd-even 5-row prize
#define LOT_PRZ_OEG6    11  // odd-even 6-row prize
#define LOT_PRZ_OEG7    12  // odd-even 7-row prize
#define LOT_PRZ_MHG1    13  // matching match-1 prize
#define LOT_PRZ_MHG2    14  // matching match-2 prize
#define LOT_PRZ_MHG3    15  // matching match-3 prize
#define LOT_PRZ_EXN1    16  // extra number prize
#define LOT_PRZ_OUG10   17  // outsider select-10 prize
#define LOT_PRZ_OUG11   18  // outsider select-11 prize
#define LOT_PRZ_OUG12   19  // outsider select-12 prize
#define LOT_PRZ_OUG13   20  // outsider select-13 prize
#define LOT_PRZ_OUG14   21  // outsider select-14 prize
#define LOT_PRZ_OUG15   22  // outsider select-15 prize
#define LOT_PRZ_NOR7    23  // normal 7th prize                         EH01
#define LOT_MAXPRZ_CUR  24  // max. # prizes currently defined          EH01

#define LOT_MAXDRAW     10  // # of draws
#define LOT_MAXSR       2   // # of selection ranges
#define LOT_SR_MK6  0   // mark 6 selection range
#define LOT_SR_GBL  1   // goldball selection range
#define LOT_SR_MIN  0   // minimum selection range
#define LOT_SR_MAX  1   // maximum selection range
#define LOT_MAXMDRAW    30  // max. no. of multi draw ..AL11

#define LOT_MAXGAME 10  // # of games per draw
#define LOT_GAME_NOR    0   // normal
#define LOT_GAME_AON    1   // addon
#define LOT_GAME_OEG    2   // odd-even
#define LOT_GAME_MHG    3   // matching
#define LOT_GAME_EXN    4   // extra number
#define LOT_GAME_OUG    5   // outsider
#define LOT_MAXGAME_CUR 6   // max. # of games currently define         FT02

// max. no. of prizes for each game type                                EH01
#define LOT_MAX_NOR      7   // normal for MK6 (1-7)                   EH01
#define LOT_MAX_GNOR     6   // normal for GBL (1-6)       // JC03
#define LOT_MAX_AON      1   // addon
#define LOT_MAX_OEG      6   // odd-even for MK6 (2-7)
#define LOT_MAX_GOEG     5   // odd-even for GBL (2-6)
#define LOT_MAX_MHG      3   // matching match (1-3)
#define LOT_MAX_EXN      1   // extra number
#define LOT_MAX_OUG      6   // outsider select (10-15)
#define LOT_MAX_GAME_PRZ 7   // max sub-game within all game type       EH01

#define LOT_MAXSUBGAME   50     // max. no. of subgame per lottery type
#define LOT_SGM_NOR     0   // normal (mk6/goldball)
#define LOT_SGM_AON     1   // addon
#define LOT_SGM_OEG2    2   // odd-even 2-row
#define LOT_SGM_OEG3    3   // odd-even 3-row
#define LOT_SGM_OEG4    4   // odd-even 4-row
#define LOT_SGM_OEG5    5   // odd-even 5-row
#define LOT_SGM_OEG6    6   // odd-even 6-row
#define LOT_SGM_OEG7    7   // odd-even 7-row
#define LOT_SGM_MHG1    8   // matching match-1
#define LOT_SGM_MHG2    9   // matching match-2
#define LOT_SGM_MHG3    10  // matching match-3
#define LOT_SGM_EXN     11  // extra number
#define LOT_SGM_OUG10   12  // outsider select-10
#define LOT_SGM_OUG11   13  // outsider select-11
#define LOT_SGM_OUG12   14  // outsider select-12
#define LOT_SGM_OUG13   15  // outsider select-13
#define LOT_SGM_OUG14   16  // outsider select-14
#define LOT_SGM_OUG15   17  // outsider select-15
#define LOT_SGM_MAX     6   // max. no. of subgame per game
#define LOT_MAXSUBGAME_CUR  18     // max. no. of subgames per lottery type
                                // currently defined

#define LOT_AON_NGEN    3   // # of number generated for add-on game
#define LOT_MINBINV     2   // minimum base investment $2

#define LOT_MAXTYPE 5   // type of lottery
#define LOT_TYPE_MK6    0   // mark6
#define LOT_TYPE_PWB    1   // powerball
#define LOT_MAXTYPE_CUR 2   // max. # lottery type currently defined

// lottery tsn id defines
#define LOT_LOCID       5   // location id, mark6
#define LOT_PWBLOCID    7   // location id, powerball
#define LOT_BETTYP      1   // bet type id = 1
#define LOT_MDTYPE      7   // bet type id for multi-draw

// Lottery
#define LOT_MAXLOS      3   // Max. no. of losing selection
#define LOT_MINWIN      3   // Min. no of winning selection
#define LOT_SPCDNO      7   // Extra no. position
#define LOT_SELBSE      1   // selection base number
#define LOT_SELMAX      55  // selection max number

// Goldball
#define LOT_NODNO_GBL   5   // No. of draw from normal set
#define LOT_NOGBL       1   // No. of goldball
#define LOT_MAXLOS_GBL  3   // Max. no of losing selection
#define LOT_MINWIN_GBL  2   // Min. no. of winning selection
#define LOT_SPCDNO_GBL  6   // Gold ball position
#define LOT_GBLBSE      61  // Gold Ball number base number
#define LOT_GBLMAX      115 // Gold Ball number max number

// RL07..
// Concurrent game selection range and limits
#define LOT_MINPWBSEL   5   // Gold ball min. # of normal selection
#define LOT_MINMK6SEL   6   // Mark 6 min. # of selection
#define LOT_OEG_MIN     2   // Odd-even game min. game type
#define LOT_OEG_MAX     7   // Odd-even game max. game type (mark6)
#define LOT_OEG_PWBMAX  6   // Odd-even game max. game type (goldball)
#define LOT_MHG_MIN     1   // Matching game min. game type
#define LOT_MHG_MAX     3   // Matching game max. game type
#define LOT_OUG_MIN    10   // Outsider game min. game type
#define LOT_OUG_MAX    15   // Outsider game max. game type
// ..RL07

// CS12..
#define LOT_TYPE_NORMAL     0   // normal draw
#define LOT_TYPE_SNOWBALL   1   // snowball draw
#define LOT_TYPE_MERGE      2   // draw merged
#define LOT_SNAME_LEN       4   // max. length of lottery short name
#define LOT_NAME_LEN       41   // max. length of lottery long name 
// ..CS12

#pragma pack(1)

struct  LOTDNOM         // drawn # map
    {
    unsigned char       offbu;   // bitmap #
    unsigned char       mapbu;   // bitmap
    };

struct  LOTDNO          // drawn #
    {
    unsigned short      numwu;   // #
    struct LOTDNOM      map;    // map
    };

struct  LOTPRZ          // prize
    {
    LONGLONG            przd;       // prize per $ in cents     -1=overflow
                                    // [LOTPRZL/LOTAPRZL/LOTAONPRZL]
    struct LOTPZSTS     sts;        // prize status
                                    // [LOTPZSTTW]
    };

struct  LOTGAM          // game info
    {
    unsigned short        bse1:1;     // badsale expired [lot_lotbse_m]
    unsigned short        pay1:1;     // started pay          // JC10
    unsigned short        :14;        // unused
    struct BSTPOLAREA   area[BST_AREA_MAX]; // area control     PN06
    };

struct  LOTDRW          // per draw info
    {
    unsigned short      filewu;      // file id (file set no.)
    unsigned short      yearwu;      // year [LOTYEARW]
    unsigned short      drawwu;      // draw [LOTNUMW]
    unsigned short      typewu;      // type of lottery
    unsigned short      maxdrawwu;      // maximum # of multi-draws
    unsigned short      drefidxwu;  // index of description ref. table map // CS12..
    unsigned char       masterbu;   // index # of master draw (valid only if master1=true)
    unsigned char       slavebu;    // index # of slave draw (valid only if slave1=true)
    char                shortnams[LOT_SNAME_LEN]; // lottery short name   // ..CS12 
    struct LOTDNO       dno[LOT_MAXDNO];    // drawn # [LOTDNOB]
    struct LOTPRZ       prz[LOT_MAXPRZ];    // prizes
    struct LOTGAM       gam[LOT_MAXGAME];   // game info
    time_t              drwdat;     // draw date [LOTDATW]
    time_t              opndat;     // opening date [LOTODTW] [LOTCTMW]
    time_t              clsdat;     // closing date // CS12
    time_t              clsdattim;  // closing date time [LOTCDTW]
    unsigned short        wrn1:1;     // close warning sent [lot_lotwrn_m]
    unsigned short        cls1:1;     // closed [lot_lotcls_m]
    unsigned short        fin1:1;     // final [lot_lotfin_m]
    unsigned short        resi1:1;    // result in
    unsigned short        wps1:1;     // winner pass done ! FT08
    unsigned short        used1:1;    // this draw portion is used
    unsigned short        eod1:1;     // end of day done
    unsigned short        xdraw1:1;   // special/snowball draw // CS12..
    unsigned short        master1:1;  // merged to master draw 
    unsigned short        slave1:1;   // slave draw being merged // ..CS12
    unsigned short        :6;         // unused
    };

struct  LOTTYPG         // game specific info
    {
    unsigned int        subglu;      // sub-game enabled map 
                                    // [LOTAGMAPL/LOTPWBAGMAPL]
    unsigned int        unitlu;      // unit investment in $
                                    // [BSPOLUNTW/LOTABETW/LOTPWBABETW]
    unsigned short        ena1:1;     // game enable flag [LOTAENAT/LOTPWBENAT]
    unsigned short        :15;
    };

struct  LOTTYP          // type specific info
    {
    unsigned LONGLONG   expdivdu[LOT_MAXGAME];    
                                     // dividend expired last night
                                     // [LOTEXPR/LOTPWBEXPR]
    unsigned short      defidxwu;    // default draw index into D
                                     // [LOTCURB/LOTPWBCURB]
    unsigned short      defsdidxwu;  // default snowball draw index // CS12
                                     // [LOTCURB/LOTPWBCURB]
    unsigned short      srwu[LOT_MAXSR][2];// selection ranges
                                    // [LOTMSLW/LOTPWBMINW/LOTPWBMAXW]
    struct LOTTYPG      gam[LOT_MAXGAME];// game specific info
    unsigned short      bsiwu;       // badsale interval [LOTBSIB]
    unsigned short      cwiwu;       // draw close warning interval [LOTCWIB]
    unsigned short      maxdrawwu;      // maximum # of multi-draws
    unsigned LONGLONG   uliadu;      // unsettled liability  !FT04
                                    //  it will be updated at eod
    };

struct  LOT
    {
    struct LOTDRW       d[LOT_MAXDRAW]; // draw info
    struct LOTTYP       t[LOT_MAXTYPE]; // draw type specific info
    };

#pragma pack(1)

#endif
