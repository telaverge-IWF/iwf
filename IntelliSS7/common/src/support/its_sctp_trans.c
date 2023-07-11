/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 9.12  2008/07/16 13:45:16  mpatri
 * LOG: Fixed multihoming at client issue
 * LOG:
 * LOG: Revision 9.11  2008/07/10 06:27:36  ssingh
 * LOG: Parallel stack support (multiple instances of M3UA)
 * LOG: Design Ids: D8070, D8090, D8094
 * LOG:
 * LOG: Revision 9.10  2008/07/03 13:25:30  skatta
 * LOG: Fix for issue #1042 in whizible
 * LOG:
 * LOG: Revision 9.9  2008/06/30 08:58:55  nvijikumar
 * LOG: Fixing Linking Issue
 * LOG:
 * LOG: Revision 9.8  2008/06/27 14:18:09  mpatri
 * LOG: Accelero CGI Phase I: Modification to adopt code review comments & Fixing other issues
 * LOG:
 * LOG: Revision 9.7  2008/06/23 05:56:46  mpatri
 * LOG: Accelero CGI Phase I: D0020, D0250-Multihome support & fixing current issues
 * LOG:
 * LOG: Revision 9.6  2008/06/04 06:32:06  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.5  2008/04/15 05:03:15  kramesh
 * LOG: Merged Persistent Branch Changes to current.
 * LOG:
 * LOG: Revision 9.4.2.6  2008/02/25 10:57:42  omayor
 * LOG: modification to support  C++ API for SCTP Client transport
 * LOG:
 * LOG: Revision 9.4.2.5  2007/10/12 08:08:12  pspl
 * LOG: Made changes in function SCTPTRAN_ReConnectOnLostCommunication(), to fix
 * LOG: Tecklec issue# 6351.
 * LOG:
 * LOG: Revision 9.4.2.4  2007/06/28 05:33:01  pspl
 * LOG: Code clean up. Corrected log level of some statements from error to debug.
 * LOG: (Rahul)
 * LOG:
 * LOG: Revision 9.4.2.3  2007/06/22 15:31:24  pspl
 * LOG: 1. Change to not reusing client socket to reconnect after getting lost
 * LOG: communication.
 * LOG: 2. Cleanup.(Rahul/Rajnikant).
 * LOG:
 * LOG: Revision 9.4.2.2  2007/06/15 15:16:36  pspl
 * LOG: Added support for multihome in sctp (Rahul/Rajnikant)
 * LOG:
 * LOG: Revision 9.4.2.1  2007/06/04 14:16:11  pspl
 * LOG: Multihome support added (Rajnikant)
 * LOG:
 * LOG: Revision 9.4  2007/01/10 11:15:10  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.3  2005/06/02 06:56:06  yranade
 * LOG: Changes for Linux Kernel SCTP Integration as per ACC652-SDS-LKSC-V1.0.02.
 * LOG:
 * LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 * LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.5.2.2.6.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.4.2.5.2.2  2004/09/29 09:56:14  asingh
 * LOG: Changes for linux ES 30 operating system; compilation issue.
 * LOG:
 * LOG: Revision 7.4.2.5.2.1  2004/05/03 12:36:13  ssingh
 * LOG: Bug#805/776;
 * LOG: Stack dumping core while trying to send DATA to INACTIVE
 * LOG: Non Transfer messages received on stream other than zero.
 * LOG:
 * LOG: Revision 7.4.2.5  2003/10/16 13:47:39  lbana
 * LOG: incorrect patch applied on this branch.
 * LOG:
 * LOG: Revision 7.4.2.4  2003/10/15 21:02:32  lbana
 * LOG: remove transport after association lost indication.
 * LOG:
 * LOG: Revision 7.4.2.3  2003/09/12 22:53:00  lbana
 * LOG: Set isActive flag for remote transports to true|false
 * LOG:
 * LOG: Revision 7.4.2.2  2003/08/27 19:32:33  hcho
 * LOG: Set state is done in UAL.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/08/04 23:11:38  hcho
 * LOG: propagate CANT_SATRT indication to ual.
 * LOG:
 * LOG: Revision 7.4  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.3  2002/12/30 17:29:45  lbana
 * LOG: propagating bug fixes in PR6.1 to current
 * LOG:
 * LOG: Revision 7.2  2002/12/16 15:31:40  ngoel
 * LOG: set correct mask while creating remote transport
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/28 21:36:41  lbana
 * LOG: Initialize stack variables.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 16:15:27  omayor
 * LOG: Add reconnection code on client side of the association. Also don't
 * LOG: remove the remote if association is lost (client side only).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.11  2002/01/10 17:37:38  mmiers
 * LOG: Finish off the refcounting code.
 * LOG:
 * LOG: Revision 5.10  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.9  2002/01/09 21:21:59  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.8  2002/01/04 22:50:05  mmiers
 * LOG: Update SCTP code sig
 * LOG:
 * LOG: Revision 5.7  2002/01/02 23:30:55  mmiers
 * LOG: Mark the callbacks as exported.
 * LOG:
 * LOG: Revision 5.6  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.5  2001/11/15 02:02:57  mmiers
 * LOG: Note some things to do.
 * LOG:
 * LOG: Revision 5.4  2001/11/01 19:21:21  mmiers
 * LOG: Reader/writer lock problem
 * LOG:
 * LOG: Revision 5.3  2001/09/19 00:53:36  mmiers
 * LOG: Bugs found in cross platform build.
 * LOG:
 * LOG: Revision 5.2  2001/09/18 22:18:58  mmiers
 * LOG: Add internal transports API
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.38  2001/04/27 21:23:28  labuser
 * LOG: typo in AddRemoteTrans.
 * LOG:
 * LOG: Revision 3.37  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.36  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.35  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.34  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.33  2001/02/06 00:26:00  mmiers
 * LOG: Continue adding assertions.
 * LOG:
 * LOG: Revision 3.32  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.31  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.30  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.29  2000/12/29 17:56:56  mmiers
 * LOG: Return SUCCESS, not num bytes read
 * LOG:
 * LOG: Revision 3.28  2000/12/21 21:29:10  mmiers
 * LOG: Can't pass in the addr.
 * LOG:
 * LOG: Revision 3.27  2000/12/21 20:53:00  mmiers
 * LOG: Missing payload ident.
 * LOG:
 * LOG: Revision 3.26  2000/12/21 20:37:00  mmiers
 * LOG: Old bug parsing.
 * LOG:
 * LOG: Revision 3.25  2000/12/21 18:41:40  mmiers
 * LOG: Pass management indication to codec
 * LOG:
 * LOG: Revision 3.24  2000/12/21 18:36:12  mmiers
 * LOG: Set codec and ptype on preconfigured transports
 * LOG:
 * LOG: Revision 3.23  2000/12/21 18:24:07  mmiers
 * LOG: Finish fixing address conversion
 * LOG:
 * LOG: Revision 3.22  2000/12/21 01:47:39  mmiers
 * LOG: Temp version.
 * LOG:
 * LOG: Revision 3.21  2000/12/21 00:30:28  mmiers
 * LOG: Make Get/Put return ITS error codes.
 * LOG:
 * LOG: Revision 3.20  2000/12/21 00:06:52  mmiers
 * LOG: Build remotes correctly.
 * LOG:
 * LOG: Revision 3.19  2000/12/20 23:38:43  mmiers
 * LOG: It helps if you create the transport.
 * LOG:
 * LOG: Revision 3.18  2000/12/19 23:19:39  mmiers
 * LOG: Debug section rewind
 * LOG:
 * LOG: Revision 3.17  2000/12/19 22:01:23  mmiers
 * LOG: Missing break
 * LOG:
 * LOG: Revision 3.16  2000/12/19 21:34:41  mmiers
 * LOG: Missing allocation
 * LOG:
 * LOG: Revision 3.15  2000/12/18 23:46:54  mmiers
 * LOG: Add SLS key to signature.
 * LOG:
 * LOG: Revision 3.14  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.13  2000/11/30 19:37:45  mmiers
 * LOG: Ready to debug.
 * LOG:
 * LOG: Revision 3.12  2000/11/30 17:55:55  mmiers
 * LOG: Straighten out the defines (we had overlaps)
 * LOG:
 * LOG: Revision 3.11  2000/11/29 23:38:26  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 3.10  2000/11/29 20:38:17  mmiers
 * LOG: Build on solaris.
 * LOG:
 * LOG: Revision 3.9  2000/11/29 20:35:28  mmiers
 * LOG: Use the pointers.
 * LOG:
 * LOG: Revision 3.8  2000/11/29 20:27:20  mmiers
 * LOG: Fix UNIX build warnings
 * LOG:
 * LOG: Revision 3.7  2000/11/29 18:24:42  mmiers
 * LOG: Write ok.  Think about SLS->stream.
 * LOG:
 * LOG: Revision 3.6  2000/11/29 00:59:30  mmiers
 * LOG: Got read done.  Write should be simple.
 * LOG:
 * LOG: Revision 3.5  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.4  2000/11/17 23:09:52  mmiers
 * LOG: clean up on SCTP some.
 * LOG:
 * LOG: Revision 3.3  2000/11/16 23:01:55  mmiers
 * LOG: Add the SCTP transport.  Getting close on this...
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: its_sctp_trans.c,v 9.12.2.1.4.1.28.1.2.5.2.2.2.2.2.4 2015/06/24 06:44:19 jkchaitanya Exp $"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if !defined(WIN32)
#if defined(solaris)
#include <sys/socket.h>
#endif
#include <netinet/in.h>
#endif

#include <its_timers.h>
#include <its_trace.h>
#include <its_sctp.h>
#include <its_sctp_trans.h>
#include <its_assertion.h>
#include <its_alarm.h>

#define LK_SCTP_CLASS_NAME  "LKSCTP"
#define SK_SCTP_CLASS_NAME  "SKSCTP"

ITS_UINT     sksctpAlarmLevel;

/**
 * These two IOCTLs are used for setting socket-level
 * recv and send timeouts.
 */
#define IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT 0x0021
#define IOCTL_SET_SND_NON_BLOCKING_TIMEOUT 0x0022


/*
 * UA usage
 */
ITSDLLAPI CALLBACK_Manager    *SCTPTRAN_ManagementCallbacks = NULL;

#if 0

/*
 * SCTP hooks
 */

