/**************************-*-Dia-*-*************************************
 *                                                                          *
 *             Copyright 2006 IntelliNet Technologies, Inc.                 *
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
 *  ID: $Id: dia_codec.h,v 3.1.30.1 2012/10/01 09:00:59 rsanjay Exp $
 *  
 *  LOG: $Log: dia_codec.h,v $
 *  LOG: Revision 3.1.30.1  2012/10/01 09:00:59  rsanjay
 *  LOG:  opendiameter code removal changes:bugzilla-id 300
 *  LOG:
 *  LOG: Revision 3.1  2008/03/31 10:33:25  nvijikumar
 *  LOG: Start GA 3.0
 *  LOG:
 *  LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 *  LOG: Start GA 1.1
 *  LOG:
 *  LOG: Revision 1.1  2006/03/03 13:11:19  tpanda
 *  LOG: Code reorganisation:codec functionality moved to separate file
 *  LOG:
 *
 ****************************************************************************/
#ident "$Id:" 

#ifndef DIA_CODEC_H_
#define DIA_CODEC_H_

#include <dia_defines.h>
#include <diameter/Command.h>

namespace diameter
{
const
CommandAdapter* Decode(void *data, size_t length);

int
Encode(diameter::Command& mesg, ITS_OCTET* buff, ITS_INT& length);
};


#endif
