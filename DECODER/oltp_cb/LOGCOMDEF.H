//
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
//    LOGCOMDEF.H - defines logger error code; it is extracted from
//      loghdrdef.h so that all OLTP system can include this file instead
//      of loghdrdef.h
//
//    Author : Raymond Leung        29-Aug-2001
//
//    Mod :
//          LY01            25-FEB-2002
//          ( add 2 error codes for SB )
//
//          DD02            09-APR-2002
//          (add "BCS service not disabled")
//
//          DJ03            10-APR-2002
//           - define the LOG_ACC_NUM 
//
//          RL04            04-NOV-2002
//          ( add error code 239 for transaction already reversed )
//
//          LY05            26-NOV-2002
//          for enhanced error messages with more details
//
//          LY06            10-MAR-2003
//          support large value bet intercept
//
//          RL07            20-MAR-2003
//          ( add OLTP-AB error codes )
// 
//          DJ08            24-04-2003
//          - Add the ROUND_LOG_BLK define
//
//          LY09            13-MAY-2003
//          ( add reject message error code )
//          
//          LY10            09-JUN-2003
//          ( unify the error code of cancel error (17452) )
//          PN11            26-JUN-2003
//          ( add error code for bet intercept )
//          DJ12            23-07-2003
//          - Modify account # to 8 digital
//          VC13            10-09-2003
//          - Add error code for invalid transaction code, invalid bill
//            type for DEPHNDR
//          LY14            15-JAN-2004
//          - new SB error code
//          LY15            09-MAR-2004
//          - new SB error code for 3A
//-----------------------------------------------------------------------
//

#ifndef LOGCOMDEF_H
#define LOGCOMDEF_H

#include "fcbdef.h"

#pragma pack(1)

// OLTP error codes
#define LOG_ERR_OK            0     // No error
#define LOG_ERR_INVMSG        1     // Invalid message format
#define LOG_ERR_ILLFLD        2     // Illegal field
#define LOG_ERR_ILLBNK        3     // Illegal banker
#define LOG_ERR_OUTFLD        4     // Out of field
#define LOG_ERR_SCRRUN        5     // Scratched runner
#define LOG_ERR_DUPSEL        6     // Duplicated selections
#define LOG_ERR_TMYBNK        7     // Too many bankers
#define LOG_ERR_INVRCE        8     // Invalid race
#define LOG_ERR_INVPOL        9     // Invalid pool
#define LOG_ERR_NOFMLA       10     // No formula
#define LOG_ERR_RCESEQ       11     // Race seq. error in all-up
#define LOG_ERR_ILLVLE       12     // Illegal value
#define LOG_ERR_INSSEL       13     // Insufficient selections
#define LOG_ERR_INVMTG       14     // Invalid meeting
#define LOG_ERR_POLCLS       15     // Pool is closed
#define LOG_ERR_VLEBIG       16     // Value too big
#define LOG_ERR_ILLFML       17     // Illegal All-up formula
#define LOG_ERR_ALRDSN       18     // Already signoned
#define LOG_ERR_ILLOPN       19     // Illegal operator number
#define LOG_ERR_ILLOFI       20     // Illegal on/off course indicator
#define LOG_ERR_ILLVER       21     // Illegal version number (BT)
#define LOG_ERR_ILLCTR       22     // Illegal centre number
#define LOG_ERR_ILLWDW       23     // Illegal window number
#define LOG_ERR_NOTSGN       24     // Not signed on
#define LOG_ERR_ILLSID       25     // Illegal signon ID
#define LOG_ERR_ILLTSN       26     // Illegal TSN
#define LOG_ERR_RNOTSGN      27     // Terminal to be released is not signed on
#define LOG_ERR_RTRMBSY      28     // Terminal to be released is busy
#define LOG_ERR_CPOSYS       29     // Cancel/Pay ticket sold on other system
#define LOG_ERR_NOSMTG       30     // no such meeting
#define LOG_ERR_NOSTKT       31     // no such ticket
#define LOG_ERR_LSETKT       32     // Losing ticket
#define LOG_ERR_PAYHDO       33     // Paid at head office
#define LOG_ERR_PRECAN       34     // Previously cancelled ticket
#define LOG_ERR_PREPAD       35     // Previously paid ticket
#define LOG_ERR_REGDIV       36     // Registered dividend
#define LOG_ERR_RESNOT       37     // Result not in
#define LOG_ERR_NOTERM       38     // No such terminal
#define LOG_ERR_ILLDAT       39     // Illegal date
#define LOG_ERR_ILLSWH       40     // Illegal switch setting
#define LOG_ERR_ILLMCD       41     // Illegal message code
#define LOG_ERR_ILLCPM       42     // Illegal cancel/payout method
#define LOG_ERR_BALOVR       43     // Balance overflow (for shroff total fields)
#define LOG_ERR_ERRCLM       44     // Error claimed
#define LOG_ERR_NOTCLM       45     // Not error claimed
#define LOG_ERR_ILLACN       46     // Illegal account number
#define LOG_ERR_ILLTBD       47     // Deposit not available
#define LOG_ERR_ILLNUM       48     // Deposit message number
#define LOG_ERR_LNKERR       49     // Link error
#define LOG_ERR_NOTCTN       50     // Not centre on
#define LOG_ERR_ACCACT       51     // Account active
#define LOG_ERR_ASNPER       52     // Access not permitted
#define LOG_ERR_NOTBET       53     // Account not for betting
#define LOG_ERR_OVROUT       54     // Overflow exhausted
#define LOG_ERR_INSFUN       55     // Insufficient fund
#define LOG_ERR_NOCNCL       56     // Cancel not allowed 
#define LOG_ERR_BTNASGN      57     // BT not assigned
#define LOG_ERR_BTNENA       58     // BT not enabled
#define LOG_ERR_EPS          59     // EPS error
#define LOG_ERR_INSBAL       60     // Insufficient balance
#define LOG_ERR_INCSCD       61     // Incorrect security code
#define LOG_ERR_OWEMX        62     // Online withdraw exceed max. (can be EFT)
#define LOG_ERR_OWLMI        63     // Online withdraw less min. (can be EFT)
#define LOG_ERR_OWECN        64     // Online withdraw exceed count
#define LOG_ERR_BALBIG       65     // Balance too big
#define LOG_ERR_PAYBIG       66     // Paid amount too big
#define LOG_ERR_DEPHLD       67     // Deposit on hold
#define LOG_ERR_NOSSRV       68     // Service not supported
#define LOG_ERR_KEYCAN       69     // Keypad cancel not allowed
#define LOG_ERR_UNPOST       70     // Unposted transaction (EFT error)
#define LOG_ERR_ILLCRD       71     // Illegal card number
#define LOG_ERR_INVTERM      72     // Invalid terminal type
#define LOG_ERR_SVTREL       73     // SVT has been released
#define LOG_ERR_CSVTBAL      74     // Check SVT balance
#define LOG_ERR_ESCDIS       75     // ESC service disabled
#define LOG_ERR_STSUNK       76     // Status unknown
#define LOG_ERR_ESCPEND      77     // ESC trxn outstanding
#define LOG_ERR_CMSERR       78     // CMS error
#define LOG_ERR_NOSACC       79     // No such account
#define LOG_ERR_TMYSEL       80     // Too many selection
#define LOG_ERR_BCSDIS       81     // BCS service disabled
#define LOG_ERR_PAYORI       82     // pay at original centre
#define LOG_ERR_INVSTS       83     // invalid bet status
#define LOG_ERR_BCSNDS       84     // BCS service not disabled DD02
#define LOG_ERR_REJMSG       85     // Rejected message of matched
                                    // logical terminal in BTHNDRCOM
