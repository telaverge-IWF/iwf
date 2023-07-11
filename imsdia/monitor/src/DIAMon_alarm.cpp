/****************************************************************************
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
 * ID: $Id: DIAMon_alarm.cpp,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $
 *
 * LOG: $Log: DIAMon_alarm.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:28  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/03/07 15:49:40  yranade
 * LOG: Initial Version of Monitor Utility. Please refer README for details.
 * LOG:
 ****************************************************************************/
#ident "$Id: DIAMon_alarm.cpp,v 3.1 2008/03/31 10:33:28 nvijikumar Exp $"

#include <DIAMon_alarm.h>

void
DIAMon_Alarm(int which, int type, const char *file, const int line,
             char *format, ...)
{
    // This is a TODO
#if 0
    char buf[1024], *tmp;
    char *module = "DiaMon";
    va_list alist;
    int ret;

    va_start(alist, format);

    tmp = buf ;
    if (format) 
    {
        vsprintf(tmp, format, alist);
    }

    va_end(alist);
#endif
}

