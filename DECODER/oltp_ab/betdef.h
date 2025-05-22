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
//    Author :  Edward Hon                01-NOV-2000
//
//    Mod    :  PN01         24-JAN-2002
//              ( Delta phase 2: add a bit in sb record header to indicator
//                system odds is used for the sold bet. )
//              DD02        20-FEB-2002
//              (add 8 bits to bet status for future expansion)
//              FT03        21-FEB-2002
//              (add bonus overflow bit)
//              RL04        06-SEP-2002
//              (add shrink bet bit to bet status)
//              FT05        26-SEP-2002
//              (change of odds constraint from 0.05 to 0.01)
//              eh06        08-aug-2002
//              (implement esc sb)
//              PN07        19-DEC-2002
//              (split other selection in CRS into 3 combination)
//              VC08        6-MAR-2003
//              (add AB Bet record defines)
//              LY09        16-APR-2003
//              (new way of storage of odds)
//              VC10        23-APR-2003
//              (modify AB Bet record defines)
//              PN11        24-APR-2003
//              (support configurable pool, half time/full time cos,
//               add selection number in bet record for first goalscorer)
//              LY12        12-AUG-2003
//              (add bet selection indicator to SB PM bet selections)
//              LY13        20-AUG-2003
//              (new pool HHAD)
//              PN14        20-OCT-2003
//              ( . support SB exotic bet - HAFU
//                . use sign bit of selection count to store field indicator
//                  for fixed odds bet
//                . add new data structure to support mixed bet type in 
//                  single bet )
//              PN15        24-DEC-2003
//              . support championship related pool in stage 3
//              . remove data structure BETSB_SEL_FO_CFG since it is same
//                as BETSB_SEL_FO
//              PN16        9-JAN-2004
//              . a new bit is added to fix bug in calculation of parimutuel 
//                pool selection size.  With this bit clear, old function
//                is invoked to calculate the size of selection.
//              PN17        4-MAR-2004
//              . support stage 3a product: special pool, group winner,
//                top scorer, 8 hafu, and commingled pool
//              LY18        9-MAR-2004
//              . remove old configuarable pool structure
//              PN19        16-JUN-2004
//              . add addon bit in lottery such that AB can use it to
//                deterimine a small record size for lottery when
//                variable size is used
//              PN20        13-AUG-2004 (Q501-FB)
//              - change of CRS selection storage to support additional
//                score selection in pari-mutuel pool
//              - support section bet
#ifndef BETDEF_H
#define BETDEF_H

// info from BETxx, MARK6x, PWBx, DEPx, SBFx

#include <time.h>
#include "udtypedef.h"

#define SB_MAX_BET_BUF   512
#define SB_MAX_TRN_BUF   160    // max. size of group selections for PN15..
                                // tournament pool ( assume 16 groups * 
                                // 10 btyes) 
#define SB_MAX_TRN_SEL   9      // max. size of selection in group
                                // (assume max 64 selection) ..PN15

#pragma pack(1)

//
// Following defines are size declaration used in bet file.  If changes is
// made, file conversion on bet file is required.
//
#define BET_AUP_MAXEVT   6          // max. event of allup
#define BET_BNKM_MAXLEG  3          // maximum leg for banker bit map
#define BET_MLP_MAXLEG   6          // maximum leg for multi leg pool
#define BET_RAC_MAXSMAP  2          // maximum long word count for racing 
                                    // selection bit map; if banker bet is
                                    // selected, first long word stores
                                    // banker selection while second long word
                                    // stores other selections.
#define BET_LOT_MAXSMAP  7          // maximum byte count for lottery selection 
                                    // in bit map storage
#define BET_LOT_MAXENTRY 10          // maximum # of lottery entry in a bet  Q310 change from 4- 10
#define BET_LOT_MAXSEL   6          // maximum byte count for lottery selection
                                    // in binary value
#define BET_LOT_MAXAONS  3          // maximum byte count for add-on selection
                                    // in binary value
// PN07
#define BETSB_MAX_SEL   64          // max. # of selections per bet (field 
                                    // selection of championship)   PN15
//
// Home goal and away goal is stored for cos selection.  If 0xFF is stored
// in home goal, away goal stores selection of result which will be 0, 1, 2
// where 0 => home win, 1 => away win, 2 => draw.  For backward compatibility,
// if 0xFF is stores in away goal field, it implies that result is not 
// significant.
// ..PN07
#define BETSB_COS_OTHERSCR  0xFF    // other scores selection for COS bet record
#define BETSB_SEL_HOME  0           // home team selection
#define BETSB_SEL_AWAY  1           // away team selection
#define BETSB_SEL_DRAW  2           // draw selection

