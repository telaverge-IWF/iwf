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
 * $Id: cap_init.cpp,v 9.1 2005/03/23 12:51:12 cvsadmin Exp $
 *
 * $Log: cap_init.cpp,v $
 * Revision 9.1  2005/03/23 12:51:12  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 07:26:05  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 1.1.2.3  2003/06/18 03:50:49  mmanikandan
 * Initialize the license class in camel initialize.
 *
 * Revision 1.1.2.2  2003/06/17 04:49:05  sjaddu
 * Added LICENSE_Validate() to load the its.lic file.
 *
 * Revision 1.1.2.1  2003/06/16 11:08:21  sjaddu
 * Added file for CAMEL license capability.
 *
 ****************************************************************************/
#include <its++.h>
#include <cap_cpp.h>
#include <its_license.h>

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function will check the license capability for CAMEL
 *
 *  Input Parameters:
 *
 *  Return Value:
 *
 *  Notes: This function will called by application.
 ****************************************************************************/
void ITS_InitializeCAMELcodec()
{
	ITS_InitializeClass(itsLICENSE_Class);
    LICENSE_Validate();
    LICENSE_VerifyCapability(ITS_LIC_CAP_CAMEL);
}
