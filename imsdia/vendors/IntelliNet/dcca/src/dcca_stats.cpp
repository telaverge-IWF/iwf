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
 * LOG: $Log: dcca_stats.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.3  2006/11/14 10:23:05  hbhatnagar
 * LOG: shifted the namespace here from corresponding .h file
 * LOG:
 * LOG: Revision 2.2  2006/11/13 06:48:17  hbhatnagar
 * LOG: Proper indentation and cleanup
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:56  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:32:01  nvijikumar
 * LOG: Made the stat object as singleton (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_stats.cpp,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <dcca_stats.h>

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/**
 * Global to this file
 */
static its::ITS_Mutex guard(0);
static DCCAStats *dccaStats = NULL;

/****************************************************************************
 *
 *  Purpose                : Singleton
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : DCCAStats*
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
DCCAStats* 
DCCAStats::GetDCCAStats()
{

    ITS_ASSERT(guard.Acquire() == ITS_SUCCESS);
    
    if (dccaStats == NULL)
    {
        dccaStats = new DCCAStats();
    }
    
    guard.Release();

    return dccaStats;
}

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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAStats::DCCAStats()
{
    Lock();
    
    numCCRSent           = 0;
    numCCASent           = 0;
    numCCRRecv           = 0;
    numCCARecv           = 0;
    numActiveSessions    = 0;

    Unlock();
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
DCCAStats::~DCCAStats()
{
    Lock();
    
    numCCRSent           = 0;
    numCCASent           = 0;
    numCCRRecv           = 0;
    numCCARecv           = 0;
    numActiveSessions    = 0;

    Unlock();
}

/****************************************************************************
 *
 *  Purpose                : To reset the statistics
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAStats::ResetAll()
{
    Lock();
    
    numCCRSent = 0;
    numCCASent = 0;
    numCCRRecv = 0;
    numCCARecv = 0;

    Unlock();
}

/****************************************************************************
 *
 *  Purpose                : To update the send statistics
 *
 *  Input Parameters       : eve - The event
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAStats::UpdateSendStats(DCCA_EVENT *eve)
{
    Lock();
    
    if( eve->req && eve->cmd == DCCA_COMMAND_CCR )
    {
        numCCRSent++;
    }

    else if( !eve->req && eve->cmd == DCCA_COMMAND_CCA )
    {
        numCCASent++;
    }

    Unlock();
}

/****************************************************************************
 *
 *  Purpose                : To update the recv statistics
 *
 *  Input Parameters       : eve - The event
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAStats::UpdateRecvStats(DCCA_EVENT *eve)
{
    Lock();
    
    if( eve->req && eve->cmd == DCCA_COMMAND_CCR )
    {
        numCCRRecv++;
    }

    else if( !eve->req && eve->cmd == DCCA_COMMAND_CCA )
    {
        numCCARecv++;
    }

    Unlock();
}

/****************************************************************************
 *
 *  Purpose                : To print the statistics
 *
 *  Input Parameters       : os - The stream
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAStats::Print(std::ostream& os) const
{
     Lock();

     os << "Num of CCR sent       : " << numCCRSent << endl;
     os << "Num of CCR recv       : " << numCCRRecv << endl;
     os << "Num of CCA sent       : " << numCCASent << endl;
     os << "Num of CCA recv       : " << numCCARecv << endl;
     os << "Num of Active Sessions: " << numActiveSessions << endl;

     Unlock();
}


/****************************************************************************
 *
 *  Purpose                : Add to active session
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAStats::AddToActiveSession()
{
    Lock();
    
    numActiveSessions++;

    Unlock();
}

/****************************************************************************
 *
 *  Purpose                : Remove from active session
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
void DCCAStats::RemoveFromActiveSession()
{
    Lock();

    numActiveSessions--;

    Unlock();
}
