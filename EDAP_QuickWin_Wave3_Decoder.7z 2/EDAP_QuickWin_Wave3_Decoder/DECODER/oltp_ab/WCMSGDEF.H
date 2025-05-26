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
//    WCMSGDEF.H - Defines for interfaces WC and remotes
//
//    Author :  Joseph Chan         13-JUL-2005
//
//    Mods:     JC01        16-NOV-2005
//              use bitmap indicate disable aup betting by race
//
//              JC02        25-NOV-2005
//              add extra info for error ack
//
//              CS03        03-DEC-2005
//              modify to support advanced snowball draw selling
//
//              CS04        05-DEC-2006
//              - fixing of wrong placing of on/off course indicator
//
#ifndef WCMSG_H
#define WCMSG_H

#include <time.h>
#include "o_maildef.h"
#include "udtypedef.h"
#include "rdsdef.h"
#include "lotdef.h"

#define WC_MAX_VAR_SIZE     10000               // max packet size from WC by UDP
#define WC_MAX_RACE_SIZE    6000                // max size of race details
#define WC_MAX_BUF          1000                // max buffer
#define WC_MAX_ENT          UCHAR_MAX           // maximum entry count

#define WC_STD_POOL         1   // standard pool type
#define WC_EXO_POOL         2   // exotic pool type
#define WC_AUP_POOL         3   // all-up pool type
#define WC_POOLTYPE_MAX     3   // all-up pool type

// RDC request from WC
#define WCMSG_CODE_NONE     0       // function code not decided
#define WCMSG_CODE_MTGINP   301     // new meeting schedule
#define WCMSG_CODE_MTGRCC   302     // race close interval
#define WCMSG_CODE_PARRCW   303     // race close warning interval
#define WCMSG_CODE_MTGBSI   304     // change of bad sale interval
#define WCMSG_CODE_MTGSRS   305     // start sell all pools in a meeting
#define WCMSG_CODE_MTGSPS   306     // stop sell all pools in a meeting
#define WCMSG_CODE_RCESPS   307     // stop sell W/P/Q/QP or all pools in a race
#define WCMSG_CODE_RCESPP   308     // stop pay all pools in a race
#define WCMSG_CODE_POLSRS   309     // start sell a pool
#define WCMSG_CODE_POLSPS   310     // stop sell a pool
#define WCMSG_CODE_POLSPP   311     // stop pay pool
#define WCMSG_CODE_RCESUB   312     // race substitutes
#define WCMSG_CODE_RCESCR   313     // race scratch runner
#define WCMSG_CODE_RCERES   314     // race results
#define WCMSG_CODE_RCEPTT   315     // race post time 
#define WCMSG_CODE_RCECLS   316     // race close
#define WCMSG_CODE_POLRAD   317     // pool result and dividend
#define WCMSG_CODE_RCEAPP   318     // all-up post race pass
#define WCMSG_CODE_POLRFD   319     // pool refund
#define WCMSG_CODE_POLCRF   320     // cancel pool refund
#define WCMSG_CODE_PARAUE   321     // enable/disable all-up formulae
#define WCMSG_CODE_PARAUF   322     // allup formulae
#define WCMSG_CODE_RCEEAU   323     // enable/disable allup betting in a race
#define WCMSG_CODE_PARAUW   324     // aup reinvestment warning limit 
#define WCMSG_CODE_MTGABN   325     // abandon meeting
#define WCMSG_CODE_PARMBV   326     // max. bet value
#define WCMSG_CODE_PARPHL   327     // pay out limits
#define WCMSG_CODE_PARTBD   328     // telebet deposit parameters
#define WCMSG_CODE_PARTBW   329     // telebet withdrawal parameters
#define WCMSG_CODE_PARCRE   330     // enable/disable deposit betting
#define WCMSG_CODE_PAREMC   331     // EFT min. cash voucher amount
#define WCMSG_CODE_PARNBD   332     // next business date
#define WCMSG_CODE_PARPHB   333     // peak hour min. bet 
#define WCMSG_CODE_PARLBV   334     // large bet values
#define WCMSG_CODE_PARLDV   335     // large dividend values
#define WCMSG_CODE_LOTINP   336     // new lottery schedule
#define WCMSG_CODE_LOTDDT   337     // change of lottery draw date
#define WCMSG_CODE_LOTODT   338     // change of lottery opening date
#define WCMSG_CODE_LOTCDT   339     // change of lottery closing date time
#define WCMSG_CODE_LOTSRS   340     // start sell lottery
#define WCMSG_CODE_LOTSPS   341     // stop sell lottery
#define WCMSG_CODE_LOTRES   342     // lottery result
#define WCMSG_CODE_LOTPRZ   343     // lottery prize
#define WCMSG_CODE_LOTSPP   344     // stop pay lottery prize
#define WCMSG_CODE_LOTCLM   345     // claim lottery prize
#define WCMSG_CODE_LOTCCM   346     // cancel claim on lottery prize
#define WCMSG_CODE_PARLBS   347     // lottery bad sale interval
#define WCMSG_CODE_PARLCW   348     // lottery close warning interval
#define WCMSG_CODE_LOTSRN   349     // lottery selection range
#define WCMSG_CODE_LOTUNI   350     // lottery unit bet
#define WCMSG_CODE_LOTCEN   351     // lottery ccgame enable/disable selling
#define WCMSG_CODE_PARCVE   352     // CV Encashment 
#define WCMSG_CODE_LSCMTG   353     // losing amount consolation control - meeting 
#define WCMSG_CODE_LSCRCE   354     // losing amount consolation control - race
#define WCMSG_CODE_LSCPOL   355     // losing amount consolation control - pool
#define WCMSG_CODE_PAREXB   356     // enable/disable external branch
#define WCMSG_CODE_LOTMER   357     // lottery draw merge // CS03
                         

