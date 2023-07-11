/*********************************-*-C++-*-************************************
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

#include <sys/socket.h>
#include <netdb.h>

#include "HAComponent.h"
#include "AvaMgr.h"
#include "AvaMgr.pb.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "AvailabilityManager.h"

using namespace eAccelero;

uint32_t AvailabilityManager::GetTipcNodeId(TIPCAddr addr)
{
    return tipc_node((((struct sockaddr_tipc *) addr)->addr.id.node));
}



uint32_t AvailabilityManager::GetSelfTipcNodeId() {
    TIPCAddr addr;
    TIPCSock sock(SOCK_RDM);

    sock.GetSockAddr(addr);
    return tipc_node((((struct sockaddr_tipc *) addr)->addr.id.node));
}



int AvailabilityManager::GetAddrFamily(const char *ipAddress) {

    struct addrinfo hint, *info = 0;

    memset(&hint, 0, sizeof (hint));

    hint.ai_family = AF_UNSPEC;
    hint.ai_flags = AI_NUMERICHOST;

    int ret = getaddrinfo(ipAddress, NULL, &hint, &info);

    if (ret) {
        CLOG_ERROR("IP address DOES NOT belong to either AF_INET or AF_INET6");
        return -1;
    }

    int result = info->ai_family;

    freeaddrinfo(info);

    return result;
}


bool AvailabilityManager::isNodeActive()
{
    if((m_uiOwnTipcNodeId >= MESS_MIN_ACTIVE_INSTANCE) &&(m_uiOwnTipcNodeId <= MESS_MAX_ACTIVE_INSTANCE) )
    {
        return true;
    }
    else if ((m_uiOwnTipcNodeId >= MESS_MIN_STANDBY_INSTANCE) &&(m_uiOwnTipcNodeId <= MESS_MAX_STANDBY_INSTANCE) )
    {
        return false;
    }
    else
    {
        CLOG_CRITICAL("Node State is not Active or Standby.Node State:%d",m_uiOwnTipcNodeId);
    }
    return false;
}



std::vector<std::string> AvailabilityManager::Split(const char *str, char c) {
    std::vector<std::string> result;

    while (1) {
        const char *begin = str;

        while (*str != c && *str)
            str++;

        std::string tempStr = std::string(begin, str);
        tempStr.erase(tempStr.find_last_not_of(" \f\n\r\t\v") + 1);

        result.push_back(tempStr);

        if (0 == *str++)
            break;
    }

    return result;
}

bool AvailabilityManager::StartComponent(uint16_t componentId, bool isRestart)
{
    ProcessAttributes* pAttrib = &(m_objProcessMap[componentId]);
    uint8_t priority = m_objProcessMap[componentId].priority;
    std::string processNameWithLocationAndArgs = pAttrib->processName;

    std::string processNameWithLocation;
    char processArgsAll[ARGUMENT_LEN];

    std::string::size_type end = processNameWithLocationAndArgs.find_first_of(' ');

    if (end != string::npos) {
        processNameWithLocation = processNameWithLocationAndArgs.substr(0, end);

        std::string::size_type begin = end + 1;
        std::string processArgs = processNameWithLocationAndArgs.substr(begin);

        size_t lastNonWhitespace;
        lastNonWhitespace = processArgs.find_last_not_of(" \f\n\r\t\v");

        if (lastNonWhitespace != string::npos) {
            processArgs.erase(lastNonWhitespace + 1);
            sprintf(processArgsAll, "-i %d -m %d %s",
                    m_objSelfCurrentStatus.selfInstanceId,
                    m_iInstanceStartMode,
                    processArgs.c_str());
        } else {
            processArgs.clear();
            sprintf(processArgsAll, "-i %d -m %d",
                    m_objSelfCurrentStatus.selfInstanceId,
                    m_iInstanceStartMode);
        }

    } else {
        processNameWithLocation = processNameWithLocationAndArgs;

        sprintf(processArgsAll, "-i %d -m %d",
                m_objSelfCurrentStatus.selfInstanceId,
                m_iInstanceStartMode);
    }

    pid_t pid;
    LaunchProcess(processNameWithLocation.c_str(), processArgsAll, pid);

    if (pid < 0) {
        return false;
    }
    if(isRestart)
    {
        //Raise an Alarm for successfully restarting the process.
        if(priority == PROCESS_PRIORITY_HIGH)
        {
            //Don't raise the alarm if suppression flag is set.
            if(m_bSuppressHigPriorityProcessAlarm)
            {
                m_bSuppressHigPriorityProcessAlarm = false;
            }
            else
            {
                m_avaMgrAlarm->RaiseHighPriorityProcessUpAlarm(processNameWithLocation);
            }
        }else {
            m_avaMgrAlarm->RaiseLowPriorityProcessUpAlarm(processNameWithLocation);
        }
    }
    else
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
    	pAttrib->secondsToShutdownApplication = (tv.tv_sec) + ((tv.tv_usec) / 1000000) + m_uiCfgProcessRestartMaxAllowedIntervalHp;
        pAttrib->secondsToNextSigChld = (tv.tv_sec) + ((tv.tv_usec) / 1000000) + m_uiCfgProcessRestartMaxAllowedInterval;
        pAttrib->processRestartCounter = 0;
    }

    pAttrib->pid = pid;

    pAttrib->currentComponentStatus = COMPONENT_STATUS_INDETERMINATE;
    CLOG_NOTICE("Component %s being launched", pAttrib->processName.c_str());
    return true;
}

bool AvailabilityManager::TerminateAllComponents(bool highPriority)
{
    bool ret = true;
    CLOG_NOTICE(" > TerminateAllComponents");

    std::unordered_map<uint16_t, ProcessAttributes>::iterator iter;
    CLOG_NOTICE(" > TerminateAllComponents");
    for (iter = m_objProcessMap.begin(); iter != m_objProcessMap.end(); iter++)
    {
        if((*iter).second.pid != 0)
        {
            if((*iter).second.currentComponentStatus != COMPONENT_STATUS_STOPPED)
            {
                if((highPriority && ((*iter).second.priority == PROCESS_PRIORITY_HIGH))|| (!highPriority))
                {
                    CLOG_NOTICE("Sending SIGTERM to component %d with pid %d",(*iter).first,(*iter).second.pid);

                    /*The component is killed intentionally by AvaMgr and hence should not be considered as restart.
                     * Hence reducing the count to compensate for the SIGCHLD received due to this kill. */

                    ((*iter).second.processRestartCounterForShutdownApplication)--;
                    ((*iter).second.processRestartCounter)--;

                    int ret = kill(((*iter).second.pid), SIGTERM);
                    if(ret < 0)
                    {
                        CLOG_ERROR("Failed to send signal SIGTERM to component %d with pid %d, error %d",
				(*iter).first,(*iter).second.pid,errno);
                        ret = false;
		    }
		    // start a grace period before we send KILL signal
		    StartSigtermTimer((*iter).first, m_uiCfgMaxTimeToWaitBeforeSendingSigkill);
		}
            }
        }
    }
    CLOG_NOTICE(" < TerminateAllComponents");
    return ret;
}