#define LOG_ERR_SBDIS        86     // SB service disbaled
#define LOG_ERR_STFLOCK      87     // staff locked

                                    // TB/ESC error to OLTP-CB
#define LOG_ERR_ALRACC      100     // Already account accessed
#define LOG_ERR_ALRACR      101     // Already account released

// If any update to the following 4 error code setting - inform CMS
#define LOG_ERR_ACOPEN      102     // Account already opened
#define LOG_ERR_ACRPLY      103     // Account already replaced
#define LOG_ERR_ACCCLS      104     // Account closed
#define LOG_ERR_SAMEDEL     105     // Same account details

#define LOG_ERR_ACUSED      106     // Account used by other customer
#define LOG_ERR_INVNACN     107     // Invalid new account number
#define LOG_ERR_DBALAC      108     // Debit balance account
#define LOG_ERR_NONBA       109     // No nominated bank account number (can be EFT)
#define LOG_ERR_IDMMAT      110     // ID. mismatch
#define LOG_ERR_NOSTXN      111     // No such transaction
#define LOG_ERR_TOTLMN      112     // Bet total less than minimum
#define LOG_ERR_CANCAN      113     // Cancellation not allowed
#define LOG_ERR_UNSTRA      114     // Outstanding transaction
#define LOG_ERR_BUSY        115     // System busy
#define LOG_ERR_NOTRAN      116     // No transaction found in ESC RCL & ENQ
#define LOG_ERR_NALLOW      117     // Transaction not allow for ESC ENQ
#define LOG_ERR_UNKREJ      118     // Reject code for unknown status transaction
                                    // (ESC has not done the CB status
                                    //  unknown transaction)
#define LOG_ERR_AMTMMA      119     // Amount mismatch

