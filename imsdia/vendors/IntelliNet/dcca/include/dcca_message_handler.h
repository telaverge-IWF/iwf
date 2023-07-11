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
 * LOG: $Log: dcca_message_handler.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:30  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/11/24 16:28:04  hbhatnagar
 * LOG: made changes for the key as Session Index and proper indentation done
 * LOG:
 * LOG: Revision 2.2  2006/11/14 10:15:46  hbhatnagar
 * LOG: shifted namespaces to .cpp
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
 * ID: $Id: dcca_message_handler.h,v 3.1 2008/03/31 10:33:30 nvijikumar Exp $
 *
 ****************************************************************************/

#ifndef DCCA_MESSAGE_HANDLER_H
#define DCCA_MESSAGE_HANDLER_H

/**
 * Includes
 */
#include <its++.h>
#include <dia_msghandler.h>
#include <dcca_fsm.h>
#include <dcca_conf.h>
#include <dcca_common.h>
#include <dcca_context.h>

/****************************************************************************
 *
 *  Interface: DCCADiaMessageHandler Class
 *      
 *  Purpose  : To implement DCCA DIA message handling
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *
 ****************************************************************************/
class DCCADiaMessageHandler : public MessageHandler
{
public:
    /**
     * Constructor
     */
    DCCADiaMessageHandler(DCCAFsm*, DCCAContextTable*);
    /**
     * Destructor
     */
    ~DCCADiaMessageHandler();
    /**
     * To handle DIA message
     */
    ITS_INT HandleMessage(DIAThread *thr, its::Event &ev);    

private:
    /**
     * Used objects
     */
    DCCAFsm          *dccaFsm;
    DCCAContextTable *dccaContextTable;
    /**
     * Supported message handling functions
     */
    ITS_INT ERRMessageHandling(DCCA_EVENT*);
    ITS_INT CCRMessageHandling(DCCA_EVENT*);
    ITS_INT CCAMessageHandling(DCCA_EVENT*);
    ITS_INT AARMessageHandling(DCCA_EVENT*);
    ITS_INT AAAMessageHandling(DCCA_EVENT*);
    ITS_INT IndicationMessageHandling(DCCA_EVENT*);
    ITS_INT SessionTerminationMessageHandling(DCCA_EVENT*);
};

/****************************************************************************
 *
 *  Interface: DCCATimerMessageHandler Class
 *      
 *  Purpose  : To implement DCCA timer message handling
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *
 ****************************************************************************/
class DCCATimerMessageHandler : public MessageHandler
{
public:
    /**
     * Constructor
     */
    DCCATimerMessageHandler(DCCAFsm*, DCCAContextTable*);
    /**
     * Destructor
     */
    ~DCCATimerMessageHandler();
    /**
     * To handle timer message
     */
     ITS_INT HandleMessage(DIAThread *thr, its::Event &ev);

private:
    /**
     * Used objects
     */
    DCCAFsm          *dccaFsm;
    DCCAContextTable *dccaContextTable;
};

/****************************************************************************
 *
 *  Interface: DCCAMessageHandler Class
 *      
 *  Purpose  : To implement DCCA message handling
 *
 * --------------------------------------------------------------------------
 * Name      Date          Reference     Description
 * --------------------------------------------------------------------------
 *
 * badri     2006-08-22    None          Created
 *
 ****************************************************************************/
class DCCAMessageHandler
{
public:

    /**
     * Constructor
     */
    DCCAMessageHandler(DCCAFsm*, DCCAContextTable*);
    /**
     * Destructor
     */
    ~DCCAMessageHandler();        
    /**
     * To handle DCCA message
     */
    ITS_INT HandleMessage(DCCA_EVENT*);
    /**
     * Get message handler
     */
    MessageHandler* DCCAGetMessageHandler(ITS_USHORT);
    
private:        
    /**
     * Message handler objects
     */
    DCCADiaMessageHandler   *dccaDiaMessageHandler;
    DCCATimerMessageHandler *dccaTimerMessageHandler;        
};

#endif
