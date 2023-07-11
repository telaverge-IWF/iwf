/*********************************-*-C-*-***************************************
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
 * LOG: $Log: its_ssl_tls_session.cpp,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.2.16.3  2013/09/04 05:05:41  vsarath
 * LOG: Implemented tls read/write lock
 * LOG:
 * LOG: Revision 1.2.16.2  2013/07/10 13:05:53  vsarath
 * LOG: Updated for adding two versions of openssl
 * LOG:
 * LOG: Revision 1.2.16.1  2013/06/25 10:00:04  jvikram
 * LOG: Merged changes from DRE Branch.
 * LOG:
 * LOG: Revision 1.2.4.1.2.5.4.2  2013/02/18 06:05:55  jvikram
 * LOG: Fix for issue 1032
 * LOG:
 * LOG: Revision 1.2.4.1.2.5.4.1  2013/02/15 04:52:40  jvikram
 * LOG: Fix for issue 706
 * LOG:
 * LOG: Revision 1.2.4.1.2.5  2013/01/04 10:51:44  jvikram
 * LOG: Fix for issue 832
 * LOG:
 * LOG: Revision 1.2.4.1.2.4  2012/12/20 13:03:56  jvikram
 * LOG: Fix for issue 706
 * LOG:
 * LOG: Revision 1.2.4.1.2.3  2012/11/20 08:31:36  cprem
 * LOG: Merged from B-DRE-0212-00-TLS branch for 07 release
 * LOG:
 * LOG: Revision 1.2.4.1.2.2  2012/11/06 12:51:57  pramana
 * LOG: Reverse merged from B-DRE-0212-00-TLS branch for 212-06 release
 * LOG:
 * LOG: Revision 1.2.4.1.2.1.20.4  2012/11/19 09:46:39  jvikram
 * LOG: Added for CRL Support
 * LOG:
 * LOG: Revision 1.2.4.1.2.2  2012/11/06 12:51:57  pramana
 * LOG: Reverse merged from B-DRE-0212-00-TLS branch for 212-06 release
 * LOG:
 * LOG: Revision 1.2.4.1.2.1.20.2  2012/11/06 08:43:14  jvikram
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 1.2.4.1.2.1.20.1  2012/11/05 07:29:58  cprem
 * LOG: Changed hard-coded failure return to the existing macro.
 * LOG:
 * LOG: Revision 1.2.4.2  2012/08/01 06:17:24  ncshivakumar
 * LOG: Code changes for Bug-119
 * LOG:
 * LOG: Revision 1.2.4.1  2012/06/22 04:00:34  ncshivakumar
 * LOG: TLS compilation changes on linux
 * LOG:
 * LOG: Revision 1.2  2010/07/09 10:39:21  nvijikumar
 * LOG: Link with OS SSL lib
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:03:42  nvijikumar
 * LOG: GNUTLS and OPENSSL made separate
 * LOG:
 * LOG:
 *ID: $Id: its_ssl_tls_session.cpp,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/
#ident "$Id: its_ssl_tls_session.cpp,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#include <iostream>
#include <its_ssl_tls_session.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/x509v3.h>
#include <openssl/err.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <pthread.h>
#include <its_trace.h>
#include <string>
#if defined(solaris) || defined (solaris64)
#include <sys/filio.h>
#endif

/*.implementation:public SSLContext 
************************************************************************
*  Purpose: Constructor
*        To create a SSL context 
*
*  Input:
*    endType: CLIENT or SERVER 
*  
*  Note: Context in Open SSL is equivalent to Credentials in GNU tls 
*        Not exactly equivalent but to set the certificates and keys, you
*        need Context in Open SSL just like you need credentials of type
*        certificates in GNU tls.     
************************************************************************/