#define BETSB_MAX_ENT   5           // maximum entry for SB bet  PN14

// PN20.. defines for correct score related pool
#define BETSB_CRS_MAX   5           // max score of a team
// # of byte for CRS bit map selection =
// round up to byte (# of correct score selection + others selection + 
//  field bit indicator)
//#define BETSB_CRS_SELBC NUNIT((BETSB_CRS_MAX+1)*(BETSB_CRS_MAX+1)+3+1, 8)

#define BETSB_CRS_SELBC	5
// ..PN20

// PN11..
// Field indicator for selection with 32 bits.  Currently, this is used by
// HCS of SB bet only.
#define BET_SEL_FLD     0x80000000  // field bit - leftmost bit ..PN11

struct BETSTS           // bet status
{
  unsigned short          cancel1:1;      // cancel
  unsigned short          paidpart1:1;    // paid - partial
  unsigned short          paidfinal1:1;   // paid - final
  unsigned short          divcal1:1;      // divcal - dividend is finalised
                                        // In sb system, this bit will
                                        // be set when all matches of 
                                        // involved can be concluded during
                                        // eod.  Cancelled "SB" bet is also set
                                        // with this bit too such that latest
                                        // match date in the bet can be updated
                                        // as reference in the period of bet
                                        // retention in system.
  unsigned short          claim1:1;       // error claimed
  unsigned short          released1:1;    // released to be paid at centre payCentrelu
  unsigned short          overflow1:1;    // overflow
  unsigned short          hop1:1;         // h.o. payment
  unsigned short          bonusovfl1:1;   // bonus overflow       FT03
  unsigned short          shrink1:1;      // bet shrunk to shrink bet file  RL04
                                        // For soccer betting system, this bit 
                                        // set implies that bet must be kept in
                                        // system until payout expires.  This
                                        // bet may exist in daily bet file or
                                        // shrink bet file.
  unsigned short          nsize1:1;       // new size for SB simple pool record
                                        // in order to fix wrong calculation
                                        // of selection size in parimutual
                                        // (for newly issued SB bet, this
                                        // bit will always be set)  PN16
  unsigned short          fieldsizef1 :1;  // Using 34 field size flag AUG2020, replace extot1
  unsigned short		  forfeitfl:1;  // Q405 Forfeit flag - If this flag is set before dividend 
  unsigned short          lscovfl1:1;     // losing inv. consolation overflow
  unsigned short          :2;             // for future expansion DD02 FT03 RL04
};

union BET_PTR_PAY_CB        // shared variable to be used in OLTP-CB
{
  unsigned int          lscnlu;         // consolation of losing investment in
                                        // cents, only available when final
                                        // paid or div cal bit is set.  
  unsigned int          fwdreclu;       // bet record # of child ticket for
                                        // partial pay ticket
};
struct BET_PTR_PAY                      // partial pay pointer
{
  unsigned int          fwdreclu;       // bet record # of child ticket
  unsigned int          bckreclu;       // bet record # of parent ticket
};
struct BET_PTR_CV                       // CV pointer
{
  LONGLONG          selllogseqlu;   // log seq at selling
  LONGLONG          paylogseqlu;    // log seq at payout
};
union BET_PTR
{
  struct BET_PTR_PAY    pay;
  struct BET_PTR_CV     cv;
};
struct  BETCBHDR                        // CB header
{
  unsigned int          sellCentrelu;   // selling centre
  unsigned short        sellWindowu;    // selling window
  unsigned LONGLONG     prvPaydu;       // previous payout in cents
  unsigned int          payCentrelu;    // payout centre
  __time32_t                payTime;        // payout time
  char                  paySysb;        // paying system
  unsigned char         genbu;          // ticket generation number
  union BET_PTR         ptr;            // pointer
};
struct BETSBCBHDR
{
  struct BETCBHDR       hdr;
  unsigned short        fdwbfcwu;       // entry # to BFC entry of child ticket
  unsigned short        bckbfcwu;       // entry # to BFC entry of parent ticket
};
struct BETSBACLOCCB     // cb selling location
{
  unsigned int          centrelu;       // center #
  unsigned short        windowu;        // window #
};
struct BETSBACLOCDIR    // direct input location
{
  unsigned int          citlu;          // cit #
  unsigned char         typebu;         // input type/cit type
};
struct BETSBACLOCVOICE  // voice selling location
{
  char                  floorb;         // ascii floor
  char                  benchb;         // ascii bench
  unsigned char         termbu;         // terminal #
};
union BETSBACLOC       // ab selling location
{
  struct BETSBACLOCCB    cb;
  struct BETSBACLOCVOICE voice;
  struct BETSBACLOCDIR   dir;
};
struct BETSBACHDR       // account betting header used in sb bet file
{
  unsigned int          acclu;          // account #
  unsigned int          translu;        // transaction #
  __time32_t                payTime;        // payout date
  LONGLONG              cardd;          // card #
  char                  area;           // selling area [refer to bstypedef.h]
  union BETSBACLOC      loc;            // selling location
};

