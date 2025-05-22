
//    *******************************************************************
//    *                                                                 *
//    *   (c) COPYRIGHT.  The Hong Kong Jockey Club                       *
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
//    LOGDEF.H   - Logger file defines
//
//    Author : Edward Hon                01-NOV-2000
//
//    Mod :    eh01   08-aug-2002    soccer betting
//
//
//
#ifndef LOGDEF_H
#define LOGDEF_H

#include "loghdrdef.h"
#include "logatdef.h"
#include "logbtdef.h"
#include "logeftdef.h"
#include "logrdcdef.h"
#include "logothdef.h"
#include "..\oltp_ab\SimpleSbcDef.h"//replace string "oltp_ab" with "cpp"

#pragma pack(1)

// DD: log header had been moved to loghdrdef.h

union   LOGDATA         // log data
{
  union LOGBT           bt;
  union LOGAT           at;
  struct LOGEFT         eft;
  struct LOGRDC         rdc;
  union  LOGOTH         oth;
  struct LOGSBC         sbc;

};

struct  LOG             // log record
{
  struct LOGHDR         hdr;
  union LOGDATA         d;
};


//new solace header 
struct PAYLOAD_HDR
{
	unsigned int system_id; // system id
	unsigned int business_date; // business date
	unsigned __int64 activity_id; // activity id
	unsigned __int64 cust_session_id; // customer session id. added in DEC2022 R1a for EDW
	unsigned int enquiry_status; // enquiry status
	unsigned char activity_nature; // activity nature
	unsigned short sequence_num; // sequence number
	unsigned short activity_total_num; // total number of activity in this batch
	unsigned short extra_data_len; // extra data length
};

#pragma pack()

#endif
