#include <its.h>
#include <its_object.h>
#include <its_timers.h>

ITS_Class itsSS7STANDALONE_Class;

ITS_TIME
TIMERS_Time()
{
    return time(NULL);
}
