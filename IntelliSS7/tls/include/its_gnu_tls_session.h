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
 * LOG: $Log: its_gnu_tls_session.h,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.1.46.1  2013/06/25 10:00:04  jvikram
 * LOG: Merged changes from DRE Branch.
 * LOG:
 * LOG: Revision 1.1.6.1  2012/11/06 12:51:57  pramana
 * LOG: Reverse merged from B-DRE-0212-00-TLS branch for 212-06 release
 * LOG:
 * LOG: Revision 1.1.34.1  2012/11/05 04:22:33  cprem
 * LOG: Fixed some warnings.
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:04:41  nvijikumar
 * LOG: GNUTLS and OPENSSL made seperate
 * LOG:
 * LOG:
 *ID: $Id: its_gnu_tls_session.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/
#ident "$Id: its_gnu_tls_session.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#ifndef __GNU_TLS_SESSION_H__
#define __GNU_TLS_SESSION_H__

#include <stdio.h>
#include <its_tls_common.h>
#include <gnutls/gnutls.h>
#include <gnutls/extra.h>
#include <gnutls/openpgp.h>
#include <gnutls/x509.h>

#define GNUTLS_ERROR_CHECK(ret)                                               \
    do                                                                        \
    {                                                                         \
        if(ret <  GNUTLS_E_SUCCESS)                                           \
        {                                                                     \
            fprintf(stderr, "TLS ERROR: %s\n", gnutls_strerror(ret));         \
            return ret;                                                       \
        }                                                                     \
    }while(0);

#define TLS_THROW_EXCEPTION(ret)                                              \
    do                                                                        \
    {                                                                         \
        if(ret != GNUTLS_E_SUCCESS)                                           \
        {                                                                     \
            fprintf(stderr, "TLS ERROR: %s\n", gnutls_strerror(ret));         \
            throw ITS_E_TLSFAILED;                                            \
        }                                                                     \
    }while(0);

using namespace its;

/* Callback will be called when server request for Client Certificate*/
typedef  int (*CertificateCallback)(gnutls_session session, 
                     const gnutls_datum* req_ca_dn, int nreqs, 
                     const gnutls_pk_algorithm* pk_algos, 
                     int pk_algos_length, gnutls_retr_st* st);
gnutls_datum mmap_file( const char* file);
void munmap_file( gnutls_datum data);

void
AppsGnuTlsDebug(int level, const char *msg);

struct ServerCredential
{
    AUTHENTICATION type;
    union 
    {
        gnutls_certificate_credentials cert_cred;
        gnutls_srp_server_credentials  srp_cred;
        gnutls_anon_server_credentials anon_cred;
    }u;   
};



class X509Certificate
{
public:
    X509Certificate(char * crtFileName)
    {
        gnutls_x509_crt_init(&crt);
        data = mmap_file(crtFileName);
        gnutls_x509_crt_import(crt, (const gnutls_datum *)&data, GNUTLS_X509_FMT_PEM);  
    }
    ~ X509Certificate()
    {
         munmap_file(data);
    }
    
    gnutls_datum data;  
    gnutls_x509_crt crt;

};

class X509Key
{
public: 
    X509Key(char * keyFileName)
    {
        gnutls_x509_privkey_init(&key);
        data = mmap_file(keyFileName);
        gnutls_x509_privkey_import( key, (const gnutls_datum *)&data, GNUTLS_X509_FMT_PEM);
    }
    ~ X509Key()
    {
        munmap_file(data);
    }
    gnutls_datum data;
    gnutls_x509_privkey key;

};
    

class ServerCertificate : public Certificate
{

public:

    /*.implementation:public ServerCertificate
    ************************************************************************
    *  Purpose:
    *      It Allocates credential on the basis of the AUTHENTICATION type
    *
    *  Input:
    *  cred : Authentication
    *    
    ************************************************************************/
    ServerCertificate(AUTHENTICATION cred);
    
