/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                  
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: ual_route_handler.c,v 9.8 2008/06/29 15:17:44 skatta Exp $
 *
 *  LOG: $Log: ual_route_handler.c,v $
 *  LOG: Revision 9.8  2008/06/29 15:17:44  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.7  2008/05/25 17:11:25  kramesh
 *  LOG: Whizible Bug ID 932. Incorrect Routing Key printing.
 *  LOG:
 *  LOG: Revision 9.6  2005/11/30 23:50:49  clin
 *  LOG: change ITS_TRACE to UAL trace.
 *  LOG:
 *  LOG: Revision 9.5  2005/07/04 04:09:27  randresol
 *  LOG: In AddLink, add a case for the LOAD_SHARE Mode
 *  LOG:
 *  LOG: Revision 9.4  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.3  2005/05/05 06:00:11  adutta
 *  LOG: Fix for #1769
 *  LOG:
 *  LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 *  LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:49  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:19  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.2.7.18.1  2004/12/15 13:15:37  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.2.2.7  2003/09/11 00:45:08  lbana
 *  LOG: Code reorganized for Pause/Resumes and test config with 2 linksets.
 *  LOG:
 *  LOG: Revision 7.2.2.6  2003/09/10 18:16:52  hcho
 *  LOG: remove warnings and bug fix for trans indicator
 *  LOG:
 *  LOG: Revision 7.2.2.5  2003/09/09 20:19:21  lbana
 *  LOG: bug fix on sg side for pause/resume
 *  LOG:
 *  LOG: Revision 7.2.2.4  2003/09/08 19:32:48  lbana
 *  LOG: Added callback info for pause/resume when transport goes Up/Down
 *  LOG:
 *  LOG: Revision 7.2.2.3  2003/08/04 23:17:34  hcho
 *  LOG: fixes in DUNA/DAVA and propagate CANT_START indication to the user.
 *  LOG:
 *  LOG: Revision 7.2.2.2  2003/07/11 21:14:04  labuser
 *  LOG: DUNA/DAVA functionality is added.
 *  LOG:
 *  LOG: Revision 7.2.2.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.2  2002/12/30 17:28:48  lbana
 *  LOG: Propagating bug fixes in PR6.1 to current
 *  LOG:
 *  LOG: Revision 7.1.2.1  2002/12/26 23:32:27  lbana
 *  LOG: buge fixes in ual in IPSP mode testing
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.10  2002/07/22 18:42:06  lbana
 *  LOG: format.
 *  LOG:
 *  LOG: Revision 6.9  2002/07/18 18:25:28  lbana
 *  LOG: add family in AS Context to avoid sequency dependancy in xml file
 *  LOG:
 *  LOG: Revision 6.8  2002/07/12 14:51:37  lbana
 *  LOG: get family from asInfo in RK_Context
 *  LOG:
 *  LOG: Revision 6.7  2002/07/10 13:29:13  lbana
 *  LOG: removed all warnings
 *  LOG:
 *  LOG: Revision 6.6  2002/06/12 19:20:17  lbana
 *  LOG: Put in changes after Henry's comments.
 *  LOG:
 *  LOG: Revision 6.5  2002/05/21 22:13:13  lbana
 *  LOG: more debugging in current
 *  LOG:
 *  LOG: Revision 6.4  2002/05/17 20:22:06  lbana
 *  LOG: More testing on current.
 *  LOG:
 *  LOG: Revision 6.3  2002/05/15 16:19:05  lbana
 *  LOG: Add localPC parsing of the resource manager. Compiled the routeHandler
 *  LOG: module.
 *  LOG:
 *  LOG: Revision 6.2  2002/05/13 20:30:42  lbana
 *  LOG: uals in current starts from here...
 *  LOG:
 *  LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 *  LOG: Begin PR7.
 *  LOG:
 *  LOG: Revision 1.2  2002/01/09 22:31:48  lbana
 *  LOG: remove endofline character appended in dos
 *  LOG:
 *  LOG: Revision 1.1  2002/01/09 21:46:15  lbana
 *  LOG: Baseline for M3UA Draft Version 10 and SUA draft ver 9
 *  LOG:
 ****************************************************************************/