struct BETFLEXICOMBO
{
	unsigned int	baseinv:31;	// flexibet=0; BASE investment in dollar; flexibet = 1; noofcombination
	unsigned int	flexibet:1;	// flexi bet	
};

union BETINVESTCOMBO
{
	//unsigned int	baseinv:31;	// flexibet=0; BASE investment in dollar; flexibet = 1; noofcombination
	//unsigned int	flexibet:1;	// flexi bet	
	struct BETFLEXICOMBO flexi;

	unsigned int    binvlu;         // base investment in dollar. added by in sp3. 2016.10.20
};

struct  BETHDR                          // common header
{
  unsigned LONGLONG     totdu;          // total payout in cents
  union BETINVESTCOMBO	betinvcomb;		// Q308 changes
  unsigned int     costlu;         // total cost in cents
  __time32_t                sellTime;       // sell time
  unsigned int			businessDate;		// business date
  unsigned char         bettypebu;      // bet type
  struct BETSTS         sts;
};
// Q308 changes
// if flexibet = 0; baseinv = base investment in dollar
// if flexibet = 1; baseinv = number of combinations 

struct  BETIND          // indicator
{
  unsigned char  bnk1:1; // banker
  unsigned char  fld1:1; // field
  unsigned char  mul1:1; // multiple
  unsigned char  mbk1:1; // multiple banker
  unsigned char  rand1:1;// randomly generated
  unsigned char  :2;
  unsigned char  twoentry:1;// randomly generated
  
};
struct  BETAUPSEL       // extended allup info per event
{
  unsigned char         racebu;         // race #
  unsigned char         bettypebu;      // non-allup bet type
  struct BETIND         ind;            // indicator
  unsigned __int64		pid[BET_RAC_MAXSMAP];	// pool id
  unsigned char			fdsz;					// field size
  unsigned __int64      sellu[BET_RAC_MAXSMAP]; // selection bitmap
  unsigned short        comwu;          // # of combinations
  unsigned int          pftrlu;         // pay factor
};
struct  BETAUP          // allup selections
{
  unsigned char			loc;			// location
  unsigned char			day;			// Day
  __time32_t			md;				// meeting day
  unsigned char         evtbu;          // # of events
  unsigned char         fmlbu;          // formula
  struct BETAUPSEL      sel[BET_AUP_MAXEVT];    // selections
};
union BETEXBNK
{
  unsigned __int64      sellu[BET_MLP_MAXLEG];  // selection bitmap
  unsigned char         bnkbu[BET_BNKM_MAXLEG]; // # of bankers per leg [max. 3 legs]
};

struct  BETEXOSTD       // exotic or standard info
{
	unsigned char			loc;			// location
	unsigned char			day;			// day
	__time32_t				md;			    // meeting date
	unsigned char			racebu;         // race #
	struct BETIND			ind;            // indicator
	unsigned __int64		pid[BET_RAC_MAXSMAP];	// pool id
	unsigned char			fdsz[BET_MLP_MAXLEG];	// field size
	unsigned __int64        sellu[BET_MLP_MAXLEG];  // selection bitmap
	union BETEXBNK			betexbnk;
};

