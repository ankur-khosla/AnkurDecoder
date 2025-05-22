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
//  Function:   Header file for AB EOD transactions
//
//  Author  :   Farina Tsui     8-Jul-2003
//
//  Mod     :   FT01            9-JAN-2004
//              Delete EODTRN_RCR (reimbursement crediting)
//              - replaced it by EODTRN_DRCR with type DRCR_AUTO_REIM
//
//              FT02            11-FEB-2004
//              - Add statement charge transaction EODTRN_STMCHG
//                (Statement charge was treated as a Debit transaction 
//                 previously, but now handled as a separate transaction)
//
//              FT03            17-FEB-2004
//              modify union EODTRN_LOG
//              -  remove reverse CIT transaction
//              -  add cancel m6 si & div. from o/s esc tran
//
//              FT04            18-MAR-2004
//              - Add trancations EODTRN_PANCAP & EODTRN_ATMDEP
//
//              FT05            6-AUG-2004
//              - Add struct EODTRN_LOG_DIV for settled dividend log record
//                (instead of writing 2 ACU_TRAN_DIV for PM & FO dividend,
//                 just combine the 2 into 1 log record together with the 
//                 SOD balance for next day)
//
#ifndef EODTRNDEF_H
#define EODTRNDEF_H

#include "acudef.h"


#pragma pack(1)

struct EODTRN_EXTRA
{
    struct ACU_TRAN_EXTRA   e;
    unsigned short          sizewu;
};

union EODTRN_END
{
    unsigned short          sizewu;     // for settled tran
    struct EODTRN_EXTRA     ext;        // for unsettled tran
};

struct EODTRN_LOT
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_LOT     body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position        
};

struct EODTRN_LOT2
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_LOT2    body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position   
};

struct EODTRN_RAC
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_RAC     body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position        
};


struct EODTRN_WTW
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_WTW     body;
    unsigned short          sizewu;
};

struct EODTRN_CAN
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_CAN     body;
    unsigned short          sizewu;
};       

struct EODTRN_SB
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_SB      body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position        
};

struct EODTRN_SB2
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_SB2     body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position    
};

struct EODTRN_ACA_CB
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_ACA_CB  body;
    unsigned short          sizewu;
};

struct EODTRN_ACA_VOICE
{
    struct ACU_TRAN_HDR         h;
    struct ACU_TRAN_ACA_VOICE   body;
    unsigned short              sizewu;
};

struct EODTRN_ACA_CIT
{
    struct ACU_TRAN_HDR         h;
    struct ACU_TRAN_ACA_CIT     body;
    unsigned short              sizewu;
};

struct EODTRN_ACA_MAT
{
    struct ACU_TRAN_HDR         h;
    struct ACU_TRAN_ACA_MAT     body;
    unsigned short              sizewu;
};

struct EODTRN_ACA_AUTO
{
    struct ACU_TRAN_HDR         h;
    struct ACU_TRAN_ACA_AUTO    body;
    unsigned short              sizewu;
};

struct EODTRN_CIT           // cit deposit/fee or deposit/fee refund
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_CIT     body;          
    unsigned short          sizewu;
};

struct EODTRN_DEP
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DEP     body;
    unsigned short          sizewu;
};

struct EODTRN_DEP_TSN
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DEP_TSN body;
    unsigned short          sizewu;
};

struct EODTRN_DEP_ATM        // ATM Deposit
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DEP_ATM body;
    unsigned short          sizewu;
};

struct EODTRN_HSTACC        // account header in history file
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_HSTACC  body;    
    unsigned short          sizewu;
};

struct EODTRN_DRCR          // debit credit adjustmen
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DRCR    body;
    unsigned short          sizewu;
};

struct EODTRN_ACR           // account release
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_ACR     body;
    unsigned short          sizewu;
};

struct EODTRN_SOD
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_SOD     body;
    unsigned short          sizewu;
};

struct EODTRN_RIM           // outstanding bank guarantee reimbursement
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_RIM     body;
    unsigned short          sizewu;
};

struct EODTRN_DIV
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DIV     body;
    unsigned short          sizewu;
};

struct EODTRN_DIV_PUR       // dividend for purged transaction
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DIV_PUR body;    
    unsigned short          sizewu;
};

struct EODTRN_DIV_PUR2      // purged transaction after Q206
{
    struct ACU_TRAN_HDR      h;
    struct ACU_TRAN_DIV_PUR2 body;    
    unsigned short           sizewu;
};

struct EODTRN_DFT           // dividend forfeited
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_DFT     body;
    unsigned short          sizewu;
};

struct EODTRN_AFR           // cit annual fee reversed
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_AFR     body;
    unsigned short          sizewu;
};

struct EODTRN_STMCHG        // statement charge     ! FT02
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_STMCHG  body;
    unsigned short          sizewu;
};

struct EODTRN_CHG           // service charge
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_CHG     body;
    unsigned short          sizewu;
};

//struct EODTRN_PANCAP        // PAN capture
//{
//    struct ACU_TRAN_HDR     h;
//    struct ACU_TRAN_PANCAP  body;
//    unsigned short          sizewu;
//};

struct EODTRN_OLDTB         // old TB tran
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_OLDTB   body;
    unsigned short          sizewu;
};
struct EODTRN_LOG_DIV    // settled dividend log record
{
  struct ACU_TRAN_DIV    div[ACU_DIV_MAX];
  LONGLONG               sodbald;     // next day SOD balance
};

struct EODTRN_HSTRAC2       // RAC2 tran in history file
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_HSTRAC2 body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position        
};

struct EODTRN_HSTRAC3       // RAC3 tran in history file
{
    struct ACU_TRAN_HDR     h;
    struct ACU_TRAN_HSTRAC3 body;
    union EODTRN_END        end;        // since struct BETDATA is of
                                        // variable size, EODTRN_END may be
                                        // put at variable position        
};

union EODTRN_LOG            // tran that have to be logged
{
    struct EODTRN_DIV_PUR     divpur;       // dividend purged for SB upto Q106
    struct EODTRN_DIV_PUR2    divpur2;      // dividend purged after Q206
    struct EODTRN_DFT         dft;          // dividend forfeited
    struct EODTRN_DRCR        drcr;         // dr/cr transaction
                                            //  for typelu=ACU_CREDIT_BGRIM only
    // FT07...
    struct EODTRN_LOT         lot;          // cancel m6 s.i.; LOT div post 
    struct EODTRN_SB          sb;           // SB div post
    struct EODTRN_HSTRAC2     rac2;         // RAC2 div post
    // ...FT07
    struct EODTRN_LOT2         lot2;          // cancel m6 s.i.; LOT div post 
    struct EODTRN_SB2          sb2;           // SB div post
    struct EODTRN_HSTRAC3      rac3;         // RAC3 div post
};

union EODTRN_UNS            // unsettled transactions
{
    struct EODTRN_LOT         lot;
    struct EODTRN_RAC         rac;
    struct EODTRN_SB          sb;
};
    
#pragma pack()

#endif
