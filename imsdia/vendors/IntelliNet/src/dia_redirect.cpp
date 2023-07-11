/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_redirect.cpp,v $
 * LOG: Revision 1.8.10.4.6.2.18.1  2017/12/21 04:37:21  jkchaitanya
 * LOG: Ticket 1149 changes to support case insensitivity for peers, hosts 7 realms
 * LOG:
 * LOG: Revision 1.8.10.4.6.2  2013/04/18 13:38:24  jsarvesh
 * LOG: changes done for interface stats increment for req in message
 * LOG:
 * LOG: Revision 1.8.10.4.6.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 1.8.10.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 1.8.34.2  2012/11/20 10:31:24  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 1.8  2009/09/07 06:24:00  rajeshak
 * LOG: Klockworks reported Issue fix.
 * LOG:
 * LOG: Revision 1.7  2009/05/12 08:42:31  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 1.6  2009/03/19 16:22:15  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 1.5  2009/03/19 12:37:16  nvijikumar
 * LOG: Global instance is created for the Class ITSDiaConfig to avoid function
 * LOG: call overhead as ITSDiaConfig::GetITSDiaConfig() was called max time
 * LOG:
 * LOG: Revision 1.4  2009/02/19 14:04:57  ssaxena
 * LOG: Partial fix for the whizible issue Id 1493, 1481 and 1482.
 * LOG: Default routing failed and Relay/Proxy failed to forward
 * LOG: ASR/RAR.
 * LOG:
 * LOG: Revision 1.3  2009/02/19 13:16:10  ssaxena
 * LOG: Change in signature of HandleRedirectReqMsg from its::Event to
 * LOG: ITS_USHORT. Performance changes(Viji).
 * LOG:
 * LOG: Revision 1.2  2009/02/05 09:56:30  ssaxena
 * LOG: Changes for Redirect Agent code reviews.
 * LOG:
 * LOG: Revision 1.1  2009/02/03 10:19:46  ssaxena
 * LOG: Added a new src file for Redirect Agent functionality.
 * LOG:
 ****************************************************************************/

#include <its++.h>
#include <engine++.h>

#include <dia_utils.h>
#include <dia_msg_router.h>
#include <dia_redirect.h>
#include <dia_cache_table.h>
#include <dia_stack.h>
#include <DiameterDictionaryStats.h>



#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
#endif


