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
 * LOG: $Log: its_gnu_tls_session.cpp,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:03:42  nvijikumar
 * LOG: GNUTLS and OPENSSL made separate
 * LOG:
 * LOG:
 *
 *ID: $Id: its_gnu_tls_session.cpp,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/
#ident "$Id: its_gnu_tls_session.cpp,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#include <its_gnu_tls_session.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <pthread.h>
#include <string>
#if defined(solaris) || defined (solaris64)
#include <sys/filio.h>
#endif

#include <gcrypt.h>

GCRY_THREAD_OPTION_PTHREAD_IMPL;

static pthread_mutex_t tlsLock = PTHREAD_MUTEX_INITIALIZER;

/*.implementation:public ServerCertificate
************************************************************************
*  Purpose:Constructor
*      It Allocates credential on the basis of the AUTHENTICATION type
*
*  Input:
*  cred : Authentication
*
************************************************************************/
ServerCertificate::ServerCertificate(AUTHENTICATION cred)
{   int ret;
    switch(cred)
    {
        case X_509:
            cert.type = X_509;
            ret = gnutls_certificate_allocate_credentials (&(cert.u.cert_cred));
            TLS_THROW_EXCEPTION(ret); 
            break;
        case OPEN_PGP:
            cert.type = OPEN_PGP;
            ret = gnutls_certificate_allocate_credentials (&(cert.u.cert_cred));
            TLS_THROW_EXCEPTION(ret);
            break;
        case SRP:
            cert.type = SRP;
            //ret = gnutls_srp_allocate_server_credentials (&(cert.u.srp_cred));        
            break;
        case ANONYMOUS:
            cert.type = ANONYMOUS; 
            ret = gnutls_anon_allocate_server_credentials (&(cert.u.anon_cred));
            TLS_THROW_EXCEPTION(ret);
            break;
        default:
            cert.type = INVALID_AUTH;  
            break; 
    }
}

/*.implementation:public ~ ServerCertificate
************************************************************************
*  Purpose: Destructor
*      It frees allocated credential
*
*  Input:
*
************************************************************************/

