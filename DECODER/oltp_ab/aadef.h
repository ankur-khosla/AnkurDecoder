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
//  Function:   Header file for message between OLTP-AB and BCS-AA.
//
//  Author  :   Edward Hon      Dec-2002
//
//  Mod.    :   HL01 18-Jun-2003
//                   Change unsigned variable to signed variable for debit 
//                   and credit amount in account statement because credit
//                   amount can be negative value like account balance.
//              HL02 27-Aug-2003
//                   add two more transaction types
//                   1.  dividend for purged transaction
//                   2.  dividend settled today 
//
//      KL03 Update AA message structures
//
//      KL04 03-Nov-2003
//           change the type of AA_BCS_DETCDTREQ.typebu to
//           AA_BCS_DETCDTREQ.typelu
//
//      KL05 18-Nov-2003
//           change the Customer type to Channel Accessibility
//
//      KL06 01-Dec-2003
//           Update structures details
//
//      KL07 05-Jan-2004
//           Update structures details
//
//      KL08 30-Jan-2004
//      change CON='C' to CON='M'
//
//      HL09 4-Feb-2004
//            User likes to have more credit debit adjustment items. 
//      Some items might be duplicated as old ones. Old ones are
//      not deleted because such move may cause confusion in other 
//      system like EWIN.
//
//      KL10 06-Feb-2004
//      Add 4 new BCS Real Time Transaction
//
//      HL11 09-Feb-2004
//      Add 2 transaction types for statement : statement charge and
//            dividend of outstanding ESC transaction
//
//      KL12 16-Feb-2004
//      Add one extra byte (or two for unicode) to all fixed size 
//      string field that may have variable size content.
//      Remove AA_CUSBANKINFO
//
//      HL13 19-Feb-2004
//      There will be a transaction for cancelling AB deposit and this 
//          transaction can be reversed. 
//
//      KL14 01-Mar-2004
//      Add online statement bet transaction key structure 
//
//      KL15 03-Mar-2004
//      Add 8 new messages and update message (AA spec 1.9) 
//
//      HL16 15-March-2004
//      Add 2 transaction types for statement : debit adjustment -- others and
//            credit adjustment -- others
//
//      KL17 17-Mar-2004
//      Update spec 1.10
//
//      KL18 30-Mar-2004
//      Use 8 bytes instead of 4 bytes for amount in cents field.
//      Add account monitoring message
//
//      HL19 1-April-2004
//           - add system generated debit adjustment for 
//                      Forfeited Deposit Fee By System
//
//      HL20 16-April-2004
//           - Since settled dividend and dividend for purged transaction 
//             should be in format as that in legacy, so old codes can be used
//             in statement. There will be no need to create new codes for
//             these two. So the last two items are moved to fill the holes
//             after these two items are deleted.
//             And also there will be no cancel deposit transaction.
//
//      KL17 21-Apr-2004
//      Update spec 1.11, Add Funds Available for Betting 
//      to Account Fund Analysis Message
//
//      RL18 27-Apr-2004
//      Authority verification
//
//      KL19 05-May-2004
//      Update spec 1.11, 
//      - In Account Bet Parameter Message, 
//          change data size of the days at recall at BT to 2.
//      - Add Staff ID to Verification of Password and Role Message.
//
//      KL20 13-May-2004
//      Update spec 1.11, 
//      - Use signed variables 
//
//      HL21    29-May-2004
//      User requests to have new set of debit credit adjustment reason code,
//      the transaction codes for statement are adjusted accordingly.
//      The new debit credit codes are occupying 76 to 151. 1-75 are codes 
//      from legacy system. Some of them may be identical to the new codes in 
//      meaning and resson. For easy handling on possible frequent changes 
//      in the future on such codes, the whole new set will be input to the 
//      list at the position of 76.
//
//      RL22    31-May-2004
//      Add channel lock message
//
//      JC23    01-JUN-2004
//      move position of fields to syn with CB
//
//      HL24    15-JUN-2004
//      Add two transaction codes : CIT DEPOSIT FORFEITED and
//                                  ESC DEPOSIT FORFEITED
//              initiated by CMS.
//		Also, separate ESC DEPOSIT from CIT DEPOSIT as a new code. 
//
//      KL25    15-Jun-2004
//      Update spec 1.12, 
//      - Add HKID to Device Cancel message
//      - Add additional information to the reply message when the requested 
//        account is locked.
//      - Add additional byte to the string in some fields sent from OLTP to BCS.
//
//      HL26    15-JUN-2004
//      Add one more transaction code to differentiate CB call header from BT
//	    or ESC
//
//      HL27    23-JUN-2004
//      Refer to HL26, CB call header will show or will not show ESC# but 
//	    same transaction code CB Call Heare will be used.
//
//      KL28    19-JUL-2004
//      Add a type for LMAT in Account details update
//
//      KL29    22-JUL-2004
//      Update AA spec 1.14
//
//      HL30	24-JUL-2004
//      Add one more status "settled" for bet transactions on statement. Also
//	    change status to bit map format
//
//      KL31    05-AUG-2004
//      Update AA spec 1.15
//
//      KL32    30-AUG-2004
//      Update AA spec 1.16
//      - Take out Account Online Withdrawal from Account Bet Parameter message
//      - Add Deposit Amount and Waive Deposit Fee Flag to Device Issue message
//
//      KL33    08-SEP-2004
//      Update AA spec 1.17
//      - Add ECV Card Issue and ECV Card Cancel
//      - Add Device Deposit Fee to Account Status Enquiry Message
//
//      HL34    12-NOV-2004
//	Add 9 transaction codes 158 - 160, 162 - 167 (NOTE:161 was used before)
//        These codes are initiated by CMS to do transactions similar to 
//	  some credit debig ajustment. Since they are activated by system, so 
//	  there is "AUTO' in the message content. 
//	  Since users keep on changing descrition details, so old codes smaller 
//	  than 75 may be similar to new ones, but for simplicity, new codes are
//	  added instead of changing the old ones. 
//
//      HL34    25-NOV-2004
//	  Change descriotion text requested by user
//
//      KL36    10-DEC-2004
//      Update AA spec
//      - Add Background message from OLTP-AB to BCS-AA, Account Range
//
//	EH37	15-Feb-2005
//	New batch deposit interface with TB
//
//      RL38    22-Mar-2005
//      (. add MAT realtime message 'account fund for closure'
//         to help fixing BCSAA internal design problem.
//       . Add support for multiple BG. )
//

#ifndef AADEF_H
#define AADEF_H

#include "udtypedef.h"
#include "bcsgendef.h"
#include "bcsdef.h"

#pragma pack(1)

#define AA_MAX_BUF_SIZE     1000
#define AA_TRAPMSG_SIZE     2500
// KL11..
#define AA_SURNAME_LEN      21
#define AA_OTHNAME_LEN      41
#define AA_CHNSURNAME_LEN   12
#define AA_CHNOTHNAME_LEN   12
#define AA_HKID_LEN         21
//#define AA_BANKACC_LEN      27
#define AA_BANKCODE_LEN     3
#define AA_BNKNUM_LEN       4
#define AA_BCHNUM_LEN       4
#define AA_BNKACCNUM_LEN    13
#define AA_PANNUM_LEN       19
#define AA_CONID_LEN        10
#define AA_TERMID_LEN       8
#define AA_REQACCNUM_LEN    18
#define AA_DRCR_RMK_LEN     51
#define AA_ALD_LEN          21
#define AA_ADDR_LEN         51
#define AA_TEL_LEN          21
#define AA_REASON_LEN       31

enum AA_BCS_DEVICE_TYPE {
/*
    AA_DEV_TYP_TBTR = 10,
    AA_DEV_TYP_MAT = 12,
    AA_DEV_TYP_SI = 13,
    AA_DEV_TYP_AUTO = 14,
    AA_DEV_TYP_MPT = 15,
    AA_DEV_TYP_CIT = 16,
    AA_DEV_TYP_CB = 17,
*/
    AA_DEV_TYP_INTERNET = 8,
    AA_DEV_TYP_CIT2 = 7,
    AA_DEV_TYP_CIT3 = 1,
    AA_DEV_TYP_CIT3A = 2,
    AA_DEV_TYP_CIT5 = 3,
    AA_DEV_TYP_CIT6 = 4,
    AA_DEV_TYP_TWM = 5,
    AA_DEV_TYP_CITPDA = 6,
    AA_DEV_TYP_MPB = 7,
    AA_DEV_TYP_ESC = 11,
    AA_DEV_TYP_CIT8 = 9,
    AA_DEV_TYP_MAX = 11,
};

#define ABP_STS_ENA     1    // Enabled
#define ABP_STS_DIS     2    // Disabled

// Account Info
struct AA_ACCINFO
{
    unsigned int        accnumlu;    // Account number
    unsigned int        rectrklu;    // Recorder track
};

// Customer Info
struct AA_CUSINFO
{
    unsigned char       cussalbu;    // Customer salutation
    char                surnames[AA_SURNAME_LEN];   // Customer surname
    char                othnames[AA_OTHNAME_LEN];   // Customer other name
    char                chnsurnames[AA_CHNSURNAME_LEN];// Customer Chinese surname name
    char                chnothnames[AA_CHNOTHNAME_LEN];// Customer Chinese surname name
    unsigned char       custypebu;   // Channel Accessibility (Customer type)
    unsigned char        rac1:1;      // 1 = Racing bet type
    unsigned char        lot1:1;      // 1 = Lottery bet type
    unsigned char        sb1:1;       // 1 = SB bet type
    unsigned char        :5;          // not used
    unsigned char       fbtypebu;    // SB account type
    unsigned char       langbu;      // Spoken Lang, 1=Eng 2=Man 3=Can
        #define LANGENG     1            // English
        #define LANGMAN     2            // PuTongHua
        #define LANGCAN     3            // Cantonese
    unsigned char       staffacctflag;    // Staff betting account flag
	unsigned char       staffaccttype;    // Staff betting account type
	    
};

