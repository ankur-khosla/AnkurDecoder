//    *******************************************************************
//    *                                                                 *
//    *  Function : This function is to format bet details from bet/log *
//    *             record                                              *
//    *                                                                 *
//    *             For AUP pool:                                       *
//    *                 eg. AWN 2X3 2*1+2/3*1+6                         *
//    *             Format:                                             *
//    *                 (pool name+formula+race+selection)              *
//    *                                                                 *
//    *             For STD+EXO pool:                                   *
//    *                 eg. WIN 1*1+2                                   *
//    *             Format:                                             *
//    *                 (pool name+race+selection)                      *
//    *                                                                 *
//    *             For LOT pool:                                       *
//    *                 eg. RG MK6 1+2+4+17+18+45                       *
//    *             For GBL pool:                                       *
//    *                 eg. RG GBL 1+3+4+9+20+25#61                     *
//    *             Format:                                             *
//    *                 (indicator+pool name+selection)                 *
//    *                                                                 *
//    *             For CV:                                             *
//    *                 eg. CV 0 0 AUTO                                 *
//    *             Format:                                             *
//    *                 (pool name+log seq at selling+                  *
//    *                  pay seq at selling+method)                     *
//    *                                                                 *
//    *******************************************************************

#include "DeSelMap.h"

char* DeSelMap::GetType(char m_cType, char Type[10])
{
	switch (m_cType)
	{
	case BETTYP_WINPLA:
		sprintf(Type, "W-P");
		break;
		
	case BETTYP_WIN:
		sprintf(Type, "WIN");
		break;
		
	case BETTYP_PLA:
		sprintf(Type, "PLA");
		break;

	case BETTYP_QIN:
		sprintf(Type, "QIN");
		break;

	case BETTYP_QPL:
		sprintf(Type, "QPL");
		break;

	case BETTYP_DBL:
		sprintf(Type, "DBL");
		break;

	case BETTYP_TCE:
		sprintf(Type, "TCE");
		break;

	case BETTYP_FCT:
		sprintf(Type, "FCT");
		break;

	case BETTYP_QTT:
		sprintf(Type, "QTT");
		break;

	case BETTYP_DQN:
		sprintf(Type, "D-Q");
		break;

	case BETTYP_TBL:
		sprintf(Type, "TBL");
		break;

	case BETTYP_TTR:
		sprintf(Type, "T-T");
		break;

	case BETTYP_6UP:
		sprintf(Type, "6UP");
		break;

	case BETTYP_DTR:
		sprintf(Type, "D-T");
		break;

	case BETTYP_TRIO:
		sprintf(Type, "TRI");
		break;

	case BETTYP_QINQPL:
		sprintf(Type, "QQP");
		break;

	case BETTYP_CV:
		sprintf(Type, "CV");
		break;

	case BETTYP_MK6:
		sprintf(Type, "MK6");
		break;

	case BETTYP_PWB:
		sprintf(Type, "PWB");
		break;

	case BETTYP_ALUP:
		sprintf(Type, "ALUP");
		break;

	case BETTYP_FF:
		sprintf(Type, "F-F");
		break;

	case BETTYP_BWA:
		sprintf(Type, "BWA");
		break;

	case BETTYP_CWA:
		sprintf(Type, "CWA");
		break;

	case BETTYP_CWB:
		sprintf(Type, "CWB");
		break;

	case BETTYP_CWC:
		sprintf(Type, "CWC");
		break;
	
	case BETTYP_IWN:
		sprintf(Type, "IWN");
		break;
	default:
		sprintf(Type, "XXXX");
		break;
	}

	return(Type);
}

void DeSelMap::GetSel(const struct LOG *pMlog, unsigned char m_cType, char bufs[1024]) // bet line output
{
    //char pols[5], legs[5], sels[1024], cvs[5];
	char legs[5], sels[1024];
    unsigned char indexbu=0;

    switch (m_cType)
    {
		case BETTYP_ALUP:
            indexbu = pMlog->d.bt.rac.bet.d.var.a.fmlbu;
			getForm(indexbu, legs);
            fmtAup(pMlog, sels); // format allup bets
            sprintf(bufs, "%s", osi_atrim(sels)); // output string
            break;

        case BETTYP_MK6:
        case BETTYP_PWB:

            fmtMk6(pMlog, pMlog->d.bt.lot.tsn.s.w12.type3, sels); // format mk6/gbl bets
            // output string
            sprintf(bufs+strlen(bufs), "%s", osi_atrim(sels)); 
            break;

        case BETTYP_WINPLA:
        case BETTYP_WIN:
        case BETTYP_PLA:
        case BETTYP_IWN:
		case BETTYP_QIN:
        case BETTYP_QPL:
        case BETTYP_DBL:
        case BETTYP_TCE:
		case BETTYP_FCT:
        case BETTYP_QTT:
        case BETTYP_DQN:
        case BETTYP_TBL:
        case BETTYP_TTR:
        case BETTYP_6UP:
        case BETTYP_DTR:
        case BETTYP_TRIO:
        case BETTYP_QINQPL:
		case BETTYP_FF:
		case BETTYP_BWA:
		case BETTYP_CWA:
		case BETTYP_CWB:
		case BETTYP_CWC:		
            fmtNrm(pMlog, sels); // format std/exo bets
            sprintf(bufs, "%s", osi_atrim(sels)); // output string
            break;

        default:
            break;
    }
}

