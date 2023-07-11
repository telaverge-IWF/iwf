
/* ********************************-*-CPP-*-***********************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#include "ReplicationManager.h"
#include "shm.h"

using namespace eAccelero;
using namespace std;


ReplicationManager::ReplicationManager()
    :HAMeSSComponent("ReplicationManager", COMP_REPLICATION_MANAGER),
     m_logger("REPMGR"),
     m_syslogChannel("REPMGR",(LOG_PID),LOG_LOCAL6)
{
    Stub::RepMgrInterfaceRespCbk::RegisterRepMgrInterfaceRespHandler();
}

ReplicationManager::~ReplicationManager()
{
    //Logger::currLogger = NULL;
}

void ReplicationManager::Initialize()
{
      HAMeSSComponent::Initialize();
}

void ReplicationManager::Terminate()
{
}

int ReplicationManager::ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId)
{
    return 0;
}

int ReplicationManager::ProcessAvailabilityStatusResetPostFunc(bool switchOver)
{
    return 0;
}

int ReplicationManager::ProcessComponentStatusUpdate(uint16_t componentId,HAComponentStatus newStatus)
{
    return 0;
}


int ReplicationManager::InitiateReplication(InitiateReplicationRequest *Request,InitiateReplicationResponse *Response)
{
    cout << "Received InitiateReplication:" << Request->DebugString() << endl;
    int ret  = create_shm();
    if(ret == 0)
        printf("Created shm successfully");
    else
        printf("shm creation failed");
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}

int ReplicationManager::ReplicateNewCacheEntry(ReplicateEntryRequest *Request,ReplicateEntryResponse *Response)
{
    void* data = NULL;
    //void* data = malloc(Request->repentry(0).data().length());
    int ret = 0;

    cout << "Received ReplicateNewCacheEntry:" << Request->DebugString() << endl;

    //Read the entry from shared memory
    ret = read_shm(Request->repentry(0).header().sequenceid(),&data,Request->repentry(0).data().length());
    if(ret == 0)
        printf("Read from shm for index %d successful",Request->repentry(0).header().sequenceid());
    else
    {
        printf("Read from shm for index %d failed",Request->repentry(0).header().sequenceid());
        return 0;
    }

    //Send Create Cache Entry request to all Standby instances.
    //TODO change it to selective peers.
    SendCreateEntryRequest(MESS_MULTICAST_STANDBY,Request,data);
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}

void ReplicationManager::SendCreateEntryRequest(uint16_t instanceId,ReplicateEntryRequest *Request,void* data)
{
    //Form the request to replicate.
    MeSSEndpoint dest = {COMP_REPLICATION_MANAGER, instanceId};
    Stub::RepMgrInterface repIntf(dest,0);
    Request->mutable_repentry(0)->mutable_data()->set_data(data,Request->repentry(0).data().length());

    cout << "Sending SendCreateEntryRequest :" << Request->DebugString() << endl;
    //Send the request to Peer RepMgr.
    repIntf.CreateCacheEntry(*Request);
}

int ReplicationManager::ReplicateUpdatedCacheEntry(ReplicateEntryRequest *Request,ReplicateEntryResponse *Response)
{
    cout << "Received ReplicateNewCacheEntry:" << Request->DebugString() << endl;
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}

int ReplicationManager::ReplicateDeletedCacheEntry(ReplicateEntryRequest *Request,ReplicateEntryResponse *Response)
{
    cout << "Received ReplicateDeletedCacheEntry:" << Request->DebugString() << endl;
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}


int ReplicationManager::CreateCacheEntry(ReplicateEntryRequest *Request,ReplicateEntryResponse *Response)
{
    cout << "Received CreateCacheEntry:" << Request->DebugString() << endl;
    //Update the Shared memory

    update_shm(Request->repentry(0).header().sequenceid(),Request->repentry(0).data().data().c_str(),Request->repentry(0).data().length());

    //Notify the application
    //Send it to appropriate application based on componentID in the message
    uint16_t componentId = Request->repentry(0).header().componentid();
    MeSSEndpoint dest = {componentId, MeSSObj().Self().instance};
    Stub::ApplicationReplicationInterface appIntf(dest,0);
    //Clear the data part from the request since it is already written to shared memory
    ReplicationEntry repEntry = Request->repentry(0);
    Data *data =  repEntry.mutable_data();
    data->release_data();
    appIntf.ReplicateNewCacheEntry(*Request);
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}

int ReplicationManager::UpdateCacheEntry(ReplicateEntryRequest *Request,ReplicateEntryResponse *Response)
{
    cout << "Received UpdateCacheEntry:" << Request->DebugString() << endl;
    update_shm(Request->repentry(0).header().sequenceid(),(Request->repentry(0).data().data().c_str()),Request->repentry(0).data().length());
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}

int ReplicationManager::DeleteCacheEntry(ReplicateEntryRequest *Request,ReplicateEntryResponse *Response)
{
    cout << "Received DeleteCacheEntry:" << Request->DebugString() << endl;
    shm_clear_entry(Request->repentry(0).header().sequenceid(),Request->repentry(0).data().length());
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}

int ReplicationManager::FetchCacheEntries(FetchReplicationEntriesRequest *Request,ReplicateEntryResponse *Response)
{
    cout << "Received FetchCacheEntries:" << Request->DebugString() << endl;
    Response->set_responseid(Request->requestid());
    Response->set_status(0);
    return 0;
}


int ReplicationManager::CreateCacheEntryRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}

int ReplicationManager::UpdateCacheEntryRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}

int ReplicationManager::DeleteCacheEntryRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}

int ReplicationManager::FetchCacheEntriesRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}

int ReplicationManager::ReplicateNewCacheEntryRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}
int ReplicationManager::ReplicateUpdatedCacheEntryRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}
int ReplicationManager::ReplicateDeletedCacheEntryRespCbk(ReplicateEntryResponse *Response)
{
    return 0;
}
int main( int argc, char *argv[] )
{
    ReplicationManager *repMgr = NULL;

    try {

        repMgr = new ReplicationManager();     // Start our component runnin
        CLOG_DEBUG("Initializeing App %d", argc);
        repMgr->Init(argc, argv);     // Initialize Replication Manager Objects.
        //repMgr->GetLogger().SetLevel(Logger::DEBUG, true);
        CLOG_NOTICE("REPMGR  initialized");
        repMgr->Run();                // In Line
    }
    catch(CmdParseException &e) {
        std::cerr << e.what() << std::endl;
    }
    catch(Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    CLOG_NOTICE("REPMGR exiting");
    if (repMgr) delete repMgr;
    return 0;
}
