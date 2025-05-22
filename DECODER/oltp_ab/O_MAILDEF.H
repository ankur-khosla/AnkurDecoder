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
//      O_MAILDEF.H - mail defines for compatability with old mail format
//
//      Author:         Leonard Yau
//
//      Date:           12 DEC 2000
//
//      Mod.:           FT01        30-JAN-2002           
//                      Add Mark 6 prize 7
//              
//                      JC02        09-MAY-2002
//                      include exw & ltw reply & winner list for get size
//                      of mail box concerned
//          
//                      JC03        10-MAY-2002
//                      A new header file mailrwccdef.h is used to define
//                      the mail structures to be received by RWCC. 
//                      
//                      PN04        16-AUG-2002
//                      Change variable name according to coding standard
//
//                      FT05        12-SEP-2002
//                      add msg O_MAIL_RINWARN allup reinvestment threshold
//
//                      JC06        16-DEC-2002
//                      include error code in rdc ack to WC
//
//                      VC07        15-AUG-2003
//                      add old message format for DEPHNDR
//                      add old message defines for DEPHNDR
//
//                      FT08        23-SEP-2004
//                      - change D-T/T-T pseudo collation field size from
//                        I2 to I4 for Q105 release
//                      PN09        20-OCT-2004
//                      ( remove unused defines )
//                      PN10        20-SEP-2005
//                      ( remove unused defines )
//
//                      FT11        22-SEP-2005
//                      - add randomly generated indicator to lottery & exotic
//                        winner list (Q106)
//
//                      FT12        11-NOV-2005
//                      - use new mail header for all msg with WC in Q206 
//                        ( add error code at end of header)
//                        For lottery, this error code is a dummy field only
//                        in Q206 since the interface between WC & OLTP will 
//                        not change until Q306 )
//
//                      JC13                22-FEB-2006
//                      remove struct MAILWCLLCOLQ as WCHNDR will use same
//                      structure as from WC for unsol. col. request 
//
#ifndef O_MAILDEF_H

#define O_MAILDEF_H 1

#include "udtypedef.h"
#include "rdsdef.h"
#include "mailhdrdef.h"
#include "mailcoldef.h"
#include "logdef.h"

#define O_RDS_MAXLEG 6
#define O_RDS_MAXRES 4
#define O_RDS_MAXDH 3
#define O_RDS_MAXPSUB 12
#define O_RDS_SELSIZ 6
#define O_RDS_MAXDIV 15
#define O_RDS_MAXWCSIZ 6
#define O_RDS_MAXFLD 14

#define O_LOT_MAXPRZ            7           // max prize of mk6     FT01
#define O_LOT_ODDEVEN_INVD      6           // no of types of odd even game
#define O_LOT_MATCH_INVD        3           // no of types of matching game
#define O_LOT_OUTSIDER_INVD     6           // no of types of outsider game
#define O_LOT_NODNO             6           // no of normal no
#define O_LOT_NOENO             1           // no of extra no

// Mark 6 / Powerball winning investment
#define O_LOT_PRZ_NOR1          0           // winning investment 1
#define O_LOT_PRZ_NOR2          1           // winning investment 2
#define O_LOT_PRZ_NOR3          2           // winning investment 3
#define O_LOT_PRZ_NOR4          3           // winning investment 4
#define O_LOT_PRZ_NOR5          4           // winning investment 5
#define O_LOT_PRZ_NOR6          5           // winning investment 6
#define O_LOT_PRZ_NOR7          6           // winning investment 7     FT01

// Odd even game winning investment
#define O_LOT_PRZ_OEG2          0           // odd even 2 row winnng investment
#define O_LOT_PRZ_OEG3          1           // odd even 3 row winnng investment
#define O_LOT_PRZ_OEG4          2           // odd even 4 row winnng investment
#define O_LOT_PRZ_OEG5          3           // odd even 5 row winnng investment
#define O_LOT_PRZ_OEG6          4           // odd even 6 row winnng investment
#define O_LOT_PRZ_OEG7          5           // odd even 7 row winnng investment

