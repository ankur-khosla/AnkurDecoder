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
//    Author : Edward Hon                01-NOV-2000
//
//    Mod :     JC01        12-NOV-2002
//              add partial unit bet minimum cost
//
//              JC02        20-FEB-2003
//              both "Change lottery closing date" and
//              "Change lottery closing time" contains new closing date/time
//
//              CS03        30-OCT-2003
//              add more area for selling to support OLTP-AB
//
//              JC04        18-OCT-2004
//              remove wcm expand bit as no one use it.  Forget why keep the original
//              wcm in the logger, may be just want to display the wcm from WC when
//              do the logdmp and audit
//
//              JC05        20-DEC-2004
//              add CV encashment checking parameters (178)
//
//              JC06        22-JUL-2005
//              limit the max. # of lottery prize in logger record
//
//              JC07        30-AUG-2005
//              1. combine logger for lottery, GBL/MK6 and normal/ccgame
//              2. add logger record for losing investment consolation (353/354/355)
//              3. change logger for struct LOGRDCLBV
//              4. add msnl, caller in logger for use of RWCC handshake
//              5. use logger structure of code 330 for code 356 also 
//
//              JN08        20-OCT-2005
//              For pools stop sell in a race, change 1 = WPQQP instead of -1
//
//              JC09        10-NOV-2005
//              use __time32_t for change post date time
//
//              JC10        16-NOV-2005
//              use bitmap for disable aup betting
//
//              CS11        06-DEC-2005
//              1. modify lottery input to support advance draw selling
//                 - add snowball flag, draw's short/long name in LOGRDCLSCH 
//                 - add slave draw index in LOGRDCIDL
//                 - add new logger record for draw merge (357) LOTRECLMER
//              2. delete structure LOGRDCLCT as replace by LOGRDCLCD and
//                 add new variable of lottery closing date
//
#ifndef LOGRDCDEF_H

#define LOGRDCDEF_H 1

#include <time.h>
#include <limits.h> //JC07
#include "udtypedef.h"
#include "rdsdef.h"
#include "lotdef.h"
//#include "wcmsgdef.h"
#include "bstypedef.h"

#define LOGRDC_MAXDHEAT         3                               // maximum dead heat
#define LOGRDC_RESSIZ           LOGRDC_MAXDHEAT * RDS_MAXRES    // race result size
#define LOGRDC_FLDRES           32                              // field result indicator in result

//#define LOGRDC_LRGBET_NOPOOL    5                               // define same as RDCPAR.H
#define LOGRDC_LRGDIV_NOPOOL    3                               // define same as RDCPAR.H

#define LOGRDC_MAX_ENT          UCHAR_MAX                       // maximum entry count

#pragma pack(1)

// MEETING OPTION

struct  LOGRDCRSCH      // race schedule portion
    {
        unsigned short  pstwu;          // race post time
        unsigned short  fszwu;          // field size
        unsigned short  distwu;         // race distance
        unsigned int    nraclu;         // on-course pools bitmap
        unsigned int    fraclu;         // off-course pools bitmap
        unsigned int    pleglu[RDS_MAXPOOL];    // pool legs bitmap
    };

struct  LOGRDCMSCH      // meeting schedule 
    {
        unsigned short     setwu;       // file set no. allocated
        unsigned short     mnumwu;      // meeting no.
        __time32_t             mdat;        // meeting date (bitty date)
        unsigned short     trcwu;       // total no. of race
        unsigned short     nrciwu;      // on-cousre race close interval (min.)
        unsigned short     frciwu;      // off-course race close interval(min.)
        unsigned short     bsiwu;       // bad sale expire interval (sec.)
        unsigned short     mrpwu;       // meeting retention period (in day)
        unsigned int       cstartlu;    // collation start
        LONGLONG           rstartd;     // next aup rin file VBN
        struct LOGRDCRSCH  rsch[RDS_MAXRACE+1]; // race schedule portion, [0] not used
    };

// abandon meeting, no more data log

