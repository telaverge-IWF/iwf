/*********************************-*-CPP-*-*********************************
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

#include <iostream>
#include <vector>
#include <openssl/crypto.h>
#include "its_ssl_tls_thread_support.h"

// Call-back prototypes
static void lock_callback(int mode, int n, const char * file, int line);
static unsigned long id_callback(void);
static struct CRYPTO_dynlock_value* create_dyn_lock_callback(const char *file,
                                                                int line);
static void dyn_lock_callback(int mode, struct CRYPTO_dynlock_value *l,
                                                const char *file, int line);
static void destroy_dyn_lock_callback(struct CRYPTO_dynlock_value *l, 
                                                const char *file, int line);
OpenSslThreadSupport OpenSslThreadSupport::m_pInstance;

OpenSslThreadSupport& OpenSslThreadSupport::getInstacnce()
{
    return m_pInstance;
}

pthread_rwlock_t* OpenSslThreadSupport::GetLockAt(int index)
{
    return mutex_vector[index];
}

int OpenSslThreadSupport::Init()
{
    for (int i = 0; i < CRYPTO_num_locks(); i++)
    {
        pthread_rwlock_t* rw_lock = (pthread_rwlock_t*)
                            malloc(sizeof(pthread_rwlock_t));
        if (rw_lock == NULL)
        {
            return -1;
        }
        pthread_rwlock_init(rw_lock, NULL);
        mutex_vector.push_back(rw_lock);
    }

    // Static locks callbacks
    CRYPTO_set_locking_callback((void (*)(int,int,
                                    const char *,int))lock_callback);
    CRYPTO_set_id_callback((unsigned long (*)(void))id_callback);

    // Dynamic locks callbacks
    CRYPTO_set_dynlock_create_callback(create_dyn_lock_callback);
    CRYPTO_set_dynlock_lock_callback(dyn_lock_callback);
    CRYPTO_set_dynlock_destroy_callback(destroy_dyn_lock_callback);

    return 0;
}

OpenSslThreadSupport::~OpenSslThreadSupport()
{
    std::vector<pthread_rwlock_t*>::iterator it;
    for (it = mutex_vector.begin(); it != mutex_vector.end(); )
    {
        delete *it;
        *it = NULL;
        mutex_vector.erase(it++);
    }
}

// Call-back definitions
static void lock_callback(int mode, int n, const char * file, int line)
{
    OpenSslThreadSupport&  threadObj = OpenSslThreadSupport::getInstacnce();

    if ((mode & (CRYPTO_READ|CRYPTO_LOCK)) == (CRYPTO_READ|CRYPTO_LOCK))
    {
        pthread_rwlock_rdlock(threadObj.GetLockAt(n));
    }
    else if ((mode & (CRYPTO_WRITE|CRYPTO_LOCK)) == (CRYPTO_WRITE|CRYPTO_LOCK))
    {
        pthread_rwlock_wrlock(threadObj.GetLockAt(n));
    }
    else if ((mode & CRYPTO_UNLOCK) == CRYPTO_UNLOCK)
    {
        pthread_rwlock_unlock(threadObj.GetLockAt(n));
    }
}

static unsigned long id_callback(void)
{
    return ((unsigned long)pthread_self());
}

static struct CRYPTO_dynlock_value* create_dyn_lock_callback(const char *file,
                                                                    int line)
{
    struct CRYPTO_dynlock_value *value;
    value = (CRYPTO_dynlock_value*) malloc(sizeof(CRYPTO_dynlock_value));
    if (!value)
    {
        return NULL;
    }
    pthread_rwlock_init(&value->rw_lock, NULL);
    return value;
}

static void dyn_lock_callback(int mode, struct CRYPTO_dynlock_value *l,
                                                const char *file, int line)
{
    if ((mode & (CRYPTO_READ|CRYPTO_LOCK)) == (CRYPTO_READ|CRYPTO_LOCK))
    {
        pthread_rwlock_rdlock(&l->rw_lock);
    }
    else if ((mode & (CRYPTO_WRITE|CRYPTO_LOCK)) == (CRYPTO_WRITE|CRYPTO_LOCK))
    {
        pthread_rwlock_wrlock(&l->rw_lock);
    }
    else if ((mode & CRYPTO_UNLOCK) == CRYPTO_UNLOCK)
    {
        pthread_rwlock_unlock(&l->rw_lock);
    }
}


static void destroy_dyn_lock_callback(struct CRYPTO_dynlock_value *l,
                                            const char *file, int line)
{
    pthread_rwlock_destroy(&l->rw_lock);
    free(l);
}