bool AvailabilityManager::StartAllComponents(bool lowPriority)
{
    uint32_t index = 0;
    for(;index < m_objComponentIdVector.size();index++)
    {
        if(m_objProcessMap[m_objComponentIdVector[index]].currentComponentStatus == COMPONENT_STATUS_STOPPED)
        {
            if(((lowPriority &&  m_objProcessMap[m_objComponentIdVector[index]].priority == PROCESS_PRIORITY_LOW))|| (!lowPriority))
            {
                bool status;
                if(m_bComponentsRunning)
                {
                    status = StartComponent(m_objComponentIdVector[index],true);
                }
                else
                {
                    status = StartComponent(m_objComponentIdVector[index]);
                }
                if(!status)
                {
                    CLOG_FATAL("Sending SIGTERM to every process in process group. MANUAL intervention required.");
                    kill(0, SIGTERM);
                    return false;
                }
            }
        }

    }
    return true;
}


int AvailabilityManager::AssignIPAddresses(std::vector<std::string> &ipAddresses,
					    const char *interface,
					    bool assign)
{
    for(uint8_t i =0;i< ipAddresses.size();i++)
    {
        //get the routing prefix
        std::map<std::string, unsigned char>::iterator rtPrefixIter;
        rtPrefixIter = m_objVirtualIpAddressRoutingPrefixMap.find(ipAddresses[i]);
        if( rtPrefixIter != m_objVirtualIpAddressRoutingPrefixMap.end())
        {
            if(assign)
            {
                CLOG_INFO("Assigning VIP %s",(ipAddresses[i]).c_str());
            }
            else
            {
                CLOG_INFO("Unassigning VIP %s",(ipAddresses[i]).c_str());
            }
            AssignIpAddressToInterface(interface,
                    ipAddresses[i].c_str(),
                    rtPrefixIter->second,
                    assign);

        }

    }

    return 0;
}

