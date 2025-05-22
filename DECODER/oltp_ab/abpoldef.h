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
//  Function: This is a general header file for AB Pre-Online Processing.
//
//  Author  : David Jin     19-09-2003
//
//  Mod.    : 
//             
//
#ifndef ABPOLDEF_H
#define ABPOLDEF_H

#include <time.h>
#include "udtypedef.h"

#define ABPOL_TXT_MAX       512         // max text length
#define ABPOL_WRK_CHAN      20          // # work file channel

enum POL_JOB_STS
{
    POL_STS_PENDING = 0,
    POL_STS_DOING,
    POL_STS_BYPASSED,
    POL_STS_DONE,    
};

enum POL_JOB
{
    POLJOB_NEWBG = 0,
    POLJOB_ACSTS,
    POLJOB_CREDIT,
    POLJOB_MK6SI,
    POLJOB_DEBIT,
    POLJOB_WTHSI,
    POLJOB_MAX
};

enum ABWRK_REC
{
    ABWRK_REC_HDR = 0,                  // Control Header Record (701) or (801)
    ABWRK_REC_SIC,                      // Mark 6 SI Control Record (702)
    ABWRK_REC_SID,                      // Mark 6 SI details (703) 
    ABWRK_REC_NBG,                      // New Bank Guarantee Amount (704) 
    ABWRK_REC_CHS,                      // Change of Account status (705)
    ABWRK_REC_CQD,                      // Cheque Deposit (706) 
    ABWRK_REC_WDS,                      // Withdrawal S.I. (707)
    ABWRK_REC_BGR,                      // Bank Guarantee request (708)
    ABWRK_REC_WDR,                      // Withdrawal request (709) 
    ABWRK_REC_REL,                      // Mark 6 SI account release
    ABWRK_REC_PDR,                      // Progressive CIT Deposit Refund (802)
    ABWRK_REC_DPR,                      // CIT Deposit Refund (803)
    ABWRK_REC_AFD,                      // CIT Annual Fee Deduction (804)
    ABWRK_REC_AFR,                      // CIT Annual Fee Refund (805)
    ABWRK_REC_DPD,                      // CIT Deposit Deduction (806)
    ABWRK_REC_ESC_DPD,                  // ESC Deposit Deduction (807)
    ABWRK_REC_DEBIT,                    // Debit Adjustment (808)
    ABWRK_REC_CREDIT,                   // Credit Adjustment (809)
    ABWRK_REC_ESC_RFD,                  // ESC Deposit Refund  (810)
    ABWRK_REC_CIT_FFT,                  // CIT Deposit Forfeit (811)   
    ABWRK_REC_ESC_FFT,                  // ESC Deposit Forfeit (812)  
    ABWRK_REC_MAX,                      
};

#pragma pack(1)

struct ABPOL_LOTACA             // lottery S.I account access
{
    BOOL                succt;          // Successful Flag
    BOOL                ndrawt;         // n-Draw Failure Flag
    unsigned int        ttlAmtlu;       // batch total amount
    unsigned int        countlu;        // Total No. of Mark 6 SI Count   
    unsigned char       lotTypebu;      // lottery type MK6/GBL
};

struct ABPOL_LOT                // lottery post request
{
    unsigned int        siEntrylu;      // SI entry number
    unsigned char       lotTypebu;      // lottery type (what is what?)
    unsigned int        binvlu;         // base investment
    unsigned int        costlu;         // cost
    char                selb[ABPOL_TXT_MAX+1]; // selection, variable size in mail
};

struct ABPOL_BG                 // change bg request
{
    LONGLONG            bankgd;         // bank guarantee
    unsigned char       bgTypebu;       // bank gaurantee type
};

struct ABPOL_STS                // change account status
{
    unsigned char       oldStatusbu;    // old status, see ACUDEF.H, ACU_STATUS_...
    unsigned char       newStatusbu;    // new status, see ACUDEF.H, ACU_STATUS_...
};

struct ABPOL_CHEQUE_DEP         // cheque deposit request
{
    unsigned int        amountlu;       // deposit amount
};

struct ABPOL_WTW_SI             // withdrawal S.I. request
{
    unsigned char       typebu;         // withdrawal type, see ACUDEF.H, ACU_WTW_...
    unsigned LONGLONG   remBaldu;       // remaining balance
};

struct ABPOL_STATUS             // pre-online service status
{
    enum POL_JOB_STS    jobsta[POLJOB_MAX];
    unsigned char        start1:1;       // receive start pol-online
    unsigned char        cvtdone1:1;     // file convert done
    unsigned char        postdone1:1;    // all job done
    unsigned char        :5;
};

