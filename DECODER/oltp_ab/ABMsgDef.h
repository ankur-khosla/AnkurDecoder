// MsgDef.h: interface for the MsgDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDEF_H__F5486365_6306_11D2_896E_00C04F79D485__INCLUDED_)
#define AFX_MSGDEF_H__F5486365_6306_11D2_896E_00C04F79D485__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//	Message Type Definition
#define LOGAB_CODE_SGN                1 // sign on
#define LOGAB_CODE_SGF                2 // sign off
#define LOGAB_CODE_ACA                3 // account access via voice
#define LOGAB_CODE_ACR                4 // account release
#define LOGAB_CODE_WTW                5 // withdrawal
#define LOGAB_CODE_RAC                6 // racing bet
#define LOGAB_CODE_LOT                7 // lottery bet
#define LOGAB_CODE_CAN                8 // cancel
#define LOGAB_CODE_RCL                9 // recall
#define LOGAB_CODE_OLS               10 // on-line statement
#define LOGAB_CODE_DEP               11 // deposit/deposit cit
#define LOGAB_CODE_RAC_TOT           12 // racing bet total enquiry
#define LOGAB_CODE_LOT_TOT           13 // lottery bet total enquiry
#define LOGAB_CODE_ADTENQ            14 // account detail enquiry
#define LOGAB_CODE_SB                15 // soccer bet
#define LOGAB_CODE_SB_ENQ            16 // soccer bet enquiry
#define LOGAB_CODE_CARD_REPL         17 // card replace
#define LOGAB_CODE_CARD_ISSUE        18 // card issue
#define LOGAB_CODE_CARD_RET          19 // return esc card
#define LOGAB_CODE_DEVISSUE          20 // device issue
#define LOGAB_CODE_DEVREPL           21 // device replace
#define LOGAB_CODE_DEVCAN            22 // device cancel
#define LOGAB_CODE_BAL               23 // account balance via EFT
#define LOGAB_CODE_BNKBAL_DID        24 // bank balance via DID
#define LOGAB_CODE_CV_EFT            25 // cv via EFT
#define LOGAB_CODE_PANCAP            26 // pan capture
#define LOGAB_CODE_EFT_LTEST         27 // EFT link test
#define LOGAB_CODE_EFT_MISC          28 // EFT miscellaneous
#define LOGAB_CODE_DEPCAN            29 // cancel AB deposit
#define LOGAB_CODE_REVDEP            30 // reverse AB deposit
#define LOGAB_CODE_REVDEPCAN         31 // reverse cancel AB deposit
#define LOGAB_CODE_CHGSCD            32 // BT change security code
#define LOGAB_CODE_TXNENQ            33 // transaction enquiry
#define LOGAB_CODE_RDT               34 // race day table
#define LOGAB_CODE_NRDT              35 // new race day table
#define LOGAB_CODE_AUTHVER           36 // authority verification 
#define LOGAB_CODE_ACSTATM           37 // account statement request // HL11
#define LOGAB_CODE_ECV_ISSUE         38 // ECV issue
#define LOGAB_CODE_ECV_RET           39 // ECV return
#define LOGAB_CODE_ECV_CLSENQ        40 // ECV close enquiry
#define LOGAB_CODE_EFT_ERT           46 // EFT ERT information (Q210)
//#define LOGAB_CODE_ACA_NBA           48 // account access with NBA information (Q210)
#define LOGAB_CODE_CSCBAL			 49 // 201108PSR CSC Card Balance
#define LOGAB_CODE_CSCRPL			 50 // 2011IBT CSC Card Replace
#define LOGAB_CODE_CSCRET			 51 // 2011IBT CSC Card Return

#define LOGAB_CODE_STSENQ            98 // Status enquiry
#define LOGAB_CODE_ILLMSG            99 // illegal message code
// MAT transaction
#define LOGAB_CODE_ACCOPN           101 // account open
#define LOGAB_CODE_ACCCLS           102 // account close
#define LOGAB_CODE_DEBIT            103 // debit
#define LOGAB_CODE_CREDIT           104 // credit
#define LOGAB_CODE_ACCUPD           105 // Account Details Update
#define LOGAB_CODE_CHGSEC           106 // Change of Security Code
#define LOGAB_CODE_VALBET           107 // Validate Bet
#define LOGAB_CODE_UNSATLOTSI       108 // Unsatisfied Lottery SI Posting
#define LOGAB_CODE_UNSETTXNRET      109 // Unsettled transaction retrieval
#define LOGAB_CODE_REJBGREIMB       110 // Rejected Bank Guarantee Reimbursement
#define LOGAB_CODE_ALLUPEXP         111 // All-up Explosion
#define LOGAB_CODE_CALTRF           112 // Call Transfer Request
#define LOGAB_CODE_RELTRM           113 // Release Terminal
#define LOGAB_CODE_ACCBETPARA       114 // Account Bet Parameter
#define LOGAB_CODE_BANKGT           115 // Generate Bank Guarantee
#define LOGAB_CODE_BGREINB          116 // Credit Background Reinbursement
#define LOGAB_CODE_REVANLFEE        117 // Reverse Annual Fee
#define LOGAB_CODE_RESETPAN         118 // Reset PAN Capature
#define LOGAB_CODE_FUNDANALY        119 // Account Fund Analysis
#define LOGAB_CODE_ACCMONITOR       120 // Account monitor
#define LOGAB_CODE_ACCPARAM         121 // Account parameter
#define LOGAB_CODE_ACCSTATUS        122 // Account status
#define LOGAB_CODE_STMCHARGE        123 // Statement charge
#define LOGAB_CODE_ACCRANGE         124 // Account Range Request
#define LOGAB_CODE_ACCFBLMT         125 // Account FB Limit // KL10..
#define LOGAB_CODE_EXTOLS           126 // Extended on-line statement
#define LOGAB_CODE_EXTALLUPEXP      127 // Extended All-up Explosion // ..KL10
#define LOGAB_CODE_CHANLOCK         128 // Channel Lock