SSLContext::SSLContext(END_POINT_TYPE type)
{
#ifdef SSL_NEW
    const SSL_METHOD *meth;   
#else
    SSL_METHOD *meth;   
#endif
        if(type == CLIENT)
        {
            meth = TLSv1_client_method();
            ctxt = SSL_CTX_new(meth);
        }
        else
        {
            meth = TLSv1_server_method();
            ctxt = SSL_CTX_new(meth);
        }
    if(ctxt == NULL)
    {
        throw ITS_E_TLSFAILED;
    }
    endType = type;
}

/*.implementation:public ~SSLContext
************************************************************************
*  Purpose: DESTRUCTOR
*        To free SSL Context created 
*
*  Input:
*  
*       
************************************************************************/

SSLContext::~ SSLContext()
{
    SSL_CTX_free(ctxt);
}

/*.implementation:public SetX509TrustFile
************************************************************************
*  Purpose:
*      This method sets the X.509 trust file for the allocated credential.
*      File is generated using Cert Tool
*  Input:
*   trustFile: File Name
*
************************************************************************/
int
SSLContext::SetX509TrustFile( char  * trustFile)
{
    int ret;
    TLS_NULLPTR_CHECK(trustFile);
    if(endType ==  CLIENT)
    { 
        ret = SSL_CTX_load_verify_locations(ctxt, trustFile, 0);
        OPENSSL_ERROR_CHECK(ret); 
    }
    else
    {
        ret = SSL_CTX_load_verify_locations(ctxt, trustFile, 0);
        OPENSSL_ERROR_CHECK(ret); 
        SSL_CTX_set_client_CA_list(ctxt,SSL_load_client_CA_file(trustFile));
    }
    return ITS_SUCCESS;
}

int
SSLContext::SetX509TrustFile( char  * MasterCAFile, char * cAPath)
{
    int ret;
    TLS_NULLPTR_CHECK(MasterCAFile);
    SSL_CTX_set_verify(ctxt,SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT,NULL);

    if(endType ==  CLIENT)
    { 
        ret = SSL_CTX_load_verify_locations(ctxt, 0, cAPath);
        OPENSSL_ERROR_CHECK(ret); 
    }
    else
    {
        ret = SSL_CTX_load_verify_locations(ctxt, 0, cAPath);
        OPENSSL_ERROR_CHECK(ret); 
        SSL_CTX_set_client_CA_list(ctxt,SSL_load_client_CA_file(MasterCAFile));
    }
    return ITS_SUCCESS;
}
/*.implementation:public SetX509KeyFile
************************************************************************
*  Purpose:
*   This method sets the X.509 certificate & Key file for the allocated 
*   credential.
*   File is generated using Cert Tool
*
*  Input:
*   certFile: Cert File Name
*   keyFile : Key file Name
*
************************************************************************/
int
SSLContext::SetX509KeyFile( char * certFile, char * keyFile ) 
{   
    int ret;   
    TLS_NULLPTR_CHECK(certFile);
    TLS_NULLPTR_CHECK(keyFile);

    ret = SSL_CTX_use_certificate_file(ctxt, certFile, SSL_FILETYPE_PEM);
    OPENSSL_ERROR_CHECK(ret); 
    ret = SSL_CTX_use_PrivateKey_file(ctxt, keyFile ,SSL_FILETYPE_PEM);     
    OPENSSL_ERROR_CHECK(ret); 
    return 1;//we need to return '1' if its success& 0 if fails.
}

/*.implementation:public EnableCrlCheck
************************************************************************
*  Purpose: 
*      This method enables CRL Verification and loads the configured CRL files
*      into the X509_Store for OpenSSL to use the same.
*
*  Input:
*    CA : Reference to Vector of CertificateAuthority Object Pointers.
*    crlPath: Path to where the CRL's are stored.
*
*  Output: None
*
*  Note: 
*      
************************************************************************/
int SSLContext::EnableCrlCheck(std::vector<its::CertificateAuthority*>& CA, std::string crlPath)
{
    X509_STORE *store = SSL_CTX_get_cert_store(ctxt);
    X509_LOOKUP *lookup = NULL;

    std::vector<its::CertificateAuthority*>::const_iterator it;

    if (!(lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file())))
    {
        return ERRCLOOKOBJ;
    }

    X509_STORE_set_flags(store, X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);

    for(it = CA.begin(); it != CA.end(); it++)
    {
        std::string path = crlPath;
        std::string crlfile = path.append((*it)->GetCRL().GetCRLFileName());

        if(crlfile.length())
        {
            if (X509_load_crl_file(lookup, crlfile.c_str(), X509_FILETYPE_PEM) != 1)
            {
                return ERRLCRLF;
            }
        }
    }
    return ITS_SUCCESS;
}

