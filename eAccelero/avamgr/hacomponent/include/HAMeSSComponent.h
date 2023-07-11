/* 
 * File:   HAMeSSComponent.h
 * Author: adey
 *
 * Created on July 1, 2012, 4:13 PM
 */

#ifndef HAMESSCOMPONENT_H
#define	HAMESSCOMPONENT_H

#include "ComponentDefines.h"
#include "InterfaceDefines.h"
#include "MeSSComponent.h"
#include "HAComponent.h"
#include "HAComponent.pb.h"
#include "AvaMgrComponentStatusInterface_caller.h"

namespace eAccelero {

enum DeploymentMode {
    STANDALONE_MODE = 1,
    ACTIVE_STANDBY_MODE,
    ACTIVE_COLD_STANDBY_MODE,
    ACTIVE_HOT_STANDBY_MODE
};

#define HOSTNAME_LEN    256

#define METHOD_ID_START 1

    enum MethodId {
        M_AVAMGR_PROCESS_AVAILABILITY_STATUS_RESET_REQ = METHOD_ID_START,
        M_AVAMGR_PROCESS_AVAILABILITY_STATUS_GET_REQ,
        M_AVAMGR_GET_PEER_PING_REQ,
        M_AVAMGR_ACTIVATE_SWITCHOVER_REQ
    };

    enum InstanceAvailabilityStatus {
        //Do not change the order
        INDETERMINATE,
        STANDBY,
        ACTIVE
    };

    enum CurrentProcessStatus {
       HEARTBEAT_OK,
       HUNG_THREAD,    
    };

    class HAMeSSComponent : public MeSSComponent,
    public AvaMgrProcessStatusInterface,
    public Stub::AvaMgrComponentStatusInterfaceRespCbk {
    public:

        static HAMeSSComponent& Instance() {
            return *(static_cast<HAMeSSComponent*> (m_instance));
        }

        HAMeSSComponent(const char *name, unsigned compId);

        ~HAMeSSComponent();

        virtual void Initialize();

        virtual void Terminate();


        /* Used to reset the Instance Id binding for the MeSSEndpoint.
         * This is used by the Availability Manager to request a specific Component to do an ACTIVE/STANDBY switch over, i.e.,
         * change the instance id binding between ACTIVE/STANDBY.
         * (DO NOT OVERRIDE, UNLESS REQUIRED) 
         */
        virtual int AvailabilityStatusResetRequest(AvailabilityStatusResetReq* Request, AvailabilityStatusResetResp* Response);

        /* Used to get the Instance Id for a specific Component */
        virtual int AvailabilityStatusGetRequest(AvailabilityStatusGetReq* Request, AvailabilityStatusGetResp* Response);


        /*
         * Used to incorporate component-specific functions
         * 'before' instance id switch over.
         * (COMPONENTS SHOULD OVERRIDE THIS FUNCTION)
         */
        virtual int ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId);

        /*
         * Used to incorporate component-specific functions
         * 'after' instance id switch over.
         * (COMPONENTS SHOULD OVERRIDE THIS FUNCTION)
         */
        virtual int ProcessAvailabilityStatusResetPostFunc(bool switchOver);

        /*
         * Used to incorporate component-specific functions
         * 'after' status update from AVAMGR for any component is received.
         * (COMPONENTS SHOULD OVERRIDE THIS FUNCTION)
         */
        virtual int ComponentStatusUpdateBroadcast(ComponentStatusUpdateReq *Request,ComponentStatusUpdateResp *Response);

        virtual int ProcessComponentStatusUpdate(uint16_t componentId, HAComponentStatus newStatus);


        virtual int ComponentStatusUpdateRespCbk(ComponentStatusUpdateResp *Response);

        /* This method would return the status/state of any component based on Component Id.        
         * This is a method which can be used by any component to know the current status of any other component.
         */
        HAComponentStatus GetComponentStatus(uint16_t componentId);

        /*
         * This method would inform the component to stop replication because
         * avamgr has lost connectivity to couchbase and replicating any further
         * state would fail.
         */
        int StopReplication(ReplicationReq* Request, ReplicationResp* Response);

        /*
         * This is invoked after processing of StopReplication. 
         * The components can over-ride this method to take any specific actions
         * while replication is being stopped.
         */
        virtual int StopReplicationPostFunc();

        /*
         * This method would inform the component to start replication after it was stopped.
         * The stoppage of replication would be due to loss of connectivity with couchbase.
         */
        int StartReplication(ReplicationReq* Request, ReplicationResp* Response);

        /*
         * This is invoked after processing of StartReplication. 
         * The components can over-ride this method to take any specific actions
         * while replication is started after previous stop.
         */
        virtual int StartReplicationPostFunc();



        /*
         */
        void UpdateComponentSelfStatus(HAComponentStatus newStatus);

        /*
         * This method returns the Self Component Status
         */
        HAComponentStatus GetSelfStatus();

        
        int AvailabilityActiveUpdateBroadcast(AvailabilityActiveReq *Request,
                AvailabilityActiveResp *Response);

        virtual int AvailabilityActiveUpdateBroadcastCbk();
        static bool isReplicationEnabled()
        {
            return m_bIsReplicationEnabled;
        }


	static void EnableReplication()
	{
	    m_bIsReplicationEnabled=true;
	}

	static void DisableReplication()
	{
	    m_bIsReplicationEnabled=false;

	}

    private:
        struct CmdArgs {

            CmdArgs()
            : mode("m", "mode", "Whether instance should be started in standalone mode") {
            }
            CmdOption<std::string> mode;
        } m_cmdArgs;

        static void setReplicationState(uint32_t mode)
        {
            if(mode == ACTIVE_HOT_STANDBY_MODE)
            {
                m_bIsReplicationEnabled = true;
            }
            else
            {
                m_bIsReplicationEnabled = false;
            }
        }
        std::map<uint16_t,HAComponentStatus> m_componentStatusMap;
        HAComponentStatus m_componentSelfStatus;
        uint32_t GetSelfTipcNodeId();
        void SendComponentStatusUpdate(uint16_t instanceId,HAComponentStatus newStatus);
        static bool m_bIsReplicationEnabled;
    };

} // namepsace eAccelero


#endif	/* HAMESSCOMPONENT_H */