// Bank Account Number
struct AA_BANKACCNUM
{
    char                bnknums[AA_BNKNUM_LEN];   // Bank number
    char                bchnums[AA_BCHNUM_LEN];   // Branch number
    char                bnkaccnums[AA_BNKACCNUM_LEN];// Bank account number
};


// new bank account details  -- Q210
struct AA_BCS_ACC_DET_BANK_INFO_NEW
{
    unsigned char       bankind;    // Bank indicateor  1=pri,2=sec 
	char                bnknums[AA_BNKNUM_LEN];   // Bank number
    char                bchnums[AA_BCHNUM_LEN];   // Branch number
    char                bnkaccnums[AA_BNKACCNUM_LEN];// Bank account number
	unsigned char       invnba;    // Invalid NBA 0=false,1=true
	unsigned char       resetert;    // Resert ERT Info 0=false,1=true

};



// *********************************** OLTP ***********************************

// ********** OLTP -> BCS  Status Enquiry For OLTP Txn **********
// Request (OLTP->BCS), just header

// Reply (BCS->OLTP)
struct AA_BCS_STSENQTXNRPY
{
    unsigned int        txnidlu;    // current/last process txn id
};

// ********** Reverse For OLTP Txn **********
// Reverse Request (OLTP->BCS)
struct AA_OLTP_REVREQ
{
    unsigned int        txnidlu;    // current/last process txn id
};


// ********** OLTP -> BCS  Background message **********

// Failed Lottery SI Posing (OLTP->BCS)
struct AA_OLTP_FAILLOTSIPOS
{
    unsigned int        accnumlu;      // Account number
};

// Failed Automatic Close Account (OLTP->BCS)
struct AA_OLTP_FAILAUTOCLSACC
{
    unsigned int        accnumlu;      // Account number
};

// Trap Message (OLTP->BCS)
struct AA_OLTP_TRAPMSG
{
    unsigned short      trapcodewu;    // Trap Code
        #define TC_HV_WTD           0       // High value withdrawl
        #define TC_CHQ_WTD          1       // Cheque withdrawl
        #define TC_EFT_TXN_NPOST    2       // EFT transaction not posted
        #define TC_EPOST_TXN_NPOST  3       // EPOST transaction not posted
        #define TC_WTD_BNK_TMOUT    4       // Withdrawal bank timeout
        #define TC_WTD_NCDT_NBA     5       // Withdrawal not credited to NBA
        #define TC_EPSCO_PIN_ERR    6       // EPSCO detected PIN error
        #define TC_REJ_PO_DEP       7       // Rejected payout deposit
        #define TC_HVB              8       // High value bet
        #define TC_HVC              9       // High value cancel
        #define TC_KEY_ACC_REC      10      // Key account recall
        #define TC_UNSUC_ACC_ACS    11      // Unsuccessful account access
        #define TC_INSUF_AUTH       12      // Insufficient authority
        #define TC_ACC_ACS_BYPASS   13      // Account access bypass
        #define TC_MON_ACC_ACS      14      // Monitored Account Access
        #define TC_BET_INTERCEPT    15      // Bet intercept

    unsigned int        accnumlu;      // Account number
    unsigned LONGLONG   amtdu;         // Amount (in cents)
    // String N bytes, formatted info
    char textb[AA_TRAPMSG_SIZE];
};

// Insufficient Fund for N Draws (OLTP->BCS)
struct AA_OLTP_INSUFFUND
{
    unsigned int        accnumlu;      // Account number
};

// Batch deposit summary (OLTP->BCS)
struct AA_OLTP_BATDEPSUM
{
    struct BCS_DATE     valdate;        // Value date
    struct BCS_DATE     caldate;        // Calender date
    unsigned char       typebu;         // Batch deposit sender type
        #define BD_DEP_HKSC         0       // Hksc
        #define BD_DEP_EPS          1       // Eps
    unsigned int        batnumlu;       // Batch number
    unsigned short      acpttxncntwu;   // Accepted transaction count
    unsigned LONGLONG   acptamtdu;      // Accepted transaction Amount (in cents)
    unsigned LONGLONG   rechargedu;     // Recharges (in cents)
    unsigned short      rejcntwu;       // Reject transaction count
    unsigned LONGLONG   rejamtdu;       // Reject transaction Amount (in cents)

};

struct AA_REJBATDEPSUB
{
    struct BCS_DATE     valdate;        // Value date
    struct BCS_DATE     caldate;        // Calender date
    unsigned char       typebu;         // Batch deposit sender type
    unsigned int        batnumlu;       // Batch account number
    unsigned short      bankcodewu;     // internal bank/terminal #	EH37
    char                bankacc[BCS_ACCNUM_LEN];    // Bank account number
    unsigned int        seqnumlu;       // Input sequence number
    unsigned int        clubaccnumlu;   // Club account number
    char                reqclubaccnumacc[AA_REQACCNUM_LEN];    // Request club account number
    unsigned LONGLONG   amtdu;          // Amount (in cents)
};

// Rejected batch deposit (OLTP->BCS)
struct AA_OLTP_REJBATDEP
{
    struct AA_REJBATDEPSUB   depsub;         // Batch Deposit sub
    unsigned char       reasonbu;       // Reason for reject
        #define RB_INV_TXN_CODE     0       // Invalid transaction code 
        #define RB_INV_BIL_TYPE     1       // Invalid bill type 
        #define RB_INV_ACC          2       // Invalid account 
        #define RB_NO_ACC           3       // No such account 
        #define RB_ACC_BAL_OF       4       // Account balance overflow
        #define RB_ACC_ACS_NPERM    5       // Account access not permitted 
        #define RB_ACC_ACS_NALW     6       // Account access not allowed 
        #define RB_VTB              7       // Value too big 
        #define RB_VTL              8       // Value too low  
        #define RB_UNKN_EXCEP       9       // Unknown exception 
        #define RB_ACC_CLS         10       // Account Closed
};

// Change of Next Business Date  (OLTP->BCS) KL29
struct AA_OLTP_CHGNXTBUSDATE
{
    struct BCS_DATE     date;       // Next Business Date
};

// Account Range   (OLTP->BCS) KL36
struct AA_OLTP_ACCRANGE
{
    unsigned int        straccnumlu;   // Start account number
    unsigned int        endaccnumlu;   // End account number
};

// Number of Account Range (OLTP->BCS)
struct AA_OLTP_ACCRANGENUM
{
    unsigned short      numacclu;      // Number of account range
};

// ********** OLTP -> BCS  Real Time message **********

// *** Account Details Enquiry
// Request (OLTP->BCS)
struct AA_OLTP_ACCDETENQREQ
{
    unsigned int        accnumlu;    // Account number
    unsigned char       detcodebu;     // Detail code
        #define ADC_HKID            1  // HKID 
        #define ADC_SEX             2  // SEX
        #define ADC_BANKCODE        3  // BANK CODE    //Q405
    unsigned LONGLONG   devnumdu;    // Device number if detcodebu = 3, o/w = 0
};

// Account Details Reply
// HKID
struct AA_BCS_HKID
{
    char                hkids[AA_HKID_LEN];   // HK ID
};

// SEX
struct AA_BCS_SEX
{
    char                sexb;        // Sex, 'F'/'M'
        #define FEL     'F'          // Female
        #define MAL     'M'          // Male
    char                surnames[AA_SURNAME_LEN];
    char                othernames[AA_OTHNAME_LEN];
    char                chinsurnames[AA_CHNSURNAME_LEN];
    char                chinothnames[AA_CHNOTHNAME_LEN];
};

// Device Deposit Fee
struct AA_BCS_DEVDEPFEE
{
    unsigned int        amountlu;    // Device Deposit Fee (in cents)
};

// Bank code
struct AA_BCS_BANKCODE
{
    char		        bankcode[3];    // q405
};


// Reply (BCS->OLTP) 
union AA_BCS_ACCDETRPY
{
    struct AA_BCS_HKID  hkid;       // HK ID
    struct AA_BCS_SEX   sex;        // Sex
    struct AA_BCS_DEVDEPFEE devdepfee; // KL33, Device Deposit Fee
};

// *** BT Sign On ***
// Request (OLTP->BCS)
struct AA_OLTP_BTSGNREQ
{
    unsigned int        passwordlu;    // Password
    unsigned char       pwdLenbu;      // Password length
};

struct AA_BCS_BTSGNAUTH
{
    unsigned int        secu1:1;        // Security code override
    unsigned int        super1:1;       // Super key account access
    unsigned int        key1:1;         // Key account access
    unsigned int        normal1:1;      // Normal account access
    unsigned int        fb9acc1:1;      // FB Type 9 A/C Access
    unsigned int        signon1:1;      // Sign on
    unsigned int        signoff1:1;     // Sign off
    unsigned int        racesell1:1;    // Race bet selling
    unsigned int        lotsell1:1;     // Lottery bet selling
    unsigned int        fbsell1:1;      // FB bet selling
    unsigned int        cheqwtd1:1;     // Cheque withdrawal
    unsigned int        aupaywtd1:1;    // Autopay withdrawal
    unsigned int        cancurcall1:1;  // Cancel current call bets
    unsigned int        canprvcall1:1;  // Cancel previous call bets
    unsigned int        reccurcall1:1;  // Recall current call bets
    unsigned int        recprvcall1:1;  // Recall previous call bets
    unsigned int        hvbetauth1:1;   // High value bet authorization
    unsigned int        :15;            // not used
};