// Matching game winning investment
#define O_LOT_PRZ_MHG1          0           // match 1 winning investment
#define O_LOT_PRZ_MHG2          1           // match 2 winning investment
#define O_LOT_PRZ_MHG3          2           // match 3 winning investment

// Outsider game winning investment
#define O_LOT_PRZ_OUG10         0           // outsider 10 winning investment
#define O_LOT_PRZ_OUG11         1           // outsider 11 winning investment
#define O_LOT_PRZ_OUG12         2           // outsider 12 winning investment
#define O_LOT_PRZ_OUG13         3           // outsider 13 winning investment
#define O_LOT_PRZ_OUG14         4           // outsider 14 winning investment
#define O_LOT_PRZ_OUG15         5           // outsider 15 winning investment

#define O_MAIL_EXW_MAXWIN 10
#define O_MAIL_EXW_WINSIZ O_RDS_MAXDIV * 20
#define O_MAIL_EXW_TRICOLSIZ 364
#define O_MAIL_EXW_MAXCBL 4
#define O_MAIL_EXW_MAXWCOM    O_RDS_MAXDIV * O_RDS_MAXWCSIZ * O_MAIL_EXW_MAXCBL

#define O_MAIL_COL_MAXDBLSZ   O_RDS_MAXFLD*O_RDS_MAXFLD
#define O_MAIL_COL_MAXQPPSZ   O_RDS_MAXFLD*(O_RDS_MAXFLD-1)/2
#define O_MAIL_COL_MAXTRISZ   O_RDS_MAXFLD*(O_RDS_MAXFLD-1)*(O_RDS_MAXFLD-2)/6
#define O_MAIL_COL_MAXCOLSIZ  2*O_RDS_MAXFLD + 2*O_MAIL_COL_MAXQPPSZ + \
                              O_MAIL_COL_MAXTRISZ

#define O_EXW_ERRMSGLEN 16

#define O_CTRSIZ        16      // size of centre / account # in text

enum RPYTYPE {RPY6UP = 0, RPYWIN, RPYQIN, RPYTRI, RPYWINLIST, RPYEXOWIN};

#pragma nomember_alignment

//*******************************************************************
// 
// Header structure
//
//*******************************************************************

struct O_MAILHDR
{
  unsigned short        tidwu;  // transaction id
  unsigned char         srcbu;  // source system #
  unsigned char         desbu;  // destination system #
};


//*******************************************************************
//
// Lottery winner pass structures
//
//*******************************************************************

struct O_LOTDNOM
{
    unsigned char               offbu;      // bitmap offset
    unsigned char               mapbu;      // bitmap
};

struct O_MAILLWPQ                           // lotter winner pass request
{
    unsigned short              yearwu;     // year                  
    unsigned short              drawwu;     // draw #
    struct O_LOTDNOM            map[O_LOT_NODNO+O_LOT_NOENO];
                                            // draw result
};

struct O_LWPD                               // lottery winner pass reply detail
{
    double                  invr;           // total investment
    double                  wininvr[O_LOT_MAXPRZ];
                                            // winning investments
    unsigned short          drawnwu[O_LOT_NODNO+O_LOT_NOENO];
                                            // drawn numbers
    unsigned short          dummywu;        // unused 
    double                  tktsoldr;       // ticket sold

    double                  addon_invr;     // add on game investment
    double                  oddeven_invr[O_LOT_ODDEVEN_INVD];
                                            // odd-even game investments
    double                  match_invr[O_LOT_MATCH_INVD];
                                            // matching game investments
    double                  extra_invr;     // extra number game investment
    double                  outsider_invr[O_LOT_OUTSIDER_INVD];
                                            // outsider game investments
    char                    dummy1b[80];    // unused
    double                  addon_wininvr;  // add on game winning investment
    double                  oddeven_wininvr[O_LOT_ODDEVEN_INVD];
                                            // odd-even winning investments
    double                  match_wininvr[O_LOT_MATCH_INVD];
                                            // match winning investments                                            
    double                  extra_wininvr;  // extra number winning investment
    double                  outsider_wininvr[O_LOT_OUTSIDER_INVD];
                                            // outsider winning investments
    char                    dummy2b[88];    // unused
};


