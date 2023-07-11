/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 * 
 * LOG: $Log: dcca_module.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.3  2006/11/14 10:23:05  hbhatnagar
 * LOG: shifted the namespace here from corresponding .h file
 * LOG:
 * LOG: Revision 2.2  2006/11/13 06:47:18  hbhatnagar
 * LOG: Proper indentation and cleanup done
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:56  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.5  2006/09/27 05:59:36  hbhatnagar
 * LOG: Modified the creation of MML (badri)
 * LOG:
 * LOG: Revision 1.1.2.4  2006/09/26 11:29:21  nvijikumar
 * LOG: Creating MML object is deleted and so application has to create it (badri)
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:34:36  nvijikumar
 * LOG: Made the stat object creation as singleton (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_module.cpp,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <dcca_module.h>

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/****************************************************************************
 *
 *  Purpose                : Constructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/

DCCAModule::DCCAModule() : DIAModule(1, DIA_DCCA_MODULE_NAME, ITS_DCCA_SRC)
{
    
    /**
     * Trace 
     */
    dccaTrace = DCCATrace::GetDCCATrace();
    dccaTrace->DCCAEnableTrace();
    
    /**
     * Statistics
     */ 
    dccaStats = DCCAStats::GetDCCAStats();

    /**
     * Configuration
     */ 
    DCCAConf::GetDCCAConf();

     
    /**
     * Fsm
     */
    dccaFsm = new DCCAFsm();

    /**
     * Context
     */
    dccaContextTable = new DCCAContextTable();

    /**
     * Message handler 
     */
    dccaMessageHandler = new DCCAMessageHandler(dccaFsm, dccaContextTable);
    RegisterMessageHandler(
    dccaMessageHandler->DCCAGetMessageHandler(ITS_DIA_SRC), ITS_DIA_SRC);    
    RegisterMessageHandler(
    dccaMessageHandler->DCCAGetMessageHandler(ITS_TIMER_SRC), ITS_TIMER_SRC);
}

/****************************************************************************
 *
 *  Purpose                : Destructor
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : None
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
DCCAModule::~DCCAModule()
{    
    /**
     * Message handler
     */
    delete dccaMessageHandler;    
    dccaMessageHandler = NULL;
    
    /**
     * Context
     */
    delete dccaContextTable;
    dccaContextTable = NULL;

    /**
     * Fsm
     */
    delete dccaFsm;
    dccaFsm = NULL;

    /**
     * Statistics
     */
    delete dccaStats;
    dccaStats = NULL;

    /**
     * Trace
     */
    dccaTrace->DCCADisableTrace();
    delete dccaTrace;
    dccaTrace = NULL;
}

/****************************************************************************
 *
 *  Purpose                : To handle DCCA message
 *
 *  Input Parameters       : eve - DCCA_EVENT
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAModule::HandleMessage(DCCA_EVENT *eve)
{
    if(!eve->ind)
    {
        /**
         * Update statistics only if it is a command
         */
        if(eve->dir)
        {
            dccaStats->UpdateRecvStats(eve);
        }
        else
        {
            dccaStats->UpdateSendStats(eve);
        }
    }

    return dccaMessageHandler->HandleMessage(eve);
}
