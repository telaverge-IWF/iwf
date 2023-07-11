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
 * LOG: 
 * LOG:
 * LOG:
 *
 * ID: $Id: 
 *
 ****************************************************************************/

#include <dcca_conf.h>
#include <dcca_common.h>

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
static DCCAConf *dccaConf = NULL;

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
 *  Return Value           : DCCAConf*
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
DCCAConf* 
DCCAConf::GetDCCAConf()
{

    ITS_ASSERT(guard.Acquire() == ITS_SUCCESS);
    
    if (dccaConf == NULL)
    {
        dccaConf = new DCCAConf();
    }
    
    guard.Release();

    return dccaConf;
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
DCCAConf::DCCAConf()
{
    DCCACommon::GetDCCAConf(&tx, &tcc, &ccfh, &retainSession);

    if( tx == 0 )
    {
        tx = 10; /* Default 10 seconds */
    }

    if( tcc == 0 || tcc <= tx )
    {
        tcc = 30; /* Default 30 seconds */
    }

    if( ccfh > 2 )
    {
        ccfh = 0; /* Default TERMINATE */
    }
    if( retainSession == 0) /*Default to false clean session entry after error CCA-U received*/
    {
        retainSession = 0;
    }
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
DCCAConf::~DCCAConf()
{
    
}

/****************************************************************************
 *
 *  Purpose                : To get conf
 *
 *  Input Parameters       : which - The conf
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : The conf
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
ITS_UINT DCCAConf::GetConf(ITS_INT which)
{
    if( DCCA_CONF_CCFH == which )
    {    
        return ccfh;
    }
    else if( DCCA_CONF_TX_TIMER == which )
    {    
        return tx;
    }
    else if( DCCA_CONF_TCC_TIMER == which )
    {
        return tcc;
    }
    else if( DCCA_CONF_RETAIN_SESSION == which)
    {
        return retainSession;
    }
    return 0;
}

/****************************************************************************
 *
 *  Purpose                : To set conf
 *
 *  Input Parameters       : which - The conf
 *                           value - The value
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
void DCCAConf::SetConf(ITS_INT which, ITS_UINT value)
{
    if( DCCA_CONF_CCFH == which )
    {
        /**
         * You can not set this through conf !!
         */
    }
    else if( DCCA_CONF_TX_TIMER == which )
    {
        tx = value;
    }
    else if( DCCA_CONF_TCC_TIMER == which )
    {
        tcc = value;
    }
    else if( DCCA_CONF_RETAIN_SESSION == which )
    {
        retainSession = value;
    }
}

/****************************************************************************
 *
 *  Purpose                : To print the conf
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
void DCCAConf::Print(std::ostream& os) const
{
    os << "Tx Value  : " << tx   << " seconds" << endl;
    os << "Tcc Value : " << tcc  << " seconds" << endl;
    os << "CCFH Value: " << ccfh << endl;
}