void DeSelMap::fmtAup( const struct LOG * pMlog, char sels[1024])
{
    unsigned short iwu=0, numofbnkbmp=0;
	unsigned char bettype;

	for (int a=0; a < pMlog->d.bt.rac.bet.d.var.a.evtbu; a++)
	{
		bettype = pMlog->d.bt.rac.bet.d.var.a.sel[a].bettypebu;

		switch (bettype)
		{
			case BETTYP_WINPLA:
			case BETTYP_WIN:
			case BETTYP_PLA:
			case BETTYP_BWA:
			case BETTYP_CWA:
			case BETTYP_CWB:
			case BETTYP_CWC:			
				if (a == 0)
					sprintf(sels, "%d*", pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu);
				else
					sprintf(sels+strlen(sels), "%d*", 
					pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu);
					fmtSln(pMlog, 0, true, a, sels+strlen(sels));
					fmtInd(pMlog, true, a, sels+strlen(sels));
					sprintf(sels+strlen(sels), "/");
				break;
			case BETTYP_IWN:
			case BETTYP_QIN:
			case BETTYP_QPL:
			case BETTYP_TRIO:
			case BETTYP_QINQPL:
			case BETTYP_FF:
				
				if (a == 0)
                    sprintf(sels, "%d*", pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu);
                else
                    sprintf(sels+strlen(sels), "%d*", 
                            pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu);

                // get number of banker bitmap
                if ((pMlog->d.bt.rac.bet.d.var.a.sel[a].ind.bnk1 & 0x01) == 1)
                    numofbnkbmp = 1; 

                fmtQin(pMlog, numofbnkbmp, 2, 0, true, a, 
                       sels+strlen(sels));
                fmtInd(pMlog, true, a, sels+strlen(sels));
                sprintf(sels+strlen(sels), "/");
				break;

			case BETTYP_FCT:

				if (a == 0)
					sprintf(sels, "%d*", pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu);
				else
					sprintf(sels + strlen(sels), "%d*",
						pMlog->d.bt.rac.bet.d.var.a.sel[a].racebu);
				fmtExtAup(pMlog, 2, a, sels + strlen(sels));
				fmtInd(pMlog, true, a, sels + strlen(sels));
				sprintf(sels + strlen(sels), "/");

				break;

        default:
            break;
		}
	}
	sels[strlen(sels)-1] = 0; // cancel last '/' operator
}
/*    switch (pMlog->d.bt.rac.bet.d.hdr.bettypebu) // format selection details for diff. pool
    {
        case BETTYP_AWP:
        case BETTYP_AWN:
        case BETTYP_APL:
            // for each event
            for (iwu=0; iwu<pMlog->d.bt.rac.bet.d.var.a.evtbu; iwu++)
            {
                if (iwu == 0)
                    sprintf(sels, "%d*", pMlog->d.bt.rac.bet.d.var.a.sel[iwu].racebu);
                else
                    sprintf(sels+strlen(sels), "%d*", 
                            pMlog->d.bt.rac.bet.d.var.a.sel[iwu].racebu);
                fmtSln(pMlog, 0, true, iwu, sels+strlen(sels));
                fmtInd(pMlog, true, iwu, sels+strlen(sels));
                sprintf(sels+strlen(sels), "/");
            }
            sels[strlen(sels)-1] = 0; // cancel last '/' operator
            break;
        case BETTYP_AQN:
        case BETTYP_AQP:
        case BETTYP_ATR:
        case BETTYP_AQQP:
            // for each event
            for (iwu=0; iwu<pMlog->d.bt.rac.bet.d.var.a.evtbu; iwu++)
            {
                if (iwu == 0)
                    sprintf(sels, "%d*", pMlog->d.bt.rac.bet.d.var.a.sel[iwu].racebu);
                else
                    sprintf(sels+strlen(sels), "%d*", 
                            pMlog->d.bt.rac.bet.d.var.a.sel[iwu].racebu);

                // get number of banker bitmap
                if ((pMlog->d.bt.rac.bet.d.var.a.sel[iwu].ind.bnk1 & 0x01) == 1)
                    numofbnkbmp = 1; 

                fmtQin(pMlog, numofbnkbmp, 2, 0, true, iwu, 
                       sels+strlen(sels));
                fmtInd(pMlog, true, iwu, sels+strlen(sels));
                sprintf(sels+strlen(sels), "/");
            }
            sels[strlen(sels)-1] = 0; // cancel last '/' operator
            break;
        default:
            break;
    }
*/


void DeSelMap::fmtMk6( const struct LOG * pMlog, unsigned int m_iType, char sels[200])
{
    unsigned short pwbbasewu=0, offsetwu=0, iwu=0; 
    char drselb[3];
    
    memset(drselb, 0, sizeof(drselb)); // init drselbu

    // Insert multi-draw description if bet is multi-draw
    if (m_iType == TSN_TYPE_MD)
    {
        // Convert no. of draws into ascii
        editD(drselb, "99", (LONGLONG)pMlog->d.bt.rac.bet.d.var.lot.var.md.drselbu);
        for (iwu=0; iwu<strlen(drselb); iwu++)
            sels[offsetwu+iwu] = drselb[iwu];
        offsetwu += strlen(drselb);

        sels[offsetwu] = ' ';
        offsetwu += 1;
    }

    // Format concurrent game selections
    if (pMlog->d.bt.rac.bet.d.var.lot.n.gamebu >= LOT_GAME_OEG && 
        pMlog->d.bt.rac.bet.d.var.lot.n.gamebu <= LOT_GAME_OUG)
    {
        fmtbet_ccg(pMlog->d.bt.rac.bet.d.hdr.bettypebu, pMlog->d.bt.rac.bet.d.var.lot.n.gamebu,
                   pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.pcmbu, &offsetwu, sels);
    }

    if (pMlog->d.bt.rac.bet.d.var.lot.n.gamebu == LOT_GAME_OEG)
    {
        // Format odd-even selections
        fmtbet_oeg(pMlog->d.bt.rac.bet.d.hdr.bettypebu, pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.nbnkbu,
                   pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.bnkmbu, &offsetwu, sels);
    }
    else
    {
        // Single entry
        if ((pMlog->d.bt.rac.bet.d.var.lot.n.multi1 & 0x01) == 0)
        {
            // Format banker bitmap
            if (pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.nbnkbu != 0)
            {
                //
                // modified by david jin
                //
                if (pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.pbasbu != 0
                    && pMlog->d.bt.rac.bet.d.var.lot.n.gamebu == LOT_GAME_EXN)
                {
                    // Insert powerball selection set separator '#'
                    sels[offsetwu] = BET_PWBSEP_C;
                    offsetwu += 1;
                    //pwbbasewu = fmtbet->d.var.lot.n.sel.single.pbasbu;
                } 
                ///////////////////////////////////////////////////////////           

                // Format banker selection bitmap
                fmtMk6Sln(pwbbasewu, 1, pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.bnkmbu, 
                        &offsetwu, sels);

                // Insert banker symbol '>'
                if (pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.nothbu != 0)
                {
                    // No more other selections
                    sels[offsetwu] = BET_BNKSYM_C;
                    offsetwu += 1;
                }
            }
                                              
            // Format normal selection bitmap (for Mk6+GBL)
            if (pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.nothbu != 0)
            {
                fmtMk6Sln(pwbbasewu, 1, pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.othmbu, 
                        &offsetwu, sels); 
            }

            // Insert field symbol if field bet
            if ((pMlog->d.bt.rac.bet.d.var.lot.n.field1 & 0x01) != 0)
            {
                // Insert field symbol 'F'
                sels[offsetwu] = BET_FLDSYM_C;
                offsetwu += 1;
            }  

            // Format powerball selection bitmap
            if (pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.npwbbu != 0)
            {
                // Insert powerball selection set separator '#'
                sels[offsetwu] = BET_PWBSEP_C;
                offsetwu += 1;
                pwbbasewu = pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.pbasbu;
                fmtMk6Sln(pwbbasewu, 1, pMlog->d.bt.rac.bet.d.var.lot.n.sel.single.pcmbu,
                        &offsetwu, sels);
            }
        }
        else        // Multi-entry
        {
            for (iwu=0; iwu<pMlog->d.bt.rac.bet.d.var.lot.n.sel.multi.entbu; iwu++)
            {
                fmtMk6Sln(pwbbasewu, 0, pMlog->d.bt.rac.bet.d.var.lot.n.sel.multi.selbu[iwu],
                        &offsetwu, sels);

                // Insert entry separator '/'
                sels[offsetwu] = BET_ENTSEP_C;
                offsetwu += 1;
            }
            // No Insert entry separator at the end
            offsetwu -= 1;
        }

        // Format any add-on selections
        if (pMlog->d.bt.rac.bet.d.var.lot.var.aon.abaswu != 0)
        {
            // There are add-on selections
            fmtbet_aon(pMlog->d.bt.rac.bet.d.var.lot.var.aon.aselbu, pMlog->d.bt.rac.bet.d.var.lot.var.aon.abaswu, 
                        &offsetwu, sels);
        }
    }

    // Insert field delimiter ' '
    sels[offsetwu] = '\0';
}

