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
//  Author  : Leonard Yau       24-MAR-2003
//
//  Fucntion: Data structures to hold the descriptions reference table.
//            Two data files are created to store description reference
//            information:
//            1. DREF.DAT   - description reference file with an array of
//                            bytes
//            2. DREFMP.DAT - mapping table for DREF.DAT
//
//            When a pool or any reference type is defined with description
//            required, an entry is inserted into DREFMP and assigned a
//            start byte offset in description reference array.  Each 
//            entry contains a key and and a retention referenced
//            date.  This date is used for housekeeping purpose.
//
//            Based on the transaction date and reference table key, 
//            corresponding reference information table can be found.
//
//            Retention referenced date is updated when corresponding reference entry
//            is settled and pool is concluded.
//
//            During end of day, reshuffling is required for entry with
//            reference table purged.  This depends on the retention
//            reference date + days of retention period in different system:
//            . For Account bet system, retention period will be number
//              of days for the earliest date in the history file sets.
//            . For OLTP-CB system, retention period will be 0 since it
//              is only required on recall or log file dump
//            . For OLTP-SB system, retention period will be payout period.
//
//  Mods:   DJ01            11-02-2004
//          - Add pool creation date
//          - Add key reserved bit
//          PN02            25-FEB-2004
//          ( support special pool )
//          JC03            01-MAR-2004
//          Change the buffer size for DREF from 16000 to 5000 blocks as the
//          current max. byte size should be 2000 blocks only
//
//          JC04            12-MAR-2004
//          add TRN names in SPC pool info
//
//          JC05            18-MAR-2004
//          change the TRN short name length to 5  in order to reserve some
//          space for other use.  The reson is to avoid file conversion for
//          Stage 3A
//
//          PN06            29-JUL-2005
//          Define structure for team table and player table which will be
//          stored in reference file instead of SBCTL.DAT.  Currently, we
//          will support up to 65535 entries.  If more than 65535, another
//          mapping table is required such that the value will be reused
//          since the value in bet record is only defined with 2 bytes.
//
//          PN07            19-AUG-2005
//          Q106: Store bracket pool information for race meeting
//          PN08            7-DEC-2005
//          - undo PN07 as this need to be stored in another file to be 
//            updated by different process: WCHNDR.  Actually, this structure 
//            is not used by any program yet.
//          - support special draw short name and long name with a set of 
//            new files created: DREF2.DAT DREFMP2.DAT for racing and lottery.
//            This required since update of the reference file information is
//            handled and owned by another process i.e. WCHNDR.
//
#include <time.h>
#include "sbdef.h"
#include "lotdef.h"

#ifndef DREFDEF_H
#define DREFDEF_H

#define DREF_SIZE (5000*512)           // size of character array in DREF.DAT   // JC03

#define DREF_MAX_ENTRIES    2000        // max no. of entries in the 
                                        // mapping table

// possible return codes for creation of descriptions of a reference instance

enum DREFSTS
{
    DREF_OK = 0,
    DREF_NO_FREE_SPACE,
    DREF_DUPLICATE
};

#pragma nomember_alignment

struct DREFTRND         // description table for tournament pool
{
    char                    pnames[SB_LEN_TRN_NAME];// tournament name
    char                    pcodes[SB_LEN_TRN_CODE];// tournament short name        // JC05
    char                    fillerb[28];
    char                    events[SB_LEN_TRN_NAME];// event description
    unsigned char           nselbu;                 // number of selection
    struct SB_TRNMENT_SEL   sel[SB_MAX_LEAGUE_TEAM];// selection
                                                    // [0] is not used,
                                                    // when nsetbu==1 => [1]
};

// PN02..
struct DREFSPC_MATCH
{
    unsigned short      homewu;
    unsigned short      awaywu;
};

struct DREFSPC_TRN          // JC04
{
    char                    trnNames[SB_LEN_TRN_NAME];      // TRN name string
    char                    codes[SB_LEN_TRN_NAME];         // TRN short codes 
};

union DREFSPC_PNAME         // pool description
{
    struct DREFSPC_MATCH    match;                  // match base info.
    struct DREFSPC_TRN      trn;                    // TRN base info.
};