struct  LOGRDCRCW       // race close interval
    {
        unsigned short  occtwu;         // on-course close interval (min)
        unsigned short  ofctwu;         // off-course close interval (min)
    };

struct  LOGRDCSPSTT             // change sell/ pay status
    {
        unsigned int    vbt1:1;         // off-course indicator // CS03..
        unsigned int    did1:1;         // on-course indicator
        unsigned int    esc1:1;         // off-course indicator //..CS03
        unsigned int    onc1:1;         // on-course indicator
        unsigned int    ofc1:1;         // off-course indicator
        unsigned int    :11;            // unused               // CS03
    };

struct  LOGRDCBSE       // meeting bad sale interval change 
    {
        unsigned short  bswu;           // new bad sale interval (in secs)
    }; 

// RACE OPTION

struct  LOGRDCSUB       // race substitute runner input
    {
        unsigned char   subbu[RDS_MAXSUB];      // substitute
    };

struct  LOGRDCSCR       // race scratching input
    {
        unsigned __int64    scrlu;          // scratching bit map
        unsigned __int64    nopbu;          // no. of placing for place
    };

struct  LOGRDCRES       // race result input
    {
        unsigned __int64    reslu[RDS_MAXRES];  // race result bit map
        unsigned int		full1:1;            // full result
        unsigned int		:15;                // unused
    };

struct  LOGRDCPTT       // race post time
    {
        __time32_t          pttDate;            // new post date time   // JC09
//        unsigned short  timewu;         // new race post time
    };

// Re-activate all-up post race pass, no more data log

// The following messages:
// start sell a pool, stop pay a pool, pool refund, cancel pool refund  
// will use the same struct LOGRDCSPSTT

// race close message, no more data log
// race collation final, no more data log
// race stop pay all pools, no more data log

// POOL OPTION
struct WCM          // information for each winning combination
{
        LONGLONG        divd;                   // dividend (in cents)
        unsigned LONGLONG    wclu[RDS_MAXWCSIZ];     // win comb bitmap
        unsigned LONGLONG    orgwclu[RDS_MAXWCSIZ];  // original win comb bitmap
};

struct  LOGRDCRAD       // pool rad/claim details input
    {
        unsigned char   subbu[RDS_MAXLEG][RDS_MAXSUB];  // sub. runner #
        unsigned __int64    scrlu[RDS_MAXLEG];              // scratching bitmap 
        unsigned short  nowu;                           // no. of result and dividend
        unsigned char   sflgbu;                         // substitute existing flag
        unsigned short    ovfl1:1;                        // dividend overflow
        unsigned short    clm1:1;                         // claim
        unsigned short    punit1:1;                       // partial unit
        unsigned short    unoff1:1;                       // unofficial
//        unsigned int    expand1:1;                      // wcm expanded       // JC04
        unsigned short    :12;                            // unused
        struct WCM      wcm[RDS_MAXDIV];                // wcm info for each wcm
    };

struct  LOGRDCPEW       // pool exotic winner
    {
        unsigned short  reswu[LOGRDC_RESSIZ+1][RDS_MAXLEG+1];
                                // each leg race result 
    };
// CS11..
struct LOGNAME
{
    char                shorts[LOT_SNAME_LEN]; // snowball draw short name // CS03
    char                longs[LOT_NAME_LEN];   // snowball draw long name // CS03
};
// ..CS11

//LOTTERY OPTION

struct  LOGRDCLSCH      // lottery schedule
    {

        __time32_t          ddate;          // draw date
        __time32_t          odate;          // opening date
        __time32_t          cdate;          // closing date & time
// ctimewu no use any more, but want to keep the structure size,
// just set it as filler        // JC
//        unsigned short  ctimewu;        // closing time in hhmm
//        unsigned short  fillerwu;       // closing time in hhmm
        struct LOGNAME  name;           // lottery name             // CS11
        unsigned short  retwu;          // retention period
        unsigned char   drawIdxbu;      // draw index used
        unsigned char   fileIdxbu;      // file index used
        unsigned short  lastLotSeqwu;   // last lottery sequence
        BOOL            xdrawt;         // snowball draw (true=1)   // CS11
        unsigned char   drefIdxbu;      // reference file entry     // CS11
    };

