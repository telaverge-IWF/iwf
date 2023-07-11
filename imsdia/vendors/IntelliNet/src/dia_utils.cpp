/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: dia_utils.cpp,v $
 * LOG: Revision 3.24.4.7.4.6.4.2.4.1.8.1  2017/12/21 04:37:22  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 3.24.4.7.4.6.4.2.4.1  2014/05/12 05:48:52  millayaraja
 * LOG: merged changes for Hop-By-Hop Id fix from B-DRE-0400-01-AICENT-POC branch
 * LOG:
 * LOG: Revision 3.24.4.7.4.6.4.2  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.24.4.7.4.6.4.1  2013/12/05 07:03:47  vsarath
 * LOG: Fix for issue 1520
 * LOG:
 * LOG: Revision 3.24.4.7.4.6  2013/04/04 09:06:11  mallikarjun
 * LOG: MemLeak Fixes Bug 1205 1298
 * LOG:
 * LOG: Revision 3.24.4.7.4.5  2013/03/21 11:49:06  mallikarjun
 * LOG: Bug-1194-Changes
 * LOG:
 * LOG: Revision 3.24.4.7.4.4  2013/03/20 05:14:32  mallikarjun
 * LOG: dia_utils.cpp
 * LOG:
 * LOG: Revision 3.24.4.7.4.3  2013/03/06 08:31:00  jvikram
 * LOG: BUGID=1016, 1027, 803. Fixed the specified bugs.
 * LOG:
 * LOG: Revision 3.24.4.7.4.2  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.24.4.7.4.1  2013/02/01 11:34:16  pramana
 * LOG: Merged from branch 0212 to 0300.
 * LOG:
 * LOG: Revision 3.24.4.8  2013/01/18 04:48:00  jsarvesh
 * LOG: cppcheck changes
 * LOG:
 * LOG: Revision 3.24.4.7  2012/12/17 05:36:47  mallikarjun
 * LOG: Bug 650 static routing for relay
 * LOG:
 * LOG: Revision 3.24.4.6  2012/11/20 17:39:45  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.24.4.3.8.1  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.24.4.4  2012/11/06 16:31:21  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.24.4.3.12.1  2012/11/06 08:59:00  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.24.4.3  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.24.4.2  2012/09/06 11:30:46  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.24.6.3  2012/09/05 13:13:29  jvikas
 * LOG: DIA_BASE_CMD macro used.
 * LOG:
 * LOG: Revision 3.24.6.2  2012/09/04 04:47:34  jvikas
 * LOG: Bug210: Route-Record added in BaseGenericCmd if DTF is enabled.
 * LOG:
 * LOG: Revision 3.24.6.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.24.4.1  2012/08/21 08:55:57  ksalil
 * LOG: Merge from branch B-DRE-IDIA-0100-00
 * LOG:
 * LOG: Revision 3.24.2.1  2012/07/19 05:41:57  pramana
 * LOG: changes for ckecking mandatory AVPs
 * LOG:
 * LOG: Revision 3.24  2011/08/23 04:08:38  vkumara
 * LOG: Added DataToUInt to fix CmdCode decode error for an unsigned values from abnf.
 * LOG: (Extra FF was returning from existing DataToInt ()).
 * LOG:
 * LOG: Revision 3.23  2009/07/13 06:46:21  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.22  2009/06/30 03:21:48  rajeshak
 * LOG: Added missing return statement.
 * LOG:
 * LOG: Revision 3.21  2009/06/29 14:54:53  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.20  2009/03/19 12:34:50  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 3.19  2009/03/19 11:29:00  rajeshak
 * LOG: Memory leak fix for error scenario.
 * LOG:
 * LOG: Revision 3.18  2009/03/03 11:34:20  rajeshak
 * LOG: Enhanced decode with proper exception handling.
 * LOG:
 * LOG: Revision 3.17  2009/03/03 10:23:59  nvijikumar
 * LOG: PutEventReference and GetEventReference utility functions provided
 * LOG: to simulate AddTailNoCopy concept (Performance changes)
 * LOG:
 * LOG: Revision 3.16  2009/02/03 10:21:11  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.15  2009/01/09 09:06:50  nvijikumar
 * LOG: Added Alarm for Decode failure and Receive failure
 * LOG:
 * LOG: Revision 3.14  2009/01/06 13:59:09  nvijikumar
 * LOG: Removed GetSessionId API since it is not used
 * LOG:
 * LOG: Revision 3.13  2009/01/06 12:52:50  rajeshak
 * LOG: comments added
 * LOG:
 * LOG: Revision 3.12  2009/01/03 05:59:17  rajeshak
 * LOG: Memory Fix, make sure these are reverted if we move to STL string
 * LOG:
 * LOG: Revision 3.11  2008/12/23 08:34:45  rajeshak
 * LOG: Moved and renamed InitNInsertAcctSession & InitNInsertAuthSession function
 * LOG: from dia_utils to dia_session_table
 * LOG:
 * LOG: Revision 3.10  2008/12/12 18:30:48  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.9  2008/12/12 12:32:08  nvijikumar
 * LOG: Updated with statistic support
 * LOG:
 * LOG: Revision 3.8  2008/12/07 09:50:15  rajeshak
 * LOG: Added definition of two new functions InitNInsertAcctSession and
 * LOG: InitNInsertAuthSession to avoid code duplication.
 * LOG:
 * LOG: Revision 3.7  2008/10/31 05:58:10  nvijikumar
 * LOG: IssueID:none
 * LOG: FeatureID:none
 * LOG: Description: Code cleanup
 * LOG:
 * LOG: Revision 3.6  2008/07/31 06:17:32  sureshj
 * LOG: Code is Put under Tls Enabled Tag
 * LOG:
 * LOG: Revision 3.5  2008/06/13 11:47:30  hbhatnagar
 * LOG: Added method to populate the ciphersuites as needed by TLS wrapper
 * LOG:
 * LOG: Revision 3.4  2008/04/16 12:20:53  hbhatnagar
 * LOG: Made changes in IsResultCodeModified for the ASA,RAA, STA and
 * LOG: ACA(Event and Stop) message. For these message return ITS_FALSE.
 * LOG:
 * LOG: Revision 3.3  2008/04/09 10:03:35  hbhatnagar
 * LOG: Added Check for Answer in IsResultCodeModified
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:41:52  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:32  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.10  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.2.2  2007/05/30 13:43:08  nvijikumar
 * LOG: Return Proper Error code if message decode failed.
 * LOG:
 * LOG: Revision 2.8.2.1  2007/05/28 14:19:46  nvijikumar
 * LOG: Return proper error code if failed to decode the message.
 * LOG:
 * LOG: Revision 2.8  2007/02/21 10:28:01  nvijikumar
 * LOG: Control Hex dump print from XML.
 * LOG:
 * LOG: Revision 2.7  2006/11/03 14:03:26  nvijikumar
 * LOG: 64 bit Compilation support.
 * LOG:
 * LOG: Revision 2.6  2006/10/25 11:29:23  nvijikumar
 * LOG: Print Byte dump Only if traces are enabled.
 * LOG:
 * LOG: Revision 2.5  2006/10/17 09:54:20  nanaparthi
 * LOG: Changes for Solaris Build.
 * LOG:
 * LOG: Revision 2.4  2006/10/16 06:17:49  yranade
 * LOG: Cleanup.
 * LOG:
 * LOG: Revision 2.3  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:21:54  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 ****************************************************************************/