#include "ual_intern.h"
#include <its_route_rwlock.h>
#include <its_link.h>

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   We had a LinkSet for each new AS as well as a ROUTE_Info to the 
 *   Destination table for that DPC.
 *     
 *  Input Parameters:
 *     
 *
 *  Input/Output Parameters:
 *      
 *   None.
 *
 *  Output Parameters:
 *      
 *   None.
 *
 *  Return Value:
 *      
 *   ITS_SUCCESS - in case no error occured, any other return value indicates
 *   an error condition.
 *
 *  Notes:
 *    
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference     Description
 * -----------------------------------------------------------------------------
 * gdevanand 05-03-2005  BugId:1769   changing linkSet family when 
 *                                    asEntry->family is NULL and family is ITU 
 *
 *  See Also:
 *
 ******************************************************************************/
int
UAL_AddLinkSetAndDestination(RK_Context *asEntry)
{
    int ret = ITS_EINVALIDARGS;
    SS7_LinkSet linkSet;
    ROUTE_MatchInfo rinfo;

    if (asEntry->isMember)
    {
        return ITS_SUCCESS;
    }

    /*
     * Creating the LinkSet for new AS
     */
    memset(&linkSet, 0, sizeof(SS7_LinkSet));

    linkSet.adjacent = asEntry->asInfo.dpc;
    linkSet.lpc      = UAL_GL_LOCAL_PC;
    linkSet.maxLinks = 0;
    linkSet.adjSTP   = ITS_FALSE;
    linkSet.isC      = ITS_FALSE;   /* not sure which one to set to true */ 
    linkSet.is5Bit   = ITS_TRUE;    /* let's set that one to true */
    linkSet.ni       = asEntry->na.na;
    linkSet.isUp     = ITS_FALSE;       /* initally there is no link */
    
    linkSet.linkSet = 0x00;

    linkSet.family = asEntry->asInfo.family;

    /*
     * I think we can do that since the AddLinkSet function checks for
     * duplicates. I am afraid this will cause a lot of error trace event
     * though it is not an error.
     */
    while ((ret == ITS_EINVALIDARGS) && (linkSet.linkSet <= 255))
    {
        linkSet.linkSet++;

        ret = LINKSET_AddLinkSet(&linkSet);

    }

    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error adding New LinkSet for AS %u\n.", asEntry->rCtxt));

        return ITS_ENOMEM;
    }

    asEntry->linkSet = linkSet.linkSet;

    /* 
     * now create the Destination 
     */
    memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));

    rinfo.basic      = asEntry->asInfo;
    rinfo.basic.type = REMOTE_ROUTE;
    rinfo.linkSet    = asEntry->linkSet;
    rinfo.priority   = 0;
    rinfo.rkey       = asEntry->rCtxt;

    ret = ROUTE_AddRouteContextInfo(&rinfo);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error adding RouteContextInfo for AS %u\n.", 
                         asEntry->rCtxt));
    }

    /* create remote route for ssn 1 */
    memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));
 
    rinfo.basic              = asEntry->asInfo;
    rinfo.basic.criteria.ssn = 1;
    rinfo.basic.type         = REMOTE_ROUTE;
    rinfo.linkSet            = asEntry->linkSet;
    rinfo.priority           = 0;
 
    ret = ROUTE_AddRouteContextInfo(&rinfo);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error adding route for SSN 1."));
    }

    return ret;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *
 *  Input/Output Parameters:
 *
 *    None.
 *
 *  Output Parameters:
 *
 *    None.
 *
 *  Return Value:
 *
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Function added for proper handling
 *                                       of Link Removal at SG, when ASP goes  
 *                                       down. 
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_INT
UAL_RemLink(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_INT     ret = ITS_SUCCESS;
    SS7_LinkPtr lp;

    UAL_WARNING(("UAL_RemLink: linkset %d link %d \n",
                        linkSet , linkCode));

    LINK_LockTables();

    lp = LINK_FindLinkNoLock(linkSet, linkCode);

    if (lp)
    {
        lp->refCount--;

        if (lp->refCount > 0)
        {
            LINK_RemLinkInfoFromTransport(lp);

            LINK_CommitLinkNoLock(lp);
        }
        else if (lp->refCount == 0)
        {
            ret = LINK_RemLink(linkSet, lp);

            if (ret != ITS_SUCCESS)
            {
                UAL_ERROR(("UAL_RemLink: Error in removing link %d "
                           "from ls = %d\n", lp->linkCode, linkSet));
            }
        }
    }

    LINK_UnlockTables();

    return ret;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *
 *  Input/Output Parameters:
 *
 *    None.
 *
 *  Output Parameters:
 *
 *    None.
 *
 *  Return Value:
 *
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Function added for proper handling
 *                                       of Adding Link at SG, when ASP   
 *                                       is connected.
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_INT
UAL_AddLink(RK_Context *rk_context, RKListNode *rkNode, TRANSPORT_Control *trCtrl)
{
    ITS_INT        ret = ITS_SUCCESS;
    SS7_Link       *lp = NULL, link;
    ITS_INT        count = 0;
    SS7_LinkSetPtr lsp;

    UAL_DEBUG(("UAL_AddLink: AS = %u Trid = %d\n", rk_context->rCtxt,
                      TRANSPORT_INSTANCE(trCtrl)));

    memset(&link, 0, sizeof(SS7_Link));
    lsp = LINKSET_FindLinkSet(rk_context->linkSet);

    LINK_LockTables();

    if (rk_context->trafficMode == UAL_OVERRIDE)
    {
        for (; lsp && count < lsp->numLinks; count++)
        {
            lp = LINK_FindLinkNoLock(lsp->linkSet, count);

            if (lp == NULL || (lp && lp->id == ITS_NO_SRC))
            {
                break;
            }
        }

        if (lp)  /* Someone else comitted this link */
        {
            lp->refCount++;
            memcpy(&link, lp, sizeof(SS7_Link));
            link.id = TRANSPORT_INSTANCE(trCtrl);
        }
        else
        {
            link.id       = TRANSPORT_INSTANCE(trCtrl);   /* Set trid for this link */
            link.linkCode = count;

            link.family     = rk_context->asInfo.family;
            link.initActive = ITS_FALSE;
            link.termFixed  = ITS_FALSE;
            link.isSAAL     = ITS_FALSE;
            link.isAllowed  = ITS_TRUE;
            link.isUp       = ITS_TRUE;

            link.refCount++;
        }
    }
    else if(rk_context->trafficMode == UAL_LOADSHARE)
    {
       
        for (; lsp && count < lsp->numLinks; count++)
        {
            lp = LINK_FindLinkNoLock(lsp->linkSet, count);

            if (lp == NULL || (lp && lp->id == ITS_NO_SRC) || lp->id == TRANSPORT_INSTANCE(trCtrl))
            {
                break;
            }
        }

        if (lp && lp->id == TRANSPORT_INSTANCE(trCtrl))  /* Someone else comitted this link */
        {
            lp->refCount++;
            memcpy(&link, lp, sizeof(SS7_Link));
            link.id = TRANSPORT_INSTANCE(trCtrl);
        }
        else
        {
            link.id       = TRANSPORT_INSTANCE(trCtrl);   /* Set trid for this link */
            link.linkCode = count;

            link.family     = rk_context->asInfo.family;

            link.initActive = ITS_FALSE;
            link.termFixed  = ITS_FALSE;
            link.isSAAL     = ITS_FALSE;
            link.isAllowed  = ITS_TRUE;
            link.isUp       = ITS_TRUE;

            link.refCount++;
        }


    }
 
    ret = LINK_AddLink(lsp->linkSet, &link);

    if (ret == ITS_SUCCESS || ret == ITS_EDUPLENTRY)
    {

        lp = NULL;
        lp = LINK_FindLinkNoLock(rk_context->linkSet,
                                 link.linkCode);

        if(lp != NULL)
        {
            if (rkNode)
            {
                /* put the linkCode in RKListNode */
                rkNode->linkCode = lp->linkCode;
            }
            LINK_AddLinkInfoToTransport(trCtrl, lp);

            if (!UAL_TRANSPORT_PENDING(trCtrl))
            {
                TRANSPORT_SetState(trCtrl, ITS_TRUE);
                LINK_SetLinkState(lp, ITS_TRUE);
            }
            else
            {
                LINK_SetLinkState(lp, ITS_TRUE);
            }

            UAL_DEBUG(("UAL_AddLink: Added link %02x to"
                             "the linkSet %02x for transport id %d\n",
                             lp->linkCode, lsp->linkSet, lp->id));
        }
        else
        {
            UAL_ERROR(("UAL_AddLink: FindLink returns NULL\n"));
        }
    }
    else
    {
        UAL_ERROR(("UAL_AddLink: Error adding linkCode"
                         " %d to the linkset %d for the "
                         "transport id %d\n",  link.linkCode,
                         lsp->linkSet, link.id));
    }

    LINK_UnlockTables();

    return ret;
}
