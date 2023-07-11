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
 *  ID: $Id: ual_support.c,v 9.15.6.1.46.4 2015/10/27 10:16:06 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_support.c,v $
 *  LOG: Revision 9.15.6.1.46.4  2015/10/27 10:16:06  jkchaitanya
 *  LOG: changes for invalid read found at IWF shutdown time
 *  LOG:
 *  LOG: Revision 9.15.6.1.46.3  2015/04/22 04:28:56  jkchaitanya
 *  LOG: changes for bug 5392
 *  LOG:
 *  LOG: Revision 9.15.6.1.46.2  2015/03/02 10:46:46  jkchaitanya
 *  LOG: changes for printing asptbl entries in mml fix merged from stack branch
 *  LOG:
 *  LOG: Revision 9.15.6.1.46.1  2014/12/15 09:44:24  jkchaitanya
 *  LOG: changes for crash fix in mml command for asp state for bug 5392
 *  LOG:
 *  LOG: Revision 9.15.6.1  2009/03/24 04:11:29  ssodhi
 *  LOG: enable_u_astbl_cmd_on_asp_side cmd
 *  LOG:
 *  LOG: Revision 9.15  2008/06/30 14:05:50  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.14  2008/06/29 15:18:23  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.13  2008/06/20 10:39:41  mshanmugam
 *  LOG: Accelero CGI Phase I:D0170
 *  LOG:
 *  LOG: Revision 9.12  2008/05/25 17:11:25  kramesh
 *  LOG: Whizible Bug ID 932. Incorrect Routing Key printing.
 *  LOG:
 *  LOG: Revision 9.11  2008/05/01 16:18:31  kramesh
 *  LOG: Propagated Bridgeport issue 1541. Routing Key more than 255.
 *  LOG:
 *  LOG: Revision 9.10  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.9.2.9  2007/07/06 06:58:35  pspl
 *  LOG: (PSPL, abhijeet) Support added for get/set audTimer from/to XML for SCON-DAUD feature
 *  LOG:
 *  LOG: Revision 9.9.2.8  2007/06/26 08:36:49  pspl
 *  LOG: (PSPL, abhijeet) Removed the line that was added by mistake
 *  LOG:
 *  LOG: Revision 9.9.2.7  2007/06/22 11:50:36  pspl
 *  LOG: Auditing support for receipt of SSNM message (SCON/DUNA/DRST)
 *  LOG:
 *  LOG: Revision 9.9.2.6  2007/05/29 14:35:33  pspl
 *  LOG: -(PSPL,Manish) Fixed Code to check duplicate ASP Ids
 *  LOG:
 *  LOG: Revision 9.9.2.5  2007/05/25 07:21:16  pspl
 *  LOG: Fixed core dump for MML command u_astbl. (Vipul)
 *  LOG:
 *  LOG: Revision 9.9.2.4  2007/05/25 07:15:45  pspl
 *  LOG: (PSPL,Manish)
 *  LOG: - UAL_GetRoutingKeys() is changed to extract RK_Contexts instead of rKeys, and renamed
 *  LOG: - Hardcoading of UAL_OVERRIDE_MODE removed
 *  LOG: - Changed the Parameter type of SendASPActive()
 *  LOG:
 *  LOG: Revision 9.9.2.3  2007/04/26 06:58:06  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - misc trace changes
 *  LOG:
 *  LOG: Revision 9.9.2.2  2007/04/05 14:41:03  pspl
 *  LOG: UAL_IncrementMIBStats() added, and a \#define added
 *  LOG:
 *  LOG: Revision 9.9.2.1  2007/03/29 05:24:07  pspl
 *  LOG: Rahul, minor ual fixes, fix for callback not getting removed
 *  LOG:
 *  LOG: Revision 9.9  2007/01/17 09:21:32  yranade
 *  LOG: Warning removals.
 *  LOG:
 *  LOG: Revision 9.8  2005/12/09 03:50:20  clin
 *  LOG: Add SSNM pegs for M3UA.
 *  LOG:
 *  LOG: Revision 9.7  2005/12/08 03:42:56  clin
 *  LOG: fix bug #2482
 *  LOG:
 *  LOG: Revision 9.6  2005/11/30 23:52:03  clin
 *  LOG: change ITS_TRACE to UAL trace.
 *  LOG:
 *  LOG: Revision 9.5  2005/11/30 15:12:41  clin
 *  LOG: make debug flag works to display ASP/IPSP client its own routing info.
 *  LOG:
 *  LOG: Revision 9.4  2005/11/23 20:48:12  clin
 *  LOG: fix bug #2481
 *  LOG:
 *  LOG: Revision 9.3  2005/11/23 19:48:15  clin
 *  LOG: fix bug #2531
 *  LOG:
 *  LOG: Revision 9.2  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:50  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:20  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.9  2005/02/21 10:41:40  adutta
 *  LOG: Fix for Bug#1557
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.8  2005/01/24 11:57:50  snagesh
 *  LOG: Windows compilation fixes
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.7  2005/01/07 15:03:05  ssingh
 *  LOG: Changed to enhance ACTIVE-BACKUP redundancy.
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.6  2005/01/06 19:49:21  sbabu
 *  LOG: Fixed problems during testing
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.5  2005/01/06 04:39:58  snagesh
 *  LOG: Added definition of Peg Manager
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.4  2005/01/04 15:18:04  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.3  2004/12/21 12:29:49  ssingh
 *  LOG: changed defined(UAL_DEBUG) to UAL_DDEBUG
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.2  2004/12/15 16:38:08  dsatish
 *  LOG: Changes propagated from SHIM
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2.4.1  2004/12/15 13:15:37  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.2  2004/10/06 08:44:52  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.2.2.4.2.1  2004/05/03 13:00:47  ssingh
 *  LOG: Bug#787; Processing of number of Active ASPs in AS goes below
 *  LOG: minimum (n+k) in a Loadshare/Broadcast.
 *  LOG:
 *  LOG: Revision 7.2.2.4  2003/10/22 14:05:42  lbana
 *  LOG: add check for numlinks.
 *  LOG:
 *  LOG: Revision 7.2.2.3  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.2.2.2  2003/10/14 20:29:44  lbana
 *  LOG: remove begin and end tags for the fixes.
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
 *  LOG: Revision 6.13  2002/08/26 21:52:56  mmiers
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 6.12  2002/07/26 13:27:04  ngoel
 *  LOG: print alarm level as string
 *  LOG:
 *  LOG: Revision 6.11  2002/07/24 19:53:43  lbana
 *  LOG: fix bugs in reconnect logic, and get aspinfo element from parser
 *  LOG: extension.
 *  LOG:
 *  LOG: Revision 6.10  2002/07/24 13:51:48  ngoel
 *  LOG: fix route style strings
 *  LOG:
 *  LOG: Revision 6.9  2002/07/11 20:43:22  ngoel
 *  LOG: add dump cfg function
 *  LOG:
 *  LOG: Revision 6.8  2002/07/10 13:29:13  lbana
 *  LOG: removed all warnings
 *  LOG:
 *  LOG: Revision 6.7  2002/05/30 16:17:09  lbana
 *  LOG: More testing on current. Removed a few bugs.
 *  LOG:
 *  LOG: Revision 6.6  2002/05/17 20:20:02  lbana
 *  LOG: first level debugging...
 *  LOG:
 *  LOG: Revision 6.5  2002/05/14 18:55:09  lbana
 *  LOG: fix compiler errors in macros
 *  LOG:
 *  LOG: Revision 6.4  2002/05/14 18:35:38  lbana
 *  LOG: fixed errors in first reading...
 *  LOG:
 *  LOG: Revision 6.3  2002/05/13 23:24:38  lbana
 *  LOG: Build in current. Now for the testing.....
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
#include <its_hash.h>
#include <its_timers.h>
#include <its_transports.h>
#include <its_object.h>

#ident "$Id: ual_support.c,v 9.15.6.1.46.4 2015/10/27 10:16:06 jkchaitanya Exp $"

#define RESERVE_SLOT -1

void PRINT_EVENT(ITS_EVENT* evt)
{
#if defined(UAL_DDEBUG)
    int x = 0;
    printf("Event source 0x%02x\n",evt->src);
    for(x = 0; x < evt->len; x++)
    {
       if(x != 0 && x % 16 == 0)
       {
          printf("\n");
       }
       printf("0x%02x ",evt->data[x]);
    }
   printf("\n");
   fflush(stdout);
#endif

   return;
}

#define PRINT_BUF_MAX_STRING 2000
#define MAX_HDR_STRING_SIZE  160 

static char *styles[] =
{
    "DPC, NI",
    "DPC, OPC, NI",
    "DPC, SIO",
    "DPC, OPC, SIO",
    "DPC, SIO, SSN Range",
    "DPC, SIO, CIC Range",
    "DPC, OPC, SIO, SSN Range",
    "DPC, OPC, SIO, CIC Range",
    "DPC, SIO, SSN",
    "DPC, SIO, CIC",
    "DPC, OPC, SIO, SSN",
    "DPC, OPC, SIO, CIC",
    NULL
};

static char* str_rtypes[] = 
{
    "Don't care",
    "Local route",
    "Remote route",
    "Concerned route",
    "Duplicate route",
    "Routing key route"
};

static char* str_asp_state[] =
{
    "ASP DOWN     ",
    "ASP INACTIVE ",
    "ASP ACTIVE   ",
    "UNKNOWN STATE"
};

static char* str_as_state[] =
{
    "AS DOWN     ",
    "AS INACTIVE ",
    "AS ACTIVE   ",
    "AS PENDING  ",
    "UNKNOWN STATE"
};

