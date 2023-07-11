/* ********************************-*-C-*-************************************
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


#include <CMgrDbInterface.h>
#include "ErrorResp.h"

using namespace std;
extern std::map<int,std::string> errorMap;


void CMgrDbInterface::mysql_set_error_for_Peer_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pPeerConfig->has_peerhostname())
        err->add_variables(pPeerConfig->peerhostname());

    if(pPeerConfig->has_realm())
        err->add_variables(pPeerConfig->realm());

    if(pPeerConfig->has_altpeername())
        err->add_variables(pPeerConfig->altpeername());

    if(pPeerConfig->has_serveripaddr())
        err->add_variables(pPeerConfig->serveripaddr().c_str());

    if(pPeerConfig->has_port() && 
       (iReturn!= SET_PEER_ERR_IP_AND_SECUREPORT_ALREADY_PRESENT))
    {
        char sPort[20];
        snprintf(sPort,20,"%d",pPeerConfig->port());
        err->add_variables(sPort);
    }
    if(pPeerConfig->has_secureport())
    {
        char sPort[20];
        snprintf(sPort,20,"%d",pPeerConfig->secureport());
        err->add_variables(sPort);
    }
    if(iReturn == DEL_PEER_ERR_USED_AS_ALTERNATE_PEER)
    {
	    char sStatement[MAX_STATEMENT_SIZE];
	    sql::ResultSet *pRes = NULL;

	    PeerConfig localPeerConfigObj;
	    localPeerConfigObj.set_altpeername(pPeerConfig -> peerhostname());

	    sql_Peer_Create_Select_Query(&localPeerConfigObj,sStatement);
	    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	    {
		    if(pRes != NULL)        
		    {
			    delete pRes;
		    }

		    DLOG_ERROR("Query Execution Failed: %s",sStatement);

		    if(iReturn == DRE_DB_FAIL)
			    iReturn = DEL_PEER_ERR_DB_ERROR;

		    DLOG_NONE(" < %s ",__FUNCTION__);
		    return;
	    }

	    memset(sStatement,0,MAX_STATEMENT_SIZE);

    	    DLOG_DEBUG("pRes->rowsCount() = %d", pRes->rowsCount());
	    if(pRes->rowsCount() > 0)
	    {
		    while(pRes -> next())
		    {
			    if(!pRes->isNull("PeerHostIdentity"))
			    {
				    snprintf(sStatement+strlen(sStatement),MAX_STATEMENT_SIZE,"%s,",pRes->getString("PeerHostIdentity").c_str());
			    }
		    }
		    sStatement[strlen(sStatement)-1] = ' ';		
		    err->add_variables(sStatement);
	    }
	    delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_PeerSecondaryIp_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    string sSecondaryIp;
    char sStr[10];

    if(iIndex != -1)
        sSecondaryIp = pPeerConfig->secondaryipaddr(iIndex);
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    if(pPeerConfig->has_peerhostname())
        err->add_variables(pPeerConfig->peerhostname());

    if(pPeerConfig->has_realm())
        err->add_variables(pPeerConfig->realm());

    if(iIndex != -1)
    {
        DLOG_DEBUG("Setting SecondaryIp %s",sSecondaryIp.c_str());
        err->add_variables(sSecondaryIp);
    }
    if(iReturn == ADD_SECONDARY_ERR_IP_MAX_COUNT_REACHED)
    {
        snprintf(sStr,10,"%d",MAX_SECONDARY_IP_SUPPORTED);
        err->add_variables(sStr);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);

}
void CMgrDbInterface::mysql_set_error_for_PeerDictionaryMap_Config_Reqs(PeerConfig *pPeerConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    string sDictionaryName;
    char sStr[10];

    if(iIndex != -1)
        sDictionaryName = pPeerConfig->dictionaryname(iIndex);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pPeerConfig->has_peerhostname())
        err->add_variables(pPeerConfig->peerhostname());

    if(pPeerConfig->has_realm())
        err->add_variables(pPeerConfig->realm());

    if(iIndex != -1)
    {
        DLOG_DEBUG("Setting Dictionary %s",sDictionaryName.c_str());
        err->add_variables(sDictionaryName);
    }

    if(iReturn == ADD_DICTID_ERR_DICTNAME_MAX_COUNT_REACHED)
    {
        snprintf(sStr,10,"%d",MAX_DICT_SUPPORTED);
        err->add_variables(sStr);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrDbInterface::mysql_PeerOfRealm_Get_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pPeersConfig->peers_size();

    DLOG_NONE(" > %s ",__FUNCTION__);

    DLOG_DEBUG(" %s: PeerConfig Req Size = %d ",__FUNCTION__,iCount); 
    for(int i=0; i<iCount; i++)
    {
        pRes = NULL;
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerAndTimer_Create_Select_Query(localPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_REALMOFPEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_peer_resultset_to_realm_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        delete pRes;
    }

    if(iCount == 0)
    {

        ::PeerConfig localPeerConfig;

        sql_PeerAndTimer_Create_Select_Query(&localPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_REALMOFPEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(&localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_peer_resultset_to_realm_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Peer_Config_Reqs(&localPeerConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;


    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_peer_resultset_to_realm_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());   
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_REALMOFPEER_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            mysql_check_and_Add_Peer_resultset(pRes,resp);
        }       
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_add_peer_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::RealmConfig* localRealmObj = localRealmsObj->add_realms();

    localRealmObj->set_realmname(pRes->getString("RealmName"));
    mysql_add_peer_resultset_to_DestinationProtoBuff(pRes,localRealmObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_add_peer_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = localRealmObj->destinfo_size();

    DLOG_DEBUG(" %s: Destinfo Req Size = %d ",__FUNCTION__,iCount); 

    for(int i=0;i<iCount;i++)
    {
        ::Destination* localDestionationObj = localRealmObj->mutable_destinfo(i);       

        if(localDestionationObj->peername() == pRes->getString("PeerHostIdentity"))
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_SUCCESS;
        }
    }

    ::Destination* localDestionationObj = localRealmObj->add_destinfo();

    localDestionationObj->set_peername(pRes->getString("PeerHostIdentity"));
    localDestionationObj->set_peerid(pRes->getInt64("PeerID"));


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}



void CMgrDbInterface::mysql_check_and_Add_Peer_resultset(sql::ResultSet *pRes,DRECfgResp *resp)
{
    ::RealmsConfig* localRealmsObj;

    DLOG_NONE(" > %s ",__FUNCTION__);

    localRealmsObj = resp->mutable_realms();

    int iRealmCount = localRealmsObj->realms_size();

    DLOG_DEBUG(" %s: Realms Req Size = %d ",__FUNCTION__,iRealmCount); 
    for(int j=0; j<iRealmCount; j++)
    {
        ::RealmConfig* localRealmObj = localRealmsObj->mutable_realms(j);

        // Assuming that all this variable will be there

        if(localRealmObj->realmname() == pRes->getString("RealmName"))
        {

            mysql_add_peer_resultset_to_DestinationProtoBuff(pRes,localRealmObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return; 
        }
    }

    mysql_add_peer_resultset_to_RealmProtoBuff(pRes,localRealmsObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Peer_Get_Config_Reqs_for_peerstat(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pPeersConfig->peers_size();

    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_DEBUG(" %s: Peers Req Size = %d ",__FUNCTION__,iCount); 

    for(int i=0; i<iCount; i++)
    {
        pRes = NULL;
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerAndTimer_Create_Select_Query(localPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_peer_and_peerTimer_withstat_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            if(iReturn == GET_PEER_ERR_NO_DATA_PRESENT)
                iReturn = GET_PEER_ERR_NO_PEER_PRESENT;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iCount == 0)
    {

        ::PeerConfig localPeerConfig;

        sql_PeerAndTimer_Create_Select_Query(&localPeerConfig,sStatement);

        if ((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(&localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_peer_and_peerTimer_withstat_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Peer_Config_Reqs(&localPeerConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;


    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Peer_Get_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pPeersConfig->peers_size();

    DLOG_NONE(" > %s ",__FUNCTION__);
    DLOG_DEBUG(" %s: Peers Req Size = %d ",__FUNCTION__,iCount); 

    for(int i=0; i<iCount; i++)
    {
        pRes = NULL;
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerAndTimer_Create_Select_Query(localPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
        if((iReturn = mysql_peer_and_peerTimer_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iCount == 0)
    {

        ::PeerConfig localPeerConfig;

        sql_PeerAndTimer_Create_Select_Query(&localPeerConfig,sStatement);

        if ((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(&localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_peer_and_peerTimer_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_Peer_Config_Reqs(&localPeerConfig,resp,iReturn);
            delete pRes;
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;


    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_peer_and_peerTimer_withstat_resultset_to_protoBuff(sql::ResultSet *pResPeerAndTimerT,DRECfgResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pResPeerAndTimerT->rowsCount());      
        if(pResPeerAndTimerT->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PEER_ERR_NO_DATA_PRESENT;
        }

        while(pResPeerAndTimerT->next())
        {
            mysql_check_and_add_peer_peerTimer_stat_resultset_to_protoBuff(pResPeerAndTimerT,resp);
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_peer_and_peerTimer_resultset_to_protoBuff(sql::ResultSet *pResPeerAndTimerT,DRECfgResp *resp)
{

    DLOG_NONE(" > %s ",__FUNCTION__);
    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pResPeerAndTimerT->rowsCount());      
        if(pResPeerAndTimerT->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PEER_ERR_NO_DATA_PRESENT;
        }

        while(pResPeerAndTimerT->next())
        {
            mysql_check_and_add_peer_peerTimer_dictionary_resultset_to_protoBuff(pResPeerAndTimerT,resp);
        }
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


void CMgrDbInterface::mysql_check_and_add_peer_peerTimer_stat_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::PeersConfig* localPeersObj = resp->mutable_peers();


    int iPeerConfigCount =  localPeersObj->peers_size();
    DLOG_DEBUG(" %s: Peers Req Size = %d ",__FUNCTION__,iPeerConfigCount); 

    for(int j=0;j<iPeerConfigCount;j++)
    {
        ::PeerConfig* localPeerObj = localPeersObj->mutable_peers(j);

        if(localPeerObj->peerhostname() == pRes->getString("PeerHostIdentity") &&
                localPeerObj->realm() == pRes->getString("RealmName"))
        {
            if(!localPeerObj->has_peerid())
                mysql_add_stat_resultset_to_protoBuff(pRes,localPeerObj);
            mysql_add_dictionary_resultset_to_protoBuff(pRes,localPeerObj);
            mysql_add_SecondaryIp_resultset_to_protoBuff(pRes,localPeerObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }

    mysql_add_peer_peerTimer_resultset_to_protoBuff(pRes,localPeersObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}
/*
void CMgrDbInterface::mysql_check_and_add_peer_peerTimer_SecondaryIp_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::PeersConfig* localPeersObj = resp->mutable_peers();
    int iPeerConfigCount =  localPeersObj->peers_size();
    DLOG_DEBUG(" %s: Peers Req Size = %d ",__FUNCTION__,iPeerConfigCount);
    for(int j=0;j<iPeerConfigCount;j++)
    {
        ::PeerConfig* localPeerObj = localPeersObj->mutable_peers(j);
        if(localPeerObj->peerhostname() == pRes->getString("PeerHostIdentity") &&
                localPeerObj->realm() == pRes->getString("RealmName"))
        {
            mysql_add_SecondaryIp_resultset_to_protoBuff(pRes,localPeerObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }    

    mysql_add_peer_peerTimer_resultset_to_protoBuff(pRes,localPeersObj);

    DLOG_NONE(" < %s ",__FUNCTION__);

}
*/

