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
 * LOG: $Log: dcca_common.cpp,v $
 * LOG: Revision 3.4.46.1.8.2.2.1  2014/08/26 10:24:47  pramana
 * LOG: Logging related refinements
 * LOG:
 * LOG: Revision 3.4.46.1.8.2  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.4.46.1.8.1  2014/02/12 07:12:15  millayaraja
 * LOG: changes done for conditional compilation for IWF/DRE and IWF specific changes
 * LOG:
 * LOG: Revision 3.4.46.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.4.56.1  2013/08/12 13:08:13  jsarvesh
 * LOG: Overriding DCCA feature not to clear the Session and allow sending CCR-T in case of CCA-U with Error Code
 * LOG:
 * LOG: Revision 3.4  2011/01/11 08:46:50  rajeshak
 * LOG: DCCA Timeout issue fix(IWLAN)
 * LOG:
 * LOG: Revision 3.3  2009/01/07 13:44:04  rajeshak
 * LOG: Fix for KLOCK Work reported issues
 * LOG:
 * LOG: Revision 3.2  2008/12/12 18:06:08  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.7  2007/01/23 07:43:46  hbhatnagar
 * LOG: Fix for SendIndicationToApp:SessionIndex was missing
 * LOG:
 * LOG: Revision 2.6  2006/11/24 16:36:30  hbhatnagar
 * LOG: Made changes for SessionId as Key and corresponding changes
 * LOG:
 * LOG: Revision 2.5  2006/11/14 10:25:11  hbhatnagar
 * LOG: made changes for the error response and cleanup
 * LOG:
 * LOG: Revision 2.4  2006/11/13 06:37:07  hbhatnagar
 * LOG: done proper indentation and cleanup.
 * LOG:
 * LOG: Revision 2.3  2006/10/30 15:35:58  hbhatnagar
 * LOG: Changes for DCCA to work with ITSDEMO
 * LOG:
 * LOG: Revision 2.2  2006/10/26 14:45:57  hbhatnagar
 * LOG: made changes for BCGI in GetDccaEvent.( Hemant)
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.4  2006/09/27 09:26:30  hbhatnagar
 * LOG: Added support for bcgi namespace (badri)
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/25 08:45:51  nvijikumar
 * LOG: Converted file from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:36:37  nvijikumar
 * LOG: Enhanced the configuration function (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_common.cpp,v 3.4.46.1.8.2.2.1 2014/08/26 10:24:47 pramana Exp $
 * ID: $Id: dcca_common.cpp,v 3.4.46.1.8.2.2.1 2014/08/26 10:24:47 pramana Exp $
 *
 ****************************************************************************/

#include <its++.h>
#include <its_route.h>
#include <its_transports.h>
#include <dia_defines.h>
#include <dia_msg_router.h>
#include <dia_cmn.h>
#include <dia_utils.h>
#include <dcca_common.h>

#if defined (ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
#endif



/****************************************************************************
 *
 *  Purpose                : To get configuration information for this module
 *
 *  Input Parameters       : None
 *  
 *  Input/Output Parameters: tx   - The Tx timer value
 *                           tcc  - The Tcc timer value
 *                           ccfh - The CCFH value
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
DCCACommon::GetDCCAConf(
ITS_UINT *tx, ITS_UINT *tcc, ITS_UINT *ccfh, ITS_UINT *retainSession)
{
    char key[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];
    ITS_ResourceManager *rf = new
                 ITS_ResourceManager(APPL_GetConfigFileName());

    rf->Lock();
    rf->Rewind(NULL);

    while (rf->GetKeyName(NULL, key, ITS_PATH_MAX) == ITS_SUCCESS &&
           rf->GetKeyValue(NULL, value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (strcmp(key, "DccaTxTimerValue") == 0)
        {
            *tx = atoi(value);
        }

        if (strcmp(key, "DccaTccTimerValue") == 0)
        {
            *tcc = atoi(value);
        }

        if (strcmp(key, "DccaCcfhValue") == 0)
        {
            *ccfh = atoi(value);
        }
        if (strcmp(key, "DccaUpdateErrorAction") == 0)
        {
            *retainSession = atoi(value);
        }
    }
    rf->Unlock();

    delete rf;

    DCCA_TRACE_DEBUG((
    "DCCA: DCCACommon: GetDCCAConf: " \
    "Tx timer is: %d ...    Tcc timer is: %d ...", *tx, *tcc));

    return ITS_SUCCESS;
}

/****************************************************************************
 *
 *  Purpose                : To prepare DCCA_EVENT from diameter::Command
 *
 *  Input Parameters       : com - The command
 *  
 *  Input/Output Parameters: eve - The event
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
ITS_INT DCCACommon::GetDccaEvent( DIA_BASE_CMD *gCmd, DCCA_EVENT *eve)
{
    /**
     * SessionId
     */
    if(gCmd->getSessionId())
    {
        string s = gCmd->getSessionId()->value();
        //Fixed Copy to fixed size buffer
        strncpy((char *)eve->sessId, s.c_str(), SESSION_ID_LENGTH-1);
    }

    /**
     * Command-Code
     */
    eve->cmd = gCmd->getCommandCode();

    /**
     * Error command
     */
    //Warning Fix - suggest parentheses around assignment used as truth value
#if 0
    if( (eve->err = gCmd->isError()) != 0 )
    {    
       return ITS_SUCCESS; 
    }
#endif
    eve->err = gCmd->isError();
    return CcDecode(gCmd, eve);
}