// lottery start sell, no more data log
// lottery stop sell, no more data log
// lottery close, no more data log
// lottery collation final, no more data log

struct  LOGRDCLDD       // change of lottery draw date
    {
        __time32_t          nddate;         // new draw date
    };

struct  LOGRDCLOD       // change of lottery opening date
    {
        __time32_t          nodate;         // new lottery opening date
    };

struct  LOGRDCLCD       // change of lottery closing date               // JC02..
    {
        __time32_t          ncdate;         // new closing date(same date > 24:00) //  CS11
        __time32_t          ncdattim;       // new closing date time(next date&time > 24:00) // CS11
        char            reopenb;        // 1= function for re-open draw
    };

//struct  LOGRDCLCT       // change of lottery closing time               // CS11..           
//    {
//        __time32_t          ncdate;         // new lottery closing date time
//        unsigned short  ctimewu;        // new lottery closing time in hhmm
//        char            reopenb;        // 1= function for re-open draw // ..CS11
//    };                                                                  // ..JC02

struct  LOGRDCLRES      // lottery result
    {
        unsigned short  noswu[LOT_MAXDNO];      // drawn no.+extra no.
    };

struct  LOGRDCLPRZ      // lottery prize
    {
        unsigned char       gtypbu;             // cc game type
        LONGLONG            przd[LOT_MAXPRZ_CUR];   // prize value  -1=overflow // JC06
        struct LOTPZSTS     sts[LOT_MAXPRZ_CUR];    // prize status             // JC06
    };  

struct LOGRDCPRZSTS     // stop pay/claim/cancel claim lottery prize
    {
        unsigned char   gtypbu;         // cc game type
        short           pznow;          // prize id(s) bitmap 
    };

struct LOGRDCLWPS       // winner pass request from RWCC
    {
        unsigned short  numwu[LOT_MAXDNO];        // result; numwu[0]=unused
    };

// PARAMETER OPTION


struct  LOGRDCRWI       // race close warning interval
    {
        unsigned short  intwu;      // new interval (in min.)
    };

struct  LOGRDCMBV       // max. bet value
    {
        unsigned LONGLONG  mbvdu;   // max. bet value (in cents)
        unsigned LONGLONG  micvdu;  // max. manuaL issue cv (in cents)
        unsigned LONGLONG  esccvdu; // max. esc cv (in cents)
        unsigned LONGLONG  svtcvdu; // max. auto svt cv (in cents)
        unsigned LONGLONG  optcvdu; // max. auto opt cv (in cents)
    };

struct  LOGRDCAFE       // allup enabling
    {
        unsigned int    enable1:1;      // enable indicator
        unsigned int    :15;            // unused
    };

struct  LOGRDCAFM       // allup formula enabling
    {
        BOOL   enabu[RDS_MAXAPOOL][RDS_MAXAFML];   // enable flag
    };

struct  LOGRDCAWL       // all up re-investment warning limit
    {
        unsigned LONGLONG   aupdu;      // warning limit (in cents)
    };

struct  LOGRDCPAYL      // pay limit
    {
        unsigned LONGLONG   hodu;       // pay at ho limit (in cents) 
        unsigned LONGLONG   ocdu;       // pay at original ctr limit(cents)
    };

struct LOGRDCLBS        // lottery bad sale expired
    {
        unsigned short  bsiwu;          // bad sale expired (in sec)
    };

struct LOGRDCLCI        // lottery close warning internal
    {
        unsigned short  cwiwu;          // close warning int.(in min)
    };

struct LOGRDCLMS
    {
        unsigned short  selbaswu;       // base selection number
        unsigned short  selmaxwu;       // maximum selection number
        unsigned short  gblbaswu;       // base goldball number
        unsigned short  gblmaxwu;       // maximum goldball number
    };

