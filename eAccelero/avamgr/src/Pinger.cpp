
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "AvailabilityManager.h"
#include "Pinger.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <error.h>

#define DIAMETRIQ_PING_SIGNATURE_STRING "DIAMETRIQ_PING"

using namespace eAccelero;

namespace eAccelero {


    Pinger::Pinger() {

    }

    Pinger::~Pinger() {

    }

    bool Pinger::PingPeerOverICMP(IN const char* sTarget,IN const char* sSource,IN uint32_t iTimeMiliSec,int16_t iPingFd) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingPeerOverICMP() >>>>>>>>>>");

        int iSendRet;
        u_char rawOutPacket[MAXPACKET];
        struct sockaddr_in toAddress;

        memset(rawOutPacket, 0, sizeof (rawOutPacket));
        memset((void *) &toAddress, 0, sizeof (struct sockaddr_in));
        /* Sequence Number for the ICMP Ping Request*/
        m_uiIcmpSeqNumber++;

        /* Setting ICMP Ping Request Parameters*/
        PingSetIcmpPacket(rawOutPacket, m_uiIcmpSeqNumber);

        /* Setting toAddress Structure*/
        if (PingGetHostNameInfo(sTarget, &toAddress, NULL) == PNG_FAIL) {
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingPeerOverICMP() <<<<<<<<<<");
            return PNG_FAIL;
        }

        /* Sending Ping Request*/
        iSendRet = sendto(m_iPingFd, (char *) rawOutPacket,
                PACKLEN, 0,
                (struct sockaddr*) &toAddress,
                (socklen_t)sizeof (struct sockaddr_in));

        if (iSendRet < 0 || iSendRet != (PACKLEN)) {
            if (iSendRet < 0)
            {
                CLOG_ERROR("Could not send ICMP ping errno = %d",errno);
                CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingPeerOverICMP() <<<<<<<<<<");
                return PNG_FAIL;
            }
        }

        /* Setting the flag to indicate the Ping Request is already send
         * When we get the Ping Request from the Peer, If this flag is
         * not set immediately we will send back the ping request.*/
        m_bSendFirstPingRequest = 1;