#include <stdlib.h>
#include <sys/time.h>
#include <its++.h>
#include <its_mutex.h>

#include <dia_utils.h>
#include <dia_trace.h>
#include <dia_ip_trans.h>
#include <dia_redirect.h>
#include <its_dia_config.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif

static ITS_Mutex  __HOPGate(0);
static ITS_Mutex  __ENDGate(0);

void PRINT_EVENT(ITS_EVENT* evt)
{
    if (itsDiaConfig.IsHexDumpEnabled())
    {
        int x = 0;
        printf("Event source 0x%02x\n",evt->src);
        printf("Event Len %d\n",evt->len);
        for(x = 0; x < evt->len; x++)
        {
            if(x != 0 && x % 8 == 0)
            {
                printf("\n");
            }
            printf("0x%02x, ",evt->data[x]);
        }
        printf("\n");
        fflush(stdout);
    }

    return;
}

void DiaUtils::InitTrustedCAs(std::string masterCA, std::string cAPath,
                                                 std::string cAFiles)
{
    std::string script(SCRIPT);
    script.append(masterCA);
    script.append(" ");
    script.append(cAPath);
    script.append(" ");
    script.append(cAFiles);
    //std::cout<<"script"<<script<<endl;
    if((system(script.c_str())) == -1)
    {
        DT_ERR(("Creating Master CA and Rehashing failed"));
    }
}

void
DiaUtils::HmiSleep(HMIThread_Info* hmiInfo, ITS_INT val)
{
    ITS_INT count = 0;

    if(itsDiaConfig.IsHMIEnabled())
    {
        HMI_ResetCounter(hmiInfo);

        while (count < val)
        {
            TIMERS_Sleep(HMI_GetTimeOutInterval()/1000);
            count  += HMI_GetTimeOutInterval()/1000;

            HMI_ResetCounter(hmiInfo);
        }
    }
    else
    {
        TIMERS_Sleep(val);
    }
}

/* Hop-By-Hop Identifier is a monotonically
   increasing number, whose start value was
   randomly generated
*/
ITS_UINT DiaUtils::GenerateHopByHopId()
{
    static ITS_UINT nextHopId = 0;

    if (const_cast<ITS_Mutex&>(__HOPGate).Acquire() != ITS_SUCCESS)
    {
        DT_ERR(("Mutex acquisition of __HOPGate failed and proceeding with errno = %d", errno));
    }

    if (nextHopId == 0)
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        srand((unsigned int)(tv.tv_sec + tv.tv_usec));
        nextHopId = rand();
    }
    else
    {
        nextHopId++;
    }

    unsigned int nextHopIdLocal = nextHopId;
    if (const_cast<ITS_Mutex&>(__HOPGate).Release() != ITS_SUCCESS)
    {
        DT_ERR(("Mutex release of __HOPGate failed and proceeding with errno = %d", errno));
    }

    return (nextHopIdLocal);
}

ITS_UINT DiaUtils::GenerateEndToEndId()
{
    static ITS_UINT nextEId = 0;

    if (const_cast<ITS_Mutex&>(__ENDGate).Acquire() != ITS_SUCCESS)
    {
        DT_ERR(("Mutex acquisition of __ENDGate failed and proceeding with errno = %d", errno));
    }

    if (nextEId == 0)
    {
        struct timeval tv;
        gettimeofday(&tv, 0);
        srand((unsigned int)(tv.tv_sec + tv.tv_usec));

        /* Set High Order 12 bits */
        nextEId = (unsigned int)(tv.tv_sec) << 20;
    }
    /* clear lower 20 bits */
    nextEId &= 0xFFF00000;

    /* set lower 20 bits */
    nextEId |= rand() & 0x000FFFFF;

    unsigned int nextEIdLocal = nextEId;
    if (const_cast<ITS_Mutex&>(__ENDGate).Release() != ITS_SUCCESS)
    {
        DT_ERR(("Mutex release of __ENDGate failed and proceeding with errno = %d", errno));
    }

    return (nextEIdLocal);
}

ITS_UINT
DiaUtils::DataToInt(ITS_OCTET *d, ITS_INT c)
{
    unsigned int x = 0;
    int i;

    for (i = 0; i < c; i++)
    {
        x <<= 8;
        /*
         * for the first octet, make sure we sign-extend into
         * the upper bits.  Subsequent octets can just be OR'd
         * into the lower bytes after the shift.
         */
        if (i == 0)
        {
            x |= (signed char)d[i];
        }
        else
        {
            x |= d[i];
        }
    }

    return x;
}

ITS_UINT
DiaUtils::DataToUInt(ITS_OCTET *d, ITS_INT c)
{
    unsigned int x = 0;
    int i;

    for (i = 0; i < c; i++)
    {
        x <<= 8;
        /*
         * for the first octet, make sure we sign-extend into
         * the upper bits.  Subsequent octets can just be OR'd
         * into the lower bytes after the shift.
         */
        if (i == 0)
        {
            x |= (unsigned char)d[i];
        }
        else
        {
            x |= d[i];
        }
    }

    return x;
}