void DeSelMap::fmtNrm(const struct LOG *pMlog, char sels[1024])
{
    unsigned short iwu=0, legwu=0;

    sprintf(sels, "%d*", pMlog->d.bt.rac.bet.d.var.es.racebu); // get race number

    switch (pMlog->d.bt.rac.bet.d.hdr.bettypebu) // get selection details for diff. pool
    {
        case BETTYP_WINPLA:
        case BETTYP_WIN:
        case BETTYP_PLA:
		case BETTYP_BWA:
		case BETTYP_CWA:
		case BETTYP_CWB:
		case BETTYP_CWC:
            fmtSln(pMlog, 0, false, 0, sels+strlen(sels));
            break;
        case BETTYP_QINQPL:
        case BETTYP_QIN:

        case BETTYP_QPL:

        case BETTYP_TRIO:
		case BETTYP_FF:
            fmtQin(pMlog, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[0], 2, 0, false, 0, 
                   sels+strlen(sels));
            break;
		case BETTYP_IWN:
            fmtQin(pMlog,1, 2, 0, false, 0, 
                   sels+strlen(sels));
            break;


        case BETTYP_TCE:
            fmtExt(pMlog, 3, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[0], sels+strlen(sels));
            break;
		case BETTYP_FCT:
			fmtExt(pMlog, 2, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[0], sels + strlen(sels));
			break;
        case BETTYP_QTT:
            fmtExt(pMlog, 4, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[0], sels+strlen(sels));
            break;
        case BETTYP_DBL:
        case BETTYP_TBL:
        case BETTYP_6UP:
            // get number of legs
           // legwu = pMlog->d.bt.rac.bet.d.hdr.bettypebu;
			if (pMlog->d.bt.rac.bet.d.hdr.bettypebu == BETTYP_DBL)
			{
				legwu = 2;
			}
			else if (pMlog->d.bt.rac.bet.d.hdr.bettypebu == BETTYP_TBL)
			{
				legwu = 3;
			}
			else if (pMlog->d.bt.rac.bet.d.hdr.bettypebu == BETTYP_6UP)
			{
				legwu = 6;
			}
            for (iwu=0; iwu<legwu; iwu++)
            {
                fmtSln(pMlog, iwu, false, 0, sels+strlen(sels));
                if (iwu < legwu-1)
                    sprintf(sels+strlen(sels), "/"); // field seperator
            }
            break;

		case BETTYP_TTR:

			// get number of legs
//            legwu = 3/*stdExoBetType2LegCnt(pMlog->d.bt.rac.bet.d.hdr.bettypebu)*/;
/*
            for (iwu=0; iwu<legwu; iwu++)
            {
                fmtQin(pMlog, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[iwu], 2, iwu*2, false, 0, 
                       sels+strlen(sels));
                if (iwu < legwu-1)
                    sprintf(sels+strlen(sels), "/"); // field seperator
            }
            break;
*/
			// get number of legs
            legwu = 3/*stdExoBetType2LegCnt(pMlog->data.bt.rac.tran.bet.d.hdr.bettypebu)*/;
            for (iwu=0; iwu<legwu; iwu++)
            {
                fmtQin(pMlog, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[iwu], 2, iwu*2, false, 0, 
                       sels+strlen(sels));
                if (iwu < legwu-1)
                    sprintf(sels+strlen(sels), "/"); // field seperator
            }
			if ( pMlog->d.bt.rac.bet.d.var.es.ind.twoentry )
			{
				sprintf( sels+strlen(sels), "|%d*", pMlog->d.bt.rac.bet.d.var.es.racebu);
				for (iwu=0; iwu<legwu; iwu++)
				{
					fmtQin2(pMlog, 0, 2, iwu*2, false, 0, 
						   sels+strlen(sels));
					if (iwu < legwu-1)
						sprintf(sels+strlen(sels), "/"); // field seperator
				}
			}
            break;

        case BETTYP_DQN:       
        case BETTYP_DTR:
            // get number of legs
            legwu = 2;	//(pMlog->d.bt.rac.bet.d.hdr.bettypebu);
            for (iwu=0; iwu<legwu; iwu++)
            {
                fmtQin(pMlog, pMlog->d.bt.rac.bet.d.var.es.betexbnk.bnkbu[iwu], 2, iwu*2, false, 0, 
                       sels+strlen(sels));
                if (iwu < legwu-1)
                    sprintf(sels+strlen(sels), "/"); // field seperator
            }
            break;

        default:
            break;
    }

    fmtInd(pMlog, false, 0, sels+strlen(sels)); // format indicator
}

void DeSelMap::fmtInd( const struct LOG *pMlog, const bool allupt, // true if allup
			 const unsigned short idwu, // id no. for allup array
             char sels[200]) // selections

{
    bool prtft=false;

    if (allupt == false) // std+exo bet
    {
        if ((pMlog->d.bt.rac.bet.d.var.es.ind.fld1 & 0x01) == 1)
        {
            sprintf(sels, "F"); // field indicator
            prtft=true;
        }
        if ((pMlog->d.bt.rac.bet.d.var.es.ind.mul1 & 0x01) == 1)
        {
            if (prtft == false)
                sprintf(sels, "M"); // multiple indicator
            else
                sprintf(sels+strlen(sels), "M"); 
        }
    }
    else // aup bet
    {
        if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.fld1 & 0x01) == 1)
            sprintf(sels, "F"); // field indicator 
        if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.mul1 & 0x01) == 1)
            sprintf(sels, "M"); // multiple indicator
    }
}

