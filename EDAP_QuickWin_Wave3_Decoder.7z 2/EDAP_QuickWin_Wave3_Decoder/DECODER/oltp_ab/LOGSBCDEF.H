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
//    LOGSBCDEF.H - Defines the structures of SBC logger records
//
//    Author : Joseph Chan                20 Aug 2001
//
//    Mod :         JC01            06-FEB-2002
//                  change match result data type to short
//
//                  JC02            22-FEB-2002
//                  1. change peak hour minimum message
//                  2. add new message
//
//                  JC03            26-FEB-2002
//                  change message struct of SBMSG_CTL_CODE_AC_PAY_MAX
//
//                  JC04            05-MAR_2002
//                  change struct name to more appropriate
//
//                  JC05            15-MAR-2002
//                  add enable/ disable flag for max/ min investment
//
//                  JC06            15-APR-2002
//                  change peak hour min. amt to unsigned LONGLONG
//                  value in cents.
//
//                  JC07            06-SEP-2002
//                  1. change the amount value (SBCMXPO, SBCAPAR, HOPAY,
//                     INVL, IMXN) to unsigned LONGLONG
//                  2. remove struct SBCINVL and SBCINVV since no
//                     anyplace refer
//                  3. odds value to be stored in n*100
//
//                  CS08            12-SEP-2002
//                  replace define name
//
//                  JC09            19-SEP-2002
//                  add position limit flag
//
//                  JC10            24-OCT-2002
//                  remove souce system id from header
//                  ( such information to be stored in mail header portion )
//
//                  JC11            09-JAN-2003
//                  add business date in match define message
//                  background: SBC send define match message to
//                  RM with business date but no such field in the
//                  message sent to SB.  RM wants to get same mail
//                  both from SBC and logger record from SB.
//
//                  JC12            17-JAN-2003
//                  change defines for supporting position limit by combination
//
//                  JC13            27-MAR-2003
//                  expand odds storage unsigned to I*4
//
//                  JC14            19-MAY-2003
//                  add mail messages for next business date from SBC
//
//                  JC15            12-JUN-2003
//                  1. delete position limits in define pool message
//                  2. take out SBC message code 5 "net loss warning %"
//                  3. take out player list in pool define
//                  4. add new logger message defines: LOGSBCACCEPT (66),
//                      LOGSBCITRCP (67), LOGSBCPLIMIT (68), LOGSBCFGSINFO (71)
//                      LOGSBCPOOLRES (72), LOGSBCCOMBREFUND (73)
//                      LOGSBCCOMBCANRFD (74)
//
//                  JC16            08-JUL-2003
//                  include cpx pools to be close in match close logger
//
//                  JC17            14-JUL-2003
//                  add exotic winning investment report
//
//                  JC18            17-JUL-2003
//                  add new max # of cpx pool in logger record
//
//                  JC19            07-AUG-2003
//                  add new logger message defines: LOGSBCMBT (78)
//
//                  JC20            12-AUG-2003
//                  add div. type for simple pari-mutuel pool
//
//                  JC21            03-SEP-2003
//                  all up set has a number to indicate what level it
//                  is collated up to
//
//                  JC22            08-SEP-2003
//                  1. add SBMSG_CTL_CODE_STS_ACOMB (79),
//                         SBMSG_CTL_CODE_SEL_ACOMB (80)
//                  2. control whether detail liability is required
//
//                  JC23            22-SEP-2003
//                  add sbc control message caller
//
//                  JC24            23-SEP-2003
//                  add SBMSG_CTL_CODE_BETADJ (81)
//
//                  JC25            15-OCT-2003
//                  Delta 3 - stage 2
//                  1. add comb info. for define pool message ( for CRS only ) 
//
//                  JC26            30-Oct-2003
//                  add bonus % by level by pool
//
//                  JC27            20-NOV-2003
//                  add HDC draw deduction %
//
//                  JC28            03-DEC-2003
//                  expand array size for bonus by pool by level
//
//                  JC29            29-DEC-2003
//                  add logger record for tournament pools
//
//                  DJ30            12-02-2004
//                  add pool create business date when define new trn pool
//
//                  JC31            21-FEB-2004
//                  add team information in team list logger records
//
//                  JC32            25-FEB-2004
//                  add pool cat in TRN id
//
//                  JC33            11-MAR-2004
//                  1. add defines for Stage 3A
//                  2. replace function code 29 by 107, 83 by 108, 78 by 110, 
//                  3. expand min bet value by terminal (110)
//                     to by TRM by pooltype by pool cat
//
//                  JC34            06-APR-2004
//                  since the limitation of the logger size in legacy,
//                  when define 500 matches, the match sequence list in
//                  logger record make the logger exceed the max. logger
//                  size, to solve it, trimming is performed when create
//                  the seq list, 4 bits for match day and 1 byte for match
//                  #, i.e. 3 bytes for 2 matches
//
//                  JC35            08-APR-2004
//                  add define for pool close
//
//                  JC36            15-APR-2004
//                  add bit to indicate others is accepted for TPS
//
//                  JC37            05-JUN-2004
//                  add # of leg to be matched for dividend of multi-leg pools
//
//                  JC38            20-SEP-2004
//                  1. changes for Q105
//                  2. add define section bet set (126)
//
//                  JC39            05-OCT-2004
//                  change logger structure for Q105
//
#ifndef LOGSBCDEF_H
#define LOGSBCDEF_H 1

#include "sbdef.h"
//#include "sbmsgdef.h"
#include "betdef.h"                         // JC24
//#include "drefdef.h"                        // JC29

#define     LOGSBC_TYPE_MATCH   1
#define     LOGSBC_TYPE_TRN     2
#define     LOGSBC_TYPE_CPX     3
#define     LOGSBC_TYPE_SPC     4

#define     LOGSBC_WCM_SIZE     3           // JC15

#define     LOGSBC_TERM_TYPE_SVT    0       // JC19
#define     LOGSBC_TERM_TYPE_OPT    1       // JC19

