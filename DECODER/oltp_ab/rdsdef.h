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
//    RDSDEF.H - info from RDSCOM.DAT/RDSCHL, COLLAT
//               This will store information on meeting that is not 
//               concluded yet.
//
//    Author : Edward Hon                01-NOV-2000
//
//    Mod :     JC01            18-JUN-2002
//              move the declaration of structure RDSCOM from rdscom.h
//
//              JC02            19-JUL-2002
//              remove maxacomlu in RDSRACE - no one use it
//
//              AC03            22-JUL-2002
//              change # of available meetings from 3 to 5              
//  
//              AC04            26-JUL-2002
//              add unsettled liability 
//
//              PN05            4-SEP-2002
//              . remove concluded bit
//              . add area control array
//
//              JC06            27-SEP-2002
//              current race in meeting is no use any more
//              PN07            9-JUN-2003
//              ( move partial unit bet data structure to BSTYPEDEF.H )
//
//              CS07            10-DEC-2004
//              add define move in from rdcupdate.
//
//              JC08            21-FEB-2005
//              add a flag to indicate a pool has started pay
//
//              FT09            6-JUL-2005
//              add abandoned race flag
//              - when WCHNDR receives abandon meeting message, it will set
//                this flag for all remaining races
//              PN10            19-AUG-2005
//              ( Q106: support losing investment consolation )
//
//              CS11            26-AUG-2005
//              - rename the DEFINE align with standard
//
//              JC12            27-SEP-2005
//              add last msn used for WC/RWCC
//
//              JC13            18-NOV-2005
//              add sold1 in meeting to indicate start sell has been
//              performed on the meeting
//
#ifndef RDSDEF_H
#define RDSDEF_H

#include <time.h>
#include "bstypedef.h"
#include "bettypdef.h"
#include "udtypedef.h"

//contains RDCPAR info

#define RDS_LOC_ST      1       // meeting location
#define RDS_LOC_HV      2
#define RDS_LOC_X1      3
#define RDS_LOC_X2      4
#define RDS_DAY_SUN     1       // meeting day code
#define RDS_DAY_MON     2
#define RDS_DAY_TUE     3
#define RDS_DAY_WED     4
#define RDS_DAY_THU     5
#define RDS_DAY_FRI     6
#define RDS_DAY_SAT     7

#define RDS_MAXMEET     10      // # of meetings
#define RDS_MAXRACE     31      // # of races per meeting
#define RDS_MAXPOOL     20      // # of pools per race
#define RDS_MAXRES      4       // # of results per race
#define RDS_MAXSUB      3       // # of substitutions per race
#define RDS_MAXAPOOL    5       // # of allup pool
#define RDS_MAXAFML     50      // # of allup formula
#define RDS_MAXLEG      6       // max. # of legs per pool
#define RDS_MAXDIV      36      // max. # of dividend per pool
#define RDS_MAXFLD      62      // max. field size. support 34 starters
#define RDS_MAXPSUB     12      // max. # of substitutions per pool
#define RDS_MAXWCSIZ    6       // max. bitmap size for a winning comb.
#define RDS_MAXDH       3       // max. dead heat
#define RDS_SELSIZ      6       // max. selection bitmap size
#define RDS_MAXLSCTIER  5       // max. losing investment consolation tier PN10

// maximum collation size per pool
#define RDS_WINCOLSIZ   RDS_MAXFLD
#define RDS_PLACOLSIZ   RDS_MAXFLD
#define RDS_QINCOLSIZ   RDS_MAXFLD * (RDS_MAXFLD-1)/2
#define RDS_QPLCOLSIZ   RDS_MAXFLD * (RDS_MAXFLD-1)/2
#define RDS_DBLCOLSIZ   RDS_MAXFLD * RDS_MAXFLD
#define RDS_TRICOLSIZ   RDS_MAXFLD * (RDS_MAXFLD-1) * (RDS_MAXFLD-2) / 6
#define RDS_TCECOLSIZ   RDS_MAXFLD * (RDS_MAXFLD-2) * (RDS_MAXFLD-1)
#define RDS_QTTCOLSIZ   RDS_MAXFLD * (RDS_MAXFLD-3) * (RDS_MAXFLD-2)*(RDS_MAXFLD-1)
#define RDS_TBLCOLSIZ   RDS_MAXFLD * (RDS_MAXRACE-2)
#define RDS_DQNCOLSIZ   RDS_MAXFLD * (RDS_MAXFLD-1) * (RDS_MAXRACE-1) / 2
#define RDS_TTRCOLSIZ   RDS_TRICOLSIZ * (RDS_MAXRACE-2)
#define RDS_6UPCOLSIZ   RDS_MAXFLD * (RDS_MAXRACE-5)
#define RDS_DTRCOLSIZ   RDS_TRICOLSIZ * (RDS_MAXRACE-1)

