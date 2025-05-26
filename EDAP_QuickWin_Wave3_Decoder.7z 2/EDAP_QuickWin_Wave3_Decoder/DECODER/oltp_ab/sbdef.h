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
//    SBDEF.h - This is a header file for the general defines used in OLTP-SB.
//           
//    Author:   Edward Hon        20-Aug-2001
//
//    Mod   :   PN01            24-JAN-2002
//              ( double size of fixed odds collation area )
//              DD02            31-JAN-2002
//              ( Delta M-2: add peak hour minimum cost parameters)
//              JC03            06-FEB-2002
//              1. add partial result-in bit in match status
//              2. change match result data type to short
//              DD04            20-FEB-2002
//              (take away net loss warning parameters)
//
//              JC05            22-FEB-2002
//              add checking enabling flag for some parameter
//
//              JC06            26-FEB-2002
//              re-position of the sbcom variables
//
//              LY07            01-MAR-2002
//              All up set total investments now do not include
//              level 1 investment
//
//              JC08            05-MAR-2002
//              1. add checking enabling flag for a/c max. profit
//              2. change variable name for the ac max profit to
//                 more appropriate
//
//              JC09            05-JUN-2002
//              add define for max special odds currently used
//
//              PN10            14-JUN-2002
//              ( change odds divisor from double constant to integer constant )
//
//              JC11            06-SEP-2002
//              1. change hoPayd to unsigned LONGLONG
//              2. odds value to be stored in n*100
//
//              PN12            12-SEP-2002
//              ( move area defines to BSTYPEDEF.H )
//
//              JC13            16-SEP-2002
//              add pool position limit flag
//              ( true = netLossd value for max. netLoss,
//                false = netLossd value for min. profit )
//
//              JC14            17-SEP-2002
//              add pool define flag by area
//
//              PN15            14-JAN-2003
//              ( add position limit by collated combination, alway 
//                accept unit bet and intercept unit bet for position limit
//                validation )
//
//              LY16            18-JAN-2003
//              ( change accept, intercept values to unsigned int )
//
//              LY17            13-FEB-2003
//              increase max bt per system limit to cater for ESC
//
//              AL18            06-MAR-2003 
//              include "bcsgendef.h" to make compiler silent in complaining 
//              bcsdef.h
//
//              LY19            10-MAR-2003
//              to support in-hedging, add a special account type BOOKIE
//              PN20            19-MAR-2003
//              . remove unused define SB_ODDS_DIVISOR
//
//              JC21            27-MAR-2003
//              expand odds storage to unsigned I*4
//
//              PN22            24-APR-2003
//              . support configurable pool, first goal scorer
//              . add half time correct score pool
//              . expand number of pool per all-up set to 30
//              . add partial unit bet control parameter
//              . add parameter for intercept
//              . add winning combination for complex pool
//              . add bookie flag for account types
//
//              JC23            29-APR-2003
//              1. add global enabling on intercept
//              2. separate intercept, always accept value by area
//              3. modify configurable pool structure
//
//              PN24            29-APR-2003
//              ( increase fix odds collation size to 100000 blocks )
//
#ifndef SBDEF_H
#define SBDEF_H

#include <time.h>
#include "udtypedef.h"
#include "bstypedef.h"                              // PN12
//#include "bcsgendef.h"                              // AL18
#include "bcsdef.h"

#define SB_BT_MAX               25000               // max. # of bt
                                                    // CB 7000, ESC 7000, TB3 5000,
                                                    // TB4 5000, spare/fall-back 1000
