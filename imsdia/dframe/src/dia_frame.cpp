/**************************-*-Dia-*-*************************************
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
 *  ID: $Id: dia_frame.cpp,v 3.3.24.1.2.7.6.4.4.1.4.1.6.1 2014/10/27 08:28:37 pramana Exp $
 *  
 *  LOG: $Log: dia_frame.cpp,v $
 *  LOG: Revision 3.3.24.1.2.7.6.4.4.1.4.1.6.1  2014/10/27 08:28:37  pramana
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7.6.4.4.1.4.1  2014/05/05 09:33:31  millayaraja
 *  LOG: moved the diaFrame logs to new Macro as used by Stack
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7.6.4.4.1  2014/01/06 09:22:26  cprem
 *  LOG: Changes in diameter stack to support session replication. Review request 1611.
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7.6.4  2013/04/08 07:49:02  cprem
 *  LOG: Added a new method for initialization if DiaFrame.
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7.6.3  2013/04/07 10:34:03  cprem
 *  LOG: Reverted a change done for performance long back which is breaking singleton property of DiaFrame during multi-threading.
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7.6.2  2013/04/07 03:57:30  cprem
 *  LOG: Changes made to fix HA bugs. Review Request 784
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7.6.1  2013/03/22 06:33:33  pramana
 *  LOG: Changes for HA feature
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.7  2012/11/20 17:39:44  pramana
 *  LOG: Merged from CMAPI branch for 212-07 release
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.2.12.2  2012/11/20 10:24:28  rgovardhan
 *  LOG: merge from 00 Nov20Rel
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.5  2012/11/19 07:50:55  jvikas
 *  LOG: Delete only incdication data as DiaMsgFlow is deleted at stack downstream.
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.4  2012/11/06 16:31:20  pramana
 *  LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.2.16.1  2012/11/06 10:06:17  cprem
 *  LOG: Merged from 00 branch for 0212-06 release
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.3  2012/11/05 11:52:37  jvikas
 *  LOG: Changed the macro DIA_BASE_CMD into DiaMsgFlow
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.2  2012/10/01 09:01:02  rsanjay
 *  LOG:  opendiameter code removal changes:bugzilla-id 300
 *  LOG:
 *  LOG: Revision 3.3.24.1.2.1  2012/09/06 11:30:45  jvikas
 *  LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 *  LOG:
 *  LOG: Revision 3.3.24.1.4.1  2012/08/21 06:16:25  jvikas
 *  LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 *  LOG:
 *  LOG: Revision 3.3.24.1  2012/03/07 13:23:08  brajappa
 *  LOG: Changes made for the DRE demo
 *  LOG:
 *  LOG: Revision 3.3  2008/10/28 11:58:37  nvijikumar
 *  LOG: IssueID: none
 *  LOG: FeatureID: none
 *  LOG: Description: Porting Performance Enhancements changes from
 *  LOG:              3.0 Branch
 *  LOG:
 *  LOG: Revision 3.2.2.2  2008/09/16 10:48:19  nvijikumar
 *  LOG: Mutex for only object creation of singleton class
 *  LOG:
 *  LOG: Revision 3.2.2.1  2008/09/16 09:41:17  nvijikumar
 *  LOG: Avoided Mutex in GetDiaFrame() API (For Optimization)
 *  LOG:
 *  LOG: Revision 3.2  2008/04/01 15:56:04  hbhatnagar
 *  LOG: Changes for Proxy and Relay support (3.0 release) - (Viji, Hemant)
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.9  2007/01/12 13:50:34  nvijikumar
 *  LOG: Provided API to App to get Session Id or Peer Info incase of indications.
 *  LOG:
 *  LOG: Revision 2.8  2006/11/14 10:27:28  nvijikumar
 *  LOG: Provided API to check whether DCCA feature is enabled.
 *  LOG:
 *  LOG: Revision 2.7  2006/11/06 08:36:22  nvijikumar
 *  LOG: change from ITS_UINT to ITS_ULONG for 64bit support.
 *  LOG:
 *  LOG: Revision 2.6  2006/10/30 21:40:53  yranade
 *  LOG: Provide ReleaseSession API.
 *  LOG:
 *  LOG: Revision 2.5  2006/10/24 14:26:30  yranade
 *  LOG: RegisterApplication now takes AppId type.
 *  LOG: Reorganize Initialization a bit
 *  LOG:
 *  LOG: Revision 2.4  2006/10/16 16:04:41  yranade
 *  LOG: Custom message header from stack in Big-endian format.
 *  LOG:
 *  LOG: Revision 2.3  2006/10/13 17:09:54  yranade
 *  LOG: ITS-Diameter updates.
 *  LOG:
 *  LOG: Revision 2.2  2006/10/05 12:11:07  yranade
 *  LOG: Updates for ITS-Diameter.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.17  2006/09/01 16:34:56  yranade
 *  LOG: Enable diameter specific licensing.
 *  LOG:
 *  LOG: Revision 1.16  2006/06/13 06:40:20  tpanda
 *  LOG: minor fix to new message hdr format
 *  LOG:
 *  LOG: Revision 1.15  2006/06/12 12:33:15  yranade
 *  LOG: Enhancements to the way, message is formatted by the diameter vendor lib,
 *  LOG: when sending to the application. Used to fix issue in routing
 *  LOG: when applicationid in the header is 0, for applications like Rf-Ro, GqGq'
 *  LOG:
 *  LOG: Revision 1.14  2006/05/11 15:37:42  yranade
 *  LOG: Fix issue with appId in Indications. (tpanda)
 *  LOG:
 *  LOG: Revision 1.13  2006/05/08 10:33:01  tpanda
 *  LOG: Graceful End of client session
 *  LOG:
 *  LOG: Revision 1.12  2006/05/05 10:41:29  yranade
 *  LOG: Updates to handle indication with message.
 *  LOG:
 *  LOG: Revision 1.11  2006/04/25 15:38:26  yranade
 *  LOG: Add Try-catch block during GenericCommand decode.
 *  LOG: Add flowerboxes
 *  LOG: Add Legacy Callbacks to resolve linking issues at app level.
 *  LOG:
 *  LOG: Revision 1.10  2006/04/17 05:23:45  adutta
 *  LOG: AppId bitwise fix
 *  LOG:
 *  LOG: Revision 1.9  2006/04/13 18:06:54  yranade
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 1.8  2006/03/20 06:23:51  yranade
 *  LOG: Added AllocateSessionIndex API. This "must" be used by Applications
 *  LOG: to "initiate" requests.
 *  LOG:
 *  LOG: Revision 1.7  2006/03/15 11:09:11  yranade
 *  LOG: Reorganization.
 *  LOG:
 *  LOG: Revision 1.6  2006/03/15 09:56:05  yranade
 *  LOG: 1. Split OD Specifics and move them to vendors
 *  LOG: 2. Support Diameter Client Capability
 *  LOG: 3. Code Reorganization
 *  LOG:
 *  LOG: Revision 1.5  2006/03/13 16:38:13  yranade
 *  LOG: Added GetMessageType.
 *  LOG:
 *  LOG: Revision 1.4  2006/03/13 16:30:34  yranade
 *  LOG: Added DiaMsg class abstraction for inbound messages
 *  LOG: Coding indentation and standards.
 *  LOG:
 *  LOG: Revision 1.3  2006/03/09 11:47:32  tpanda
 *  LOG: Encode/Decode feature provided by wei's api replaced our encode/decode function.Hence dia_codec.* files are redundant
 *  LOG:
 *  LOG: Revision 1.2  2006/03/03 13:08:50  tpanda
 *  LOG: Modified because of code reorganisation
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:08:15  tpanda
 *  LOG: Building IMS Diameter Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_frame.cpp,v 3.3.24.1.2.7.6.4.4.1.4.1.6.1 2014/10/27 08:28:37 pramana Exp $"

#include <time.h>
#include <sys/timeb.h>

#include <its_license.h>
#include <dia_frame.h>
#include <dia_frame_stats.h>
#include <dia_trace.h>
#include <dia_defines.h>
#include <dia_utils.h>

using namespace std;
using namespace its;
using namespace diameter;

#if defined (VENDOR_ITS)
#include <diameter/base/BaseGenericCommand.h>
using namespace diameter::base;
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose: 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
//DiaMsg::DiaMsg(diameter::Command *command)
DiaMsg::DiaMsg(DIA_BASE_CMD *command)
{
    memset(&hdr, 0, sizeof(ITS_HDR));
    memset(&diaMsg, 0, sizeof(DIA_MSG));

    /* Used for Transport disconnect indication */
    indicationData = NULL;

    hdr.type = ITS_DIAMETER;
    diaMsg.msgType = ITS_DIA_MSG_TYPE_DATA;

    diaMsg.cmd = command;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
