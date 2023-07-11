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
 * LOG: $Log: dia_msghandler.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/10/05 11:53:11  yranade
 * LOG: ITS-Diameter specific updates. Removed cyclic dependency, move DiaThread
 * LOG: interface into it's own file.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/04/07 11:35:46  yranade
 * LOG: DoxyGen Compatible Code Comments.
 * LOG:
 * LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 * LOG: Building IMS Infrastructure
 * LOG:
 *
 * ID: $Id: dia_msghandler.h,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: dia_msghandler.h,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $"

#ifndef DIA_MSG_HANDLER_H
#define DIA_MSG_HANDLER_H

#include <iostream>

#include <dia_defines.h>
#include <dia_thread.h>

/** MessageHandler 
 *****************************************************************************
 *  Interface:
 *      Abstract Base Class MessageHandler 
 *      
 *  Purpose:
 *      
 *****************************************************************************/
class MessageHandler
{
public:
    /***********************************************************************/
    /** Purpose:
    *       Create a specific message handler class
    *       
    *  Input Parameters:
    *       src: Source for this handler
    *       
    ************************************************************************/
    MessageHandler(ITS_USHORT src)
        :handlerSrc(src){}

    /***********************************************************************/
    /** Purpose:
    *       Destruct a message handler
    ************************************************************************/
    virtual ~MessageHandler(){}
    
    /***********************************************************************/
    /** Purpose:
    *       Destruct a message handler
    *
    *  Return Value:
    *       src - Source for this handler
    ************************************************************************/
    ITS_USHORT GetMessageHandlerType()
    {
        return handlerSrc;
    }

    /***********************************************************************/
    /** Purpose:
    *       Pure Virtual Function HandleMessage
    *
    *  Return Value:
    *       Users have to implement this.
    ************************************************************************/    
    virtual int HandleMessage(DIAThread *thr, its::Event &ev) = 0;
    
protected:
    ITS_USHORT handlerSrc;
    
private:
    
};

#endif
