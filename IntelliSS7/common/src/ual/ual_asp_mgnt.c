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
 *  ID: $Id: ual_asp_mgnt.c,v 9.21.2.4.2.2.40.2.2.5 2015/01/22 15:08:25 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_asp_mgnt.c,v $
 *  LOG: Revision 9.21.2.4.2.2.40.2.2.5  2015/01/22 15:08:25  jkchaitanya
 *  LOG: changes for aspid issue faced in the HP site
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2.40.2.2.4  2014/12/18 11:26:40  jkchaitanya
 *  LOG: changes for invalid read
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2.40.2.2.3  2014/12/03 03:10:28  jkchaitanya
 *  LOG: changes for invalid read
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2.40.2.2.2  2014/11/27 05:17:32  jkchaitanya
 *  LOG: chanegs to send ASP Active from IPSP client(MSC)
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2.40.2.2.1  2014/11/21 06:37:47  jkchaitanya
 *  LOG: changes for IPSP configurations
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2.40.2  2014/11/17 04:59:49  jkchaitanya
 *  LOG: changes for HA Bug Fixes
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2.40.1  2014/10/27 08:18:49  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.2  2010/06/28 14:25:54  haltaf
 *  LOG: Fix for issue id #3077, #3088
 *  LOG:
 *  LOG: Revision 9.21.2.4.2.1  2010/06/10 13:14:58  chandrashekharbs
 *  LOG: Fix for Issue id 2946
 *  LOG:
 *  LOG: Revision 9.21.2.4  2009/10/05 08:30:14  kramesh
 *  LOG: ASP - ACTIVE does not contain RC. Issue 2374.
 *  LOG:
 *  LOG: Revision 9.21.2.3  2009/04/09 08:15:56  ssodhi
 *  LOG: Handling SCTP connection down indication
 *  LOG:
 *  LOG: Revision 9.21.2.2  2009/03/24 04:14:39  ssodhi
 *  LOG: SG was not sending Notify to standby asp after sending ASP UP ACK - fixed
 *  LOG:
 *  LOG: Revision 9.21.2.1  2009/03/12 09:03:00  kramesh
 *  LOG: Correct handling of ASP INACTIVE ACK & ASP DOWN ACK.
 *  LOG:
 *  LOG: Revision 9.21  2008/07/17 14:49:20  ssingh
 *  LOG: Warning removal for Solaris Compilation
 *  LOG:
 *  LOG: Revision 9.20  2008/07/16 11:57:55  skatta
 *  LOG: Fix for issue #1050 - processing of ASP ACTIVE message with out optional parameters and removing  ual warnings
 *  LOG:
 *  LOG: Revision 9.19  2008/07/03 13:26:00  skatta
 *  LOG: Fix for issue #1043 in whizible
 *  LOG:
 *  LOG: Revision 9.18  2008/06/30 14:04:34  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.17  2008/06/29 15:15:18  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.16  2008/06/20 10:07:02  mshanmugam
 *  LOG: Accelero CGI Phase I:D0150, D0170-D0200, D0230, D0240
 *  LOG:
 *  LOG: Revision 9.15  2008/05/28 13:43:05  kramesh
 *  LOG: Incorrect printing of routing key.
 *  LOG:
 *  LOG: Revision 9.14  2008/05/25 17:08:00  kramesh
 *  LOG: Whizible Bug Id 935. Asp State not changing to INACTIVE during processing
 *  LOG: of Inactive_ack.
 *  LOG: Whizible Bug Id 932. Incorrect Routing Key value printing.
 *  LOG:
 *  LOG: Revision 9.13  2008/05/01 16:16:35  kramesh
 *  LOG: Propagated TCS issue 1034. Error Traces Missing Routing context.
 *  LOG: Propagated Bridgeport Isse 1541. Routing key value more than 255.
 *  LOG:
 *  LOG: Revision 9.12  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.11.2.17  2007/07/27 08:59:02  pspl
 *  LOG: Changed for loop counter to send ASP active message in function
 *  LOG: UpdateAsAndAspStates() to fix a core dump. (Vipul)
 *  LOG:
 *  LOG: Revision 9.11.2.16  2007/06/12 08:57:07  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - added state change code when UAL_ERR_INV_ROUT_CTXT and UAL_ERR_UNSU_THM received
 *  LOG: - Added state checking before sending ASP_ACTIVE, in handling UAL_ST_ASP_FAILURE
 *  LOG: - added code to handle stray INACTIVE_ACK messages
 *  LOG: - misc changes
 *  LOG:
 *  LOG: Revision 9.11.2.15  2007/06/05 10:46:56  pspl
 *  LOG: (PSPL, abhijeet) replaced UAL_FATAL with UAL_CRITICAL
 *  LOG:
 *  LOG: Revision 9.11.2.14  2007/06/05 05:57:10  pspl
 *  LOG: (PSPL, abhijeet) removed unused UAL_SendASP_ACTIVE(), and few misc changes
 *  LOG:
 *  LOG: Revision 9.11.2.13  2007/05/29 14:33:46  pspl
 *  LOG: -(PSPL,Manish) Fixed looping code for dumping AS Table
 *  LOG:
 *  LOG: Revision 9.11.2.12  2007/05/29 08:25:59  pspl
 *  LOG: (PSPL, abhijeet) changes to the comment to reflect the actual logic
 *  LOG:
 *  LOG: Revision 9.11.2.11  2007/05/29 07:13:44  pspl
 *  LOG: - Removed breaking out of loop for sending NOTIFY (with routing context)
 *  LOG:   for AS_INACTIVE in UpdateStaticConfigOfAS().
 *  LOG:   Added one extra local(to inner for loop) binary flag.
 *  LOG: - Loop control changed for checking dulplicate aspId on entire static array,
 *  LOG:   instead of only __UAL_AS_Manager.numEntries+1 in ProcessASP_UP().
 *  LOG: (Vipul)
 *  LOG:
 *  LOG: Revision 9.11.2.10  2007/05/28 10:46:39  pspl
 *  LOG: - Added a function deriveASPStateFromRCtxt(), to get the state for the
 *  LOG:   ASP depending on the individual states of the rCtxt. Fixed bug 121
 *  LOG: - added a null check to avoid core dump for 2sg + 2as + 1asp case.
 *  LOG: (Vipul)
 *  LOG:
 *  LOG: Revision 9.11.2.9  2007/05/25 07:15:45  pspl
 *  LOG: (PSPL,Manish)
 *  LOG: - UAL_GetRoutingKeys() is changed to extract RK_Contexts instead of rKeys, and renamed
 *  LOG: - Hardcoading of UAL_OVERRIDE_MODE removed
 *  LOG: - Changed the Parameter type of SendASPActive()
 *  LOG:
 *  LOG: Revision 9.11.2.8  2007/05/24 09:00:00  pspl
 *  LOG: (PSPL, abhijeet) Added code to check presence of an ASP with same aspId by
 *  LOG:                  iterating through the aspList of the all the AS's.
 *  LOG:
 *  LOG: Revision 9.11.2.7  2007/05/23 10:32:08  pspl
 *  LOG: (PSPL, abhijeet) misc changes in the trace message
 *  LOG:
 *  LOG: Revision 9.11.2.6  2007/05/21 10:20:27  pspl
 *  LOG: (PSPL, abhijeet) Changes to take care of the UP_ACK messages in DOWN/INACTIVE states of ASP
 *  LOG:
 *  LOG: Revision 9.11.2.5  2007/05/03 09:36:31  pspl
 *  LOG: (PSPL, abhijeet) state changed for ASP
 *  LOG:
 *  LOG: Revision 9.11.2.4  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.11.2.3  2007/04/30 11:17:37  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - SendASPActive() now being called when Notify for ASP_DOWN received
 *  LOG: - misc trace msg changes
 *  LOG:
 *  LOG: Revision 9.11.2.2  2007/04/26 06:55:57  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - changes for handling erros from DecodeMsg()
 *  LOG: - setting of data in timer context moved before
 *  LOG:   the Transport_Putevent(), in Sendxxx() for ASP_UP and ASP_ACTIVE
 *  LOG: - raised 4026 alarm (for invalid msgType)
 *  LOG:
 *  LOG: Revision 9.11.2.1  2007/04/05 14:48:23  pspl
 *  LOG: ackTimer[indexing] changed from trafficMode value to be msgType value being used
 *  LOG:
 *  LOG: Revision 9.11  2007/01/10 11:15:11  yranade
 *  LOG: Merge changes from 6.5.3 and Lucent branches
 *  LOG:
 *  LOG: Revision 9.10  2005/12/09 20:57:16  cbashyam
 *  LOG: Bug fixes for Bugs : 2479, 2480
 *  LOG:
 *  LOG: Revision 9.9  2005/12/08 03:34:46  clin
 *  LOG: fix bug #2482 and trace text.
 *  LOG:
 *  LOG: Revision 9.8  2005/12/06 14:40:14  cbashyam
 *  LOG: Bug fixes for Bug ID : 2533
 *  LOG:
 *  LOG: Revision 9.7  2005/11/30 23:48:14  clin
 *  LOG: change ITS_TRACE to UAL trace. and changes related to bug #2576
 *  LOG:
 *  LOG: Revision 9.6  2005/11/23 20:46:35  clin
 *  LOG: fix bug #2481
 *  LOG:
 *  LOG: Revision 9.5  2005/11/23 19:44:09  clin
 *  LOG: fix bug #2531
 *  LOG:
 *  LOG: Revision 9.4  2005/11/09 19:40:39  cbashyam
 *  LOG: Bug fixes for Bug ID : 2457
 *  LOG:
 *  LOG: Revision 9.3  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 *  LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:18  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.10  2005/02/21 10:25:57  adutta
 *  LOG: Fix for Bug#1495
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.9  2005/02/21 10:17:45  adutta
 *  LOG: Fix for bug#1487
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.8  2005/02/21 09:42:18  dsatish
 *  LOG: UpdateStaticConfigOfAS modified.
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.7  2005/01/19 10:20:10  ssingh
 *  LOG: M3UA v2 Changes
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.6  2005/01/07 15:03:05  ssingh
 *  LOG: Changed to enhance ACTIVE-BACKUP redundancy.
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.5  2005/01/06 17:14:24  sbabu
 *  LOG:  ual OAM Changes
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.4  2005/01/06 17:02:50  sbabu
 *  LOG: ual OAM Changes
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.3  2005/01/04 15:09:22  sbabu
 *  LOG: UAL OAM changes
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.2  2004/12/15 16:26:53  dsatish
 *  LOG: Changes propagated from SHIM branch
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1.10.1  2004/12/15 13:11:15  asingh
 *  LOG: separate traces for UAL
 *  LOG:
 *  LOG: Revision 7.4.2.6.2.1  2004/05/03 13:16:05  ssingh
 *  LOG: Bug fixes for #774/784/785/790/792/793/794/803/806/808.
 *  LOG:
 *  LOG: Revision 7.4.2.6  2003/10/22 13:21:11  lbana
 *  LOG: commoit all TCS bug fixes.
 *  LOG:
 *  LOG: Revision 7.4.2.5  2003/10/15 15:30:19  lbana
 *  LOG: clean up...
 *  LOG:
 *  LOG: Revision 7.4.2.4  2003/10/14 20:28:54  lbana
 *  LOG: fix null pointer dereference and also place a check whether we send INACTIVE
 *  LOG: before bringing AS to ACTIVE.
 *  LOG:
 *  LOG: Revision 7.4.2.3  2003/09/12 22:56:09  lbana
 *  LOG: Stop timer for active even when active_ack is received without the TM.
 *  LOG:
 *  LOG: Revision 7.4.2.2  2003/08/04 23:17:34  hcho
 *  LOG: fixes in DUNA/DAVA and propagate CANT_START indication to the user.
 *  LOG:
 *  LOG: Revision 7.4.2.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.4  2002/12/30 17:28:48  lbana
 *  LOG: Propagating bug fixes in PR6.1 to current
 *  LOG:
 *  LOG: Revision 7.3.2.3  2003/03/19 21:47:58  lbana
 *  LOG: added context for the callback manager
 *  LOG:
 *  LOG: Revision 7.3.2.2  2002/12/30 17:01:02  lbana
 *  LOG: Set transport state to true, instead of setting link/linksets
 *  LOG:
 *  LOG: Revision 7.3.2.1  2002/12/26 23:32:26  lbana
 *  LOG: buge fixes in ual in IPSP mode testing
 *  LOG:
 *  LOG: Revision 7.3  2002/11/14 21:32:28  omayor
 *  LOG: Warning removal
 *  LOG:
 *  LOG: Revision 7.2  2002/09/06 21:04:50  yranade
 *  LOG: inline is not a C89 keyword.  Don't use it.
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 6.24  2002/08/26 21:52:56  mmiers
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 6.23  2002/07/24 19:53:42  lbana
 *  LOG: fix bugs in reconnect logic, and get aspinfo element from parser
 *  LOG: extension.
 *  LOG:
 *  LOG: Revision 6.22  2002/07/22 18:41:27  lbana
 *  LOG: make asp active procedure more readable.
 *  LOG:
 *  LOG: Revision 6.21  2002/07/19 20:27:02  ngoel
 *  LOG: correct alarm number
 *  LOG:
 *  LOG: Revision 6.20  2002/07/12 16:09:24  ngoel
 *  LOG: bug fix by lbana
 *  LOG:
 *  LOG: Revision 6.19  2002/07/12 14:59:43  lbana
 *  LOG: get family from asInfi in RK_Context.
 *  LOG:
 *  LOG: Revision 6.18  2002/07/10 22:03:25  lbana
 *  LOG: Get family type from routing key info. and fix in ASP_DOWN_ACK
 *  LOG:
 *  LOG: Revision 6.17  2002/07/10 21:33:43  lbana
 *  LOG: *** empty log message ***
 *  LOG:
 *  LOG: Revision 6.16  2002/07/10 13:29:13  lbana
 *  LOG: removed all warnings
 *  LOG:
 *  LOG: Revision 6.15  2002/07/09 21:19:44  lbana
 *  LOG: Start MML procedures for UALs
 *  LOG:
 *  LOG: Revision 6.14  2002/07/08 18:18:30  ngoel
 *  LOG: add ual alarms
 *  LOG:
 *  LOG: Revision 6.13  2002/06/14 16:07:03  lbana
 *  LOG: Remove the links in on ASP_DOWN too. If last link in linkSet set the state
 *  LOG: to FALSE.
 *  LOG:
 *  LOG: Revision 6.12  2002/06/13 21:52:02  lbana
 *  LOG: Test more than one ASP in override mode... still working on loadshare.
 *  LOG:
 *  LOG: Revision 6.11  2002/06/13 18:40:15  lbana
 *  LOG: Start adding Management callback.
 *  LOG:
 *  LOG: Revision 6.10  2002/06/12 23:01:45  lbana
 *  LOG: Problem in removing the links when receiving ASP Inactive.
 *  LOG:
 *  LOG: Revision 6.9  2002/06/12 19:20:17  lbana
 *  LOG: Put in changes after Henry's comments.
 *  LOG:
 *  LOG: Revision 6.8  2002/05/21 22:13:13  lbana
 *  LOG: more debugging in current
 *  LOG:
 *  LOG: Revision 6.7  2002/05/17 20:20:02  lbana
 *  LOG: first level debugging...
 *  LOG:
 *  LOG: Revision 6.6  2002/05/15 15:37:47  lbana
 *  LOG: need to call LINK_AddLinkInfoToTransport.
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

#include <its_ual.h>
#include <its_link.h>
#include "ual_intern.h"
#include "ual_config_mgnt.h"

#ident "$Id: ual_asp_mgnt.c,v 9.21.2.4.2.2.40.2.2.5 2015/01/22 15:08:25 jkchaitanya Exp $"

#define  NUM_TRAFFIC_MODES 3

#define  TRAFFIC_MODE_OR   0
#define  TRAFFIC_MODE_LS   1
#define  TRAFFIC_MODE_BC   2

#define  MAX_RKEYS_IN_IE   16  /* D0150 - 04-june-08 */

/*
 * For registering ASP on Association up
 */
ITSDLLAPI CALLBACK_Manager    *UAL_ASP_ManagementCallbacks = NULL;