    /*.implementation:public ~ ServerCertificate
    ************************************************************************
    *  Purpose:
    *      It frees allocated credential 
    *
    *  Input:
    *    
    ************************************************************************/
    ~ ServerCertificate();
    

    /*.implementation:public SetX509TrustFile
    ************************************************************************
    *  Purpose:
    *      This method sets the X.509 trust file for the allocated credential. 
    *      File is generated using Cert Tool 
    *  Input:
    *   trustFile: File Name, CA file 
    *    
    ************************************************************************/
    int
    SetX509TrustFile( char  * trustFile);
    
    
    /*.implementation:public SetX509CrlFile
    ************************************************************************
    *  Purpose:
    *      This method sets the X.509  file for the allocated credential. 
    *      File is generated using Cert Tool 
    *  Input:
    *   crlFile: File Name 
    *    
    ************************************************************************/
    int
    SetX509CrlFile( char  * crlFile);
    
    /*.implementation:public SetX509KeyFile
    ************************************************************************
    *  Purpose:
    *      This method sets the X.509 certificate & Key file for the allocated credential. 
    *      File is generated using Cert Tool 
    *  Input:
    *   certFile: Cert File Name 
    *   keyFile : Key file Name
    *    
    ************************************************************************/
    int
    SetX509KeyFile( char * certFile, char * keyFile );
    
   
    /*.implementation:public SetPgpKeyRingFile
    ************************************************************************
    *  Purpose:
    *      This method sets the OPEN PGP key ring  file for the allocated credential. 
    *      File is generated using Cert Tool 
    *  Input:
    *   keyRingFile: File Name 
    *    
    ************************************************************************/
    int
    SetPgpKeyRingFile( char * keyRingFile );
    
   

    /*.implementation:public SetPgpKeyFile
    ************************************************************************
    *  Purpose:
    *      This method sets the OPEN PGP certFile & keyFile for the allocated credential
    *
    *  Input:
    *     certFile : Certificate file name
    *     keyFile : Key File name
    *    
    ************************************************************************/
    int
    SetPgpKeyFile( char * certFile, char * keyFile );
    
    /*.implementation:public SetSrpPasswdFile
    ************************************************************************
    *  Purpose:
    *      This method sets the SRP password & password config file
    *
    *  Input:
    *     passwdFile : Password File Name
    *   passwdConfFile : Password Config file Name 
    ************************************************************************/
    int
    SetSrpPasswdFile( char  * passwdFile, char * passwdConfFile );
    

    /*.implementation:public CredentialSetDefaultFile
    ************************************************************************
    *  Purpose:
    *      This method sets Default File.
    *
    *  Input:
    *    
    ************************************************************************/
    int
    CredentialSetDefaultFile();
    
    /*Server Credentials, current implementation uses cerificate type*/
    ServerCredential cert;

};
struct ClientCredential
{
    AUTHENTICATION type;
    union 
    {
        gnutls_anon_client_credentials anon_cred;
        gnutls_certificate_credentials cert_cred;
        gnutls_srp_client_credentials srp_cred;

    }u;
};


class ClientCertificate : public Certificate
{
public:

    /*.implementation:public ClientCertificate
    ************************************************************************
    *  Purpose:
    *    Allocating Client Credential on the basis of AUTHENTICATION type
    *
    *  Input:
    *   cred : Authentication type    
    ************************************************************************/
    ClientCertificate(AUTHENTICATION cred);
    
    
    /*.implementation:public ~ClientCertificate
    ************************************************************************
    *  Purpose:
    *      Destructor to free already allocated Client Credential
    *
    *  Input:
    *    
    ************************************************************************/
    ~ ClientCertificate(); 
    
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
    SetX509TrustFile( char * trustFile );
       
    
    /*.implementation:public SetX509KeyFile
    ************************************************************************
    *  Purpose:
    *      This method sets the X.509 certificate & Key file for the allocated credential. 
    *      File is generated using Cert Tool 
    *  Input:
    *   certFile: Cert File Name 
    *   keyFile : Key file Name
    *    
    ************************************************************************/
    int
    SetX509KeyFile( char * certFile, char * keyFile );
    