        /* Registering the timer, When this timer expires we will send the
         * ping request once again... We will try like this for CfgNumConsecutivePingAckRcvFailuresFromPeer
         * number of times, if we are still missing the ping from peer, then
         * peer state is changed to INDETERMINATE*/
        m_AvaMgr->RegisterTimer(iTimeMiliSec);

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingPeerOverICMP() <<<<<<<<<<");
        return PNG_SUCCESS;

    }

    bool Pinger::PingBindToAddress(IN const char* sTarget, IN const char* sSource, IN int addrFamily) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingBindToAddress() >>>>>>>>>>");

        if (addrFamily == AF_INET) {
            /* Creating the raw socket... */
            m_iPingFd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
        }  else {
            CLOG_ERROR("IP address is not IPv4. IPv6 is NOT currently supported");

            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingBindToAddress() <<<<<<<<<<");
            return PNG_FAIL;
        }

        if (m_iPingFd < 0) {
            CLOG_ERROR("Could not create socket, errno = %d", errno);

            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingBindToAddress() <<<<<<<<<<");
            return PNG_FAIL;
        }

        struct sockaddr_in sourceAddress;

        memset((char *) &sourceAddress, 0, sizeof (sourceAddress));

        if (addrFamily == AF_INET) {
            sourceAddress.sin_family = AF_INET;
        } else {
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingBindToAddress() <<<<<<<<<<");
            return PNG_FAIL;
        }

        sourceAddress.sin_port = htons(0);

        if (sSource != NULL) {
            sourceAddress.sin_addr.s_addr = inet_addr(sSource);
        } else {
            sourceAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            string tmp = inet_ntoa(sourceAddress.sin_addr);
            m_sSource = tmp;
        }

        /* Binding to the socket using m_iPingFd*/
        if (bind(m_iPingFd, (struct sockaddr *) &sourceAddress, sizeof (sourceAddress)) == -1) {
            CLOG_ERROR("Could not bind specified source address %s to socket for ICMP ping", sSource);
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingBindToAddress() <<<<<<<<<<");
            return PNG_FAIL;
        } else {
            if (sSource != NULL) {
                CLOG_NOTICE("Bound specified source address %s to socket for ICMP ping", sourceAddress);
            } else {
                CLOG_NOTICE("Bound INADDR_ANY to socket for ICMP ping");
            }
        }

        /* Checking if the IcmpSocket Hander is already Register...
         * if Socket Handler is already register, we are removing the old handler
         * and setting the handler-id to zero
         */
        if(m_AvaMgr->GetIcmpSocketHandlerId())
        {
            m_AvaMgr->UnRegisterEvent(m_AvaMgr->GetIcmpSocketHandlerId(),SOCK_EVENT_TYPE);
            m_AvaMgr->SetIcmpSocketHandlerId(0);
        }

        /* Registering the PingFd to the Epoll*/
        m_AvaMgr->RegisterPinger(m_iPingFd);
        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingBindToAddress() <<<<<<<<<<");
        return PNG_SUCCESS;
    }

    bool Pinger::PingNearHopGateway(IN const char* sTarget, IN const char* sSource,
            IN uint32_t iTimeMiliSec,
            IN int addrFamily) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingNearHopGateway() >>>>>>>>>>");
        u_char rawPacket[PACKLEN];

        m_sTarget = sTarget;
        if(sSource != NULL)
            m_sSource = sSource;

        m_uiPingPeriodicityTimer = iTimeMiliSec;
        m_uiAddrFamily = addrFamily;

        memset(rawPacket, 0, sizeof (rawPacket));

        /* if PingFd is set to -1, we will create the Fd again
         * otherwise we will use the existing PingFd for sending the
         * ping request*/
        if (m_iPingFd == -1) {
            if(!PingBindToAddress(sTarget,sSource,addrFamily)) {
                CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingNearHopGateway() <<<<<<<<<<");
                return PNG_FAIL;
            }

        }

        /* Sending the Ping request to the Target*/
        if (PingPeerOverICMP(sTarget,sSource,iTimeMiliSec,m_iPingFd) == PNG_FAIL) {
            CLOG_ERROR("Ping Failed Returning False");
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingNearHopGateway() <<<<<<<<<<");
            return PNG_FAIL;
        }

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingNearHopGateway() <<<<<<<<<<");
        return PNG_SUCCESS;
    }

    uint16_t Pinger::PingCkSum(IN uint16_t *addr, IN unsigned len) {
        uint16_t answer = 0;
        /*
         * Our algorithm is simple, using a 32 bit accumulator (sum), we add
         * sequential 16 bit words to it, and at the end, fold back all the
         * carry bits from the top 16 bits into the lower 16 bits.
         */
        uint32_t sum = 0;
        while (len > 1) {
            sum += *addr++;
            len -= 2;
        }

        // mop up an odd byte, if necessary
        if (len == 1) {
            *(unsigned char *) &answer = *(unsigned char *) addr;
            sum += answer;
        }

        // add back carry outs from top 16 bits to low 16 bits
        sum = (sum >> 16) + (sum & 0xffff); // add high 16 to low 16
        sum += (sum >> 16); // add carry
        answer = ~sum; // truncate to 16 bits
        return answer;
    }

    void Pinger::PingSetIcmpPacket(OUT u_char *rawOutPacket, OUT uint16_t iIcmpSeqNumber) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingSetIcmpPacket() >>>>>>>>>>");
        struct icmp *pIcmpPacket;
        int iIcmpPackLen;
        ICMPPayloadData *pPayloadData;

        /* Setting values for ICMP Ping Request */
        pIcmpPacket = (struct icmp *) rawOutPacket;
        memset(pIcmpPacket, 0, sizeof(struct icmp));
        pIcmpPacket->icmp_type = ICMP_ECHO;
        pIcmpPacket->icmp_code = 0;
        pIcmpPacket->icmp_cksum = 0;
        pIcmpPacket->icmp_seq = iIcmpSeqNumber; /* seq and id must be reflected */
        pIcmpPacket->icmp_id = getpid();

        /* Setting User Data ICMP Ping Request */
        pPayloadData = (ICMPPayloadData *)&rawOutPacket[ICMPHEADER];

        pPayloadData->peerData.selfInstanceId = m_AvaMgr->GetSelfInstanceId();
        pPayloadData->peerData.selfInstanceAvailabilityStatus = m_AvaMgr->GetSelfCurrentStatus();
        CLOG_DEBUG("selfInstance status = %d",pPayloadData->peerData.selfInstanceAvailabilityStatus);

        memset(pPayloadData->peerData.selfHostname, 0, HOSTNAME_LEN);
        strncpy(pPayloadData->peerData.selfHostname, m_AvaMgr->GetSelfHostname(), HOSTNAME_LEN);
        CLOG_DEBUG("selfHostname = %s",pPayloadData->peerData.selfHostname);

        pPayloadData->peerData.selfLastGoActiveTime = m_AvaMgr->GetSelfLastGoActiveTime();
        pPayloadData->peerData.selfIsAnyEthernetInterfaceNotOperational = m_AvaMgr->GetSelfEthernetInterfaceNotOperational();

	pPayloadData->peerData.selfCbNodeStatus =  m_AvaMgr->GetSelfCbNodeStatus();

        memset(pPayloadData->signatureBuff,0,strlen(DIAMETRIQ_PING_SIGNATURE_STRING)+1);
        strncpy(pPayloadData->signatureBuff,DIAMETRIQ_PING_SIGNATURE_STRING,15);

        iIcmpPackLen = DEFDATALEN + ICMP_MINLEN + sizeof(ICMPPayloadData);
        /* Setting CheckSum Value*/
        pIcmpPacket->icmp_cksum = PingCkSum((unsigned short *) pIcmpPacket, iIcmpPackLen);

    }

    bool Pinger::PingGetHostNameInfo(IN const char* sTarget, OUT struct sockaddr_in *pToAddress, OUT char* sHostName) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingGetHostNameInfo() >>>>>>>>>>");
        struct hostent *pHostent;

        /* Setting sockaddr_in */
        pToAddress->sin_family = AF_INET;
        pToAddress->sin_addr.s_addr = inet_addr(sTarget);
        if (pToAddress->sin_addr.s_addr != (u_int) - 1) {
            if(sHostName != NULL)
                strcpy(sHostName, sTarget);
        } else {
            pHostent = gethostbyname(sTarget);
            if (!pHostent) {
                CLOG_ERROR("Unknown host %s", sTarget);
                CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingGetHostNameInfo() <<<<<<<<<<");
                return PNG_FAIL;
            }

            pToAddress->sin_family = pHostent->h_addrtype;
            bcopy(pHostent->h_addr, (caddr_t) & pToAddress->sin_addr, pHostent->h_length);
            /* Setting hostname */
            if(sHostName != NULL)
                strncpy(sHostName, pHostent->h_name, sizeof (sHostName) - 1);
        }

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingGetHostNameInfo() <<<<<<<<<<");
        return PNG_SUCCESS;
    }

    void Pinger::PingSetTimerValue(IN uint32_t iTimeMiliSec, OUT struct timeval *pTimerValue) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingSetTimerValue() >>>>>>>>>>");
        uint32_t iSecond;

        suseconds_t microSecond;

        /* Setting seconds*/
        iSecond = iTimeMiliSec / 1000;
        pTimerValue->tv_sec = iSecond;

        /* Setting milliseconds*/
        microSecond = iTimeMiliSec % 1000;
        pTimerValue->tv_usec = microSecond * 1000;

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingSetTimerValue() <<<<<<<<<<");
    }

    bool Pinger::checkICMPPayloadLength(IN u_char *rawOutPacket, IN int iRecvPackLen) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::checkICMPPayloadLength() >>>>>>>>>>");
        int iHeaderLength;
        int iIcmpUserDataLength;
        struct sockaddr_in toAddress;
        char sHostNameBuf[MAXHOSTNAMELEN];

        iHeaderLength = sizeof ( struct ip);
        iIcmpUserDataLength = sizeof(ICMPPayloadData);


        /* Checking the Length of the packet
         * Making sure that it has minimum ping request size*/

        if (iRecvPackLen < (iHeaderLength + ICMP_MINLEN + iIcmpUserDataLength)) {
            /* Get the hostname...*/
            if (PingGetHostNameInfo(m_sTarget.c_str(), &toAddress, sHostNameBuf) == PNG_FAIL) {
                CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::checkICMPPayloadLength() <<<<<<<<<<");
                return PNG_FAIL;
            }

            CLOG_WARNING("Packet too short (%d bytes) from %s", iRecvPackLen, sHostNameBuf);
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::checkICMPPayloadLength() <<<<<<<<<<");
            return PNG_FAIL;
        }

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::checkICMPPayloadLength() <<<<<<<<<<");
        return PNG_SUCCESS;
    }

    bool Pinger::PingCheckSrcIp(IN u_char *rawOutPacket, IN const char *sSource) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingCheckSrcIp() >>>>>>>>>>");
        struct ip  *pIpPart;
        struct in_addr ipAddr;

        inet_aton(sSource,&ipAddr);

        /* Checking source address*/
        pIpPart = (struct ip *) rawOutPacket;
        if(pIpPart->ip_src.s_addr  == ipAddr.s_addr)
        {
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckSrcIp() <<<<<<<<<<");
            return PNG_SUCCESS;
        }
        else
        {
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckSrcIp() <<<<<<<<<<");
            return PNG_FAIL;
        }

    }

    bool Pinger::PingCheckDestIp(IN u_char *rawOutPacket, IN const char *sTarget) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingCheckDestIp() >>>>>>>>>>");
        struct ip  *pIpPart;
        struct in_addr ipAddr;

        inet_aton(sTarget,&ipAddr);

        /* Checking destination Address*/
        pIpPart = (struct ip *) rawOutPacket;
        if(pIpPart->ip_dst.s_addr  == ipAddr.s_addr)
        {
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckDestIp() <<<<<<<<<<");
            return PNG_SUCCESS;
        }
        else
        {
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckDestIp() <<<<<<<<<<");
            return PNG_FAIL;
        }

    }

    bool Pinger::PingCheckICMPUserData(IN u_char *rawOutPacket) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingCheckICMPUserData() >>>>>>>>>>");

        ICMPPayloadData *pPayloadData;
        int iHeaderLength;

        iHeaderLength = sizeof ( struct ip);

        CLOG_DEBUG("HeaderLength = %d",iHeaderLength);
        pPayloadData = (ICMPPayloadData*)&rawOutPacket[iHeaderLength + ICMPHEADER];


        if(strcmp(pPayloadData->peerData.selfHostname,m_AvaMgr->GetSelfHostname()) == 0) {

            CLOG_DEBUG("Received ICMP Ping Echo Request/Reply from the same node. Hence, ignoring...");
            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingCheckICMPUserData() <<<<<<<<<<");
            return PNG_INVALID;
        }

        if(strcmp(pPayloadData->signatureBuff,DIAMETRIQ_PING_SIGNATURE_STRING) != 0) {
            CLOG_WARNING("Signature is not correct in Ping request");
            CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckICMPUserData() <<<<<<<<<<");
                return PNG_INVALID;
            }

        /* Setting peer node status.... from the UserData in the ping Request...*/
        if (PingSetPeerNodeStatus(rawOutPacket) != PNG_SUCCESS) {

            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingCheckICMPUserData() <<<<<<<<<<");
            return PNG_INVALID;
        }

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckICMPUserData() <<<<<<<<<<");
        return PNG_SUCCESS;

    }

    bool Pinger::PingSetPeerNodeStatus(IN u_char *rawOutPacket) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingSetPeerNodeStatus() >>>>>>>>>>");
        ICMPPayloadData *pPayloadData;
        int iHeaderLength;
        struct timeval tmVal;

        iHeaderLength = sizeof ( struct ip);
        pPayloadData = (ICMPPayloadData*)&rawOutPacket[iHeaderLength + ICMPHEADER];

        /* Setting LastPeer Ack time*/
        gettimeofday(&tmVal, NULL);
        m_AvaMgr->SetLastPeerAckTime(tmVal);

        /* Setting Instance Id */
        m_AvaMgr->SetPeerInstanceId(pPayloadData->peerData.selfInstanceId);
        CLOG_DEBUG("Icmp Ping : selfInstanceId %d",pPayloadData->peerData.selfInstanceId);

        /* Setting LastGoActive Time */
        m_AvaMgr->SetPeerLastGoActiveTime(pPayloadData->peerData.selfLastGoActiveTime);

        /* Setting IsAnyEthernetInterfaceNotOperational */
        m_AvaMgr->SetPeerEthernetInterfaceNotOperational(pPayloadData->peerData.selfIsAnyEthernetInterfaceNotOperational);

        /* Setting Peer Node status*/
        m_AvaMgr->SetPeerCurrentStatus((eAccelero::InstanceAvailabilityStatus)pPayloadData->peerData.selfInstanceAvailabilityStatus);
        CLOG_DEBUG("Icmp Ping : PeerStatus %d",pPayloadData->peerData.selfInstanceAvailabilityStatus);

        /* Setting Peer Hostname*/
        m_AvaMgr->SetPeerHostname(pPayloadData->peerData.selfHostname);
        CLOG_DEBUG("Icmp Ping : Hostname %s",pPayloadData->peerData.selfHostname);


	/*Setting Peer Cb Node Status*/
	m_AvaMgr->SetPeerCbNodeStatus(pPayloadData->peerData.selfCbNodeStatus);
	CLOG_DEBUG("Icmp Ping : Peer Cb Node Status %d",pPayloadData->peerData.selfCbNodeStatus);


        /* Resetting waiting for icmp ping parameter
         *
         * During standby state, when Peer state goes to INDETERMINATE
         * when each recurrsive timer expires, m_uiWaitCountForIcmpPingFromPeer value
         * is incremented, if this value reaches MAX_WAIT_COUNT_FOR_ICMP_PING_IN_INDETERMINA
         * avamgr will go to active state.
         *
         *
         * If avamgr receives Ping from Peer, then it will remain in standby state.
         * For this we are resetting the m_uiWaitCountForIcmpPingFromPeer value to zero
         * each time we get the ping from peer when avamgr is in standby state*/
        m_AvaMgr->ResetWaitingForIcmpPingFromPeer();

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingSetPeerNodeStatus() <<<<<<<<<<");
        return PNG_SUCCESS;
    }

    /* This function is not used after introduction
     * of split brain */
    bool Pinger::PingCheckICMPPart(IN u_char *rawOutPacket, IN uint16_t iIcmpSeqNumber) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingCheckICMPPart() >>>>>>>>>>");
        struct icmp *pIcmpPacket;
        int iHeaderLength;
        int iSelectReturnue = PNG_SUCCESS;

        iHeaderLength = sizeof ( struct ip);
        pIcmpPacket = (struct icmp *) (rawOutPacket + iHeaderLength);
        if (pIcmpPacket->icmp_type == ICMP_ECHOREPLY) {
            if (pIcmpPacket->icmp_seq != iIcmpSeqNumber) {
                iSelectReturnue = PNG_FAIL;
            }
            if (pIcmpPacket->icmp_id != getpid()) {
                iSelectReturnue = PNG_FAIL;
            }
        } else {
            iSelectReturnue = PNG_FAIL;
        }

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingCheckICMPPart() <<<<<<<<<<");
        return iSelectReturnue;
    }

    /* This function is not used after introduction
     * of split brain */
    int Pinger::PingGetRandomNum(int iRangeLowest, int iRangeHighest) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingGetRandomNum() >>>>>>>>>>");
        int iNumber;
        int iRand;

        unsigned int uiCount;
        static unsigned int iseed;

        uiCount = (unsigned int) time(NULL);

        iseed++;
        uiCount = uiCount + iseed;

        iNumber = rand_r(&uiCount);

        if (iRangeLowest - iRangeHighest > 0) {
            iRand = iNumber % (iRangeLowest - iRangeHighest + 1);
        } else {
            iRand = iNumber % (iRangeHighest - iRangeLowest + 1);
        }

        iRand = iRangeLowest + iRand;

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingGetRandomNum() <<<<<<<<<<");
        return iRand;
    }

    /* This functions handle ping Timer Expiry Event */
    int Pinger::PingOnPeriodicTimerExpiry(TimerEvent &event) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingOnPeriodicTimerExpiry() >>>>>>>>>>");
        m_iPingFailedCounter++;

        /*  if the m_iPingFailedCounter is less that the configured retry value (m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer),
         *  then increment  value and send the ping request to the peer again and start the pingPeriodicity time again*/
        if(m_iPingFailedCounter <= m_AvaMgr->GetCfgNumConsecutivePingAckRcvFailuresFromPeer())
        {
            /* Timer is started in side the PingPeerOverICMP */
            PingPeerOverICMP(m_sTarget.c_str(),m_sSource.c_str(),m_uiPingPeriodicityTimer,m_iPingFd);
        }
        else
        {
            /* if the iPingFailedCounter exceeded the maxmimum configured value
             * 1) set the peer status as INDETERMINATE
             * 2) reseting the periodic timer id*/

            m_AvaMgr->SetPeerCurrentStatus(INDETERMINATE);
            m_AvaMgr->SetPeriodicTimerId(0);
        }

        /* Checking if the split Brain is resolved....
         * Reset all the member variables if the split brain issue is resolved*/
        PingResetIfSplitBrainIsResolved();
        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingOnPeriodicTimerExpiry() <<<<<<<<<<");
        return 0;
    }

    /* This functions handle Socket Event for the ICMP fd */
    int Pinger::PingOnIcmpSocketEvent(SockEvent &event) {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingOnIcmpSocketEvent() >>>>>>>>>>");

        int iRecvReturn, iFromLen;
        u_char rawPacket[PACKLEN];
        struct sockaddr_in fromAddress;

        memset((void *) &fromAddress, 0, sizeof (struct sockaddr_in));
        memset(rawPacket, 0, sizeof (rawPacket));

        /* This condition should not occur...*/
        if(event.FD() != m_iPingFd)
        {
            CLOG_DEBUG("FD from the event is different from m_iPingFd, event.FD = %d m_iPingFd = %d",event.FD(),m_iPingFd);
            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");
            return 0;
        }

        iFromLen = sizeof (sockaddr_in);
        if(m_iPingFd != -1) {
            /* Receiving the data from the raw socket*/
            if ((iRecvReturn = recvfrom(m_iPingFd, (char *) rawPacket, PACKLEN, 0, (struct sockaddr *) &fromAddress, (socklen_t*) & iFromLen)) < 0) {
                CLOG_ERROR("recvfrom() returned = %d error = %d",iRecvReturn,errno);


                /* if error occured in reciving the data
                 * 1) close the raw socket fd
                 * 2) create the socket again.. and register in epoll*/

                close(m_iPingFd);
                if(!PingBindToAddress(m_sTarget.c_str(),m_sSource.c_str(),m_uiAddrFamily)) {
                    CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");
                    return PNG_FAIL;
                }

                CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");

                return PNG_FAIL;
            }else{
                CLOG_DEBUG("recvfrom returns %d",iRecvReturn);
            }
        }else {

            CLOG_DEBUG("m_iPingFd == -1");
            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");
            return PNG_FAIL;

        }


        /* Check IP Header....*/
        if (checkICMPPayloadLength(rawPacket, iRecvReturn) == PNG_FAIL) {

            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");
            return PNG_FAIL;
        }

        /* Checking the source IP,,,*/
        if (PingCheckSrcIp(rawPacket,m_sTarget.c_str()) == PNG_FAIL) {

            /* Checking if the split brain issue is resolved
             * Reset all the member variables if the split brain issue is resolved*/
            PingResetIfSplitBrainIsResolved();
            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");
            return PNG_FAIL;
        }


        /* Checking the UserData in the ICMP Ping.... req/resp */
        if (PingCheckICMPUserData(rawPacket) == PNG_INVALID) {

            /* Checking if the split brain issue is resolved
             * Reset all the member variables if the split brain issue is resolved*/
            PingResetIfSplitBrainIsResolved();
            CLOG_DEBUG(" Either ICMP Ping Echo Request/Reply received from self, or the ICMP Ping Echo Request is not from Availability Manager Pinger.");
            CLOG_DEBUG("<<<<<<<<<< Exiting Pinger::PingOnIcmpSocketEvent() <<<<<<<<<<");
            return PNG_FAIL;
        }


        /* Checking if the Periodic Timer is register....
         * if timer is register UnRegister the timer event....
         * And resetting the timer value.. */
        if(m_AvaMgr->GetPeriodicTimerId())
        {
            m_AvaMgr->UnRegisterEvent(m_AvaMgr->GetPeriodicTimerId(),TIMER_EVENT_TYPE);
            m_AvaMgr->SetPeriodicTimerId(0);
        }

        /* If FirstPingRequest value is not set..
         * Sending the Ping Request to the peer with the avamgr current state
         * */
        if(!m_bSendFirstPingRequest){
            if (PingPeerOverICMP(m_sTarget.c_str(),m_sSource.c_str(),m_uiPingPeriodicityTimer,m_iPingFd) == PNG_FAIL) {
                CLOG_ERROR("Ping Failed Returning False");
            }
        }

        /* Checking if the split brain issue is resolved...
         * Reset all the member variables if the split brain issue is resolved*/
        PingResetIfSplitBrainIsResolved();

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingOnIcmpSocketEvent() <<<<<<<<<<");
        return PNG_SUCCESS;
    }

    void Pinger::PingResetIfSplitBrainIsResolved() {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingResetIfSplitBrainIsResolved() >>>>>>>>>>");

        CLOG_DEBUG("Peer State is %d ",m_AvaMgr->GetPeerCurrentStatus());

        /* Checking if the peer current state is not INDETERMINATE...
         * If it is not INDETERMINATE... Then next recurssive timer execution..
         * split brain issue will be resolved... */
        if(m_AvaMgr->GetPeerCurrentStatus() != INDETERMINATE)
        {
            CLOG_DEBUG("Peer State is  %d , Reseting all values",m_AvaMgr->GetPeerCurrentStatus());
            PingResetAllValues();
        }

    }

    /* This function will reset the all values to intial state*/
    int Pinger::PingResetAllValues() {
        CLOG_DEBUG(">>>>>>>>>> Entered Pinger::PingResetAllValues() >>>>>>>>>>");
        if(m_iPingFd != -1)
        {
            /* Checking if the socket id is Registered
             * If socket id is registered...
             * Ungregister the event and reset the socket event id*/
            if(m_AvaMgr->GetIcmpSocketHandlerId())
            {
                m_AvaMgr->UnRegisterEvent(m_AvaMgr->GetIcmpSocketHandlerId(),SOCK_EVENT_TYPE);
                m_AvaMgr->SetIcmpSocketHandlerId(0);
            }
            /* closing the raw socket...*/
            close(m_iPingFd);
        }

        /* Checking if the timer event is registered
         * If timer event ois registered....
         * Unregister the event and reset the timer event id*/
        if(m_AvaMgr->GetPeriodicTimerId())
        {
            m_AvaMgr->UnRegisterEvent(m_AvaMgr->GetPeriodicTimerId(),TIMER_EVENT_TYPE);
            m_AvaMgr->SetPeriodicTimerId(0);
        }

        /* Resetting the member variables*/
        m_iPingFd = -1;
        m_bSendFirstPingRequest = 0;
        m_uiIcmpSeqNumber = 1;
        m_iPingFailedCounter = 1;

        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::PingResetAllValues() <<<<<<<<<<");
        return 0;
    }

}