// maximum collation counters per meeting
// ( WIN + PLA + QIN + QPL + DBL + TRIO + TCE + QTT + TBL + DQN + TTR
// + 6UP + DTR )
//#define RDS_MAXCOL    ( ( RDS_WINCOLSIZ +             \
//                      RDS_PLACOLSIZ +                 \
//                      RDS_QINCOLSIZ +                 \
//                      RDS_QPLCOLSIZ +                 \
//                      RDS_TRICOLSIZ +                 \
//                      RDS_TCECOLSIZ +                 \
//                      RDS_QTTCOLSIZ ) * RDS_MAXRACE + \
//                      RDS_DBLCOLSIZ +                 \
//                      RDS_TBLCOLSIZ +                 \
//                      RDS_DQNCOLSIZ +                 \
//                      RDS_TTRCOLSIZ +                 \
//                      RDS_6UPCOLSIZ +                 \
//                      RDS_DTRCOLSIZ )

// max. # of winning bitmap per pool, allow for 6up winning combination
#define RDS_MAXWCOM     RDS_MAXDIV * RDS_MAXWCSIZ
                
#define RDS_TPOOL       RDS_MAXPOOL * RDS_MAXRACE * RDS_MAXMEET // total # of pools
#define RDS_TDIV        RDS_MAXDIV * RDS_TPOOL  // size of dividend array
#define RDS_TWCOM       RDS_MAXWCOM * RDS_TPOOL // size of winning comb array
//#define RDS_TWCOM     1000000                 // size of winning comb array
//#define RDS_TCOL      RDS_MAXMEET * RDS_MAXCOL// size of collation array
#define RDS_TCOL        12350000        // size of collation array
                                        // for RDS_MAXMEET = 3
                                        //     RDS_MAXRACE = 15
                                        //     RDS_MAXFLD  = 24
                                        // total = 12,342,024
                                        // round to the nearest 12,350,000 

// winning combination size ( unit in unsigned int )
#define WCM_PER_POOL    (RDS_MAXDIV*RDS_MAXWCSIZ)       // size per pool 36*6 = 216
#define WCM_PER_RACE    (WCM_PER_POOL*RDS_MAXPOOL)      // size per race 216*20 = 4320
#define WCM_PER_MTG     (WCM_PER_RACE*RDS_MAXRACE)      // size per meeting 4320*31 = 133920
#define WCM_FLD_BIT     ox80000000                      // field bit - leftmost bit

// dividend size ( unit in LONGLONG - amount in cents )
#define DIV_PER_POOL    RDS_MAXDIV                      // size per pool 36
#define DIV_PER_RACE    (RDS_MAXDIV*RDS_MAXPOOL)        // size per race 36*20 = 720
#define DIV_PER_MTG     (DIV_PER_RACE*RDS_MAXRACE)      // size per meeting 720*31 = 22320

// pool defines
#define RDS_POOL_WIN    0       
#define RDS_POOL_PLA    1
#define RDS_POOL_QIN    2
#define RDS_POOL_QPL    3
#define RDS_POOL_TRI    4
#define RDS_POOL_TCE    5
#define RDS_POOL_QTT    6
#define RDS_POOL_DBL    7
#define RDS_POOL_DQN    8
#define RDS_POOL_TBL    9
#define RDS_POOL_TTR    10
#define RDS_POOL_6UP    11
#define RDS_POOL_DTR    12
#define RDS_POOL_MIN    0           // min racing pool id, please change it if add/ delete pool
#define RDS_POOL_MAX    12          // max racing pool id, please change it if add/ delete pool