/****************************************************************************
 *
 *  Purpose                : To send an indication to the application
 *
 *  Input Parameters       : IndFromStack - The indication
 *                           sessionIndex - The session index
 *                           appId        - The application id
 *  
 *  Input/Output Parameters: None
 *  
 *  Output Parameters      : None
 *  
 *  Return Value           : ITS_SUCCESS or !ITS_SUCCESS
 *  
 *  Notes                  : Change this. Change this.. Change this...
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-23    None          Created
 *  
 ****************************************************************************/

ITS_INT
DCCACommon::SendIndicationToApp(ITS_UINT IndFromStack, ITS_OCTET* sessId,
                    ITS_UINT appId, ITS_UINT sessIndx, ITS_UINT clientId)
{
    //give message to app if the node is active only
    ITS_NODE_STATE state;
    if ((ITS_GetNodeState(&state) == ITS_SUCCESS) &&
        state != ITS_STATE_PRIMARY)
    {
        return ITS_SUCCESS;
    }

    ITS_OCTET indic[MAX_INDIC_BUFF_LEN];
    memset(indic, 0, MAX_INDIC_BUFF_LEN);
    ITS_UINT indicLen = 0;
    ITS_USHORT dest;
    ITS_HDR hdr;
    ITS_EVENT ev;
    int index = 0;

    indic[indicLen++] = IndFromStack;

    int sessIdLen = strlen((const char*)sessId);

    if (sessIdLen > MAX_SESSION_ID_LEN)
    {
        sessIdLen = MAX_SESSION_ID_LEN;
    }

    strncpy((char*)&indic[indicLen], (const char*)sessId, sessIdLen);
    indicLen += sessIdLen;
    indic[indicLen++] = '\0';

    if (clientId)
    {
       ITS_EVENT_INIT(&ev, ITS_DIA_SRC, ITS_DIA_HDR_SIZE + indicLen + sizeof(ITS_UINT));
    }
    else
    {
       ITS_EVENT_INIT(&ev, ITS_DIA_SRC, ITS_DIA_HDR_SIZE + indicLen);
    }

    memset(&hdr, 0, sizeof(ITS_HDR));

    /* Set Msg Type */
    ev.data[index++] = ITS_DIA_MSG_TYPE_IND;

    /* Set Session Index */
    DIA_SET_INT(&ev.data[index], sessIndx);
    index += sizeof(ITS_UINT);

    /* Set Application Id */
    DIA_SET_INT(&ev.data[index], appId);
    index += sizeof(ITS_UINT);

    /* Now copy in the data  */
    if (indicLen)
    {
        memcpy(&ev.data[index], indic, indicLen);
        index += indicLen;
    }

    if (clientId)
    {
        DIA_SET_INT(&ev.data[index],clientId);
        index += sizeof(ITS_UINT);
    }

    hdr.type = ITS_DIAMETER;
    hdr.context.appId = appId;

    DCCA_TRACE_DEBUG(("DCCA::SendIndicationToApp:: AppId = %d, SessionIndex = %d",
             hdr.context.appId, sessIndx));

    if (itsDiaConfig.IsDistScenario())
    {
       /* It should be same as declared in IDS */
        dest = ITS_MAB_SRC;

        /* If Callback is registered from IDS No need of PutEvent */
        if (IDSMsgProcessCallBack != NULL)
        {
            IDSMsgProcessCallBack(&ev);
            ITS_EVENT_TERM(&ev);
            return DIA_SUCCESS;
        }
    }
    else
    {
        dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
    }

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        if (its::Transport::PutEvent(dest, &ev) == ITS_SUCCESS)
        {
            DCCA_TRACE_DEBUG(("DCCA: Sent Indication to Application = %d\n", dest));
            ITS_EVENT_TERM(&ev);
            return ITS_SUCCESS;
        }
    }
    else
    {
        DCCA_TRACE_ERROR(("DCCA: Incoming - No Route to Application\n"));
    }

    return !(ITS_SUCCESS);
}
