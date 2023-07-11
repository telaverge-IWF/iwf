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
 * LOG: $Log: dcca_module.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.3  2006/11/14 10:16:30  hbhatnagar
 * LOG: shifted the namespace to .cpp
 * LOG:
 * LOG: Revision 2.2  2006/11/13 06:52:02  hbhatnagar
 * LOG: removed the declartion of the MML from the module
 * LOG:
 * LOG: Revision 2.1  2006/10/25 06:44:55  hbhatnagar
 * LOG: Integration with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/25 08:28:09  nvijikumar
 * LOG: Converted the files from DOS 2 UNIX (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:22:17  nvijikumar
 * LOG: DCCA First Cut (badri)
 * LOG:
 *
 * ID: $Id: dcca_module.h,v 3.1 2008/03/31 10:33:30 nvijikumar Exp $
 *
 ****************************************************************************/

#ifndef DCCA_MODULE_H
#define DCCA_MODULE_H

/**
 * Includes
 */
#include <its++.h>
#include <dcca_trace.h>
#include <dia_module.h>
#include <dcca_fsm.h>
#include <dcca_stats.h>
#include <dcca_common.h>
#include <dcca_context.h>
#include <dcca_message_handler.h>

/****************************************************************************
 *
 *  Interface: DCCAModule Class
 *      
 *  Purpose  : To implement DCCA functionality
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *
 ****************************************************************************/
class DCCAModule : public DIAModule
{
public:
    /**
     * Constructor
     */
    DCCAModule();
    /**
     * Destructor
     */
    ~DCCAModule();
    /**
     * To handle DCCA message
     */
    ITS_INT HandleMessage(DCCA_EVENT*);

private:
    /**
     * Module objects
     */            
    DCCAFsm            *dccaFsm;
    DCCAStats          *dccaStats;
    DCCATrace          *dccaTrace;
    DCCAContextTable   *dccaContextTable;
    DCCAMessageHandler *dccaMessageHandler;
};

#endif