struct ABPOL_CKP                // pre-online done, checkpoint
{
    struct ABPOL_STATUS status;          // pre-online service status
    BOOL                sodt;            // pre-online all service done
};

struct ABPOL_LOYALTY            // Work records generated by Loyalty 
{
    unsigned LONGLONG   amountdu;       // amount
    unsigned LONGLONG   citdu;          // cit # or esc #
    unsigned char       cittypbu;       // CIT Type
    char                remarks[ABPOL_TXT_MAX+1];
};

struct ABPOL_DCR_ADJ            // debit credit adjustmen
{
    unsigned LONGLONG   amountdu;       // amount
    unsigned int        typelu;         // Adjustment Type 
    BOOL                negbalb;        // TRUE = allow negative balance
    char                remarks[ABPOL_TXT_MAX+1];   // remark variable length
};

struct ABPOL_FAIL_HDR           // pre-online fail record header
{
    short               sizew;          // size in byte
    unsigned int        acclu;          // account number
    unsigned short      codewu;         // Record Type
      #define ABPOL_FAIL_SI_POST  605   // Failed Lottery SI Posting 
      #define ABPOL_FAIL_AC_CLOSE 606   // Failed Automatic Close Account 
      #define ABPOL_FAIL_SI_FUND  607   // Insufficient Fund for N Draws 
      #define ABPOL_FAIL_SI_SUCC  609   // Successful Lottery SI Posting
      #define ABPOL_FAIL_LOYALTY  610   // Rejected CIT Transaction (610)
      #define ABPOL_FAIL_LOY_ESC  611   // Rejected ESC Transaction 
      #define ABPOL_FAIL_LOY_NEG  612   // Negative Balance (612) 
      #define ABPOL_FAIL_DCR_ADJ  613   // Rejected Adjustment Transaction

    __time32_t              bussdat;        // Requested Business Date
    unsigned int        errlu;          // error code, Failed SI Entry Number (605)
};

struct ABPOL_FAIL_LOY           // pre-online loyalty fail record 
{
    unsigned LONGLONG   citdu;          // CIT #, or ESC #
    unsigned char       typbu;          // CIT Transaction Type
        #define ABPOL_CIT_PROGDEP   1   // Progressive CIT Deposit Refund
        #define ABPOL_CIT_DEP       2   // CIT Deposit Refund
        #define ABPOL_CIT_FEE_DED   3   // CIT Annual Fee Deduction
        #define ABPOL_CIT_FEE_REF   4   // CIT Annual Fee Refund
        #define ABPOL_CIT_DPD       5   // CIT Deposit Deduction
        #define ABPOL_CIT_FFT       6   // CIT Deposit Forfeit 
        #define ABPOL_ESC_DPD       7   // ESC Deposit Deduction  RL01
        #define ABPOL_ESC_RFD       8   // ESC Deposit Refund     RL01
        #define ABPOL_ESC_FFT       9   // ESC Deposit Forfeit    RL01

    LONGLONG            amountd;        // Account Balance for Negative Balance (612)
    unsigned char       rejbu;          // Reject Reason
};

struct ABPOL_FAIL_DCR           // Rejected Adjustment Transaction (613)
{
    unsigned LONGLONG   amountdu;       // amount
    BOOL                debitb;         // TRUE=Debit, FALSE=Credit
    unsigned int        typelu;         // Adjustment Type 
    unsigned char       rejbu;          // Reject Reason
};

struct ABPOL_FAIL_STS           // pre-online Failed Automatic Close 
{
    unsigned char       statusbu;       // 0 - Success, 1 - Failed
        #define ABPOL_FAIL_STS_SUC  0
        #define ABPOL_FAIL_STS_FAI  1
    LONGLONG            amountd;        // Account Balance
    unsigned char       rejbu;          // Reject Reason
};

struct ABPOL_FAIL_MK6SI         // Failed Lottery SI Posting (605) 
{
    unsigned int            siEntrylu;  // SI entry number
    unsigned char           lotTypebu;  // lottery type MK6/GBL
    __time32_t                  drawdate ;  // lottery draw date
};

union ABPOL_FAIL_BODY           // pre-online fail record body
{
    struct ABPOL_FAIL_LOY   loy;
    struct ABPOL_FAIL_STS   sts;
    struct ABPOL_FAIL_MK6SI mk6si;
    struct ABPOL_FAIL_DCR   dcr;        // Rejected Adjustment Transaction  (613)
};

struct ABPOL_FAIL               // pre-online fail record
{
    struct ABPOL_FAIL_HDR   hdr;        // header
    union ABPOL_FAIL_BODY   d;          // pre-online fail record body 
};

#pragma pack()

#endif