#define     LOGSBC_CALLER_SBC       0       // control message caller is SBC    // JC23
#define     LOGSBC_CALLER_SBCC      1       // control message caller is SBCC   // JC23

#define     LOGSBC_WCM_COMB_SIZE    64      // wcm size, max for ADTP 32*2      // JC29

#define     SBC_CMD_START_SELL      0 
#define     SBC_CMD_STOP_SELL       1
#define     SBC_CMD_MATCH_CLOSE     2
#define     SBC_CMD_POOL_CLOSE      3       // JC35
#define SBC_WCM_BUFSIZE (SB_MAX_POOL_CPX*LOGSBC_WCM_SIZE*SB_MAX_CPX_DIV)

#define SPC_MAX_ITEM        5       // max. SPC pool item #
#define SPC_MAX_SELECT      6       // max. SPC pool selection #

#pragma pack(1)

//struct LOGSBCPROFITMAX_ENT
//{
//    unsigned char         acTypebu;         // A/C type
//    unsigned char         enabu;            // checking enabling
//    unsigned LONGLONG     amtdu;            // maximum profit in cents
//};

struct LOGSBCPROFITMAX     // daily max profit per account (1)      // JC39
{
    unsigned char               numbu;      // # of entry
//    struct LOGSBCPROFITMAX_ENT  ent[SBMSG_ENT_SIZE];
    struct SBMSG_PROFITMAX_ENT  ent[100];
};

struct SBCAPAR
{
    unsigned char       typebu;                     // account type
    unsigned char       enabu;                      // allow soccer betting
    unsigned LONGLONG   amtdu;                      // amount in cents  // JC07
};

struct LOGSBCAPAR       // fix odds account type parameter (2)
{
    unsigned char       numbu;                      // # of AC type involved
    struct SBCAPAR      par[SB_MAX_AC_TYPE];    
};

//struct SBCMXPO
//{
//    unsigned char       idbu;                       // simple pool id/ all-up level
//    unsigned LONGLONG   amtdu;                      // max long odds value*100, or,
//                                                    // max. amount in cents // JC07
//};

struct LOGSBCMAXI                       // (3), (12), (13)
                                        // (120), (121), (122), (123), (124), (125) 
{
    unsigned char           numbu;                  // # of entry
//    struct SBCMXPO      mxpo[SBMSG_ENT_SIZE];    
    struct SBMSG_MAXI_ENT   ent[SBMSG_ENT_SIZE];
};

struct SBCAUTH
{
    unsigned char       areabu;                     // area code
    unsigned char       enabu;                      // max. inv. auth enabling
};

struct LOGSBCMIAU       // max. investment authorisation (9)
{
    unsigned char       numbu;                      // # of area involved
    struct SBCAUTH      auth[BST_AREA_MAX];         // CS08
};

struct SBCBONUS
{
    unsigned char       idbu;                       // simple pool id (no use by (93))
    unsigned char       levbu;                      // all-up level (no use for (14))   // JC26
    unsigned short      bonwu;                      // bonus % * 100
};

struct LOGSBCBON        // bonus % by pool (14), bonus % by all-up level (15)
{
    unsigned char       numbu;                      // # of simple pool/ all-up level involved
    struct SBCBONUS     bonus[SB_MAX_POLLEV];       // JC28
};

//struct SBCIMXN1                                     // structure for each area in LOGSBCIMXN
//{
//    unsigned char       areabu;                     // area id
//    unsigned char       enabu;                      // enabling         // JC05
//    unsigned char       poolbu;                     // pool id
//    unsigned LONGLONG   amtdu[2];                   // amount in cents  // JC07
//                                                    // [0] for fixed odds, [1] for pari-mutuel
//};

struct LOGSBCIMXN                       // (16), (17), (18), (19), (128), (129), (130),
                                        // (131), (132), (133), (134), (135), (136)
{
    unsigned char           numbu;                  // number of entry
//    struct SBCIMXN1     imxn1[SBMSG_ENT_SIZE];      // JC15
    struct SBMSG_IMXN_ENT   ent[SBMSG_ENT_SIZE];
};

//struct SBCAINVL
//{
//    unsigned char       areabu;                     // area id
//    unsigned char       enabu;                      // enabling         // JC05
//    unsigned LONGLONG   amtdu[2];                   // amount in cents  // JC07
//                                                    // [0] for fixed odds, [1] for pari-mutuel
//};
//
//struct LOGSBCAINVL      // max all-up investment per bet (17)
//                        // min all-up investment per bet (19)
//                        // max cross pool all-up inv. per bet (128)     // JC38
//                        // min cross pool all-up inv. per bet (135)     // JC38
//{
//    unsigned char       numbu;                      // number of area involved
//    struct SBCAINVL     ainvl[BST_AREA_MAX];        // CS08
//};

struct SBCAUFM
{
    unsigned char       pidbu;                      // simple pool id
    unsigned LONGLONG   enaBitdu;                   // enabling bit mask,
                                                    // refer to all-up formula id 
};

struct LOGSBCAUFM       // all-up formula (22)
{
    unsigned char       numbu;                      // # of simple pool involved
    struct SBCAUFM      sbcaufm[SB_MAX_POOL];       // all-up formula bit mask
};

struct SBCNAME                                      // structure for each league/ team/ player
                                                    // in LOGSBCNAME
{
    unsigned short      idwu;                       // league/ team/ player id/ tournament pool id
    unsigned char       lenbu[2];                   // [0]=english name len, [1]=chinese name len
    char                nameb[SB_MAX_NAME_BUF];     // the name buffer, english name then chinese name
};

struct LOGSBCNAME       // team name (24), league name (25), player name (26)
{
    unsigned char       numbu;                      // number of items
    unsigned char       bu[SB_MAX_VAR_SIZE];
};

