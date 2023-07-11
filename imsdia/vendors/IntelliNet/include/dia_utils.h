/*********************************-*HPP*-************************************
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
 * LOG: $Log: dia_utils.h,v $
 * LOG: Revision 3.13.2.1.2.6.4.1.4.2.8.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.13.2.1.2.6.4.1.4.2  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.13.2.1.2.6.4.1.4.1  2013/12/09 04:52:43  ncshivakumar
 * LOG: Fixed bug 2439,2443,2368,1898
 * LOG:
 * LOG: Revision 3.13.2.1.2.6.4.1  2013/03/21 12:31:37  mallikarjun
 * LOG: Bug-1194-changes
 * LOG:
 * LOG: Revision 3.13.2.1.2.6  2012/12/03 09:51:42  rsanjay
 * LOG: Dre service script packaging changes
 * LOG:
 * LOG: Revision 3.13.2.1.2.5  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.13.2.1.2.2.8.1  2012/11/20 10:28:35  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.13.2.1.2.3  2012/11/06 16:31:20  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.13.2.1.2.2.12.1  2012/11/06 08:52:13  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.13.2.1.2.2  2012/10/19 17:54:43  brajappa
 * LOG: BugId 15: IPv6 support enhancements
 * LOG:
 * LOG: Revision 3.13.2.1.2.1  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.13.2.1.4.1  2012/08/21 06:16:25  jvikas
 * LOG: Checkin Working Modified Stack Code -Need to Cleanup and Fix Issues.
 * LOG:
 * LOG: Revision 3.13.2.1  2012/03/07 13:23:08  brajappa
 * LOG: Changes made for the DRE demo
 * LOG:
 * LOG: Revision 3.13  2011/08/23 04:06:51  vkumara
 * LOG: Added DataToUInt to fix CmdCode decode error for an unsigned values from abnf.
 * LOG: (Extra FF was returning from existing DataToInt ()).
 * LOG:
 * LOG: Revision 3.12  2009/07/13 06:09:23  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.11  2009/06/29 14:49:07  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.10  2009/03/03 10:21:16  nvijikumar
 * LOG: PutEventReference and GetEventReference utility functions provided
 * LOG: to simulate AddTailNoCopy concept (Performance changes)
 * LOG:
 * LOG: Revision 3.9  2009/02/03 10:15:56  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.8  2009/01/06 14:02:16  nvijikumar
 * LOG: Removed GetSessionId API since it is not used
 * LOG:
 * LOG: Revision 3.7  2008/12/23 08:27:56  rajeshak
 * LOG: Moved and renamed InitNInsertAcctSession & InitNInsertAuthSession function
 * LOG: from dia_utils to dia_session_table
 * LOG:
 * LOG: Revision 3.6  2008/12/12 17:57:02  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.5  2008/12/07 09:35:32  rajeshak
 * LOG: Added two new functions InitNInsertAcctSession and InitNInsertAuthSession to avoid code duplication
 * LOG:
 * LOG: Revision 3.4  2008/07/31 06:18:37  sureshj
 * LOG: Code is Put under Tls Enabled Tag
 * LOG:
 * LOG: Revision 3.3  2008/06/13 11:18:47  hbhatnagar
 * LOG: Made changes for the TLS implementation and also related xml parsing.
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:10:03  hbhatnagar
 * LOG: Changes for Proxy and Relay support 3.0 release - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/10/16 06:17:29  yranade
 * LOG: Cleanup.
 * LOG:
 * LOG: Revision 2.3  2006/10/07 12:24:55  yranade
 * LOG: Today's round of updates.
 * LOG:
 * LOG: Revision 2.2  2006/10/05 13:00:22  yranade
 * LOG: Getting there.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:44  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:29  yranade
 * LOG: Initial Version of ITS-Diameter (Yogesh, Viji, Tushar)
 * LOG:
 * ID: $Id: dia_utils.h,v 3.13.2.1.2.6.4.1.4.2.8.1 2014/07/02 06:37:11 millayaraja Exp $
 ****************************************************************************/