#define LOG_ERR_UNKERR      126     // Unknown error (for exception)
#define LOG_ERR_INVFMT      127     // Invalid format (for unregconized 
                                    // EFT error)

                                    // Following are additional error
                                    // returned to or from bcs:
#define LOG_ERR_BCSBUSY     200     // system busy
#define LOG_ERR_TXNRCV      201     // transaction not received
#define LOG_ERR_OLDTX       202     // old transaction
#define LOG_ERR_REVERR      203     // reverse cannot be done
#define LOG_ERR_ILLSTF      204     // illegal staff
#define LOG_ERR_ILLCSHR     205     // illegal cashier
#define LOG_ERR_DSBLOC      206     // branch is disabled
#define LOG_ERR_DSBSTF      207     // staff not enabled
#define LOG_ERR_SAMESTF     208     // same staff enabled the bt
#define LOG_ERR_INSAUTH     209     // Insufficient authority
#define LOG_ERR_INVPSW      210     // incorrect password
#define LOG_ERR_SGNOTH      211     // staff signed on at other branch
#define LOG_ERR_SNOTSGN     212     // staff not sign on
#define LOG_ERR_CNOTSGN     213     // cashier not sign on
#define LOG_ERR_INVCSHR     214     // invalid cashier code
// duplicated, see 111    #define LOG_ERR_NOSTX       215     // no such transaction
#define LOG_ERR_UNSTX       216     // outstanding transaction
#define LOG_ERR_UNSBAL      217     // outstanding balance
#define LOG_ERR_ILLCTX      218     // illegal cash transfer
#define LOG_ERR_ALRSTP      219     // already stopped pay
#define LOG_ERR_NOTSTP      220     // not stopped pay
#define LOG_ERR_NOTAUP      221     // not all-up ticket
#define LOG_ERR_NOTCV       222     // not cv ticket
#define LOG_ERR_TKTNREL     223     // ticket not released
#define LOG_ERR_NOTHOP      224     // not pay at h.o. ticket
#define LOG_ERR_BADRPY      225     // bcs failed to format reply on status
                                    // enquiry for real time message
#define LOG_ERR_SOBETO      226     // CV sold before today
#define LOG_ERR_PDBETO      227     // CV paid before today
#define LOG_ERR_CVNTPD      228     // CV not paid yet
#define LOG_ERR_INVSYS      229     // invalid system no. in xcash msgs
#define LOG_ERR_MSGSIZ      230     // invalid message size
#define LOG_ERR_CVSTS       231     // invalid CV status
#define LOG_ERR_CONTIN      232     // invalid continue information
#define LOG_ERR_PHYTN       233     // invalid physical BT number
#define LOG_ERR_ALLZRO      234     // loc/wdw & term id are all 0
#define LOG_ERR_SESSION     235     // invalid session flag
#define LOG_ERR_ALRRPB      236     // h.o. payout already released to branch
#define LOG_ERR_PAYRPB      237     // h.o. payout at designated branch
#define LOG_ERR_EFTNENA     238     // EFT not enabled
#define LOG_ERR_ALRREV      239     // transaction already reversed

// OLTP-SB error codes
#define LOG_ERR_INSLEG      300     // insufficient legs for all up/multi-leg
#define LOG_ERR_MTHSEQ      301     // match no. sequence error for all up
#define LOG_ERR_ACCNSB      302     // account not for soccer betting
#define LOG_ERR_SELCLS      303     // selection closed (bet on stopped sell combo.)
#define LOG_ERR_BETEMX      304     // bet total cost exceeding max bet value
#define LOG_ERR_LGOEMX      305     // all up bet exceeding max long odds value
#define LOG_ERR_PAYEMX      306     // dividend exceeding max payout per bet
#define LOG_ERR_NLSEMX      307     // liability exceeding max net loss
#define LOG_ERR_SB9EMX      308     // daily total sales exceeding daily max
                                    // investment allowed for SB A/C type 9
#define LOG_ERR_ODDMMA      309     // odds not matched
#define LOG_ERR_CNDMIS      310     // condition not matched
#define LOG_ERR_INAREA      311     // invalid operation area
#define LOG_ERR_INVACT      312     // invalid account type
#define LOG_ERR_NOTAUPS     313     // pool is not on an all up set
#define LOG_ERR_NOAUP       314     // pool is not opened for all up
#define LOG_ERR_NOSINGLE    315     // pool is not opened for single
#define LOG_ERR_SALENA      316     // sales not available
#define LOG_ERR_RMREJ       317     // Rejected by RM           PN11
#define LOG_ERR_CTRADE      318     // call trading room        PN11
#define LOG_ERR_OUTRNG      319     // out of range
#define LOG_ERR_INVSEL      320     // invalid selection
#define LOG_ERR_INVAUP      321     // invalid all up cross pool combination
#define LOG_ERR_SCRMUL      322     // more than 1 selection in scratched leg
#define LOG_ERR_NOENTRY     323     // no entry on void leg     LY15
#define LOG_ERR_SELLSTOP    324     // selling stopped          LY15