void DeSelMap::fmtQin( const struct LOG *pMlog, const unsigned short numofbnk, // num of bankers
             const unsigned short numofbmp, // num of bitmaps
             const unsigned short bmpposwu, // bitmap position
             const bool allupt, // true if allup
             const unsigned short idwu, // id no. of allup array
             char sels[]) // selections
{
    unsigned short iwu=0;

    if (allupt == false) // std+exo bet
    {
        if (numofbnk == 0) // if no banker
            fmtSln(pMlog, bmpposwu, false, 0, sels);
        else 
        {
            for (iwu=0; iwu<numofbmp; iwu++)
            {
                if (iwu == 0) // get horse number with banker
                    fmtSln(pMlog, iwu+bmpposwu, false, 0, sels);
                else
                    fmtSln(pMlog, iwu+bmpposwu, false, 0, sels+strlen(sels));
                if (iwu < numofbmp-1)
				{
					if (pMlog->d.bt.rac.bet.d.hdr.bettypebu != BETTYP_IWN)
						sprintf(sels+strlen(sels), ">"); // banker seperator
					else 
						sprintf(sels+strlen(sels), "#"); // banker seperator  <======== IWN 

	


				}   
            }
        }
    }
    else // allup bet
    {
        if (numofbnk == 0) // if no banker
            fmtSln(pMlog, bmpposwu, true, idwu, sels);
        else 
        {
            for (iwu=0; iwu<numofbmp; iwu++)
            {
                if (iwu == 0) // get horse number with banker
                    fmtSln(pMlog, iwu+bmpposwu, true, idwu, sels);
                else
                    fmtSln(pMlog, iwu+bmpposwu, true, idwu, 
                           sels+strlen(sels));
                if (iwu < numofbmp-1)
                    sprintf(sels+strlen(sels), ">"); // banker seperator
            }
        }
    }
}

void DeSelMap::fmtQin2( const struct LOG *pMlog, const unsigned short numofbnk, // num of bankers
             const unsigned short numofbmp, // num of bitmaps
             const unsigned short bmpposwu, // bitmap position
             const bool allupt, // true if allup
             const unsigned short idwu, // id no. of allup array
             char sels[]) // selections
{
    unsigned short iwu=0;

    if (numofbnk == 0) // if no banker
        fmtSln2(pMlog, bmpposwu, false, 0, sels);
    else 
    {
        for (iwu=0; iwu<numofbmp; iwu++)
        {
            if (iwu == 0) // get horse number with banker
                fmtSln2(pMlog, iwu+bmpposwu, false, 0, sels);
            else
                fmtSln2(pMlog, iwu+bmpposwu, false, 0, sels+strlen(sels));
            if (iwu < numofbmp-1)
                sprintf(sels+strlen(sels), ">"); // banker seperator
        }
    }
}

void DeSelMap::fmtSln( const struct LOG *pMlog, const unsigned short bmppos, // bitmap position 
             const bool allupt, // true if allup
             const unsigned short idwu, // id no. for allup array
             char sels[]) // selections
{
    unsigned short iwu=0, jwu=0, fldwu=0;

    fldwu = RDS_MAXFLD; // max field size for each race

    if (allupt == false) // std+exo bet
    {
        for (jwu=1; jwu<=fldwu; jwu++)
        {
			
			

				if ((pMlog->d.bt.rac.bet.d.var.es.sellu[bmppos] & ((__int64)1<<jwu)) != 0)
				{
					iwu++;
					if (iwu == 1)
						sprintf(sels, "%02d+", jwu);
					else
						sprintf(sels+strlen(sels), "%02d+", jwu);
				}


				




        }
    }
    else // allup bet
    {
        for (jwu=1; jwu<=fldwu; jwu++)
        {
            // get selections details
            if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].sellu[bmppos] & ((__int64)1<<jwu)) != 0)
            {
                iwu++;
                if (iwu == 1)
                    sprintf(sels, "%d+", jwu);
                else
                    sprintf(sels+strlen(sels), "%d+", jwu);
            }
        }
    }

	//exclude TCE/QTT/FCT, they cancel last '+' in fmtExt/fmtExtAup 
	//1.if allup, bet type 'FCT' is from leg1/leg2.. 
	//2.if signle leg, bet type 'FCT' is from header
    if (pMlog->d.bt.rac.bet.d.hdr.bettypebu != BETTYP_TCE && 
        pMlog->d.bt.rac.bet.d.hdr.bettypebu != BETTYP_QTT &&
		(
			((!allupt) && (pMlog->d.bt.rac.bet.d.hdr.bettypebu != BETTYP_FCT)) ||
			(allupt && pMlog->d.bt.rac.bet.d.var.a.sel[idwu].bettypebu != BETTYP_FCT)
		)
	)
        sels[strlen(sels)-1] = 0; // cancel last '+' operator
}

void DeSelMap::fmtSln2( const struct LOG *pMlog, const unsigned short bmppos, // bitmap position 
             const bool allupt, // true if allup
             const unsigned short idwu, // id no. for allup array
             char sels[]) // selections
{
    unsigned short iwu=0, jwu=0, fldwu=0;

    fldwu = RDS_MAXFLD; // max field size for each race

    for (jwu=1; jwu<=fldwu; jwu++)
    {
        // get selection details
        if ((pMlog->d.bt.rac.bet.d.var.es.betexbnk.sellu[bmppos] & ((__int64)1<<jwu)) != 0)
        {
            iwu++;
            if (iwu == 1)
                sprintf(sels, "%02d+", jwu);
            else
                sprintf(sels+strlen(sels), "%02d+", jwu);
        }
    }
	sels[strlen(sels)-1] = 0; // cancel last '+' operator
}

