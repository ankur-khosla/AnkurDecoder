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
//    Author : Paul Ou                13-Sep-2016
//	  ExtraData

#include <time.h>
#include "tsndef.h"

#pragma pack(1)

// Racing bet; Lottery bet; CV issue (Cash Voucher-LOGBTCV)
struct EXTRADATARLC
{
	unsigned short			acterrwu;	// Activity error code; LOG.hdr.errwu
	__int64					actts;		// Activity timesstamp; LOG.hdr.timelu
	//__int64			custotl;	// Customer total
	__int64					btsellt;	// Bet selling time; BET.d.hdr.sellTime
	unsigned __int64		tsntktid;	// TSN ticket id
};

// Cash in/out (LOGBTCIO); BT Sign-Off(LOGBTSGF); BT Sign-On (LOGBTSGN); Message (LOGBTMSG); Force Sign Off (LOGBTFSGF); Cancel account transaction by tran# and token (LOGBTCANTRN);
// All ESC Transaction (LOGBTESCD); Cash Counter (CKPCSH); Invalid message data flag; Soccer bet enquiry (LOGBTSB); Change password; Reject message (LOGBTREJMSG); Ticket enquiry from BT and MAT(LOGBTENQ);
// Recall customer session from BT(LOGBTRCL); Sweepstake bet(LOGBTSWP); MSR/MSP(LOGBTMSRMSP);
// Staff authority bitmask(LOGBTAMASK); Get Staff authority bitmask (LOGBTAUTH); AT Transaction (LOGAT); EFT activity; Others transactions (LOGOTH); SBC message(LOGSBC);
// Cancel/Cancel Enquery/payout
struct EXTRADATACOMM
{
	unsigned short		acterrwu;	// Activity error code; LOG.LOGHDR.errwu
	__int64				actts;		// Activity timesstamp;
};

struct CVRelInfo
{
	// the following information is only applicable for CV relating transaction
	unsigned __int64		tktid;	 // Ticket id; BET.ticketiddu
	unsigned int			verifier; // Verifier; BET.content
	unsigned int			businessDate; // create business date; BET.d.hdr.businessDate
	int						sellTime; //create time; 4 bytes; BET.d.hdr.sellTime
	unsigned __int64		selllogseqlu; // create activity id; BET.h.ptr.cv.selllogseqlu
	unsigned __int64		terseid; // terminal session id; 
	unsigned __int64		custoseid; // customer session id; 
	unsigned int			sellCentrelu; // create center no; BET.h.sellCentrelu
	unsigned int			sellWindowu; // create window no; BET.h.sellWindowu
	unsigned int			methodbu; // create method; BET.d.var.cv.methodbu
	unsigned int			currencyId; // currency id
	unsigned __int64		costlu; // CV amount; BET.d.hdr.costlu
	unsigned __int64		originallu; // CV original eft amount; BET.h.prveft.eft.originallu
	unsigned __int64		remainlu; // CV remain eft amount; BET.h.prveft.eft.remainlu
	unsigned char			claim1;		 // claimed flag; BET.d.hdr.sts.claim1
	unsigned char			paidfinal1;		 // paid flag; BET.d.hdr.sts.paidfinal1
	unsigned char			hdOfficeF;		 // head office flag
	unsigned __int64		retcenno;	// release to centre no
	unsigned int			payDate;  // paid bizdate; BET.h.payDate
	unsigned int			payTime; // paid time; BET.h.payTime
	unsigned int			paySysb; // paid system id; BET.h.paySysb
	unsigned __int64		paylogseqlu; // paid activity id; BET.h.ptr.cv.paylogseqlu
	unsigned __int64		paidTerseid; // paid terminal session id
	unsigned __int64		paidCustSessid; // paid customers session id
	unsigned int			payCentrelu; // paid centre no; BET.h.payCentrelu
	unsigned int			paidWinNo; // paid window no
	unsigned short			paidMethod;	   //paid method
	unsigned int			retdate;  // retention bizdate; BET.h.retdate
	unsigned int			payExpBizDate;  // payout expired bizdate
	unsigned int			purgedate;  // purge bizdate; BET.h.purgedate
	unsigned int			sts;  // ticket status; BET.d.h.sts
	unsigned __int64		lastactid; // last activity id
	unsigned __int64		rowver; // row version; BET.rowver
};

// Cancel/Cancel Enquery/payout (LOGBTCCP) 
struct EXTRADATACCP
{
	unsigned short			acterrwu;	// Activity error code; LOG.LOGHDR.errwu
	__int64					actts = 0;		// Activity timesstamp; LOG.LOGHDR.timelu
	__int64					btsellt = 0;	// Bet selling time; BET.d.hdr.sellTime
	struct TSN_INFO			tsninfo; // if partial paid,child TSN
};

//Cash Voucher(LOGBTCCP) -- only for CV cash; CV payout
struct EXTRADATACV
{
	unsigned short			acterrwu;	// Activity error code; LOG.LOGHDR.errwu
	__int64					actts;		// Activity timesstamp; LOG.LOGHDR.timelu
	__int64					btsellt;	// Bet selling time; BET.d.hdr.sellTime
	struct TSN_INFO			tsninfo; // if partial paid,child TSN
	struct CVRelInfo		cvRelinfo = { 0 }; // only for Cash Voucher
};

// TB Deposit issue (LOGBTTBDI); ESC Transactions (LOGBTESC);
struct EXTRADATADE
{
	struct EXTRADATACOMM	extdcomm;
	struct TSN_INFO			tsninfo; // new tsn info
};
