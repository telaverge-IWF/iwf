
/* ********************************-*-H-*-***********************************
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

#ifndef _HASH_H_
#define _HASH_H_

#include "SpookyV2.h"
namespace eAccelero {
#define hashsize(n) ((uint32_t)1<<(n))
#define hashmask(n) (hashsize(n)-1)
class Hash {
    public:
        Hash();
        void Initialize(uint64_t seed1,uint64_t seed2);
        static inline uint32_t Hash32(const void* message,size_t length, uint32_t seed)
        {
            return ::SpookyHash::Hash32(message,length,seed);
        }

        static inline uint64_t Hash64(const void* message,size_t length, uint64_t seed)
        {
            return ::SpookyHash::Hash64(message,length,seed);
        }

        static inline uint16_t Hash16 (const void* message,size_t length, uint32_t seed)
        {
            uint32_t hash32 = ::SpookyHash::Hash32(message,length,seed);
            hash32 = hash32 & hashmask(16);
            return ((uint16_t)hash32);
        }

    private:
        uint64_t seed1;
        uint64_t seed2;
        ::SpookyHash sHash;

}; // class Hash
} //namespace eAccelero

#endif
