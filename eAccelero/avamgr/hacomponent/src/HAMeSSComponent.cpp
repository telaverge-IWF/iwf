#include "HACommon.pb.h"
#include "ComponentDefines.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "HAMeSSComponent.h"


namespace eAccelero {

bool HAMeSSComponent::m_bIsReplicationEnabled = false;

    HAMeSSComponent::HAMeSSComponent(const char *name, unsigned compId)
    : MeSSComponent(name, compId),m_componentSelfStatus(COMPONENT_STATUS_INDETERMINATE)
    {
        //Populate ComponentStatus Map to be COMPONENT_INITIAL_STATUS
        //Currently that would be COMPONENT_STATUS_INDETERMINATE
        for(uint16_t componentId = COMPONENT_ID_START;componentId < COMPONENT_ID_END; componentId++)
        {
            m_componentStatusMap[componentId] = (HAComponentStatus)COMPONENT_STATUS_INDETERMINATE;
        }

         Stub::AvaMgrComponentStatusInterfaceRespCbk::RegisterAvaMgrComponentStatusInterfaceRespHandler();
    }

    HAMeSSComponent::~HAMeSSComponent() {

    }

    void HAMeSSComponent::Initialize() {
        MeSSComponent::Initialize();

        // Init code
    }

    void HAMeSSComponent::Terminate() {
        // Terminate code

        MeSSComponent::Terminate();
    }


    /* Used to reset the Instance Id binding for the MeSSEndpoint.
    This is used by the Availability Manager to request a specific Component to do an ACTIVE/STANDBY switch over, i.e.,
    change the instance id binding between ACTIVE/STANDBY.
    (DO NOT OVERRIDE, UNLESS REQUIRED) */

    int HAMeSSComponent::AvailabilityStatusResetRequest(AvailabilityStatusResetReq* req, AvailabilityStatusResetResp* resp)
    {
        char selfHostname[HOSTNAME_LEN];
        gethostname(selfHostname, HOSTNAME_LEN);

        bool switchOver = false; // used to check if the reset request is due to a switch over

        resp->set_responseid(req->requestid());
        resp->set_componentid(MeSSObj().Self().compId);
        resp->set_newinstanceid(MeSSObj().Self().instance);

        resp->set_peerhostname(selfHostname);

        if (req->has_switchover())
        {
            switchOver = req->switchover();
        }

        resp->set_isavailabilitystatusreset(false);

        if (!(strcmp(req->selfhostname().c_str(), selfHostname))) {

            this->ProcessAvailabilityStatusResetPreFunc((uint16_t)req->newinstanceid());

            MeSSObj().Self().instance = (uint16_t)(req->newinstanceid());

            MeSSObj().Rebind(MeSSObj().Self());

            resp->set_newinstanceid(MeSSObj().Self().instance);
            resp->set_isavailabilitystatusreset(true);

            this->ProcessAvailabilityStatusResetPostFunc(switchOver);
        }

        return 0;
    }

    /* Used to get the Instance Id for a specific Component */
    int HAMeSSComponent::AvailabilityStatusGetRequest(AvailabilityStatusGetReq* req, AvailabilityStatusGetResp* resp)
    {
        char selfHostname[HOSTNAME_LEN];
        gethostname(selfHostname, HOSTNAME_LEN);

        resp->set_responseid(req->requestid());
        resp->set_componentid(MeSSObj().Self().compId);
        resp->set_instanceid(MeSSObj().Self().instance);

        resp->set_peerhostname(selfHostname);
        resp->set_currentprocessstatus(HEARTBEAT_OK);
        resp->set_currentcomponentstatus(m_componentSelfStatus);

        return 0;
    }

