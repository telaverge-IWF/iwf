/****************************************************************************
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
 * ID: $Id: DIAMon.cpp,v 3.4.4.1.36.3 2013/04/01 05:40:48 vsarath Exp $
 *
 * LOG: $Log: DIAMon.cpp,v $
 * LOG: Revision 3.4.4.1.36.3  2013/04/01 05:40:48  vsarath
 * LOG: Fix for Coverity warnings
 * LOG:
 * LOG: Revision 3.4.4.1.36.2  2013/03/12 04:49:02  vsarath
 * LOG: Fix for coverity issue
 * LOG:
 * LOG: Revision 3.4.4.1.36.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.4.4.1  2012/02/06 06:28:46  brajappa
 * LOG: Resolved compilation errors caused in g++ 4.4.x
 * LOG:
 * LOG: Revision 3.4  2011/02/08 22:48:58  nvijikumar
 * LOG: Compilation Issue fix
 * LOG:
 * LOG: Revision 3.3  2010/09/03 09:33:19  nvijikumar
 * LOG: Compilation issue on Solaris GCC
 * LOG:
 * LOG: Revision 3.2  2010/07/07 08:34:46  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2008/03/27 12:07:43  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/07 15:49:40  yranade
 * LOG: Initial Version of Monitor Utility. Please refer README for details.
 * LOG:
 ****************************************************************************/
#ident "$Id: DIAMon.cpp,v 3.4.4.1.36.3 2013/04/01 05:40:48 vsarath Exp $"

#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <signal.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <fcntl.h>


#include <its++.h>
#include <its_exception.h>
#include <its_exception_log.h>
#include <its_event_log.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <syslog.h>
#include <expat.h>

#include <DIAMon_trace.h>
#include <DIAMon.h>
#include <DIAMon_prot.h>
#include <DIAMon_alarm.h>

#include <its_statics.cpp>

using namespace its;
using namespace std;

#if defined (WIN32)
    static ITS_NtExceptionLog exceptionLog("DIA_Mon");
#elif defined (unix)
    static ITS_UnixExceptionLog exceptionLog("DIA_Mon");
#endif


#define DIA_MON_ASSERT(assertion)                                                  \
    if (!(assertion))                                                              \
    {                                                                              \
        ITS_ASSERT_PRINT(assertion);                                               \
        if (inParser)                                                              \
        {                                                                          \
            fprintf(stderr, "At around line %d column %d in parsed text.\n",       \
                    XML_GetCurrentLineNumber(parser),                              \
                    XML_GetCurrentColumnNumber(parser));                           \
        }                                                                          \
        DIAMon_Alarm(11002, ALARM_LVL_CRIT, __FILE__, __LINE__, (char*)string("DIAMon Exiting").c_str()); \
        abort();                                                                   \
    }

#define MAX_TASKS    32
#define MAX_START_TIME 10

/*
 * Parser strings
 */
#define TASKS_STRING        "Task"
#define APPL_STRING         "DIA_Mon"
#define DEPENDENCIES_STRING "Dependency"

Globals globals = {0,0};
DIA_MonitorService ms;
char task[MAX_TITLE_LEN];
MonitorObject *pMonitorObject[MAX_TASKS];
char dMatrix[MAX_DEPEND_LEN][MAX_DEPEND_LEN];

static XML_Parser   parser;
static ITS_BOOLEAN  inParser = ITS_FALSE;
ITS_BOOLEAN  isTask          = ITS_FALSE;
ITS_BOOLEAN  isDependency    = ITS_TRUE;
bool isMonitorOn             = true;

int numMonitorObjects = 0;
int numofDependencies = 0;
pid_t died_pid = 0;

//Warning Fix: deprecated conversion from string constant to "char*"
static void PreRunCheck(const char *taskName);
static void MON_SLEEP(int secs);

#if defined (DO_SNMP)

class DIA_InheritedMonitor : public DIA_Monitor
{
public:
    DIA_InheritedMonitor() : adpProcessIndex(0) {}

    bool Start()
    {
        DIAMON_TRACE_DEBUG(("Application started from OAM"));
       
        adpProcessIndex = ms.GetTaskIndex("IDS");
 
        if(!pMonitorObject[adpProcessIndex]->bStarted)
        {
           ms.StartTask(pMonitorObject[adpProcessIndex]);

        }

        return true;
    }

