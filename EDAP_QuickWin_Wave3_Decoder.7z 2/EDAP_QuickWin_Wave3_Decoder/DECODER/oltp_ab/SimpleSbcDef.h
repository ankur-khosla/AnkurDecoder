#ifndef SIMPLESBCDEF_H
#define SIMPLESBCDEF_H

#pragma pack(1)

struct LOGSBCTRNID          // tournament id in logger record
{
    unsigned char           ptypebu;    // pool type
    unsigned char           pmbu;       // FO/ PM
//    unsigned char           catbu;      // for SPC => SB_SPC_TRN/SB_SPC_MAT
//                                        // for TPS => SB_TPS_PLAYER/SB_TPS_TEAM
//                                        // others => filler
    unsigned char           pidbu;      // TRN => TRN id
                                        // SPC-TRN base => TRN id
                                        // SPC-match base => match day 
    unsigned char           subidbu;    // GPF/GPW => group id
                                        // ADTP => event id
                                        // TPS => PLAYER/TEAM type
                                        // SPC-TRN base => type id
                                        // SPC-match base => match #
                                        // others => filler
    unsigned char           itembu;     // SPC => item id
                                        // others => filler
    unsigned short          idxwu;      // TRN index/ SPC map index 
};

struct LOGSBCPOOLNEW            // define new pool (with 2 collation area) (147)
{
    unsigned char               single1:1;          // single allowed
    unsigned char               aup1:1;             // all-up allowed
    unsigned char               hftbet1:1;          // half/full time bet allowed
    unsigned char               ipbet1:1;           // in-running bet allowed
    unsigned char               norbet1:1;          // normal betting allowed [y/n] // JC45
    unsigned char               extbet1:1;          // extra time Betting			// Q407
    unsigned char               :2;                 // unused                       // JC45
    unsigned char               cpxPoolbu;          // cpx pool type
    unsigned char               pTypebu;            // pool type SIMPLE/CPX
    short                       idxw;               // champ/ match/ cpx pool index
    unsigned int                newColSizelu;       // next collation size pointer JN46
    unsigned short              newNumwu;           // new max # of cpx pool
    unsigned int                punitlu;            // partial unti in $
    unsigned int                minCostlu;          // min. tkt cost in $
    struct BSTMEMPTR            oddsp;                    // odds pointer             JN46
    unsigned int                nwcmSizelu;               // next wcm array pointer   JN46
    unsigned short              numCombwu;               // no. of col/plimit combination JN46
    unsigned char               poolCat;
	unsigned char				noOfSimplePool;
	unsigned char				dayCode;
	unsigned char				matchId;
	unsigned char				poolType;
};

struct LOGSBCTINP           // define new TRN pool (108)/ SPC pool (109)
{
    struct LOGSBCTRNID      id;                     // tournament id
    __time32_t                  tDate;                  // tournament event date, DJ30...
    __time32_t                  drsdate;                // reference creation datetime ( datBusinessTime() )
    __time32_t                  sDate;                  // trn settlement date                       
    __time32_t                  cDate;                  // pool creation date
    unsigned short          newNumwu;               // new last TRN/SPC Map index used
    unsigned short          spcIdxwu;               // new SPC idx
    unsigned short          newSpcwu;               // new last SPC index used
    short                   catIdxw;                // default match idx/ TRN idx
                                                    // for SPC set default id used only, -1=>no default)
    //LONGLONG                netLossd;               // max. net loss amount in cents
    unsigned char            single1:1;              // single allowed
    unsigned char            aup1:1;                 // all-up allowed
    unsigned char            exact1:1;               // exact result order
    unsigned char            exo1:1;                 // exotic pool flag i.e. non-collated
    unsigned char            min1:1;                 // min select for TPS, 0=>others enabled    // JC36
	unsigned char            hftbet1 : 1;              // half time betting pool allowed [y/n] // JN46
	unsigned char            ipbet1 : 1;               // in-play betting pool allowed [y/n]   // JN46
	unsigned char            norbet1 : 1;              // normal betting allowed [y/n]         // JN46
    unsigned char           minSelbu;               // min. # of selection in each group
    unsigned char           maxSelbu;               // max. # of selection in each group
    unsigned char           nselbetbu;              // min. # of selection in a bet
    unsigned char           nGroupbu;               // # of group
    unsigned char           nTeambu;                // max. # of team in within groups
    //unsigned int            colSizelu;              // collation size of this pool
    //unsigned int            colStartlu;             // collation pointer in COLCOM
    unsigned int            newColSizelu;           // next use collation pointer
    unsigned short          refMapPtrwu;            // ref. file mapping table pointer
    unsigned int            refDataPtrlu;           // ref. file data byte pointer
    unsigned int            refDataSizelu;          // ref. file data byte size
    unsigned int            refDataNewSizelu;       // ref. file new data byte pointer
    unsigned short          fillerwu;               // 
    unsigned int            punitlu;                // partial unti in $        // JC33..
    unsigned int            minCostlu;              // min. tkt cost in cents
    unsigned char           numSelbu;               // number of selection
    unsigned short          homewu;                 // for SPC match base used only
    unsigned short          awaywu;                 // for SPC match base used only
};

union   LOGSBCD                         // log data
{
	struct LOGSBCPOOLNEW	poolNew;
	struct LOGSBCTINP		tinp;
};

struct LOGSBCH
{
    unsigned short      codewu;         // sbc function code
	unsigned int        msnlu;          // msn
};

struct LOGSBC          // log message
{
    struct LOGSBCH      h;              // header
    union  LOGSBCD      d;              // data
};


#pragma pack()

#endif