void DeSelMap::fmtExt( const struct LOG *pMlog, const unsigned short numofbmp, // number of bitmap
             const unsigned short numofbnk, // number of banker
             char sels[]) // selections
{
    unsigned short iwu=0, numofbnkbmp=0;
    
    // single/single banker TCE/QTT/FCT bet
    if (pMlog->d.bt.rac.bet.d.var.es.ind.bnk1 == 0 && pMlog->d.bt.rac.bet.d.var.es.ind.fld1 == 0 &&
        pMlog->d.bt.rac.bet.d.var.es.ind.mbk1 == 0 && pMlog->d.bt.rac.bet.d.var.es.ind.mul1 == 0) 
    {
        for (iwu=0; iwu<numofbmp; iwu++)
        {
            if (iwu == 0)
                fmtSln(pMlog, iwu, false, 0, sels);
            else
                fmtSln(pMlog, iwu, false, 0, sels+strlen(sels));
        }
        sels[strlen(sels)-1] = 0; // cancel last '+' operator
    }
    else if ((pMlog->d.bt.rac.bet.d.var.es.ind.mbk1 & 0x01) == 1) // multi-banker bet
    {
        for (iwu=0; iwu<numofbmp; iwu++)
        {
            if (iwu == 0)
                fmtSln(pMlog, iwu, false, 0, sels);
            else
                fmtSln(pMlog, iwu, false, 0, sels+strlen(sels));

            sprintf(sels+strlen(sels)-1, ">"); // banker seperator
        }
        sels[strlen(sels)-1] = 0; // cancel last '>' operator
    }
    else if ((pMlog->d.bt.rac.bet.d.var.es.ind.mul1 & 0x01) == 1) // mult bet
    {
        if ((pMlog->d.bt.rac.bet.d.var.es.ind.bnk1 & 0x01) == 0) // multiple bet
        {
            for (iwu=0; iwu<numofbmp; iwu++)
            {
                if (iwu == 0)
                    fmtSln(pMlog, iwu, false, 0, sels);
                else
                    fmtSln(pMlog, iwu, false, 0, sels+strlen(sels));
            }
            sels[strlen(sels)-1] = 0; // cancel last '+' operator
        }
    }

    if ((pMlog->d.bt.rac.bet.d.var.es.ind.bnk1 & 0x01) == 1) // for single/multiple banker
    {
        for (iwu=0; iwu<numofbmp; iwu++) // get num of bnk bitmap
        {
            if (pMlog->d.bt.rac.bet.d.var.es.sellu[iwu] == 0)
                break;
            numofbnkbmp++; 
        }

        for (iwu=0; iwu<numofbmp; iwu++)
        {
            if (iwu == 0)
                fmtSln(pMlog, iwu, false, 0, sels);
            else
                fmtSln(pMlog, iwu, false, 0, sels+strlen(sels));

            if (iwu == numofbnkbmp-2)
                sprintf(sels+strlen(sels)-1, ">"); // banker seperator
        }
        sels[strlen(sels)-1] = 0; // cancel last '>' operator
    }
}

void DeSelMap::fmtExtAup(const struct LOG *pMlog, const unsigned short numofbmp, // number of bitmap
	const unsigned short idwu, // id no. of allup array
	char sels[]) // selections
{
	unsigned short iwu = 0, numofbnkbmp = 0;

	// single/single banker TCE/QTT/FCT bet
	if (pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.bnk1 == 0 && pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.fld1 == 0 &&
		pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.mbk1 == 0 && pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.mul1 == 0)
	{
		for (iwu = 0; iwu<numofbmp; iwu++)
		{
			if (iwu == 0)
				fmtSln(pMlog, iwu, true, idwu, sels);
			else
				fmtSln(pMlog, iwu, true, idwu, sels + strlen(sels));
		}
		sels[strlen(sels) - 1] = 0; // cancel last '+' operator
	}
	else if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.mbk1 & 0x01) == 1) // multi-banker bet
	{
		for (iwu = 0; iwu<numofbmp; iwu++)
		{
			if (iwu == 0)
				fmtSln(pMlog, iwu, true, idwu, sels);
			else
				fmtSln(pMlog, iwu, true, idwu, sels + strlen(sels));

			sprintf(sels + strlen(sels) - 1, ">"); // banker seperator
		}
		sels[strlen(sels) - 1] = 0; // cancel last '>' operator
	}
	else if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.mul1 & 0x01) == 1) // mult bet
	{
		if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.bnk1 & 0x01) == 0) // multiple bet
		{
			for (iwu = 0; iwu<numofbmp; iwu++)
			{
				if (iwu == 0)
					fmtSln(pMlog, iwu, true, idwu, sels);
				else
					fmtSln(pMlog, iwu, true, idwu, sels + strlen(sels));
			}
			sels[strlen(sels) - 1] = 0; // cancel last '+' operator
		}
	}

	if ((pMlog->d.bt.rac.bet.d.var.a.sel[idwu].ind.bnk1 & 0x01) == 1) // for single/multiple banker
	{
		for (iwu = 0; iwu<numofbmp; iwu++) // get num of bnk bitmap
		{
			if (pMlog->d.bt.rac.bet.d.var.a.sel[idwu].sellu[iwu] == 0)
				break;
			numofbnkbmp++;
		}

		for (iwu = 0; iwu<numofbmp; iwu++)
		{
			if (iwu == 0)
				fmtSln(pMlog, iwu, true, idwu, sels);
			else
				fmtSln(pMlog, iwu, true, idwu, sels + strlen(sels));

			if (iwu == numofbnkbmp - 2)
				sprintf(sels + strlen(sels) - 1, ">"); // banker seperator
		}
		sels[strlen(sels) - 1] = 0; // cancel last '>' operator
	}
}

void DeSelMap::fmtbet_aon (const unsigned char mapbu[],  // Addon selection bitmap
                 const unsigned short baswu,   // Addon base investment
                 unsigned short *offsetwu, // position offset
                 char betb[]) // selections
{   
    char ccgameb[] = "[MATCH-3 ";
    char tempb[2] = "";
    char basinvb[20] = "";
    const char inmaskb[] = "99";                // Mask

    int i = 0;                                  // Temporary variable
    
    *offsetwu += 1;
    
    memcpy(betb+*offsetwu, ccgameb, sizeof(ccgameb));
    *offsetwu += strlen(ccgameb);

    // Format addon selections
    // Selection values are binary, not bitmap
    for (i = 0; i < BET_LOT_MAXAONS; i++)
    {
        // Insert the number into ascii bet line
        editD(tempb, inmaskb, (LONGLONG)mapbu[i]);
                
        if (mapbu[i] < 10)
        {
            // Single digit result
            betb[*offsetwu] = tempb[1];
            *offsetwu += 1;
        }
        else if (mapbu[i] >= 10 && mapbu[i] <= 99)
        {
            // Two-digit result
            betb[*offsetwu] = tempb[0];
            *offsetwu += 1;
            betb[*offsetwu] = tempb[1];
            *offsetwu += 1;
        }

        // Insert separator '+' or ' ' 
        if (i != BET_LOT_MAXAONS-1)
        {    
            betb[*offsetwu] = BET_NUMSEP_C;
            *offsetwu += 1;
        }
        else
        {
            betb[*offsetwu] = ' ';
            *offsetwu += 1;
        }
    }       

    // Format addon base investment
    editD(basinvb, "$99,999S", (LONGLONG)baswu); // get base investment
    ltrimzero(basinvb);
    memcpy(betb+*offsetwu, basinvb, sizeof(basinvb));
    *offsetwu += strlen(basinvb) - 1;

    betb[*offsetwu] = ']';
    *offsetwu += 1;
}