struct DREFSPCD             // description for special pool
{
    unsigned int            match1:1;       // match id flag
    unsigned int            :7;             // unused
    struct SB_MATCH_ID      id;             // ----/ match day
                                            // TRN#/ match #
    union DREFSPC_PNAME     pname;          // pool description
    char                    items[SB_LEN_SPC_ITEM]; // item description
    unsigned char           nselbu;                 // number of selection
    char                    sels[SB_MAX_SPC_SEL+1][SB_LEN_TRN_NAME];  
                                                    // selection description
                                                    // [0] is not used,
                                                    // when nsetbu==1 => [1]
};
// ..PN02

// PN06..
struct DREFTEAMD        // team table description
{
    unsigned short      cntwu;          // # of teams defined
    char                name[SB_MAX_TEAM][SB_LEN_TEAM];
};

struct DREFPLAYERD      // player table description
{
    unsigned short      cntwu;          // # of players defined
    char                player[SB_MAX_PLAYER][SB_LEN_PLAYER];   // player table
};
// ..PN06

// PN08..
// lottery special draw description
struct DREFLOTD         // special draw description 
{
    char        codes[LOT_SNAME_LEN];   // lottery draw code
    char        names[LOT_NAME_LEN];    // lottery long name
};
// ..PN08

struct DREF
{
    char drefs[DREF_SIZE];
};

//
// Following data structure defines key used in mapping table.  New key 
// structure will be added whenever there is a new type of description
// table is introduced.
// 
//
union DREFPID                           // pool id for pool
{
    unsigned int        poollu;         // pool id in binary value
    struct SB_MATCH_ID  match;          // match id
};

struct DREFTRN                          // key for tournament pool
{
    __time32_t          tdate;              // tournament date (from SBC, not
                                        // form part of the key, it is for
                                        // information only)
    __time32_t          cdate;              // pool creation date 
                                        // (should come from SBC, but now
                                        // we just use parcom.busdat)
    unsigned char   ptype;              // tournament pool type
    unsigned char   trnidbu;            // tournament number
    unsigned char   evtidbu;            // event code / group # for GWP
};

// PN02..
struct DREFSPC                          // key for special pool
{
    __time32_t          tdate;              // tournament date (from SBC, not
                                        // form part of the key, it is for
                                        // information only)
    __time32_t          cdate;              // pool creation date
    unsigned char   typebu;             // type number
    unsigned char   itembu;             // item number
};
// ..PN02

struct DREFLOT
{
    unsigned short  yearwu;      // year
    unsigned short  drawwu;      // draw
    unsigned short  typewu;      // type of lottery
};

union DREFKEY
{
    struct DREFTRN  trnment;            // tournament pool
    struct DREFSPC  spc;                // special pool     PN02
    struct DREFLOT  lot;                // lottery          PN08
    unsigned char   reservebu[20];      // Reserved size for renewal
};

struct DREFMPE                          // entry for mapping table
{
    __time32_t          drsdate;            // reference creation datetime ( datBusinessTime() )
    __time32_t          edate;              // reference pool concluded datetime
                                        // (updated when pool close)
    __time32_t          rdate;              // reference retention date (settlement date from SBC)
                                        // (retention date for house keeping;
                                        // this can be match date or event
                                        // date or first dividend declared date or
                                        // closing date or lottery draw date... whatever
                                        // user specifies.  This will be
                                        // business date to determine when
                                        // all bets of corresponding date
                                        // will be purged from system.)
    unsigned int    startlu;            // start byte offset in DREF
    unsigned int    sizelu;             // size of reference table
    unsigned char   rtypebu;            // reference type
        #define RTYPE_TRNMENT   1       // tournament
        #define RTYPE_SPC       2       // special pool     PN02
        #define RTYPE_TEAM      3       // team name        PN06
        #define RTYPE_PLAYER    4       // player name      PN06
        #define RTYPE_LOT       5       // lottery draw     PN08
    union DREFKEY   key;                // key of corresponding reference type
};

struct DREFMP                           // file structure of DREFMP.DAT
{
    unsigned int    nbytelu;            // number of byte used in DREF.DAT
    unsigned short  nentrywu;           // number of entry in mapping table used
    struct DREFMPE  entry[DREF_MAX_ENTRIES];    // entries 
};

#pragma member_alignment

#endif
