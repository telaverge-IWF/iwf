/*********************************-*-H-*-***************************************
 *                                                                             *
 *     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.       *
 *             Manufactured in the United States of America.                   *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.          *
 *                                                                             *
 *   This product and related documentation is protected by copyright and      *
 *   distributed under licenses restricting its use, copying, distribution     *
 *   and decompilation.  No part of this product or related documentation      *
 *   may be reproduced in any form by any means without prior written          *
 *   authorization of IntelliNet Technologies and its licensors, if any.       *
 *                                                                             *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the         *
 *   government is subject to restrictions as set forth in subparagraph        *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software          *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                           *
 *                                                                             *
 *******************************************************************************
 *                                                                             *
 * CONTRACT: INTERNAL                                                          *
 *                                                                             *
 *******************************************************************************
 *
 * LOG: $Log: its_tls_common.h,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.1.20.2  2013/07/09 05:47:08  vsarath
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 1.1.20.1  2013/06/25 10:00:04  jvikram
 * LOG: Merged changes from DRE Branch.
 * LOG:
 * LOG: Revision 1.1.6.4  2012/12/20 13:03:01  jvikram
 * LOG: Fix for issue 706
 * LOG:
 * LOG: Revision 1.1.6.3  2012/11/20 08:31:36  cprem
 * LOG: Merged from B-DRE-0212-00-TLS branch for 07 release
 * LOG:
 * LOG: Revision 1.1.6.1.20.4  2012/11/19 11:53:29  cprem
 * LOG: Merged from 00 branch for 07 release.
 * LOG:
 * LOG: Revision 1.1.6.1.20.3  2012/11/19 09:46:12  jvikram
 * LOG: Added for CRL Support
 * LOG:
 * LOG: Revision 1.1.6.2  2012/11/06 12:51:57  pramana
 * LOG: Reverse merged from B-DRE-0212-00-TLS branch for 212-06 release
 * LOG:
 * LOG: Revision 1.1.6.1.20.2  2012/11/06 08:33:14  jvikram
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 1.1.6.1.20.1  2012/11/05 04:23:29  cprem
 * LOG: Fixed warnings during compilation.
 * LOG:
 * LOG: Revision 1.1.4.1  2012/08/01 06:16:03  ncshivakumar
 * LOG: Code changes for Bug-119
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:04:41  nvijikumar
 * LOG: GNUTLS and OPENSSL made seperate
 * LOG:
 * LOG:
 *ID: $Id: its_tls_common.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/
#ident "$Id: its_tls_common.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#ifndef __TLS_COMMON_H__
#define __TLS_COMMON_H__

#include <its++.h>
#include <CAu.h>

#define KEYFILE "key.pem"
#define CERTFILE "cert.pem"
#define CAFILE "ca.pem"
#define CRLFILE "crl.pem"

#define PGPKEYFILE "secret.asc"
#define PGPCERTFILE "public.asc"
#define PGPRINGFILE "ring.gpg"


#define SRP_PASSWD "tpasswd"
#define SRP_PASSWD_CONF "tpasswd.conf"

/*continuity from Exceptions defined in its.h */
#define ITS_E_TLSFAILED  -123
#define ITS_E_TLSTIMEOUT -124

typedef void (*DebugFunction)(int level, const char * msg);

#define OPENSSL_SUCCESS   1
#define MAX_CIPHERS       7
#define MAX_KX            9
#define MAX_MAC           5
#define MAX_BUF           200

#define OPENSSL_ERROR_CHECK(ret)                                              \
    do                                                                        \
    {                                                                         \
        if(ret != OPENSSL_SUCCESS)                                            \
        {                                                                     \
            return ret;                                                       \
        }                                                                     \
    }while(0);

#define TLS_NULLPTR_CHECK(ptr)                                                \
    do                                                                        \
    {                                                                         \
        if( ptr == NULL)                                                      \
        {                                                                     \
            return ITS_ENULLPTR;                                              \
        }                                                                     \
    }while(0);