    /*
     * Used to incorporate component-specific functions
     * 'before' instance id switch over.
     * (COMPONENTS SHOULD OVERRIDE THIS FUNCTION)
     */
    int HAMeSSComponent::ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId) {
        CLOG_WARNING("PLEASE OVERRIDE THIS FUNCTION");

        return 0;
    }

    /*
     * Used to incorporate component-specific functions
     * 'after' instance id switch over.
     * (COMPONENTS SHOULD OVERRIDE THIS FUNCTION)
     */
    int HAMeSSComponent::ProcessAvailabilityStatusResetPostFunc(bool switchOver) {
        CLOG_WARNING("PLEASE OVERRIDE THIS FUNCTION");

        return 0;
    }

    /*
     * Used to incorporate component-specific functions
     * 'after' status update from AVAMGR for any component is received.
     * (COMPONENTS SHOULD OVERRIDE THIS FUNCTION)
     */
    int HAMeSSComponent::ComponentStatusUpdateBroadcast(ComponentStatusUpdateReq *req,ComponentStatusUpdateResp * resp)
    {
        if(req->tipcnodeid() == GetSelfTipcNodeId())
        {
            HAComponentStatus status;
            uint16_t componentId;
            for(int i =0;i < req->currentcomponentstatus_size();i++)
            {
                status = (HAComponentStatus)req->currentcomponentstatus(i).currentstatus();
                if(status != COMPONENT_STATUS_INDETERMINATE)
                {
                    componentId = req->currentcomponentstatus(i).componentid();
                    CLOG_DEBUG("Received a Component Status Update for Component %d, new Status %d",componentId,status);
                    //Update the local StatusMap for the component.
                    m_componentStatusMap[componentId] = status;

                    //Invoke the method which shall be implemented by the component to listen for status updates.
                    this->ProcessComponentStatusUpdate(componentId,status);
                }
            }

            // Now set the response with self status
            resp->set_responseid(req->requestid());
            ComponentStatus* compStatus = resp->mutable_currentcomponentstatus();
            compStatus->set_currentstatus(m_componentSelfStatus);
            compStatus->set_componentid(MeSSObj().Self().compId);
        }

        return 0;
    }

    int HAMeSSComponent::ProcessComponentStatusUpdate(uint16_t componentId,HAComponentStatus newStatus)
    {
        CLOG_WARNING("PLEASE OVERRIDE THIS FUNCTION");
        return 0;
    }

    /* This method would return the status/state of any component based on Component Id.
     * This is a method which can be used by any component to know the current status of any other component.
     */
    HAComponentStatus HAMeSSComponent::GetComponentStatus(uint16_t componentId)
    {
        return m_componentStatusMap[componentId];
    }

    /*
     * This method returns the Self Component Status
     */
    HAComponentStatus HAMeSSComponent::GetSelfStatus()
    {
        return m_componentSelfStatus;
    }

    void HAMeSSComponent::UpdateComponentSelfStatus(HAComponentStatus newStatus)
    {

        //Update the local status
        m_componentSelfStatus = newStatus;

        //Send update to AvaMgr
        SendComponentStatusUpdate(MESS_MULTICAST_STANDBY,newStatus);
        SendComponentStatusUpdate(MESS_MULTICAST_ACTIVE,newStatus);

    }

    void HAMeSSComponent::SendComponentStatusUpdate(uint16_t instanceId,HAComponentStatus newStatus)
    {
        MeSSEndpoint dest = {COMP_AVAILABILITY_MANAGER,instanceId};
        static uint32_t requestId = 0;
        Stub::AvaMgrComponentStatusInterface intf(dest,0);

        ComponentStatusUpdateReq req;
        req.set_requestid(requestId++);
        req.set_tipcnodeid(GetSelfTipcNodeId());
        ComponentStatus* compStatus = req.add_currentcomponentstatus();
        compStatus->set_currentstatus(newStatus);
        compStatus->set_componentid(MeSSObj().Self().compId);

        //Send Status Update to AvaMgr
        intf.ComponentStatusUpdate(req);

    }

    int HAMeSSComponent::ComponentStatusUpdateRespCbk(ComponentStatusUpdateResp *Response)
    {
        return 0;
    }


    uint32_t HAMeSSComponent::GetSelfTipcNodeId() {
        TIPCAddr addr;
        TIPCSock sock(SOCK_RDM);

        sock.GetSockAddr(addr);
        return tipc_node((((struct sockaddr_tipc *) addr)->addr.id.node));
    }


    int HAMeSSComponent::StartReplication(ReplicationReq* req, ReplicationResp* resp)
    {
        if(req->tipcnodeid() == GetSelfTipcNodeId())
        {
            m_bIsReplicationEnabled = true;
            //Invoking PostFunc if Application wants this event.
            this->StartReplicationPostFunc();

        }
        return 0;
    }


    int HAMeSSComponent::StartReplicationPostFunc()
    {
        return 0;
    }

    int HAMeSSComponent::StopReplication(ReplicationReq* req, ReplicationResp* rep)
    {
        if(req->tipcnodeid() == GetSelfTipcNodeId())
        {
            m_bIsReplicationEnabled = false;
            //Invoke the PostFunc
            this->StopReplicationPostFunc();
        }
        return 0;
    }

    int HAMeSSComponent::StopReplicationPostFunc()
    {
        return 0;
    }

    int HAMeSSComponent::AvailabilityActiveUpdateBroadcast(AvailabilityActiveReq *Request,
                                          AvailabilityActiveResp *Response)
    {
        CLOG_DEBUG("AVAILABILITY ACTIVE UPDATE BROADCAST");
        this->AvailabilityActiveUpdateBroadcastCbk();
        return 0;
    }

    int HAMeSSComponent::AvailabilityActiveUpdateBroadcastCbk()
    {
        return 0;
    }
} // namespace eAccelero