static ITS_INT 
ProcessASP_UP_ACK(ASP_Entry* aspRec, ITS_EVENT* ualEvent, ITS_BOOLEAN flag);
static ITS_INT
ProcessASP_ACTIVE(ASP_Entry* aspRec, ITS_EVENT* ualEvent, ITS_BOOLEAN aspFlag);
static int
UpdateLocalRoutingKeys(ASP_Entry *aspRec, ITS_BOOLEAN isNonMember);

static char* Get_ASCII_UALError(ITS_INT code);

ITS_UINT deriveASPStateFromRCtxt(ASP_Entry *aspRec);

ITS_BOOLEAN UAL_ExecuteConfigCmd(UAL_ConfigPriv info, char **dumpStr);

typedef struct UpdateStaticConfigOfAS_hash_iterative_proc_input
{
    ITS_INT*     aspId;
    ASP_Entry*    aspRec;
    SOCK_IPv4Addr address;
	ITS_BOOLEAN flag;
} UpdateStaticConfigOfAS_hash_iterative_proc_input;

/*typedef struct StoreASPActiveConfigData
{
    ITS_INT*     rKey;
    int          rKeyLen;
    ASP_Entry*   aspRec;
    UAL_TRAFFIC_TYPE mode;
	ITS_BOOLEAN  flag;
} StoreASPActiveConfigData;*/

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
static int
UpdateStaticConfigOfAS_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
    int ret = ITS_SUCCESS;
    RK_Context* ctxt = (RK_Context*)data;

    ITS_BOOLEAN matchFound = ITS_FALSE;
    ASPListNode* aspNode = NULL;
    UpdateStaticConfigOfAS_hash_iterative_proc_input *inputp = NULL;
    ITS_INT*     aspId =   NULL; 
    ASP_Entry*   aspRec =  NULL;
    SOCK_IPv4Addr address = 0;
    ITS_BOOLEAN flag;
    ITS_BOOLEAN aspFound = ITS_FALSE;

    inputp  = (UpdateStaticConfigOfAS_hash_iterative_proc_input *)in;
    aspId   =   inputp->aspId; 
    aspRec  =  inputp->aspRec;
    address = inputp->address;
    flag    = inputp->flag;

    UAL_DEBUG(("ASP ID : %d Flag : %d\n", *aspId, flag));
    aspNode = ASPList_Iterate(ctxt->aspList);
	
	for(;aspNode; aspNode = ASPList_Iterate(NULL))
	{
        UAL_DEBUG(("Inside ASPList For Loop"));

        UAL_DEBUG(("Transport ID in ASP Node : %d\n", aspNode->trId));
        UAL_DEBUG(("ASP ID in ASP Node : %d\n", aspNode->aspInfo.aspid));
		/* no ASPID was found in UP message */
		if (*aspId == -1)
		{
			if (IsAspAddress(aspNode, address, aspId))
			{
			   if (aspNode->state == UAL_ASP_DOWN)
			   {
				   aspFound = ITS_TRUE;
			   }
			}
		}
		else if(aspNode->aspInfo.aspid == *aspId)
		{
			if (aspNode->state == UAL_ASP_DOWN)
			{
				aspFound = ITS_TRUE;
			}
		}

        UAL_DEBUG(("ASP Found Flag %d\n", aspFound));
		if (aspFound)
		{
			RKListNode rknd;

			 /* set the outer flag */
			matchFound = ITS_TRUE;

			/* reset the inner flag */
			aspFound = ITS_FALSE;

			memset(&rknd, 0, sizeof(RKListNode));
			rknd.rCtxt = ctxt->rCtxt;
			rknd.entry = ctxt;

			UAL_ERROR(("ASP State : %d\n", ctxt->state));
			if (ctxt->state == UAL_AS_DOWN)
			{
				ctxt->state = UAL_AS_INACTIVE; 
			}

			ITS_USHORT as_state = UAL_ST_ID_AS_INACTIVE;

			if (ctxt->state == UAL_AS_INACTIVE)
            {
				as_state = UAL_ST_ID_AS_INACTIVE;
            }
			else if (ctxt->state == UAL_AS_ACTIVE)
			{
				as_state = UAL_ST_ID_AS_ACTIVE;
			}
			else if (ctxt->state == UAL_AS_PENDING)
			{
				as_state = UAL_ST_ID_AS_PENDING;
			}
			else
			{
				UAL_ERROR(("Unknown ASP State : %d\n", ctxt->state));
			}

            UAL_DEBUG(("AS State in UpdateStaticConfigOfAS_hash_iterative_pro  %d\n", as_state));

			if (flag) /* Only for remote ASP_UP */
			{
				/* find the current state of AS of this asp and 
				   send that state in the NTFY */
				 ret = UAL_SendNotify(aspRec->trId, 
									 UAL_ST_TYPE_AS_STAT_CHG,
									 as_state, 
									 &ctxt->rCtxt, 1, 0);
				 if (ret != ITS_SUCCESS)
				 {
					UAL_ERROR(("Error sending NTFY, AS_INACTIVE\n"));
				 }

				 UAL_Alarm(4016, __FILE__, __LINE__, "RC %u", ctxt->rCtxt);
			}

			if(aspRec->asList == NULL)
			{
				aspRec->asList = UAL_CreateList();
			}

			RKList_AddEntry(aspRec->asList, &rknd);

			if(aspNode->entry == NULL)
			{
				aspNode->entry = aspRec;
			}

			aspNode->state = UAL_ASP_INACTIVE;
			aspNode->trId  = aspRec->trId;

			break;
		} 
	}

    if (matchFound == ITS_FALSE)
    {
        UAL_ERROR(("NO MATCH FOUND "));
       /* 
        * 1. Do not send errors for local asp up message processing
	*    in IPSP they are fake ones. 
	* 2. We don't have either ip address or aspid match 
	*/
        if (*aspId == -1 && flag) 
        {
           UAL_ERROR(("No AspId or Matching IP address received. \n"));
   
           UAL_SendERR(aspRec->trId, UAL_ERR_ASP_ID_REQUIERED, NULL, 0);

		   return ITS_ENOTFOUND;
        }
    }

    if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
    {
        if (!UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE))
        {
            /* for IPSP dynamic registration */
            aspRec->remoteInfo.aspInfo.aspid = *aspId;
        }
    }

    return ret;
}

int UpdateStaticConfigOfAS(ITS_INT *aspId, ASP_Entry* aspRec, 
                            SOCK_IPv4Addr address, ITS_BOOLEAN flag)
{
    int ret = ITS_SUCCESS;
    UpdateStaticConfigOfAS_hash_iterative_proc_input in;
    in.aspId   = aspId;
    in.aspRec  = aspRec;
    in.address = address;
    in.flag    = flag;
    
    UAL_DEBUG(("ASP ID : %d Flag : %d\n", *aspId, flag));

    ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, &in,
		       NULL, UpdateStaticConfigOfAS_hash_iterative_proc);

    aspRec->aspId = *aspId; /*put aspid in hash table*/
    UAL_DEBUG(("ASPID in UpdateStaticConfigOfAS : %d\n", aspRec->aspId));

    return ret;
}

static ITS_INT 
Process_ErrorMsg(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_INT     ret     = ITS_SUCCESS;
    ITS_INT     ieCount = 0;
    ITS_UAL_IE  ies[ITS_MAX_UAL_IES];
    ITS_INT     errCode = 0;
    int i = 0;
    char* err_string = NULL;

    memset(ies, 0 , ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ERR_Desc);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("Decode UAL_ERROR msg ret val = %d\n", 
                            ret));

        return ret;
    }

    for(; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_ERROR_CODE)
        {
            errCode = ies[i].param_data.errCode.eCode;
            err_string = Get_ASCII_UALError(errCode);
	    
	    /* Handle the specific errors reported and
	     * take care of the state change back to what it was/ would have been */
	    if(errCode == UAL_ERR_UNSU_THM && aspRec->ackTimer[ASP_ACTIVE_MSG] != (ITS_SERIAL)0)
	    {
                TIMERS_CancelTimer(aspRec->ackTimer[ASP_ACTIVE_MSG]);
                aspRec->ackTimer[ASP_ACTIVE_MSG] = (ITS_SERIAL)0;
                memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
	       
	        aspRec->state = deriveASPStateFromRCtxt(aspRec);
	    }
	    else if(errCode == UAL_ERR_INV_ROUT_CTXT)
	    {
	        if(aspRec->ackTimer[ASP_ACTIVE_MSG] != (ITS_SERIAL)0)
		{
                    TIMERS_CancelTimer(aspRec->ackTimer[ASP_ACTIVE_MSG]);
                    aspRec->ackTimer[ASP_ACTIVE_MSG] = (ITS_SERIAL)0;
                    memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
	       
	            aspRec->state = deriveASPStateFromRCtxt(aspRec);
		}
		else if (aspRec->ackTimer[ASP_INACTIVE_MSG] != (ITS_SERIAL)0)
		{
                    TIMERS_CancelTimer(aspRec->ackTimer[ASP_INACTIVE_MSG]);
                    aspRec->ackTimer[ASP_INACTIVE_MSG] = (ITS_SERIAL)0;
                    memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
	       
	            aspRec->state = deriveASPStateFromRCtxt(aspRec);
		}
	      
	    }
            break;
        }
    }

    UAL_ERROR(("UAL_ErrorString = %s\n", err_string));

    UAL_Alarm(4007, __FILE__, __LINE__, "Error %s", err_string);

    UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_ERR_RECV_ID);

    return ret;
}
extern int
SendASPActive_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out);
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

static void
UpdateAsAndAspStates(RK_Context *rctxt, ASP_Entry *aspRec,
	             ASPListNode *asp_nd, UAL_STATUS_TYPE *status)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_NODE_STATE state;
    ITS_Class  redClass;

    UAL_CB_Context cb_ctxt;

    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    switch (status->type)
    {
    case UAL_ST_TYPE_AS_STAT_CHG:
        switch(status->id)
        {
        case UAL_ST_ID_AS_INACTIVE:
            UAL_DEBUG(("State Changed at %s to INACTIVE\n", ITW_STRING));

	    rctxt->state = UAL_AS_INACTIVE;

	    /* set the ASP's state */
	    aspRec->state = deriveASPStateFromRCtxt(aspRec);

	    if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
            {
                UAL_Alarm(4056, __FILE__, __LINE__, 
                          "RC %u", rctxt->rCtxt);
            }
            else
            {
               UAL_Alarm(4006, __FILE__, __LINE__, 
                         "RC %u", rctxt->rCtxt);
            }

            break;
        case UAL_ST_ID_AS_ACTIVE:
            UAL_DEBUG(("State Changed at %s to ACTIVE\n", ITW_STRING));

	    rctxt->state = UAL_AS_ACTIVE;

	    /* set the ASP's state */
	    //aspRec->state = UAL_ASP_ACTIVE;

	    if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
            {
                UAL_Alarm(4057, __FILE__, __LINE__, 
                          "RC %u", rctxt->rCtxt);
            }
            else
            {
                UAL_Alarm(4021, __FILE__, __LINE__, 
                          "RC %u", rctxt->rCtxt);
            }
            break;
        case UAL_ST_ID_AS_PENDING:
            UAL_DEBUG(("State Changed at %s to PENDING\n", ITW_STRING));

	    rctxt->state = UAL_AS_PENDING;

	    if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
            {
                UAL_Alarm(4058, __FILE__, __LINE__, 
                          "RC %u", rctxt->rCtxt);
            }
            else
            {
                UAL_Alarm(4022, __FILE__, __LINE__, 
                          "RC %u", rctxt->rCtxt);
            }

            UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_AS_CTXT;
            UAL_CB_CTXT_AS_STATE(&cb_ctxt) = rctxt->state;
            UAL_CB_CTXT_RKEY(&cb_ctxt)     = rctxt->rCtxt;
            UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = aspRec->trId;
            CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                     (ITS_POINTER) &cb_ctxt);

            if ((redClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME)) != NULL)
            {
                /* Make ASP overall active, if needed  */
                ret = REDUNDANCY_GetNodeStartUpFlagAndState(&state);

                if ((ret == ITS_SUCCESS) && (state == ITS_STATE_BACKUP))
                {
		   ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, NULL,
						   NULL, SendASPActive_hash_iterative_proc);

                   /* Make Node Primary */
                   ITS_SendStateChangeEventToStack(ITS_STATE_PRIMARY);
                }
            }
            break;
        }

        break;
    case UAL_ST_TYPE_OTHER:
        switch(status->id)
        {
        case UAL_ST_ID_INSUF_ASP:
            UAL_DEBUG(("Insufficient ASP resources in %s\n", ITW_STRING));

            UAL_Alarm(4023, __FILE__, __LINE__, "RC %u, TransportId %x",
                      rctxt->rCtxt, aspRec->trId);

            break;
        case UAL_ST_ALT_ASP_ACTIVE:
            UAL_DEBUG(("Alternate ASP ACTIVE: TR-ID = 0x%02x\n",
                                aspRec->trId));
              
            UAL_Alarm(4024, __FILE__, __LINE__, "RC %u, TransportId %x",
                       rctxt->rCtxt, aspRec->trId);
            if (asp_nd != NULL)
            {
                asp_nd->state = UAL_ASP_INACTIVE;
            }

	    aspRec->state = UAL_ASP_INACTIVE;

            break;
        case UAL_ST_ASP_FAILURE:
	    /* 
	     * Need to get ASP ID to know which one transitioned to
	     * ASP_DOWN state in SG.
	     */
	    UAL_DEBUG(("Atleast one ASP went DOWN in an AS\n"));
	    
	     /* Send ASP_Active */
            if (aspRec->state != UAL_ASP_ACTIVE   && 
	        SendASPActive(rctxt) != ITS_SUCCESS)
            {
                    UAL_ERROR(("Failed to Send ASP Active\n"));
            }
        	     
            UAL_Alarm(4025, __FILE__, __LINE__, "TransportId %x",
                              aspRec->trId);
            break;
        }

     	break;
    }
    return;
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
 *  kramesh    05-01-2008   BugId: 1034     Propagated TCS Isse.
 *                                          Error Traces Missing
 *                                          Routing context.                                          
 *
 *  See Also:
 ****************************************************************************/
