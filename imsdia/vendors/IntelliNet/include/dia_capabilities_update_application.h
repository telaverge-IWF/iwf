/*********************************-*-H-*-**********************************
 *                                                                          *
 *             Copyright 2012 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.       *
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
 ****************************************************************************/

#if !defined DIA_CAPABILITIES_UPDATE_APPLICATION_H_
#define DIA_CAPABILITIES_UPDATE_APPLICATION_H_

#include <list>
#include <pthread.h>    

#include <its_mutex.h>
#include <dia_peer_table.h>



class CapabilitiesUpdateApplication
{
public:
    static CapabilitiesUpdateApplication *GetCapabilitiesUpdateApplication();

    int ProcessCUR(DIA_CMD* cmd,PEER_ENTRY *pEntry,ITS_EVENT *evt);

    int ProcessCUA(DIA_CMD* cmd,PEER_ENTRY *pEntry);

    int SendCUA(bool error, bool retrans,ITS_UINT result,
                PEER_ENTRY *pEntry,ITS_EVENT *evt);

    void UpdateCeCacheOfPeer(DIA_CUR * cur,PEER_ENTRY *pEntry,bool isRequest);
    bool IsCapabilityUpdateIsSupported();

private:

    static its::ITS_Mutex m_capabilitiesUpdateAppObjectGuard;

    CapabilitiesUpdateApplication() 
    {
        //pthread_rwlock_init(&m_routingTableLock,NULL);
    };

   // pthread_rwlock_t m_routingTableLock;
    
    ~CapabilitiesUpdateApplication();

    CapabilitiesUpdateApplication(CapabilitiesUpdateApplication&) {};

    static CapabilitiesUpdateApplication *m_capabilitiesUpdateAppObject;
};


#define CAPABILITIES_UPDATE_APPLICATION CapabilitiesUpdateApplication::GetCapabilitiesUpdateApplication()

#endif
