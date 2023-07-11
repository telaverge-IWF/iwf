#include "stdint.h"
#include "Sync.h"
#include "Statistics.h"
#include "GenericStatsCounter.h"
#include "MsgStatsCounter.h"

    /**
     * Global Variables to assign the ThreadIndex index
     **/

namespace eAccelero {


    Statistics statistics;

    uint32_t Statistics::globalStatsIndex;

    __thread uint32_t StatsIndex;
    Statistics::Statistics()
    {
        globalStatsIndex = 0;
    }

    uint32_t Statistics::getNewThreadIndex()
    {
        //Lock the global variable
        Mutex::ScopedMutex sMutex(tIndexMutex);
        uint32_t tempIndex = globalStatsIndex;
        globalStatsIndex++;
        sMutex.unlock();
        //return the local copy
        return tempIndex;
    }

    //This method collates all threads specific stats and returns total stats.
    uint64_t collateStats(GenericStatsCounter *stats)
    {
        int index = 0;
        uint64_t totalCount = 0;

        for(;(index < EACC_MAX_THREADS);index++)
        {
            totalCount = totalCount + stats[index].GetCount();
        }

        return totalCount;
    }


    //Reset all thread specific counters
    void ResetGenericStatsCounter(GenericStatsCounter *stats)
    {
        int index = 0;
        for(;(index < EACC_MAX_THREADS);index++)
        {
            stats[index].Reset();
        }
    }

    //Reset all thread specific counters for MsgStatsCounter.
    void ResetMsgStatsCounter(MsgStatsCounter *stats)
    {
        int index = 0;
        for(;(index < EACC_MAX_THREADS);index++)
        {
            stats[index].Reset();
        }
    }
    //This method collates all threads specific stats and returns total
    //stats for MsgStatsCounter.
    MsgStatsCounter collateMsgStatsCounter(MsgStatsCounter *stats)
    {
        MsgStatsCounter msgCounter;
        int index = 0;
        msgCounter.rxReqCount =0;
        msgCounter.rxRspCount =0;
        msgCounter.txReqCount =0;
        msgCounter.txRspCount =0;


        for(;(index < EACC_MAX_THREADS);index++)
        {
            msgCounter.rxReqCount = msgCounter.rxReqCount + stats[index].rxReqCount;
            msgCounter.rxRspCount = msgCounter.rxRspCount + stats[index].rxRspCount;
            msgCounter.txReqCount = msgCounter.txReqCount + stats[index].txReqCount;
            msgCounter.txRspCount = msgCounter.txRspCount + stats[index].txRspCount;
        }
        return msgCounter;
    }

};//namespace eAccelero