/* Initialize PegManager */
UAL_PEG_Mgr *ualPegMgr = NULL;

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Init the ASP_Table and the RK_Manager.
 *    these are UAL manager tables maintaining the AS and ASP states.
 *   
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
UAL_InitializeInternalTables()
{
   int ret = ITS_SUCCESS;

   /*Initialize ASP, AS hash table and array */
   __UAL_ASP_Table = HASH_CreateTable();

   __UAL_AS_Manager.asTable = HASH_CreateTable();
   __UAL_AS_Manager.numEntries = 0;

   /*Initialize AuditTimersTable, used to keep track of DAUD timers */
   __UAL_Audit_Timer_Table = HASH_CreateTable();

   ret = UALPEGMgr_CreatePegMgr();

   return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Creates a new instance of a LIST (IntelliSS7 linked list).
 *   
 *  Input Parameters:
 *     
 *    None.
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
 *    pointer to LIST_Manager structure.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI LIST_Manager*
UAL_CreateList()
{
   return LIST_Create();
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Removes all nodes in this manager
 *   
 *  Input Parameters:
 *     
 *    - pointer to a LIST_Manager instance.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
UAL_DeleteList(LIST_Manager* lm)
{
    LIST_Delete(lm);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Deletes the UAL_ASP_Table data structure.
 *   
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
UAL_DeleteInternalTables()
{
    HASH_DeleteTable(__UAL_ASP_Table);
    HASH_DeleteTable(__UAL_AS_Manager.asTable);
    HASH_DeleteTable(__UAL_Audit_Timer_Table);

    UALPEGMgr_DestroyPegMgr();

    return ITS_SUCCESS;
}


/*
 * ASP list functions
 */


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Add a entry to the ASP list for a specific AS.
 *
 *  Input Parameters:
 *     
 *    - Pointer to the ASPListNode instance to be added.
 *
 *  Input/Output Parameters:
 *      
 *    - Pointer a ASP_List Instance.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 * 
 *    Usage:
 *    ASP_Entry *ent;
 *    ASPListNode nd;
 *    :
 *    ent = malloc();
 *    :
 *    nd.entry = ent;
 *    :
 *    ret = ASPList_AddEntry(al, nd);
 *    :
 *    See other functions ASPList_Iterate(), ASPList_Remove()
 *    if you create ASPListNode on the heap you clean it up 
 *    if AddEntry returns success upon removing RemoveEntry will clean
 *    up the heap. 
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int 
ASPList_AddEntry(ASP_List* al, ASPListNode* nd)
{
    int ret = ITS_SUCCESS;
    ASPListNode tmp;

    memset(&tmp, 0, sizeof(ASPListNode));

    tmp.aspInfo  = nd->aspInfo;
    tmp.trId   = nd->trId;
    tmp.state  = nd->state; 
    tmp.entry  = nd->entry;

    /* UAL can have its own error codes defined
     */
    ret = LIST_AddTail(al, &tmp, sizeof(ASPListNode));
    /* Process error code here and return UAL Error code
     * TODO: Need to define UAL Error codes.
     */

    return ret;
}


/*
 * local helper function
 */
static int
asp_compare(LIST_Entry* le, ITS_USHORT* match, int len)
{
    int ret = 0;
    ASPListNode* fromList = (ASPListNode *)le->data;

    /*Transport id should be sufficient enough to remove it*/
    if(fromList->trId == (*match))
    {
        ret = 1; /*We found the match */
    }

    return ret;
}

ITS_BOOLEAN
IsAspAddress(ASPListNode *aspNode, SOCK_IPv4Addr address, ITS_INT *aspId)
{
    int i = 0;

    for (i = 0; i < aspNode->aspInfo.numHome; i++)
    {
        if (aspNode->aspInfo.home[i] == address)
        {
            *aspId = aspNode->aspInfo.aspid;

            return ITS_TRUE;    
        }
    }

    *aspId = -1;

    return ITS_FALSE;
}



/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Removes an entry from an ASP list.
 *   
 *  Input Parameters:
 *     
 *    - ITS_USHORT: value of the trid representing that ASP entry
 *                  in the list.
 *
 *  Input/Output Parameters:
 *    
 *    - Pointer a ASP_List Instance.    
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    Frees ASPListNode from ASP_List in asList of pointers.
 *    :
 *    FOUND: Do I need to call RKList_RemoveEntry() before freeing
 *    ASP_Entry object created by the user.
 *    :
 *    :
 *    ret = ASPList_RemoveEntry()
 *    :
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
ASPList_RemoveEntry(ASP_List* al, ITS_USHORT trId)
{
    int ret;
    ASPListNode* rmPtr = NULL;
    int rmLen;

    ITS_C_ASSERT(al != NULL);

    /* Implement compare function function here
       LIST_RemoveFunc int (*func)(LIST_Entry* le, ASP_Entry* match, int len)
     */
    ret = LIST_Remove(al, (LIST_RemoveFunc) asp_compare, &trId, sizeof(ASPListNode), 
                      (void **)&rmPtr,  &rmLen);

    if(rmPtr != NULL) 
    {
        ITS_Free(rmPtr); /*its_list.c allocated memory for this ptr*/
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    List Iterator....
 *   
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *      
 *    - Pointer to a ASP_List instance.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    - Pointer to the next ASPListNode instance in the list.
 *
 *  Notes:
 *
 *    Usage:
 *
 *    ASP_List* al;
 *    ASP_Entry* tmp;
 *    :
 *    tmp = ASPList_Iterate(al);
 *    for(; tmp != NULL;tmp = ASPList_Iterate(NULL))
 *    {
 *    }
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI ASPListNode* 
ASPList_Iterate(ASP_List* al)
{
    static LIST_Entry*   iterate = NULL;
    static LIST_Manager* manager = NULL;

    ASPListNode* next = NULL;

    /* If user passes list pointer iterator will start from the beginning*/
    if(al != NULL)
    {
        manager = al;
        iterate = (LIST_HEAD(al) != NULL) ? LIST_HEAD(al) : NULL ;
    }

    if( (al != NULL) && (LIST_COUNT(al) == 0))
    {
       iterate = NULL;
    }

    if(iterate != NULL)
    {
        next = (ASPListNode *)iterate->data;

        iterate = iterate->next;
    }

    return next;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Search for an entry in the list.
 *
 *  Input Parameters:
 *     
 *    - ITS_USHORT value of the trid of the searched node
 *
 *  Input/Output Parameters:
 *      
 *    - Pointer to the ASP_List being searched.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    - Pointer to the ASPListNode instance found in the list
 *    - NULL if the entry was not found
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/   
UALDLLAPI ASPListNode* 
ASPList_FindEntry(ASP_List* al, ITS_USHORT tId)
{
    ASPListNode* match = NULL;

    match = ASPList_Iterate(al);

    for(; (match != NULL); match = ASPList_Iterate(NULL))
    {
        if(match->trId == tId)
        {
            break;
        }
        else
        {
            match = NULL;
        }
    }

    return match;
}


/*
 * RK list functions
 */

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Add an entry to a RK_List instance.
 *   
 *  Input Parameters:
 *     
 *    - Pointer to a RKListNode instance to be inserted in the list.
 *
 *  Input/Output Parameters:
 *      
 *    - Pointer to RK_List where an entry is added
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int 
RKList_AddEntry(RK_List* asl, RKListNode* nd)
{
    int ret = ITS_SUCCESS;
    RKListNode* tmp = NULL;

    /* avoid duplicates */
    tmp = RKList_FindEntry(asl, nd->rCtxt);
    if (tmp)
    {
        if (tmp->entry != nd->entry)
        {
            tmp->entry = nd->entry;
        }
    }
    else
    {
        if((tmp = (RKListNode *)calloc(1, sizeof(RKListNode))) == NULL)
        {
            return ITS_ENOMEM;
        }

        tmp->rCtxt    = nd->rCtxt;
        tmp->entry    = nd->entry; 

        ret = LIST_AddTail(asl, tmp, sizeof(RKListNode));

        if(ret != ITS_SUCCESS)
        {
           free(tmp);
        }

        /* Process error code here and return UAL Error code
         * TODO: Need to define UAL Error codes.
         */
    }

    return ret;
}


static int 
rk_compare(LIST_Entry* le, ITS_UINT* match, int len)
{
    int ret = 0;
    RKListNode* fromList = (RKListNode *)le->data;

    /*Transport id should be sufficient enough to remove it*/
    if(fromList->rCtxt == (*match))
    {
        ret = 1; /*We found the match */
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Removed an entry from a RK_List.
 *
 *  Input Parameters:
 *     
 *    - ITS_UINT, Routing Context value to be removed from the list.
 *
 *  Input/Output Parameters:
 *
 *    - Pointer to RK_List instance 
 *      
 *    None.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *    Usage:
 *    RKList_RemoveEntry() wiil free the memory allocated during 
 *    RKList_AddEntry() for RKListNode and it also frees the pointer
 *    RK_Context based on the routing context information ie ITS_UNIT
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int 
RKList_RemoveEntry(RK_List* rkl, ITS_UINT rCtxt)
{
    int ret = ITS_SUCCESS;
    RKListNode* rmPtr = NULL;
    int rmLen;

    /* Implement compare function function here
       LIST_RemoveFunc int (*func)(LIST_Entry* le, ASP_Entry* match, int len)
     */
    ret = LIST_Remove(rkl, (LIST_RemoveFunc) rk_compare, &rCtxt, sizeof(RKListNode), 
                      (void **)&rmPtr,  &rmLen);

    if(rmPtr != NULL) 
    {
        ITS_Free(rmPtr); /*this memeory is allocated in its_list.c*/
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    List iterator.
 *
 *  Input Parameters:
 *     
 *    None.
 *
 *  Input/Output Parameters:
 *      
 *    - Pointer to the RK_List instance.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    - Pointer to the next List entry RK_Context.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI RKListNode* 
RKList_Iterate(RK_List* rkl)
{
    static LIST_Entry*   iterate = NULL;
    static LIST_Manager* manager = NULL;

    RKListNode* next = NULL;

    /* If user passes list pointer iterator will start from the beginning*/
    if(rkl != NULL)
    {
        manager = rkl;
        iterate = (LIST_HEAD(rkl) != NULL) ? LIST_HEAD(rkl) : NULL ;
    }

    if(manager && LIST_COUNT(manager) == 0)
    {
       iterate = NULL;
    }

    if(iterate != NULL)
    {
        /*Return Node in a list instead of the context ptr (for PR6 and up)*/
        if(iterate->data != NULL)
        {
           next = ((RKListNode *)iterate->data);
        }

        iterate = iterate->next;
    }

    return next;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Find an entry is a RK_List instance.
 * 
 *  Input Parameters:
 *     
 *    - Routing Context (ITS_UINT) value to search in the list.
 *
 *  Input/Output Parameters:
 *      
 *    - Pointer to RK_List instance to be searched.
 *
 *  Output Parameters:
 *      
 *    None.
 *
 *  Return Value:
 *      
 *    - Pointer to RK_Context instance found in the list
 *    - NULL if not found
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI RKListNode* 
RKList_FindEntry(RK_List* rkl, ITS_UINT rCtxt)
{
    RKListNode* match = NULL;

    match = RKList_Iterate(rkl);

    for(; (match != NULL); match = RKList_Iterate(NULL))
    {
        if(match->entry->rCtxt == rCtxt)
        {
            break;
        }
        else
        {
            match = NULL;
        }
    }

    return match;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Add an ASP_Entry to the UAL_ASP_Table.
 *   
 *  Input Parameters:
 *     
 *    - Pointer to the ASP_Entry instance to be added.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI ASP_Entry * 
ASPTable_AddEntry(ASP_Entry* ent)
{
    int ret = ITS_SUCCESS;
    ASP_Entry* entry = NULL;

    if(ent != NULL)
    {
        entry = (ASP_Entry *)calloc(1, sizeof(ASP_Entry));
        memcpy(entry, ent, sizeof(ASP_Entry));

        entry->asList = UAL_CreateList();
       
        entry->isStateInactive = ITS_FALSE;

        memset(entry->ackTimer, 0, (UAL_MAX_TIMERS * sizeof(ITS_SERIAL)));

        ret = HASH_AddEntry(__UAL_ASP_Table, UAL_HASH_RID, entry->trId, 
                            (ITS_POINTER)entry);

        if(ret != ITS_SUCCESS)
        {
           free(entry);
           entry = NULL;
        }
    }

    return entry;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Search for an entry in the UAL_ASP_Table.
 *
 *  Input Parameters:
 *     
 *    - ITS_USHORT is the Trasport ID for a given ASP.
 *
 *  Input/Output Parameters:
 *      
 *    None.
 *
 *  Output Parameters:
 *      
 *    - double pointer to ASP_Entry, NULL if not found.
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
ASPTable_FindEntry(ITS_USHORT context, ASP_Entry** entry)
{
    int ret = ITS_SUCCESS;

    ret = HASH_FindEntry(__UAL_ASP_Table, UAL_HASH_RID, 
                         context, (ITS_POINTER*)entry);

    return ret;
}

 
/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Remove an entry from the UAL_ASP_table.
 *   
 *  Input Parameters:
 *     
 *    - ITS_USHORT, transport id to be removed from the table.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    Transport ID is the Context. The context is to retrive the
 *    entry from HasTable implemented in IntelliSS7 Suuport
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int 
ASPTable_RemoveEntry(ITS_USHORT context)
{
    int ret = ITS_SUCCESS;
    ITS_POINTER data;

    ret = HASH_FindEntry(__UAL_ASP_Table, UAL_HASH_RID, context, &data);

    if(ret == ITS_SUCCESS)
    {
        UAL_DeleteList(((ASP_Entry*)data)->asList);

        ((ASP_Entry *)data)->asList = NULL;

        free(data);
        ret = HASH_DeleteEntry(__UAL_ASP_Table, UAL_HASH_RID, context);
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Get the next free slot in the AS Table.
 *    This function returns a number in the range [1,UAL_MAX_NUM_AS].
 *    It starts with nextAvail = 0. It keeps on incremeting nextAvail
 *    till it reacheds UAL_MAX_NUM_AS. After that it again starts with
 *    nextAvail = 0. Before returning nextAvail as return value it makes
 *    sure that there is no RK_Context with sCtxt = nextAvail in AS_Manager.asTable.
 *
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI ITS_UINT 
RKManager_GetNextFreeSlot()
{
    //* Don't use slot 0 */
    static ITS_UINT nextAvail = 1;
    int ret = -1;
    int count = 0;

    while(RKManager_FindEntry(nextAvail)) 
    {
	nextAvail++;
	if (nextAvail > UAL_MAX_NUM_AS)
	{
            //* Don't use slot 0 */
	    nextAvail = 1;
	}

	// count counts the number of times we searched.
        // This will prevent infinite loop if have reached the limit
	// of UAL_MAX_NUM_AS

	count ++;
	if (count > UAL_MAX_NUM_AS) 
	{
	    return ret;
	}
    }
    ret = nextAvail;
    nextAvail++;

    if (nextAvail > UAL_MAX_NUM_AS)
    {
        //* Don't use slot 0 */
	nextAvail = 1;
    }


    return ret;
}

int
UAL_AllocateLocalRKId(ITS_UINT *rCtxt)
{
    ITS_C_ASSERT(rCtxt != NULL);

    if ((*rCtxt = RKManager_GetNextFreeSlot()) > 0)
    {
        return ITS_SUCCESS;
    }
    else
    {
        return *rCtxt;
    }
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *    Add an entry to the AS Table.
 *   
 *  Input Parameters:
 *     
 *    - ITS_INT index int the AS table (i.e) the routing ctxt
 *
 *  Input/Output Parameters:
 *      
 *    None.
 *
 *  Output Parameters:
 *      
 *    - RK_Context pointer to be added
 *
 *  Return Value:
 *      
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int 
RKManager_AddEntry(ITS_UINT index, RK_Context* ent)
{
    int ret = ITS_SUCCESS;

    if((index <= 0) || (index > UAL_MAX_NUM_AS))
    {
        return -1;
    }

    if(ent != NULL)
    {

        ret = HASH_AddEntry(__UAL_AS_Manager.asTable, UAL_HASH_RID, index, 
                            (ITS_POINTER)ent);

        if(ret == ITS_SUCCESS)
        {
           __UAL_AS_Manager.numEntries++;
        }
    }

    return ret;

}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI RK_Context* 
RKManager_FindEntry(ITS_UINT rc)
{
    RK_Context* ctxt = NULL;

    HASH_FindEntry(__UAL_AS_Manager.asTable, UAL_HASH_RID, 
                         rc, (ITS_POINTER*)&ctxt);

    return ctxt;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int 
RKManager_RemoveEntry(RK_Context* ent)
{
   
   int ret = ITS_SUCCESS;
    if(ent == NULL)
    {
        ret = -1;
        return ret;
    }

    ret = RKManager_RemoveEntryContext(ent->rCtxt);

    return ret;

}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
int RKManager_RemoveEntryContext(ITS_UINT rc)
{
    int ret = ITS_SUCCESS;
    ITS_POINTER data;

    if(rc > 0 && rc <= UAL_MAX_NUM_AS)
    {
	ret = HASH_FindEntry(__UAL_AS_Manager.asTable, UAL_HASH_RID, rc, &data);

	if(ret == ITS_SUCCESS)
	{
	    UAL_DeleteList(((RK_Context *)data)->aspList);
	    ((RK_Context *)data)->aspList = NULL;
	    free(data);

	    ret = HASH_DeleteEntry(__UAL_AS_Manager.asTable, UAL_HASH_RID, rc);

	    ret = ITS_SUCCESS;

	    __UAL_AS_Manager.numEntries--;
	}
    }
    else
    {
        ret = !ITS_SUCCESS;
    }

    return ret;
	
}

static int 
hash_iterative_proc(ITS_INT context, ITS_POINTER data, 
                     void* in, void* out)
{
   int ret = ITS_SUCCESS;
   static int len = 0;
   int size = *(int *) in; /* Size of the out pointer array*/
   ITS_USHORT* ctxt = out;

   ASP_Entry* entry = (ASP_Entry *)data;

   if(len < size)
   {
       if(entry != NULL)
       {
          ctxt = ctxt + len;

          *ctxt = entry->trId; 

          len++;

          if(len == size) len = 0; /* reset the length*/
       }
   }
   else
   {
       ret = !ITS_SUCCESS;
   }

   return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *   
 *    Used for broadcast....
 *
 *  Input Parameters:
 *     
 *    None.
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
 *    ITS_SUCCESS is returned in case every component has been initialized, any
 *    other return values indicate that an error as occured.
 *
 *  Notes:
 *
 *    Usage:
 *
 *    ITS_USHORT trids[256];
 *    currently available transport ids.
 *    ITS_INT    avail;
 *
 *    ret = ASPTable_GetAllTransportIds(&trids, 256, &avail);
 *
 *    for(x = 0; x < avail; x++) {
 *        ITS_PutEvent(trids[x], &event);
 *    }
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
ASPTable_GetAllTransportIds(ITS_USHORT* trids, ITS_INT size, ITS_INT* avail)
{
   int  ret = ITS_SUCCESS;
   if (__UAL_ASP_Table == NULL)
   {
       return !ITS_SUCCESS;
   }

   *avail = HASH_NUM_ENTRIES(__UAL_ASP_Table);

   if(*avail == 0 || *avail > size)
   {
       ret = !ITS_SUCCESS;
   }
   else
   {
       ret = HASH_VTableIterate(__UAL_ASP_Table, UAL_HASH_RID, avail, 
                                 trids, hash_iterative_proc);
   }

   return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *     
 *  Input/Output Parameters:
 *
 *     None.      
 *
 *  Output Parameters:
 *      
 *     None.
 *
 *  Return Value:
 *      
 *
 *  Notes:
 * 
 *     None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int
UAL_SetTimerMsgData(UAL_TimerCtx *ctx, ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS;

    ITS_C_ASSERT((ctx != NULL) && (evt != NULL));

    if (evt->len <= UAL_MAX_MSG_LEN)
    {
        ctx->len = evt->len;
    
        ITS_C_ASSERT(evt->len < UAL_MAX_MSG_LEN);

        memcpy(ctx->msg, evt->data, evt->len);
    }
    else
    {
        ret = ITS_ENOMEM;
    }

    return ret;
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *     
 *  Input/Output Parameters:
 *
 *     None.      
 *
 *  Output Parameters:
 *      
 *     None.
 *
 *  Return Value:
 *      
 *
 *  Notes:
 * 
 *     None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI ITS_BOOLEAN
UAL_CheckASPending(RK_Context* rk_ctxt)
{
    ITS_BOOLEAN  ret    = ITS_FALSE;
    ITS_BOOLEAN  flag   = ITS_TRUE;
    ASPListNode* asp_nd = NULL;

    ITS_USHORT   nActiveAsp=0; 
    ITS_USHORT   nCount=0; 
    ITS_BOOLEAN  retCode = ITS_FALSE;
    ITS_USHORT   notifyTrans[16];
    ITS_UINT     notifyAspId[16];

    if(rk_ctxt != NULL)
    {
        if(rk_ctxt->state == UAL_AS_ACTIVE)
        {
            asp_nd = ASPList_Iterate(rk_ctxt->aspList);

            for(; asp_nd && flag; asp_nd = ASPList_Iterate(NULL))
            {
                if(asp_nd->state == UAL_ASP_ACTIVE)
                {
                    nActiveAsp++;
                    flag = ITS_FALSE;
                }
                else 
                {
                    /* If number of Active ASPs are going less then   *
                     * rk_ctxt->nActives and TrafficMode is LoadShare *
                     * or BroadCast, send NOTIFY to Inactive ones for *
                     * Insufficient Resources for given AS            *
                     */
                    if (asp_nd->state == UAL_ASP_INACTIVE)
                    {
                         if (rk_ctxt-> trafficMode != UAL_OVERRIDE)
                         {
                            notifyTrans[nCount] = asp_nd->trId;
                            notifyAspId[nCount++] = asp_nd->aspInfo.aspid;
                         }
                    }
                    flag = ITS_TRUE;
                }
                ret = flag;
            }

            while ((nCount > 0) && (nActiveAsp < rk_ctxt->nActives))
            {
                nCount--;

                retCode = UAL_SendNotify(notifyTrans[nCount], 
                                     UAL_ST_TYPE_OTHER, UAL_ST_ID_INSUF_ASP, 
                                     &rk_ctxt->rCtxt, 1, notifyAspId[nCount]);

                if(retCode == ITS_SUCCESS)
                {
                    UAL_DEBUG(("Notify INSUF_ASP sent to the TR-ID = 0x%02x\n",
                                      notifyTrans[nCount]));
                }
                else
                {
                    UAL_ERROR(("Failed to send INSUF_ASP Notify to TR-ID = 0x%02x\n",
                                      notifyTrans[nCount]));
                }
            }
        }
    }

    return ret;
}

UALDLLAPI ITS_BOOLEAN
UAL_CheckASDown(RK_Context* rk_ctxt)
{
    ITS_BOOLEAN ret = ITS_FALSE;
    ITS_BOOLEAN flag = ITS_TRUE;
    ASPListNode* asp_nd = NULL;

    if(rk_ctxt != NULL)
    {
        if(rk_ctxt->state == UAL_AS_INACTIVE)
        {
            asp_nd = ASPList_Iterate(rk_ctxt->aspList);

            for(; asp_nd && flag; asp_nd = ASPList_Iterate(NULL))
            {
                if(asp_nd->state == UAL_ASP_INACTIVE)
                {
                    flag = ITS_FALSE;
                }
                else
                {
                    flag = ITS_TRUE;
                }

                ret = flag;
            }
         }
         else if(rk_ctxt->state == UAL_AS_ACTIVE)
         {
             ret = ITS_FALSE;
         }
    }

    return ret;
}

UALDLLAPI SS7_LinkPtr
GetLinkPtrFromTransport(ITS_OCTET linkSet, TRANSPORT_Control *tc)
{
    SS7_LinkPtr found = NULL, tmp;

    tmp = TRANSPORT_SS7_INFO(tc).linkInfo;

    for(; tmp ;tmp = tmp->next) 
    {
        if(tmp->linkSet && 
           (tmp->linkSet->linkSet == linkSet))
        {
            found = tmp;

            break;
        }
    }

    return found;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *     
 *  Input/Output Parameters:
 *
 *     None.      
 *
 *  Output Parameters:
 *      
 *     None.
 *
 *  Return Value:
 *      
 *
 *  Notes:
 * 
 *     None.
 *
 *  See Also:
 *
 ******************************************************************************/
UALDLLAPI int UAL_CancelPendingTimer(ITS_USHORT trId, RK_Context* rk_context)
{
    ITS_INT    ret = ITS_SUCCESS;
    ITS_EVENT  event;
    ITS_USHORT pending_id;
    SS7_LinkPtr linkPtr;

    ITS_EVENT_INIT(&event, 0, 0);

    if(rk_context->pendingTimer != (ITS_SERIAL)0 && 
       rk_context->pendingTrans != (ITS_SERIAL)0)
    {
        pending_id = TRANSPORT_INSTANCE(rk_context->pendingTrans);

        ret = TIMERS_CancelTimer(rk_context->pendingTimer);

        if(ret == ITS_SUCCESS)
        {
            UAL_DEBUG(("Cancelled Pending Timer TRID 0x%02x:\n",
                              trId));
        }

        while(!TRANSPORT_EXIT_NOW(rk_context->pendingTrans))
        {
            ret = ITS_PeekNextEvent(rk_context->pendingTrans, &event);

            if(ret == ITS_ENOMSG || ret == ITS_EBADMUTEX)
            {
                TRANSPORT_EXIT_NOW((TRANSPORT_Control *)rk_context->pendingTrans)
                     = ITS_TRUE;
            }
            else
            {
                ret = TRANSPORT_PutEvent(trId, &event);

                if(ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Got Invalid Transport while sending "
                        "pending events\n"));
                }
            }
        }

        linkPtr = GetLinkPtrFromTransport(rk_context->linkSet, 
                                          rk_context->pendingTrans);

        if(linkPtr != NULL)
        {
            ret = LINK_RemLink(rk_context->linkSet, linkPtr);

            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Failed to remove link from linkSet\n"));
            }
        }

        TRANSPORT_Delete(rk_context->pendingTrans);

        rk_context->pendingTimer = (ITS_SERIAL)0;
        rk_context->pendingTrans = NULL;
    }

    return ret;
}

UALDLLAPI ITS_OCTET
UAL_GetNextAvailableLinkCode(ITS_OCTET linkSet)
{
    SS7_LinkSetPtr lsp;
    SS7_LinkPtr*   lp;
    ITS_INT        count = 0;
    ITS_OCTET      lc    = 0xff;

    if( !(lsp = LINKSET_FindLinkSet(linkSet)))
    {
        return lc;
    }

    lp = lsp->links;

    if (lp != NULL && lsp->numLinks)
    {
        /*no exclusive lock here */
        for(lp = lsp->links; *lp != NULL; lp += count)
        {
            count++;
        }

        if(count > 16)
        {
            UAL_WARNING(("No more links available\n"));

            count = lc;
        }
        else if(count != 0)
        {
            lsp->links[count] = (void *) -1; /*reserve the slot*/
        }
    }
    else
    {
        count = 0;
    }

    return (count & 0xff);
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Routing Key value more than 255 related function.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-01-2008   BugId: 1541     Propagated Bridgeport Isse.
 *                                          Support of Routing Key value 
 *                                          more than 255.                                          
 *
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN u_astbl_cmd_enabled_on_asp_side = ITS_FALSE;
static int
DumpAS_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{

   int ret = ITS_SUCCESS;
   char buf[80];
   char temp[PRINT_BUF_MAX_STRING];
   char hdr_str[MAX_HDR_STRING_SIZE]; 
   char* temp_str1 = NULL;
   int str_len = 0;
   ITS_BOOLEAN addHeader = ITS_FALSE;


   char **temp_strp = (char**)in;

   RK_Context* ctxt = (RK_Context*)data;

   if(ctxt == NULL)
   {
     return ret;
   }

   /* We are not interested in printing
    * our own states.
    */
   if (ctxt->isMember && !UAL_GL_DEBUG_FLAG)
   {
	   if (!UAL_IS_IPSP_DOUBLE_EXCHG(UAL_GL_IPSP_TYPE))
       {
           /* We will add following message only once */
           if(addHeader == ITS_FALSE)
           {
                strcat(hdr_str, "\n *** This command is not available"
                             " on ASP/IPSP client Side. ***\n");
                addHeader = ITS_TRUE;    
           } 
       }
       if(u_astbl_cmd_enabled_on_asp_side == ITS_FALSE)
	   {
		   return ITS_SUCCESS;
	   }
   }

   memset(temp, 0, PRINT_BUF_MAX_STRING);
   memset(buf, 0, 80);

   strcat(temp, "--------------------------------------------------\n"); 
   sprintf(buf, "    rCtxt = %u\n", ctxt->rCtxt);
   strcat(temp, buf);
   memset(buf, 0, 80);

   sprintf(buf, "    state = %s\n", str_as_state[ctxt->state]);
   strcat(temp, buf);
   memset(buf, 0, 80);

     switch(ctxt->trafficMode)
     {
	 case UAL_MODE_NONE:
	    sprintf(buf, "    trafficMode = %s\n", "UAL_MODE_NONE");
	    break;

	 case UAL_OVERRIDE:
	    sprintf(buf, "    trafficMode = %s\n", "UAL_OVERRIDE");
	    break;

	 case UAL_LOADSHARE:
	    sprintf(buf, "    trafficMode = %s\n", "UAL_LOADSHARE");
	    break;

	 case UAL_BROADCAST:
	    sprintf(buf, "    trafficMode = %s\n", "UAL_BROADCAST");
	    break;

	 default:
	    sprintf(buf, "    trafficMode = %s\n", "UAL_UNKNOWN");
     }
     strcat(temp, buf);
     memset(buf, 0, 80);

     sprintf(buf, "    n+k redundancy = %d + %d \n", 
	      ctxt->nActives, ctxt->kStandby);
     strcat(temp, buf);
     memset(buf, 0, 80);

     strcat(temp, "    ROUTE_Info:\n");

     sprintf(buf, "        ROUTE_TYPE     = %s \n", str_rtypes[ctxt->asInfo.type]);
     strcat(temp, buf);
     memset(buf, 0, 80);

     sprintf(buf, "        ROUTE_CRITERIA = %s \n", styles[ctxt->asInfo.style]);
     strcat(temp, buf);
     memset(buf, 0, 80);

     sprintf(buf, "        Point Code     = %d \n", ctxt->asInfo.dpc);

     strcat(temp, buf);
     memset(buf, 0 , 80);

     switch(ctxt->asInfo.style)
     {
	 case ROUTE_DPC_NI:
	     break;
	 case ROUTE_DPC_OPC_NI:
	     break;
	 case ROUTE_DPC_SIO:
	     break;
	 case ROUTE_DPC_SIO_SSN_RANGE:
	     break;
	 case ROUTE_DPC_SIO_CIC_RANGE:
	     break;
	 case ROUTE_DPC_SIO_SSN:
	     break;
	 case ROUTE_DPC_SIO_CIC:
	     break;
	 case ROUTE_DPC_OPC_SIO:
	     break;
	 case ROUTE_DPC_OPC_SIO_SSN_RANGE:
	     break;
	 case ROUTE_DPC_OPC_SIO_CIC_RANGE:
	     break;
	 case ROUTE_DPC_OPC_SIO_SSN:
	     break;
	 case ROUTE_DPC_OPC_SIO_CIC:
	     break;
	 case ROUTE_DPC_UDEF:
	     break;
     }

     sprintf(buf, "    %s \n", "ASP List: ");
     strcat(temp, buf);

     memset(buf, 0 , 80);

     if(ctxt->aspList && ASP_LIST_COUNT(ctxt->aspList)) 
     {
	 char buf1[80];

	 ASPListNode* nd = ASPList_Iterate(ctxt->aspList);
	 for(; nd; nd = ASPList_Iterate(NULL))
	 {
	    sprintf(buf1, "        TRID = 0x%02x    ASP_STATE = %s    ASP Id = %d\n",
		    nd->trId, str_asp_state[nd->state], nd->aspInfo.aspid );

	    strcat(temp, buf1);
	 }
     } 

     sprintf(buf, "        Instance = %d\n", ctxt->instance);
     strcat(temp, buf);

     temp_str1 = *temp_strp;

     if(temp_str1 != NULL)
     {
	 str_len = strlen(temp_str1);
     }

     *temp_strp = calloc(1, strlen(temp) + str_len + 1);

     if(*temp_strp == NULL)
     {
	 return ITS_ENOMEM;
     }

     if(temp_str1 != NULL)
     {
	memmove(*temp_strp, temp_str1, str_len);
     }

     strcat(*temp_strp, temp);
     memset(temp, 0, PRINT_BUF_MAX_STRING);

     if(temp_str1 != NULL)
     {
	free(temp_str1);
	temp_str1 = NULL;
     } 
     return ret;
}

void UAL_DumpASTable(char** dump_string)
{
   char* temp_str = NULL;
   char hdr_str[MAX_HDR_STRING_SIZE]; 
   char temp[PRINT_BUF_MAX_STRING];

   if(dump_string == NULL)
   {
       return;
   }

   if ((u_astbl_cmd_enabled_on_asp_side == ITS_FALSE) && (UAL_GL_ITW_MODE == UAL_ITW_ASP))
   {
       *dump_string = calloc(1, MAX_HDR_STRING_SIZE);
       sprintf(*dump_string, "\n *** This command not available on ASP Side. ***\n");
       return;
   } 

   memset(temp, 0, PRINT_BUF_MAX_STRING);
   memset(hdr_str,  0, MAX_HDR_STRING_SIZE);
 
   strcat(hdr_str, "-----------\n");
   strcat(hdr_str, "Dump of AS_Manager:\n");

   if(AS_CONTEXT_COUNT != 0)
   {
        HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, &temp_str,
                               NULL, DumpAS_hash_iterative_proc);
   }
   else
   {
      strcat(hdr_str, "AS Table is Empty:\n");
   }

   if(dump_string != NULL)
   {
       int len = 0;

       if(temp_str != NULL)
       {
           len = strlen(temp_str);
       }

       *dump_string = calloc(1, strlen(hdr_str) + len + 1);
  
       if(*dump_string == NULL)
       {
          return;
       }
 
       strcat(*dump_string, hdr_str);
       if(temp_str != NULL)
       {
          strcat(*dump_string, temp_str);
       }
   }

   return;
}


UALDLLAPI void UAL_DumpASPTable(char** dump_string)
{
   char buf[MAX_HDR_STRING_SIZE];
   char temp[PRINT_BUF_MAX_STRING];
   ITS_USHORT trids[UAL_MAX_NUM_ASSOC];
   int ret, num_trids = 0;
   ASP_Entry* aspRec = NULL;

   int i = 0, len = 0;
   char* dup1, *dup2;

   if(dump_string == NULL)
   {
       return;
   }

   memset(buf,   0, MAX_HDR_STRING_SIZE); 
   memset(temp,  0, PRINT_BUF_MAX_STRING);
   memset(trids, 0, sizeof(ITS_USHORT) * UAL_MAX_NUM_ASSOC);

   dup1 = dup2 = NULL;

   strcat(temp, "--------------------------------------------------\n");
   strcat(temp, "Dump of Association Table(ASP).\n");

   ret = ASPTable_GetAllTransportIds(trids, UAL_MAX_NUM_ASSOC,
                                     &num_trids); 

   for(i = 0 ; i < num_trids; i++)
   {
       ret = ASPTable_FindEntry(trids[i], &aspRec);

       if(ret == ITS_SUCCESS)
       {
           RKListNode* rk = NULL;

           strcat(temp, "--------------------------------------------------\n");

           if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
           {
               switch(aspRec->remoteInfo.state)
               {
                   case UAL_ASP_DOWN:
                   case UAL_ASP_INACTIVE:
                   case UAL_ASP_ACTIVE:
                   case UAL_ASP_CANT_START:
                   case UAL_ASP_UP:
                       {
                           sprintf(buf, "state    = %s\n", 
                                   str_asp_state[aspRec->remoteInfo.state]);
                       }
                       break;
                   default:
                       {
                           sprintf(buf, "state    = UNKNOWN\n");
                       }
                       break;
               }
           }
           else
           {
               sprintf(buf, "state    = %s\n", str_asp_state[aspRec->state]);
           }

           strcat(temp, buf);
           sprintf(buf, "TRID     = 0x%02x\n", aspRec->trId); 
           strcat(temp, buf);

           if (aspRec->payload == SCTP_PAYLOAD_M3UA)
           {
               sprintf(buf, "Payload  = M3UA\n"); 
           }
           else if (aspRec->payload == SCTP_PAYLOAD_SUA)
           {
               sprintf(buf, "Payload  = SUA\n"); 
           }
           else
           {
               sprintf(buf, "Payload  = Unknown\n"); 
           }

           strcat(temp, buf);

           if (UAL_GL_ITW_MODE == UAL_ITW_IPSP && 
               UAL_IS_IPSP_DOUBLE_EXCHG(UAL_GL_IPSP_TYPE)) 
           { 
               sprintf(buf, "ASP ID   = %d \n", 
                       aspRec->remoteInfo.aspInfo.aspid);
           }
           else
           {
               sprintf(buf, "ASP ID   = %d \n", aspRec->aspId);
           }

           strcat(temp, buf);

           strcat(temp, "    AS List: \n");

           rk = RKList_Iterate(aspRec->asList);

           if (rk != NULL)
           {
               for(; rk; rk = RKList_Iterate(NULL))
               {
                    RK_Context* ctxt = rk->entry;

                    /*
                     * Not interested in diplaying its own states
                     * to the user MML commands.
                     */
		     if (ctxt->isMember && !UAL_GL_DEBUG_FLAG)
	     	     {
		         continue;
		     }

                     sprintf(buf, "        rCtxt  =  %u   State  =  %s \n",
                             ctxt->rCtxt, str_as_state[ctxt->state]);
                     strcat(temp, buf);
               }
           }

           dup2 = dup1;

           if(dup2 != NULL)
           {
              len = strlen(dup2);
           }

           dup1 = calloc(1, strlen(temp) + len + 1); 
           if(len != 0)
           {
               memmove(dup1, dup2, len);
           }
           strcat(dup1, temp);

           if(dup2 != NULL)
           {
               free(dup2);
               dup2 = NULL;
           }

           memset(temp, 0, PRINT_BUF_MAX_STRING);
       }
   }

   if(num_trids == 0)
   {
      dup1 = calloc(1, strlen(temp) + 1);
      strcat(dup1, temp);
   } 

   *dump_string = dup1;

   return;
}


UALDLLAPI void UAL_DumpCfg(char **dump_string)
{
   char hdr_str[MAX_HDR_STRING_SIZE]; 
   char temp[PRINT_BUF_MAX_STRING];
   char buf[80];

   if(dump_string == NULL)
   {
       return;
   }
   memset(temp, 0, PRINT_BUF_MAX_STRING);
   memset(hdr_str,  0, MAX_HDR_STRING_SIZE);

   strcat(hdr_str, "---------------------------------------------------\n");
   strcat(hdr_str, "Dump of UAL Config:\n");
   
    if ( UAL_GL_ITW_MODE == UAL_ITW_SG)
    {
        sprintf(buf, "    Interworking Mode    <sgMode> \n");
    }
    else if ( UAL_GL_ITW_MODE == UAL_ITW_ASP)
    {
        sprintf(buf, "    Interworking Mode    <aspMode> \n");
    }
    else if ( UAL_GL_ITW_MODE == UAL_ITW_IPSP)
    {
        sprintf(buf, "    Interworking Mode    <ipspMode> \n");
    }

    strcat(temp, buf);
    memset(buf, 0, 80);

    sprintf(buf, "    Ack Timer            <%d> \n", UAL_GL_ACK_TIMER);
    strcat(temp, buf);
    memset(buf, 0, 80);

    sprintf(buf, "    Pending Timer        <%d> \n", UAL_GL_PEND_TIMER);
    strcat(temp, buf);
    memset(buf, 0, 80);

    sprintf(buf, "    Heart Beat Interval   <%d> \n", UAL_GL_HB_INTER );
    strcat(temp, buf);
    memset(buf, 0, 80);

    sprintf(buf, "    Aud Timer            <%d> \n", UAL_GL_AUD_TIMER);
    strcat(temp, buf);
    memset(buf, 0, 80);

    switch(UAL_AlarmLevel)
    {
        case ALARM_LVL_CRIT :
            sprintf(buf, "    Alarm Level           <CRITICAL>\n");
        break;

        case ALARM_LVL_MAJOR :
            sprintf(buf, "    Alarm Level           <MAJOR>\n");
        break;

         case ALARM_LVL_MINOR :
            sprintf(buf, "    Alarm Level           <MINOR>\n");
        break;

        case ALARM_LVL_INFO :
            sprintf(buf, "    Alarm Level           <INFO>\n");
        break;

        case ALARM_LVL_OFF :
            sprintf(buf, "    Alarm Level           <OFF>\n");
        break;

        default :
            sprintf(buf, "    Alarm Level           <Not Set>\n");
        break;
    }

    strcat(temp, buf);
    memset(buf, 0, 80);

   if(dump_string != NULL)
   {
       int len = 0;

       len = strlen(temp);

       *dump_string = calloc(1, strlen(hdr_str) + len + 1);
   
       strcat(*dump_string, hdr_str);
       strcat(*dump_string, temp);
   }

}


UALDLLAPI ITS_INT
UALPEGMgr_CreatePegMgr()
{
    ITS_INT ret = ITS_SUCCESS;

    if ( (ualPegMgr = calloc(1, sizeof(UAL_PEG_Mgr))) == NULL)
    {
        ret = ITS_ENOMEM;
    }

    ualPegMgr->name = strdup("UAL Peg Manager");

    return ret;
}


UALDLLAPI ITS_INT
UALPEGMgr_DestroyPegMgr()
{
    ITS_INT      ret = ITS_SUCCESS;
    UAL_PEG_List *ptr = NULL, *tmp;

    if (!ualPegMgr)
    {
        return ITS_SUCCESS;
    }

    if (ualPegMgr->name)
    {
        free(ualPegMgr->name);
    }

	for (ptr = ualPegMgr->list; ptr;)
    {
        tmp = ptr;
        ptr = ptr->next; /* move on to next */

        free(tmp);

        UALPEGMGR_NUM_TRANS(ualPegMgr)--;
    }

    if (UALPEGMGR_NUM_TRANS(ualPegMgr) != 0)
    {
        UAL_ERROR(("UALPEGMgr_DestroyPegList: PegList link is broken.\n"));

        ret = ITS_ENOMSG;
    }

    return ret;
}


static UAL_MIB_STATS*
ualpeglist_getStats(ITS_USHORT trid)
{
    UAL_MIB_STATS *ret = NULL;
    UAL_PEG_List  *ptr;
    ITS_BOOLEAN   found = ITS_FALSE;

    if (ualPegMgr)
    {
        for (ptr = ualPegMgr->list; ptr && !found; ptr = ptr->next)
        {
            if (ptr->stats.transportID == trid)
            {
                found = ITS_TRUE;
                ret = &(ptr->stats);
            }
        }
    }

    if (!found)
    {
	UAL_WARNING(("UALPEGMgr_GetStats: TransportID = %x was not found in transport_list of Peg Manager\n", trid));
    }

    return ret;
}


UALDLLAPI UAL_MIB_STATS*
UALPEGMgr_GetStats(ITS_USHORT trid)
{
    return ualpeglist_getStats(trid);
}


UALDLLAPI ITS_INT
UALPEGMgr_AddElement(ITS_USHORT trid)
{
    UAL_PEG_List *ptr = NULL;
    ITS_INT ret = ITS_SUCCESS;

    UAL_WARNING(("UALPEGMgr_AddElement: Adding trId=%0x to transport_list of Peg Manager\n", trid));
    if (!ualpeglist_getStats(trid))
    {
        ptr = calloc(1, sizeof(UAL_PEG_List));

        if (ptr)
        {
	    UAL_PEG_List *tmp = ualPegMgr->list;

            ptr->stats.transportID = trid;

            ptr->next = tmp;
            ualPegMgr->list = ptr;
            
	    UALPEGMGR_NUM_TRANS(ualPegMgr)++;
	    
	    UAL_DEBUG(("UALPEGMgr_AddElement: Added trId=%0x, to the transport_list of Peg Manager\n", trid));
        }
    }

    return ret;
}


UALDLLAPI ITS_INT
UALPEGMgr_RemoveElement(ITS_USHORT trid)
{
    UAL_PEG_List *tmp = NULL, *ptr;
    UAL_PEG_List *prev;

    UAL_WARNING(("UALPEGMgr_RemoveElement: Removing trId=%0x, from transport_list of Peg Manager\n", trid));
    if (ualPegMgr)
    {
        prev = ualPegMgr->list;

        for (ptr = ualPegMgr->list; ptr && !tmp; ptr = ptr->next)
        {
            if (ptr->stats.transportID == trid)
            {
                tmp = ptr;

                break;
            }

            prev = ptr;
        }

        if (tmp)
        {
            prev->next = tmp->next;

            UALPEGMGR_NUM_TRANS(ualPegMgr)--;

            if (tmp == prev)
            {
                ualPegMgr->list = NULL;
            }

            free(tmp);
        }
    }

    return ITS_SUCCESS;
}


UALDLLAPI ITS_INT
UAL_GetMIBStats(ITS_USHORT trid, UAL_MIB_STATS *stats)
{
    ITS_INT ret = ITS_ENOTRANSPORT;

    UAL_MIB_STATS *tmp = NULL;

    if (stats == NULL)
    {
        ret = ITS_ENOMEM;
    }
    else
    {
        tmp = ualpeglist_getStats(trid);

        if (tmp)
        {
            ret = ITS_SUCCESS;

            memcpy(stats, tmp, sizeof(UAL_MIB_STATS));
        }
        else
        {
            UAL_ERROR(("UAL_GetMIBStats: Invalid transportID = %x\n",
                         trid));
        } 
    }

    return ret;
}

UALDLLAPI ITS_INT
UAL_IncrementMIBStats(ITS_USHORT trId, UAL_PEG_ID id)
{
    UAL_MIB_STATS *stats = NULL;
    stats = UALPEGMgr_GetStats(trId);
    
    if (stats == NULL)
    {
        // Error trace
        UAL_ERROR(("UAL_IncrementMIBStats: Could not get the MIBStats structure for the transport, trid=%x\n", trId));
        return (!ITS_SUCCESS);
    }

    switch(id)
    {
        case UAL_PEG_UP_SENT_ID:
	{
            stats->aspUpSent++;
            break;
        }
        case UAL_PEG_UP_RECV_ID:
        {
            stats->aspUpRecv++;
            break;
        }
        case UAL_PEG_UPACK_SENT_ID:
        {
            stats->aspUpAckSent++;
            break;
        }
        case UAL_PEG_UPACK_RECV_ID:
        {
            stats->aspUpAckRecv++;
            break;
        }
        case UAL_PEG_DN_SENT_ID:
        {
            stats->aspDnSent++;
            break;
        }
        case UAL_PEG_DN_RECV_ID:
        {
            stats->aspDnRecv++;
            break;
        }
        case UAL_PEG_DNACK_SENT_ID:
        {
            stats->aspDnAckSent++;
            break;
        }
        case UAL_PEG_DNACK_RECV_ID:
        {
            stats->aspDnAckRecv++;
            break;
        }
        case UAL_PEG_AC_SENT_ID:
        {
            stats->aspAcSent++;
            break;
        }
        case UAL_PEG_AC_RECV_ID:
        {
            stats->aspAcRecv++;
            break;
        }
        case UAL_PEG_ACACK_SENT_ID:
        {
            stats->aspAcAckSent++;
            break;
        }
        case UAL_PEG_ACACK_RECV_ID:
        {
            stats->aspAcAckRecv++;
            break;
        }
        case UAL_PEG_IA_SENT_ID:
        {
            stats->aspIaSent++;
            break;
        }
        case UAL_PEG_IA_RECV_ID:
        {
            stats->aspIaRecv++;
            break;
        }
        case UAL_PEG_IAACK_SENT_ID:
        {
            stats->aspIaAckSent++;
            break;
        }
        case UAL_PEG_IAACK_RECV_ID:
        {
            stats->aspIaAckRecv++;
            break;
        }
        case UAL_PEG_NOTIFY_SENT_ID:
        {
            stats->notifySent++;
            break;
        }
        case UAL_PEG_NOTIFY_RECV_ID:
        {
            stats->notifyRecv++;
            break;
        }
        case UAL_PEG_REG_REQ_SENT_ID:
        {
            stats->regReqSent++;
            break;
        }
        case UAL_PEG_REG_REQ_RECV_ID:
        {
            stats->regReqRecv++;
            break;
        }
        case UAL_PEG_REG_RSP_SENT_ID:
        {
            stats->regRspSent++;
            break;
        }
        case UAL_PEG_REG_RSP_RECV_ID:
        {
            stats->regRspRecv++;
            break;
        }
        case UAL_PEG_DEREG_REQ_SENT_ID:
        {
            stats->deregReqSent++;
            break;
        }
        case UAL_PEG_DEREG_REQ_RECV_ID:
        {
            stats->deregReqRecv++;
            break;
        }
        case UAL_PEG_DEREG_RSP_SENT_ID:
        {
            stats->deregRspSent++;
            break;
        }
        case UAL_PEG_DEREG_RSP_RECV_ID:
        {
            stats->deregRspRecv++;
            break;
        }
        case UAL_PEG_ERR_SENT_ID:
        {
            stats->errSent++;
            break;
        }
        case UAL_PEG_ERR_RECV_ID:
        {
            stats->errRecv++;
            break;
        }
        case UAL_PEG_PAUSE_IND_ID:
        {
	    stats->pause++;
	    break;
        }
        case UAL_PEG_RESUME_IND_ID:
        {
	    stats->resume++;
	    break;
	}    
        case UAL_PEG_DATA_SENT_ID:
        {
            stats->dataSent++;
            break;
        }
        case UAL_PEG_DATA_RECV_ID:
        {
            stats->dataRecv++;
            break;
        }
        case UAL_PEG_DAUD_SENT_ID:
        {
            stats->daudSent++;
            break;
        }
        case UAL_PEG_DAUD_RECV_ID:
        {
            stats->daudRecv++;
            break;
        }
        case UAL_PEG_DUNA_SENT_ID:
        {
            stats->dunaSent++;
            break;
        }
        case UAL_PEG_DUNA_RECV_ID:
        {
            stats->dunaRecv++;
            break;
        }
        case UAL_PEG_DAVA_SENT_ID:
        {
            stats->davaSent++;
            break;
        }
        case UAL_PEG_DAVA_RECV_ID:
        {
            stats->davaRecv++;
            break;
        }
        case UAL_PEG_SCON_SENT_ID:
        {
            stats->sconSent++;
            break;
        }
        case UAL_PEG_SCON_RECV_ID:
        {
            stats->sconRecv++;
            break;
        }
        case UAL_PEG_DRST_SENT_ID:
        {
            stats->drstSent++;
            break;
        }
        case UAL_PEG_DRST_RECV_ID:
        {
            stats->drstRecv++;
            break;
        }
        case UAL_PEG_DUPU_SENT_ID:
        {
            stats->dupuSent++;
            break;
	}    
        case UAL_PEG_DUPU_RECV_ID:
        {
            stats->dupuRecv++;
            break;
        }
	default:
	{
	    break;
	}    
    }
    return ITS_SUCCESS;
}


UALDLLAPI ITS_INT
UAL_GetPegInfo(ITS_USHORT trid, UAL_PEG_ID which, ITS_INT *value,
               SCTP_PAYLOAD ptype)
{
    ITS_INT ret = ITS_SUCCESS;
    UAL_MIB_STATS *tmp = NULL;

    if (value == NULL)
    {
        ret = ITS_ENOMEM;
    }
    else
    {
        if (ptype == SCTP_PAYLOAD_M3UA)
        {
            if (which < UAL_PEG_PAUSE_IND_ID)
            {
                return (ITS_ENOTFOUND);
            }
        }
        else
        {
            if (which >= UAL_PEG_PAUSE_IND_ID)
            {
                return (ITS_ENOTFOUND);
            }
        }

        tmp = ualpeglist_getStats(trid);

        if (tmp)
        {
            switch (which)
            {
            default:
            case UAL_PEG_INVALID_ID:
                ret = ITS_ENOTFOUND;
                break;

            case UAL_PEG_UP_SENT_ID:
                *value = tmp->aspUpSent;
                break;

            case UAL_PEG_UP_RECV_ID:
                *value = tmp->aspUpRecv;
                break;

            case UAL_PEG_UPACK_SENT_ID:
                *value = tmp->aspUpAckSent;
                break;

            case UAL_PEG_UPACK_RECV_ID:
                *value = tmp->aspUpAckRecv;
                break;

            case UAL_PEG_DN_SENT_ID:
                *value = tmp->aspDnSent;
                break;

            case UAL_PEG_DN_RECV_ID:
                *value = tmp->aspDnRecv;
                break;

            case UAL_PEG_DNACK_SENT_ID:
                *value = tmp->aspDnAckSent;
                break;

            case UAL_PEG_DNACK_RECV_ID:
                *value = tmp->aspDnAckRecv;
                break;

            case UAL_PEG_AC_SENT_ID:
                *value = tmp->aspAcSent;
                break;

            case UAL_PEG_AC_RECV_ID:
                *value = tmp->aspAcRecv;
                break;

            case UAL_PEG_ACACK_SENT_ID:
                *value = tmp->aspAcAckSent;
                break;

            case UAL_PEG_ACACK_RECV_ID:
                *value = tmp->aspAcAckRecv;
                break;

            case UAL_PEG_IA_SENT_ID:
                *value = tmp->aspIaSent;
                break;

            case UAL_PEG_IA_RECV_ID:
                *value = tmp->aspIaRecv;
                break;

            case UAL_PEG_IAACK_SENT_ID:
                *value = tmp->aspIaAckSent;
                break;

            case UAL_PEG_IAACK_RECV_ID:
                *value = tmp->aspIaAckRecv;
                break;

            case UAL_PEG_NOTIFY_SENT_ID:
                *value = tmp->notifySent;
                break;

            case UAL_PEG_NOTIFY_RECV_ID:
                *value = tmp->notifyRecv;
                break;

            case UAL_PEG_REG_REQ_SENT_ID:
                *value = tmp->regReqSent;
                break;

            case UAL_PEG_REG_REQ_RECV_ID:
                *value = tmp->regReqRecv;
                break;

            case UAL_PEG_REG_RSP_SENT_ID:
                *value = tmp->regRspSent;
                break;

            case UAL_PEG_REG_RSP_RECV_ID:
                *value = tmp->regRspRecv;
                break;

            case UAL_PEG_DEREG_REQ_SENT_ID:
                *value = tmp->deregReqSent;
                break;

            case UAL_PEG_DEREG_REQ_RECV_ID:
                *value = tmp->deregReqRecv;
                break;

            case UAL_PEG_DEREG_RSP_SENT_ID:
                *value = tmp->deregRspSent;
                break;

            case UAL_PEG_DEREG_RSP_RECV_ID:
                *value = tmp->deregRspRecv;
                break;

            case UAL_PEG_ERR_SENT_ID:
                *value = tmp->errSent;
                break;

            case UAL_PEG_ERR_RECV_ID:
                *value = tmp->errRecv;
                break;

            case UAL_PEG_PAUSE_IND_ID:
                *value = tmp->pause;
                break;
            
            case UAL_PEG_RESUME_IND_ID:
                *value = tmp->resume;
                break;

            case UAL_PEG_DATA_SENT_ID:
                *value = tmp->dataSent;
                break;

            case UAL_PEG_DATA_RECV_ID:
                *value = tmp->dataRecv;
                break;

            case UAL_PEG_DAUD_SENT_ID:
                *value = tmp->daudSent;
                break;

            case UAL_PEG_DAUD_RECV_ID:
                *value = tmp->daudRecv;
                break;

            case UAL_PEG_DUNA_SENT_ID:
                *value = tmp->dunaSent;
                break;

            case UAL_PEG_DUNA_RECV_ID:
                *value = tmp->dunaRecv;
                break;

            case UAL_PEG_DAVA_SENT_ID:
                *value = tmp->davaSent;
                break;

            case UAL_PEG_DAVA_RECV_ID:
                *value = tmp->davaRecv;
                break;

            case UAL_PEG_SCON_SENT_ID:
                *value = tmp->sconSent;
                break;

            case UAL_PEG_SCON_RECV_ID:
                *value = tmp->sconRecv;
                break;

            case UAL_PEG_DRST_SENT_ID:
                *value = tmp->drstSent;
                break;

            case UAL_PEG_DRST_RECV_ID:
                *value = tmp->drstRecv;
                break;

            case UAL_PEG_DUPU_SENT_ID:
                *value = tmp->dupuSent;
                break;

            case UAL_PEG_DUPU_RECV_ID:
                *value = tmp->dupuRecv;
                break;
            }
        }
        else
        {
            UAL_ERROR(("UAL_GetPegInfo: Invalid transportID = %x\n",
                        trid));
            ret = ITS_EENDOFLIST;
        }
    }
    return ret;
}


UALDLLAPI ITS_INT
UAL_GetAllPegInfo(ITS_USHORT trid, UAL_MIB_STATS *value)
{
    UAL_MIB_STATS* tmp =  NULL;

    tmp = ualpeglist_getStats(trid);

    if (!tmp)
    {
        UAL_ERROR(("UAL_GetAllPegInfo: Invalid transportID = %x\n",
                    trid));
        return (ITS_ENOTFOUND);
    }

    *value = *tmp;

    return ITS_SUCCESS;
}


UALDLLAPI ITS_INT
UAL_ClearPegInfo(ITS_USHORT trid, UAL_PEG_ID which)
{
    ITS_INT ret = ITS_SUCCESS;
    UAL_MIB_STATS *tmp = NULL;

    tmp = ualpeglist_getStats(trid);

    if (tmp)
    {
        switch (which)
        {
        default:
        case UAL_PEG_INVALID_ID:
            ret = ITS_ENOTFOUND;
            break;

        case UAL_PEG_UP_SENT_ID:
            tmp->aspUpSent = 0;
            break;

        case UAL_PEG_UP_RECV_ID:
            tmp->aspUpRecv = 0;
            break;

        case UAL_PEG_UPACK_SENT_ID:
            tmp->aspUpAckSent = 0;
            break;

        case UAL_PEG_UPACK_RECV_ID:
            tmp->aspUpAckRecv = 0;
            break;

        case UAL_PEG_DN_SENT_ID:
            tmp->aspDnSent = 0;
            break;

        case UAL_PEG_DN_RECV_ID:
            tmp->aspDnRecv = 0;
            break;

        case UAL_PEG_DNACK_SENT_ID:
            tmp->aspDnAckSent = 0;
            break;

        case UAL_PEG_DNACK_RECV_ID:
            tmp->aspDnAckRecv = 0;
            break;

        case UAL_PEG_AC_SENT_ID:
            tmp->aspAcSent = 0;
            break;

        case UAL_PEG_AC_RECV_ID:
            tmp->aspAcRecv = 0;
            break;

        case UAL_PEG_ACACK_SENT_ID:
            tmp->aspAcAckSent = 0;
            break;

        case UAL_PEG_ACACK_RECV_ID:
            tmp->aspAcAckRecv = 0;
            break;

        case UAL_PEG_IA_SENT_ID:
            tmp->aspIaSent = 0;
            break;

        case UAL_PEG_IA_RECV_ID:
            tmp->aspIaRecv = 0;
            break;

         case UAL_PEG_IAACK_SENT_ID:
            tmp->aspIaAckSent = 0;
            break;

         case UAL_PEG_IAACK_RECV_ID:
            tmp->aspIaAckRecv = 0;
            break;

        case UAL_PEG_NOTIFY_SENT_ID:
            tmp->notifySent = 0;
            break;

        case UAL_PEG_NOTIFY_RECV_ID:
            tmp->notifyRecv = 0;
            break;

        case UAL_PEG_REG_REQ_SENT_ID:
            tmp->regReqSent = 0;
            break;

        case UAL_PEG_REG_REQ_RECV_ID:
            tmp->regReqRecv = 0;
            break;

        case UAL_PEG_REG_RSP_SENT_ID:
            tmp->regRspSent = 0;
            break;

        case UAL_PEG_REG_RSP_RECV_ID:
            tmp->regRspRecv = 0;
            break;

        case UAL_PEG_DEREG_REQ_SENT_ID:
            tmp->deregReqSent = 0;
            break;

        case UAL_PEG_DEREG_REQ_RECV_ID:
            tmp->deregReqRecv = 0;
            break;

        case UAL_PEG_DEREG_RSP_SENT_ID:
            tmp->deregRspSent = 0;
            break;

        case UAL_PEG_DEREG_RSP_RECV_ID:
            tmp->deregRspRecv = 0;
            break;

        case UAL_PEG_ERR_SENT_ID:
            tmp->errSent = 0;
            break;

        case UAL_PEG_ERR_RECV_ID:
            tmp->errRecv = 0;
            break;

        case UAL_PEG_PAUSE_IND_ID:
            tmp->pause = 0;
            break;

        case UAL_PEG_RESUME_IND_ID:
            tmp->resume = 0;
            break;

        case UAL_PEG_DATA_SENT_ID:
            tmp->dataSent = 0;
            break;

        case UAL_PEG_DATA_RECV_ID:
            tmp->dataRecv = 0;
            break;

        case UAL_PEG_DAUD_SENT_ID:
            tmp->daudSent = 0;
            break;

        case UAL_PEG_DAUD_RECV_ID:
            tmp->daudRecv = 0;
            break;

        case UAL_PEG_DUNA_SENT_ID:
            tmp->dunaSent = 0;
            break;

        case UAL_PEG_DUNA_RECV_ID:
            tmp->dunaRecv = 0;
            break;

        case UAL_PEG_DAVA_SENT_ID:
            tmp->davaSent = 0;
            break;

        case UAL_PEG_DAVA_RECV_ID:
            tmp->davaRecv = 0;
            break;

        case UAL_PEG_SCON_SENT_ID:
            tmp->sconSent = 0;
            break;

        case UAL_PEG_SCON_RECV_ID:
            tmp->sconRecv = 0;
            break;

        case UAL_PEG_DRST_SENT_ID:
            tmp->drstSent = 0;
            break;

        case UAL_PEG_DRST_RECV_ID:
            tmp->drstRecv = 0;
            break;

        case UAL_PEG_DUPU_SENT_ID:
            tmp->dupuSent = 0;
            break;

        case UAL_PEG_DUPU_RECV_ID:
            tmp->dupuRecv = 0;
            break;
        }
    }
    else
    {
        UAL_ERROR(("UAL_ClearPegInfo: Invalid transportID = %x\n",
                    trid));
        ret = ITS_EENDOFLIST;
    }

    return ret;
}


UALDLLAPI ITS_INT
UAL_ClearAllPegInfo(ITS_USHORT trid, SCTP_PAYLOAD ptype)
{
    ITS_USHORT appMode;
    UAL_MIB_STATS *tmp = NULL;

    tmp = ualpeglist_getStats(trid);

    if (tmp)
    {
        appMode =  tmp->appMode;

        if (ptype == SCTP_PAYLOAD_M3UA)
        {

            /*UAL_PEG_PAUSE_IND_ID*/
            tmp->pause = 0;

            /*UAL_PEG_RESUME_IND_ID*/
            tmp->resume = 0;

            /*UAL_PEG_DATA_SENT_ID*/
            tmp->dataSent = 0;

            /*UAL_PEG_DATA_RECV_ID*/
            tmp->dataRecv = 0;

            /*UAL_PEG_DAUD_SENT_ID*/
            tmp->daudSent = 0;

            /*UAL_PEG_DAUD_RECV_ID*/
            tmp->daudRecv = 0;

            /*UAL_PEG_DUNA_SENT_ID*/
            tmp->dunaSent = 0;

            /*UAL_PEG_DUNA_RECV_ID*/
            tmp->dunaRecv = 0;

            /*UAL_PEG_DAVA_SENT_ID*/
            tmp->davaSent = 0;

            /*UAL_PEG_DAVA_RECV_ID*/
            tmp->davaRecv = 0;

            /*UAL_PEG_SCON_SENT_ID*/
            tmp->sconSent = 0;

            /*UAL_PEG_SCON_RECV_ID*/
            tmp->sconRecv = 0;

            /*UAL_PEG_DRST_SENT_ID*/
            tmp->drstSent = 0;

            /*UAL_PEG_DRST_RECV_ID*/
            tmp->drstRecv = 0;

            /*UAL_PEG_DUPU_SENT_ID*/
            tmp->dupuSent = 0;

            /*UAL_PEG_DUPU_RECV_ID*/
            tmp->dupuRecv = 0;
        }
        else
        {
            /*UAL_PEG_UP_SENT_ID*/
            tmp->aspUpSent = 0;
            
            /*UAL_PEG_UP_RECV_ID*/
            tmp->aspUpRecv = 0;
            
            /*UAL_PEG_UPACK_SENT_ID*/
            tmp->aspUpAckSent = 0;
            
            /*UAL_PEG_UPACK_RECV_ID*/
            tmp->aspUpAckRecv = 0;
            
            /*UAL_PEG_DN_SENT_ID*/
            tmp->aspDnSent = 0;
            
            /*UAL_PEG_DN_RECV_ID*/
            tmp->aspDnRecv = 0;

            /*UAL_PEG_DNACK_SENT_ID*/
            tmp->aspDnAckSent = 0;

            /*UAL_PEG_DNACK_RECV_ID*/
            tmp->aspDnAckRecv = 0;

            /*UAL_PEG_AC_SENT_ID*/
            tmp->aspAcSent = 0;

            /*UAL_PEG_AC_RECV_ID*/
            tmp->aspAcRecv = 0;

            /*UAL_PEG_ACACK_SENT_ID*/
            tmp->aspAcAckSent = 0;

            /*UAL_PEG_ACACK_RECV_ID*/
            tmp->aspAcAckRecv = 0;

            /*UAL_PEG_IA_SENT_ID*/
            tmp->aspIaSent = 0;

            /*UAL_PEG_IA_RECV_ID*/
            tmp->aspIaRecv = 0;

            /*UAL_PEG_IAACK_SENT_ID*/
            tmp->aspIaAckSent = 0;

            /*UAL_PEG_IAACK_RECV_ID*/
            tmp->aspIaAckRecv = 0;

            /*UAL_PEG_NOTIFY_SENT_ID*/
            tmp->notifySent = 0;

            /*UAL_PEG_NOTIFY_RECV_ID*/
            tmp->notifyRecv = 0;

            /*UAL_PEG_REG_REQ_SENT_ID*/
            tmp->regReqSent = 0;

            /*UAL_PEG_REG_REQ_RECV_ID*/
            tmp->regReqRecv = 0;

            /*UAL_PEG_REG_RSP_SENT_ID*/
            tmp->regRspSent = 0;

            /*UAL_PEG_REG_RSP_RECV_ID*/
            tmp->regRspRecv = 0;

            /*UAL_PEG_DEREG_REQ_SENT_ID*/
            tmp->deregReqSent = 0;

            /*UAL_PEG_DEREG_REQ_RECV_ID*/
            tmp->deregReqRecv = 0;

            /*UAL_PEG_DEREG_RSP_SENT_ID*/
            tmp->deregRspSent = 0;

            /*UAL_PEG_DEREG_RSP_RECV_ID*/
            tmp->deregRspRecv = 0;

            /*UAL_PEG_ERR_SENT_ID*/
            tmp->errSent = 0;

            /*UAL_PEG_ERR_RECV_ID*/
            tmp->errRecv = 0;
        }

        tmp->transportID = trid;
        tmp->appMode = appMode;

        return (ITS_SUCCESS);
    }
    UAL_ERROR(("UAL_ClearAllPegInfo: Invalid transportID = %x\n",
                trid));

    return ITS_ENOTFOUND;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UALDLLAPI int
SendASPActive(RK_Context *rCtxt)
{
    int ret = ITS_SUCCESS;
    ITS_UAL_IE m3uaIES[32];
    ITS_EVENT evt;

    ITS_EVENT_INIT(&evt, ITS_FIRST_USER_SRC, 256);
    evt.src = ITS_FIRST_USER_SRC;

    m3uaIES[0].param_id = UAL_PRM_MSG_HDR;
    m3uaIES[0].param_length =  sizeof(UAL_MSG_HDR);
    m3uaIES[0].param_data.msgHeader.msgClass = UAL_CLASS_ASPTM;
    m3uaIES[0].param_data.msgHeader.msgType = UAL_MSG_ASPAC;
    m3uaIES[0].param_data.msgHeader.version = UAL_GL_VERSION;
    m3uaIES[0].param_data.msgHeader.reserved = 0x00;

    m3uaIES[1].param_id = UAL_PRM_TRAFFIC_MODE;
    m3uaIES[1].param_length = sizeof(UAL_TRAFFIC_MODE);
    m3uaIES[1].param_data.trafMode.tm = rCtxt->trafficMode;

    m3uaIES[2].param_id = UAL_PRM_ROUT_CTX;

    ret = UAL_EncodeRoutingContext(m3uaIES[2].param_data.rCtxt.rCtxt,
                                   &m3uaIES[2].param_length,
                                   &rCtxt->rCtxt, 1);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Encoding Routing Ctxt"));
    }

    ret = UAL_EncodeMsg(m3uaIES, 3, &evt, &UAL_ASPAC_Desc);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Encode ASP_Active message"));
    }
    return TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UALDLLAPI int
SendASPInactive(ITS_UINT rCtxt)
{
    int ret = ITS_SUCCESS;
    ITS_UAL_IE m3uaIES[32];
    ITS_EVENT evt;

    ITS_EVENT_INIT(&evt, ITS_FIRST_USER_SRC, 256);
    evt.src = ITS_FIRST_USER_SRC;

    m3uaIES[0].param_id = UAL_PRM_MSG_HDR;
    m3uaIES[0].param_length =  sizeof(UAL_MSG_HDR);
    m3uaIES[0].param_data.msgHeader.msgClass = UAL_CLASS_ASPTM;
    m3uaIES[0].param_data.msgHeader.msgType = UAL_MSG_ASPIA;
    m3uaIES[0].param_data.msgHeader.version = UAL_GL_VERSION;
    m3uaIES[0].param_data.msgHeader.reserved = 0x00;

    m3uaIES[1].param_id = UAL_PRM_TRAFFIC_MODE;
    m3uaIES[1].param_length = sizeof(UAL_TRAFFIC_MODE);
    m3uaIES[1].param_data.trafMode.tm = UAL_OVERRIDE_MODE;

    m3uaIES[2].param_id = UAL_PRM_ROUT_CTX;

    ret = UAL_EncodeRoutingContext(m3uaIES[2].param_data.rCtxt.rCtxt,
                                   &m3uaIES[2].param_length,
                                   &rCtxt, 1);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Encoding Routing Ctxt"));
    }

    ret = UAL_EncodeMsg(m3uaIES, 3, &evt, &UAL_ASPIA_Desc);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error Encode ASP_Inactive message"));
    }
    return TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UALDLLAPI int
UAL_GetRoutingContexts(RK_Context *rCtxts[], ITS_OCTET *rCount)
{
   ITS_USHORT trids[UAL_MAX_NUM_ASSOC];

   int ret, num_trids = 0;
   ASP_Entry* aspRec = NULL;
   int i = 0;
   ITS_BOOLEAN foundCtxt = ITS_FALSE;
   
   *rCount=0;
   ret = ASPTable_GetAllTransportIds(trids, UAL_MAX_NUM_ASSOC,
                                     &num_trids);
   if (ret == ITS_SUCCESS)
   {
      for(i = 0 ; i < num_trids; i++)
      {
          ret = ASPTable_FindEntry(trids[i], &aspRec);
          if(ret == ITS_SUCCESS)
          {
              RKListNode* rk =  RKList_Iterate(aspRec->asList);

              for(; rk; rk = RKList_Iterate(NULL))
              {    
                   rCtxts[(*rCount)++] = rk->entry;
                   foundCtxt = ITS_TRUE;
              }
           }
       }
   }
   else
   {
       UAL_CRITICAL(("Failed to get any association"));
   }
    
   if (foundCtxt == ITS_FALSE)
   {
      return !ITS_SUCCESS;   
   }
   return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Routing Key value more than 255 related function.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-01-2008   BugId: 1541     Propagated Bridgeport Isse.
 *                                          Support of Routing Key value 
 *                                          more than 255.                                          
 *
 *  See Also:
 ****************************************************************************/
typedef struct CheckRoutingInfoValid_hash_iterative_proc_input
{
    ITS_UINT*     rkey;
	RK_Context*   asCtxt;
} CheckRoutingInfoValid_hash_iterative_proc_input;

static int
CheckRoutingInfoValid_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out);

int
UAL_CheckRoutingInfoValid(ITS_UINT *rkey, RK_Context* asCtxt)
{
    ITS_INT dummy_ret, ret = !ITS_SUCCESS;
	ITS_BOOLEAN found = ITS_FALSE;
    CheckRoutingInfoValid_hash_iterative_proc_input in;	
	in.rkey   = rkey;
	in.asCtxt = asCtxt;


    dummy_ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, &in,
		       &found, CheckRoutingInfoValid_hash_iterative_proc);

	if(found == ITS_TRUE)
	{
		ret = ITS_SUCCESS;
	}

    return ret;
}

static int
CheckRoutingInfoValid_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
    RK_Context* ctxt = (RK_Context*)data;
	ITS_UINT *rkey = ((CheckRoutingInfoValid_hash_iterative_proc_input *)in)->rkey;
	RK_Context* asCtxt = ((CheckRoutingInfoValid_hash_iterative_proc_input *)in)->asCtxt;
	ITS_INT ret = !ITS_SUCCESS;

	if(ctxt != NULL)
	{
		/* match dpc */
		if (asCtxt->asInfo.dpc == ctxt->asInfo.dpc)
		{
			if (asCtxt->asInfo.style == ROUTE_DPC_SIO &&
				ctxt->asInfo.style == ROUTE_DPC_NI)
			{
				/* match ni */
				if((asCtxt->asInfo.criteria.sio & ROUTE_NI_MASK)
					== (ctxt->asInfo.criteria.sio))
				{
					if (asCtxt->trafficMode != ctxt->trafficMode)
					{
						UAL_ERROR(("Trying to register to existing "
								   "routing key with different traffic "
								   "mode\n"));
					}
					else
					{
						UAL_DEBUG(("Routing Key already exists\n"));
					}

					*rkey = ctxt->rCtxt;
					*((ITS_BOOLEAN *)out) = ITS_TRUE;
					// return failure to make Iterate function break from for loop
					return (!ITS_SUCCESS);
				}
			}

			if (asCtxt->asInfo.style == ctxt->asInfo.style &&
				(asCtxt->asInfo.style == ROUTE_DPC_NI ||
				 asCtxt->asInfo.style == ROUTE_DPC_SIO))
			{
				/* match ni or sio */
				if((asCtxt->asInfo.criteria.sio) == 
				   (ctxt->asInfo.criteria.sio))
				{
					if (asCtxt->trafficMode != ctxt->trafficMode)
					{
						UAL_ERROR(("Trying to register to existing "
								   "routing key with different traffic "
								   "mode\n"));
					}
					else
					{
						UAL_DEBUG(("Routing Key already exists\n"));
					}

					*rkey = ctxt->rCtxt;
					*((ITS_BOOLEAN *)out) = ITS_TRUE;
					// return failure to make Iterate function break from for loop
					return (!ITS_SUCCESS);
				}
			}
		}
	}
	return ret;
}

/****************************************************************
 * purpose: This function is used to add an entry for 'timerVal'
 *          to the AuditTimersTable HASH_Table with pc as the key
 *
 * Parameters:
 *     pc[in], this is the affected PC and is used a a key to store 
 *         the timer value.
 *     timerVal[in], The value of the timer that is started 
 * return value:
 *     ITS_SUCCESS on successful addition
 ***************************************************************/
UALDLLAPI ITS_INT 
AuditTimersTable_AddEntry(ITS_UINT pc, ITS_SERIAL *timerVal)
{
    int ret = ITS_SUCCESS;
    ITS_SERIAL* entry = NULL;

    if(timerVal != NULL)
    {
        entry = (ITS_SERIAL *)calloc(1, sizeof(ITS_SERIAL));
        memcpy(entry, timerVal, sizeof(ITS_SERIAL));
        ret = HASH_AddEntry(__UAL_Audit_Timer_Table, UAL_HASH_RID, pc, 
                       (ITS_POINTER)entry);
    }
    return ret;

}


/****************************************************************
 * purpose: This function is used to find entry in AuditTimersTable,
 *          for 'pcContext' and populate it in 'timerVal'
 *
 * Parameters:
 *     pcContext[in], this is the key/context for which the entry needs 
 *                to be searched for, in AuditTimersTable
 *     timerVal[out], will be filled in with value if an 
 *               entry for 'pcContext' exists in the AuditTimersTable.
 * return value:
 *     ITS_SUCCESS on successful addition
 ***************************************************************/
UALDLLAPI int
AuditTimersTable_FindEntry(ITS_UINT pcContext, ITS_SERIAL** timerVal)
{
    return HASH_FindEntry(__UAL_Audit_Timer_Table, UAL_HASH_RID, 
                         pcContext, (ITS_POINTER*)timerVal);
}


/****************************************************************
 * purpose: This function is used to remove an entry for 'pcContext'
 *          from the AuditTimersTable
 *
 * Parameters:
 *     pcContext[in], this is the key/context for which the entry needs
 *                to be removed from AuditTimersTable
 * return value:
 *     ITS_SUCCESS on successful removal
 ***************************************************************/
UALDLLAPI int 
AuditTimersTable_RemoveEntry(ITS_USHORT pcContext)
{
    int ret = ITS_SUCCESS;
    ITS_POINTER data;

    ret = HASH_FindEntry(__UAL_Audit_Timer_Table, UAL_HASH_RID, pcContext, &data);

    if(ret == ITS_SUCCESS)
    {
        ret = HASH_DeleteEntry(__UAL_Audit_Timer_Table, UAL_HASH_RID, pcContext);
        free(data);
    }

    return ret;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
UALDLLAPI
int UAL_UpdateASListToASP (ITS_UINT rCtxt)
{
    int ret = 0;
    int i = 0;
    RK_Context*  rk_ctxt = NULL;

    rk_ctxt = RKManager_FindEntry(rCtxt);

    if (rk_ctxt != NULL)
    {
        ITS_USHORT trids[UAL_MAX_NUM_ASSOC];
        int num_trids = 0;
        RKListNode entry;

        entry.rCtxt = rk_ctxt->rCtxt;
        entry.entry = rk_ctxt;
        entry.entry->isMember = ITS_TRUE;

        ret = ASPTable_GetAllTransportIds(trids, UAL_MAX_NUM_ASSOC,
                                          &num_trids);

        for(i = 0 ; i < num_trids; i++)
        {
            ASP_Entry* aspRec = NULL;

            ret = ASPTable_FindEntry(trids[i], &aspRec);

            if (ret == ITS_SUCCESS && aspRec != NULL)
            {
                //Adding internally taking care of duplicate stuff
                ret = RKList_AddEntry(aspRec->asList, &entry);
            }
        }
     }

    return ret;
}