// Reply (BCS->OLTP) 
struct AA_BCS_BTSGNRPY
{
    unsigned int        rectrklu;      // Recorder track
    struct AA_BCS_BTSGNAUTH auth;      // authority bitmap
};

// *** EFT PAN Capture ***
// Request (OLTP->BCS)
struct AA_OLTP_EFTPANREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       pantypebu;
    char                pannumb[AA_PANNUM_LEN];   // PAN number
};

// *** CIT Issue or Replacement (During ESC Migration only) ***
// Request (OLTP->BCS)
struct AA_OLTP_CITISSUEREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       typebu;        // CIT type
    unsigned LONGLONG   numdu;         // CIT number
    unsigned char       updflagbu;     // Update fee flag
    unsigned LONGLONG   fundavadu;     // Fund available for betting (in cents)
};

// reply (BCS->OLTP)
struct AA_BCS_CITISSUERPY
{
    unsigned int        annlfeededlu;   // Annual fee deduction (in cents)
    unsigned int        depfeededlu;    // Deposit fee deduction (in cents)
    unsigned int        annlfeereflu;   // Annual fee refund (in cents)
    unsigned int        depfeelreflu;   // Deposit fee refund (in cents)
};


// *** Device Issue ***
// Request (OLTP->BCS)
struct AA_OLTP_DEVISSUEREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       typebu;        // Device type
    unsigned LONGLONG   numdu;         // Device number
    LONGLONG            fundavad;      // Fund available for betting (in cents)
    LONGLONG            depAmtd;       // deposit amount
    BOOL                waiveDepFeet;  // waive deposit fee flag
    char                hkids[AA_HKID_LEN];   // HK ID KL25.. Add Null char
};

// reply (BCS->OLTP)
struct AA_BCS_DEVISSUERPY
{
    unsigned int        annlfeededlu;   // Annual fee deduction (in cents)
    unsigned int        depfeededlu;    // Deposit fee deduction (in cents)
};


// *** Device Cancel ***
// Request (OLTP->BCS)
struct AA_OLTP_DEVCANREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       typebu;        // Device type
    unsigned LONGLONG   numdu;         // Device number
    unsigned char       forfflagbu;    // Forfeit available for betting
    char                hkids[AA_HKID_LEN];   // HK ID KL25..
};

// reply (BCS->OLTP)
struct AA_BCS_DEVCANRPY
{
    unsigned int        annlfeereflu;   // Annual fee refund (in cents)
    unsigned int        depfeelreflu;   // Deposit fee refund (in cents)
};

// *** Device Replacement ***
// Request (OLTP->BCS)
struct AA_OLTP_DEVREPREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       oldtypebu;     // Old device type
    unsigned LONGLONG   oldnumdu;      // Old device number
    unsigned char       newtypebu;     // New device type
    unsigned LONGLONG   newnumdu;      // New device number
    unsigned char       updflagbu;     // Update fee flag
    unsigned char       forfflagbu;    // Forfeit available for betting
    LONGLONG            fundavad;      // Fund available for betting (in cents)
};

// reply (BCS->OLTP)
struct AA_BCS_DEVREPRPY
{
    unsigned int        annlfeededlu;   // Annual fee deduction (in cents)
    unsigned int        depfeededlu;    // Deposit fee deduction (in cents)
    unsigned int        annlfeereflu;   // Annual fee refund (in cents)
    unsigned int        depfeelreflu;   // Deposit fee refund (in cents)
};

// Kl15..
// *** Change of Security Code ***
// Request (OLTP->BCS)
struct AA_OLTP_CHGSECREQ
{
    unsigned int        accnumlu;      // Account number
    char                hkids[AA_HKID_LEN];   // HK ID KL25.. Add Null char
    unsigned int        oldnumlu;      // Old security code
    unsigned int        newnumlu;      // New security code
};
// ..KL15

struct AA_BCS_CHGSECRPY
{
    unsigned char       lockVBTbu;     // 0 = FALSE, otherwise TRUE
};

// *** Authority verification ***
// Request (OLTP->BCS)
struct AA_OLTP_AUTHVERREQ
{
    unsigned int        staffidlu;     // Staff ID
    unsigned int        passwordlu;    // Password
    unsigned char       pwdLenbu;      // Password length
    unsigned char       rolebu;        // role function to be verified
};

// Kl33..
// *** ECV Card Issue ***
// Request (OLTP->BCS)
struct AA_OLTP_ECVCARDISSREQ
{
    unsigned LONGLONG   ecvnumdu;      // ECV card number
    char                hkids[AA_HKID_LEN];   // HK ID
    unsigned char       langbu;      // Spoken Lang, 1=Eng 2=Man 3=Can
    char                sexb;        // Sex, 'F'/'M'
    struct BCS_DATE     birthdate;   // Date of Birth
    char                surnames[AA_SURNAME_LEN];
    char                othernames[AA_OTHNAME_LEN];
    char                addr1s[AA_ADDR_LEN];
    char                addr2s[AA_ADDR_LEN];
    char                addr3s[AA_ADDR_LEN];
    char                addr4s[AA_ADDR_LEN];
    char                addr5s[AA_ADDR_LEN];
    char                tel1s[AA_TEL_LEN];
    char                tel2s[AA_TEL_LEN];
    char                locb;        // Sex, 'F'/'M'
    LONGLONG            balanced;    // Opening balance (in cents)
    char                depfeeb;     // Waive Deposit Fee Flag, 1 = TRUE
};

struct AA_BCS_ECVCARDISSRPY
{
    unsigned int        accnumlu;    // Account number
    unsigned int        depfeelu;    // Deposit Fee (in cents)
    unsigned int        seccodelu;   // Security code

};

// *** ECV Card Cancel ***
// Request (OLTP->BCS)
struct AA_OLTP_ECVCARDCANREQ
{
    unsigned int        accnumlu;    // Account number
    unsigned LONGLONG   ecvnumdu;    // ECV card number
    char                depfeeb;     // Forfeit Deposit Fee Flag, 1 = TRUE
    unsigned int        refundlu;    // Deposit Fee Refund (in cents)
    char                reasons[AA_REASON_LEN]; // Reason
};

struct AA_BCS_ECVCARDCANRPY
{
    unsigned int        depfeelu;    // Card deposit fee (in cents)
};
// ..KL33


// *********************************** BCS ***********************************



// ********** Status Wnquiry for BCS Transaction **********

// *** BCS  -> OLTP Status Enquiry For BCS Txn ***
// Reply (OLTP->BCS)
struct AA_OLTP_STSENQTXNRPY
{
    unsigned int        txnidlu;    // current/last process txn id
};

// ********** BCS  -> OLTP Background message **********

// *** BCS Background Txn ***
// Account Bet Parameter type = online EFT transaction
struct AA_BCS_ACC_BET_OET
{
    unsigned char       methodbu;     // method
        #define ABP_OET_MBS         1
        #define ABP_OET_ATM         2       // HSBC
        #define ABP_OET_MPT         3
        #define ABP_OET_EWIN        4
        #define ABP_OET_TWM         5
        #define ABP_OET_CIT         6
        #define ABP_OET_CITPDA      7
        #define ABP_OET_CIT8        8
        #define ABP_OET_BOC         9       // RL42
    unsigned char       custtypebu;         // Channel Accessibility (Customer type)
        #define ABP_OET_NOR         1       // Normal
        #define ABP_OET_KEY         2       // Key
        #define ABP_OET_SUP         3       // Super Key
        #define ABP_OET_LOT         4       // Lottery Only
    unsigned char        rechrgamt1:1;       // recharge amount
    unsigned char        mindepcnt1:1;       // min deposit count
    unsigned char        maxdepcnt1:1;       // max deposit count
    unsigned char        :5;                 // not used
    unsigned LONGLONG   rechrgamtdu;        // recharge amount (in cents)
    unsigned LONGLONG   minamtdu;           // minimum deposit (in cents)
    unsigned LONGLONG   maxamtdu;           // maximum deposit (in cents)
};

// Account Bet Parameter type = account withdrawal
struct AA_BCS_ACC_BET_ACC_WTD
{
    unsigned char        daymaxamt1:1;       // daily max amount
    unsigned char        daymaxcnt1:1;       // daily max count
    // KL32.. unsigned int        minamt1:1;          // min amount
    unsigned char        :6;                 // not used
    unsigned char       methodbu;           // method
        #define ABP_WTD_CASH       1        // Cash
        // KL32.. #define ABP_WTD_ONLINE     2        // Online
    unsigned LONGLONG   daymaxamtdu;        // daily max amount (in cents)
    unsigned char       daymaxcntbu;        // daily max count
    // KL32.. unsigned LONGLONG   minamtdu;           // minimum amount (in cents)
};

// Account Bet Parameter type = account balance exception
struct AA_BCS_ACC_BET_ACC_BAL_EXC
{
    unsigned char        highbal1:1;  // High balance
    unsigned char        lowbal1:1;   // Low balance
    unsigned char        highdiv1:1;  // High dividend
    unsigned char        highinvrac1:1; // High investment for racing
    unsigned char        highinvsb1:1;  // High investment for football
    unsigned char        :3;          // not used
    unsigned LONGLONG   hibaldu;     // High balance in cents (report when balance over)
    unsigned LONGLONG   lobaldu;     // Low balance in cents (report when balance under)
    unsigned LONGLONG   hidivdu;     // High dividend in cents (report when bet with dividend over)
    unsigned LONGLONG   hiinvracdu;  // High investment in cents (racing) (report when investment over)
    unsigned LONGLONG   hiinvsbdu;   // High investment in cents (football) 
                                     // Note: Set this value same as high 
                                     // investment (racing) until this is available on UI
};

