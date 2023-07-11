/********************************-*-C++-*-*************************************
**                                                                          *
**     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
**             Manufactured in the United States of America.                *
**       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
**                                                                          *
**    This product and related documentation is protected by copyright and  *
**    distributed under licenses restricting its use, copying, distribution *
**    and decompilation.  No part of this product or related documentation  *
**    may be reproduced in any form by any means without prior written      *
**    authorization of IntelliNet Technologies and its licensors, if any.   *
**                                                                          *
**    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
**    government is subject to restrictions as set forth in subparagraph    *
**    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
**    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
**                                                                          *
*****************************************************************************/

#include <RandomNumber.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>


namespace eAccelero {

    uint32_t RandomNumberGenerator::randomNumber;

    RandomNumberGenerator::RandomNumberGenerator()
    {
        randomNumber = 0;
    }

    uint32_t RandomNumberGenerator::getRandomNumber()
    {
        //Lock the global variable
        Mutex::ScopedMutex sMutex(randomNumberMutex);

        if (randomNumber == 0)
        {
            struct timeval tv;
            gettimeofday(&tv, 0);
            srand((unsigned int)(tv.tv_sec + tv.tv_usec));

            /* Set High Order 12 bits */
            randomNumber = (unsigned int)(tv.tv_sec) << 20;
        }

        /* clear lower 20 bits */
        randomNumber &= 0xFFF00000;

        /* set lower 20 bits */
        randomNumber |= rand() & 0x000FFFFF;

        uint32_t randomNumberLocal = randomNumber;

        sMutex.unlock();
        return (randomNumberLocal);
    }


};//namespace eAccelero