struct  BETLOTS         // single lottery info
{
  unsigned char         nbnkbu;         // # of bankers
  unsigned char         nothbu;         // # of other selections [0=non-banker]
  unsigned char         bnkmbu[BET_LOT_MAXSMAP];    // banker bitmap
                                                    // or odd-even selection
  unsigned char         othmbu[BET_LOT_MAXSMAP];    // other selections bitmap
  unsigned char         npwbbu;         // # of powerball selections
  unsigned char         pbasbu;         // powerball base
  unsigned char         pcmbu[BET_LOT_MAXSMAP];       
                                        // powerball selections bitmap
                                        // or concurrent game bitmap
};
struct  BETLOTM         // multiple entry
{
  unsigned char         entbu;          // # of entries
  unsigned char         selbu[BET_LOT_MAXENTRY][BET_LOT_MAXSEL];    
                                        // binary selection
};
union   BETLOTN         // lottery info minus add-on
{
  struct BETLOTM        multi;
  struct BETLOTS        single;
};
struct  BETLOTFIX       // single draw lottery info
{
  unsigned char         multi1:1;       // multi-entry
  unsigned char         rand1:1;        // randomly generated
  unsigned char         field1:1;       // field bet
  unsigned char         addon1:1;       // add-on selection is available PN19
  unsigned char         spc1:1;         // special draw                  PN26
  unsigned char         pub1:1;         // Partial Unit Bet
  //unsigned char         :2;
  unsigned char         gamebu;         // game type
  LONGLONG				poolidd;		// SP3 pool id
  char					fieldsizeb;		// field size
  union BETLOTN         sel;            // normal selections
};

struct  BETLOTMD        // multi-draw lottery extra info
{                       // in normal bet file only
  unsigned LONGLONG     odivdu;         // online dividend in cents
  unsigned char         drrfdbu;        // number of draw refunded 
  unsigned char         drselbu;        // # of draws selected
  unsigned char         drrembu;        // # of draws remaining
  unsigned char         drdivbu;        // # of draws online divcal'd
};

struct BETAON
{
  unsigned char         aselbu[BET_LOT_MAXAONS];    // add-on selections
  unsigned short        abaswu;         // add-on investment in $
};                                       // =0 no add-on

struct BETLOTVAR		//  new change in Q310 , lottery etra information
{
	struct BETAON		aon;			// add on information
	struct BETLOTMD		md;				// mult-draw infomation
};

struct  BETLOT          // lottery info  // change in Q310
{
  unsigned short yearwu;
  unsigned short drawwu;
  unsigned short typewu;
  struct BETLOTFIX      n;      // single draw info -- variable size
  struct BETLOTVAR      var;     // add-on game info and optional multi-draw info
};
struct  BETDEP          // cv info
{
  unsigned char         methodbu;       
    #define BETDEP_ISSMTD_AUTO  0       // auto issue
    #define BETDEP_ISSMTD_KEY   1       // keypad issue
    #define BETDEP_ISSMTD_EFT   2       // eft issue
};

// LY09..
struct BETSB_ODDS       // internal format of SB odds
{
    unsigned short value14:14;
    unsigned short chkdigit2:2;
};

struct BETSB_SEL_FO_3           // HFT/CRS/GPF                  PN17
{
  struct BETSB_ODDS     odds;   // odds
  unsigned char         selbu[2];       // selection
};
struct BETSB_SEL_FO_2           // OOE/TTG/HAD/CHP/GPW/SPC/TPS     
{
  struct BETSB_ODDS     odds;   // odds
  unsigned char         selbu;  // selection
};


// multiple line HILO
struct BETSB_SEL_FO_2G           
{
	unsigned char       line1;       //  handicap goal[2]
	unsigned char       line2;       //  handicap goal[2]
	//unsigned char		goalbu[2]; 
	unsigned char		lineslot:3;            // lineslot
	//unsigned int		:5;						//reseverved
	struct BETSB_ODDS     odds;   // odds
  unsigned char         selbu;  // selection
};


// multiple line CHLO
struct BETSB_SEL_FO_2C          
{
	/*
	unsigned int		line1:10 ;        // bit 0 to 9 corner line1
	unsigned int		line2:10;         // bit 10 to 19 corner line2
	unsigned int		lineslot:3;         // bit 20 to 22 line slot
*/
	
	unsigned short  line1;        // bit 0 to 9 corner line1
	unsigned char	line2:4;         // bit 10 to 19 corner line2
	unsigned char	lineslot:3;         // bit 20 to 22 line slot
	
	struct BETSB_ODDS     odds;   // odds
    unsigned char         selbu;  // selection
};



struct BETSB_SEL_FO_1           // FGS
{
  unsigned char         selbu;  // selection number 
  unsigned short        selwu;  // player #
  struct BETSB_ODDS     odds;   // odds
};
// ..LY09
// PN26..
struct BETSB_SEL_FO_SCC     // Scorecast
{
  struct BETSB_SEL_FO_1 fgs;    // first goal scorer selection and odds
  struct BETSB_SEL_FO_3 crs;    // correct score selection and odds
  struct BETSB_ODDS     odds;   // scorecast odds
};
// ..PN26  