//
// the following messages are bad sale expired log request
// initiated by WCHNDR
#define WCMSG_CODE_POLBSE   401     // pool bad sale expired
#define WCMSG_CODE_LOTBSE   402     // lottery bad sale expired
//
// the following message is requests initiated by WCHNDR
// when event detacted in WCHTIMER  
#define WCMSG_CODE_RCECLW   403     // race close warning
#define WCMSG_CODE_LOTCLW   404     // lottery close warning
#define WCMSG_CODE_LOTCLS   405     // lottery close
//
// the following messages are requests initiated by WCHNDR
// race/ lottery close reply from BTHNDR  
#define WCMSG_CODE_RCEFIN   406     // race collation final
#define WCMSG_CODE_LOTFIN   407     // lottery collation final
//
#define WCMSG_CODE_APPSTA   408     // appprp start
#define WCMSG_CODE_APPDON   409     // appprp done
//
//
// the following messages are requested by RWCC only
//
#define WCMSG_CODE_RCERPT   501     // race report request
#define WCMSG_CODE_LOTRPT   502     // lottery report request
#define WCMSG_CODE_PUNMIN   503     // change partial unit bet minimum cost
#define WCMSG_CODE_RCESPSA  504     // stop sell all pools in a race
//
// the following messages are used by RWCC only
//
#define WCMSG_CODE_HELP     601     // for command help menu
#define WCMSG_CODE_POLWPS   602     // pool exotic winner pass
#define WCMSG_CODE_LPOLWPS  603     // pool exotic winner pass with win. comb.
#define WCMSG_CODE_LOTWPS   604     // lottery winner pass
//#define WCMSG_CODE_LSCEXT   605     // dummy code for global change on loosing
//                                    // consolation enabling for external branch

#pragma nomember_alignment


struct WCMSG_MTGID                      // meeting ID
{
    unsigned char       locbu;          // meeting location
    unsigned char       daybu;          // meeting day code
};

struct WCMSG_DATE                       // Date format
{
    unsigned char       daybu;          // day of month
    unsigned char       mthbu;          // month no.
    unsigned short      yrwu;           // year (9999)    
};

struct WCMSG_TIME                       // Time format
{
    unsigned char       hrbu;           // hour
    unsigned char       minbu;          // minute
    unsigned char       secbu;          // second
};

struct WCMSG_MTGRCC                     // Race Close Interval (302)
{
    struct WCMSG_MTGID  mtgid;          // meeting ID
    unsigned short      oncwu;          // on-course close interval (min)
    unsigned short      ofcwu;          // off-course close interval (min)
};