//called by the BeActive function( only from the active avamgr)
uint32_t AvailabilityManager::CheckAndHandleCbCluster(bool isPeerNodeDown,bool isManagementInterfaceDown)
{
    uint32_t ret=CB_OK;
    static bool isReplicationDisabled=false;
    CLOG_DEBUG(">>>> AvailabilityManager::CheckAndHandleCbCluster >>>>");
    CLOG_DEBUG("isPeerNodeDown=%d m_objSelfCurrentStatus.selfCbNodeStatus=%d  m_objPeerCurrentStatus.peerCbNodeStatus=%d m_CmStatus.nodesInCluster=%d isManagementInterfaceDown=%d",
	isPeerNodeDown,m_objSelfCurrentStatus.selfCbNodeStatus,m_objPeerCurrentStatus.peerCbNodeStatus,m_CmStatus.nodesInCluster,isManagementInterfaceDown);

    /*if Peer node(avamgr) is down and local couchbase node is down, disable replication
    as we cannot switchover*/

    if((isPeerNodeDown && (m_objSelfCurrentStatus.selfCbNodeStatus != HEALTHY ))||
       (isPeerNodeDown && m_CmStatus.nodesInCluster == 0 && m_objPeerCurrentStatus.peerCbNodeStatus != HEALTHY)||
	((m_objSelfCurrentStatus.selfCbNodeStatus != HEALTHY )&&(m_objPeerCurrentStatus.peerCbNodeStatus != HEALTHY)))
    {
  	//Disable Replication
  	AvailabilityManager::stopReplication = true;
	CLOG_DEBUG("Disable Replication :isPeerNodeDown && m_objSelfCurrentStatus.selfCbNodeStatus == UNHEALTHY||isPeerNodeDown && m_CmStatus.nodesInCluster == 0");
        if(!isReplicationDisabled)
        {
            //Raise alarm saying Replication is disabled!
            m_avaMgrAlarm->RaiseSessionReplicationDisabledAlarm();
            isReplicationDisabled=true;

        }

    }

    //if local couchbase node is down and peer couchbase node is up, switchover
    else if((m_objSelfCurrentStatus.selfCbNodeStatus == UNHEALTHY ||m_CmStatus.status != CB_OK)&&
       m_objPeerCurrentStatus.peerCbNodeStatus == HEALTHY)
    {
        if(m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational)
        {
            CLOG_DEBUG("PeerEthernetInterfaceNotOperational and Local Couchbase is down, So disable Replication!");
            //Disable Replication
            AvailabilityManager::stopReplication = true;
            if(!isReplicationDisabled)
            {
                //Raise alarm saying Replication is disabled!
                m_avaMgrAlarm->RaiseSessionReplicationDisabledAlarm();
                isReplicationDisabled=true;

            }



        }
        else
        {
            CLOG_DEBUG("SwitchOver!: m_objSelfCurrentStatus.selfCbNodeStatus == UNHEALTHY && m_objPeerCurrentStatus.peerCbNodeStatus == HEALTHY");
            ret=!CB_OK;
            CLOG_DEBUG("<<<< AvailabilityManager::CheckAndHandleCbCluster <<<<");
            if(isReplicationDisabled)
            {
                //Raise alarm saying replication is restored!
                m_avaMgrAlarm->RaiseSessionReplicaionRestoredAlarm();
                isReplicationDisabled=false;
            }
        }
        return ret;

    }

    //if number of nodes in cluster is one and PeerCbNodeStatus is HEALTHY
    //this means that peer Couchbase node is back up
    //number of nodes in the cluster is got by getCbStatus

    else if (m_CmStatus.nodesInCluster == 1 &&
 	     m_objPeerCurrentStatus.peerCbNodeStatus == HEALTHY)
    {
	//Add the Peer Couchbase node back to the cluster
  	AvailabilityManager::stopReplication = false;
	CLOG_DEBUG("Add Peer Couchbase Node back m_CmStatus.nodesInCluster == 1 && m_objPeerCurrentStatus.peerCbNodeStatus == HEALTHY");
	isPeerNodeDown=false;
	ClusterManagementEvent event;
 	event.operation= CM_OP_ADD_NODE;
	m_clMgr->PutEvent(event);
        if(isReplicationDisabled)
        {
            //Raise alarm saying replication is restored!
            m_avaMgrAlarm->RaiseSessionReplicaionRestoredAlarm();
            isReplicationDisabled=false;
        }


    }

    // if Peer Couchbase node is down or the entire Peer Node is down
    // if we have already failed over the Peer node dont do it again
    else if(m_CmStatus.nodesInCluster !=1 &&
	     ((m_objPeerCurrentStatus.peerCbNodeStatus == UNHEALTHY ||
		isPeerNodeDown)||(isManagementInterfaceDown)) )
    {

  	AvailabilityManager::stopReplication = false;
	CLOG_DEBUG("No of nodes=%d, self status=%d, peer status=%d",m_CmStatus.nodesInCluster, m_objSelfCurrentStatus.selfCbNodeStatus,
		    m_objPeerCurrentStatus.peerCbNodeStatus);
	CLOG_DEBUG("Failover Peer couchbase node and rebalance");
	ClusterManagementEvent event;
	event.operation= CM_OP_REM_NODE;
	m_clMgr->PutEvent(event);
        if(isReplicationDisabled)
        {
            //Raise alarm saying replication is restored!
            m_avaMgrAlarm->RaiseSessionReplicaionRestoredAlarm();
            isReplicationDisabled=false;
        }

    }
    else
    {
  	AvailabilityManager::stopReplication = false;
	CLOG_DEBUG("No of nodes=%d, self status=%d, peer status=%d",m_CmStatus.nodesInCluster, m_objSelfCurrentStatus.selfCbNodeStatus,
		    m_objPeerCurrentStatus.peerCbNodeStatus);
	CLOG_DEBUG("All Available Cb Nodes are HEALTHY!");
        if(isReplicationDisabled)
        {
            //Raise alarm saying replication is restored!
            m_avaMgrAlarm->RaiseSessionReplicaionRestoredAlarm();
            isReplicationDisabled=false;
        }

    }

    CLOG_DEBUG("<<<< AvailabilityManager::CheckAndHandleCbCluster <<<<");
    return ret;
}