struct VARSEQ               // JC34
{
    unsigned char       m1day4:4;       // match day of first match
    unsigned char       m1num8:8;       // match # of first match
    unsigned char       m2day4:4;       // match day of second match
    unsigned char       m2num8:8;       // match # of seconf match
};

struct LOGSBCMINP       // define new match (27)/ // define new match enquiry (63)
{
    short               mIdxw;                      // new match index
    struct SBMSG_ID     id;                         // match id
    __time32_t              t;                          // match date/ time
    __time32_t              bDate;                      // match business date  // JC11
    unsigned char       leagbu;                     // league id
    unsigned short      homewu;                     // home team id
    unsigned short      awaywu;                     // away team id
    unsigned short      newMatchMaxwu;              // new number of match
    unsigned short      newMseqMaxwu;               // new number in match seq
//    struct SBMSG_ID     newSeq[SB_MAX_MATCH];       // new match seq
    unsigned char       bu[SB_MAX_VAR_SIZE];        // new match seq
                                                    // [bit 0 to bit 3 for match day
                                                    //  bit 4 to bit 11 for match #]    // JC34
};

struct LOGSBCPLIMIT_ENT                             // JC15..
{
    unsigned char       seqbu;                      // combination sequence
    LONGLONG            posLimitd;                  // pos. limit in cents
                                                    // >0 => max. net loss
                                                    // <=0 => min. profit
                                                    // Remarks: this is opposite with
                                                    // that in interface between SBC and
                                                    // remotes.  In the message from SBC,
                                                    // >0 for min profit, <=0 for max ne loss. 
};                                                  // ..JC15

struct LOGSBCPINP       // define new pool (107)
{
    LONGLONG                    netLossd;           // max. net loss amount in cents
    unsigned char               single1:1;          // single allowed
    unsigned char               aup1:1;             // all-up allowed
    unsigned char               hftbet1:1;          // half/full time bet allowed       // JC38
    unsigned char               :5;                 // unused
    struct SBMSG_POOL_ID        pid;                // max. size of pool id is occupied
    unsigned char               cpxPoolbu;          // cpx pool type
    unsigned char               pTypebu;            // pool type SIMPLE/CPX
    short                       idxw;               // champ/ match/ cpx pool index
    unsigned int                newColSizelu;       // new collation size
    unsigned int                colStartlu;         // collation start
    unsigned int                colSizelu;          // collation size
    unsigned short              newNumwu;           // new max # of cpx pool    // JC18
    unsigned int                punitlu;            // partial unti in $        // JC33
    unsigned int                minCostlu;          // min. tkt cost in $       // JC33
    unsigned short              numwu;              // num of combination       // JC25
    struct SB_RESULT            crssel[SB_MAX_CRS_SEL]; // comb info, now for CRS only    // JC25
};

// JC29..
//
struct LOGSBCTRNID          // tournament id in logger record
{
    unsigned char           ptypebu;    // pool type
    unsigned char           pmbu;       // FO/ PM
//    unsigned char           catbu;      // for SPC => SB_SPC_TRN/SB_SPC_MAT
//                                        // for TPS => SB_TPS_PLAYER/SB_TPS_TEAM
//                                        // others => filler
    unsigned char           pidbu;      // TRN => TRN id
                                        // SPC-TRN base => TRN id
                                        // SPC-match base => match day 
    unsigned char           subidbu;    // GPF/GPW => group id
                                        // ADTP => event id
                                        // TPS => PLAYER/TEAM type
                                        // SPC-TRN base => type id
                                        // SPC-match base => match #
                                        // others => filler
    unsigned char           itembu;     // SPC => item id
                                        // others => filler
    unsigned short          idxwu;      // TRN index/ SPC map index
};

// variable buffer of data for dref
// TRN name string len (unsigned char)
// TRN name string (variable size)
// TRN short name len (unsigned char)
// TRN short name (variable size)
// Event/ Item description len (unsigned char)
// Event/ Item description (variable size)
//
struct LOGSBCTINP           // define new TRN pool (108)/ SPC pool (109)
{
    struct LOGSBCTRNID      id;                     // tournament id
    __time32_t                  tDate;                  // tournament event date, DJ30...
    __time32_t                  drsdate;                // reference creation datetime ( datBusinessTime() )
    __time32_t                  sDate;                  // trn settlement date                       
    __time32_t                  cDate;                  // pool creation date
    unsigned short          newNumwu;               // new last TRN/SPC Map index used
    unsigned short          spcIdxwu;               // new SPC idx
    unsigned short          newSpcwu;               // new last SPC index used
    short                   catIdxw;                // default match idx/ TRN idx
                                                    // for SPC set default id used only, -1=>no default)
    LONGLONG                netLossd;               // max. net loss amount in cents
    unsigned int            single1:1;              // single allowed
    unsigned int            aup1:1;                 // all-up allowed
    unsigned int            exact1:1;               // exact result order
    unsigned int            exo1:1;                 // exotic pool flag i.e. non-collated
    unsigned int            min1:1;                 // min select for TPS, 0=>others enabled    // JC36
    unsigned char           :3;                     // unused
    unsigned char           minSelbu;               // min. # of selection in each group
    unsigned char           maxSelbu;               // max. # of selection in each group
    unsigned char           nselbetbu;              // min. # of selection in a bet
    unsigned char           nGroupbu;               // # of group
    unsigned char           nTeambu;                // max. # of team in within groups
    unsigned int            colSizelu;              // collation size of this pool
    unsigned int            colStartlu;             // collation pointer in COLCOM
    unsigned int            newColSizelu;           // next use collation pointer
    unsigned short          refMapPtrwu;            // ref. file mapping table pointer
    unsigned int            refDataPtrlu;           // ref. file data byte pointer
    unsigned int            refDataSizelu;          // ref. file data byte size
    unsigned int            refDataNewSizelu;       // ref. file new data byte pointer
    unsigned char           fillerwu;               // FILLER - 2BYTES TO 1BYTE (201108PSR)
    BOOL					otherselwt;             // Enable Others Selection (JKC only) (201108PSR)
    unsigned int            punitlu;                // partial unti in $        // JC33..
    unsigned int            minCostlu;              // min. tkt cost in cents
    unsigned char           numSelbu;               // number of selection
    unsigned short          homewu;                 // for SPC match base used only
    unsigned short          awaywu;                 // for SPC match base used only
    unsigned char           varbu[SB_MAX_VAR_SIZE]; // data for dref            // ..JC33
};

