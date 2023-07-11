#include <engine++.h>
#include <its_types.h>
#include <sg_as.h>
#include <sua_sccp_test.h>
#include <iostream>

using namespace its;
using namespace std;

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
ASP_Main(its::ThreadPoolThread *thr)
{
    Worker *work = (Worker *)(thr);
    ITS_ASSERT(thr != NULL);
    ITS_TRACE_DEBUG(("Started ASP Mode\n"));

    do
    {
        menu();
    }
    while (!work->GetExit());

    return 0;
}