#define SB_AT_MAX               BCS_MAXAT           // max. # of at
#define SB_BT_PER_SYS           12000               // max. # of bt per system LY17
#define SB_MAX_WEEK_DAY         7                   // max. # of day in a week
#define SB_MAX_MATCH            100                 // max. # of outstanding matches
#define SB_MAX_CHP              50                  // max. # of outstanding championship
#define SB_MAX_LEAGUE_TEAM      64                  // max. # of teams in league
#define SB_MAX_LEAGUE           65                  // max. # of league
#define SB_MAX_TEAM             4097                // max. # of teams
#define SB_MAX_PLAYER           4097                // max. # of player
#define SB_MAX_ROUND            256                 // max. # of round
#define SB_MAX_AC_TYPE          10                  // max. # of SB account type
#define SB_MAX_AUP_EVENT        10                  // max. # of allup events
#define SB_MAX_POOL_CPX         8                   // max. # of simple pools in complex pool
#define SB_MAX_CPX_POOL         50                  // max. # of complex pools outstanding
#define SB_MAX_CPX_DIV          5                   // max. # of dividends per complex pool
#define SB_MAX_MATCH_PLAYER     40                  // max. # of player per match
                                                    // PN22
#define SB_MAX_COL_FO           (100000*512)        // fixed odds collation size in bytes
                                                    // PN01 PN24
#define SB_MAX_COL_PM           (5000*512)          // pari-mutuel odds collation size in bytes
#define SB_MAX_AUP_SET          5                   // max. # of fixed odds all-up sets
#define SB_MAX_AUP_POOL         30                  // max. # of pools in fo all-up set
                                                    // PN22
#define SB_ODDS_GEN_MAX         SB_MAX_LEAGUE_TEAM  // max. # of odds in a pool
                                                    // currently champion has most odds
#define SB_ODDS_SPC_MAX         5                   // max. # of HDC/OOU odds set per pool
#define SB_ODDS_SPC_MAX_CUR     1                   // max. # of HDC/OOU odds used // JC09
#define SB_HDCGOAL_FACTOR       10                  // handicap goal factor
#define SB_MAX_AFML             60                  // max aup formula for sb

#define SB_MAX_COMB             SB_MAX_LEAGUE_TEAM  // max number of collated
                                                    // combination; currently
                                                    // it is champion pool with
                                                    // max. 64 teams    PN15
// PN22.. Selection number for goalscorer
#define SB_MAX_PLAYER_SEL     44        // max # of goalscorer selection
                                        // selection 0 is not used
#define SB_MAX_PLAYER_HO      41        // home others
#define SB_MAX_PLAYER_AO      42        // away others
#define SB_MAX_PLAYER_NG      43        // no goal
// ..PN22

#define SB_POOL_1X2     0
#define SB_POOL_HDC     1
#define SB_POOL_COS     2
#define SB_POOL_DBR     3
#define SB_POOL_TOS     4
#define SB_POOL_OOU     5
#define SB_POOL_OES     6
#define SB_POOL_FGS     7
#define SB_POOL_HCS     8   // half time full time correct score     PN22
#define SB_MAX_POOL_MATCH_USE   (SB_POOL_HCS+1)     // max. # of simple pools in use
                                                    // PN22
#define SB_MAX_POOL_MATCH       12                  // max. # of simple pools in a match
                                                    // 0 to 11 are for match related simple pools
                                                    // 12 to 15 are for non-match related simple pools

#define SB_POOL_SPC_MATCH	18	// special pool (match related)
#define	SB_POOL_SPC_TRN		19	// special pool (tournament related)
#define SB_POOL_THF     20  // treble half time/full time correct score PN22
#define SB_POOL_HFM		21	// mulitple half time/full time result
#define SB_POOL_HCSD	22  // half/full time correct score doubled
#define	SB_POOL_BNG		23  // Bingo
#define SB_POOL_CHP		40  // Championship
#define	SB_POOL_CHPP	41	// Champion and First Runner Up
#define	SB_POOL_FINP	42  // Quarter Finalist
#define	SB_POOL_GPF		43  // Group Forcast
#define SB_POOL_GPW		44	// Group Winner
#define SB_POOL_TPS		45	// Top Scorer/Team


#define SB_MAX_POOL     40                          // max. # of pool type PN22
                                                    // 20 to 39 for non simple
                                                    // pool type

#define SB_LEN_LEAGUE   64                          // length of championship name
#define SB_LEN_TEAM     64                          // length of team name
#define SB_LEN_PLAYER   32                          // length of player name