// Account Bet Parameter type = bet transaction exception
struct AA_BCS_ACC_BET_TXN_EXC
{
    unsigned short        nor1:1;         // Normal, KL12
    unsigned short        key1:1;         // Key
    unsigned short        spk1:1;         // Super Key
    unsigned short        :5;             // not used
    unsigned short        highinv1:1;     // High investment
    unsigned short        highcan1:1;     // High cancel
    unsigned short        highinvsb1:1;   // High investment for football
    unsigned short        highcansb1:1;   // High cancel for football
    unsigned short        :4;             // not used
    unsigned LONGLONG   hiinvdu;        // High investment (in cents)
    unsigned LONGLONG   hicanceldu;     // High cancel (in cents)
    unsigned LONGLONG   hiinvsbdu;      // High investment for football (in cents)
    unsigned LONGLONG   hicancelsbdu;   // High cancel for football(in cents)
};

// Account Bet Parameter type = peak hour
struct AA_BCS_ACC_BET_PEAK_HR
{
    unsigned char       areabu;          // Area
        #define ABP_PEAK_ESC        1    // ESC
        #define ABP_PEAK_NONESC     2    // Non ESC
    unsigned char       racestsbu;       // Status, 1=Enabled, 2=Disabled
	unsigned char       fbstsbu;         // Status, 1=Enabled, 2=Disabled
    unsigned char       racemtgpeakhrbu; // Meeting peak hour (number of minutes per race)
    unsigned char       racpeakhrbu;     // Race peak hour (number of minutes per race)
    unsigned char       fbmtgpeakhrbu;   // Meeting peak hour for fb (number of minutes per race)
    unsigned char       fbpeakhrbu;      // fb peak hour (number of minutes per race)
    unsigned LONGLONG   mtgtotcostdu;    // Meeting peak total cost (in cents)
    unsigned LONGLONG   ractotcostdu;    // Race peak total cost (in cents)
    unsigned LONGLONG   mtgtotcostsbdu;  // Meeting peak total cost for football (in cents)
    unsigned LONGLONG   ractotcostsbdu;  // Race peak total cost for football (in cents)

};

// Account Bet Parameter type = Recall at BT
struct AA_BCS_ACC_BET_RCL_BT
{
    unsigned char       stsbu;           // Status, 1=Enabled, 2=Disabled
    unsigned short      numdaywu;        // Number of days for statement
};

// Account Bet Parameter type = Automatic Status Change
struct AA_BCS_ACC_BET_AU_STS_CHG
{
    unsigned char       stsbu;           // Status, 1=Enabled, 2=Disabled
    unsigned short      numdaywu;        // Number of days a/c without bet 
                                         // selling activities flagged frozen
};

// Account Bet Parameter type = Cash Deposit
struct AA_BCS_ACC_BET_CSH_DEP
{
    unsigned char        holdtm1:1;      // Hold time in minute
    unsigned char        tmrange1:1;     // Deposit time range
    unsigned char        minamt1:1;      // Min deposit amount
    unsigned char        :5;             // not used
    unsigned short      holdtimewu;     // Hold time in minute
    struct BCS_TIME     tmfrom;         // Deposit time range (From)
    struct BCS_TIME     tmto;           // Deposit time range (To)
    unsigned LONGLONG   minamtdu;       // Minimum deposit amount (in cents)
};

// Account Bet Parameter type = Minimum Withdrawal SI
struct AA_BCS_ACC_BET_MIN_WTD_SI
{
    unsigned char       stsbu;         // Status, 1=Enabled, 2=Disabled
    unsigned LONGLONG   amtdu;         // Amount (in cents)
};

// Account Bet Parameter type = Report Withdrawal Online Over
struct AA_BCS_ACC_BET_WTD_OVER
{
    unsigned char       stsbu;         // Status, 1=Enabled, 2=Disabled
    unsigned LONGLONG   amtdu;         // Amount (in cents)
};

// Account Bet Parameter type = Credit Background Reinbursement
struct AA_BCS_ACC_BET_BGREINB
{
    unsigned char       bggrpbu;         // BG group
    unsigned char       stsbu;           // Status, 1=Enabled, 2=Disabled
    unsigned short      numdaywu; 
};

// Account Bet Parameter details
union AA_BCS_ACC_BET_PARA_DET
{
    struct AA_BCS_ACC_BET_OET           oet;
    struct AA_BCS_ACC_BET_ACC_WTD       accwtd;
    struct AA_BCS_ACC_BET_ACC_BAL_EXC   accbalexc;
    struct AA_BCS_ACC_BET_TXN_EXC       txnexc;
    struct AA_BCS_ACC_BET_PEAK_HR       peakhr;
    struct AA_BCS_ACC_BET_RCL_BT        rclbt; 
    struct AA_BCS_ACC_BET_AU_STS_CHG    austschg;
    struct AA_BCS_ACC_BET_CSH_DEP       cshdep;
    struct AA_BCS_ACC_BET_MIN_WTD_SI    minwtdsi;
    struct AA_BCS_ACC_BET_WTD_OVER      wtdover;
    struct AA_BCS_ACC_BET_BGREINB       bgreinb;
};

// Account Bet Parameter (BCS->OLTP)
struct AA_BCS_ACCBETPARA
{
    unsigned short      typewu;     // Parameter type
        #define ABP_OET             0       // Online EFT transaction  
        #define ABP_ACC_WTD         1       // Account withdrawal 
        #define ABP_ACC_BAL_EXC     2       // Account balance exception 
        #define ABP_BET_TXN_EXC     3       // Bet transaction exception
        #define ABP_PEAK_HR         4       // Peak hour 
        #define ABP_RCL_BT          5       // Recall at BT
        #define ABP_AUTO_STS_CHG    6       // Automatic status change 
        #define ABP_CSH_DEP         7       // Cash Deposit
        #define ABP_MIN_WTD_SI      8       // Minimum Withdrawal SI
        #define ABP_RPT_WTD_OVER    9       // Report Withdrawal Online Over
        #define ABP_BGREINB         10      // Credit Background Reinbursement

    union AA_BCS_ACC_BET_PARA_DET   detail;
};


// Generate SI Withdrawal (BCS->OLTP)
//struct AA_BCS_SIWD
//{
//    unsigned char       flagbu;     // generate flag, true = 1, false = 0
//};

// Generate Bank Guarantee (BCS->OLTP)
struct AA_BCS_BANKGT
{
    unsigned char       bggrpbu;    // BG group
    unsigned char       flagbu;     // generate flag, true = 1, false = 0
};

// Credit Background Reinbursement (BCS->OLTP) KL31
struct AA_BCS_BGREINB
{
    struct BCS_DATE     date;       // Generate date, year
    unsigned char       bggrpbu;    // BG group
    unsigned char       daybu;      // Parameter - Credit Reimbursement for N Days
    unsigned char       flagbu;     // generate flag, true = 1, false = 0
    struct BCS_DATE     nxtbusdate; // Next Business Date
};

//CSC Issue (2011IBT)
struct AA_BCS_CSCISSREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    struct AA_CUSINFO   cusinfo;     // Acc Info
    unsigned int        seccodelu;   // Security Code
    unsigned LONGLONG   csccardid;   // CSC Card ID
    unsigned LONGLONG   cscdepfee;   // Card deposit fee (in cent)
};

//CSC Card Replace Request (2011IBT)
struct AA_OLTP_CSCRPLREQ
{
    unsigned int        accno;   // Account number
    unsigned LONGLONG   oldcscid;   // Old CSC card ID
    unsigned LONGLONG   newcscid;   // New CSC card ID
    unsigned char   fdepfee;   // Forfeit old card deposit fee (0=FALSE,1=TRUE)
    unsigned char   wdepfee;   // Waive new card deposit fee (0=FALSE,1=TRUE)
};

//CSC Card Replace Reply (2011IBT)
struct AA_OLTP_CSCRPLRPY
{
    unsigned LONGLONG   refamt;   // Refund amount for old CSC card (in cents)
    unsigned LONGLONG   depamt;   // Deposit amount for new CSC card (in cents)
};

//CSC Card Return Request (2011IBT)
struct AA_OLTP_CSCRETREQ
{
    unsigned int        accno;  //Account number
    unsigned LONGLONG   cscid;  //CSC card ID
    unsigned char   fordep;  //Forfeit deposit (0=FALSE,1=TRUE)
    LONGLONG   accbal;  //Account Balance (in cents)
};

//CSC Card Return Reply (2011IBT)
struct AA_OLTP_CSCRETRPY
{
    unsigned LONGLONG   refamt;   // Refund amount for CSC card (in cents)
};

// Reverse Annual Fee (BCS->OLTP)
struct AA_BCS_REVANLFEE
{
    unsigned char       flagbu;     // reverse flag, true = 1, false = 0
};

// RL38..
// Bank Guarantee Reimbursement Schedule (BCS->OLTP)
struct AA_BCS_BGTAPE
{
    struct BCS_DATE         date;
    unsigned short          elapsewu;
    unsigned char           bgtypebu;
    BOOL                    reimt;
};
struct AA_BCS_BGSCHEDULE
{
    unsigned short          nwu;
    struct AA_BCS_BGTAPE    bgtape[100];
};
// ..RL38

// ********** BCS  -> OLTP Real-Time message **********