ServerCertificate::~ ServerCertificate()
{      
    switch(cert.type)
    {
        case X_509:
        case OPEN_PGP:    
            gnutls_certificate_free_credentials (cert.u.cert_cred);
            break;
        case SRP:
            //gnutls_srp_free_server_credentials (cert.u.srp_cred);   
            break;
        case ANONYMOUS:
            gnutls_anon_free_server_credentials (cert.u.anon_cred);
            break;
        default:
            break;
    }
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
ServerCertificate::SetX509TrustFile( char  * trustFile)
{
    int ret; 
    if(trustFile != NULL && cert.type == X_509)
    {
        pthread_mutex_lock(&tlsLock);  
        ret = gnutls_certificate_set_x509_trust_file (cert.u.cert_cred, 
                                                       trustFile,
                                                       GNUTLS_X509_FMT_PEM);   
        pthread_mutex_unlock(&tlsLock);  
        GNUTLS_ERROR_CHECK(ret);
    }
    return ITS_E_TLSFAILED;
}
    
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
ServerCertificate::SetX509CrlFile( char  * crlFile)
{
    int ret;
    if(crlFile != NULL && cert.type == X_509)
    {
        pthread_mutex_lock(&tlsLock);  
        ret =  gnutls_certificate_set_x509_crl_file (cert.u.cert_cred, crlFile,
                                                     GNUTLS_X509_FMT_PEM);   
        pthread_mutex_unlock(&tlsLock);  
        GNUTLS_ERROR_CHECK(ret);
    }
    return ITS_E_TLSFAILED;
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
ServerCertificate::SetX509KeyFile( char * certFile, char * keyFile )
{
    int ret;
    if(certFile != NULL && keyFile != NULL && cert.type == X_509)
    {
        pthread_mutex_lock(&tlsLock);  
        ret =  gnutls_certificate_set_x509_key_file (cert.u.cert_cred, 
                                                     certFile, keyFile,
                                                     GNUTLS_X509_FMT_PEM); 
        pthread_mutex_unlock(&tlsLock);  
        GNUTLS_ERROR_CHECK(ret);
    }
    return ITS_E_TLSFAILED;
}

 /*.implementation:public SetPgpKeyRingFile
************************************************************************
*  Purpose:
*      This method sets the OPEN PGP key ring  file for the i
*       allocated credential.
*      File is generated using Cert Tool
*
*  Input:
*      keyRingFile: File Name
*
************************************************************************/
   
int
ServerCertificate::SetPgpKeyRingFile( char * keyRingFile )
{
    if( keyRingFile != NULL && cert.type == OPEN_PGP)
    {
        //return gnutls_certificate_set_openpgp_keyring_file (cert.u.cert_cred, 
          //                                                  keyRingFile ); 
    }
    return ITS_E_TLSFAILED;
}
   
/*.implementation:public SetPgpKeyFile
************************************************************************
*  Purpose:
*      This method sets the OPEN PGP certFile & keyFile for the
*       allocated credential
*
*  Input:
*     certFile : Certificate file name
*     keyFile : Key File name
*
************************************************************************/

int
ServerCertificate::SetPgpKeyFile( char * certFile, char * keyFile )
{
    if(certFile != NULL && keyFile != NULL && cert.type == OPEN_PGP)
    {
        //return gnutls_certificate_set_openpgp_key_file (cert.u.cert_cred, 
          //                                              certFile, keyFile );      
    }
    return ITS_E_TLSFAILED;
}           

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
ServerCertificate::SetSrpPasswdFile( char  * passwdFile, 
                                         char * passwdConfFile )
{
    if(passwdFile != NULL && passwdConfFile != NULL && cert.type == SRP)
    {
        //return gnutls_srp_set_server_credentials_file (cert.u.srp_cred, 
          //                                             passwdFile,
            //                                           passwdConfFile);
    }
    return ITS_E_TLSFAILED;
}           

/*.implementation:public CredentialSetDefaultFile
************************************************************************
*  Purpose:
*      This method sets Default File.
*
*  Input:
*
************************************************************************/

int
ServerCertificate::CredentialSetDefaultFile()
{
    int ret = !GNUTLS_E_SUCCESS;
    switch(cert.type)
    {
        case X_509:
            ret = gnutls_certificate_set_x509_trust_file (cert.u.cert_cred,CAFILE, 
                                                    GNUTLS_X509_FMT_PEM);
            GNUTLS_ERROR_CHECK(ret);
            ret = gnutls_certificate_set_x509_crl_file (cert.u.cert_cred,CRLFILE, 
                                                  GNUTLS_X509_FMT_PEM);
            GNUTLS_ERROR_CHECK(ret);
            ret = gnutls_certificate_set_x509_key_file (cert.u.cert_cred, 
                                                  CERTFILE,KEYFILE,
                                                  GNUTLS_X509_FMT_PEM);            
            break;
#if 0
        case OPEN_PGP:
            gnutls_certificate_set_openpgp_keyring_file (cert.u.cert_cred, 
                                                         PGPRINGFILE );
            gnutls_certificate_set_openpgp_key_file (cert.u.cert_cred, 
                                                     PGPCERTFILE,
                                                     PGPKEYFILE  );
            break;
        case SRP:
            gnutls_srp_set_server_credentials_file (cert.u.srp_cred,
                                                    SRP_PASSWD ,
                                                    SRP_PASSWD_CONF  );
            break;
#endif
        case OPEN_PGP:
        case SRP:
        case INVALID_AUTH:    
        case ANONYMOUS:
        default:    
            break;
    }
    return ret;

}


/*.implementation:public ClientCertificate
************************************************************************
*  Purpose: CONSTRUCTOR
*    Allocating Client Credential on the basis of AUTHENTICATION type
*
*  Input:
*   cred : Authentication type
************************************************************************/
ClientCertificate::ClientCertificate(AUTHENTICATION cred)
{
    int ret;
    switch(cred)
    {
        
        case ANONYMOUS:
        cert.type = ANONYMOUS;
            ret = gnutls_anon_allocate_client_credentials (&(cert.u.anon_cred));   
            TLS_THROW_EXCEPTION(ret);
            break;
        case X_509:
        cert.type = X_509;
            ret = gnutls_certificate_allocate_credentials (&(cert.u.cert_cred));
            TLS_THROW_EXCEPTION(ret);
            break;
        case SRP:
        cert.type = SRP;
            //gnutls_srp_allocate_client_credentials(&(cert.u.srp_cred));        
            break;
        default:
            cert.type = INVALID_AUTH;  
            break;

    }
    
}

/*.implementation:public ~ClientCertificate
************************************************************************
*  Purpose: DESTRUCTOR
*      Destructor to free already allocated Client Credential
*
*  Input:
*
************************************************************************/

ClientCertificate::~ ClientCertificate()  
{
    
    switch(cert.type)
    {
        case ANONYMOUS:
            gnutls_anon_free_client_credentials (cert.u.anon_cred);
            break;
        case X_509:
            gnutls_certificate_free_credentials (cert.u.cert_cred);
            break;
        case SRP:
            //gnutls_srp_free_client_credentials (cert.u.srp_cred);
            break;        
        case PSK:
        default:
            break;
    }

}

/*.implementation:public SetX509TrustFile
************************************************************************
*  Purpose:
*      Method to set trust file for X.509 Authentication type
*
*  Input:
*
************************************************************************/

int
ClientCertificate::SetX509TrustFile( char * trustFile )
{
    int ret; 
    if(cert.type == X_509 )
    {
         
        pthread_mutex_lock(&tlsLock);  
        ret = gnutls_certificate_set_x509_trust_file(cert.u.cert_cred, 
                                                      trustFile, 
                                                      GNUTLS_X509_FMT_PEM);
        pthread_mutex_unlock(&tlsLock);  
        GNUTLS_ERROR_CHECK(ret); 
    }
    return ITS_E_TLSFAILED;
    
}  

/*.implementation:public SetX509KeyFile
************************************************************************
*  Purpose:
*      This method sets the X.509 certificate & Key file for the
*      allocated credential.
*      File is generated using Cert Tool
*  Input:
*   certFile: Cert File Name
*   keyFile : Key file Name
*
************************************************************************/

int
ClientCertificate::SetX509KeyFile( char * certFile, char * keyFile )
{
    int ret;
    if(certFile != NULL && keyFile != NULL && cert.type == X_509)
    {
        pthread_mutex_lock(&tlsLock);  
    ret = gnutls_certificate_set_x509_key_file (cert.u.cert_cred, certFile, 
                                              keyFile, GNUTLS_X509_FMT_PEM); 
        pthread_mutex_unlock(&tlsLock);  
        GNUTLS_ERROR_CHECK(ret); 
    }
    return ITS_E_TLSFAILED;
}

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
ClientCertificate::SetSrpPasswd( char  * username, char * passwd )
{
    if(cert.type == SRP)
    {
        //return gnutls_srp_set_client_credentials(cert.u.srp_cred, 
          //                                       username, passwd);       
    }
    return ITS_E_TLSFAILED; 
}

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
ClientCertificate::SetCertificateCallback(CertificateCallback  certCallback)
{
    gnutls_certificate_client_set_retrieve_function(cert.u.cert_cred, 
                                                    certCallback);
}



/*.implementation:public GnuTlsSession
************************************************************************
*  Purpose: CONSTRUCTOR
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

GnuTlsSession::GnuTlsSession(END_POINT_TYPE endPt, int sockInfo)
{
    int ret;
    switch(endPt)
    {
        case SERVER:
            sock = sockInfo;
            ret = gnutls_init (&session, GNUTLS_SERVER);  
            TLS_THROW_EXCEPTION(ret);
            break;
        case CLIENT:
            sock = sockInfo;
            ret = gnutls_init (&session, GNUTLS_CLIENT);         
            TLS_THROW_EXCEPTION(ret);
            break;
        default:
            break;  
    }
    gnutls_set_default_priority(session);
    sock = sockInfo;
    gnutls_transport_set_ptr (session,(gnutls_transport_ptr) sock);
    
}

/*.implementation:public ~ GnuTlsSession
************************************************************************
*  Purpose: DESTRUCTOR
*      This method creates a deletes a session from Tls data base
*
*  Input:
*
************************************************************************/
    
GnuTlsSession::~ GnuTlsSession()
{
    gnutls_deinit (session);            
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
GnuTlsSession::Bye()
{
    gnutls_bye (session, GNUTLS_SHUT_RDWR);
    
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
GnuTlsSession::RecordSend(char * msg,  int sizeMsg)
{

    int    nleft;
    int    nwritten;

    if(!(msg) || !(sizeMsg))
    {
        return ITS_ENULLPTR;

    }

    /* Set up how much we need to write */
    nleft = sizeMsg;


    /* While still bytes to write do so */
    while (nleft > 0)
    {
    /* Write some data */
        nwritten =  gnutls_record_send (session, msg, sizeMsg);


    /* If any of these errors return # actually written */
        if (nwritten <= 0 )
        {
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
    return (sizeMsg);
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
GnuTlsSession::RecordRecieve(char * buffer, int sizeBuff)
{
    int ret;
    if(buffer == NULL || sizeBuff == 0)
    {       
        return ITS_ENULLPTR;
    }     
    ret =  gnutls_record_recv (session, buffer, sizeBuff);
    return ret;
}

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
GnuTlsSession::RecordPending()
{
    int ret;
    ret = gnutls_record_check_pending(session); 
    GNUTLS_ERROR_CHECK(ret);
    return ITS_SUCCESS;
}

/*.implementation:public CheckAlert
************************************************************************
*  Purpose:
*    Method to Check for the Last Alert. When Record recieve failed
*
*  Input:
*   ret = Return value of RecordRecieve
*
************************************************************************/
int
GnuTlsSession::CheckAlert(int ret)
{
    int lastAlert = 0;
    if (ret == GNUTLS_E_WARNING_ALERT_RECEIVED
        || ret == GNUTLS_E_FATAL_ALERT_RECEIVED)
    {
        lastAlert = gnutls_alert_get (session);
        /* The check for renegotiation is only useful if we are
         *  a server, and we had requested a rehandshake.  */
    }  
    return lastAlert;
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
GnuTlsSession::VerifyCertificate ( const char *hostname , const char * realmName)
{
    unsigned int status;
    const gnutls_datum *cert_list;
    unsigned int cert_list_size;
    int ret;
    gnutls_x509_crt cert;
    char *stPtr = NULL, *endPtr = NULL;
    char dn[256],cn[128];
    size_t size;
    /* This verification function uses the trusted CAs in the credentials
     * structure. So you must have installed one or more CA certificates.
     */
    if(!hostname)
    {
        return ITS_E_TLSFAILED;
    }
    ret = gnutls_certificate_verify_peers2 (session, &status);
    GNUTLS_ERROR_CHECK(ret);
    if (status & GNUTLS_CERT_INVALID)
    {
        printf("certificate is invalid \n");
        return ITS_E_TLSFAILED;
    }   
    else if (status & GNUTLS_CERT_SIGNER_NOT_FOUND)
    {
        printf("certificate is SIGNER \n");
        return ITS_E_TLSFAILED;
    }
    else if (status & GNUTLS_CERT_REVOKED)
    {
        printf("certificate is REVOK \n");
        return ITS_E_TLSFAILED;
    }
    else
    {
        printf("certificate is valid \n");
    }
    /* Up to here the process is the same for X.509 certificates and
     * OpenPGP keys. From now on X.509 certificates are assumed. This can
     * be easily extended to work with openpgp keys as well.
     */
    cert_list = gnutls_certificate_get_peers (session, &cert_list_size);
    if (cert_list == NULL)
    {
        printf("Unable to get certificate \n");
        return ITS_E_TLSFAILED;
    }

    if (gnutls_certificate_type_get (session) == GNUTLS_CRT_X509)
    {
        while(cert_list_size)
        {
            if (gnutls_x509_crt_init (&cert) < 0)
            {
                        printf("Invalid Certificate \n");
                return ITS_E_TLSFAILED;
            }
            /* This is not a real world example, since we only check the first
             * certificate in the given chain.
             */
            if (gnutls_x509_crt_import (cert, 
                &cert_list[cert_list_size -1], GNUTLS_X509_FMT_DER) < 0)
            {
                        printf(" Invalid Certificate  \n");
                return ITS_E_TLSFAILED;
            }
            /* Beware here we do not check for errors.
             */
            if (gnutls_x509_crt_get_expiration_time (cert) < time (0))
            {
                        printf("Expired Certificate\n");
                return ITS_E_TLSFAILED;
            }
            if (gnutls_x509_crt_get_activation_time (cert) > time (0))
            {
                        printf("Unactivated Certificate \n");
                return ITS_E_TLSFAILED;
            }
            if (!gnutls_x509_crt_check_hostname (cert, hostname))
            {
                if (!gnutls_x509_crt_check_hostname (cert,realmName ))
                {
                    size = sizeof(dn);
                    gnutls_x509_crt_get_dn(cert,dn,&size );
                    dn[255] = '\0';
                    stPtr = strstr(dn, "CN=");
                    endPtr= strstr(dn, ",UID");
                    if(stPtr == NULL || endPtr == NULL)
                    {
                        printf("Certificate is Corrupted \n");
                        return ITS_E_TLSFAILED;
                    }
                    stPtr = stPtr + 3;  /* 3 is Size of string "CN="*/ 
                    /* Common Name always comes between subtring "CN=" 
                       & ",UID" */
                    memcpy(cn,stPtr, endPtr - stPtr);
                    cn[endPtr-stPtr] = '\0';
                    if(strcmp(cn, hostname))
                    {
                        printf("HOST NAME MIS MATCH \n");
                        return ITS_E_TLSFAILED;
 
                    }
		    else
		    {
		        printf("Host Name MATCHED With COMMON Name \n");
		    }
                }
		else
		{
		    printf("Realm Name MATCHED With DNS Name \n");
		}
            }
            else
            {
	        printf("Host Name MATCHED With DNS Name \n");
	    }
            gnutls_x509_crt_deinit (cert);
            cert_list_size--;
        }
    }
    else
    {
       return ITS_E_TLSFAILED;
    } 
    return ITS_SUCCESS;
}

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
GnuTlsSession::GetCertificateType()
{
    return gnutls_certificate_type_get(session);
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
TlsClientSession::Handshake()
{   
    int ret; 
    ret = gnutls_handshake (session);       
    GNUTLS_ERROR_CHECK(ret);
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
TlsClientSession::Handshake(int timeout)
{
    int ret , ioctlVal =1;
    fd_set fdSet;
    struct timeval tOut;
    FD_ZERO(&fdSet);
    FD_SET(sock,&fdSet);

    tOut.tv_sec = timeout;
    tOut.tv_usec = 0;

    /* Making the Socket Non Blocking by calling IOCTL to Make
       Handshake at Client Non Blocking*/

    ioctl(sock,FIONBIO,&ioctlVal);
    pthread_mutex_lock(&tlsLock);  

    /* Now Client will send a Client Hello and will come out of 
       Handshake with a return value  GNUTLS_E_AGAIN. So Next time
       when handshake will be called it will continue handshake & will
       not send Client Hello again */
    ret = gnutls_handshake(session);
    pthread_mutex_unlock(&tlsLock);  

    /* Making the Socket Blocking again by changing the Ioctl val =0*/
    ioctlVal = 0;
    ioctl(sock,FIONBIO,&ioctlVal);

    /* Issue id: 1218 - TLS handshake procedure is not executing properly
    ** sometimes gnutls_handshake was completing the handshake and returing success 
    ** in 1st call itself which was not handled.
    */ 
    if(ret == GNUTLS_E_SUCCESS)
    {
        return ITS_SUCCESS;
    }

    if(ret == GNUTLS_E_AGAIN)
    {
    /* Handshake inside the select call with timeout to make handshake time
       out*/
        select(sock+1,&fdSet,NULL,NULL,&tOut);
        if(FD_ISSET(sock,&fdSet))
        {
            pthread_mutex_lock(&tlsLock);  

    /* Now this handshake is Blocking but we will come here if
       there will be any data on the socket, Now handshake will proceed
       because server has replied to Client Hello, So peer is also interested 
       in handshake so handshake will not block */  
            ret = gnutls_handshake (session);
            pthread_mutex_unlock(&tlsLock);  
            GNUTLS_ERROR_CHECK(ret);
        }
        else
        {
            return ITS_E_TLSTIMEOUT;
        }
        return ITS_SUCCESS;
    }
    return ITS_E_TLSFAILED;
}

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
TlsClientSession::SetRecordMaxSize(int size)
{  
   int ret;
   if(size)
   {
       ret= gnutls_record_set_max_size(session, size);
       GNUTLS_ERROR_CHECK(ret);
       return ITS_SUCCESS;
   }
   return ITS_E_TLSFAILED;
}

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
TlsClientSession::SetPriority(PRIORITY_TYPE type , const int * priority)
{
    int ret;
    switch(type)
    {
        case CIPHER:            
            ret =  gnutls_cipher_set_priority( session, priority );
            break;
        case KX:
            ret =  gnutls_kx_set_priority( session, priority );
            break;
        case MAC:
            ret =  gnutls_mac_set_priority( session, priority );
            break;
        case COMPRESSION:
            ret =  gnutls_compression_set_priority( session, priority );
            break;
        case PROT:
            ret =  gnutls_protocol_set_priority( session, priority );
            break;
        case CERT_CD:
            ret =  gnutls_certificate_type_set_priority( session, priority );
            break;
        default:
            return !ITS_SUCCESS;
    }
         
    GNUTLS_ERROR_CHECK(ret);
    return ITS_SUCCESS;
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
TlsClientSession::SetCipherSuite(int * cipherSuiteList)
{
    int ret, kxCtr =0, ciphCtr =0, macCtr =0, counter=0;
    int cipherPriority[MAX_CIPHERS],kxPriority[MAX_KX],macPriority[MAX_MAC];
    ITS_OCTET kx =0, cipher =0,mac =0;

  
    TLS_NULLPTR_CHECK(cipherSuiteList);    
    /*Creating a List of required cipher, kx & mac from the 
           given list of cipher Suites*/
    while(cipherSuiteList[counter] !=0)
    {
        switch(cipherSuiteList[counter])
        {        
            case TLS_RSA_ARCFOUR_SHA:
                if(!(kx & its::ITS_RSA))
                {
                    kx = kx | its::ITS_RSA;
                    kxPriority[kxCtr] = GNUTLS_KX_RSA;
                    kxCtr++;
                }
                if(!(cipher & its::ARCFOUR_128))
                {
                    cipher = cipher | its::ARCFOUR_128;
                    cipherPriority[ciphCtr] = GNUTLS_CIPHER_ARCFOUR_128;        
                    ciphCtr++; 
                }
                if(!(mac & its::ITS_SHA))
                {
                    mac = mac | its::ITS_SHA;
                    macPriority[macCtr] = GNUTLS_MAC_SHA;
                    macCtr++;
                }
                break;            
            case TLS_RSA_ARCFOUR_MD5:
                if(!(kx & its::ITS_RSA))
                {
                    kx = kx | its::ITS_RSA;
                    kxPriority[kxCtr] = GNUTLS_KX_RSA;
                    kxCtr++;
                }
                if(!(cipher & its::ARCFOUR_128))
                {
                    cipher = cipher | its::ARCFOUR_128;
                    cipherPriority[ciphCtr] = GNUTLS_CIPHER_ARCFOUR_128;        
                    ciphCtr++; 
                }                
                if(!(mac & its::ITS_MD5))
                {
                    mac = mac | its::ITS_MD5;
                    macPriority[macCtr] = GNUTLS_MAC_MD5;
                    macCtr++;
                }
                break;              
            case TLS_RSA_3DES_EDE_CBC_SHA:
                if(!(kx & its::ITS_RSA))
                {
                    kx = kx | its::ITS_RSA;
                    kxPriority[kxCtr] = GNUTLS_KX_RSA;
                    kxCtr++;
                }
                if(!(cipher & its::DES_CBC))
                {
                    cipher = cipher | its::DES_CBC;
                    cipherPriority[ciphCtr] = GNUTLS_CIPHER_3DES_CBC;        
                    ciphCtr++; 
                }
                
                if(!(mac & its::ITS_SHA))
                {
                    mac = mac | its::ITS_SHA;
                    macPriority[macCtr] = GNUTLS_MAC_SHA;
                    macCtr++;
                }
                break;
            case TLS_RSA_AES_128_CBC_SHA:   
                if(!(kx & its::ITS_RSA))
                {
                    kx = kx | its::ITS_RSA;
                    kxPriority[kxCtr] = GNUTLS_KX_RSA;
                    kxCtr++;
                }
                if(!(cipher & its::AES_128_CBC))
                {
                    cipher = cipher | its::AES_128_CBC;
                    cipherPriority[ciphCtr] = GNUTLS_CIPHER_AES_128_CBC;        
                    ciphCtr++; 
                }                
                if(!(mac & its::ITS_SHA))
                {
                    mac = mac | its::ITS_SHA;
                    macPriority[macCtr] = GNUTLS_MAC_SHA;
                    macCtr++;
                }
                break;
            default:
                break;
        }       
        counter++;
    }
    /*Terminating The list of Ciphers, KX, MAc with ZERO */
    cipherPriority[ciphCtr] = 0;
    kxPriority[kxCtr] = 0;
    macPriority[macCtr] = 0;

    /*Setting The priority*/
    ret =  gnutls_cipher_set_priority( session, cipherPriority);
    GNUTLS_ERROR_CHECK(ret);
    ret =  gnutls_kx_set_priority( session, kxPriority);
    GNUTLS_ERROR_CHECK(ret);
    ret =  gnutls_mac_set_priority( session, macPriority );

    GNUTLS_ERROR_CHECK(ret);
    return ITS_SUCCESS;
      
        
}


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
TlsClientSession::CredentialSet(Certificate * cliCert)
{
    int ret;

    TLS_NULLPTR_CHECK(cliCert);    

    switch(((ClientCertificate * )cliCert)->cert.type)       
    {
        case X_509:     
        case OPEN_PGP:
            ret = gnutls_credentials_set (session, GNUTLS_CRD_CERTIFICATE,
                ((ClientCertificate * )cliCert)->cert.u.cert_cred);
            break;
        case SRP:   
            ret = gnutls_credentials_set (session, GNUTLS_CRD_SRP, 
                ((ClientCertificate * )cliCert)->cert.u.srp_cred);
            break;
        case ANONYMOUS: 
            ret = gnutls_credentials_set (session, GNUTLS_CRD_ANON,
                ((ClientCertificate * )cliCert)->cert.u.anon_cred);
            break;
        default:
             return !ITS_SUCCESS;
    }
    GNUTLS_ERROR_CHECK(ret);
    return ITS_SUCCESS;
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
TlsServerSession::Handshake()
{   
    int ret; 
    ret = gnutls_handshake (session);       
    GNUTLS_ERROR_CHECK(ret);
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
TlsServerSession::Handshake(int timeout)
{
    int ret;
    fd_set fdSet;
    struct timeval tOut;
    FD_ZERO(&fdSet);
    FD_SET(sock,&fdSet);

    tOut.tv_sec = timeout;
    tOut.tv_usec = 0;
 
    /*Putting handshake in select to make it handshake
      with Time Out, Thread will not block*/ 
    select(sock+1,&fdSet,NULL,NULL,&tOut);
    if(FD_ISSET(sock,&fdSet))
    {
        pthread_mutex_lock(&tlsLock);  
        ret = gnutls_handshake (session);
        pthread_mutex_unlock(&tlsLock);  
        GNUTLS_ERROR_CHECK(ret);
    }
    else
    {
        return ITS_E_TLSTIMEOUT;
    }
    return ITS_SUCCESS;
}

/*.implementation:public RehandShake
************************************************************************
*  Purpose:
*      Method to send a alert to client for Rehandshake for the same session
*
*  Input:
*
************************************************************************/

int
TlsServerSession::RehandShake()
{
   int ret;
   ret =  gnutls_rehandshake(session);
   GNUTLS_ERROR_CHECK(ret);
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
TlsServerSession::CertificateRequest()
{
    gnutls_certificate_server_set_request( session, GNUTLS_CERT_REQUEST);
    return ITS_SUCCESS;
}

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
TlsServerSession::CredentialSet(Certificate * servCert)
{
    int ret;

    TLS_NULLPTR_CHECK(servCert);    

    switch(((ServerCertificate * )servCert)->cert.type)       
    {
        case X_509:     
        case OPEN_PGP:
            ret = gnutls_credentials_set (session, GNUTLS_CRD_CERTIFICATE,
                    ((ServerCertificate * )servCert)->cert.u.cert_cred);
            break;
        case SRP:   
            ret = gnutls_credentials_set (session, GNUTLS_CRD_SRP,
                    ((ServerCertificate *)servCert)->cert.u.srp_cred);
            break;
        case ANONYMOUS: 
            ret = gnutls_credentials_set (session, GNUTLS_CRD_ANON,
                    ((ServerCertificate *)servCert)->cert.u.anon_cred);
            break;
        default:
            return !ITS_SUCCESS;
    }

    GNUTLS_ERROR_CHECK(ret);
    return ITS_SUCCESS;
}

/*.implementation:public mmap_file 
************************************************************************
*  Purpose:
*     Memory Map a certificate file in the process address space  
*
*  Input:
*     file : Name of a file to map
*
*  Output:
*    Ptr to address space which is mapped     
************************************************************************/
gnutls_datum 
mmap_file( const char* file)
{
    int fd;
    gnutls_datum mmaped_file = { NULL, 0 };
    struct stat stat_st;
    void* ptr;

       fd = open( file, 0);
       
       if (fd==-1) 
           return mmaped_file;

       fstat( fd, &stat_st);

       if ((ptr = mmap( NULL, stat_st.st_size, 
                       PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
           return mmaped_file;

       mmaped_file.data = (unsigned char *)ptr;
       mmaped_file.size = stat_st.st_size;

       return mmaped_file;
}

/*.implementation:public munmap_file
************************************************************************
*  Purpose:
*   Unmap the already mapped file
*
*  Input:
*   data: ptr to address space 
*
************************************************************************/
void 
munmap_file( gnutls_datum data)
{
    munmap( (char *)data.data, data.size);
}