void DeSelMap::fmtbet_oeg ( const unsigned char bettypebu,       // bet type
                  const unsigned char nselbu,   // # of selections
                  const unsigned char mapbu[],  // Selection bitmap
                  unsigned short *offsetwu, // Offset
                  char sels[]) // selections
{
    int i = 0;              // Temporary variable
    
    for (i = 0; i < nselbu; i++)
    {
        if (mapbu[i] & 0x01)
        {
            // Odd number selected
            sels[*offsetwu] = 'O';
        }
        else
        {
            // Even number selected
            sels[*offsetwu] = 'E';
        }
        *offsetwu += 1;

/*        
        if (i != nselbu - 1)
        {   
            // Insert separator 
            sels[*offsetwu] = '+';
            *offsetwu += 1;
        }
        else
        {
            sels[*offsetwu] = ' ';
        }
*/
        if (bettypebu != BETTYP_PWB)
        {
            if (i != nselbu - 1)
            {
                // Insert separator
                sels[*offsetwu] = '+';
                *offsetwu += 1;
            }
            else
            {
                sels[*offsetwu] = ' ';
            }
        }   
        else
        {
            if (i == nselbu - 2)
            {
                // Insert separator
                sels[*offsetwu] = '#';
                *offsetwu += 1;
            }
            else if (i == nselbu - 1)
            {
                sels[*offsetwu] = ' ';
            }
            else
            {
                // Insert separator
                sels[*offsetwu] = '+';
                *offsetwu += 1;
            }
        }
    }    
}

void DeSelMap::fmtMk6Sln ( const unsigned short pwbbasenumwu, // gbl base no.
                 const bool lott, // true if lottery select
                 const unsigned char mapbu[8], // lottery bitmap
                 unsigned short *offsetwu, // position offset
                 char betb[]) // selections

{   
    // Temporary variables
    int i = 0;
    int j = 0;
    char tempb[3] = "";
    const char inmaskb[] = "999";            // Mask
    unsigned char bitmapbu = 0;    
    unsigned short lotnumwu = 0;            // Actual lottery number in binary 

    if (lott == true)
    {
        // Single entry
        // Obtain selection number from bitmap then convert to ascii 
        // and placed in result array
        for (i = 0; i < BET_LOT_MAXSMAP; i++)
        {
            bitmapbu = mapbu[i];
            j = 0;
        
            while (bitmapbu)
            {
                if (bitmapbu & 0x01)
                {
                    if (pwbbasenumwu != 0)
                        // Get actual lottery number
                        lotnumwu = i * 8 + j + pwbbasenumwu;
                    else
                        // Get actual lottery number 
                        lotnumwu = i * 8 + j;
               
                    // Insert the number into ascii bet line
                    editD(tempb, inmaskb, (LONGLONG)lotnumwu);
                
                    if (lotnumwu < 10)
                    {
                        // Single digit result
                        betb[*offsetwu] = tempb[2];
                        *offsetwu += 1;
                    }
                    else if (lotnumwu >= 10 && lotnumwu <= 99)
                    {
                        // Two-digit result
                        betb[*offsetwu] = tempb[1];
                        *offsetwu += 1;
                        betb[*offsetwu] = tempb[2];
                        *offsetwu += 1;
                    }
                    else
                    {
                        // Three-digit result
                        betb[*offsetwu] = tempb[0];
                        *offsetwu += 1;
                        betb[*offsetwu] = tempb[1];
                        *offsetwu += 1;
                        betb[*offsetwu] = tempb[2];
                        *offsetwu += 1;
                    }

                    // Insert separator '+'
                    betb[*offsetwu] = BET_NUMSEP_C;
                    *offsetwu += 1;
                }                       

                bitmapbu >>= 1;
                j++;
            }
        } 
    }
    else
    {
        // Multi-entry
        // Selection values are binary, not bitmap
        for (i = 0; i < BET_LOT_MAXSEL; i++)
        {
            // Insert the number into ascii bet line
            editD(tempb, inmaskb, (LONGLONG)mapbu[i]);
                
            if (mapbu[i] < 10)
            {
                // Single digit result
                betb[*offsetwu] = tempb[2];
                *offsetwu += 1;
            }
            else if (mapbu[i] >= 10 && mapbu[i] <= 99)
            {
                // Two-digit result
                betb[*offsetwu] = tempb[1];
                *offsetwu += 1;
                betb[*offsetwu] = tempb[2];
                *offsetwu += 1;
            }

            // Insert separator '+'
            betb[*offsetwu] = BET_NUMSEP_C;
            *offsetwu += 1;
        } 
    }
        
    // Last number separator sign not required
    *offsetwu -= 1;
	betb[*offsetwu] = ' ';  
}

void DeSelMap::ltrimzero(char * instrs) // input amount string
{
    unsigned short iwu=0;

    if (instrs[0] == '$')
    {
        for (iwu=1; iwu<strlen(instrs); iwu++)
        {
            // get 1st non-zero character
            if (instrs[iwu] != '0' && instrs[iwu] != ',') 
                break;
        }
        strcpy(instrs+1, instrs+iwu);
    }
}

void DeSelMap::fmtbet_ccg ( const unsigned char bettypebu,       // bet type
                  const unsigned char gamebu,       // Subgame type
                  const unsigned char mapbu[],      // Subgame map    
                  unsigned short *offsetwu,  // Offset
                  char sels[]) // selections
{
    int i = 0;                          // Temporary variable
    int j = 0;
    int gamenuml = 0;   
    int maxmapl = 0;   
    
    char tempb[2] = "";
    const char inmaskb[] = "99";                     
    unsigned char ccgmapbu;
	unsigned char ccgamenamebu[BETTYP_AON_MAX+2][4]
    = {"NOR","MT3", "EOC", "MHG", "EXN", "OUG", "GBN"};

    // Format ccgame name
    if (bettypebu == BETTYP_PWB && gamebu == LOT_GAME_EXN)
    {
        for (i = 0; i < sizeof(ccgamenamebu[1]) - 1; i++)
        {
            sels[*offsetwu] = ccgamenamebu[BETTYP_AON_MAX+1][i];
            *offsetwu += 1;
        }
    }
    else
    {
        for (i = 0; i < sizeof(ccgamenamebu[1]) - 1; i++)
        {
            sels[*offsetwu] = ccgamenamebu[gamebu][i];
            *offsetwu += 1;
        }
    }
    
    // Format ccgame subgame type
    sels[*offsetwu] = '-';
    *offsetwu += 1;

    if (gamebu == LOT_GAME_OEG)
    {
        maxmapl = 1;
    }
    else
    {
        maxmapl = BET_LOT_MAXSMAP;
    }
    
    for (i = 0; i < maxmapl; i++)
    {
        j = 0;
        ccgmapbu = mapbu[i];

        while (ccgmapbu)
        {
            if (ccgmapbu & 0x01)
            {
                gamenuml = i * 8 + j;
                
                // Insert the number into ascii bet line
                editD(tempb, inmaskb, (LONGLONG)gamenuml);
                
                if (gamenuml < 10)
                {
                    // Single digit result
                    sels[*offsetwu] = tempb[1];
                    *offsetwu += 1;
                }
                else if (gamenuml >= 10 && gamenuml <= 99)
                {
                    // Two-digit result
                    sels[*offsetwu] = tempb[0];
                    *offsetwu += 1;
                    sels[*offsetwu] = tempb[1];
                    *offsetwu += 1;
                }     

                sels[*offsetwu] = '-';
                *offsetwu += 1;                               
            }
            
            j += 1;
            ccgmapbu >>= 1;
        }
    }

    // No separator at the end
    sels[*offsetwu - 1] = ' ';    
} 