union O_MAILLWPBODY                         // Lottery winner pass reply body
{
    struct O_LWPD           data;           // normal reply data      
    unsigned short          errorcodewu;    // error code
};


struct O_MAILLWPP                           // lottery winner pass
{
    unsigned char           yearbu;         // year
    unsigned char           unsol1:1;       // unsolicited
    unsigned char           error1:1;       // error
    unsigned char           final1:1;       // final
    unsigned char           :5;             // unused
    unsigned short          drawwu;         // draw #
    union O_MAILLWPBODY     lwpbody;        //
};

struct O_MAILLWL                            // lottery winner list
{
    unsigned short              yearwu;     // year
    unsigned short              drawwu;     // draw number
    unsigned short              reqidwu;    // request ID
    BOOL                        randt;      // randomly generated ! FT11
    char                        cas[O_CTRSIZ];    // center / account #
    int                         binvlu;     // base investment
    char                        bets[MAIL_BETSIZE];
                                            // acsii bet line
};

union O_MAIL_LOTWPS_REQ_BODY
{
    struct O_MAILLWPQ       ltw;       // lottery winner pass request
    struct O_MAILLWPP       lwp;       // lottery winner pass
    struct O_MAILLWL        lwl;       // lottery winner list    
};


struct O_MAIL_LOTWPS                    // lottery request
{
    struct  MAILHDR                hdr;    // message header        ! FT12
    union   O_MAIL_LOTWPS_REQ_BODY body;    // message body
};

struct O_MAIL_LTWREQ
{
    struct MAILHDR          hdr;       // header                    ! FT12
    struct O_MAILLWPQ       ltw;       // lottery winner pass request
};

struct O_MAIL_LTWRPY                    // lottery winner reply
{
    struct MAILHDR          hdr;        // header                   ! FT12
    struct O_MAILLWPP       lwp;        // lottery winner reply body
};

struct O_MAIL_LTWWIN                    // lottery winner reply
{
    struct MAILHDR          hdr;        // header                   ! FT12
    struct O_MAILLWL        lwl;        // lottery winner reply body
};

//*******************************************************************
//
// Exotic winner pass structure
//
//*******************************************************************
struct  O_MAILEWPQ      // exotic winner pass request
{
    unsigned char       locbu;              // location
    char                dayb;               // day
    unsigned char       racebu;             // race
    unsigned char       poolbu;             // pool
    unsigned short      reswu[O_RDS_MAXLEG][O_RDS_MAXRES];  // result bitmap
    unsigned char       subbu[O_RDS_MAXPSUB];       // substitutes, # legs x sub. r 
    unsigned short      nstwu[O_RDS_MAXLEG];        // non-starter bitmap
    unsigned char       legbu;              // # of legs completed
    unsigned char       colbu;              // pseudo collation flag (on: 1; off:0)
    unsigned char       cblbu;              // total no. of count back level
    unsigned char       nwcbu[O_MAIL_EXW_MAXCBL]; 
                            // no. of winning combination for each count back level
    unsigned short      wcwu[O_MAIL_EXW_MAXWCOM]; 
                        // winning combination bitmap (wc) for all 
                        // count back levels (cbl)
                        // It is vaiable in size, depending on pool
                        //   it should be accessed as :
                        //     { { m byte   // wc bitmaps for cbl i
                        //                  // the size of each wc depends on pool
                        //       } repeat for nwcbu[i] times  
                        //     } repeat for cblbu times  
};

struct  O_MAILEWPPWIN   // exotic winner reply winning info
{
    double              winvr;              // winning investment
    unsigned short      comwu[O_RDS_MAXWCSIZ];//winning comb. bitmap
                                            // variable size depending on pool
};

