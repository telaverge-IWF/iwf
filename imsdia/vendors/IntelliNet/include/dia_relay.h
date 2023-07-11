/*********************************-*CPP*-************************************
 *                                                                          *
 *     Copyright 2008 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_relay.h,v $
 * LOG: Revision 1.2  2008/12/12 17:53:08  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 1.1  2008/12/07 09:55:17  rajeshak
 * LOG: Created new file to separate the functionality of relay
 * LOG:
 *
 * ID: $Id: dia_relay.h,v 1.2 2008/12/12 17:53:08 rajeshak Exp $
 ****************************************************************************/
#ident "$Id: dia_relay.h,v 1.2 2008/12/12 17:53:08 rajeshak Exp $"

#ifndef DIA_RELAY_H
#define DIA_RELAY_H

#include <dia_defines.h>
#include <dia_module.h>
#include <dia_cmn.h>
#include <dia_realm_table.h>
#include <dia_session_table.h>

/*.Interface: DiaRelayHandler 
 *****************************************************************************
 *  Interface:
 *      DiaRelayHandler Class
 *      
 *  Purpose:
 *      Handler Class that handles messages received from the Network 
 *****************************************************************************/
class DiaRelayHandler
{
public:
    /*.implementation:public,inline,DiaRelayHandler
    ************************************************************************
    *  Purpose:
    *       DiaRelayHandler Class Constructor.
    *       
    *       
    ************************************************************************/
    DiaRelayHandler () {}

    /*.implementation:public,inline,DiaRelayHandler
    ************************************************************************
    *  Purpose:
    *       Destruct DiaRelayHandler
    *           
    ************************************************************************/
    ~DiaRelayHandler(){}
    
    /*.implementation:public,DiaRelayHandler
    ************************************************************************
    *  Purpose:
    *       Main Entry Function for processing Network messages
    *           
    ************************************************************************/
    static int HandleReqMessage(ITS_USHORT trInst, 
                                DIA_BASE_CMD *&cmd, REALM_ENTRY *realm );

    static int HandleAnsMessage(DIA_BASE_CMD *&cmd, SESSION_ENTRY *ent);

     
private:
};

#endif