// Account Open Request (BCS->OLTP)  (before Q210)
struct AA_BCS_ACCOPENREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    struct AA_CUSINFO   cusinfo;     // Acc Info
//    char                bankaccs[AA_BANKACC_LEN];   // Nominate Bank Acc(Bank# brh# a/c#)
    struct AA_BANKACCNUM nba;        // Nominate Bank account, KL31
    unsigned int        seccodelu;   // Security Code
    unsigned char       forcebu;     // Force to change securtiy code
        #define AA_FORCE        0    // FALSE
        #define AA_NOTFORCE     1    // TRUE
};

// Account Open Request (BCS->OLTP)  (after Q210)
struct AA_BCS_ACONEWREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    struct AA_CUSINFO   cusinfo;     // Acc Info
//    char                bankaccs[AA_BANKACC_LEN];   // Nominate Bank Acc(Bank# brh# a/c#)
    unsigned int        seccodelu;   // Security Code
	unsigned char       forcebu;     // Force to change securtiy code
	unsigned char       bankind1;     // Force to change securtiy code
    struct AA_BANKACCNUM nba1;        // Nominate Bank account1
	unsigned char       bankind2;     // Force to change securtiy code
    struct AA_BANKACCNUM nba2;        // Nominate Bank account1
	unsigned char       resacc;     //	Restricted acount
	char				onlinerefno[13];	// Online application reference number
	unsigned char		ewalletonly;  //ewallet only flag:0 = False, 1 = True
};



struct AA_BCS_ACC_DET_ACCINFO
{
    struct AA_CUSINFO   cusinfo;    // Acc Info
    unsigned char       accstatusbu; // Account status
        #define AA_OPEN     1       // open
        #define AA_DORMANT  2       // dormant
        #define AA_FROZEN   3       // frozen
	unsigned char		ewalletonly;  //ewallet only flag:0 = False, 1 = True
};

//  before Q210
union AA_BCS_ACC_DET  
{
    struct AA_BCS_ACC_DET_ACCINFO   accsinfo;       // Acc Info
//    char                nbas[AA_BANKACC_LEN];       // Nominate Bank Account
    struct AA_BANKACCNUM            nba;    // Nominate Bank account, KL31
};

//Q210 new structure for details -- different from loggerAB spec
union AA_BCS_ACC_DET_NEW
{
    struct AA_BCS_ACC_DET_ACCINFO   accsinfo;       // Acc Info
//    char                nbas[AA_BANKACC_LEN];       // Nominate Bank Account
    struct AA_BCS_ACC_DET_BANK_INFO_NEW  nba;    // Nominate Bank account, KL31
};


// Account Details Update (BCS->OLTP)  (before Q210)
struct AA_BCS_ACCUPDREQ
{
    struct AA_ACCINFO   accinfo;        // Account info
    unsigned char       acctypebu;      // Account details type
        #define ACCUPD_ACCINFO     1    // Account info
        #define ACCUPD_BANKINFO    2    // Bank info
        #define ACCUPD_LMAT        100  // KL28, for LMAT, 
                                        //  update accstatusbu in accsinfo only
    union AA_BCS_ACC_DET   accdet;      // Acc details
};


// Account Details Update NEW after Q210
struct AA_BCS_ACUNEWREQ
{
    struct AA_ACCINFO   accinfo;        // Account info
    unsigned char       acctypebu;      // Account details type
        #define ACCUPD_ACCINFO     1    // Account info
        #define ACCUPD_BANKINFO    2    // Bank info
        #define ACCUPD_LMAT        100  // KL28, for LMAT, 
                                        //  update accstatusbu in accsinfo only
    union AA_BCS_ACC_DET_NEW   accdet;      // Acc details
};



// Account Details Update Reply (BCS->OLTP)
struct AA_BCS_ACCUPDRPY
{
    LONGLONG  balanced;                 // Account balance
};

// Account Details Request
//struct AA_BCS_ACCDETREQ
//{
//    struct AA_ACCINFO      accinfo;     // Account info
//    unsigned char          detcodebu;   // Detail code
//};

// Change of Security Code (BCS->OLTP)
struct AA_BCS_CHGSECREQ
{
    struct AA_ACCINFO   accinfo;      // Account info
    unsigned int        newseccodelu; // New security code
    unsigned char       forcebu;      // Force to change securtiy code, 1=TRUE
    unsigned char       unlockvoicebu; // Unlock Voice Channel, 1=TRUE
};

// Account close (BCS->OLTP)
struct AA_BCS_ACCCLSREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    unsigned LONGLONG   wdamtdu;     // Withdrawal amount (in cents)
    unsigned char       wdtypebu;    // Withdrawal type
        #define CASH     1           // Cash
        #define AUTOPAY  2           // Autopay
        #define CHEQ     3           // Cheque
};

// Online statement
// Continue ID
struct AA_BCS_OLSTAT_CONID
{
    unsigned int        blocklu;     // Block number
    unsigned short      blkoffwu;    // block offset
    unsigned short      trnoffwu;    // transaction offset
    unsigned short      filewu;      // file number
};

// Online statement request (BCS->OLTP)
struct AA_BCS_OLSTATREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    struct BCS_DATE     date;        // Request date
    char                typeb;       // 'S'=start, 'M'=continue
        #define STA     'S'          // Start
        #define CON     'M'          // Continue KL08
    struct AA_BCS_OLSTAT_CONID  conidb;  // Continue ID
    unsigned char       txncatbu;    // Txn category
        #define OLREQALL     0            // all
        #define OLREQLOT     1            // lottery
        #define OLREQRAC     2            // racing
        #define OLREQCATWTD     3            // withdrawal
        #define OLREQCATCAN     4            // cancel
        #define OLREQCATSB      5            // SB
        #define OLREQCATDEP     6            // deposit
};

// KL14..
// Transaction key
// FB
struct AA_BCS_OLSTAT_TXNKEY_SB
{
    unsigned char       daybu;      // match day
    unsigned char       numbu;      // match num
    unsigned char       poolbu;     // pool ID
    unsigned char       typebu;     // 0 = Fixed Odds, 1 = Pari-Mutuel
    unsigned char       aupbu;      // allup flag
};

// Lottery
struct AA_BCS_OLSTAT_TXNKEY_LOT
{
    unsigned short      yearwu;     // draw year
    unsigned short      numwu;      // draw number
    unsigned short      typeu;      // lot type
};

// Racing
struct AA_BCS_OLSTAT_TXNKEY_RAC
{
    unsigned char       locbu;      // meeting location
    unsigned char       daybu;      // meeting day
    unsigned char       numbu;      // racing number
    unsigned char       typebu;     // bet type
    unsigned char       aupbu;      // allup flag
};
// ..KL14

