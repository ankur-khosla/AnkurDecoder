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
//  Function:   This header file defines general structures for BCS data
//              
//  Mod.:       AL01  06-MAR-2003
//              - move define BCS_MAXAT from bcsdef.h to bcsgendef.h
//------------------------------------------------------------------------

#ifndef BCSGENDEF_H
#define BCSGENDEF_H

#pragma pack(1)


struct BCS_DATE
{
    char    day;
    char    month;
    short   year;
};

struct BCS_TIME
{
    char    hour;
    char    minute;
    char    second;
};

#define BCS_FIELD_SEP       0x1C    // seperator for fields of BCS messages

#define BCS_MAXAT           1000    // # of at

#pragma pack()

#endif
