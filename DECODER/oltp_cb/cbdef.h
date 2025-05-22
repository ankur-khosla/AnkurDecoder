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
//    Mod : 

#ifndef CBDEF_H
#define CBDEF_H

#include "bcsdef.h"

#define CB_MAXOLTP      4       // maximum number of OLTP-CB
#define CB_MAXOLD       4       // maximum number of legacy-CB
#define CB_MAXSYS       8       // # of cb
#define CB_MAXESCSYS    1       // # of esc system
#define CB_MAXBT        10000   // # of bt
#define CB_MAXAT        BCS_MAXAT   // # of at
#define CB_MAXEFT       (CB_MAXBT)  // # of eft
#define CB_MAXCTR       9999    // # of centres
#define CB_MAXWDW       999     // # of windows
#define CB_MAXXCHCHAN   10      // # of cross cashing channels
#define CB_MAXTBDCHAN   10      // # of tb deposit channels
#define CB_MAXEFTCHAN   10      // # of eft channels

#define CB_MAXPRESALE   7       // # of presale days
#define CB_MAXPAYDAY    14      // # of payout days

#define CB_MAXBETSET    20      // # of bet file sets
#define CB_MAXDEPSET    31      // # of deposit file sets
#define CB_PAYPERIOD    60      // payout period in # of days
#define CB_CVPAYPERIOD  180     // CV payout period in # of days
#define CB_CVRETENTION  CB_MAXDEPSET  // CV retention period
#endif
