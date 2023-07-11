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
 * LOG: $Log: dcca_feature.cpp,v $
 * LOG: Revision 3.3.42.1.16.1  2014/10/27 08:28:37  pramana
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.3.42.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.3  2010/07/07 08:27:07  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.2  2008/12/12 18:06:08  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.13  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.10.2.2  2007/04/19 09:53:36  hbhatnagar
 * LOG: Dont remove context if Rc=2xxx (BCGI requirement)
 * LOG:
 * LOG: Revision 2.10.2.1  2007/03/15 18:30:42  hbhatnagar
 * LOG: Removed Duplicate Function call
 * LOG:
 * LOG: Revision 2.10  2007/02/21 13:00:17  hbhatnagar
 * LOG: made changes so that release indication should not be sent for already
 * LOG: released session ( for BCGI)
 * LOG:
 * LOG: Revision 2.9  2006/12/01 13:00:12  hbhatnagar
 * LOG: made changes for the correct error respose from peer
 * LOG:
 * LOG: Revision 2.8  2006/11/30 10:11:37  hbhatnagar
 * LOG: made changes for the error handling
 * LOG:
 * LOG: Revision 2.7  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.6  2006/11/14 10:23:05  hbhatnagar
 * LOG: shifted the namespace here from corresponding .h file
 * LOG:
 * LOG: Revision 2.5  2006/11/13 06:43:18  hbhatnagar
 * LOG: made changes so that the indication goes to DCCA module for AuthAppid 4
 * LOG:
 * LOG: Revision 2.4  2006/11/06 12:41:30  nvijikumar
 * LOG: 64 bit Compilation support ( Yogesh ).
 * LOG:
 * LOG: Revision 2.3  2006/10/31 08:38:32  hbhatnagar
 * LOG: Made changes for the BCGI.
 * LOG:
 * LOG: Revision 2.2  2006/10/30 15:35:58  hbhatnagar
 * LOG: Changes for DCCA to work with ITSDEMO
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/16 11:34:08  nvijikumar
 * LOG: Added DCCA licensing capability (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_feature.cpp,v 3.3.42.1.16.1 2014/10/27 08:28:37 pramana Exp $
 *
 ****************************************************************************/

/**
 * Includes
 */
#include <dia_cmn.h>
#include <its_license.h>
#include <dcca_module.h>
#include <dcca_common.h>
#include <dcca_feature.h>

/**
 * Global to this file
 */
static DCCAModule *dccaModule = NULL;

/**
 * Namespace
 */
#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/****************************************************************************
 *
 *  Purpose                : To access this feature
 *
 *  Input Parameters       : gCmd- The diameter Base Generic command
 *                           sin - The session index
 *                           dir - The direction
 *                           app - The application id
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAAccess(DIA_BASE_CMD *gCmd, ITS_UINT sin, ITS_UINT dir, ITS_UINT app)
{    
    DCCA_EVENT eve;
    memset(&eve, 0x00, sizeof(DCCA_EVENT));
    eve.sin = sin;
    eve.dir = dir;
    eve.app = app;

    if (gCmd == NULL)
    {
        DCCA_TRACE_ERROR(("Invalid Message Recieved"));
        if (eve.dir == 1)
            return ITS_DIA_UNABLE_TO_DELIVER;
        else
            return ITS_DIA_DCCA_ERROR;
    }

    ITS_UINT ret = DCCACommon::GetDccaEvent(gCmd, &eve);
    if (ret != ITS_SUCCESS)
        return ret;

    ITS_UINT retmod = dccaModule->HandleMessage(&eve); 
    if (retmod  == ITS_SUCCESS)
    {
        //Remove stack session , currently works only for BCGI
        int retval =  DCCAReleaseStackSession(&eve);
        /**
         * This check is to verify that DCCA_RELEASE_SESSION_IND should
         * not be sent on already released session. If the result code 
         * is not 2001 or 2002, send ITS_SUCCESS instead of indication (BCGI)  
         */
        if (retval == DCCA_RELEASE_SESSION_IND &&
            gCmd->getResultCode() &&
            (gCmd->getResultCode()->value() < DCCA_DIAMETER_SUCCESS_MIN_RANGE ||
             gCmd->getResultCode()->value() > DCCA_DIAMETER_SUCCESS_MAX_RANGE )) 
        {
           return ITS_SUCCESS;
        }
        else
        {
            return retval;
        }

    }
    else if (retmod == ITS_DIA_DCCA_ERROR && eve.dir == 1) 
    {
        return ITS_DIA_UNABLE_TO_DELIVER;
    }
    else
    {
        return retmod;
    }
}

/****************************************************************************
 *
 *  Purpose                : To access this feature with only indication
 *
 *  Input Parameters       : ind - The indication
 *                           sin - The session index
 *                           app - The application id
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAAccessInd(ITS_UINT ind, ITS_OCTET* sessionId, ITS_UINT app, ITS_UINT sessIdx = 0)
{
    if (sessionId == NULL)
    {
        DCCA_TRACE_ERROR(("Invalid Indication Recieved"));
        return ITS_DIA_DCCA_ERROR;
    }
 
    DCCA_EVENT eve;
    memset(&eve, 0x00, sizeof(DCCA_EVENT));

    //Correcting Copy into fixed size Buffer
    strncpy((char*)eve.sessId,(char*)sessionId, SESSION_ID_LENGTH-1);
    eve.ind = ind;
    eve.app = app;
    eve.sin = sessIdx;
    eve.dir = 1;

    if (app == DCCA_INTERFACE_APP_ID)
    {
        return dccaModule->HandleMessage(&eve);
    }
    
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To initialize this feature
 *
 *  Input Parameters       : objClass - This object
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
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/
ITS_INT
DCCAInitialize(ITS_Class objClass)
{    
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_DIA_DCCA))
    {
        return ITS_ENOLICENSE;
    }
    DCCAAccessFp    = DCCAAccess;
    DCCAAccessIndFp = DCCAAccessInd;
    dccaModule   = new DCCAModule();
    dccaModule->Start();
    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To terminate this feature
 *
 *  Input Parameters       : objClass - This object
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
void
DCCATerminate(ITS_Class objClass)
{    
    dccaModule->Stop();
    delete dccaModule;
    dccaModule   = NULL;
    DCCAAccessFp = NULL;
}

/**
 * DCCA feature class record
 */
ITSDLLAPI ITS_ClassRec itsDCCA_ClassRec =
{
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        DCCA_FEATURE_NAME,
        (ITS_ClassInitProc)DCCAInitialize,
        (ITS_ClassPartDestroyProc)DCCATerminate,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL
    }
};
ITSDLLAPI ITS_Class itsDCCA_Class = &itsDCCA_ClassRec;