struct LOGRDCLBA
    {
        unsigned int    amtlu;          // lottery base investment
    };

struct  LOGRDCLRPT       // lottery report request
    {
        unsigned char   idbu;           // report id, refer rpbdef.h
    };

struct  LOGRDCTBD       // tb deposit parameters
    {
        unsigned LONGLONG   amtdu;      // min. deposit amt (in cents)
        unsigned short      stimwu;     // start time in 4 sec.
        unsigned short      etimwu;     // end time in 4 sec.
    };

struct  LOGRDCTBW       // tb (EFT) withdrawal parameters
    {
        unsigned LONGLONG   mindu;      // min. withd. amt (in cents)
        unsigned LONGLONG   maxdu;      // max. per day (in cents)
        unsigned short      cntwu;      // max. withd. count per day
        unsigned short      dohwu;      // dep on hold time in min. 
    };

struct LOGRDCDSA        // disable all-up betting by race   // JC10
    {
        unsigned int    dsalu;          // disable aup betting bitmap
                                        // ( bit 1 => race 1 ...)
    };

struct LOGRDCEAB        // enable/disable all up betting
    {
        unsigned int    ena1:1;         // enable indicator
        unsigned int    :15;            // unused
    };

struct LOGRDCEDB        // enable/disable deposit betting
    {
        unsigned int    ena1:1;         // enable indicator
        unsigned int    :15;            // unused
    };

struct  LOGRDCNBD       // next business date
    {
         __time32_t         dat;            // date
    };

struct  LOGRDCPMC       // peak hour minimum cost
    {
        unsigned int    cblu;           // cb in $
    };

struct  LOGRDCEFT       // eft cv min
    {
        unsigned int    rdlu;           // raceday in $
        unsigned int    nrdlu;          // non-raceday in $
    };

struct  LOGRDCLBV_ENT                   // JC07..
    {
        unsigned char       betTypebu;
        unsigned LONGLONG   amtdu;
    };

struct  LOGRDCLBV       // large bet W/P/Q/QPL/TCE
    {
        unsigned char           numbu;
        struct  LOGRDCLBV_ENT   ent[LOGRDC_MAX_ENT];
    };                                  // ..JC07

struct  LOGRDCLDV       // large div [] refer BETTYPDEF.H, e.g. BETYPE_STD for std
    {
        unsigned LONGLONG ldvdu[LOGRDC_LRGDIV_NOPOOL];// large div.in $
    };

struct  LOGRDCAEN       // Concurrent Game Enable/Disable Flag
    {
        BOOL              enat;         // enable(1), disable(0) flag
    };

//struct  LOGRDCABE       // Concurrent Game Unit Bet Value
//    {
//        unsigned short    ubvwu;        // unit bet value (in $)
//    };
  
struct  LOGRDCAPR       // Concurrent Game Default Prize
    {
        unsigned LONGLONG dpvdu;        // default prize value 
                                        // in cents per $ of investment
    };

struct  LOGRDCCCDED     // Concurrent Game Deductions
    {
        unsigned short    taxwu;        // % tax deduction (in % *100)
        unsigned short    comwu;        // % commission deduction (in %*100)
        unsigned short    fundwu;       // % fund deduction (in %*100)
    };

struct  LOGRDCRCLW       // race close warning
    {
        unsigned short  hourwu;         // hour
        unsigned short  minwu;          // minute
        unsigned int    onc1:1;         // on-course indicator
        unsigned int    ofc1:1;         // off-course indicator
        unsigned int    :14;            // unused
    };

struct  LOGRDCRRPT       // racing report request
    {
        unsigned char   idbu;           // report id, refer rpbdef.h
    };

// since the unit bet and min. total cost kept in rdscom is by bet type,
// the pool id in header of this message is kept for the bet type instead
// i.e. 0=W-P, 1=WIN, 2=PLA...
struct  LOGRDCPUMIN      // partial unit bet minimum cost   // JC01..
    {
        unsigned int    unitlu;         // partial unit bet in $
        unsigned int    costlu;         // minimum total cost amount in $
    };                                                      // ..JC01