struct WCMSG_MTGBSI                     // Bad Sale Interval (304)
{
    struct WCMSG_MTGID  mtgid;          // meeting ID
    unsigned short      secwu;          // bad sale interval (sec)
};             

struct WCMSG_COSIND                     // on/off course indicator
{
    unsigned short       ofc1:1;        // off-course indicator  // CS04
    unsigned short       onc1:1;        // on-course indicator   // CS04
    unsigned short       :14;           // unused
};

struct WCMSG_MTGSEL                     // Start Sell All Pools in a mtg (305)
                                        // Stop  Sell All Pools in a mtg (306)
{
    struct WCMSG_MTGID  mtgid;          // meeting ID    
    struct WCMSG_COSIND cosind;         // on/off course indicator
};

struct WCMSG_RACE                       // Stop Pay all pools in a race (308)
                                        // Race Close (316)
                                        // AUP Post Race Pass (318)
                                        // Abandon Meeting (325)
{
    struct WCMSG_MTGID  mtgid;          // meeting ID    
    unsigned char       racebu;         // race no.    
};

struct WCMSG_RCESPS                     // Stop Sell pools in a race (307)
{
    struct WCMSG_RACE   race;           // meeting id + race no.
    unsigned char       polindbu;       // pools indication
        #define POOLS_ALL       0       // stop sell all pools
        #define POOLS_WPQQP     1       // stop sell W,P,Q,QP
    struct WCMSG_COSIND cosind;         // on/off course indicator
};

struct WCMSG_POOL                       // Stop Pay a pool (311)
                                        // Pool Refund (319)
                                        // Cancel Pool Refund (320)
{
    struct WCMSG_RACE   race;           // meeting id + race no.
    unsigned char       codebu;         // pool code    
};

struct WCMSG_POLSEL                     // Start Sell a pool (309)
                                        // Stop  Sell a pool (310)
{
    struct WCMSG_POOL   pool;           // meeting ID + race no. + pool code 
    struct WCMSG_COSIND cosind;         // on/off course indicator
};     

struct WCMSG_MPOOL                      // multi-leg pool
{
    unsigned char       codebu;         // pool code
    unsigned int        legmaplu;       // legs bitmap of multi-leg pool
};

struct WCMSG_MTGRCE                     // meeting schedule race details
{
    unsigned char       racebu;         // race no.
    unsigned char       fieldbu;        // field size
    struct WCMSG_DATE   date;           // post date
    struct WCMSG_TIME   time;           // post time
    unsigned short      distwu;         // race distance
    unsigned int        onpolu;         // on-course pool bitmap
    unsigned int        offpolu;        // off-course pool bitmap
    unsigned char       numbu;          // no. of pools
    struct WCMSG_MPOOL  mpool[RDS_MAXPOOL];    // multi-leg pool
};

struct WCMSG_MTGINP                     // meeting schedule define (301)
{
    struct WCMSG_MTGID  mtgid;          // meeting ID
    unsigned short      mtgnowu;        // meeting no.
    struct WCMSG_DATE   mtgdate;        // meeting date
    unsigned short      onintwu;        // on-course race close interval in min.
    unsigned short      offintwu;       // off-course race close interval in min.
    unsigned short      bsintwu;        // bad sale interval in seconds
    unsigned short      retentwu;       // retention period in days
    unsigned char       numbu;          // no. of races
    unsigned char       varbu[WC_MAX_RACE_SIZE];   // race data     
};

struct WCMSG_RCESUB                     // race substitutes (312)
{
    struct WCMSG_RACE   race;           // meeting id + race no.
    unsigned char       subbu[RDS_MAXSUB];// substitude horse no.
};

struct WCMSG_RCESCR                     // race scratching (313)
{
    struct WCMSG_RACE   race;           // meeting id + race no.
    unsigned int        scrbitlu;       // scratch starters bitmap
    unsigned char       numplabu;       // no. of placing for PLA pool
};
    
