/*********************************-*-H-*-**************************************
**                                                                          *
**          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
**            Manufactured in the United States of America.                 *
**      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
**                                                                          *
**   This product and related documentation is protected by copyright and   *
**   distributed under licenses restricting its use, copying, distribution  *
**   and decompilation.  No part of this product or related documentation   *
**   may be reproduced in any form by any means without prior written       *
**   authorization of Diametriq and its licensors, if any.                  *
**                                                                          *
**   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
**   government is subject to restrictions as set forth in subparagraph     *
**   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
**   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
**                                                                          *
*****************************************************************************/


#ifndef _RANDOM_NUMBER_H_
#define _RANDOM_NUMBER_H_
#include<Sync.h>
namespace eAccelero {

 class RandomNumberGenerator {

     public:
         RandomNumberGenerator();
         ~RandomNumberGenerator() { }
         uint32_t getRandomNumber();
     private:
         Mutex randomNumberMutex;
         static uint32_t randomNumber;
 };

};//namespace eAccelero

#endif
