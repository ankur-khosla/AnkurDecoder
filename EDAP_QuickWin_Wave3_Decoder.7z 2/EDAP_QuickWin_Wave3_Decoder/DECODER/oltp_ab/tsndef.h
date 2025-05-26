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
//  Author  : Vicki Chung       12-DEC-2000
//
//  Mods    :   HL01: 21-June-2002
//              There are  only 3 bits in TSN to store bet types. SB is
//              the 9th bet type so there must be another enum defines to 
//              indicate SB bet type. 
//
//              PN02    14-MAY-2003
//              ( add window number in tsn )
//              

#ifndef TSNDEF_H
#define TSNDEF_H

#pragma pack(1)

#define TSN_EXTTSN_LEN  16
#define TSN_EXTREF_LEN  17
#define TSN_REF_SYMBOL  'R'
#define TSN_FMTTSNREF_LEN   20
#define TSN_OFFSET_MAX  0x4000000   // max. number of record offset value 
                                    // stored in tsn i.e. # bits for record
                                    // number + 1 (for sb ticket)

struct  TSN_12          // word 1 and 2 of tsn
  {
  unsigned char         rechb;          // high order bits of record #
  unsigned char          loc3:3;         // location for racing ticket
    #define TSN_LOC_CV_ODDYR    1
    #define TSN_LOC_MK6         5
    #define TSN_LOC_SWP         6
    #define TSN_LOC_PWB         7
  unsigned char          type3:3;        // bet type
    #define TSN_TYPE_ESC        0
    #define TSN_TYPE_LOT        1       //single-draw lottery
    #define TSN_TYPE_AUP        2
    #define TSN_TYPE_EXO        3
    #define TSN_TYPE_STD        4
    #define TSN_TYPE_TBD        5
    #define TSN_TYPE_CV         6
    #define TSN_TYPE_MD         7       //multi-draw lottery
  unsigned char          secu2:2;        // low order bits of security code
  unsigned short        reclw;          // low order record # bits
  };

struct  TSN_3OLD                // old word 3
  {
  unsigned short  ctrl8:8;        //centre/eft low order bits
  unsigned short  wdw6:6;         //window [eft=0]
  unsigned short  ctrh2:2;        //centre/eft high order bits
  };

// PN02..
struct TSN_3CTRWDW
{
  unsigned short  ctrl10:10;      // centre number
  unsigned short  wdw6:6;         // window number
};

union   TSN_3                   // word 3
  {
  struct TSN_3OLD       old;    // old [w4.new1=0]
  struct TSN_3CTRWDW    ctrwdw; // centre/window
  };
// ..PN02

struct  TSN_4           //4th word of tsn
  {
  unsigned short  secu3:3;        //high order security code bits
                                //or presale day count in bet file
  unsigned short  sys3:3;         //sale system #
  unsigned short  new1:1;         //new tsn flag
  unsigned short  day9:9;         //meeting day of year [racing]
                                //draw # [lottery] or transaction day of year
  };

struct  TSN_34          // word 3 and 4 of TSN
  {
  union  TSN_3 tsn3;
  struct TSN_4 tsn4;
  };

struct  TSN_A           //full tsn
  {
  struct TSN_12 w12;    // word 1 and 2
  union TSN_3   w3;     // word 3
  struct TSN_4  w4;     // word 4
  };
struct  TSN_SB1                 // word 1 of soccer betting tsn
  {
  unsigned short          rech10:10;      // high order bits of record offset
  unsigned short          yr1:1;          // last bit of sale year
  unsigned short          type3:3;        // bet type
    #define TSN_TYPE_SB         4       // soccer betting [w4.sys3=0
                                        // and w4.new1=1]
  unsigned short          secu2:2;        // low order bits of security code
  };
struct TSN_SB3                  // word 3 of soccer betting tsn
{
  unsigned short          ctr14:14;       // selling centre
  unsigned short          offUnit2:2;     // offset unit
                                // 0 = word unit, 1 = 2-word unit,
                                // 2 = 4-word unit, 3 = 8-word unit
        //  0 => rec from 0           to 0x3FFFFFF  (up to block 262143)
        //  1 => rec from 0x4000000   to 0xBFFFFFE  (up to block 786431)
        //  2 => rec from 0xC000000   to 0x1BFFFFFC (up to block 1835007)
        //  3 => rec from 0x1C0000000 to 0x3BFFFFF8 (up to block 3932159)
        // With this implemenation, we can store up to 16.77 million ticket per
        // day in soccer bet file.  This is calculated with average bet size 
        // equal to 120 bytes.
};