static ITS_INT 
Process_NotifyMsg(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_INT     ret     = ITS_SUCCESS;
    ITS_INT     ieCount = 0;
    ITS_UAL_IE  ies[ITS_MAX_UAL_IES];
    ITS_UINT    rkeys[MAX_RKEYS_IN_IE];
    ITS_INT     numkeys = 0;

    ASPListNode*    asp_nd = NULL;
    RKListNode*     rk_nd  = NULL;
    RK_Context*     rctxt  = NULL;
    UAL_STATUS_TYPE nStatus;

    int i = 0;

    memset(ies,   0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));
    memset(rkeys, 0, MAX_RKEYS_IN_IE * sizeof(MAX_RKEYS_IN_IE));

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_NTFY_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("Process_NotifyMsg : Decode Failure ret val = %d\n", ret));

        return ret;
    }

    for(; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_ROUT_CTX)
        {
            ret = UAL_DecodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                           ies[i].param_length,
                                           rkeys, &numkeys);

            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Decode R-CTXT failed ret value = %d\n", 
                                 ret));
            }
        }
        else if(ies[i].param_id == UAL_PRM_STATUS)
        {
            nStatus.id   = ies[i].param_data.statusType.id;
            nStatus.type = ies[i].param_data.statusType.type;
        }
    }

    /*
     * Remote node is nice enough to send us notify with 
     * routing contexts, or he sent notify without routing 
     * contexts except status indication in the message. 
     *
     * Case 1: We have routing keys.
     */
    for (i = 0; i < numkeys; i++)
    {
	rctxt = RKManager_FindEntry(rkeys[i]);

	if (rctxt != NULL)
	{
	    asp_nd = ASPList_FindEntry(rctxt->aspList,
	                               aspRec->trId);

	    UpdateAsAndAspStates(rctxt, aspRec, asp_nd, &nStatus);
	}
	else
	{
	    UAL_ERROR(("Process_NotifyMsg: Missing routing"
			     "context in RKManager %d", rkeys[i]));
	}
    }

    /* Case 2: We did not receive routing keys
     *         in Notify message.
     */
    if (numkeys == 0)
    {
        rk_nd = RKList_Iterate(aspRec->asList);

        for (; rk_nd; rk_nd = RKList_Iterate(NULL))
	{
	    asp_nd = ASPList_FindEntry(rk_nd->entry->aspList,
	      	                       aspRec->trId);

	    UpdateAsAndAspStates(rk_nd->entry, aspRec,
	                         asp_nd, &nStatus);
	}
    }
    else
    { 
         UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_NOTIFY_RECV_ID);
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
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_INT
UAL_HandleManagementClassMsg(ITS_EVENT *ualEvent, ITS_OCTET msgType,
                             ASP_Entry *aspRec)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_UAL_IE diagnInfo;

    switch(msgType)
    {
    case UAL_MSG_ERR:

        UAL_DEBUG(("UAL_HandleManagementClassMsg: Received ERR "
                         "message.\n"));

        Process_ErrorMsg(aspRec, ualEvent);
        break;

    case UAL_MSG_NOTIFY:

        UAL_DEBUG(("UAL_HandleManagementClassMsg: Received NTFY "
                         "message.\n"));

        Process_NotifyMsg(aspRec, ualEvent);
        break;

    default:

        UAL_DEBUG(("UAL_HandleManagementClassMsg: Received Unexpected"
                         " message.\n"));
        UAL_Alarm(4026, __FILE__, __LINE__, "TransportId %x", aspRec->trId);

        /*Build and send Diagnostic Info param*/
        diagnInfo.param_id = UAL_PRM_DIAGNOSTIC;
        if (ualEvent->len < UAL_MAX_DIAG_INFO_LEN)
        {
          diagnInfo.param_length = ualEvent->len;
          memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                  ualEvent->data, ualEvent->len);
        }
        else
        {
          diagnInfo.param_length = UAL_MAX_DIAG_INFO_LEN;
          memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                ualEvent->data, UAL_MAX_DIAG_INFO_LEN);
        }
        ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNSUP_MSG_TYPE,
                  &diagnInfo, 1);

    }

    return ret;
}

/************************************************
 * Helper function to be used for sending ASP_ACTIVE 
 * or ASP_INACTIVE to SG, when 
************************************************/
 
ITS_INT SendActiveOrInactiveMsg(UAL_CMD cmd, ITS_INT trId,  UAL_ASP_STATE state)
{
    ASP_Entry  *aspEntry =  NULL;
    RKListNode* rk =  NULL;
    ASPListNode* asp_nd =  NULL;
    char *dumpStr = NULL;
    struct UAL_Config cfg;
    ITS_INT retVal = ITS_SUCCESS;

    UAL_ConfigInit(&cfg);

    /* Here we will get aspEntry from Trid */
    if(ASPTable_FindEntry(trId, &aspEntry) == ITS_SUCCESS)
    {
        /* send cmd (ASP INACTIVE or ASP_ACTIVE) */
        UAL_DEBUG(("PreState was %s, returning to PreState.\n",
	            ((state == UAL_ASP_ACTIVE)? "ASP_ACTIVE" : "ASP_INACTIVE") ));
    
        /* If the command is ASP_UP */
        if(cmd == UAL_CMD_ASP_UP)
        {
            if(state == UAL_ASP_INACTIVE)
            {
                aspEntry->isStateInactive = ITS_TRUE;
            }

            UAL_SetASPInfo(&cfg, cmd, trId);
            if(UAL_ExecuteConfigCmd(cfg.priv, &dumpStr)== ITS_FALSE)
            {
                retVal = !ITS_SUCCESS;
            }
        }
        else /* if the command is ASP_ACTIVE or ASP_INACTIVE */
        {
            /* Iterate for all ASP.s in all AS.s
               Search for an ASP in AS which has same Trid
               And collect the Routing Context */
            rk = RKList_Iterate(aspEntry->asList);
    
            for(; rk; rk = RKList_Iterate(NULL))
            {
                asp_nd =  ASPList_Iterate(rk->entry->aspList);
                for(; asp_nd; asp_nd = ASPList_Iterate(NULL))
                {
                    UAL_DEBUG(("\nSendActOrInact: Transport asp_nd %d aspEnt %d...\n", asp_nd->trId, aspEntry->trId));
#if 0  // Since there will be only one ASP per Node 
                    if (aspEntry->trId == asp_nd->trId)
                    {
#endif
                        UAL_DEBUG(("\nSendActOrInact: Transport matched...\n"));
                        UAL_SetASPInfo(&cfg, cmd, rk->entry->rCtxt);
                        if(UAL_ExecuteConfigCmd(cfg.priv, &dumpStr)== ITS_FALSE)
                        {
                           retVal = !ITS_SUCCESS;
                        }
#if 0
                    }
#endif
                }
            } 
        }
    }
    else
    {
      retVal = !ITS_SUCCESS;
    }
    return retVal;
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
 *    None. 
 *
 *  Notes:
 *
 *    None.
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference       Description
 * -----------------------------------------------------------------------------
 * mshanmugam 24-05-2006  BugId: 3861    Moved calling of function 
 *                                       UpdateStaticConfigOfAS() to the end, to
 *                                       avoid sending of NOTIFY message before
 *                                       sending ASP_UP_ACK message.
 *  See Also:
 *
 ******************************************************************************/
typedef struct CheckIfAspIdUsed_hash_iterative_proc_input 
{
    ITS_INT          aspId; /*no asp-id*/
    ITS_USHORT       strId; /*Get Transport ID*/
    ITS_INT          ret;
} CheckIfAspIdUsed_hash_iterative_proc_input;
typedef struct CheckIfAspIdUsed_hash_iterative_proc_output 
{
    ITS_INT          ret;             /*no asp-id*/
    ITS_BOOLEAN      foundDuplicate; /*Get Transport ID*/
} CheckIfAspIdUsed_hash_iterative_proc_output;

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
 static int 
CheckIfAspIdUsed_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
    ITS_INT           ret     = ITS_SUCCESS;
    ASPListNode* aspNode=NULL;
    RK_Context *rCtxt = (RK_Context *)data;
    ITS_INT          aspId = ((CheckIfAspIdUsed_hash_iterative_proc_input *)in)->aspId; /*no asp-id*/
    ITS_USHORT        strId = ((CheckIfAspIdUsed_hash_iterative_proc_input *)in)->strId; /*Get Transport ID*/
	aspNode = ASPList_Iterate(rCtxt->aspList);
	for(; aspNode ; aspNode = ASPList_Iterate(NULL))
	{
	/* check aspId existence only if non-NULL aspNode and non-NULL trId */
		if(aspNode != NULL && aspNode->trId)
		{
			UAL_DEBUG(("ProcessASP_UP: received ASP_UP for aspId=%d, on trId=%0x\n", aspId, strId));

			/* asp-id would be considered as duplicate only if the 
			 * ASP_UP message is received from a different trId */
			if (aspNode->trId != strId && aspNode->aspInfo.aspid == aspId)
			{
				UAL_DEBUG(("ProcessASP_UP: aspId(%d) already exists for another ASP(state=%d), on trId=%0x\n", 
						aspId, aspNode->state, aspNode->trId));
				ret = UAL_SendERR(strId, UAL_ERR_INV_ASP_ID, NULL, 0);
				((CheckIfAspIdUsed_hash_iterative_proc_output *)out)->foundDuplicate = ITS_TRUE;
				((CheckIfAspIdUsed_hash_iterative_proc_output *)out)->ret = ret;
				return !ITS_SUCCESS;
			}
		}
	}
	return ITS_SUCCESS;
}



static ITS_INT
ProcessASP_UP(ASP_Entry* aspRec, ITS_EVENT* ualEvent, ITS_BOOLEAN flag)
{
    ITS_UAL_IE        ies[ITS_MAX_UAL_IES];
    ITS_INT           ieCount = 0;
    ITS_INT           dummy_ret, ret     = ITS_SUCCESS;
    ITS_INT           aspId   = -1;            /*no asp-id*/
    /* IPSP mode has some issue with extracting aspId so assiging it to 1 
     * need to fix */
/*    if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
    {
        aspId = 1;
    }*/

    ITS_USHORT        strId   = ualEvent->src; /*Get Transport ID*/
    ITS_USHORT        rtrId   = UAL_MANAGER_INSTANCE;
    char              host_or_path[20];
    RKListNode*       rk_nd = NULL;
    ITS_UINT          eRkeys[MAX_RKEYS_IN_IE]; /*useful when ASP is ACTIVE*/
    ITS_INT           numKeys = 0;
    UAL_CB_Context    cb_ctxt;
    SOCK_IPv4Addr     address = 0;
    TRANSPORT_Control *tc = NULL;
    int               i = 0;
    int               count = 1; /* Send number of ASP_UPs */

    memset(host_or_path, 0, sizeof(char) * 20);
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    if (flag)
    {
        UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_UP_RECV_ID);
    }

    /* get the transport */
    tc = TRANSPORT_FindTransport(ualEvent->src);
    TRANSPORT_UnfindTransport(tc);
    if (tc == NULL)
    {
        UAL_Alarm(4052, __FILE__, __LINE__, NULL);
        UAL_ERROR(("Invalid Transport Id: %d\n", ualEvent->src));

        return ITS_EBADTRANSPORT;
    } 

    if (flag)
    {
        UAL_Alarm(4009, __FILE__, __LINE__, "TransportId %x", ualEvent->src);
    }

    /* get one of the remote address */
    sprintf(host_or_path, "%s", (*(SOCKTRAN_Manager *)tc).socket.host_or_path);

    ret =  SOCK_IPv4NameToAddr(host_or_path, &address);
    if (ret != ITS_SUCCESS)
    {
        UAL_ERROR(("Error getting ASP Address:\n"));

        return -1;
    }

    memset(ies, 0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));
    memset(eRkeys,0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ASPUP_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_UP: Decode Failure for ASP UP:\n"));

        return ret;
    }

    if(UAL_GL_ITW_MODE == UAL_ITW_SG) 
    {
        for(i = 0; (i < ieCount); i++)
        {
            if(ies[i].param_id == UAL_PRM_ASP_ID)
            {
                aspId = ies[i].param_data.aspId.aspId;
                UAL_DEBUG(("Incoming ASPId : %d", aspId));

                break;
            }
        }
    }

    if(aspId == -1)
    {
        if(UAL_GL_ITW_MODE != UAL_ITW_SG && UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
            aspId = aspRec->aspId;
        else
            aspId = UAL_GL_ASP_ID;
    }

    memset(eRkeys, 0, sizeof(eRkeys));

    /* Check if the aspId was already used by some ASP that had sent ASP_UP earlier 
     * We do this by iterating over the list of AS's (and its aspList) to find a 
     * conflicting entry
     */
    CheckIfAspIdUsed_hash_iterative_proc_input in;
    CheckIfAspIdUsed_hash_iterative_proc_output out;
	in.aspId = aspId;
	in.strId = strId;
	out.foundDuplicate = ITS_FALSE;
	out.ret = ITS_SUCCESS;
	dummy_ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, &in,
			   &out, CheckIfAspIdUsed_hash_iterative_proc);

	if (out.foundDuplicate == ITS_TRUE)
	{
		return out.ret;
	}

    /* 
     * Check if the ASP was active for some AS, if so demote to inactive
     * then send UP_ACK plus ERR and NTFY. As per the draft... whatever...
     */
    
    rk_nd = RKList_Iterate(aspRec->asList);

    for(; rk_nd; rk_nd = RKList_Iterate(NULL))
    {
        ASPListNode* aspNode = NULL;
        RK_Context*  rkctxt = rk_nd->entry;

        aspNode = ASPList_FindEntry(rkctxt->aspList, strId);

        if(aspNode != NULL)
        {
            if(aspNode->state == UAL_ASP_ACTIVE)
            {
                RK_Context *asContext = NULL;
                RKListNode* rkListNode = NULL;
                SS7_LinkPtr linkPtr = NULL;
                SS7_LinkSetPtr linkSetPtr = NULL;

                eRkeys[numKeys] = rkctxt->rCtxt;

                rkListNode = RKList_FindEntry(aspRec->asList, rkctxt->rCtxt);

                if(rkListNode != NULL)
                {
                    linkPtr = LINK_FindLink(rkctxt->linkSet, rkListNode->linkCode);
                }

                if (linkPtr == NULL)
                {
                    UAL_ERROR(("ProcessASP_UP:Error finding Link\n"));
                }
                else
                {
                    ret = LINK_RemLink(rkctxt->linkSet, linkPtr);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("ProcessASP_UP:Error removing link.\n"));
                    }
                    UAL_DEBUG(("\nProcessASP_UP: Link %d Removed from LS %d...\n", linkPtr->linkCode, rkctxt->linkSet));
                }

                linkSetPtr = LINKSET_FindLinkSet(rkctxt->linkSet);
                if (linkSetPtr == NULL)
                {
                    UAL_ERROR(("Error finding LinkSet: %d\n", rkctxt->linkSet));
                }
                else if (linkSetPtr->numLinks == 0)
                {
                    ret = LINKSET_SetLinkSetState(linkSetPtr, ITS_FALSE);
                    if (ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("Error changing LinkSet: %d to DOWN. \n",
                                          rkctxt->linkSet));
                    }
                }

                asContext = RKManager_FindEntry(rkctxt->rCtxt);
                if (asContext != NULL)
                {
                    if(UAL_CheckASPending(asContext)) 
                    {
                        asContext->state = UAL_AS_PENDING;

                        UAL_StartPendingStateProcedure(asContext);
                    }
                }
                numKeys++;
            }
            
            aspNode->state = UAL_ASP_INACTIVE;

            aspNode->aspInfo.aspid = aspId;
        }
    }

    /* Send ASP_UP ACK */
    for(i = 0; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_MSG_HDR)
        {
            ies[i].param_data.msgHeader.msgType = UAL_MSG_ASPUP_ACK;
            break;
        }
    }

    ret = UAL_EncodeMsg(ies, 2/*two params*/, 
                        ualEvent, &UAL_UPACK_Desc);


    if (!flag)
    {
        count = 0; /* Do not send if we are IPSP client */
        ProcessASP_UP_ACK(aspRec, ualEvent, flag);
        ITS_EVENT_TERM(ualEvent);
    }
    else
    {
        ualEvent->src = rtrId;

        if(ret == ITS_SUCCESS) /*Send ASP_UP_ACK*/
        {
            ret = TRANSPORT_PutEvent(strId, ualEvent);
            UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_UPACK_SENT_ID);
        }
    }

    /* Other than IPSP client should send an ack */
    if (!UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE))
    {
        if(numKeys > 0) /*ASP serving as ACTIVE for the R-CTXTs */
        {
            ITS_UAL_IE errIe[1];

            UAL_ERROR(("ProcessASP_UP: Send an Unexpected Message.\n"));

            errIe[0].param_id = UAL_PRM_ROUT_CTX;

            ret = UAL_EncodeRoutingContext(errIe[0].param_data.rCtxt.rCtxt,
                                           &errIe[0].param_length,
                                           eRkeys, numKeys);

            ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNEPECTED_MSG, errIe, 1);
        }

        if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
        {
            aspRec->remoteInfo.state = UAL_ASP_INACTIVE;
            aspRec->state = UAL_ASP_INACTIVE; 

            UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = aspRec->remoteInfo.state;
            UAL_CB_CTXT_ASP_ID(&cb_ctxt)    = aspRec->remoteInfo.aspInfo.aspid;
        }
        else
        {
            aspRec->state = deriveASPStateFromRCtxt(aspRec); 

            UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = aspRec->state;
            UAL_CB_CTXT_ASP_ID(&cb_ctxt)    = aspId;
        }

        UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
        UAL_CB_CTXT_TRANS_ID(&cb_ctxt)  = aspRec->trId;

        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                  (ITS_POINTER)&cb_ctxt);
    }

    /* we use ASPID to know staticaly which AS the ASP belongs to */
    ret = UpdateStaticConfigOfAS(&aspId, aspRec, address, flag);
    if (ret != ITS_SUCCESS)
    {
        return -1;
    }

    return ret;
}