// Online statement reply TXN (OLTP->BCS)
struct AA_OLTP_OLSTATTXN
{
    unsigned int        txnnumlu;     // Txn num of this txn
    unsigned char       txnflgbu;     // Txn category
        #define OLRPYNOR     0             // Normal
        #define OLRPYCAN     1             // Cancelled
        #define OLRPYDIVOF   2             // Dividend overflow
        #define OLRPYREVERSE 4             // Reversed
        #define OLRPYSETTLED 8		   // Settled	    //HL30

        
    unsigned short      txntypewu;    // Txn type
#define TXN_AT_CALL_HDR            1  // AT Call Header
#define TXN_AUTO_ACC_ACS           2  // Auto Account Access
#define TXN_RAC_BET                3  // Racing bet
#define TXN_MK6                    4  // MK6
#define TXN_WTD_CASH               5  // Withdrawal (cash)
#define TXN_WTD_EFT                6  // Withdrawal (EFT online)
#define TXN_WTD_AUTOPAY            7  // Withdrawal (autopay)
#define TXN_WTD_CHEQ               8  // Withdrawal (cheque)
#define TXN_CAN_MK6                9  // Cancel (MK6)
#define TXN_CAN_BET                10 // Cancel (bet)
#define TXN_CAN_WTD                11 // Cancel (withdrawal)
#define TXN_STAT_REQ               12 // Statement request
#define TXN_DET_ADJ_ESC_DEP_FEE    13 // Debit adjustment (ESC deposit fee)
#define TXN_DET_ADJ_ESC_DEP_FOR    14 // Debit adjustment (ESC deposit fee forfeited)
#define TXN_DET_ADJ_DISHON_CHEQ    15 // Debit adjustment (dishonoured cheque)
#define TXN_DET_ADJ_REJ_REIMB      16 // Debit adjustment (rejected reimbursement)
#define TXN_DET_ADJ_BAD_DET_WRT_IN 17 // Debit adjustment (bad debt write in)
#define TXN_DET_ADJ_REV_ENT        18 // Debit adjustment (reversing entry)
#define TXN_CDT_ADJ_CHEQ_DEP       19 // Credit adjustment (cheque deposit)
#define TXN_CDT_ADJ_EXG_PAY        20 // Credit adjustment (exgratia payment)
#define TXN_CDT_ADJ_BAD_DET_WRT_IN 21 // Credit adjustment (bad debt write out)
#define TXN_CDT_ADJ_REV_ENT        22 // Credit adjustment (reversing entry)
#define TXN_CDT_ADJ_ESC_DEP_REF    23 // Credit adjustment (ESC deposit fee refund)
#define TXN_STA_DAT_CHG_DTL        24 // Static data change (details)
#define TXN_STA_DAT_CHG_CALL_TFR   25 // Static data change (call transfer)
#define TXN_STA_DAT_CHG_MEMO       26 // Static data change (memorandum)
#define TXN_ACC_REL                27 // Account release
#define TXN_CHG_WTD_AUTO_PAY       28 // Change to withdrawal S.I.  (autopay)
#define TXN_CHG_WTD_CHEQ           29 // Change to withdrawal S.I.  (cheque)
#define TXN_CHG_WTD_DEL            30 // Change to withdrawal S.I.  (delete)
#define TXN_CHG_MK6_CHG            31 // Change to MK6 S.I. (change)
#define TXN_CHG_MK6_DEL            32 // Change to MK6 S.I. (delete)
#define TXN_SOD_BAL                33 // Start of day balance
#define TXN_CHG_BG_NEW             34 // Change of bank guarantee (new)
#define TXN_CHG_BG_OLD             35 // Change of bank guarantee (new for old)
#define TXN_CHG_BG_DEL             36 // Change of bank guarantee (delete)
#define TXN_CHG_BG_REIMB           37 // Bank guarantee reimbursement
#define TXN_OPEN_ACC               38 // Open account 
#define TXN_ISS_CARD               39 // Issue card 
#define TXN_REPL_CARD              40 // Replace card
#define TXN_CARD_REPL_BY           41 // Card replaced by
#define TXN_CB_BT_CALL_HDR         42 // CB BT call header
#define TXN_DIV_CDT_CUR_CARD       43 // Dividend credited (current card)
#define TXN_DIV_CDT_OLD_CARD       44 // Dividend credited (old card)
#define TXN_DEP_CASH               45 // Deposit (cash)
#define TXN_DEP_EFT                46 // Deposit (EFT online)
#define TXN_DEP_PAYOUT             47 // Deposit (payout)
#define TXN_MO_BET_DEP             48 // Mobile Betting Deposit / Withdrawal Recharge
#define TXN_ATM_DEP_WTD_RCG        49 // ATM Deposit / Withdrawal Recharge
#define TXN_MPT_DEP_WTD_RCG        50 // MPT Deposit / Withdrawal Recharge
#define TXN_INT_DEP_WTD_RCG        51 // Internet Deposit / Withdrawal Recharge
#define TXN_TWM_DEP_WTD_RCG        52 // TWM Deposit / Withdrawal Recharge
#define TXN_CIT_DEP_WTD_RCG        53 // CIT Deposit / Withdrawal Recharge
#define TXN_PDA_DEP_WTD_RCG        54 // PDA Deposit / Withdrawal Recharge
#define TXN_BE_CALL_HDR            55 // BT Call Header
#define TXN_EWIN_CALL_HDR          56 // EWIN Call Header
#define TXN_CIT_CALL_HDR           57 // CIT Call Header
#define TXN_DEP_CALL_HDR           58 // BT Deposit Call Header
#define TXN_BAT_DEP_CALL_HDR       59 // Batch Deposit Call Header
#define TXN_EFT_DEP_CALL_HDR       60 // EFT Deposit Call Header
#define TXN_CLS_ACC                61 // Close Account
#define TXN_PAN_CAP                62 // PAN Capture
#define TXN_CIT_ANN_FEE_REV        63 // CIT annual fee reverse
#define TXN_SB                     64 // SB
#define TXN_SB_DIV                 65 // SB Dividend
#define TXN_SB_DIV_FOR             66 // SB Dividend Forfeited
#define TXN_CAN_SB                 67 // Cancel SB
#define TXN_ATM_DEP                68 // ATM deposit
#define TXN_CIT_DEP_REF            69 // CIT Deposit refund
#define TXN_CIT_DEP                70 // CIT Deposit
#define TXN_CIT_ANN_FEE            71 // CIT annual fee
#define TXN_CIT_ANN_FEE_REF        72 // CIT annual fee refund
#define TXN_CIT_NEW_ANN_FEE        73 // CIT new annual fee
#define TXN_CIT_ANN_FEE_WAIV       74 // CIT annual fee waived
#define TXN_CIT_PRG_DEP_REF        75 // CIT progressive deposit refund

//HL20...
// #define TXN_DIV_PURGED_TRAN        76 // div for purged tran // HL02
// #define TXN_DIV_SETTLED_TODAY      77 // dividend settled today // HL02

//HL21... 
    #define TXN_DEBIT_CDC       76  // CASH DEPOSIT CLAIM
    #define TXN_DEBIT_SACCDCS   77  // SUSPENSE A/C TO CASH DEPOSIT 
                                    //  CLAIM SETTLEMENT
    #define TXN_DEBIT_EFTDC     78  // EFT DEPOSIT CLAIM
    #define TXN_DEBIT_SACEFTDCS 79  // SUSPENSE A/C TO EFT DEPOSIT CLAIM 
                                    //  SETTLEMENT
    #define TXN_DEBIT_DBS       80   // DEPOSIT BAD SALES
    #define TXN_DEBIT_DSHCQ     81   // DISHONOURED CHEQUE
    #define TXN_DEBIT_RBGIM     82   // REJECTED BG REIMBURSEMENT
    #define TXN_DEBIT_DFCCA     83   // DEBIT FROM CHEQUE CONTROL ACCOUNT
    #define TXN_DEBIT_DCACWO    84   // DORMANT CONTROL A/C W/OUT
    #define TXN_DEBIT_EWUPS     85  // EFT WITHDRAWAL NOT POSTED
    #define TXN_DEBIT_EWTMO     86  // EFT BANK TIME OUT WITHDRAWAL
    #define TXN_DEBIT_CITWNP    87  // CIT WITHDRAWAL NOT POSTED
    #define TXN_DEBIT_CITBTOW   88  // CIT BANK TIME OUT WITHDRAWAL
    #define TXN_DEBIT_ESCEWNP   89  // ESC EFT WITHDRAWAL NOT POSTED
    #define TXN_DEBIT_ESCEBTO   90  // ESC EFT BANK TIME OUT
    #define TXN_DEBIT_UBSDIV    91  // UBS DIVIDEND
    #define TXN_DEBIT_BOFLTF    92  // BALANCE OVERFLOW TRANSFER
    #define TXN_DEBIT_EACEODR   93  // EMERGENCY A/C EOD REVERSING ENTRY 
                                    //  (RACEDAY ONLY)
    #define TXN_DEBIT_CITAF     94  // CIT ANNUAL FEE
    #define TXN_DEBIT_CITDF     95  // CIT DEPOSIT FORFEITED
    #define TXN_DEBIT_CITPDAD   96  // CIT / PDA DEPOSIT
    #define TXN_DEBIT_CITRMC    97  // CIT R & M CHARGES
    #define TXN_DEBIT_BCFPDA    98  // BATTERY CHARGES FOR PDA
    #define TXN_DEBIT_DFAFFT    99  // DEBIT GFBC ACCCOUNT FOR FUND TRANSFER
    #define TXN_DEBIT_ESCDF     100 // ESC DEPOSIT FEE
    #define TXN_DEBIT_ESCFDF    101 // ESC FORFEITED DEPOSIT FEE
    #define TXN_DEBIT_BDWRI     102 // BAD DEBT WRITE IN
    #define TXN_DEBIT_SACWO     103 // SUSPENSE A/C WRITE OUT
    #define TXN_DEBIT_OUTDC     104 // OUTSTANDING DR/CR FOR DORMANT A/C REJ W/D
    #define TXN_DEBIT_DIPFRS    105 // DIVIDEND PROFIT - RS
    #define TXN_DEBIT_DIPFFS    106 // DIVIDEND PROFIT - FS
    #define TXN_DEBIT_DIPFLS    107 // DIVIDEND PROFIT - LS
    #define TXN_DEBIT_REVENT    108 // REVERSING ENTRY
    #define TXN_DEBIT_OTHERS    109 // DEBIT ADJUSTMENT - OTHERS

