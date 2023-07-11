/**************************-*-Dia-*-*****************************************
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
 * LOG: $Log: app_mml.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:23  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/04/25 15:20:01  nvijikumar
 * LOG: Code Enhancement (Flowerboxes)
 * LOG:
 * LOG: Revision 1.1  2006/04/17 16:04:43  yranade
 * LOG: MML Server Support.
 * LOG:
 *
 * ID: $Id: app_mml.h,v 3.1 2008/03/31 10:33:23 nvijikumar Exp $
 ****************************************************************************/

#if !defined(_APP_DBC_H_)
#define _APP_DBC_H_

#include <dia_mml.h>

class APPMMLServer: public DiaMMLServer
{
public:

   /*  implementation: public
    ****************************************************************************
    *  Purpose: Constructor
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None
    *
    *  Notes:
    *
    *  See Also:
    ****************************************************************************/
    APPMMLServer(const std::string& nameParam)
        : DiaMMLServer(nameParam)
    {};

   /*  implementation: public
    ****************************************************************************
    *  Purpose: Destructor
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None
    *
    *  Notes:
    *
    *  See Also:
    ****************************************************************************/
    virtual ~APPMMLServer()
    {};

   /*  implementation: public
    ****************************************************************************
    *  Purpose: 
    *      All Commands that need to be displayed to the MMLConsole need to be
    *      Defined Here.This function also processes the commands received by the
    *      from the User Driven MML Console.
    *
    *  Input Parameters:
    *      None.
    *
    *  Input/Output Parameters:
    *      None.
    *
    *  Output Parameters:
    *      None.
    *
    *  Return Value:
    *      None
    *
    *  Notes:
    *
    *  See Also:
    ****************************************************************************/
    void DoCommand(std::istream& commandLine);

};

#endif