struct WCMSG_RCERES                     // race result (314)
{
    struct WCMSG_RACE   race;           // meeting id + race no.
    unsigned int        reslu[RDS_MAXRES]; // placing starter no. bitmap
};

struct WCMSG_RCEPTT                     // race post time (315)
{
    struct WCMSG_RACE   race;           // meeting id + race no.
    struct WCMSG_DATE   date;           // post date
    struct WCMSG_TIME   time;           // post time
};

struct WCMSG_PRZSTT
{
    unsigned short       div1:1;        // dividend-in
    unsigned short       part1:1;       // partial unit
    unsigned short       clm1:1;        // prize claim
    unsigned short       dfix1:1;       // dividend fixed    
    unsigned short       :12;           // unused
};

struct WCMSG_POLDIV                     // dividend details
{
    struct WCMSG_PRZSTT przstt;         // dividend status bitmap
    LONGLONG            amtd;           // dividend amount (in cent)
    BOOL                xprzt;          // consolation/6-win bonus Flag
    unsigned int        wcmaplu[RDS_MAXWCSIZ]; // winning combination bitmap    
};

struct WCMSG_POLRAD                     // pool result & dividend (317) 
{ 
    struct WCMSG_POOL   pool;           // meeting ID + race no. + pool code 
    BOOL                subst;          // substitution Flag 
    unsigned char       numbu;          // no. of dividends  
    struct WCMSG_POLDIV div[RDS_MAXDIV];    // dividend details
};

struct WCMSG_AUPFML                     // aup formula details 
{
    unsigned char       poolbu;         // pool code
    unsigned LONGLONG   fmlmapdu;       // AUP formulae Bitmap    
};

struct WCMSG_PARAUF                     // AUP Formulae (322)
{
    unsigned char       numbu;          // no. of pools
    struct WCMSG_AUPFML data[RDS_POOL_MAX]; // aup formula details
};

struct WCMSG_RCEEAU                     // Enable AUP Betting (323)     // JC01
{
    struct WCMSG_MTGID  mtgid;          // meeting ID                  
    unsigned int        rcestslu;       // race status bitmap       
                                        // 1=enable aup betting / 0=disable aup betting 
                                        // bit 0 unused, bit 1 = race 1...
};

struct WCMSG_PARMBV                     // Max Bet Value (326)
{
    unsigned LONGLONG   maxbetdu;       // OCB Max. Bet Value (cents)
    unsigned LONGLONG   maxcvdu;        // Max. CV amount (cents)
    unsigned LONGLONG   svtcvdu;        // Max. SVT CV amount (cents)
    unsigned LONGLONG   optcvdu;        // Max. OPT CV amount (cents)
};

struct WCMSG_PARPHL                     // Payout Limit (327)
{
    unsigned LONGLONG   hopaydu;        // Pay at HO limit (cents)
    unsigned LONGLONG   ocbpaydu;       // Pay at original centre limit (cents)
};


struct WCMSG_PARTBD                     // TB Deposit Parameter (328)
{
    unsigned LONGLONG   mindepdu;       // min. deposit amount (cents)
    struct WCMSG_TIME   startime;       // start time for deposit
    struct WCMSG_TIME   endtime;        // end time for deposit
};

struct WCMSG_PARTBW                     // TB Withdrawal Parameter (329)
{
    unsigned LONGLONG   minwdrwdu;      // min. withdrawal amount (cents)
    unsigned LONGLONG   maxwdrwdu;      // max. withdrawal amount (cents)
    unsigned char       maxcntbu;       // max. withdrawal count
    unsigned short      holdtmwu;       // TB deposit on hold time (mins)
};

struct WCMSG_PAREMC                     // EFT Min. CV Limit (331)
{
    unsigned int        rcedaylu;       // race day limit (dollar)
    unsigned int        nonrcelu;       // non-race day limit (dollar)
};

struct WCMSG_LBET
{
    unsigned char       poolbu;         // pool code
    unsigned LONGLONG   amtdu;          // large bet value (cents)
};

struct WCMSG_PARLBV                     // Large Bet Values (334)
{
    unsigned char       numbu;          // no. of pool
    struct WCMSG_LBET   data[RDS_POOL_MAX];     // large bet details
};