void CMgrDbInterface::mysql_check_and_add_peer_peerTimer_dictionary_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::PeersConfig* localPeersObj = resp->mutable_peers();


    int iPeerConfigCount =  localPeersObj->peers_size();
    DLOG_DEBUG(" %s: Peers Req Size = %d ",__FUNCTION__,iPeerConfigCount); 

    for(int j=0;j<iPeerConfigCount;j++)
    {
        ::PeerConfig* localPeerObj = localPeersObj->mutable_peers(j);

        if(localPeerObj->peerhostname() == pRes->getString("PeerHostIdentity") &&
                localPeerObj->realm() == pRes->getString("RealmName"))
        {

            mysql_add_dictionary_resultset_to_protoBuff(pRes,localPeerObj);
            mysql_add_SecondaryIp_resultset_to_protoBuff(pRes,localPeerObj);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }

    mysql_add_peer_peerTimer_resultset_to_protoBuff(pRes,localPeersObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void CMgrDbInterface::mysql_add_stat_resultset_to_protoBuff(sql::ResultSet *pRes,::PeerConfig* pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    if(!pRes->isNull("PeerID"))     
        pPeerConfig->set_peerid(pRes->getInt("PeerID"));
    if(!pRes->isNull("TLSEnabled")) 
        pPeerConfig->set_tlsenabled(pRes->getInt("TLSEnabled"));
    //localPeerObj->set_transporttype(); //it is defined as integer in table and string in Class
    if(!pRes->isNull("TransportType"))      
    {
        if(pRes->getInt("TransportType") == 1)
            pPeerConfig->set_transporttype("TCP");
        else if(pRes->getInt("TransportType") == 2)
            pPeerConfig->set_transporttype("SCTP");
        else pPeerConfig->set_transporttype("Not Specified");
    }

    if(!pRes->isNull("PeerIP"))     
        pPeerConfig->set_serveripaddr(pRes->getString("PeerIP"));
    if(!pRes->isNull("PeerPort"))   
        pPeerConfig->set_port(pRes->getInt("PeerPort"));
    if(!pRes->isNull("FailOverEnable"))     
        pPeerConfig->set_failoverenable(pRes->getInt("FailOverEnable"));
    if(!pRes->isNull("FailBackEnable"))     
        pPeerConfig->set_failebackenable(pRes->getInt("FailBackEnable"));
    if(!pRes->isNull("AltPeerID"))  
        pPeerConfig->set_altpeername(pRes->getString("AltPeerID"));
    if(!pRes->isNull("isMate"))     
        pPeerConfig->set_ismate(pRes->getInt("isMate"));
    if(!pRes->isNull("TcVal"))      
        pPeerConfig->set_tctimerval(pRes->getInt("TcVal"));
    if(!pRes->isNull("WdVal"))      
        pPeerConfig->set_watchdogtimer(pRes->getInt("WdVal"));
    if(!pRes->isNull("Eval"))       
        pPeerConfig->set_expirytimer(pRes->getInt("Eval"));
    if(!pRes->isNull("Enable"))     
        pPeerConfig->set_peerstatus(pRes->getInt("Enable"));
    if(!pRes->isNull("BusyReconnectTimer"))       
        pPeerConfig->set_busyreconnecttimerval(pRes->getInt("BusyReconnectTimer"));
    if(!pRes->isNull("DoNotwantToTalkToYouTimer"))       
        pPeerConfig->set_donotwanttotalktoyoutimerval(pRes->getInt("DoNotwantToTalkToYouTimer"));
    if(!pRes->isNull("IsSupportDisconnectCause"))       
        pPeerConfig->set_issupportdisconnectcause(pRes->getInt("IsSupportDisconnectCause"));
    if(!pRes->isNull("SecurePort"))       
        pPeerConfig->set_secureport(pRes->getInt("SecurePort"));

    DLOG_NONE(" %s state %d ",__FUNCTION__,pPeerConfig->peerstate());
    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_add_SecondaryIp_resultset_to_protoBuff(sql::ResultSet *pRes,::PeerConfig* pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(pRes->isNull("OTHERHOME_IPADDR"))
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;   
    }

    int Ipcount = pPeerConfig->secondaryipaddr_size();
    for(int j=0; j<Ipcount;j++)
    {
        string IpAddr = pPeerConfig->secondaryipaddr(j);
        if(IpAddr.compare(pRes->getString("OTHERHOME_IPADDR")) == 0)
        {
            return;
        }             
    }
    pPeerConfig->add_secondaryipaddr(pRes->getString("OTHERHOME_IPADDR"));
    DLOG_NONE(" < %s ",__FUNCTION__);
}
void CMgrDbInterface::mysql_add_dictionary_resultset_to_protoBuff(sql::ResultSet *pRes,::PeerConfig* pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    if(pRes->isNull("DICTIONARY_ID"))       
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }
    int DictCount = pPeerConfig->dictionaryname_size();
    for(int j=0; j<DictCount;j++)
    {
        string dictionary = pPeerConfig->dictionaryname(j).c_str();
        if(dictionary.compare(pRes->getString("DICTIONARY_NAME")) == 0)
        {
            return;
        }
    } 
    pPeerConfig->add_dictionaryid(pRes->getInt("DICTIONARY_ID"));
    pPeerConfig->add_dictionaryname(pRes->getString("DICTIONARY_NAME"));
    pPeerConfig->add_typeofapp(pRes->getInt("APP_TYPE"));
    DLOG_NONE(" < %s ",__FUNCTION__);
}



void CMgrDbInterface::mysql_add_peer_peerTimer_resultset_to_protoBuff(sql::ResultSet *pRes,PeersConfig  *pPeersConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::PeerConfig* localPeerObj = pPeersConfig->add_peers(); 


    if(!pRes->isNull("RealmName"))  
        localPeerObj->set_realm(pRes->getString("RealmName"));
    if(!pRes->isNull("PeerHostIdentity"))   
        localPeerObj->set_peerhostname(pRes->getString("PeerHostIdentity"));
    if(!pRes->isNull("PeerID"))     
        localPeerObj->set_peerid(pRes->getInt("PeerID"));
    if(!pRes->isNull("TLSEnabled")) 
        localPeerObj->set_tlsenabled(pRes->getInt("TLSEnabled"));
    //localPeerObj->set_transporttype(); //it is defined as integer in table and string in Class
    if(!pRes->isNull("TransportType"))      
    {
        if(pRes->getInt("TransportType") == 1)
            localPeerObj->set_transporttype("TCP");
        else if(pRes->getInt("TransportType") == 2)
            localPeerObj->set_transporttype("SCTP");
    }

    if(!pRes->isNull("PeerIP"))     
        localPeerObj->set_serveripaddr(pRes->getString("PeerIP"));
    if(!pRes->isNull("PeerPort"))   
        localPeerObj->set_port(pRes->getInt("PeerPort"));
    if(!pRes->isNull("FailOverEnable"))     
        localPeerObj->set_failoverenable(pRes->getInt("FailOverEnable"));
    if(!pRes->isNull("FailBackEnable"))     
        localPeerObj->set_failebackenable(pRes->getInt("FailBackEnable"));
    if(!pRes->isNull("AltPeerID"))  
        localPeerObj->set_altpeername(pRes->getString("AltPeerID"));
    if(!pRes->isNull("isMate"))     
        localPeerObj->set_ismate(pRes->getInt("isMate"));
    if(!pRes->isNull("TcVal"))      
        localPeerObj->set_tctimerval(pRes->getInt("TcVal"));
    if(!pRes->isNull("WdVal"))      
        localPeerObj->set_watchdogtimer(pRes->getInt("WdVal"));
    if(!pRes->isNull("Eval"))       
        localPeerObj->set_expirytimer(pRes->getInt("Eval"));
    if(!pRes->isNull("Enable"))     
        localPeerObj->set_peerstatus(pRes->getInt("Enable"));
    if(!pRes->isNull("BusyReconnectTimer"))       
        localPeerObj->set_busyreconnecttimerval(pRes->getInt("BusyReconnectTimer"));
    if(!pRes->isNull("DoNotwantToTalkToYouTimer"))       
        localPeerObj->set_donotwanttotalktoyoutimerval(pRes->getInt("DoNotwantToTalkToYouTimer"));
    if(!pRes->isNull("IsSupportDisconnectCause"))       
        localPeerObj->set_issupportdisconnectcause(pRes->getInt("IsSupportDisconnectCause"));
    if(!pRes->isNull("SecurePort"))       
        localPeerObj->set_secureport(pRes->getInt("SecurePort"));


    mysql_add_dictionary_resultset_to_protoBuff(pRes,localPeerObj);
    mysql_add_SecondaryIp_resultset_to_protoBuff(pRes,localPeerObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

#if 0
DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Get_Config_Reqs_Through_Peer(PeersConfig *pPeersConfig,DRECfgResp *resp)
{

    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    int iCount = pPeersConfig->peers_size();
    DLOG_DEBUG(" %s: Peers Req Size = %d ",__FUNCTION__,iCount); 

    DLOG_NONE(" > %s ",__FUNCTION__);
    for(int i=0; i<iCount; i++)
    {
        pRes = NULL;
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_DefaultRoute_Create_Select_Query(localPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);
            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEFROUTE_ERR_DB_ERROR;

            return iReturn;
        }
        if((iReturn = mysql_DefaultRoute_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iCount == 0)
    {

        ::PeerConfig localPeerConfig;

        sql_DefaultRoute_Create_Select_Query(&localPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_DEFROUTE_ERR_DB_ERROR;

            return iReturn;
        }

        if((iReturn = mysql_DefaultRoute_resultset_to_protoBuff(pRes,resp)) != DRE_DB_SUCCESS)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;


    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}
#endif

DbStatus_e CMgrDbInterface::mysql_PeerAndTimer_Add_validation(PeerConfig *pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    sql_Peer_Create_Check_Unique_Constrain(pPeerConfig,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) == DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_SUCCESS)
            iReturn = SET_PEER_ERR_IP_AND_PORT_ALREADY_PRESENT;

    }
    if(iReturn != SET_PEER_ERR_IP_AND_PORT_ALREADY_PRESENT)
    {
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_Peer_Create_Check_Unique_Constrain_For_SecurePort(pPeerConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) == DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_SUCCESS)
                iReturn = SET_PEER_ERR_IP_AND_SECUREPORT_ALREADY_PRESENT;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_PeerAndTimer_Add_Config_Reqs(PeerConfig *pPeerConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_Peer_Payload_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload validation Failed \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = sql_PeerTimers_Payload_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload validation Failed \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }


    if((iReturn = mysql_AlternatePeer_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Alternate Peer Validation Failed \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_PeerAndTimer_Add_validation(pPeerConfig)) != DRE_DB_FAIL)
    {
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }

    sql_Peer_Create_Check_Modifcation_Query(pPeerConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_PEER_ERR_DB_ERROR;

        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_Peer_Create_Add_Query(pPeerConfig,sStatement);      
    }
    else // MOD
    {
        delete pRes;
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,SET_PEER_ERR_PEER_REALM_ALREADY_EXISTS);
        DLOG_ERROR("Record Already Present");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_PEER_ERR_PEER_REALM_ALREADY_EXISTS;
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);       

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_PEER_ERR_DB_ERROR;

        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        return iReturn;
    }


    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_PeerTimers_Create_Check_Modifcation_Query(pPeerConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_PEER_ERR_TIMERS_FAILED_DB_ERROR;

        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        return iReturn;
    }


    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_PeerTimers_Create_Add_Query(pPeerConfig,sStatement);        
    }
    else // MOD
    {

        delete pRes;
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,SET_PEER_ERR_PEER_REALM_ALREADY_EXISTS);
        DLOG_ERROR("Record Already Present");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_PEER_ERR_PEER_REALM_ALREADY_EXISTS;
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);       

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_PEER_ERR_TIMERS_FAILED_DB_ERROR;

        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        return iReturn;
    }

    iReturn = mysql_PeerDictionaryMap_Add_Config_Reqs_Through_Peer(pPeerConfig,resp);
    if(iReturn == DRE_DB_SUCCESS)
    {
        iReturn = mysql_PeerSecondaryIp_Add_Config_Reqs_Through_Peer(pPeerConfig,resp);   
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

void CMgrDbInterface::copy_PeerConfig(LBPeerGroupResp *resp,LBPeerGroup *pLBPeerGroup,int iIndexPeer)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    ::LBPeerGroup* plocalPeerGroupResp;

    plocalPeerGroupResp = copy_checkPeerGroupAlreadyPresent(resp,pLBPeerGroup);
    if(!plocalPeerGroupResp)
    {
        plocalPeerGroupResp = resp->add_peergroups();
        if(pLBPeerGroup->has_lbpeergroupname())
            plocalPeerGroupResp->set_lbpeergroupname(pLBPeerGroup->lbpeergroupname());
        if(pLBPeerGroup->has_lbpeergroupid())
            plocalPeerGroupResp->set_lbpeergroupid(pLBPeerGroup->lbpeergroupid());
        if(pLBPeerGroup->has_enablepcrfbinding())
            plocalPeerGroupResp->set_enablepcrfbinding(pLBPeerGroup->enablepcrfbinding());

    }
    ::LBPeer* pLBPeerResp = plocalPeerGroupResp->add_lbpeers();

    ::LBPeer* plocalLBPeer = pLBPeerGroup->mutable_lbpeers(iIndexPeer);
    pLBPeerResp->CopyFrom(*plocalLBPeer);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return ;
}