#define SB_HOME_WIN     0                           // home win
#define SB_AWAY_WIN     1                           // away win
#define SB_DRAW         2                           // draw

#define SB_OVER         0                           // over
#define SB_UNDER        1                           // under

#define SB_EVEN         0                           // even
#define SB_ODD          1                           // odd

#define SB_PCAT_FO      0                           // fix odds pool category
#define SB_PCAT_PM      1                           // parimutuel pool category
#define SB_MAX_PCAT     2                           // max pool category

#define SB_MIN_HDC      (-5)                        // min. handicap goal (max. home give score)
#define SB_MAX_HDC      5                           // max. handicap goal (max. home get score)
#define SB_MAX_COS      5                           // max. correct score
#define SB_MAX_TOS      7                           // max. total score
#define SB_MAX_OOU      10                          // max. over or under

#define SB_RES_HALF     0                           // half result index
#define SB_RES_FULL     1                           // full result index
#define SB_MAX_RES      2                           // number of result entry

#define SB_RES_VOID     -1                          // result void
#define SB_RES_NOTIN    -2                          // result not-in

#define SB_AC_TYPE_BOOKIE   9                       // LY19 bookie account type

// PN22.. defines for configurable pool
#define SB_MAX_CFG_SEL  99      // maximum # of selection
#define SB_MAX_CFG_POOL 99      // maximum # of outstanding pool
// ..PN22

//
// Following define is used for declaration of an unknown array of item
// within the last field of a data structure.  Such data type is only used 
// for type casting purpose on a byte stream, and should not used for any
// variable declaration.
//
#define SB_MAX_COL_ENT  3000    // number of entry in collation table
#define SB_MAX_COL_HDC  100     // number of entry in handicap collation table
#define SB_MAX_COL_ADIR 5000    // number of entry in all-up set collation 
                                // directory PN22
                                // Remark: this is only large enough for an 
                                // all-up set defined with 3 level 30 pools.
                                // If more level is required, less pool can be
                                // supported.  Validation is required in all-up
                                // set defined.
        
//#pragma pack(1)

struct SB_RESULT                // result
{
    short                 homew;                    // home goals [<0 void] // JC03
    short                 awayw;                    // away goals           // JC03
};

struct SB_POOL_COMMON           // common pool info
{
    unsigned short        drefwu;       // index number of description  PN22
                                        // reference table map          PN22
    unsigned int          colStalu;                 // collation start in bytes
    unsigned short        colSizwu;                 // collation size in bytes
//    struct BSTPOLAREA     area[BST_AREA_MAX];       // area control     // JC14
    unsigned int          single1:1;                // single betting allowed
    unsigned int          aup1:1;                   // all-up betting allowed
    unsigned int          cancel1:1;                // cancel allowed (this
                                                    // will be set during
                                                    // start sell and cleared
                                                    // during match close or
                                                    // badsales timeout)
    unsigned int          pay1:1;                   // paying
    unsigned int          refund1:1;                // refund
    unsigned int          claim1:1;                 // claim
    unsigned int          exotic1:1;                // exotic pool
    unsigned int          fix1:1;                   // dividend fixed
    unsigned int          :8;                       // unused       // JC13
//    struct BSTPUBET       pubet;                    // partial unit bet control
                                                    // parameter        PN22
};

struct SB_ODDS_GEN              // general odds
{
    unsigned int          curlu;                    // current odds * 100       // JC21
    unsigned int          prvlu;                    // previous odds * 100      // JC21
    unsigned int          sell1:1;                  // selling allowed 
    unsigned int          refund1:1;                // refund selection    PN22
    unsigned int          :6;                       // unused
};

struct SB_ODDS_SPC              // special odds for HDC and OOU
{
    char                  curGoalb[2];              // current handicap goal
                                                    // [0] handicap goal 1 * 10 or OOU goal
                                                    // [1] handicap goal 2 * 10 [=goal 1 if normal]
    char                  prvGoalb[2];
    struct SB_ODDS_GEN    odds[2];                  // for HDC, [0]=SB_HOME_WIN, [1]=SB_AWAY_WIN
                                                    // for OOU, [0]=SB_OVER, [1]=SB_UNDER
};

