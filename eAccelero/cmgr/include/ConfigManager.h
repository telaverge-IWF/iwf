/*********************************-*-H-*-************************************
 *                                                                          *
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
 ****************************************************************************/

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "Component.h"
#include "Logger.h"
#include "MonitorMysql.h"
#include "CMAPICMgr.h"
#include "CMAPIIwfCMgr.h"

class CMAPIIwfCMgr;
class CMAPICMgr;
class MonitorMysql;

class ConfigManager : public eAccelero::HAMeSSComponent
{
    public:
        ConfigManager(uint16_t instanceId, uint16_t installationMode, std::map<std::string, std::string> &objConfigReaderMap,ConfigManagerAlarms **pconfigManagerAlarms);  // default ctor
        ~ConfigManager()
        {
            Logger::currLogger = NULL;
            if(!m_configManagerAlarms)
                delete m_configManagerAlarms;
#if 0
            if(!m_cmapiInterface)
                delete m_cmapiInterface;

            if(!m_cmapiIwfInterface)
                delete m_cmapiIwfInterface;
#endif
            if(!mysqlPingThread)
                delete mysqlPingThread;

            if(!m_monitorMysql)
                delete m_monitorMysql;

        } // default dtor
        void Initialize();      // Initialization Method  -- More Comments -- TODO
        void Terminate();       // Termination Method   -- More Comments -- TODO
        void RegisterMethods(); // Register Methods for calling REPMGR services.
		/*LOGGING*/
		void InitLog();
		Logger& GetLogger();

		Logger m_logger;
		SyslogChannel m_syslogChannel;
		//FileLogChannel m_fileLogChannel; /*TBD::Use This for File Logging*/

		void SetLogChannel(const unsigned int channel);
		void SetLogLevel(const unsigned int level);
		void InitializeLogConfig();
        //Over-riding functions from HAMeSSComponent
        int ProcessAvailabilityStatusResetPreFunc(uint16_t newInstanceId);

        int ProcessAvailabilityStatusResetPostFunc(bool switchOver);

        int ProcessComponentStatusUpdate(uint16_t componentId,HAComponentStatus newStatus);
        int AvailabilityActiveUpdateBroadcastCbk();

        void SetMysqlMonitorObject(MonitorMysql *pMonitorMysql);

        void UpdateSelfStatus();
    private:
        ConfigManagerAlarms *m_configManagerAlarms;
        CMAPICMgr *m_cmapiInterface;
        CMAPIIwfCMgr *m_cmapiIwfInterface;
        eAccelero::Thread* mysqlPingThread;
        MonitorMysql *m_monitorMysql;
        uint16_t m_InstallationMode;
        //mysql_cli_interface* m_dbHandler; // this should be moved out
        std::map<std::string, std::string> m_objConfigReaderMap;
        //int ShowUser(GetConfigReq*, AllResponses*);
        //int AddUser(SetConfigReq*, AllResponses*);
        //int DeleteUser(SetConfigReq*, AllResponses*);
        //int VerifyPassword(GetConfigReq*, AllResponses*);
        bool monitorConnection;
};

#endif /* CONFIGMANAGER_H */