void CMgrDbInterface::copy_PeerConfig(DRECfgResp *resp,PeerConfig *pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::PeersConfig* plocalPeersConfig = resp->mutable_peers();
    ::PeerConfig* plocalPeerConfig = plocalPeersConfig->add_peers();

    plocalPeerConfig->CopyFrom(*pPeerConfig);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return;
}

DbStatus_e CMgrDbInterface::mysql_PeerAndTimer_Mod_Config_Reqs(PeerConfig *pPeerConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_Peer_Payload_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload validation Failed (Primary key are not set) \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = sql_PeerTimers_Payload_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload validation Failed (Primary Key are not set) \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_AlternatePeer_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Alternate Peer Validation Failed \n",__FUNCTION__,__LINE__);
        mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

#if 0
    if(sql_Peer_Check_All_Invalid(pPeerConfig) == DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload no fields are set for validation (Only Primary Key is set) \n",__FUNCTION__,__LINE__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    if(sql_PeerTimers_Check_All_Invalid(pPeerConfig) == DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload no fields are set for validation (Only Primary Key is set) \n",__FUNCTION__,__LINE__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

#endif

    if(sql_Peer_Check_All_Invalid(pPeerConfig) == DRE_DB_FAIL)
    {

        sql_Peer_Create_Check_Modifcation_Query(pPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);

            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,MOD_PEER_ERR_PEER_NOT_PRESENT);
            DLOG_ERROR("Record is not present ");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_PEER_ERR_PEER_NOT_PRESENT;
        }
        else // MOD
        {
            sql_Peer_Create_Mod_Query(pPeerConfig,sStatement);
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);       

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
            return iReturn;
        }
    }

    if(sql_PeerTimers_Check_All_Invalid(pPeerConfig) == DRE_DB_FAIL)
    {
        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);

        sql_PeerTimers_Create_Check_Modifcation_Query(pPeerConfig,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEER_ERR_TIMERS_FAILED_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,MOD_PEER_ERR_TIMERS_NOT_PRESENT);
            DLOG_ERROR("Record is not present ");
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_PEER_ERR_TIMERS_NOT_PRESENT;
        }
        else // MOD
        {
            sql_PeerTimers_Create_Mod_Query(pPeerConfig,sStatement);
        }

        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);       

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEER_ERR_TIMERS_FAILED_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(pPeerConfig,resp,iReturn);
            return iReturn;
        }
    }

    iReturn = mysql_PeerDictionaryMap_Add_Config_Reqs_Through_Peer(pPeerConfig,resp);
    if(iReturn == DRE_DB_SUCCESS)
    {
        iReturn = mysql_PeerSecondaryIp_Add_Config_Reqs_Through_Peer(pPeerConfig,resp);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerSecondaryIp_Add_validation(PeerConfig *pPeerConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerConfig->has_peerhostname() && pPeerConfig->has_realm())
    {
        sql_PeerMutiHoming_Create_Validation_Query_for_Peer(pPeerConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_SECONDARYIP_ERR_PEER_NOT_PRESENT;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_PeerSecondaryIp_Add_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0}; 
    sql::ResultSet *pRes = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn = DRE_DB_SUCCESS;
    int iSecondaryIpCount = pPeerConfig->secondaryipaddr_size();
    DLOG_DEBUG(" %s: SecondaryIp Req Size = %d ",__FUNCTION__,iSecondaryIpCount);

    for(int i=0;i<iSecondaryIpCount;i++)
    {

        if((iReturn = mysql_PeerSecondaryIp_Add_validation(pPeerConfig,i)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_PeerSecondaryIp_Config_Reqs(pPeerConfig,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerMultiHoming_Create_Check_Modifcation_Query(pPeerConfig,sStatement,i);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_SECONDARYIP_ERR_DB_ERROR;
            mysql_set_error_for_PeerSecondaryIp_Config_Reqs(pPeerConfig,resp,iReturn,i);
            return iReturn;
        }
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        if(pRes->rowsCount() == 0) // ADD
        {
            sql_PeerMultiHoming_Create_Add_Query(pPeerConfig,sStatement,i);       
        }
        else // MOD
        {

            delete pRes;
            mysql_set_error_for_PeerSecondaryIp_Config_Reqs(pPeerConfig,resp,ADD_SECONDARY_ERR_IP_ALREADY_ASSOCIATED,i);
            DLOG_ERROR("Record Already Present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SECONDARY_ERR_IP_ALREADY_ASSOCIATED;
        }
        delete pRes;

        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_SECONDARYIP_ERR_DB_ERROR;

            mysql_set_error_for_PeerSecondaryIp_Config_Reqs(pPeerConfig,resp,iReturn,i);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerMultiHoming_Create_Select_Query(pPeerConfig,sStatement,i);
        pRes = NULL;

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_SECONDARYIP_ERR_DB_ERROR;

            mysql_set_error_for_PeerSecondaryIp_Config_Reqs(pPeerConfig,resp,iReturn,i);
            return iReturn;
        }
        if(pRes->rowsCount() > MAX_SECONDARY_IP_SUPPORTED) // ADD
        {    
            delete pRes;
            DLOG_ERROR("Number of Secondary IP is already reached 4");  
            mysql_set_error_for_PeerSecondaryIp_Config_Reqs(pPeerConfig,resp,ADD_SECONDARY_ERR_IP_MAX_COUNT_REACHED,-1);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_SECONDARY_ERR_IP_MAX_COUNT_REACHED;

        }    

        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_PeerDictionaryMap_Add_validation(PeerConfig *pPeerConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerConfig->dictionaryname_size() > iIndex && iIndex > -1) 
    {   
        sql_PeerDictionaryMap_Create_Validation_Query_for_Dictionary(pPeerConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_DICTID_ERR_INVALID_DICTNAME;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }   

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pPeerConfig->has_peerhostname() && pPeerConfig->has_realm())
    {
        sql_PeerDictionaryMap_Create_Validation_Query_for_Peer(pPeerConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_DICTID_ERR_PEER_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerDictionaryMap_Add_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DLOG_NONE(" > %s ",__FUNCTION__);

    DbStatus_e iReturn = DRE_DB_SUCCESS;
    int iDictionaryCount = pPeerConfig->dictionaryname_size();
    DLOG_DEBUG(" %s: Dictionaryname Req Size = %d ",__FUNCTION__,iDictionaryCount); 

    for(int i=0;i<iDictionaryCount;i++)
    {

        if((iReturn = mysql_PeerDictionaryMap_Add_validation(pPeerConfig,i)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,iReturn,i);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerDictionaryMap_Create_Check_Modifcation_Query(pPeerConfig,sStatement,i);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,iReturn,i);
            return iReturn;
        }


        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_PeerDictionaryMap_Create_Add_Query(pPeerConfig,sStatement,i);       
        }
        else // MOD
        {
            string sDictionary;
            sDictionary = pPeerConfig->dictionaryname(i);
            DLOG_WARNING(" Already Peer with hostname %s and RealmName %s is associated to dictionary %s",pPeerConfig->peerhostname().c_str(),pPeerConfig->realm().c_str(),sDictionary.c_str());

            delete pRes;
            return iReturn;
#if 0
            delete pRes;
            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,ADD_DICTID_ERR_DICTNAME_ALREADY_ASSOCIATED,i);
            DLOG_ERROR("Record Already Present");   
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_DICTID_ERR_DICTNAME_ALREADY_ASSOCIATED;
#endif
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);       

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,iReturn,i);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerDictionaryMap_Create_Select_Query(pPeerConfig,sStatement,0);	

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)	

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,iReturn,-1);
            return iReturn;
        }


        if(pRes->rowsCount() > MAX_DICT_SUPPORTED) // checking the maximum number of Dictionary Supported 
        {

            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,ADD_DICTID_ERR_DICTNAME_MAX_COUNT_REACHED,-1);

            return ADD_DICTID_ERR_DICTNAME_MAX_COUNT_REACHED;
        }

        delete pRes;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_DictionaryPeerConfig_Create_Select_Query(pPeerConfig,sStatement,i);
        pRes = NULL;

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);
            DLOG_NONE(" < %s ",__FUNCTION__);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_DICTID_ERR_DB_ERROR;

            mysql_set_error_for_PeerDictionaryMap_Config_Reqs(pPeerConfig,resp,iReturn,i);
            return iReturn;
        }

        mysql_DictionaryName_resultset_to_peer_protoBuff(pRes,pPeerConfig,i);
        delete pRes;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);       
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_DictionaryName_resultset_to_peer_protoBuff(sql::ResultSet *pRes,PeerConfig *pPeerConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {
        DLOG_DEBUG(" %s: Result Set Row Count = %d ",__FUNCTION__,pRes->rowsCount());   
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_SUCCESS;
        }


        while(pRes->next())
        {
            if(!pRes->isNull("DICTIONARY_ID"))
                pPeerConfig->add_dictionaryid(pRes->getInt("DICTIONARY_ID"));
            if(!pRes->isNull("APP_TYPE"))
                pPeerConfig->add_typeofapp(pRes->getInt("APP_TYPE"));
        }       
    }
    catch (sql::SQLException &e)
    {
        DLOG_CRITICAL("#\t\t unix://path_to_mysql_socket.sock caused expected exception");
        DLOG_CRITICAL("#\t\t %s MySQL error code: %d",e.what(),e.getErrorCode());
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


#if 0
DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Add_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_DefaultRoute_Payload_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload validation Failed \n",__FUNCTION__,__LINE__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    sql_DefaultRoute_Create_Check_Modifcation_Query(pPeerConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DRE_DB_FAIL;

        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        sql_DefaultRoute_Create_Add_Query(pPeerConfig,sStatement);      
    }
    else // MOD
    {
        delete pRes;
        DLOG_ERROR("Record Already Present");   
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);       

        if(iReturn == DRE_DB_FAIL)
            iReturn = DRE_DB_FAIL;

        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