// Q408 
struct BETSB_SEL_FO_NTS         // for NTS
{
  char                  noofgoal; // Goal #
  struct BETSB_SEL_FO_2 sel[3]; // variable selections 
};


struct BETSB_SEL_FO_OOU
{
  unsigned char         scorebu;        // score to compared with
  struct BETSB_SEL_FO_2 sel[2];         // variable selections
};


struct BETSB_SEL_FO_HILO
{
	
//	unsigned char unused1:4;               // unused
//	unsigned char unused2:2;               // unused
//	unsigned char newMflag:1;               // uses new multiple line data structure
//	unsigned char unused3:1;               // unused  

	unsigned char unused;
	struct BETSB_SEL_FO_2G sel[10];         // new variable selections with goals line along each selection Maximum repeat for 10 selections
  	
};

struct BETSB_SEL_FO_CHLO
{
	unsigned short	line1;			// total corner * 10 (max value 400)
	//unsigned char	unused1: 1;				// unused
	unsigned short   line2:15;			// total corner line 2 * 10 (max value 400)
	unsigned short   new_flag:1;			// indicates use new multiple line data structure
	struct BETSB_SEL_FO_2C sel[10];		// new format for multiple line (Bit31 on) maximum repeat for 10 selections
	
};




struct BETSB_SEL_FO_HDC         // for HDC & HHAD
{
  char                  goal1b; // handicap goal 1 *10 [HDC]
                                // handicap goal       [HHAD]
  char                  goal2b; // handicap goal 2 *10 [HDC]
                                // [= goal 1 if normal handicap]
                                // not used for HHAD
  struct BETSB_SEL_FO_2 sel[3]; // variable selections LY13
};
struct BETSB_SEL_PM_SPC         // pari-mutuel OOU/HDC/HHAD
{
  char                  compb;          // score to compared [OOU] with
                                        // or handicap goal*10 [HDC]
                                        // or handicap goal [HHAD]
  unsigned char         selbu;          // variable selections LY13 PN14
};
// PN11..
struct BETSB_SEL_PM_1           // fgs
{
  unsigned char         selbu;  // selection number 
  unsigned short        selwu;  // player #
};

// LY12..
struct BETSBIND                         // SB bet indicator
{
  unsigned char crs1:1;                  // correct score with dynamic number
                                        // of bytes for selection   PN20
  unsigned char rand1:1;                 // randomly generated
  unsigned char :6;                      // unused
};

struct BETSB_SEL_PM_TRN_GRP
{
  unsigned char     selbu[SB_MAX_TRN_SEL];  // selection bit map
                        // bit 0 set => field selected in the selection entity
                        // bit n set => selection n is picked
};

struct BETSB_SEL_PM_TRN     // tournament pool selection bit map    PN15..
{
    unsigned char   minbu;      // min. number of selection in each group
    unsigned char   maxbu;      // max. number of selection in each group
    unsigned char   cntbu;      // number of selection for a bet
    unsigned char   ngrpbu;     // number of group / position
                                // (which is pool dependent:
                                // CHP/CHP2 : number of ordered position
                                // QFT: number of group)
    unsigned char   gsizbu;     // number of byte per group / posititon
    unsigned char   vbu[SB_MAX_TRN_BUF];    // group selection
                                // variable part : BETSB_SEL_PM_TRM_GRP[ngrpbu]
};                              // ..PN15

// PN20..
struct BETSB_SEL_PM_CRS2    // selection for correct score related pool 
{
    unsigned char maxbu;    // maximum score for a team selection in score
                            // => number of byte for a score selection
                            // = [(maxbu+1)*(maxbu+1)+4+7]/8
    unsigned char vbu[(BETSB_CRS_SELBC)*2]; // selection bit map 
                            // bit 0 => field indicator
                            // bit 1 to (maxbu+1)*(maxbu+1) => score selected
                            // bit (maxbu+1)*(maxbu+1) + 1 => others, home win
                            // bit (maxbu+1)*(maxbu+1) + 2 => others, away win
                            // bit (maxbu+1)*(maxbu+1) + 3 => others, draw 
};
// ..PN20
  