union SB_ODDS                   // odds info
{
    struct SB_ODDS_GEN    gen[SB_ODDS_GEN_MAX];
    struct SB_ODDS_SPC    spc[SB_ODDS_SPC_MAX];
};

struct SB_POOL                  // pool info
{
    __time32_t                oddsTime;                 // time odds last changed
    LONGLONG              netLossd;                 // max. net loss
    unsigned LONGLONG     divdu;                    // pari-mutuel dividend in cents
    char                  pmGoalb;                  // pari-mutuel goal for HDC and OOU
    struct SB_POOL_COMMON pInfo[SB_MAX_PCAT];       // pool info
    char                  numOdds;                  // number of odds info.
    union SB_ODDS         odds;                     // odds info
    LONGLONG              plimitd[SB_MAX_COMB];     // position limit in cents 
                                                    // > 0 => max. net loss
                                                    // <= 0 => min. profit
                                                    // PN15
};

struct SB_MATCH_ID
{
    unsigned char         daybu;                    // day of week
    unsigned char         matchbu;                  // match # within day
};

struct SB_CPX_POOL_ID
{
    unsigned char         poolbu;                   // pool type
    struct SB_MATCH_ID    match;                    // match id
};
struct SB_CPX_DIV               // complex dividend
{
    unsigned LONGLONG     divdu;      // dividend
    unsigned char         typebu;     // type
        #define SB_DIV_NORMAL   1     // normal dividend
        #define SB_DIV_CONSOL   2     // consolation
    unsigned int          pay1:1;     // paying
    unsigned int          claim1:1;   // claim
    unsigned int          fix1:1;     // dividend fix
    unsigned int          :5;
};
struct SB_CPX_POOL              // complex pool
{
    unsigned char         ptypebu;                  // pool type for parameter
                                                    // table reference
    unsigned char         numPoolbu;                // # of simple pool
    struct SB_CPX_POOL_ID id[SB_MAX_POOL_CPX];      // match info
    struct SB_POOL_COMMON pInfo;                    // common pool info
    unsigned int          wptrlu;                   // start of winning comb.
    unsigned char         numDivbu;                 // # of dividend
    struct SB_CPX_DIV     div[SB_MAX_CPX_DIV];      // dividend
};

struct SB_STATUS
{
    __time32_t                rfdTime;                  // start of refund time
//    unsigned char         clsWarnbu[BST_AREA_MAX];  // close warning sent indicator
                                                    // PN12
    unsigned int          def1:1;                   // match defined
    unsigned int          close1:1;                 // closed
    unsigned int          final1:1;                 // collation final
    unsigned int          partres1:1;               // partial result in    // JC03
    unsigned int          res1:1;                   // result in
    unsigned int          abandon1:1;               // abandon
    unsigned int          refund1:1;                // apply refund time
    unsigned int          clseod1:1;                // eod done after close
    unsigned int          purged1:1;                // match can be purged
                                                    // (This flag is used by
                                                    // eod to indicated whether
                                                    // a match can be purged 
                                                    // today.  It will be
                                                    // set when eod starts
                                                    // according to attached
                                                    // pool status.  If there
                                                    // is any non controlled
                                                    // fixed all-up bet or
                                                    // parimutuel all-up bet,
                                                    // any related match in all
                                                    // selected events will be 
                                                    // purged)
    unsigned int          :7;                       // unused               // JC03
};

struct SB_MATCH                 // match
{
    __time32_t                time;                     // match time
    struct SB_MATCH_ID    id;                       // match id
    unsigned short        homewu;                   // home team #
    unsigned short        awaywu;                   // away team #
    struct SB_RESULT      result[SB_MAX_RES];       // half time and full time result
    short                 fgPlayerw;        // first goalscorer winning PN22..
                                            // selection number
    unsigned short        playerwu[SB_MAX_MATCH_PLAYER+1];
                                            // player # by selection number
                                            // 0 => selection number not defined
                                            // ..PN22
    struct SB_POOL        pool[SB_MAX_POOL_MATCH];  // pool
    struct SB_STATUS      status;
    __time32_t                rpttime;          // report match date        PN15
};