/*.implementation:public OpenSslTlsSession
************************************************************************
*  Purpose: CONSTRUCTOR
*      This method stores the socket descriptor 
*
*  Input:
*    sd : Socket Descriptor of transport layer
*
*  Output: 
*
* Note: This will Non Create a session. If you are using Tls of Type Open
*       Ssl then credential set is Must. 
************************************************************************/

OpenSslTlsSession::OpenSslTlsSession(int sd) 
{
    sock = sd;
    session = NULL;
    pthread_mutex_init(&tlsSessionLock, NULL);
} 

/*.implementation:public OpenSslTlsSession
************************************************************************
*  Purpose: DESTRUCTOR
*      This method fees the Open SSL session created
*
*  Input:
*
************************************************************************/
OpenSslTlsSession::~OpenSslTlsSession()
{
    if(session != NULL)
    {
        SSL_free(session);
    }

}

/*.implementation:public Bye 
************************************************************************
*  Purpose:
*      This method Says Good Bye to another end Point.
*      It will close further Read & Write
*
*  Input:
*
************************************************************************/
void
OpenSslTlsSession::Bye()
{   
    if(session != NULL)
    {
        ITS_INT ret;
        ITS_ULONG err;
        char buf[MAX_BUF];

        ret = SSL_shutdown(session); 
        if(ret < 0)
        {
            err = ERR_peek_last_error(); // returns the latest error code from 
            // the thread's error queue without modifying it.
            ERR_error_string_n(err, buf, MAX_BUF);
            ITS_TRACE_ERROR(("TLS:Shutdown Failed:%s\n",buf));
            ERR_clear_error(); // empties the current thread's error queue
        }

    }
}

/*.implementation:public RecordRecieve
************************************************************************
*  Purpose:
*      Method to Recieve Record from Tls Layer which internally
*      using Transport layer Recieve
*
*  Input:
*     buffer : ptr to Buffer
*     sizeBuff : size of buffer
*
*  Return : number of bytes Read
*
*  Note: Its a blocking call but it does't wait for the buffer to fill
*        it reads what ever the data is available. It blocks if there is 
*        no data     
************************************************************************/
int 
OpenSslTlsSession::RecordRecieve(char * buff, int buffSize)
{   int ret;

    TLS_NULLPTR_CHECK(buff);
    if(buffSize > 0)
    {
        if(session == NULL)
        {
            return ITS_E_TLSFAILED; 
        } 
        ITS_ULONG err;
        ITS_INT ret;
        char buf[MAX_BUF];

        ret =  SSL_read(session, buff, buffSize);
        if(ret < 0)
        {
            err = ERR_peek_last_error();
            ERR_error_string_n(err, buf, MAX_BUF);
            ITS_TRACE_ERROR(("TLS:Read Failed:%s\n",buf));
            ERR_clear_error();
        }
        OPENSSL_ERROR_CHECK(ret);
        return ret; 
    }

    return ITS_E_TLSFAILED;
}