struct LOGSBCTSETT          // change settlement date (84)
{
    struct LOGSBCTRNID      id;                     // tournament id
    __time32_t                  sDate;                  // new settlement date
};

struct LOGSBCTMOD           // modify tournament name, aup/sng flag (85)
{
    struct LOGSBCTRNID      id;                     // tournament id
    unsigned char           single1:1;              // single allowed
    unsigned char           aup1:1;                 // all-up allowed
    unsigned char           :6;                     // unused
    unsigned char           names[SB_LEN_TRN_NAME]; // new event name
};

struct LOGSBCTTASS          // change team assignment (86)
{
    struct LOGSBCTRNID      id;                     // tournament id
    unsigned char           numTeambu;              // number of team
    struct SBMSG_TRN_SEL    ent[SB_MAX_LEAGUE_TEAM];
};

struct SBMSG_TRN_STANDBY
{
    unsigned char           posbu;      // pos in team list of this standby
    unsigned char           nselbu;     // new # of selection in the corresponding group
    struct SBMSG_TRN_SEL    sel;
};

struct LOGSBCTSTANDBY       // team standby replacement (96)/ cancel replacement (97)
{
    struct LOGSBCTRNID          id;                     // tournament id
    unsigned char               numTeambu;              // number of team
    struct SBMSG_TRN_STANDBY    sTeam[SB_MAX_LEAGUE_TEAM];
};

struct LOGSBCTTEAM_ENT                                  // JC31..
{
    unsigned char           idxbu;                      // index of team list
    struct SBMSG_TRN_TEAM   info;                       // team information (for RM used only)
};

struct LOGSBCTTEAM          // result (88)
                            // refund team (89)/ cancel refund team (90)
                            // loss team (91)/ cancel loss team (92)
                            // team start sell (99)/ team stop sell (100)
{
    struct LOGSBCTRNID      id;                     // tournament id
    unsigned char           numTeambu;              // number of team
    struct LOGSBCTTEAM_ENT  ent[SB_MAX_LEAGUE_TEAM];// team details
};

struct LOGSBCTPID           // close (87)/ refund (1042)/ cancel refund (1043)
                            // stop pay (1041)/ all-up pass request (1051)
{
    struct LOGSBCTRNID      id;                     // tournament id
};

struct LOGSBCTSEL           // start sell pool (1020)/ stop sell pool (1021)
{
    unsigned short          areawu;                     // area bit mask
    unsigned short          numwu;                      // number of TRN        // JC38
    struct LOGSBCTRNID      id[SB_TRNMENT_MAX_POOL];    // tournament id list   // JC38
};

struct LOGSBCTMAXNL         // change pool max. NL (1030)
{
    struct LOGSBCTRNID      id;                     // tournament id
    LONGLONG                netLossd;               // maximum net loss in cents
};

struct LOGSBCTCOMB_INFO
{
    unsigned char           seqbu;                  // sequence of the odds
    unsigned char           enabu;                  // enable selling flag
                                                    // used for odds only
    unsigned LONGLONG       amtdu;                  // odds value*100/ plimit value in cents
};
//
// variable data buffer for TRN each odds/ plimit
// struct LOGSBCTCOMB_INFO[numbu]
// char    comb[3]
//
struct LOGSBCTCOMB          // odds (1031)/ position limit by comb. (1068)
{
    struct LOGSBCTRNID      id;                     // tournament id
    unsigned char           numbu;                  // # of odds/ plimit involved
    unsigned char           varbu[SB_MAX_VAR_SIZE];
};

struct LOGSBCTCOMB_DATA     // TRN combination data
{
    unsigned char           numTeambu;                  // number of team
    struct SBMSG_TRN_TEAM   team[SB_TRNMENT_MAX_RES];   // team selection info.
                                                        // the team id field is not
                                                        // used for payout record
};

struct LOGSBCTPAY_ENT
{
    unsigned char           cntbu;                  // count back level
    unsigned char           typebu;                 // div. type
    unsigned LONGLONG       divdu;                  // dividend for pari-mutuel pool
    unsigned char           claim1:1;               // div. claim
    unsigned char           :7;                     // unused
    struct LOGSBCTCOMB_DATA comb;
};
struct LOGSBCTPAY           // start pay (1040)
{
    struct LOGSBCTRNID      id;                     // tournament id
    unsigned int            wcmStartlu;             // wcm pointer in WCMCOM
    unsigned int            wcmNewSizelu;           // next use wcm pointer
    unsigned char           numbu;                  // number of winning combination
    struct LOGSBCTPAY_ENT   ent[SB_MAX_CPX_DIV];
};

// ..JC29

struct LOGSBCMMODI      // modify match details (45)
{
    short               mIdxw;                      // new match index
    struct SBMSG_ID     id;                         // match id
    __time32_t              t;                          // match date/ time
//    __time32_t              rptDate;                    // new match business date  // JC34
};

struct LOGSBCPMODI      // modify pool details (30)             // JC12..
{
    short                   idxw;                   // match/ cpx index
    unsigned char           pIdxbu;                 // pool index ( for simple pool use only )
    LONGLONG                netLossd;               // maximum net loss in cents
    struct SBMSG_POOL_ID    pid;                    // pool id
};

struct LOGSBCPLIMIT     // set position limit (68)              // JC15
{
    short                   idxw;                   // match/ cpx index
    unsigned char           pTypebu;                // pool type ( for simple pool use only )
    struct SBMSG_POOL_ID    pid;                    // pool id, max size occupied
    unsigned char           numPlimitbu;            // # of position limit
    struct LOGSBCPLIMIT_ENT ent[SBMSG_ENT_SIZE];    // position limit entry
};                                                              // ..JC12

