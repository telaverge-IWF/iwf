/* 
 * File:   Pinger.h
 * Author: adey
 *
 * Created on June 28, 2012, 6:08 PM
 */

#ifndef PINGER_H
#define	PINGER_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "Component.h"
#include "MeSS.h"

#define OUT
#define IN

#define PNG_INVALID 2
#define PNG_SUCCESS 1
#define PNG_FAIL	0

#define ICMPHEADER  8
#define	DEFDATALEN	(64-ICMP_MINLEN)                        /* default data length */
#define	MAXIPLEN	60
#define	MAXICMPLEN	sizeof(ICMPPayloadData) + ICMPHEADER
#define	MAXPACKET	(65536 - 60 - ICMP_MINLEN)              /* maximum packet size */
#define PACKLEN     (DEFDATALEN + MAXIPLEN + MAXICMPLEN)



namespace eAccelero {

    class Pinger {
        public:
            int16_t m_iPingFd;
            bool m_bSendFirstPingRequest;
            uint16_t m_uiIcmpSeqNumber;
            int16_t m_iPingFailedCounter;
            AvailabilityManager *m_AvaMgr;
            std::string m_sTarget;
            std::string m_sSource;
            uint16_t m_uiPingPeriodicityTimer;
            uint16_t m_uiAddrFamily;

            Pinger();

            Pinger(AvailabilityManager *m_AvaMgr):m_iPingFd(-1),
            m_bSendFirstPingRequest(0),
            m_uiIcmpSeqNumber(1),
            m_iPingFailedCounter(0),
            m_AvaMgr(m_AvaMgr)
        {
            m_sTarget = m_AvaMgr->GetArbitratorIpAddress();
            m_uiPingPeriodicityTimer = m_AvaMgr->GetPingPeriodicityForArbitrator();
            m_uiAddrFamily = AF_INET;
        }

            ~Pinger();

            virtual bool PingNearHopGateway(IN const char* sTarget, IN const char* sSource, 
                    IN uint32_t iTimeMiliSec, IN int addrFamily);

            int PingOnIcmpSocketEvent(SockEvent &event);

            int PingOnPeriodicTimerExpiry(TimerEvent &event);

            bool PingPeerOverICMP(IN const char* sTarget,IN const char* sSource,IN uint32_t iTimeMiliSec,int16_t iPingFd);

            bool PingBindToAddress(IN const char* sTarget, IN const char* sSource, IN int addrFamily);

        private:

            Pinger(Pinger const&);

            void operator=(Pinger const&);

            int PingGetRandomNum(IN int iRangeLowest, IN int iRangeHighest);

            bool PingGetHostNameInfo(IN const char* sTarget, OUT struct sockaddr_in *pToAddress, OUT char *sHostName);

            uint16_t PingCkSum(IN uint16_t *addr, IN unsigned len);

            void PingSetIcmpPacket(OUT u_char *rawOutPacket, OUT uint16_t m_uiIcmpSeqNumber);

            void PingSetTimerValue(IN uint32_t iTimeMiliSec, OUT struct timeval *pTimerValue);

            bool PingCheckICMPPart(IN u_char *rawOutPacket, IN uint16_t m_uiIcmpSeqNumber);

            bool checkICMPPayloadLength(IN u_char *rawOutPacket, IN int iRecvPackLen);

            bool PingCheckSrcIp(IN u_char *rawOutPacket, IN const char *sSource);

            bool PingCheckDestIp(IN u_char *rawOutPacket, IN const char *sTarget);

            bool PingCheckICMPUserData(IN u_char *rawOutPacket);

            bool PingSetPeerNodeStatus(IN u_char *rawOutPacket);

            void PingResetIfSplitBrainIsResolved();

            int PingResetAllValues();

    };

} // namespace eAccelero


#endif	/* PINGER_H */