bool DeSelMap::editD( char *outstrs, const char *inmasks, const LONGLONG valued )
{
    bool            negt        = (valued < 0);     // Negative value ?
    LONGLONG        vald        = valued;
    unsigned short  digcntwu    = 0;                // No. of decimal
    short           masklenw    = strlen(inmasks);  // length of inmasks
    char            cvtstrs[32] = "";               // Converted decimal

    // ensure that the mask is not too long
    // if it is, fill the target with '-' and return error code
    // otherwise, make a local copy of the mask
    if (masklenw > 30) return  (editBadOutput(outstrs, masklenw));

    // Loop through each character and count the number of possible spaces
    // that we can stuff a digit into
    while (*inmasks)
        switch (*(inmasks++))
        {
        case '9':
        case 'Z':
        case '(':
        case '$':
        case '+':
        case '-':
            digcntwu++;     // Increment digit room
            break;
        default :;
        }
    inmasks -= masklenw;    // point back to first element of inmasks

    if (negt) vald = -vald;     // Negate value
 //   if (OSI_SUCCEEDED(osi_cvt_l_ti((unsigned int*) &vald, cvtstrs, digcntwu, sizeof(longlong))))
         return  (editNL(outstrs, inmasks, cvtstrs, negt));
//    else return  (editBadOutput(outstrs, masklenw));
}

bool DeSelMap::editNL( /* [out] */  char        *outstrs,
             /* [in ] */  const char  *inmasks,
             /* [in ] */  const char  *incvtstrs,
             /* [in ] */  const bool   negt )
{
    char        masks[32]   = "";
    short       masklenw    = strlen(inmasks);
    char        dollarb     = 0;        // Dollar substitution symbol
    short       i,  j       = 0;
    bool        leadsignt   = false;    // Leading sign required flag
    bool        leaddollart = false;    // Loading dollar/quote required flag
    bool        signsubt    = false;    // Sign substituted flag
    bool        dollarsubt  = false;    // Dollar substituted flag
    bool        significant = false;    // Comma is not signicant

    strcpy(masks, inmasks);
    memset(outstrs, 0, masklenw + 1);

    // Stuff digits/sign into position
    // Remove leading comma and pad significant zero(s)
    for (i = 0, j = 0;  i < masklenw;  i++)
        switch (masks[i])
        {
        case 'S':
            outstrs[i] = negt ? '-' : ' ';
            signsubt   = true;
            break;
        case 'X':
            outstrs[i] = negt ? '-' : '+';
            signsubt   = true;
            break;
        case '+':
        case '-':
            if (incvtstrs[j] > '0')
            {
                outstrs[i]  = incvtstrs[j];
                significant = true;
            }
            else outstrs[i] = significant ? '0' : ' ';
            leadsignt = true;
            j++;
            break;
        case '$':
        case '(':
            leaddollart = true;
            dollarb     = masks[i];
        case 'Z':
            if (incvtstrs[j] > '0')
            {
                outstrs[i]  = incvtstrs[j];
                significant = true;
            }
            else outstrs[i] = significant ? '0' : ' ';
            j++;
            break;
        case '9':
            outstrs[i]  = incvtstrs[j++];
            significant = true;
            break;
        case ',':
            outstrs[i] = significant ? ',' : ' ';
            break;
        default:  // mask is not a formatting char so
                  // it is directly put into result
            outstrs[i] = masks[i];
            break;
        }

    // if a leading dollar or quote sign is required, scan the result until
    // it can be floated up to the significant digit
    if (leaddollart)
    {
        for (i = masklenw;  i--;)
        {
            if (outstrs[i] == ' ')
                switch (masks[i])
                {
                case ',':
                    if ( (i != 0) &&  // check previous mask character
                         ((masks[i-1] != '$') && (masks[i-1] != '(')) ) break;
                    masks[i] = dollarb;
                    // Fall through
                case '$':
                case '(':
                    outstrs[i] = dollarb;
                    dollarsubt = true;
                }
            if (dollarsubt) break;  // break out of for loop
        }

        // string substitution was not done, put '-' through the
        // resultant string and return an error
        if (!dollarsubt) return  (editBadOutput(outstrs, masklenw));
    }

    // if the sign subtituion has been done or there is no need for one,
    // the conversion is complete
    if ( signsubt || (!negt && !leadsignt) ) return  (true);

    for (i = masklenw;  i--;)
    {
        if (outstrs[i] == ' ')
            switch (masks[i])
            {
            case ',':
                if ( (i==0) ||
                     ((masks[i-1] != '+') && (masks[i-1] != '-')) )  // error
                    return  (editBadOutput(outstrs, masklenw));
                masks[i] = masks[i-1];  // mask update
                // Fall through
            case '+':
            case '-':
                if (negt) outstrs[i] = '-';
                else      outstrs[i] = (masks[i] == '+') ? '+' : ' ';
                signsubt = true;
                break;
            }
        if (signsubt) break;  // break out of for loop
    }

    // if is -ve value and sign substitution has not been done
    if (negt && !signsubt) return  (editBadOutput(outstrs, masklenw));
    return  (true);
}

bool DeSelMap::editBadOutput( /* [out] */  char         *outstrs,
                    /* [in ] */  const short   lenw )
{
    memset(outstrs, '-', lenw);
    outstrs[lenw] = '\0';
    return  (false);
}

unsigned short DeSelMap::stdExoBetType2LegCnt(const unsigned char  bet_typebu )
{
    unsigned char  pool_typebu[RDS_MAXPOOL]; // = {UCHAR_MAX};
    unsigned char  pool_cntbu               = 0;
    
    pool_cntbu = bet2PoolType(bet_typebu, pool_typebu);

    return  (pool_cntbu); //((pool_cntbu == 0) ? 0 : poldat[pool_typebu[0]].nlegwu);
}

