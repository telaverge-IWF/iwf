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

#include <its.h>
#include <its++.h>
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

#if defined(WIN32)
#define EXPORT  __declspec(dllexport)
#define IMPORT  __declspec(dllimport)
#else
#define EXPORT
#define IMPORT
#endif

#if !defined(HAVE_NAMESPACES)
# define(HAVE_NAMESPACES)
#endif

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif
//
using namespace std;
using namespace its;
using namespace engine;

extern "C"
{
    void TcapThreadFunction(ITS_ThreadPoolThread* thr, 
                                   ITS_HANDLE handle);

    void TcapThreadFunction_ITU(ITS_ThreadPoolThread* thr, 
                                       ITS_HANDLE handle);

    void 
    RouteSS7(){}

    void
    RouteAPP(){}

    void
    MyPreFunc()
    {
        ThreadPoolEntry thr;
        engine::Worker *eng;
        int appType=1;
        cout << "Inside MyPreFunc " << endl;
        workerPool->GetFirstAvailThread(thr);
        eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
        cout << endl;
        workerPool->DispatchOnThread(thr, TcapThreadFunction, (void *)0);
    }

    void
    TcapThreadFunction(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle)
    {
        TcapThreadFunction_ITU(thr, handle);
    }
}