struct SB_CHP                   // championship
{
    __time32_t                time;                     // championship time
    unsigned char         leaguebu;                 // league #
    unsigned char         roundbu;                  // round #
    unsigned char         numTeambu;                // # of teams
    unsigned short        teamwu[SB_MAX_LEAGUE_TEAM];     // team #
    struct SB_STATUS      status;
    struct SB_POOL        pool;                     // common pool info
    unsigned short        champwu;                  // winning team
};

struct SB_AUP_PAR               // all-up by level by set parameter
{
    LONGLONG              netLossd;                 // net loss limit in cents, 
    LONGLONG              oddsMaxd;                 // max. long odds*100  per bet,
};

struct SB_AUP                   // all-up set info.
{
    unsigned int          colStalu;                 // collation start
    unsigned int          colSizlu;                 // collation size
    unsigned char         levelbu;                  // max. all-up level
    unsigned char         poolbu;                   // # of pools (0=>this set
                                                    // is not defined)
    struct SB_AUP_PAR     par[SB_MAX_AUP_EVENT-1];  // by level para, indexed by event-2
    struct SB_CPX_POOL_ID id[SB_MAX_AUP_POOL];      // pool info
};

struct SB_PAR_AREA
{
    unsigned char         enat;         // enable checking (for max only) //JC05
    LONGLONG              maxd;         // max. investment per bet in cents
    LONGLONG              mind;         // min. investment per bet in cents
};

struct SB_PAR_1                 // per pool or all-up
{
    unsigned short        unitwu;                   // unit investment in $
//    struct SB_PAR_AREA    area[BST_AREA_MAX];        // per-area parameter PN12
//    struct BSTPUBET       pubet;    // partial unit bet control parameter PN22
};
struct SB_PAR                   // per pool or per all-up level
{
    LONGLONG              payMaxd;      // max. payout in cents
    unsigned short        bonuswu;      // bonus % * 100
};

// LY16.. PN15..
// Unit investment check on failure of position limit validation.
struct SB_PAR_PLIMIT
{
    unsigned int          daccept1:1;   // direct accept enable flag   PN22
    unsigned int          accept1:1;    // always accept unit bet enable flag PN22
    unsigned int          intercept1:1; // large unit bet intercept flag  PN22
    // Accept bet with unit investment <= this value.
    unsigned int          acceptlu;     // unit investment in $ to accept bet
    // Intercept required for bet with unit investment >= this value.
    unsigned int          interceptlu;  // unit investment in $ to intercept bet
};
//..PN15 ..LY16

struct SB_POOL_PAR
{
    struct SB_PAR         para;
    struct SB_PAR_1       parb[SB_MAX_PCAT];        // other parameters
    BOOL                  afmt[SB_MAX_AFML];        // allup formula
//    struct SB_PAR_PLIMIT  plimitunit[BST_AREA_MAX]; // unit invest. for position limit 
                                                    // check PN15 // JC23
};

struct SB_AC_TYPE
{
    LONGLONG              invMaxd;      // max. account investment per day in cents
    unsigned int          sbEnable1:1;  // soccer betting enable
    unsigned int          intercept1:1; // customer always intercept flag PN22
    unsigned int          bookie1:1;    // bookie type account PN22
    unsigned int          :5;           // unused
};

struct SB_AREA_PAR
{
    unsigned int          invAuth1:1;   // max. investment authorization
// DD02...
    unsigned int          peakhr1:1;    // 1 = peak hour effective
    unsigned int          :6;           // unused
    LONGLONG              peakmind;     // peak hour minimum cost in cents
// ...DD02
};