struct SBCODDS
{
    unsigned char       seqbu;                      // sequence of the odds
    unsigned char       spcSeqbu;                   // special odds sequence
                                                    // for HDC, 0=home win, 1=away win
                                                    // for HHAD, 0=home win, 1=away win, 2=draw
                                                    // for OOU, 0=over, 1=under
    unsigned char       enabu;                      // enable selling flag
    unsigned int        oddslu;                     // odds value *100      // JC13
    char                comb[3];                    // comb info            // JC25
                                                    // these 3 bytes comb information is
                                                    // reserved only, in future, it will
                                                    // be used as CRS dynamic combination
};

struct SBCODDOPT
{
    char                goalb[2];                   // [0] = HDC goal * 10 or OOU score
                                                    //       or HHAD goal
                                                    // [1] = split HDC goal * 10 (=[0] for normal)
};

struct LOGSBCODDS       // odds (31)
{
    short                   idxw;                   // match idx/ champ idx/ cpx pool idx
    struct SBMSG_POOL_ID    pid;                    // pool id ( max. size of pool id is occupied )
    struct SBCODDOPT        oddOpt;                 // extra odds info for HDC/OOU/HHAD
                                                    // (not used for other pools)
    unsigned char           numbu;                  // # of odds involved
    struct SBCODDS          odds[SB_ODDS_GEN_MAX];    
};

struct LOGSBCRFDT        // define refund time: for match (32)/ for champ (33)
{
    short               idxw;                       // match idx/ champ idx
    struct SBMSG_ID     id;                         // match id/ champ id
    struct SBMSG_DATE   date;
    struct SBMSG_TIME   time;
};

struct LOGSBCPSEL       // start sell pool (20), stop sell pool (21)
{
    unsigned short          areawu;                 // area bit mask
//    short                   idxw;                   // match idx/ cpx pool idx
    unsigned short          numwu;                  // # of pool                // JC38
//    struct SBMSG_POOL_ID    pid[SB_MAX_POOL_MATCH]; // pool id
    unsigned char           bu[SB_MAX_VAR_SIZE];    // match idx/ cpx pool idx +
                                                    // SBMSG_POOL_ID list       // JC38
};

struct LOGSBCMSEL_ENT                               // JC38
{
    short                   idxw;                   // match index
    struct SBMSG_ID         id;                     // match id, match # (all=0), day (all=0)
};

struct LOGSBCMSEL       // start sell match (34), stop sell match (35)
{
    unsigned short          areawu;                 // area bit mask
//    short                   idxw;                   // match index
    unsigned short          numwu;                  // # of match               // JC38
//    struct SBMSG_ID         id[SB_MAX_MATCH];       // match id, match # (all=0), day (all=0)
    struct LOGSBCMSEL_ENT   ent[SB_MAX_MATCH];      // match index + match id   // JC38
};

struct SBCGOAL                                      // JC01
{
    short               homew;                      // home team score ( <0 = void )
    short               awayw;                      // away team score
};

struct SBCMRES
{
    struct SBCGOAL      goal[2];                    // result of 1st half and full time
};

struct SBCCRES
{
    unsigned char       numbu;                      // # of team involved
    unsigned short      teamwu[SB_MAX_LEAGUE_TEAM]; // team ids
};

union SBCRES
{
    struct SBCMRES      mres;
    struct SBCCRES      cres;
};

struct LOGSBCRESU       // match result (38)/ champ result (39)
{
    short               idxw;                       // match index/ champ index
    struct SBMSG_ID     id;                         // match id/ champ id
    union SBCRES        res;                            
};

struct LOGSBCWCM
{
    unsigned char       nLegbu;                 // number of leg
    char                comb[LOGSBC_WCM_COMB_SIZE];               // JC29
    unsigned char       cntbu;                  // count back level
    unsigned char       typebu;                 // div. type
    unsigned char       numLegbu;               // # of leg to be matched for div.  // JC37
    unsigned LONGLONG   divdu;                  // dividend for pari-mutuel pool
    unsigned char       claim1:1;               // div. claim
    unsigned char       :7;                     // unused
};

struct LOGSBCPAY        // start pay (40)
{
    short                   idxw;                   // match idx/ champ idx/ cpx idx
    struct SBMSG_POOL_ID    pid;                    // pool id ( max. size of pool id is occupied )
    unsigned int            wcmStartlu;             // start of winning combination
    unsigned int            wcmSizelu;              // new size of winning combination
    unsigned char           numbu;                  // number of winning combination
    struct LOGSBCWCM        wcm[SB_MAX_CPX_DIV];    // winning combination
};

struct LOGSBCPSTS        // pool close (37), stop pay (41), refund (42), cancel refund (43)
{
    short                   idxw;                   // match idx/ champ idx/ cpx pool idx
    struct SBMSG_POOL_ID    pid;                    // pool id    
};

struct SBCACHK
{
    LONGLONG            netLossd;                   // bet loss in cents, <0= no limit
    LONGLONG            oddMaxd;                    // max long odds * 100, <0 = no limit
};

struct LOGSBCASET       // nominate all-up set (48)/ nominate all-up set enquiry (65)
{
    short               idxw;                       // index of the set
    __time32_t              date;                       // date of the earliest match
    unsigned int        newColSizelu;               // new collation size
    unsigned int        colStartlu;                 // collation start
    unsigned int        colSizelu;                  // collation size
    unsigned char       numLevbu;                   // # of event information
    unsigned char       colLevelbu;                 // collated level           // JC21
    unsigned char       numPolbu;                   // # of pool invloved
    unsigned char       bu[SB_MAX_VAR_SIZE];
                                // variable struct SBCACHK * numLevbu +
                                // (actual size used for each SBMSG_POOL_ID) * numPolbu
};