ITS_INT
UAL_ProcessASPUP_IPSP_SE(ASP_Entry *aspRec, ITS_EVENT *ualEvent)
{
    return ProcessASP_UP(aspRec, ualEvent, ITS_FALSE); 
}

UALDLLAPI int
UAL_SendASP_ACTIVE(ITS_UINT *rkArray, int rk_len, ASP_Entry* aspRec, 
               UAL_TRAFFIC_TYPE mode, ITS_BOOLEAN flag /*used for ipsp */)
{
    ITS_INT       ret = ITS_SUCCESS;
    ITS_EVENT     msg;
    ITS_UAL_IE    ies[ITS_MAX_UAL_IES];
    UAL_TimerCtx  timerCtx;
    int           j = 0;

    memset(ies,  0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE)); /* Init Stack variables */
    memset(&timerCtx, 0, sizeof(UAL_TimerCtx));
    ITS_EVENT_INIT(&msg, UAL_MANAGER_INSTANCE, UAL_MAX_MSG_LEN);

    /* build the ASPAC Message */
    ies[j].param_id = UAL_PRM_MSG_HDR;
    ies[j].param_data.msgHeader.msgClass = UAL_CLASS_ASPTM;
    ies[j].param_data.msgHeader.msgLen   = sizeof(UAL_MSG_HDR);
    ies[j].param_data.msgHeader.msgType  = UAL_MSG_ASPAC;
    ies[j].param_data.msgHeader.version  = UAL_GL_VERSION;
    ies[j].param_data.msgHeader.reserved = 0x00;

    /*Set Traffic mode param*/
    ies[++j].param_id             = UAL_PRM_TRAFFIC_MODE;
    ies[j].param_length           = sizeof(UAL_TRAFFIC_TYPE);
    ies[j].param_data.trafMode.tm = mode;

    if(rk_len > 0)
    {
         /* Set Routing Context*/
        ies[++j].param_id = UAL_PRM_ROUT_CTX;
        ret = UAL_EncodeRoutingContext(ies[j].param_data.rCtxt.rCtxt, 
                                       &ies[j].param_length, 
                                       rkArray, rk_len);

        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("SendASP_ACTIVE: failed to encode Routing "
                             "Context.\n"));
            return ret;
        }
    }

    /* encode the ASPAC message */
    ret = UAL_EncodeMsg(ies, j + 1, &msg, &UAL_ASPAC_Desc);
    if (ret != ITS_SUCCESS)
    {    
        UAL_ERROR(("SendASP_ACTIVE: UAL_EncodeMsg failed code %d.\n",
		   ret));
        return ret;
    }

    if (!flag)
    {
        UAL_DEBUG(("SendASP_ACTIVE: Sending ASPAC to trId %d.\n",
                    aspRec->trId));

        /*Start Timer for all three traffic modes*/
        timerCtx.from       = aspRec->trId;
        timerCtx.type       = UAL_RETRANS;
        timerCtx.retryCount = UAL_GL_NUM_RETRY;
        timerCtx.ackMsgType = UAL_MSG_ASPAC_ACK;
        timerCtx.tm         = mode;
        timerCtx.msgType    = ASP_ACTIVE_MSG;

        ret = UAL_SetTimerMsgData(&timerCtx, &msg);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("SendASP_ACTIVE: UAL msg too long for timer."));

            return ret;
        }

        /* Timer info in ASP record */
        memcpy(&aspRec->timerCtx, &timerCtx, sizeof(UAL_TimerCtx));

        ret = TRANSPORT_PutEvent(aspRec->trId, &msg);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("SendASP_ACTIVE: TRANPORT_PutEvent failed code "
                         "%d.\n", ret));
        }

        if(aspRec->ackTimer[ASP_ACTIVE_MSG] != (ITS_SERIAL)0)
        {
            UAL_DEBUG(("SendASP_ACTIVE: Timer has been running for"
		               " ASP_ACTIVE_MSG message\n"));

            TIMERS_CancelTimer(aspRec->ackTimer[ASP_ACTIVE_MSG]);
        }

        /* Start the ACK timer */
        aspRec->ackTimer[ASP_ACTIVE_MSG] = TIMERS_StartTimer(UAL_MANAGER_INSTANCE, 
                                                    UAL_GL_ACK_TIMER, 
                                                    (void *)&timerCtx, 
                                                     sizeof(UAL_TimerCtx));

        UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_AC_SENT_ID);

    }
    else
    {
        ret = ProcessASP_ACTIVE(aspRec, &msg, ITS_FALSE);

        ITS_EVENT_TERM(&msg);
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

typedef struct UpdateLocalRoutingKeys_hash_iterative_proc_input
{
    ITS_POINTER  rkeys;
    ITS_POINTER  rcount;
    ASP_Entry   *aspRec;
    ITS_BOOLEAN isNonMember;

} UpdateLocalRoutingKeys_hash_iterative_proc_input;


static int
UpdateLocalRoutingKeys_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{
   int k = 0; /* index of non member keys */
   RK_Context *tmp = (RK_Context *)data;

   ITS_UINT **rkeys = (ITS_UINT **) ((UpdateLocalRoutingKeys_hash_iterative_proc_input *)in)->rkeys;
   ITS_INT  *rcount = (ITS_INT  *) ((UpdateLocalRoutingKeys_hash_iterative_proc_input *)in)->rcount;
   ASP_Entry   *aspRec = ((UpdateLocalRoutingKeys_hash_iterative_proc_input *)in)->aspRec;
   ITS_BOOLEAN isNonMember = ((UpdateLocalRoutingKeys_hash_iterative_proc_input *)in)->isNonMember;

   if (tmp)
   {
       if (isNonMember)
       {
           if (!tmp->isMember)
           {
               *rkeys[(tmp->trafficMode - 1)*MAX_RKEYS_IN_IE+ ++k] = tmp->rCtxt;
               rcount[tmp->trafficMode - 1]++;
           }
       }
       else
       {
           tmp->state = UAL_AS_ACTIVE;
           aspRec->state = UAL_ASP_ACTIVE;
       }
   }
   return ITS_SUCCESS;
}

static int
UpdateLocalRoutingKeys(ASP_Entry *aspRec, ITS_BOOLEAN isNonMember)
{
    int      k = 0; /* index of non member keys */
    int i = 0;
    ITS_INT  ret = ITS_SUCCESS;
    //ITS_UINT rkeys[NUM_TRAFFIC_MODES][MAX_RKEYS_IN_IE];
    ITS_INT  rcount[NUM_TRAFFIC_MODES] = {0,0,0};
    ITS_UINT** rkeys = NULL;

    rkeys = (ITS_UINT**)malloc( sizeof(ITS_UINT*) *NUM_TRAFFIC_MODES);
    for (i=0;i<NUM_TRAFFIC_MODES;i++)
        rkeys[i] = (ITS_UINT*)malloc(sizeof(ITS_UINT)*MAX_RKEYS_IN_IE);


    UpdateLocalRoutingKeys_hash_iterative_proc_input in;
    in.rkeys = (char *) rkeys;
    in.rcount = (char *) rcount;
    in.isNonMember = isNonMember;
    in.aspRec = aspRec; 
    ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, &in,
		       NULL, UpdateLocalRoutingKeys_hash_iterative_proc);
    for (k = 0; (isNonMember && k < NUM_TRAFFIC_MODES && rcount[k]); k++)
    {
        ret = UAL_SendASP_ACTIVE(rkeys[k], rcount[k],aspRec,
                              k + 1, ITS_TRUE);
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
static int
ASPUP_ACK_UpdateStaticConfigOfAS_hash_iterative_proc(ITS_INT context, ITS_POINTER data,
                     void* in, void* out)
{

    ITS_INT        ret     = ITS_SUCCESS;
    RK_Context* ctxt = (RK_Context*)data;
	ASPListNode *aspNode = NULL;
	ASP_Entry* aspRec = (ASP_Entry*)in;
	if (ctxt->isMember == ITS_FALSE)
	{
		aspNode = ASPList_Iterate (ctxt->aspList);

		if (aspNode != NULL)
		{
			ret = UpdateStaticConfigOfAS(&aspNode->aspInfo.aspid,
					                   aspRec, 0, ITS_FALSE);
			if (ret != ITS_SUCCESS)
			{
				return -1;
			}
		}
	}
	return ITS_SUCCESS;
}
static ITS_INT 
ProcessASP_UP_ACK(ASP_Entry* aspRec, ITS_EVENT* ualEvent, ITS_BOOLEAN aspFlag)
{
    ITS_UAL_IE     ies[ITS_MAX_UAL_IES];
    ITS_UINT       rKeys[NUM_TRAFFIC_MODES][MAX_RKEYS_IN_IE];
    ITS_INT        numKeys[NUM_TRAFFIC_MODES] = {0,0,0};
    ITS_INT        ieCount = 0;
    ITS_INT        ret = ITS_SUCCESS;
    ITS_OCTET      data[UAL_MAX_RCTXT_LEN];
    RKListNode     *rk_nd = NULL;
    UAL_CB_Context cb_ctxt;    
    int            i = 0;
    ITS_USHORT     trId = ualEvent->src; /*Get transport ID*/
    ITS_INT        preState;

    memset(ies,   0, ITS_MAX_UAL_IES   * sizeof(ITS_UAL_IE));
    memset(rKeys, 0, NUM_TRAFFIC_MODES * MAX_RKEYS_IN_IE *
           sizeof(ITS_UINT));
    memset(data,  0, UAL_MAX_RCTXT_LEN * sizeof(ITS_OCTET));
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));
    
    if (aspFlag)
    {
        UAL_Alarm(4008, __FILE__, __LINE__, "TransportId %x", trId);
    }

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_UPACK_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_UP_ACK: Decode Failure \n"));
        return ret;
    }


    preState = aspRec->state;
    aspRec->state = UAL_ASP_INACTIVE;

    /* Handle UP_ACK for different staes of ASP */
    if(UAL_IS_APP_ASP(UAL_GL_ITW_MODE))
    {
        /* bugzilla bug #84 */
        if(preState == UAL_ASP_INACTIVE)
        {
            if(aspRec->ackTimer[ASP_UP_MSG] != (ITS_SERIAL)0) /*we got an ack*/
            {
                TIMERS_CancelTimer(aspRec->ackTimer[ASP_UP_MSG]);
                aspRec->ackTimer[ASP_UP_MSG] = (ITS_UINT)0;
                memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
            }

            UAL_ERROR(("ProcessASP_UP_ACK:Received ASP_UP_ACK in ASP_INACTIVE state, "
                                        "message is discarded.\n"));
            return ret;
	    }
        else if (preState == UAL_ASP_ACTIVE)
        {
            if(aspRec->ackTimer[ASP_UP_MSG] != (ITS_SERIAL)0) /*we got an ack*/
            {
                TIMERS_CancelTimer(aspRec->ackTimer[ASP_UP_MSG]);
                aspRec->ackTimer[ASP_UP_MSG] = (ITS_UINT)0;
                memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
            }

	        aspRec->state = UAL_ASP_INACTIVE;
            UAL_ERROR(("ProcessASP_UP_ACK:Received ASP_UP_ACK in ASP_ACTIVE state, "
                                        "message is discarded.\n"));
            ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNEPECTED_MSG, NULL, 0);
        }
        /* bugzilla bug #18 #82 */
	    else if (aspRec->ackTimer[ASP_UP_MSG] == (ITS_SERIAL)0)
	    {
	        aspRec->state = preState;
            UAL_ERROR(("ProcessASP_UP_ACK: ASP_UP message was not sent, yet ASP_UP_ACK message received, "
                                        "discarded.\n"));
            return ret;
	    }
    }

    if(aspRec->ackTimer[ASP_UP_MSG] != (ITS_SERIAL)0) /*we got an ack*/
    {
        TIMERS_CancelTimer(aspRec->ackTimer[ASP_UP_MSG]);
        aspRec->ackTimer[ASP_UP_MSG] = (ITS_UINT)0;
        memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
    }

    /* update server's state if is single exchange client */
    if (UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE) && aspFlag)
    {
        aspRec->remoteInfo.state = UAL_ASP_INACTIVE;
    }

    /* For double exchange, in case we did not receive ASP_UP,
       we need to update state as well */
    if (UAL_IS_IPSP_DOUBLE_EXCHG(UAL_GL_IPSP_TYPE))
    {
        aspRec->remoteInfo.state = UAL_ASP_INACTIVE;

		ret = HASH_VTableIterate(__UAL_AS_Manager.asTable, UAL_HASH_RID, aspRec,
				   NULL, ASPUP_ACK_UpdateStaticConfigOfAS_hash_iterative_proc);
		if (ret !=ITS_SUCCESS) 
		{
			return ret;
		}

    }

    
    if (aspFlag)
    {
        UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
        UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_INACTIVE;
        UAL_CB_CTXT_TRANS_ID(&cb_ctxt)  = aspRec->trId;
        UAL_CB_CTXT_ASP_ID(&cb_ctxt) = aspRec->aspId;
    
        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                  (ITS_POINTER)&cb_ctxt);

        UAL_IncrementMIBStats(trId, UAL_PEG_UPACK_RECV_ID);
    }

    if(aspRec->isStateInactive == ITS_TRUE)
    {
        aspRec->isStateInactive = ITS_FALSE;
        return ret;
    }

    /* Sending ASP_ACTIVE*/

    rk_nd = RKList_Iterate(aspRec->asList);

    for(;rk_nd; rk_nd = RKList_Iterate(NULL))
    {
        RK_Context   *rCtxt = rk_nd->entry;
        ASPListNode  *asp   = NULL;
        ITS_INT      ti, ri;

        ti = ri = 0;

        if(UAL_GL_ITW_MODE != UAL_ITW_SG) 
        {
           asp = ASPList_FindEntry(rCtxt->aspList, trId);

           if(asp != NULL) /*For static config*/
           {
               asp->state = UAL_ASP_INACTIVE;
           }

	   if (!UAL_IS_IPSP_SINGLE_EXCHG(UAL_GL_IPSP_TYPE) &&
               !rCtxt->isMember)
	   {
	       /* Select only member keys for sending active*/
	       continue;
	   }
        }
	
        if(rCtxt->trafficMode == UAL_LOADSHARE)
        {
           ti = TRAFFIC_MODE_LS;
        }
        else if(rCtxt->trafficMode == UAL_OVERRIDE)
        {
            ti = TRAFFIC_MODE_OR;
        }
        else if(rCtxt->trafficMode == UAL_BROADCAST)
        {
            ti = TRAFFIC_MODE_BC;
            UAL_ERROR(("Broadcast Traffic Mode is not supported:\n"));
        }
        else
        {
            ti = -1;
            UAL_DEBUG(("ProcessASP_UP_ACK: Invalid Traffic Mode:\n"));
        }

	if (ti >= 0)
	{
            i = numKeys[ti]++;
            rKeys[ti][i] = rCtxt->rCtxt;
	}

        if(i == MAX_RKEYS_IN_IE)
        {
            UAL_CRITICAL(("ProcessASP_UP_ACK: routing contrexts > MAX")) ;
        }
    }

    for(i = 0; i < NUM_TRAFFIC_MODES; i++)
    {
        UAL_TRAFFIC_TYPE mode = UAL_MODE_NONE;
        ITS_BOOLEAN      flag = ITS_TRUE;
        
        if(i == TRAFFIC_MODE_OR)
        {
           mode = UAL_OVERRIDE_MODE;
        }
        else if(i == TRAFFIC_MODE_LS)
        {
           mode = UAL_LOADSHARE_MODE;
        }
        else if(i == TRAFFIC_MODE_BC)
        {
           mode = UAL_BROADCAST_MODE;
        }
        else
        {
           UAL_DEBUG(("ProcessASP_UP_ACK: Traffic mode over run:\n"));
           flag = ITS_FALSE;
        }

        if(flag && numKeys[i] > 0)
        {
            ITS_Class      redClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);
            ITS_NODE_STATE state    = ITS_STATE_BACKUP;
            int            redRet   = ITS_SUCCESS;

            //redRet = REDUNDANCY_GetNodeStartUpFlagAndState(&state);
            redRet = ITS_SUCCESS;
            ITS_GetNodeState(&state);
            
            UAL_DEBUG(("ProcessASP_UP_ACK: redClass: %p redRet: %d state : %s\n", 
				redClass, redRet, ITS_NODE_STATE_STRING(state)));
            if (redClass == NULL || (redRet == ITS_ENOTCONFIG) ||
                (((redRet == ITS_ENOTFOUND) || (redRet == ITS_SUCCESS)) 
				 && (state == ITS_STATE_PRIMARY)))
            {
                /* Do not send in server mode */
                if (!UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE) && aspFlag) 
                {
                    StoreASPActiveConfigData storeASPActiveData;
                    storeASPActiveData.rKey = rKeys[i];
                    storeASPActiveData.rKeyLen = numKeys[i];
                    storeASPActiveData.aspRec = aspRec;
                    storeASPActiveData.mode = mode;
                    storeASPActiveData.flag = ITS_FALSE;
                    /* We may be ASP, IPSP Double exchange or IPSP Client */
                    if (CALLBACK_NUM_CALLBACKS(__UAL_SCTPMgntCallBack))
                    {
                        CALLBACK_CallCallbackList(__UAL_SCTPMgntCallBack, NULL,
                                (ITS_POINTER) &storeASPActiveData);

                    }
                    else
                    {
                        ret = UAL_SendASP_ACTIVE(rKeys[i], numKeys[i],aspRec, mode, 
                                ITS_FALSE);
                    }
                }
            }
        }
    }

    if (UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE) && aspFlag)
    {
        UpdateLocalRoutingKeys(aspRec, ITS_TRUE);
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
 *    None. 
 *
 *  Notes:
 *     1. Look for all the ASes in ASP
 *     2. Find ASP in ASPList contained in RK_Context
 *     3. Update ASP state, and check whether this RContext
 *        should go to the pending state.
 *     4. If it is in Pending state start pending timer
 *     5. If it is graceful shut down, send DOWN_ACK.
 *    
 *  See Also:
 *
 ******************************************************************************/
static ITS_INT 
ProcessASP_DOWN(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_INT    ieCount = 0;
    ITS_INT    ret = ITS_SUCCESS;

    ITS_USHORT     trId  = ualEvent->src;
    RKListNode*    rkNode= NULL;
    ITS_EVENT      ackEvent;
    UAL_CB_Context cb_ctxt;
    int i = 0;
    UAL_DEBUG(("Process ASP DOWN ENtry"));

    UAL_Alarm(4011, __FILE__, __LINE__, "TransportId %x", trId);

    memset(ies, 0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ASPDN_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_DOWN: Decode Failure \n"));
        return ret;
    }


    ITS_EVENT_INIT(&ackEvent, UAL_MANAGER_INSTANCE, 256);

    UAL_IncrementMIBStats(trId, UAL_PEG_DN_RECV_ID);

    rkNode = RKList_Iterate(aspRec->asList);

    for(; rkNode; rkNode = RKList_Iterate(NULL))
    {
        ASPListNode* nd = NULL;
        nd = ASPList_FindEntry(RK_LIST_CONTEXT(rkNode)->aspList, trId);

        if(nd != NULL)
        {
            SS7_LinkPtr     linkPtr    = NULL;
            SS7_LinkSetPtr  linkSetPtr = NULL;

            RK_Context* rk_ctxt = rkNode->entry;
            nd->state   = UAL_ASP_DOWN; /* Update state of ASP*/

            /* 
             * Before starting pending state, remove the link or
             * there might be a link conflict with the pending transport
             */

            linkPtr = LINK_FindLink(rkNode->entry->linkSet, rkNode->linkCode);
            if (linkPtr == NULL)
            {
                UAL_DEBUG(("Error finding LinkCode %d, on "
                                   "linkSet %d.\n", rkNode->linkCode,
                                   rkNode->entry->linkSet));
            }
            else
            {
                ret = LINK_RemLink(rkNode->entry->linkSet, linkPtr);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error removing link.\n"));
                }
            }

            rkNode->linkCode = 0xFF;

            /* Set the linkSet Inactive only if the AS was ACTIVE. If it is
             * INACTIVE or DOWN the state of the Linkset should be Inactive
             * already
             */

            linkSetPtr = LINKSET_FindLinkSet(rkNode->entry->linkSet);
            if (linkSetPtr == NULL)
            {
                UAL_ERROR(("Error finding LinkSet: %d\n", rkNode->entry->linkSet));
            }
            else if ((linkSetPtr->numLinks == 0) &&
                     (rk_ctxt->state != UAL_AS_DOWN && 
                      rk_ctxt->state != UAL_AS_INACTIVE))
            {
                ret = LINKSET_SetLinkSetState(linkSetPtr, ITS_FALSE);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error changing LinkSet: %d to DOWN. \n",
                                      rkNode->entry->linkSet));
                }
            }

            /*if AS is in PENDING*/
            if(UAL_CheckASPending(rk_ctxt))
            {
                /*change state to PENDING*/
                rk_ctxt->state = UAL_AS_PENDING; 

                ret = UAL_StartPendingStateProcedure(rk_ctxt);
            }
            else if(UAL_CheckASDown(rk_ctxt))
            {
                rk_ctxt->state = UAL_AS_DOWN;

                /* remove the AS node from AS list for that ASP */
                ret = RKList_RemoveEntry(aspRec->asList, rk_ctxt->rCtxt);
                if (ret != ITS_SUCCESS)
                {
                    UAL_DEBUG(("AS entry %d was not removed from "
                                       "ASP entry\n", rk_ctxt->rCtxt));
                }
            }

            memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

            UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_AS_CTXT;
            UAL_CB_CTXT_AS_STATE(&cb_ctxt)  = rk_ctxt->state;
            UAL_CB_CTXT_RKEY(&cb_ctxt)      = rk_ctxt->rCtxt;
            UAL_CB_CTXT_TRANS_ID(&cb_ctxt)  = aspRec->trId;

            CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                      (ITS_POINTER)&cb_ctxt);
        }
    }

    aspRec->state = UAL_ASP_DOWN; /*change state*/

    if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
    {
        aspRec->remoteInfo.state = UAL_ASP_DOWN;
    }
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
    UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_DOWN;
    UAL_CB_CTXT_ASP_ID(&cb_ctxt)    = aspRec->aspId;

    CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                              (ITS_POINTER)&cb_ctxt);

    for(i = 0; i < ieCount; i++)  /*Send ASP DOWN ACK*/
    {
        if(ies[i].param_id == UAL_PRM_MSG_HDR)
        {
            ies[i].param_data.msgHeader.msgType =
                                     UAL_MSG_ASPDN_ACK;
        }
    }

    ret = UAL_EncodeMsg(ies, 2/*num of params*/, 
                        &ackEvent, &UAL_DNACK_Desc);

    if(ret == ITS_SUCCESS)
    {
        if(TRANSPORT_PutEvent(trId, &ackEvent) != ITS_SUCCESS)
        {
            UAL_DEBUG(("ProcessASP_DOWN: Invalid Transport: TRID=%d\n"
			       ,trId));
        }
        else
        {
            UAL_IncrementMIBStats(trId, UAL_PEG_DNACK_SENT_ID);
        }
    }

    UAL_DEBUG(("Process ASP DOWN Exit"));
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
 *    None. 
 *
 *  Notes:
 *   
 *     1. Note present state of ASP
 *     2. if ASP state is ASP DOWN not much work
 *     3. if the ASP is in ACTIVE/INACTIVE, mark it 
 *          as DOWN and start procedures to bring it up.
 *  See Also:
 *
 ******************************************************************************/
