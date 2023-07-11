/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: ClientInterface.cpp,v 1.4 2005/07/05 11:28:05 mmanikandan Exp $
 *
 * LOG: $Log: ClientInterface.cpp,v $
 * LOG: Revision 1.4  2005/07/05 11:28:05  mmanikandan
 * LOG: Changes for ISUP Distributed.
 * LOG:
 * LOG: Revision 1.3  2005/06/08 07:16:32  mmanikandan
 * LOG: Validation Bugs 1926, 1927, 1937
 * LOG:
 * LOG: Revision 1.2  2005/05/31 10:39:50  adutta
 * LOG: Fix for Deregister msg.
 * LOG:
 * LOG: Revision 1.1  2005/05/25 10:13:59  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/


#include <ClientInterface.h>
#include <engine++.h>


/* Populates the struct from event data*/ 
extern MULAPP_DLLAPI int
MABCL_Decode(MABCL_MESSAGE *msg, ITS_EVENT *event);

/* Populates the event data from struct*/ 
extern MULAPP_DLLAPI int
MABCL_Encode(MABCL_MESSAGE *msg, ITS_EVENT *event);

ClientHandler* ClientHandler::s_clientHandler = NULL;

ClientHandler* ClientHandler::GetClientHandler()
{
    if (s_clientHandler == NULL)
    {
        s_clientHandler = new ClientHandler;
    }

    return s_clientHandler;
}

ClientHandler::ClientHandler()
{
    rinfoMutex_ = new its::Mutex(0);
    cidmapMutex_ = new its::Mutex(0);
}

ClientHandler::~ClientHandler()
{
    std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eIter = routInfo_.end();
    
    while (bIter != eIter)
    {
        free(*bIter);
        
        bIter++;
    }

    routInfo_.clear();

    delete rinfoMutex_;
    delete cidmapMutex_;

    clIdMap_.clear();


    if (s_clientHandler)
        delete s_clientHandler;
}

