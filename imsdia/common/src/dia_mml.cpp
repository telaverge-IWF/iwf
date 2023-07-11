/*********************************-*-CDIA-*-**********************************
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
 *  ID: $Id: dia_mml.cpp,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $
 *
 *  LOG: $Log: dia_mml.cpp,v $
 *  LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.3  2006/06/21 10:41:27  nvijikumar
 *  LOG: Modification for Copyright info.
 *  LOG:
 *  LOG: Revision 1.2  2006/04/13 18:06:18  yranade
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 *  LOG: Building IMS Infrastructure
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id: dia_mml.cpp,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $"

#include <its++.h>
#include <its_route.h>
#include <its_thread_pool.h>
#include <its_support_exception.h>

#include <engine++.h>

#include <dia_trace.h>
#include <dia_mml.h>
#include <dia_config.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
void
DiaMMLServer::DoCommand(istream& commandLine)
{
    string dummy;

    if (Cmd("disTraces", "Disable ALL Dia Tracing"))
    {
        diaDebugTrace->Disable();
        diaWarningTrace->Disable();
        diaErrorTrace->Disable();
        diaCriticalTrace->Disable();
    }
    else if (Cmd("enTraces", "Enable ALL Dia Tracing"))
    {
        diaDebugTrace->Enable();
        diaWarningTrace->Enable();
        diaErrorTrace->Enable();
        diaCriticalTrace->Enable();
    }
    else if (Cmd("enCriticalTraces", "Enable Dia Critical Traces"))
    {
        diaCriticalTrace->Enable();
    }
    else if (Cmd("enErrorTraces", "Enable Dia Error Traces"))
    {
        diaErrorTrace->Enable();
    }
    else if (Cmd("enWarningTraces", "Enable Dia Warning Traces"))
    {
        diaWarningTrace->Enable();
    }
    else if (Cmd("enDebugTraces", "Enable Dia Debug Traces"))
    {
        diaDebugTrace->Enable();
    }
    else if (Cmd("disCriticalTraces", "Disable Dia Critical Traces"))
    {
        diaCriticalTrace->Disable();
    }
    else if (Cmd("disErrorTraces", "Disable Dia Error Traces"))
    {
        diaErrorTrace->Disable();
    }
    else if (Cmd("disWarningTraces", "Disable Dia Warning Traces"))
    {
        diaWarningTrace->Disable();
    }
    else if (Cmd("disDebugTraces", "Disable Dia Debug Traces"))
    {
        diaDebugTrace->Disable();
    }
}