static ITS_INT 
ProcessASP_DOWN_ACK(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_UAL_IE     ies[ITS_MAX_UAL_IES];
    ITS_INT        ieCount = 0;
    ITS_INT        ret = ITS_SUCCESS;
    UAL_CB_Context cb_ctxt;
    UAL_ASP_STATE  preState;
    TRANSPORT_Control* trCtrl = NULL;
    ITS_BOOLEAN strayDownAck = ITS_FALSE;

    UAL_DEBUG(("ProcessASP_DOWN_ACK\n"));

    UAL_Alarm(4010, __FILE__, __LINE__, "TransportId %x", ualEvent->src);

    memset(ies, 0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));


    // Removed this check since timerCtx was not being populated while sending the ASP DOWN message
    // and hence was discarding the ASP DOWN ACK message received from SG and was resending the ASP
    // DOWN message 
/*
    if (aspRec->timerCtx.ackMsgType != UAL_MSG_ASPDN_ACK)
    {
        UAL_ERROR(("Received invalid/unexpected ASP_DOWN_ACK TRID = 0x%x. "
                         "Message Discarded\n", ualEvent->src));
        return ITS_EBADSTATE;
    }
*/

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_DNACK_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_DOWN_ACK: Decode Failure \n"));
        return ret;
    }

    UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_DNACK_RECV_ID);
    if(aspRec->ackTimer[ASP_DOWN_MSG] != (ITS_SERIAL)0)
    {
        TIMERS_CancelTimer(aspRec->ackTimer[ASP_DOWN_MSG]);
        aspRec->ackTimer[ASP_DOWN_MSG] = (ITS_SERIAL)0;
        memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
    }
    else
    {
        strayDownAck = ITS_TRUE;
    }
    
    /****************************************************** 
     * new code to replace the old code that did something 
     * similar, commented using #if (see below)
     * basically, 
     * the code, changes the state of the ASP to ASP_DOWN
     * and then if it was in either of ASP_INACTIVE or ASP_ACTIVE
     * state, initiates the process to get it in that state.
     ******************************************************/
    preState = aspRec->state;
    aspRec->state = UAL_ASP_DOWN;

    if(preState != aspRec->state)
    {
        /* notify user our state has been changed */
        UAL_CB_CTXT_ASP_ID(&cb_ctxt)    = aspRec->aspId;
        UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = aspRec->state;
        UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
        UAL_CB_CTXT_TRANS_ID(&cb_ctxt)  = aspRec->trId;
    
        CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                  (ITS_POINTER)&cb_ctxt);
    }
    
    trCtrl = TRANSPORT_FindTransport(aspRec->trId);
    TRANSPORT_UnfindTransport(trCtrl);

    if (trCtrl == NULL)
    {
        UAL_Alarm(4052, __FILE__, __LINE__, NULL);

        UAL_ERROR(("Invalid Transport Id: %d\n", aspRec->trId));

        return (ITS_EBADTRANSPORT);
    }

    /* To send MTP3-PAUSE to the USER */
    TRANSPORT_SetState(trCtrl, ITS_FALSE);

    if((UAL_GL_ITW_MODE != UAL_ITW_SG) && (strayDownAck == ITS_TRUE))
    {
        if (preState == UAL_ASP_INACTIVE)
	    {
	        SendActiveOrInactiveMsg(UAL_CMD_ASP_UP, aspRec->trId, UAL_ASP_INACTIVE);
	    }
	    else if(preState == UAL_ASP_ACTIVE)
        {
	        SendActiveOrInactiveMsg(UAL_CMD_ASP_UP, aspRec->trId, UAL_ASP_ACTIVE);
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
 *    None. 
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
static ITS_INT 
ProcessASP_HEARTBEAT(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_INT    ieCount = 0;
    ITS_INT    ret = ITS_SUCCESS;

    ITS_EVENT  ackEvent;
    ITS_INT    ackLen = ualEvent->len;

    int i = 0;

    memset(ies, 0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_HEARTBEAT_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("HEARTBEAT Deocode error = %d\n", ret));
        return ret;
    }
    else
    {
        for(;i < ieCount; i++)
        {
            if(ies[i].param_id == UAL_PRM_MSG_HDR)
            {
                ies[i].param_data.msgHeader.msgType = UAL_MSG_BEAT_ACK;
                break;
            }
        }

        ackLen += 8;

        ITS_EVENT_INIT(&ackEvent, UAL_MANAGER_INSTANCE, ackLen);

        ret = UAL_EncodeMsg(ies, 2, &ackEvent, &UAL_HEARTBEAT_ACK_Desc);

        if(ret == ITS_SUCCESS)
        {
            TRANSPORT_PutEvent(aspRec->trId, &ackEvent);
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
 *    None. 
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
static ITS_INT 
ProcessASP_HEARTBEAT_ACK(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_INT    ieCount = 0;
    ITS_INT    ret = ITS_SUCCESS;

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_HEARTBEAT_ACK_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_HEARTBEAT_ACK: Decode Failure \n"));
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
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_INT
UAL_HandleStateMaintMsg(ITS_EVENT *ualEvent, ITS_OCTET msgType,
                        ASP_Entry *aspRec)
{
    int ret = ITS_SUCCESS;
    ITS_UAL_IE diagnInfo;

    if(aspRec == NULL)
    {
        UAL_ERROR(("NO ASP Record present:\n"));

        return !ret;
    }

    switch(msgType)
    {
    case UAL_MSG_ASPUP:

        UAL_DEBUG(("UAL_HandleStateMaintMsg: Received ASPUP message on"
                         " assoc: %02x.\n", aspRec->trId));

        ret = ProcessASP_UP(aspRec, ualEvent, ITS_TRUE);

        break;

    case UAL_MSG_ASPUP_ACK:

        UAL_DEBUG(("UAL_HandleStateMaintMsg: Received ASPUP_ACK message"
                         " on assoc: %02x.\n", aspRec->trId));

        ret = ProcessASP_UP_ACK(aspRec, ualEvent, ITS_TRUE);
        break;
    
    case UAL_MSG_ASPDN:
    
        UAL_DEBUG(("UAL_HandleStateMaintMsg: Received ASPDN message on"
                         "assoc: %02x.\n", aspRec->trId));
       
        ret = ProcessASP_DOWN(aspRec, ualEvent);

        break;
    
    case UAL_MSG_ASPDN_ACK:

        UAL_DEBUG(("UAL_HandleStateMaintMsg: Received ASPDN_ACK"
		          " message on assoc: %02x.\n", aspRec->trId));

        ret = ProcessASP_DOWN_ACK(aspRec, ualEvent);

        break;
    
    case UAL_MSG_BEAT:
        
        UAL_DEBUG(("UAL_HandleStateMaintMsg: Received HEARTBEAT"
		         " message on assoc: %02x.\n",  aspRec->trId));

        ret = ProcessASP_HEARTBEAT(aspRec, ualEvent);

        break;

    case UAL_MSG_BEAT_ACK:

        UAL_DEBUG(("UAL_HandleStateMaintMsg: Received HEARTBEAT_ACK"
		         " message on assoc: %02x.\n", aspRec->trId));

        ret = ProcessASP_HEARTBEAT_ACK(aspRec, ualEvent);
        
        break;

    default:
        
        /* ignore the message */
        UAL_ERROR(("UAL_HandleStateMaintMsg: Received invalid Msg Type: "
                         "%02x.\n", msgType));

        UAL_Alarm(4026, __FILE__, __LINE__, "TransportId %x", aspRec->trId);

        /*Build and send Diagnostic Info param*/
        diagnInfo.param_id = UAL_PRM_DIAGNOSTIC;
        if (ualEvent->len < UAL_MAX_DIAG_INFO_LEN)
        {
            diagnInfo.param_length = ualEvent->len;
            memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                  ualEvent->data, ualEvent->len);
        }
        else
        {
            diagnInfo.param_length = UAL_MAX_DIAG_INFO_LEN;
            memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                   ualEvent->data, UAL_MAX_DIAG_INFO_LEN);
        }
        ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNSUP_MSG_TYPE,
                              &diagnInfo, 1);

        break;

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
 * ssingh    04-01-2005  BugId: 807      Modified function for proper handling
 *                                       of Adding/Removing Link at SG, when ASP
 *                                       is connected/goes down.
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_INT
UAL_UpdateISS7_RouteInfo(ASP_Entry* aspRec, ASPListNode *prevActive,
                         RK_Context *rk_context, ITS_BOOLEAN flag)
{
    ITS_INT    ret = 0;
    RKListNode *rkListNode = NULL, node;
    ITS_USHORT trId = aspRec->trId;

    /*Find RK_Context is serving in this ASP or not*/
    rkListNode = RKList_FindEntry(aspRec->asList, rk_context->rCtxt);

    if(rkListNode == NULL)
    {
        node.entry = rk_context;
        node.rCtxt = rk_context->rCtxt;
        node.linkCode = ASP_LINK_CODE_MASK;

        ret = RKList_AddEntry(aspRec->asList, &node);

        if(ret == ITS_ENOMEM)
        {
            /*ERROR Handling*/
        }
        else
        {
            rkListNode = RKList_FindEntry(aspRec->asList, rk_context->rCtxt);
        }
    }

    if(prevActive) /*we had an active asp in override*/
    {
        ASP_Entry   *prevASPEntry = NULL;
        RKListNode  *prevRKNode   = NULL;

        ret = ASPTable_FindEntry(prevActive->trId, &prevASPEntry);
        if (ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Error Finding ASP Entry.\n"));

            return !ITS_SUCCESS;
        }

        prevASPEntry -> state = prevActive -> state;

        prevRKNode = RKList_FindEntry(prevASPEntry->asList, rk_context->rCtxt);
        if (prevRKNode != NULL)
        {
            if (UAL_RemLink(rk_context->linkSet, prevRKNode->linkCode) == ITS_SUCCESS)
            {
                prevRKNode->linkCode =
                         ASP_LINK_CODE_MASK; /* We removed the link, but this node serving under
                                              * INACTIVE ASP. And next DOWN on this should not
                                              * remove the actual link.
                                              */
            }
        }
        else
        {
            UAL_ERROR(("Error Getting RK Node.\n"));

            return !ITS_SUCCESS;
        }
    }

    if(trId != ITS_NO_SRC)
    {
        TRANSPORT_Control* trCtrl = NULL;

        /* set the route status to UP */

        /*
         * Adding Link to the linkSet
         */
        trCtrl = TRANSPORT_FindTransport(trId);
        TRANSPORT_UnfindTransport(trCtrl);

        if (trCtrl == NULL)
        {
            UAL_Alarm(4052, __FILE__, __LINE__, NULL);

            UAL_ERROR(("Invalid Transport Id: %d\n", trId));

            return (ITS_EBADTRANSPORT);
        }

        UAL_AddLink(rk_context, rkListNode, trCtrl);

        /*SUA specific */
        if ( UAL_PROTOCOL_TYPE == SCTP_PAYLOAD_SUA)
        {
              /*TODO: check with Narendar. */
        }
    }
    else
    {
        UAL_ERROR(("UAL_UpdateISS7_RouteInfo: Invalid Transport ID.\n"));
    }

    return ret;
}

/* Traffic Management Process*/
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
 *    None. 
 *
 *  Notes:
 *
 *    None.
 *
 *  See Also:
 *
 ******************************************************************************/
static ITS_INT 
ProcessASP_ACTIVE(ASP_Entry* aspRec, ITS_EVENT* ualEvent, ITS_BOOLEAN aspFlag)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_UINT    rKeys[MAX_RKEYS_IN_IE];
    ITS_INT     numKeys = 0;
    ITS_INT     ieCount = 0;
    ITS_UAL_IE  ies[ITS_MAX_UAL_IES];
    ITS_INT     aspId = aspRec->aspId;
    ITS_BOOLEAN isStaticConfig = ITS_FALSE;

    UAL_TRAFFIC_TYPE mode = UAL_MODE_NONE;
    UAL_AS_STATE     prev_as_state[MAX_RKEYS_IN_IE];
    UAL_CB_Context cb_ctxt;

    RKListNode*   rk_nd = NULL;
    ITS_UINT      updatedKeys[MAX_RKEYS_IN_IE];
    ITS_UINT      invalidModeKeys[MAX_RKEYS_IN_IE];
    ITS_UINT      invalidKeys[MAX_RKEYS_IN_IE];
    ITS_UINT      notifyKeys[MAX_RKEYS_IN_IE];
    ITS_USHORT    notifyTrans[MAX_RKEYS_IN_IE];
    ITS_EVENT     retEvent;
    ITS_INT       retLen = 0;
    ITS_INT       imCount = 0, ikCount = 0, nCount = 0, uCount = 0;
    int           i = 0;
    SUA_ASP_LABEL label;
    ITS_USHORT    strid = aspRec->trId;
    ITS_USHORT    rtrid = UAL_MANAGER_INSTANCE;
    int           count = 1; /* Send atleast once */

    if (aspFlag)
    {
        UAL_DEBUG(("ProcessASP_ACTIVE:\n"));

        UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_AC_RECV_ID);
    }

    /* for IPSP dynamic registration*/
    if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
    {
        aspId = aspRec->remoteInfo.aspInfo.aspid;
    }

    /*Init all static arrays*/
    memset(ies,         0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));
    memset(rKeys,       0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(invalidKeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(notifyKeys,  0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(notifyTrans, 0, MAX_RKEYS_IN_IE * sizeof(ITS_USHORT));
    memset(invalidModeKeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));


    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ASPAC_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret)
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_ACTIVE: Decode Failure \n"));
        return ret;  /*TODO: return subsystem error code*/
    }

    for(i = 0; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_ROUT_CTX)
        {
            ret = UAL_DecodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                           ies[i].param_length,
                                           rKeys, &numKeys);
        }
        else if(ies[i].param_id == UAL_PRM_TRAFFIC_MODE)
        {
            mode = ies[i].param_data.trafMode.tm;
        }
        else if(ies[i].param_id == SUA_PRM_DRN_LABEL)
        {
            memcpy(&label, &(ies[i].param_data), sizeof(SUA_ASP_LABEL));
        }
        else if(ies[i].param_id == SUA_PRM_TID_LABEL)
        {
            memcpy(&label, &(ies[i].param_data), sizeof(SUA_ASP_LABEL));
        }
    }

    if(numKeys == 0)
    {
        isStaticConfig = ITS_TRUE;
    }

    if (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        count = 2;
    }

    /* 
     * 1. Get Routing Info from Routing Context.
     * 2. if traffic mode is supported, Update ASP state for 
     *    each routing context.
     * 3. Check if there exist a route for this transport.
     * 4. if route doesn't exist add REMOTE_ROUTE
     * 5. check pending timer for the traffic mode in this active
     * 6. if pending timer is running stop it and send all the 
     *    transactions to the transport id in timer context.
     */

     for(i = 0; i < numKeys || isStaticConfig; i++)
     {
         ITS_UINT     rc_val = 0;
         RK_Context*  rk_context;

         /* get RK_Context from AS Table */
         if(!isStaticConfig)
         {
             rk_context = RKManager_FindEntry(rKeys[i]);
         }
         else
         {
             rk_context = NULL;

             /* 
              *  if it is from static config we iterate the RK list 
              *  for the ASP 
              */

             if(rk_nd == NULL)
             {
                 rk_nd = RKList_Iterate(aspRec->asList);
             }
             else
             {
                 rk_nd = RKList_Iterate(NULL);
             }

             if(rk_nd != NULL)
             {
                 rk_context = RK_LIST_CONTEXT(rk_nd);
             }
         }

         /* Do it for EVERY routing context.
	  * In IPSP update states for the remote routing
	  * contexts (!isMember)
	  */
         if(rk_context != NULL &&
            ((!rk_context->isMember && UAL_IS_IPSP_DOUBLE_EXCHG(UAL_GL_IPSP_TYPE)) ||
              UAL_IS_IPSP_SINGLE_EXCHG(UAL_GL_IPSP_TYPE) ||
              UAL_GL_ITW_MODE == UAL_ITW_SG))
         {
             ASPListNode* prevActive = NULL;
             ASPListNode* aspPresent = NULL; /*Static config*/
             ASPListNode* asp_nd = NULL;
             ITS_BOOLEAN dupAct = ITS_FALSE;

             rc_val = rk_context->rCtxt;

             UAL_DEBUG(("R-CTXT Present: %u \n", rc_val));

             if(rk_context->aspList == NULL)
             {
                 rk_context->aspList = UAL_CreateList();
             }

             if(rk_context->trafficMode != UAL_MODE_NONE &&
                rk_context->trafficMode != mode)
             {
			     if(mode != UAL_MODE_NONE)
				 {
                     invalidModeKeys[imCount++] = rc_val; /* to SendError */
                     continue;
				 }
             }
             else if(rk_context->trafficMode == UAL_OVERRIDE)
             {
             }
             else if(rk_context->trafficMode == UAL_MODE_NONE)
             {
                 rk_context->trafficMode = mode; /*get mode from ACTIVE*/
             }

             asp_nd = ASPList_Iterate(rk_context->aspList);

             for(; asp_nd; asp_nd = ASPList_Iterate(NULL))
             {
                 if((aspId == asp_nd->aspInfo.aspid && aspId != 0) || 
                    asp_nd->trId == aspRec->trId)
                 {
                     /*ASPID matches to the static config ASP WO rctxt*/
                     aspPresent = asp_nd;
                 }

                 if(rk_context->trafficMode == UAL_OVERRIDE)
                 {
                     if(asp_nd->state == UAL_ASP_ACTIVE)
                     {
                         prevActive = asp_nd;/*one ASP serving as ACTIVE*/
                     }
                 }
             }

             /* for ASP/IPSP dynamic registration */
             if (!aspPresent && rk_context->reqState == UAL_AS_REG)
             {
                 UAL_ASP_INFO aspInfoArray[64];
                 ASPListNode aspListEntry;

		         memset(&aspInfoArray, 0, (64 * sizeof(UAL_ASP_INFO)));
		         memset(&aspListEntry, 0, sizeof(ASPListNode));

                 if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
                 {
                     aspInfoArray[i].aspid = aspRec->remoteInfo.aspInfo.aspid;
                 }
                 else
                 {
                     aspInfoArray[i].aspid = aspRec->aspId;
                 }

                 aspListEntry.state = UAL_ASP_ACTIVE;
                 aspListEntry.trId  = aspRec->trId;
                 aspListEntry.aspInfo = aspInfoArray[i];
                 aspListEntry.entry = aspRec;

                 ret = ASPList_AddEntry(rk_context->aspList, &aspListEntry);

                 if (ret != ITS_SUCCESS)
                 {
                     UAL_ERROR(("ProcessASP_ACTIVE: Error adding ASP List"
                                " to RKContext\n"));
                 }
             }

	         if (aspPresent)
             {    
                 if (rk_context->state == UAL_AS_ACTIVE &&
                     aspPresent->state == UAL_ASP_ACTIVE)
                 {
                     UAL_DEBUG(("ProcessASP_ACTIVE:Multiple Active's received"
                                    " from ASP %d\n", aspRec->aspId));
                     dupAct = ITS_TRUE;
                 }
             }

             if (!dupAct && prevActive)
             {
                prevActive->state     = UAL_ASP_INACTIVE;

		        if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
                {
                    prevActive->entry->remoteInfo.state = UAL_ASP_INACTIVE;
                }
		        else
                {
                    prevActive->entry->state = UAL_ASP_INACTIVE;
                }

                notifyKeys[nCount]    = rc_val; /*to Notify*/
                notifyTrans[nCount++] = prevActive->trId;

                if (aspFlag)
                {
                    UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
                    UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_INACTIVE;
                    UAL_CB_CTXT_ASP_ID(&cb_ctxt)    = prevActive->aspInfo.aspid;

                    CALLBACK_CallCallbackList(__UAL_MgntCallBack,
                                             NULL,
                                             (ITS_POINTER)&cb_ctxt);
                }
             }

	         if (aspPresent)
             {
                 aspPresent->entry = aspRec;
                 aspPresent->state = UAL_ASP_ACTIVE; /* ACTIVE ASP */
                 aspPresent->trId  = aspRec->trId;
             }

	         if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
             {
                 aspRec->remoteInfo.state = UAL_ASP_ACTIVE;
             }
	         else
             {
                 aspRec->state = UAL_ASP_ACTIVE;
             }

             if (!dupAct)
             {
                 /* In server mode this is meant for local routes */
                 ret = UAL_CancelPendingTimer(aspRec->trId, rk_context);

                 ret = UAL_UpdateISS7_RouteInfo(aspRec, prevActive,
                                                rk_context, ITS_TRUE);

                 if(ret != ITS_SUCCESS)
                 {
                     continue;
                 }

                 if (aspFlag)
                 {
                     UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
                     UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_ACTIVE;
                     UAL_CB_CTXT_ASP_ID(&cb_ctxt)    = aspRec->aspId;
                     UAL_CB_CTXT_TRANS_ID(&cb_ctxt)  = aspRec->trId;

                     CALLBACK_CallCallbackList(__UAL_MgntCallBack,
                                               NULL,
                                               (ITS_POINTER)&cb_ctxt);
                 }
             }

             prev_as_state[uCount] = rk_context->state;

             updatedKeys[uCount++] = rc_val;

             if (rk_context->state != UAL_AS_ACTIVE)
             {
                 rk_context->state = UAL_AS_ACTIVE; /*Now we are active AS*/

                 UAL_Alarm(4015, __FILE__, __LINE__, "RC %u", rc_val);                 
                 if (aspFlag)
                 {
                     UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_AS_CTXT;
                     UAL_CB_CTXT_AS_STATE(&cb_ctxt) = UAL_AS_ACTIVE;
                     UAL_CB_CTXT_RKEY(&cb_ctxt)     = rc_val;
                     UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = aspRec->trId;

                     CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                              (ITS_POINTER) &cb_ctxt);
                 }
             }
         }
         else
         {
             if(numKeys != 0)
             {
                /*Invalid Routing context from ASP*/
                invalidKeys[ikCount++] = rKeys[i];
             }
 
             isStaticConfig = ITS_FALSE;
         }
     }

    /*
     * 1. Send ASP_ACTIVE_ACK
     * 2. Send Notify message if notify keys present
     * 3. Send InvalidKeys and Unsupported traffic mode 
     *    if there are any keys.
     */

    if (aspFlag)
    {
        /* Build ASP_ACTIVE_ACK*/
        for(i = 0; i < ieCount; i++)
        {
            if(ies[i].param_id == UAL_PRM_ROUT_CTX)
            {
                memset(ies[i].param_data.rCtxt.rCtxt, 0, 
                       sizeof(ies[i].param_data.rCtxt.rCtxt));

                if(uCount > 0)
                {
                    ies[i].param_length = 0; /*reset the length*/

                    ret = UAL_EncodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                                   &ies[i].param_length,
                                                   updatedKeys, uCount);

                    retLen = uCount * sizeof(ITS_UINT);

                    if(ret != ITS_SUCCESS)
                    {
                        UAL_ERROR(("ProcessASP_ACTIVE:"
			                 "Encode Routing context ret"
                                         "value = %d\n", ret));

                        break;
                    }
                }
            }
            else if(ies[i].param_id == UAL_PRM_TRAFFIC_MODE)
            {
               ies[i].param_data.trafMode.tm = mode;
               ies[i].param_length           = sizeof(UAL_TRAFFIC_MODE);
            }
            else if(ies[i].param_id == UAL_PRM_MSG_HDR)
            {
                ies[i].param_data.msgHeader.msgType = UAL_MSG_ASPAC_ACK;
            }

            retLen += ies[i].param_length;
        }

        if(ret == ITS_SUCCESS && uCount > 0)
        {
            ITS_INT  k = 0;

            ITS_EVENT_INIT(&retEvent, rtrid, 256);

            ret = UAL_EncodeMsg(ies, 3 /*four params*/, 
                                &retEvent, &UAL_ASPAC_ACK_Desc);

            if(ret == ITS_SUCCESS)
            {
                if( (ret = TRANSPORT_PutEvent(strid, &retEvent))
                     == ITS_SUCCESS)
                {
                    UAL_DEBUG(("ASP_ACTIVE_ACK send success:\n"));

                    UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_ACACK_SENT_ID);
                }
                else
                {
                    UAL_ERROR(("ASP_ACTIVE_ACK send ret val = %d\n",
                                       ret));
                }
            }
            else
            {
                UAL_ERROR(("Encoding of ASP ACTIVE ACK failed:\n"));
            }

            while(k < uCount)
            {
                RK_Context* notify_change = NULL;
                ITS_UINT    rc = 0;

                if(prev_as_state[k] != UAL_AS_ACTIVE)
                {
                    ASPListNode* aspListNode = NULL;
                
                    rc = updatedKeys[k];

                    notify_change = RKManager_FindEntry(rc);

                    if(notify_change == NULL)
                    {
                        continue;
                    }

                    aspListNode = ASPList_Iterate(notify_change->aspList);

                    for(;aspListNode; aspListNode = ASPList_Iterate(NULL))
                    {
                       if(aspListNode->state == UAL_ASP_DOWN)
                       {
                           continue;
                       }

                       /*Notify AS STATE change*/
                       ret = UAL_SendNotify(aspListNode->trId, 
                                            UAL_ST_TYPE_AS_STAT_CHG,
                                            UAL_ST_ID_AS_ACTIVE, 
                                            &rc, 1, 0);
                    }
                }
                k++;
            }
        }

        while(nCount > 0)
        {
            nCount--;

            /*TODO: Reduce Number of Sends here
                    remember number of rctxts are per transport base
             */
            ret = UAL_SendNotify(notifyTrans[nCount], UAL_ST_TYPE_OTHER,
                                 UAL_ST_ALT_ASP_ACTIVE, &notifyKeys[nCount],
				 1, aspId);

            if(ret == ITS_SUCCESS)
            {
                UAL_DEBUG(("ALTERNATE_ASP_ACTIVE send to the TR-ID = 0x%02x\n",
                                  notifyTrans[nCount]));
            }
            else
            {
                UAL_ERROR(("Notify ALTERNATE_ASP_ACTIVE send to TR-ID = 0x%02x\n",
                                  notifyTrans[nCount]));
            }
        } 
    }
    else
    {
        /* for IPSP single exchange client, send notify to remote for the
          AS state change  */
        ITS_INT  k = 0;
        while(k < uCount)
        {
            RK_Context* notify_change = NULL;
            ITS_UINT    rc = 0;
 
            if(prev_as_state[k] != UAL_AS_ACTIVE)
            {
                ASPListNode* aspListNode = NULL;
 
                rc = updatedKeys[k];
 
                notify_change = RKManager_FindEntry(rc);
 
                if(notify_change == NULL)
                {
                    continue;
                }
 
                aspListNode = ASPList_Iterate(notify_change->aspList);
 
                for(;aspListNode; aspListNode = ASPList_Iterate(NULL))
                {
                    if(aspListNode->state == UAL_ASP_DOWN)
                    {
                        continue;
                    }
 
                    /* Notify AS STATE change */
                    ret = UAL_SendNotify(aspListNode->trId,
                                         UAL_ST_TYPE_AS_STAT_CHG,
                                         UAL_ST_ID_AS_ACTIVE,
                                         &rc, 1, 0);
               }
            }
 
            k++;
        }
    }

    /* ASSUMPTION: In IPSP single exchange server mode there should 
     *             not be any invalid routing contexts.
     */
    /*Send Invalid mode keys*/
    if(imCount > 0)
    {
        ITS_UAL_IE modeIes[1];
        ITS_INT    modeCount = 1;

        modeIes[0].param_id = UAL_PRM_ROUT_CTX;

        ret = UAL_EncodeRoutingContext(modeIes[0].param_data.rCtxt.rCtxt,
                                      &modeIes[0].param_length,
                                      invalidModeKeys, imCount);
        if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Encode R-CTXT ret value = %d\n", ret));
        }
        else
        {
            ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNSU_THM, modeIes, modeCount);
        }
    }

    /*Send Invalid routing contexts if there are any*/
    if(ikCount > 0)
    {
        ITS_UAL_IE errIes[1];
        ITS_INT    errCount = 1;

        errIes[0].param_id = UAL_PRM_ROUT_CTX;

        ret = UAL_EncodeRoutingContext(errIes[0].param_data.rCtxt.rCtxt,
                                      &errIes[0].param_length,
                                      invalidKeys, ikCount);
        if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Encode R-CTXT ret value = %d\n", ret));
        }
        else
        {
            ret = UAL_SendERR(aspRec->trId, UAL_ERR_INV_ROUT_CTXT, errIes,
			      errCount);
        }
    }

    if (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        UpdateLocalRoutingKeys(aspRec, ITS_FALSE);
    }

    if (UAL_IS_IPSP_DE_SERVER(UAL_GL_IPSP_TYPE))
    {
        UpdateLocalRoutingKeys(aspRec, ITS_TRUE);
    }
    return ret;
}