#define LOGAB_CODE_ACCOPN_NBA       137 // Account Open with NBA2 info (new from Q210)
#define LOGAB_CODE_ACCUPD_ERT       138 // Acocunt Update with ERT info (new from Q210)

#define LOGAB_CODE_CSCISSUE         139 // CSC associate card and open account (new from 2011IBT)

// Control message
#define LOGAB_CODE_SBC              201 // sb control
#define LOGAB_CODE_WC               202 // WC messages
#define LOGAB_CODE_ENABCS           203 // enable/disable bcs service
#define LOGAB_CODE_BCSCLS           204 // close bcs
#define LOGAB_CODE_ENASB            205 // enable/disable sb service
#define LOGAB_CODE_SBCLS            206 // close sb
#define LOGAB_CODE_ENAEPO           207 // enable EPOST service
#define LOGAB_CODE_EFTGW            208 // change EFTGW
#define LOGAB_CODE_LOTWPS           209 // lottery winner pass done
#define LOGAB_CODE_SYSCLS           210 // system close
// Batch deposit transaction
#define LOGAB_CODE_BATDEP           301 // Batch deposit
#define LOGAB_CODE_BATDEPSUM        302 // Batch deposit summary
// POL
#define LOGAB_CODE_POL_CKP          401 // pre-online checkpoint request
#define LOGAB_CODE_POL_BG           402 // change bank gaurantee
#define LOGAB_CODE_POL_STS          403 // change account status
#define LOGAB_CODE_POL_LOTACA       404 // s.i. lottery account access
#define LOGAB_CODE_POL_LOT          405 // s.i. lottery post
#define LOGAB_CODE_POL_LOTACR       406 // s.i. lottery account release
#define LOGAB_CODE_POL_WTW          407 // s.i. withdrawal
#define LOGAB_CODE_POL_DEP          408 // cheque deposit
#define LOGAB_CODE_POL_PRGDEPRFD    409 // progressive device deposit refund
#define LOGAB_CODE_POL_DEPRFD       410 // device deposit refund
#define LOGAB_CODE_POL_ANLFEEDED    411 // device annual fee deduction
#define LOGAB_CODE_POL_ANLFEERFD    412 // device annual fee refund
#define LOGAB_CODE_POL_DEPDED       413 // deposit deduction
#define LOGAB_CODE_POL_ESCDEPDED    414 // esc deposit deduction
#define LOGAB_CODE_POL_ESCDEPRFD    415 // esc deposit refund
#define LOGAB_CODE_POL_DEBIT        416 // pre-online debit
#define LOGAB_CODE_POL_CREDIT       417 // pre-online credit
#define LOGAB_CODE_POL_DEPFFT       418 // pre-online cit deposit forfeit
#define LOGAB_CODE_POL_ESCDEPFFT    419 // pre-online esc deposit forfeit
// EOD  !FT01...
//    #define LOGAB_CODE_EOD_DIV          501 // dividend generated tonight!FT19
#define LOGAB_CODE_EOD_DIVPUR       502 // dividend purged 
#define LOGAB_CODE_EOD_DFT          503 // dividend forfeited        !FT03
//    #define LOGAB_CODE_EOD_DIVOS        504 // div from o/s esc tran!FT09 FT19
#define LOGAB_CODE_EOD_CR           505 // credit adjustment         !FT06
#define LOGAB_CODE_EOD_CANSI        506 // cancel m6 si              !FT09
#define LOGAB_CODE_EOD_LOT          507 // settled lottery bet       !FT19
#define LOGAB_CODE_EOD_RAC2         508 // settled racing bet        !FT19
#define LOGAB_CODE_EOD_SB           509 // settled SB bet            !FT19
#define LOGAB_CODE_EOD_DIVPUR2      510 // dividend purged type 2    !FT19


#endif // !defined(AFX_MSGDEF_H__F5486365_6306_11D2_896E_00C04F79D485__INCLUDED_)