//This is a utility thread that can be used to execute blocking operations which cannot be performed on main/MeSS thread
//to avoid issues.
void AvailabilityManager::UtilityThread(void* arg)
{
    UtilityEvent event;


    while(m_utilityThreadrunning)
    {
        if(!(m_utility_q.WaitAndPop(event,TQ_WAIT_TIMEOUT)))
	{
	    //Timeout has happened, so just continue.
	    continue;
	}
        string vip;
        struct SendGARPEventData* evData = NULL;
        switch(event.ev_type)
        {
            case UTILITY_FLUSH_ARP_TABLES:
                CLOG_DEBUG("Received UTILITY_FLUSH_ARP_TABLES event.");
                LaunchProcessAndWait("/sbin/arptables","-F");
                break;
            case UTILITY_SENDGARP_VIP:

                evData = (struct SendGARPEventData*)event.data;

                CLOG_DEBUG("Received UTILITY_SENDGARP_VIP event with data Interface: %s,VIP : %s",
                        evData->intfName,evData->ipAddress);

                //Send GARP with target IP as the sender's IP Address so that Windows machine honour the GARP.
                SendGratuitousArp(evData->intfName,evData->ipAddress,true);
                //Send GARP with target IP as the Broadcast IP Address (255.255.255.255) so that Linux machines honour the GARP.
                SendGratuitousArp(evData->intfName,evData->ipAddress,false);

                free(evData->intfName);

                break;
            case UTILITY_BLOCK_ARP_VIP:

                vip = (char*)event.data;
                CLOG_DEBUG("Received UTILITY_BLOCK_ARP_VIP event with data VIP : %s"
                        ,vip.c_str());
                AddArpTableRulesForInterface(vip.c_str(),true,true);
                AddArpTableRulesForInterface(vip.c_str(),false,true);

                free(event.data);
                break;
            case UTILITY_UNBLOCK_ARP_VIP:

                vip = (char*)event.data;
                CLOG_DEBUG("Received UTILITY_UNBLOCK_ARP_VIP event with data VIP : %s"
                        ,vip.c_str());
                AddArpTableRulesForInterface(vip.c_str(),true,false);
                AddArpTableRulesForInterface(vip.c_str(),false,false);

                free(event.data);
                break;
            default:
                CLOG_ERROR("Utility Operation type %d not supported.",event.ev_type);
        }
    }
}

