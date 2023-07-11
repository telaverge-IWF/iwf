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

using namespace std;
extern std::map<int,std::string> errorMap;


CMgrDbInterface::CMgrDbInterface(string sHostName,string sUserName,string sPassword,string sDataBase,ConfigManager *pConfigManager,ConfigManagerAlarms *pConfigManagerAlarms):
    m_dbHandle(sHostName,sUserName,sPassword,sDataBase,pConfigManagerAlarms)
{
    DLOG_DEBUG("CMgrDbInterface: HOSTNAME %s",sHostName.c_str());
    m_ConfigManager = pConfigManager;
    m_ConfigManagerAlarms = pConfigManagerAlarms;
}

DbStatus_e CMgrDbInterface::mysql_PeerGroup_resultset_to_protoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" ResultSet Count = %d ",pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PEERGROUP_ERR_NO_DATA_PRESENT;
        }

        while(pRes->next())
        {
            mysql_check_and_Add_PeerGroup_resultset(pRes,resp);
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


DbStatus_e CMgrDbInterface::mysql_Peerid_to_protobuf(sql::ResultSet *pRes,::LBPeerGroup *resp,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" ResultSet Count = %d ",pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_SUCCESS;
        }

        ::LBPeer *pLBPeer = resp->mutable_lbpeers(iIndex);

        while(pRes->next())
        {
            if(!pRes->isNull("PeerID"))
            {
                DLOG_DEBUG(" PeerID %d %s ",pRes->getInt("PeerID"),__FUNCTION__);
                pLBPeer->set_lbpeerid(pRes->getInt("PeerID"));
            }
            else
                DLOG_DEBUG(" PEER_GRP_ID is NULL");
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



DbStatus_e CMgrDbInterface::mysql_PeerGroupid_to_protobuf(sql::ResultSet *pRes,::LBPeerGroup *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" ResultSet Count = %d ",pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DRE_DB_SUCCESS;
        }

        while(pRes->next())
        {
            if(!pRes->isNull("PEER_GRP_ID"))
            {
                DLOG_DEBUG(" PEER_GRP_ID %d %s ",pRes->getInt("PEER_GRP_ID"),__FUNCTION__);
                resp->set_lbpeergroupid(pRes->getInt("PEER_GRP_ID"));
            }
            else
                DLOG_DEBUG(" PEER_GRP_ID is NULL");
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



DbStatus_e CMgrDbInterface::mysql_PeerConfig_resultset_to_protoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    try
    {
        DLOG_DEBUG(" ResultSet Count = %d ",pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_PEERCONFIG_ERR_NO_DATA_PRESENT;
        }

        ::LBPeerGroup *pLBPeerGroup = resp->add_peergroups();

        while(pRes->next())
        {
            ::LBPeer *pLBPeer = pLBPeerGroup->add_lbpeers();
            pLBPeer->set_lbpeername(pRes->getString("PeerHostIdentity"));
            pLBPeer->set_lbpeerrealm(pRes->getString("RealmName"));
            pLBPeer->set_lbpeerweight(pRes->getInt("PEER_WEIGHT"));
            pLBPeer->set_lbpeerpriority(pRes->getInt("PEER_PRIORITY"));
            pLBPeer->set_lbpeerid(pRes->getInt("PeerID"));
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



void CMgrDbInterface::mysql_check_and_Add_PeerGroup_resultset(sql::ResultSet *pRes,LBPeerGroupResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = resp->peergroups_size();

    DLOG_DEBUG(" PeerGroupCount = %d ",iPeerGroupCount);
    for(int j=0; j<iPeerGroupCount; j++)
    {
        // Assuming that all this variable will be there
        ::LBPeerGroup* localPeerGroup = resp->mutable_peergroups(j);

        ::LBAlgorithm* localLBAlogrithm = localPeerGroup->mutable_lbalgo();

        if(localPeerGroup->lbpeergroupname() == pRes->getString("PEER_GRP_NAME") &&
                localPeerGroup->enablepcrfbinding() == pRes->getInt("ENABLE_PCRF_BINDING") &&
                localLBAlogrithm->lbmethod() == pRes->getString("LB_METHOD"))
        {
            mysql_add_PeerGroup_resultset_to_PeerProtoBuff(pRes,localPeerGroup);    
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }
    }   

    mysql_add_PeerGroup_resultset_to_PeerGroupProtoBuff(pRes,resp);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_add_PeerGroup_resultset_to_PeerGroupProtoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::LBPeerGroup* localPeerGroup = resp->add_peergroups();

    localPeerGroup->set_lbpeergroupname(pRes->getString("PEER_GRP_NAME"));
    localPeerGroup->set_lbpeergroupid(pRes->getInt("PEER_GRP_ID"));
    localPeerGroup->set_enablepcrfbinding(pRes->getInt("ENABLE_PCRF_BINDING"));

    ::LBAlgorithm *localLBALogrithm = localPeerGroup->mutable_lbalgo();

    localLBALogrithm->set_lbmethod(pRes->getString("LB_METHOD"));
    localLBALogrithm->set_lbmethoddesc(pRes->getString("DESCRIPTION"));

    mysql_add_PeerGroup_resultset_to_PeerProtoBuff(pRes,localPeerGroup);    

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_add_PeerGroup_resultset_to_PeerProtoBuff(sql::ResultSet *pRes,::LBPeerGroup *localPeerGroup)
{

    DLOG_NONE(" > %s ",__FUNCTION__);

    if(pRes->isNull("PeerHostIdentity"))
    {
        DLOG_DEBUG(" PeerHostIdentity is NULL ");
        DLOG_NONE(" < %s ",__FUNCTION__);
        return;
    }

    ::LBPeer* localLBPeerObj = localPeerGroup->add_lbpeers();

    if(!pRes->isNull("PeerHostIdentity"))
        localLBPeerObj->set_lbpeername(pRes->getString("PeerHostIdentity"));
    if(!pRes->isNull("RealmName"))
        localLBPeerObj->set_lbpeerrealm(pRes->getString("RealmName"));
    if(!pRes->isNull("PEER_WEIGHT"))
        localLBPeerObj->set_lbpeerweight(pRes->getInt("PEER_WEIGHT"));
    if(!pRes->isNull("PEER_PRIORITY"))
        localLBPeerObj->set_lbpeerpriority(pRes->getInt("PEER_PRIORITY"));
    if(!pRes->isNull("PeerID"))
        localLBPeerObj->set_lbpeerid(pRes->getInt("PeerID"));

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Lbalgo_resultset_to_protoBuff(sql::ResultSet *pRes,LBPeerGroupResp *resp,int component)
{

    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {
        DLOG_DEBUG(" Resultset Count = %d ",pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_LBALGO_ERR_NO_DATA_PRESENT;
        }
        int Andresult = 0;
        while(pRes->next())
        {
            int Lbcomponent = pRes->getInt("SUPPORTED_MODULES");
            if(component != 0)
            {
                Andresult = (Lbcomponent & component);
            }
            if(component == 0 || (Andresult == component))
            {
                ::LBAlgorithm* pLBAlgorithm = resp->add_lbalgos();

                pLBAlgorithm->set_lbmethod(pRes->getString("LB_METHOD"));
                pLBAlgorithm->set_lbmethoddesc(pRes->getString("DESCRIPTION"));
                pLBAlgorithm->set_suppcomponent((LBAlgorithm_SuppComponentID)pRes->getInt("SUPPORTED_MODULES"));
            }
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



DbStatus_e CMgrDbInterface::mysql_defaultRoute_resultset_to_protoBuff(sql::ResultSet *pRes,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    try
    {
        DLOG_DEBUG(" Resultset Count = %d ",pRes->rowsCount());
        if(pRes->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_DEFROUTE_ERR_NO_DATA_PRESENT;
        }


        while(pRes->next())
        {
            mysql_check_and_Add_defaultRoute_resultset(pRes,resp);
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

void CMgrDbInterface::mysql_check_and_Add_defaultRoute_resultset(sql::ResultSet *pRes,DRECfgResp *resp)
{
    ::RealmsConfig* localRealmsObj;

    DLOG_NONE(" > %s ",__FUNCTION__);

    localRealmsObj = resp->mutable_realms();

    int iRealmCount = localRealmsObj->realms_size();
    DLOG_DEBUG(" iRealmCount = %d ",iRealmCount);
    for(int j=0; j<iRealmCount; j++)
    {
        ::RealmConfig* localRealmObj = localRealmsObj->mutable_realms(j);

        if(localRealmObj->realmname() == pRes->getString("RealmName"))
        {

            mysql_add_defaultRoute_resultset_to_DestinationProtoBuff(pRes,localRealmObj);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return; 
        }
    }

    mysql_add_defaultRoute_resultset_to_RealmProtoBuff(pRes,localRealmsObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_add_defaultRoute_resultset_to_RealmProtoBuff(sql::ResultSet *pRes,RealmsConfig* localRealmsObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::RealmConfig* localRealmObj = localRealmsObj->add_realms();

    localRealmObj->set_realmname(pRes->getString("RealmName"));

    mysql_add_realm_resultset_to_DestinationProtoBuff(pRes,localRealmObj);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_add_defaultRoute_resultset_to_DestinationProtoBuff(sql::ResultSet *pRes,RealmConfig* localRealmObj)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::Destination* localDestionationObj = localRealmObj->add_destinfo();

    localDestionationObj->set_peername(pRes->getString("PeerHostIdentity"));

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

#if 0
DbStatus_e CMgrDbInterface::mysql_DefaultRoute_resultset_to_protoBuff(sql::ResultSet *pResDefaultR,DRECfgResp *resp)
{

    DLOG_NONE(" < %s ",__FUNCTION__);
    try
    {
        if(pResDefaultR->rowsCount() == 0)
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return GET_DEFROUTE_ERR_NO_DATA_PRESENT;
        }

        ::PeersConfig* localPeersObj = resp->mutable_peers();

        while(pResDefaultR->next())
        {
            ::PeerConfig* localPeerObj = localPeersObj->add_peers();    

            localPeerObj->set_realm(pResDefaultR->getString("RealmName"));
            localPeerObj->set_peerhostname(pResDefaultR->getString("PeerHostIdentity"));
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
#endif

void CMgrDbInterface::mysql_set_error_for_LocalTransportTagResponse_Config_Reqs(LocalTransportTagResponse *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_StaticRoutingTableConfigResp_Config_Reqs(StaticRoutingTableConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    DLOG_NONE(" < %s ",__FUNCTION__);
}


void CMgrDbInterface::mysql_set_error_for_StackConfigResponse_Config_Reqs(StackConfigResponse *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_drecfgResp_Config_Reqs(DRECfgResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_LBPeerGroupResp_Config_Reqs(LBPeerGroupResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_DynDictionaryResponse_Config_Reqs(DynDictionaryResponse *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_AvaMgrConfigResp_Config_Reqs(AvaMgrConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_RepMgrConfigResp_Config_Reqs(RepMgrConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_DreHAConfigResp_Config_Reqs(DreHAConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
#if 0
    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
#endif
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_UserResp_Config_Reqs(UserResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_LoggerConfResp_Config_Reqs(LoggerConfResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_AsfConfResp_Config_Reqs(ASFConfigResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_TraceResp_Config_Reqs(TraceResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_Lbalgo_Config_Reqs(::LBAlgorithm *pLBAlgorithm, LBPeerGroupResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pLBAlgorithm->has_lbmethod())
        err->add_variables(pLBAlgorithm->lbmethod());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_PeerGroup_Config_Reqs(::LBPeerGroup *pLBPeerGroup, LBPeerGroupResp *resp,DbStatus_e iReturn)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pLBPeerGroup->has_lbpeergroupname())
        err->add_variables(pLBPeerGroup->lbpeergroupname());

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_PeerGroupMap_Config_Reqs(::LBPeerGroup *pLBPeerGroup, LBPeerGroupResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::LBPeer *pLBPeer;

    if(iIndex != -1)
        pLBPeer = pLBPeerGroup->mutable_lbpeers(iIndex);

    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(iIndex != -1)
    {
        if(pLBPeer->has_lbpeername())
            err->add_variables(pLBPeer->lbpeername());
    }

    if(pLBPeerGroup->has_lbpeergroupname())
        err->add_variables(pLBPeerGroup->lbpeergroupname());

    if(iIndex != -1)
    {
        if(pLBPeer->has_lbpeerrealm())
            err->add_variables(pLBPeer->lbpeerrealm());
    }



    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::mysql_set_error_for_DefaultRoute_Config_Reqs(RealmConfig *pRealmConfig, DRECfgResp *resp,DbStatus_e iReturn,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);


    ErrorDetails* err = resp->add_errordetails();
    err->set_errorcode(iReturn);
    err->set_errormsgkey(errorMap[iReturn]);
    DLOG_DEBUG("Error key is %s", (errorMap[iReturn]).c_str());

    if(pRealmConfig->has_realmname())
        err->add_variables(pRealmConfig->realmname());


    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::mysql_Lbalgo_Add_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::LBAlgorithm* pLBAlgorithm;
    ::LBAlgorithm  localLBAlgorithm;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("iPeerGroupCount = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {

        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);
        if(!pLBPeerGroup->has_lbalgo())
            pLBAlgorithm = &localLBAlgorithm;
        else
            pLBAlgorithm = pLBPeerGroup->mutable_lbalgo();  



        if((iReturn = sql_LbAlgorithm_Payload_Validation(pLBAlgorithm)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("LBalgorithm Validation Failed");
            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_LbAlgorithm_Create_Check_Modifcation_Query(pLBAlgorithm,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_LbAlgorithm_Create_Add_Query(pLBAlgorithm,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");
            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,ADD_LBALGO_ERR_LBALGO_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_LBALGO_ERR_LBALGO_ALREADY_PRESENT;

        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_LBALGO_ERR_DB_ERROR;

            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;

        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}



DbStatus_e CMgrDbInterface::mysql_Lbalgo_Mod_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::LBAlgorithm* pLBAlgorithm;
    ::LBAlgorithm  localLBAlgorithm;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("PeerGroupCount = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);
        if(!pLBPeerGroup->has_lbalgo())
            pLBAlgorithm = &localLBAlgorithm;
        else
            pLBAlgorithm = pLBPeerGroup->mutable_lbalgo();  



        if((iReturn = sql_LbAlgorithm_Payload_Validation(pLBAlgorithm)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("LBalgorithm Validation Failed");
            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_LbAlgorithm_Create_Check_Modifcation_Query(pLBAlgorithm,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);


            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_LBALGO_ERR_DB_ERROR;

            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;

        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record is not present ");
            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,MOD_LBALGO_ERR_LBALGO_NOT_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return MOD_LBALGO_ERR_LBALGO_NOT_PRESENT;

        }
        else // MOD
        {
            sql_LbAlgorithm_Create_Mod_Query(pLBAlgorithm,sStatement);
        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_LBALGO_ERR_DB_ERROR;

            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);

            return iReturn;
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerGroup_Add_validation(LBPeerGroup *pPeerGroup)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerGroup->has_lbalgo())
    {
        sql_PeerGroup_Create_Validation_Query_for_Lbalgo(pPeerGroup,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEERGROUP_ERR_LBALGO_INVALID;

        }
    }

    return iReturn;
    DLOG_NONE(" < %s ",__FUNCTION__);
}


DbStatus_e CMgrDbInterface::mysql_PeerGroup_Add_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("iPeerGroupCount = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);

        if((iReturn = mysql_PeerGroup_Add_validation(pLBPeerGroup)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }

        if((iReturn = sql_PeerGroup_Payload_Validation(pLBPeerGroup)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Peergroup Validation Failed");
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroup_Create_Check_Modifcation_Query(pLBPeerGroup,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            sql_PeerGroup_Create_Add_Query(pLBPeerGroup,sStatement);
        }
        else // MOD
        {
            delete pRes;
            DLOG_ERROR("Record Already Present");   
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,ADD_PEERGROUP_ERR_PEER_GROUP_ALREADY_PRESENT);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return ADD_PEERGROUP_ERR_PEER_GROUP_ALREADY_PRESENT;

        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroup_Create_Select_Query(pLBPeerGroup,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(pRes != NULL)    
            {
                delete pRes;
            }

            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        mysql_PeerGroupid_to_protobuf(pRes,pLBPeerGroup);
        delete pRes;
    }

    iReturn = mysql_PeerConfig_Add_Config_Reqs(pLBPeerGroupReq,resp);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerGroup_Mod_validation(LBPeerGroup *pPeerGroup)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pPeerGroup->has_lbalgo())
    {
        sql_PeerGroup_Create_Validation_Query_for_Lbalgo(pPeerGroup,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEERGROUP_ERR_LBALGO_INVALID;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerGroup_Mod_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("iPeerGroupCount = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);

        if((iReturn = mysql_PeerGroup_Mod_validation(pLBPeerGroup)) != DRE_DB_SUCCESS)
        {
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);   
            return iReturn;
        }


        if((iReturn = sql_PeerGroup_Payload_Validation(pLBPeerGroup)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Peergroup Validation Failed");
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroup_Create_Check_Modifcation_Query(pLBPeerGroup,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }
            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            delete pRes;
            DLOG_ERROR("Record is not present ");

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,MOD_PEERGROUP_ERR_PEER_GROUP_DOESNT_EXIST);
            DLOG_NONE(" < %s ",__FUNCTION__);

            return MOD_PEERGROUP_ERR_PEER_GROUP_DOESNT_EXIST;

        }
        else // MOD
        {
            sql_PeerGroup_Create_Mod_Query(pLBPeerGroup,sStatement);

        }

        delete pRes;
        if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
        {
            DLOG_ERROR("Query Execution Failed %s",sStatement);
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEERGROUP_ERR_DB_ERROR;  

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        pRes = NULL;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroup_Create_Select_Query(pLBPeerGroup,sStatement);

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEERGROUP_ERR_DB_ERROR;  

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        mysql_PeerGroupid_to_protobuf(pRes,pLBPeerGroup);
        delete pRes;

    }

    iReturn = mysql_PeerConfig_Mod_Config_Reqs(pLBPeerGroupReq,resp);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerConfig_Mod_validation(::LBPeerGroup* pLBPeerGroup,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pLBPeerGroup->lbpeers_size() > iIndex && iIndex > -1) 
    {   
        sql_PeerGroupMap_Create_Validation_Query_for_Peer(pLBPeerGroup,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = MOD_PEERCONFIG_ERR_PEER_DOESNT_EXIST;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_PeerGroupMap_Create_Validation_Query_for_PeerGroup(pLBPeerGroup,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_PEERCONFIG_ERR_PEER_GROUP_DOESNT_EXIST;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}

DbStatus_e CMgrDbInterface::mysql_PeerConfig_Mod_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("iPeerGroupCount = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);

        int iPeerCount = pLBPeerGroup->lbpeers_size();  

        DLOG_DEBUG(" %s: iPeerCount = %d ",__FUNCTION__,iPeerCount);
        for(int i=0;i<iPeerCount;i++)
        {

            pRes = NULL;

            if((iReturn = mysql_PeerConfig_Add_validation(pLBPeerGroup,i)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);   
                return iReturn;
            }

            if((iReturn = sql_PeerGroupMap_Payload_Validation(pLBPeerGroup,i)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("PeergroupMap Validation Failed");
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_PeerGroupMap_Create_Check_Modifcation_Query(pLBPeerGroup,sStatement,i);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;

            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                delete pRes;
                DLOG_ERROR("Record is not present ");
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,MOD_PEERCONFIG_ERR_PEER_WITH_REALM_NOT_PRESENT_IN_GROUP,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return MOD_PEERCONFIG_ERR_PEER_WITH_REALM_NOT_PRESENT_IN_GROUP;

            }
            else // MOD
            {
                sql_PeerGroupMap_Create_Mod_Query(pLBPeerGroup,sStatement,i);

            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = MOD_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;

            ::PeerConfig localPeerConfig;
            ::LBPeer *pLBPeer = pLBPeerGroup->mutable_lbpeers(i);
            localPeerConfig.set_peerhostname(pLBPeer->lbpeername());
            localPeerConfig.set_realm(pLBPeer->lbpeerrealm());

            sql_Peer_Create_Select_Query(&localPeerConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            mysql_Peerid_to_protobuf(pRes,pLBPeerGroup,i);

            delete pRes;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

DbStatus_e CMgrDbInterface::mysql_PeerConfig_Add_validation(::LBPeerGroup* pLBPeerGroup,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pLBPeerGroup->lbpeers_size() > iIndex && iIndex > -1) 
    {   
        sql_PeerGroupMap_Create_Validation_Query_for_Peer(pLBPeerGroup,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = ADD_PEERCONFIG_ERR_PEER_DOESNT_EXIST;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_PeerGroupMap_Create_Validation_Query_for_PeerGroup(pLBPeerGroup,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = ADD_PEERCONFIG_ERR_PEER_GROUP_DOESNT_EXIST;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}



DbStatus_e CMgrDbInterface::mysql_PeerConfig_Add_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    DLOG_NONE(" > %s ",__FUNCTION__);


    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("iPeerGroupCount = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);

        int iPeerCount = pLBPeerGroup->lbpeers_size();  
        DLOG_DEBUG(" %s: iPeerCount = %d ",__FUNCTION__,iPeerCount);

        for(int i=0;i<iPeerCount;i++)
        {

            pRes = NULL;

            if((iReturn = mysql_PeerConfig_Add_validation(pLBPeerGroup,i)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);   
                return iReturn;
            }

            if((iReturn = sql_PeerGroupMap_Payload_Validation(pLBPeerGroup,i)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("PeergroupMap Validation Failed");
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_PeerGroupMap_Create_Check_Modifcation_Query(pLBPeerGroup,sStatement,i);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                sql_PeerGroupMap_Create_Add_Query(pLBPeerGroup,sStatement,i);

            }
            else // MOD
            {
                delete pRes;
                DLOG_ERROR("Record Already Present");   
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,ADD_PEERCONFIG_ERR_PEER_WITH_REALM_ALREADY_PRESENT_IN_GROUP,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return ADD_PEERCONFIG_ERR_PEER_WITH_REALM_ALREADY_PRESENT_IN_GROUP;

            }

            delete pRes;
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;

            ::PeerConfig localPeerConfig;
            ::LBPeer *pLBPeer = pLBPeerGroup->mutable_lbpeers(i);
            localPeerConfig.set_peerhostname(pLBPeer->lbpeername());
            localPeerConfig.set_realm(pLBPeer->lbpeerrealm());

            sql_Peer_Create_Select_Query(&localPeerConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = ADD_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            mysql_Peerid_to_protobuf(pRes,pLBPeerGroup,i);
            delete pRes;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}





DbStatus_e CMgrDbInterface::mysql_DefaultRoute_Mod_Config_Reqs_Through_Realm(RealmConfig *pRealmConfig,DRECfgResp *resp, int iDestinationIndex)
{
    sql::ResultSet *pRes = NULL;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn = DRE_DB_FAIL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    if((iReturn = sql_DefaultRoute_Payload_Validation(pRealmConfig,iDestinationIndex)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("DefualtRoute Configuration Validation Failed");
        mysql_set_error_for_DefaultRoute_Config_Reqs(pRealmConfig,resp,iReturn,iDestinationIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if(sql_DefaultRoute_Check_All_Invalid(pRealmConfig,iDestinationIndex) == DRE_DB_SUCCESS)
    {
        DLOG_ERROR("DefaultRoute Modify: Only Primary Key is set");
        mysql_set_error_for_DefaultRoute_Config_Reqs(pRealmConfig,resp,MOD_DEFROUTE_ERR_NO_FIELD_IS_SET_FOR_MODIFICATION,iDestinationIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_DEFROUTE_ERR_NO_FIELD_IS_SET_FOR_MODIFICATION;
    }



    sql_DefaultRoute_Create_Check_Modifcation_Query(pRealmConfig,sStatement,iDestinationIndex);
    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }


        DLOG_ERROR("Query Execution Failed %s",sStatement);
        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_DEFROUTE_ERR_DB_ERROR;

        mysql_set_error_for_DefaultRoute_Config_Reqs(pRealmConfig,resp,iReturn,iDestinationIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_ERROR("Record is not present ");
        mysql_set_error_for_DefaultRoute_Config_Reqs(pRealmConfig,resp,MOD_DEFROUTE_ERR_RECORD_NOT_PRESENT,iDestinationIndex);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_DEFROUTE_ERR_RECORD_NOT_PRESENT;

    }
    else // MOD
    {
        sql_DefaultRoute_Create_Mod_Query(pRealmConfig,sStatement,iDestinationIndex);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_DEFROUTE_ERR_DB_ERROR;

        mysql_set_error_for_DefaultRoute_Config_Reqs(pRealmConfig,resp,iReturn,iDestinationIndex);

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}


DbStatus_e CMgrDbInterface::mysql_LocalHost_Mod_Config_Reqs(LocalHostConfig *pLocalHostConfig,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    sql_LocalHostConfig_Create_Check_Modifcation_Query(pLocalHostConfig,sStatement);    

    if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_HOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,iReturn);

        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);

    if(pRes->rowsCount() == 0) // ADD
    {
        delete pRes;
        DLOG_NONE("%s:%d Record is not Present\n",__FUNCTION__,__LINE__);
        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,MOD_HOST_ERR_HOST_NOT_PRESENT);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return MOD_HOST_ERR_HOST_NOT_PRESENT;
    }
    else // MOD
    {

        sql_LocalHostConfig_Create_Mod_Query(pLocalHostConfig,sStatement);
    }

    delete pRes;
    if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
    {   
        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = MOD_HOST_ERR_DB_ERROR;

        mysql_set_error_for_LocalHost_Config_Reqs(pLocalHostConfig,resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);   
        return iReturn;
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}




DbStatus_e CMgrDbInterface::mysql_PeerGroup_Get_Config_Reqs(LBPeerGroupReq *req,LBPeerGroupResp *Resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = req->peergroups_size();
    DLOG_DEBUG(" %s: LBPeerGroupReq count = %d ",__FUNCTION__,iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = req->mutable_peergroups(j);
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroupMapAndPeerGrpAndAlgorithm_Create_Select_Query(pLBPeerGroup,sStatement);        

        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,Resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_PeerGroup_resultset_to_protoBuff(pRes,Resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            if(iReturn == GET_PEERGROUP_ERR_NO_DATA_PRESENT)
                iReturn = GET_PEERGROUP_ERR_NO_PEERGROUP_PRESENT;
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,Resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        delete pRes;
    }

    if(iPeerGroupCount == 0)
    {
        pRes = NULL;
        LBPeerGroup localLBPeerGroup;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroupMapAndPeerGrpAndAlgorithm_Create_Select_Query(&localLBPeerGroup,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(&localLBPeerGroup,Resp,iReturn);

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_PeerGroup_resultset_to_protoBuff(pRes,Resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;

            mysql_set_error_for_PeerGroup_Config_Reqs(&localLBPeerGroup,Resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_PeerConfig_Get_Config_Reqs(LBPeerGroupReq *req,LBPeerGroupResp *Resp)
{
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = req->peergroups_size();
    DLOG_DEBUG("LBPeerGroupReq Count = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {
        ::LBPeerGroup *pLBPeerGroup = req->mutable_peergroups(j);

        int iPeerCount = pLBPeerGroup->lbpeers_size();  
        DLOG_NONE(" %s: iPeerCount = %d ",__FUNCTION__,iPeerCount);

        for(int i=0;i<iPeerCount;i++)
        {
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_PeerGroupMap_Create_Select_Query(pLBPeerGroup,sStatement,i);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_PEERCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,Resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_PeerConfig_resultset_to_protoBuff(pRes,Resp)) != DRE_DB_SUCCESS)
            {
                if(iReturn == GET_PEERCONFIG_ERR_NO_DATA_PRESENT)
                    iReturn = GET_PEERCONFIG_ERR_NO_PEERCONFIG_PRESENT;
                delete pRes;
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,Resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }


            delete pRes;
        }

        if(iPeerCount == 0)
        {
            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_PeerGroupMap_Create_Select_Query(pLBPeerGroup,sStatement,0);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = GET_PEERCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,Resp,iReturn,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            if((iReturn = mysql_PeerConfig_resultset_to_protoBuff(pRes,Resp)) != DRE_DB_SUCCESS)
            {
                delete pRes;
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,Resp,iReturn,-1);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }


            delete pRes;

        }
    }

    if(iPeerGroupCount == 0)
    {
        pRes = NULL;
        ::LBPeerGroup localLBPeerGroup;
        memset(sStatement,0,MAX_STATEMENT_SIZE);
        sql_PeerGroupMap_Create_Select_Query(&localLBPeerGroup,sStatement,0);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = GET_PEERCONFIG_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroupMap_Config_Reqs(&localLBPeerGroup,Resp,iReturn,-1);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        if((iReturn = mysql_PeerConfig_resultset_to_protoBuff(pRes,Resp)) != DRE_DB_SUCCESS)
        {
            delete pRes;
            mysql_set_error_for_PeerGroupMap_Config_Reqs(&localLBPeerGroup,Resp,iReturn,-1);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }


        delete pRes;

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_Lbalgo_Get_Config_Reqs(LBPeerGroupReq *req,LBPeerGroupResp *Resp)
{
    int component = 0;
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    sql::ResultSet *pRes = NULL;
    ::LBAlgorithm* pLBAlgorithm;
    ::LBAlgorithm  localLBAlgorithm;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = req->peergroups_size();
    DLOG_DEBUG("LBPeerGroupReq Count = %d ",iPeerGroupCount);

    if(iPeerGroupCount != 0)
    {
        LBPeerGroup *LBPeerG = req->mutable_peergroups(0);
        LBAlgorithm *AlgoSch = LBPeerG->mutable_lbalgo();
        if(AlgoSch->has_suppcomponent())
            component = AlgoSch->suppcomponent();
    }


    pLBAlgorithm = &localLBAlgorithm;
    sql_LbAlgorithm_Create_Select_Query(pLBAlgorithm,sStatement);
    if ((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
    {
        if(pRes != NULL)    
        {
            delete pRes;
        }

        DLOG_ERROR("Query Execution Failed %s",sStatement);

        if(iReturn == DRE_DB_FAIL)
            iReturn = GET_LBALGO_ERR_DB_ERROR;


        mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,Resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    if((iReturn = mysql_Lbalgo_resultset_to_protoBuff(pRes,Resp,component)) != DRE_DB_SUCCESS)
    {
        delete pRes;
        mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,Resp,iReturn);
        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    delete pRes;

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_PeerGroup_Delete_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("LBPeerGroupReq Count = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {

        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);

        sql_PeerGroup_Create_Check_Modifcation_Query(pLBPeerGroup,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_PEERGROUP_ERR_DB_ERROR;

            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            DLOG_ERROR("Record is not present ");
            delete pRes;
            mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,DEL_PEERGROUP_ERR_PEER_GROUP_DOESNT_EXIST);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_PEERGROUP_ERR_PEER_GROUP_DOESNT_EXIST;
        }
        else
        {

            delete pRes;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_PeerGroup_Create_Delete_Query(pLBPeerGroup,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_PEERGROUP_ERR_DB_ERROR;

                mysql_set_error_for_PeerGroup_Config_Reqs(pLBPeerGroup,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}


DbStatus_e CMgrDbInterface::mysql_Lbalgo_Delete_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    char sStatement[MAX_STATEMENT_SIZE];
    sql::ResultSet *pRes = NULL;
    DbStatus_e iReturn =  DRE_DB_SUCCESS;
    ::LBAlgorithm* pLBAlgorithm;
    ::LBAlgorithm  localLBAlgorithm;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("LBPeerGroupReq Count = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {

        pRes = NULL;
        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);
        if(!pLBPeerGroup->has_lbalgo())
            pLBAlgorithm = &localLBAlgorithm;
        else
            pLBAlgorithm = pLBPeerGroup->mutable_lbalgo();  


        sql_LbAlgorithm_Create_Check_Modifcation_Query(pLBAlgorithm,sStatement);
        if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
        {
            if(pRes != NULL)    
            {
                delete pRes;
            }

            DLOG_ERROR("Query Execution Failed %s",sStatement);

            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_LBALGO_ERR_DB_ERROR;

            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

        memset(sStatement,0,MAX_STATEMENT_SIZE);

        if(pRes->rowsCount() == 0) // ADD
        {
            DLOG_ERROR("Record is not present ");
            delete pRes;
            mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,DEL_LBALGO_ERR_LBMETHOD_DOESNT_EXIST);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return DEL_LBALGO_ERR_LBMETHOD_DOESNT_EXIST;
        }
        else
        {
            delete pRes;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_LbAlgorithm_Create_Delete_Query(pLBAlgorithm,sStatement);
            if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
            {
                DLOG_ERROR("Query Execution Failed %s",sStatement);
                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_LBALGO_ERR_DB_ERROR;

                mysql_set_error_for_Lbalgo_Config_Reqs(pLBAlgorithm,resp,iReturn);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }
        }

    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}

void CMgrDbInterface::Copy_PeersConfig_request_to_Response(PeersConfig *req,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    PeersConfig localPeer;

    if(resp->has_peers())
    {
        PeersConfig *localRespPeers = resp->mutable_peers();

        int iRespPeerCount = localRespPeers->peers_size();
        DLOG_NONE("%s: Num of Peers send from dre = %d ",__FUNCTION__,iRespPeerCount);

        int iReqPeerCount = req->peers_size();

        if(iReqPeerCount == 0)
        {
            DLOG_NONE(" Request Peer Count is 0 %s ",__FUNCTION__);
            /*
             * In this cli/gui will not send any peer,
             * so Peersize will be zero in the request
             *
             * but dre will send all the configured peer.
             * so here we fill the request with the response from DRE
             * in next function it will query DB one by one and fill rest
             * of the data
             */
            req->CopyFrom(*localRespPeers);
            DLOG_NONE(" < %s ",__FUNCTION__);
            return;
        }

        DLOG_NONE(" Request Peer Count is  %d : %s ",iReqPeerCount,__FUNCTION__);
        /*
         * If the control reach this part of the code, then
         * from CLI/GUI user has asked for a specific Peer
         * that peer information will be there in the request
         *
         * But dre still response will all the peer configure
         * in the below loop, we are filtering out the peer which
         * are not set from the CLI
         *
         */
        for(int i=0;i<iRespPeerCount;i++)
        {
            PeerConfig *localRespPeer = localRespPeers->mutable_peers(i);
            for(int j=0;j<iReqPeerCount;j++)
            {

                PeerConfig *localReqPeer = req->mutable_peers(j);

                if(localRespPeer->has_peerhostname() && localReqPeer->has_peerhostname())
                {
                    if(localRespPeer->peerhostname() == localReqPeer->peerhostname())
                    {
                        if(localRespPeer->has_realm() && localReqPeer->has_realm())
                        {
                            if(localRespPeer->realm() == localReqPeer->realm())
                            {
                                PeerConfig *localPeerConfig = localPeer.add_peers();
                                localPeerConfig->CopyFrom(*localRespPeer);
                                DLOG_NONE("Response from DRE -Req modified to = %s",localPeerConfig->DebugString().c_str());
                            }
                        }
                    } 
                }
            } 
        }

        localRespPeers->Clear();
        localRespPeers->CopyFrom(localPeer);
    }
    else
    {
        DLOG_NONE(" %s: No Peers are send from dre ",__FUNCTION__);
    }


    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::Copy_DRECfgResp_localresponse_to_Reponse(DRECfgResp *localresp,DRECfgResp *resp)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    PeersConfig localPeer;

    if(resp->has_peers())
    {
        PeersConfig *RespPeers = resp->mutable_peers();
        PeersConfig *localRespPeers = localresp->mutable_peers();

        int ilocalRespPeerCount = localRespPeers->peers_size();
        int iRespPeerCount = RespPeers->peers_size();

        for(int i=0;i<iRespPeerCount;i++)
        {
            PeerConfig *pPeer = RespPeers->mutable_peers(i);
            for(int j=0;j<ilocalRespPeerCount;j++)
            {
                PeerConfig *plocalPeer = localRespPeers->mutable_peers(i);
                if(pPeer->has_peerhostname() && plocalPeer->has_peerhostname())
                {
                    if(pPeer->peerhostname() == plocalPeer->peerhostname())
                    {
                        if(pPeer->has_realm() && plocalPeer->has_realm()) 
                        {
                            if(pPeer->realm() == plocalPeer->realm()) 
                            {
                                PeerConfig *localPeerConfig = localPeer.add_peers();
                                localPeerConfig->CopyFrom(*plocalPeer);
                                localPeerConfig->MergeFrom(*pPeer);

                            }
                        }

                    }
                }
            }
        }

        RespPeers->Clear();
        RespPeers->CopyFrom(localPeer);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
}

DbStatus_e CMgrDbInterface::check_for_requestid(PeersConfig *req, DRECfgResp *resp)
{
    int iOperID = -1;
    DbStatus_e iReturn = DRE_DB_SUCCESS;
    PeersConfig localreq;
    DRECfgResp localDRECfgResp;

    DLOG_NONE(" > %s ",__FUNCTION__);


    DLOG_NONE(" req %p %s ",req,__FUNCTION__);    
    if(req->has_operreqid())
    {
        DLOG_NONE("%s Operreq ID is set in Peers ",__FUNCTION__);
        iOperID = req->operreqid();
    }

    DLOG_NONE(" OperID = %d %s ",iOperID,__FUNCTION__);

    if (DRE_DB_FAIL == m_dbHandle.mysql_set_current_connection())
    {
        DLOG_CRITICAL("Failed to Get the Database Connection");    
        resp->set_respcode(CMAPI_ERROR);
        mysql_set_error_for_drecfgResp_Config_Reqs(resp,CONFIG_COMMON_ERR_FAIL_TO_GET_CONN_FROM_CONN_POOL);
        return 0;
    }  

    switch(iOperID)
    {
        case GET_PEER:
            Copy_PeersConfig_request_to_Response(req,resp);
            iReturn = mysql_Peer_Get_Config_Reqs_for_peerstat(req,resp);
            break;
        case GET_PEERSTATE:
            break;
        case GET_REALMOFPEER:
            iReturn = mysql_PeerOfRealm_Get_Config_Reqs(req,&localDRECfgResp);
            Copy_DRECfgResp_localresponse_to_Reponse(&localDRECfgResp,resp);
            break;
        default:
            DLOG_NONE(" OperID default %s ",__FUNCTION__);
            break;
    }

    if(iReturn == DRE_DB_SUCCESS)
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_PEER_ERR_NO_PEER_PRESENT) 
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_PEER_ERR_NO_DATA_PRESENT) 
        resp->set_respcode(CMAPI_SUCCESS);
    else if(iReturn == GET_REALMOFPEER_ERR_NO_DATA_PRESENT)
        resp->set_respcode(CMAPI_SUCCESS);
    else 
        resp->set_respcode(CMAPI_ERROR);


    m_dbHandle.mysql_release_current_connection();

    DLOG_NONE(" < %s ",__FUNCTION__);
    return DRE_DB_SUCCESS;
}

DbStatus_e CMgrDbInterface::mysql_PeerConfig_Delete_validation(::LBPeerGroup* pLBPeerGroup,int iIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);
    char sStatement[MAX_STATEMENT_SIZE] = {0};
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    if(pLBPeerGroup->lbpeers_size() > iIndex && iIndex > -1) 
    {   
        sql_PeerGroupMap_Create_Validation_Query_for_Peer(pLBPeerGroup,sStatement,iIndex);
        if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
        {
            if(iReturn == DRE_DB_FAIL)
                iReturn = DEL_PEERCONFIG_ERR_PEER_DOESNT_EXIST;

            DLOG_NONE(" < %s ",__FUNCTION__);
            return iReturn;
        }

    }

    memset(sStatement,0,MAX_STATEMENT_SIZE);
    sql_PeerGroupMap_Create_Validation_Query_for_PeerGroup(pLBPeerGroup,sStatement);
    if((iReturn = m_dbHandle.mysql_exec_and_check_get_query(sStatement)) != DRE_DB_SUCCESS)
    {
        if(iReturn == DRE_DB_FAIL)
            iReturn = DEL_PEERCONFIG_ERR_PEER_GROUP_DOESNT_EXIST;

        DLOG_NONE(" < %s ",__FUNCTION__);
        return iReturn;
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;

}



DbStatus_e CMgrDbInterface::mysql_PeerConfig_Delete_Config_Reqs(LBPeerGroupReq *pLBPeerGroupReq,LBPeerGroupResp *resp)
{
    DbStatus_e iReturn =  DRE_DB_SUCCESS;

    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = pLBPeerGroupReq->peergroups_size();
    DLOG_DEBUG("LBPeerGroupReq Count = %d ",iPeerGroupCount);

    for(int j=0;j<iPeerGroupCount;j++)
    {

        char sStatement[MAX_STATEMENT_SIZE] = {0};
        sql::ResultSet *pRes = NULL;

        ::LBPeerGroup *pLBPeerGroup = pLBPeerGroupReq->mutable_peergroups(j);
        int iPeerCount = pLBPeerGroup->lbpeers_size();  
        DLOG_DEBUG("LBPeer Req Count = %d ",__FUNCTION__,iPeerCount);

        for(int i=0;i<iPeerCount;i++)
        {
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            pRes = NULL;

            if((iReturn = mysql_PeerConfig_Delete_validation(pLBPeerGroup,i)) != DRE_DB_SUCCESS)
            {
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);   
                return iReturn;
            }


            sql_PeerGroupMap_Create_Check_Modifcation_Query(pLBPeerGroup,sStatement,i);
            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }

                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn =  DEL_PEERCONFIG_ERR_DB_ERROR;

                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            memset(sStatement,0,MAX_STATEMENT_SIZE);

            if(pRes->rowsCount() == 0) // ADD
            {
                DLOG_ERROR("Record is not present ");
                delete pRes;
                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,DEL_PEERCONFIG_ERR_PEER_WITH_REALM_NOT_PRESENT_IN_GROUP,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return DEL_PEERCONFIG_ERR_PEER_WITH_REALM_NOT_PRESENT_IN_GROUP;
            }
            else
            {

                delete pRes;
                memset(sStatement,0,MAX_STATEMENT_SIZE);
                sql_PeerGroupMap_Create_Delete_Query(pLBPeerGroup,sStatement,i);
                if((iReturn = m_dbHandle.mysql_exec_set_query(sStatement)) != DRE_DB_SUCCESS)
                {
                    DLOG_ERROR("Query Execution Failed %s",sStatement);

                    if(iReturn == DRE_DB_FAIL)
                        iReturn = DEL_PEERCONFIG_ERR_DB_ERROR;

                    mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                    DLOG_NONE(" < %s ",__FUNCTION__);
                    return iReturn;
                }
            }

            ::PeerConfig localPeerConfig;
            ::LBPeer *pLBPeer = pLBPeerGroup->mutable_lbpeers(i);
            localPeerConfig.set_peerhostname(pLBPeer->lbpeername());
            localPeerConfig.set_realm(pLBPeer->lbpeerrealm());

            pRes = NULL;
            memset(sStatement,0,MAX_STATEMENT_SIZE);
            sql_Peer_Create_Select_Query(&localPeerConfig,sStatement);

            if((iReturn = m_dbHandle.mysql_exec_get_query(sStatement,&pRes)) != DRE_DB_SUCCESS)
            {
                if(pRes != NULL)    
                {
                    delete pRes;
                }
                DLOG_ERROR("Query Execution Failed %s",sStatement);

                if(iReturn == DRE_DB_FAIL)
                    iReturn = DEL_PEERCONFIG_ERR_DB_ERROR;


                mysql_set_error_for_PeerGroupMap_Config_Reqs(pLBPeerGroup,resp,iReturn,i);
                DLOG_NONE(" < %s ",__FUNCTION__);
                return iReturn;
            }

            mysql_Peerid_to_protobuf(pRes,pLBPeerGroup,i);

            delete pRes;

        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return iReturn;
}





void CMgrDbInterface::copy_LBAlgorithmConfig(LBPeerGroupResp *resp,::LBAlgorithm *pLBAlgorithm)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::LBAlgorithm *plocalLBAlgorithm = resp->add_lbalgos();
    plocalLBAlgorithm->CopyFrom(*pLBAlgorithm);

    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::copy_PeerGroupConfig(LBPeerGroupResp *resp,LBPeerGroup *pLBPeerGroup)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::LBPeerGroup* plocalPeerGroup = resp->add_peergroups();
    plocalPeerGroup->CopyFrom(*pLBPeerGroup);

    DLOG_NONE(" < %s ",__FUNCTION__);
    return ;
}



::LBPeerGroup* CMgrDbInterface::copy_checkPeerGroupAlreadyPresent(LBPeerGroupResp *resp,LBPeerGroup *pLBPeerGroup)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iPeerGroupCount = resp->peergroups_size();

    for(int i=0;i<iPeerGroupCount;i++)
    {
        LBPeerGroup *pLBPeerGrouplocal = resp->mutable_peergroups(i);
        if(!pLBPeerGrouplocal->has_lbpeergroupname())
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return NULL;    
        }
        else if(pLBPeerGrouplocal->lbpeergroupname() == pLBPeerGroup->lbpeergroupname())
        {
            DLOG_NONE(" < %s ",__FUNCTION__);
            return pLBPeerGrouplocal;
        }
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return NULL;

}

void CMgrDbInterface::copy_RealmConfig(DRECfgResp *resp,RealmConfig *pRealmConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    ::RealmsConfig* plocalRealmsConfig = resp->mutable_realms();
    ::RealmConfig* plocalRealmConfig = plocalRealmsConfig->add_realms();

    plocalRealmConfig->CopyFrom(*pRealmConfig);
    DLOG_NONE(" < %s ",__FUNCTION__);
    return;
}



void CMgrDbInterface::copy_RealmConfig(DRECfgResp *resp,RealmConfig *pRealmConfig,int iDestinationIndex)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount;
    int iFailed = 1;


    ::RealmsConfig* plocalRealmsConfig = resp->mutable_realms();
    iCount = plocalRealmsConfig->realms_size();


    for(int i=0;i<iCount;i++)
    {


        DLOG_DEBUG("%s:%d iCount = %d \n",__FUNCTION__,__LINE__,i);
        ::RealmConfig* plocalRealmConfig = plocalRealmsConfig->mutable_realms(i);
        iFailed = 0;

        if(plocalRealmConfig->has_realmname() == pRealmConfig->has_realmname())
        {
            if(plocalRealmConfig->has_realmname() && !(plocalRealmConfig->realmname() == pRealmConfig->realmname()))
            {
                iFailed = 1;

                DLOG_DEBUG("%s:%d RealmName != RealmName \n",__FUNCTION__,__LINE__);
                continue;
            }
        }
        else
        {
            iFailed = 1;
            DLOG_DEBUG("%s:%d  RealmName field is not Present \n",__FUNCTION__,__LINE__);
            continue;
        }

        if(plocalRealmConfig->has_localaction() == pRealmConfig->has_localaction())
        {
            if(plocalRealmConfig->has_localaction() && !(plocalRealmConfig->localaction() == pRealmConfig->localaction()))
            {
                iFailed = 1;
                DLOG_DEBUG("%s:%d  localaction != localaction \n",__FUNCTION__,__LINE__);
                continue;
            }
        }
        else
        {
            iFailed = 1;
            DLOG_DEBUG("%s:%d  localaction field is not Present \n",__FUNCTION__,__LINE__);
            continue;
        }

        if(plocalRealmConfig->has_enableproxyinfoavp() == pRealmConfig->has_enableproxyinfoavp())
        {
            if(plocalRealmConfig->has_enableproxyinfoavp() && !(plocalRealmConfig->enableproxyinfoavp() == pRealmConfig->enableproxyinfoavp()))
            {
                iFailed = 1;
                DLOG_DEBUG("%s:%d enableproxyinfoavp != enableproxyinfoavp \n",__FUNCTION__,__LINE__);
                continue;
            }
        }
        else
        {
            iFailed = 1;
            DLOG_DEBUG("%s:%d  enableproxyinfoavp field is not Present \n",__FUNCTION__,__LINE__);
            continue;
        }

        if(plocalRealmConfig->has_redirecthostusage() == pRealmConfig->has_redirecthostusage())
        {
            if(plocalRealmConfig->has_redirecthostusage() && !(plocalRealmConfig->redirecthostusage() == pRealmConfig->redirecthostusage()))
            {
                iFailed = 1;
                DLOG_DEBUG("%s:%d redirecthostusage != redirecthostusage\n",__FUNCTION__,__LINE__);
                continue;
            }
        }
        else
        {
            iFailed = 1;
            DLOG_DEBUG("%s:%d  redirecthostusage field is not Present \n",__FUNCTION__,__LINE__);
            continue;
        }

        if(plocalRealmConfig->has_redirectmaxcachetime() == pRealmConfig->has_redirectmaxcachetime())
        {
            if(plocalRealmConfig->has_redirectmaxcachetime() && !(plocalRealmConfig->redirectmaxcachetime() == pRealmConfig->redirectmaxcachetime()))
            {
                iFailed = 1;
                DLOG_DEBUG("%s:%d redirectmaxcachetime != redirectmaxcachetime\n",__FUNCTION__,__LINE__);
                continue;
            }
        }
        else
        {
            iFailed = 1;
            DLOG_DEBUG("%s:%d  redirectmaxcachetime field is not Present \n",__FUNCTION__,__LINE__);
            continue;
        }

        // if you reach here means all the above condition are successfull, ie one entry is already present
        copy_DestinationConfig(plocalRealmConfig,iDestinationIndex,pRealmConfig);
        break;
    }

    if(iFailed == 1)
    {
        DLOG_NONE("%s:%d  copy_RealmOnlyConfig",__FUNCTION__,__LINE__);
        copy_RealmOnlyConfig(plocalRealmsConfig,iDestinationIndex,pRealmConfig);
    }

    DLOG_NONE(" < %s ",__FUNCTION__);
    return;
}

void CMgrDbInterface::copy_RealmOnlyConfig(RealmsConfig *pRealmsConfig,int iDestinationIndex,RealmConfig *pFromRealmConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    RealmConfig *pToRealmConfig = pRealmsConfig->add_realms();


    if(pFromRealmConfig->has_realmname())
    {
        pToRealmConfig->set_realmname(pFromRealmConfig->realmname());       
    }

    if(pFromRealmConfig->has_localaction())
    {
        pToRealmConfig->set_localaction(pFromRealmConfig->localaction());   
    }

    if(pFromRealmConfig->has_enableproxyinfoavp())
    {
        pToRealmConfig->set_enableproxyinfoavp(pFromRealmConfig->enableproxyinfoavp()); 
    }

    if(pFromRealmConfig->has_redirecthostusage())
    {
        pToRealmConfig->set_redirecthostusage(pFromRealmConfig->redirecthostusage());   
    }

    if(pFromRealmConfig->has_redirectmaxcachetime())
    {
        pToRealmConfig->set_redirectmaxcachetime(pFromRealmConfig->redirectmaxcachetime()); 
    }

    copy_DestinationConfig(pToRealmConfig,iDestinationIndex,pFromRealmConfig);
    DLOG_NONE(" < %s ",__FUNCTION__);
}

void CMgrDbInterface::copy_DestinationConfig(RealmConfig *pToRealmConfig,int iDestinationIndex,RealmConfig *pFromRealmConfig)
{
    DLOG_NONE(" > %s ",__FUNCTION__);

    int iCount = pFromRealmConfig->destinfo_size();

    if(iCount >= iDestinationIndex)
    {

        ::Destination* plocalDestination = pFromRealmConfig->mutable_destinfo(iDestinationIndex);
        ::Destination* plDestination = pToRealmConfig->add_destinfo();

        plDestination->CopyFrom(*plocalDestination);
    }
    DLOG_NONE(" < %s ",__FUNCTION__);
    return;
}