ITS_USHORT  (*SCTP_SocketPtr)(int af, int t);
int         (*SCTP_BindPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
int         (*SCTP_ListenPtr)(ITS_USHORT sd, int backlog);
ITS_USHORT  (*SCTP_AcceptPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int *wlen);
int         (*SCTP_ConnectPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
int         (*SCTP_SendMsgPtr)(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
int         (*SCTP_RecvMsgPtr)(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
int         (*SCTP_ClosePtr)(ITS_USHORT sd);
int         (*SCTP_PendingPtr)(ITS_USHORT sd);
int         (*SCTP_IoctlPtr)(ITS_USHORT sd, int req, ...);

#endif

/*
 * codec record
 */
static SCTPTRAN_CodecRec    codecs[SCTP_FAM_MAX][SCTP_PAYLOAD_MAX];

/* Global Structure */
SCTPTRAN_ClassPart  sctptranClass;

//static ITS_Class lkClass = NULL;

/*
 * transport names
 */
#define SCTP_TRANSPORT_NAME "SCTP-Transport-%u"

//SKSCTP ALARMS
ALARM_FORMAT_SUBSYS(SKSCTP, 7001,
                    "Established SCTP Association",
                    ALARM_LVL_INFO,
                    " ", "SKSCTP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(SKSCTP, 7002,
                    "Lost SCTP Association",
                    ALARM_LVL_MAJOR,
                    " ", "SKSCTP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(SKSCTP, 7003,
                    "Reestablished SCTP Association",
                    ALARM_LVL_MAJOR,
                    " ", "SKSCTP", ITS_FALSE);

ALARM_FORMAT_SUBSYS(SKSCTP, 7004,
                    "Graceful SCTP Shutdown",
                    ALARM_LVL_MAJOR,
                    " ", "SKSCTP", ITS_FALSE);

ALARM_Format *SKSCTP_Alarms[] = {
                                NULL,
                                &ALARM_SKSCTP7001,
                                &ALARM_SKSCTP7002,
                                &ALARM_SKSCTP7003,
                                &ALARM_SKSCTP7004
                                };


/*
 * function to get family of m3ua instance
 */
static 
SCTP_PAYLOAD_FAMILY SCTPTRAN_GetPayloadFamily(char *name);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates an SCTP socket
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 * 
 * dsatish         06-10-2006  IssueId#4311             binding issue
 *
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_Open(SOCKTRAN_Manager* m)
{
    char var[1024], val[1024];
    char *tmp;
    SCTP_API_IOCTL_ARG arg = {{0}};
    ITS_SocketInfo  extraHomes[SCTP_MAX_HOMES];
    unsigned int    numExtraHomes = 0;
    int i = 0;
    int isFirstTime= 1;
    

    ITS_C_REQUIRE(m != NULL);

    /*
     * we have (already) the local port number.  So what we need is to
     * get the local bind addresses.  Further, we then need the remote
     * address(es) and port.
     */
    ITS_TRACE_DEBUG(("SCTPTRAN_Open\n"));
    
    /*Commented as part of CGI development*/
#if 0
    lkClass = ITS_FindFeature(LK_SCTP_CLASS_NAME);


    if (lkClass != NULL)
    {
        ITS_TRACE_WARNING(("Linux Kernel SCTP Configured. \n"));
    }
#endif

    /* is SCTP around ?*/
    if (SCTPTRAN_SOCKET(m) == NULL || SCTPTRAN_BIND(m) == NULL ||
        SCTPTRAN_CONNECT(m) == NULL || SCTPTRAN_CLOSE(m) == NULL)
    {
        ITS_TRACE_ERROR(("Platform specific SCTP that extends \
               the SCTP transport class record is missing.\n"));

        return (ITS_EINVALIDARGS);
    }
    /* FIXME:: When SCTPTRAN_Open called during ReConnect,
     * Not allocating again as not freed the Connect one
     * May need to re-look again for multiple Remotes
     */
    if (SOCKTRAN_SOURCE(m) == NULL)
    { 
        if ((SOCKTRAN_SOURCE(m) =
            (ITS_SocketInfo *)calloc(1,
                                     sizeof(ITS_SocketInfo))) == NULL)
        {
            ITS_TRACE_ERROR(("SCTPTRAN_Open: out of memory.\n"));

            return (ITS_ENOMEM);
        }
    }

    /* get the socket */
    
    SCTPTRAN_SOCKET(m)((SCTPTRAN_ManagerPtr)m);

    if (SOCKTRAN_SOURCE(m)->socket == (ITS_SOCKET)ITS_INVALID_SRC ||
        SOCKTRAN_SOURCE(m)->socket == (ITS_SOCKET)ITS_NO_SRC)
    {
        ITS_TRACE_ERROR(("Couldn't open SCTP socket.\n"));

        return (ITS_EBADSOCKET);
    }

    /* lock the DB */
    if (RESFILE_Lock(TRANSPORT_RES(m)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't lock resource file\n"));

        (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

        return (ITS_EBADMUTEX);
    }

    if (RESFILE_Rewind(TRANSPORT_RES(m), TRANSPORT_NAME(m)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't rewind resource file\n"));

        (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

        return (ITS_EBADMUTEX);
    }

    /* get the bindings */
    while (RESFILE_GetKeyName(TRANSPORT_RES(m), TRANSPORT_NAME(m),
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(TRANSPORT_RES(m), TRANSPORT_NAME(m),
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        /* local addr? */
        ITS_TRACE_DEBUG(("var %s val %s\n",var,val));
        if (strcmp(var, LOCAL_HOST_NAME_STRING) == 0)
        {
#if 0
            /* turn it into something useful */
            if (NULL == SOCKTRAN_SOURCE(m))
            {
#endif
                                        

                if(isFirstTime == 1)
                {
                    if (SOCK_CreateAddr(INET_DOMAIN, val, SOCKTRAN_PORT(m),
                                &SOCKTRAN_SOURCE(m)->addr,
                                &SOCKTRAN_SOURCE(m)->asize) != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR(("Couldn't create bind addr\n"));

                        (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                        RESFILE_Unlock(TRANSPORT_RES(m));

                        return (ITS_EINVALIDARGS);
                    }

                    isFirstTime= 0;
                }
                else
                {
                    /*The primary local address has already been read.
                     Now read the secondary into an array and set it
                     into extraHomes in one shot at the end as the
                     memory to be allocated for extraHomes array needs
                     to be contiguous and we dont know at this point
                     here how many extra homes are there*/
                    extraHomes[numExtraHomes].addr  = NULL;
                    if (SOCK_CreateAddr(INET_DOMAIN, val, SOCKTRAN_PORT(m),
                                &extraHomes[numExtraHomes].addr,
                                &extraHomes[numExtraHomes].asize) != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR(("Couldn't create bind addr\n"));

                        (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                        RESFILE_Unlock(TRANSPORT_RES(m));

                        return (ITS_EINVALIDARGS);
                    }
                    numExtraHomes++;
                }


#if 0

                if (SOCK_CreateAddr(INET_DOMAIN, val, SOCKTRAN_PORT(m),
                                &SOCKTRAN_SOURCE(m)->addr,
                                &SOCKTRAN_SOURCE(m)->asize) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("Couldn't create bind addr\n"));

                    (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                    RESFILE_Unlock(TRANSPORT_RES(m));

                    return (ITS_EINVALIDARGS);
                }

#endif



#if 0
            }
            else
            {
                /*The primary local address has already been read.
                  Now read the secondary into an array and set it 
                  into extraHomes in one shot at the end as the
                  memory to be allocated for extraHomes array needs
                  to be contiguous and we dont know at this point
                  here how many extra homes are there*/
                if (SOCK_CreateAddr(INET_DOMAIN, val, SOCKTRAN_PORT(m),
                                &extraHomes[numExtraHomes].addr,
                                &extraHomes[numExtraHomes].asize) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("Couldn't create bind addr\n"));

                    (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                    RESFILE_Unlock(TRANSPORT_RES(m));

                    return (ITS_EINVALIDARGS);
                }
                numExtraHomes++;                                  
            }
#endif 
            

            /*FIXME: IOCTL should be called for both lksctp and sksctp
             * Hence commenting out the check for lkClass
             */

            //if (lkClass != NULL)
            {
                if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                         IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT,
                                         &arg) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("Couldn't set recv timeout IOCTL\n"));

                    (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                    RESFILE_Unlock(TRANSPORT_RES(m));

                    return (ITS_EINVALIDARGS);
                }
                if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                     IOCTL_SET_SND_NON_BLOCKING_TIMEOUT, 
                                     &arg) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("Couldn't set send timeout IOCTL\n"));

                    (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                    RESFILE_Unlock(TRANSPORT_RES(m));

                    return (ITS_EINVALIDARGS);
                }

            }
        }
        /*
         * the next three MUST appear IN ORDER to have any effect
         */
        else if (strcmp(var, MAX_IN_STREAMS_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, NUM_OUT_STREAMS_STRING) == 0)
        {
            arg.value2 = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, MAX_ATTEMPTS_STRING) == 0)
        {
            arg.value3 = RESFILE_ParseNum(val);
	    
            //if (lkClass != NULL)
            {
                /* -1 indicates keep sending init, but in Kernel how to implement it? */
                if (arg.value3 <= -1)
                {
                    /* So set to default value, normally it is Max.Init.Retransmit */
                    arg.value3 = 0;
                }
            }
            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_INIT_DATA,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, INIT_COOKIE_LIFE_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_INIT_COOK_LIFE,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init cookie IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
	else if (strcmp(var, ASOC_FAILURE_RETRY_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_ASSOC_FAIL_RETRY,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set association max attempt IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
	else if (strcmp(var, ACK_DELAY_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_SACK_DELAY,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set ack delay IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
	else if (strcmp(var, RECONN_TIMEOUT_STRING) == 0)
        {
            TRANSPORT_RECONNECT(m) = RESFILE_ParseNum(val);
	}
	else if (strcmp(var, RTO_MAX_STRING) == 0)
        {
            arg.value3 = RESFILE_ParseNum(val);
	}
	else if (strcmp(var, RTO_MIN_STRING) == 0)
        {
            arg.value2 = RESFILE_ParseNum(val);
	}
	else if (strcmp(var, RTO_INITIAL_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_INIT_RTO_PARAMS,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set rto params IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
	else if (strcmp(var, SEND_BUFFER_SIZE_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_SEND_BUF_SIZE,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set send buffer IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
	else if (strcmp(var, RECV_BUFFER_SIZE_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_RECV_BUF_SIZE,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set recv buffer IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
	else if (strcmp(var, PATH_FAILURE_RETRY_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_PATH_FAIL_RETRY,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set path failure retry IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, INIT_HB_ON_STRING) == 0)
        {
            arg.value = strcmp(val, "YES") == 0 ||
                        strcmp(val, "yes") == 0;

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_INIT_HB_ON,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init HB IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, INIT_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);


            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                 IOCTL_SET_INIT_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init timeout IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, SEND_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_SEND_TIMEOUT,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set send timeout IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, RECV_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_RECV_TIMEOUT,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set recv timeout IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, HB_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_HB_TIMEOUT,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set hb timeout IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, SHUT_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_SHUT_TIMEOUT,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set shutdown timeout IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, PMTU_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((SCTPTRAN_IOCTL(m))((SCTPTRAN_ManagerPtr)m,
                                    IOCTL_SET_PMTU_TIMEOUT,
                                    &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set pmtu timeout IOCTL\n"));

                (SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
    }/*End while*/

    /*Now go through the extraHomes loop and copy it to SCTPTRANS_EXTRAHOMES(m)
      and then call bind. Bind will do a bindx to all addresses*/



    SCTPTRAN_EXTRAHOMES(m) = (ITS_SocketInfo*)calloc(numExtraHomes,
                                            sizeof(ITS_SocketInfo));

    for( i = 0; i < numExtraHomes; i++)
    {
        memcpy(&SCTPTRAN_EXTRAHOMES(m)[i],
            &extraHomes[i],
            sizeof(ITS_SocketInfo));
                
    }
    SCTPTRAN_NUMEXTRAHOMES(m) = numExtraHomes;
 
   
    /* bind it */
    if ((SCTPTRAN_BIND(m))((SCTPTRAN_ManagerPtr)m) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't bind addr, check below ipaddress\n"));
        for(i=0;i<numExtraHomes;i++)
        {
            PrintMyAddr(((SCTPTRAN_EXTRAHOMES(m))[i]).addr,1);
        }

        SCTPTRAN_CLOSE(m)((SCTPTRAN_ManagerPtr)m);
        

        RESFILE_Unlock(TRANSPORT_RES(m));

        //int ret = ITS_SUCCESS;

        //ITS_C_ASSERT(ret != ITS_SUCCESS);

        return (ITS_EINVALIDARGS);
    }


    RESFILE_Unlock(TRANSPORT_RES(m));

    return (ITS_SUCCESS);
}

#if 0
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method connects an SCTP socket
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/

ITSDLLAPI int
SCTPTRAN_ConnectToSec(SCTPTRAN_Manager *m)
{
        
    ITS_C_REQUIRE(m != NULL);

    ITS_TRACE_DEBUG(("Connecting to secondary remote addr\n"));

    if (SCTPTRAN_CONNECT(m) == NULL)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Connect: SCTP not present\n"));

        return (ITS_ENOTRANSPORT);
    }

    if (SOCKTRAN_REMOTE_COUNT(m) != 1)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Connect: Data inconsistency\n"));

        return (ITS_EINVALIDARGS);
    }

    SCTPTRAN_ASSOC_STATE(m) = ITS_ASSOC_CONNECTING;

    /*FIXME: There is no SCTPTRAN_SECADDR now. Change the below
      code to call connect for all the secondary addresses.
      May be think of calling sctp_connectx*/
#if 0
    return (SCTPTRAN_CONNECT(m))((SCTPTRAN_ManagerPtr)m,
                                  SCTPTRAN_SECADDR(m)->addr,
                                  SCTPTRAN_SECADDR(m)->asize);
#endif
    return (SCTPTRAN_CONNECT(m))((SCTPTRAN_ManagerPtr)m);
    
    //                              SCTPTRAN_EXTRAHOMES(m),
    //                              SCTPTRAN_NUMEXTRAHOMES(m));

}
#endif

ITSDLLAPI int
SCTPTRAN_Connect(SOCKTRAN_Manager *m)
{
    ITS_C_REQUIRE(m != NULL);

    if (SCTPTRAN_CONNECT(m) == NULL)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Connect: SCTP not present\n"));

        return (ITS_ENOTRANSPORT);
    }

    /*FIXME: Check the need for this*/
    if (SOCKTRAN_REMOTE_COUNT(m) != 1)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Connect: Data inconsistency\n"));

        return (ITS_EINVALIDARGS);
    }

    SCTPTRAN_ASSOC_STATE(m) = ITS_ASSOC_CONNECTING;

    /* A change in the implementation SCTPTRAN_Connect.
       It now tries to connect to all the homes of the remote.
       This obsoletes the need for SCTPTRAN_ReconnectOnLostCommunication 
       and SCTPTRAN_ConnectToSec
    */

    return (SCTPTRAN_CONNECT(m))((SCTPTRAN_ManagerPtr)m);
    
    //                             SOCKTRAN_CONNECT(m)->addr,
    //                             1);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reconnects an SCTP socket. This is used only by LK-SCTP
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History: 
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_ReConnect(SOCKTRAN_Manager *local, SOCKTRAN_Manager *remote)
{
    int i;

    ITS_TRACE_DEBUG(("SCTPTRAN_ReConnect:\n"));

    if (SOCKTRAN_RETRY_COUNT(local) == 0)
    {
        /* For SCTP Transport, No retryCount*/
        ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: Retry count = 0\n"));

        /* Let us set it for infinite */
        SOCKTRAN_RETRY_COUNT(local) = -1;
    }

    /* create the client socket */
    i = 0;
    while (SOCKTRAN_RETRY_COUNT(local) < 0 || i < SOCKTRAN_RETRY_COUNT(local))
    {
        if (TRANSPORT_EXIT_NOW(local))
        {
            ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: TRANSPORT_EXIT_NOW failed\n"));

            return (ITS_EBADSOCKET);
        }

        /*
          In the previous connection attempt, in the failure case also the sctp kernel
          will retry the connection internely, so before closing the socket 
          we need to check wether the connection is already established. if so returning
          ITS_SUCCESS
        */

        if(i != 0 && SCTPTRAN_ASSOC_STATE(remote) == ITS_ASSOC_CONNECTED)
        {
            return (ITS_SUCCESS);
        }

        /* FIXME::free is commented here as local->source is not
         * getting allocated again in SCTPTRAN_Open for reconnects
         * as its already allocated during first connect..
         * May need to re-look again for multiple Remotes
         * free(SOCKTRAN_SOURCE(local));
         */
        SCTPTRAN_Close(local);
        //free(SOCKTRAN_SOURCE(local));

        if (SCTPTRAN_Open(local) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: failed to "
                             "open client socket\n"));

            i++;
            continue;
        }

        SCTPTRAN_ASSOC_STATE(remote) = ITS_ASSOC_CONNECTING;

        /* connect to the server */
        int iErrno;
        iErrno = SCTPTRAN_Connect((SOCKTRAN_Manager *)remote);
        if (iErrno != ITS_SUCCESS)
        {
#if 1
            if(iErrno == EINPROGRESS)
            {
                TIMERS_USleep(500*USEC_PER_MILLISEC);
                return (ITS_SUCCESS);
            }
#endif
            ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: connect to "
                             "server failed\n"));
	        if(TRANSPORT_RECONNECT(local))
	        {
                	ITS_TRACE_DEBUG(("Reconnect in %d millisecond",TRANSPORT_RECONNECT(local)));
                	//TIMERS_USleep(TRANSPORT_RECONNECT(local)*USEC_PER_MILLISEC);
                    // Using sleep function, since above function is coming out. with out sleeping
                    // when we are getting event
                    sleep(TRANSPORT_RECONNECT(local)/1000);
	        }
	        else
	        {
                	ITS_TRACE_DEBUG(("Reconnect in 5000 sleep millisecond"));
                	//TIMERS_USleep(5000*USEC_PER_MILLISEC);
                    // Using sleep function, since above function is coming out. with out sleeping
                    // when we are getting event
                    sleep(5);
	        }

            i++;
            continue;
        }

        return (ITS_SUCCESS);
    }

    return (ITS_EBADSOCKET);
}

#if 0
ITSDLLAPI int
SCTPTRAN_ReConnectOnLostCommunication(SOCKTRAN_Manager *local, 
                                      SOCKTRAN_Manager *remote)
{
    ITS_TRACE_DEBUG(("SCTPTRAN_ReConnect:\n"));

    /* create the client socket */
    if (TRANSPORT_EXIT_NOW(local))
    {
        ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: TRANSPORT_EXIT_NOW failed\n"));
        return (ITS_EBADSOCKET);
    }

    SCTPTRAN_Close(local);
    free(SOCKTRAN_SOURCE(local));
    /* We make previous address of SOCKTRAN_SOURCE(local) to NULL */
    SOCKTRAN_SOURCE(local) = NULL;

    if (SCTPTRAN_Open(local) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: failed to open client socket\n"));
        return (ITS_EBADSOCKET);
    }

    /* We get address of TRANSPORT_Control object for local transport, 
     * using SOCKTRAN_Manager which contains back pointer to TRANSPORT_Control.
     * There we update the newly created SOCKTRAN_SOURCE(local), so the 
     * consistent remains with  SOCKTRAN_Manager and TRANSPORT_Control.
     */
    TRANSPORT_Control  ** localTC =  SOCKTRAN_REMOTES(local);
    SOCKTRAN_SOURCE(*localTC) = SOCKTRAN_SOURCE(local);
   
    if(SCTPTRAN_CONN_TO_SEC(remote) && SCTPTRAN_NUMEXTRAHOMES(remote) > 0)
    {
	    ITS_TRACE_DEBUG(("Try reconnecting to secondary\n "));
    	SCTPTRAN_ConnectToSec((SCTPTRAN_Manager *)remote);
	    SCTPTRAN_CONN_TO_SEC(remote) = 0;
    }
    else
    {
	    ITS_TRACE_DEBUG(("Try reconnecting to primary. \n"));
	    SCTPTRAN_Connect(remote);
	    SCTPTRAN_CONN_TO_SEC(remote) = 1;
    } 
    return (ITS_SUCCESS);
}

#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method closes an SCTP socket
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SCTPTRAN_Close(SOCKTRAN_Manager *m)
{
    if (SCTPTRAN_CLOSE(m) == NULL)
    {
        return;
    }

    (*SCTPTRAN_CLOSE(m))((SCTPTRAN_ManagerPtr)m);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method gets the state of an associtation
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     ITS_SCTP_STATE 
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_GetAssocState(SOCKTRAN_Manager *m, ITS_SCTP_STATE *state)
{
    SCTP_API_IOCTL_ARG   arg;
    struct sockaddr_in  to;
    memset(&to, 0, sizeof(to));
    int sd = 0;
    
    int ret = ITS_SUCCESS;
    
    if (m != NULL)
    {
        sd = SOCKTRAN_SOURCE(m)->socket;

        to.sin_addr.s_addr = 
           ((struct sockaddr_in*)(m->socket.connect->addr))->sin_addr.s_addr;
        to.sin_port = m->socket.port;
        to.sin_port = SOCK_NToHS(to.sin_port);
        memcpy(&arg.addr, &to, sizeof(struct sockaddr_in));

        /* get the number of available streams */
        ret = SCTPTRAN_IOCTL(m)((SCTPTRAN_ManagerPtr)m, 
                                IOCTL_GET_STATE_REPORT, 
                                &arg);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTPTRAN_GetAssocState: Failed to get assoc "
                             "state, ret = %d\n", ret));
        }
        else
        {
            *state = arg.value; 
        }
    }
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds a local end point.
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
 *      ITS_SUCCESS - transport built.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
static int
LocalCreate(ITS_Object h, va_list args)
{
    char buf[ITS_PATH_MAX];
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    int i;
    SCTP_PAYLOAD_FAMILY pfamily = 0;

    ITS_TRACE_DEBUG(("CreateLocal:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    /* Get the codec */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(h), TRANSPORT_NAME(h),
                              PAYLOAD_TYPE_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: INI is missing "
                         "payload type.\n"));

        return (ITS_ENOTRANSPORT);
    }

    pfamily = SCTPTRAN_GetPayloadFamily(buf);

    for (i = 0; i < SCTP_PAYLOAD_MAX; i++)
    {
        if (codecs[pfamily][i].name && 
            strcmp(codecs[pfamily][i].name, buf) == 0)
        {
            SCTPTRAN_PAYLOAD(h) = codecs[pfamily][i].type;
            SCTPTRAN_ENCODE(h) = codecs[pfamily][i].encode;
            SCTPTRAN_DECODE(h) = codecs[pfamily][i].decode;

            break;
        }
    }

    ITS_C_ASSERT(i != SCTP_PAYLOAD_MAX);

    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(h); i++)
    {
        SCTPTRAN_PAYLOAD(SOCKTRAN_REMOTES(h)[i]) = SCTPTRAN_PAYLOAD(h);
        SCTPTRAN_ENCODE(SOCKTRAN_REMOTES(h)[i]) = SCTPTRAN_ENCODE(h);
        SCTPTRAN_DECODE(SOCKTRAN_REMOTES(h)[i]) = SCTPTRAN_DECODE(h);
    }

    /* bail on no codec */
    if (i == SCTP_PAYLOAD_MAX)
    {
        ITS_TRACE_ERROR(("Codec not found\n"));

        return (ITS_ENOTRANSPORT);
    }

    /* allocate the read buffer */
    SCTPTRAN_BUFFER(h) = ITS_Malloc(LKSCTP_MAX_BUFF_SIZE);
    if (SCTPTRAN_BUFFER(h) == NULL)
    {
        ITS_TRACE_ERROR(("LocalCreate: out of memory\n"));

        return (ITS_ENOMEM);
    }

#if 0
    if (lkClass == NULL)
    {
        return (ITS_SUCCESS);
    }
#endif

    /* Get the server state */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(h), TRANSPORT_NAME(h),
                              IS_CLIENT_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        SCTPTRAN_IS_CLIENT(h) = ITS_FALSE;
    }
    else
    {
        SCTPTRAN_IS_CLIENT(h) = strcmp(buf, "YES") == 0 ||
                                  strcmp(buf, "yes") == 0;
    }

    /* may need to listen if server */
    if (SCTPTRAN_IS_CLIENT(h))
    {
        /* IS CLIENT */
    }
    else
    {
        /* We need to Listen */
        if (SCTPTRAN_LISTEN(h) != NULL)
        {
            if ((SCTPTRAN_LISTEN(h))((SCTPTRAN_ManagerPtr)h, 
                                      SOMAXCONN) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't bind addr\n"));

                ((SCTPTRAN_CLOSE(h))((SCTPTRAN_ManagerPtr)h));

                return (ITS_EINVALIDARGS);
            }
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method  to print SCTPTRAN_Objectpart
 *
 *  Input Parameters:
 *      SCTPTRAN_Objectpart: the object to be printed
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Sarvesh       31-01-2014  				                Debuging
 *
 ****************************************************************************/


static void PrintSCTPTranObject(SCTPTRAN_Manager *obj)
{
    ITS_TRACE_DEBUG(("SCTPTransObject  \n "));	
    ITS_TRACE_DEBUG(("ptype             %d \n ",SCTPTRAN_PAYLOAD(obj)));	
    ITS_TRACE_DEBUG(("buffer            %s \n ",SCTPTRAN_BUFFER(obj)));	
    ITS_TRACE_DEBUG(("isClient          %d \n ",SCTPTRAN_IS_CLIENT(obj)));	
    ITS_TRACE_DEBUG(("inStreams         %d \n ",SCTPTRAN_INSTREAMS(obj)));	
    ITS_TRACE_DEBUG(("outStreams        %d \n ",SCTPTRAN_OUTSTREAMS(obj)));	
    ITS_TRACE_DEBUG(("state             %d \n ",SCTPTRAN_STATE(obj)));	
    ITS_TRACE_DEBUG(("flags             %d \n ",SCTPTRAN_FLAGS(obj)));	
    ITS_TRACE_DEBUG(("numExtraHomes     %d \n ",SCTPTRAN_NUMEXTRAHOMES(obj)));	
}

int PrintMyAddr(struct sockaddr_in *to)
{
    unsigned int x;
    x = ntohl(to->sin_addr.s_addr);
    ITS_TRACE_DEBUG(("Printing the IP ADDR as %d.%d.%d.%d:%d \n",
              (int)((x>>24) & 0x000000ff),
              (int)((x>>16) & 0x000000ff),
              (int)((x>>8) & 0x000000ff),
              (int)(x & 0x000000ff),
              ntohs(to->sin_port)));
    return 1;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method frees the remote end point.
 *
 *  Input Parameters:
 *      ITS_Objetc : the object to be freed
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Rajnikant     04-06-2007   				 LK-SCTP Integration
 *
 ****************************************************************************/

static void RemoteDestroy(ITS_Object obj)
{
    int i = 0;
    
    ITS_TRACE_DEBUG(("Destroying SCTP Object  \n "));	
    SCTPTRAN_Manager *ret = (SCTPTRAN_Manager *)obj;

    PrintSCTPTranObject(ret);

    if(SCTPTRAN_NUMEXTRAHOMES(ret) > 0)
    {
        /*Deallocating the memory for secondary Addresses */	
        for( i = 0; i < SCTPTRAN_NUMEXTRAHOMES(ret); i++)
        {
            PrintMyAddr(((SCTPTRAN_EXTRAHOMES(ret))[i]).addr);
            free(((SCTPTRAN_EXTRAHOMES(ret))[i]).addr);
            ((SCTPTRAN_EXTRAHOMES(ret))[i]).addr = NULL;
        }
        free(SCTPTRAN_EXTRAHOMES(ret));
        SCTPTRAN_EXTRAHOMES(ret) = NULL;
        
        SCTPTRAN_NUMEXTRAHOMES(ret) = 0;	
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds a remote end point.
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
 *      ITS_SUCCESS - transport built.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
static int
RemoteCreate(ITS_Object obj, va_list args)
{
    char buf[ITS_PATH_MAX];
    const char *name = NULL;
    ITS_USHORT instance;
    ITS_UINT mask;
    SCTPTRAN_Manager *local = NULL;

    ITS_TRACE_DEBUG(("CreateRemote: %08x\n", obj));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);
    local = va_arg(args, SCTPTRAN_Manager *);

    SCTPTRAN_PAYLOAD(obj) = SCTPTRAN_PAYLOAD(local);
    SCTPTRAN_ENCODE(obj) = SCTPTRAN_ENCODE(local);
    SCTPTRAN_DECODE(obj) = SCTPTRAN_DECODE(local);
    
    /* allocating the memory for the secondary address here */
    /* Multi home setup */
    SCTPTRAN_RECONN_STATE(obj) = 1;
    SCTPTRAN_CONN_TO_SEC(obj) = 1;
	
    /*FIXME: I think the below #if 0 ed code can be thrown off as we
     are now allocating memory for SCTPTRANS_EXTRAHOMES(obj) in
     AddRemoteTransport. Keep this code till testing*/
#if 0
    if((SCTPTRAN_SECADDR(obj)) == NULL)
    {
        if ((SCTPTRAN_SECADDR(obj) =
        (ITS_SocketInfo *)calloc(1,
                               sizeof(ITS_SocketInfo))) == NULL)
        {
            ITS_TRACE_ERROR(("RemoteCreate: out of memory.\n"));

            return (ITS_ENOMEM);
        }

        if (SOCK_CreateAddr(INET_DOMAIN, "0.0.0.0", 0,
                        &SCTPTRAN_SECADDR(obj)->addr,
                        &SCTPTRAN_SECADDR(obj)->asize) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("LocalCreate: Out of memory.\n"));

            return (ITS_ENOMEM);
        }

        SCTPTRAN_SECFLAG(obj) = 0;
    }
#endif
    /* Get the client state */

    ITS_TRACE_DEBUG(("Transport Name = %s SCTPTRAN_NUMEXTRAHOMES = %d\n",TRANSPORT_NAME(obj),SCTPTRAN_NUMEXTRAHOMES(obj)));
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(obj), TRANSPORT_NAME(obj),
                              IS_CLIENT_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        SCTPTRAN_IS_CLIENT(obj) = ITS_FALSE;
    }
    else
    {
        SCTPTRAN_IS_CLIENT(obj) = strcmp(buf, "YES") == 0 ||
                                  strcmp(buf, "yes") == 0;
    }

#if 1
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(obj), TRANSPORT_NAME(obj),
                              LOCAL_HOST_NAME_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
       ITS_TRACE_DEBUG(("LOCAL_HOST_NAME_STRING = %s\n",buf));
    }
    else
    {
       SCTPTRAN_NUMEXTRAHOMES(obj) = 1;
       if((SCTPTRAN_EXTRAHOMES(obj) = 
        (ITS_SocketInfo *)calloc(1,
                               sizeof(ITS_SocketInfo))) == NULL)
        {
            ITS_TRACE_ERROR(("RemoteCreate: out of memory.\n"));

            return (ITS_ENOMEM);
        }

       ITS_TRACE_DEBUG(("LOCAL_HOST_NAME_STRING = %s SOCKTRAN_PORT = %d \n",buf, SOCKTRAN_PORT((SOCKTRAN_Manager *)obj)));
#if 1 
        if (SOCK_CreateAddr(INET_DOMAIN, buf, SOCKTRAN_PORT((SOCKTRAN_Manager *)obj),
#else
        if (SOCK_CreateAddr(INET_DOMAIN, buf, 0,
#endif

                        &SCTPTRAN_EXTRAHOMES(obj)->addr,
                        &SCTPTRAN_EXTRAHOMES(obj)->asize) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("RemoteCreate: Out of memory.\n"));

            return (ITS_ENOMEM);
        }      
    }
#endif


    /* may need to connect */
    if (SCTPTRAN_IS_CLIENT(obj))
    {
        int retVal;

        retVal = SCTPTRAN_Connect((SOCKTRAN_Manager *)obj);

        //if (lkClass != NULL)
        { 
            if (retVal != ITS_SUCCESS)
            {
                /* Reconnect */
                return(SCTPTRAN_ReConnect((SOCKTRAN_Manager *)local,
                                          (SOCKTRAN_Manager *)obj));
            }
            else
            {
                return(ITS_SUCCESS);
            }
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method adds a (possibly) new remote to the local transport.
 *
 *  Input Parameters:
 *      local - the transport to add to
 *      msg - info about the new association
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The remote added.  NULL indicates processing failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/


static SCTPTRAN_Manager *
AddRemoteTransport(SCTPTRAN_Manager *local,
                   SCTP_API_MSG_HDR *msg)
{
    int i = 0, j = 0, index = 0, l =0, m=0 ;
    ITS_SocketInfo a, b, c, d;
    ITS_USHORT trid;
    char buf[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];
    SOCK_IPv4Addr addr;
    ITS_USHORT port;
    SCTPTRAN_Manager *ret = NULL;
    ITS_INT mask = TRANSPORT_MASK(local);

    /*Note: a - contains the sock address of incoming msg
      b - contains sock address of a particular remote
      transport of the given local
      c - contains the secondary addresses of incoming msg
      */

    a.type = 0;
    a.af = 0;
    a.addr = (void *)msg->name;
    a.asize = msg->nameLen;

    memset(buf,   0, sizeof(char) * ITS_PATH_MAX);
    memset(value, 0, sizeof(char) * ITS_PATH_MAX);

    ITS_TRACE_DEBUG(("AddRemote\n"));

    /* check if already there? */
    /* FIXME: this is the most in efficient search. this loop is going to be
       a killer if the local is an SCTP server and we need to support 64K
       remote SCTP clients. In that case this loop in worst case will execute
       64000 * numHomes for each client */
    ITS_TRACE_DEBUG(("Remote count = %d\n",SOCKTRAN_REMOTE_COUNT(local)));
    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(local); i++)
    {
        b.type = 0;
        b.af = 0;
        b.addr = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->addr;
        b.asize = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->asize;


        ret = (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];



        // return ret;


        /*msg->secNames will contain even the primary address of the remote
          So if we iterate through secNames and compare it with b thats
          enough*/


        /*
           The address in the message matches with the one being added 
           on the client side in a multihomed setup. The client knows 
           the primary through configuration and comes to know the secondary 
           after setting up the connection.
           */

        /* Comparing the first address present in the msg with the address 
           present on transport object  */ 

        if (SOCK_AddrsAreEqual(&a, &b))
        {
            ITS_TRACE_DEBUG(("Remote already present: %d trid %08x %d\n", i,
                        SOCKTRAN_REMOTES(local)[i],
                        TRANSPORT_INSTANCE(SOCKTRAN_REMOTES(local)[i])));

            /*Check if the remote transport being added has 
              multiple homes. If yes then check if extraHomes field in the
              remote transport object is already assigned memory. If yes
              free the memory and reallocate as per the new number of
              remote homes received in the msg
              */
            if( NULL != SCTPTRAN_EXTRAHOMES(ret) )
            {
                RemoteDestroy((ITS_Object)ret);
            }

            if( NULL == SCTPTRAN_EXTRAHOMES(ret) && (msg->numSecNames > 1) )
            {
                if ((SCTPTRAN_EXTRAHOMES(ret) =
                            (ITS_SocketInfo *)calloc((msg->numSecNames - 1),
                                sizeof(ITS_SocketInfo))) == NULL)
                {
                    ITS_TRACE_ERROR(("AddRemoteTransport: out of memory.\n"));

                    return NULL;
                }

            }

            index = 0;                
            for( j = 0; j < msg->numSecNames; j++ )
            {
                c.type = 0;
                c.af = 0;
                c.addr = (void *)(((struct sockaddr_in*)msg->secNames) + j);
                c.asize = sizeof(struct sockaddr_in);

                /* Copy the secondary address only if its not
                   equal to the primary address */

                if(SOCK_AddrsAreEqual(&a, &c) != ITS_TRUE)
                {

                    ITS_TRACE_DEBUG(("The Secondary IP Address is\n"));	
                    PrintMyAddr(c.addr);

                    if (SOCK_CreateAddr(INET_DOMAIN, "0.0.0.0", 0,
                                &SCTPTRAN_EXTRAHOMES(ret)[index].addr,
                                &SCTPTRAN_EXTRAHOMES(ret)[index].asize) 
                            != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR(("LocalCreate: Out of memory.\n"));

                        return NULL;
                    }

                    SCTPTRAN_EXTRAHOMES(ret)[index].type  = c.type;
                    SCTPTRAN_EXTRAHOMES(ret)[index].af    = c.af;
                    SCTPTRAN_EXTRAHOMES(ret)[index].asize = c.asize;

                    memcpy(SCTPTRAN_EXTRAHOMES(ret)[index].addr,
                            c.addr,
                            sizeof(struct sockaddr_in));
                    index++;                        
                }
            }
            if(msg->numSecNames > 1)
            {
                SCTPTRAN_NUMEXTRAHOMES(ret) = msg->numSecNames - 1;
            }

            ITS_TRACE_DEBUG(("The Transport is already there for IP Address\n"));	
            PrintMyAddr(a.addr);	
            return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
        }
        else if((msg->numSecNames > 0))
        {
            for(l=0; l< msg->numSecNames ; l++)
            {
                c.type = 0;
                c.af = 0;
                c.addr = (void *)(((struct sockaddr_in*)msg->secNames) + l);
                c.asize = sizeof(struct sockaddr_in);

                if(SOCK_AddrsAreEqual(&c, &b) == ITS_TRUE)
                {
                    if( NULL != SCTPTRAN_EXTRAHOMES(ret) )
                    {
                        RemoteDestroy((ITS_Object)ret);
                    }

                    ITS_TRACE_DEBUG(("IP Address is (a.addr)\n"));
                    PrintMyAddr(a.addr);

#if 1
                    if( NULL == SCTPTRAN_EXTRAHOMES(ret) )
                    {
                        if ((SCTPTRAN_EXTRAHOMES(ret) =
                                    (ITS_SocketInfo *)calloc((msg->numSecNames),
                                        sizeof(ITS_SocketInfo))) == NULL)
                        {
                            ITS_TRACE_ERROR(("AddRemoteTransport: out of memory.\n"));

                            return NULL;
                        }

                    }

#endif

#if 0

                    if( NULL == SCTPTRAN_EXTRAHOMES(ret) )
                    {
                        if ((SCTPTRAN_EXTRAHOMES(ret) =
                                    (ITS_SocketInfo *)calloc((msg->numSecNames - 1),
                                        sizeof(ITS_SocketInfo))) == NULL)
                        {
                            ITS_TRACE_ERROR(("AddRemoteTransport: out of memory.\n"));

                            return NULL;
                        }

                    }
#endif
#if 0
                    if(((SCTPTRAN_EXTRAHOMES(ret))[index]).addr == NULL)
                    {
                        SCTPTRAN_EXTRAHOMES (ret)[index].addr = 
                            (struct sockaddr_in *)calloc(1,sizeof(struct sockaddr_in));	
                    }

                    SCTPTRAN_EXTRAHOMES (ret)[0].type = a.type;
                    SCTPTRAN_EXTRAHOMES (ret)[0].af = a.af;
                    SCTPTRAN_EXTRAHOMES (ret)[0].asize = a.asize;

                    memcpy (SCTPTRAN_EXTRAHOMES (ret)[index].addr,
                            a.addr, sizeof (struct sockaddr_in));
#endif

                    ITS_TRACE_DEBUG(("Incoming Message IP Address is\n"));	
                    PrintMyAddr(a.addr);

                    if (SOCK_CreateAddr(INET_DOMAIN, "0.0.0.0", 0,
                                &SCTPTRAN_EXTRAHOMES(ret)[l].addr,
                                &SCTPTRAN_EXTRAHOMES(ret)[l].asize) 
                            != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR(("LocalCreate: Out of memory.\n"));

                        return NULL;
                    }

                    ITS_TRACE_DEBUG(("l = %d index = %d\n",l,index));
                    SCTPTRAN_EXTRAHOMES(ret)[l].type  = a.type;
                    SCTPTRAN_EXTRAHOMES(ret)[l].af    = a.af;
                    SCTPTRAN_EXTRAHOMES(ret)[l].asize = a.asize;

                    memcpy(SCTPTRAN_EXTRAHOMES(ret)[l].addr,
                            a.addr,
                            sizeof(struct sockaddr_in));
                    /* changes made for the bug 4177, 
                    
                       In the below loop "index" variable is used. 
                       if we didnt increment this value, index will be
                       zero and it will replace the ip.
                    */
                    index++;

                    for(m= 1; m < msg->numSecNames ; m++)
                    {
                        d.type = 0;
                        d.af = 0;
                        d.addr = (void *)(((struct sockaddr_in*)msg->secNames) + m);
                        d.asize = sizeof(struct sockaddr_in);

                        if(SOCK_AddrsAreEqual(&d, &c) != ITS_TRUE)
                        {
                            ITS_TRACE_DEBUG(("The Secondary IP Address is\n"));
                            PrintMyAddr(c.addr);

                            if (SOCK_CreateAddr(INET_DOMAIN, "0.0.0.0", 0,
                                        &SCTPTRAN_EXTRAHOMES(ret)[index].addr,
                                        &SCTPTRAN_EXTRAHOMES(ret)[index].asize)
                                    != ITS_SUCCESS)
                            {
                                ITS_TRACE_ERROR(("LocalCreate: Out of memory.\n"));

                                return NULL;
                            }

                            ITS_TRACE_DEBUG(("l = %d index = %d\n",l,index));
                            SCTPTRAN_EXTRAHOMES(ret)[index].type  = d.type;
                            SCTPTRAN_EXTRAHOMES(ret)[index].af    = d.af;
                            SCTPTRAN_EXTRAHOMES(ret)[index].asize = d.asize;

                            memcpy(SCTPTRAN_EXTRAHOMES(ret)[index].addr,
                                    d.addr,
                                    sizeof(struct sockaddr_in));

                            index++;

                        }

                    }

                    /*
                       Add this "return" as part of the fix for the bug 4177 (Fri Aug  8 15:20:39 IST 2014)
                       */
                    SCTPTRAN_NUMEXTRAHOMES(ret) = index - 1;        

                    return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
                }
            }
        }

#if 0
        else if ((msg->numSecNames > 0) && SOCK_AddrsAreEqual(&c, &b))
        {
            ITS_TRACE_DEBUG(("Remote already present: %d trid %08x %d\n", i,
                        SOCKTRAN_REMOTES(local)[i],
                        TRANSPORT_INSTANCE(SOCKTRAN_REMOTES(local)[i])));
            /* if second address is present in msg then copy it on the second
               address field of transport */
            if(SCTPTRAN_SECFLAG(ret) == 0)
            {
                if(SCTPTRAN_SECADDR(ret) !=NULL)
                {
                    SCTPTRAN_SECFLAG(ret) = 1;
                    SCTPTRAN_SECADDR(ret)->type = a.type;
                    SCTPTRAN_SECADDR(ret)->af = a.af;
                    SCTPTRAN_SECADDR(ret)->asize = a.asize;
                    memcpy(SCTPTRAN_SECADDR(ret)->addr,
                            a.addr,
                            sizeof(struct sockaddr_in));
                }
            }
            ITS_TRACE_DEBUG(("The Transport is already there for IP Address\n"));	
            PrintMyAddr(c.addr);	
            return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
        }
#endif



    }

    /* find a slot.  Not very efficient, but we don't check that many */
    if (TRANSPORT_LockManager() != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't lock transport manager\n"));

        return (NULL);
    }

    for (trid = SCTPTRAN_FIRST_SRC; trid <= SCTPTRAN_LAST_SRC; trid++)
    {
        TRANSPORT_Control *tc;

        if ((tc = TRANSPORT_FindTransportNoLock(trid)) == NULL)
        {
            break;
        }
    }

    /* overflow */
    if (trid == SCTPTRAN_LAST_SRC + 1)
    {
        ITS_TRACE_ERROR(("Too many associations\n"));

        TRANSPORT_UnlockManager();

        return (NULL);
    }

    /* reserve this slot */
    TRANSPORT_ReserveSlot(trid);

    /* release the lock */
    TRANSPORT_UnlockManager();

    /* add the section and vars */
    sprintf(buf, SCTP_TRANSPORT_NAME, trid);

    if (RESFILE_Lock(TRANSPORT_RES(local)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't get DB lock\n"));

        return (NULL);
    }

    /* section */
    if (RESFILE_AddSection(TRANSPORT_RES(local), buf) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't add section.\n"));

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    /* variables */
    if (SOCK_GetIPv4AddrAndPort((SOCK_AddrStore *)msg->name,
                &addr, &port) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't get addr.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    if (SOCK_IPv4AddrToName(value, addr) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't decode addr.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    /* host addr */
    if (RESFILE_AddKeyValue(TRANSPORT_RES(local), buf,
                SERVER_PATH_STRING, value) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't add variable.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    /* port */
    sprintf(value, "%u", port);
    if (RESFILE_AddKeyValue(TRANSPORT_RES(local), buf,
                SERVER_PORT_STRING, value) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't add variable.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    if (SOCKTRAN_EndPointAddVirtualTransport((SOCKTRAN_Manager *)local,
                buf, trid,
                ITS_TRANSPORT_SINGLE_USER|
                mask) !=
            ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Failed to create remote transport\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    RESFILE_Unlock(TRANSPORT_RES(local));

    /* we use the nolock method to avoid adding a reference */
    if (TRANSPORT_LockManager() != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't lock transport manager\n"));

        return (NULL);
    }

    ret = (SCTPTRAN_Manager *)TRANSPORT_FindTransportNoLock(trid);

    /* Transport got created dynamically (not throught xml file) */
    /* multi home setup */

    /* Why are we comparing against 1 here? Reason is go and
       check the comments in LKSCTP_GetSecondaryAddresses and
       SKSCTP_GetSecondaryAddresses. As explained there we get
       the primary address also in the secNames. So if the remote
       is truly multihomed then including the primary the
       numSecNames needs to be greater than 1
       */
    if(msg->numSecNames > 1)
    {
        if( NULL != SCTPTRAN_EXTRAHOMES(ret) )
        {
            RemoteDestroy((ITS_Object)ret);                    
        }

        if( NULL == SCTPTRAN_EXTRAHOMES(ret) )
        {
            if ((SCTPTRAN_EXTRAHOMES(ret) =
                        (ITS_SocketInfo *)calloc((msg->numSecNames - 1),
                            sizeof(ITS_SocketInfo))) == NULL)
            {
                ITS_TRACE_ERROR(("AddRemoteTransport: out of memory.\n"));

                return NULL;
            }

        }
        index = 0;        
        for( i = 0; i < msg->numSecNames; i++)
        {

            c.type = 0;
            c.af = 0;
            c.addr = (void *)(((struct sockaddr_in*)msg->secNames) + i);
            c.asize = sizeof(struct sockaddr_in);

            if(SOCK_AddrsAreEqual(&a, &c) != ITS_TRUE)
            {
                if ( SOCK_CreateAddr(INET_DOMAIN, "0.0.0.0", 0,
                            &SCTPTRAN_EXTRAHOMES(ret)[index].addr,
                            &SCTPTRAN_EXTRAHOMES(ret)[index].asize)
                        != ITS_SUCCESS )
                {
                    ITS_TRACE_ERROR(("LocalCreate: Out of memory.\n"));

                    return NULL;
                }

                SCTPTRAN_EXTRAHOMES(ret)[index].type = c.type;
                SCTPTRAN_EXTRAHOMES(ret)[index].af   = c.af;
                SCTPTRAN_EXTRAHOMES(ret)[index].asize = c.asize;
                memcpy(SCTPTRAN_EXTRAHOMES(ret)[index].addr,
                        c.addr,
                        sizeof(struct sockaddr_in));
                index++;                
            }
        }
        SCTPTRAN_NUMEXTRAHOMES(ret) = msg->numSecNames - 1;        
    }
    ITS_TRACE_DEBUG(("The Transport is Created for IP Address\n"));	
    PrintMyAddr(a.addr);	

    TRANSPORT_UnlockManager();

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method finds a remote from the local transport.
 *
 *  Input Parameters:
 *      local - the transport to add to
 *      msg - info about the association
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The remote found.  NULL indicates processing failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SCTPTRAN_Manager *
FindRemoteTransport(SCTPTRAN_Manager *local,
                    SCTP_API_MSG_HDR *msg)
{
    int i, j;
    ITS_SocketInfo a, b, c;

    a.type = 0;
    a.af = 0;
    a.addr = (void *)msg->name;
    a.asize = msg->nameLen;

    SCTPTRAN_Manager *rem;

    ITS_TRACE_DEBUG(("FindRemote\n"));

    PrintMyAddr(a.addr);    	

    /* Check list */
    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(local); i++)
    {
        b.type = 0;
        b.af = 0;
        b.addr = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->addr;
        b.asize = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->asize;

        if (SOCK_AddrsAreEqual(&a, &b))
        {
            ITS_TRACE_DEBUG((" Found Remote Transport for Address\n"));
      	    PrintMyAddr(a.addr);    	
            ITS_TRACE_DEBUG(("FindRemote: found %08x\n",
                             SOCKTRAN_REMOTES(local)[i]));

            return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
        }
	/* else compare with secondary IP*/
        else
        {
            rem = (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
            ITS_TRACE_DEBUG(("SCTPTRAN_NUMEXTRAHOMES %d \n",SCTPTRAN_NUMEXTRAHOMES(rem)));
            for( j = 0; j < SCTPTRAN_NUMEXTRAHOMES(rem); j++ )
            {                

                /*---m trial--commented to fix multihoming at server-------starts----*/
                #if 0
                b.addr = SCTPTRAN_EXTRAHOMES(rem)[i].addr;
                b.asize = SCTPTRAN_EXTRAHOMES(rem)[i].asize;
                #endif
                /*---m trial--commented to fix multihoming at server-------ends------*/

                /*---m trial--added to fix multihoming at server-------starts----*/
	        c.type = 0;
        	c.af = 0;

                c.addr = SCTPTRAN_EXTRAHOMES(rem)[j].addr;
                c.asize = SCTPTRAN_EXTRAHOMES(rem)[j].asize;
            	ITS_TRACE_DEBUG((" Extrahomes present in our configuration \n"));
                PrintMyAddr(c.addr);           //---m trial--added to fix multihoming at server

                /*---m trial--added to fix multihoming at server-------ends------*/

                //if (SOCK_AddrsAreEqual(&a, &b))   //---m trial--commented to fix multihoming at server

		if (SOCK_AddrsAreEqual(&a, &c))     //---m trial--added to fix multihoming at server
                {
            	    ITS_TRACE_DEBUG((" Found Remote Transport for Address\n"));

                    PrintMyAddr(c.addr);           //---m trial--added to fix multihoming at server
      	    	    //PrintMyAddr(b.addr);         //---m trial--commented to fix multihoming at server	

                    ITS_TRACE_DEBUG(("FindRemote: found %08x\n",
                             SOCKTRAN_REMOTES(local)[i]));

                    return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
                }
            }
        }
    }

    ITS_TRACE_ERROR(("FindRemote: no transport found Iterations %d\n",i));

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an ITS_EVENT from a SCTP socket.
 *
 *  Input Parameters:
 *      h - the handle to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name             Date        Reference               Description
 * -----------------------------------------------------------------------------
 * ssingh          04-01-2005  BugId: 924/770/818   Added changes along with code 
 *                             826/861/867        propagated for PAUSE/RESUME @ ASP.
 *
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 * chandrabs       16/09/2008                      Fix for whizible issue 1107
 ****************************************************************************/
static int
SCTPReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int sz, ret;
    SCTPTRAN_Manager* local = (SCTPTRAN_Manager*)h;
    //int sd = SOCKTRAN_SOURCE(local)->socket;
    SCTP_API_MSG_HDR msg;
    SCTP_API_IOVEC iovec;
    SCTP_API_CMSG cmsg;
    SOCK_AddrStore addr;
    ITS_BOOLEAN doReturn, isManagement;
    SCTPTRAN_Manager *rem;
    ITS_OCTET sls = 0;
    SCTP_API_IOCTL_ARG arg;
    struct sockaddr_in  to;
    int flag = SCTP_API_SYNC;

    msg.name = (ITS_POINTER)&addr;
    msg.nameLen = sizeof(SOCK_AddrStore);
    msg.ioVecs = &iovec;
    msg.numIOVecs = 1;
    iovec.vector = SCTPTRAN_BUFFER(h);
    iovec.len = 65535;
    msg.control = (ITS_POINTER)&cmsg;
    msg.controlLen = sizeof(cmsg);
    cmsg.hdr.type = 0;

    sz = 0;

    msg.secNames    = NULL;
    msg.numSecNames = 0;

    ITS_TRACE_DEBUG(("SCTPReceive\n"));

    if (SCTPTRAN_DECODE(h) == NULL)
    {
        ITS_TRACE_ERROR(("SCTPReceive: no decode\n"));

        return (ITS_ERCVFAIL);
    }

    if (SCTPTRAN_RECVMSG(local) == NULL)
    {
        ITS_TRACE_WARNING(("SCTPReceive: SCTP missing\n"));

        return (ITS_ERCVFAIL);
    }

    
    /*FIXME: Check if ASYNC mode works in sksctp also*/
    //if (lkClass != NULL)
    //{
    //flag = SCTP_API_ASYNC;
    //}
    /*FIXME: Check this part*/
    //else
    //{
        flag = SCTP_API_SYNC;
    //}

    //while ((sz = (*SCTP_RecvMsgPtr)(sd, &msg, flag)) >= 0)
    while ((sz = SCTPTRAN_RECVMSG((local))(local,
                                           &msg,
                                           flag)) >= 0)
    {
        doReturn = ITS_FALSE;
        local = (SCTPTRAN_Manager*)h;
        switch (cmsg.hdr.type)
        {
            case SCTP_CM_DATA_IO:
                /* got data */
                ITS_TRACE_DEBUG(("Got DATA\n"));

                if(SCTPTRAN_PAYLOAD(h) != cmsg.data.sndRcv.payload)
                {
                    ITS_TRACE_ERROR(("\nPayload received %d != configured payload %d",
                                          cmsg.data.sndRcv.payload, SCTPTRAN_PAYLOAD(h)));

#if 0
                    /* Application who needs this information should add a callback to the
                       SCTPTRAN_ManagementCallbacks  callback and perform the necessary action
                       For the time being this invocation of callback is commented.
                    */
                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);
#endif
                }

                rem = FindRemoteTransport(local,
                                          &msg);

                if (rem)
                {
                    ITS_TRACE_DEBUG(("Have data, send to user or MGMT\n"));

                    ITS_EVENT_INIT(ev, TRANSPORT_INSTANCE(rem), sz);

                    memcpy(ev->data, iovec.vector, sz);

                    sls = (ITS_OCTET) cmsg.data.sndRcv.stream;

                    isManagement = ITS_FALSE;

                    if ((ret = SCTPTRAN_DECODE(h)(rem,
                                                  ev,
                                                  &isManagement,
                                                  &sls)) == ITS_SUCCESS)
                    {
                        if (isManagement)
                        {
                            ITS_TRACE_DEBUG(("Send to MGMT\n"));

                            TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, ev);
                        }
                        else
                        {
                            ITS_TRACE_DEBUG(("Send to user\n"));

                            doReturn = ITS_TRUE;
                        }
                    }
                    else
                    {
                        /* only complain if the codec didn't filter */
                        if (ret != ITS_ENOMSG)
                        {
                            ITS_TRACE_DEBUG(("Decode failed\n"));
                        }
                    }

                }
                break;

            case SCTP_CM_ASSOC_CHG:
                ITS_TRACE_DEBUG(("assoc changed: "));

                //SKSCTP_Alarm(7001, __FILE__, __LINE__, "Transport Name=%s", TRANSPORT_NAME(h));

                switch (cmsg.data.assocChg.state)
                {
                    case SCTP_AC_COMM_UP:
                        ITS_TRACE_DEBUG(("ASSOCIATION UP\n"));

                        /* if remote not present, create/add it */
                        rem = AddRemoteTransport(local,
                                                 &msg);

                        /* send open msg to UAL */
                        if (rem)
                        {
                            /* Reset the flags now */
                            SCTPTRAN_RECONN_STATE(rem) = 0;
                            SCTPTRAN_CONN_TO_SEC(rem) = 0;
                            SCTPTRAN_ASSOC_STATE(rem) = ITS_ASSOC_CONNECTED;

                            if (SCTPTRAN_IOCTL(local))
                            {
                                to.sin_addr.s_addr =
                                ((struct sockaddr_in*)(rem->socket.connect->addr))->sin_addr.s_addr;
                                to.sin_port = rem->socket.port;

                                to.sin_port = SOCK_NToHS(to.sin_port);
                                /*copy addr from the msg name*/
                                memcpy(&to,msg.name,msg.nameLen);
                                memcpy(&arg.addr, &to, sizeof(struct sockaddr_in));

                                /* get the number of available streams */
                                if ((SCTPTRAN_IOCTL(local))(local, 
                                                            IOCTL_GET_NUM_OUT_STREAMS, 
                                                            &arg)!= ITS_SUCCESS)
                                {
                                    ITS_TRACE_ERROR(("IOCTL failed to get num out streams.\n"));
                                }
                                else
                                {
                                    SCTPTRAN_OUTSTREAMS(rem) = arg.value;
                                    ITS_TRACE_DEBUG(("The Max Out streams are %u\n",SCTPTRAN_OUTSTREAMS(rem)));
                                }
                            }
                            else
                            {
                                ITS_TRACE_WARNING(("IOCTL Pointer is NULL.\n"));
                            }

                            /* send open msg to UAL */
                            ITS_TRACE_DEBUG(("New remote TRANSPORT added: \n"));

                            /* RESUME will be triggered after the exchange of ASP_ACTIVE/ACTIVE_ACK */
                             TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_TRUE); 

                            CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                     (ITS_POINTER)rem,
                                                     (ITS_POINTER)&msg);
                        }
                        else
                        {
                            ITS_TRACE_WARNING(("Unable to create SCTP remote\n"));
                        }
                        break;

                    case SCTP_AC_COMM_LOST:
                        ITS_TRACE_DEBUG(("ASSOCIATION DOWN\n"));

                        //SKSCTP_Alarm(7002, __FILE__, __LINE__, "Transport Name=%s", TRANSPORT_NAME(h));

                        rem = FindRemoteTransport(local,
                                                  &msg);

                        /* send close msg to UAL */
                        if (rem)
                        {
                            TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);
                            SCTPTRAN_ASSOC_STATE(rem) = ITS_ASSOC_DOWN;

                            CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                     (ITS_POINTER)rem,
                                                     (ITS_POINTER)&msg);
                            /*FIXME: The reconnect logic should happen even in sksctp.
                              So commenting out the check for lkClass */
                            //if (lkClass != NULL)
                            {
                                if (SCTPTRAN_IS_CLIENT(local))
                                {
                                    /* if client try to reconnect */
                                    //SCTPTRAN_ReConnectOnLostCommunication(local,
                                    //                                      (SOCKTRAN_Manager *)rem);
                                    SCTPTRAN_Connect((SOCKTRAN_Manager*)rem);
  
                                    /* Re-connect caretes a new FD, till now things
                                       worked as the newly allocated fd value co-incidently remained
                                       remained the same as previous.*/
                                    //sd = SOCKTRAN_SOURCE(local)->socket;
                                    ITS_TRACE_DEBUG(("Called Asynchoronus connect,waiting for either a \
                                                  SCTP_AC_COMM_LOST or  SCTP_AC_CANT_START \n"));
                                    SCTPTRAN_RECONN_STATE(rem) = 1;
                                    continue;
                                }
                                else
                                {
                                    /* delete the section */
                                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                    {
                                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                        RESFILE_Unlock(TRANSPORT_RES(rem));
                                    }

                                    /* if remote present, remove/delete it */
                                    SOCKTRAN_EndPointRemVirtualTransport(
                                               (SOCKTRAN_Manager*)local,
                                                TRANSPORT_INSTANCE(rem));

                                    ITS_DestructObject((ITS_Object)rem);
                                }
                            }
#if 0
                            else
                            {
                                /* delete the section */
                                if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                {

                                    RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                    RESFILE_Unlock(TRANSPORT_RES(rem));
                                }

                                if (SCTPTRAN_IS_CLIENT(rem))
                                {
                                    /* if client try to reconnect */
                                    (*SCTP_ConnectPtr)(sd, (SOCK_AddrStore *)msg.name, msg.nameLen);
                                }
                                else
                                {
                                    /* delete the section */
                                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                    {
                                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                        RESFILE_Unlock(TRANSPORT_RES(rem));
                                    }

                                    /* if remote present, remove/delete it */
                                    SOCKTRAN_EndPointRemVirtualTransport(local,
                                                                         TRANSPORT_INSTANCE(rem));

                                    ITS_DestructObject((ITS_Object)rem);
                                }
                            }
#endif
                        }
                        break;

                    case SCTP_AC_COMM_RESTART:
                        ITS_TRACE_DEBUG(("ASSOCIATION RESTART\n"));

                        //SKSCTP_Alarm(7003, __FILE__, __LINE__, "Transport Name=%s", TRANSPORT_NAME(h));

                        /* if remote not present, create/add it */
                        rem = AddRemoteTransport(local,
                                                 &msg);

                        /* send open msg to UAL */
                        if (rem)
                        {
                            SCTPTRAN_ASSOC_STATE(rem) = ITS_ASSOC_CONNECTED;

                            if (SCTPTRAN_IOCTL(local))
                            {
                                to.sin_addr.s_addr =
                                ((struct sockaddr_in*)(rem->socket.connect->addr))->sin_addr.s_addr;
                                to.sin_port = rem->socket.port;

                                to.sin_port = SOCK_NToHS(to.sin_port);

                                memcpy(&to,msg.name,msg.nameLen);
                                memcpy(&arg.addr, &to, sizeof(struct sockaddr_in));

                                /* get the number of available streams */
                                if ( (SCTPTRAN_IOCTL(local))(local, 
                                        IOCTL_GET_NUM_OUT_STREAMS, 
                                        &arg)  != ITS_SUCCESS )
                                {
                                    ITS_TRACE_ERROR(("IOCTL failed to get num out streams.\n"));
                                }
                                else
                                {
                                    SCTPTRAN_OUTSTREAMS(rem) = arg.value;
                                }
                            }
                            else
                            {
                                ITS_TRACE_WARNING(("IOCTL Pointer is NULL.\n"));
                            }

                            TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                            TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_TRUE);

                            CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                     (ITS_POINTER)rem,
                                                     (ITS_POINTER)&msg);
                        }
                        break;

                    case SCTP_AC_COMM_ABORTED:
                        ITS_TRACE_DEBUG(("ASSOCIATION ABORTED/SHUTDOWN\n"));

                        //SKSCTP_Alarm(7004, __FILE__, __LINE__, "Transport Name=%s", TRANSPORT_NAME(h));

                        rem = FindRemoteTransport(local,
                                                  &msg);

                        /* send close msg to UAL */
                        if (rem)
                        {
                            SCTPTRAN_ASSOC_STATE(rem) = ITS_ASSOC_DOWN;
                            TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                            CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                     (ITS_POINTER)rem,
                                                     (ITS_POINTER)&msg);
                            /*FIXME: The logic to reconnect should be done even 
                              for sksctp*/

                            //if (lkClass != NULL)
                            {
                                if (SCTPTRAN_IS_CLIENT(local))
                                {
                                    /* if client try to reconnect */
                                    if (SCTPTRAN_Connect((SOCKTRAN_Manager *)rem) != ITS_SUCCESS)
                                    {
                                        /* Reconnect */
                                        SCTPTRAN_ReConnect(
                                            (SOCKTRAN_Manager*)local,
                                            (SOCKTRAN_Manager *)rem);
                                        /* Reconnect creates a new socket */                                        
                                    }
                                }
                                else
                                {
                                    /* delete the section */
                                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                    {
                                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                        RESFILE_Unlock(TRANSPORT_RES(rem));
                                    }

                                    /* if remote present, remove/delete it */
                                    SOCKTRAN_EndPointRemVirtualTransport(
                                        (SOCKTRAN_Manager*)local,
                                        TRANSPORT_INSTANCE(rem));
                                    ITS_DestructObject((ITS_Object)rem);
                                }
                            }
#if 0
                            else
                            {
                                /* delete the section */
                                if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                {
                                    RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                    RESFILE_Unlock(TRANSPORT_RES(rem));
                                }

                                if (SCTPTRAN_IS_CLIENT(rem))
                                {
                                    /* if client try to reconnect */
                                    (*SCTP_ConnectPtr)(sd, (SOCK_AddrStore *)msg.name, msg.nameLen);
                                }
                                else
                                {
                                    /* delete the section */
                                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                    {
                                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                        RESFILE_Unlock(TRANSPORT_RES(rem));
                                    }

                                    /* if remote present, remove/delete it */
                                    SOCKTRAN_EndPointRemVirtualTransport(local,
                                                                         TRANSPORT_INSTANCE(rem));
                                    ITS_DestructObject((ITS_Object)rem);
                                }
                            }
#endif
                        }
                        break;
#if 1
                    case SCTP_AC_SHUTDOWN_DONE:
                        ITS_TRACE_DEBUG(("ASSOCIATION SHUTDOWN DONE\n"));

                        rem = FindRemoteTransport(local,
                                                  &msg);

                        /* send close msg to UAL */
                        if (rem)
                        {
                            SCTPTRAN_ASSOC_STATE(rem) = ITS_ASSOC_DOWN;
                            TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                            CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                      (ITS_POINTER)rem,
                                                      (ITS_POINTER)&msg);
                            if (!SCTPTRAN_IS_CLIENT(local))
                            {
                                /* delete the section */
                                if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                {
                                    RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                    RESFILE_Unlock(TRANSPORT_RES(rem));
                                }

                                /* if remote present, remove/delete it */
                                SOCKTRAN_EndPointRemVirtualTransport(
                                        (SOCKTRAN_Manager*)local,
                                        TRANSPORT_INSTANCE(rem));
                                ITS_DestructObject((ITS_Object)rem);
                            }
#if 0
                            /* delete the section */
                            if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                            {
                                RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                RESFILE_Unlock(TRANSPORT_RES(rem));
                            }

                            /* if remote present, remove/delete it */
                            SOCKTRAN_EndPointRemVirtualTransport(
                                (SOCKTRAN_Manager*)local,
                                TRANSPORT_INSTANCE(rem));
                            ITS_DestructObject((ITS_Object)rem);
#endif
                        }
                        break;
#endif

                    case SCTP_AC_CANT_START:
                        ITS_TRACE_DEBUG(("ASSOCIATION CAN'T START\n"));

                        rem = FindRemoteTransport(local,
                                                  &msg);
                        if(rem)
                        {
                            SCTPTRAN_ASSOC_STATE(rem) = ITS_ASSOC_DOWN;
                            /*FIXME: The reconnect logic should be done for 
                             *sksctp also. Hence removing the check
                             *for lkClass */

                            //if (lkClass != NULL)
                            {
                                if(SCTPTRAN_IS_CLIENT(rem))
                                {
                                    //SCTPTRAN_ReConnectOnLostCommunication(
                                    //    (SOCKTRAN_Manager*)local,
                                    //    (SOCKTRAN_Manager *)rem);
                                    //
                                    // Sleep here to avoid the immediate retry.
                                    // after the getting the can't connect event

                                    sleep(TRANSPORT_RECONNECT(local)/1000);
                                    SCTPTRAN_Connect((SOCKTRAN_Manager*)rem); 
                                }
                                else
                                {
                                    /* delete the section */
                                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                    {
                                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                        RESFILE_Unlock(TRANSPORT_RES(rem));
                                    }

                                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                             (ITS_POINTER)rem,
                                                             (ITS_POINTER)&msg);

                                    /* if remote present, remove/delete it */
                                    SOCKTRAN_EndPointRemVirtualTransport(
                                        (SOCKTRAN_Manager*)local,
                                         TRANSPORT_INSTANCE(rem));

                                    ITS_DestructObject((ITS_Object)rem);
                                }
                            }
#if 0
                            else
                            {
                                if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                                {
                                    RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));
                                    RESFILE_Unlock(TRANSPORT_RES(rem));
                                }

                                CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                                         (ITS_POINTER)rem,
                                                         (ITS_POINTER)&msg);

                                /* if remote present, remove/delete it */
                                SOCKTRAN_EndPointRemVirtualTransport(local,
                                                                     TRANSPORT_INSTANCE(rem));

                                ITS_DestructObject((ITS_Object)rem);
                            }
#endif
                        }
                        break;

                    default:
                        ITS_TRACE_DEBUG(("unknown state\n"));
                        break;
                }
                break;

            case SCTP_CM_INTF_CHG:
                ITS_TRACE_DEBUG(("interface changed: "));

                switch (cmsg.data.intfChg.state)
                {
                    case SCTP_IC_ADDR_REACHABLE:
                        ITS_TRACE_DEBUG(("INTF REACHEABLE\n"));
                        break;

                    case SCTP_IC_ADDR_UNREACHABLE:
                        ITS_TRACE_DEBUG(("INTF UNREACHEABLE\n"));
                        break;

                    default:
                        ITS_TRACE_DEBUG(("unknown state\n"));
                        break;
                }
                break;


            case SCTP_CM_SEND_FAIL:
                ITS_TRACE_DEBUG(("send fail\n"));

                break;

            case SCTP_CM_REMOTE_ERR:
                ITS_TRACE_DEBUG(("remote error: cause: %d len: %d\n",
                             cmsg.data.remErr.causeCode,
                             cmsg.data.remErr.causeLen));

                break;

            case SCTP_CM_HB_RESP:
                ITS_TRACE_DEBUG(("hb response\n"));

                break;

            default:
                ITS_TRACE_DEBUG(("unknown notification\n"));

                break;
        }

        if (doReturn)
        {
            break;
        }
    }

    //TODO: call free addrs function of the platform sctp
    SCTPTRAN_FREEPADDRS(local)(msg.secNames);
    if (sz <= 0)
    {
        ITS_TRACE_WARNING(("SCTP Recv failed\n"));

        return (ITS_ERCVFAIL);
    }

    return (sz);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an ITS_EVENT to a UDP socket.
 *
 *  Input Parameters:
 *      h - the handle to write into
 *      ev - the buffer to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 ****************************************************************************/
static int
SCTPWriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    SCTP_API_MSG_HDR msg;
    SCTP_API_IOVEC iovec;
    SCTP_API_CMSG cmsg;
    SOCK_AddrStore addr;

    ITS_BOOLEAN isManagement;
    ITS_OCTET sls;
    int ret;

    ITS_TRACE_DEBUG(("WriteEvent:\n"));

    if (SCTPTRAN_ENCODE(h) == NULL)
    {
        return (ITS_ESENDFAIL);
    }

    if (ev->src == UAL_MANAGER_INSTANCE)
    {
        isManagement = ITS_TRUE;
    }
    else
    {
        isManagement = ITS_FALSE;
    }

    if ((ret = SCTPTRAN_ENCODE(h)(h, ev,
                                  &isManagement, &sls)) != ITS_SUCCESS)
    {
        if (ret == ITS_ENOMSG || ret == ITS_EBADSTATE)
        {
            /* This is ok, the codec is filtering */
            /* return event lengh for ITS_SUCCESS */
            return (ev->len);
        }

        return (ITS_EINVALIDARGS);
    }

    memcpy(&addr, SOCKTRAN_CONNECT(h)->addr, SOCKTRAN_CONNECT(h)->asize);

    msg.name = (ITS_POINTER)&addr;
    msg.nameLen = sizeof(SOCK_AddrStore);
    msg.ioVecs = &iovec;
    msg.numIOVecs = 1;
    iovec.vector = (ITS_POINTER)ev->data;
    iovec.len = ev->len;
    msg.control = (ITS_POINTER)&cmsg;
    msg.controlLen = sizeof(cmsg);
    cmsg.hdr.len = sizeof(SCTP_API_SND_RCV);
    cmsg.hdr.type = SCTP_CM_DATA_IO;
    cmsg.hdr.level = 0;
    cmsg.data.sndRcv.stream = sls;
    cmsg.data.sndRcv.flags = 0;
    cmsg.data.sndRcv.payload = SCTPTRAN_PAYLOAD(h);

    return (SCTPTRAN_SENDMSG(h))((SCTPTRAN_ManagerPtr)(h), 
                              &msg, 
                              SCTP_API_SYNC);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method does the necessary part of shutting down a bad socket.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Shutdown(SOCKTRAN_Manager *ft)
{
    if (MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("Shutdown: mutex corrupted\n"));
        abort();
    }

    if (!SOCKTRAN_IS_VALID(ft))
    {
        MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));

        return;
    }

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    SOCKTRAN_IS_VALID(ft) = ITS_FALSE;

    TRANSPORT_IS_ACTIVE(TRANSPORT(ft)) = ITS_FALSE;

    TRANSPORT_SetState(TRANSPORT(ft), ITS_FALSE);

    if (ITS_IsInstanceOf((ITS_Class)itsSOCKTRAN_ServerClass,
                         (ITS_Object)ft) ||
        ITS_IsInstanceOf((ITS_Class)itsSOCKTRAN_DynamicServerClass,
                         (ITS_Object)ft))
    {
        SOCKTRAN_SOURCE(ft)->addr = NULL;
    }

    if (SCTPTRAN_CLOSE(ft) != NULL)
    {
        (SCTPTRAN_CLOSE(ft))((SCTPTRAN_ManagerPtr)ft);
    }

    SOCKTRAN_SOURCE(ft) = NULL;

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method does the necessary part of restarting a bad socket.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Restart(SOCKTRAN_Manager *ft)
{
    if (SOCKTRAN_IS_VALID(ft))
    {
        return;
    }

    SOCKTRAN_IS_VALID(ft) = ITS_TRUE;

    if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    TRANSPORT_IS_ACTIVE(TRANSPORT(ft)) = ITS_TRUE;

    /* TRANSPORT_SetState(TRANSPORT(ft), ITS_TRUE); */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_READ_EVENT(h)(h, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    if (ret < 0)
    {
        return (ITS_ERCVFAIL);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point, if a message
 *      is pending
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalPeekNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if (NULL == SCTPTRAN_PENDING(h))
    {
        return (ITS_EINVALIDARGS);
    }

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    if ((SCTPTRAN_PENDING(h))(h))
    {
        ret = SOCKTRAN_READ_EVENT(h)(h, ev);

        if (ret < 0)
        {
            MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

            return (ITS_ERCVFAIL);
        }
    }
    else
    {
        ret = ITS_ENOMSG;
    }

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set the exit flag on a transport.
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      doExit - ITS_TRUE to mark the transport to exit
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SetExit(ITS_HANDLE tr, ITS_BOOLEAN doExit)
{
    TRANSPORT_Control *tc;

    TRANSPORT_EXIT_NOW(tr) = doExit;

    /*
     * this is tricky.  The SCTP transport is dual layer; the socket
     * layer hides the underlying task queue.  This code sets the exit
     * flag on the task queue.
     */
    ITS_C_ASSERT(SOCKTRAN_SOURCE(tr) != NULL);

    tc = TRANSPORT_FindTransport((ITS_USHORT)SOCKTRAN_SOURCE(tr)->socket);

    TRANSPORT_UnfindTransport(tc);

    TRANSPORT_SetExit(tc, doExit);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an event to a remote end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RemotePutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_WRITE_EVENT(h)(h, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(h));

    if (ret != ev->len)
    {
        return (ITS_ESENDFAIL);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return an error. Used for mapping GetNextEvent, 
 *      PeeknextEvent and PutEvent in the Iterative Server.
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ReturnErrorFunction(ITS_HANDLE h, ITS_EVENT* event)
{
    return !ITS_SUCCESS;
}

/*
 * forward
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSCTPTRAN_RemoteEndPointClassRec;

static SOCKTRAN_ClassExtRec SCTPReadWrite =
{
    /* core class */
    {
        ITS_EXT_VERSION
    },
    /* socket class */
    {
        SCTPReadEvent,                      /* Read one */
        SCTPWriteEvent,                     /* Write one */
        &itsSCTPTRAN_RemoteEndPointClassRec /* associate */
    }
};



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register a codec here.
 *
 *  Input Parameters:
 *      ptype - the codec type
 *      encode - the encode function
 *      decode - the decode function
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the codec is added, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_RegisterCodec(char *name, SCTP_PAYLOAD ptype,
                       SCTP_CodecPtr encode, SCTP_CodecPtr decode)
{
    SCTP_PAYLOAD_FAMILY pfamily = SCTPTRAN_GetPayloadFamily(name);

    if (ptype > SCTP_PAYLOAD_MAX || encode == NULL || decode == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (codecs[pfamily][ptype].name != NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    codecs[pfamily][ptype].name = strdup(name);
    codecs[pfamily][ptype].type = ptype;
    codecs[pfamily][ptype].encode = encode;
    codecs[pfamily][ptype].decode = decode;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return an error. Used for mapping GetNextEvent, 
 *      PeeknextEvent and PutEvent in the Iterative Server.
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_DeregisterCodec(char *name)
{
    int i;
    SCTP_PAYLOAD_FAMILY pfamily = 0;

    if (name == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    pfamily = SCTPTRAN_GetPayloadFamily(name);

    for (i = 0; i < SCTP_PAYLOAD_MAX; i++)
    {
        if (codecs[pfamily][i].name && strcmp(codecs[pfamily][i].name, name) == 0)
        {
            free(codecs[pfamily][i].name);

            codecs[pfamily][i].name = NULL;
            codecs[pfamily][i].type = 0;
            codecs[pfamily][i].encode = NULL;
            codecs[pfamily][i].decode = NULL;
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return family of the PAYLOAD of SCTP transport . 
 *      This is used to index the codecs family and payload type making it
 *      two dimential array for storring the information.
 *      At present this is returning only for M3UA, but later can be used with
 *      other payload types too. For others index is mapped to zero.
 *
 *  Input Parameters:
 *      name - name of the class of type of the payload string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      SCTP_PAYLOAD_FAMILY 
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static 
SCTP_PAYLOAD_FAMILY SCTPTRAN_GetPayloadFamily(char *name)
{
    SCTP_PAYLOAD_FAMILY pfamily = 0;

    if (strcmp(name, "ANSI-M3UA") == 0)
    {
       pfamily = ANSI_M3UA;
    }
    else if (strcmp(name, "CCITT-M3UA") == 0)
    {
       pfamily = CCITT_M3UA;
    }
    else if (strcmp(name, "TTC-M3UA") == 0)
    {
       pfamily = TTC_M3UA;
    }
    else if (strcmp(name, "PRC-M3UA") == 0)
    {
       pfamily = PRC_M3UA;
    }

    return pfamily;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the SCTP transport subsytem.
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
 *      If the routing subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("Initialize\n"));

    SCTPTRAN_ManagementCallbacks = CALLBACK_InitManager();

    if (SCTPTRAN_ManagementCallbacks == NULL)
    {
        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*
 * the SCTP class record(s)
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSCTPTRAN_LocalEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_LocalEndPointClassRec,  /* the root object */
        sizeof(SCTPTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SCTPTRAN_LOCAL_ENDPOINT_CLASS_NAME,     /* class name */
        ITS_AddFeature,                         /* no class initialize */
        ITS_RemFeature,                         /* no class destructor */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        LocalCreate,                            /* instantiate */
        ITS_INST_NO_DEST,                       /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&SCTPReadWrite            /* extension */
    },
    /* transport */
    {
        LocalGetNextEvent,              /* get next */
        LocalPeekNextEvent,             /* peek next */
        ReturnErrorFunction,            /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        SetExit                         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSCTPTRAN_LocalEndPointClass =
    (TRANSPORT_Class)&itsSCTPTRAN_LocalEndPointClassRec;

ITSDLLAPI SOCKTRAN_ClassRec itsSCTPTRAN_RemoteEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_RemoteEndPointClassRec,  /* the root object */
        sizeof(SCTPTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SCTPTRAN_REMOTE_ENDPOINT_CLASS_NAME,    /* class name */
        ITS_AddFeature,                         /* no class initialize */
        ITS_RemFeature,                         /* no class destructor */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        RemoteCreate,                           /* instantiate */
        RemoteDestroy,                       /* destructor  ITS_INST_NO_DEST*/
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&SCTPReadWrite            /* extension */
    },
    /* transport */
    {
        ReturnErrorFunction,            /* getNext */
        ReturnErrorFunction,            /* peekNext */
        RemotePutEvent,                 /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSCTPTRAN_RemoteEndPointClass =
    (TRANSPORT_Class)&itsSCTPTRAN_RemoteEndPointClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the SCTP transport subsystem.
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
 *
 *  Notes:
 *
 *  See Also:
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("Terminate:\n"));

    CALLBACK_DestroyManager(SCTPTRAN_ManagementCallbacks);
}

ITSDLLAPI ITS_ClassRec itsSCTPTRAN_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SCTPTRAN_CLASS_NAME,            /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsSCTPTRAN_Class = &itsSCTPTRAN_ClassRec;
