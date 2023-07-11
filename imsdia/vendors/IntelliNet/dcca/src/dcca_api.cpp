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
 *
 * LOG: $Log: dcca_api.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.3  2007/01/23 07:43:46  hbhatnagar
 * LOG: Fix for SendIndicationToApp:SessionIndex was missing
 * LOG:
 *                                                                          *
 *
 * ID: $Id: dcca_api.cpp,v 3.1 2008/03/31 10:33:30 nvijikumar Exp $
 *
 ****************************************************************************
 */

#ident "$Id: dcca_api.cpp,v 3.1 2008/03/31 10:33:30 nvijikumar Exp $"

#include <dcca_conf.h>
#include <dcca_trace.h>
#include <dcca_stats.h>


/****************************************************************************
 *
 *  Purpose                : To print the Dcca module statistics  and used by
 *                           mml interface
 *
 *  Input Parameters       : reference to ostream object
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
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

void
DCCAApi::PrintDccaStats(std::ostream& os)
{
     DCCAStats::GetDCCAStats()->Print(os);
}


/****************************************************************************
 *
 *  Purpose                : To clear the Dcca module statistics and  used by
 *                           mml interface
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
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

void
DCCAApi::ClearDccaStats()
{
    DCCAStats::GetDCCAStats()->ResetAll();
}

/****************************************************************************
 *
 *  Purpose                : To enable the Dcca module trace and used by
 *                           mml interface
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
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

void
DCCAApi::EnableDccaTrace()
{
    DCCATrace::GetDCCATrace()->DCCAEnableTrace();
}

/****************************************************************************
 *
 *  Purpose                : To disable the Dcca module trace  and used by mml
 *                           interface
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
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

void 
DCCAApi::DisableDccaTrace()
{
    DCCATrace::GetDCCATrace()->DCCADisableTrace();
}

/****************************************************************************
 *
 *  Purpose                : To get the Tx timer value from Dcca module and 
 *                           used by mml interface
 *
 *  Input Parameters       : None
 *
 *  Input/Output Parameters: None
 *
 *  Output Parameters      : None
 *
 *  Return Value           : returns the Tx timer value in seconds.
 *
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

unsigned int
DCCAApi::GetTxTimer()
{
    unsigned int value = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
    return value;
}

/****************************************************************************
 *
 *  Purpose                : To set the Tx timer value in Dcca module and 
 *                           used by mml interface
 *
 *  Input Parameters       : Tx timer value in seconds
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
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

void
DCCAApi::SetTxTimer(unsigned int timerVal)
{
    DCCAConf::GetDCCAConf()->SetConf(DCCA_CONF_TX_TIMER, timerVal);
}

/****************************************************************************
 *
 *  Purpose                : To get the Tcc timer value from Dcca module and 
 *                           used by mml interface
 *
 *  Input Parameters       : None
 *
 *  Input/Output Parameters: None
 *
 *  Output Parameters      : None
 *
 *  Return Value           : returns the Tcc timer value in seconds.
 *
 *  Notes                  : None
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/

unsigned int
DCCAApi::GetTccTimer()
{
    unsigned int value = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TCC_TIMER);
    return value;
}

/****************************************************************************
 *
 *  Purpose                : To set the Tcc timer value in Dcca module and 
 *                           used by mml interface
 *
 *  Input Parameters       : Tcc timer value in seconds.
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
 * Hemant   2006-10-30    None          Created
 *
 ****************************************************************************/
void 
DCCAApi::SetTccTimer(unsigned int timerVal)
{
    DCCAConf::GetDCCAConf()->SetConf(DCCA_CONF_TCC_TIMER, timerVal);
}
