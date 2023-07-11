/*********************************-*-H-*-***********************************
*                                                                          *
*          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
*            Manufactured in the United States of America.                 *
*      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
*                                                                          *
*   This product and related documentation is protected by copyright and   *
*   distributed under licenses restricting its use, copying, distribution  *
*   and decompilation.  No part of this product or related documentation   *
*   may be reproduced in any form by any means without prior written       *
*   authorization of Diametriq and its licensors, if any.                  *
*                                                                          *
*   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
*   government is subject to restrictions as set forth in subparagraph     *
*   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
*   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
*                                                                          *
****************************************************************************/

#ifndef OPENSSLTHREADSUPPORT_H
#define OPENSSLTHREADSUPPORT_H

class OpenSslThreadSupport
{
    public:
        static OpenSslThreadSupport& getInstacnce();
        pthread_rwlock_t* GetLockAt(int index);
        int Init();
        ~OpenSslThreadSupport();

    private:
        std::vector<pthread_rwlock_t*>mutex_vector;
        // Make the class singleton
        OpenSslThreadSupport(){};
        OpenSslThreadSupport(OpenSslThreadSupport const&){};
        OpenSslThreadSupport& operator=(OpenSslThreadSupport const&)
        {
            return m_pInstance;
        };
        static OpenSslThreadSupport m_pInstance;
};

struct CRYPTO_dynlock_value
{
    pthread_rwlock_t rw_lock;
};

#endif // #ifndef OPENSSLTHREADSUPPORT_H