int
DiaUtils::EncodeMsg(diameter::Command *cmd, ITS_OCTET **buff, int& len)
{
    DT_DBG(("EncodeMsg::"));

    try
    {
        cmd->encode(*buff, len);
        return (ITS_SUCCESS);
    }
    catch (NoSuchAttributeException& e) //Fixing Big parameter passed by Value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (WrongCommandTypeException& e) //Fixing Big parameter passed by Value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (UnknownTypeException& e) //Fixing Big parameter passed by Value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (CodecException& e) //Fixing Big parameter passed by Value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));
    }

    return (!ITS_SUCCESS);
}

int
DiaUtils::DecodeMsg(DIA_BASE_CMD **cmd, const ITS_OCTET *buff, int len)
{
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;
    if (*cmd)
    {
        delete (*cmd);
        *cmd = NULL;
    }

    cmdFlag = buff[4];

    cmdCode = DataToUInt((ITS_OCTET *)&buff[5], (sizeof(ITS_UINT) - 1));

    DT_DBG(("DecodeMsg::CmdCode = %d", cmdCode));
    try
    {
        DT_DBG(("Message Received: cmdCode = %d",
                 cmdCode));
        *cmd = new DIA_BASE_CMD( buff, len,0);

	if(((*cmd)->getOriginHost())==NULL)
	{
		DT_ERR(("Mandatory AVP Missing::OriginHost"));
		//free (*cmd);
		//*cmd = NULL;
		return(ITS_DIA_MISSING_AVP);
	}

	if(((*cmd)->getOriginRealm())==NULL)
	{
		DT_ERR(("Mandatory AVP Missing::OriginRealm"));
		//free (*cmd);
		//*cmd = NULL;
		return(ITS_DIA_MISSING_AVP);
	}


	if(((*cmd)->isRequest())==true && ((*cmd)->getDestinationRealm())==NULL)
	{
		DT_ERR(("Mandatory AVP Missing::DestinationRealm"));
		//free (*cmd);
		//*cmd = NULL;
		return(ITS_DIA_MISSING_AVP);
	}
        return (ITS_SUCCESS);
    }
    catch (CodecException& e)//Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        UPDATE_DIA_STATS_DECODE_FAILED();
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (e.errcode());
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (ITS_DIA_INVALID_MSG_LENGTH);
    }

    *cmd = NULL;
    return (ITS_DIA_INVALID_AVP_LENGTH);
}

int
DiaUtils::DecodeMsg(diameter::Command **cmd, const ITS_OCTET *buff, int len)
{
    ITS_OCTET cmdFlag = 0x0;
    ITS_UINT cmdCode = 0;
    if (*cmd)
    {
        delete (*cmd);
        *cmd = NULL;
    }

    cmdFlag = buff[4];

    cmdCode = DataToUInt((ITS_OCTET *)&buff[5], (sizeof(ITS_UINT) - 1));

    DT_DBG(("DecodeMsg::CmdCode = %d", cmdCode));
    try
    {
        DT_DBG(("Message Received: cmdCode = %d",
                 cmdCode));
        *cmd = new DIA_GEN_CMD(buff, len);
        return (ITS_SUCCESS);
    }
    catch (NoSuchAttributeException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        UPDATE_DIA_STATS_DECODE_FAILED();
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (ITS_DIA_MISSING_AVP);
    }
    catch (WrongCommandTypeException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        UPDATE_DIA_STATS_DECODE_FAILED();
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (ITS_DIA_CMD_UNSUPPORTED);
    }
    catch (UnknownTypeException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        UPDATE_DIA_STATS_DECODE_FAILED();
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (ITS_DIA_INVALID_BIT_IN_HDR);
    }
    catch (CodecException& e) //Fixing Big parameter passing by value
    {
        DT_ERR(("Exception Caught: %s , Error Cause: %s ",
                         e.name(), e.what()));
        UPDATE_DIA_STATS_DECODE_FAILED();
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (e.errcode());
    }
    catch (...)
    {
        DT_ERR(("Unknown Exception Caught"));
        UPDATE_DIA_STATS_DECODE_FAILED();
        DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
        return (ITS_DIA_INVALID_MSG_LENGTH);
    }

    *cmd = NULL;
    UPDATE_DIA_STATS_DECODE_FAILED();
    DIA_Alarm(15100, __FILE__, __LINE__, "CmdCode =%d",cmdCode);
    return (ITS_DIA_INVALID_AVP_LENGTH);
}

int
DiaUtils::GetCmdFromData(DIA_BASE_CMD **cmd, ITS_OCTET *data)
{
    ITS_ULONG addr;
    memcpy(&addr, data, sizeof(ITS_ULONG));
    *cmd = (DIA_BASE_CMD*)addr;
    return ITS_SUCCESS;
}

int
DiaUtils::GetCmdFromEvent(DIA_BASE_CMD **cmd, ITS_EVENT *evt)
{
    ITS_ULONG addr;
    memcpy(&addr, evt->data, sizeof(ITS_ULONG));
    *cmd = (DIA_BASE_CMD *)addr;
    return ITS_SUCCESS;
}

int
DiaUtils::GetCmdFromEvent(DIA_GEN_CMD **cmd, ITS_EVENT *evt)
{
    ITS_ULONG addr;
    memcpy(&addr, evt->data, sizeof(ITS_ULONG));
    *cmd = (DIA_GEN_CMD *)addr;

    return ITS_SUCCESS;
}

int
DiaUtils::GetCmdFromData(DIA_GEN_CMD **cmd, ITS_OCTET *data)
{
    ITS_ULONG addr;
    memcpy(&addr, data, sizeof(ITS_ULONG));
    *cmd = (DIA_GEN_CMD *)addr;

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *        Populates and adds the Result-Code AVP to Diameter Command.
 *
 *  Input Parameters:
 *        bCmd      : Base Generic Command
 *        rsltCode  : ITS_UINT
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful addition of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::AddResultCodeAvp(DIA_BASE_CMD *&bCmd, ITS_UINT rsltCode)
{
    int ret;
    diameter::String rslt;

    ResultCode resultCode(rsltCode);
    resultCode.Encode(rslt);

    DT_DBG(("Encoded len for ResultCode AVP = %d", rslt.length()));

    if (bCmd->addAvpBuf(rslt.c_str(), rslt.length()) == 0)
    {
        DT_DBG(("Result-Code AVP Added :: %d\n", rsltCode));
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("Result-Code AVP Not Added :: %d\n", rsltCode));
        ret = !ITS_SUCCESS;
    }

    /* Make sure these deletes are removed if we move to original
       STL string */
    rslt.Free();
    return ret;
}

