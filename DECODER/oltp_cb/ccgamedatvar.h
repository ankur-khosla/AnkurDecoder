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
//      CCGAMEDATVAR.H   -   Concurrent game common data
//
//	Author : Vicki Chung
//	
// 	Date : 22 Feb., 2001
//
//	Mod. : 
//

#ifndef	CCGAMEDATVAR_H
#define CCGAMEDATVAR_H 1

#include "bettypdef.h"

#pragma pack(1)

#ifndef _CCGAME_DATA_

extern unsigned char ccgamenamebu[BETTYP_AON_MAX+2][4];

#else

// Add-on / Concurrent game name
unsigned char ccgamenamebu[BETTYP_AON_MAX+2][4]
    = {"NOR","MT3", "EOC", "MHG", "EXN", "OUG", "GBN"};
#endif
                                                              
#pragma pack()

#endif  // CCGAMEDATVAR_H