int
ClientHandler::IsClientAllowed (ClientRoutingInfo* msg)
{
    int ret = ITS_SUCCESS;
    rinfoMutex_->Acquire();

    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();

    while (biter != eiter)
    {
        if (((*biter)->clientID == msg->clientID) && 
            ((*biter)->u.tcap.regType == msg->u.tcap.regType))
        {
            printf("Returning wrong client\n");
            ret = CLIENT_DUPLICATE_ENTRY;
            break;
        }

        if ((*biter)->routing_criteria == 
                                   msg->routing_criteria)
        {
            switch((*biter)->routing_criteria)
            {
            case MABCL_TCAP_RT_DID_EVEN:
                if ((*biter)->u.tcap.regType == msg->u.tcap.regType)
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                break;
            case MABCL_TCAP_RT_DID_ODD:
                if ((*biter)->u.tcap.regType == msg->u.tcap.regType)
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                break;
            case MABCL_TCAP_RT_TID_RANGE:
                if ((((msg->u.tcap.ltid >= (*biter)->u.tcap.ltid) &&
                      (msg->u.tcap.ltid <= (*biter)->u.tcap.utid)) ||
                     ((msg->u.tcap.utid >= (*biter)->u.tcap.ltid) &&
                      (msg->u.tcap.utid <= (*biter)->u.tcap.utid))) &&
                    ((*biter)->u.tcap.regType == msg->u.tcap.regType))
                     
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }

                break;
            case MABCL_TCAP_RT_LPC_DPC_LSSN:
                if (((MTP3_PC_GET_VALUE(msg->u.tcap.lpc) == 
                      MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc)) &&
                     (MTP3_PC_GET_VALUE(msg->u.tcap.dpc) == 
                      MTP3_PC_GET_VALUE((*biter)->u.tcap.dpc)) &&
                     (msg->u.tcap.ssn == (*biter)->u.tcap.ssn)) &&
                    ((*biter)->u.tcap.regType == msg->u.tcap.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_TCAP_RT_LPC_LSSN:
                if (((MTP3_PC_GET_VALUE(msg->u.tcap.lpc) == 
                      MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc)) &&
                     (msg->u.tcap.ssn == (*biter)->u.tcap.ssn)) &&
                    ((*biter)->u.tcap.regType == msg->u.tcap.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_TCAP_RT_LSSN:
                if ((msg->u.tcap.ssn == (*biter)->u.tcap.ssn) &&
                    ((*biter)->u.tcap.regType == msg->u.tcap.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_TCAP_RT_LPC:
                if ((MTP3_PC_GET_VALUE(msg->u.tcap.lpc) == 
                     MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc)) &&
                    ((*biter)->u.tcap.regType == msg->u.tcap.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_TCAP_RT_DPC:
                if ((MTP3_PC_GET_VALUE(msg->u.tcap.dpc) == 
                     MTP3_PC_GET_VALUE((*biter)->u.tcap.dpc)) &&
                    ((*biter)->u.tcap.regType == msg->u.tcap.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_ISUP_RT_LPC_CIC_RANGE:
                if (((((msg->u.isup.lcic >= (*biter)->u.isup.lcic) &&
                      (msg->u.isup.lcic <= (*biter)->u.isup.ucic)) ||
                     ((msg->u.isup.ucic >= (*biter)->u.isup.lcic) &&
                      (msg->u.isup.ucic <= (*biter)->u.isup.ucic))) &&
                    (MTP3_PC_GET_VALUE(msg->u.isup.lpc) == 
                     MTP3_PC_GET_VALUE((*biter)->u.isup.lpc))) &&
                    ((*biter)->u.isup.regType == msg->u.isup.regType))
                {
                     printf("duplicate criteria\n");
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_ISUP_RT_DPC_CIC_RANGE:
                if (((((msg->u.isup.lcic >= (*biter)->u.isup.lcic) &&
                      (msg->u.isup.lcic <= (*biter)->u.isup.ucic)) ||
                     ((msg->u.isup.ucic >= (*biter)->u.isup.lcic) &&
                      (msg->u.isup.ucic <= (*biter)->u.isup.ucic))) &&
                    (MTP3_PC_GET_VALUE(msg->u.isup.dpc) == 
                     MTP3_PC_GET_VALUE((*biter)->u.isup.dpc))) &&
                    ((*biter)->u.isup.regType == msg->u.isup.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_ISUP_RT_LPC:
                if ((MTP3_PC_GET_VALUE(msg->u.isup.lpc) == 
                     MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc)) &&
                    ((*biter)->u.isup.regType == msg->u.isup.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            case MABCL_ISUP_RT_DPC:
                if ((MTP3_PC_GET_VALUE(msg->u.isup.dpc) == 
                     MTP3_PC_GET_VALUE((*biter)->u.tcap.dpc)) &&
                    ((*biter)->u.isup.regType == msg->u.isup.regType))
                {
                    ret = ROUTING_CRITERIA_DUPLICATE_ENTRY;
                }
                break;
            }
        }

        if (ret != ITS_SUCCESS)
            break;
        biter++;
    }

    rinfoMutex_->Release();

    return ret;
}

int
ClientHandler::Register(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    engine::Worker* worker = (engine::Worker*)thr;
    MABCL_MESSAGE msg;

    if (MABCL_Decode(&msg, evt) != ITS_SUCCESS)
    {
        MABCL_MESSAGE rackMsg;
        rackMsg.clientID = msg.clientID;
        rackMsg.msg_type = REGISTER_ACK_MSG;
        rackMsg.u.regAck.result = 1;
        rackMsg.u.regAck.errorCode = 1;

        ITS_EVENT event;
        if (MABCL_Encode(&rackMsg, &event) != ITS_SUCCESS)
        {
            return !ITS_SUCCESS;
        }

        TRANSPORT_PutEvent(worker->GetInstance(), &event);
    }

    ITS_ULONG clientid = msg.clientID;

    int ret = !ITS_SUCCESS;

    printf("ClientId : %d\n",msg.clientID);
      
    for (int i = 0; i < msg.u.regInfo.numOfRecords; i++)
    {
        ClientRoutingInfo* info = 
            (ClientRoutingInfo*) malloc(sizeof(ClientRoutingInfo));
        info->clientID = clientid;
        info->routing_criteria = msg.u.regInfo.routing_criteria;
        switch(msg.u.regInfo.routing_criteria)
        {
            case MABCL_TCAP_RT_DPC:
            case MABCL_TCAP_RT_LPC:
            case MABCL_TCAP_RT_LSSN:
            case MABCL_TCAP_RT_LPC_LSSN:
            case MABCL_TCAP_RT_LPC_DPC_LSSN:
            case MABCL_TCAP_RT_TID_RANGE:
            case MABCL_TCAP_RT_DID_EVEN:
            case MABCL_TCAP_RT_DID_ODD:
                info->u.tcap = msg.u.regInfo.u.tcap[i];
                ret = IsClientAllowed(info);
                break;
            case MABCL_ISUP_RT_DPC:
            case MABCL_ISUP_RT_LPC:
            case MABCL_ISUP_RT_DPC_CIC_RANGE:
            case MABCL_ISUP_RT_LPC_CIC_RANGE:
                info->u.isup = msg.u.regInfo.u.isup[i];
                printf("checking is client allowed\n");
                ret = IsClientAllowed(info);
                break;
        }

        if (ret == ITS_SUCCESS)
        {
            rinfoMutex_->Acquire();
            printf("Adding element to routing info\n");
            routInfo_.push_back(info);
            rinfoMutex_->Release();

            if (i == 0)
            {
                cidmapMutex_->Acquire();
                printf("Worker Instance 1 : %d\n",worker->GetInstance());
                clIdMap_.insert(ClientIDMap::value_type(clientid, worker->GetInstance()));
                cidmapMutex_->Release();
            }
        }
        else
        {
            break;
        }
    }

    if (ret == ITS_SUCCESS)
    {
        
        MABCL_MESSAGE rackMsg;
        rackMsg.clientID = clientid;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;
        rackMsg.msg_type = REGISTER_ACK_MSG;

        rackMsg.u.regAck.result = ITS_SUCCESS;
        rackMsg.u.regAck.errorCode = 0;
        
        SendMsg(&rackMsg);
    } 
    else
    {
        MABCL_MESSAGE rackMsg;
        rackMsg.clientID = clientid;
        rackMsg.msg_type = REGISTER_ACK_MSG;
        rackMsg.u.regAck.routing_criteria = msg.u.regInfo.routing_criteria;
        rackMsg.u.regAck.result = 1;
        rackMsg.u.regAck.errorCode = ret;

        ITS_EVENT event;
        if (MABCL_Encode(&rackMsg, &event) != ITS_SUCCESS)
        {
            return !ITS_SUCCESS;
        }

        TRANSPORT_PutEvent(worker->GetInstance(), &event);

        return !ITS_SUCCESS;
    }
}

int
ClientHandler::DeRegister(TPOOL_THREAD *thr, ITS_EVENT *evt)
{
    MABCL_MESSAGE msg;

    if (MABCL_Decode(&msg, evt) != ITS_SUCCESS)
    {
        MABCL_MESSAGE dackMsg;
        dackMsg.clientID = msg.clientID;
        dackMsg.msg_type = DERGISTER_ACK_MSG;
        dackMsg.u.deregAck.result = 1;
        dackMsg.u.deregAck.errorCode = 1;
        dackMsg.u.deregAck.routing_criteria = msg.u.regInfo.routing_criteria;

        SendMsg(&dackMsg);
        return !ITS_SUCCESS;
    }

    ITS_ULONG clientid = msg.clientID;

    MABCL_MESSAGE dackMsg;
    dackMsg.clientID = clientid;
    dackMsg.msg_type = DERGISTER_ACK_MSG;
    dackMsg.u.deregAck.result = 0;
    dackMsg.u.deregAck.errorCode = 0;
    dackMsg.u.deregAck.routing_criteria = msg.u.regInfo.routing_criteria;
    SendMsg(&dackMsg);

    cidmapMutex_->Acquire();
    ClientIDMap::iterator iter = clIdMap_.find(clientid);
    if (iter != clIdMap_.end())
    {
        clIdMap_.erase(iter);

        std::list<ClientRoutingInfo*>::iterator bIter = routInfo_.begin();
        std::list<ClientRoutingInfo*>::iterator eIter = routInfo_.end();

        rinfoMutex_->Acquire();
        while(bIter != eIter)
        {
            if ((*bIter)->clientID == clientid)
            {
                routInfo_.erase(bIter);
                break;
            }
            bIter++;
        }
        rinfoMutex_->Release();
    }
    cidmapMutex_->Release();

    return ITS_SUCCESS; 
}

int 
ClientHandler::FindBestTCAPClient(MABCL_TCAP* tc)
{
    int ret = 0;

    rinfoMutex_->Acquire();
    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();
    std::list<ClientRoutingInfo*>::iterator tmpIter = routInfo_.end();
    ITS_BOOLEAN match = ITS_FALSE;

    while (biter != eiter)
    {
        match = ITS_FALSE;

        switch((*biter)->routing_criteria)
        {
        case MABCL_TCAP_RT_DID_EVEN:
        {
            if (!(tc->ltid % 2))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_DID_ODD:
        {
            if (tc->ltid % 2)
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_TID_RANGE:
        {
            if ((tc->ltid >= (*biter)->u.tcap.ltid) &&
                (tc->ltid >= (*biter)->u.tcap.utid))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_LPC_DPC_LSSN:
        {
            if ((MTP3_PC_GET_VALUE(tc->lpc) == MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc)) &&
                (MTP3_PC_GET_VALUE(tc->dpc) == MTP3_PC_GET_VALUE((*biter)->u.tcap.dpc)) &&
                (tc->ssn == (*biter)->u.tcap.ssn))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_LPC_LSSN:
        {
            if ((MTP3_PC_GET_VALUE(tc->lpc) == MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc)) &&
                (tc->ssn == (*biter)->u.tcap.ssn))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_LSSN:
        {
            printf("Verifying LSSN %d %d\n",tc->ssn, (*biter)->u.tcap.ssn);
            if (tc->ssn == (*biter)->u.tcap.ssn)
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_LPC:
        {
            if (MTP3_PC_GET_VALUE(tc->lpc) == MTP3_PC_GET_VALUE((*biter)->u.tcap.lpc))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_TCAP_RT_DPC:
        {
            if (MTP3_PC_GET_VALUE(tc->dpc) == MTP3_PC_GET_VALUE((*biter)->u.tcap.dpc))
            {
                match = ITS_TRUE;
            }
            break;
        }
        }

        if (match == ITS_TRUE)
        {
            if (tmpIter == eiter)
            {
                tmpIter = biter;
            }
            else
            {
                if ((*biter)->routing_criteria > 
                    (*tmpIter)->routing_criteria)
                {
                    tmpIter = biter;
                }
            }
        }

        biter++;
    }

    if (tmpIter != eiter)
    {
        ret = (*tmpIter)->clientID;
    }

    rinfoMutex_->Release();

    return ret;
}

int 
ClientHandler::FindBestISUPClient(MABCL_ISUP* ic)
{
    int ret = 0;

    rinfoMutex_->Acquire();
    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();
    std::list<ClientRoutingInfo*>::iterator tmpIter = routInfo_.end();
    ITS_BOOLEAN match = ITS_FALSE;

    while (biter != eiter)
    {
        match = ITS_FALSE;

        switch((*biter)->routing_criteria)
        {
        case MABCL_ISUP_RT_LPC_CIC_RANGE:
        {
            printf("***** verifying : %d %d %d %d %d***********\n", 
                ic->lcic, (*biter)->u.isup.lcic,
                (*biter)->u.isup.ucic, MTP3_PC_GET_VALUE(ic->lpc),
                MTP3_PC_GET_VALUE((*biter)->u.isup.lpc));

            if ((ic->lcic >= (*biter)->u.isup.lcic) &&
                (ic->lcic <= (*biter)->u.isup.ucic) &&
                (MTP3_PC_GET_VALUE(ic->lpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.lpc)))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_ISUP_RT_DPC_CIC_RANGE:
        {
            if ((ic->lcic >= (*biter)->u.isup.lcic) &&
                (ic->lcic <= (*biter)->u.isup.ucic) &&
                (MTP3_PC_GET_VALUE(ic->dpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.dpc)))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_ISUP_RT_LPC:
        {
            if (MTP3_PC_GET_VALUE(ic->lpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.lpc))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_ISUP_RT_DPC:
        {
            if (MTP3_PC_GET_VALUE(ic->dpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.dpc))
            {
                match = ITS_TRUE;
            }
            break;
        }
        }

        if (match == ITS_TRUE)
        {
            if (tmpIter == eiter)
            {
                tmpIter = biter;
            }
            else
            {
                if ((*biter)->routing_criteria > 
                    (*tmpIter)->routing_criteria)
                {
                    tmpIter = biter;
                }
            }
        }

        biter++;
    }

    if (tmpIter != eiter)
    {
        ret = (*tmpIter)->clientID;
    }

    rinfoMutex_->Release();

    return ret;
}

int 
ClientHandler::FindBestMTP3Client(MABCL_ISUP* ic)
{
    int ret = 0;

    rinfoMutex_->Acquire();
    std::list<ClientRoutingInfo*>::iterator biter = routInfo_.begin();
    std::list<ClientRoutingInfo*>::iterator eiter = routInfo_.end();
    std::list<ClientRoutingInfo*>::iterator bkIter = eiter;
    std::list<ClientRoutingInfo*>::iterator prIter = eiter;
    ITS_BOOLEAN match = ITS_FALSE;

    while (biter != eiter)
    {
        match = ITS_FALSE;

        switch((*biter)->routing_criteria)
        {
        case MABCL_ISUP_RT_LPC_CIC_RANGE:
        {
            printf("***** %d %d %d %d %d***********\n",
                ic->lcic, (*biter)->u.isup.lcic,
                (*biter)->u.isup.ucic, MTP3_PC_GET_VALUE(ic->lpc),
                MTP3_PC_GET_VALUE((*biter)->u.isup.lpc));

            if ((ic->lcic >= (*biter)->u.isup.lcic) &&
                (ic->lcic <= (*biter)->u.isup.ucic) &&
                (MTP3_PC_GET_VALUE(ic->lpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.lpc)))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_ISUP_RT_DPC_CIC_RANGE:
        {
            if ((ic->lcic >= (*biter)->u.isup.lcic) &&
                (ic->lcic <= (*biter)->u.isup.ucic) &&
                (MTP3_PC_GET_VALUE(ic->dpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.dpc)))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_ISUP_RT_LPC:
        {
            if (MTP3_PC_GET_VALUE(ic->lpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.lpc))
            {
                match = ITS_TRUE;
            }
            break;
        }
        case MABCL_ISUP_RT_DPC:
        {
            if (MTP3_PC_GET_VALUE(ic->dpc) == MTP3_PC_GET_VALUE((*biter)->u.isup.dpc))
            {
                match = ITS_TRUE;
            }
            break;
        }
        }

        if (match == ITS_TRUE)
        {
            if ((*biter)->u.isup.regType == 0)
            {
                printf("Assigning Backup Iter\n");
                bkIter = biter;
            }
            if ((*biter)->u.isup.regType == 1)
            {
                printf("Assigning Primary Iter\n");
                prIter = biter;
            } 
        }

        biter++;
    }

    if (prIter != eiter)
    {
        ret = (*prIter)->clientID;
    }
    else if (bkIter != eiter)
    {
        ret = (*bkIter)->clientID;
    }

    rinfoMutex_->Release();

    return ret;
}

int
ClientHandler::SendMsg(MABCL_MESSAGE* msg)
{
    ITS_EVENT evt;

    if (MABCL_Encode(msg, &evt) != ITS_SUCCESS)
    {
        return !ITS_SUCCESS;
    }

    cidmapMutex_->Acquire();
    ClientIDMap::iterator iter = clIdMap_.find(msg->clientID);
    if (iter != clIdMap_.end())
    {
        printf("Worker Instance : %d\n",iter->second);

        printf("Message to client event len:%d\n",evt.len);
        for(int i=0;i<evt.len;i++)
        {
            if ((i + 1) % 16 == 0) printf("\n");
            printf("%02x ",evt.data[i]);
        }
        printf("\n");

        TRANSPORT_PutEvent(iter->second, &evt);
    }
    else
    {
        cidmapMutex_->Release();
        return !ITS_SUCCESS;
    }

    cidmapMutex_->Release();
    return ITS_SUCCESS;
}

int
ClientHandler::CleanUP(TPOOL_THREAD *thr)
{
    engine::Worker* worker = (engine::Worker*)thr;
    ITS_INT sockid = worker->GetInstance();

    int cid = 0;

    cidmapMutex_->Acquire();

    ClientIDMap::iterator biter = clIdMap_.begin();
    ClientIDMap::iterator eiter = clIdMap_.end();
    ClientIDMap::iterator tmpIter = eiter;

    while (biter != eiter)
    {
        if (biter->second == sockid)
        {
            cid = biter->first;
            clIdMap_.erase(biter);
            printf("Erasing Client : %d\n",cid);
            break;
        }

        biter++;
    }

    cidmapMutex_->Release();

    if (cid)
    {
        rinfoMutex_->Acquire();
        
        std::list<ClientRoutingInfo*>::iterator iter1 = routInfo_.begin();
        std::list<ClientRoutingInfo*>::iterator iter2 = routInfo_.end();
        std::list<ClientRoutingInfo*>::iterator ersIter;
        
        while (iter1 != iter2)
        {
            if ((*iter1)->clientID == cid)
            {
                ersIter = iter1;
                iter1++;
                routInfo_.erase(ersIter);
                printf("Erasing element in RoutingInfo\n");
            }
            else
            {
                iter1++;
            }
        }

        rinfoMutex_->Release();
    }
            

    return ITS_SUCCESS;
}
