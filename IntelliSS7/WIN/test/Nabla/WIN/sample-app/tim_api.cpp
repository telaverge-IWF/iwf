////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT:  TCAP Interface Module                                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: tim_api.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
// LOG: $Log: tim_api.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 1.2  2003/03/28 21:12:49  rsonak
// LOG: Copied from PR6.1
// LOG:
// LOG: Revision 1.1.2.1  2002/09/26 17:54:10  pmandal
// LOG: simulators for WIN messages
// LOG:
// LOG: Revision 1.1.2.3  2002/09/23 16:47:21  ngoel
// LOG: add semaphore to sync initialization
// LOG:
// LOG: Revision 1.1.2.2  2002/09/23 16:22:30  ngoel
// LOG: add comments
// LOG:
// LOG: Revision 1.1.2.1  2002/09/23 15:51:47  pmandal
// LOG: Commit send/receive code
// LOG:
// LOG: Revision 1.1.2.2  2002/09/20 13:17:26  ngoel
// LOG: removed warning
// LOG:
// LOG: Revision 1.1.2.1  2002/09/19 17:36:36  ngoel
// LOG: TCAP Interface Module
// LOG:
// LOG:
// LOG:
//
////////////////////////////////////////////////////////////////////////////////
//

#include <engine++.h>
#include <engine.h>
#include <tim_api.h>
#include <tcap++.h>
#include <Asn.h>
#include <app_dbc.h>
#if defined(GW_TRANSPORT)
#include <GWTransport.h>
#endif
#include <its_semaphore.h>

using namespace std;
using namespace its;

static ITS_THREAD t;
static int argc;
static char **argv;

#define QUEUE_ID   10
TaskQueueTransport *timRcvQueue; 
int opc;
int dpc;
int ossn;
int dssn;
int gwpc;
char gwip1[20];
char gwip2[20];
char gwip3[20];
char gwip4[20];
static Semaphore sem(0);

extern "C" void TIMConnectToISG(ITS_ResourceManager *rf);



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will initialize and start Accelero middleware. 
 *
 *  Input Parameters:
 *      None 
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
 *
 ****************************************************************************/
void *
EngineStart(void *arg)
{
    ENGINE_Initialize(argc, (const char **)argv, NULL, 0);

    /* Need to create APPDbcServer Object for MML Functionality */
    APPDbcServer    appDbcServer("Application MML Console");

    ENGINE_Run(argc, (const char **)argv);
    return NULL;

}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is the heart of initialization procedure to be called by
 *      tnetix Application.
 *
 *  Input Parameters:
 *      argc - number of command line arguments
 *      argv - command line arguments
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if no failure has occurred.
 *      Otherwise EINITFAIL is reported. 
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
TIM_Api::Initialize(int arg1, char** arg2)
{

    argc = arg1;
    argv = arg2;
    THREAD_CreateThread(&t, 0, EngineStart, NULL, ITS_TRUE);

    /* Wait until PreFunc posts the semaphore */
    sem.Wait();


    return ITS_SUCCESS;

}
 
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will terminate the TIM Api class. 
 *
 *  Input Parameters:
 *      None 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is always returned.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int 
TIM_Api::Terminate()
{
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is TIM engine pre function. This function is specified 
 *  as a callback in xml configuration file. Here application specific
 *  configuration is read and application receive queue is created. Application 
 *  receives all incomminfg TCAP messages in this queue.
 *
 *  Input Parameters:
 *      None 
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
 *
 ****************************************************************************/
extern "C" void
TIMPreFunc()
{
    string value;

    ITS_ResourceManager *rf = new ITS_ResourceManager(APPL_GetConfigFileName());

    if (rf->GetKeyValueOf("", "LOCAL_PC", value) == ITS_SUCCESS)
    {
        opc = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "REMOTE_PC", value) == ITS_SUCCESS)
    {
        dpc = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "LOCAL_SSN", value) == ITS_SUCCESS)
    {
        ossn = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "REMOTE_SSN", value) == ITS_SUCCESS)
    {
        dssn = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "GW_PC", value) == ITS_SUCCESS)
    {
        gwpc = atoi(value.c_str());
    }

    if (rf->GetKeyValueOf("", "GW_IP1", value) == ITS_SUCCESS)
    {
        strcpy(gwip1, value.c_str());
    }
    else
    {
        strcpy(gwip1, "0.0.0.0");
    }

    if (rf->GetKeyValueOf("", "GW_IP2", value) == ITS_SUCCESS)
    {
        strcpy(gwip2, value.c_str());
    }
    else
    {
        strcpy(gwip2, "0.0.0.0");
    }

    if (rf->GetKeyValueOf("", "GW_IP3", value) == ITS_SUCCESS)
    {
        strcpy(gwip3, value.c_str());
    }
    else
    {
        strcpy(gwip3, "0.0.0.0");
    }

    if (rf->GetKeyValueOf("", "GW_IP4", value) == ITS_SUCCESS)
    {
        strcpy(gwip4, value.c_str());
    }
    else
    {
        strcpy(gwip4, "0.0.0.0");
    }

    timRcvQueue = new TaskQueueTransport("TIM Receive Queue", 
                                          QUEUE_ID, 
                                          ITS_TRANSPORT_TQUEUE);

   /* Post the semaphore to free Initialization API */
   sem.Post();
    

} 


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function is default application selector. This function is 
 * specified as application routing callback in application xml file. This 
 * function returns instance of receive queue so that all incoming application 
 * messages could be sent to this queue.
 *
 *  Input Parameters:
 *      None 
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
 *
 ****************************************************************************/
extern "C" ITS_USHORT 
RouteAPP(ITS_HDR *hdr, ITS_EVENT *event)
{
    return timRcvQueue->GetInstance();
}