#ident "$Id: dia_utils.h,v 3.13.2.1.2.6.4.1.4.2.8.1 2014/07/02 06:37:11 millayaraja Exp $"

#ifndef DIA_UTILS_H
#define DIA_UTILS_H

#include <its_types.h>
#include <dia_cmn.h>
#include <dia_peer_table.h>
#include <dia_session_table.h>
#include <itsdiameter.h>


#define REQUEST_BIT_SET(x)      (x & 0x80)
#define PROXY_BIT_SET(x)        (x & 0x40)
#define ERROR_BIT_SET(x)        (x & 0x20)
#define RETRANSMIT_BIT_SET(x)   (x & 0x10)
/* Max Buffer Size */
#define SESS_MAX_BUF_SIZE            255
#define DIA_SESID_AVP_CODE_POS         20
#define DIA_SESID_AVP_LEN_POS          25
#define DIA_SESID_AVP_DATA_POS         28     

#define SET_REQUEST_BIT(x)      (x | 0x80)
#define SET_PROXY_BIT(x)        (x | 0x40)
#define SET_ERROR_BIT(x)        (x | 0x20)
#define SET_RETRANSMIT_BIT(x)   (x | 0x10)

#define SCRIPT "tlsScript.sh "


#define SET_REQUEST_BIT(x)      (x | 0x80)
#define SET_PROXY_BIT(x)        (x | 0x40)
#define SET_ERROR_BIT(x)        (x | 0x20)
#define SET_RETRANSMIT_BIT(x)   (x | 0x10)

#define DIA_SET_INT(b, v)                      \
    ((b)[0] = (ITS_OCTET)(((v) >> 24) & 0xFF),  \
     (b)[1] = (ITS_OCTET)(((v) >> 16) & 0xFF),  \
     (b)[2] = (ITS_OCTET)(((v) >> 8) & 0xFF),   \
     (b)[3] = (ITS_OCTET)((v) & 0xFF))
#define DIA_GET_INT(b)                         \
    (((b)[0] << 24) | ((b)[1] << 16) |          \
     ((b)[2] << 8) | (b)[3])


#define DIA_SET_HOP_BY_HOP    DIA_SET_INT
#define DIA_SET_END_TO_END    DIA_SET_INT

#define DIA_SET_CMD_CODE(b, v)                  \
     (b)[0] = (ITS_OCTET)(((v) >> 16) & 0xFF),  \
     (b)[1] = (ITS_OCTET)(((v) >> 8) & 0xFF),   \
     (b)[2] = (ITS_OCTET)((v) & 0xFF)


enum DiaSendFlags
{
    DIA_SEND_FLAG_REL_SESSION = 0x0001,
};

typedef struct DiaMsgToPeerEvtT
{
    DIA_BASE_CMD *cmd;
    ITS_UINT     sessionIdx;
    ITS_UINT     flags;
    ITS_USHORT   toPeer;
}DiaMsgToPeerEvt;

#define DIA_CMD_FLAG_POS    4
#define DIA_VERSION_POS 0
#define DIA_CMD_CODE_POS    5
#define DIA_APP_ID_POS    8

void PRINT_EVENT(ITS_EVENT* evt);

class DiaUtils
{
public:
    DiaUtils() {}

    ~DiaUtils() {}
    
    static void InitTrustedCAs(std::string masterCA, std::string cAPath, std::string cAFiles);
    
    static void HmiSleep(HMIThread_Info* hmiInfo, ITS_INT val);

    static ITS_UINT GenerateHopByHopId();

    static ITS_UINT GenerateEndToEndId();

    static ITS_UINT DataToInt(ITS_OCTET *d, ITS_INT c);

    static int EncodeMsg(diameter::Command *cmd, ITS_OCTET **buff, int& len);

