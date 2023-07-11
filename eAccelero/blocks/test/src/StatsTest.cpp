#include <pthread.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "Sync.h"
#include "Statistics.h"
#include "GenericStatsCounter.h"
#include "MsgStatsCounter.h"

using namespace eAccelero;

#define NUM_THREADS 10

static GenericStatsCounter count[NUM_THREADS];

Statistics *stats = new Statistics();

void* threadfun(void *args)
{
    StatsIndex = stats->getNewThreadIndex(); 
    printf("Thread index set is %d\n",StatsIndex);
    printf("Child thread id is %u\n",pthread_self());
    //Waiting
    while(1)
    {
        sleep(1);
        count[StatsIndex].Increment();
        printf("Incrementing Counter with index %d,Value after increment is %lu\n",StatsIndex,count[StatsIndex].GetCount());
    }

    return NULL;
}


int main()
{

    printf("Main's thread id is %u\n",pthread_self());
    int i =0;
    pthread_t t;

    //stats = new Statistics();

    for(i=0; i < NUM_THREADS; i++)
    {
            pthread_create(&t,NULL,threadfun,NULL);
    }
    while(1)
    {
        sleep(10);
        printf("Statistics value is %ld\n",collateStats(count));
    }

}
