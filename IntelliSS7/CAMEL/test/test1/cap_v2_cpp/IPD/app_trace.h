/////////////////////////////////-*-C++-*-////////////////////////////////////
//                                                                          //
//   Copyright 1997-2001 IntelliNet Technologies, Inc. All Rights Reserved. //
//             Manufactured in the United States of America.                //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
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
// CONTRACT: Internal //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
#ifndef APP_TRACE_H
#define APP_TRACE_H

#include <its++.h>
#include <its_trace.h>
#include <engine++.h>



#define APP_TRACE_DEBUG(x) ITS_TRACE(ITS_DEBUG_STRING, x)
#define APP_TRACE_WARNING(x) ITS_TRACE(ITS_WARNING_STRING, x)
#define APP_TRACE_ERROR(x) ITS_TRACE(ITS_ERROR_STRING, x)
#define APP_TRACE_CRITICAL(x) ITS_TRACE(ITS_CRITICAL_STRING, x)



namespace AppTrace 
{
    class TraceApp
    {
        public:
            //
            // Initializes the IntelliSS7 trace subsystem. 
            // This method must be called
            // from the main function before the trace subsystem is used.
            //
    	    static void Initialize();
   };

} // namespace AppTrace
#endif  APP_TRACE_H