struct  O_MAILEWPP      // exotic winner pass reply
{
    unsigned char       locbu;              // location
    char                dayb;               // day
    unsigned char       racebu;             // race #
    unsigned char       poolbu;             // pool
    unsigned char       cblbu;              // countback level
    unsigned char       unsol1:1;           // unsolicited
    unsigned char       error1:1;           // error
    unsigned char       final1:1;           // final
    unsigned char       :5;                 // unused
    unsigned char       numbu;              // # of winning combinations
    unsigned char       dummy1bu;           // unused byte
    unsigned short      scrwu;              // scratching bitmap (for TCE/QTT only)
    unsigned short      errwu;              // error code
    double              invr;               // total gross investment ($)
    double              rfdr;               // refund ($)
    unsigned char       clegbu;             // # of legs completed
    unsigned char       dummy2bu;           // unused byte
    char                winb[O_MAIL_EXW_WINSIZ];    
                            // byte array of winning inv. & win. comb. bitmap
                            // used struct O_MAILEWPPWIN to access this array
             
};

struct  O_MAILEWMISWLD                      // exotic winner details
{
    BOOL                randt;                  // randomly generated ! FT11
    int                 binvl;                  // base investement ($)
    char                cas[O_CTRSIZ];          // centre/account #
    unsigned short      selwu[O_RDS_SELSIZ];    // selection bitmap
};

struct  O_MAILEWMISWL                       // exotic winning misc info
{
    unsigned int        numlu;              // # of winners
    struct O_MAILEWMISWLD win[O_MAIL_EXW_MAXWIN];
};

struct  O_MAILEWMISWC                       // exotic winner collation
{
    double              totr;               // total winning
//  short               colw[O_MAIL_EXW_TRICOLSIZ];     // collation area PN04
    unsigned int        collu[O_MAIL_EXW_TRICOLSIZ];    // collation area FT08
};

struct  O_MAILEWMIS6UP                      // 6up exotic winner info
{
    double              totr;               // total winning
    unsigned int        collu[O_RDS_MAXFLD];
};

union   O_MAILEWMISD                        // exotic winner misc. info detail
{
    struct O_MAILEWMISWL    wl;             // winner list
    struct O_MAILEWMISWC    c;              // winning collation
    struct O_MAILEWMIS6UP   s[2];           // 6up winning [0 6win, 1 6up]
};


struct  O_MAILEWMIS                         // exotic winner misc. info
{
    unsigned char           locbu;          // location             
    char                    dayb;           // day
    unsigned char           racebu;         // race #
    unsigned char           poolbu;         // pool
    unsigned char           resbu[O_RDS_MAXLEG][O_RDS_MAXRES][O_RDS_MAXDH]; // result
    unsigned short          subwu[O_RDS_MAXPSUB];     // substitutes bitmaps
    unsigned short          scrwu[O_RDS_MAXLEG];      // scratching bitmaps
    unsigned char           clegbu;         // # of legs completed
    union O_MAILEWMISD      d;
};


union O_MAIL_EXOWPS_REQ_BODY            // exotic winner pass request message body
{
    struct O_MAILEWPQ       exw;        // exotic winner pass request 
    struct O_MAILEWPP       exp;        // exotic winner pass reply
    struct O_MAILEWMIS      ewi;        // exotic winner misc. info    
};

struct  O_MAIL_EXOWPS                   // exotic winner pass request
{
    struct O_MAILHDR    hdr;                // mail header, no changes
    union O_MAIL_EXOWPS_REQ_BODY body;  // message body 
};

struct O_MAIL_EXWREQ                    // exotic winner request
{
    struct O_MAILHDR        hdr;
    struct O_MAILEWPQ       exw;        // request body
};

struct O_MAIL_EXWRPY                    // exotic winner reply
{
    struct O_MAILHDR        hdr;
    struct O_MAILEWPP       exp;        // reply body
};

struct O_MAIL_EXWWIN                    // exotic winner list
{
    struct O_MAILHDR        hdr;
    struct O_MAILEWMIS      ewi;        // winner list body
};

