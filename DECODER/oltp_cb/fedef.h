//    *******************************************************************
//    *                                                                 *
//    *   ?COPYRIGHT.  The Hong Kong Jockey Club                       *
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

#ifndef fedef_H
#define fedef_H

#include "udtypedef.h"
#include "pardef.h"
#include "ethdef.h"

#define FE_MAXNU_C	100		// Max. number of front-end
#define FE_MPATH_C	2		// Max. link path
#define FE_MAXBE_C	(PAR_OLTP_MAX)	// Max. number of back-end
#define FE_MAXCNT_C	51		// Number of message in a block

#pragma nomember_alignment

struct  FENUMS
{
    unsigned char   fel:3;      // lower bits of front-end #
    unsigned char   port:3;     // port #
    unsigned char   feh:1;      // high bits of front-end #
    unsigned char   bc:1;       // high bits of bc
};

union  FENUM
{
    unsigned char   numbu;      // Front-end number
    struct FENUMS   fenum;      // Front-end bits
};

#define FE_PATH_UP	1	// path up
#define FE_PATH_DOWN	0	// path down
#define FE_PATH_UNKNOWN	-1	// path status unkown

struct  FEINFS
{
    char    okb;	//FEOKT(0:1,0:fe_max_c)          ! path ok flag
    char    addb[ETH_ADDR_LEN];
};  

struct  FEINF
{
    char    curb;	//FECURB(0:fe_max_c)             ! current path no.
    bool    deft;   //FEDEFT(0:fe_max_c)             ! fe defined flag
    struct  FEINFS     inf[FE_MPATH_C]; 
    unsigned longlong  outcntdu[FE_MAXCNT_C];    // outward counter
    unsigned longlong  incntrdu[FE_MAXCNT_C];    // inward counter
};

struct  FECOM       // global section structure
{
    struct  FEINF  fe[FE_MAXNU_C];      // Front-end info
    struct  FEINF  be[FE_MAXBE_C+1];    // Back-end info (zeroth ele. unused)
    bool    tracet;     // trace blocking counter flag
};

#pragma member_alignment

#endif