//  PN22..
struct SB_CFG                   // configurable pool ( Quick bet )
{
    __time32_t                  time;       // pool closing date and time
    unsigned int            poolidlu;   // pool id in binary value
    unsigned char           pgrpbu;     // pool group                               // JC23
        #define SB_CFG_PCAT_CHP 1       // champion
        #define SB_CFG_PCAT_CFG 2       // special configurable pool
    struct SB_POOL          pool;       // pool information
    struct SB_STATUS        status;     // pool status
    unsigned int            maxpay1:1;  // max. payout check enable flag
    unsigned int            maxloss1:1; // max. loss check enable flag
    unsigned int            :6;                                       
    LONGLONG                netlossd;   // maximum net loss
    struct SB_PAR           para;       // pool parameter
    struct SB_PAR_1         parb[SB_MAX_PCAT];  // other parameter
//    struct SB_PAR_PLIMIT    plimitunit[BST_AREA_MAX];
                                        // unit invest for position limit check
    unsigned char           nselbu;     // number of selection
    unsigned char           selbu[SB_MAX_CFG_SEL];  // selection number
    unsigned char           ndivbu;                 // # of dividend
    struct SB_CPX_DIV       div[SB_MAX_CPX_DIV];    // dividend
};
// ..PN22

struct SB
{                                                                       // JC06
    unsigned int          lossAuth1:1;      // net loss authorization
    unsigned int          aupCheck1:1;      // all-up net loss checking enabled
    unsigned int          poolCheck1:1;     // pool net loss checking enabled   // JC05..
    unsigned int          maxLOddsCheck1:1; // max long odds checking enabled
    unsigned int          payMaxCheck1:1;   // max payout checking enabled
    unsigned int          profitMaxCheck1:1;// max profit checking enabled      // JC08
    unsigned int          :10;                   
    LONGLONG              acProfitMaxd;     // max. account profit per day in cents //JC08
    struct SB_AC_TYPE     acType[SB_MAX_AC_TYPE];
    unsigned int          colSizelu[SB_MAX_PCAT];   // size of collation used in bytes
    unsigned LONGLONG     hoPaydu;          // h.o. pay limit in cents      // JC11
    unsigned short        oddIntwu;         // odds grace period in seconds
    unsigned short        badSaleIntwu;     // bad sale interval in seconds
//    struct SB_AREA_PAR    area[BST_AREA_MAX];// per area parameter PN12
    unsigned short        closeWarnwu;      // match close warning in minutes
    unsigned short        refundwu;         // refund deduction % * 100
    unsigned short        kalawu;           // handicap kala deduction % * 100
    short                 cancelIntw;       // cancel interval in minute, <0 no limit
    struct SB_POOL_PAR    poolPar[SB_MAX_POOL];
    struct SB_PAR         aupLevelPar[SB_MAX_AUP_EVENT-1];  // index by level-2
    struct SB_PAR_1       aupPar[SB_MAX_PCAT];              // allup parameter
    unsigned short        retDaywu;         // full retention days
    unsigned char         goalMaxbu;        // team goal max.
    unsigned char         scoreMaxbu;       // total score max.
    unsigned char         oouMaxbu;         // over or under max.
    unsigned short        matchMaxwu;       // last used match index +1
    unsigned short        chpMaxwu;         // last used championship index +1
    unsigned short        cpxMaxwu;         // last used complex pool index +1
    unsigned short        mseqMaxwu;        // number of match sequence used
    struct SB_MATCH       match[SB_MAX_MATCH];      // match
    struct SB_CHP         chp[SB_MAX_CHP];  // championship
    struct SB_CPX_POOL    cpx[SB_MAX_CPX_POOL];     // complex pools
    struct SB_MATCH_ID    seq[SB_MAX_MATCH];        // match in sequence
    struct SB_AUP         aup[SB_MAX_AUP_SET];      // fixed odds all-up sets
    LONGLONG              oddsMaxd[SB_MAX_AUP_EVENT-1]; 
                                                    // max. odds per bet for
                                                    // non-controlled all-up 
                                                    // fixed odds (by level,
                                                    // indexed by event-2), 
    // the # of defined for league, team, player are counted from index o
    // but the data of index 0 are not used, the index # and the name id are same
    // e.g. league name # 1 is stored in leagueName[1]
    unsigned short        leagueMaxwu;  // # of league defined
    char                  leagueName[SB_MAX_LEAGUE][SB_LEN_LEAGUE]; // league name
    unsigned short        teamMaxwu;    // # of teams defined
    char                  teamName[SB_MAX_TEAM][SB_LEN_TEAM];       // team name
    unsigned short        playerMaxwu;  // # of players defined
    char                  playerName[SB_MAX_PLAYER][SB_LEN_PLAYER]; // player name
    unsigned int          wsizlu;       // next use winning comb. array PN22..
    unsigned short        rmtimewu;     // RM intercept timer in seconds
    unsigned short        cfgMaxwu;     // # of used configurable pool 
    struct SB_CFG         cfg[SB_MAX_CFG_POOL]; // configurable pool       
                                        // ..PN22
};

