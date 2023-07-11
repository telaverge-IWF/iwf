////////////////////////////////////C++-//////////////////////////////////////
//                                                                          // 
//   Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.      // 
//             Manufactured in the United States of America.                // 
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.      // 
//                                                                          // 
//   This product and related documentation is protected by copyright and   // 
//   distributed under licenses restricting its use, copying, distribution  // 
//   and decompilation.  No part of this product or related documentation   // 
//   may be reproduced in any form by any means without prior written       // 
//   authorization of IntelliNet Technologies and its licensors, if any.    // 
//                                                                          // 
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          // 
//  CONTRACT: INTERNAL                                                      // 
//                                                                          // 
//////////////////////////////////////////////////////////////////////////////
//
//  IPD
//
//
//  This file contains the engine initialization functions for the IPD.
//
/////////////////////////////////////////////////////////////////////////////
#include <its++.h>
#include <its.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>

#include <engine++.h>
#include <its_thread_pool.h>
#include <its_work_item.h>
#include <its_mutex.h>

#include <its_statics.cpp>

#include <app_trace.h>

#if defined(WIN32)
#define EXPORT  __declspec(dllexport)
#define IMPORT  __declspec(dllimport)
#else
#define EXPORT
#define IMPORT
#endif


#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

using namespace std;
using namespace its;
using namespace engine;
ITS_USHORT IVRTransportInst=0;
extern "C"
{

    EXPORT void TcapThreadFunction
                ( 
                ITS_ThreadPoolThread* thr, 
                ITS_HANDLE handle
                );

    EXPORT void TcapThreadFunction_ITU
                (
                ITS_ThreadPoolThread* thr, 
                ITS_HANDLE handle
                );

    extern "C" EXPORT ITS_USHORT RouteSS7
                                 (
                                 ITS_HDR *h, 
                                 ITS_EVENT *ev
                                 )
    {
	//refer to Engine Documentation
        cout << "Route SS7 executed "<<endl;
	return (ITS_DEFAULT_USER_SRC);
    }

    extern "C" EXPORT ITS_USHORT RouteAPP
                                 (
                                 ITS_HDR *h, 
                                 ITS_EVENT *ev
                                 )
    {
	//refer to Engine Documentation
        cout << "Route APP executed "<<endl;
	return (ITS_DEFAULT_USER_SRC);
    }

    extern "C" EXPORT void MyPreFuncold()
    {
    }

    extern "C" EXPORT void MyPreFunc()
    {
	//refer to Engine Documentation
        int res;
        ThreadPoolEntry thr;
        engine::Worker *eng;
        int appType=1;
	AppTrace::TraceApp::Initialize();
        APP_TRACE_DEBUG(("Inside Initialization, please wait..... " ));
        //Find IVR Transport

       static bool IVRTransportInstFound = false;
       if (!IVRTransportInstFound)
       {
           IVRTransportInstFound =true;
           for (unsigned short l=0;l<32000;l++)
           {
               TRANSPORT_Control *tc= TRANSPORT_FindTransport(l);
               if (tc != NULL && strcmp(tc->transport.name,"IVR")==0)
               {
	           APP_TRACE_DEBUG(("FOUND IVR TRANSPORT :    " ));
                   IVRTransportInst=l;
                   break;
               }
           }
        }       
	for ( int i=0; i<1; i++ )
	{
	    if ( workerPool!=NULL )
                  res=workerPool->GetFirstAvailThread(thr);
	    else
            {
	        cout << "worker pool is NULL" << endl;
	        APP_TRACE_DEBUG((" worker pool is NULL :    " ));
            }
            eng = reinterpret_cast<engine::Worker *>(thr.GetThread());

	    if ( eng == NULL )
                workerPool->ReturnToAvailThreads(thr);
	        workerPool->DispatchOnThread
                   (
                   thr, 
                   DISP_Dispatch_USER_CPP, 
                   (void *)eng->GetCallbackStruct()
                   );

	 }
    }
}