/*.implementation:public RecordSend
************************************************************************
*  Purpose:
*      Method to send Record from Tls Layer which internally
*       using Transport layer send
*
*  Input:
*  msg : Pointer to msg
*  sizeMsg : size of msg
*
*  Return: number of bytes send
*
* Note:
************************************************************************/
int 
OpenSslTlsSession::RecordSend(char * msg, int msgSize)
{

    int    nleft;
    int    nwritten;


    if(!(msg) || !(msgSize))
    {
        return ITS_ENULLPTR;

    }

    /* Set up how much we need to write */
    nleft = msgSize;


    /* While still bytes to write do so */
    pthread_mutex_lock(&tlsSessionLock);
    while (nleft > 0)
    {
        if(session == NULL)
        {
            pthread_mutex_unlock(&tlsSessionLock);
            return ITS_E_TLSFAILED; 
        } 

        /* Write some data */
        ITS_ULONG err;
        ITS_INT ret;
        char buf[MAX_BUF];

        nwritten =  SSL_write(session, msg, msgSize);
        if(nwritten < 0)
        {
            err = ERR_peek_last_error();
            ERR_error_string_n(err, buf, MAX_BUF);
            ITS_TRACE_ERROR(("TLS:Write Failed:%s\n",buf));
            ERR_clear_error();
        }

        /* If any of these errors return # actually written */
        if (nwritten <= 0 )
        {
            pthread_mutex_unlock(&tlsSessionLock);
            return nwritten;
        }

        /* else adjust counters and keep going */
        else
        {

            /*
             * Note that the buf pointer is incremented as opposed to
             * doing a write to buf+nwritten (which might have been a
             * bit more clear).
             */
            nleft -= nwritten;
            msg += nwritten;
        }
    }

    /* Return how much we actually wrote */
    pthread_mutex_unlock(&tlsSessionLock);
    return (msgSize);
}

/*.implementation:public CredentialSet
************************************************************************
*  Purpose:
*     Setting the credential for client session.
*
*  Input:
*   cliCert: Pointer to ClientCertificate class
*
*  Note: For Open SSL this Call is Mandatory. This Actually Creates the Session
************************************************************************/   
int
OpenSslTlsSession::CredentialSet(Certificate * ctx)
{
    int ret;  
    session = SSL_new(((SSLContext *)ctx)->ctxt);
    if(session == NULL)
    {
        return ITS_E_TLSFAILED;
    }
    sessCtx = ((SSLContext *)ctx)->ctxt;
    ret =  SSL_set_fd(session,sock); 
    OPENSSL_ERROR_CHECK(ret);
    return ITS_SUCCESS;
}

/*.implementation:public VerifyCertificate
************************************************************************
*  Purpose:
*    Method to Verify Peers Certificate, Expiry , Activation time & HostName
*
*  Input:
*   hostname: Trusted Domain Name of the Certificate.
*   realName : Trusted Realm Name
************************************************************************/  
int
OpenSslTlsSession::VerifyCertificate(const char * hostname, const char * realmName)
{
    X509 *peer =NULL;
    char peer_CN[256];
    int match_found,i, subj_alt_names_count, ret = ITS_SUCCESS;
#ifdef SSL_NEW
    STACK_OF(GENERAL_NAME)  *subj_alt_names;
#else
    STACK *subj_alt_names;
#endif
    GENERAL_NAME *subj_alt_name;

    if(session == NULL)
    {
        return ITS_E_TLSFAILED; 
    } 
    if(SSL_get_verify_result(session)!=X509_V_OK)
    {
        ret = ITS_E_TLSFAILED;
    }

    /*Check the cert chain. The chain length
      is automatically checked by OpenSSL when
      we set the verify depth in the ctx */

    /*Check the common name*/
    if(ret == ITS_SUCCESS)
    {
        peer=SSL_get_peer_certificate(session);
        match_found = 0;
        if(peer != NULL)
        {
            if ((subj_alt_names = 
#ifdef SSL_NEW
                        (stack_st_GENERAL_NAME*)X509_get_ext_d2i(peer, 
                            NID_subject_alt_name, 
                            NULL, NULL)))
#else
                (STACK*)X509_get_ext_d2i(peer, 
                        NID_subject_alt_name, 
                        NULL, NULL)))
#endif

                        {
                            subj_alt_names_count = sk_GENERAL_NAME_num(subj_alt_names);
                            for (i = 0; i < subj_alt_names_count; i++) 
                            {
                                subj_alt_name = sk_GENERAL_NAME_value(subj_alt_names, i);
                                if (subj_alt_name->type == GEN_DNS) 
                                {
                                    if (strcasecmp(hostname, 
                                                (char *)(subj_alt_name->d.dNSName->data)) 
                                            !=0 )
                                    {
                                        if (strcasecmp(realmName, 
                                                    (char *)(subj_alt_name->d.dNSName->data)) 
                                                != 0)
                                        {
                                            X509_NAME_get_text_by_NID
                                                (X509_get_subject_name(peer),
                                                 NID_commonName, peer_CN, 256);
                                            if(strcasecmp(peer_CN,hostname) != 0)
                                            {
                                                ret = ITS_E_TLSFAILED;
                                            }
                                        }
                                    }
                                }
                            }
                        }

        }
        else
        {
            ret = ITS_E_TLSFAILED;
        }  
    }

    if (peer)
    {
        X509_free(peer);
    }

    return ret;
}

