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
//  Author  : Raymond Leung     14-DEC-2000
//
//  Mods    :


#ifndef   AFMVAR_H
#define   AFMVAR_H


//#include "afmdef.h"

#define AFMARRAY_SIZE 70

// All-up formula table
#ifndef  _AFM_DATA_
extern  struct AFM   afm[AFMARRAY_SIZE];
#else
        struct AFM   afm[AFMARRAY_SIZE] =
        {
            {  2,  1, 0x01, "2X1  " },	// 2X1      No. of events = 2
            {  2,  3, 0x03, "2X3  " },	// 2X3
            {  3,  1, 0x01, "3X1  " },	// 3X1      No. of events = 3
            {  3,  3, 0x02, "3X3  " },	// 3X3
            {  3,  4, 0x03, "3X4  " },	// 3X4
            {  3,  6, 0x06, "3X6  " },	// 3X6
            {  3,  7, 0x07, "3X7  " },	// 3X7
            {  4,  1, 0x01, "4X1  " },	// 4X1      No. of events = 4
            {  4,  4, 0x02, "4X4  " },	// 4X4
            {  4,  5, 0x03, "4X5  " },	// 4X5
            {  4,  6, 0x04, "4X6  " },	// 4X6
            {  4, 10, 0x0C, "4X10 " },	// 4X10
            {  4, 11, 0x07, "4X11 " },	// 4X11
            {  4, 14, 0x0E, "4X14 " },	// 4X14
            {  4, 15, 0x0F, "4X15 " },	// 4X15
            {  5,  1, 0x01, "5X1  " },	// 5X1      No. of events = 5
            {  5,  5, 0x02, "5X5  " },	// 5X5
            {  5,  6, 0x03, "5X6  " },	// 5X6
            {  5, 10, 0x08, "5X10 " },	// 5X10
            {  5, 15, 0x18, "5X15 " },	// 5X15
            {  5, 16, 0x07, "5X16 " },	// 5X16
            {  5, 20, 0x0C, "5X20 " },	// 5X20
            {  5, 25, 0x1C, "5X25 " },	// 5X25
            {  5, 26, 0x0F, "5X26 " },	// 5X26
            {  5, 30, 0x1E, "5X30 " },	// 5X30
            {  5, 31, 0x1F, "5X31 " },	// 5X31
            {  6,  1, 0x01, "6X1  " },	// 6X1      No. of events = 6
            {  6,  6, 0x02, "6X6  " },	// 6X6
            {  6,  7, 0x03, "6X7  " },	// 6X7
            {  6, 15, 0x10, "6X15 " },	// 6X15
            {  6, 20, 0x08, "6X20 " },	// 6X20
            {  6, 21, 0x30, "6X21 " },	// 6X21
            {  6, 22, 0x07, "6X22 " },	// 6X22
            {  6, 35, 0x18, "6X35 " },	// 6X35
            {  6, 41, 0x38, "6X41 " },	// 6X41
            {  6, 42, 0x0F, "6X42 " },	// 6X42
            {  6, 50, 0x1C, "6X50 " },	// 6X50
            {  6, 56, 0x3C, "6X56 " },	// 6X56
            {  6, 57, 0x1F, "6X57 " },	// 6X57
            {  6, 62, 0x3E, "6X62 " },	// 6X62
            {  6, 63, 0x3F, "6X63 " },	// 6X63
            {  7,  1, 0x01, "7X1  " },  // 7X1      No. of events = 7
            {  7,  7, 0x02, "7X7  " },  // 7X7
            {  7,  8, 0x03, "7X8  " },  // 7X8
            {  7, 21, 0x20, "7X21 " },  // 7X21
            {  7, 28, 0x60, "7X28 " },  // 7X28
            {  7, 29, 0x07, "7X29 " },  // 7X29
            {  7, 35, 0x10, "7X35 " },  // 7X35
            {  7, 56, 0x30, "7X56 " },  // 7X56
            {  7, 63, 0x70, "7X63 " },  // 7X63
            {  7, 64, 0x0F, "7X64 " },  // 7X64
            {  7, 70, 0x18, "7X70 " },  // 7X70
            {  7, 91, 0x38, "7X91 " },  // 7X91
            {  7, 98, 0x78, "7X98 " },  // 7X98
            {  7, 99, 0x1F, "7X99 " },  // 7X99
            {  7,112, 0x3C, "7X112" },  // 7X112
            {  7,119, 0x7C, "7X119" },  // 7X119
            {  7,120, 0x3F, "7X120" },  // 7X120
            {  7,126, 0x7E, "7X126" },  // 7X126
            {  7,127, 0x7F, "7X127" },  // 7X127
        };

#endif


#endif // AFMVAR_H

