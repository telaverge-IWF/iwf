/*********************************-*-H-*-**********************************
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
 *  ID: $Id: ssg_configuration.h,v 1.1.1.1.2.1.18.1 2014/12/03 09:21:38 mhimanshu Exp $
 *
 *  LOG: $Log: ssg_configuration.h,v $
 *  LOG: Revision 1.1.1.1.2.1.18.1  2014/12/03 09:21:38  mhimanshu
 *  LOG: stats implementation at MML - diaS6aStats and activeSubscribers
 *  LOG:
 *  LOG: Revision 1.1.1.1.2.1  2013/05/28 05:54:09  jkchaitanya
 *  LOG: changes for coverity for IWF-PhaseII
 *  LOG:
 *  LOG: Revision 1.1.1.1  2013/01/09 16:41:35  brajappa
 *  LOG: Initial import
 *  LOG:
 *  LOG: Revision 1.2  2011/04/15 11:34:29  nvijikumar
 *  LOG: UT Updates
 *  LOG:
 *  LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 *  LOG: Initial Draft for SSG
 *  LOG:
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: ssg_configuration.h,v 1.1.1.1.2.1.18.1 2014/12/03 09:21:38 mhimanshu Exp $"

#if !defined(_SSG_CONFIGURATION_H_)
#define _SSG_CONFIGURATION_H_

#define GENERAL_CONFIG           "General-Config"
#define NETWORK_INDICATOR 	 "NetworkIndicator"

enum NI_TYPE
{
INTERNATIONAL= 0x00,
NATIONAL =0x80
};


//
// Shared configuration access function.
//

class SsgConfiguration;
extern SsgConfiguration& GetSsgConfiguration();

//
//  SsgConfiguration.
//
//  Can be split using inner classes in the future if necessary.
//

class SsgConfiguration
{
public:
    friend SsgConfiguration& GetSsgConfiguration();

    SsgConfiguration();

    virtual ~SsgConfiguration();

    void Lock() const;

    void Unlock() const;

    bool IsDebugDump() const
    {
        return isDebugDump;
    }

    void SetDebugDump(bool onOff)
    {
        Lock();

        isDebugDump = onOff;

        Unlock();
    }
    NI_TYPE GetNI() const
    {
        return ni;
    }

    ITS_INT GetSsgReqTimerVal() const
    {
        return mapReqTimer;
    }

    ITS_INT GetSsgPC() const
    {
        return ssgPc;
    }

    bool HasSsgPC() const
    {
        return hasSsgPc;
    }

    ITS_INT GetSsgSSN() const
    {
        return ssgSsn;
    }

    bool HasSsgSSN() const
    {
        return hasSsgSsn;
    }

    bool DoesappHandleMGMT() const
    {
        return appHandleMGMT;
    }

    void SetappHandleMGMT(bool val)
    {
        appHandleMGMT = val;
    }

    ITS_INT GetMscPC() const
    {
        return mscPc;
    }
    ITS_INT GetStpPC() const /*may be not required */
    {
        return stpPc;
    }
    bool HasMscPC() const
    {
        return hasMscPc;
    }
    bool HasStpPC() const
    {
        return hasMscPc;
    }
    ITS_OCTET GetQOSIndicator() const
    {
        return qosIndicator;
    }

    ITS_OCTET GetNpnValue()
    {
        return _npnValue;
    }

    void SetNpnValue(ITS_OCTET npnValue)
    {
        _npnValue= npnValue;
    }

protected:

    bool isDebugDump;
    NI_TYPE ni;
    static its::ITS_Mutex guard;
    its::ITS_Mutex lock;

    // Timers
    ITS_INT mapReqTimer;
    ITS_INT ssgPc;
    bool hasSsgPc;
    ITS_INT ssgSsn;
    bool hasSsgSsn;
    ITS_INT mscPc;
    bool hasMscPc;
    ITS_INT stpPc;
    bool hasStpPc;
    bool appHandleMGMT;
    int ParseResourceManager();
    ITS_OCTET qosIndicator;
    ITS_OCTET _npnValue;
};

#define GET_CFG GetSsgConfiguration

extern const char* GetOriginHost();
extern const char* GetOriginRealm();
extern const char* GetDestinationHost();
extern const char* GetDestinationRealm();
extern void SetOriginHost(const char* OriginHost);
extern void SetOriginRealm(const char* OriginRealm);
extern void SetDestinationHost(const char* DestinationHost);
extern void SetDestinationRealm(const char* DestinationRealm);

#endif