struct  LOGRDCLCLW       // lottery close warning
    {
        unsigned short  hourwu;         // hour
        unsigned short  minwu;          // minute
    };

struct LOGRDCCVEC       // CV encashment checking       // JC05
{
    BOOL                        enat;       // checking enable flag
    unsigned LONGLONG           amtdu;      // remaining amount
    unsigned short              percwu;     // % used for betting
};

struct LOGRDCLSCMTG_ENT                                                 // JC07..
{
    unsigned char           tierbu;                 // tier id
    unsigned char           chanbu;                 // channel id, AB or CB
    BOOL                    enat;                   // enable flag
    unsigned LONGLONG       amtdu;                  // amount in cents
};

// for struct LOGRDCLSCMTG, if corresponding meeting index >= RDS_MAXMEET,
// the message is for the global change on external branch enabing,
// there should be no more data for tier/channel, i.e. numbu == 0
// WCHNDR will update the global external branch enabling to each defined meeting.
struct LOGRDCLSCMTG                                 // losing inv con ctl - meeting
{
    BOOL                    enat;                   // enable flag for external branches
    unsigned char           numbu;                  // # of tier
    struct LOGRDCLSCMTG_ENT ent[LOGRDC_MAX_ENT];    // by tier by channel data
};

struct LOGRDCLSCRCE_ENT
{
    unsigned char           racebu;                 // race #
    BOOL                    enat;                   // enable flag
};

struct LOGRDCLSCRCE                                 // losing inv con ctl - race
{
    unsigned char           chanbu;                 // channel id, AB or CB
    unsigned char           numbu;                  // # of entry
    struct LOGRDCLSCRCE_ENT ent[LOGRDC_MAX_ENT];    // by race by channel  
};

struct LOGRDCLSCPOL_ENT
{
    unsigned char           tierbu;                 // tier id
    unsigned char           poolbu;                 // pool id
    unsigned short          percwu;                 // % * 100
};

struct LOGRDCLSCPOL                                 // losing inv con ctl - pool
{
    unsigned char           chanbu;                 // channel id, AB or CB
    unsigned char           numbu;                  // # of entry
    struct LOGRDCLSCPOL_ENT ent[LOGRDC_MAX_ENT];    // by tier by pool data
};

struct LOGRDCLMER                                   // draw merge    // CS11..
{
    unsigned char              masteridxbu;        // draw index of master draw 
    unsigned char              slaveidxbu;         // draw index of slave draw 
};                                                                   // ..CS11