/*.implementation:public SetCipherSuite
************************************************************************
*  Purpose: Set the Cipher Suite list
*
*
*  Input:
*   cipherSuiteList: List of cipherSuites Which needs to be enable
*
*  Note: If you are setting cipher suite then SetPriority is not required
************************************************************************/
int
OpenSslTlsSession::SetCipherSuite(int * cipherSuiteList)
{
    int  ret, counter=0;
    std::string cipherList;

    bool contFlag = 0;
    
    TLS_NULLPTR_CHECK(cipherSuiteList);    
    /*Creating a List of required cipher, kx & mac from the 
           given list of cipher Suites*/
    while(cipherSuiteList[counter] !=0)
    {
        switch(cipherSuiteList[counter])
        {        
            case TLS_RSA_ARCFOUR_SHA:
                if(contFlag)
                { 
                    cipherList.append(":");
                    cipherList.append("RSA+RC4+SHA:!EXPORT");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("RSA+RC4+SHA:!EXPORT");
                }
                break;            
            case TLS_RSA_ARCFOUR_MD5:
                
                if(contFlag)
                { 
                    cipherList.append(":");
                    cipherList.append("RSA+RC4+MD5:!EXPORT");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("RSA+RC4+MD5:!EXPORT");
                }
                break;              
            case TLS_RSA_3DES_EDE_CBC_SHA:
                if(contFlag)
                { 
                    cipherList.append(":");
                    cipherList.append("RSA+3DES+SHA:!EXPORT");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("RSA+3DES+SHA:!EXPORT");
                }
                break;
            case TLS_RSA_AES_128_CBC_SHA: 
                if(contFlag)
                {
                    cipherList.append(":");
                    cipherList.append("AES128-SHA");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("AES128-SHA");
                }
                break;
            case TLS_RSA_NULL_MD5:
                if(contFlag)
                {
                    cipherList.append(":");
                    cipherList.append("NULL-MD5");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("NULL-MD5");
                }
                break;
             case TLS_RSA_NULL_SHA:
                if(contFlag)
                {
                    cipherList.append(":");
                    cipherList.append("NULL-SHA");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("NULL-SHA");
                }
                break;
             case TLS_RSA_DES_CBC_SHA:
                if(contFlag)
                {
                    cipherList.append(":");
                    cipherList.append("DES-CBC-SHA");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("DES-CBC-SHA");
                }
                break;
             case TLS_RSA_AES_256_CBC_SHA:
                if(contFlag)
                {
                    cipherList.append(":");
                    cipherList.append("AES256-SHA");
                }
                else
                {
                    contFlag = 1;
                    cipherList.append("AES256-SHA");
                }
                break;

            default:
                break;
        }       
        counter++;
    }
    /*Terminating The list of Ciphers, KX, MAc with ZERO */
    ret =  SSL_set_cipher_list(session, cipherList.c_str());
    OPENSSL_ERROR_CHECK(ret);
    return ITS_SUCCESS;

}

