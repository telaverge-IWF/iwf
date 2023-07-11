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
 * LOG: $Log: its_tls_factory.cpp,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.1.54.2  2013/09/04 05:06:56  vsarath
 * LOG: Implemented tls read/write lock
 * LOG:
 * LOG: Revision 1.1.54.1  2013/08/05 09:38:44  jvikram
 * LOG: Fixed core issue if TLS tags are commented/ommitted in config xml file and
 * LOG: TLS is enabled.
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:03:42  nvijikumar
 * LOG: GNUTLS and OPENSSL made separate
 * LOG:
 * LOG:
 *
 *ID: $Id: its_tls_factory.cpp,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/
#ident "$Id: its_tls_factory.cpp,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#include <its_tls_factory.h>

#include <its_ssl_tls_session.h>
#include <its_ssl_tls_thread_support.h>

#if !defined(USE_ONLY_SSL)
#include <its_gnu_tls_session.h>
#endif

TlsFactoryClass * TlsFactoryClass::tlsObj = NULL;

/*.implementation:public InitializeTls 
************************************************************************
*  Purpose:
*    Initizlizing TLS Library.
*
*  Input:
*   type : OPEN_SSL or GNU_TLS
*  
*  Return: Instance of this class
*       
*
*  Note:Its a one time call so Its a singleton class.   
************************************************************************/
TlsFactoryClass *
TlsFactoryClass::InitializeTls(TLS_TYPE type)
{
#if defined(USE_ONLY_SSL)
    if(type != OPEN_SSL)
    {
        return NULL;
    }
#endif

    try
    { 
        if((tlsObj == NULL) && (type != INVALID_TLS))
        {
            tlsObj =  new TlsFactoryClass(type);
            OpenSslThreadSupport &threadObj =
                OpenSslThreadSupport::getInstacnce(); 
            threadObj.Init();
        }
    }
    catch(...)
    {
        return NULL;
    }
    return tlsObj;
}


/*.implementation:public DeInitializeTls 
************************************************************************
*  Purpose:
*     Deinit the TLS library, It internally deletes the object       
*
*  Input:
*  
*  Note: Call it when you don't want to use TLS implementation any more. 
*        If you have called DeInitializeTls no need to delete the object   
************************************************************************/
void
TlsFactoryClass::DeInitializeTls()
{
    if(tlsObj != NULL)
    {
        delete tlsObj;
        tlsObj = NULL;
    }
}


/*.implementation:public GetTlsInstance 
************************************************************************
*  Purpose:
*        To get the already created instance of this class
*
*  Input:
*  
*  Return: Instance of this class
*       
************************************************************************/

TlsFactoryClass *
TlsFactoryClass::GetTlsInstance()
{
    return tlsObj;
}

/*.implementation:private InitializeTls 
************************************************************************
*  Purpose:
*    Initizlizing TLS Library. Constructor can't be called directly
*    You have to call InitializeTls to call constructor.
*
*  Input:
*   type : OPEN_SSL or GNU_TLS
*  
*  Return: Instance of this class
*       
*
*  Note:Its a one time call so Its a singleton class.   
************************************************************************/
TlsFactoryClass::TlsFactoryClass(TLS_TYPE type)
{
    if(tlsObj !=NULL)
    {
    } 
    else
    {
        tlsType = type;
        if(tlsType == GNU_TLS)
        {
#if 0
            gcry_control (GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);  
            gnutls_global_init();
#endif
        } 
        else
        {
            SSL_load_error_strings();
            SSL_library_init();
            debugFlag = 0;
        }
    }
}

/*.implementation:public  
************************************************************************
*  Purpose: 
*     Deinit the TLS library.      
*
*  Input:
*  
*  Note: Call it when you don't want to use TLS implementation any more. 
*        If you have called DeInitializeTls no need to delete the object   
************************************************************************/
TlsFactoryClass::~ TlsFactoryClass()
{
   if(tlsType == GNU_TLS)
   {
#if !defined(USE_ONLY_SSL)
       gnutls_global_deinit();
#endif
   } 
   else
   {
   
   }
}

/*.implementation:public SetDebug 
************************************************************************
*  Purpose:
*        To Set the DEBUG on
*
*  Input:
*     level: Level of GNU TLS debug LOG.
*     func : Pointer to user defined function to print traces 
*  
*  Return:
*      
*  Note: Only TLS_TYPE of GNU_TLS supports Debug option     
************************************************************************/
int 
TlsFactoryClass::SetDebug(int level)
{
    if(tlsType == GNU_TLS)
    {
#if !defined(USE_ONLY_SSL)
        gnutls_global_set_log_level(level);
        gnutls_global_set_log_function(AppsGnuTlsDebug);
#endif
    } 
    else
    {
        debugFlag = 1;
    
    }
    return ITS_SUCCESS;
}

/*.implementation:public CreateCertificate 
************************************************************************
*  Purpose:
*        To Create a certificate. It creates a Context in case of Open
*        SSL, which will be used to set Trust files & Certificate Key 
*        pairs. In case of GNU TLS it will Allocate credentials for 
*        Certificate        
*
*  Input:
*    endType: CLIENT or SERVER 
*  
*  Return: Instance of this Certificate class
*       
*************************************************************************/
Certificate *
TlsFactoryClass::CreateCertificate(its::END_POINT_TYPE endType)
{

    Certificate * cert = NULL;
    try
    {
        if(tlsType == GNU_TLS)
        {
#if !defined(USE_ONLY_SSL)
            if(endType == CLIENT)
            {
                cert = new ClientCertificate(X_509);
                return cert;
            }
            else 
            {
                cert = new ServerCertificate(X_509);
                return cert;
            }
#endif
        }
        else
        {
            cert = new SSLContext(endType);
            if(debugFlag)
            {
                SSL_CTX_set_info_callback(((SSLContext *)cert)->ctxt,AppsSslDebug); 
            }
            return cert;  
        }
    }
    catch(...) 
    {
        return NULL;
    } 


}

/*.implementation:public CreateSession 
************************************************************************
*  Purpose:
*        To Create a Tls Session. 
*
*  Input:
*    endType: CLIENT or SERVER 
*    sd     : Socket Descriptor
*  
*  Return: Instance of this TlsSession class
*       
************************************************************************/
TlsSession *
TlsFactoryClass::CreateSession(its::END_POINT_TYPE endType, int sd )
{
    TlsSession * sess = NULL;
    try
    {
        if(tlsType == GNU_TLS)
        {
#if !defined(USE_ONLY_SSL)
            if(endType == CLIENT)
            {
                sess = new TlsClientSession(sd);
                return sess;
            }
            else 
            {
                sess = new TlsServerSession(sd);
                return sess;
            }
#endif
        }
        else
        {
            if(endType == CLIENT)
            {
                sess = new SslClientSession(sd);
                return sess;
            }
            else 
            {
                sess = new SslServerSession(sd);
                return sess;
            }
        }
    }
    catch(...)
    {
        return NULL;
    }  
}