/*.implementation:static
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
DiaRedirectHandler::HandleRedirectReqMsg( DIA_BASE_CMD *&cmd,
                                          REALM_ENTRY *&rEntry,
                                          ITS_USHORT trInst)
{
    /*update the stats for number of request message received for dictionary
     * id*/
     DIA_INC_INTERFACE_TOTAL_REQUEST_RECEIVED(cmd->GetDictId(),(cmd->getCommandCode()));
    int ret;
    DiaSocketTransport *tr = NULL;
    DIA_BASE_CMD *bCmd = (DIA_BASE_CMD *)cmd;
    DIA_HDR &hdr = (DIA_HDR&)bCmd->getHeader();
    ITS_UINT rhCount = 0;

    /**
     * If cmd is Not Proxyable, then it is not redirect request.
     */
    if (!cmd->isProxyable())
    {
        DT_ERR(("Non-Proxiable message received for Agent"));
        return !ITS_SUCCESS;
    }

    DT_DBG(("DiaRedirectHandler::HandleRedirectReqMsg\n"));
    /**
     * Modifying Header Flag's in encoded buffer.
     */
    unsigned char* buffer = (unsigned char *)cmd->getEncodedBuf();
    buffer[4] = (buffer[4] & ~0x80);
    buffer[4] = (buffer[4] | 0x20);

    /**
     * Adding Result Code AVP.
     */
    DT_DBG(("Adding Result Code AVP"));
    int rsltCode = ITS_DIA_REDIRECT_INDICATION;

    if (DiaUtils::AddResultCodeAvp( bCmd, rsltCode ) != ITS_SUCCESS)
    {
        return !ITS_SUCCESS;
    }

    /**
     * Adding Redirect-Host AVPs.
     */
    for ( int i=0; i < DIA_RE_DEST_CNT(rEntry) &&
                   DIA_RE_REDIRECT_HOST(rEntry, i) != NULL;
                   i++ )
    {
        if ( DIA_RE_DEST_APP_ID( rEntry , i ).appId == hdr.appId )
        {
            const char *dHost = DIA_RE_REDIRECT_HOST(rEntry, i);
            URI uri(dHost, URI::AAA, 3880, URI::TCP, URI::DIAMETER);

            DT_DBG(("Adding Redirect Host AVP"));
            if (DiaUtils::AddRedirectHostAvp(bCmd, uri) != ITS_SUCCESS)
            {
                continue;
            }
            rhCount++;
        }
    }
    if ( rhCount == 0 )
    {
        DT_ERR(("No Redirect-Host AVP added in Ans"));
        return !ITS_SUCCESS;
    }

    /**
     * Adding Redirect-Host-Usage AVP.
     */
    DT_DBG(("Adding Redirect Host Usage AVP"));
    ITS_UINT rdUsage = DIA_RE_REDIRECT_USAGE(rEntry);
    if (DiaUtils::AddRedirectHostUsageAvp( bCmd, rdUsage ) != ITS_SUCCESS)
    {
        DT_WRN(("Redirect-Usage AVP failed to added"));
    }

    /**
     * Adding Redirect-Host-Max-Cache-Time AVP.
     */
    DT_DBG(("Adding Redirect Host Max Cache Time AVP"));
    ITS_UINT time = DIA_RE_REDIRECT_MAX_TIME(rEntry);
    if (DiaUtils::AddRedirectHostMaxCacheTimeAvp( bCmd, time ) != ITS_SUCCESS)
    {
        DT_WRN(("Redirect-Max-Cache-Time AVP failed to added"));
    }

    /**
     * Sending Redirected Answer.
     */
    tr = trTable[trInst];

    if ( tr != NULL)
    {
        if( DiaMsgRouter::SendCmdToPeer(trInst, &hdr, bCmd) == ITS_SUCCESS )
        {
            DT_DBG(("Send Redirected Ans to Peer :: SUCCESS"));
            return ITS_SUCCESS;
        }
        else
        {
            DT_ERR(("Send Redirected Ans to Peer :: FAILED"));
            return !ITS_SUCCESS;
        }
    }
    DT_WRN(("Requested Peer is Not UP."));
    return !ITS_SUCCESS;
}

