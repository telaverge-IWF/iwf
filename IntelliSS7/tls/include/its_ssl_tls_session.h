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
 * LOG: $Log: its_ssl_tls_session.h,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.2.46.1  2013/06/25 10:00:04  jvikram
 * LOG: Merged changes from DRE Branch.
 * LOG:
 * LOG: Revision 1.2.6.2  2012/11/20 08:31:36  cprem
 * LOG: Merged from B-DRE-0212-00-TLS branch for 07 release
 * LOG:
 * LOG: Revision 1.2.34.3  2012/11/19 09:45:47  jvikram
 * LOG: Added for CRL Support
 * LOG:
 * LOG: Revision 1.2.34.2  2012/11/06 08:32:27  jvikram
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 1.2.34.1  2012/11/05 04:23:12  cprem
 * LOG: Added a mutex to fix issue with multiple threads. SSL Context and Session are protected by this Mutex.
 * LOG: Revision 1.2  2010/07/09 10:41:57  nvijikumar
 *
 * LOG: Compilation issue fix with TCS flags
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:04:41  nvijikumar
 * LOG: GNUTLS and OPENSSL made seperate
 * LOG:
 * LOG:
 *
 *ID: $Id: its_ssl_tls_session.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/

#ident "$Id: its_ssl_tls_session.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#ifndef __SSL_TLS_SESSION_H__
#define __SSL_TLS_SESSION_H__

#include <its_tls_common.h>
#include <openssl/ssl.h>
#include <CAu.h>

using namespace its;

extern "C" void AppsSslDebug(const SSL *s, int where, int ret);

class SSLContext : public Certificate
{
public:

    /*.implementation:public SetX509TrustFile
    ************************************************************************
    *  Purpose:
    *       Constructor to create context of Open SSL
    *
    *  Input:
    *      type: CLIENT or SERVER 
    *
    *  Note: In Open SSL Credentials is not there, Context is used to set
    *        Certificates    
    ************************************************************************/
    SSLContext(END_POINT_TYPE type);

    /*.implementation:public SetX509TrustFile
    ************************************************************************
    *  Purpose:
    *       Deleting the Already created ContextL
    *
    *  Input:
    *    
    ************************************************************************/
    ~ SSLContext();

    /*.implementation:public SetX509TrustFile
    ************************************************************************
    *  Purpose:
    *      Method to set trust file for X.509 Authentication type  
    *
    *  Input:
   *      trustFile: CA file 
    *    
    ************************************************************************/
    int
    SetX509TrustFile( char  * trustFile);
    
    int
    SetX509TrustFile( char  * MasterCAFile, char * cAPath);

    /*.implementation:public SetX509KeyFile
    ************************************************************************
    *  Purpose:
    *      This method sets the X.509 certificate & Key file for the Context. 
    *      File is generated using Cert Tool 
    *  Input:
    *   certFile: Cert File Name 
    *   keyFile : Key file Name
    *    
    ************************************************************************/
    int
    SetX509KeyFile( char * certFile, char * keyFile );

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
    int EnableCrlCheck(std::vector<its::CertificateAuthority*>& CA, std::string crlPath);


    /* In Open SSL Context is used to set certificate, there is no credentials*/
    SSL_CTX *ctxt;

private:
    END_POINT_TYPE endType;
    SSLContext();
    SSLContext(const SSLContext &);
    SSLContext & operator=(const SSLContext &);
     
};

class OpenSslTlsSession : public  TlsSession
{
public:
    /*.implementation:public OpenSslTlsSession  
    ************************************************************************
    *  Purpose: CONSTRUCTOR Create Open SSL  Tls Session
    *
    *
    *  Input:
    *     sd : Socket descriptor
    *
    *  Note : Creating a session does't create a session, you have to set 
    *         credentials to use session.
    ************************************************************************/ 
    OpenSslTlsSession(int sd);

    /*.implementation:public OpenSslTlsSession  
    ************************************************************************
    *  Purpose: Destructor Delete Open SSL  Tls Session
    *
    *
    *  Input:
    *
    ************************************************************************/
    virtual
    ~OpenSslTlsSession();

