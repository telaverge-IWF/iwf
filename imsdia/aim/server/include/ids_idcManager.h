 /**************************************************************************
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
 *  ID: $Id: ids_idcManager.h,v 1.4 2010/08/19 11:23:06 nvijikumar Exp $
 *
 *  LOG: $Log: ids_idcManager.h,v $
 *  LOG: Revision 1.4  2010/08/19 11:23:06  nvijikumar
 *  LOG: Porting changes from B-MOTO-IDIA-0421-00
 *  LOG: 1. New Overload implimentation changes are not being ported.
 *  LOG: 2. Force disconnect changes are not being ported.
 *  LOG:
 *  LOG: Revision 1.3  2009/02/19 05:29:06  nvijikumar
 *  LOG: New API exposed to ClientHandler for writing a event
 *  LOG:
 *  LOG: Revision 1.2  2009/01/04 06:54:29  nvijikumar
 *  LOG: Some more updates
 *  LOG:
 *  LOG: Revision 1.1  2009/01/04 06:37:14  nvijikumar
 *  LOG: Platform transport replaced with new TCP transport to handle IDC traffic
 *  LOG: To limit number of threads with multiple connections
 *  LOG:
 *  LOG:
 ****************************************************************************/
#ident "$Id: ids_idcManager.h,v 1.4 2010/08/19 11:23:06 nvijikumar Exp $"

#if !defined(_IDC_TRANS_MANAGER_H)
#define _IDC_TRANS_MANAGER_H

#include <iostream>

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_msghandler.h>

#include <ids_common.h>
#include <sys/socket.h>
#include <errno.h>

#define IDS_MAX_CONNS 64


/*.Interface: IdcReadWriteUtils
 *****************************************************************************
 *  Interface:
 *      IdcReadWriteUtils Class
 *
 *  Purpose:
 *      Utility Class that provides funcs to Read/Write Opertion
 *****************************************************************************/
class IdcReadWriteUtils
{
public:
    IdcReadWriteUtils() {};
    ~IdcReadWriteUtils() {};

    /* Read/Write from/to socket */
    int ReadEvent( ITS_INT sd, ITS_EVENT *ev);
    int WriteEvent( ITS_INT sd, ITS_EVENT *ev);
   
    int WriteEvent(IDS_TRANS_INFO* trInfo, ITS_EVENT *ev);
    int Read(int sd, char *buf, int nbytes);
    int Write(int sd, char *buf, int nbytes);
};

/*.Interface: IdcTxQueueHandler
 *****************************************************************************
 *  Interface:
 *      IdcTxQueueHandler Class
 *
 *  Purpose:
 *      Handler Class that handles messages received from the sock writer
 *****************************************************************************/
class IdcTxQueueHandler:public MessageHandler, public IdcReadWriteUtils
{
public:
    IdcTxQueueHandler ()
        :MessageHandler(ITS_NO_SRC){ }

    ~IdcTxQueueHandler(){}

    int HandleMessage(DIAThread *thr, its::Event &ev);
};


/*.Interface: IdcSockReader
 *****************************************************************************
 *  Interface:
 *      IdcSockReader Class derived from DIAThread class.
 *
 *  Purpose:
 *      Implement the SockReader Functionality using thread.
 *****************************************************************************/
class IdcSockReader: public DIAThread, public IdcReadWriteUtils
{
public:
    IdcSockReader()
        :DIAThread(0, true, this)
    {
        _doExit = ITS_FALSE;
    }
    void SetExit()
    {
        _doExit = ITS_TRUE;
    }
    int HandleReadEvent(int sockId);
    void Execute(void *arg);
protected:
    ITS_BOOLEAN  _doExit;
private:
};

/*.Interface: IdcSockAcceptor 
 *****************************************************************************
 *  Interface:
 *      IdcSockReader Class derived from DIAThread class.
 *
 *  Purpose:
 *      Implement the Socket acceptor Functionality using thread.
 *****************************************************************************/
class IdcSockAcceptor: public DIAThread
{
public:
    IdcSockAcceptor()
        :DIAThread(0, true, this)
    {
        _doExit = ITS_FALSE;
    }

    void SetExit()
    {
        _doExit = ITS_TRUE;
    }

    void Execute(void *arg);

    void SetServerSocket(int socket)
    {
        _serSocket = socket;
    }
protected:
    ITS_BOOLEAN  _doExit;
    int _serSocket;
};

/*.Interface: IdcTransManager
 *****************************************************************************
 *  Interface:
 *      IdcTransManager Class
 *
 *  Purpose:
 *      Implement the IDC transport Manager Functionality
 *****************************************************************************/
class IdcTransManager:public DIAModule
{
public:
    static IdcTransManager* GetIdcTransManager();

    ~IdcTransManager()
    {
        if (sockWrite)
        delete sockWrite;
    }

    int Stop()
    {
        if (idcSockAcceptor)
        {
            idcSockAcceptor->SetExit();
        }
        if (idcSockReader)
        {
            idcSockReader->SetExit();
        }
#if _IDS_SENDER_THR
        its::Event ev;
        ev.SetSource(IDS_TCP_SEND_MSG_QUEUE);
        its::ITS_Transport::PutEvent(IDS_TCP_SEND_MSG_QUEUE, ev);
#endif
        return (ITS_SUCCESS);
    }

    bool CreateTcpTrans();

    int StartMgr();

    /* Functions associated with threads */
    void ProcessTcpReceiver();
    void ProcessTcpConnsAcceptor();
    void ProcessTcpSender();
private:
    /* constructor */
    IdcTransManager(int numThreads);

    MessageHandler  *sockWrite;
    IdcSockAcceptor *idcSockAcceptor;
    IdcSockReader   *idcSockReader;
};
#endif // _IDC_TRANS_MANAGER_H