// OLTP-AB error codes
#define LOG_ERR_INVACC      400     // invalid account number
#define LOG_ERR_INVIDD      401     // invalid id number
#define LOG_ERR_INVAMT      402     // invalid amount
#define LOG_ERR_INVSTF      403     // invalid staff
#define LOG_ERR_INVPWD      404     // invalid password
#define LOG_ERR_ILLENT      405     // illegal entry
#define LOG_ERR_NOSSTF      406     // no such staff
#define LOG_ERR_PWDMMA      407     // password mismatch
#define LOG_ERR_NOSTRA      408     // no such transaction
#define LOG_ERR_FUNACT      409     // function active
#define LOG_ERR_ACALEX      410     // account exist already
#define LOG_ERR_NOACMA      411     // no account matched
#define LOG_ERR_POLNAV      412     // pool not available
#define LOG_ERR_INVBKR      413     // invalid banker
#define LOG_ERR_INVFLD      414     // invalid field
#define LOG_ERR_NOTREL      415     // account not released
#define LOG_ERR_STFACT      416     // staff active
#define LOG_ERR_ALRCAN      417     // transaction already cancelled
#define LOG_ERR_ALRREL      418     // terminal already released
#define LOG_ERR_ACCUNL      419     // account unlocked
#define LOG_ERR_INFNAV      420     // other system info. not available
#define LOG_ERR_AMTEXL      421     // amount exceeds withdraw limit
#define LOG_ERR_TMWITH      422     // too many withdrawals
#define LOG_ERR_AMTLOW      423     // withdraw amount too low
#define LOG_ERR_ILLTYP      424     // illegal account type
#define LOG_ERR_NOBNKR      425     // no reply from bank-epo time out
#define LOG_ERR_EPOBSY      426     // epo busy
#define LOG_ERR_BNKACT      427     // bank account active-epo dup. tx.
#define LOG_ERR_NOPAN       428     // bank card not register-cit eps
#define LOG_ERR_DSMERR      429     // dsm error - from epost
#define LOG_ERR_ISNEXC      430     // isn exceed limit - from epost
#define LOG_ERR_NBTMSI      431     // no phone bet - mk6 si account
#define LOG_ERR_POLSNA      432     // pool sales not available
#define LOG_ERR_CITISS      433     // cit already issued
#define LOG_ERR_NFTMTH      434     // free trial months not defined
#define LOG_ERR_FTDIS       435     // free trial disabled
#define LOG_ERR_SDNDEF      436     // start date not defined
#define LOG_ERR_LTCDAT      437     // input date less than current date
#define LOG_ERR_SDLTED      438     // start date greater then end date
#define LOG_ERR_PLNDEF      439     // previous level not defined
#define LOG_ERR_LVLNDEF     440     // level not defined
#define LOG_ERR_ALRRFD      441     // fee already refunded
#define LOG_ERR_ALRDDT      442     // fee already deducted
#define LOG_ERR_NOMINDP     443     // no. min deposit, (for recharge parameter)
#define LOG_ERR_ILLMSG      444     // invalid message code
#define LOG_ERR_DUPID       445     // duplicated ID
#define LOG_ERR_INVTXC      446     // VC13..Invalid transaction code
#define LOG_ERR_INVBTY      447     // VC13..Invalid bill type

// Please change max. error value when adding new error code
#define LOG_ERR_MAX         447


// terminal type
#define LOG_TRM_BT          1       // bt
#define LOG_TRM_MAT         2       // MAT
#define LOG_TRM_WC          3       // WC
#define LOG_TRM_XCH         4       // cross cashing [destination system only]
#define LOG_TRM_OPR         5       // operator
#define LOG_TRM_SBC         6       // SBC

#define LOG_BET_NUMMASK     0x3F    // msn mask

struct LOGCTLBLK            // logger file control block record
{
    struct FCB fcb;         // common file control block information
    int        blockl;      // vbn of last logical record
    int        offsetl;     // next free byte within last logical record
    __time32_t     busdate;     // business date
};

union LOGCTLBUF
{
    struct LOGCTLBLK logctb;
    unsigned int     buflu[128];
};

#define LOG_BLKFTR      50          // logical record size in blocks 

#define LOG_ACC_NUM     8           // display account # with 7 digital, DJ12

#define ROUND_LOG_BLK(n)        (((n) - FILE_DBLK_VBN) / LOG_BLKFTR* \
                                LOG_BLKFTR + FILE_DBLK_VBN)

#pragma pack(1)

#endif // LOGCOMDEF_H