union BETSB_SEL_PM_DET                  // SB PM selections detail
{
  struct BETSB_SEL_PM_1     pm1[BETSB_MAX_SEL]; // fgs variable selections..PN11
  struct BETSB_SEL_PM_SPC   sel;                // oou/hdc/hhad
  unsigned char             sel2bu[BETSB_MAX_SEL][2];       // cos
                                                // variable sections 
                                                // ('FF' stored for others on
                                                // cos selection)
// PN14..
  unsigned short            sel1wu[BETSB_MAX_ENT];  
                                    // half-full selection bit map: 
                                    // bit n set implies collated entry n is
                                    // selected, maximum 9 combinations
                                    // tos selection bit map : 
                                    // only entry 0 is used
  unsigned char             sel1bu; // oes/1x2 selection bit map    ..PN14
  unsigned int              sellu[2];   
                                    // half time/full time cos selection bit map
                                    // (indexed by SB_RES_HALF, SB_RES_FULL) :
                                    // bit n set implies collated entry n is
                                    // selected.  Sign bit (bit 31) is used
                                    // to store field bet selected on
                                    // corresponding result.
                                    // ..PN11
  struct BETSB_SEL_PM_TRN   trnsel; // tournament pool selection PN15
  struct BETSB_SEL_PM_CRS2  crs;    // HCS selections PN20
};

struct BETSB_SEL_PM                     // soccer betting pari-mutuel selection
{
  struct BETSBIND           ind;        // bet indicator
  union BETSB_SEL_PM_DET    det;        // selection details
};

union BETSB_SEL_NON             // soccer betting non-allup selection
{
  struct BETSB_SEL_FO_1 fo1[BETSB_MAX_SEL];     // fix odds fgs
                                                // variable selections
  struct BETSB_SEL_FO_2 fo2[BETSB_MAX_SEL];     // oes/tos/1X2/gpw/tps  PN17
                                                // variable selections
  struct BETSB_SEL_FO_OOU       foOou;          // oou
  struct BETSB_SEL_FO_HILO		hilo;			// new hilo
  struct BETSB_SEL_FO_CHLO		chlo;			// new chlo
  struct BETSB_SEL_FO_3 fo3[BETSB_MAX_SEL];     // dbr/cos/gpf/chp  PN17
                                                // variable selections
  struct BETSB_SEL_FO_SCC       foscc[BETSB_MAX_SEL];           
                                                // Scorecast    PN26
  struct BETSB_SEL_FO_HDC       foHdc;          // hdc
  struct BETSB_SEL_FO_NTS		foNts;			// nts /ets  Q408
  struct BETSB_SEL_PM            pm;            // pari-mutuel
};
// ..LY12

struct BETSB_SEL_AUP        // soccer betting allup selection per event
{
  unsigned int          pftrlu;         // pay factor
  unsigned short        bonuswu;        // bonus % for first level
  unsigned short        levelbonwu;     // per-level bonus % (first one is
                                        // not used)
  union BETSB_SEL_NON   sel;            // selections
};

// PN14.. 
struct BETSB_SEL_MIX    // mix bet type 
{
  unsigned short        bonusewu;       // bonus %
  union BETSB_SEL_NON   sel;            // selections
};
// ..PN14

union BETSB_SEL
{
  union  BETSB_SEL_NON  non;
  struct BETSB_SEL_AUP  aup;
  struct BETSB_SEL_MIX  mix;            // mix bet type             PN14
};

// PN11..
struct BETSB_SIMPLE_TEAM
{
  unsigned short        homewu; // home team #
  unsigned short        awaywu; // away team #
};
                                                                               
union BETSB_SIMPLE_S
{
  struct BETSB_SIMPLE_TEAM      team;           // team number
  __time32_t                        cdate;          // tournament pool / SPC 
                                                // creation date (part of a 
                                                // key)
};
// ..PN11

struct BETSB_SIMPLE             // simple pool selection [variable length]
{
  unsigned char         daybu:7;  // day of week/event #/group # for GWP/
                                // item # for SPC
  unsigned char         extrabu:1;  // extra time bet Q407
  unsigned char         matchbu;// match of the day/tournament #/ pool #
                                // for SPC
  __time32_t                date;   // match/settlement date
  unsigned char         poolbu:6; // pool type #
  unsigned char			selrefund:1; //selective refund indicator  // MSR2014
  unsigned char         livebu:1; // live betting flag 
  union BETSB_SIMPLE_S  info;   // pool dependent information    PN11
  unsigned char         numbu:7;// # of selections              PN14
  unsigned char         fld1:1; // field selection              PN14
  union BETSB_SEL       sel;    // variable selections
};

// PN20..
struct BETSB_SCT_ID     // identity information for section bet
{
  unsigned char         setbu;          // section set number
};

union BETSB_BONUS_SCT
{
  unsigned short        bonuspcentwu;   // bonus % * 100 for non-allup
  struct BETSB_SCT_ID   sctid;          // identity information for section bet
};

