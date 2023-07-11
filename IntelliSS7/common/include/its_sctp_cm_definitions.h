/*********************************-*-H-*-**********************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 * LOG: $Log: its_sctp_cm_definitions.h,v $
 * LOG: Revision 1.2  2008/06/23 06:59:55  skatta
 * LOG: Added compilation check for linux
 * LOG:
 * LOG: Revision 1.1  2008/06/20 11:35:23  mpatri
 * LOG: Accelero CGI Phase I: Support for SCTP Configuration APIs
 * LOG:
 * LOG:
 * LOG:
 *
 * ID: $Id: its_sctp_cm_definitions.h,v 1.2 2008/06/23 06:59:55 skatta Exp $
 ****************************************************************************/

#ident "$Id: its_sctp_cm_definitions.h,v 1.2 2008/06/23 06:59:55 skatta Exp $"


#ifndef _ITS_SCTP_CM_DEFINITIONS_H_
#define _ITS_SCTP_CM_DEFINITIONS_H_


/**************************************
 * Include files
 *************************************/
//#include <sctp.h>
#include <its_sctp.h>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
//#include <netinet/in.h>
#include <netinet/sctp.h>
#if defined linux
#include <linux/types.h>
#endif
#include <stdlib.h>


using namespace std;

#define YES 1
#define NO  0
#define ASSOC_MAX_STR_LEN          32
#define ASSOC_REMOTE_NAME_STRING   "-Virtual-1"
#define ASSOC_DFLT_IN_STREAM       32
#define ASSOC_DFLT_OUT_STREAM      32
#define ASSOC_DFLT_MAX_INIT        5
#define ITS_EMALLOCFAIL            -200
#define ITS_ENOASSOCIATION         -201
#define ITS_ESCTPCMINITIALIZEFAIL  -202

#define ITS_SCTPCM_EVENT_RCV_THREAD_CONTEXT 25001

/** SCTPCM_ASSOC_ID handles the implementation
 dependency of sctp_assoc_t type ( integer or void *) **/

#ifdef _SCTP_13_ABOVE_KERNEL_
    #define SCTPCM_ASSOC_ID(x) x
#else
    #define SCTPCM_ASSOC_ID(x) atoi((char*)x)
#endif


/**************************************
 * Enum definitions
 *************************************/
typedef enum
{
    SCTP_ENDPOINT_CLIENT,
    SCTP_ENDPOINT_SERVER
}SCTP_ENDPOINT_TYPE;


/**************************************
 * Data structures
 *************************************/
/* 
   This structure defines a list for entries that collide for
   same hash key in the SCTPAssociationHashTable
*/
 
typedef struct _SCTP_Association_Entry_
{
    sctp_assoc_t associationID;
    SCTPAssociation* ptrToSCTPAssociationObj;
    struct _SCTP_Association_Entry_* next;    
}
SCTPAssociationEntry;

typedef struct
{
    SCTPAssociationEntry* entry; /* Ptr to list of colliding entries */    
}
SCTPAssociationHashTable;

/* The SCTP hash is a simple hash. It just masks off the MSB 16 bits for 
   the give key. SCTP association Id will be given as the key.
   The hashed value is just the LSB 16 bits. We currently have requirement
   to support upto 64K SCTP associations. Assuming that the association IDs
   are incremented sequentially by the kernel SCTP, at most we have the
   association IDs going till 64K which is well within the limit of 
   16 bits. Hence hashing the association Id to its 16 bit equivalent will
   mostly give a unique hash 
*/
#define SCTP_HASH(x) ((x) & 0x0000FFFF)

typedef struct
{
    sctp_assoc_t   associationID;
    ITS_SCTP_STATE state;
}SCTPAssociationProperties;

typedef struct    
{
    std::string              primaryIPAddress;
    std::vector<std::string> secondaryIPAddress;
    ITS_USHORT               port;
    SCTP_ENDPOINT_TYPE       type;
    
    /*** added by mpatri  --starts-- ***/       
    bool           hasLocalIP;
    bool           hasLocalPort;             
    std::string    name;
    std::string    family;

    ITS_UINT       minRetransmitTimeout; /*srto_min in SCTP_RTOINFO option*/
    ITS_UINT       maxRetransmitTimeout; /*srto_max in SCTP_RTOINFO option*/
    ITS_USHORT     pathMaxRetransmit;    /*spp_pathmaxrxt in SCTP_PEER_ADDR_PARAMS option*/
    ITS_USHORT     assocMaxRetransmit;   /*sasoc_asocmaxrxt in SCTP_ASSOCINFO option*/
    ITS_USHORT     maxInboundStreams;    /*sinit_max_instreams in SCTP_INIT option*/
    ITS_USHORT     numOutboundStreams;   /*sinit_num_outstreams in SCTP_INIT option*/
    ITS_USHORT     initMaxAttempts;      /*sinit_max_attempts in SCTP_INIT option*/
    ITS_UINT       SACKDelay;            /*sack_delay in SCTP_DELAYED_SACK option*/
    ITS_UINT       hbInterval;           /*spp_hbinterval in SCTP_PEER_ADDR_PARAMS option*/
    ITS_UINT       txBufferSize;         /*SO_SNDBUF in SOL_SOCKET option*/
    ITS_UINT       rxBufferSize;         /*SO_RCVBUF in SOL_SOCKET option*/
    char           *cookieLife;
    char           *hbOn;
    char           *initTimeOut;
    char           *sendTimeOut;
    char           *recvTimeOut;
    char           *hbTimeOut;
    char           *shutdownTimeOut;
    char           *pmtuTimeOut;	

    /*** added by mpatri  --ends-- ***/
}SCTPEndPointProperties;

#define CONFIG_MALLOC malloc

#endif /*#ifndef   _ITS_SCTP_CM_DEFINITIONS_H_*/


