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
 * ID: $Id: dmc_trans.h,v 1.4 2010/04/29 06:42:59 nvijikumar Exp $
 *
 * LOG: $Log: dmc_trans.h,v $
 * LOG: Revision 1.4  2010/04/29 06:42:59  nvijikumar
 * LOG: Fix for compilation issue on Sun CC - version 12 [Viji]
 * LOG:
 * LOG: Revision 1.3  2009/05/11 06:43:49  nvijikumar
 * LOG: Re-connect functionality is moved to Application
 * LOG:
 * LOG: Revision 1.2  2009/04/11 05:29:38  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 1.1  2009/03/02 04:39:43  nvijikumar
 * LOG: Initial draft for MML API Support
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: dmc_trans.h,v 1.4 2010/04/29 06:42:59 nvijikumar Exp $"

#ifndef DMC_TRANS_H
#define DMC_TRANS_H

#include <its++.h>
#include <its_thread.h>
#include <its_emlist.h>
#include <its_sockets.h>

#include <dmc_common.h>

#define SOCK_CONNECT_INTERVAL 5
/*.Interface: DmcReadWriteUtils
 *  ****************************************************************************
 *  Interface:
 *      DmcReadWriteUtils Class
 *
 *  Purpose:
 *      Utility Class that provides funcs to Read/Write Opertion
 *****************************************************************************/
class DmcReadWriteUtils
{
public:
    DmcReadWriteUtils() {};
    ~DmcReadWriteUtils() {};

    /* Read/Write from/to socket */
    int ReadEvent(ITS_HANDLE hd, ITS_EVENT *ev);
    int WriteEvent(ITS_HANDLE hd, ITS_EVENT *ev);
};

/*.Interface: DmcTransport
 *****************************************************************************
 *  Interface:
 *      DmcTransport Class
 *
 *  Purpose:
 *      Handler Class that handles messages received from the sock writer
 *****************************************************************************/
class DmcTransport: public DmcReadWriteUtils, public its::Thread
{
public:
    DmcTransport()
        : its::Thread(0, (ITS_THREAD_FUNC)CallFunc, ITS_TRUE),
        isInitialized(ITS_FALSE),
        ipAddr(NULL),
        servPort(0),
        taskQue(NULL),
        sockInfo(NULL),
       _thrExit(ITS_FALSE),
       isConnUp(ITS_FALSE),
       cbFunc(NULL)
    {};

    ~DmcTransport() 
    {
        CloseConnection();
        if(ipAddr != NULL)
        {
            free(ipAddr);
        }
        EMLIST_Delete(taskQue);
    };

    int CloseConnection()
    {
        if (isConnUp == ITS_TRUE)
        {
            close (sockInfo->socket);
            sockInfo = NULL;
            isConnUp = ITS_FALSE;
            return ITS_SUCCESS;
        }
        return !ITS_SUCCESS;
    }

    int PreInitialize()
    {
        taskQue = EMLIST_Create();
        return ITS_SUCCESS;
    };

    ITS_BOOLEAN
    IsConnectionUp()
    {
        return isConnUp;
    }
    void
    RegisterCallBack(DMC_CB func)
    {
        cbFunc = func;
    }

    int Initialize(const ITS_CHAR *host, ITS_INT port);
    int Connect();
    int ReceiveEvent(DM_MSG *msg);
    int Send(DM_MSG *msg);
    int GetNextEvent(ITS_EVENT *evt);
    int PutEvent(ITS_EVENT *evt);
    void ReadThread();
    /***********************************************************************/
    /** Purpose:
    *       Start a dia application specific thread    
    *           
    ************************************************************************/
    int StartThread()
    {
        _thrExit = ITS_FALSE;
        return Enter(this);
    }
    /***********************************************************************/
    /** Purpose:
     *       Stop a dia application specific thread    
     *           
     ************************************************************************/
    int StopThread()
    {
        _thrExit = ITS_TRUE;
        return ITS_SUCCESS;
    }
    void ProcessHeartBeat();
private:
    /* ReadThread */
    static THREAD_RET_TYPE 
    CallFunc(void *arg)
    {
        DmcTransport *trans = (DmcTransport *)arg;
        if (trans != NULL)
        {
            trans->ReadThread();
        }
        THREAD_NORMAL_EXIT;
    }
private:
    ITS_BOOLEAN    isInitialized;
    ITS_CHAR       *ipAddr;
    ITS_INT        servPort;
    EMLIST_Manager *taskQue;
    ITS_SocketInfo *sockInfo;
    ITS_BOOLEAN    _thrExit;
    ITS_BOOLEAN    isConnUp;
    DMC_CB         cbFunc;
};
#endif
