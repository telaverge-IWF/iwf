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

#include <its++.h>
#include <its.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>

#include <engine.h>
#include <its_thread_pool.h>
#include <its_work_item.h>
#include <its_mutex.h>

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif
extern "C"
{
    int main ( int argc, 
               const char **argv )
    {
        APPL_SetConfigDir("./");
	APPL_SetName("IPD");//Set the application name, and XML config file name
        APPL_SetConfigFileExtension("xml");
	APPL_GetConfigFileName();
        APPL_SetTraceDir("Trace/");
	ENGINE_Initialize(argc, argv, NULL, 0);//Initialize the Engine
	ENGINE_Run(argc, argv);//start the engine and buckle up.
        return EXIT_SUCCESS;

    }

}