    static int DecodeMsg(DIA_BASE_CMD **cmd, const ITS_OCTET *buff, int len);

    static int DecodeMsg(diameter::Command **cmd, const ITS_OCTET *buff, int len);

    static int GetCmdFromEvent(DIA_BASE_CMD **cmd, ITS_EVENT *evt);

    static int GetCmdFromEvent(DIA_GEN_CMD **cmd, ITS_EVENT *evt);

    static int GetCmdFromData(DIA_GEN_CMD **cmd, ITS_OCTET *data);

    static int GetCmdFromData(DIA_BASE_CMD **cmd, ITS_OCTET *data);

    static ITS_UINT DataToUInt(ITS_OCTET *d, ITS_INT c);

    /**
     * API for agents to add the Route-Record AVP.
     */   
    static int AddRouteRecordAvp(DIA_GEN_CMD *&gCmd, SESSION_ENTRY *sessInfo);

    static int AddRouteRecordAvp(DIA_BASE_CMD *&gCmd, SESSION_ENTRY *sessInfo);

    /**
     * API for relay to add the Proxy-Info  AVP.
     */   
    static int AddProxyInfoAvp(DIA_GEN_CMD *&gCmd);

    static int AddProxyInfoAvp(DIA_BASE_CMD *&gCmd);
    /**
     * API for relay to add the Remove Proxy Info AVP.
     */ 
    static int RemoveProxyInfoAvp(DIA_GEN_CMD *&gCmd);

    static int RemoveProxyInfoAvp(DIA_BASE_CMD *&gCmd);

    /**
     * API for proxy agent to check if Result-Code AVP is modified 
     * by Applicaiton.
     */
    static ITS_BOOLEAN IsResultCodeModified(DIA_BASE_CMD *&gCmd,
                                             SESSION_ENTRY *ent);
    static ITS_BOOLEAN IsResultCodeModified(DIA_GEN_CMD *&gCmd,
                                             SESSION_ENTRY *ent);
    /**
     * API to populate the CipherSuiteList as per xml configuration
     */
#ifdef TLS_ENABLED
    static void PopulateCipherSuiteList(DIA_CIPHER_SUITE cipherSuite, ITS_INT* list);
    static void PopulateCipherSuiteList(ITS_INT* list);
#endif

    /**
     * API to add the Result-Code AVP in Base Command (Use by Redirect Agent).
     */
    static int AddResultCodeAvp(DIA_BASE_CMD *&bCmd, ITS_UINT rsltCode);

    /**
     * API for Redirect Agent to add the Redirect-Host AVP.
     */
    static int AddRedirectHostAvp(DIA_BASE_CMD *&bCmd, diameter::URI &uri);

    /**
     * API for Redirect Agent to add the Redirect-Host-Usage AVP.
     */
    static int AddRedirectHostUsageAvp(DIA_BASE_CMD *&bCmd, ITS_UINT redUsage);

    /**
     * API for Redirect Agent to add the Redirect-Host-Max-Cache-Time AVP.
     */
    static int AddRedirectHostMaxCacheTimeAvp(DIA_BASE_CMD *&bCmd, 
                                                               ITS_UINT time);
    
    static int PutEventReference(ITS_USHORT dest, ITS_EVENT *evt);
    static int GetEventReference(its::Event *inEvt, ITS_EVENT *OutEvt);

    //
    // Returns true if the ipStr pointed is an IPv6 address. False otherwise
    //
    static bool IsIPv6Address(const char *ipStr);
 
    static bool CompareIPAddress(const char *ipStrFirst,const char *ipStrSecond , int addrFamily=AF_UNSPEC);
    static int GetSessionString(ITS_OCTET* data, std::string &str);
    static int GetStackTQInst(const char* sessId);
    static int GetStackTQInst(DIA_BASE_CMD *bCmd);

private:
};

#endif