    /*.implementation:public Bye
    ************************************************************************
    *  Purpose:
    *      This method Says Good Bye to another end Point. It will close further Read 
    *      & Write
    *
    *  Input:
    *    
    ************************************************************************/
    void
    Bye();

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
    * Note:     
    ************************************************************************/
    int 
    RecordRecieve(char * buff, int buffSize);

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
    * Note:     
    ************************************************************************/
    int 
    RecordSend(char * msg, int msgSize);

    /*.implementation:public CredentialSet
    ************************************************************************
    *  Purpose:
    *     Setting the credential for client session.
    *
    *  Input:
    *   cliCert: Pointer to ClientCertificate class
    *    
    ************************************************************************/
    
    int
    CredentialSet(Certificate * ctx);

    /*.implementation: public VerifyCertificate
    ************************************************************************
    *  Purpose:
    *    Method to Verify Peers Certificate, Expiry , Activation time & HostName
    *
    *  Input:
    *   HostName: Trusted Domain Name of the Certificate.
    *   realmName : Realm Name
    ************************************************************************/
    int
    VerifyCertificate(const char * hostname, const char * realmName);

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
    SetCipherSuite(int * cipherSuiteList);


    SSL * session; 
    SSL_CTX * sessCtx;
	pthread_mutex_t tlsSessionLock;
private : 

    OpenSslTlsSession();
    OpenSslTlsSession(const OpenSslTlsSession &);
    OpenSslTlsSession & operator=(const OpenSslTlsSession &);
};

class SslClientSession : public  OpenSslTlsSession
{   
public:
   
    /*.implementation:public SslClientSession  
    ************************************************************************
    *  Purpose: CONSTRUCTOR Create Client Session for Open SSL 
    *
    *
    *  Input:
    *     sd : Socket descriptor
    *
    *  Note : Creating a session does't create a session, you have to set 
    *         credentials to use session.
    ************************************************************************/ 
    SslClientSession(int sd)
        :OpenSslTlsSession(sd)
    {

    }
    /*.implementation:public SslClientSession  
    ************************************************************************
    *  Purpose: Delete Session from data base 
    *
    *
    *  Input:
    *
    ************************************************************************/
    ~ SslClientSession()
    {

    }
    
    /*.implementation:public Handshake
    ************************************************************************
    *  Purpose:
    *      This method will perform Tls Handshake with the Server.
    *
    *  Input:
    *
    * Note: All Cipher Suite Negotiation & Certificate & key Exchange is
    *       done in this Method. Implementation of Handshake in Open SSL is 
    *       different for Client & Server unlike Gnu Tls. In which implementation
    *       is Same    
    ************************************************************************/
    int
    Handshake();

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
    virtual
    int
    Handshake(int time);


   
private:
    SslClientSession();
    SslClientSession(const SslClientSession &);
    SslClientSession & operator=(const SslClientSession &);
 
};
class SslServerSession : public  OpenSslTlsSession
{   
public:

    /*.implementation:public SslServerSession  
    ************************************************************************
    *  Purpose: CONSTRUCTOR Create Server Session for Open SSL 
    *
    *
    *  Input:
    *     sd : Socket descriptor
    *
    *  Note : Creating a session does't create a session, you have to set 
    *         credentials to use session.
    ************************************************************************/
    SslServerSession(int sd)
        :OpenSslTlsSession(sd) 
    {

    }

    /*.implementation:public SslServerSession  
    ************************************************************************
    *  Purpose: Delete Session from data base 
    *
    *
    *  Input:
    *
    ************************************************************************/
    ~ SslServerSession()
    {

    }
    
    /*.implementation:public Handshake
    ************************************************************************
    *  Purpose:
    *      This method will perform Tls Handshake with the Client.
    *
    *  Input:
    *
    * Note: All Cipher Suite Negotiation & Certificate & key Exchange is
    *       done in this Method. Implementation of Handshake in Open SSL is 
    *       different for Client & Server unlike Gnu Tls. In which implementation
    *       is Same    
    ************************************************************************/
    int
    Handshake();

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
    virtual
    int
    Handshake(int time);


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
    CertificateRequest();

private:

    SslServerSession();
    SslServerSession(const SslServerSession &);
    SslServerSession & operator=(const SslServerSession &);
 
};
#endif /* __TLS_SESSION_H__ */