int AvailabilityManager::LaunchProcessAndWait(const char *processName, const char *processArgs, int64_t timeout)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::LaunchProcessAndWait() >>>>>>>>>>");
    pid_t   my_pid;
    int     status;

    if (0 == (my_pid = fork()))
    {

        //Unblock all signals
        //This is required for arping to work, else arping will not return and wait forever
        //after sending out one GARP because it uses SIGALARM to send subsquent GARP's
        //Hence unblocking all so that some other process doesn't face issues.
        SigSet sig, oldSig;
        sig.Fill();
        sig.SetMask(SIG_UNBLOCK, &sig, &oldSig);

        char args[ARGUMENT_LEN];
        const char *argv[ARGUMENT_COUNT];
        char *ptr = NULL;

        strncpy(args, processArgs, ARGUMENT_LEN);
        args[255] = 0;

        int count = 0;
        argv[count++] = processName;
        char *token = strtok_r(args, " ", &ptr);

        while (token) {
            argv[count++] = token;
            token = strtok_r(NULL, " ", &ptr);
        }

        argv[count] = NULL;
        if (-1 == execv(processName, (char*const*)argv)) {
            CLOG_ERROR("child process execve failed.");
            return -1;
        }
    }

    timeout = timeout/10000;

    while (0 == waitpid(my_pid , &status , WNOHANG)) {
        CLOG_DEBUG("Waiting for pid %d to finish.",my_pid);
        if ( --timeout < 0 ) {
            CLOG_ERROR("timeout");
            return -1;
        }
        usleep(10000);
    }

    CLOG_DEBUG("%s WEXITSTATUS %d WIFEXITED %d [status %d]\n",
            processName, WEXITSTATUS(status), WIFEXITED(status), status);

    if (1 != WIFEXITED(status) || 0 != WEXITSTATUS(status)) {
        CLOG_ERROR("%s failed",processName);
        //TODO: What to do here?
        return -1;
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::LaunchProcessAndWait() <<<<<<<<<<");
    return 0;
}