/*.implementation:static
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
DiaRedirectHandler::HandleRedirectedAnsMsg( DIA_BASE_CMD *&cmd,
                                           PEER_ENTRY *&pEntry)
{
    int ret = !ITS_SUCCESS;
    DIA_BASE_CMD *bCmd = (DIA_BASE_CMD *)cmd;
    DIA_HDR &hdr = (DIA_HDR&)bCmd->getHeader();
    DiaSocketTransport *tr = NULL;
    ITS_USHORT trInst = 0;
    bool foundDestUp = false;
    ITS_UINT rhCount=0;
    const char *destHost;
    PEER_ENTRY *newPentry = NULL;
    SESSION_ENTRY *ent = NULL;
    const char *sessId;
    CACHE_ENTRY *cEntry = NULL;
    std::string cacheKey;
    ITS_UINT maxCacheTime = 0;
    DIA_BASE_CMD *reqMsg = NULL;
 
 
    /**
     * Check Session Id.
     */
    if (bCmd->getSessionId() != NULL)
    {
        sessId = bCmd->getSessionId()->value().c_str();

        if (SESSION_TABLE->FindEntry(ent,
                                     (ITS_OCTET *)sessId,
                                     strlen(sessId)) != ITS_SUCCESS)
        {
            DT_ERR(("Session Entry Not found...Discarding"));
            return !ITS_SUCCESS;
        }
    }
    else
    {
        return !ITS_SUCCESS;
    }

    /**
     * Check Hop-by-hop Id.
     * For relay and proxy check with local Hop-by-Hop Id. 
     * For local check with receive Hop-by-Hop Id. 
     */
    if ( (DIA_SE_IS_AGENT(ent) && (hdr.hh != DIA_SE_LOCAL_HH(ent))) ||
         (!DIA_SE_IS_AGENT(ent) && (hdr.hh != DIA_SE_RX_HH(ent))) )
     {
        DT_ERR(("Invalid Hop-by-Hop id received in answer message"));
        return !ITS_SUCCESS;
     }

    DT_DBG(("DiaRedirectHandler::HandleRedirectedAnsMsg\n"));

    /**
     * Get the Redirect-Host AVPs Count.
     */
    if ((rhCount = bCmd->countRedirectHost()) == 0)
    {
        DT_ERR(("RedirectHost AVP Not found in Message"));
        return !ITS_SUCCESS;
    }
    else
    {
        DT_DBG(("Total RedirectHost AVP in ans Msg ::%d", rhCount));

        /**
         * Get the Redirect-Host AVPs Value and find which
         * detination is available (transport up).
         */
        for (int i = 0; i < rhCount; i++)
        {
            destHost = bCmd->getRedirectHost(i)->fqdn.value().c_str();
            DT_DBG(("Find RedirectHost in PeerTable :: %s", destHost));

            if(PEER_TABLE->FindEntry(destHost, newPentry))
            {
                trInst = DIA_PE_INST(newPentry);
                tr = trTable[trInst];
                if( tr != NULL )
                {
                    foundDestUp = true;
                    break;
                }
            }
        }

        if (!foundDestUp)
        {
            DT_WRN(("Either destHost Not found in peer table or it is Not Up"));
            return !ITS_SUCCESS;
        }
        DT_DBG(("Redirect Host found :: %s", newPentry->hostIdentity));
    }
 
    /**
     * If Local Caching is Enable, then only get the redirect usage 
     * and max cache timer value.
     */
    if (itsDiaConfig.IsLocalCachingEnabled())
    {
        DT_DBG(("Local Caching is Enabled :: Find usage and timer value"));

        /**
         * Get the Redirect-Host-Usage AVP Value.
         */
        if ( bCmd->containsRedirectHostUsage() )
        {
            ITS_UINT rdUsage = bCmd->getRedirectHostUsage()->value();
            DT_DBG(("RedirectHostUsage : %d", rdUsage));

            switch( rdUsage )
            {
                case ALL_SESSION:
                {
                    if ( bCmd->getSessionId() )
                    {
                        cacheKey = bCmd->getSessionId()->value();
                    }
                    break;
                }
                case ALL_USER:
                {
                    if ( bCmd->getDestinationHost() !=NULL &&
                         bCmd->getDestinationRealm() != NULL)
                    {
                        cacheKey = bCmd->getDestinationHost()->value();
                        cacheKey.append( bCmd->getDestinationRealm()->value() );
                    }
                    break;
                }
                case REALM_AND_APPLICATION:
                {
                    if ( bCmd->getDestinationRealm() != NULL &&
                         bCmd->getApplicationId() != NULL )
                    {
                        cacheKey = bCmd->getDestinationRealm()->value();
                        ITS_UINT appId = bCmd->getApplicationId();
                        char buf[MAX_LEN_APPID];
                        //Correcting Calling rixky function
                        memset(buf, 0, MAX_LEN_APPID);
                        snprintf(buf, MAX_LEN_APPID-1, "%d", appId);
                        cacheKey.append( buf );
                    }
                    break;
                }
                case ALL_REALM:
                {
                    if ( bCmd->getDestinationRealm() != NULL )
                    {
                        cacheKey = bCmd->getDestinationRealm()->value();
                    }
                    break;
                }
                case ALL_APPLICATION:
                {
                    if ( bCmd->getApplicationId() != NULL )
                    {
                        ITS_UINT appId = bCmd->getApplicationId();
                        char buf[MAX_LEN_APPID];
                       //Correcting Calling risky function
                        memset(buf, 0, MAX_LEN_APPID);
                        snprintf(buf,MAX_LEN_APPID-1, "%d", appId);
                        cacheKey =  buf;
                    }
                    break;
                }
                case ALL_HOST:
                {
                    if ( bCmd->getDestinationHost() != NULL )
                    {
                        cacheKey = bCmd->getDestinationHost()->value();
                    }
                    break;
                }
                default:
                {
                    DT_DBG(("RedirectUsage : Value do not support Local Caching"));
                }
            }
            DT_DBG(("Key of this Entry : %s\n", cacheKey.c_str()));
        }

        /**
         * Get the Redirect-Host-Max-Cache-Time AVP Value.
         */
        if ( bCmd->containsRedirectMaxCacheTime() )
        {
            maxCacheTime = bCmd->getRedirectMaxCacheTime()->value();
            DT_DBG(("RedirectMaxCacheTime : %d",maxCacheTime));
        }

        /**
         * Before insert into table, Check cacheKey and timer value.
         */
        if (strlen(cacheKey.c_str()) && maxCacheTime )
        {
            cEntry = (CACHE_ENTRY *)malloc(sizeof(CACHE_ENTRY));
            if (cEntry == NULL)
            {
                DT_ERR(("Memory Allocation failure"));
                return !ITS_SUCCESS;
            }
            memset(cEntry, 0, sizeof(CACHE_ENTRY));

            DIA_CACHE_DEST_HOST(cEntry) = strdup(destHost);

            //Warning Fix - suggest parentheses around assignment used as truth value
            if ((ret = CACHE_TABLE->InsertEntry( cacheKey.c_str(),
                                                maxCacheTime,
                                                cEntry )) != ITS_SUCCESS )
            {
                DT_WRN(("Entry insertion Failed"));
            }
        }
        else
        {
            DT_WRN(("Cache Timer or Key value is NULL"));
        }
    }

    /**
     * Get the Request Msg saved in PendingQ.
     */
     if ( pEntry != NULL &&
          DIA_PE_PENDING_Q(pEntry) != NULL &&
          !DIA_PEER_CHK_IS_FAILOVER_ENABLED(pEntry) )
     {
         DT_DBG(("Get ReqMsg from PendingQ::%d", bCmd->getHeader().hh));
         reqMsg =  DIA_PE_PENDING_Q(pEntry)->GetEntry(bCmd->getHeader().hh);

         if(reqMsg == NULL)
         {
             DT_ERR(("ReqMsg Not found in PendingQ"));
             return !ITS_SUCCESS;
         }
     }
     else
     {
         DT_ERR(("ReqMsg Not found"));
         return !ITS_SUCCESS;
     }

    /**
     * Forward Request Msg to DestHost.
     */
    if ( tr != NULL)
    {
        DIA_HDR &reqHdr = (DIA_HDR&)reqMsg->getHeader();

        if( DiaMsgRouter::SendCmdToPeer(trInst, &reqHdr, reqMsg) ==ITS_SUCCESS )
        {
            DT_DBG(("Send Request to Redirected destHost :: SUCCESS"));
            ret = ITS_SUCCESS;
        }
        else
        {
            DT_ERR(("Send Request to Redirected destHost :: FAILED"));
            ret = !ITS_SUCCESS;
        }
    }
    //Fix for coverity CID11712,CID11711,CID11710.As reqMsg will be freed in DiaMsgFlow destructor.
    return ret;
}