union   LOGRDCD         // log data
    {
        struct LOGRDCMSCH       msch;       // meeting schedule
        struct LOGRDCSPSTT      spstt;      // change sell/ pay status
        struct LOGRDCSUB        sub;        // subsitute
        struct LOGRDCSCR        scr;        // scratching
        struct LOGRDCRES        res;        // result
        struct LOGRDCPTT        ptt;        // change post time
        struct LOGRDCDSA        dsa;        // disable all-up betting by race   // JC10
        struct LOGRDCEAB        eab;        // enable ext branch lossing consolation // JC07
        struct LOGRDCRAD        rad;        // pool rad/claim details input
        struct LOGRDCRCW        rcw;        // race close interval
        struct LOGRDCBSE        bse;        // bad sale expire
        struct LOGRDCRWI        rwi;        // race close warning interval
        struct LOGRDCAFE        afe;        // allup enabling
        struct LOGRDCAFM        afm;        // allup formula enabling
        struct LOGRDCAWL        awl;        // all up re-investment warning limit
        struct LOGRDCMBV        mbv;        // max. bet value
        struct LOGRDCPAYL       payl;       // payout limit
        struct LOGRDCTBD        tbd;        // tb deposit parameters
        struct LOGRDCTBW        tbw;        // tb (EFT) withdrawal parameters
        struct LOGRDCEDB        edb;        // enable/disable deposit betting
        struct LOGRDCEFT        eft;        // eft cv min
        struct LOGRDCNBD        nbd;        // next business date
        struct LOGRDCPMC        pmc;        // peak hour minimum cost
        struct LOGRDCLBV        lbv;        // large bet warning value
        struct LOGRDCLDV        ldv;        // large div warning value
        struct LOGRDCRCLW       rclw;       // race close warning
        struct LOGRDCRRPT       rrpt;       // racing report request
        struct LOGRDCPUMIN      pumin;      // partial unit minimum cost    // JC01
        struct LOGRDCLCLW       lclw;       // lottery close warning
        struct LOGRDCLSCH       lsch;       // lottery schedule
        struct LOGRDCLDD        ldd;        // change draw date
        struct LOGRDCLOD        lod;        // change openning date
        struct LOGRDCLCD        lcd;        // change closing date
//        struct LOGRDCLCT        lct;        // change closing time // CS11
        struct LOGRDCLRES       lres;       // lottery result
        struct LOGRDCLPRZ       lprz;       // lottery prizes
        struct LOGRDCPRZSTS     lpsts;      // change prizes status
        struct LOGRDCLWPS       lwps;       // winner pass request from RWCC
        struct LOGRDCAEN        aen;        // ccgame enabling
//        struct LOGRDCABE        abe;        // ccgame unit investment
        struct LOGRDCAPR        apr;        // ccgame prizes amount
        struct LOGRDCLBS        lbs;        // lottery bad sale expire
        struct LOGRDCLCI        lci;        // lottery close warning interval
        struct LOGRDCLMS        lms;        // lottery selection range
        struct LOGRDCLBA        lba;        // lottery unit investment
        struct LOGRDCLRPT       lrpt;       // lottery report request
        struct LOGRDCCVEC       cvec;       // CV encashment checking       // JC05
        struct LOGRDCLSCMTG     lscmtg;     // losing inv con ctl - meeting     // JC07
        struct LOGRDCLSCRCE     lscrce;     // losing inv con ctl - race        // JC07
        struct LOGRDCLSCPOL     lscpol;     // losing inv con ctl - pool        // JC07
        struct LOGRDCLMER       lmer;       // snowball merge       // CS11
  };

struct  LOGRDCIDR       // racing id
    {
        unsigned short  indexwu;        // meeting index
        unsigned short  racewu;         // race #
        short           poolw;          // JN08 for message(307), stop sell pools in a race 
                                        //      pool id, all pools =0, win/pla/qin/qpl = 1  
                                        //      for other message, pool id define refer to RDSDEF.H
        __time32_t          mdate;          // meeting date
        unsigned char   locbu;          // location
        unsigned char   daybu;          // day
    };

struct  LOGRDCIDL       // lottery id
    {
        unsigned short  yearwu;         // year
        unsigned short  drawwu;         // draw
        unsigned short  typewu;         // lottery type         // lottery type, e.g. MK6/ GBL
        unsigned char   typbu;          // cc game type         // ccgame, e.g. NOR, AON
        unsigned char   subtbu;         // cc game sub type     // subgame, e.g. OUG10
        unsigned char   idxbu;          // lottery index
        unsigned char   sidxbu;         // slave draw index=draw index+1, 0=unused // CS11 
        unsigned short  sdrawwu;        // slave draw no. // CS11
    };

//struct  LOGRDCIDCC      // concurrent game id
//    {
//        unsigned char           idbu;   // cc game id
//        unsigned char           typbu;  // cc game type     // NORMAL/CCGAMES
//        unsigned char           subtbu; // cc game sub type
//    };

union   LOGRDCID
    {
        struct LOGRDCIDR  r;
        struct LOGRDCIDL  l;
//        struct LOGRDCIDCC c;
    };

struct  LOGRDC          // log message
    {
		unsigned __int64	actid;		// activity id
        unsigned int    msnlu;      // msn
        unsigned short  callerbu;   // WC/RWCC
        unsigned short  funcodewu;  // rdc function code
        union LOGRDCID  i;
        union LOGRDCD   d;
    };

#pragma pack(1)

#endif
