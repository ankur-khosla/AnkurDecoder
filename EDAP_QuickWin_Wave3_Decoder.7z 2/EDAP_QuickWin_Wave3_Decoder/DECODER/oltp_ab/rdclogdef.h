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
//    Mod :     JC01        03-MAY-2002
//              add new tid (208) for simplified exotic winner
//              request from RWCC 

#ifndef   RDCLOGDEF_H

#define   RDCLOGDEF_H 1

// RDCLOG.H -- "RDCLOG.DAT" logger message format

// the file is updated sequentially on-line and contain a trace of all
// transactions within the system.  It is used to restore the system to
// a correct state after failure and purged at end of day process.

// Message codes
//
// RDC request from WC
#define RDCLOG_MTGINP   1       // new meeting schedule
#define RDCLOG_MTGRCE   22      // new race schedule
#define RDCLOG_MTGRCC   15      // race close interval
#define RDCLOG_PARRCW   81      // race close warning interval
#define RDCLOG_MTGBSC   20      // change of bad sale interval
#define RDCLOG_MTGSRS   16      // start sell all pools in a meeting
#define RDCLOG_MTGSPS   17      // stop sell all pools in a meeting
#define RDCLOG_RCESPS   24      // stop sell pools in a race
#define RDCLOG_RCESPP   41      // stop pay all pools in a race
#define RDCLOG_POLSRS   5       // start sell a pool
#define RDCLOG_POLSPS   6       // stop sell a pool
#define RDCLOG_POLSPP   10      // stop pay pool
#define RDCLOG_RCESUB   7       // race substitutes
#define RDCLOG_RCESCR   2       // race scratch runner
#define RDCLOG_RCERES   8       // race results
#define RDCLOG_RCEPRS   25      // partial race result
#define RDCLOG_RCEPTT   3       // race post time 
#define RDCLOG_RCECLS   4       // race close
#define RDCLOG_POLRAD   9       // input pool result and dividend
#define RDCLOG_POLUDV   71      // unofficial pool Result & Div.
#define RDCLOG_POLNRAD  175     // new input pool rad with I*8 div. amount 
#define RDCLOG_RCEAPP   31      // all-up post race pass
#define RDCLOG_POLRFD   12      // refund pool
#define RDCLOG_POLCRF   19      // cancel refund pool
#define RDCLOG_PARAUE   94      // enable/disable all-up formulae
#define RDCLOG_PARAUF   83      // allup formulae
#define RDCLOG_RCEEAU   166     // enable/disable allup betting in a race
#define RDCLOG_PARAUW   84      // aup reinvestment warning limit 
#define RDCLOG_MTGABN   13      // abandon meeting
#define RDCLOG_PARMBV   82      // max. bet value
#define RDCLOG_PARPHL   85      // pay out limits
#define RDCLOG_PARTBD   91      // telebet deposit parameters
#define RDCLOG_PARTBW   92      // telebet withdrawal parameters
#define RDCLOG_PARCRE   93      // enable/disable deposit betting
#define RDCLOG_PAREMC   121     // EFT min. cash voucher amount
#define RDCLOG_PARNBD   107     // next business date
#define RDCLOG_PARPHB   129     // peak hour min. bet 
#define RDCLOG_PARLBV   164     // large bet values
#define RDCLOG_PARLDV   165     // large dividend values
#define RDCLOG_LOTINP   51      // new lottery schedule
#define RDCLOG_LOTDDT   54      // change of lottery draw date
#define RDCLOG_LOTODT   55      // change of lottery opening date
#define RDCLOG_LOTCDT   56      // change of lottery closing date
#define RDCLOG_LOTCTM   57      // change of lottery closing time
#define RDCLOG_LOTSRS   52      // start sell lottery
#define RDCLOG_LOTSPS   53      // stop sell lottery
#define RDCLOG_LOTRSC   60      // lottery result
#define RDCLOG_LOTDVC   61      // lottery prize
#define RDCLOG_LOTNDVC  176     // new lottery prize with I*8 div. amount
#define RDCLOG_LOTSPP   62      // stop pay lottery prize
#define RDCLOG_LOTCLM   63      // claim lottery prize
#define RDCLOG_LOTCCM   64      // cancel claim on lottery prize
#define RDCLOG_PARLBS   86      // lottery bad sale interval
#define RDCLOG_PARLCW   87      // lottery close warning interval
#define RDCLOG_PARLMS   90      // MK6 selection range
#define RDCLOG_PARGMS   168     // GBL selection range
#define RDCLOG_PARLBA   98      // MK6 default base investment
#define RDCLOG_PARGBA   169     // GBL default base investment
#define RDCLOG_PARAEN   159     // MK6 ccgame enable/disable
#define RDCLOG_PARGEN   172     // GBL ccgame enable/disable
#define RDCLOG_PARABE   160     // MK6 ccgame bet value
#define RDCLOG_PARGBE   173     // GBL ccgame bet value
//
// the following messages are bad sale expired log request
// initiated by WCHNDR
#define RDCLOG_POLBSE   201     // pool bad sale expired
#define RDCLOG_LOTBSE   202     // lottery bad sale expired
//
// the following message is requests initiated by WCHNDR
// when event detacted in WCHTIMER  
#define RDCLOG_RCECLW   14      // race close warning
#define RDCLOG_LOTCLW   58      // lottery close warning
#define RDCLOG_LOTCLS   203     // lottery close
//
// the following messages are requests initiated by WCHNDR
// race/ lottery close reply from BTHNDR  
#define RDCLOG_RCEFIN   204     // race collation final
#define RDCLOG_LOTFIN   205     // lottery collation final
//
// the following messages are requests initiated by WCHNDR
// start/ complete all-up post race pass 
#define RDCLOG_APPSTA   206     // appprp start
#define RDCLOG_APPDON   207     // appprp done
//
// the following messages are requested by RWCC only
//
#define RDCLOG_RCERPT   29      // race report request
#define RDCLOG_LOTRPT   67      // lottery report request
//
// the following message will not be handled by WCHNDR
//
#define RDCLOG_RCEDIS   26      // race distance
#define RDCLOG_MTGCND   27      // course condition
#define RDCLOG_MTGTXT   28      // text message
#define RDCLOG_RCEDSP   37      // start display race details
#define RDCLOG_RCESCT   38      // race sectional time
#define RDCLOG_RCEMAR   39      // race margin input
#define RDCLOG_RCEJDG   40      // judge's sign input
#define RDCLOG_LOTJKP   65      // lottery jackpot + snowball c/f
#define RDCLOG_RCEJKY   74      // change of jockey
#define RDCLOG_RCEWGT   76      // change of weight carried
#define RDCLOG_RCETIM   77      // race time input
#define RDCLOG_RCESTR   78      // race promoted standby starter
#define RDCLOG_PARLDP   88      // MK6 default prize
#define RDCLOG_PARPLD   97      // pool deduction parameter
#define RDCLOG_PARDCP   99      // dbl consolation prize percentage
#define RDCLOG_PARLTD   100     // lottery deduction parameters
#define RDCLOG_PARLSB   101     // lottery snowball parameter
#define RDCLOG_PARLPZ   102     // lottery prize distribution percentages
#define RDCLOG_PARSBN   103     // 6up bonus distribution percentage
#define RDCLOG_POLJKP   110     // jackpot allocation
#define RDCLOG_LOTSBP   128     // preserve snowball amount
#define RDCLOG_PARL1P   131     // MK6 max. 1st prize
#define RDCLOG_PARTTR   132     // countback % for t-t
#define RDCLOG_PARDTR   134     // jackpot % for d-t
#define RDCLOG_PARTCP   135     // jackpot % for d-t
#define RDCLOG_POLJPG   136     // jackpot generated
#define RDCLOG_PARLMF   157     // MK6 min. 1st prize fund
#define RDCLOG_DUMMY    163     // dummy message for msn sync.
#define RDCLOG_PARGDP   167     // GBL default prize
#define RDCLOG_PARG1P   170     // GBL max. 1st prize
#define RDCLOG_PARGMF   171     // GBL min. 1st prize fund
#define RDCLOG_PARAPR   161     // MK6 ccgame prize value
#define RDCLOG_PARGPR   174     // GBL ccgame prize value
#define RDCLOG_PARADE   162     // MK6 ccgame prize deductions
#define RDCLOG_POLEXW   42      // exotic winner pass
#define RDCLOG_LOTWPS   66      // lottery winner pass

#define RDCLOG_SIM_POLEXW   208 // simplified exotic winner pass    // JC01

#define RDCLOG_POLCLM   11      // claim pool
#define RDCLOG_POLCCM   18      // cancel claim pool
                                // claim/ cancel claim only used by RWCC
                                // WC will not send these request as 
                                // the prize is asked for claim/ cancel claim
                                // in the start pay message

#pragma nomember_alignment

// Each logger record of the RDCLOG consists of a header part and a body
// part.  The header is a fixed portion while the body varies depending 
// on the transaction.
// The logger record is formatted by WCHNDR and pass to BTHNDR for logging.
// We must make sure that the data in log record contains all information
// required for recovery, i.e. no need to get information from other
// sources, e.g. global sections.
//

struct RDCLOGHDR        // logger record header 
    {
        unsigned short  sizewu;         // message size
        unsigned short  codewu;         // message code
        unsigned short  timewu;         // time stamp
        unsigned char   sysidxbu;       // system index
        unsigned char   updtermbu;      // update flag + terminal no.
                                        // bit 0 for update flag,
                                        // bit 1-7 for terminal no.
    };

#pragma member_alignment

//struct RDCLOG rdclog;

#endif // RDCLOGDEF_H