    void Kill()
    {
        DIAMON_TRACE_DEBUG(("Application terminated from OAM"));

        adpProcessIndex = ms.GetTaskIndex("IDS");

        ms.ExecutePostTerm(pMonitorObject[adpProcessIndex]->postTerm);

    }

    void SetMonitorOn(bool val)
    {
        DIAMON_TRACE_DEBUG(("Monitor Set from OAM"));

        isMonitorOn = val;
    }

    static int SendAlarm(DIA_EventManagement::EventID eventID,
                         DIA_EventManagement::Severity severity,
                         DIA_ManagedObject::ID oid, const char *desc)
    {
        SEND_ALARM(eventID, severity, oid, desc);

        return ITS_SUCCESS;
    }

private:
    int adpProcessIndex;
};

//DIA_NODOPERATIONALSTATE

// DIA_Gateway implementation

static DIA_InheritedMonitor _im;

DIA_Monitor &DIA_Monitor::GetMonitor()
{
    return _im;
}

#endif //DO_SNMP

////////////////////////////////////////////////////////////////////////////////
extern "C"
void SignalHandler(int signo)
{
   DIAMON_TRACE_ERROR(("Signal Handler Caught...Exiting"));

   _exit(0);
}


////////////////////////////////////////////////////////////////////////////////
extern "C" void
sig_chld (int signo)
{
    pid_t pid;

    int stat, childVal, sigNo;
    int index;

    while(( pid = waitpid(-1, &stat, WNOHANG)) >0)
    {
        DIAMON_TRACE_DEBUG(("Pid DIED %d", pid));

        died_pid = pid;

        char* task = ms.GetTaskName(pid);
        index = ms.GetTaskIndex(task);
        pMonitorObject[index]->end = time(NULL);

        /*
        * We now have the info in 'stat' and can manipulate it using
        * the macros in wait.h.
        */
        if (WIFEXITED(stat))                /* did child exit normally? */
        {
            childVal = WEXITSTATUS(stat); /* get child's exit status */
          
            if ( task != NULL ) 
            {
                DIAMON_TRACE_DEBUG(("Task %s exited normally with status %d\n", task, childVal));
            }
        }
        else if (WIFSIGNALED(stat))
        {
            sigNo = WTERMSIG(stat); /* get the signal number that caused termination */

#if defined WCOREDUMP
            if ( WCOREDUMP(stat))
            {
                DIAMON_TRACE_ERROR(("core file generated for task %s\n", task));

                char cmd[255];
                char tbuf[255];
                time_t local;
                tm abuf;
                const char *month[] = {"Jan", "Feb", "Mar", "Apr",
                                       "May", "Jun", "Jul", "Aug",
                                       "Sep", "Oct", "Nov", "Dec"};

                time(&local);
                localtime_r(&local, &abuf);

                snprintf(tbuf, 254, "%s%02d.%02d:%02d:%02d", month[abuf.tm_mon],
                        abuf.tm_mday, abuf.tm_hour, abuf.tm_min,
                        abuf.tm_sec);

                strcpy(cmd, "cp core core.");
                strncat(cmd, tbuf, 255-strlen(cmd)-1);

                system(cmd);
            }
#endif

            DIAMON_TRACE_DEBUG(("Task %s exited with signal %d\n", task, sigNo));
        }
        else if (WIFSTOPPED(stat))
        {
            sigNo = WSTOPSIG(stat);

            DIAMON_TRACE_DEBUG(("Task stopped %s, signal number = %d\n", task, sigNo));
        }
    }

}


////////////////////////////////////////////////////////////////////////////////
static void 
GetExistingPid(MonitorObject *pTask)
{
    int pid;

    std::ifstream infile ("/tmp/proc");

    if ( !infile)
    {
        DIAMON_TRACE_CRITICAL(("Unable to open proc file"));

        return;
    }
    
    while ( infile >> pid )
    {
       pTask->pid = pid;
    }
}

