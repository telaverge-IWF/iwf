/*********************************-*HPP*-************************************
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
 * LOG: $Log: dia_connector.h,v $
 * LOG: Revision 3.3.20.1.6.4.18.3  2015/02/17 06:22:44  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.3.20.1.6.4.18.2  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.3.20.1.6.4  2013/04/07 03:54:21  cprem
 * LOG: Changes made to fix HA bugs. Review Request 784
 * LOG:
 * LOG: Revision 3.3.20.1.6.3  2013/03/22 06:33:33  pramana
 * LOG: Changes for HA feature
 * LOG:
 * LOG: Revision 3.3.20.1.6.2  2013/03/07 05:50:32  ncshivakumar
 * LOG: transport type TCP for DRE.
 * LOG:
 * LOG: Revision 3.3.20.1.6.1  2013/03/05 06:52:02  ncshivakumar
 * LOG: Multihome changes
 * LOG:
 * LOG: Revision 3.3.20.1  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.3.44.1  2012/11/14 08:27:59  millayaraja
 * LOG: modified to accomdate Peer stack stats
 * LOG:
 * LOG: Revision 3.3  2009/02/04 05:45:14  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG: 1. One thread for accepting connections and other for initiate connections
 * LOG: 2. One thread to Read from I-Connections and other for R-Connections
 * LOG:
 * LOG: Revision 3.2  2008/11/26 12:04:30  nvijikumar
 * LOG: Local IP binding for Client Sockets
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2006/12/11 13:52:01  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.4  2006/11/30 18:52:05  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG:
 * LOG: Revision 2.3  2006/11/25 04:00:12  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_connector.h,v 3.3.20.1.6.4.18.3 2015/02/17 06:22:44 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_connector.h,v 3.3.20.1.6.4.18.3 2015/02/17 06:22:44 jkchaitanya Exp $"

#ifndef DIA_CONNECTOR_H
#define DIA_CONNECTOR_H

#include <dia_ip_trans.h>
#include <dia_stack_statistics.h>

#if defined TRY_AGAIN
#undef TRY_AGAIN
#endif
#define MAX_IP_ADDRS 5   //1 primary and 4 secondary.

class DiaConnector: public DIAThread
{
public:
    DiaConnector(int type,bool activate = true)
        :DIAThread(0, true, this, DETACHED)
    { 
        m_bDeActivated = !activate;
        _doExit = ITS_FALSE;
        _type   = type;
        noIPV4IPs = 0;
        noIPV6IPs = 0;
        TCPIPV4addrs = NULL;
        TCPIPV6addrs = NULL;
    }

    ~DiaConnector() {}

    its::Socket* GetSocket()
    {
        if (trHandle != NULL)
        {
            return trHandle->GetSocket();
        }
        return NULL;
    }
    bool SetSocketFd()
    {
        if (trHandle != NULL)
        {
            return ((DiaPeerSockTransport *)trHandle)->SetSocketFd();
        }
        return false;
    }

    ITS_INT GetType()
    {
        return trHandle->GetType();
    }
    PEER_ENTRY* GetPeer()
    {
        if (trHandle != NULL)
        {
            return trHandle->GetPeer();
        }
        return NULL;
    }

    ITS_USHORT GetInstance()
    {
        if (trHandle != NULL)
        {
            return trHandle->GetInstance();
        }
        return 0;
    }

    void SetExit()
    {
        if (_doExit)
            return;
        else
            _doExit = ITS_TRUE;
    }

    int Bind(bool isIPv6);
    int Connect();
    int EstablishCommunication();
    void InitConnections();
    void Execute(void *arg);
    void CopyIpAddresses();

    void DeActivate()
    {
        m_bDeActivated = true;
    }

    void Activate()
    {
        m_bDeActivated = false;
    }

private:
    DiaSocketTransport *trHandle;
    ITS_BOOLEAN  _doExit;
    int          _type;
    const char *ipv6AddrsToUseInBind[MAX_IP_ADDRS];
    unsigned int noIPV6IPs;
    const char *ipv4AddrsToUseInBind[MAX_IP_ADDRS];
    unsigned int noIPV4IPs;
    const char* TCPIPV4addrs;
    const char* TCPIPV6addrs;

    bool m_bDeActivated;
};

class DiaConnectorReader: public DIAThread, public DiaSocketRead, public DiaStackPeerStats
{
public:
    DiaConnectorReader()
        :DIAThread(0, true, this, DETACHED)
    {
        _doExit = ITS_FALSE;
        trHandle = NULL;
    }

    ~DiaConnectorReader() {}

    void markDown()
    {
        if (trHandle != NULL)
        {
            trHandle->markDown();
        }
    }
    void SetExit()
    {
        if (_doExit)
            return;
        else
            _doExit = ITS_TRUE;
    }
    int HandleMessage(ITS_EVENT *event);
    int HandleSocketError(PEER_ENTRY *peer);
    int Read(ITS_EVENT *event);
    void Execute(void *arg);

private:
    ITS_BOOLEAN  _doExit;
};

#endif