static ITS_INT 
ProcessASP_ACTIVE_ACK(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_INT    ret = ITS_SUCCESS;
    ITS_UINT   rKeys[MAX_RKEYS_IN_IE];
    ITS_INT    nkeys = 0;
    ITS_INT    ieCount = 0;
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    TRANSPORT_Control *trCtrl = NULL;
    
    UAL_CB_Context   cb_ctxt;
    UAL_TRAFFIC_TYPE mode = UAL_MODE_NONE;
    int i = 0;        /*counters for loops*/
    memset(rKeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(ies,   0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    UAL_DEBUG(("ProcessASP_ACTIVE_ACK:\n"));

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ASPAC_ACK_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_ERROR(("ProcessASP_ACTIVE_ACK : Decode Failure decode ret val = %d\n", ret));

        return ret;
    }

    if( aspRec->ackTimer[ASP_ACTIVE_MSG] != (ITS_SERIAL)0)
    {
        TIMERS_CancelTimer(aspRec->ackTimer[ASP_ACTIVE_MSG]);
        aspRec->ackTimer[ASP_ACTIVE_MSG] = (ITS_SERIAL)0;
        memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
    }
    else
    {
        UAL_DEBUG(("ProcessASP_ACTIVE_ACK: Unexpected message, Discarding!! \n"));
	return ITS_EBADSTATE;
    }
    
    UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_ACACK_RECV_ID);
    for(; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_TRAFFIC_MODE)
        {
            mode = ies[i].param_data.trafMode.tm;
        }
        else if(ies[i].param_id == UAL_PRM_ROUT_CTX)
        {
            ret = UAL_DecodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                           ies[i].param_length,
                                           rKeys, &nkeys);
        }
    }

    /*
     * Generate only one Notification in case of multiple
     * RCs
     */
    UAL_CB_CTXT_TYPE(&cb_ctxt) = UAL_CB_ASP_CTXT;
    UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_ACTIVE;
    UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = aspRec->trId;

    CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                              (ITS_POINTER)&cb_ctxt);

    aspRec->state = UAL_ASP_ACTIVE; /*Update local ASP State*/

    /* update server's state if is single exchange client */ 
    if (UAL_IS_IPSP_SE_CLIENT(UAL_GL_IPSP_TYPE))
    {
        aspRec->remoteInfo.state = UAL_ASP_ACTIVE;
    }

    trCtrl = TRANSPORT_FindTransport(aspRec->trId);
    TRANSPORT_UnfindTransport(trCtrl);
    if(trCtrl == NULL)
    {
        UAL_Alarm(4052, __FILE__, __LINE__, NULL);
 
        UAL_ERROR(("\nProcessASP_ACTIVE_ACK:Transport not found\n"));
        return ITS_EBADTRANSPORT;
    }
    
    UAL_DEBUG(("\nProcessASP_ACTIVE_ACK:Setting the transport state to TRUE..RESUME\n"));
    TRANSPORT_SetState(trCtrl, ITS_TRUE);

    for(i = 0; i < nkeys; i++)
    {
        ASPListNode* aspListNode    = NULL;
        RK_Context*  rk_ctxt = NULL;

        rk_ctxt = RKManager_FindEntry(rKeys[i]);

        if(rk_ctxt != NULL)
        {
            aspListNode = ASPList_Iterate(rk_ctxt->aspList);

            for(; aspListNode; aspListNode = ASPList_Iterate(NULL))
            {
                if(aspListNode->trId == aspRec->trId)
                {
                    aspListNode->state = UAL_ASP_ACTIVE;
                }
            }

            rk_ctxt->state = UAL_AS_ACTIVE;

            UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_AS_CTXT;
            UAL_CB_CTXT_AS_STATE(&cb_ctxt) = UAL_AS_ACTIVE;
            UAL_CB_CTXT_RKEY(&cb_ctxt)     = rKeys[i];
            UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = aspRec->trId;

            CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL,
                                      (ITS_POINTER) &cb_ctxt);
    
        if (rk_ctxt->isMember && 
            (UAL_GL_ITW_MODE == UAL_ITW_IPSP))
        {
            aspListNode = ASPList_FindEntry(rk_ctxt->aspList, 0);
            }
            mode = rk_ctxt->trafficMode;
        }
    }

    return ret;
}