/****************************************************************************
 *  Purpose:
 *        Populates and adds the Redirect-Host AVP to Diameter Command.
 *
 *  Input Parameters:
 *        bCmd      : Base Generic Command
 *        uri       : URI refrence
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful addition of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::AddRedirectHostAvp(DIA_BASE_CMD *&bCmd, diameter::URI &uri)
{
    int ret;
    diameter::String Str;

    RedirectHost redirectHost( uri );
    redirectHost.Encode(Str);

    DT_DBG(("Encoded len for RredirectHost AVP = %d",Str.length() ));

    if (bCmd->addAvpBuf(Str.c_str(), Str.length()) == 0)
    {
        DT_DBG(("Redirect-Host AVP Added :: %s\n", uri.fqdn.c_str()));
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("Redirect-Host AVP Not Added :: %s\n", uri.fqdn.c_str()));
        ret = !ITS_SUCCESS;
    }
    /* Make sure these deletes are removed if we move to original
       STL string */
    Str.Free();
    return ret;
}

/****************************************************************************
 *  Purpose:
 *        Populates and adds the Redirect-Host-Usage AVP to Diameter Command.
 *
 *  Input Parameters:
 *        bCmd      : Base Generic Command
 *        redUsage  : ITS_UINT
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful addition of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::AddRedirectHostUsageAvp(DIA_BASE_CMD *&bCmd, ITS_UINT redUsage)
{
    diameter::String Str;

    switch( redUsage )
    {
        case ALL_SESSION:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::ALL_SESSION);
            hostUsage.Encode(Str);
        }
            break;

        case ALL_REALM:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::ALL_REALM);
            hostUsage.Encode(Str);
        }
            break;

        case REALM_AND_APPLICATION:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::REALM_AND_APPLICATION);
            hostUsage.Encode(Str);
        }
            break;

        case ALL_APPLICATION:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::ALL_APPLICATION);
            hostUsage.Encode(Str);
        }
            break;

        case ALL_HOST:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::ALL_HOST);
            hostUsage.Encode(Str);
        }
            break;

        case ALL_USER:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::ALL_USER);
            hostUsage.Encode(Str);
        }
            break;

        default:
        {
            RedirectHostUsage hostUsage(RedirectHostUsage::DONT_CACHE);
            hostUsage.Encode(Str);
        }
    }

    DT_DBG(("Encoded len for RedirectUsage AVP = %d",Str.length()));

    int ret;
    if (bCmd->addAvpBuf(Str.c_str(), Str.length()) == 0)
    {
        DT_DBG(("Redirect-Usage AVP Added::%d\n", redUsage));
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("Redirect-Usage AVP Not Added::%d\n", redUsage));
        ret = !ITS_SUCCESS;
    }

    /* Make sure these deletes are removed if we move to original
       STL string */
    Str.Free();

    return ret;
}

/****************************************************************************
 *  Purpose:
 *        Populates and adds the Redirect-Host-Max-Cache-Time AVP to
 *        Diameter Command.
 *
 *  Input Parameters:
 *        bCmd      : Base Generic Command
 *        time      : ITS_UINT
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful addition of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::AddRedirectHostMaxCacheTimeAvp(DIA_BASE_CMD *&bCmd, ITS_UINT time)
{
    int ret;
    diameter::String Str;

    RedirectMaxCacheTime maxCacheTime(time);
    maxCacheTime.Encode(Str);

    DT_DBG(("Encoded len for RedirectHostMaxCacheTime AVP = %d",Str.length()));

    if (bCmd->addAvpBuf(Str.c_str(), Str.length()) == 0)
    {
        DT_DBG(("Redirect-Host-Max-Cache-Time AVP Added :: %d\n", time));
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_WRN(("Redirect-Host-Max-Cache-Time AVP Not Added :: %d\n", time));
        ret = !ITS_SUCCESS;
    }

    /* Make sure these deletes are removed if we move to original
       STL string */
    Str.Free();

    return ret;
}

/****************************************************************************
 *  Purpose:
 *        Populates and adds the Route-Record AVP to Diameter Command.
 *
 *  Input Parameters:
 *        gCmd      : Base Generic Command
 *        sessInfo  : Session Entry Pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful addition of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::AddRouteRecordAvp(DIA_BASE_CMD *&gCmd, SESSION_ENTRY *sessInfo)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *entry = NULL;
    DiaSocketTransport* tr = NULL;
    unsigned int cmdCode = 0;
    ITS_USHORT peerInst = 0;

    DT_DBG(("DiaUtils::AddRouteRecordAvp"));
    if (gCmd)
    {
        cmdCode = gCmd->getCommandCode();
        if (cmdCode == DIA_MSG_RA ||
            cmdCode == DIA_MSG_AS)
        {
            peerInst = DIA_SE_PEER_INST_AGENT(sessInfo);
        }
        else
        {
            peerInst = DIA_SE_PEER_INST(sessInfo);
        }
        tr = trTable[peerInst];
        if (tr != NULL)
        {
           entry = tr->GetPeer();
           if (entry == NULL)
           {
               DT_ERR(("Peer not found for transport"));
               return ret;
           }
        }
        else
        {
            DT_ERR(("Invalid transport"));
            return ret;
        }

        DIA_GEN_CMD *ce= DIA_PE_CE_CACHE(entry);
        if (ce)
        {
            const std::string ceCacheIdentity  = (ce->getOriginHost())->value();
            RouteRecord routeRecord(ceCacheIdentity);

            //Add RouteRecordAVP directly to the encoded buffer and to the
            //Command instance(for reflecinting the included AVP in Trace File)
            diameter::String routeRecStr;
            routeRecord.Encode(routeRecStr);
            gCmd->addAvpBuf(routeRecStr.c_str(), routeRecStr.length());
	    if( DIA_SE_AGENT_TYPE(sessInfo) != ITS_DIA_RELAY)
	    {
                DIA_GEN_CMD* genCmd = (DIA_GEN_CMD*)gCmd->GetBaseGenCommand();
            	genCmd->getContainer().add(routeRecord.name(),routeRecord,false); 
            }

            /* Make sure these deletes are removed if we move to original
               STL string */
            routeRecStr.Free();

            DT_DBG(("Route-Record AVP successfully added to Message"));
            ret = ITS_SUCCESS;
        }
        else
        {
           DT_WRN(("AddRouteRecordAvp: Capabilties Exchange is not proper"));
        }
    }
    else
    {
        DT_ERR(("AddRouteRecordAvp: Invalid Msg"));
    }

    return ret;
}