#define RDS_POOL_AWIN   0
#define RDS_POOL_APLA   1
#define RDS_POOL_AQIN   2
#define RDS_POOL_AQPL   3
#define RDS_POOL_ATRI   4
#define RDS_POOL_ATCE   5
#define RDS_POOL_AQTT   6

#define RDS_POOL_STARTSELL   1   // CS07.. // CS11..
#define RDS_POOL_STOPSELL    2
#define RDS_POOL_DEFINE      3   // ..CS07 // ..CS11

#pragma pack(1)

// PN10..
enum RDS_BETCHAN        // betting channel category
{
    RDS_BETCHAN_CB,     // cashbet
    RDS_BETCHAN_AB,     // account bet
    RDS_BETCHAN_MAX     // maximum bet channel
};

struct RDSLSCM  // losing investment consolation control by meeting parameter
{
    unsigned LONGLONG   invdu;      // minimum losing investment in cents
    unsigned int        ena1:1;     // tier enable flag
};

struct RDSLSCR  // losing investment consolation control by race parameter
{
    unsigned int    ena1:1; // losing investment consolation enable flag
};

struct RDSLSCP  // losing investment consolation control by pool parameter
{
    unsigned short  percwu[RDS_MAXLSCTIER]; // consolation % * 100
};
// ..PN10

struct  RDSSYSMEET      // meeting related system parameter
  {
  unsigned LONGLONG     auprwdu;    // allup reinvestment warning limit [BSARWR]
  unsigned short        rcwiwu;     // race close warning interval [BSRCWLW]
  unsigned short        poluntwu[BETTYP_MAX];   // pool unit in $ [BSPOLUNTW]
  BOOL                  aupfmt[RDS_MAXAPOOL][RDS_MAXAFML];
                                    // allup formula define flag [BSAFMT]
                                    // aupfmt[0][] not used
  BOOL                  aupenat;    // all-up betting enabling flag
  struct BSTPUBET       punitbet[BETTYP_MAX];   // PN07
                                    // partial unit bet control parameter
  };

struct  RDSPOOL         // pool info
  {
  unsigned int          leglu;      // leg bitmap [=0 undefined] [rds_poolleg_w]
  unsigned int          cptrlu;     // offset to race collation start
  unsigned int          wptrlu;     // start of winning comb bitmap [rds_poolrpt_w]
  unsigned int          dptrlu;     // start of dividend [rds_pooldpt_w]
  unsigned short        ndivwu;     // # of dividend [rds_poolres_w]
  unsigned int          bse1:1;     // badsale expired [rds_poolbse_m]
  unsigned int          rfd1:1;     // refund [rds_poolrfd_m]
  unsigned int          div1:1;     // dividend in [rds_pooldiv_m]
  unsigned int          par1:1;     // partial dividend [rds_pooldvf_m]
  unsigned int          pfix1:1;    // partial dividend fixed
                                    // when set indicates that >0 dividend is fixed
                                    // this should be set in end of day if
                                    // the claim bit is on
                                    // this should be cleared in end of day if
                                    // the claim bit is off
  unsigned int          fix1:1;     // dividend fixed [rds_poolfix_m]
  unsigned int          clm1:1;     // dividend claimed [rds_poolclm_m]
  unsigned int          paid1:1;    // started pay, will not clear even stop pay    // JC08
  unsigned int          :8;         // unused
  struct BSTPOLAREA     area[BST_AREA_MAX]; // area control     PN05
  // PN10.. losing investment consolation control by pool parameter
  struct RDSLSCP        lscp[RDS_BETCHAN_MAX];
  // ..PN10
  };