#endif

#if 0

DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Mod_Config_Reqs_Through_Peer(PeerConfig *pPeerConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if((iReturn = sql_DefaultRoute_Payload_Validation(pPeerConfig)) != DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload validation Failed (Primary key are not set) \n",__FUNCTION__,__LINE__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(sql_DefaultRoute_Check_All_Invalid(pPeerConfig) == DRE_DB_SUCCESS)
    {
        DLOG_DEBUG("%s:%d Peer Payload no fields are set for validation (Only Primary Key is set) \n",__FUNCTION__,__LINE__);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    sql_DefaultRoute_Create_Check_Modifcation_Query(pPeerConfig,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DRE_DB_FAIL;

        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record is not present ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }
    else // MOD
    {
        sql_DefaultRoute_Create_Mod_Query(pPeerConfig,sStatement);
    }

    delete pRes;

    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);       

        if(iReturn == DRE_DB_FAIL)
            iReturn = DRE_DB_FAIL;

        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

#endif

DbStatus_e CMgrDbInterface::mysql_AltPeer_Delete_validation(PeerConfig *pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerConfig->has_peerhostname() && pPeerConfig->has_realm())
    {
        sql_Peer_Create_Validation_Query_for_alternate_peer(pPeerConfig,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_FAIL)
        {
            if(iReturn == DRE_DB_SUCCESS)
                iReturn = DEL_ALTPEER_ERR_ALTPEER_NOT_CONFIGURED;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_AltPeer_Delete_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = pPeersConfig->peers_size();
    DLOG_DEBUG(" %s: PeersConfig Req Size = %d ",__FUNCTION__,iCount); 

    for(int i=0; i<iCount; i++)
    {
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        if((iReturn = mysql_AltPeer_Delete_validation(localPeerConfig)) != DRE_DB_FAIL)
        {
            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pRes = NULL;
        sql_Peer_Create_Check_Modifcation_Query(localPeerConfig,sStatement);    
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_ALTPEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record is not present ");
            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,DEL_ALTPEER_ERR_PEER_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_ALTPEER_ERR_PEER_NOT_PRESENT;
        }
        else
        {

            delete pRes;
            PeerConfig lPeerConfig;
            lPeerConfig.set_altpeername("");
            lPeerConfig.set_realm(localPeerConfig->realm());
            lPeerConfig.set_peerhostname(localPeerConfig->peerhostname());
            lPeerConfig.set_ismate(false);
            lPeerConfig.set_failoverenable(false);
            lPeerConfig.set_failebackenable(false);

            sql_Peer_Create_Mod_Query(&lPeerConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);
                DLOG_NONE(" < %s ",__FUNCTION__);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_ALTPEER_ERR_DB_ERROR;

                mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
                return iReturn;
            }
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_Peer_Delete_Config_Reqs(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = pPeersConfig->peers_size();
    DLOG_DEBUG(" %s: PeersConfig Req Size = %d ",__FUNCTION__,iCount); 

    for(int i=0; i<iCount; i++)
    {
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        pRes = NULL;
        sql_Peer_Create_Check_Modifcation_Query(localPeerConfig,sStatement);    
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_PEER_ERR_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record is not present ");
            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,DEL_PEER_ERR_PEER_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_PEER_ERR_PEER_NOT_PRESENT;
        }

        delete pRes;
	pRes = NULL;
	PeerConfig localPeerConfigObj;
	localPeerConfigObj.set_altpeername(localPeerConfig -> peerhostname());

	sql_Peer_Create_Select_Query(&localPeerConfigObj,sStatement);
	if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	{
		if(pRes != NULL)        
		{
			delete pRes;
		}

		DLOG_ERROR("Query Execution Failed: %s",sStatement);

		if(iReturn == DRE_DB_FAIL)
			iReturn = DEL_PEER_ERR_DB_ERROR;

		mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}

	memset(sStatement,0,MAX_STATEMENT_SIZE);

	if(pRes->rowsCount() > 0) // ADD
	{
		delete pRes;
		DLOG_ERROR("##Cant delete its a alternate peer for some other Peer##");
		mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,DEL_PEER_ERR_USED_AS_ALTERNATE_PEER);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return DEL_PEER_ERR_USED_AS_ALTERNATE_PEER;
	}

	else
	{
	    delete pRes;
            sql_Peer_Create_Delete_Query(localPeerConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_PEER_ERR_DB_ERROR;

                mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerTimers_Create_Check_Modifcation_Query(localPeerConfig,sStatement);      
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)        
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed: %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_PEER_ERR_TIMERS_FAILED_DB_ERROR;

            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record is not present ");
            mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,DEL_PEER_ERR_TIMER_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_PEER_ERR_TIMER_NOT_PRESENT;
        }
        else
        {

            delete pRes;
            sql_PeerTimers_Create_Delete_Query(localPeerConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_PEER_ERR_TIMERS_FAILED_DB_ERROR;

                mysql_set_error_for_Peer_Config_Reqs(localPeerConfig,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

#if 0
        {
            RealmConfig lRealmConfig;

            if(localPeerConfig->has_realm())
            {
                lRealmConfig.set_realmname(localPeerConfig->realm());

                memset(sStatement,0,MAX_STATEMENT_SIZE);
                sql_RealmRouting_Create_Select_Query(&lRealmConfig,sStatement,0);
                pRes = NULL;

                if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
                {
                    if(pRes != NULL)        
                    {
                        delete pRes;
                    }

                    DLOG_ERROR("Query Execution Failed: %s",sStatement);
                    DLOG_NONE(" < %s ",__FUNCTION__);

                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DRE_DB_FAIL;

                    return iReturn;
                }


                if(pRes->rowsCount() == 0) // ADD
                {
                    memset(sStatement,0,MAX_STATEMENT_SIZE);
                    sql_Realm_Create_Delete_Query(&lRealmConfig,sStatement);
                    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                    {
                        if(pRes != NULL)        
                        {
                            delete pRes;
                        }

                        DLOG_ERROR("Query Execution Failed: %s",sStatement);
                        DLOG_NONE(" < %s ",__FUNCTION__);

                        if(iReturn == DRE_DB_FAIL)
                            iReturn = DRE_DB_FAIL;

                        return iReturn;
                    }
                }

                memset(sStatement,0,MAX_STATEMENT_SIZE);
                delete pRes;
            }
            else
            {
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DRE_DB_FAIL;
            }
        }
#endif
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_Get_RealmName_From_RealmRouting(PeerConfig *localPeerConfig,char *pRealmName)
{
    char sStatement[MAX_STATEMENT_SIZE];
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);
    RealmConfig lRealmConfig;
    ::Destination* localDestinationObj;

    localDestinationObj = lRealmConfig.add_destinfo();
    localDestinationObj->set_realmname(localPeerConfig->realm());
    localDestinationObj->set_peername(localPeerConfig->peerhostname());

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_RealmRouting_Create_Select_Query(&lRealmConfig,sStatement,1);
    pRes = NULL;

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = DRE_DB_FAIL;

        return iReturn;
    }


    if(pRes->rowsCount() > 0) // ADD
    {
        pRes->next();
        strcpy(pRealmName,(pRes->getString("REALM_NAME")).c_str());
    }
    else
    {

        delete pRes;
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_FAIL;
    }

    delete pRes;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;

}

DbStatus_e CMgrDbInterface::mysql_PeerSecondaryIp_Delete_validation(PeerConfig *pPeerConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerConfig->has_peerhostname() && pPeerConfig->has_realm())
    {
        sql_PeerMutiHoming_Create_Validation_Query_for_Peer(pPeerConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_SECONDARYIP_ERR_NOT_ASSOCIATED_WITH_PEER;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_PeerSecondaryIp_Delete_Config_Reqs_Through_Peer(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = pPeersConfig->peers_size();
    DLOG_DEBUG(" %s: PeersConfig Req Size = %d ",__FUNCTION__,iCount);    

    for(int i=0; i<iCount; i++) 
    {    
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        int iSecondaryIpCount = localPeerConfig->secondaryipaddr_size();
        DLOG_DEBUG(" %s: SecondaryIp Req Size = %d ",__FUNCTION__,iSecondaryIpCount);

        for(int j=0;j<iSecondaryIpCount;j++)
        {
            if((iReturn = mysql_PeerSecondaryIp_Delete_validation(localPeerConfig,j)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_PeerSecondaryIp_Config_Reqs(localPeerConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);   
                return iReturn;
            }


            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;
            sql_PeerMultiHoming_Create_Check_Modifcation_Query(localPeerConfig,sStatement,j);
            if((iReturn =  m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_SECONDARYIP_ERR_DB_ERROR;
                mysql_set_error_for_PeerSecondaryIp_Config_Reqs(localPeerConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                mysql_set_error_for_PeerSecondaryIp_Config_Reqs(localPeerConfig,resp,DEL_SECONDARYIP_ERR_NOT_ASSOCIATED_WITH_PEER,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_SECONDARYIP_ERR_NOT_ASSOCIATED_WITH_PEER;
            }
            else
            {

                delete pRes;
                sql_PeerMultiHoming_Create_Delete_Query(localPeerConfig,sStatement,j);
                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_SECONDARYIP_ERR_DB_ERROR;

                    mysql_set_error_for_PeerSecondaryIp_Config_Reqs(localPeerConfig,resp,iReturn,j);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }
            
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_PeerDictionaryMap_Delete_validation(PeerConfig *pPeerConfig,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerConfig->dictionaryname_size() > iIndex && iIndex > -1) 
    {   
        sql_PeerDictionaryMap_Create_Validation_Query_for_Dictionary(pPeerConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_DICTID_ERR_INVALID_DICTNAME;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }   

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    if(pPeerConfig->has_peerhostname() && pPeerConfig->has_realm())
    {
        sql_PeerDictionaryMap_Create_Validation_Query_for_Peer(pPeerConfig,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_DICTID_ERR_PEER_NOT_PRESENT;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerDictionaryMap_Delete_Config_Reqs_Through_Peer(PeersConfig *pPeersConfig,DRECfgResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);
    int iCount = pPeersConfig->peers_size();
    DLOG_DEBUG(" %s: PeersConfig Req Size = %d ",__FUNCTION__,iCount); 

    for(int i=0; i<iCount; i++)
    {
        ::PeerConfig* localPeerConfig = pPeersConfig->mutable_peers(i);

        int iCountDictionary = localPeerConfig->dictionaryname_size();
        DLOG_DEBUG(" %s: Dictionary Req Size = %d ",__FUNCTION__,iCountDictionary); 

        for(int j=0;j<iCountDictionary;j++)
        {
            if((iReturn = mysql_PeerDictionaryMap_Delete_validation(localPeerConfig,j)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_PeerDictionaryMap_Config_Reqs(localPeerConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);   
                return iReturn;
            }


            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;
            sql_PeerDictionaryMap_Create_Check_Modifcation_Query(localPeerConfig,sStatement,j);
            if((iReturn =  m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)        
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_DICTID_ERR_DB_ERROR;

                mysql_set_error_for_PeerDictionaryMap_Config_Reqs(localPeerConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                mysql_set_error_for_PeerDictionaryMap_Config_Reqs(localPeerConfig,resp,DEL_DICTID_ERR_NOT_ASSOCIATED_WITH_PEER,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_DICTID_ERR_NOT_ASSOCIATED_WITH_PEER;
            }
            else
            {
#if 0
                if((iReturn = check_last_PeerDicationary_configuration(localPeerConfig,j)) != DRE_DB_SUCCESS)
                {
                    delete pRes;
                    mysql_set_error_for_PeerDictionaryMap_Config_Reqs(localPeerConfig,resp,DEL_DICTID_LAST_DICTIONARY_ENTRY,j);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
                else
                {
                    sql_PeerDictionaryMap_Create_Delete_Query(localPeerConfig,sStatement,j);
                }
#else

                sql_PeerDictionaryMap_Create_Delete_Query(localPeerConfig,sStatement,j);
#endif
                delete pRes;

                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed: %s",sStatement);

                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_DICTID_ERR_DB_ERROR;

                    mysql_set_error_for_PeerDictionaryMap_Config_Reqs(localPeerConfig,resp,iReturn,j);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_DictionaryPeerConfig_Create_Select_Query(localPeerConfig,sStatement,i);
            pRes = NULL;

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)        
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed: %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_DICTID_ERR_DB_ERROR;

                mysql_set_error_for_PeerDictionaryMap_Config_Reqs(localPeerConfig,resp,iReturn,j);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            mysql_DictionaryName_resultset_to_peer_protoBuff(pRes,localPeerConfig,i);
            delete pRes;

        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::check_last_PeerDicationary_configuration(::PeerConfig *pPeerConfig,int iIndex)
{
	DLOG_NONE(" > %s ",__FUNCTION__);
	char sStatement[MAX_STATEMENT_SIZE] = {0};
	sql::ResultSet *pRes = NULL;
	DbStatus_e iReturn = DRE_DB_SUCCESS;


	sql_PeerDictionaryMap_Create_Select_Query(pPeerConfig,sStatement,iIndex);

	if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
	{
		if(pRes != NULL)	
		{
			delete pRes;
		}

		DLOG_ERROR("Query Execution Failed: %s",sStatement);
		DLOG_NONE(" < %s ",__FUNCTION__);
		return iReturn;
	}
	memset(sStatement,0,MAX_STATEMENT_SIZE);
    // check if this is the last Dicationary configuration 
    if(pRes->rowsCount() == 1)
	{
		iReturn = DRE_DB_FAIL;
	}
	else
	{
		iReturn = DRE_DB_SUCCESS;
	}

	delete pRes;

	DLOG_NONE(" < %s ",__FUNCTION__);
	return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_AlternatePeer_Validation(PeerConfig *pPeerConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    char sStatement[MAX_STATEMENT_SIZE] = {0};
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    memset(sStatement,0,MAX_STATEMENT_SIZE);
    PeerConfig localPeer;

    if(!pPeerConfig->has_altpeername())
    {
        DLOG_NONE(" < %s ",__FUNCTION__);
        return DRE_DB_SUCCESS;
    }

    //sql_Peer_Create_Check_Modifcation_Query(&localPeer,sStatement);
    sql_Peer_Create_Select_Query(&localPeer,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_PEER_ERR_DB_ERROR;

        return iReturn;
    }


    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_CRITICAL("We cannot configure First Peer with Alternate Peer.");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return SET_PEER_ERR_ALT_PEER_FIRST_PEER;
    }

    delete pRes;
    pRes = NULL;
    memset(sStatement,0,MAX_STATEMENT_SIZE);

    localPeer.set_peerhostname(pPeerConfig->altpeername());

    sql_Peer_Create_Select_Query(&localPeer,sStatement);

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)        
        {
            delete pRes;
            pRes = NULL;
        }
        DLOG_ERROR("Query Execution Failed: %s",sStatement);
        DLOG_NONE(" < %s ",__FUNCTION__);

        if(iReturn == DRE_DB_FAIL)
            iReturn = SET_PEER_ERR_DB_ERROR;

        return iReturn;
    }


    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("This is Not the first Peer, Alternate Peer passed is not present in Peer Table");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return  SET_PEER_ERR_ALT_PEER_NOT_PRESENT;
    }

    delete pRes;
    pRes = NULL;
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}