int
DiaUtils::AddRouteRecordAvp(DIA_GEN_CMD *&gCmd, SESSION_ENTRY *sessInfo)
{
    int ret = (!ITS_SUCCESS);
    PEER_ENTRY *entry = NULL;
    DiaSocketTransport* tr = NULL;
    unsigned int cmdCode = 0;
    ITS_USHORT peerInst = 0;

    DT_DBG(("DiaUtils::AddRouteRecordAvp"));
    if (gCmd)
    {
        cmdCode = gCmd->getCommandCode();
        if (cmdCode == DIA_MSG_RA ||
            cmdCode == DIA_MSG_AS)
        {
            peerInst = DIA_SE_PEER_INST_AGENT(sessInfo);
        }
        else
        {
            peerInst = DIA_SE_PEER_INST(sessInfo);
        }
        tr = trTable[peerInst];
        if (tr != NULL)
        {
           entry = tr->GetPeer();
           if (entry == NULL)
           {
               DT_ERR(("Peer not found for transport"));
               return ret;
           }
        }
        else
        {
            DT_ERR(("Invalid transport"));
            return ret;
        }

        DIA_GEN_CMD *ce= DIA_PE_CE_CACHE(entry);
        if (ce)
        {
            const std::string ceCacheIdentity  = (ce->getOriginHost())->value();
            RouteRecord routeRecord(ceCacheIdentity);

            gCmd->getContainer().add(routeRecord.name(),routeRecord,false);

            DT_DBG(("Route-Record AVP successfully added to Message"));
            ret = ITS_SUCCESS;
        }
        else
        {
           DT_WRN(("AddRouteRecordAvp: Capabilties Exchange is not proper"));
        }
    }
    else
    {
        DT_ERR(("AddRouteRecordAvp: Invalid Msg"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *        Populates and adds the Proxy-Info AVP to Diameter Command.
 *
 *  Input Parameters:
 *        gCmd      : Base Generic Command
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful addition of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::AddProxyInfoAvp(DIA_GEN_CMD *&gCmd)
{
    int ret = (!ITS_SUCCESS);
    DIA_CER *lcer = NULL;

    DT_DBG(("DiaUtils::AddProxyInfoAvp"));

    if (gCmd)
    {
        ProxyInfo proxyInfo;
        lcer = itsDiaConfig.GetLocalCER();
        const std::string origHost = lcer->getOriginHost().value();
        const ProxyHost proxyHost(origHost);

        std::string state ("ProxyStateEnabled");
        const ProxyState proxyState(state);

        proxyInfo.setProxyHost(proxyHost);
        proxyInfo.setProxyState(proxyState);

        gCmd->getContainer().add(proxyInfo.name(),proxyInfo,false);
        DT_DBG(("Proxy-Info AVP successfully added to Message"));
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_ERR(("DiaMsgRouter::AddProxyInfoAvp: Invalid Msg"));
    }

    return ret;
}

int
DiaUtils::AddProxyInfoAvp(DIA_BASE_CMD *&gCmd)
{
    int ret = (!ITS_SUCCESS);
    DIA_CER *lcer = NULL;

    DT_DBG(("DiaUtils::AddProxyInfoAvp"));

    if (gCmd)
    {
        ProxyInfo proxyInfo;
        lcer = itsDiaConfig.GetLocalCER();
        const std::string origHost = lcer->getOriginHost().value();
        const ProxyHost proxyHost(origHost);

        std::string state ("ProxyStateEnabled");
        const ProxyState proxyState(state);

        proxyInfo.setProxyHost(proxyHost);
        proxyInfo.setProxyState(proxyState);

        diameter::String pxyStr;
        proxyInfo.Encode(pxyStr);

        gCmd->addAvpBuf(pxyStr.c_str(), pxyStr.length());

        /*Add Route Record AVP if DTF is enabled in BaseGenericCmd*/
        if(itsDiaConfig.IsDTFEnabled())
        {
            DIA_GEN_CMD* genCmd = (DIA_GEN_CMD*)gCmd->GetBaseGenCommand();
            genCmd->addAVP(proxyInfo, true);
        }

        /* Make sure these deletes are removed if we move to original
           STL string */
        pxyStr.Free();

        DT_DBG(("Proxy-Info AVP successfully added to Message"));
        ret = ITS_SUCCESS;
    }
    else
    {
        DT_ERR(("DiaMsgRouter::AddProxyInfoAvp: Invalid Msg"));
    }

    return ret;
}



/****************************************************************************
 *  Purpose:
 *        Checks whether correct Proxy-Info AVP is present in Diameter
 *        in command. If present removes the AVP.
 *  Input Parameters:
 *        gCmd      : Base Command
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_SUCCESS  : On successful removal of  AVP.
 *        !ITS_SUCCESS : In case of failure
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
int
DiaUtils::RemoveProxyInfoAvp(DIA_BASE_CMD *&bCmd)
{
    DIA_CER *lcer = NULL;
    int pinfoCount;

    DT_DBG(("DiaUtils::RemoveProxyInfoAvp"));

    //populate generic cmd from the buffer we have
    DIA_GEN_CMD* gCmd = new DIA_GEN_CMD((ITS_OCTET*)bCmd->getEncodedBuf(),bCmd->getEncodedBufLen());

    if (gCmd)
    {
        lcer = itsDiaConfig.GetLocalCER();
        const std::string origHost = lcer->getOriginHost().value();

        if ((pinfoCount = gCmd->countProxyInfo()) == 0)
        {
            DT_WRN(("RemoveProxyInfoAvp:: No Proxy-Info found in Message"));

            delete gCmd;
            return ITS_SUCCESS;
        }

        for (int i = 0; i < pinfoCount; i++)
        {
            ProxyInfo *proxyInfo = const_cast<ProxyInfo *> (gCmd->getProxyInfo(i));

            if (strcasecmp((proxyInfo->getProxyHost()).value().c_str(),origHost.c_str())==0)
            {
                DT_DBG(("Found Proxy-Info AVP with Local Node Identity"));
                DT_DBG(("Removing the Proxy-Info Grouped AVP"));

                //const AVP &avp1 = dynamic_cast<const AVP&> (proxyInfo->getProxyHost());
                if (proxyInfo->removeAVP(proxyInfo->getProxyHost()) == ITS_SUCCESS)
                {
                    DT_DBG(("Proxy-Host AVP removed successfully"));
                }
                else
                {
                   DT_WRN(("Unable to remove Proxy-Host AVP"));
                   delete gCmd;
                   return (!ITS_SUCCESS);
                }

                if (proxyInfo->removeAVP(proxyInfo->getProxyState()) == ITS_SUCCESS)
                {
                    DT_DBG(("Proxy-State AVP removed successfully"));
                }
                else
                {
                   DT_WRN(("Unable to remove Proxy-State AVP"));
                   delete gCmd;
                   return (!ITS_SUCCESS);
                }

                if (((DIA_CMD*)gCmd)->removeAVP(*proxyInfo) == ITS_SUCCESS)
                {
                    DT_DBG(("Proxy-Info AVP removed successfully"));

                    int len;
                    ITS_OCTET* buff = NULL;

                    ITS_OCTET* oldPtr = (ITS_OCTET*) bCmd->getEncodedBuf();
                    if (oldPtr)
                    {
                        delete [] buff; //delete old buffer
                    }

                    EncodeMsg(gCmd, &buff, len); //new buffer with proxyInfo avp removed...

                    bCmd->setEncodedBuf(buff);   //new buf is set
                    bCmd->setEncodedBufLen(len);

                    delete gCmd;    //avp removed... delete cmd obj..

                    return ITS_SUCCESS;
                }
                else
                {
                   DT_WRN(("Unable to remove Proxy-Info AVP"));
                   delete gCmd;
                   return (!ITS_SUCCESS);
                }

            }
        }

        DT_DBG(("RemoveProxyInfoAvp:: Proxy-Info AVP(s) in the Message does" \
                " not matches with Local Node Identity"));
    }
    else
    {
        DT_ERR(("DiaUtils::RemoveProxyInfoAvp: Invalid Msg"));
    }

    if (gCmd)
        delete gCmd;

    return (!ITS_SUCCESS);
}

/****************************************************************************
 *  Purpose:
 *        Checks whether Result-Code AVP is modified from success to failure
 *        in Diameter command.
 *
 *  Input Parameters:
 *        gCmd      : Diameter Base Command
 *        ent       : Session Entry Pointer
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *        ITS_TRUE  : If result code modified.
 *        ITS_FALSE : if result code not modified.
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
ITS_BOOLEAN
DiaUtils::IsResultCodeModified(DIA_BASE_CMD *&gCmd, SESSION_ENTRY *ent)
{
    ITS_BOOLEAN rCodeEntSucc, rCodeMsgSucc;
    ITS_UINT resFinal = DIA_SE_RESULT_CODE(ent);
    ITS_UINT rCodeMsg = 0;
    ITS_BOOLEAN found = ITS_FALSE;

    if (gCmd->getResultCode())
    {
        rCodeMsg = (gCmd->getResultCode())->value();
    }

    if(DIA_SE_IS_AGENT(ent) &&
       !(gCmd->isRequest()) &&
       (rCodeMsg != DIA_SE_RESULT_CODE(ent)))

    {
        DT_DBG(("DiaUtils::IsResultCodeModified"));

        switch (gCmd->getCommandCode())
        {
        case DIA_MSG_ST:
             DT_DBG(("Session Termination Answer. Discarding ResultCode" \
                     "Changes."));
             found = ITS_TRUE;
             break;
        case DIA_MSG_AS:
             DT_DBG(("Abort Session Answer. Discarding ResultCode Changes."));
             found = ITS_TRUE;
             break;
        case DIA_MSG_RA:
             DT_DBG(("Re-Auth Answer. Discarding ResultCode Changes."));
             found = ITS_TRUE;
             break;
        case DIA_MSG_AC:
             if ((gCmd->getAccountingRecordType()->value() ==
                  AccountingRecordType::EVENT_RECORD)          ||
                 (gCmd->getAccountingRecordType()->value() ==
                  AccountingRecordType::STOP_RECORD))
             {
                 DT_DBG(("Accounting Event or Stop Answer.Discarding" \
                         "ResultCode Changes."));
                 found = ITS_TRUE;
             }
             break;
        default:
             break;
        }

        if (found == ITS_TRUE)
        {
            DT_DBG(("Keeping ResultCode value received from Peer in Message"));
            resFinal = DIA_SE_RESULT_CODE(ent);

            gCmd->setResultCode(resFinal);
            return ITS_FALSE;
        }

        if ((DIA_SE_RESULT_CODE(ent) >= ITS_DIA_SUCCESS_MIN_RANGE) &&
            (DIA_SE_RESULT_CODE(ent) <= ITS_DIA_SUCCESS_MAX_RANGE))
        {
            rCodeEntSucc = ITS_TRUE;

        }
        else
        {
            rCodeEntSucc = ITS_FALSE;
        }

        if ((rCodeMsg >= ITS_DIA_SUCCESS_MIN_RANGE) &&
            (rCodeMsg <= ITS_DIA_SUCCESS_MAX_RANGE))
        {
            rCodeMsgSucc = ITS_TRUE;
        }
        else
        {
            rCodeMsgSucc = ITS_FALSE;
        }


        if (rCodeEntSucc && !rCodeMsgSucc)
        {
            DT_DBG(("The ResultCode AVP modified by the Application"));

            if ((rCodeMsg >= ITS_DIA_PROT_ERR_MIN_RANGE &&
                rCodeMsg <= ITS_DIA_PROT_ERR_MAX_RANGE) && !(gCmd->isError()))
            {
                DT_WRN(("Protocol Error without E-bit set." \
                        " Discarding Modification"));
            }
            else
            {
               DT_DBG(("Received from Peer: %d, Received from App: %d",
                                         DIA_SE_RESULT_CODE(ent), rCodeMsg));
               DT_DBG(("Value modified from Success to Failure in message"));

               DIA_SE_RESULT_CODE(ent) = rCodeMsg;
               return ITS_TRUE;
            }
        }
        DT_DBG(("Received from Peer: %d, Received from App: %d",
                            DIA_SE_RESULT_CODE(ent), rCodeMsg));

        DT_DBG(("Values differ, but keeping ResultCode value received" \
                " from Peer in Message"));
        resFinal = DIA_SE_RESULT_CODE(ent);

        gCmd->setResultCode(resFinal);
        return ITS_FALSE;
    }
    return ITS_FALSE;
}

#ifdef TLS_ENABLED
/****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *        cipherSuite      : Type of CipherSuite
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *        ITS_INT* : Array of Integers
 *
 *  Return Value:
 *        None
 *  Notes:
 *        None.
 *
 *  See Also:
 *        None
 *
 ****************************************************************************/
void
DiaUtils::PopulateCipherSuiteList(DIA_CIPHER_SUITE cipherSuite, ITS_INT* list)
{
    ITS_INT suiteList[CIPHER_SUITE_LIST] = {0};
    DT_DBG(("PopulateCipherSuiteList"));
    DT_DBG(("PopulateCipherSuiteList: CipherSuite is %s", DIA_CIPHER_TYPE_TO_TEXT(cipherSuite)));

    switch (cipherSuite)
    {
    case  TLS_RSA_WITH_RC4_128_MD5:
        suiteList[0] = TLS_RSA_ARCFOUR_MD5;
        suiteList[1] = 0;

    break;

    case  TLS_RSA_WITH_RC4_128_SHA:
        suiteList[0] = TLS_RSA_ARCFOUR_SHA;
        suiteList[1] = 0;
    break;

    case  TLS_RSA_WITH_3DES_EDE_CBC_SHA:
        suiteList[0] = TLS_RSA_3DES_EDE_CBC_SHA;
        suiteList[1] = 0;
    break;

    case  TLS_RSA_WITH_AES_128_CBC_SHA:
        suiteList[0] = TLS_RSA_AES_128_CBC_SHA;
        suiteList[1] = 0;
    break;

    case  TLS_RFC_3588_ALL:
        suiteList[0] = TLS_RSA_ARCFOUR_MD5;
        suiteList[1] = TLS_RSA_ARCFOUR_SHA;
        suiteList[2] = TLS_RSA_3DES_EDE_CBC_SHA;
        suiteList[3] = TLS_RSA_AES_128_CBC_SHA;
        suiteList[4] = 0;
    break;

    default:
        list[0] = NULL;
        return;
    }
    memcpy(list, suiteList, (CIPHER_SUITE_LIST) * sizeof(ITS_INT));
}

void
DiaUtils::PopulateCipherSuiteList(ITS_INT* list)
{
    ITS_INT suiteList[CIPHER_SUITE_LIST] = {0};
    DT_DBG(("PopulateCipherSuiteList"));

    ITSDiaConfig *cfg =  &itsDiaConfig;
    ITSDiaConfig::SecurityConfig& secConf = cfg->GetSecurityConfig();

    ITS_INT cipherCount = secConf.GetCipherCount();
    ITS_INT count = 0;

    for(int i=0; i < cipherCount; i++)
    {

        if (strcmp(secConf.GetCipherAt(i).c_str(),"TLS_RSA_WITH_RC4_128_MD5") == 0)
        {
            suiteList[count++] = TLS_RSA_ARCFOUR_MD5;
            suiteList[count] = 0;
        }
        
        else if (strcmp(secConf.GetCipherAt(i).c_str(),"TLS_RSA_WITH_RC4_128_SHA") == 0)
        {
            suiteList[count++] = TLS_RSA_ARCFOUR_SHA;
            suiteList[count] = 0;
        }

        else if (strcmp(secConf.GetCipherAt(i).c_str(),"TLS_RSA_WITH_3DES_EDE_CBC_SHA") == 0)
        {
            suiteList[count++] = TLS_RSA_3DES_EDE_CBC_SHA;
            suiteList[count] = 0;
        }

        else if (strcmp(secConf.GetCipherAt(i).c_str(),"TLS_RSA_WITH_AES_128_CBC_SHA") == 0)
        {
            suiteList[count++] = TLS_RSA_AES_128_CBC_SHA;
            suiteList[count] = 0;
        }

        else if (strcmp(secConf.GetCipherAt(i).c_str(), "TLS_RSA_WITH_NULL_MD5") == 0)
        {
            suiteList[count++] = TLS_RSA_NULL_MD5;
            suiteList[count] = 0;
        }

        else if (strcmp(secConf.GetCipherAt(i).c_str(), "TLS_RSA_WITH_NULL_SHA") == 0)
        {
           suiteList[count++] = TLS_RSA_NULL_SHA;
           suiteList[count] = 0;
        }

        else if (strcmp(secConf.GetCipherAt(i).c_str(), "TLS_RSA_WITH_DES_CBC_SHA") == 0)
        {
            suiteList[count++] = TLS_RSA_DES_CBC_SHA;
            suiteList[count] = 0;
        }
        else if (strcmp(secConf.GetCipherAt(i).c_str(), "TLS_RSA_WITH_AES_256_CBC_SHA") == 0)
        {
           suiteList[count++] =  TLS_RSA_AES_256_CBC_SHA;
           suiteList[count] = 0;
        }

        else
        {
            DT_DBG(("Cipher-suite not supported"));
        }
    }

    memcpy(list, suiteList, (CIPHER_SUITE_LIST) * sizeof(ITS_INT));
}
#endif

int
DiaUtils::PutEventReference(ITS_USHORT dest, ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS;

    if (evt == NULL)
    {
        DT_ERR(("DiaUtils::PutEventReference Null pointer found"));
        return !ITS_SUCCESS;
    }
    //accessing evt members down after check to NULL
    ITS_OCTET *evtData = evt->data;
    ITS_USHORT evtLen = evt->len;
    ITS_EVENT outEvt;
    ITS_EVENT_INIT(&outEvt, evt->src, sizeof(ITS_USHORT)+sizeof(ITS_ULONG));

    /* Copy evt len */
    memcpy(outEvt.data, &evtLen, sizeof(ITS_USHORT));

    /* Copy evt data address */
    memcpy(&outEvt.data[sizeof(ITS_USHORT)], &evtData, sizeof(ITS_ULONG));

    /* Let other thread free the data */
    evt->data = NULL;

    if ((ret = TRANSPORT_PutEvent(dest, &outEvt)) != ITS_SUCCESS)
    {
        DT_ERR(("DiaUtils::PutEventReference PutEvent Failed"));
        ITS_EVENT_TERM(&outEvt);
    }
    return ret;
}

int
DiaUtils::GetEventReference(its::Event *inEvt, ITS_EVENT *outEvt)
{
    ITS_USHORT evtLen = 0;
    ITS_OCTET* evtData = NULL;

    if (inEvt == NULL || outEvt == NULL)
    {
        DT_ERR(("DiaUtils::GetEventReference Null pointer found"));
        return !ITS_SUCCESS;
    }

    outEvt->src = inEvt->GetSource();
    memcpy(&evtLen, inEvt->GetData(),sizeof(ITS_USHORT));
    memcpy(&evtData, &inEvt->GetData()[sizeof(ITS_USHORT)],
                                            sizeof(ITS_ULONG));
    outEvt->len  = evtLen;
    outEvt->data = evtData;

    return ITS_SUCCESS;
}

bool 
DiaUtils::IsIPv6Address(const char *ipStr)
{
    // IPv6 addresses has ':'
    while(*ipStr != '\0')
    {
        if (*ipStr == ':')
        {
            return true;
        }
        ipStr++;
    }
    return false;
}

int
DiaUtils::GetSessionString(ITS_OCTET* data, std::string &str)
{
    ITS_INT ret = ITS_SUCCESS;
    ITS_UINT avpCode = 0;
    ITS_UINT len = 0;
    ITS_CHAR buff[SESS_MAX_BUF_SIZE];

    DT_DBG(("DiaUtils::GetSessionString"));

    memset(buff, '\0', sizeof(buff));

    avpCode = DiaUtils::DataToInt(&data[DIA_SESID_AVP_CODE_POS],(sizeof(ITS_UINT)));
    len = DiaUtils::DataToInt(&data[DIA_SESID_AVP_LEN_POS],(sizeof(ITS_UINT) - 1));

    DT_DBG(("GetSessionString: AVP Code %d", avpCode));
    DT_DBG(("GetSessionString: AVP len  %d", len));



    if ( (avpCode != 263) || ( len <= (sizeof(ITS_UINT)*2) ) )
    {
        DT_DBG(("GetSessionString: Session AVP not found"));

        str = "";

        return (ITS_ENOTFOUND);
    }
    len = len - (sizeof(ITS_UINT)*2);

    memcpy(buff, &data[DIA_SESID_AVP_DATA_POS], len);
    str = buff;

    DT_DBG(("GetSessionString: Session string <%s> <%d>",
                                         str.c_str(), str.size()));

    return ITS_SUCCESS;
}

int
DiaUtils::GetStackTQInst(const char* sessId)
{
    ITS_USHORT dest = DIASTACK_TQ_INST;
    int tqInst = 0;
    if (sessId && itsDiaConfig.IsQueueMgmtEnabled())
    {
        unsigned int sessKey = 0;

        sessKey = HASH_MakeKey(sessId, strlen(sessId));
        int numThreads =
                itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();
        tqInst = sessKey%numThreads;

        DT_DBG(("Session Id =%s, SessionId Key =%d, TQ=%d",
                                 sessId, sessKey, tqInst));
     }
     dest = DIASTACK_TQ_INST + tqInst;
     return dest;
}

int
DiaUtils::GetStackTQInst(DIA_BASE_CMD *bCmd)
{
    ITS_USHORT dest = DIASTACK_TQ_INST;
    int tqInst = 0;
    if (itsDiaConfig.IsQueueMgmtEnabled())
    {
        if (bCmd->getSessionId())
        {
            unsigned int sessKey = 0;
            const char* sessId =
                  bCmd->getSessionId()->value().c_str();

            sessKey = HASH_MakeKey(sessId, strlen(sessId));
            int numThreads =
                itsDiaConfig.GetQueueMgmt().GetMsgRouterThreadCount();
            tqInst = sessKey%numThreads;

            DT_DBG(("Session Id =%s, SessionId Key =%d, TQ=%d",
                                 sessId, sessKey, tqInst));
        }
    }
    dest = DIASTACK_TQ_INST + tqInst;
    return dest;
}

bool DiaUtils::CompareIPAddress(const char *ipStrFirst,const char *ipStrSecond , int addrFamily)
{

    DT_DBG(("ENTER CompareIPAddress"));
    bool retVal=false;
    char buff[INET6_ADDRSTRLEN];
    if( (NULL == ipStrFirst) || (NULL == ipStrSecond) )
    {
        DT_DBG(("Null IP Passed to CompareIPAddress")); 
        return retVal;
    }
    DT_DBG((" ipStrFirst = %s : ipStrSecond = %s : addrFamily = %d ",ipStrFirst,ipStrSecond,addrFamily));
    if( addrFamily == AF_INET)
    {
        DT_DBG((" :: AF_INET :: IpV4 Address Comparision"));
        if((inet_pton(AF_INET, ipStrSecond, buff)) != 1)
        {
            DT_DBG(("Configured: %s is either DNS or invalid IP, returning!", ipStrSecond));
            retVal = true;
            return retVal;
        }
        if(strncmp(ipStrFirst, ipStrSecond, INET6_ADDRSTRLEN) == NULL)
        {
            DT_DBG(("IP Compare Success"));
            retVal=true;
        }
        else
        {
            DT_DBG(("IP Compare Failed"));
        }
    }
    else  if( addrFamily == AF_INET6)
    { 
        if((inet_pton(AF_INET6, ipStrSecond, buff)) != 1)
        {
            DT_DBG(("Configured: %s is either DNS or invalid IP, returning!", ipStrSecond));
            retVal = true;
            return retVal;
        }
        DT_DBG((" :: AF_INET6 :: IpV6 Address Comparision"));
        struct in6_addr firstAddr_in6;
        struct in6_addr secondAddr_in6;
        if ( inet_pton(AF_INET6, ipStrFirst, &firstAddr_in6) > 0)
        {
            if ( inet_pton(AF_INET6, ipStrSecond, &secondAddr_in6) > 0)
            {
                if( strncmp( (const char *)firstAddr_in6.s6_addr, (const char *)secondAddr_in6.s6_addr, INET6_ADDRSTRLEN) == NULL)
                {
                    DT_DBG(("IP Compare Success"));
                    retVal=true;
                }
                else
                {
                    DT_DBG(("IP Compare Failed"));
                }	
            }
            else 
            {    
                DT_DBG(("inet_pton failure for the  ipV6Add:: Second-IP = %s\n",ipStrSecond));
            } 
        }
        else
        {
            DT_DBG(("inet_pton failure for the  ipV6Add:: First-IP = %s\n",ipStrFirst));
        }


    }
    else
    {
        DT_DBG(("Undefined Address Family : addrFamily = %d ",addrFamily));
    }
    DT_DBG(("LEAVE CompareIPAddress : retVal = %d ",retVal));
    return retVal;
}