unsigned char DeSelMap::bet2PoolType( /* [in ] */  const unsigned char  bet_typebu,
                            /* [out] */  unsigned char        pool_typebu[] )
{
    // Default 1 to 1 mapping from bet to pool type
    unsigned char  pool_cntbu = 1;
    unsigned char  local_poltypbu[RDS_MAXPOOL] = {0};  // Pool type of bet

    switch (bet_typebu)
    {
    case BETTYP_AWN   :
    case BETTYP_WIN   :  local_poltypbu[0] = RDS_POOL_WIN;  break;
    case BETTYP_APL   :
    case BETTYP_PLA   :  local_poltypbu[0] = RDS_POOL_PLA;  break;
    case BETTYP_AQN   :
    case BETTYP_QIN   :  local_poltypbu[0] = RDS_POOL_QIN;  break;
    case BETTYP_AQP   :
    case BETTYP_QPL   :  local_poltypbu[0] = RDS_POOL_QPL;  break;
    case BETTYP_DBL   :  local_poltypbu[0] = RDS_POOL_DBL;  break;
    case BETTYP_ATC   :
    case BETTYP_TCE   :  local_poltypbu[0] = RDS_POOL_TCE;  break;
    case BETTYP_AQT   :
    case BETTYP_QTT   :  local_poltypbu[0] = RDS_POOL_QTT;  break;
    case BETTYP_DQN   :  local_poltypbu[0] = RDS_POOL_DQN;  break;
    case BETTYP_TBL   :  local_poltypbu[0] = RDS_POOL_TBL;  break;
    case BETTYP_TTR   :  local_poltypbu[0] = RDS_POOL_TTR;  break;
    case BETTYP_6UP   :  local_poltypbu[0] = RDS_POOL_6UP;  break;
    case BETTYP_DTR   :  local_poltypbu[0] = RDS_POOL_DTR;  break;
    case BETTYP_ATR   :
    case BETTYP_TRIO  :  local_poltypbu[0] = RDS_POOL_TRI;  break;
    case BETTYP_AWP   :
    case BETTYP_WINPLA:  pool_cntbu = 2;
                         local_poltypbu[0] = RDS_POOL_WIN;
                         local_poltypbu[1] = RDS_POOL_PLA;  break;
    case BETTYP_AQQP  :
    case BETTYP_QINQPL:  pool_cntbu = 2;
                         local_poltypbu[0] = RDS_POOL_QIN;
                         local_poltypbu[1] = RDS_POOL_QPL;  break;
    default           :  pool_cntbu = 0;                    break;
    }

    // Return result
    if (pool_typebu) memcpy(pool_typebu, local_poltypbu,
                            sizeof(unsigned char) * pool_cntbu);
    return  (pool_cntbu);
}

char* DeSelMap::osi_atrim( /* [in|out] */  char  *strs )
{
    return  (osi_ltrim(osi_rtrim(strs)));
}


char* DeSelMap::osi_ltrim( /* [in|out] */  char  *strs )
{
    char  *ps = strs;

    // Check valid pointer
    if (!ps) return  (ps);

    // Find 1st non-space character
    while (isspace(*ps)) ps++;

    // Shift memory to remove spaces
    if (strs != ps) memmove(strs, ps, strlen(ps) + 1);
    return  (strs);
}

char* DeSelMap::osi_rtrim( /* [in|out] */  char  *strs )
{
    char  *ps = 0;

    // Check valid pointer
    if (!strs) return  (strs);
    else ps = strs + strlen(strs) - 1;  // Index last character

    // Ignore right spaces util a non-space character found
    while ((ps >= strs) && isspace(*ps)) ps--;

    // Terminate string with null character
    *(++ps) = '\0';
    return  (strs);
}

void DeSelMap::BtoHex(unsigned char *cpSrc, int iSize, char *cpDest) const
{
	int j=0;
	for(int i=0;i<iSize;i++, j+=2)
	{
		sprintf(&cpDest[j], "%02X", cpSrc[i]);
	}
}

char* DeSelMap::getForm(unsigned char index, char legs[5])
{
	char m_cFormulaList[41][5];

	sprintf(m_cFormulaList[0], "2x1");
	sprintf(m_cFormulaList[1], "2x3");
	sprintf(m_cFormulaList[2], "3x1");
	sprintf(m_cFormulaList[3], "3x3");
	sprintf(m_cFormulaList[4], "3x4");
	sprintf(m_cFormulaList[5], "3x6");
	sprintf(m_cFormulaList[6], "3x7");
	sprintf(m_cFormulaList[7], "4x1");
	sprintf(m_cFormulaList[8], "4x4");
	sprintf(m_cFormulaList[9], "4x5");
	sprintf(m_cFormulaList[10], "4x6");
	sprintf(m_cFormulaList[11], "4x10");
	sprintf(m_cFormulaList[12], "4x11");
	sprintf(m_cFormulaList[13], "4x14");
	sprintf(m_cFormulaList[14], "4x15");
	sprintf(m_cFormulaList[15], "5x1");
	sprintf(m_cFormulaList[16], "5x5");
	sprintf(m_cFormulaList[17], "5x6");
	sprintf(m_cFormulaList[18], "5x10");
	sprintf(m_cFormulaList[19], "5x15");
	sprintf(m_cFormulaList[20], "5x16");
	sprintf(m_cFormulaList[21], "5x20");
	sprintf(m_cFormulaList[22], "5x25");
	sprintf(m_cFormulaList[23], "5x26");
	sprintf(m_cFormulaList[24], "5x30");
	sprintf(m_cFormulaList[25], "5x31");
	sprintf(m_cFormulaList[26], "6x1");
	sprintf(m_cFormulaList[27], "6x6");
	sprintf(m_cFormulaList[28], "6x7");
	sprintf(m_cFormulaList[29], "6x15");
	sprintf(m_cFormulaList[30], "6x20");
	sprintf(m_cFormulaList[31], "6x21");
	sprintf(m_cFormulaList[32], "6x22");
	sprintf(m_cFormulaList[33], "6x35");
	sprintf(m_cFormulaList[34], "6x41");
	sprintf(m_cFormulaList[35], "6x42");
	sprintf(m_cFormulaList[36], "6x50");
	sprintf(m_cFormulaList[37], "6x56");
	sprintf(m_cFormulaList[38], "6x57");
	sprintf(m_cFormulaList[39], "6x62");
	sprintf(m_cFormulaList[40], "6x63");	

	strcpy(legs, m_cFormulaList[index]);
	return (legs);
}