struct WCMSG_LDIV                       // Large Div. details 
{
    unsigned char       typebu;         // pool type
    unsigned LONGLONG   amtdu;          // large dividend value (cents)    
};

struct WCMSG_PARLDV                     // Large Dividend Values (335)
{
    unsigned char       numbu;          // no. of dividend
    struct WCMSG_LDIV   data[WC_POOLTYPE_MAX];   // Large Div. details 
};

struct WCMSG_LOTID                      // Lottery Draw ID
{
    unsigned char       yrbu;           // draw year (yy)
    unsigned short      numwu;          // draw no.
};

struct WCMSG_LOTDRAW                    // Start Sell Lottery (340)
                                        // Stop Sell Lottery  (341)
{
    struct WCMSG_LOTID  did;            // draw ID
    unsigned char       gidbu;          // game ID
};

struct WCMSG_LOTINP                     // Lottery Schedule   (336)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    BOOL                snowdrwt;       // snowball draw flag // CS03
    char                shortnames[LOT_SNAME_LEN-1]; // snowball draw short name // CS03
    char                longnames[LOT_NAME_LEN-1];   // snowball draw long name // CS03
    struct WCMSG_DATE   drwdat;         // draw date
    struct WCMSG_DATE   opndat;         // opening date
    struct WCMSG_DATE   clsdat;         // closing date
    struct WCMSG_TIME   clstm;          // closing time
    unsigned short      retentwu;       // retention period (day)
};

struct WCMSG_LOTDATE                    // Lottery Draw Date (337)
                                        // Lottery Opening Date (338)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    struct WCMSG_DATE    date;          // new draw/opening date
};

struct WCMSG_LOTCDT                     // change of Lot. Closing Date Time (339)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    struct WCMSG_DATE    date;          // new draw/opening date
    unsigned char        reopent;       // re-open draw flag 
    struct WCMSG_TIME    time;          // closing time
};

struct WCMSG_LOTRES                     // Lottery Result (342)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    unsigned char        numbu;         // no. of result
    unsigned char        drawbu[LOT_SELMAX]; // draw no.
};

struct WCMSG_PRZDAT                     // Lottery Prize details
{
    unsigned char       subtypebu;      // subgame type
    struct WCMSG_PRZSTT przstt;         // prize status bitmap
    unsigned LONGLONG   amtdu;          // prize value (cents)
};

struct WCMSG_LOTPRZ                     // Lottery Prize (343)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    unsigned char        gtypebu;       // lottery game type [0]=>normal, [>0]=>cc game
    unsigned char        numbu;         // no. of prize
    struct WCMSG_PRZDAT  data[LOT_MAX_GAME_PRZ]; // Lottery Prize details
};

struct WCMSG_LOTSPP                     // Stop Pay On Lottery Prize (344)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    unsigned char        gtypebu;       // lottery game type [0]=>normal, [>0]=>cc game
    unsigned char        numbu;         // no. of prize
    unsigned char        subtypebu[LOT_MAXSUBGAME_CUR]; // subgame type
};


struct WCMSG_LOTCLM                     // Claim Lottery Prize (345)
                                        // Cancel Claim Lottery Prize (346)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    unsigned short       przwu;         // Prize no.
};

struct WCMSG_LOTITV                     // Lottery Bad Sale Interval (347)
                                        // Lottery Close Warning Interval (348)
{
    unsigned char       gidbu;          // game ID
    unsigned short      intwu;          // lottery bad sale interval (sec)
                                        // lottery close warning interval (min)
};

struct WCMSG_LOTSRN                     // Lottery Selection Range (349)
{
    unsigned char       gidbu;          // game ID
    unsigned short      maxselwu;       // max. selection no.
    unsigned short      minselwu;       // min. selection no.
    unsigned short      maxextwu;       // max. extra no.
    unsigned short      minextwu;       // min. extra no.
};

struct WCMSG_LOTUNI                     // Lottery Unit Investment  (350)
{
    unsigned char       gidbu;          // game ID
    unsigned char       gtypebu;        // concurrent game type
    unsigned int        amtlu;          // base investment (dollar)
};

