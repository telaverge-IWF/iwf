/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2004 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
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
 *      
 *  ID: $Id: dia_oam_server.h,v 1.1 2008/12/05 11:52:10 nvijikumar Exp $
 *         
 *  LOG: $Log: dia_oam_server.h,v $
 *  LOG: Revision 1.1  2008/12/05 11:52:10  nvijikumar
 *  LOG: Initial draft for Alarm support
 *  LOG:
 *  LOG:
 *         
 ****************************************************************************/
#ident "$Id: dia_oam_server.h,v 1.1 2008/12/05 11:52:10 nvijikumar Exp $"

#if !defined(DIA_OAM_SERVER_H)
#define DIA_OAM_SERVER_H
 
#include <its.h>

#if defined(__cplusplus)
extern "C"
{
#endif

#define OAMSERVER_CLASS_NAME          "DIA OAM Server Class"
extern ITS_Class                      itsDIAOAMServer_Class;

#if defined(__cplusplus)
}
#endif

#endif /* DIA_OAM_SERVER_H */