struct TSN19T_1
{
    unsigned short        loc3:3;         // meeting location/sales year
    unsigned short        sys3:3;         // sale system #
    unsigned short        type5:5;        // ticket type
    unsigned short        secu5:5;        // security code
};

struct TSN19T_2
{
    unsigned short        rech12:12;      // record offset (hi bits)
    unsigned short        reserved2:2;
    unsigned short        offUnit2:2;     // offset unit
                                        // 0 = word unit, 1 = 2-word unit,
                                        // 2 = 4-word unit, 3 = 8-word unit
};

struct TSN19T_4
{
    unsigned short        verifierh6:6;   // content verifier (hi bits)
    unsigned short        tsn16:1;        // TSN is 16 digits long (= 0 for TSN19)
    unsigned short        day9:9;         // meeting day/transaction day/draw number
};

struct TSN19_5
{
    unsigned short        unused4:4;
    unsigned short        verifierl12:12; // content verifier (lo bits)
};

struct TSN19T
{
    struct TSN19T_1     w1;
    struct TSN19T_2     w2;
    unsigned short      reclwu;         // record offset (lo bits)
    struct TSN19T_4     w4;
    struct TSN19_5      w5;
};

struct TSN19A_1
{
    unsigned short        tranh6:6;       // transaction number (hi bits)
    unsigned short        type5:5;        // ticket type
    unsigned short        secu5:5;        // security code
};

struct TSN19A_2
{
    unsigned short        acclh14:14;     // account number (hi bits)
    unsigned short        tranm2:2;       // transaction number (mid bits)
};

struct TSN19A_4
{
    unsigned short        tranl6:6;       // transaction number (lo bits)
    unsigned short        tsn16:1;        // TSN is 16 digits long (= 0 for TSN19)
    unsigned short        day9:9;         // meeting day/transaction day/draw number
};

struct TSN19A
{
    struct TSN19A_1     w1;
    struct TSN19A_2     w2;
    unsigned short      acclwu;         // account number (lo bits)
    struct TSN19A_4     w4;
    struct TSN19_5      w5;
};

struct TSN_SB           // soccer betting tsn
{
  struct TSN_SB1        w1;     // word 1
  unsigned short        reclwu; // word 2 - low order record offset bits
  struct TSN_SB3        w3;     // word 3
  struct TSN_4          w4;     // word 4
};
union   TSN
  {
  struct TSN_A          s;      // structured
  unsigned short        w[5];
  struct TSN_SB         sb;     // soccer betting tsn
  struct TSN19T         s19t;
  struct TSN19A         s19a;
  };

// for old TB deposit - ( TB account # minus check-digt ) * 10000 + transaction
// # is stored in tsn.w12.rechb, tsn.w4.sys3, tsn.w3.wnd6
// [minus top bit] and tsn.w12.reclw, listed from high to low

// for new TB deposit and ESC transaction - account # in tsn.w3 and
// tsn.w12.reclw, transaction # in tsn.w4.sys3, tsn.w12.loc3
// and tsn.w12.rechb, listed from high to low

//HL01 start...
enum TSNBTYPE {
                TSN_BTYPE_ESC,      // ESC
                TSN_BTYPE_LOT,      // Single Draw Lottery
                TSN_BTYPE_AUP,      // All-up
                TSN_BTYPE_EXO,      // Exotic
                TSN_BTYPE_STD,      // Standard
                TSN_BTYPE_TBD,      // Telebet Deposit
                TSN_BTYPE_CV,       // CV
                TSN_BTYPE_MD,       // Multi-Draw Lottery
                TSN_BTYPE_SB,       // Soccer Betting
                TSN_BTYPE_GBL,      // Gold ball single draw
                TSN_BTYPE_GBM,      // Gold ball multi draw
              };  
//HL01 ...end

#pragma pack()

#endif