/*  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-25-2008   BugId: 935    ASP is not changing its own state 
 *                                        after ASP INACTIVE procedure in LoadShareMode 
 */

static ITS_INT
ProcessASP_INACTIVE(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_INT    ret     = ITS_SUCCESS;
    ITS_INT    nkeys   = 0;
    ITS_INT    ieCount = 0;
    ITS_UINT   rkeys[MAX_RKEYS_IN_IE];
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    ITS_UINT   errKeys[MAX_RKEYS_IN_IE];
    ITS_UINT   regKeys[MAX_RKEYS_IN_IE];
    ITS_UINT   invalidModeKeys[MAX_RKEYS_IN_IE];
    RKListNode* rk_nd = NULL;
    ITS_EVENT  retEvent;
    ITS_INT    retLen = 0;
    ITS_BOOLEAN imFlag = ITS_FALSE; /*to send invalid mode*/
    UAL_TRAFFIC_TYPE tmode = UAL_MODE_NONE;
    UAL_CB_Context cb_ctxt;
    ITS_BOOLEAN do_process = ITS_TRUE;
    int i = 0, eCount = 0, rCount = 0, imCount = 0;

    memset(rkeys,   0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(errKeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(regKeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(invalidModeKeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(ies,     0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));
    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    UAL_DEBUG(("ProcessASP_INACTIVE:\n"));

    UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_IA_RECV_ID);

    /* decode message */
    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ASPIA_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_DEBUG(("ProcessASP_INACTIVE: Decode Failure \n"));
        return ret;
    }


    for(; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_ROUT_CTX)
        {
            ret = UAL_DecodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                           ies[i].param_length,
                                           rkeys, &nkeys);

            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Decode R-CTXT ret val = %d\n", ret));
            }
        }
        else if(ies[i].param_id == UAL_PRM_TRAFFIC_MODE)
        {
             tmode = ies[i].param_data.trafMode.tm;
        }
    }

    i = nkeys;

    if (ret == ITS_SUCCESS)
    {
        UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
        UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_INACTIVE;
        UAL_CB_CTXT_TRANS_ID(&cb_ctxt) =  aspRec->trId;
        if (UAL_GL_ITW_MODE != UAL_ITW_IPSP)
        {
            UAL_CB_CTXT_ASP_ID(&cb_ctxt) = aspRec->aspId;
        }
        else
        {
            UAL_CB_CTXT_ASP_ID(&cb_ctxt) = aspRec->remoteInfo.aspInfo.aspid;
        } 

        CALLBACK_CallCallbackList(__UAL_MgntCallBack,
                                  NULL,
                                  (ITS_POINTER)&cb_ctxt);
    }

    for(rk_nd = RKList_Iterate(aspRec->asList);do_process;)
    {
        RK_Context* rk_context = NULL;
        ASPListNode* asp_nd     = NULL;
        static ITS_BOOLEAN flag = ITS_FALSE; /*for no R-CTXTs in inactive*/

        if(nkeys == 0) /*we receive no R-CTXTs in INACTIVE*/
        {
            if(flag)
            {
                rk_nd = RKList_Iterate(NULL);
            }

            if(rk_nd == NULL)
            {
                do_process = ITS_FALSE;

                continue;
            }

            rk_context = RK_LIST_CONTEXT(rk_nd);
            flag = ITS_TRUE;
        }
        else /*if you have any R-CTXTs in INACTIVE*/
        {
            rk_context = RKManager_FindEntry(rkeys[--i]);

            if(i == 0)
            {
                do_process = ITS_FALSE;
            }

            if(rk_context == NULL)
            {
                /*Invalid Routing context from ASP*/
                errKeys[eCount++] = rkeys[i];

                continue;
            }
        }

        if(rk_context->trafficMode != tmode &&
           tmode != UAL_MODE_NONE)
        {
            /*send invalid traffic mode error; */
            invalidModeKeys[imCount++] = rkeys[i];
            imFlag = ITS_TRUE;

            continue;
        }

        asp_nd = ASPList_FindEntry(rk_context->aspList, aspRec->trId);

        if(asp_nd == NULL)
        {
            UAL_ERROR(("ASP is not part of this R-CTXT = %u"
                            "TR-ID 0x%02x\n", rk_context->rCtxt, 
                             aspRec->trId));
        }
        else
        {
            RKListNode* rkListNode = NULL;
            SS7_LinkPtr linkPtr = NULL;
            SS7_LinkSetPtr linkSetPtr = NULL;

            rkListNode = RKList_FindEntry(aspRec->asList, rk_context->rCtxt);

            linkPtr = LINK_FindLink(rk_context->linkSet, rkListNode->linkCode);
            if (linkPtr == NULL)
            {
                UAL_ERROR(("Error finding Link\n"));
            }
            else
            {
                ret = LINK_RemLink(rk_context->linkSet, linkPtr);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error removing link.\n"));
                }
            }

            /*
             * check if we have to set the linkset to down, that is no more links
             * available. 
             */

            linkSetPtr = LINKSET_FindLinkSet(rk_context->linkSet);
            if (linkSetPtr == NULL)
            {
                UAL_ERROR(("Error finding LinkSet: %d\n", rk_context->linkSet));
            }
            else if (linkSetPtr->numLinks == 0)
            {
                ret = LINKSET_SetLinkSetState(linkSetPtr, ITS_FALSE);
                if (ret != ITS_SUCCESS)
                {
                    UAL_ERROR(("Error changing LinkSet: %d to DOWN. \n",
                                      rk_context->linkSet));
                }
            }
            
            asp_nd->state = UAL_ASP_INACTIVE;

            if(UAL_CheckASPending(rk_context))
            {
                rk_context->state = UAL_AS_PENDING; /*update to pending state*/
                ret = UAL_StartPendingStateProcedure(rk_context);

                if (ret == ITS_SUCCESS && rk_context->pendingTrans != NULL)
                {
                    UAL_CB_CTXT_TYPE(&cb_ctxt)     = UAL_CB_AS_CTXT;
                    UAL_CB_CTXT_AS_STATE(&cb_ctxt) = UAL_AS_PENDING;
                    UAL_CB_CTXT_RKEY(&cb_ctxt)     = rk_context->rCtxt;
                    UAL_CB_CTXT_TRANS_ID(&cb_ctxt) = 
                                   TRANSPORT_INSTANCE(rk_context->pendingTrans); 

                    CALLBACK_CallCallbackList(__UAL_MgntCallBack,
                                              NULL,
                                              (ITS_POINTER)&cb_ctxt);
                }
            }

            if (UAL_GL_ITW_MODE == UAL_ITW_IPSP)
            {
               aspRec->remoteInfo.state = deriveASPStateFromRCtxt(aspRec);
            }
            else
            {
               aspRec->state = deriveASPStateFromRCtxt(aspRec);
            }
           
        }

        regKeys[rCount++] = rk_context->rCtxt;
    }

    ret = ITS_SUCCESS; /*Reset the val*/
    /*Send INACTIVE ACK*/
    for(i = 0; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_ROUT_CTX && (rCount > 0))
        {
            ret = UAL_EncodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                           &ies[i].param_length,
                                           regKeys, rCount);

            retLen += ies[i].param_length;

            if(ret != ITS_SUCCESS)
            {
                UAL_ERROR(("Encode RoutingContext Ret Val = %d\n",
                                  ret));
            }
        }
        else if(ies[i].param_id == UAL_PRM_MSG_HDR)
        {
            ies[i].param_data.msgHeader.msgType = UAL_MSG_ASPIA_ACK;

            retLen += ies[i].param_length;
        }
    }

    retLen += 8;

    if(ret == ITS_SUCCESS && (rCount > 0))
    {
        ITS_EVENT_INIT(&retEvent, UAL_MANAGER_INSTANCE, retLen);
        ret = UAL_EncodeMsg(ies, 2 /*num of params*/, &retEvent, 
                            &UAL_ASPIA_ACK_Desc);

        if(ret == ITS_SUCCESS)
        {
            ret = TRANSPORT_PutEvent(aspRec->trId, &retEvent);

            if(ret != ITS_SUCCESS)
            {
                UAL_DEBUG(("INACTIVE_ACK send ret val = %d\n",
                                    ret));
            }
            else
            {
                UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_IAACK_SENT_ID);
            } 
        }
    }

    /*Send ERROR Msg for invalid Routing keys*/
    if(eCount > 0)
    {
        ITS_UAL_IE errIes[1];
        ITS_INT    errCount = 1;

        errIes[0].param_id = UAL_PRM_ROUT_CTX;

        ret = UAL_EncodeRoutingContext(errIes[0].param_data.rCtxt.rCtxt,
                                      &errIes[0].param_length,
                                      errKeys, eCount);
        if(ret != ITS_SUCCESS)
        {
            UAL_ERROR(("Encode R-CTXT ret value = %d\n", ret));
        }
        else
        {
            ret = UAL_SendERR(aspRec->trId, UAL_ERR_INV_ROUT_CTXT, errIes, errCount);
        }
    }

    if(imFlag)
    {
        ITS_UAL_IE mies[10];
        ITS_INT    retVal = 0;

        retVal = UAL_EncodeRoutingContext(mies[0].param_data.rCtxt.rCtxt,
                                          &mies[0].param_length,
                                          invalidModeKeys,imCount);

        mies[0].param_id = UAL_PRM_ROUT_CTX;

        retVal = UAL_SendERR(aspRec->trId, UAL_ERR_UNSU_THM,
                             mies, 1);
    }

    if (UAL_IS_IPSP_SE_SERVER(UAL_GL_IPSP_TYPE))
    {
        UpdateLocalRoutingKeys(aspRec, ITS_TRUE);
    }
 
    if (UAL_IS_IPSP_DOUBLE_EXCHG(UAL_GL_IPSP_TYPE))
    {
        UpdateLocalRoutingKeys(aspRec, ITS_FALSE);
    }

    return ret;
}

