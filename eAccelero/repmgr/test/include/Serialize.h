/* ********************************-*-H-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "info.h"
#define DELIMITER "~"
#define SERIALIZE_BUF_MAX 256

typedef enum structType
{
    ERLBF_SESS_INFO=1,
    ERLBF_SESS_BIND_KEY,
    ASF,
    STACK_SESSION_ENTRY


}STRUCT_TYPE;

class Serialize
{
    
    public:
        int32_t serialize(STRUCT_TYPE strType, void *outData, void *inData);
        int32_t deserialize( STRUCT_TYPE strType, void *outData, void *inData);

};

#endif