////////////////////////////////////////////////////////////////////////////////
int 
DIA_MonitorService::GetTaskIndex(char *taskName)
{
    int retindex = 0;

    for (int i=0; i < numMonitorObjects; i++)
    {
        if ( strcmp(pMonitorObject[i]->title, taskName) == 0 )
        {
            retindex = i;

            break;
        }
    }

    return retindex;
}

////////////////////////////////////////////////////////////////////////////////
char* 
DIA_MonitorService::GetTaskName(pid_t pid)
{
    char *name = NULL;

    for (int i=0; i < numMonitorObjects; i++)
    {
        if ( pMonitorObject[i]->pid == pid)
        {
            if (strcmp(pMonitorObject[i]->type, "Task" ) == 0)
            {
                name = pMonitorObject[i]->taskName;
            }
            else
            {
                name = pMonitorObject[i]->dependencyName;
            }
            break;
        }
    }

    return name;

}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::PollMonitorObjects()
{

    /* Polling mechanism for checking tasks */

    int j = 0;

    for ( int i=0; i < numMonitorObjects; i++)
    {
        if(pMonitorObject[i]->bStarted)
        {
            /* check to see if the process is running */
            if (!FindTask(pMonitorObject[i]->pid))
            {
                time_t runtime = (pMonitorObject[i]->end - pMonitorObject[i]->start);

                DIAMON_TRACE_DEBUG(("TIME %d", runtime));

                DIAMON_TRACE_ERROR(("%s not running\n", pMonitorObject[i]->title));

                //Warning Fix: deprecated conversion from string constant to "char*"
                DIAMon_Alarm(11009, ALARM_LVL_CRIT, __FILE__, __LINE__,
                        (char*)string("DIAMon detected task %s not running").c_str(), pMonitorObject[i]->title);

                if ( runtime < MAX_START_TIME )
                {
#if defined (NMS_VENDOR)
                    if (strcmp(pMonitorObject[i]->title, "DIAD") == 0)
                    {
                        system("/opt/nmstx/bin/txreset");
                        system("/opt/nms/bin/ctdaemon -ks");
                    }
#endif

                    pMonitorObject[i]->restarts++;
                }
                else
                {
                    pMonitorObject[i]->restarts = 0;
                }
                if (  pMonitorObject[i]->restarts >= globals.no_of_tries )
                {
                    pMonitorObject[i]->bStarted = false;
                    //pMonitorObject[i]->restarts = 0;

                    DIAMON_TRACE_ERROR(("Unable to start %s", pMonitorObject[i]->title));

                    DIAMON_TRACE_ERROR(("CHECK %s configuration", pMonitorObject[i]->title));

                    //Warning Fix: deprecated conversion from string constant to "char*"
                    DIAMon_Alarm(11006, ALARM_LVL_CRIT, __FILE__, __LINE__,
                         (char *)string("DIAMon unable to start task %s, giving up after %d tries").c_str(), 
                         pMonitorObject[i]->title, globals.no_of_tries);
              
                    continue;
                }
                if ( strcmp(pMonitorObject[i]->type, "Task") == 0 )
                {
                    if(strlen(pMonitorObject[i]->postTerm) != 0 )
                    {
                        DIAMON_TRACE_DEBUG(("PostTerm %s", pMonitorObject[i]->postTerm));

                        ExecutePostTerm(pMonitorObject[i]->postTerm); 

                    }
                    /* Check for any dependencies */
                    if (pMonitorObject[i]->numOfDependencies > 0 )
                    {
                        while ( j < pMonitorObject[i]->numOfDependencies )
                        {
                            if( !FindTask(pMonitorObject[i]->dependency[j]))
                            {
                                int index = GetTaskIndex(pMonitorObject[i]->dependency[j]);

                                /* Start the associated dependency */
                                StartTask(pMonitorObject[index]);
                            }
                            j++;
                        }
                    }
                }
                else
                {
                    //Fixing Array compared against 0 
                    if ( pMonitorObject[i] != NULL )
                    {
                        int taskToStop = GetTaskIndex(pMonitorObject[i]->taskName); 

                        StopTask(pMonitorObject[taskToStop]);
                    }
                }

                /* Restart the task */
                StartTask(pMonitorObject[i]); 
            }
        }
    } 
}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::ExecutePostTerm(char* command)
{

 if ( command != NULL )
 { 
    if(system(command) !=0)
    { 
        DIAMON_TRACE_ERROR(("Could not execute %s", command));
    }
    else
    {
       DIAMON_TRACE_DEBUG(("Executed postTerm"));
    }
 }
}