    /*.implementation:public SetSrpPasswd 
    ************************************************************************
    *  Purpose:
    *      This Method will sets the username & Password at client side 
    *      User Name and Password will be used for Authentication
    *
    *  Input:
    *     username : user Name
    *     passwd   : Password
    *    
    ************************************************************************/
    int
    SetSrpPasswd( char  * username, char * passwd );

    /*.implementation:public CertificateCallback
    ************************************************************************
    *  Purpose:
    *      This method sets a Callback by the client when server requests
    *      for certificate     
    *
    *  Input:
    *   certCallback : Pointer to function of type CertificateCallback
    *    
    ************************************************************************/    
    void
    SetCertificateCallback(CertificateCallback  certCallback);
    
    /* Client Credentials*/
    ClientCredential cert;

};

class GnuTlsSession : public  TlsSession
{
public:
    /*.implementation:public TlsSession
    ************************************************************************
    *  Purpose:
    *      This method creates a Initilize a new session & sets the 
    *      default priority.
    *      This Method also sets Transport ptr i.e Socket descriptor to 
    *      access transport layer
    *
    *  Input:
    *    endPt : Tells the end point ie client or server   
    *    sockInfo : Socket Descriptor of transport layer
    *
    *  Output: gnutls_session
    *
    * Note: This will set Session
    ************************************************************************/
    GnuTlsSession(END_POINT_TYPE endPt, int sockInfo);
    

    /*.implementation:public ~ TlsSession
    ************************************************************************
    *  Purpose:
    *      This method creates a deletes a session from Tls data base
    *
    *  Input:
    *    
    ************************************************************************/
    virtual
    ~ GnuTlsSession();
   

    
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
    RecordSend(char * msg,  int sizeMsg);
    
    /*.implementation:public RecordRecieve
    ************************************************************************
    *  Purpose:
    *      Method to Recieve Record from Tls Layer which internally using Transport layer 
    *      Recieve     
    *
    *  Input:
    *  buff: Pointer to buffer
    *  sizeBuff : Size of buffer 
    *    
    ************************************************************************/
    int
    RecordRecieve(char  *   buffer, int sizeBuff);
    
    /*.implementation:public RecordPending
    ************************************************************************
    *  Purpose:
    *    Method to Check if any Record is pending for session to recieve
    *
    *  Input:
    *
    *  Note: You can use this before RecordRecieve if you don't want
    *         RecordRecieve to block
    ************************************************************************/
    int
    RecordPending(); 

    /*.implementation:public CheckAlert
    ************************************************************************
    *  Purpose:
    *    Method to Check for the Last Alert. When Record recieve failed
    *
    *  Input:
    *   ret = Return value of RecordRecieve  
    ************************************************************************/
    int
    CheckAlert(int ret);
    
    /*.implementation:public VerifyCertificate
    ************************************************************************
    *  Purpose:
    *    Method to Verify Peers Certificate, Expiry , Activation time & HostName
    *
    *  Input:
    *   HostName: Trusted Domain Name of the Certificate.
    *   realmName : Realm Name
    ************************************************************************/
    int
    VerifyCertificate ( const char *hostname, const char * realName);

    /*.implementation:public GetCertificateType
    ************************************************************************
    *  Purpose:
    *   Get The type of certificate for the Session
    *
    *  Input:
    *
    * Return:
    *   Certificate Type: CRT or OPEN PGP
    ************************************************************************/
    int 
    GetCertificateType();


    /*Session Created after Init*/  
    gnutls_session  session;
    /*Socket descriptor of transport Layer*/

private:
    GnuTlsSession();
    GnuTlsSession(const GnuTlsSession &);
    GnuTlsSession & operator=(const GnuTlsSession &);
};

