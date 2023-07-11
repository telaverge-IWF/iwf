/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: servermain.c,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 * $Log: servermain.c,v $
 * Revision 9.1  2005/03/23 12:54:27  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 09:41:22  cvsadmin
 * PR6.4.2 sources propagated to Current.
 *
 * Revision 1.1.2.1.6.1  2004/01/05 10:01:25  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.1.2.1  2003/10/13 10:23:28  akumar
 * Code cleanup operation.
 *
 * Revision 1.1.2.1  2003/06/05 05:43:46  sjaddu
 * Added first revision of files for isupserver.
 *
 *
 ****************************************************************************/

#include <engine.h>

#define MAXPATH     256

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      main program
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
main(int argc, const char** argv)
{
    char path[MAXPATH];

    memset( path, 0, MAXPATH );

    APPL_SetName("isup");
    APPL_SetConfigFileExtension("xml");

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}


