/* ********************************-*-H-*-************************************
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

#ifndef __IWF_MESS_H__
#define __IWF_MESS_H__
#include <iostream>
#include <dia_stats.h>
#include "dia_peer_table.h"
#include <dia_mgmt.h>
#include <dia_frame.h>

#include "HAMeSSComponent.h"
#include "Component.h"
#include "Thread.h"
#include "ComponentDefines.h"
#include "InterfaceDefines.h"
#include "its_redundancy.h"
#include <string>
#include "Compo.h"

#include "CMAPIIwfConfig.h"
#include "CMAPIDreConfig.h"

#define DRE_SERVER_COMP_ID 123

class IwfMeSS: public eAccelero::HAMeSSComponent, public eAccelero::Runnable
{
    protected:
        unsigned m_counter;
        //std::ostrstream oss; 
        CMAPIIwfConfig *m_CmapiIwfObj;
        CMAPIDreConfig *m_CmapiDreObj;
        int m_argc;
        char** m_argv;
        eAccelero::SyslogChannel* m_SysLogChannelObj;
        static void PopulateErrorMap();
    public:
        static std::map<int,std::string> errorMap;
        eAccelero::CondVar m_cond; 
        IwfMeSS(int argc, const char** argv) : 
            HAMeSSComponent("IWF_MESS", eAccelero::COMP_IWF_APP),
            m_counter(82), 
            m_argc(argc), 
            m_argv((char**)argv)
    {
        m_CmapiDreObj = new CMAPIDreConfig();
        m_CmapiIwfObj = new CMAPIIwfConfig();
        m_SysLogChannelObj = new eAccelero::SyslogChannel("IWF", (LOG_PID), LOG_LOCAL6); 
        this->GetLogger().SetLogChannel(m_SysLogChannelObj);
        this->GetLogger().SetLevel(eAccelero::Logger::EACC_LOG_DEBUG);

        PopulateErrorMap();
    }

        void Initialize()
        {
            HAMeSSComponent::Initialize();

        }
        void Terminate()
        {
            HAMeSSComponent::Terminate();
        }

        void Run(void*);
        int ProcessComponentStatusUpdate(uint16_t componentId, eAccelero::HAComponentStatus newStatus);
        void SetLogLevel(unsigned int level);
        int ProcessAvailabilityStatusResetPostFunc(bool switchOver);
};	
#endif
