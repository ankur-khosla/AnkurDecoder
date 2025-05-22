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
// Function: This header defines the code that is used when bet record is
//           referenced.  For all other cases for OLTP internal processing,
//           defines in RDSDEF.H should be used.
//
//    Author : Edward Hon                01-NOV-2000
//
//    Mod :    VC01             8-APR-2003
//             Add bet type BETYPE_LOT
//             PN02             23-DEC-2003
//             ( add mixed bet type for fixed odds soccer bet )
//             PN03             3-AUG-2004
//             ( add section bet )

#ifndef BETTYPDEF_H
#define BETTYPDEF_H

#define BETTYP_WINPLA   0
#define BETTYP_WIN      1
#define BETTYP_PLA      2
#define BETTYP_QIN      3
#define BETTYP_QPL      4
#define BETTYP_DBL      5
#define BETTYP_TCE      6
#define BETTYP_QTT      7
#define BETTYP_DQN      8
#define BETTYP_TBL      9
#define BETTYP_TTR      10
#define BETTYP_6UP      11
#define BETTYP_DTR      12
#define BETTYP_TRIO     13
#define BETTYP_QINQPL   14
#define BETTYP_CV       15
#define BETTYP_MK6      16
#define BETTYP_PWB      17
#define BETTYP_AUP      18
#define BETTYP_SB       19      // pari-mutuel collated soccer bet
#define BETTYP_SB_FO    20      // fix-odds collated soccer bet
#define BETTYP_SB_EXO   21      // exotic soccer bet
#define BETTYP_SB_AUP_PM        22      // all-up soccer bet parimutuel
#define BETTYP_SB_AUP_FO_CTL    23      // controlled fixed odds allup bet
                                        // => an allup set is associated, need
                                        // to look up by first pool selected
#define BETTYP_SB_AUP_FO_NON    24      // Non-controlled fixed odds allup bet
#define BETTYP_SB_SCT_FO        25      // section bet      PN03
#define BETTYP_SB_MIX_FO        26  // mixed bet type - fixed odds  PN02 PN03
#define BETTYP_FF				27	// racing first four -- Q406
#define BETTYP_BWA				28	// bracket win -- Q406
//#define BETTYP_BWB				29	// bracket win -- Q406  remove in 2014NOV
//#define BETTYP_BWC				30	// bracket win -- Q406  remove in 2014NOV
//#define BETTYP_BWD				31	// bracket win -- Q406  remove in 2014NOV
#define BETTYP_CWA				29	// Composite Win 
#define BETTYP_CWB				30	// Composite Win
#define BETTYP_CWC				31	// Composite Win
#define BETTYP_IWN				33	// Insurance Win
#define BETTYP_FCT				34  // FCT AUG2020 L311


#define BETTYP_MAX      50      // max. # of bet type
 
struct BETTYP_POOL
{
  unsigned char numbu;     // # of pools [max. 2] referred to by this BETTYP
  unsigned char poolbu[2]; // pools referred to by this BETTYP
};
// sub code for add-on game

#define BETTYP_AON 1
#define BETTYP_OEG 2
#define BETTYP_MHG 3
#define BETTYP_ENR 4
#define BETTYP_OUG 5
#define BETTYP_AON_MAX 5        // max. # of add-on games

#define BETYPE_STD  0
#define BETYPE_EXO  1
#define BETYPE_AUP  2
#define BETYPE_LOT  3           // VC01
#define BETYPE_NA  -1

#define BETTYP_AWP      18	// Define from work file, combine allup and non allup bet type code
#define BETTYP_AWN      19	// Define from work file, combine allup and non allup bet type code
#define BETTYP_APL      20	// Define from work file, combine allup and non allup bet type code
#define BETTYP_AQN      21	// Define from work file, combine allup and non allup bet type code
#define BETTYP_AQP      22	// Define from work file, combine allup and non allup bet type code
#define BETTYP_ATR      23	// Define from work file, combine allup and non allup bet type code
#define BETTYP_AQQP     24	// Define from work file, combine allup and non allup bet type code
#define BETTYP_ATC      25	// Define from work file, combine allup and non allup bet type code
#define BETTYP_AQT      26	// Define from work file, combine allup and non allup bet type code


#endif
