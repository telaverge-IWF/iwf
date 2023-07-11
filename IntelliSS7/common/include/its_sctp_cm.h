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
 * LOG: $Log: its_sctp_cm.h,v $
 * LOG: Revision 1.1  2008/06/20 11:35:14  mpatri
 * LOG: Accelero CGI Phase I: Support for SCTP Configuration APIs
 * LOG:
 * LOG:
 * LOG:
 *
 * ID: $Id: its_sctp_cm.h,v 1.1 2008/06/20 11:35:14 mpatri Exp $
 ****************************************************************************/

#ident "$Id: its_sctp_cm.h,v 1.1 2008/06/20 11:35:14 mpatri Exp $"


#ifndef _ITS_SCTP_CM_H_
#define _ITS_SCTP_CM_H_

/******************************
 * Include Files
 *****************************/
#include <its_sctp_trans.h>
#include <its_sctp_event_interface.h>
#include <its_sctp_cm_definitions.h>
//#include <its_sctp_cm_macros.h>

#include <its_tq_trans.h>
//#include <its_lksctp.h>

#define MAX_SCTP_ASSOCIATIONS 64000
#define SCTPCM_MSGQ_ID 25000    

           /*FIXME: A decision need to be made
	   on the value of SCTPCM_MSGQ_ID so that
	   it does not collide with other Queue IDs
	   in Accelero */

#define ESCTPCMINITIALIZEFAIL -205
/*
* Globals 
*/
extern TQUEUETRAN_Manager* SCTPCM_EventRcvQueue ;

/******************************
 * Class forward declarations
 *****************************/
class SCTPAssociation;

/******************************
 * Class declarations
 *****************************/
class SCTPEndPoint
{
    /*Constructor and Destructor*/
    public:
            SCTPEndPoint(){}       
	    SCTPEndPoint(/*const*/ SCTPEndPoint& ); 
	    SCTPEndPoint(const string& assocName, const string& assocFamily);
            virtual ~SCTPEndPoint(){}

    /*Public APIs of this class*/
    public:
            void SetPrimaryIP(std::string  IPAddress);
            void AddSecondaryIP(std::string  IPAddress);
            void SetPort(ITS_USHORT port);
            void SetType(SCTP_ENDPOINT_TYPE type);
            void SetTransport(SCTPTRAN_Manager* transport);
            SCTPTRAN_Manager* GetTransport(void) const;
            void ReturnTransport(TRANSPORT_Control *tc);
            std::string GetPrimaryIP(void) const;
            std::vector<std::string> GetSecondaryIPVector(void) const;
            SCTPEndPointProperties GetSCTPEndPointProperties(void) const;
            std::vector<SCTPAssociation*>& GetSCTPAssociationBackwardRef(void);
            ITS_USHORT GetPort(void) const;
            ITS_USHORT GetTrId(void) const;
            void SetTrId(ITS_USHORT TrId);
	    std::string GetFamily(void) const;
            std::string GetName(void) const;
    /*Overloaded operators*/
    public:
            bool operator ==(SCTPEndPoint& SCTPEndPointObj);
    private:
            SCTPEndPointProperties*  m_SCTPEndPointProperties;
            ITS_USHORT               m_TrId;
            std::vector<SCTPAssociation*> m_SCTPAssociationBackwardRef;
};

class SCTPAssociation
{
    /*Constructors and Destructors*/
    public:
            SCTPAssociation();
            SCTPAssociation(const SCTPAssociation&);
            ~SCTPAssociation(){}

    /*Public APIs*/
    public:
            ITS_INT Enable(void); 
            int Disable(void); 
            void AddLocalEndPoint(SCTPEndPoint* localEndPoint);
            void AddRemoteEndPoint(SCTPEndPoint* remoteEndPoint);
            ITS_SCTP_STATE GetAssociationState(void);
            void SetAssociationState(ITS_SCTP_STATE AssocState);
            SCTPAssociationProperties GetSCTPAssociationProperties(void) const;
            sctp_assoc_t GetAssociationID(void);
	    void SetAssociationID(sctp_assoc_t AssocID);
            SCTPEndPoint* GetSCTPLocalEndPoint(void) const;
            SCTPEndPoint* GetSCTPRemoteEndPoint(void) const;
                   
    /*Member variables*/
    private:
            SCTPEndPoint*                 m_LocalEndPoint;
            SCTPEndPoint*                 m_RemoteEndPoint;
            SCTPAssociationProperties*    m_PtrToSCTPAssocProperties;
	     
};


class SCTPConfigurationManager
{
    /*constructors and destructors*/
    public:
            SCTPConfigurationManager(){}
	    ~SCTPConfigurationManager(){}

    /* Configuration Manager Public APIs */
    public:
            ITS_INT Initialize(void);
            ITS_INT RegisterSCTPEventReceiver(ISCTPEvent* SCTPEventSink);

            SCTPAssociation* CreateClient(SCTPEndPoint& localEndPoint, 
                                          SCTPEndPoint& remoteEndPoint);
            ITS_INT CreateServer(SCTPEndPoint& localEndPoint);

            ITS_INT Enable(SCTPAssociation& SCTPAssocObj);
            ITS_INT Disable(SCTPAssociation& SCTPAssocObj);

            ITS_INT DeleteClient(SCTPAssociation& SCTPAssocObj);
            ITS_INT DeleteServer(SCTPEndPoint& localEndPoint);

            SCTPAssociation* GetSCTPAssociationObject(sctp_assoc_t associationID) const;
	    ISCTPEvent* GetEventSink() const ;

	    std::vector<SCTPEndPoint*>&     GetLocalServerEndPointVector(void);
	    std::vector<SCTPAssociation*>& GetUnEnabledClientVector(void) ;

	    SCTPAssociationHashTable* GetSCTPAssocHashTable(void);
    private:
	    SCTPAssociationHashTable m_SCTPAssocTable[MAX_SCTP_ASSOCIATIONS];
                    // Hash table of SCTP association id to SCTP assoc object reference
	    std::vector<SCTPEndPoint*> m_LocalClientEndPointVector ;
            std::vector<SCTPEndPoint*> m_LocalServerEndPointVector ;
	    std::vector<SCTPAssociation*> m_UnEnabledClientVector;
	    ITS_INT isInitialized ;
            ISCTPEvent* m_SCTPEventReg;
	    ITS_THREAD m_SCTPCM_EventRcvThread;
	    
};


extern void
SCTPCM_SCTPTransCallback (ITS_POINTER object, 
                        ITS_POINTER userData,
                       ITS_POINTER callData);

extern THREAD_RET_TYPE
SCTPConfigManagerThreadFunc(void* arg);


#endif /*#ifndef _ITS_SCTP_CM_H_*/


