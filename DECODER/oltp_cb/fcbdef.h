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
//      General define for File Control Block.
//
//      The first block (512-byte and VBN=1) of all data files used in
//      OLTP must be the File Control Block. It contains the general
//      information which are common to all files. For further file
//      specific information, can be appended as desire.
//
//    Author : Edward Hon                01-NOV-2000
//
//    Mod :     PN01            18-APR-2002
//              ( move defines to filedef.h )
//

#ifndef FCBDEF_H
#define FCBDEF_H

#include <time.h>

#pragma pack(1)

struct FCB              // file control block for file access
{
  __time32_t                lstupd;         // last update date/time
  unsigned short        syswu;          // system number
  unsigned short        fverwu;         // file version number
    #define FCB_FVER_CURRENT    0       // current version number
  unsigned int          lstblklu;       // last used block
  unsigned short        lstoffwu;       // last byte used in last block
};


union FCBBLK            // file control block - the 1st VBN
{
  struct FCB            fcb;
  unsigned int          buflu[128];
};

#pragma pack()

#endif
