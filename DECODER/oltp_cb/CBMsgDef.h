// MsgDef.h: interface for the MsgDef class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDEF_H__F5486365_6306_11D2_896E_00C04F79D485__INCLUDED_)
#define AFX_MSGDEF_H__F5486365_6306_11D2_896E_00C04F79D485__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//	Message Type Definition
// transaction from betting terminal
#define	LOG_SGN_C		1	// sign on
#define LOG_SGF_C		2	// sign off
#define LOG_BET_C		3	// bet
#define LOG_LOT_C		4	// lottery
#define LOG_CSHI_C		5	// cash in
#define LOG_CSHO_C		6	// cash out
#define LOG_CAN_C		7	// cancel
#define LOG_PAY_C		8	// payout
#define LOG_RDT_C		9	// rdt request
#define LOG_TBD_C		10	// telebet deposit
#define LOG_CVI_C		11	// cv issue
#define LOG_CVC_C		12	// cv cash
#define LOG_ACA_C		13	// account access
#define LOG_ACR_C		14	// account release
#define LOG_DEP_C		15	// deposit (after account access)
#define LOG_WTW_C		16	// withdrawal
#define LOG_RCL_C		17	// account recall
#define LOG_ENQ_C		18	// transaction enquiry
#define LOG_ACOPEN_C	19	// account open / card issue
#define LOG_CRDREP_C	20	// card replacement
#define LOG_CLS_C		21	// account close
#define LOG_DTLUPD_C	22	// account details update
#define LOG_DTLENQ_C	23	// account details enquiry
#define LOG_SVTWNR_C	24	// unsolicited svt warning message
#define LOG_SVTSER_C	25	// unsolicited svt severe error message

// change message code 26 to soccer betting
#define LOG_SB_C		26	// soccer betting
#define LOG_SB_ENQ		27	// soccer betting total enquiry

// transaction from eft terminal
#define LOG_EFTDEP_C	30	// eft deposit
#define LOG_EFTWTW_C	31	// eft withdrawal
#define	LOG_EFTACB_C	32	// eft account balance enquiry
#define LOG_EFTCVI_C	33  // eft cv issue request
#define LOG_EFTEMVCVI_C  83  // eft EMV CV Issue Request
#define LOG_EFTBKB_C	34	// eft bank balance enquiry
#define LOG_EFTXBT_C	35	// eft transfer for betting
#define LOG_EFTINI_C	36	// eft terminal initialisation
#define LOG_EFTSTSP_C	37	// eft status reply
#define LOG_EFTSER_C	38	// eft severe error
// transaction from MAT via BCS
#define LOG_EFTOPN_C	101	// open eft
#define LOG_EFTCLS_C	102	// close eft
#define LOG_EFTSTS_C	103	// request eft status
#define LOG_SVTSGN_C	104	// svt sign on request
#define LOG_SVTSGF_C	105	// svt sign off request
#define LOG_ENADCV_C	106	// enable/disable cash voucher
#define	LOG_TMHVCV_C	107	// enable/disable terminal high value cv
#define LOG_TMPAYO_C	108	// enable/disable terminal payout
#define LOG_RELTRM_C	109	// release betting terminal
#define LOG_EFTREL_C	110	// release eft
#define LOG_EFTRCL_C	111	// eft recall
#define LOG_STPPAY_C	112	// stop pay ticket
#define LOG_RLSTPY_C	113	// release stop pay ticket
#define LOG_RLPBRH_C	114	// release payout to branch
#define LOG_CRPBRH_C	115	// cancel release payout to branch
#define LOG_TRMRCL_C	116	// terminal recall
#define LOG_CVTREK_C	117	// cv tracking
#define LOG_TKTENQ_C	118	// ticket enquiry
#define LOG_AUPXPO_C	119	// all-up explosion
#define LOG_TRMBAL_C	120	// request terminal balance
#define LOG_KEYCAN_C	121	// keypad cancel
#define LOG_CON_C		122	// centre on
// other log transaction
#define LOG_REVPC_C		201	// reverse pay/cancel
#define LOG_SYSCLS_C	202	// system close
#define LOG_ENAESC_C	203	// enable/disable esc service
#define LOG_ENABCS_C	204	// enable / disable bcs service
#define LOG_WC_C		205	// wagering control transaction
#define LOG_REVBCS_C	206	// reverse bcs request reply
#define LOG_FRCSGF_C	207	// forced sign off
#define	LOG_APSDONE_C	208	// allup post race pass done
#define LOG_BCSCLS_C	209	// bcs system close
#define LOG_ENAEFT_C	210	// enable eft service
#define LOG_LOTWPS_C	211	// lottery winner pass
#define LOG_MSG_SBC        212      // sb control transaction
#define LOG_MSG_REVSB      213      // reverse sb transaction
#define LOG_MSG_ENASB      214      // enable/disable sb service
#define LOG_MSG_SBCLS      215      // sb system close
#define LOG_MSG_STSENQ     216      // status enquiry

#define LOG_SB			220	// SB Bet

#define LOGAB_CODE_ERR				50001 // code for error message
#define LOGAB_CODE_SIMPLE_SEL       50002 // code for simple selections
#define LOGAB_CODE_FILE_HDR		    50003 // code for file_header

#endif // !defined(AFX_MSGDEF_H__F5486365_6306_11D2_896E_00C04F79D485__INCLUDED_)
