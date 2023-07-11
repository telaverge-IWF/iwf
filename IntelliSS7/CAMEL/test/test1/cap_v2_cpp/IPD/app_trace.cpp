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

#include <app_trace.h>



namespace AppTrace 
{
    void TraceApp::Initialize()
    {
        its::TraceSubSystem::InitializeTrace();

        its::TraceSubSystem &trace = its::TraceSubSystem::GetTrace();
        trace.AddLevel(ITS_DEBUG_STRING,    engine::AppDebugTrace);
        trace.AddLevel(ITS_WARNING_STRING,  engine::AppWarningTrace);
        trace.AddLevel(ITS_ERROR_STRING,    engine::AppErrorTrace);
        trace.AddLevel(ITS_CRITICAL_STRING, engine::AppCriticalTrace);
    }

} // namespace AppTrace
