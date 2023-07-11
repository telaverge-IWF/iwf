/**************************-*-Dia-*-*****************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *
 *  ID: $Id: app_common.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $
 *
 *  LOG: $Log: app_common.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 *  LOG: Baseline ITS Demo.
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.9  2006/07/02 12:15:32  yranade
 *  LOG: Minor Enhancements
 *  LOG:
 *  LOG: Revision 1.8  2006/07/01 15:33:58  yranade
 *  LOG: Slight changes for tweaking performance.
 *  LOG:
 *  LOG: Revision 1.7  2006/06/07 07:28:22  yranade
 *  LOG: Compile with CC Compiler.
 *  LOG:
 *  LOG: Revision 1.6  2006/06/06 14:32:43  tpanda
 *  LOG: Handle Error Response
 *  LOG:
 *  LOG: Revision 1.5  2006/04/28 10:51:39  yranade
 *  LOG: Fix small issue in generating traffic.
 *  LOG:
 *  LOG: Revision 1.4  2006/04/25 14:09:57  adsouza
 *  LOG: Updated MsgDump File Name.
 *  LOG:
 *  LOG: Revision 1.3  2006/04/25 14:07:30  adsouza
 *  LOG: 1. Code Enhancements (Added Comments, Flowerboxes)
 *  LOG: 2. Method to Inject Hex Dumps
 *  LOG:
 *  LOG: Revision 1.1  2006/04/17 16:06:46  yranade
 *  LOG: Implementation of some common functions.
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: app_common.cpp,v 3.1 2008/03/31 10:33:26 nvijikumar Exp $"

#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>

#include <app.h>
#include <app_stats.h>
#include <diameter/base/NONPROXYABLEERROR.h>
#include <diameter/base/PROXYABLEERROR.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace base;
#endif

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function actually sends the Command to the base 
 *      diameter stack.
 *
 *  Input Parameters:
 *      impl - type CommandImpl.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success returns ITS_SUCCESS.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SendToStack(Command* impl)
{
    int ret;

    ITS_BOOLEAN isReq = impl->isRequest() ? ITS_TRUE:ITS_FALSE;
    int commandCode = impl->getCommandCode();

    /* 
     * Access the diameter stack HANDLE  
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        /* 
         * Using the diameter stack HANDLE: aka DiaFrame
         * send the Command to the Diameter Stack. 
         * Update application statistics
         */

        ret = diaFrame->Send(impl);

        if (ret != ITS_SUCCESS)
        {
           APP_TRACE_CRITICAL(("Send Failure %d\n", ret));

           return ret;
        }
    }

    APPStats::GetAPPStats()->UpdateSendStats(commandCode, isReq);

    return ITS_SUCCESS;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function generates the load for the diameter
 *      stack during the load testing. If the appMode is set to 
 *      LOAD_TEST, this function is called.
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
 *      On success returns ITS_SUCCESS.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int GenerateLoad()
{
    static int count = 0;
    time_t    tx;
    struct tm tbuf, *temp;
    char buff[80];


    while (true)
    {
        if (APPStats::sendTraffic)
        {
            /*
             * Generate a burst of traffic of burstsize
             */
            for (int i = 0; i < APPStats::burstSize; i++)
            {
                if (TrafficGeneratorFunc == NULL)
                {
                    APP_TRACE_ERROR(("Traffic Generator Func Not Set"));

                    return (!ITS_SUCCESS);
                }

                (*TrafficGeneratorFunc)();
            }

            /*
             * Sleep for the duration as specified in slpTime
             * Duration Provided should be in milliseconds
             */
            ftime(&APPStats::current);
            TIMERS_USleep(APPStats::slpTime * 1000);

            /*
             * If the traffic duration (seconds) expires, update the stats
             */
            if ((APPStats::current.time - APPStats::starter.time) >=
                 APPStats::duration)
            {
                if (APPStats::firstTime)
                {
                    ftime(&APPStats::sendComplete);
                    APPStats::sendTraffic = ITS_FALSE;
                    APPStats::firstTime = false;
                    time(&tx);
                    temp = localtime_r(&tx, &tbuf);
                    strftime(buff, 80, "[ %b%d %Y %H:%M:%S  ]" , &tbuf);
                    cout << "Test stopped sending traffic at ----->"
                         << buff << endl;
               }
           }
       }
       else
           TIMERS_Sleep(1);
   }
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function converts the string into the Hex value.
 *
 *  Input Parameters:
 *      char *octet: String containing the Hexa value
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the ITS_OCTET which contains the Hexa value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static
ITS_OCTET GetHexValue(char *octet)
{
    int i;
    ITS_OCTET val = 0;
    int len = strlen(octet);
    int incr = 1;

    for (i=len-1; i >= 0; i--, incr=incr*16)
    {
        if(isdigit(octet[i]))
        {
            val = val + (octet[i] - 48)*incr;
        }
        else if (tolower(octet[i]) == 'a')
        {
            val = val + 10*incr;
        }
        else if (tolower(octet[i]) == 'b')
        {
            val = val + 11*incr;
        }
        else if (tolower(octet[i]) == 'c')
        {
            val = val + 12*incr;
        }
        else if (tolower(octet[i]) == 'd')
        {
            val = val + 13*incr;
        }
        else if (tolower(octet[i]) == 'e')
        {
            val = val + 14*incr;
        }
        else if (tolower(octet[i]) == 'f')
        {
            val = val + 15*incr;
        }
    }

    return val;
}

/*
 * Holds the message in the dump;
 */
ITS_OCTET msg[1024];

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function reads the dump from dump.txt and creates the
 *      Message.
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
 *      Returns the size of the dump
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int ReadDump()
{
    FILE *fp;
    int size = 0;
    char escape;
    char word[256];

    memset(msg, sizeof(msg), 0);

    fp = fopen("MsgDump.txt", "r");

    if (NULL == fp)
    {
        APP_TRACE_ERROR(("Unable to open file : MsgDump.txt"));
        return -1;
    }
    else
    {
        while(fscanf(fp, "%s", word) != EOF)
        {
            if(word[0] == '#')
            {
                do
                {
                    escape = fgetc(fp);
                }
                while (escape != '\n');
                continue;
            }
            msg[size++] = GetHexValue(word);
        }
    }

    return size;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the message to the stack as a dump.
 *      Dump should be in the file dump.txt in the current folder.
 *
 *  Input Parameters:
 *      ITS_USHORT inst: Application Thread Instance
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void InjectDump(ITS_USHORT inst)
{
    Event ev;
    int len;
    int i;

    ev.SetSource(ITS_DIA_SRC);

    if ((len = ReadDump()) <= 0)
    {
        APP_TRACE_ERROR(("Invalid Buffer in File"));
        return;
    }

    ev.SetData(msg, len);

    its::Transport::PutEvent(inst, ev);

}
/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *
 *         Utility function to handle error responses
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Error response
 *      Command
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

int HandleErrorResponse(const diameter::CommandImpl *impl)
{
    APP_TRACE_DEBUG(("Error Answers Received"));
    if(impl->isProxyable())
    {
       PROXYABLEERROR err(*impl);
       cout<<endl<<err<<endl;
    }
    else
    {
       NONPROXYABLEERROR err(*impl);
       cout<<endl<<err<<endl;
    }

    return (ITS_SUCCESS);
}

