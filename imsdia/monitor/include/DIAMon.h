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
 * ID: $Id: DIAMon.h,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $
 *
 * LOG: $Log: DIAMon.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/07 15:49:40  yranade
 * LOG: Initial Version of Monitor Utility. Please refer README for details.
 * LOG:
 ****************************************************************************/
#ident "$Id: DIAMon.h,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $"

////////////////////////////////////////////////////////////////////////////////
//
//  MonitorService.
//

#if !defined(_DIAMON_H_)
#define _DIAMON_H_

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#if defined (unix)
#include <sys/types.h>
#include <unistd.h>
#endif

#include <iostream>
#include <string>
#include <its++.h>
#include <DIAMon_prot.h>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif
#if defined(STD_NAMESPACE)
using namespace std;
#endif

#if !defined(WIN32)
#define MAX_PATH 260
#endif

#define MAX_TITLE_LEN   MAX_PATH
#define MAX_DEPEND_LEN  MAX_PATH 
#define MAX_ARGS        256
#define TYPE_LEN        20 

struct MonitorObject
{
    char title[MAX_TITLE_LEN];    // Title of the task for monitoring
    char taskName[MAX_PATH];      // Task name
    char dependencyName[MAX_PATH];// Dependency name
    char dirName[MAX_PATH];       // Current directory for the task
    bool bStarted;                // If TRUE, task was started
    pid_t pid;	                  // ProcessId of the task 
    char dependency[MAX_DEPEND_LEN][MAX_DEPEND_LEN];
    int numOfDependencies;        // No. of dependencies 
    char args[MAX_ARGS];          // args to the object
    char type[TYPE_LEN];          // type of object ( task or dependency)
    char postTerm[MAX_PATH];      // PostTerminate action
    time_t start;
    time_t end;
    int restarts;
    
};

struct Globals
{ 
    // Polling interval
    int monitor_interval;
    int no_of_tries;
};

class DIA_MonitorService
{
public:
    DIA_MonitorService(){};

    ~DIA_MonitorService(){};

    void StartTasks();

    void EventLogCreate();

    void ReadConfig();

    void BeforeAppLoop();

    void AppLoop();

    void AfterAppLoop();

    void Run();

    int DaemonInit();

    static void	        CreateProcess(MonitorObject *pTask );

    static void         StartTask(MonitorObject *pTask);
 
    static void         PollMonitorObjects();

    static void         ExecutePostTerm(char *command);
    
    static bool         FindTask(pid_t pid);

    static bool         FindTask(char *taskName);

    static void         StopTask(MonitorObject *pTask);

    static int          GetTaskIndex(char *taskName);

    static char*        GetTaskName(pid_t pid);
 
};

#endif    // !defined(_DIAMON_H_)
