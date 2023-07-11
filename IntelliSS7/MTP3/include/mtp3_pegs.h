/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: 
 *
 * LOG: $Log: mtp3_pegs.h,v $
 * LOG: Revision 9.4.10.1  2010/06/21 10:16:36  chandrashekharbs
 * LOG: Compilation error at OAM resolved
 * LOG:
 * LOG: Revision 9.4  2008/06/04 06:34:53  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.3  2007/01/10 11:15:01  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.2  2005/05/06 05:31:43  adutta
 * LOG: MTP route pegs declaration
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1.6.1  2005/01/31 11:35:27  snagesh
 * LOG: Peg structures modified
 * LOG:
 * LOG: Revision 1.1.4.1  2004/08/10 12:28:43  kannanp
 * LOG: Create Public Interface for MTP3 Pegs - propagated from TCS.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_MTP3_PEGS_H_
#define _ITS_MTP3_PEGS_H_
#include <its_link.h>
#ident "$Id: mtp3_pegs.h,v 9.4.10.1 2010/06/21 10:16:36 chandrashekharbs Exp $"

/*
 *  MTP3 Peg Public interface
 *
 */

#define DURATION_OM_TICK 10 /* Duration OMs are pegged for every 10 seconds */

typedef struct
{
    ITS_UINT msgPause;
    ITS_UINT msgResume;
    ITS_UINT msgStatus;
    ITS_UINT initialize;
    ITS_UINT terminate;
    ITS_UINT msgReceivedInError;
    ITS_UINT changeover;
    ITS_UINT changeback;
    ITS_UINT slUnavailable;
    ITS_UINT linkInhibit;
    ITS_UINT linkUnInhibit;
    ITS_UINT linkforceUninhibit;
    ITS_UINT congestion;
    ITS_UINT slsUnavailable;
    ITS_UINT tfcReceived;
    ITS_UINT tfaReceived;
    ITS_UINT routesetUnavailable;
    ITS_UINT adjacentSpUnaccesible;
    ITS_UINT userpartEnable;
    ITS_UINT userpartDisable;
}
MTP3_GenPegs;

typedef struct
{
    ITS_UINT cooTx;
    ITS_UINT cooRx;
    ITS_UINT coaTx;
    ITS_UINT coaRx;
    ITS_UINT ecoTx;
    ITS_UINT ecoRx;
    ITS_UINT ecaTx;
    ITS_UINT ecaRx;
    ITS_UINT cbdTx;
    ITS_UINT cbdRx;
    ITS_UINT cbaTx;
    ITS_UINT cbaRx;
    ITS_UINT linTx;
    ITS_UINT linRx;
    ITS_UINT liaTx;
    ITS_UINT liaRx;
    ITS_UINT lunTx;
    ITS_UINT lunRx;
    ITS_UINT luaTx;
    ITS_UINT luaRx;
    ITS_UINT lidTx;
    ITS_UINT lidRx;
    ITS_UINT lfuTx;
    ITS_UINT lfuRx;
    ITS_UINT lliTx;
    ITS_UINT lliRx;
    ITS_UINT lriTx;
    ITS_UINT lriRx;
    ITS_UINT dlcTx;
    ITS_UINT dlcRx;
    ITS_UINT cssTx;
    ITS_UINT cssRx;
    ITS_UINT cnsTx;
    ITS_UINT cnsRx;
    ITS_UINT cnpTx;
    ITS_UINT cnpRx;
    ITS_UINT upuTx;
    ITS_UINT upuRx;
    ITS_UINT sltmTx;
    ITS_UINT sltmRx;
    ITS_UINT sltaTx;
    ITS_UINT sltaRx;
}
MTP3_LinkPegs;

typedef struct
{
    ITS_UINT tfaTx;
    ITS_UINT tfaRx;
    ITS_UINT tfpTx;
    ITS_UINT tfpRx;
    ITS_UINT rstTx;
    ITS_UINT rstRx;
    ITS_UINT tfrRx;
    ITS_UINT tfcTx;
    ITS_UINT tfcRx;
    ITS_UINT sifTx;
}
MTP3_RoutePegs;
 

#define TOTAL_MTP_LINKS (MAX_LINKSETS * MAX_LINKS_PER_LINKSET)
#define MAX_ADJACENT_SP 100  /* This is a limitation... Need to take care of it */

/* Active/Inactive OM Buffer structure */

typedef struct
{
  ITS_OCTET activeOm;
  ITS_OCTET inactiveOm;
} 
mtp3OmBuffer;
 
/* MTP3 Link Statistics Structure */

