/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: ssg_configuration.cpp,v 1.1.1.1.4.1.2.1 2013/12/10 13:34:00 millayaraja Exp $
 *
 *  LOG: $Log: ssg_configuration.cpp,v $
 *  LOG: Revision 1.1.1.1.4.1.2.1  2013/12/10 13:34:00  millayaraja
 *  LOG: updated productization code for eAccelero Logging
 *  LOG:
 *  LOG: Revision 1.1.1.1.4.1  2013/10/04 13:43:07  millayaraja
 *  LOG: changes for RHEL machine dependent compilation flags and dependencies in IWF code
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:36  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.2  2011/04/15 11:34:07  nvijikumar
 *  LOG: UT Updates
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ssg_configuration.cpp,v 1.1.1.1.4.1.2.1 2013/12/10 13:34:00 millayaraja Exp $"

#include <its++.h>
#include <iostream>
#include <engine++.h>
#include <its_timers.h>
#include <its_iniparse.h>

#include <ssg_trace.h>
#include <ssg_defines.h>
#include <ssg_configuration.h>
#include "iwf_prot_utils.h"

#if defined(ITS_STD_NAMESPACE)
#ifdef GCC_LESS_THAN_4_3
//using namespace std::tr1;
using namespace std;
#else
using namespace std;
#endif
using namespace its;
using namespace engine;
#endif

ITS_Mutex SsgConfiguration::guard(0);
static SsgConfiguration *config = NULL;

const char* orHost   = NULL;
const char* orRealm  = NULL;
const char* dhHost   = NULL;
const char* drRealm  = NULL;

// 
// Shared configuration access function.
//
ITS_BOOLEAN isQosConfigured = ITS_FALSE;

SsgConfiguration::SsgConfiguration()
    : isDebugDump(false),
      ni(INTERNATIONAL),
      lock(0),
      mapReqTimer(60),
      ssgPc(1),
      hasSsgPc(false),
      ssgSsn(5),
      hasSsgSsn(false),
      mscPc(0),
      hasMscPc(false),
      stpPc(0),
      hasStpPc(false),
      appHandleMGMT(false),
      qosIndicator(0x00),
      _npnValue(0x00)
{
    try
    {
        ParseResourceManager();
        ITS_C_ASSERT(hasSsgPc == true);
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    }
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);
        standardExc.Log();
    }
}

SsgConfiguration::~SsgConfiguration()
{
    if (config != NULL)
    {
        delete config;
        config = NULL;
    }

}

void
SsgConfiguration::Lock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Acquire();

    if (res != ITS_SUCCESS)
    {
    }
}

void
SsgConfiguration::Unlock() const
{
    int res = const_cast<ITS_Mutex&>(lock).Release();

    if (res != ITS_SUCCESS)
    {
    }
}

int
SsgConfiguration::ParseResourceManager()
{
    // sequential parsing
    char key[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];

    ITS_ResourceManager *rf = new ITS_ResourceManager(APPL_GetConfigFileName());

    if (rf == NULL)
    {
        return !ITS_SUCCESS;
    }
    rf->Lock();
    rf->Rewind(NULL);

    while (rf->GetKeyName(NULL, key, ITS_PATH_MAX) == ITS_SUCCESS &&
           rf->GetKeyValue(NULL, value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (strcmp(key, NETWORK_INDICATOR) == 0)
        {
            if (strcmp(value, "National") == 0)
            {
                ni = NATIONAL;
            }
            else
            {
                ni = INTERNATIONAL;
            }
        }
        else if (strcmp(key, "DEBUG_DUMP") == 0)
        {
            if (RESFILE_ParseNum((const char*) value))
            {
                isDebugDump = true;
            }
            else
            {
                isDebugDump = false;
            }
        }
        else if (strcmp(key, "SSG_REQ_TIMER") == 0)
        {
            mapReqTimer    = RESFILE_ParseNum((const char*) value);
        }
        else if (strcmp(key, "SSG_STACK_POINTCODE") == 0)
        {
            hasSsgPc = true;
            ssgPc = RESFILE_ParseNum((const char*) value);
        }
        else if (strcmp(key, "SSG_STACK_SSN") == 0)
        {
            hasSsgSsn = true;
            ssgSsn = RESFILE_ParseNum((const char*) value);
        }
        else if (strcmp(key, "MSC_POINTCODE") == 0)
        {
            hasMscPc = true;
            mscPc = RESFILE_ParseNum((const char*) value);
        }
        else if (strcmp(key, "STP_POINTCODE") == 0)
        {
            hasStpPc = true;
            stpPc = RESFILE_ParseNum((const char*) value);
        }
        else if (strcmp(key, "AppHandlesMGMT") == 0)
        {
            if (RESFILE_ParseNum((const char*)value))
            {
                appHandleMGMT = true;
            }
        }
        else if (strcmp(key, "SSG_NPN_VALUE") == 0)
        {
            SetNpnValue(RESFILE_ParseNum((const char*) value));
        }
        else if (strcmp(key, "QOS_INDICATOR") == 0)
        {
            qosIndicator = RESFILE_ParseNum((const char*)value);
        }
    }
    rf->Unlock();

    if (rf != NULL)
    {
        delete rf;
        rf = NULL;
    }
    return ITS_SUCCESS;
}

//
// retrieve the current Ssg configuration.
//
SsgConfiguration& GetSsgConfiguration()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("--Entry GetSsgConfiguration ");
    ITS_ASSERT(SsgConfiguration::guard.Acquire() == ITS_SUCCESS);

    if (config == NULL)
    {
        config = new SsgConfiguration;
    }

    SsgConfiguration::guard.Release();

    DLOG_DEBUG("--Exit GetSsgConfiguration ");
    return *config;
}


const char* GetOriginHost()
{
    return orHost;
}
const char* GetOriginRealm()
{
    return orRealm;
}
const char* GetDestinationHost()
{
    return dhHost;
}
const char* GetDestinationRealm()
{
    return drRealm;
}
void SetOriginHost(const char* OriginHost)
{
    orHost = strdup(OriginHost);
}
void SetOriginRealm(const char* OriginRealm)
{
    orRealm = strdup(OriginRealm);
}
void SetDestinationHost(const char* DestinationHost)
{
    dhHost = strdup(DestinationHost);
}
void SetDestinationRealm(const char* DestinationRealm)
{
    drRealm = strdup(DestinationRealm);
}