/*.implementation:public Handshake
************************************************************************
*  Purpose:
*      This method will perform Tls Handshake with the Server.
*
*  Input:
*
* Note: All Cipher Suite Negotiation & Certificate & key Exchange is
*       done in this Metho. Its a Blocking Call
************************************************************************/
int
SslClientSession::Handshake()
{
    int ret, ssl_ret;
    if(session == NULL)
    {
        return ITS_E_TLSFAILED; 
    } 
    ITS_ULONG err;
    char buf[MAX_BUF];

    ret = SSL_connect(session);
    ssl_ret = SSL_get_error(session, ret);
    if((ssl_ret != SSL_ERROR_WANT_READ) && (ssl_ret !=  SSL_ERROR_WANT_WRITE))
    {
        err = ERR_peek_last_error();
        ERR_error_string_n(err, buf, MAX_BUF);
        ITS_TRACE_ERROR(("TLS:Connect Failed:%s\n",buf));
        ERR_clear_error();
    }
    OPENSSL_ERROR_CHECK(ret);
    return ITS_SUCCESS;
}


/*.implementation:public Handshake
************************************************************************
*  Purpose:
*      This method will perform Tls Handshake with timeout with the peer. 
*
*  Input:
*    time: Duration after which handshake expires 
*
*  Note: Handshake is a blocking call so thread hangs if peer
*        is not replying, for that reason handshake with time out
*        is required 
************************************************************************/
int
SslClientSession::Handshake(int timeout)
{
    int ret, ioctlVal = 1;
    fd_set fdSet;
    struct timeval tOut;

    if(session == NULL)
    {
        return ITS_E_TLSFAILED; 
    }

    FD_ZERO(&fdSet);
    FD_SET(sock,&fdSet);

    tOut.tv_sec = timeout;
    tOut.tv_usec = 0;

    /* Making the Socket Non Blocking by calling IOCTL to Make
       Handshake at Client Non Blocking*/
    ioctl(sock, FIONBIO, &ioctlVal);

    /* Now Client will send a Client Hello and will come out of 
       Handshake with a return value  GNUTLS_E_AGAIN. So Next time
       when handshake will be called it will continue handshake & will
       not send Client Hello again */
    ITS_ULONG err;
    ITS_INT ssl_ret;
    char buf[MAX_BUF];

    ret = SSL_connect(session);
    ssl_ret = SSL_get_error(session, ret);
    if((ssl_ret != SSL_ERROR_WANT_READ) && (ssl_ret !=  SSL_ERROR_WANT_WRITE))
    {
        err = ERR_peek_last_error();
        ERR_error_string_n(err, buf, MAX_BUF);
        ITS_TRACE_ERROR(("TLS:Connect Failed:%s\n",buf));
        ERR_clear_error();
    }
    ioctlVal = 0;

    /* Making the Socket Blocking again by changing the Ioctl val =0*/
    ioctl(sock, FIONBIO, &ioctlVal);

    /* Handshake inside the select call with timeout to make handshake time
       out*/
    select(sock+1,&fdSet,NULL,NULL,&tOut);
    if(FD_ISSET(sock,&fdSet))
    {
        /* Now this handshake is Blocking but we will come here if
           there will be any data on the socket, Now handshake will proceed
           because server has replied to Client Hello, So peer is also interested 
           in handshake so handshake will not block */  

        ITS_ULONG err;
        ITS_INT ret;
        char buf[MAX_BUF];

        ret = SSL_connect(session);
        if(ret < 0)
        {
            err = ERR_peek_last_error();
            ERR_error_string_n(err, buf, MAX_BUF);
            ITS_TRACE_ERROR(("TLS:Connect Failed:%s\n",buf));
            ERR_clear_error();
        }
        OPENSSL_ERROR_CHECK(ret); 
    }
    else
    {
        return ITS_E_TLSTIMEOUT;
    }
    return ITS_SUCCESS;
}


