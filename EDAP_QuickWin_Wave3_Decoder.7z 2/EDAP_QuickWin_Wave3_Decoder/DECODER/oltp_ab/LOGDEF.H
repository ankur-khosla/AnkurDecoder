
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
#include "simplesbcdef.h"

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



#pragma pack()

#endif