struct BETSB_DET
{
  unsigned int          bonuslu;        // total bonus in cents
  unsigned int          refundlu;       // refund in cents 
  union BETSB_BONUS_SCT sctbonus;       // bonus or section bet id
  unsigned char         numbu;          // # of simple pool
  unsigned char         fmlentbu;       // all-up formula / # of entry  PN14..
  unsigned char         vbu[SB_MAX_BET_BUF];  
                                // variable part :-
                                //  single entry: BETSB_SIMPLE[*]
                                //  multiple entry (when bet type is not
                                //      all-up bet and fmlentbu > 0): 
                                //      [ BETSB_SIMPLE with n entry ][npoolbu]
                                //                                      ..PN14
};

// ..PN20

union   BETVAR                          // variable part
{
  struct BETAUP         a;      // allup
  struct BETEXOSTD      es;     // exotic/standard
  struct BETLOT         lot;    // lottery
  struct BETDEP         cv;     // cash voucher
  struct BETSB_DET      sb;     // soccer betting
};
struct  BETDATA
{
  struct BETHDR         hdr;    // common header
  union BETVAR          var;    // variable part
};

struct  BET
{
  struct BETCBHDR       h;      // header
  struct BETDATA        d;      // data
};
union BETSBHDR
{
  struct BETSBCBHDR     sbcb;     // cashbet header in OLTP-SB bet file
  struct BETSBACHDR     sbac;   // account bet header in OLTP-SB bet file
};
struct BETSB            // bet record in SB
{
  short                 lenw;           // length in byte
  unsigned int          offsetlu;       // record word offset of bet in normal
                                        // bet file (same as the one in tsn)
  unsigned char          cb1:1;          // cb indicator
  unsigned char          ac1:1;          // account-betting indicator
  unsigned char          reversed1:1;    // sell reversed
  unsigned char          woodds1:1;      // selling without odds specified  PN01
  unsigned char          :4;
  union BETSBHDR        h;      // header
  struct BETDATA        d;      // data
};
struct BETSB_CB         // soccer betting bet record in CB
{
  unsigned short        lenwu;  // size of bet record
  struct BETCBHDR       hdr;
  struct BETDATA        d;
};
//struct BETSB_AC         // soccer betting bet record in AC
//{
//  unsigned short        lenwu;  // size of bet record
//  struct BETACHDR       hdr;
//  struct BETDATA        d;
//};

struct BETABRAC
{
  unsigned char   srcbu:6;    // source of sell (Changed 201108PSR)
  unsigned char   blc1:1;  // Transaction with CSC Card (Added 201108PSR); triggers control
  unsigned char   csctrn : 1;  // Transaction with CSC Card (Added 201108PSR)
  //__time32_t          dat;      // meeting date
  //unsigned char   locbu;    // location
  //unsigned char   daybu;    // day
  struct BETDATA  d;        // data
};
struct BETABLOT
{
  unsigned char   srcbu:7;    // source of sell (Changed 201108PSR)
  unsigned char   csctrn:1;  // Transaction with CSC Card (Added 201108PSR)
  //unsigned short  yearwu;   // year
  //unsigned short  drawwu;   // draw #
  //unsigned short  typewu;   // type of lottery
  struct BETDATA  d;        // data
};
// FT25...
struct BETABEXTRA
{
  unsigned short   lenwu;
  unsigned int     lscnlu;      // losing consolation in cents     
                                // only available when final paid or div cal bit is set.  
  // more attributes can be added here in future
};
struct BETABRAC2                // for AB history & DIVBET only
{
    struct BETABEXTRA   extra;
    struct BETABRAC     bet;
};
// ...FT25
union BETDATA_AB
{
    struct BETABRAC  rac;
    struct BETABLOT  lot;
    struct BETABRAC2 rac2;          // for AB history & divbet only
};
// VC08..               // AB Bet Record 
struct  BETAB
{
  short                 lenw;       // length in byte   VC10
  unsigned int          acclu;      // account #
  unsigned int          translu;    // transaction #
  unsigned char         abbettypebu;
    #define BETAB_AUP       0
    #define BETAB_EXO       1
    #define BETAB_LOT       2
    #define BETAB_AUP2      3       // for AB history & divbet.dat only
    #define BETAB_EXO2      4       // for AB history & divbet.dat only
  union BETDATA_AB      bet;        // bet information
};
// VC08..

