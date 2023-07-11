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
 *  ID: $Id: mtp3.c,v 9.1 2005/03/23 12:56:16 cvsadmin Exp $
 * LOG: $Log: mtp3.c,v $
 * LOG: Revision 9.1  2005/03/23 12:56:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1  2003/07/22 19:34:09  lbana
 * LOG: Bug fixes in mtp3.c and transport.c file for ECT.
 * LOG:
 * LOG: Revision 7.2  2002/11/26 21:04:15  ngoel
 * LOG: merge prc changes from pr6.2
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:11:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/01 16:02:57  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/07/31 20:26:48  sjaddu
 * LOG: opc,dpc in mtp3 indication.
 * LOG:
 * LOG: Revision 6.3  2002/06/04 20:46:36  mmiers
 * LOG: Get the right message type
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:30:38  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:15:04  mmiers
 * LOG: Begin PR7.
 * LOG: Revision 5.7.2.1  2002/04/18 19:59:06  sjaddu
 * LOG: NMS 3.8 changes in PR6
 * LOG:
 * LOG: Revision 5.7  2002/02/15 23:11:57  ssharma
 * LOG: Set the transport state on activation.
 * LOG:
 * LOG: Revision 5.6  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.5  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 5.4  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.3  2001/11/07 20:54:23  randresol
 * LOG: Fix memory leak in NMSRetrieveMTP3Message
 * LOG:
 * LOG: Revision 5.2  2001/10/05 22:59:42  mmiers
 * LOG: NMS MTP2 API is taking shape.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:34  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2001/02/28 15:58:52  hxing
 * LOG: Problem fixed with Enqueue
 * LOG:
 * LOG: Revision 3.2  2000/12/06 22:52:24  hxing
 * LOG: ISUP integration.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:10:51  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/05/11 22:12:08  randresol
 * LOG: Intetration with VMI
 * LOG:
 * LOG: Revision 2.3  2000/01/29 00:10:46  rsonak
 * LOG:
 * LOG: Added externs for MTP3 and SCCP management callback managers
 * LOG:
 * LOG: Revision 2.2  2000/01/28 00:47:06  rsonak
 * LOG:
 * LOG: Commit the PR2 patch. Added MTPS Pause and Resume callbacks for the STANDALONE
 * LOG: and INTEGRATED cases
 * LOG:
 * LOG: Revision 2.1  2000/01/25 23:46:37  mmiers
 * LOG:
 * LOG:
 * LOG: Missing ev.src
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:33:15  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.11  1999/11/06 00:02:59  mmiers
 * LOG:
 * LOG:
 * LOG: Do it right.
 * LOG:
 * LOG: Revision 1.10  1999/11/05 23:29:36  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitize the build.  Single configuration now.
 * LOG:
 * LOG: Revision 1.9  1999/10/07 17:43:48  mmiers
 * LOG:
 * LOG:
 * LOG: Try to bring some sanity to the build process.
 * LOG:
 * LOG: Revision 1.8  1999/10/06 22:12:43  cbascon
 * LOG:
 * LOG: Temporary change. Added #defines for disregarding SCCP and TCAP if only MTP3 is needed
 * LOG:
 * LOG: Revision 1.7  1999/09/24 19:34:02  ite
 * LOG:
 * LOG: fhasle: fixed some bugs in MTP3.
 * LOG:
 * LOG: Revision 1.6  1999/06/21 22:28:15  ite
 * LOG:
 * LOG: Don't invert the logic.  Duh.
 * LOG:
 * LOG: Revision 1.5  1999/06/21 22:22:22  ite
 * LOG:
 * LOG:
 * LOG: Make sure all code is aware of integrated vs. standalone.
 * LOG:
 * LOG: Revision 1.4  1998/11/13 18:42:11  mmiers
 * LOG: Fix this up for HNS.
 * LOG:
 * LOG: Revision 1.3  1998/10/28 00:27:19  mmiers
 * LOG: More fixes for NMS SCCP/MTP3.
 * LOG:
 * LOG: Revision 1.2  1998/10/27 21:08:55  mmiers
 * LOG: Finish up round 1 of NMS/SCCP integration.
 * LOG:
 * LOG: Revision 1.1  1998/09/28 19:23:26  mmiers
 * LOG: Update other vendor libraries for MTP3.
 * LOG:
 * LOG: Revision 1.2  1998/09/28 17:40:45  mmiers
 * LOG: Add Init, Term methods.
 * LOG:
 * LOG: Revision 1.1  1998/09/28 17:37:51  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.6  1998/09/27 00:53:11  mmiers
 * LOG: Start cleaning up connectionless.
 * LOG:
 * LOG: Revision 1.5  1998/09/27 00:04:18  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:30  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/24 19:24:38  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/09/24 17:31:51  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 16:33:11  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <its_intern.h>

