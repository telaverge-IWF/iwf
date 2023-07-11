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
 * LOG: $Log: dia_acceptor.h,v $
 * LOG: Revision 3.2.60.4.4.1.18.3  2015/02/17 06:22:43  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.2.60.4.4.1.18.2  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.2.60.4.4.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.2.60.4  2013/04/07 03:54:21  cprem
 * LOG: Changes made to fix HA bugs. Review Request 784
 * LOG:
 * LOG: Revision 3.2.60.3  2013/03/22 06:33:33  pramana
 * LOG: Changes for HA feature
 * LOG:
 * LOG: Revision 3.2.60.2  2013/03/15 12:59:51  mallikarjun
 * LOG: BUG-1194-Chages
 * LOG:
 * LOG: Revision 3.2.60.1  2013/02/21 11:17:29  ncshivakumar
 * LOG: modified for multitransport support
 * LOG:
 * LOG: Revision 3.2  2009/02/04 05:45:14  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG: 1. One thread for accepting connections and other for initiate connections
 * LOG: 2. One thread to Read from I-Connections and other for R-Connections
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.9  2007/02/17 07:13:55  nanaparthi
 * LOG: Fix for Follwing issue (Bug 5237)
 * LOG: * On non-redundant static setup with SCTP transport if you kill the client
 * LOG: * abnormally on peer side trace prints Exception Caught: CodecException ,
 * LOG: * Error Cause: Wrong Command Header length
 * LOG:
 * LOG: Revision 2.8  2006/12/11 13:52:01  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.7  2006/11/30 18:52:05  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG:
 * LOG: Revision 2.6  2006/11/25 04:00:12  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.5  2006/11/06 05:14:01  nvijikumar
 * LOG: SCTP support for 64bit solaris compilation.
 * LOG:
 * LOG: Revision 2.4  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.3  2006/09/26 06:11:10  nvijikumar
 * LOG: SCTP Changes (Viji, Naresh)
 * LOG:
 * LOG: Revision 2.2  2006/09/13 10:10:11  yranade
 * LOG: Don't keep dynamics array in acceptor trans. Globally maintained in trTable.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_acceptor.h,v 3.2.60.4.4.1.18.3 2015/02/17 06:22:43 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_acceptor.h,v 3.2.60.4.4.1.18.3 2015/02/17 06:22:43 jkchaitanya Exp $"

#ifndef DIA_ACCEPTOR_H
#define DIA_ACCEPTOR_H

#if defined(linux)
#include <its_lksctp_sockets.h>
#elif defined(solaris) || defined(solaris64)
#include <its_sksctp_sockets.h>
#endif

#include <dia_ip_trans.h>

#if defined TRY_AGAIN
#undef TRY_AGAIN
#endif


class DiaAcceptorReader: public DIAThread, public DiaSocketRead
{
public:
    #if !defined(linux) || defined(USE_SELECT)
    DiaAcceptorReader(ITS_BOOLEAN initiateTLSHandShake)
    : DIAThread(0, true, this, DETACHED)
    #else
    DiaAcceptorReader(DiaEpollSockContainer *acceptEpolTable,
                     ITS_BOOLEAN initiateTLSHandShake)
       : DIAThread(0, true, this, DETACHED),accEpollTbl(acceptEpolTable)
    #endif
    {
        _doExit = ITS_FALSE;
        trHandle = NULL;
        startTLSHandShakeFirst = initiateTLSHandShake;
    }

    ~DiaAcceptorReader() { }

    void SetExit()
    {
        if (_doExit)
            return;
        else
            _doExit = ITS_TRUE;
    }
    ITS_BOOLEAN IsAwaitFirstCER()
    {
        if (trHandle != NULL)
        {
            return ((DiaPeerSockTransport *)trHandle)->IsAwaitFirstCER();
        }
        return ITS_FALSE;
    }
    #ifdef TLS_ENABLED
    ITS_BOOLEAN IsTLSHandShakeComplete()
    {
        if (trHandle != NULL)
        {
            return ((DiaPeerSockTransport *)trHandle)->IsTLSHandShakeComplete();
        }
        return ITS_FALSE;
    }
    void SetTLSHandShakeComplete()
    {
        if (trHandle != NULL)
        {
            ((DiaPeerSockTransport *)trHandle)->SetTLSHandShakeComplete();
        }
    }

    #endif
    void Execute(void *arg);
    int HandleMessage(ITS_EVENT *event);
    int Read(ITS_EVENT *event);
    int HandleFirstCER(ITS_EVENT *event);
    int VerifyPeerConnectionIpAddress(PEER_ENTRY*);
    int HandleSocketError(PEER_ENTRY *peer);

private:
    ITS_BOOLEAN  _doExit;
    #if defined(linux) || !defined(USE_SELECT)
    DiaEpollSockContainer  *accEpollTbl;
    #endif
    ITS_BOOLEAN startTLSHandShakeFirst;
};

class DiaAcceptor: public DiaSocketTransport, public DIAThread
{
public:
    #if !defined(linux) || defined(USE_SELECT)
    DiaAcceptor(int type, ITS_USHORT instance=0,bool activate = true)
       : DiaSocketTransport(type, instance),
        DIAThread(0, true, this, DETACHED)
    #else 
    DiaAcceptor(int type,DiaEpollSockContainer *acceptEpolTable, ITS_USHORT instance=0,bool activate = true)
       : DiaSocketTransport(type, instance),
        DIAThread(0, true, this, DETACHED),accEpollTbl(acceptEpolTable)
    #endif
    {
         m_bDropNewConnections = !activate;
        _doExit = ITS_FALSE;
        _type   = type;
    }


    void SetExit()
    {
        DiaSocketTransport::SetExit();
        if (_doExit)
            return;
        else
            _doExit = ITS_TRUE;
    }

    void AcceptConnections();
    void Execute(void *arg);

    void DeActivate()
    {
        m_bDropNewConnections = true;
    }
    void Activate()
    {
        m_bDropNewConnections = false;
    }

private:
    int          _noDynamics;
    ITS_BOOLEAN  _doExit;
    int          _type;
    //Flag which specifies whether to Accept Connections 
    bool m_bDropNewConnections;
    #if defined(linux) || !defined(USE_SELECT)
    DiaEpollSockContainer  *accEpollTbl;
    #endif
};

#endif


