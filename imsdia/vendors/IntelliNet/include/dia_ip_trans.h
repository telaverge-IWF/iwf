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
 * LOG: $Log: dia_ip_trans.h,v $
 * LOG: Revision 3.19.4.1.4.3.2.1.2.3.14.5  2020/02/14 11:36:11  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1.2.3.14.4  2015/05/11 06:39:42  jkchaitanya
 * LOG: changes ported from stack branch
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1.2.3.14.3  2015/02/17 06:22:44  jkchaitanya
 * LOG: changes for peer down crash ported from stack branch for bugs 5507, 6067
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1.2.3.14.2  2014/12/17 05:19:08  jkchaitanya
 * LOG: changes to revert back the server down crash changes
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1.2.3  2013/12/11 09:59:05  vsarath
 * LOG: Fix for issues 1639, 2143
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1.2.2  2013/10/26 07:42:21  ncshivakumar
 * LOG: RFC 6733 changes
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1.2.1  2013/09/10 08:36:39  ncshivakumar
 * LOG: RFC6733 Changes
 * LOG:
 * LOG: Revision 3.19.4.1.4.3.2.1  2013/07/01 06:53:26  ncshivakumar
 * LOG: CHanges for fixing crash.Refer review board http://172.16.1.100/reviewboard/r/1016/
 * LOG:
 * LOG: Revision 3.19.4.1.4.3  2013/03/15 10:25:23  mallikarjun
 * LOG: BUG-1194-Chages
 * LOG:
 * LOG: Revision 3.19.4.1.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.19.4.1.4.1  2013/02/01 11:34:15  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.19.4.2  2013/01/18 04:48:00  jsarvesh
 * LOG: cppcheck changes
 * LOG:
 * LOG: Revision 3.19.4.1  2012/12/21 06:05:54  jsarvesh
 * LOG: fix for bug 732 invalid read
 * LOG:
 * LOG: Revision 3.19  2011/04/08 08:16:45  nvijikumar
 * LOG: Fix for Helpdesk Id 2465 (Issue when unreachable IP is configured)
 * LOG:
 * LOG: Revision 3.18  2011/01/03 14:07:20  nvijikumar
 * LOG: Changes for MVL
 * LOG:
 * LOG: Revision 3.17  2010/09/20 05:09:59  nvijikumar
 * LOG: trIndx -1 is invalid for unsigned short
 * LOG:
 * LOG: Revision 3.16  2010/06/30 04:07:06  nvijikumar
 * LOG: TLS .h file name changed
 * LOG:
 * LOG: Revision 3.15  2009/07/24 09:17:28  rajeshak
 * LOG: Reverting back the split SessionTable changes (missing)
 * LOG:
 * LOG: Revision 3.14  2009/06/29 14:50:19  rajeshak
 * LOG: Write Mutex changes.
 * LOG:
 * LOG: Revision 3.13  2009/04/17 09:33:25  rajeshak
 * LOG: Fix for Issue:1818. (Core dump due to multiple thread accessing the
 * LOG: trTable peerEntry List)
 * LOG: Provided a lock-unlock function.
 * LOG:
 * LOG: Revision 3.12  2009/02/19 08:30:34  rajeshak
 * LOG: IssueID: 1574 & 1637
 * LOG: FeatureID:none
 * LOG: Description: Coredump on getting DPR on SCTP transport.
 * LOG: Clearing the transport instance from the trTable after socket delete.
 * LOG:
 * LOG: Revision 3.11  2009/02/05 05:44:54  rajeshak
 * LOG: Returning proper values
 * LOG:
 * LOG: Revision 3.10  2009/02/04 05:41:22  nvijikumar
 * LOG: Changes for 64 Peer support with fixed number of threads
 * LOG:
 * LOG: Revision 3.9  2009/01/03 06:51:38  nvijikumar
 * LOG: 1. Introduced new array to maintain the transports Slots
 * LOG: 2. Used slots should not be allocated for newly added peers
 * LOG:
 * LOG: Revision 3.8  2008/12/11 11:10:54  nvijikumar
 * LOG: Mutex not required to get entry from trInstList
 * LOG:
 * LOG: Revision 3.7  2008/10/28 12:05:11  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.2.2.1  2008/10/12 11:52:23  nvijikumar
 * LOG: Changes made for Bridgewater to reduce the Context switches.
 * LOG:
 * LOG: Revision 3.6  2008/08/29 13:07:51  vnarang
 * LOG: Creating DETACHED Threads for DiaSocketTransport
 * LOG:
 * LOG: Revision 3.5  2008/07/31 06:20:51  sureshj
 * LOG: Code is Put under Tls Enabled Tag
 * LOG:
 * LOG: Revision 3.4  2008/07/09 14:03:24  vnarang
 * LOG: Using New Tls Class API integrated for GNU TLS & OPEN SSL & Adding Copilation option
 * LOG:
 * LOG: Revision 3.3  2008/06/13 11:18:47  hbhatnagar
 * LOG: Made changes for the TLS implementation and also related xml parsing.
 * LOG:
 * LOG: Revision 3.2  2008/04/22 12:51:25  nanaparthi
 * LOG: Fix for Issue #856
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.15  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.14.4.1  2008/01/07 18:16:19  hbhatnagar
 * LOG: Changes made to provide fix for the Bridgewater ticket 1836. Subsequent
 * LOG: issues 20, 22 and 23 are also fixed by this. A detailed summary is given:
 * LOG:
 * LOG: After a detailed discussion with Yogesh and Rachel it was decided
 * LOG: to use Blocking version of Read in Diameter ReadEvent() API
 * LOG: (as it was earlier). Instead send a SIGUSR1 signal to particular thread which is
 * LOG: on Blocking read so that read is interrupted and we can shutdown the
 * LOG: sockets. This resolution is preferred over the NonBlockingRead() for
 * LOG: performance reasons as  NBR involves polling. The branch tag B-IDIA-0210-00
 * LOG: ( cut for both IntelliSS7 and imsdia) created to provide the interim patch
 * LOG: to Bridgewater for the ticket 1836 remains unchanged ( discussed with
 * LOG: Rachel) and NonBlockingRead() will be used in it.
 * LOG:
 * LOG: Hence a part of this solution for both linux and solaris moved the
 * LOG: pthread_kill() API from InitializeFailover() API to SetExit().
 * LOG:
 * LOG: Revision 2.14  2006/12/29 06:54:59  nanaparthi
 * LOG: Added log to these files, forgot it in the previous commit
 * LOG:
 * LOG: Revision 2.13  2006/12/29 06:42:27  nanaparthi
 * LOG: SCTP Multihoming related changes (baseline code base)
 * LOG:
 * LOG: Revision 2.12  2006/12/29 06:26:07  nanaparthi
 * LOG: Fix for crash if Mesg sent from peer in R-OPEN state
 * LOG:
 * LOG: Revision 2.11  2006/12/17 03:35:58  tpanda
 * LOG: Fix for bug# 5067 and default route handling
 * LOG:
 * LOG: Revision 2.10  2006/12/14 13:43:12  tpanda
 * LOG: Fix for sending STR failing from peer to backup(bug#5053)
 * LOG:
 * LOG: Revision 2.9  2006/12/14 06:36:46  tpanda
 * LOG: Fix for crash while bringing up server with SCTP tranport
 * LOG:
 * LOG: Revision 2.8  2006/12/11 13:52:01  tpanda
 * LOG: REDUNDANCY_SLOT_CHANGES are removed and code seems to be stable
 * LOG:
 * LOG: Revision 2.7  2006/12/10 13:43:48  tpanda
 * LOG: Redundancy Bug Fixes and enhancements--Transport Order Fix
 * LOG:
 * LOG: Revision 2.6  2006/11/30 18:52:05  tpanda
 * LOG: Redundancy slot changes backed out. TODO: Refer (REDUNDANCY_SLOT_CHANGES) defines
 * LOG:
 * LOG: Revision 2.5  2006/11/25 04:00:12  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 2.4  2006/11/06 05:14:01  nvijikumar
 * LOG: SCTP support for 64bit solaris compilation.
 * LOG:
 * LOG: Revision 2.3  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.2  2006/09/26 06:11:10  nvijikumar
 * LOG: SCTP Changes (Viji, Naresh)
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_ip_trans.h,v 3.19.4.1.4.3.2.1.2.3.14.5 2020/02/14 11:36:11 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_ip_trans.h,v 3.19.4.1.4.3.2.1.2.3.14.5 2020/02/14 11:36:11 jkchaitanya Exp $"

#ifndef DIA_IP_TRANS_H
#define DIA_IP_TRANS_H

#if defined(linux)
#include <its_lksctp_sockets.h>
#elif defined(solaris) || defined(solaris64)
#include <its_sksctp_sockets.h>
#endif

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_msghandler.h>
#include <dia_peer_fsm.h>
#include <dia_peer_table.h>
#include <dia_timer_handler.h>
#ifdef TLS_ENABLED
#include <its_tls_factory.h>
#endif

#if defined(linux) && !defined(USE_SELECT)
#include<sys/epoll.h>
#endif

#include <sys/socket.h>
#include <errno.h>

#if defined TRY_AGAIN
#undef TRY_AGAIN
#endif

#define IP_ADDRESS_LEN 64
#define SCTP_PPID_FOR_CLEAR_TEXT         46
#define SCTP_PPID_FOR_ENCRYPTED_DATA     47
#define TRANSPORT_DEL_DELAY_TIMER_VALUE   1

class DiaSocketTransportContainer;
extern its::ITS_Mutex __TIGate;
extern DiaSocketTransportContainer trTable;
class DiaEpollSockContainer;

/**
 * Declaration of the client and server certificates.
 */
#ifdef TLS_ENABLED
extern Certificate *clientCertificate;
extern Certificate *serverCertificate; 
#endif

typedef enum
{
    DIA_TRANS_CONNECTOR = 0,
    DIA_TRANS_ACCEPTOR
}DIA_TRANS_SPEC;

/*.Interface: DiaSocketTransport 
 *****************************************************************************
 *  Interface:
 *      DiaSocketTransport Class
 *      
 *  Purpose:
 *      DiaSocketTransport contains transport/socket info for perticular
 *      Peer
 *****************************************************************************/
class DiaSocketTransport
{
public:
    DiaSocketTransport(ITS_INT type, ITS_USHORT instance)
    {
        _type = type;
        _socket = NULL;
#ifdef TLS_ENABLED
        _tlsSess = NULL; 
#endif
        _peer = NULL;
        _instance = InsertInstance(instance);
        _ifMarkedDown = false;
	_unsentData = NULL;
	_unsentDataLen = 0;
	_isSockCongested = false;
 
	if (_instance == 0 
           && type != ITS_DIA_SERVER_SOCK_TRANS
           && type != ITS_DIA_SCTP_SERVER_SOCK_TRANS)
        {
            throw;
        }
    }
    virtual ~DiaSocketTransport()
    {
        //SetExit();
        if (_socket)
        {
            delete _socket;
            _socket = NULL;
        }
#ifdef TLS_ENABLED
        
        if (_tlsSess)
        {
            delete _tlsSess;
            _tlsSess = NULL;
        }
#endif
        ClearTrInstance();

    }
    void SetExit()
    {
        markDown();

        if (_socket && _socket->GetSocketInfo())
        {
            if(_peer && DIA_PE_STATE(_peer) == PEER_ST_WAIT_CONN_ACK)
            {
                /* It is possible that thread blocked in connect()
                 * for unreachable IP */
                return;
            }
            if(shutdown(_socketFd,SHUT_RD) < 0)
            {
                DT_WRN(("shutdown(%d,SHUT_RD) return errno = %d",_socketFd, errno));
            }

        }
    }

    ITS_USHORT GetInstance()
    {
        return _instance;
    }

    ITS_INT GetType() 
    {
        return _type;
    }

    its::Socket* GetSocket()
    {
        return _socket;
    }

    /**
     * Added API to get the TLS session
     * object.
     */
#ifdef TLS_ENABLED

    TlsSession *GetTlsSession()
    {
        return _tlsSess;
    }

    /**
     * Added API to set the TLS session
     * object.
     */
    void SetTlsSession(TlsSession *tlsSess)
    {
        _tlsSess = tlsSess;
    }

#endif
    void SetPeer(PEER_ENTRY*& peer)
    {
       _peer = peer;
    }

    PEER_ENTRY*& GetPeer()
    {
        return _peer;
    }

    void ResetLastUpdate()
    {
        _lastUpdate = 0;
    }

    ITS_UINT GetLastUpdate()
    {
        return _lastUpdate;
    }

    void IncrementLastUpdate()
    {
        _lastUpdate++;
    }

    ITS_USHORT AllocateInstance();

    //inserts instance to global transport table
    ITS_USHORT InsertInstance(ITS_USHORT instance);
    void ClearTrInstance();


    ITS_UINT Initialize(const char* serverHostName, ITS_USHORT portNo);
    ITS_UINT Initialize(const char* serverHostName, ITS_USHORT portNo,
                     const char* multiHomeipaddrs[], ITS_USHORT noIPs);   // SCTP MultiHoming

    virtual void Shutdown();
    virtual void Shutdown(DiaEpollSockContainer*);
    virtual int ReadEvent(ITS_EVENT *cEvt);
    virtual int WriteData(ITS_OCTET *data, ITS_UINT len);
    virtual int FlushData(ITS_BOOLEAN &isPeerToBeDisconnected, ITS_BOOLEAN delUnsentData = ITS_FALSE);

    virtual int HandleMessage(ITS_EVENT *event)
    {
        return (ITS_SUCCESS);
    };

    void GetSockInfo(ITS_SocketInfo *info);
    bool CheckIfMarkedDown() { return _ifMarkedDown;}
    void markDown(){_ifMarkedDown = true;}
    bool IsSocketCongested()
    {
       return _isSockCongested;
    }
    void SetSockCongestionFlag(bool isCongested)
    {
       _isSockCongested = isCongested;
    }
    void ResetSockFlushLastUpdate()
    {
       _sockFlushLastUpdate = 0;
    }
    ITS_UINT GetSockFlushLastUpdate()
    {
       return _sockFlushLastUpdate;
    }
    void IncrementSockFlushLastUpdate()
    {
       _sockFlushLastUpdate++;
    }
    void StartTrHandleDeleteDelayTimer();
    void SetStartedDelayTimer(){_isDelayTimerStarted = true;}
    bool IsDelayTimerStarted(){return _isDelayTimerStarted;};

public:
    ITS_USHORT   _instance;
    ITS_BOOLEAN  _ifMarkedDown;
    int          _socketFd;
    int          _fdIndex;
    const char*  _hostName;
    ITS_USHORT   _portNo;
    its::Socket* _socket;
    const char** _multiHomeipaddrs;   // SCTP MultiHoming
    ITS_USHORT   _noIPs;
    ITS_BOOLEAN    _isDelayTimerStarted;

protected:
    ITS_INT        _type;
    PEER_ENTRY*    _peer;
    ITS_UINT       _lastUpdate;
    DIA_TRANS_SPEC _transSpec;
#ifdef TLS_ENABLED
    TlsSession*  _tlsSess; //Added pointer for TLS session
#endif
private:
     ITS_OCTET      *_unsentData;
     ITS_UINT       _unsentDataLen;
     ITS_UINT       _sockFlushLastUpdate;
     ITS_BOOLEAN    _isSockCongested;
};

/*.Interface: DiaSocketRead
 *****************************************************************************
 *  Interface:
 *      DiaSocketRead Class
 *      
 *  Purpose:
 *      DiaSocketRead provided wraper functions to acces DiaSocketTransport 
 *      instance
 *****************************************************************************/
class DiaSocketRead
{
public:
    DiaSocketRead()
        :trHandle(NULL){}

    ~DiaSocketRead(){}

    ITS_USHORT GetInstance()
    {
        if (trHandle != NULL)
        {
            return trHandle->GetInstance();
        }
        return 0;
    }

    int ReadEvent(ITS_EVENT *cEvt)
    {
        if (trHandle != NULL)
        {
            return trHandle->ReadEvent(cEvt);
        }
        return !ITS_SUCCESS;
    }
    void ResetLastUpdate()
    {
        if (trHandle != NULL)
        {
            trHandle->ResetLastUpdate();
        }
    }
    void Shutdown()
    {
        if (trHandle != NULL)
        {
            trHandle->Shutdown();
        }
    }
    void Shutdown(DiaEpollSockContainer* epollTable)
    {
        if (trHandle != NULL)
        {
            trHandle->Shutdown(epollTable);
        }
    }
    PEER_ENTRY* GetPeer()
    {
        if (trHandle != NULL)
        {
            return trHandle->GetPeer();
        }
        return NULL;
    }
    void GetSockInfo(ITS_SocketInfo *info)
    {
        if (trHandle != NULL)
        {
            trHandle->GetSockInfo(info);
        }
    }
    void SetPeer(PEER_ENTRY*& peer)
    {
        if (trHandle != NULL)
        {
            trHandle->SetPeer(peer);
        }
    }
    ITS_INT GetType()
    {
        if (trHandle != NULL)
        {
            return trHandle->GetType();
        }

        //Warning Fix - control reaches end of non-void function
        return (!ITS_SUCCESS);
    }
protected:
    DiaSocketTransport *trHandle;
};

/*.Interface: DiaPeerSockTransport
 *****************************************************************************
 *  Interface:
 *      DiaPeerSockTransport Class
 *     
 *  Purpose:
 *      It is derived from DiaSocketTransport and it is for each Peer
 *****************************************************************************/
class DiaPeerSockTransport: public DiaSocketTransport
{
public: 
    DiaPeerSockTransport(int type, ITS_USHORT instance, 
                         DIA_TRANS_SPEC transSpec = DIA_TRANS_CONNECTOR)
       : DiaSocketTransport(type, instance+transSpec)
    {
        if (MUTEX_CreateMutex(&_rMutex, 0) != ITS_SUCCESS)
        {
            throw its::Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        }

        if (MUTEX_CreateMutex(&_wMutex, 0) != ITS_SUCCESS)
        {
            throw its::Error(ITS_EBADMUTEX, __FILE__, __LINE__);
        }

        if ((_transSpec = transSpec) == DIA_TRANS_ACCEPTOR)
        {
            _awaitFirstCER = ITS_TRUE; 
        }
        else
        {
            _awaitFirstCER = (!ITS_TRUE); 
        }
        _isTLSHandShakeDone=false;
    }

    ~DiaPeerSockTransport() 
    {
        MUTEX_DeleteMutex(&_wMutex);
    }

    bool SetConnection(its::Socket *connection)
    {
        ITS_SocketInfo *info = NULL;

        if (connection != NULL)
        {
            _socket = connection;

            info = connection->GetSocketInfo();

            if (info != NULL)
            {
                _socketFd = info->socket;
            }
            else
            {
                DT_ERR(("DiaPeerSockTransport::SetConnection failed"));
                return false;
            }
        }
        else
        {
            DT_ERR(("DiaPeerSockTransport::SetConnection failed"));
            return false;
        }
        return true;
    }

    bool SetSocketFd()
    {
        ITS_SocketInfo *info = NULL;
 
        if (_socket != NULL)
        {
            info = _socket->GetSocketInfo();

            if (info != NULL)
            {
                _socketFd = info->socket;
            }
            else
            {
                DT_ERR(("DiaPeerSockTransport::SetSocketFd failed"));
                return false;
            }
        }
        else
        {
            DT_ERR(("DiaPeerSockTransport::SetSocketFd failed"));
            return false;
        }
        return true;
    }

    ITS_BOOLEAN IsAwaitFirstCER()
    {
        return _awaitFirstCER;
    }
    ITS_BOOLEAN IsTLSHandShakeComplete()
    {
        return _isTLSHandShakeDone;
    }
    void UnsetFirstCERFlag()
    {
        _awaitFirstCER = ITS_FALSE;
    }
    void SetTLSHandShakeComplete()
    {
        _isTLSHandShakeDone = true;
    }

    ITS_MUTEX* getWriteLock()
    {
        return &_wMutex;
    }

    ITS_MUTEX* getReadLock()
    {
        return &_rMutex;
    }

private:
    ITS_MUTEX      _rMutex;
    ITS_MUTEX      _wMutex;
    ITS_BOOLEAN    _awaitFirstCER;
    ITS_BOOLEAN _isTLSHandShakeDone;
};

/*.Interface: DiaSocketTransportContainer
 *****************************************************************************
 *  Interface:
 *      DiaSocketTransportContainer Class
 *
 *  Purpose:
 *      Maintains List of all peer transports
 *****************************************************************************/
class DiaSocketTransportContainer
{
public:
      DiaSocketTransportContainer()
      {
      //Buffer is accessed out of bounds: trInstList
      //Fixed by replacing "<=" with "<"
         for(int i =0; i< MAX_LOCAL_TRANSPORTS; ++i)
         {
            trInstList[i] = NULL;
         }
         for(int i =0; i<MAX_PEER_CONNS; i++)
         {
             slotsList[i]=0;
         }
         lock = new its::ITS_Mutex(0);
         peerSlotLock = new its::ITS_Mutex(0);
      }

      ~DiaSocketTransportContainer()
      {
         delete lock;
         lock = NULL;
         delete peerSlotLock;
         peerSlotLock = NULL;
      }

      void SetToNULL(ITS_USHORT inst)
      {
          trInstList[inst] = NULL;
      }
      DiaSocketTransport* getAt(ITS_USHORT inst)
      {
          //lock->Acquire();
          //Fixing Out-of-bounds read
          if (inst < MAX_LOCAL_TRANSPORTS)
          {
             //lock->Release();
             return trInstList[inst];
          }
          //lock->Release();
          return NULL; //return NULL
      }
      DiaSocketTransport* operator [](ITS_USHORT inst)
      {
          //lock->Acquire();
          //Fixing Out-of-bounds read
          if (inst < MAX_LOCAL_TRANSPORTS)
          {
             DiaSocketTransport* tr = trInstList[inst];
             if (tr == NULL || tr->CheckIfMarkedDown())
             {
                //check if accepting connection slot
                if ((inst % 4) == 1)
                {
                   tr = trInstList[inst + 1];
                }
                else if ((inst % 4) == 2)
                {
                   //check if connecting connection slot
                   tr = trInstList[inst - 1];
                }
                //if still NULL, then try to get Alternate peer transport Inst
                //very much essential for redundancy
                if (tr == NULL || tr->CheckIfMarkedDown())
                {
                   ITS_USHORT aInst;
                   aInst = PeerTable::GetPeerTable()->GetAltTrInst(inst);
                   if (aInst)
                   {
                      tr = trInstList[aInst];
                      if (tr && tr->CheckIfMarkedDown())
                      {
                         /* if alternate transport is marked down, return NULL*/
                         tr = NULL;
                      }
                   }
                }
             }
            // lock->Release();
             return tr;
          }
         // lock->Release();
          return NULL; //return NULL
      }

      int swap(ITS_USHORT nInst, ITS_USHORT oInst)
      {
          lock->Acquire();
          /* check if the associated connecting transport is in use
           * or if marked down 
           */
          if((nInst-1) && trInstList[nInst-1] &&
            trInstList[nInst-1]->CheckIfMarkedDown())
          {
             trInstList[oInst]->SetExit(); 
             trInstList[oInst]=NULL;
             lock->Release();
             return (!ITS_SUCCESS);
          }
          DiaSocketTransport* tr = trInstList[nInst];
          trInstList[nInst] = trInstList[oInst];
          trInstList[oInst] = tr;
          if (tr) tr->_instance = oInst;
          lock->Release();
          return (ITS_SUCCESS);
      }

      void addAt(ITS_USHORT inst, DiaSocketTransport* entry)
      {
          lock->Acquire();
          //Fixing Out-of-bounds read
          if (inst < MAX_LOCAL_TRANSPORTS)
          {
             if (trInstList[inst] || entry)
             {
                trInstList[inst] = entry;
             }
          }
          lock->Release();
      }

      ITS_INT GetNextTrIndex()
      {
          bool found = false;
          int i;
          for (i=0;i<MAX_PEER_CONNS;i++)
          {
              if(slotsList[i] == NULL)
              {
                  found = true;
                  break;
              }
          }
          if (found)
          {
              /* Return trIndex for next available Slot */
              return ((i*4)+1);
          }
          return 0;
      }

      bool SetTrSlot(ITS_USHORT trIndex, PEER_ENTRY *& entry)
      {
          peerSlotLock->Acquire();
          unsigned int indx = 0;
          if (trIndex <= 0 || entry == NULL)
          {
              peerSlotLock->Release();
              return false;
          }

          indx = trIndex/4;

          if (slotsList[indx] != 0)
          {
              peerSlotLock->Release();
              return false;
          }

          slotsList[indx] = entry;
          peerSlotLock->Release();
          return true;
      }
      bool UnSetTrSlot(ITS_USHORT trIndex)
      {
          peerSlotLock->Acquire();
          unsigned int indx = 0;
          if (trIndex <= 0)
          {
              peerSlotLock->Release();
              return false;
          }

          indx = trIndex/4;

          if (slotsList[indx] == NULL)
          {
              peerSlotLock->Release();
              return false;
          }

          slotsList[indx] = NULL;
          peerSlotLock->Release();
          return true;
      } 
      PEER_ENTRY *& GetPeer(int indx)
      {
          return slotsList[indx];
      } 

      void LockPeerSlot()
      {
          peerSlotLock->Acquire();
      }
      void UnlockPeerSlot()
      {
          peerSlotLock->Release();
      }

private:
     its::ITS_Mutex *lock;
     its::ITS_Mutex *peerSlotLock;
     DiaSocketTransport* trInstList[MAX_LOCAL_TRANSPORTS]; 
     PEER_ENTRY *slotsList[MAX_PEER_CONNS];
};

#if !defined(linux) || defined(USE_SELECT)

/*.Interface: DiaSelectSockContainer
 *****************************************************************************
 *  Interface:
 *      DiaSelectSockContainer Class
 *
 *  Purpose:
 *      Maintains List of all peer sockets for Select operation
 *****************************************************************************/
class DiaSelectSockContainer
{
public:
    DiaSelectSockContainer()
        :lastFd(0),
        fdCount(0)
    {
        for(int i=0;i<MAX_PEER_CONNS;i++)
        {
            desc[i] = NULL;
        }
    }
    ~DiaSelectSockContainer(){}

    int SelectSock()
    {
        tv.tv_sec = 1; 
        memcpy(&selectfds, &readfds, sizeof(readfds));
        return select(lastFd+1, &selectfds, NULL, NULL, &tv);
    }
    int SetSelectSock (DiaSocketTransport *tr)
    {
        int tIndex = 0;
        if (tr != NULL)
        {
            /* Store in desc array */
            while ((desc[tIndex] != NULL) && (tIndex < (fdCount-1)))
            {
                tIndex++;
            }
            if ((desc[tIndex] == NULL) && tIndex < fdCount)
            {
                tr->_fdIndex = tIndex;
                desc[tIndex] = tr;
            }
            else
            {
                if (fdCount < MAX_PEER_CONNS)
                {
                    tr->_fdIndex = fdCount;
                    desc[fdCount++] = tr;
                }
                else
                {
                    DT_ERR(("SetSelectSock::Max connections reached"));
                    return !ITS_SUCCESS;
                }
            }

            /* Set socket for read */
            FD_SET(tr->_socketFd, &readfds);
            lastFd = tr->_socketFd;

            return ITS_SUCCESS;
        }
    }
    void UnsetSelectSock(int fdIndex)
    {
        DiaSocketTransport *tr = NULL;
        tr = desc[fdIndex];
        if (tr != NULL)
        {
            FD_CLR(tr->_socketFd, &readfds);
            fdCount--;
        }
        else
        {
            DT_ERR(("UnsetSelectSock::Invalid tr pointer"));
        }
        desc[fdIndex] = NULL;

    }
    int IsReadable(int sockFd)
    {
        return FD_ISSET(sockFd, &selectfds);
    }
public:
    DiaSocketTransport* desc[MAX_PEER_CONNS];
    int fdCount;
private:
    struct timeval tv;
    int    lastFd;
    fd_set selectfds;
    fd_set readfds;
};
#else

/*.Interface: DiaEpollSockContainer
 *****************************************************************************
 *  Interface:
 *      DiaEpollSockContainer Class
 *
 *  Purpose:
 *      Maintains List of all peer sockets for Epoll operation 
 *****************************************************************************/
class DiaEpollSockContainer
{
public:
    DiaEpollSockContainer()
        :fdCount(0),
        epollTimeout(1000)
    {
        epollfds = epoll_create(MAX_PEER_CONNS);
        if (epollfds < 0)
        {
            DT_ERR(("DiaEpollSockContainer:: epoll_create fails"));
        } 
    }
    ~DiaEpollSockContainer(){}
    int EpollWait(struct epoll_event *events)
    {
        return epoll_wait(epollfds, events, MAX_PEER_CONNS, epollTimeout);
    }

    int DelEpollSock (DiaSocketTransport *tr)
    {
        if (tr != NULL)
        {
            if (epoll_ctl(epollfds, EPOLL_CTL_DEL, tr->_socketFd, NULL) < 0)
            {
                DT_ERR(("DelEpollSock::Failed to delete fd, errno: %d", errno));
                return !ITS_SUCCESS;
            }
            return ITS_SUCCESS;
        }
        return !ITS_SUCCESS;
    }

    int SetEpollSock (DiaSocketTransport *tr)
    {
        if (tr != NULL)
        {
            static struct epoll_event ev;
            ev.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
            ev.data.ptr = tr;
            if (epoll_ctl(epollfds, EPOLL_CTL_ADD, tr->_socketFd, &ev) < 0)
            {
                DT_ERR(("SetEpollSock::Failed to add fd"));
                return !ITS_SUCCESS;
            }
            return ITS_SUCCESS;
        }
        return !ITS_SUCCESS;
    }
private:
    int epollfds;
    int fdCount;
    int epollTimeout;
};
#endif

/* 
 *  DIA_IP_TRANS_H Ends
 */
#endif