namespace its
{

enum CIPHER 
{ 
    CIPHER_NULL =1,
    ARCFOUR_128 =2, 
    DES_CBC     =4, 
    AES_128_CBC =8,
    AES_256_CBC =16, 
    ARCFOUR_40  =32
}; 

enum KEY_EXCHANGE 
{ 
    ITS_RSA    =1, 
    DHE_DSS    =2,
    DHE_RSA    =4, 
    ANON_DH    =8, 
    SRP_KX     =16,
    RSA_EXPORT =32, 
    SRP_RSA    =64, 
    SRP_DSS    =128
};


enum MAC 
{ 
    MAC_NULL=1,
    ITS_MD5 =2, 
    ITS_SHA =4, 
    RMD160 =16
};

enum CIPHER_SUITES
{
    TLS_RSA_NULL_MD5 = 1, 
    TLS_ANON_DH_3DES_EDE_CBC_SHA, 
    TLS_ANON_DH_ARCFOUR_MD5, 
    TLS_ANON_DH_AES_128_CBC_SHA, 
    TLS_ANON_DH_AES_256_CBC_SHA, 
    TLS_RSA_ARCFOUR_SHA, 
    TLS_RSA_ARCFOUR_MD5, 
    TLS_RSA_3DES_EDE_CBC_SHA, 
    TLS_RSA_EXPORT_ARCFOUR_40_MD5, 
    TLS_DHE_DSS_3DES_EDE_CBC_SHA, 
    TLS_DHE_RSA_3DES_EDE_CBC_SHA, 
    TLS_RSA_AES_128_CBC_SHA, 
    TLS_RSA_AES_256_CBC_SHA, 
    TLS_DHE_DSS_AES_256_CBC_SHA, 
    TLS_DHE_DSS_AES_128_CBC_SHA, 
    TLS_DHE_RSA_AES_256_CBC_SHA, 
    TLS_DHE_RSA_AES_128_CBC_SHA, 
    TLS_SRP_SHA_3DES_EDE_CBC_SHA, 
    TLS_SRP_SHA_AES_128_CBC_SHA, 
    TLS_SRP_SHA_AES_256_CBC_SHA, 
    TLS_SRP_SHA_RSA_3DES_EDE_CBC_SHA, 
    TLS_SRP_SHA_DSS_3DES_EDE_CBC_SHA, 
    TLS_SRP_SHA_RSA_AES_128_CBC_SHA, 
    TLS_SRP_SHA_DSS_AES_128_CBC_SHA, 
    TLS_SRP_SHA_RSA_AES_256_CBC_SHA, 
    TLS_SRP_SHA_DSS_AES_256_CBC_SHA, 
    TLS_DHE_DSS_ARCFOUR_SHA,
    //newly added
    TLS_RSA_NULL_SHA,
    TLS_RSA_DES_CBC_SHA,
};


enum AUTHENTICATION
{
    INVALID_AUTH = 0,
    X_509,
    OPEN_PGP,
    SRP,
    PSK,
    ANONYMOUS
};

enum  END_POINT_TYPE
{
    CLIENT,
    SERVER  
};

enum PRIORITY_TYPE
{
    CIPHER,
    KX,
    MAC,
    COMPRESSION,
    PROT,
    CERT_CD
};

enum TLS_TYPE
{
    INVALID_TLS, 
    GNU_TLS,
    OPEN_SSL
};

class Certificate
{
public:

    Certificate() 
    {
        tlsType = OPEN_SSL;
    }
    virtual ~ Certificate() { }
    virtual int SetX509TrustFile( char  * trustFile) = 0;
    virtual int SetX509TrustFile( char  * MasterCAFile, char * cAPath)
    {
        return ITS_SUCCESS;
    }
    virtual int EnableCrlCheck(std::vector<its::CertificateAuthority*>& CA, std::string crlPath)
    { 
        return ITS_SUCCESS;
    }
    virtual int SetX509KeyFile( char * certFile, char * keyFile ) = 0;

    TLS_TYPE tlsType;
};

class TlsSession
{
public:

    virtual ~ TlsSession() { }
    virtual void Bye() = 0;
    virtual int RecordRecieve(char * buff, int buffSize) = 0;
    virtual int RecordSend(char * msg, int msgSize) = 0;
    virtual int VerifyCertificate(const char *hostname,const char *realName)= 0;    virtual int CredentialSet(Certificate * ctx)
    {
        return ITS_SUCCESS;
    }

    virtual int CertificateRequest()
    {
        return ITS_SUCCESS;
    }

    virtual int Handshake()
    {
        return ITS_SUCCESS;
    }

    virtual int Handshake(int time)
    {
        return ITS_SUCCESS;
    }

    virtual int SetCipherSuite(int * cipherSuiteList)
    {
        return ITS_SUCCESS;
    }
    int sock;

private:

};
};

#endif /* __TLS_DEFINES_H__ */