////////////////////////////////////////////////////////////////////////////////
bool
DIA_MonitorService::FindTask (pid_t pid)
{
    bool ret = true;

    // kill with signal 0 is meant to check for the process's existence
    // man -s2 kill
    if (kill(pid, 0))
    {
    	if (errno == EINVAL)
        {
            DIAMON_TRACE_DEBUG(("Unable to execute kill"));
	    ret = true;
        } 
        else if (errno == ESRCH)
        {
            DIAMON_TRACE_DEBUG(("ESRCH error process %d has died",pid));
            ret = false;
        }
        else if ( errno == EPERM)
        {
            DIAMON_TRACE_DEBUG(("PERMISSION DENIED : Check for %d failed",pid));
            ret = true;
	}
	/*else
	{
            DIAMON_TRACE_DEBUG(("Other error assuming process %d has died",pid));
	    ret = false;
	}
        */
	
    }

    return ret;
}
////////////////////////////////////////////////////////////////////////////////
bool
DIA_MonitorService::FindTask (char *taskName)
{
    char buff[256];
    bool ret = true;
    int pid = 0;

    //sprintf(buff, "%s%s%s", "pgrep ", taskName, ">/tmp/proc");
    //Coveirty Issue Fix - 11825 - Calling risky function
    snprintf(buff, 256-1,"%s%s%s", "ps -e | grep ", taskName," | awk '{print $1}' >/tmp/proc");

    if (system(buff)!=0)
    {
        ret = false;
    }

    std::ifstream infile ("/tmp/proc");

    if(infile.is_open() && infile >> pid)
    {
        DIAMON_TRACE_DEBUG(("Found Task %s with pid=%d\n",taskName,pid));

        printf("Found Task %s with pid=%d\n",taskName,pid);

        //Warning Fix: deprecated conversion from string constant to "char*"
        DIAMon_Alarm(11003, ALARM_LVL_CRIT, __FILE__, __LINE__,
                     (char*)string("%s already running with pid %d").c_str(), taskName, pid);
    }
    else
    {
        ret =  false;
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::StopTask(MonitorObject *pTask)
{
    bool found = FindTask(pTask->pid);
    
    if (found)
    {
        int ret = kill(pTask->pid, SIGKILL);
      
        if (ret == 0)
        {
            DIAMON_TRACE_DEBUG(("Terminated %s",pTask->taskName));

            //Warning Fix: deprecated conversion from string constant to "char*"
            DIAMon_Alarm(11007, ALARM_LVL_INFO, __FILE__, __LINE__, 
                         (char*)string("DIAMon stopped task %s").c_str(), pTask->taskName); 
        }
        else
        {
            if (errno == ESRCH)
            {
                DIAMON_TRACE_DEBUG(("%s already terminated",pTask->taskName));
            }
            else
            {
                DIAMON_TRACE_DEBUG(("Unable to terminate %s",pTask->taskName));

                //Warning Fix: deprecated conversion from string constant to "char*"
                DIAMon_Alarm(11008, ALARM_LVL_CRIT, __FILE__, __LINE__, 
                            (char*)string("DIAMon unable to stop task %s").c_str(), pTask->taskName); 
            }
        }
    }
    else
    {   
        DIAMON_TRACE_DEBUG(("%s crashed",pTask->taskName));
    }
}


////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::CreateProcess(MonitorObject *pTask )
{
    pid_t pid;
    char *tName = NULL;

    if (strcmp(pTask->type, "Task" ) == 0)
    {
        tName = pTask->taskName;
    }
    else
    {
        tName = pTask->dependencyName;
    }
    if ((pid = fork()) < 0)
    {
        DIAMON_TRACE_ERROR(("Error in fork"));
    }

    else if (pid == 0)
    {  
        /* Child */
        int ret = chdir(pTask->dirName);
        umask(0);

        if (ret != 0)
        {
            DIAMON_TRACE_ERROR(("Unable to change directory"));
        }

        DIAMON_TRACE_DEBUG(("pTask->args .............. %s%d\n",pTask->args,strlen(pTask->args)));
        DIAMON_TRACE_DEBUG(("ProcessName .............. %s\n",tName));

        char *argv[MAX_ARGS];
        if (strlen(pTask->args) > 0 )
        {
            argv[0] = tName;
            int argc = 0;
            argv[++argc] = strtok(pTask->args, " ");

            DIAMON_TRACE_DEBUG(("argv[%d] = %s", argc, argv[argc]));

            while (argv[argc] != 0 && argc < (MAX_ARGS-1))
            {
                argv[++argc] = strtok(0, " ");

                DIAMON_TRACE_DEBUG(("argv[%d] = %s", argc, 
                                   (argv[argc] ? argv[argc] : "null")));
            }

            DIAMON_TRACE_DEBUG(("argc = %d", argc));
        }
        else
        {
            argv[0] = tName;
            argv[1] = NULL;
        }

        //if(execl(tName, tName, pTask->args,(char *)0) < 0)
        if(execv(tName,argv) < 0)
        {  
            DIAMON_TRACE_ERROR(("Error in exec"));

            //Warning Fix: deprecated conversion from string constant to "char*"
            DIAMon_Alarm(11005, ALARM_LVL_CRIT, __FILE__, __LINE__,
                         (char*)string("DIAMon unable to start task %s").c_str(), tName);

            /* exec error */
            /* Child terminates */
            _exit(0);
        }
    }
    else if (pid > 0) 
    {
        /* Parent */
        pTask->pid = pid;
        
        /* Make sure that child didn't die/
           couldn't be exec'd 
        */
        if ( pid != died_pid)
        {
            pTask->bStarted = true;
        }
        else
        {
            pTask->bStarted = false;
        }
        pTask->start = time(NULL);

        DIAMON_TRACE_DEBUG(("Task %s Pid %d",tName, pTask->pid));

        //Warning Fix: deprecated conversion from string constant to "char*"
        DIAMon_Alarm(11004, ALARM_LVL_INFO, __FILE__, __LINE__,
                     (char*)string("DIAMon started and monitoring Task %s Pid %d").c_str(),
                      tName, pTask->pid);

        /* Wait for the child */
        signal(SIGCLD, sig_chld);
	    
    }
}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::StartTask(MonitorObject *pTask)
{
    CreateProcess(pTask);    

}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::StartTasks()
{
    for (int i = 0; i < numMonitorObjects; i++)
    {
        if(isMonitorOn)
        {
            if (!FindTask(pMonitorObject[i]->title))
            {
#if defined (NMS_VENDOR)
                if ( strcmp(pMonitorObject[i]->title, "ctdaemon") == 0 )
                {
                    system("/opt/nmstx/bin/txreset");
                    sleep(1);
                    system("/opt/nms/bin/ctdaemon -ks");
                }
#endif
                if(strcmp(pMonitorObject[i]->type,"Task") == 0)
                {
                    DIAMON_TRACE_DEBUG(("Number of dependencies for  %s are %d \n",
                                        pMonitorObject[i]->title,
                                        pMonitorObject[i]->numOfDependencies));

                    for(int x = 0; x < pMonitorObject[i]->numOfDependencies; x++)
                    {
                        int ind = GetTaskIndex(pMonitorObject[i]->dependency[x]);

                        if ( !FindTask(pMonitorObject[ind]->title))
                        {
                              StartTask(pMonitorObject[ind]);
                              MON_SLEEP(1);
                        } 
                    }

                    StartTask(pMonitorObject[i]);
                }
            }
            else
            {
                DIAMON_TRACE_DEBUG(("Task already running"));

                GetExistingPid(pMonitorObject[i]); 
                
                pMonitorObject[i]->bStarted  = true;
            }
        }
    }
    

}


////////////////////////////////////////////////////////////////////////////////
void
ConstructObject(const char *title, const char *args, const char *directory, const char* postTerm)
{
     pMonitorObject[numMonitorObjects] =
                          (MonitorObject *) malloc(sizeof(MonitorObject));

     //Fixing Array Compared against 0
     if (pMonitorObject[numMonitorObjects] == NULL)
     {
         DIAMON_TRACE_ERROR(("Out of memory"));
     }
     memset(pMonitorObject[numMonitorObjects], 0, sizeof(MonitorObject));

     ITS_ASSERT(title != NULL);
     strcpy(pMonitorObject[numMonitorObjects]->title, title);

     if ( strlen(args) != 0 )
     {
         strcpy(pMonitorObject[numMonitorObjects]->args, args);
     }
     else
     {
         strcpy(pMonitorObject[numMonitorObjects]->args,"\0");
     }
     if ( strlen(directory) != 0 )
     {
         strcpy(pMonitorObject[numMonitorObjects]->dirName, directory);
     }
     else
     {
         strcpy(pMonitorObject[numMonitorObjects]->dirName, ".");
     }
     if ( postTerm != NULL )
     {
         //Coveirty Issue Fix - 12248 - Calling Risky function
         strncpy(pMonitorObject[numMonitorObjects]->postTerm, postTerm, MAX_PATH-1);
     }
     if (! isDependency)
     {
         /* Build the TaskName */
         char taskName[100] = {'\0'};
         strncpy(taskName, pMonitorObject[numMonitorObjects]->dirName, 99);
         taskName[99] = '\0';
         if (taskName[strlen(taskName) - 1] != '/')
         {
            //Fixing Destination Buffer Too Small
            strncat(taskName, "/", 100-strlen(taskName)-1);
         }

         //Fixing Destination Buffer Too Small
         strncat(taskName, pMonitorObject[numMonitorObjects]->title,
                                                    100-strlen(taskName)-1);
         strcpy(pMonitorObject[numMonitorObjects]->taskName, taskName);

         /* Set the type of the object as Task */
         strcpy(pMonitorObject[numMonitorObjects]->type, "Task");
     }
     else
     {
         /* Set the taskName to the global task*/
     
         strcpy(pMonitorObject[numMonitorObjects]->taskName, task);

         /* Build the DependencyName */
         //Fixing Destination buffer too Small
         char dependencyName[101];
         strncpy(dependencyName, pMonitorObject[numMonitorObjects]->dirName, 100);
         if (dependencyName[strlen(dependencyName) - 1] != '/')
         {
             strncat(dependencyName, "/", 101 - strlen(dependencyName));
         }

         //Fixing Destination buffer too Small
         strncat(dependencyName, pMonitorObject[numMonitorObjects]->title, 101 - strlen(dependencyName));
         strcpy(pMonitorObject[numMonitorObjects]->dependencyName, dependencyName);

         /* Set the type of the object as Dependency */
         strcpy(pMonitorObject[numMonitorObjects]->type, "Dependency");
     }
}

////////////////////////////////////////////////////////////////////////////////
void
HandleApplication(const char **attr)
{
    while (*attr)
    {
        const char *tattr = *attr;

        attr++;
    
        if (strcmp(tattr, "MonitorInterval") == 0)
        {
            globals.monitor_interval = atoi(*attr);
        }
        else if (strcmp(tattr, "TraceCritical") == 0)
        {
            if (atoi(*attr) == 1)
            {
                EnableDIAMONCriticalTracing();
            }
        }
        else if (strcmp(tattr, "TraceError") == 0)
        {
            if (atoi(*attr) == 1)
            {
                EnableDIAMONErrorTracing();
            }
        }
        else if (strcmp(tattr, "TraceDebug") == 0)
        {
            if (atoi(*attr) == 1)
            {
                EnableDIAMONDebugTracing();
            }
        }
        else if (strcmp(tattr, "TraceWarning") == 0)
        {
            if (atoi(*attr) == 1)
            {
                EnableDIAMONWarningTracing();
            }
        }
        attr++;
    }
}

////////////////////////////////////////////////////////////////////////////////
void
HandleMonitorObject(const char **attr)
{
    const char *title = NULL;
    const char *args = NULL;
    const char *postTerm = NULL;
    const char *directory = NULL;

    while (*attr)
    {
        const char *tattr = *attr;

        attr++;

        if (strcmp(tattr, "name") == 0)
        {
            title = *attr;

            if ( !isDependency)
            {
               //Correcting Calling Risky Function
               strncpy(task, *attr, MAX_TITLE_LEN-1);
            }
            else
            {
               //Correcting Calling Risky Function
               strncpy(&dMatrix[numofDependencies++][0], *attr, MAX_DEPEND_LEN-1); 
            }
        }
        else if (strcmp(tattr, "args") == 0)
        {
            args = *attr;
        }
        else if (strcmp(tattr, "directory") == 0)
        {
            directory = *attr;
        }
        else if (strcmp(tattr, "postTerminateAction") == 0)
        {
           postTerm = *attr;
        } 

        attr++;
    }
    ConstructObject(title, args, directory, postTerm); 
}

////////////////////////////////////////////////////////////////////////////////
void
ElementStart(void *data, const char *el, const char **attr)
{

    if (strcmp(el, APPL_STRING) == 0)
    {
        HandleApplication(attr);
    }
    else if (strcmp(el, TASKS_STRING) == 0)
    {
        isDependency = ITS_FALSE;
        HandleMonitorObject(attr);
        numMonitorObjects ++ ;
    }
    else if (strcmp(el, DEPENDENCIES_STRING) == 0)
    {
        isDependency = ITS_TRUE;
        HandleMonitorObject(attr);
        numMonitorObjects ++ ;
    }

}

////////////////////////////////////////////////////////////////////////////////
void
ElementEnd(void *data, const char *el)
{
    int index;

    if (strcmp(el, TASKS_STRING) == 0)
    {
       index = ms.GetTaskIndex(task);

       //pMonitorObject[index]->dependency = dMatrix;

       memcpy(pMonitorObject[index]->dependency,dMatrix,
              sizeof(dMatrix));

       pMonitorObject[index]->numOfDependencies = numofDependencies;
    
       /* Reset */
       numofDependencies = 0;
       memset(dMatrix, 0, sizeof(dMatrix));
    }

}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::ReadConfig()
{
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;

    buf = NULL;
    size = 0;

    ITS_Application::SetConfigFileExtension("xml");
    parser = XML_ParserCreate(NULL);
    DIA_MON_ASSERT(parser != NULL);

    /* set the token functions */
    XML_SetElementHandler(parser, (XML_StartElementHandler)ElementStart, 
                            (XML_EndElementHandler)ElementEnd);

    xml = fopen(ITS_Application::GetConfigFileName(), "r");
    DIA_MON_ASSERT(xml != NULL);

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    DIA_MON_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    DIA_MON_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = (char *)malloc(size);
    DIA_MON_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    DIA_MON_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NUL */
    buf[size - 1] = 0;

    inParser = ITS_TRUE;
    parseSuccessful = XML_Parse(parser, buf, size, ITS_TRUE);
    DIA_MON_ASSERT(parseSuccessful == 0);

     /* clean up */
    if (buf)
    {
        free(buf);
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService::BeforeApplicationLoop.
//

void DIA_MonitorService::BeforeAppLoop()
{
    ////////////////////////////////////////////////////////
    // Mandatory initializations.
    ////////////////////////////////////////////////////////

    globals.monitor_interval = 20;
    globals.no_of_tries = 3;

    // Parse the XML configuration file
    ReadConfig();

    DIAMON_TRACE_DEBUG(("Parsed config file"));

    //Warning Fix: deprecated conversion from string constant to "char*"
    DIAMon_Alarm(11001, ALARM_LVL_INFO, __FILE__, __LINE__, 
                (char*)string("DIAMon Started").c_str());

    StartTasks();

#if defined(DO_SNMP)

    //Start the SNMP Agent
    DIA_SNMP_AGENT.Start();

#endif

}

static void MON_SLEEP(int secs)
{
    struct timespec tim;
    struct timespec tom;
    tim.tv_sec = globals.monitor_interval;
    tim.tv_nsec = 10;
    int ret;

    ret = nanosleep(&tim, &tom);

    if (ret)
    {
        if (errno == EINTR)
        {
            if (nanosleep(&tom, 0))
            {
                 cout << "Error in reseting sleep" << endl;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService::ApplicationLoop.
//
void DIA_MonitorService::AppLoop()
{
    MON_SLEEP(globals.monitor_interval);

    if ( isMonitorOn )
    {
        PollMonitorObjects();
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService::AfterApplicationLoop.
//

void DIA_MonitorService::AfterAppLoop()
{ 
    for (int i = 0; i < numMonitorObjects; i++)
    {
        if (pMonitorObject[i])
        {
            free(pMonitorObject[i]);
        }
    }
    // Log that service is stopped.
    DIAMON_TRACE_DEBUG(("Service stopped"));

}

////////////////////////////////////////////////////////////////////////////////
void DIA_MonitorService::Run()
{
   signal(SIGINT, SignalHandler);

   PreRunCheck("DIAMon");


   BeforeAppLoop();

   while (1)
   {
       AppLoop();
   }

   AfterAppLoop();
}


////////////////////////////////////////////////////////////////////////////////
int DIA_MonitorService::DaemonInit()
{
    pid_t pid;

    if ((pid = fork()) > 0)
    {
       /* we are the parent */
       exit(0);
    }
    else if (pid == 0)
    {
        /*
         * we are the child
         * become a session leader.  We will lead a new process group,
         * and have no controlling TTY.
         */
        setsid();

        /*
         * ditch stdxx
        */

        close(0);
        close(1);
        close(2); 

        umask(0);

        Run();
    }
    else
    {
        /* fork failure. */
        return (-1);
    }

    return 1;
}

////////////////////////////////////////////////////////////////////////////////
void
DIA_MonitorService::EventLogCreate()
{
    openlog("DIAMon", LOG_PID, LOG_DAEMON);
}

////////////////////////////////////////////////////////////////////////////////
//Warning Fix: deprecated conversion from string constant to "char*"
static void
PreRunCheck(const char *taskName)
{
    char buff[256];
    int pid = 0;

#if 0
    std::ifstream infile ("/tmp/lproc");

    if(infile.is_open() && infile >> pid)
    {
        if ( pid != getpid() )
        {
            if (ms.FindTask(pid))
            {
               printf("Found Task %s with pid=%d\n",taskName,pid);

               DIAMon_Alarm(11003, ALARM_LVL_CRIT, __FILE__, __LINE__, 
                            "%s already running with pid %d", taskName, pid);

               exit(0);
            }
        }
    }
#endif

    //Correcting Calling risky function
    snprintf(buff, 256-1,"%s%d%s","echo " , getpid()," >/tmp/lproc");
    system(buff);

    /* Change */
    int fd = open("/tmp/lproc", O_RDWR);

    if (lockf(fd, F_TLOCK, 0) == 0)
    {
        printf("**** LOCKED FILE****\n");
    }
    else
    {
        if (errno == EAGAIN)
        {
            printf("Unable to aquire lock \n");
        }

        //Warning Fix: deprecated conversion from string constant to "char*"
        ms.FindTask((char*)taskName);
     
        exit(0);
    }

    //Fixing Resource leak
    if(fd != -1)
    {
        close(fd);
    }  

}

////////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

int main(int argc, const char** argv)
{
    bool runAsService = true;
   
    if ( argc > 1 )
    {
        if ( strcmp(argv[1], "-i")== 0 )
        {
            runAsService = false;
        }
    }

    try {

        // Set the exception log.

        ITS_GenericException::SetExceptionLog(exceptionLog);

        //
        // Set IntelliSS7 Application name.
        //

        ITS_Application::SetName("DIAMon");

        ms.EventLogCreate();

        if ( runAsService )
        {
            ms.DaemonInit();
        }
        else
        {
            ms.Run();
        }
    }
    catch (ITS_GenericException& exc)
    {
        exc.Log();
    } 
    catch (exception& exc)
    {
        ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

        standardExc.Log(); 
        
    }
    catch (its::GenericException& exc) //Fixing Uncaught Exception
    {
        exit(EXIT_FAILURE);
    } 
    catch (...)
    {
        exit(EXIT_FAILURE);
    }

    cout << "End of Run..." << endl;
    
    // To stop here in console application.
    cout << "Type any key to quit...";

    if(fgetc(stdin) == NULL)
    {
        return -1;
    }

    return 0;
}