/*
 * Cancel Retransmit timer and start IPSP pending
 * Procedures if the the application is running as
 * IPSP mode.
 */
static void
Cancel_RTXT_TimerAndStartIPSPPendingTimer(ASP_Entry *aspRec, RK_Context *rk_context)
{
    if (aspRec->ackTimer[rk_context->trafficMode] != (ITS_SERIAL)0)
    {
        TIMERS_CancelTimer(aspRec->ackTimer[rk_context->trafficMode]);
        aspRec->ackTimer[rk_context->trafficMode] = (ITS_SERIAL)0;
        memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
    }

    if(UAL_GL_ITW_MODE == UAL_ITW_IPSP) /* Not for ASP*/
    {
        /*May need to start pending procedures*/
        if(UAL_CheckASPending(rk_context))
        {
             UAL_StartPendingStateProcedure(rk_context);
        }
    }

    return;
	
}

/*  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  kramesh    05-25-2008   BugId: 935    ASP is not changing its own state 
 *                                        after ASP INACTIVE procedure in LoadShareMode 
 */
 
static ITS_INT 
ProcessASP_INACTIVE_ACK(ASP_Entry* aspRec, ITS_EVENT* ualEvent)
{
    ITS_INT    ret     = ITS_SUCCESS;
    ITS_INT    nkeys   = 0;
    ITS_INT    ieCount = 0;
    ITS_UINT   rkeys[MAX_RKEYS_IN_IE];
    ITS_UAL_IE ies[ITS_MAX_UAL_IES];
    RKListNode* rk_nd;
    int i = 0;
    ITS_BOOLEAN strayInactiveAck = ITS_FALSE;
    UAL_ASP_STATE preState = aspRec->state;
    UAL_CB_Context cb_ctxt;    

    memset(&cb_ctxt, 0, sizeof(UAL_CB_Context));

    memset(rkeys, 0, MAX_RKEYS_IN_IE * sizeof(ITS_UINT));
    memset(ies,   0, ITS_MAX_UAL_IES * sizeof(ITS_UAL_IE));

    UAL_DEBUG(("ProcessASP_INACTIVE_ACK\n"));

    UAL_IncrementMIBStats(aspRec->trId, UAL_PEG_IAACK_RECV_ID);

    /* decode message */

    ret = UAL_DecodeMsg(ies, &ieCount, ualEvent, &UAL_ASPIA_ACK_Desc);
    CHECK_UAL_DECODEMSG_ERROR(aspRec->trId, ret);
    if(ret != ITS_SUCCESS)
    {
        UAL_ERROR(("ProcessASP_INACTIVE_ACK Decode Failure  ret val = %d\n", ret));
        return ret;
    }

    if(aspRec->ackTimer[ASP_INACTIVE_MSG] != (ITS_SERIAL)0)
    {
        TIMERS_CancelTimer(aspRec->ackTimer[ASP_INACTIVE_MSG]);
        aspRec->ackTimer[ASP_INACTIVE_MSG] = (ITS_SERIAL)0;
        memset(&aspRec->timerCtx, 0, sizeof(UAL_TimerCtx));
    }
    else
    {
        strayInactiveAck = ITS_TRUE;
    }

    UAL_DEBUG(("\nProcessASP_INACT_ACK: strayInactiveAck %d, preState %d\n", strayInactiveAck, preState));
    aspRec->state = UAL_ASP_INACTIVE;
    
    for(; i < ieCount; i++)
    {
        if(ies[i].param_id == UAL_PRM_ROUT_CTX)
        {
            ret = UAL_DecodeRoutingContext(ies[i].param_data.rCtxt.rCtxt,
                                           ies[i].param_length,
                                           rkeys, &nkeys);

            if(ret != ITS_SUCCESS)
            {
                UAL_DEBUG(("Decode R-CTXT ret val = %d\n", ret));
            }
        }
    }


    /* Check if we have received any routing context 
     * and generate a array of rCtxt for processing
    */
    RK_Context* rk_Context[MAX_RKEYS_IN_IE] = {NULL};
    int rk_count = 0;

    if(nkeys == 0)
    {
        // consider all rctxt
        rk_nd = RKList_Iterate(aspRec->asList);
        for(;rk_nd;rk_nd = RKList_Iterate(NULL))
        {
            rk_Context[rk_count++] = RK_LIST_CONTEXT(rk_nd);

         }
    }
    else
    {
        i = nkeys;
        while(i >= 0)
        {
            /* add rk_ctxt to the array only if it is non-null */
            if((rk_Context[rk_count] = RKManager_FindEntry(rkeys[--i])) == NULL)
            {
                continue;
            }
            rk_count++;
         }
    }

    ASPListNode* asp_nd = NULL;
    int count = 0;
    for(count = 0; count < rk_count; count++)
    {
       asp_nd = ASPList_FindEntry(rk_Context[count]->aspList,
                                       aspRec->trId);


       if(asp_nd != NULL)
       {
          asp_nd->state = UAL_ASP_INACTIVE;
       }

       if(UAL_GL_ITW_MODE == UAL_ITW_IPSP)
       {
          aspRec->remoteInfo.state = deriveASPStateFromRCtxt(aspRec);
       }
       else
       {
          aspRec->state = deriveASPStateFromRCtxt(aspRec);
       }

       if (rk_Context[count]->state == UAL_AS_ACTIVE)
       {
           /* We didn't send INACTIVE but we got INACTIVE_ACK
            * Set the AS and ASP states to INACTIVE
            */
          rk_Context[count]->state = UAL_AS_INACTIVE;
       }

       Cancel_RTXT_TimerAndStartIPSPPendingTimer(aspRec, rk_Context[count]);
    }
    UAL_DEBUG(("\n1ProcessASP_INACT_ACK: strayInactiveAck %d\n", strayInactiveAck));

    /* Calling Management Callback */ 
    UAL_CB_CTXT_TYPE(&cb_ctxt)      = UAL_CB_ASP_CTXT;
    UAL_CB_CTXT_ASP_STATE(&cb_ctxt) = UAL_ASP_INACTIVE;
    UAL_CB_CTXT_TRANS_ID(&cb_ctxt) =  aspRec->trId;

    UAL_CB_CTXT_ASP_ID(&cb_ctxt) = aspRec->aspId;
    UAL_CB_CTXT_ASP_ID(&cb_ctxt) = aspRec->remoteInfo.aspInfo.aspid;

    CALLBACK_CallCallbackList(__UAL_MgntCallBack,
                                  NULL,
                                 (ITS_POINTER)&cb_ctxt);

    if(strayInactiveAck == ITS_TRUE)
    {
        UAL_DEBUG(("\nProcessASP_INACT_ACK: Inside %d\n", strayInactiveAck));
        if(preState == UAL_ASP_ACTIVE)
        {
            UAL_DEBUG(("\nProcess_ASP_INACT_ACK: Previous State is ACTIVE, hence go back...\n"));
    	    SendActiveOrInactiveMsg(UAL_CMD_ASP_ACTIVE, aspRec->trId, UAL_ASP_ACTIVE);
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
ITS_INT
UAL_HandleTrafficMaintMsg(ITS_EVENT* ualEvent, ITS_OCTET msgType,
                          ASP_Entry* aspRec)
{
    int ret = ITS_SUCCESS;
    ITS_INT errCode = 0;
    ITS_BOOLEAN errFlag = ITS_FALSE;
    ITS_UAL_IE diagnInfo;
   
    UAL_DEBUG(("UAL_HandleTrafficMainMsg:\n"));

    if(aspRec == NULL)
    {
        UAL_ERROR(("NO ASP Record present:\n"));

        return !ret;
    }

    switch(msgType)
    {
    case UAL_MSG_ASPAC:

        UAL_DEBUG(("UAL_HandleTrafficMaintMsg: Received ASPAC message "
                         "on Assoc %04x.\n", aspRec->trId)); 

        if(UAL_GL_ITW_MODE == UAL_ITW_IPSP) 
        {
           if(aspRec->remoteInfo.state == UAL_ASP_DOWN)
           {
               errFlag = ITS_TRUE; 
           }
        }
        else
        { 
            if(aspRec->state == UAL_ASP_DOWN)
            {
                 errFlag = ITS_TRUE;
            }
        }

        if(errFlag)
        {
            UAL_Alarm(4012, __FILE__, __LINE__, "TransportId %x", aspRec->trId);

            UAL_ERROR(("UAL_HandleTrafficMaintMsg: Send an Unexpected"
                           " Message.\n"));

            errCode = UAL_ERR_UNEPECTED_MSG;
        }
        else
        {
            ret = ProcessASP_ACTIVE(aspRec, ualEvent, ITS_TRUE);

            /*CALLBACK_CallCallbackList(__UAL_MgntCallBack, NULL, 
             *                         (ITS_POINTER)ualEvent);
             */
        }

        break;

    case UAL_MSG_ASPAC_ACK:

        UAL_DEBUG(("UAL_HandleTrafficMaintMsg: Received ASPAC_ACK "
                         "message on Assoc %04x.\n", aspRec->trId));

        ret = ProcessASP_ACTIVE_ACK(aspRec, ualEvent);

        break;

    case UAL_MSG_ASPIA:
 
        UAL_DEBUG(("UAL_HandleTrafficMaintMsg: Received ASPIA message "
                         "on Assoc %04x.\n", aspRec->trId)); 

        UAL_Alarm(4014, __FILE__, __LINE__, "TransportId %x", aspRec->trId);

        ret = ProcessASP_INACTIVE(aspRec, ualEvent);

        break;
  
    case UAL_MSG_ASPIA_ACK:

        UAL_DEBUG(("UAL_HandleTrafficMaintMsg: Received ASPIA_ACK "
                         "message on Assoc %04x.\n", aspRec->trId)); 

        UAL_Alarm(4013, __FILE__, __LINE__, "TransportId %x", aspRec->trId);

        ret = ProcessASP_INACTIVE_ACK(aspRec, ualEvent);

        break;

    default:

        UAL_ERROR(("UAL_HandleTrafficMaintMsg: Received invalid Msg "
                         "Type: %02x.\n", msgType));
        UAL_Alarm(4026, __FILE__, __LINE__, "TransportId %x", aspRec->trId);

        /*Build and send Diagnostic Info param*/
        diagnInfo.param_id = UAL_PRM_DIAGNOSTIC;
        if (ualEvent->len < UAL_MAX_DIAG_INFO_LEN)
        {
            diagnInfo.param_length = ualEvent->len;
            memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                   ualEvent->data, ualEvent->len);
        }
        else
        {
            diagnInfo.param_length = UAL_MAX_DIAG_INFO_LEN;
            memcpy(diagnInfo.param_data.diagInfo.diagnosticInfo,
                 ualEvent->data, UAL_MAX_DIAG_INFO_LEN);
        }
        ret = UAL_SendERR(aspRec->trId, UAL_ERR_UNSUP_MSG_TYPE,
              &diagnInfo, 1);

        break;

    }

    if(errCode != 0)
    {
       ret = UAL_SendERR(aspRec->trId, errCode, NULL, 0);
    }

    return ret;
}


static char* Get_ASCII_UALError(ITS_INT code)
{
    switch(code)
    {
    case UAL_ERR_INV_VESION:
        return "Invalid Version";

    case UAL_ERR_UNSUP_MSG_CLASS:
        return "Unsupported Message Class";

    case UAL_ERR_UNSUP_MSG_TYPE:
        return "Unsupported Message Type";

    case UAL_ERR_UNSU_THM:
        return "Unsupported Traffic Mode";

    case UAL_ERR_UNEPECTED_MSG:
        return "Unexpected Message";

    case UAL_ERR_PROT_ERROR:
        return "Protocol Error";

    case UAL_ERR_INV_STREAM_ID:
        return "Invalid Stream Indentifier";

    case UAL_ERR_REF_MGNT_BLOCK:
        return "Refused-Management Blocking";

    case UAL_ERR_ASP_ID_REQUIERED:
        return "ASP Identifier Required";

    case UAL_ERR_INV_ASP_ID:
        return "Invalid ASP Identifier";

    case UAL_ERR_INV_ROUT_CTXT:
        return "Invalid Routing Context";

    case UAL_ERR_INV_PARM_VALUE:
        return "Invalid Parameter Value";

    case UAL_ERR_PARM_FIELD_ERR:
        return "Parameter Field Error";

    case UAL_ERR_UNEXP_PARAM:
        return "Unexpected Paramter";

    case UAL_ERR_DEST_STAT_UNKNOW:
        return "Destination Status Unknown";

    case UAL_ERR_INV_NET_APP:
        return "Invalid Network Appearance";

    case UAL_ERR_NO_CONF_AS_FOR_ASP:
        return "No configured AS for ASP";
    }

    return "Unknown Error Code";
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose: To get the state for the ASP depending on the individual 
 *           states of the rCtxt. If any of the rCtxt state is ACTIVE
 *           the state of th ASP is ACTIVE, otherwise INACTIVE.
 *
 *  Input Parameters: Address of ASP Entry Record
 *
 *  Input/Output Parameters:
 *
 *     None.
 *
 *  Output Parameters:
 *
 *     None.
 *
 *  Return Value:  ASP state to be maintained
 *
 *
 *  Notes:
 *
 *     None.
 *
 *  See Also:
 *
 ******************************************************************************/
ITS_UINT deriveASPStateFromRCtxt(ASP_Entry *aspRec)
{
   ITS_UINT ret = UAL_ASP_INACTIVE;
   ITS_OCTET numOfAsInAsp = 0;
   RKListNode *rk = ((RKListNode *)ASPList_Iterate(aspRec->asList));

   for(; rk; rk = (RKListNode *)ASPList_Iterate(NULL))
   {
      if(rk->entry->state == UAL_AS_ACTIVE)
      {
         numOfAsInAsp++;
      }
   }
  
   /* If the ASP is part of more than one AS and the Inactive Message 
      is received for a particular AS (Routing Context), the ASP
      state should be ACTIVE, else if the ASP is part of only one AS or
      if there are no AS in ACTIVE state, the ASP state should be
      INACTIVE D0200 04-june-2008 
   */
   UAL_DEBUG(("\nderiveASPStateFromAS: num of Active AS in ASP %d\n", numOfAsInAsp));

   if(numOfAsInAsp > 1)
   {
       ret = UAL_ASP_ACTIVE;
   }

   return ret;
}