struct WCMSG_LOTCEN                     // Enable/Disable Concurrent Game Selling (351)
{
    unsigned char       gidbu;          // game ID
    unsigned char       gtypebu;        // concurrent game type
    BOOL                enat;           // enable/disable Flag
};

struct WCMSG_PARCVE                     // CV Encashment Control (352)
{
    BOOL                enat;           // enable/disable Flag
    unsigned LONGLONG   amtdu;          // remaining amount (cents)
    unsigned short      unusedwu;       // CV unused %
};

struct WCMSG_LSCMTG_ENT
{
    unsigned char           tierbu;             // tier id
    unsigned char           chanbu;             // 1=>CB, 2=>AB
    unsigned char           enabu;              // 1=>ENABLE, 0=>DISABLE 
    unsigned LONGLONG       amtdu;              // amount in cents
};

struct WCMSG_LSCMTG                     // losing amt consolation ctl - mtg (353)
{
    struct WCMSG_MTGID      mtgid;                  // meeting ID, 0/0 for golbal change
    unsigned char           fillerbu;               // filler
    unsigned char           numbu;                  // # of entry, must be 0 for global change
    struct WCMSG_LSCMTG_ENT ent[WC_MAX_ENT];        // by tier by channel data
};

struct WCMSG_LSCRCE_ENT
{
    unsigned char           racebu;                 // race #
    unsigned char           enabu;                  // 1=>ENABLE, 0=>DISABLE     
};

struct WCMSG_LSCRCE                     // losing amt consolation ctl - race (354)
{
    struct WCMSG_MTGID      mtgid;                  // meeting ID
    unsigned char           chanbu;                 // 1=>CB, 2=>AB
    unsigned char           numbu;                  // # of entry
    struct WCMSG_LSCRCE_ENT ent[WC_MAX_ENT];        // by race by channel data
};

struct WCMSG_LSCPOL_ENT
{
    unsigned char           tierbu;                 // tier id
    unsigned char           poolbu;                 // pool id
    unsigned short          percwu;                 // % * 100
};

struct WCMSG_LSCPOL                     // losing amount consolation control - pool (355)
{
    struct WCMSG_MTGID      mtgid;                  // meeting ID
    unsigned char           racebu;                 // race #
    unsigned char           chanbu;                 // 1=>CB, 2=>AB
    unsigned char           numbu;                  // number of entry
    struct WCMSG_LSCPOL_ENT ent[WC_MAX_ENT];        // by tier by pool data
};

struct WCMSG_LOTMER                     // special draw merge to destination draw (357) //CS03
{
    struct WCMSG_LOTDRAW id;            // master draw ID (draw ID + game ID)
    struct WCMSG_LOTDRAW xdid;          // snowball draw ID (draw ID + game ID)
};

struct WCMSG_RCERPT                     // race report request (501)
{
    struct WCMSG_POOL   pool;           // meeting id + race no. + pool code
    unsigned char       idbu;           // report id
};

struct WCMSG_LOTRPT                     // lottery report request (502)
{
    struct WCMSG_LOTDRAW id;            // draw ID + game ID
    unsigned char        idbu;          // report id
};

struct WCMSG_PUNMIN                     // change partial unit bet min cost (503)
{
    struct WCMSG_MTGID  mtgid;          // meeting ID
    unsigned char       poolbu;         // pool code
    unsigned int        totallu;        // total amount in $
    unsigned int        unitlu;         // partial unit in $
};

struct WCMSG_HDR
{
    unsigned short      codewu;         // control msg type
    unsigned int        msnlu;          // MSN
    int                 sysbitl;        // system bitmap       
    unsigned char       reSendbu;       // resent flag
};

