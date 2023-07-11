#ifndef __THREADMANAGER_H__
#define __THREADMANAGER_H__
// Headers
#include <list>
#include <map>
#include <iostream>
#include <queue>

#ifdef ITU
#undef ITU
#endif

#ifndef CCITT
#define CCITT
#endif

#include <its++.h>
#include <its_timers.h>
#include <its_ual.h>
#include <engine++.h>
#include <mtp3_intern.h>
#include <ss7_mgmt.h>
#include <dia_trace.h>
#include <dia_config.h>
#include <dia_frame.h>
#include <dia_module.h>
#include <ssg_defines.h>
#include <ssg_trace.h>
#include <ssg_configuration.h>
#include <ssg_utils.h>
#include <ssg_dbc.h>
#include <iwf_transaction_manager.h>
#include <ual_config_mgnt.h>
#include "iwf.h"


// Constant declaration
#define MAX_NO_THREADS 20
#define DEF_NO_THREADS  5
#define MIN_NO_THREADS  1

// Namespaces
using namespace std;

// Class defination
class ThreadManager
{
    public:
        // Methods
        static ThreadManager* GetInstance();
        static void Destroy();
        void DispatchOnThread();
        void MapEventToThread(its::Event&); 
        void SetSessionId(string, ITS_CTXT);
        void DecreamentCount(int id);
        int GetIndex(int threadID);
        int GetThreadQueueCount(int);
    private:
        // Methods
        ThreadManager();
        ~ThreadManager();
        ThreadManager(const ThreadManager& obj) = default;
        ThreadManager& operator =(const ThreadManager& obj) = default;
        void PutEvent(its::Event&);

        // Member variables
        static ThreadManager* mSelfPtr;
        map <ITS_CTXT,ITS_UINT> mDlgThMap;
        ITS_USHORT mAvailThreadsList[MAX_NO_THREADS];
        int mIndex;
        map <string,ITS_CTXT> mSessionDlgMap;
        ITS_UINT mCurrThreadId;
        ITS_MUTEX mMutex;
        int mAppQueueCount[MAX_NO_THREADS];
        int mNumThreads;
};


#endif