//*******************************************************************
//
// COLHNDR structure
//
//*******************************************************************
struct O_MAILCOLFIN
{
  unsigned char         colw1:1;        // win pool final
  unsigned char         colp1:1;        // pla pool final
  unsigned char         colq1:1;        // qin pool final
  unsigned char         colqp1:1;       // qpl pool final
  unsigned char         colt1:1;        // trio pool final
  unsigned char         cole1:1;        // exotic pool final
  unsigned char         colpr1:1;       // last race prp done
  unsigned char         :1;     
};

struct O_MAILACOLFIN
{
  unsigned char         acolfi6:6;      // all collation final
  unsigned char         :2;
};

union O_MAILFINSTS
{
  struct O_MAILCOLFIN   fin;            // collation final
  struct O_MAILACOLFIN  afin;           // all collation final
  unsigned char         finbu;          
};

struct O_MAILPBIT
{
  unsigned char         win1:1;         // win pool
  unsigned char         pla1:1;         // pla pool
  unsigned char         qin1:1;         // qin pool
  unsigned char         qpl1:1;         // qpl pool
  unsigned char         tri1:1;         // trio pool
  unsigned char         exo1:1;         // exotic pool includes all pools 
                                        // except win, pla, qin, qpl & trio
  unsigned char         pspare:2;       // unused 
};

union O_MAILPOLBIT
{
  struct O_MAILPBIT     pbit;
  unsigned char         pbitbu;
};

struct O_MAILRSTS
{
  unsigned char         unso1:1;        // reply status - unsolicited msg
  unsigned char         err1:1;         // reply status - error
  unsigned char         fin1:1;         // reply status - final
  unsigned char         :5;             // unused
};

union O_MAILRPYSTS
{
  struct O_MAILRSTS     rsts;           // reply status
  unsigned char         rstsbu; 
}; 

union O_MAILERRSTS
{
  unsigned short        codwu;          // error code
  double                normr;          // normal
};


struct O_MAILWCLNKP      // link test reply
{
    struct O_MAILHDR      hdr;          // mail header
    unsigned short        error1:1;     // error
    unsigned short        :7;           // unused
};

struct  O_MAILWCRCOLP    // race collation reply
{
  struct O_MAILHDR      hdr;            // mail header
  char                  locb;           // location
  char                  dayb;           // day
  unsigned char         racebu;         // race number
  unsigned char         fsizbu;         // field size
  union O_MAILPOLBIT    polbit;         // pool bitmap
  union O_MAILFINSTS    colsts;         // final collation status
  union O_MAILRPYSTS    rpysts;         // reply status
  unsigned char         errbu;          // error code (RMERRDEF.H)
  double                chktotr;        // checksum for pool totals  
                                        // (sum of 13 pools+2 refund totals)
  double                poltotr[13];    // pool total (13 pool totals
  double                rfdtotr[2];     // refund total (tce+qtt)
  unsigned short        scrwu[2];       // scratching bitmap (tce+qtt)
  unsigned int          scollu[O_MAIL_COL_MAXCOLSIZ]; // pool collation
                        // the investments (in $) for win, pla, qin, qpl 
                        // and tri pool. The pool start offset:
                        // win = 0
                        // pla = win + fldsiz
                        // qin = pla + fldsiz 
                        // qpl = qin + fldsiz*(fldsiz-1)/2
                        // tri = qpl + fldsiz*(fldsiz-1)/2
                        // if pool not defined, zero offset will be added
};

struct  O_MAILWCDBCOLP    // double collation reply
{
  struct O_MAILHDR      hdr;            // mail header
  char                  locb;           // location
  char                  dayb;           // day
  unsigned char         racebu;         // race number
  unsigned char         fstfsizbu;      // 1st leg field size
  unsigned char         sndfsizbu;      // 2nd leg field size
  union O_MAILFINSTS    colsts;         // final collation status
  union O_MAILRPYSTS    rpysts;         // reply status
  unsigned char         errbu;          // error code (RMERRDEF.H)
  double                poltotr;        // double pool total 
  unsigned int          scollu[O_MAIL_COL_MAXDBLSZ]; // double collation
                        // the investments (in $) for dbl only 
};