union WCMSG_DATA
{
    BOOL                        enat;       // Enable/Disable AUP formulae (321)
                                            // Enable/Disable Deposit Betting (330)
                                            // Enable/Disable External Branch (356)
    unsigned short              valwu;      // Race Close Warning Interval (303)
    unsigned int                vallu;      // Peak Hour Min. Bet (333)
    unsigned LONGLONG           valdu;      // AUP Reinvestment Warning Limit (324)
    struct WCMSG_DATE           date;       // Next Business Date (332)
    struct WCMSG_MTGINP         mtginp;     // meeting schedule define (301)
    struct WCMSG_MTGRCC         mtgrcc;     // Race Close Interval (302)
    struct WCMSG_MTGBSI         mtgbsi;     // Bad Sale Interval (304)
    struct WCMSG_MTGSEL         mtgsel;     // meeting start/stop sell (305)(306)
    struct WCMSG_RCESPS         rcesps;     // Stop Sell pools in a race (307)
    struct WCMSG_RACE           race;       // race (308)(316)(318)(325)
    struct WCMSG_POLSEL         polsel;     // pool start/stop sell (309)(310)
    struct WCMSG_POOL           pool;       // Race Pool (311)(319)(320)
    struct WCMSG_RCESUB         rcesub;     // race substitutes (312)
    struct WCMSG_RCESCR         rcescr;     // race scratching (313)
    struct WCMSG_RCERES         rceres;     // race result (314)
    struct WCMSG_RCEPTT         rceptt;     // race post time (315)
    struct WCMSG_POLRAD         polrad;     // pool result & dividend (317) 
    struct WCMSG_PARAUF         parauf;     // AUP Formulae (322)
    struct WCMSG_RCEEAU         rceeau;     // Enable AUP Betting (323)
    struct WCMSG_PARMBV         parmbv;     // Max Bet Value (326)
    struct WCMSG_PARPHL         parphl;     // Payout Limit (327)
    struct WCMSG_PARTBD         partbd;     // TB Deposit Parameter (328)
    struct WCMSG_PARTBW         partbw;     // TB Withdrawal Parameter (329)
    struct WCMSG_PAREMC         paremc;     // EFT Min. CV Limit (331)
    struct WCMSG_PARLBV         parlbv;     // Large Bet Values (334)
    struct WCMSG_PARLDV         parldv;     // Large Dividend Values (335)
    struct WCMSG_LOTINP         lotinp;     // Lottery Schedule   (336)
    struct WCMSG_LOTDATE        lotdate;    // Lottery Draw Date (337)(338)
    struct WCMSG_LOTCDT         lotcdt;     // change of Lot. Closing Date Time (339)
    struct WCMSG_LOTDRAW        lotdraw;    // Lottery Draw ID + Game ID (340)(341)
    struct WCMSG_LOTRES         lotres;     // Lottery Result (342)
    struct WCMSG_LOTPRZ         lotprz;     // Lottery Prize (343)
    struct WCMSG_LOTSPP         lotspp;     // Stop Pay On Lottery Prize (344)
    struct WCMSG_LOTCLM         lotclm;     // Claim/Cancel Claim Lottery Prize (345)(346)
    struct WCMSG_LOTITV         lotitv;     // Lottery Bad Sale/Cls Warning Interval (347)(348)
    struct WCMSG_LOTSRN         lotsrn;     // Lottery Selection Range (349)
    struct WCMSG_LOTUNI         lotuni;     // Lottery Unit Investment  (350)
    struct WCMSG_LOTCEN         lotcen;     // Enable/Disable Concurrent Game Selling (351)
    struct WCMSG_PARCVE         parcve;     // CV Encashment Control (352)
    struct WCMSG_LSCMTG         lscmtg;     // losing amount consolation control - meeting (353)
    struct WCMSG_LSCRCE         lscrce;     // losing amount consolation control - race (354)
    struct WCMSG_LSCPOL         lscpol;     // losing amount consolation control - pool (355)
    struct WCMSG_LOTMER         lotmer;     // special merge to destination draw (357) // CS03
    struct WCMSG_RCERPT         rcerpt;     // race report request (501)
    struct WCMSG_LOTRPT         lotrpt;     // lottery report request (502)
    struct WCMSG_PUNMIN         punmin;     // change partial unit bet min cost (503)
};

struct WCMSG_REQ
{
    struct WCMSG_HDR    hdr;                // wc message header
    union WCMSG_DATA    data;               // wc message data
};

struct WCMSG_ACK
{
//    unsigned short      errorwu;            // error code
    unsigned int        msnlu;              // msn in the wch ack.
    char                infos[100];         // extra error info string      // JC02
};

#pragma member_alignment

#endif
