/*********************************-*-CPP-*-************************************
 *
 *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 *            Manufactured in the United States of America.                 *
 *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of Diametriq and its licensors, if any.                  *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 *****************************************************************************/


/******************************************************************************
 *
 *      PROJECT     : DRE
 *      FILE        : CMgrMain.c
 *      MODULE      : Configuration Manager
 *      ENGINEER    :
 *      DESCRIPTION :
 *      HISTORY         : <Initial Implementation>
 *
 ******************************************************************************/


#include <string>
#include <map>
#include <sys/file.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdarg.h>




#include "HAMeSSComponent.h"
#include "MysqlInterface.h"
#include "ConfigReader.h"
#include "CMAPICMgr.h"
#include "CMAPIIwfCMgr.h"
#include "ConfigManager.h"
#include "ErrorResp.h"

using namespace eAccelero;

const char DREVer[]=DRE_VER;

std::map<int,std::string> errorMap;
std::map<int,std::string> iwfErrorMap;
extern void generate_error_map();    
extern void generate_iwf_error_map();    

void exit_function(void)
{
   abort();
}


/*******************************************************************************
 * Function name     : main
 * return            : int
 * arguments         : the command line parameters
 * Description       : This is the entry function for the cmgr component
 * Notes             :
 *******************************************************************************/

int main(int argc,char *argv[])
{
#if 0
    int i = atexit(exit_function);
    if (i != 0) {
        fprintf(stderr, "cannot set exit function\n");
        exit(EXIT_FAILURE);
    }
#endif


    if ((argc == 1) ||(argc >= 2 && argv[1] && !strcmp(argv[1], "--version")))
    {
        printf("Diametriq DRE %s\n",DREVer);
        exit(0);
    }

    int pid_file = open("/tmp/cmgr.pid", O_CREAT | O_RDWR, 0666);
    int rc = flock(pid_file, LOCK_EX | LOCK_NB);

    if(rc)
    {
        if(EWOULDBLOCK == errno)
        {
            std::cout << "I am already Running" << std::endl;
            exit(0);
        }
    }

    int instanceId = 0;
    int installationMode = 1;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-i") && argv[i+1])
        {
            instanceId = atoi(argv[i+1]);
        }
        else if (!strcmp(argv[i], "-m") && argv[i+1])
        {
            installationMode = atoi(argv[i+1]);
        }
    }

    /*start MESS server */
    try
    {
        char *dreMysqlServerConfDir = (char *) ::getenv("DRE_MYSQL_SERVER_CONFDIR");
        std::map<std::string, std::string> objConfigReaderMap;
        string confFile;


        if (dreMysqlServerConfDir != NULL)
            confFile = dreMysqlServerConfDir;
        else {
            printf("DRE_MYSQL_SERVER_CONFDIR environment variable not set, exiting...\n");
            ::exit(-1);
        }

        confFile += "/";
        confFile += "mysql.cfg";

        bool isConfigFileOpenSuccessful = false;
        ConfigReader configReader(confFile.c_str(), isConfigFileOpenSuccessful);

        if (isConfigFileOpenSuccessful) {
            objConfigReaderMap = configReader.getConfigMap();
        } else {
            printf("mysql.cfg open failed\n");
            exit(1);
        }

        ConfigManagerAlarms *configManagerAlarms;
        ConfigManager *pCMgr = new ConfigManager(instanceId,installationMode,objConfigReaderMap,&configManagerAlarms);
        MonitorMysql *monitorMysql = new MonitorMysql(configManagerAlarms,installationMode,objConfigReaderMap,pCMgr);
        pCMgr->SetMysqlMonitorObject(monitorMysql);
        pCMgr->Init(argc, argv);
        eAccelero::Thread*  mysqlPingThread = new eAccelero::Thread("Mysql Ping Thread");
        mysqlPingThread->Start((eAccelero::Runnable*)monitorMysql);

        generate_error_map();
        generate_iwf_error_map();

        DLOG_INFO("Starting Configuration Manager");
#if 0
        // For testing purpose
        cMgr.m_cmapiIwfInterface->TestIwfCMgr();
#endif

        pCMgr->Run();
    }
    catch(CmdParseException &e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    }
    catch(Exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    CLOG_INFO("Configuration Manager Exiting!!");

    return 0;
}