struct  O_MAILWCLCOLP      // lottery collation reply
{
  struct MAILHDR        hdr;            // mail header !FT12
  unsigned char         dyrbu;          // draw year (yy)
  union O_MAILRPYSTS    rpysts;         // reply status
  unsigned short        dnowu;          // draw no.
  union O_MAILERRSTS    errsts;         // error code (if error reply)
                                        // 2b if err reply, 8b if normal
  double                exdiv1r;        // mk6/add-on expired dividend
  double                exdiv2r;        // even-odd chain expired div.
  double                exdiv3r;        // one-two-three chain exp.div.
  double                exdiv4r;        // extra-no chain expired div.
  double                exdiv5r;        // outsiders chain expired div.
  double                inv1r;          // mk6 total investment
  double                inv2r;          // add-on-game investment
  double                inv3r;          // even-odd chain investment
  double                inv4r;          // one-two-three investment
  double                inv5r;          // extra-number investment
  double                inv6r;          // outsiders investment 
};

struct  O_MAILWCARINP      // allup reinvestment w/p/q/qp/tri reply
{
  struct O_MAILHDR      hdr;            // mail header
  char                  locb;           // location
  char                  dayb;           // day
  unsigned char         racebu;         // race number
  unsigned char         fsizbu;         // field size
  union O_MAILPOLBIT    polbit;         // pool bitmap
  unsigned char         errbu;          // err code,0=no error(RMERRDEF.H)
  unsigned short        sparewu;        // spare
  unsigned int          scollu[O_MAIL_COL_MAXCOLSIZ]; // pool collations
};

struct  O_MAILWCEWPA      // exotic winner ackowledgement
{
  struct O_MAILHDR        hdr;            // mail header
  char                  locb;           // location
  char                  dayb;           // day (-ve for refund pass)
  unsigned char         racebu;         // race number
  unsigned char         pcodbu;         // pool code
};

struct  O_MAILWCLWPA       // lottery winner ackowledgement
{
  struct MAILHDR        hdr;            // mail header !FT12
  unsigned short        dyrwu;          // draw year(yy)
  unsigned short        dnowu;          // draw no.
};

union O_MAIL_COLHNDR_BODY     
{
  struct MAILWCRCOLQ    rcolreq;        // race collation request
  struct MAILWCLCOLQ    lcolreq;        // lottery collation request
  struct MAILWCUNSRQ    unsreq;         // race status request
//  struct MAILWCLLCOLQ   unslotreq;      // lottery status request // JC13
  struct O_MAILEWPQ       exwreq;         // exotic winner pass request 
  struct O_MAILLWPQ       ltwreq;         // lottery winner pass request
};

//*******************************************************************
//
// AUPPSS structures
//
//*******************************************************************

struct O_MAIL_RINWARN          // allup reinvestment threshold
{
    struct O_MAILHDR        hdr;    // header
    unsigned char           locbu;  // meeting location
    unsigned char           daybu;  // meeting day
    unsigned char           racbu;  // race number
    unsigned char           unusedbu;
    unsigned short          reqwu;  // request id
    double                  amtr;   // amount (-ve=cancel/0=overflow)
    char                    dtls[100]; // bet details
                                       // the max. length of details is limited
                                       // to 100 in WC database
};

//*******************************************************************
//
// Reply message structures
//
//*******************************************************************

struct O_MAIL_COLHNDR
{
  struct MAILHDR               hdr;    // mail header !FT12
  union  O_MAIL_COLHNDR_BODY   body;   // message body
};

struct O_MAIL_WC_ACK            // rdc request ack. to WC
{
  short                     msnw;   // msn
  unsigned short            errorCodewu;        // error code   // JC06
};

struct O_MAIL_WC_ERR            // rdc request error reply to WC
{
  short                     filler;         // no use
  char                      errMsg[80];     // error message
};

union O_MAIL_WC_REPLY_BODY
{
  struct O_MAIL_WC_ACK      ack;
  struct O_MAIL_WC_ERR      err;
};

struct O_MAIL_WC_REPLY
{
  struct O_MAILHDR              hdr;        // mail header
  union O_MAIL_WC_REPLY_BODY    body; 
};

#endif
