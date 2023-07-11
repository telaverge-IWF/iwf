/* ********************************-*-CPP-*-***********************************
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

#include "ThreadSpec.h"
#include "Logger.h"

#include "CouchbaseMgmtClient.h"

#include <sstream>
#include <string>


using namespace eAccelero;


size_t static write_callback_func(void *buffer,
        size_t size,
        size_t nmemb,
        std::string *sJsonBuffer)
{
    CLOG_DEBUG("<<<<<<<<<< Entering write_callback_func() <<<<<<<<<<");

    unsigned char *pBuffer = (unsigned char *)buffer;
    CLOG_DEBUG(" %s:%d  Buffer = %s ",__FUNCTION__,__LINE__,(char *)pBuffer);

    int iLength = strlen((char *)pBuffer);
    if(iLength)
    {
        sJsonBuffer->append((char *)pBuffer);
    }

    CLOG_DEBUG("Json Buffer = %s \n strlen = %d  size = %d nmemb = %d\n",sJsonBuffer->c_str(),iLength,(int)size,(int)nmemb);

    CLOG_DEBUG("<<<<<<<<<< Exiting write_callback_func() <<<<<<<<<<");
    return size*nmemb;
}

CouchbaseMgmtClient::CouchbaseMgmtClient(CouchbaseConfig& config)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::CouchbaseMgmtClient() <<<<<<<<<<");
    this->config = config;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CouchbaseMgmtClient() <<<<<<<<<<");
}

CouchbaseMgmtClient::CouchbaseMgmtClient()
{
}

uint32_t CouchbaseMgmtClient::HandleCurlErrorToCBApiError(CURLcode curlError)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::HandleCurlErrorToCBApiError() <<<<<<<<<<");
    if(curlError == CURLE_OK)
    {
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::HandleCurlErrorToCBApiError() <<<<<<<<<<");
        return CB_OK;
    }
    else if(curlError == CURLE_COULDNT_CONNECT)
    {
        CLOG_ERROR("CB_FAILED_TO_CONNECT_TO_SERVER");
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::HandleCurlErrorToCBApiError() <<<<<<<<<<");
        return CB_FAILED_TO_CONNECT_TO_SERVER;
    }
    else if(curlError == CURLE_LOGIN_DENIED)
    {
        CLOG_ERROR("CB_LOGIN_DENIED");
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::HandleCurlErrorToCBApiError() <<<<<<<<<<");
        return CB_LOGIN_DENIED;
    }
    else if(curlError == CURLE_HTTP_RETURNED_ERROR)
    {
        CLOG_ERROR("CB_HTTP_ER_GT_400");
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::HandleCurlErrorToCBApiError() <<<<<<<<<<");
        return CB_HTTP_ER_GT_400;
    }
    else
    {
        CLOG_ERROR("CB_GENERIC_ERROR");
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::HandleCurlErrorToCBApiError() <<<<<<<<<<");
        return CB_GENERIC_ERROR;
    }
}

uint32_t CouchbaseMgmtClient::Initialize()
{

    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::Initialize() <<<<<<<<<<");
    curlHandle = curl_easy_init();
    if(curlHandle == NULL)
    {
        //Failed initialization. TODO Find out wht has to be done.
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::Initialize() <<<<<<<<<<");
        return CB_CURL_FAILED_TO_INITIALIZED;
    }
    //Set common options
    //Setting the base URL
    baseURL.append("http://");
    baseURL.append(config.hostName);
    baseURL.append(":");
    std::stringstream ss;
    ss << config.port;
    baseURL.append(ss.str());
    baseURL.append("/");

    CLOG_DEBUG("base URL is %s",baseURL.c_str());
    //Setting Auth Credentials
    credentials.append(config.adminUserName);
    credentials.append(":");
    credentials.append(config.adminPassword);
    CLOG_DEBUG("credentials are %s\n",credentials.c_str());

    SetCredentials(curlHandle);

    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::Initialize() <<<<<<<<<<");
    return CB_OK;
}

void CouchbaseMgmtClient::resetCurlHandle(CURL *curlHandle)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::resetCurlHandle() <<<<<<<<<<");
    curl_easy_reset(curlHandle);
    SetCredentials(curlHandle);
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::resetCurlHandle() <<<<<<<<<<");
}

void CouchbaseMgmtClient::SetCredentials(CURL *curlHandle)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::SetCredentials() <<<<<<<<<<");
    CURLcode curlError;
    curlError = curl_easy_setopt(curlHandle, CURLOPT_USERPWD , credentials.c_str());

    if (curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::SetCredentials() <<<<<<<<<<");
        return;
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_FAILONERROR, 1);

    if (curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::SetCredentials() <<<<<<<<<<");
        return;
    }
}

uint32_t CouchbaseMgmtClient::ParseCurlJson(Json::Value *jsonRoot,std::string jsonBuffer)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::ParseCurlJson() <<<<<<<<<<");
    Json::Reader jsonConfigFileReader;

    jsonConfigFileReader.parse(jsonBuffer,*jsonRoot);

    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::ParseCurlJson() <<<<<<<<<<");
    return CB_OK;
}

CouchbaseMgmtClient::~CouchbaseMgmtClient()
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::~CouchbaseMgmtClient() <<<<<<<<<<");
    curl_easy_cleanup(curlHandle);

    curl_global_cleanup();
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::~CouchbaseMgmtClient() <<<<<<<<<<");
}

CouchbaseClusterMgmtClient::CouchbaseClusterMgmtClient(CouchbaseConfig& config):
    CouchbaseMgmtClient(config)
{
}

CouchbaseClusterMgmtClient::~CouchbaseClusterMgmtClient()
{
}

uint32_t CouchbaseClusterMgmtClient::CheckRebalanceStatus(double &node1RebalanceProgress,double &node2RebalanceProgress)
{
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    CURLcode curlError;

    URL.append(baseURL);
    URL.append("pools/default/rebalanceProgress");
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_callback_func);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &sJsonBuffer);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,CB_OP_TIMEOUT);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    if(sJsonBuffer.length())
    {
        ParseCurlJson(&jsonRoot,sJsonBuffer);
        std::string sStatus = jsonRoot["status"].asString();
        CLOG_DEBUG("sStatus = %s",sStatus.c_str());

        if(sStatus == "none")
        {
            if(!jsonRoot["errorMessage"].isNull())
            {
                std::string sErrorMsg = jsonRoot["errorMessage"].asString();
                if(sErrorMsg == "Rebalance failed. See logs for detailed reason. You can try rebalance again.")
                {
                    CLOG_DEBUG("Oops Rebalance Failed...");
                    resetCurlHandle(curlHandle);
                    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
                    return CB_CURL_REBALANCE_FAILED;
                }
            }
            else
            {
                CLOG_DEBUG("Rebalance Success...");
            }
            resetCurlHandle(curlHandle);
            CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
            return CB_OK;
        }
        else
        {
            Json::Value::Members memberNames=jsonRoot.getMemberNames();
            for(uint32_t j=0;j<memberNames.size();j++)
            {
                std::string memberName=memberNames[j];
                Json::Value value=jsonRoot[memberName];
                CLOG_DEBUG("Key: %s",memberName.c_str());
                std::string s2="ns";
                if (memberName.find(s2) != std::string::npos)
                {
                    Json::Value::Members memName=jsonRoot[memberName].getMemberNames();
                    std::string key=memName[0];
                    if(j == 0)
                    {
                        node1RebalanceProgress=jsonRoot[memberName][key].asFloat();
                        CLOG_DEBUG("node1RebalanceProgress = %f",node1RebalanceProgress);
                    }
                    else
                        if(j == 1)
                        {

                            node2RebalanceProgress=jsonRoot[memberName][key].asFloat();
                            CLOG_DEBUG("node2RebalanceProgress = %f",node2RebalanceProgress);
                        }

                }
                CLOG_DEBUG("Value: %s",value.toStyledString().c_str());
            }
            CLOG_DEBUG("Rebalance In Progress...");
            resetCurlHandle(curlHandle);
            CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
            return CB_REBALANCE_INPROGRESS;
        }
    }

    resetCurlHandle(curlHandle);


    CLOG_DEBUG(" < %s:%d",__FUNCTION__,__LINE__);
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CheckRebalanceStatus() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseClusterMgmtClient::RebalanceCluster(std::vector<CouchbaseNode>& nodes)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::RebalanceCluster() <<<<<<<<<<");

    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    char url[URL_SIZE];

    std::string sParameter;
    CURLcode curlError;
    uint32_t iReturn;

    double reb1,reb2;
    memset(url,0,URL_SIZE);
    iReturn=CheckRebalanceStatus(reb1,reb2);
    if((iReturn != CB_OK) && (iReturn != CB_CURL_REBALANCE_FAILED))
    {
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::RebalanceCluster() <<<<<<<<<<");
        return iReturn;
    }

    snprintf(url,URL_SIZE,"controller/rebalance");
    sParameter = "ejectedNodes=&knownNodes=";

    for (std::vector<CouchbaseNode>::iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        CouchbaseNode localCouchbaseNode;
        localCouchbaseNode = *it;
        sParameter = sParameter + localCouchbaseNode.getOtpNode() + ",";
    }

    sParameter = sParameter.substr(0,sParameter.length()-1);
    URL.append(baseURL);
    URL.append(url);

    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::RebalanceCluster() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::RebalanceCluster() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }


    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,CB_OP_TIMEOUT);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::RebalanceCluster() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    resetCurlHandle(curlHandle);

    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::RebalanceCluster() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseClusterMgmtClient::AddNodeToCluster(CouchbaseNode node)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::AddNodeToCluster() <<<<<<<<<<");
    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    char url[URL_SIZE];
    std::string sParameter;
    CURLcode curlError;

    memset(url,0,URL_SIZE);

    snprintf(url,URL_SIZE,"controller/addNode ");
    sParameter = "hostname=" + node.hostName +"&user=" + node.getUserName() + "&password=" + node.getPassword();
    URL.append(baseURL);
    URL.append(url);
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::AddNodeToCluster() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::AddNodeToCluster() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,100);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::AddNodeToCluster() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    resetCurlHandle(curlHandle);

    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::AddNodeToCluster() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseClusterMgmtClient::FailOverNode(CouchbaseNode node)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::FailOverNode() <<<<<<<<<<");
    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    char url[URL_SIZE];
    std::string sParameter;
    CURLcode curlError;

    memset(url,0,URL_SIZE);

    snprintf(url,URL_SIZE,"controller/failOver");
    sParameter = "otpNode=" + node.getOtpNode();
    URL.append(baseURL);
    URL.append(url);
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FailOverNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FailOverNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,60);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FailOverNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    resetCurlHandle(curlHandle);


    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FailOverNode() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseClusterMgmtClient::PingNode()
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    CURLcode curlError;

    URL.append(baseURL);
    URL.append("pools");
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());


    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_callback_func);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &sJsonBuffer);


    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,CB_OP_TIMEOUT);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    resetCurlHandle(curlHandle);
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseClusterMgmtClient::PurgeUnwantedData(std::string bucket)
{

    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    CURLcode curlError;

    URL.append(baseURL);
    URL.append("pools/default/buckets/");
    URL.append(bucket);
    URL.append("/controller/unsafePurgeBucket");
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());


    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_callback_func);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &sJsonBuffer);


    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_POST, 1);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,CB_OP_TIMEOUT);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    resetCurlHandle(curlHandle);
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PurgeUnwantedData() <<<<<<<<<<");
    return CB_OK;


}

uint32_t CouchbaseClusterMgmtClient::StopRebalance()
{
    double reb1,reb2;
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
    if( CheckRebalanceStatus(reb1,reb2) != CB_REBALANCE_INPROGRESS)
    {
        CLOG_DEBUG("Rebalance not in progress");
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
        return CB_OK;
    }

    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    char url[URL_SIZE];
    std::string sParameter;
    CURLcode curlError;

    memset(url,0,URL_SIZE);

    snprintf(url,URL_SIZE,"controller/stopRebalance");
    URL.append(baseURL);
    URL.append(url);
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_POST,1);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,CB_OP_TIMEOUT);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }


    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    resetCurlHandle(curlHandle);


    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::StopRebalance() <<<<<<<<<<");
    return CB_OK;
}


uint32_t CouchbaseClusterMgmtClient::FetchClusterStatus(std::vector<CouchbaseNode>& nodes)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::FetchClusterStatus() <<<<<<<<<<");
    std::string URL;
    std::string sJsonBuffer;
    CURLcode curlError;

    URL.append(baseURL);
    URL.append("pools/default");
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FetchClusterStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_callback_func);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FetchClusterStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &sJsonBuffer);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FetchClusterStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_setopt(curlHandle,CURLOPT_TIMEOUT,CB_OP_TIMEOUT);
    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::PingNode() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FetchClusterStatus() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    parseFetchClusterStatusResponse(sJsonBuffer,nodes);
    resetCurlHandle(curlHandle);


    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FetchClusterStatus() <<<<<<<<<<");
    return CB_OK;
}

void CouchbaseClusterMgmtClient::parseFetchClusterStatusResponse(std::string sJsonBuffer,std::vector<CouchbaseNode>& nodes)
{

    Json::Value jsonRoot;
    if(sJsonBuffer.length())
    {
        ParseCurlJson(&jsonRoot,sJsonBuffer);
        const Json::Value nodeDetails = jsonRoot["nodes"];
        CLOG_DEBUG("Node Size = %d\n",nodeDetails.size());

        for(uint32_t i=0;i<nodeDetails.size();i++)
        {
            CouchbaseNode localNode;
            localNode.setOtpNode(nodeDetails[i]["otpNode"].asString());
            if(nodeDetails[i]["status"].asString() == DHEALTHY)
            {
                localNode.nodeStatus = HEALTHY;
            }
            else if(nodeDetails[i]["status"].asString() == DWARMUP)
            {
                localNode.nodeStatus = WARMUP;
            }
            else
            {
                localNode.nodeStatus = UNHEALTHY;
            }

            std::string hostname = nodeDetails[i]["hostname"].asString();
            uint32_t pos = hostname.find(":");
            uint32_t length = hostname.length();
            hostname.erase(pos,length-pos);
            localNode.hostName = hostname;

            nodes.push_back(localNode);
            CLOG_DEBUG("otpNode = %s\n",localNode.getOtpNode().c_str());
            CLOG_DEBUG("Status = %d\n",localNode.nodeStatus);
        }
    }

}

uint32_t CouchbaseBucketMgmtClient::CreateCouchbaseBucket(std::string BucketName,std::string Password, uint32_t initialSizeInMB, uint32_t noReplicas)
{
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
    std::string URL;
    Json::Value jsonRoot;
    std::string sJsonBuffer;
    char url[URL_SIZE];
    std::string sParameter;
    CURLcode curlError;

    memset(url,0,URL_SIZE);

    snprintf(url,URL_SIZE,"/pools/default/buckets");
    URL.append(baseURL);
    URL.append(url);
    CLOG_DEBUG("URL Created = %s \n",URL.c_str());
    curlError = curl_easy_setopt(curlHandle, CURLOPT_URL,URL.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    sParameter = "name=" + BucketName;
    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    sParameter = "authType=" + Password;
    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    sParameter = "ramQuotaMB=" + initialSizeInMB;
    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    sParameter = "replicaNumber=" + noReplicas;
    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }

    sParameter = "proxyPort=" + COUCHBASE_PROCY_PORT;
    curlError = curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, sParameter.c_str());

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }
    else
    {
        CLOG_DEBUG("CURLOPT_POSTFIELDS = %s\n",sParameter.c_str());
    }


    curlError = curl_easy_perform(curlHandle);

    if(curlError != CURLE_OK)
    {
        CLOG_DEBUG("Curl Error : %s (%d)\n",curl_easy_strerror(curlError),curlError);
        resetCurlHandle(curlHandle);
        CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
        return HandleCurlErrorToCBApiError(curlError);
    }

    resetCurlHandle(curlHandle);

    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::CreateCouchbaseBucket() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseBucketMgmtClient::SetBucketQuota(std::string BucketName,std::string Password,uint32_t sizeInMB)
{
    /*** TODO ***/
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::SetBucketQuota() <<<<<<<<<<");
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::SetBucketQuota() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseBucketMgmtClient::SetTTLForBucket(uint32_t timeInSecs)
{
    /*** TODO ***/
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::SetTTLForBucket() <<<<<<<<<<");
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::SetTTLForBucket() <<<<<<<<<<");
    return CB_OK;
}

uint32_t CouchbaseBucketMgmtClient::FlushBucket(std::string BucketName)
{
    /*** TODO ***/
    CLOG_DEBUG("<<<<<<<<<< Entering CouchbaseMgmtClient::FlushBucket() <<<<<<<<<<");
    CLOG_DEBUG("<<<<<<<<<< Exiting CouchbaseMgmtClient::FlushBucket() <<<<<<<<<<");
    return CB_OK;
}