class TlsClientSession : public GnuTlsSession
{
public:

    /*.implementation:public TlsClientSession
    ************************************************************************
    *  Purpose:
    *      Method will Call Tls Session constructor with end point type Client & 
    *      Socket descriptor
    *
    *  Input:
    *   SockInfo:  Socket Descriptor   
    *    
    ************************************************************************/
    TlsClientSession( int sockInfo) 
        :GnuTlsSession(CLIENT, sockInfo)
    {   

    }


    /*.implementation:public ~ TlsClientSession
    ************************************************************************
    *  Purpose:
    *      
    *
    *  Input:
    *    
    ************************************************************************/
    ~ TlsClientSession()
    {

    }

    /*.implementation:public Handshake
    ************************************************************************
    *  Purpose:
    *      This method will perform Tls Handshake with the peer.
    *
    *  Input:
    *
    * Note: All Cipher Suite Negotiation & Certificate & key Exchange is
    *       done in this Method    
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


    /*.implementation:public SetRecordMaxSize
    ************************************************************************
    *  Purpose:
    *      Setting the Max size of record, offered by client and
    *      accepted by server 
    *
    *  Input:
    *      size: size of max record ,
    *
    *  Note:
    *   Acceptable values are 512(=2^9), 1024(=2^10),
    *   2048(=2^11) and 4096(=2^12).
    *    
    ************************************************************************/
    int
    SetRecordMaxSize(int size);
    
    /*.implementation:public SetPriority
    ************************************************************************
    *  Purpose:
    *      Method to set priority of various Authentication elements
    *      like Cipher, Key Exchange
    *      MAC, Compression, Protocol & Certificate
    *
    *  Input:
    *   type: Priority of which authentication Element want to set
    *   Priority: List of priority of the corresponding element terminated by 0  
    *    
    ************************************************************************/
    int
    SetPriority(PRIORITY_TYPE type , const int * priority);
    
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
    CredentialSet(Certificate * cliCert);
 
private:
    TlsClientSession();
    TlsClientSession(const TlsClientSession &);
    TlsClientSession & operator=(const TlsClientSession &);
    
};

class TlsServerSession : public GnuTlsSession
{
public:

    /*.implementation:public TlsServerSession
    ************************************************************************
    *  Purpose:
    *      Method will Call Tls Session constructor with end point type Server & 
    *      Socket descriptor
    *
    *  Input:
    *   SockInfo:  Socket Descriptor   
    *    
    ************************************************************************/
    TlsServerSession(int sockInfo)
        :GnuTlsSession(SERVER, sockInfo)
    {

    }

    /*.implementation:public ~ TlsServerSession
    ************************************************************************
    *  Purpose:
    *
    *      
    *  Input:
    *    
    ************************************************************************/
    ~ TlsServerSession()
    {
    }

    /*.implementation:public Handshake
    ************************************************************************
    *  Purpose:
    *      This method will perform Tls Handshake with the peer.
    *
    *  Input:
    *
    * Note: All Cipher Suite Negotiation & Certificate & key Exchange is
    *       done in this Method    
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


    /*.implementation:public RehandShake
    ************************************************************************
    *  Purpose:
    *      Method to send a alert to client for Rehandshake for the same session
    *
    *  Input:
    *    
    ************************************************************************/
    int
    RehandShake();
    
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
    
    /*.implementation:public CredentialSet
    ************************************************************************
    *  Purpose:
    *   Setting the Credential for the server session    
    *
    *  Input:
    *   servCert: ServerCertificate 
    *    
    ************************************************************************/
    
     int
     CredentialSet(Certificate * servCert);

private:
     
     TlsServerSession();
     TlsServerSession(const TlsServerSession &);
     TlsServerSession & operator=(const TlsServerSession &);

};

#endif /* __TLS_SESSION_H__ */