/*.implementation:public Handshake
************************************************************************
*  Purpose:
*      This method will perform Tls Handshake with the Client.
*
*  Input:
*
* Note: All Cipher Suite Negotiation & Certificate & key Exchange is
*       done in this Method. Its a Blocking Call.d
************************************************************************/
int
SslServerSession::Handshake()
{
    int ret;
    if(session == NULL)
    {
        return ITS_E_TLSFAILED; 
    } 
    ITS_ULONG err;
    char buf[MAX_BUF];

    ret = SSL_accept(session);
    if(ret < 0)
    {
        err = ERR_peek_last_error();
        ERR_error_string_n(err, buf, MAX_BUF);
        ITS_TRACE_ERROR(("TLS:Accept Failed:%s\n",buf));
        ERR_clear_error();
    }
    OPENSSL_ERROR_CHECK(ret);
    return ITS_SUCCESS;
}

/*.implementation:public Handshake
************************************************************************
*  Purpose:
*      This method will perform Tls Handshake with timeout with the peer. 
*
*  Input:
*    time: Duration after which handshake expires 
*
*  Note: Handshake is a blocking call so thread hangs if peer
*        is not replying, for that reason handshake with time out
*        is required 
************************************************************************/
int
SslServerSession::Handshake(int timeout)
{
    int ret;
    fd_set fdSet;
    struct timeval tOut;


    FD_ZERO(&fdSet);
    FD_SET(sock,&fdSet);

    tOut.tv_sec = timeout;
    tOut.tv_usec = 0;

    select(sock+1,&fdSet,NULL,NULL,&tOut);
    if(FD_ISSET(sock,&fdSet))
    {
        if(session == NULL)
        {
            return ITS_E_TLSFAILED; 
        }
        ITS_ULONG err;
        ITS_INT ret;
        char buf[MAX_BUF];

        ret = SSL_accept(session);
        // get earliest error code from the thread's 
        // error queue and removes the entry
        if(ret < 0)
        {
            err = ERR_peek_last_error();
            ERR_error_string_n(err, buf, MAX_BUF);
            ITS_TRACE_ERROR(("TLS:Accept Failed:%s\n",buf));
            ERR_clear_error();
        }
        OPENSSL_ERROR_CHECK(ret); 
    }
    else
    {
        return ITS_E_TLSTIMEOUT;
    }
    return ITS_SUCCESS;
}

/*.implementation:public CertificateRequest
************************************************************************
*  Purpose:
*      Setting a Client Certificate request for the session which needs to be exchanged
*           during handshake
*
*  Input:
*
*    Note: Server Sends Certificate by default so no need for this Function
*             in client session
************************************************************************/
int
SslServerSession::CertificateRequest()
{
    if(session == NULL)
    {
        return ITS_E_TLSFAILED; 
    } 
    SSL_set_verify(session,SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, 0); 
    return ITS_SUCCESS;
}


extern "C" void 
AppsSslDebug(const SSL *s, int where, int ret)
{
    const char *str;
    int w;

    w=where& ~SSL_ST_MASK;

    if (w & SSL_ST_CONNECT)
    {
        str="SSL_connect";
    }
    else if (w & SSL_ST_ACCEPT)
    {
         str="SSL_accept";
    }
    else
    {
         str="undefined";
    }

    if (where & SSL_CB_LOOP)
    {
        printf("OPEN SSL  %s:%s\n",str,SSL_state_string_long(s));
    }
    else if (where & SSL_CB_ALERT)
    {
        str=(where & SSL_CB_READ)?"read":"write";
        printf("OPEN SSL  SSL3 alert %s:%s:%s\n",
                str,
                SSL_alert_type_string_long(ret),
                SSL_alert_desc_string_long(ret));
    }
    else if (where & SSL_CB_EXIT)
    {
        if (ret == 0)
        {
            printf("OPEN SSL %s:failed in %s\n",
                    str,SSL_state_string_long(s));
        }
        else if (ret < 0)
        {
           printf("OPEN SSL  %s:error in %s\n",
                    str,SSL_state_string_long(s));
        }
    }
}

void
AppsGnuTlsDebug(int level, const char * msg)
{
    printf("%d : %s \n",level,msg);
}