struct LOGSBCASMODI       // modify all-up set (52)
{
    short               idxw;                       // index of the set
    __time32_t              date;                       // date of the earliest match
    unsigned char       numLevbu;                   // # of event invloved
    struct SBCACHK      lev[SB_MAX_AUP_EVENT];
};

struct LOGSBCPEAK       // peak hour time and min bet (55)
{
    unsigned char       enabu;                      // peak hour min. bet enabling // JC02
    unsigned char       areabu;                     // area id                     // JC02
    unsigned LONGLONG   amtdu;                      // min. amount in cents // JC06
};

struct SBCUBET
{
    unsigned char       poolbu;
    unsigned short      amtwu[SB_MAX_PCAT];         // amount in $
};

struct LOGSBCUBET       // unit investment - pool (56)
{
    unsigned char       numbu;
    struct SBCUBET      ubet[SB_MAX_POOL];
};

struct LOGSBCCLS        // match close (36)                 // JC38
{
    short                       idxw;                       // match idx
    struct SBMSG_ID             id;                         // match id
    unsigned char               numbu;                      // # of pools to be close
    struct SBMSG_MATCH_CLS_POOL pool[SB_MAX_POOL_MATCH];    // simple pools only
};

struct LOGSBCABN        // abandond match (69)              // JC38
{
    short               idxw;                       // match idx
    struct SBMSG_ID     id;                         // match id
};

struct LOGSBCAPSS       // all-up pass request (51)
{
    struct SBMSG_ID     id;                         // match id
};

struct LOGSBCPAYALL     // pay all FO pools in a match (58)
{
    short               mIdxw;                      // match idx
    struct SBMSG_ID     id;                         // match id
    unsigned char       paybu[SB_MAX_POOL_MATCH];   // 1=pay, 0=do nothing
};

struct LOGSBCSPPALL     // stop pay all pools in a match (59)
{
    short               mIdxw;                      // match idx
    struct SBMSG_ID     id;                         // match id
    unsigned char       sppbu[SB_MAX_POOL_MATCH][SB_MAX_PCAT];
                                                    // 1=stop pay, 0=do nothing
};

struct LOGSBCACCEPT_ENT                             // JC15..
{
    unsigned char           pTypebu;        // pool type
    unsigned char           areabu;         // area id
    unsigned int            amtlu;          // unit bet amount in $     
};

struct LOGSBCACCEPT     // unit bet for always accept (66)
{
    unsigned char           numbu;          // number of entry
    struct LOGSBCACCEPT_ENT ent[SBMSG_ENT_SIZE];
};

struct LOGSBCITRCP_ENT
{
    unsigned char           pTypebu;        // pool type
    unsigned char           areabu;         // area id
    unsigned int            amtlu;          // unit bet amount in $     
};

struct LOGSBCITRCP      // unit bet for trigger intercept (67)
{
    unsigned char           numbu;          // number of entry
    struct LOGSBCITRCP_ENT  ent[SBMSG_ENT_SIZE];
};

struct LOGSBCACCEPTENA_ENT
{
    unsigned char               pTypebu;        // pool type
    unsigned char               areabu;         // area id
    unsigned char               enabu;          // enabling
};

struct LOGSBCACCEPTENA          // always accept checking enabling (75)
{
    unsigned char               numbu;          // number of entry
    struct LOGSBCACCEPTENA_ENT  ent[SBMSG_ENT_SIZE];
};

//struct LOGSBCITRCPENA_ENT
//{
//    unsigned char               areabu;         // area id
//    unsigned char               enabu;          // enabling
//};
//
//struct LOGSBCITRCPENA           // intercept checking enabling (76)
//{
//   unsigned char               numbu;          // number of entry
//    struct LOGSBCITRCPENA_ENT   ent[SBMSG_ENT_SIZE];
//};                                                  // ..JC15
struct LOGSBCBF         // match pool bad sale expired (2101)
                        // match pool collation final (2102)
{
    short                   idxw;                   // match idx    // JC39
    unsigned char           numbu;
    struct SBMSG_BFPOOL     bfPool[SBC_MAX_BSE];    // pool list
};

struct LOGSBCCPXBF      // CPX bad sale expired (2107)
                        // CPX collation final (2108)
{
    short                   idxw;                   // cpx idx
//    struct SBMSG_POOL_ID    pid;                    // pool id
};

//struct SBCFIN
//{
//    short               idxw;           // match/ champ/ cpx idx
//    struct SBMSG_ID     id;             // match/ champ id (no use for cpx)
//};
//
//struct LOGSBCFIN        // final collation (102)
//{
//    unsigned char       idxTypebu;
//    unsigned char       numbu;          // number of match/champ/cpx idx involved
//                                        // in this stage, fixed to 1
//    struct SBCFIN       fin[SB_MAX_MATCH];
//};

struct LOGSBCMRPT           // report request (103)             // JC29..
{
    short                   idxw;       // if idxw == SB_MAX_MATCH_DAY+1,
                                        // report repuest for 'ALL' matches
                                        // in a day, in that case, the match #
                                        // in the following match id will be
                                        // set to SB_MAX_MATCH_DAY+1 also
    struct SBMSG_ID         id;         // match/ champ id
    unsigned char           idbu;       // report id
    BOOL                    detailt;    // detail lia. report is required
    struct SBMSG_POOL_ID    pid;        // pool id - for ewp use only
};

struct LOGSBCTRPT           // report request (1103)
{
    struct LOGSBCTRNID      id;                     // tournament id
    unsigned char           idbu;                   // report id
};

union LOGSBCRPT_TYPE
{
    struct LOGSBCMRPT       mrpt;
    struct LOGSBCTRPT       trpt;
};

struct LOGSBCRPT
{
    unsigned char           typebu;
    union LOGSBCRPT_TYPE    rpt_type;
};                                                              // ..JC29

struct LOGNXTBDATE      // next business date               // JC14..
{
    __time32_t              date;
};                                                          // ..JC14