struct  BETS            // shrink bet
{
  unsigned int  reclu;  // record #
  struct BET    bet;
};
struct BETABET                  // allup bet
{
  struct BETCBHDR       cbh;    // cb header
  struct BETHDR         h;      // standard header
  struct BETAUP         d;      // detail
};
struct BETESBET                 // exotic/standard bet
{
  struct BETCBHDR       cbh;    // cb header
  struct BETHDR         h;      // standard header
  struct BETEXOSTD      d;      // detail
};
struct BETLSBET                 // lottery single draw bet
{
  struct BETCBHDR       cbh;    // cb header
  struct BETHDR         h;      // standard header
  struct BETLOTFIX      d;      // detail
};
struct BETLMBET                 // lottery multi draw bet
{
  struct BETCBHDR       cbh;    // cb header
  struct BETHDR         h;      // standard header
  struct BETLOT         d;      // detail
};
struct BETCV                    // cv
{
  struct BETCBHDR       cbh;    // cb header
  struct BETHDR         h;      // standard header
  struct BETDEP         d;      // detail
};
struct BETSABET                 // shrink allup bet
{
  unsigned int          reclu;  // record no.
  struct BETABET        bet;    // bet record
};
struct BETSESBET                // shrink exotic/standard bet
{
  unsigned int          reclu;  // record no.
  struct BETESBET        bet;    // bet record
};
struct BETSLOT                  // shrink lottery bet (single/multi)
{
  unsigned int          reclu;  // record no.
  struct BETLSBET        bet;    // bet record
};
struct BETSCV                   // shrink cv
{
  unsigned int          reclu;  // record no.
  struct BETCV          cv;     // bet record
};

#define BETAUP_SIZE     sizeof(struct BETABET)
#define BETEXOSTD_SIZE  sizeof(struct BETESBET)
#define BETLOTMD_SIZE   sizeof(struct BETLMBET)
#define BETLOTSD_SIZE   sizeof(struct BETLSBET)
#define BETDEP_SIZE     sizeof(struct BETCV)
#define BETSAUP_SIZE    sizeof(struct BETSABET)
#define BETSEXOSTD_SIZE sizeof(struct BETSESBET)
#define BETSLOT_SIZE    sizeof(struct BETSLOT)
#define BETSDEP_SIZE    sizeof(struct BETSCV)
#define BETSB_SIZE      sizeof(struct BETSB)

#define BET_UNIT_BLOCK  5       // # of blocks in a unit
#define BET_UNIT_SIZE   ( BET_UNIT_BLOCK * 512 )        // unit size in bytes
#define BET_UNIT_AUP    ( BET_UNIT_SIZE / BETAUP_SIZE )
#define BET_UNIT_EXOSTD ( BET_UNIT_SIZE / BETEXOSTD_SIZE )
#define BET_UNIT_LOTSD  ( BET_UNIT_SIZE / BETLOTSD_SIZE )
#define BET_UNIT_LOTMD  ( BET_UNIT_SIZE / BETLOTMD_SIZE )
#define BET_UNIT_CV     ( BET_UNIT_SIZE / BETDEP_SIZE )
#define BET_UNIT_SAUP   ( BET_UNIT_SIZE / BETSAUP_SIZE )
#define BET_UNIT_SEXOSTD (BET_UNIT_SIZE / BETSEXOSTD_SIZE )
#define BET_UNIT_SLOT   ( BET_UNIT_SIZE / BETSLOT_SIZE )
#define BET_UNIT_SCV    ( BET_UNIT_SIZE / BETSDEP_SIZE )
#define BET_UNIT_SB     ( BET_UNIT_SIZE / BETSB_SIZE )

// VC08..
#define BETAB_UNIT_SIZE   ( BET_UNIT_BLOCK * 512 )    // unit size in bytes
// VC08..

union BETUNIT           // a bet unit
{
  struct BETABET        aup[BET_UNIT_AUP];
  struct BETESBET       es[BET_UNIT_EXOSTD];
  struct BETLSBET       ls[BET_UNIT_LOTSD];
  struct BETLMBET       lm[BET_UNIT_LOTMD];
  struct BETCV          cv[BET_UNIT_CV];
  struct BETSABET       saup[BET_UNIT_SAUP];
  struct BETSESBET      ses[BET_UNIT_SEXOSTD];
  struct BETSLOT        slot[BET_UNIT_SLOT];
  struct BETSCV         scv[BET_UNIT_SCV];
  unsigned char         bu[BET_UNIT_SIZE];
};

#pragma pack()

#endif
