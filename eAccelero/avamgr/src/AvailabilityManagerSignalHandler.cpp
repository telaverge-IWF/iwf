/*********************************-*-C++-*-************************************
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

#include <stdint.h>
#include <stdlib.h>

#include <string>

#include "AlarmId.h"
#include "HAComponent.h"
#include "AvaMgr.h"
#include "AvaMgr.pb.h"
#include "ErrorResp.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "AvailabilityManager.h"
#include <its_dre_exit_error_codes.h>

int AvailabilityManager::OnSigChld(SignalEvent &event) {

    struct SignalEventInfo sigInfo;
    sigInfo.errorno  =  event.SigInfo()->si_errno;
    sigInfo.code  =  event.SigInfo()->si_code;
    sigInfo.pid   =  event.SigInfo()->si_pid;
    sigInfo.uid   =  event.SigInfo()->si_uid;
    sigInfo.status =  event.SigInfo()->si_status;
    sigInfo.utime  =  event.SigInfo()->si_utime;
    sigInfo.stime  =  event.SigInfo()->si_stime;

    if(m_signalList.InsertData(sigInfo) == -1) {
        return 0;
    }

    return 0;
}


void AvailabilityManager::PrintExitMsgToFile(const char* errorString,bool isItLicenseError)
{
    char* dreStatusFile = getenv("DRE_STATUS_FILE");
    if(dreStatusFile != NULL)
    {
        std::fstream fileStream;
        fileStream.open(dreStatusFile,std::fstream::out);
        fileStream<<"-----------------------------------------------------------"<<std::endl;
        fileStream<<"NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE"<<std::endl;
        fileStream<<"-----------------------------------------------------------"<<std::endl;
        fileStream<<errorString<<std::endl;
        if(isItLicenseError)
        {
            fileStream<<"Please contact Diametriq for additional licensing privileges."<<std::endl;
        }
        fileStream<<"-----------------------------------------------------------"<<std::endl;
        fileStream<<"NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE"<<std::endl;
        fileStream<<"-----------------------------------------------------------"<<std::endl;
        fileStream.close();

    }
}


void AvailabilityManager::VerifyExitStatus(uint32_t status,std::string processName)
{
    CLOG_CRITICAL("Exits status received %u",status);
    switch(status)
    {
        case ITS_LICENSE_INVALID_HOST_ID:
            {
                CLOG_CRITICAL("License violation: invalid host id.");
                const char *alarmString ="Invalid host id.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: invalid host id.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_FILE_OPENING_ERROR:
            {
                CLOG_CRITICAL("License violation: Error in opening license file.");
                const char *alarmString ="Error in opening license file.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: Error in opening license file.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_MALFORMED_LICENSE_DATA:
            {
                CLOG_CRITICAL("License violation: Malformed license data.");
                const char *alarmString ="Malformed license data.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: Malformed license data.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_INVALID_DATA:
            {
                CLOG_CRITICAL("License violation:Invalid or altered license data.");
                const char *alarmString ="Invalid or altered license data.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation:Invalid or altered license data.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_WRITING_ERROR:
            {
                CLOG_CRITICAL("License violation: Writing error.");
                const char *alarmString ="Writing error.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: Writing error.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_CORRUPTED_MUTEX:
            {
                CLOG_CRITICAL("License violation: Corrupted Mutex.");
                const char *alarmString ="Corrupted Mutex.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: Corrupted Mutex.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_VERSION_MISMATCH:
            {
                CLOG_CRITICAL("License violation: License file version mismatch.");
                const char *alarmString ="License file version mismatch.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: License file version mismatch.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_EXPIRED:
            {
                CLOG_CRITICAL("License violation: License expired.");
                const char *alarmString ="License expired.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: License expired.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_CLOCK_REVERSED:
            {
                CLOG_CRITICAL("License violation: Clock reversed.");
                const char *alarmString ="Clock reversed.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: Clock reversed.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_DURATION_EXCEEDED:
            {
                CLOG_CRITICAL("License violation:License duration exceeded.");
                const char *alarmString ="License duration exceeded.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation:License duration exceeded.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_LICENSE_CAPABILITY_VIOLATION:
            {
                CLOG_CRITICAL("License violation: Capability violated.");
                const char *alarmString ="Capability violated.";
                m_avaMgrAlarm->RaiseLicenseViolationAlarm(alarmString);
                PrintExitMsgToFile("License violation: Capability violated.",true);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_DRE_CONFIG_FETCH_ERROR:
            {
                CLOG_CRITICAL("DRE failed to fetch config from database.");
                const char *errorString ="DRE failed to fetch config from database.";
                PrintExitMsgToFile(errorString);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_DRE_CONFIG_FILE_ERROR:
            {
                CLOG_CRITICAL("DRE failed to read/parse config file.");
                const char *errorString ="DRE failed to read/parse config file.";
                PrintExitMsgToFile(errorString);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_DRE_REPLICATION_INIT_FAILURE:
            {
                CLOG_CRITICAL("DRE failed to initialize replication.");
                const char *errorString ="DRE failed to initialize replication.";
                PrintExitMsgToFile(errorString);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;
        case ITS_PROCESS_UNSTABLE_ERROR:
            {
                CLOG_CRITICAL("Process %s  was exiting continously.",processName.c_str());
                char errorString[ARGUMENT_LEN];
                snprintf(errorString,ARGUMENT_LEN,"Component %s not stable, was exiting continously.",processName.c_str());
                PrintExitMsgToFile(errorString);
                sleep(1);
                kill(0, SIGTERM);
            }
            break;

        default:
            CLOG_DEBUG("No Action for exit status %d",status);
            break;
    }
}


uint16_t AvailabilityManager::HandleQueuedSignalInfo(struct SignalEventInfo& sigInfo)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::HandleQueuedSignalInfo() >>>>>>>>>>");
    uint16_t ret = 0;
    std::string processName;

    std::unordered_map<uint16_t, ProcessAttributes>::iterator iter;
    for (iter = m_objProcessMap.begin(); iter != m_objProcessMap.end(); iter++) {
        if ((*iter).second.pid == sigInfo.pid) {

            // Check if the signal is due to a SIGTERM that we sent, in which case
            // we will have to stop the timer that is started.
            if ((*iter).second.sigtermTimerHandle != (unsigned)-1)
            {
                StopSigtermTimer((*iter).first);
                (*iter).second.sigtermTimerHandle = -1;
            }
            if ((*iter).second.sigkillTimerHandle != (unsigned)-1)
            {
                CLOG_DEBUG("SIGKILL timer stopped for component [%d].",(*iter).first);
                this->GetDispatcher()->RemoveEventHandler(TIMER_EVENT_TYPE,
                        (*iter).second.sigkillTimerHandle);
                (*iter).second.sigkillTimerHandle = -1;
            }

            CLOG_CRITICAL("SIGCHLD received");
            CLOG_CRITICAL("SigInfo \n"
                    "   si_errno:   %d\n"
                    "   si_code:    %d\n"
                    "   si_pid:     %d\n"
                    "   si_uid:     %d\n"
                    "   si_status:  0x%x\n"
                    "   si_utime:   0x%x\n"
                    "   si_stime:   0x%x\n",
                    sigInfo.errorno, sigInfo.code,
                    sigInfo.pid, sigInfo.uid,
                    sigInfo.status, sigInfo.utime,
                    sigInfo.stime);

            switch (sigInfo.code) {
                case CLD_EXITED:
                    CLOG_CRITICAL("Child has exited");
                    break;

                case CLD_KILLED:
                    CLOG_CRITICAL("Child was killed");
                    break;

                case CLD_DUMPED:
                    CLOG_CRITICAL("Child terminated abnormally");
                    break;

                case CLD_TRAPPED:
                    CLOG_CRITICAL("Traced child has trapped");
                    break;

                default:
                    //No need for monitoring CLD_STOPPED and CLD_CONTINUED
                    break;
            }

            processName = (*iter).second.processName;

            //Change the state of Component to STOPPED Status since the component is restarting
            iter->second.currentComponentStatus = COMPONENT_STATUS_STOPPED;

            CLOG_CRITICAL("SIGCHLD received for child %s", ((*iter).second.processName).c_str());
            if ((*iter).second.priority == PROCESS_PRIORITY_HIGH) {
                CLOG_CRITICAL("SIGCHLD received for HIGH PRIORITY child");
                //Raise an Alarm
                if(!m_bSuppressHigPriorityProcessAlarm)
                {
                    m_avaMgrAlarm->RaiseHighPriorityProcessDownAlarm(processName);
                }

                if ((!m_bProcessTerminationInProgress) &&
                        (!m_bSwitchoverInProgress) &&
                        (m_iInstanceStartMode != STANDALONE_MODE)) {
                    ActivateSwitchover();
                }
            }
            else {
                //Raise an alarm for Low Priority Process down.
                m_avaMgrAlarm->RaiseLowPriorityProcessDownAlarm(processName);
            }

            VerifyExitStatus(sigInfo.status);
            struct timeval tv;
            gettimeofday(&tv, NULL);

            CLOG_DEBUG("(*iter).second.secondsToShutdownApplication = %d (tv.tv_sec + ((tv.tv_usec) / 1000000)) = %d ",(*iter).second.secondsToShutdownApplication,(tv.tv_sec + ((tv.tv_usec) / 1000000)));
            if (((*iter).second.secondsToShutdownApplication) < (tv.tv_sec + ((tv.tv_usec) / 1000000))) {
                CLOG_DEBUG("Future-shutdown-time < current-time");
                (*iter).second.processRestartCounterForShutdownApplication = 0;
                ((*iter).second.processRestartCounterForShutdownApplication)++;
                ((*iter).second.secondsToShutdownApplication) = (tv.tv_sec + ((tv.tv_usec) / 1000000)) + m_uiCfgProcessRestartMaxAllowedIntervalHp;
                CLOG_CRITICAL("SIGCHLD received reseting the time and counter %d",(*iter).second.processRestartCounterForShutdownApplication);
            } else {
                CLOG_DEBUG("Future-shutdown-time > current-time");
                ((*iter).second.processRestartCounterForShutdownApplication)++;
                CLOG_INFO("SIGCHLD received for child shutdown-check check %d in %d seconds (Max-limit is %d)",
                ((*iter).second.processRestartCounterForShutdownApplication),
                m_uiCfgProcessRestartMaxAllowedIntervalHp,
                m_uiCfgProcessRestartMaxAllowedCountHp);
            }
            CLOG_DEBUG("Future shutdown Time: %d & Current Time: %d",((*iter).second.secondsToShutdownApplication), (tv.tv_sec + ((tv.tv_usec) / 1000000)));

            CLOG_DEBUG("(*iter).second.secondsToNextSigChld = %d (tv.tv_sec + ((tv.tv_usec) / 1000000)) = %d ",(*iter).second.secondsToNextSigChld,(tv.tv_sec + ((tv.tv_usec) / 1000000)));
            if (((*iter).second.secondsToNextSigChld) < (tv.tv_sec + (tv.tv_usec /  1000000))) {
                CLOG_DEBUG("Future-time < current-time");
                (*iter).second.processRestartCounter = 0;
                ((*iter).second.processRestartCounter)++;
                ((*iter).second.secondsToNextSigChld) = (tv.tv_sec + (tv.tv_usec /  1000000)) + m_uiCfgProcessRestartMaxAllowedInterval;
            } else {
                CLOG_DEBUG("Future-time > current-time");

                ((*iter).second.processRestartCounter)++;
                CLOG_INFO("SIGCHLD received for child switcher-over check %d in %d seconds (max-limit is %d)",
                ((*iter).second.processRestartCounter),
                m_uiCfgProcessRestartMaxAllowedInterval,
                m_uiCfgProcessRestartMaxAllowedCount);
            }
            CLOG_DEBUG("Future Time: %d & Current Time: %d",(*iter).second.secondsToNextSigChld, (tv.tv_sec + ((tv.tv_usec) / 1000000)));

            CLOG_DEBUG("processRestartCounterForShutdownApplication %d",(*iter).second.processRestartCounterForShutdownApplication);
            if ((*iter).second.processRestartCounterForShutdownApplication > m_uiCfgProcessRestartMaxAllowedCountHp) {
                CLOG_CRITICAL("SIGCHLD received for child has exceeded limit of %d in %d seconds",
                    m_uiCfgProcessRestartMaxAllowedCountHp,
                    m_uiCfgProcessRestartMaxAllowedIntervalHp);
                CLOG_CRITICAL("Stopping all child process");
                m_bProcessTerminationInProgress = true;
                TerminateAllComponents();
                VerifyExitStatus(ITS_PROCESS_UNSTABLE_ERROR,processName);
            }

            CLOG_DEBUG("processRestartCounter=%d and m_uiCfgProcessRestartMaxAllowedCount=%d",(*iter).second.processRestartCounter,m_uiCfgProcessRestartMaxAllowedCount);
            if ((*iter).second.processRestartCounter > m_uiCfgProcessRestartMaxAllowedCount) {
                CLOG_CRITICAL("SIGCHLD received for child has exceeded limit of %d in %d seconds",
                        m_uiCfgProcessRestartMaxAllowedCount,
                        m_uiCfgProcessRestartMaxAllowedInterval);

                //TODO:Raise an alarm mentioning Max restarts have been reached.
                // m_avaMgrAlarm->RaiseProcessRestartLimitReachedAlarm(processName);

                //Commenting out so that process shall not be restarted after max-restarts.
                (*iter).second.processRestartCounter = 0;

                if ((!m_bProcessTerminationInProgress) &&
                        (!m_bSwitchoverInProgress) &&
                        (m_iInstanceStartMode != STANDALONE_MODE)) {
                    ActivateSwitchover();
                }
            }

            //Change Components Status flag since one of the component is restarted.
            m_bAllComponentsInitialized = false;

            ret = (*iter).first;
        }
        else
        {
            // SIGCHLD not from one of the components so it has to be a
            // platform related command run by avamgr
            CLOG_DEBUG("SIGCHLD received from a non DRE component ");
            CLOG_DEBUG("\nSigInfo \n"
                    "   si_errno:   %d\n"
                    "   si_code:    %d\n"
                    "   si_pid:     %d\n"
                    "   si_uid:     %d\n"
                    "   si_status:  0x%x\n"
                    "   si_utime:   0x%x\n"
                    "   si_stime:   0x%x\n",
                    sigInfo.errorno, sigInfo.code,
                    sigInfo.pid, sigInfo.uid,
                    sigInfo.status, sigInfo.utime,
                    sigInfo.stime);

            switch (sigInfo.code) {
                case CLD_EXITED:
                    CLOG_DEBUG("Child has exited");
                    break;

                case CLD_KILLED:
                    CLOG_DEBUG("Child was killed");
                    break;

                case CLD_DUMPED:
                    CLOG_DEBUG("Child terminated abnormally");
                    break;

                case CLD_TRAPPED:
                    CLOG_DEBUG("Traced child has trapped");
                    break;

                default:
                    CLOG_DEBUG("Child exited due to some signal");
                    break;
            }

        }
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::HandleQueuedSignalInfo() <<<<<<<<<<");

    return ret;

}

void AvailabilityManager::CreateAndQueueDummySignal(pid_t pid)
{
    struct SignalEventInfo sigInfo;
    sigInfo.errorno  =  0;
    sigInfo.code  = CLD_EXITED;
    sigInfo.pid   =  pid;
    sigInfo.uid   =  0;
    sigInfo.status =  0;
    sigInfo.utime  =  0;
    sigInfo.stime  =  0;

    m_signalList.InsertData(sigInfo);


}