/*.implementation:static
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
bool
DiaRedirectHandler::CheckInLocalCache( DIA_BASE_CMD *&bCmd,
                                       SESSION_ENTRY *&sessInfo,
                                       ITS_USHORT &peerInstance,
                                       REALM_ENTRY *rEntry )
{
    PEER_ENTRY *pEntry = NULL;
    CACHE_ENTRY* cEntry = NULL;
    ITS_UINT i = 0;
    std::string key;
    bool foundEnt = false;
 
    /**
     * Check Local Cache is enable.
     */
    if (!bCmd->isRequest() ||
        !itsDiaConfig.IsLocalCachingEnabled() ||
        CACHE_TABLE->GetTableSize() <= 0 )
    {
        DT_DBG(("Local Caching is Not enabled or No entry in CacheTable"));
        return false;
    }

    /**
     * Fix for Issue: 1481
     * (Relay agent failed to send RAR message to Client when
     * Redirect agent is configured with RD-Host-Usage AVP is 1)
     * Sol: check in local cache only if commandcode != to ASR & RAR
     */
    unsigned int cmdCode = bCmd->getCommandCode();
    if ( cmdCode == DIA_MSG_AS || cmdCode == DIA_MSG_RA )
    {
        DT_DBG(("ASR or RAR Message"));
        return false;
    }

    DT_DBG(("DiaRedirectHandler::CheckInLocalCache"));
 
    /**
     * Check Local Cache in Precedence Order.
     */
    DT_DBG(("Check in cache table in Precedence Order."));

    while (i++ < MAX_USG && foundEnt == false)
    {
        key.clear();
        switch(i)
        {
            case SESSION:
            {
                if ( bCmd->getSessionId() != NULL )
                {
                    key = bCmd->getSessionId()->value();
                    DT_DBG(("\nCheck by using Session-Id ::"));
                }
                break;
            }
            case USER:
            {
                if ( bCmd->getDestinationHost() !=NULL &&
                     bCmd->getDestinationRealm() != NULL)
                {
                    key = bCmd->getDestinationHost()->value();
                    key.append( bCmd->getDestinationRealm()->value() );
                    DT_DBG(("Check by using destHost and destRealm ::"));
                }
                break;
            }
            case REALM_AND_APP:
            {
                if ( bCmd->getDestinationRealm() != NULL &&
                     bCmd->getApplicationId() != NULL )
                {
                    key = bCmd->getDestinationRealm()->value();
                    ITS_UINT appId = bCmd->getApplicationId();
                    char buf[MAX_LEN_APPID];
                    //Correcting Calling rixky function
                    memset(buf, 0, MAX_LEN_APPID);
                    snprintf(buf, MAX_LEN_APPID-1, "%d", appId);
                    key.append( buf );
                    DT_DBG(("Check by using destRealm and appId ::"));
                }
                break;
            }
            case REALM:
            {
                if ( bCmd->getDestinationRealm() != NULL )
                {
                    key = bCmd->getDestinationRealm()->value();
                    DT_DBG(("Check by using destRealm ::"));
                }
                break;
            }
            case APPLICATION:
            {
                if ( bCmd->getApplicationId() != NULL )
                {
                    ITS_UINT appId = bCmd->getApplicationId();
                    char buf[MAX_LEN_APPID];
                    //Correcting function
                    memset(buf, 0, MAX_LEN_APPID);
                    snprintf(buf, MAX_LEN_APPID-1, "%d", appId);
                    key = buf;
                    DT_DBG(("Check by using appId ::"));
                }
                break;
            }
            case HOST:
            {
                if ( bCmd->getDestinationHost() != NULL )
                {
                    key = bCmd->getDestinationHost()->value();
                    DT_DBG(("Check by using destHost ::"));
                }
                break;
            }
        }

        if(key.length() > 0 && CACHE_TABLE->FindEntry( key.c_str(), &cEntry ))
        {
            foundEnt = true;
        }
    }

    if ( cEntry != NULL &&
         PEER_TABLE->FindEntry( cEntry->destHost, pEntry ) &&
         trTable[pEntry->trInst] != NULL)
    {
        DT_DBG(("Cache Entry found and destHost is UP.\n"));

        peerInstance = DIA_PE_INST( pEntry );
        DIA_HDR &hdr = bCmd->getHeader();
        hdr.hh = DiaUtils::GenerateHopByHopId();

        const char * reqHost = bCmd->getOriginHost()->value().c_str();
        DIA_CER *lcer = itsDiaConfig.GetLocalCER();
        const char *localHost = lcer->getOriginHost().value().c_str();

        if ( strcasecmp( localHost, reqHost ) == 0 )
        {
            /**
             * If action is Local then save End-to-End Id and Hop-by-Hop Id
             * in the Rx Id.
             */
            hdr.ee = DiaUtils::GenerateEndToEndId();
            DIA_SE_RX_EE(sessInfo) = hdr.ee;
            DIA_SE_RX_HH(sessInfo) = hdr.hh;
        }
        else
        {
            /**
             * Add the Route-Record AVP and save the Hop-by-Hop Id in the
             * LOCAL Id.
             */
            DiaUtils::AddRouteRecordAvp(bCmd, sessInfo);
            DIA_SE_LOCAL_HH(sessInfo) = hdr.hh;
        }
        return true;
    }
    else
    {
        DT_WRN(("Cache Entry Not found or destHost is not UP.\n"));
        return false;
    }
}