// PN22..
#define SB_TWCOM    (10000*512)         // winning comb. array size

struct SBWCM                            // winning comb. for complex pool
{
    unsigned char wcmbu[SB_TWCOM];            
};

struct SBWCM_MHFT   // multiple leg half full time
{
    char    resb[SB_MAX_CPX_POOL][SB_MAX_RES];  // result of each match
                                                // SB_RES_VOID => all win
};

// ..PN22

struct SB_COL_ENT               // fixed odds collation entry
{
    unsigned LONGLONG     invdu;        // investment in cents
    double                liar;         // liability
};

struct SB_COL_TABLE             // fixed odds collation table
{
    unsigned LONGLONG     totInvdu;     // total investment
    struct SB_COL_ENT     ent[SB_MAX_COL_ENT];  // collation entry
};                                              // size is pool dependant

struct SB_COL_ENT_HDC           // fixed odds handicap collation entry
{
    unsigned LONGLONG     invdu;        // investment in cents
    double                liar;         // liability including kala
    double                kalar;        // kala liability
};

struct SB_COL_TABLE_HDC         // fixed odds handicap collation area
{
    unsigned LONGLONG     totInvdu;     // total investment in cents
    struct SB_COL_ENT_HDC ent[SB_MAX_COL_HDC];     // collation entry
};

struct SB_AUP_PASS              // fixed-odds all-up pass per-level information
{
    unsigned LONGLONG     invTotdu;     // total investment in cents
    unsigned LONGLONG     invUnsdu;     // unsettled investment cents
    double                liar;         // known liability including refund incents
    unsigned LONGLONG     refunddu;     // refund liability
};

struct SB_COL_FO_AREA           // fixed odds collation area
{
    unsigned int          seqStartlu;   // all-up pass start log seq.
    unsigned int          seqEndlu;     // all-up pass end log seq.
    __time32_t                time;         // all-up pass finish time
    double                roundr;       // total all-up payout rounding in cents
    struct SB_MATCH_ID    lastMatch;    // last complete div-in match ID
    struct SB_AUP_PASS    level[SB_MAX_AUP_EVENT-1];// per level all-up pass info - index by level-2
    unsigned LONGLONG     aupInvdu;     // multi-level all-up investment 
                                        // outside set in cents (this will be
                                        // updated under following condition:
                                        // by BTHNDR: selling, cancel, or
                                        // any reversed
                                        // by EOD: deduct those event
                                        // combinations with matches firstly
                                        // closed)
    unsigned char         colbu[SB_MAX_COL_FO];     // fixed odds collation tables
};

struct SB_COL_AUP_DIR           // fixed odds all-up set directory entry
{
    unsigned int          startlu;      // byte offset of collation table start
    unsigned short        nextwu;       // entry # to next collation table of same level
};

struct SB_COL_AUP               // fixed odds all-up set collation
{
    unsigned LONGLONG     totInvdu;     // total investment in cents in set
                                        // LY07 not including level1 investment
    struct SB_COL_AUP_DIR ent[SB_MAX_COL_ADIR]; // directory, size depends on level and # of simple pool
};

//#pragma pack(1)

#endif