typedef struct
{
  ITS_OCTET linkset;                   /* Linkset ID */
  ITS_OCTET linkcode;                  /* Link ID */
  ITS_UINT slInsDuration;              /* Link Inservice Duration */
  ITS_UINT slUnavailDuration;          /* Link unavailable Duration */
  ITS_UINT slLocalInhibitDuration;     /* Link Local Inhibit Duration */ 
  ITS_UINT slRemoteInhibitDuration;    /* Link Remote Inhibit Duration */
  ITS_UINT slRPODuration;              /* Link RPO Duration */
  ITS_UINT slCumulativeCongDuration;   /* Link Cumulative Congestion Duration */
  ITS_UINT slRestoration;              /* Link Restoration */
  ITS_UINT l1CongCount;                /* Link Level 1 Congestion Count */
  ITS_UINT l2CongCount;                /* Link Level 2 Congestion Count */
  ITS_UINT l3CongCount;                /* Link Level 3 Congestion Count */
  ITS_UINT msuDiscardRoutingError;     /* MSU discarded due to Routing Data Error Count */
  ITS_UINT msuDiscardCongestion;       /* Priority 0/1/2 MSUs discarded due to Congestion */
  ITS_UINT changeover;                 /* Local Automatic Changeover */
  ITS_UINT changeback;                 /* Local Automatic Changeback */
  ITS_UINT localLinkInhibit;           /* Link Inhibition by local management */
  ITS_UINT localLinkUninhibit;         /* Link Uninhibition by local management */
  ITS_UINT tfcReceived;                /* # of TFCs Received */
  ITS_UINT upuTx;                      /* # of UPUs Transmitted */ 
  ITS_UINT upuRx;                      /* # of UPUs Received */
  /*new additions*/
  ITS_UINT srtTx;                      /* # of SRTs Transmitted */
  ITS_UINT srtRx;                      /* # of SRTs Recieved  */ 
  ITS_UINT sraTx;                      /* # of SRAs Transmitted */
  ITS_UINT sraRx;                      /* # of SRAs Recieved */ 
}
mtp3LinkPegs;

typedef struct
{
  mtp3LinkPegs MTP3LinkStat[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
} 
mtp3_link_stat_table;

mtp3_link_stat_table LinkOmImage[2];

typedef struct
{
  ITS_UINT count;
  mtp3LinkPegs linkStats[TOTAL_MTP_LINKS];
} mtp3LinkData;

/* MTP3 Linkset Statistics Structure */
 
typedef struct
{
  ITS_OCTET linkset;                   /* Linkset ID */
  ITS_UINT linksetUnavailDuration;     /* Linkset unavailable duration */
  ITS_UINT tfaTx;                      /* # of TFAs Transmitted */ 
  ITS_UINT tfpTx;                      /* # of TFPs Transmitted */ 
}
mtp3LinksetPegs;

typedef struct
{
  mtp3LinksetPegs MTP3LinkSetStat[MAX_LINKSETS];
}
mtp3_linkset_stat_table;

mtp3_linkset_stat_table LinkSetOmImage[2];

typedef struct
{
  ITS_UINT count;
  mtp3LinksetPegs linksetStats[MAX_LINKSETS];
} mtp3LinkSetData;

/* MTP3 Adjacent SP Statistics Structure */
 
struct ADJ_SP
{
  ITS_UINT adjSPInaccess;
  ITS_UINT adjSPInaccDuration;
  ITS_UINT timeStamp;
};

typedef struct
{
  ITS_UINT adjSp;
  ITS_UINT adjSPInaccess;
  ITS_UINT adjSPInaccDuration;
} mtp3AdjSp;

typedef struct
{
  ITS_UINT count;
  mtp3AdjSp adjSpStats[MAX_ADJACENT_SP];
} mtp3SpData;
 
struct adj_sp_node
{
  struct adj_sp_node *prev;
  ITS_UINT adj_sig_point;
  ITS_BOOLEAN adjSpInaccFlag;
  struct ADJ_SP SpImage[2];
  struct adj_sp_node *next;
};

/* Structure shared with OAM */

typedef struct
{
  SS7_Family   family;
  mtp3LinkData lnStats; 
  mtp3LinkSetData lkStats;
  mtp3SpData spStats;
} mtp3Om;


#ifdef __cplusplus
extern "C"
{
#endif


ITSSS7DLLAPI int MTP3_GetAllGeneralPegs(MTP3_GenPegs *genPegs);

ITSSS7DLLAPI int MTP3_ClearAllGeneralPegs();

ITSSS7DLLAPI int MTP3_CleaGeneralPeg( ITS_UINT pegId);

ITSSS7DLLAPI int MTP3_GetAllLinkPegs(ITS_USHORT linkSet,
                                     ITS_USHORT linkId,
                                     MTP3_LinkPegs *linkPegs);

ITSSS7DLLAPI int MTP3_ClearAllLinkPegs(ITS_USHORT linkSet,
                                       ITS_USHORT linkCode);

ITSSS7DLLAPI int MTP3_ClearLinkPeg(ITS_USHORT linkSet,
                                   ITS_USHORT linkCode,
                                   ITS_UINT pegId);

#ifdef __cplusplus
}
#endif


#endif /*_ITS_MTP3_PEGS_H_*/