#if defined(INCLUDE_MTP3)

#include <its_mlist.h>
#include <its_ss7_trans.h>

#if defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#elif defined(PRC)
#include <china/mtp3.h>
#else
#error Protocol version not defined
#endif

extern int nms_errno;
extern int nms_debug;

extern CALLBACK_Manager*   MTP3_ManagementCallbacks;

#if NMS_VERSION < 3080

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the NMS board interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSInitializeMTP3(ITS_SS7_HANDLE handl)
{
    S16       retval;
    U8        boardNum;
    S16       sapid;
    S16       servUserId;
    U8        srcEnt;
    U8        srcInst;
    ITS_SS7_CONTEXT *context;
    
    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;
    sapid = context->mtp3Sapid;
    servUserId = context->servUserId;
    srcEnt = context->mtp3SrcEnt;
    srcInst = context->srcInst;

    /* now bind to the SAP */
    if ((retval = MTP3Bind(boardNum, context->sio, sapid,
                           srcEnt, srcInst, servUserId)) != MTP3_SUCCESS)
    {
        if (nms_debug)
        {
            printf("MTP3Bind failed, retval = %d\n", retval);
        } 
        return (ITS_ENOPROXY);
    }

    /* get a synchronization handle for this board */
    if ((context->mtp3Sync = MTP3SyncObj(boardNum, &retval)) == OS_NULL_HSYNC)
    {
        nms_errno = retval;

        return (ITS_ENOPROXY);
    }

    TRANSPORT_SetState(
            (TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(context),
            ITS_TRUE);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the NMS interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSTermMTP3(ITS_SS7_HANDLE handl)
{
    S16     retval;
    U8      boardNum;
    ITS_SS7_CONTEXT *context;

    context = (ITS_SS7_CONTEXT *)handl;
    boardNum = context->boardNum;

    TRANSPORT_SetState(
            (TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(context),
            ITS_FALSE);

    if ((retval = MTP3Unbind(boardNum)) != MTP3_SUCCESS)
    {
        nms_errno = retval;

        return (ITS_ENOPROXY);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSRetrieveMTP3Message(ITS_SS7_HANDLE handl)
{
    /* Fred Debug: update msg struct to get Stat Indication */
    union
    {
        U8          msgCode;    /* overlays "code" field of DATA_IND/STAT_IND */
        DATA_IND    dataind;    /* incoming data event */
        STAT_IND    statind;    /* incoming status event */
        XSTAT_IND   xstatind;   /* incoming extended status indication */
    } msg;
    
    MTP3_HEADER mtp3_hdr;
    MTP3_PAUSE_RESUME mtp3_pause_resume;
    MTP3_STATUS mtp3_status;
    ITS_EVENT ev;
    int ret;
    short len;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handl;

  
	if (MTP3RetrieveMessage(context->boardNum, &msg, &len) != MTP3_SUCCESS)
    {
        return (ITS_ENOMSG);
    }

    /* Fred Debug: update if to get Stat Indication */
    /* if (msg.data.code == MTP3_DATA_IND) */
    if (msg.msgCode == MTP3_DATA_IND)
    {
        memset(&mtp3_hdr, 0, sizeof(MTP3_HEADER));

        mtp3_hdr.sio = msg.dataind.srvInfo;

        MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label, msg.dataind.opc);
        MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label, msg.dataind.dpc);
        MTP3_RL_SET_SLS(mtp3_hdr.label, msg.dataind.lnkSel);

        if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA, &mtp3_hdr,
                               msg.dataind.data, len)) != ITS_SUCCESS)
        {
            return (ret);
        }

    ev.src = ITS_MTP3_SRC;

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
    }
    /* Fred Debug: update to get Stat Indication */
    else if (msg.msgCode == MTP3_STAT_IND)
    {
        switch  (msg.statind.status)
        {
        case StatPaused:
        case StatResumed:
            memset(&mtp3_pause_resume, 0, sizeof(MTP3_PAUSE_RESUME));
            MTP3_PC_SET_VALUE(mtp3_pause_resume.affected, msg.statind.pc);
            if (msg.statind.status == StatPaused)
            {
                MTP3_Encode(&ev, MTP3_MSG_PAUSE, &mtp3_hdr,
                            (ITS_OCTET *)&mtp3_pause_resume,
                            sizeof(MTP3_PAUSE_RESUME));
            }
            else
            {
                MTP3_Encode(&ev, MTP3_MSG_RESUME, &mtp3_hdr,
                            (ITS_OCTET *)&mtp3_pause_resume,
                            sizeof(MTP3_PAUSE_RESUME));
            }

        ev.src = ITS_MTP3_SRC;

            break;

        case StatCongested:                                                
        case StatCongestionEnds:
            memset(&mtp3_status, 0, sizeof(MTP3_STATUS));
            MTP3_PC_SET_VALUE(mtp3_status.affected, msg.statind.pc);
            if (msg.statind.status == StatCongested)
            {
                mtp3_status.congLevel = msg.statind.priority;                
            }
            else
            {
                mtp3_status.congLevel = 0;
            }
            MTP3_Encode(&ev, MTP3_MSG_PAUSE, &mtp3_hdr,
                        (ITS_OCTET *)&mtp3_status,
                        sizeof(MTP3_STATUS));

        ev.src = ITS_MTP3_SRC;

            break;

        case StatUsrUnavail:
        case StatRestart:
        case StatRestartEnds:
        default:
            /* No Need to handle those */
            return (ITS_SUCCESS);
            break;
        }

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
    }
    else
    {
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSSendMTP3Event(ITS_SS7_HANDLE handle,
                 ITS_OCTET mType,
                 MTP3_HEADER *mtp3,
                 ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;

    return MTP3SendData(context->boardNum, context->mtp3Sapid,
                        MTP3_RL_GET_OPC_VALUE(mtp3->label),
                        MTP3_RL_GET_DPC_VALUE(mtp3->label),
                        (U8)MTP3_RL_GET_SLS(mtp3->label),
                        (U8)((mtp3->sio & MTP3_MPC_MASK) >> 4),
                        data, dlen,
                        mtp3->sio);
}

#else /* NMS_VERSION >= 3080 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize the NMS board interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSInitializeMTP3(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    CTA_EVENT        ctaEvent;
    DWORD            ret = !MTP3_SUCCESS;
    CTA_SERVICE_DESC mtp3OpenSvcLst[]   = {{{"MTP3", "MTP3MGR"}, {0}, {0}, {0}}};
    CTA_SERVICE_NAME mtp3ServiceNames[] = {{ "MTP3", "MTP3MGR" }};
    char *snames[] = { "MTP3" };
    CTA_INIT_PARMS   mtp3Initparms      = { 0 };
    CTA_REV_INFO     info;

    ctaGetVersion(&info, sizeof(CTA_REV_INFO));
    if (info.compatlevel != CTA_COMPATLEVEL)
    {
        printf("CTA compatibility level does not match. re-compile.\n");
        exit(1);
    }

    /* bind this application as a user of the MTP3 layer */
    mtp3Initparms.size           = sizeof(CTA_INIT_PARMS);
    mtp3Initparms.traceflags     = CTA_TRACE_ENABLE;
    /*mtp3Initparms.parmflags      = CTA_PARM_MGMT_SHARED;*/
    mtp3Initparms.ctacompatlevel = CTA_COMPATLEVEL;
    mtp3Initparms.filename       = NULL;

#if !defined(INCLUDE_VMI)

#if !defined(INCLUDE_ISUP)

    //ret = ctaInitialize(NULL,0,&mtp3Initparms);
    if (ret != MTP3_SUCCESS)
    {
        /*
         * ctdaemon is not running. Initialize without tracing.
         */
        mtp3Initparms.traceflags = 0;
        mtp3Initparms.parmflags  = 0;

		// Wrong place to call this func; Not sure why construct
		// object is not invoking it.
        ret = ctaInitialize(mtp3ServiceNames,
                            sizeof(mtp3ServiceNames) /                
							sizeof(mtp3ServiceNames[0]),
                            &mtp3Initparms);

        if (ret != SUCCESS && 
			(ret == CTAERR_FUNCTION_ACTIVE ||
			 ret == CTAERR_ALREADY_INITIALIZED))
        {
			ret = SUCCESS;
		}
		else if (ret != SUCCESS)
		{
            return (ITS_ENOTFOUND);
        }

		
    }

#endif

#endif

#if !defined(INCLUDE_ISUP)

    if ((ret = ctaCreateQueue(NULL, 0,
                              &context->mtp3CtaQueueHd)) != MTP3_SUCCESS)
    {
        ctaCloseServices(NULL_CTAHD, snames,
                         sizeof(snames) / sizeof(snames[0]));

        return (ITS_ENOTFOUND);
    }

#endif

    /* Open mtp3CtaHd on mtp3CtaQueue                   */
    if ((ret = ctaCreateContext(context->mtp3CtaQueueHd,
                                context->mtp3Sapid, NULL,
                                &context->mtp3CtaHd)) != MTP3_SUCCESS)
    {
        ctaDestroyQueue(context->mtp3CtaQueueHd);
        ctaCloseServices(NULL_CTAHD, snames,
                         sizeof(snames) / sizeof(snames[0]));

        return (ITS_ENOTFOUND);
    }

    mtp3OpenSvcLst[0].svcargs.args[0] = context->boardNum;  /* board number              */
    mtp3OpenSvcLst[0].svcargs.args[1] = context->sio;       /* Service Information Octet */
    mtp3OpenSvcLst[0].svcargs.args[2] = context->mtp3Sapid; /* network SAP number        */
    mtp3OpenSvcLst[0].svcargs.args[3] = context->mtp3SrcEnt;/* application entity ID     */
    mtp3OpenSvcLst[0].svcargs.args[4] = context->srcInst;   /* Inst ID                   */
    mtp3OpenSvcLst[0].svcargs.args[5] = context->servUserId;/* Service user ID           */
    mtp3OpenSvcLst[0].svcargs.args[6] = 256;                /* Pool size                 */

    if ((ret = ctaOpenServices(context->mtp3CtaHd,mtp3OpenSvcLst, 1)) != MTP3_SUCCESS)
    {
        if ((ret = ctaDestroyContext(context->mtp3CtaHd)) != MTP3_SUCCESS)
        {
         printf(" ctaOpenServices failed RET = %d\n",ret);
            return (ITS_EINVALIDARGS);
        }

        /* Wait for context close to complete. */
        if ((ret = ctaWaitEvent(context->mtp3CtaQueueHd,
                                &ctaEvent,
                                CTA_WAIT_FOREVER)) != MTP3_SUCCESS)
        {
            return (ITS_EINVALIDARGS);
        }

        if (ctaEvent.id != CTAEVN_DESTROY_CONTEXT_DONE ||
            ctaEvent.value != CTA_REASON_FINISHED)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((ret = ctaDestroyQueue(context->mtp3CtaQueueHd)) != MTP3_SUCCESS)
        {
            return (ITS_EINVALIDARGS);
        }

        ctaCloseServices(NULL_CTAHD, snames,
                         sizeof(snames) / sizeof(snames[0]));

        return (ITS_ENOTFOUND);
    }
    else
    {
         do
		 {
             ctaWaitEvent(context->mtp3CtaQueueHd, &ctaEvent, CTA_WAIT_FOREVER);
		 }
         while (ctaEvent.id != CTAEVN_OPEN_SERVICES_DONE);

         if (ctaEvent.value != CTA_REASON_FINISHED)
         {
              /* error opening service */
              return (ITS_ENOTFOUND);
		 }

         TRANSPORT_SetState((TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(context),
                                                                        ITS_TRUE);
         return ITS_SUCCESS;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Terminate the NMS interface.
 *
 *  Input Parameters:
 *      ITS_SS7_HANDLE - The board context.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
NMSTermMTP3(ITS_SS7_HANDLE handl)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handl;
    CTA_EVENT  event;
    DWORD      ret;
    char*      mtp3CloseSvcLst[] = {"MTP3"};

  /* Close service and destroy context. */
   if ((ret = ctaCloseServices(context->mtp3CtaHd,
                               mtp3CloseSvcLst, 1)) != MTP3_SUCCESS)
   {
       return (ITS_EINVALIDARGS);
   }

   /* Wait for service close to complete. */
   if ((ret = ctaWaitEvent(context->mtp3CtaQueueHd,
                           &event,
                           CTA_WAIT_FOREVER)) != MTP3_SUCCESS)
   {
       return (ITS_EINVALIDARGS);
   }

   if (event.id != CTAEVN_CLOSE_SERVICES_DONE ||
       event.value != CTA_REASON_FINISHED)
   {
       return (ITS_EINVALIDARGS);
   }

   if ((ret = ctaDestroyContext(context->mtp3CtaHd)) != MTP3_SUCCESS)
   {
       return (ITS_EINVALIDARGS);
   }

   /* Wait for context close to complete. */
   if ((ret = ctaWaitEvent(context->mtp3CtaQueueHd,
                           &event,
                           CTA_WAIT_FOREVER)) != MTP3_SUCCESS)
   {
       return (ITS_EINVALIDARGS);
   }

   if (event.id != CTAEVN_DESTROY_CONTEXT_DONE ||
       event.value != CTA_REASON_FINISHED)
   {
       return (ITS_EINVALIDARGS);
   }

   if ((ret = ctaDestroyQueue(context->mtp3CtaQueueHd)) != MTP3_SUCCESS)
   {
       return (ITS_EINVALIDARGS);
   }

   TRANSPORT_SetState(
            (TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(context),
            ITS_FALSE);

   return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSRetrieveMTP3Message(ITS_SS7_HANDLE handl)
{
    /* Fred Debug: update msg struct to get Stat Indication */
    union
    {
        U8          msgCode;    /* overlays "code" field of DATA_IND/STAT_IND */
        DATA_IND    dataind;    /* incoming data event */
        STAT_IND    statind;    /* incoming status event */
        XSTAT_IND   xstatind;   /* incoming extended status indication */
        BIND_CFM    bindcfm;    /* bind confirmation */
    } msg;
    MTP3_HEADER mtp3_hdr;
    MTP3_PAUSE_RESUME mtp3_pause_resume;
    MTP3_STATUS mtp3_status;
    ITS_EVENT ev;
    int ret;
    short len;
    ITS_SS7_CONTEXT* context = (ITS_SS7_CONTEXT *)handl;

    len = sizeof(msg);

    if (MTP3RetrieveMessage(context->mtp3CtaHd, &msg, &len) != MTP3_SUCCESS)
    {
        return (ITS_ENOMSG);
    }

    /* Fred Debug: update if to get Stat Indication */
    /* if (msg.data.code == MTP3_DATA_IND) */
    if (msg.msgCode == MTP3_DATA_IND)
    {
        memset(&mtp3_hdr, 0, sizeof(MTP3_HEADER));

        /*
         * Subtract off size of header fields to get actual data length
         *
         * Note that the header is packed, spares in the structure are not
         * included.  Also the message "code" field in the DATA_IND
         * structure has already been stripped (and placed into the msgCode
         * field) and is not included in the length returned from
         * MTP3RetrieveMsg().  Therefore it is not included in the
         * DATA_IND_HDR_SIZE define either.
         */
        len -= DATA_IND_HDR_SIZE;
        mtp3_hdr.sio = msg.dataind.srvInfo;

        MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label, msg.dataind.opc);
        MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label, msg.dataind.dpc);
        MTP3_RL_SET_SLS(mtp3_hdr.label, msg.dataind.lnkSel);

        if ((ret = MTP3_Encode(&ev, MTP3_MSG_USER_DATA, &mtp3_hdr,
                               msg.dataind.data, len)) != ITS_SUCCESS)
        {
            return (ret);
        }

        ev.src = ITS_MTP3_SRC;

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
    }
    /* Fred Debug: update to get Stat Indication */
    else if (msg.msgCode == MTP3_STAT_IND)
    {
        MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label, context->dpc);
        MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label, context->opc);
        mtp3_hdr.sio = context->sio;

        switch  (msg.statind.status)
        {
        case StatPaused:
        case StatResumed:
            memset(&mtp3_pause_resume, 0, sizeof(MTP3_PAUSE_RESUME));
            MTP3_PC_SET_VALUE(mtp3_pause_resume.affected, msg.statind.pc);
            if (msg.statind.status == StatPaused)
            {
                MTP3_Encode(&ev, MTP3_MSG_PAUSE, &mtp3_hdr,
                            (ITS_OCTET *)&mtp3_pause_resume,
                            sizeof(MTP3_PAUSE_RESUME));
            }
            else
            {
                MTP3_Encode(&ev, MTP3_MSG_RESUME, &mtp3_hdr,
                            (ITS_OCTET *)&mtp3_pause_resume,
                            sizeof(MTP3_PAUSE_RESUME));
            }

            ev.src = ITS_MTP3_SRC;

            break;

        case StatCongested:                                                
        case StatCongestionEnds:
            memset(&mtp3_status, 0, sizeof(MTP3_STATUS));
            MTP3_PC_SET_VALUE(mtp3_status.affected, msg.statind.pc);
            if (msg.statind.status == StatCongested)
            {
                mtp3_status.congLevel = msg.statind.priority;                
            }
            else
            {
                mtp3_status.congLevel = 0;
            }
            MTP3_Encode(&ev, MTP3_MSG_STATUS, &mtp3_hdr,
                        (ITS_OCTET *)&mtp3_status,
                        sizeof(MTP3_STATUS));
            ev.src = ITS_MTP3_SRC;
            break;
        case StatUsrUnavail:
            memset(&mtp3_status, 0, sizeof(MTP3_STATUS));
            MTP3_PC_SET_VALUE(mtp3_status.affected, msg.statind.pc);
            if (msg.statind.status == StatCongested)
            {
                mtp3_status.congLevel = msg.statind.priority;                
            }
            else
            {
                mtp3_status.congLevel = 0;
            }
            mtp3_status.cause = MTP3_STATUS_UPU_INACCESS;
            MTP3_Encode(&ev, MTP3_MSG_STATUS, &mtp3_hdr,
                        (ITS_OCTET *)&mtp3_status,
                        sizeof(MTP3_STATUS));
            ev.src = ITS_MTP3_SRC;
            break;

        case StatRestart:
        case StatRestartEnds:
        default:
            /* No Need to handle those */
            return (ITS_SUCCESS);
            break;
        }

        return MQUEUE_Enqueue(VENDOR_RCV_Q(context), &ev, sizeof(ITS_EVENT));
    }
    else
    {
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      None.
 ****************************************************************************/
int
NMSSendMTP3Event(ITS_SS7_HANDLE handle, 
                 ITS_OCTET mType,
                 MTP3_HEADER *mtp3,
                 ITS_OCTET *data, ITS_USHORT dlen)
{
    ITS_SS7_CONTEXT *context = (ITS_SS7_CONTEXT *)handle;
    ITS_INT ret = 0;

    ret = MTP3SendData(context->mtp3CtaHd, context->mtp3Sapid,
                        MTP3_RL_GET_OPC_VALUE(mtp3->label),
                        MTP3_RL_GET_DPC_VALUE(mtp3->label),
                        (U8)MTP3_RL_GET_SLS(mtp3->label),
                        (U8)((mtp3->sio & MTP3_MPC_MASK) >> 4),
                        data, dlen,
                        mtp3->sio);

	return ret;
}

#endif /* NMS_VERSION */

#endif /* INCLUDE_MTP3 */
