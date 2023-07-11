#ifndef _STATISTICS_H_
#define _STATISTICS_H_
#include<Sync.h>
namespace eAccelero {

extern __thread uint32_t StatsIndex;

//Currently hard-coding to 32. Can be increased later if required.
#define EACC_MAX_THREADS 32

 class Statistics {

     public:
         Statistics();
         ~Statistics() { }
         uint32_t getNewThreadIndex();

     private:
         Mutex tIndexMutex;
         static uint32_t globalStatsIndex;
 };

extern Statistics statistics;
};//namespace eAccelero

#endif
