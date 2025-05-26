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
//    Author : Pauline Ng                01-NOV-2000
//
//    Mod : 

#ifndef UDTYPEDEF_H
#define UDTYPEDEF_H

// #include <efndef.h>

typedef char BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif 

#define LONGLONG __int64

#define STRING char*

#define EFN_SYNREQ EFN$C_ENF    // general event flag used for synchronise i/o request

#endif
