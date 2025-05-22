// #include ".\..\BetTypeDef.h"

#define SB_POOL_HAD     0	// 
#define SB_POOL_HDC     1	// handicap
#define SB_POOL_CRS     2	// correct score
#define SB_POOL_HFT     3	// half full
#define SB_POOL_TTG     4
#define SB_POOL_HILO     5	
#define SB_POOL_OOE      6	// odd even
#define SB_POOL_FGS      7	// first goal scorer
#define SB_POOL_HHAD     9  // handicap HAD
#define SB_POOL_FHAD     10  // first half HAD
#define SB_POOL_FHLO	13	// first half high low

#define SB_POOL_FCRS	14	// First Half Correct Score (2012MAR)

#define SB_POOL_CHLO	15	// Corner High Lo


#define SB_POOL_SPC_MATCH	18	// special pool (match related)
#define	SB_POOL_SPC_TRN		19	// special pool (tournament related)
#define SB_POOL_HFMP		21	// special pool (match related)
#define	SB_POOL_DHCP		22	// special pool (tournament related)

#define SB_POOL_CHP		40  // Championship
#define	SB_POOL_TOFP	41	// Champion and First Runner Up
#define	SB_POOL_ADTP	42  // Quarter Finalist
#define	SB_POOL_GPF		43  // Group Forcast
#define SB_POOL_GPW		44	// Group Winner
#define SB_POOL_TPS		45	// Top Scorer/Team

char* GetRcBetType(char m_cType, char Type[10])
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

	case BETTYP_AWP:
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

char* GetFbBetType(char m_cType, char Type[10])
{
	switch (m_cType)
	{
	case SB_POOL_HAD:
		sprintf(Type, "HAD");
		break;
		
	case SB_POOL_HDC:
		sprintf(Type, "HDC");
		break;
		
	case SB_POOL_CRS:
		sprintf(Type, "CRS");
		break;

	case SB_POOL_FCRS: //2012MAR
		sprintf(Type, "FCRS"); 
		break;

	case SB_POOL_HFT:
		sprintf(Type, "HFT");
		break;

	case SB_POOL_TTG:
		sprintf(Type, "TTG");
		break;

	case SB_POOL_HILO:
		sprintf(Type, "HILO");
		break;

	case SB_POOL_FHLO:
		sprintf(Type, "FHLO");
		break;

	case SB_POOL_CHLO:
		sprintf(Type, "CHLO");
		break;

	case SB_POOL_OOE:
		sprintf(Type, "OOE");
		break;

	case SB_POOL_FGS:
		sprintf(Type, "FGS");
		break;

	case SB_POOL_HHAD:
		sprintf(Type, "HHAD");
		break;

	case SB_POOL_FHAD:
		sprintf(Type, "FHAD");
		break;

	case SB_POOL_SPC_MATCH:
		sprintf(Type, "SPC");
		break;

	case SB_POOL_SPC_TRN:
		sprintf(Type, "SPC");
		break;

	case SB_POOL_HFMP:
		sprintf(Type, "HFMP");
		break;

	case SB_POOL_DHCP:
		sprintf(Type, "DHCP");
		break;

	case SB_POOL_CHP:
		sprintf(Type, "CHP");
		break;

	case SB_POOL_TOFP:
		sprintf(Type, "TOFP");
		break;

	case SB_POOL_ADTP:
		sprintf(Type, "ADTP");
		break;

	case SB_POOL_GPF:
		sprintf(Type, "GPF");
		break;

	case SB_POOL_GPW:
		sprintf(Type, "GPW");
		break;

	case SB_POOL_TPS:
		sprintf(Type, "TPS");
		break;

	default:
		sprintf(Type, "XXXX");
		break;
	}

	return(Type);
}