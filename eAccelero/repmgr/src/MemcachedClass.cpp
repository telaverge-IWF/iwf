
/* ********************************-*-CPP-*************************************
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


#include "MeSS.h"
#include "MemcachedClass.h"

using namespace eAccelero;

//Constructor
MemcachedClient::MemcachedClient(std::string serverName)
{
     // Initialize Attributes;    
     MemcServers = serverName;   
     mServers    = NULL;
     mServer     = NULL;
     m_CacheTimeout = 0;   //Default
     //MemcPID     = -1;
}  

// Destructor
MemcachedClient::~MemcachedClient() {
   // Add/Modify code to handle error conditions
   // Free the resources
     memcached_server_free(mServers);
     memcached_free(mServer);
     //remove(TmpRepFileName.c_str());   // remove the temp File.
  }


bool MemcachedClient::MemcachedExists(FromSource frmSrc)
{
    // This Method checks for the existence of MEMCACHED Server and procedure
    // depends on from where the request has come.
    
    bool DoMemCExists = false;
    switch (frmSrc)
    {
        case FROMINIT:              // Initialize Method Called this method
            glob_t  bRepTmpFileBuf;
            glob(TmpFilePattern.c_str(), 0, NULL, &bRepTmpFileBuf);
            //CLOG_DEBUG("%d file found", bRepTmpFileBuf.gl_pathc);
            //std::cout << bRepTmpFileBuf.gl_pathc << " Files Found" << std::endl;
            if (bRepTmpFileBuf.gl_pathc == 0)
            {
                CLOG_DEBUG("No Files Globbed");
                DoMemCExists = false;   
                break;
            }
            else            // if (bRepTmpFileBuf.gl_pathc == 1) - TODO
            {
                std::string bRepTmpFile;
                std::string sRepMemcPid;
                CLOG_DEBUG("File Found %s", bRepTmpFileBuf.gl_pathv[0]);
                //std::cout << bRepTmpFileBuf.gl_pathv[0] << " File" << std::endl;
                bRepTmpFile.assign(bRepTmpFileBuf.gl_pathv[0]);
                size_t HypenPos = bRepTmpFile.find('-');
                sRepMemcPid = bRepTmpFile.substr(HypenPos+1);
                MemcPID = atoi(sRepMemcPid.c_str());
                TmpRepFileName = bRepTmpFile;
                DoMemCExists = true;
                CLOG_DEBUG("Memcached (%d) Exists", MemcPID);
            }
            // Fall Through - Notice No break;
            
        case FROMTIMER:              // Time Called this method
            struct stat memc_stats;
            char PidBuf[50];
            memset(PidBuf, 0, 50);
            if (MemcPID != -1 && MemcPID > 0) 
            {
                sprintf(PidBuf, "/proc/%d", MemcPID);
                CLOG_DEBUG("Checking if Memcached %s Exists", PidBuf);
                if ( stat(PidBuf, &memc_stats) == -1  && errno == ENOENT )
                {
                    CLOG_DEBUG("Memcached Does Not Exist");
                    //if (frmSrc == FROMINIT)
                        remove(TmpRepFileName.c_str());
                    DoMemCExists = false;   // memcached server do not exists
                }   
                else 
                {
                    CLOG_DEBUG("Memcached Exists");
                    DoMemCExists = true; //memcached server exists.
                }
            }                      
            break;    
                   
        default:
            CLOG_DEBUG("Default Option");
            std::cout << " Default Option" << std::endl;
            break;
    }
    
    CLOG_DEBUG("DoMemCExists : %d", (int) DoMemCExists);
    std::cout << " DoMemCExists " << DoMemCExists << std::endl;
    return DoMemCExists;    
}

bool MemcachedClient::AddServer(std::string servername)
{
    // Add Code here to add one more server to the existing
    // list of servers. 
    // AS OF NOW, NOT REQUIRED -- WE CAN IMPLEMENT IF REQUIRED
    //
    bool bServerAdded = false;
    //memcached_return_t memcreturn;
    memcached_return memcreturn;
    mServers=memcached_server_list_append(mServers,servername.c_str(),11211,&memcreturn);
    //mServers=memcached_server_list_append(NULL,servername.c_str(),11211,&memcreturn);
    if ( memcreturn == MEMCACHED_SUCCESS )
    {
        memcreturn=memcached_server_push(mServer,mServers);
        if( memcreturn==MEMCACHED_SUCCESS )
        {
            bServerAdded = true; 
        }
    }
    return bServerAdded;    
}

bool MemcachedClient::InitializeCache(void)
{
    // Check if Memcached Server already running
    // if not start it.
    
    bool CacheInited = false;
    mServer = memcached_create(NULL); 
    CacheInited = AddServer(MemcServers);
    if (CacheInited == true)
    {
        CLOG_DEBUG("Memcached Server %s Added", MemcServers.c_str());
    }   
    else
    {
        CLOG_DEBUG("Failed to add server %s", MemcServers.c_str());
    }    
    return CacheInited;
}

bool MemcachedClient::StartMemcachedServer(void)
{
    
    signal(SIGCHLD, SIG_IGN);
    MemcPID = fork();
    if (MemcPID == -1) 
    { 
        CLOG_DEBUG("Failed to Create Process");
        return false; 
    }
    if ( MemcPID == 0) 
    {
        // deamonize memcached process
        /* Change the file mode mask */
        umask(0);
        /* Create a new SID for the child process */
        if ( setsid() < 0 ) 
        {
            CLOG_DEBUG("Failed to Deamonize MEMCACHED Server");
        }    
        if (execlp("memcached", "memcached", 0) == -1)    
        {
            CLOG_CRITICAL("error starting memcached server : %d:", errno);
            perror("error starting memcached server");
            exit(1);
        }      
    }
    else
    {
        std::string sMemcTmpFile = TmpFilePrefix;
        std::stringstream sMemcPID;
        sMemcPID << MemcPID;
        sMemcTmpFile.append(sMemcPID.str());
        CLOG_DEBUG("Creating TmpFile : %s", sMemcTmpFile.c_str());
        std::ofstream MemCFile;
        MemCFile.open(sMemcTmpFile);
        MemCFile.close();
        TmpRepFileName = sMemcTmpFile;
        // Memcserver started .. setup the rest.
    }
    return true;
}

 int MemcachedClient::OnTimerEvt(TimerEvent& event)
 {
     CLOG_DEBUG("TIMER: ");
     return 1;
 }
 
