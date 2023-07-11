/*********************************-*HPP*-************************************
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
 * LOG: $Log: dia_gcs_handler.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/11/16 14:52:39  tpanda
 * LOG: New file added to handle Mulitcast mesg from GCS
 * LOG:
 * LOG:
 *
 * ID: $Id: dia_gcs_handler.h,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dia_gcs_handler.h,v 3.1 2008/03/31 10:33:31 nvijikumar Exp $"

#ifndef DIA_GCS_MSG_HANDLER_H
#define DIA_GCS_MSG_HANDLER_H

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_cmn.h>
#include <its_dia_config.h>

/*.Interface: DiaGcsMsgHandler 
 *****************************************************************************
 *  Interface:
 *      DiaGcsMsgHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from the Network 
 *****************************************************************************/
class DiaGcsMsgHandler:public MessageHandler
{
public:
    /*.implementation:public,inline,DiaGcsMsgHandler
    ************************************************************************
    *  Purpose:
    *       DiaGcsMsgHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaGcsMsgHandler ()
        :MessageHandler(DIA_GCS_CTX_INST){ }

    /*.implementation:public,inline,DiaGcsMsgHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaGcsMsgHandler
    *           
    ************************************************************************/
    ~DiaGcsMsgHandler(){}
    
    /*.implementation:public,DiaGcsMsgHandler
    ************************************************************************
    *  Purpose:
    *       Main Entry Function for processing Network messages
    *           
    ************************************************************************/
    int HandleMessage(DIAThread *thr, its::Event &ev);
    
private:
};

#endif