    #define TXN_CREDIT_CDCTSAC  110 // CREDIT CASH DEPOSIT CLAIM TO 
                                    //  SUSPENSE A/C
    #define TXN_CREDIT_CDCS     111 // CASH DEPOSIT CLAIM SETTLEMENT
    #define TXN_CREDIT_EFTDCTSA 112 // CREDIT EFT DEPOSIT CLAIM TO SUSPENSE A/C
    #define TXN_CREDIT_EFTDCS   113 // EFT DEPOSIT CLAIM SETTLEMENT
    #define TXN_CREDIT_CQDHOC   114 // CHEQUE DEPOSIT - H.Q. / ON-COURSE
    #define TXN_CREDIT_CDHOC    115 // CASH DEPOSIT - HQ / ON-COURSE
    #define TXN_CREDIT_CCQWD    116 // CANCELLED CHEQUE W/D
    #define TXN_CREDIT_CCQDTAC  117 // CREDIT CHEQUE DEPOSIT TO RELEVANT A/C
    #define TXN_CREDIT_EWUPS    118 // EFT WITHDRAWAL NOT POSTED SETTLEMENT
    #define TXN_CREDIT_EFTBTOS  119 // EFT BANK TIME OUT SETTLEMENT
    #define TXN_CREDIT_CITDNP   120 // CIT DEPOSIT NOT POSTED
    #define TXN_CREDIT_CITBTOS  121 // CIT BANK TIME OUT SETTLEMENT
    #define TXN_CREDIT_ESCEDNP  122 // ESC EFT DEPOSIT NOT POSTED
    #define TXN_CREDIT_ESCWP    123 // ESC EFT WITHDRAWAL POSTED
    #define TXN_CREDIT_UBSRF    124 // UBS REFUND
    #define TXN_CREDIT_BOFLTF   125 // BALANCE OVERFLOW TRANSFER
    #define TXN_CREDIT_EACSODR  126 // EMERGENCY A/C SOD REVERSING ENTRY 
                                    //  (RACEDAY ONLY)
    #define TXN_CREDIT_CITAFR   127 // CIT ANNUAL FEE REFUND
    #define TXN_CREDIT_RCITD    128 // REINSTATE CIT DEPOSIT
    #define TXN_CREDIT_CITPDADR 129 // CIT / PDA DEPOSIT REFUND
    #define TXN_CREDIT_CITRMCR  130 // CIT R & M CHARGES REFUND
    #define TXN_CREDIT_CITDRP   131 // CIT DEPOSIT REFUND - PROGRESSIVE
    #define TXN_CREDIT_TAFCITD  132 // TRANSFER ADJUSTMENT FOR CIT DEPOSIT
    #define TXN_CREDIT_TADJ     133 // TRANSFER ADJUSTMENT
    #define TXN_CREDIT_ESCDR    134 // ESC DEPOSIT FEE REFUND
    #define TXN_CREDIT_FTTGFBC  135 // FUND TRANSFER TO GFBC ACCOUNT
    #define TXN_CREDIT_BDWRO    136 // BAD DEBT WRITE OUT
    #define TXN_CREDIT_SACWIDC  137 // SUSPENSE A/C WRITE IN - DEPOSIT CLAIM
    #define TXN_CREDIT_SACWICD  138 // SUSPENSE A/C WRITE IN - CIT DEPOSIT
    #define TXN_CREDIT_RWDDAC   139 // REJ. W/D DORMANT A/C
    #define TXN_CREDIT_REJWTW   140 // REJECTED WITHDRAWAL
    #define TXN_CREDIT_RWFCAC   141 // REJECTED WITHDRAWAL FROM CLOSED ACCOUNT
    #define TXN_CREDIT_ABFN     142 // ABFN
    #define TXN_CREDIT_OCUBRS   143 // OVER COLLATION/UNACTIONED BAD SALES - RS
    #define TXN_CREDIT_OCUBFS   144 // OVER COLLATION/UNACTIONED BAD SALES - FS
    #define TXN_CREDIT_OCUBLS   145 // OVER COLLATION/UNACTIONED BAD SALES - LS
    #define TXN_CREDIT_EXGPRS   146 // EXGRATIA PAYMENT - RS
    #define TXN_CREDIT_EXGPFS   147 // EXGRATIA PAYMENT - FS
    #define TXN_CREDIT_EXGPLS   148 // EXGRATIA PAYMENT - LS
    #define TXN_CREDIT_MBGRIN   149 // MANUAL BG REIMBURSEMENT
    #define TXN_CREDIT_REVENT   150 // REVERSING ENTRY
    #define TXN_CREDIT_OTHERS   151 // CREIT ADJUSTMENT - OTHERS
//...HL21

// The following are system generated credit debit adjustment
#define TXN_CREDIT_FESCB          152 // Balance Transferred From ESC
#define TXN_DEBIT_TVOIB           153 // Balance Transferred To Voice
#define TXN_CREDIT_BGRIM          154 // Bank Gaurantee Reimbursement 
//...HL09
//HL11...
#define TXN_STATEMENT_CHARGE      155 // statement charge
#define TXN_OS_ESC_TRAN_DIV       156 // dividend of outstanding ESC transaction
//...HL11

//HL20...
#define TXN_DEBIT_SYSFOFDF        157   // Forfeited Deposit Fee By System //HL19
					// change to "ESC FORFEITED DEPOSIT
					//	      FEE" 
//...HL20
// HL34 12-Nov-2004...
//HL24...
#define TXN_CITDFT                158   // AUTO CIT DEPOSIT FORFEITED
#define TXN_ESCDFT                159   // AUTO ESC DEPOSIT FORFEITED
#define TXN_ESC_DEP		  160	// AUTO ESC DEPOSIT

// HL27 #define TXN_CB_ESC_CALL_HDR       161	// CB ESC call header	//HL26

//...HL24
#define TXN_CIT_ANNUALFEE 	  162	// AUTO CIT ANNUAL FEE
#define TXN_CIT_DEPOSIT 	  163	// AUTO CIT DEPOSIT
#define TXN_CIT_DEPOSIT_REFUND	  164   // AUTO CIT DEPOSIT REFUND
#define TXN_CIT_DEPOSIT_REFUND_PRO  165 // AUTO CIT DEPOSIT REFUND - PROGRESSIVE
#define TXN_CIT_ANNUALFEE_REFUND  166	// AUTO CIT ANNUAL FEE REFUND
#define TXN_ESC_DEP_REFUND	  167	// AUTO ESC DEPOSIT REFUND
// ...HL34 12-Nov-2004



    LONGLONG   detamtd;      // Debit amount (in cents)     //HL01
    LONGLONG   cdtamtd;      // Credit amount (in cents)    //HL01
    char                txndetb[AA_MAX_BUF_SIZE]; // Transaction details, Separator (0x1C)
                                       // check max length later
};

// Online statement reply  (OLTP->BCS)
struct AA_OLTP_OLSTATRPY
{
    char                typeb;       // 'E'=End of Reply, 'M'=continue
        #define END     'E'          // End
    struct AA_BCS_OLSTAT_CONID  conidb;  // Continue ID
    unsigned short      numtxnwu;    // No of Txn
//...........
};

// *** Debit/Credit Transaction ***
// Request (BCS->OLTP)
struct AA_BCS_DETCDTREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    unsigned char        type1:1;     // off=debit, on=credit
    unsigned char        negbal1:1;   // 1 = allow -ve balance
    unsigned char        :6;          // not used
    unsigned LONGLONG   amtdu;       // Amount (in cents)
    unsigned short      txntypewu;   // KL04 refer to drcrtxndef.h
        #define DRCR_TXN_DIFF   200     // The different between the AA txn number
                                        // and OLTP internal txn number.
        #define DRCR_TXN_MAP(e)  e - DRCR_TXN_DIFF   // The formula
    char                remarks[AA_DRCR_RMK_LEN];  // remark

};

// Reply (OLTP->BCS)
struct AA_OLTP_DETCDTRPY
{
    unsigned int      txnlu;    // No of Txn
};

// *** Validate Bet ***
// Request (BCS->OLTP)
struct AA_BCS_VALBETREQ
{
    unsigned char       bettypebu;   // Bet type
        #define BT_MK6  1            // Mark 6
        #define BT_GB   2            // Gold Ball

    unsigned char       gametypebu;  // Game type
        #define GT_NOR  0            // Normal
        #define GT_RES  1            // Reserved
        #define GT_EOC  2            // Even-odd Chain
        #define GT_MAT  3            // Matching Game
        #define GT_EXT  4            // Extra Number
        #define GT_OUT  5            // Outsiders

    unsigned int        baseinvlu;   // Base investment (in cents)
    char                selb[AA_MAX_BUF_SIZE];  // Selections, check max length later
};

// Reply (OLTP->BCS)
struct AA_OLTP_VALBETRPY
{
    unsigned LONGLONG   totcostdu;   // Total cost (in cents)
    char                expselb[AA_MAX_BUF_SIZE];  // Expanded Selections, check max length later
};

// *** Unsatisfied Lottery SI Posting ***
// Request (BCS->OLTP)
struct AA_BCS_UNSATLOTSIREQ
{
    unsigned int        accnumlu;    // Account number
};

// *** Unsettled transaction retrieval ***
// request (BCS->OLTP)
struct AA_BCS_UNSETTXNRETREQ
{
    struct AA_ACCINFO   accinfo;     // Account info
    char                typeb;       // 'S'=start, 'M'=continue
    char                conidb[AA_CONID_LEN];  // Continue ID
    unsigned char       txntypebu;   // Unsettled transaction type
        #define TT_PBG  1            // Pending BG
        #define TT_ULSI 2            // Unsatisfied lottery SI
        #define TT_UC   3            // Unclear cheque
};

// Pending BG reply TXN
struct AA_BCS_UNSETPENDBGTXN
{
    unsigned int        txnnumlu;    // Txn num of this txn
    unsigned LONGLONG   detamtdu;    // Debit amount (in cents)
    struct BCS_DATE     date;        // Generation date
    unsigned char       bgtypebu;    // Bank guarantee type
};

// Unsatisfied Lottery SI reply TXN
struct AA_BCS_UNSETUNSATLOTSITXN
{
    unsigned int        txnnumlu;    // Txn num of this txn
    unsigned LONGLONG   totamtdu;    // Total amount (in cents)
    unsigned int        baseinvlu;   // Base investment (in cents)
    char                silotdtlb[AA_MAX_BUF_SIZE];   // SI lottery details, Separator (0x1C)
};

// reply (OLTP->BCS)
struct AA_OLTP_UNSETTXNRPY
{
    char                typeb;       // 'E'=End of Reply, 'M'=continue
    char                conidb[AA_CONID_LEN];  // Continue ID
    unsigned short      numtxnwu;    // No of Txn
//...........
};

// *** Registration of SI Withdrawal ***
// request (BCS->OLTP)
//struct AA_BCS_REGSIWTDREQ
//{
//    struct AA_ACCINFO   accinfo;     // Account info
//    unsigned char       wdtypebu;       // Withdrawal type
//    unsigned int        reslu;          // Residual (in cents)
//};

// *** Rejected Bank Guarantee Reimbursement ***
// request (BCS->OLTP)
struct AA_BCS_REJBGREIMBREQ
{
    struct AA_ACCINFO  accinfo;     // Account info
    struct BCS_DATE    date;        // Request date

};