//This method is to provided total number of keys stored in the DB Store. 
int MemcachedClient::GetTotalRecordsNum(void)
{
    // Add code here to get the number of keys present in the cache
    // and return
    // Not Implemented yet
    return 0;
}

  // Method to store the key:value pair into Store.
void MemcachedClient::StoreEntry(KeyValue kvl) 
{
    // Add Code here to store the key:value pair specified in KeyValue object
    // into the memcache
    // ex: Probable use: memcached_set(memc, key, strlen(key), value, value_length, (time_t)0, (uint32_t)0);
    //
    //memcached_return_t memcreturn;
    memcached_return memcreturn;
    memcreturn=memcached_set(mServer,kvl.Get_HashKey().c_str(), kvl.Get_HashKeyLength(),
              kvl.Get_HashValue().c_str(), kvl.Get_HashValueLength(), 
              (time_t) m_CacheTimeout,(uint32_t)0);
    if( memcreturn == MEMCACHED_SUCCESS)
    {
        CLOG_DEBUG("MEMCACHE: Key stored successfully");
    }
    else
    {
        CLOG_DEBUG("MEMCACHE: Failed to store Key:Value");
    }          
}

// Method to retrieve the  key:value pair from the store
KeyValue MemcachedClient::GetEntry(std::string key) 
{
    // Add Code here to retrieve the value of the key passed
    // from the memcached server.
    // Return the value in KeyValue Object
    // ex: Probable use: return_value = memcached_fetch(memc, return_key, &return_key_length,
    //                                   &return_value_length, &flags, &rc)
    //     KeyValue.key = return_key
    //     KeyValue.Value = return_value
    //     return KeyValue
    //
    KeyValue kvl; 
    kvl.Set_HashKey(key);
    char *return_value;
    size_t Keyl;
    uint32_t tval;
    //memcached_return_t rc;
    memcached_return rc;
    return_value = memcached_get(mServer,key.c_str(),key.length(),
                              &Keyl, (uint32_t *) &tval, &rc);
    if (rc == MEMCACHED_SUCCESS)      
    {          
        string HashVal(return_value);
        kvl.Add_HashValue(HashVal);
        CLOG_DEBUG("Key:Value Retrieval Success");          
    }
    else
    {
        CLOG_DEBUG("Failed to retrive Key:Value");
    }  
    return kvl;
}

bool MemcachedClient::DeleteEntry(std::string Key)
{
    //memcached_return_t memcreturn;
    memcached_return memcreturn;
    memcreturn = memcached_delete(mServer,Key.c_str(),Key.length(),(time_t)0);
    if ( memcreturn == MEMCACHED_SUCCESS )
    {
        CLOG_DEBUG("Key:Value pair Deleted Successfully");
    }
    else
    {
        CLOG_DEBUG("Failed to Delete Key:Value pair %d", memcreturn);
       // std::cout << memcached_strerror(mServer, memcreturn) << std::endl;
    } 
    
    return true;
}


// End of the Module : MemcachedClass.cpp