struct LOGSBCPLAYER_ID                      // JC15..
{
    unsigned char               selbu;      // selection #
    unsigned short              idwu;       // player id
};

struct LOGSBCPLAYER             // modify player info (71)
{
    short                       idxw;       // match index
    struct SBMSG_ID             id;         // match id
    unsigned char               numbu;      // number of player info
    struct LOGSBCPLAYER_ID      playerId[SB_MAX_MATCH_PLAYER];
};                                          // ..JC15

struct LOGSBCPOOLCOMB           // pool result (72)
                                // refund a selection (73)/ cancel refund a selection (74)
{
    short                       idxw;       // cpx pool index
    struct SBMSG_POOL_ID        pid;        // pool id ( max. size of pool id is occupied )
    unsigned char               numbu;      // number of winning combination
    unsigned char               bu[SB_MAX_VAR_SIZE];    // odds combination, variable size
};

//struct LOGSBCMBT_ENT                            // JC19
//{
//    unsigned char               areabu;         // area id (max BST_AREA_MAX)
//    unsigned char               pcatbu;         // FO/PM
//    unsigned char               pTypebu;        // pool type, filler for aup    // JC33
//    unsigned char               tTypebu;        // terminal type                // JC33
//                                                // either LOGSBC_TERM_TYPE_SVT or
//                                                // LOGSBC_TERM_TYPE_OPT
//    unsigned LONGLONG           amtdu;
//};

struct LOGSBCMBT                                // JC19
{
    unsigned char               numbu;          // number of entry
//    struct LOGSBCMBT_ENT        ent[SBMSG_ENT_SIZE];                // JC33
    struct SBMSG_MINBET_POOLTERM_ENT    ent[SBMSG_ENT_SIZE];
};

struct LOGSBCAUPCOMB                            // JC22
{
    unsigned short              maxwu;          // new max. entry
    unsigned short              seqwu;          // sequence # in the list
    struct SB_AUP_STOPSELL      info;           // stop sell selection info
};

struct LOGSBCBETADJ                             // JC24
{
    BOOL                        addt;           // TRUE=add inv., FALSE=minus inv.
    unsigned LONGLONG           amtdu;          // adj. amount
    unsigned char               levbu;          // # of level, 1=simple bet, >1=aup bet
                                                // >3= no real adj is done, record only
    struct BETDATA              bet;            // the betline
};

// variable data buffer for selection description
// number of entry (unsigned char)
// [
//   selection id (unsigned char)
//   description string len (unsigned char)
//   description string (variable size)
// ]
struct LOGSBCSELDESC                            // selection description (106)      // JC33
{
    struct LOGSBCTRNID          id;
    unsigned char               varbu[SB_MAX_VAR_SIZE];
};

struct LOGSBCPOOLTYPE                       // JC38..
{
    unsigned char           aup1:1;         // all-up allowed [y/n]
    unsigned char           single1:1;      // single allowed [y/n]
    unsigned char           hftbet1:1;      // half time betting pool allowed [y/n]
    unsigned char           :5;             // unused
    short                   idxw;           // match idx/ complex pool index
    struct SBMSG_POOL_ID    pid;            // pool id
};

//struct LOGSBCINTRENA
//{
//    unsigned char               numbu;          // number of entry
//    struct SBMSG_INTR_ENA_ENT   account[SB_MAX_AC_TYPE];
//};

struct LOGSBCMAXENA             // JC39
{
    unsigned char               numbu;          // number of entry
    struct SBMSG_MAXENA_ENT ent[SBMSG_ENT_SIZE];
};

struct LOGSBCSECT               // JC38
{
    short                       idxw;           // set number
    __time32_t                      cDate;          // creation date
    unsigned int                colStartlu;     // collation start
    unsigned int                colSizelu;      // collation size
    unsigned int                newColSizelu;   // new collation size
    unsigned short              enawu;          // n bit set => n level enabled
    unsigned short              bonwu[2];       // bonus % * 100,
                                                // [0]=>1 selection in each section
                                                // [1]=>2 selection in each section
    unsigned char               nsctbu;         // # of section
    struct SB_SCTB_SECTION      sct[SB_MAX_SCTB_SECTION];
                                                // section details
};

//struct LOGSBCMAXENA_AB              // JC39
//{
//    unsigned char               numbu;      // number of account type involved in the message
//    struct SBMSG_MAXENA_AB_ENT  ent[SB_MAX_AC_TYPE];
//};