// *** Release Terminal ***
// request (BCS->OLTP)
struct AA_BCS_RELTERMREQ
{
    char                termidb[AA_TERMID_LEN];    // Terminal ID
};

// reply (OLTP->BCS)
struct AA_OLTP_RELTERMRPY
{
    unsigned int        accnumlu;      // Account number
    LONGLONG            accbald;       // Current account balance

};

// *** All-up Explosion ***
// request (BCS->OLTP)
struct AA_BCS_ALLUPEXPREQ
{
    struct AA_ACCINFO  accinfo;     // Account info
    struct BCS_DATE    date;        // Request date
    unsigned int       txnnumlu;    // Transaction number
};

// reply (OLTP->BCS)
// struct AA_OLTP_ALLUPEXPRPY -> 
// struct MAIL_BCS_AXPRPY from mailbadef.h


// *** Call Transfer Request ***
// request (BCS->OLTP)
struct AA_BCS_CALTRFREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       trfareabu;     // Call transfer area code
};

// *** Account Range Request ***
//struct AA_OLTP_ACCRANGE
//{
//    unsigned int        straccnumlu;   // Start account number
//    unsigned int        endaccnumlu;   // End account number
//};

// reply (OLTP->BCS)
struct AA_OLTP_ACCRANGERPY
{
    unsigned short      numacclu;      // Number of account range
};

// *** Reset PAN capture ***
struct AA_BCS_RESETPANREQ
{
    unsigned int        accnumlu;      // Account number
};

// *** Account fund analysis
// *** Account balance for account closure     // RL38
struct AA_BCS_ACCFUNDREQ
{
    unsigned int        accnumlu;      // Account number
};

struct AA_OLTP_ACCFUNDRPY
{
    LONGLONG            sodbald;        // SOD balance (in cents)
    unsigned LONGLONG   cashdepdu;      // cash deposit (in cents)
    unsigned LONGLONG   withdrawdu;     // withdrawal (in cents)
    unsigned LONGLONG   pminvestdu;     // investment - parimutuel (in cents)
    unsigned LONGLONG   foinvestdu;     // investment - fixed odds (in cents)
    unsigned LONGLONG   pmdividenddu;   // dividend - parimutuel (in cents)
    unsigned LONGLONG   fodividenddu;   // dividend - fixed odds (in cents)
    unsigned LONGLONG   divforfeitdu;   // dividend forfeited (in cents)
    unsigned LONGLONG   debitdu;        // debit adjustment (in cents)
    unsigned LONGLONG   creditdu;       // credit adjustment (in cents)
    unsigned LONGLONG   bgamtdu;        // bank guarantee amount (in cents)
    LONGLONG            fundavad;       // funds available for betting (in cents)
};

// *** Change of account status ***
//struct AA_BCS_CHGACCSTATUSREQ
//{
//    struct AA_ACCINFO  accinfo;     // Account info
//    unsigned char      accstatus;   // new account status
//        #define AA_ACCSTATUS_OPEN   1   // open
//        #define AA_ACCSTATUS_FROZEN 2   // frozen
//};

// KL10..
// *** Monitored Account ***
// request (BCS->OLTP)
struct AA_BCS_MONIACCREQ
{
    unsigned int        accnumlu;    // Account number
    unsigned char       actionbu;    // new account status
        #define AA_MONIACC_MONI    0   // Monitor the account
        #define AA_MONIACC_NOTMONI 1   // Do not monitor the account
};

// *** Account Parameters ***
// request (BCS->OLTP)
struct AA_BCS_ACCPARAREQ
{
    unsigned int        accnumlu;    // Account number
    unsigned char       minolwtdamtstsbu;    // Minimum Online Withdrawal Status
    unsigned LONGLONG   minolwtdamtdu;       // Minimum Online Withdrawal Amount (in cents)
    unsigned char       maxdayolamtstsbu;    // Maximum Daily Online Status
    unsigned LONGLONG   maxdayolamtdu;       // Maximum Daily Online Amount (in cents)
    unsigned char       maxdayolwtdcntstsbu; // Maximum Daily Online Withdrawal Status
    unsigned char       maxdayolwtdcntbu;    // Maximum Daily Online Withdrawal Count
    unsigned char       maxdaycashwtdamtstsbu; // Maximum Daily Cash Withdrawal Amount Status
    unsigned LONGLONG   maxdaycashwtdamtdu;    // Maximum Daily Cash Withdrawal Amount (in cents)
    unsigned char       maxdaycashwtdcntstsbu; // Maximum Daily Cash Withdrawal Count Status
    unsigned char       maxdaycashwtdcntbu;    // Maximum Daily Cash Withdrawal Count
};

// *** New Account status ***
// request (BCS->OLTP)
struct AA_BCS_NEWACCSTATUSREQ
{
    unsigned int        accnumlu;    // Account number
    unsigned char       accstatusbu; // new account status
//        #define AA_ACCPARA_OPEN    1   // open
//        #define AA_ACCPARA_DORMANT 2   // dormant
//        #define AA_ACCPARA_FROZEN  3   // frozen
};

// *** Statement Charge ***
struct AA_BCS_STMCHRGREQ
{
    struct AA_ACCINFO  accinfo;     // Account info
    unsigned LONGLONG  amtdu;       // Charged Amount (in cents)
    struct BCS_DATE    fromdate;    // from date
    struct BCS_DATE    todate;      // to date
};

// .. KL10

// *** Channel lock ***
struct AA_BCS_CHANLOCKREQ
{
    unsigned int        accnumlu;    // Account number
    unsigned char       chanbu;      // channel type
        #define AA_CHAN_LOCK_VOICE 0    // voice
    unsigned char       lockbu;      // lock/unlock flag
        #define AA_UNLOCK 0    // unlock
        #define AA_LOCK   1    // lock
};

// KL15..

// *** Account FB Limit ***
struct AA_BCS_ACCFBLMTREQ
{
    unsigned int        accnumlu;      // Account number
    unsigned char       typebu;        // FB Type
};

struct AA_OLTP_ACCFBLMTRPY
{
    unsigned LONGLONG   maxinvdu;      // Daily Maximum Investment for Fixed Odds
    unsigned LONGLONG   maxpaydu;      // Daily Maximum Payout for Fixed Odds
};


// ..KL15


// *** Forced Account Release ***
// request (BCS->OLTP)
struct AA_BCS_FORACCRELREQ
{
    unsigned int        accnumlu;      // Account number
};

// *** Account Active ***
// KL25.. Reply message when Account is Active (OLTP->BCS)
struct AA_OLTP_ACCACTRPY
{
    char                acclocks[AA_ALD_LEN];   // Account lock details
};

// ..KL25

// ********** Mail Header **********

struct MAIL_MATHNDR_SUBHDR_AB
{
    // Common Header, should be in mailhdrdef.h
    // Mathdr
    unsigned int        lasttxnidlu;    // last txn id
    unsigned int        msgtxnidlu;     // msg txn id
    struct BCS_DATE     date;           // Generate date
    struct BCS_TIME     time;           // Generate time
    unsigned int        locidlu;        // location id
    unsigned short      posnowu;        // position number
    char                termidb[BCS_TERMID_SIZ];    // terminal id
    unsigned int        staffidlu;      // staff id
    unsigned int        logtermidlu;    // logical terminal id      // JC23
    unsigned char       termtypebu;     // terminal type            // JC23
        #define TERM_SYS     0            // System
        #define TERM_VOI     1            // Voice BT
        #define TERM_CIT     2            // CIT
        #define TERM_CBT     3            // CBBT
        #define TERM_MAT     4            // MAT
        #define TERM_EWIN    5            // EWIN   // KL29
        #define TERM_IVRS    6            // IVRS   // RL40
};





/*
struct AA_SGN_AUTH
{
  unsigned int  secu1:1;    // security code override
  unsigned int  normal1:1;  // normal account access
  unsigned int  key1:1;     // key account access
  unsigned int  super1:1;   // super key account access
  unsigned int  withdrawal1:1; // withdrawal
  unsigned int  racing1:1;  // racing bet
  unsigned int  lottery1:1; // lottery bet
  unsigned int  canCurCall1:1; // cancel in current call
  unsigned int  canPrvCall1:1; // cancel in today's previous call
  unsigned int  canPrvDay1:1;  // cancel in previous day
};
struct AA_REQ_SGN             // sign-on request
{
  unsigned int   stafflu;     // staff number
  unsigned int   passwordlu;  // password
  unsigned int   ltnlu;       // logical terminal number
  unsigned int   termidlu;    // terminal id
};
struct AA_REQ_SGF
{
  unsigned int   stafflu;     // staff number
  unsigned int   ltnlu;       // logical terminal number
  unsigned int   termidlu;    // terminal id
};
struct AA_REQ_CIT
{
  unsigned int   ltnlu;       // logical terminal number
  unsigned int   accountlu;   // account number
  unsigned int   citlu;       // cit number
  unsigned int   citTypebu;   // cit type
  LONGLONG       fundd;       // funds available
};
struct AA_RPY_SGN             // signon reply
{
  unsigned int       ltnlu;   // logical terminal number
  unsigned short     recTrkwu;    // recorder track
  struct AA_SGN_AUTH auth;    // authority bitmap
};
struct AA_RPY_SGF             // signoff reply
{
  unsigned int   ltnlu;       // logical terminal number
};
struct AA_RPY_CIT
{
  unsigned int   ltnlu;       // logical terminal number
  unsigned int   depositlu;   // new deposit
  unsigned int   feelu;       // new annual fee
  unsigned int   rfdDeplu;    // refund deposit
  unsigned int   rfdFeelu;    // refund annual fee
};
*/

#pragma pack()

#endif
