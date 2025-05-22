
#include "CBTextDB.h"




MsgFileMap	CBTextDB::m_msgFileMap [MaxCBMsg]	= {
/*   0 */	{ "LOG_ERR_C",		"cb_error.txt",		NULL }  // error

/*   1 */	,{ "LOG_SGN_C",		"cb_sgnon.txt",		NULL }	// sign on
/*   2 */	,{ "LOG_SGF_C",		"cb_sgnoff.txt",		NULL }	// sign off
/*   3 */	,{ "LOG_BET_C",		"cb_bet.txt",		NULL }	// bet
/*   4 */	,{ "LOG_LOT_C",		"cb_lott.txt",		NULL }	// lottery
/*   5 */	,{ "LOG_CSHI_C",	"cb_cshi.txt",		NULL }	// cash in
/*   6 */	,{ "LOG_CSHO_C",	"cb_csho.txt",		NULL }	// cash out
/*   7 */	,{ "LOG_CAN_C",		"cb_can.txt",		NULL }	// cancel
/*   8 */	,{ "LOG_PAY_C",		"cb_pay.txt",		NULL }	// payout
/*   9 */	,{ "LOG_RDT_C",		"cb_rdt.txt",		NULL }	// rdt request
/*  10 */	,{ "LOG_TBD_C",		"cb_tbd.txt",		NULL }	// telebet deosit
/*  11 */	,{ "LOG_CVI_C",		"cb_cvi.txt",		NULL }	// cv issue
/*  12 */	,{ "LOG_CVC_C",		"cb_cvc.txt",		NULL }	// cv cash
/*  13 */	,{ "LOG_ACA_C",		"cb_aca.txt",		NULL }	// account access
/*  14 */	,{ "LOG_ACR_C",		"cb_acr.txt",		NULL }	// account release
/*  15 */	,{ "LOG_DEP_C",		"cb_esc_dep.txt",		NULL }	// deposit (after account access)
/*  16 */	,{ "LOG_WTW_C",		"cb_wtw.txt",		NULL }	// withdrawal
/*  17 */	,{ "LOG_RCL_C",		"cb_rcl.txt",		NULL }	// account recall
/*  18 */	,{ "LOG_ENQ_C",		"cb_enq.txt",		NULL }	// transaction enquriy
/*  19 */	,{ "LOG_ACOPEN_C",	"cb_acopen.txt",		NULL }	// account open/card issue
/*  20 */	,{ "LOG_CRDREP_C",	"cb_crdrep.txt",		NULL }	// card replacement
/*  21 */	,{ "LOG_CLS_C"		"cb_cls.txt",			NULL }	// account close
/*  22 */	,{ "LOG_DTLUPD_C",	"cb_dtlupd.txt",		NULL }	// account details update
/*  23 */	,{ "LOG_DTLENQ_C"	"cb_dtlenq.txt",		NULL }	// account details enquiry
/*  24 */	,{ "LOG_SVTWNR_C",	"cb_svtwnr.txt",		NULL }	// unsolicited svt warning message
/*  25 */	,{ "LOG_SVTSER_C",	"cb_svtser.txt",		NULL }	// unsolicited svt sever error message
/*  26 */	,{ "LOG_SB_C",		"cb_sb_bet.txt",		NULL }	// soccer betting
/*  27 */	,{ "NULL",			"NULL",					NULL }
/*  28 */	,{ "NULL",			"NULL",					NULL }
/*  29 */	,{ "NULL",			"NULL",					NULL }
// transactoin from eft terminal		
/*	30 */	,{ "LOG_EFTDEP_C",	"cb_eftdep.txt",		NULL }	// eft deposit
/*  31 */	,{ "LOG_EFTWTW_C",	"cb_eftwtw.txt",		NULL }	// eft withdrawal
/*  32 */	,{ "LOG_EFTACB_C",	"cb_eftacb.txt",		NULL }	// eft account balance enquiry
/*  33 */	,{ "LOG_EFTCVI_C",	"cb_eftcvi.txt",		NULL }	// eft cv issue request
/*  34 */	,{ "LOG_EFTBKB_C",	"cb_eftbkb.txt",		NULL }	// eft bank balance enquiry
/*  35 */	,{ "LOG_EFTXBT_C",	"cb_eftfund.txt",		NULL }	// eft transfer for betting
/*  36 */	,{ "LOG_EFTINI_C",	"cb_eftini.txt",		NULL }	// eft terminal initialisation
/*  37 */	,{ "LOG_EFTSTSP_C",	"cb_eftstsp.txt",		NULL }	// eft status reply
/*  38 */	,{ "LOG_EFTSER_C",	"cb_eftser.txt",		NULL }	// eft severe error
/*  39 */	,{ "NULL",			"NULL",					NULL }
/*  40 */	,{ "NULL",			"NULL",					NULL }
/*  41 */	,{ "NULL",			"NULL",					NULL }
/*  42 */	,{ "NULL",			"NULL",					NULL }
/*  43 */	,{ "NULL",			"NULL",					NULL }
/*  44 */	,{ "NULL",			"NULL",					NULL }
/*  45 */	,{ "NULL",			"NULL",					NULL }
/*  46 */	,{ "NULL",			"NULL",					NULL }
/*  47 */	,{ "NULL",			"NULL",					NULL }
/*  48 */	,{ "NULL",			"NULL",					NULL }
/*  49 */	,{ "NULL",			"NULL",					NULL }
/*  50 */	,{ "NULL",			"NULL",					NULL }
/*  51 */	,{ "NULL",			"NULL",					NULL }
/*  52 */	,{ "NULL",			"NULL",					NULL }
/*  53 */	,{ "NULL",			"NULL",					NULL }
/*  54 */	,{ "NULL",			"NULL",					NULL }
/*  55 */	,{ "NULL",			"NULL",					NULL }
/*  56 */	,{ "NULL",			"NULL",					NULL }
/*  57 */	,{ "NULL",			"NULL",					NULL }
/*  58 */	,{ "NULL",			"NULL",					NULL }
/*  59 */	,{ "NULL",			"NULL",					NULL }
/*  60 */	,{ "NULL",			"NULL",					NULL }
/*  61 */	,{ "NULL",			"NULL",					NULL }
/*  62 */	,{ "NULL",			"NULL",					NULL }
/*  63 */	,{ "NULL",			"NULL",					NULL }
/*  64 */	,{ "NULL",			"NULL",					NULL }
/*  65 */	,{ "NULL",			"NULL",					NULL }
/*  66 */	,{ "NULL",			"NULL",					NULL }
/*  67 */	,{ "NULL",			"NULL",					NULL }
/*  68 */	,{ "NULL",			"NULL",					NULL }
/*  69 */	,{ "NULL",			"NULL",					NULL }
/*  70 */	,{ "NULL",			"NULL",					NULL }
/*  71 */	,{ "NULL",			"NULL",					NULL }
/*  72 */	,{ "NULL",			"NULL",					NULL }
/*  73 */	,{ "NULL",			"NULL",					NULL }
/*  74 */	,{ "NULL",			"NULL",					NULL }
/*  75 */	,{ "NULL",			"NULL",					NULL }
/*  76 */	,{ "NULL",			"NULL",					NULL }
/*  77 */	,{ "NULL",			"NULL",					NULL }
/*  78 */	,{ "NULL",			"NULL",					NULL }
/*  79 */	,{ "NULL",			"NULL",					NULL }
/*  80 */	,{ "NULL",			"NULL",					NULL }
/*  81 */	,{ "NULL",			"NULL",					NULL }
/*  82 */	,{ "NULL",			"NULL",					NULL }
/*  83 */	,{ "NULL",			"NULL",					NULL }
/*  84 */	,{ "NULL",			"NULL",					NULL }
/*  85 */	,{ "NULL",			"NULL",					NULL }
/*  86 */	,{ "NULL",			"NULL",					NULL }
/*  87 */	,{ "NULL",			"NULL",					NULL }
/*  88 */	,{ "NULL",			"NULL",					NULL }
/*  89 */	,{ "NULL",			"NULL",					NULL }
/*  90 */	,{ "NULL",			"NULL",					NULL }
/*  91 */	,{ "NULL",			"NULL",					NULL }
/*  92 */	,{ "NULL",			"NULL",					NULL }
/*  93 */	,{ "NULL",			"NULL",					NULL }
/*  94 */	,{ "NULL",			"NULL",					NULL }
/*  95 */	,{ "NULL",			"NULL",					NULL }
/*  96 */	,{ "NULL",			"NULL",					NULL }
/*  97 */	,{ "NULL",			"NULL",					NULL }
/*  98 */	,{ "NULL",			"NULL",					NULL }
/*  99 */	,{ "NULL",			"NULL",					NULL }
/*  100 */	,{ "NULL",			"NULL",					NULL }

// transaction from MAT via BCS
/*  101 */	,{ "LOG_EFTOPN_C",	"cb_eftopn.txt",		NULL }	// open eft
/*  102 */	,{ "LOG_EFTCLS_C",	"cb_eftcls.txt",		NULL }	// close eft
/*  103 */	,{ "LOG_EFTSTS_C",	"cb_eftsts.txt",		NULL }	// request eft status
/*  104 */	,{ "LOG_SVTSGN_C",	"cb_svtsgn.txt",		NULL }	// svt sign on request
/*  105 */	,{ "LOG_SVTSGF_C",	"cb_svtsgf.txt",		NULL }	// svt sign off request
/*  106 */	,{ "LOG_ENADCV_C",	"cb_enadcv.txt",		NULL }	// enable/disable cash voucher
/*  107 */	,{ "LOG_TMHVCV_C",	"cb_tmhvcv.txt",		NULL }	// enable/disable terminal high value cv
/*  108 */	,{ "LOG_TMPAYO_C",	"cb_tmpayo.txt",		NULL }	// enable/disable terminal payout
/*  109 */	,{ "LOG_RELTRM_C",	"cb_release.txt",		NULL }	// release betting terminal
/*  110 */	,{ "LOG_EFTREL_C",	"cb_eftrel.txt",		NULL }	// release eft
/*  111 */	,{ "LOG_EFTRCL_C",	"cb_eftrcl.txt",		NULL }	// eft recall
/*  112 */	,{ "LOG_STPPAY_C",	"cb_stppay.txt",		NULL }	// stop pay ticket
/*  113 */	,{ "LOG_RLSTPY_C",	"cb_rlstpy.txt",		NULL }	// release stop pay ticket
/*  114 */	,{ "LOG_RLPBRH_C",	"cb_rlpbrh.txt",		NULL }	// release payout to branch
/*  115 */	,{ "LOG_CRPBRH_C",	"cb_crpbrh.txt",		NULL }	// cancel release payout to branch
/*  116 */	,{ "LOG_TRMRCL_C",	"cb_trmrcl.txt",		NULL }	// terminal recall
/*  117 */	,{ "LOG_CVTREK_C",	"cb_cvtrek.txt",		NULL }	// cv tracking
/*  118 */	,{ "LOG_TKTENQ_C",	"cb_tktenq.txt",		NULL }	// ticket enquiry
/*  119 */	,{ "LOG_AUPXPO_C",	"cb_aupxpo.txt",		NULL }	// all-up explosion 
/*  120 */	,{ "LOG_TRMBAL_C",	"cb_trmbal.txt",		NULL }	// request terminal balance
/*  121 */	,{ "LOG_KEYCAN_C",	"cb_keycan.txt",		NULL }	// keypad cancel
/*  122 */	,{ "LOG_CON_C",		"cb_con.txt",			NULL }	// centre on
/*  123 */	,{ "NULL",			"NULL",					NULL }
/*  124 */	,{ "NULL",			"NULL",					NULL }
/*  125 */	,{ "NULL",			"NULL",					NULL }
/*  126 */	,{ "NULL",			"NULL",					NULL }
/*  127 */	,{ "NULL",			"NULL",					NULL }
/*  128 */	,{ "NULL",			"NULL",					NULL }
/*  129 */	,{ "NULL",			"NULL",					NULL }
/*  130 */	,{ "NULL",			"NULL",					NULL }
/*  131 */	,{ "NULL",			"NULL",					NULL }
/*  132 */	,{ "NULL",			"NULL",					NULL }
/*  133 */	,{ "NULL",			"NULL",					NULL }
/*  134 */	,{ "NULL",			"NULL",					NULL }
/*  135 */	,{ "NULL",			"NULL",					NULL }
/*  136 */	,{ "NULL",			"NULL",					NULL }
/*  137 */	,{ "NULL",			"NULL",					NULL }
/*  138 */	,{ "NULL",			"NULL",					NULL }
/*  139 */	,{ "NULL",			"NULL",					NULL }
/*  140 */	,{ "NULL",			"NULL",					NULL }
/*  141 */	,{ "NULL",			"NULL",					NULL }
/*  142 */	,{ "NULL",			"NULL",					NULL }
/*  143 */	,{ "NULL",			"NULL",					NULL }
/*  144 */	,{ "NULL",			"NULL",					NULL }
/*  145 */	,{ "NULL",			"NULL",					NULL }
/*  146 */	,{ "NULL",			"NULL",					NULL }
/*  147 */	,{ "NULL",			"NULL",					NULL }
/*  148 */	,{ "NULL",			"NULL",					NULL }
/*  149 */	,{ "NULL",			"NULL",					NULL }
/*  150 */	,{ "NULL",			"NULL",					NULL }
/*  151 */	,{ "NULL",			"NULL",					NULL }
/*  152 */	,{ "NULL",			"NULL",					NULL }
/*  153 */	,{ "NULL",			"NULL",					NULL }
/*  154 */	,{ "NULL",			"NULL",					NULL }
/*  155 */	,{ "NULL",			"NULL",					NULL }
/*  156 */	,{ "NULL",			"NULL",					NULL }
/*  157 */	,{ "NULL",			"NULL",					NULL }
/*  158 */	,{ "NULL",			"NULL",					NULL }
/*  159 */	,{ "NULL",			"NULL",					NULL }
/*  160 */	,{ "NULL",			"NULL",					NULL }
/*  161 */	,{ "NULL",			"NULL",					NULL }
/*  162 */	,{ "NULL",			"NULL",					NULL }
/*  163 */	,{ "NULL",			"NULL",					NULL }
/*  164 */	,{ "NULL",			"NULL",					NULL }
/*  165 */	,{ "NULL",			"NULL",					NULL }
/*  166 */	,{ "NULL",			"NULL",					NULL }
/*  167 */	,{ "NULL",			"NULL",					NULL }
/*  168 */	,{ "NULL",			"NULL",					NULL }
/*  169 */	,{ "NULL",			"NULL",					NULL }
/*  170 */	,{ "NULL",			"NULL",					NULL }
/*  171 */	,{ "NULL",			"NULL",					NULL }
/*  172 */	,{ "NULL",			"NULL",					NULL }
/*  173 */	,{ "NULL",			"NULL",					NULL }
/*  174 */	,{ "NULL",			"NULL",					NULL }
/*  175 */	,{ "NULL",			"NULL",					NULL }
/*  176 */	,{ "NULL",			"NULL",					NULL }
/*  177 */	,{ "NULL",			"NULL",					NULL }
/*  178 */	,{ "NULL",			"NULL",					NULL }
/*  179 */	,{ "NULL",			"NULL",					NULL }
/*  180 */	,{ "NULL",			"NULL",					NULL }
/*  181 */	,{ "NULL",			"NULL",					NULL }
/*  182 */	,{ "NULL",			"NULL",					NULL }
/*  183 */	,{ "NULL",			"NULL",					NULL }
/*  184 */	,{ "NULL",			"NULL",					NULL }
/*  185 */	,{ "NULL",			"NULL",					NULL }
/*  186 */	,{ "NULL",			"NULL",					NULL }
/*  187 */	,{ "NULL",			"NULL",					NULL }
/*  188 */	,{ "NULL",			"NULL",					NULL }
/*  189 */	,{ "NULL",			"NULL",					NULL }
/*  190 */	,{ "NULL",			"NULL",					NULL }
/*  191 */	,{ "NULL",			"NULL",					NULL }
/*  192 */	,{ "NULL",			"NULL",					NULL }
/*  193 */	,{ "NULL",			"NULL",					NULL }
/*  194 */	,{ "NULL",			"NULL",					NULL }
/*  195 */	,{ "NULL",			"NULL",					NULL }
/*  196 */	,{ "NULL",			"NULL",					NULL }
/*  197 */	,{ "NULL",			"NULL",					NULL }
/*  198 */	,{ "NULL",			"NULL",					NULL }
/*  199 */	,{ "NULL",			"NULL",					NULL }
/*  200 */	,{ "NULL",			"NULL",					NULL }

// other log transaction
/*  201 */	,{ "LOG_REVPC_C",	"cb_rev_pay.txt",			NULL }	// reverse pay/cancel
/*  202 */	,{ "LOG_SYSCLS_C",	"cb_syscls.txt",		NULL }	// system close
/*  203 */	,{ "LOG_ENAESC_C",	"cb_enaesc.txt",		NULL }	// enable/disable esc service
/*  204 */	,{ "LOG_ENABCS_C",	"cb_enabcs.txt",		NULL }	// enable/disable bcs service
/*  205 */	,{ "LOG_WC_C",		"cb_pool_start_pay.txt",			NULL }	// wagering control transaction
/*  206 */	,{ "LOG_REVBCS_C",	"cb_revbcs.txt",		NULL }	// reverse bcs request reply
/*  207 */	,{ "LOG_FRCSGF_C",	"cb_frcsgf.txt",		NULL }	// forced sign off
/*  208 */  ,{ "LOG_APSDONE_C",	"cb_apsdone.txt",		NULL }	// all-up post race pass done
/*	209 */	,{ "LOG_BCSCLS_C",	"cb_bcscls.txt",		NULL }	// bcs system close
/*	210	*/	,{ "LOG_ENAEFT_C",	"cb_eneft.txt",			NULL }	// enable eft service
/*	211	*/	,{ "LOG_LOTWPS_C",	"cb_lotwin.txt",		NULL }	// lottery winner pass

// undefined messages
/*  212 */	,{ "LOG_MSG_SBC",	"cb_sbc_pool_def.txt",		NULL }
/*  213 */	,{ "NULL",			"NULL",					NULL }
/*  214 */	,{ "NULL",			"NULL",					NULL }
/*  215 */	,{ "NULL",			"NULL",					NULL }
/*  216 */	,{ "NULL",			"NULL",					NULL }
/*  217 */	,{ "NULL",			"NULL",					NULL }
/*  218 */	,{ "NULL",			"NULL",					NULL }
/*  219 */	,{ "NULL",			"NULL",					NULL }
/*  220 */	,{ "LOG_SB",		"cb_sb_bet.txt",		NULL }	// SB Bet
/*  221 */	,{ "NULL",			"NULL",					NULL }
/*  222 */	,{ "NULL",			"NULL",					NULL }
};


CBTextDB::CBTextDB() : TextDB()
{
	m_iMaxMsg = MaxCBMsg;
}

