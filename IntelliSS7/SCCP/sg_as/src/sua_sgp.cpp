#include <engine++.h>
#include <its_trace.h>
#include <sg_as.h>
#include <sua_sccp_test.h>

#include <iostream>

using namespace its;
using namespace std;

#if 0
ITS_INT 
SGP_BorderNextEvent(its::ThreadPoolThread * thr, its::Event &event)
{
    return ITS_PutEvent(1, event);
}
#endif

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT 
SGP_Main(its::ThreadPoolThread *thr)
{
    Worker *work = (Worker *)(thr);
    ITS_ASSERT(thr != NULL);
    ITS_TRACE_EVENT(("Started SGP Mode\n"));

    do
    {
        menu();
    }
    while (!work->GetExit());

    return 0;
}

