/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2004 IntelliNet Technologies, Inc.                 *
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
 *
 *  ID: $Id: dia_oam_server.cpp,v 1.3.6.1.4.1 2013/02/27 08:49:07 jvikram Exp $
 *
 *  LOG: $Log: dia_oam_server.cpp,v $
 *  LOG: Revision 1.3.6.1.4.1  2013/02/27 08:49:07  jvikram
 *  LOG: Warnings raised by Coverity have been fixed
 *  LOG:
 *  LOG: Revision 1.3.6.1  2012/12/28 03:33:37  jvikas
 *  LOG: Bug 770 - Freed memory Leak in AlarmSendToClient.
 *  LOG:
 *  LOG: Revision 1.3  2010/07/07 08:26:25  nvijikumar
 *  LOG: TCS compilation flags support
 *  LOG:
 *  LOG: Revision 1.2  2008/12/10 07:03:51  nvijikumar
 *  LOG: Added WriteEvent function
 *  LOG:
 *  LOG: Revision 1.1  2008/12/05 12:06:50  nvijikumar
 *  LOG: Initial draft for Alarm support
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_oam_server.cpp,v 1.3.6.1.4.1 2013/02/27 08:49:07 jvikram Exp $"

#include <stdlib.h>
#include <string.h>
//Warning Fix - deprecated conversion from string constant to "char*"
#include <string>
#include <its.h>
#include <its_alarm.h>
#include <its_timers.h>
#include <its_assertion.h>
#include <its_thread_pool.h>
#include <its_ip_trans.h>

#include <dia_oam_server.h>

#define OAM_ALARM_SRC     0x01

static int WriteEvent(ITS_HANDLE h, ITS_EVENT *ev);

//Warning fix - deprecated conversion from string constant to char*
//static char* sync_data = "ISS7SSI";
static std::string sync_data = "ISS7SSI";
static ITS_INT   sd_len = 7;

static ITS_HANDLE servT;

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
static void
AlarmSendToClient(ITS_OCTET *bytes, ITS_UINT len)
{
   ITS_EVENT ev;

    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)servT;

    ITS_EVENT_INIT(&ev, OAM_ALARM_SRC, (ITS_USHORT)len);
    memcpy(ev.data, bytes, len);

    /* Send Event to Client */
    if (ft && SOCKTRAN_IS_VALID(ft))
    {
         if (WriteEvent(servT, &ev) != ITS_SUCCESS)
         {
             printf("Transport Write Event Failure File: %s Line %d\n",
                     __FILE__,__LINE__);
         }

         ITS_EVENT_TERM(&ev);
    }

   ITS_EVENT_TERM(&ev);
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
static void
AlarmHandler(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    /* This Callback will be invoked for all alarms received.
       Create an event from the alarm received and send it
       over Socket to the Alert Console Client which takes care
       of displaying it appropriately.
    */

    ITS_EVENT *event = (ITS_EVENT *)callData;
    AlarmSendToClient(event->data, event->len);

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
extern "C"  int 
OAMServerPreInit(TPOOL_THREAD *thr)
{
    printf("In OAM Server PreInitFile: %s Line %d\n", __FILE__,__LINE__);

    return (ITS_SUCCESS);
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
extern "C"  int 
OAMServerPostInit(TPOOL_THREAD *thr, ITS_HANDLE hdl)
{
    printf("OAM Server PostInit File: %s Line %d\n", __FILE__,__LINE__);

    if (hdl == NULL)
    {
        return (ITS_EINITFAIL);
    }

    servT = hdl;

    return (ITS_SUCCESS);
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
extern "C"  int 
OAMServerPostNext(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    printf("OAM Server PostNextEvent  File: %s Line %d\n", __FILE__,__LINE__);

    /* Nothing to Do, We aren't expecting anything from the client */

    return (!ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the ALARM subsystem to a ready state.
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
static int
ClassInitialize(ITS_Class objClass)
{
    /* register Alarm Callback */
    if (CALLBACK_AddCallback(ALARM_Callbacks, (ITS_CALLBACK)AlarmHandler, NULL) != ITS_SUCCESS)
    {
        printf("Unable to Add Alarm Callbacks File: %s Line %d\n",
                  __FILE__,__LINE__);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the ALARM subystem.
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
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    /* Remove Alarm callback */
    CALLBACK_RemCallback(ALARM_Callbacks, (ITS_CALLBACK)AlarmHandler, NULL);
}

static int
WriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;
    ITS_USHORT tmp;
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)h;

    ITS_C_REQUIRE(h != NULL);
    ITS_C_REQUIRE(ev != NULL);

    /* synchronize the stream */
    //Warning fix - deprecated conversion from string constant to char*
    ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char*)sync_data.c_str(), sd_len);

    if (ret != sd_len)
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the source */
    tmp = SOCK_HToNS(ev->src);

    ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the length */
    tmp = SOCK_HToNS(ev->len);

    ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char *)&tmp, sizeof(ITS_USHORT));

    if (ret != sizeof(ITS_USHORT))
    {
        return (ITS_ESENDFAIL);
    }

    /* Write the data */
    if (ev->len)
    {
        ret = SOCK_Write(SOCKTRAN_SOURCE(ft), (char *)ev->data, ev->len);

        if (ret != (int)ev->len)
        {
            return (ITS_ESENDFAIL);
        }
    }

    TRANSPORT_NUM_SENT(ft)++;

    return (ITS_SUCCESS);
}


/*
 * the class record
 */
static ITS_ClassRec itsDIAOAMServer_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        OAMSERVER_CLASS_NAME,           /* class name */
        (ITS_ClassInitProc)ClassInitialize,  /* class init */
        (ITS_ClassPartDestroyProc)ClassTerminate, /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
};

ITS_Class itsDIAOAMServer_Class = (ITS_Class)&itsDIAOAMServer_ClassRec;