DiaMsg::DiaMsg(ITS_HDR& _hdr, DIA_MSG& _diaMsg)
{
    hdr = _hdr;
    diaMsg = _diaMsg;

    /* Used for Transport disconnect indication */
    indicationData = NULL;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
DiaMsg::~DiaMsg()
{
    /* Delete only incdication data as DiaMsgFlow is deleted at stack
     * downstream. Not deleting indication data is permanent leak */
    if (indicationData)
    {
        free((char*)indicationData);
        indicationData = NULL;
    }
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_UINT
DiaMsg::GetApplicationId() const
{
    return hdr.context.appId;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_UINT
DiaMsg::GetSessionIndex() const
{
    return diaMsg.sessionIndex;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
const diameter::CommandImpl* 
DiaMsg::GetCommandImpl()
{
//    return &diaMsg.cmd->getImpl();
      return &(diaMsg.cmd->GetBaseGenCommand()->getImpl());
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
const diameter::Command*
DiaMsg::GetCommand()
{
    //return diaMsg.cmd;
    return diaMsg.cmd->GetBaseGenCommand();
}

const DIA_BASE_CMD*
DiaMsg::GetMsgFlow()
{
    return diaMsg.cmd;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_OCTET
DiaMsg::GetMessageType() const
{
    return diaMsg.msgType;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
bool
DiaMsg::IsIndication() const
{
    if (diaMsg.msgType == ITS_DIA_MSG_TYPE_IND)
    {
        return true;
    }
    return false;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_OCTET 
DiaMsg::GetIndication() const
{
    return diaMsg.indication;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
const ITS_HDR&
DiaMsg::GetHeader() const
{
    return (hdr);
}
const char* 
DiaMsg::GetIndicationData()
{
    return indicationData;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_Mutex DiaFrame::guard(0);
ITS_Mutex DiaFrame::lock(0);
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
DiaFrame::DiaFrame()
{
    stackInitialized = ITS_FALSE;
    configFile = NULL;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
void
DiaFrame::Lock() const
{
    int res;
    res = const_cast<ITS_Mutex&>(lock).Acquire();
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
void
DiaFrame::Unlock() const
{
    int res;
    res = const_cast<ITS_Mutex&>(lock).Release();
}

static DiaFrame *odFrame = NULL;
/*.implementation:public
 ****************************************************************************
 *  Purpose: To Get the current DiaFrame object.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes: Do not invoke this method during initialization as this could lead
 *         to creation of multiple objects in case of multiple threads.
 *         This would break the singleton behaviour expected out of the same.
 *
 *  See Also:
 *
 ****************************************************************************/
DiaFrame*
DiaFrame::GetDiaFrame()
{

   // ITS_ASSERT(DiaFrame::guard.Acquire() == ITS_SUCCESS);
    if (odFrame == NULL)
    {
       /* Moved inside if check, due to performance issue */
      /*  ITS_ASSERT(DiaFrame::guard.Acquire() == ITS_SUCCESS);*/

        odFrame = new DiaFrame;

        //DiaFrame::guard.Release();
    }
     //   DiaFrame::guard.Release();

    return odFrame;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: To Initialize of Create the DiaFrame Object.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
DiaFrame *
DiaFrame::InitDiaFrame()
{
    ITS_ASSERT(DiaFrame::guard.Acquire() == ITS_SUCCESS);

    DiaFrame::GetDiaFrame();

    DiaFrame::guard.Release();

    return odFrame;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
/*int
DiaFrame::Initialize()
{
    DT_DBG(("DiaFrame::Initialize"));

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    if (!obj.isStarted())
    {
        if (obj.Start() == ITS_SUCCESS)
        {
            stackInitialized = ITS_TRUE;

            return (ITS_SUCCESS);
        }
        else
        {
            stackInitialized = ITS_FALSE;

            return !ITS_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Stack already Initialized or ConfigFile not set"));
    }

    return (ITS_EINITFAIL);
}*/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::Initialize(bool isActive)
{
    DT_DBG(("DiaFrame::Initialize"));

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    if (!obj.isStarted())
    {
        if (obj.Start(isActive) == ITS_SUCCESS)
        {
            stackInitialized = ITS_TRUE;

            return (ITS_SUCCESS);
        }
        else
        {
            stackInitialized = ITS_FALSE;

            return !ITS_SUCCESS;
        }
    }
    else
    {
        DT_ERR(("Stack already Initialized or ConfigFile not set"));
    }

    return (ITS_EINITFAIL);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::Terminate()
{
    DT_CRT(("DiaFrame::Terminate"));

    if (configFile)
    {
        free (configFile);
    }
    obj.Terminate();

    return (ITS_SUCCESS);

}


int DiaFrame::GoActive()
{
    DT_DBG(("Switching to Active."));
    return obj.GoActive();
}

int DiaFrame::GoStandby()
{
    DT_DBG(("Switching to Standby."));
        return obj.GoStandby();
}



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int 
DiaFrame::AllocateSessionIndex(ITS_UINT appId, ITS_UINT& sessIdx,
                               std::string& sessIdString)
{
    int ret = ITS_EINVINITSTATE;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    if (stackInitialized)
    {
        if ((ret = obj.AllocateSession(appId, sessIdx, sessIdString)) == ITS_SUCCESS)
        {
            DT_DBG(("AllocateSessionIndex: Allocated %d", sessIdx));
            return (ret);
        }
    }
    else
    {
        ret = DIA_STACK_NOT_INITIALIZED;
    }
    
    DT_ERR(("AllocateSessionIndex: Allocation Failure: %d", ret));

    return (ret);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::ReleaseSession(std::string sessionId)
{
    int ret = ITS_SUCCESS;

    if (stackInitialized)
    {
        if ((ret = obj.ReleaseSession(sessionId.c_str())) == ITS_SUCCESS)
        {
            DT_DBG(("Released Session for %s", sessionId.c_str()));
            return (ret);
        }
    }
    else
    {
        ret = DIA_STACK_NOT_INITIALIZED;
    }

    DT_ERR(("ReleaseSession Failure %d", ret));

    return (ret);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
bool
DiaFrame::IsDccaEnabled()
{
    bool ret = false;
    if(ITS_FindFeature(DCCA_FEATURE_NAME))
    {
        ret = true;
    }
     return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int 
DiaFrame::Send(const Command* msg, ITS_UINT sessIndex, ITS_USHORT toPeer, ITS_UINT flags)
{
    int ret;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    DT_DBG(("DiaFrame::Send"));


    if (stackInitialized)
    {
        if ((ret = obj.SendMsgToPeer(msg, sessIndex, toPeer, flags)) == ITS_SUCCESS)
        {
            DT_DBG(("Succesfully Sent Message to Diameter Stack"));

            DiaFrameStats *stats = DiaFrameStats::GetDiaFrameStats();

            stats->Increment(stats->GetNumMsgsFromApp());
        }
        else
        {
            DT_ERR(("Send Msg Failure: Error Code %d", ret));

            return (ret);
        }
    }
    else
    {
        DT_ERR(("Send: Stack Not Initialized"));

        return (DIA_STACK_NOT_INITIALIZED);
    }

    return (ITS_SUCCESS);
}

/* DTF Changes */
int 
DiaFrame::Send(const DiaMsgFlow* msg, ITS_UINT sessIndex, ITS_USHORT toPeer, ITS_UINT flags)
{
    int ret;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    DT_DBG(("DiaFrame::Send"));


    if (stackInitialized)
    {
        if ((ret = obj.SendMsgToPeer(msg, sessIndex, toPeer, flags)) == ITS_SUCCESS)
        {
            DT_DBG(("Succesfully Sent Message to Diameter Stack"));

            DiaFrameStats *stats = DiaFrameStats::GetDiaFrameStats();

            stats->Increment(stats->GetNumMsgsFromApp());
        }
        else
        {
            DT_ERR(("Send Msg Failure: Error Code %d", ret));

            return (ret);
        }
    }
    else
    {
        DT_ERR(("Send: Stack Not Initialized"));

        return (DIA_STACK_NOT_INITIALIZED);
    }

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::Send(const Command* msg)
{
    int ret;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    DT_DBG(("DiaFrame::Send"));


    if (stackInitialized)
    {
        if ((ret = obj.SendMsgToPeer(msg)) == ITS_SUCCESS)
        {
            DT_DBG(("Succesfully Sent Message to Diameter Stack"));

            DiaFrameStats *stats = DiaFrameStats::GetDiaFrameStats();

            stats->Increment(stats->GetNumMsgsFromApp());
        }
        else
        {
            DT_ERR(("Send Msg Failure: Error Code %d", ret));

            return (ret);
        }
    }
    else
    {
        DT_ERR(("Send: Stack Not Initialized"));

        return (DIA_STACK_NOT_INITIALIZED);
    }

    return (ITS_SUCCESS);
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::Receive(its::Event& ev, DiaMsg** msg)
{   
    ITS_HDR h;
    DIA_MSG m;
    int index = 0;
    *msg = NULL;
    char* indicData = NULL;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIAMETER))
    {
        return ITS_ENOLICENSE;
    }

    memset(&h, 0, sizeof(ITS_HDR));
    memset(&m, 0, sizeof(DIA_MSG));
    
    DT_DBG(("DiaFrame::Receive"));

    ITS_OCTET *data = (ITS_OCTET *)ev.GetData();

    h.type = ITS_DIAMETER;

    m.msgType = data[index++];

    m.sessionIndex = DiaUtils::DataToInt(&data[index], sizeof(ITS_UINT));
    index +=sizeof(ITS_UINT);

    if ((m.msgType == ITS_DIA_MSG_TYPE_DATA) ||
       (m.msgType == ITS_DIA_MSG_TYPE_IND_WITH_DATA))
    {
        /* Retrieve the appId from the event */
        h.context.appId = DiaUtils::DataToInt(&data[index], sizeof(ITS_UINT));
        index += sizeof(ITS_UINT);
        ITS_ULONG cmdAddr;
        memcpy(&cmdAddr, &data[index], sizeof(ITS_ULONG));
        DT_DBG(("DTF:: DiaFrame:: addr of cmdAddr %x", &cmdAddr));
        DIA_BASE_CMD *cmd = (DIA_BASE_CMD*)cmdAddr;
        m.cmd = cmd;
    }
    else if (m.msgType == ITS_DIA_MSG_TYPE_IND)
    {
        h.context.appId = DiaUtils::DataToInt(&data[index], sizeof(ITS_UINT));
        index += 4;
        m.indication = data[index++];
        if (index < ev.GetLength())
        {
           indicData = strdup((char*)&data[index]);
        }
    }
    else
    {
        return (ITS_ERCVFAIL);
    }

    *msg = new DiaMsg(h, m);
    if (indicData )
    {
       (*msg)->indicationData = indicData;
    }

    DiaFrameStats *stats = DiaFrameStats::GetDiaFrameStats();

    stats->Increment(stats->GetNumMsgsFromStack());

    return ITS_SUCCESS;

}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::RegisterApplication(ITS_UINT appId, ITS_UINT appType)
{
    DT_DBG(("DiaFrame::RegisterApplication"));

    obj.RegisterWithAppId(appId, appType);

    return (ITS_SUCCESS);

}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
void
DiaFrame::SetConfigFile(char* cfgFile)
{
    DT_DBG(("DiaFrame::SetConfigFile"));

    configFile = strdup(cfgFile);
}

int DiaFrame::enableReplication()
{
    obj.enableReplication();
}

int DiaFrame::disableReplication()
{
    obj.disableReplication();
}

int DiaFrame::registerCreateSessionReplicationCbk(createSessionCbk createCbk)
{
    obj.registerCreateSessionReplicationCbk(createCbk);
}

int DiaFrame::registerUpdateSessionReplicationCbk(updateSessionCbk updateCbk) 
{
    obj.registerUpdateSessionReplicationCbk(updateCbk);
}

int DiaFrame::registerDeleteSessionReplicationCbk(deleteSessionCbk deleteCbk) 
{
    obj.registerDeleteSessionReplicationCbk(deleteCbk);
}

int DiaFrame::registerFetchSessionReplicaCbk(fetchSessionCbk fetchCbk) 
{
    obj.registerFetchSessionReplicaCbk(fetchCbk);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
DiaFrame::ReCreateSessionEntry(string& sessionId, ITS_EVENT& event)
{
    int ret;
    DT_DBG(("DiaFrame::ReCreateSessionEntry entry"));

    if (stackInitialized)
    {
        if ((ret = obj.ReCreateSessionEntry(sessionId, event)) != ITS_SUCCESS)
        {
            DT_ERR(("Send Msg Failure: Error Code %d", ret));

            return (ret);
        }
        else
        {
            DT_DBG(("Successfully sent Session recreation event to stack"));
        }
    }
    else
    {
        DT_ERR(("Send: Stack Not Initialized"));

        return (DIA_STACK_NOT_INITIALIZED);
    }

    DT_DBG(("DiaFrame::ReCreateSessionEntry exit"));
    return (ITS_SUCCESS);
}
/* Legacy Accelero Callbacks. Not Needed for Diameter,
   Defined here to solve linking issues
*/

#include <its_callback.h>

extern "C"
{
    CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
    CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
    CALLBACK_Manager* MTP3_PRC_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_PRC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_PRC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_PRC_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_PRC_SSNRoutingCallbacks = NULL;
    CALLBACK_Manager* MTP3_TTC_ManagementCallbacks = NULL;
    CALLBACK_Manager* ISUP_TTC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_TTC_ManagementCallbacks = NULL;
    CALLBACK_Manager* SCCP_TTC_GlobalTitleTranslator = NULL;
    CALLBACK_Manager* SCCP_TTC_SSNRoutingCallbacks = NULL;
}