struct  RDSRACE         // race info
  {
  unsigned int          cptrlu;             // offset to meeting collation start
  unsigned int          nstlu;              // non-starter bitmap [rds_racenst_w]
  unsigned int          reslu[RDS_MAXRES];  // result bitmap [RDSPLACW]
  LONGLONG              rinstoffd;          // auprin vbn start offset for this race
  unsigned int          rincomlu;           // no. of aup combinations used
  __time32_t                postTime;           // post time [rds_racepst_w]
  unsigned short        distwu;             // distance [RDSRACDISW]
  unsigned short        fldwu;              // field size [rds_racefld_b]
  unsigned char         subbu[RDS_MAXSUB];  // substitutes [rds_racesub]
  unsigned int          wrnf1:1;            // off-course close warning sent [rds_racefwrn_m]
  unsigned int          wrnn1:1;            // on-course close warning sent [rds_racenwrn_m]
  unsigned int          clsd1:1;            // closed [rds_racecld_m]
  unsigned int          cfin1:1;            // collation final [rds_racefin_m]
  unsigned int          resi1:1;            // result in [rds_racersi_m]
  unsigned int          prps1:1;            // post race pass started [rds_raceprp_m]
  unsigned int          prpd1:1;            // post race pass done [rds_raceprpdone_m]
  unsigned int          aupdsb1:1;          // allup betting disabled
  unsigned int          abd1:1;             // abandoned race  ! FT09
  unsigned int          :7;                 // unused
  struct RDSPOOL        pool[RDS_MAXPOOL];  // pool info [RDSPOOL]
  struct RDSLSCR        lscr[RDS_BETCHAN_MAX];  // losing inv. cons by race
  };


struct  RDSMEET         // meeting info
  {
  struct RDSSYSMEET     par;        // parameters
  unsigned short        filewu;     // file id
  unsigned int          cstartlu;   // collation start
  unsigned int          csizelu;    // collation size
                                    // 1st meeting starting from 2 (1=ctrl blk)
  LONGLONG              rinstartd;  // aup rin file start vbn for this meeting
  unsigned int          rinsizelu;  // no. of blocks used for this meeting
  unsigned short        nracewu;    // # of races [RDSMRCEW]
  unsigned short        bsiwu;      // bad sale interval in seconds [RDSMBSIB]
  unsigned short        rcifwu;     // race close interval, off-course [RMSMFRCIB]
  unsigned short        rcinwu;     // race close interval, on-course [RMSNRCIB]
  unsigned short        numwu;      // meeting number [RDSMNUMW]
  unsigned short        fillerwu;   // noused variable (current race)   // JC06
  __time32_t                dat;        // meeting date [RDSMDATW]
  unsigned char         locbu;      // location [RDSMLOCB]
  unsigned char         daybu;      // day [RDSMDAYB]
  unsigned int          sell1:1;    // selling/cancel allowed [rds_meetmark_m]
  unsigned int          xbrlsc1:1;  // external branch losing investment
                                    // consolation enable flag  PN10
  unsigned int          abd1:1;     // abandoned [rds_meetabd_m]
  unsigned int          used1:1;    // this meeting portion is used
  unsigned int          eod1:1;     // End Of Day done
  unsigned int          sold1:1;    // meeting has been started sell    // JC13
  unsigned int          :10;        // unused
  struct RDSRACE        race[RDS_MAXRACE+1];  // race info [RDSRACE], 
                                    // race[0] is not used
  // PN10.. losing consolation by meeting control parameter
  struct RDSLSCM        lscm[RDS_BETCHAN_MAX][RDS_MAXLSCTIER];
  };

#pragma pack(1)

struct  RDSMTG
  {
  unsigned short        meetwu;             // last meeting index used + 1
  struct RDSMEET        meet[RDS_MAXMEET];  // meeting record
  unsigned int          dsizlu;             // next use dividend array [RDSMDIVW]
  unsigned int          wsizlu;             // next use winning comb. arrary [RDSMRESW]
  unsigned int          csizelu;            // collation total size used
  LONGLONG              rsized;             // # of block used in auprin.dat
  unsigned LONGLONG     uliadu;             // unsettle liability in cents AC04 
                                            // (sum of known liability on 
                                            // unsettled bets in eod)
  };

struct  RDSDIV
  {
  LONGLONG              divd[RDS_TDIV];     // dividend record
                                            // <0 -ve expected dividend
                                            // and is only claim if claim bit is on
  };
 
struct  RDSWCM
  {
  unsigned int          wcmlu[RDS_TWCOM];   // winning comb record
  };

struct RDSCOM 
  {
  struct RDSMTG mtg;            // file RDSMTG
  struct RDSDIV div;            // file RDSDIV
  struct RDSWCM wcm;            // file RDSWCM
  unsigned int  lastmsnlu[2];   // last msn from WC/RWCC        // JC12
  };

#endif