union   LOGSBCD                         // log data
{
    unsigned LONGLONG       amtdu;      // h.o. pay limit (4)
    unsigned short          wu;         // odds grace interval in sec. (6),
                                        // bad sale interval in sec. (7)
                                        // refund deduction % * 100 (8)
                                        // match/ champ close warning interval in min.(10)
                                        // retention period in days (23)
                                        // max outstanding intercept (77)
                                        // HDC draw deduction (82)
                                        // RM intercept timer in second (141)
    unsigned char           bu;         // net loss authorisation enabling (11)
                                        // all-up checking enabling (44)
                                        // max. payout per FO bet checking enabling (60)
                                        // pool max. net loss checking enabling (61)
                                        // max. long odds checking enabling (62)
                                        // max investment checking enabling - CB (127)
    unsigned short          aubetwu[SB_MAX_PCAT];       // unit investment - aup (57)
    struct LOGSBCPROFITMAX  profitMax;  // daily max profit per account (1)
    struct LOGSBCAPAR       apar;       // fix odds account type parameter (2)
    struct LOGSBCMAXI       maxi;       // (3), (12), (13)
                                        // (120), (121), (122), (123), (124), (125) 
    struct LOGSBCMIAU       miau;       // max. investment authorisation (9)
    struct LOGSBCBON        bon;        // bonus %:  by pool (14), by all-up level (15)
                                        // by all-up level for cross pool (93)
    struct LOGSBCIMXN       imxn;       // (16), (17), (18), (19), (128), (129), (130),
                                        // (131), (132), (133), (134), (135), (136)
//    struct LOGSBCAINVL      aupInvl;    // max all-up investment per bet (17)
//                                        // min all-up investment per bet (19)
//                                        // max cross pool all-up inv. per bet (128)     // JC38
//                                        // min cross pool all-up inv. per bet (135)     // JC38
    struct LOGSBCAUFM       aufm;       // all-up formula (22)
    struct LOGSBCNAME       name;       // team name (24), league name (25), player name (26),
                                        // trn name (94), trn codes (95)
    struct LOGSBCMINP       minp;       // define new match (27), define enquiry (63)
    struct LOGSBCPINP       pinp;       // define new pool (107)
    struct LOGSBCMMODI      mmodi;      // modify match details (45)
    struct LOGSBCPMODI      pmodi;      // modify pool details (30)
    struct LOGSBCODDS       odds;       // odds (31)
    struct LOGSBCRFDT       rfdt;       // define refund time for match (32)
    struct LOGSBCPSEL       psell;      // start sell pool (20), stop sell pool (21)
    struct LOGSBCMSEL       msell;      // start sell match (34), stop sell match (35)
    struct LOGSBCCLS        cls;        // match close (36)
    struct LOGSBCABN        abn;        // abandond match (69)
    struct LOGSBCRESU       resu;       // match result (38)
    struct LOGSBCPAY        pay;        // start pay (40) 
    struct LOGSBCPSTS       psts;       // cpx close (37)/stop pay (41)
                                        // refund (42)/cancel refund (43)
    struct LOGSBCASET       aset;       // nominate all-up set (48), define enquiry (65)
    struct LOGSBCAPSS       apss;       // all-up pass request (51)
    struct LOGSBCASMODI     maset;      // modify all-up set (52)
    struct LOGSBCPEAK       peak;       // peak hour time and min bet (55)
    struct LOGSBCUBET       pubet;      // unit investment - pool (56)
    struct LOGSBCPAYALL     payall;     // pay all FO pools in a match (58)
    struct LOGSBCSPPALL     sppall;     // stop pay all pools in a match (59)
    struct LOGSBCACCEPT     uinvAcpt;   // unit bet for always accept (66)
    struct LOGSBCITRCP      uinvItrcp;  // unit bet for trigger intercept (67)
    struct LOGSBCACCEPTENA  acceptEna;  // always accept checking enabling (75)
//    struct LOGSBCITRCPENA   itrcpEna;   // intercept checking enabling (76)
//    struct LOGSBCMAXENA_AB  maxEnaAB;   // (126)/(144)
//    struct LOGSBCINTRENA    intrEna;    // Enable/disable intercept (140)
    struct LOGSBCMAXENA     maxEna;     // intercept checking enabling (76)
                                        // max. FO payout per bet - AB (126)
                                        // intercept enabling (140)
                                        // max. inv. per bet enabling - AB (144)
    struct LOGSBCPLIMIT     plimit;     // set position limit (68)
    struct LOGSBCPLAYER     playerInfo; // modify player info (71)
    struct LOGSBCPOOLCOMB   poolComb;   // pool result (72)
                                        // refund a selection (73),
                                        // cancel refund a selection (74)
    struct LOGSBCBF         poolBF;     // match pool bad sale expired (2101)
                                        // match pool final collation (2102)
    struct LOGSBCCPXBF      cpxBF;      // cpx bad sale expired (2107)
                                        // cpx final collation (2108)
//    struct LOGSBCFIN        fcol;       // match pool final collation (2102)
//    struct LOGSBCCPXFIN     cpxFcol;    // cpx final collation (2108)
    struct LOGSBCRPT        rpt;        // report request (103)/ TRN report request (1103)
    struct LOGNXTBDATE      nxtBDate;   // next business date
    struct LOGSBCMBT        mbt;        // min bet value by terminal by pool type (110)
                                        // min bet value by terminal aup (111)
                                        // (137), (138), (139)
    struct LOGSBCAUPCOMB    stsAUPComb; // stop sell (79)/can stop sell aup comb (80)
    struct LOGSBCBETADJ     betAdj;     // adjustment by a betline (81)
    struct LOGSBCTINP       tinp;       // define new TRN pool (108)/ SPC pool (109)
    struct LOGSBCTSETT      tsett;      // change settlement date (84)
    struct LOGSBCTMOD       tmod;       // modify tournament event name, aup/sng flag (85)
    struct LOGSBCTTASS      ttass;      // change team assignment (86)
    struct LOGSBCTTEAM      tteam;      // result (88)/
                                        // team refund (89)/ team canrfd (90)
                                        // team loss (91)/ team canloss (92)
                                        // team start sell (99)/ team stop sell (100)
    struct LOGSBCTSTANDBY   tstandby;   // team standby (96)/ cancel team standby (97)
    struct LOGSBCTPID       tpid;       // close (87)/ refund (1042)/ canrfd (1043)
                                        // stop pay (1041)/ all-up pass request (1051)
                                        // bad sale expired (1101)/ collation final (1102)
    struct LOGSBCTSEL       tsel;       // start sell pool (1020)/ stop sell pool (1021)
    struct LOGSBCTMAXNL     tmaxnl;     // change pool max. NL (1030)
    struct LOGSBCTCOMB      tcomb;      // odds (1031)/ position limit (1068)
    struct LOGSBCTPAY       tpay;       // start pay (1040)
    struct LOGSBCSELDESC    selDesc;    // selection description (106)
    struct LOGSBCPOOLTYPE   poolType;   // mod. pool bet type enabling (142)
    struct LOGSBCSECT       sectSet;    // define section bet set (143)
};

struct LOGSBCH
{
    unsigned short      codewu;         // sbc function code
};

struct LOGSBC          // log message
{
    struct LOGSBCH      h;              // header
    union LOGSBCD       d;              // data
};

#pragma pack()

#endif
