/****************************************************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: dms_transports.cpp,v 1.3 2009/08/25 10:18:58 rajeshak Exp $
 *
 * LOG: $Log: dms_transports.cpp,v $
 * LOG: Revision 1.3  2009/08/25 10:18:58  rajeshak
 * LOG: Fix for Issue:2322 (IDS unable to send Heartbeat Message to DMC client)
 * LOG: Passing TrHandle properly.
 * LOG:
 * LOG: Revision 1.2  2009/04/11 05:35:24  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:44  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dms_transports.cpp,v 1.3 2009/08/25 10:18:58 rajeshak Exp $"

#include <engine++.h>

#include <iostream>
#include <string>

#include <dia_defines.h>
#include <dia_trace.h>
#include <dms_common.h>

/*
 *  Transport handle for Mgmt Server
 */
ITS_HANDLE dmsHandle  = NULL;
ITS_BOOLEAN dmsInitialize = ITS_FALSE;
ITS_USHORT workerIntance = 0;

DMS_CALLBACK hbRegister        = NULL;
DIA_CALLBACK hbDeRegister      = NULL;
DIA_CALLBACK hbResetLastUpdate = NULL;

/*.implementation:static
 *  ****************************************************************************
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
DmsPreInit(TPOOL_THREAD *thr)
{
    DIA_TRACE_DEBUG(("DmsPreInit"));

    return (ITS_SUCCESS);
}

/*.implementation:static
 *  ****************************************************************************
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
DmsPostInit(TPOOL_THREAD *thr, ITS_HANDLE hdl)
{
    SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)hdl;
    DIA_TRACE_DEBUG(("DmsPostInit"));

    if (hdl == NULL)
    {
        return (ITS_EINITFAIL);
    }

    engine::Worker* worker = (engine::Worker*)thr;
    if (dmsInitialize != ITS_TRUE)
    {
        /* Transport Initialization */
        dmsInitialize = ITS_TRUE;
    }
    else
    {
        if (dmsHandle != NULL)
        {
            DIA_TRACE_ERROR(("DmsPostInit::Multiple connections not allowed"));
            if (SOCKTRAN_IS_VALID(hdl) == ITS_TRUE)
            {
               close(SOCKTRAN_SOURCE(hdl)->socket);
            }
        }
        else
        {
            workerIntance = worker->GetInstance();
            dmsInitialize = ITS_TRUE;

            dmsHandle = hdl;
            if (hbRegister != NULL)
            {
                hbRegister(&workerIntance, hdl);
            }
        }
    }
    return (ITS_SUCCESS);
}

/*.implementation:static
 *  ****************************************************************************
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
DmsPostNext(TPOOL_THREAD *thr, ITS_EVENT *event)
{
    its::Event* ev = (its::Event*)event;
    ITS_EVENT* evt = &ev->GetEvent();
    DIA_TRACE_DEBUG(("DmsPostNext"));

    if (hbResetLastUpdate != NULL)
    {
        hbResetLastUpdate(NULL);
    }

    if (evt->src == DIA_DM_APP_SRC)
    {
        if (evt->data[0] != MSG_TYPE_HB)
        {
            if (DmsMsgHandler::ProcessMsg(evt) != ITS_SUCCESS)
            {
                DIA_TRACE_ERROR(("IdsMgmt::ProcessIdsMgmtMsg failed"));
            }
        }
        else
        {
            DIA_TRACE_DEBUG(("IdsMgmt::HeartBeat Ack Received"));
        }
    }
    else
    {
        DIA_TRACE_ERROR(("DmsPostNext::Invalid event source"));
    }

    /* Nothing to Do, We aren't expecting anything from the client */
    return (ITS_SUCCESS);
}

extern "C"  int
DmsPostTerm(TPOOL_THREAD *thr)
{
    DIA_TRACE_DEBUG(("DmsPostTerm"));

    engine::Worker* worker = (engine::Worker*)thr;

    if (workerIntance == worker->GetInstance())
    {
        if (hbDeRegister != NULL)
        {
            hbDeRegister(NULL);
        }
        workerIntance = 0;
        dmsHandle = NULL;
    }
    return (ITS_SUCCESS);
}

extern "C"  int
DmsNextEventFailed(TPOOL_THREAD *thr, ITS_INT pReturn)
{
    DIA_TRACE_DEBUG(("IDS_NextEventFailed"));
    return (!ITS_SUCCESS);
}
