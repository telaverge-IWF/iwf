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
 * LOG: $Log: its_tls_factory.h,v $
 * LOG: Revision 1.1.2.1  2013/11/12 07:51:34  jvikram
 * LOG: Included TLS Source files
 * LOG:
 * LOG: Revision 1.1  2010/06/30 04:04:41  nvijikumar
 * LOG: GNUTLS and OPENSSL made seperate
 * LOG:
 * LOG:
 *
 *ID: $Id: its_tls_factory.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $
 ******************************************************************************/

#ident "$Id: its_tls_factory.h,v 1.1.2.1 2013/11/12 07:51:34 jvikram Exp $"

#ifndef __TLS_FACTORY_H__
#define __TLS_FACTORY_H__

#include <its_tls_common.h>

using namespace its;

class TlsFactoryClass
{

public:

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
    static 
    TlsFactoryClass *
    InitializeTls(TLS_TYPE type); 

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
    static
    void
    DeInitializeTls();
 
     
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
    static 
    TlsFactoryClass *
    GetTlsInstance();

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
    SetDebug(int level);

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
    ************************************************************************/
    Certificate *
    CreateCertificate(its::END_POINT_TYPE endType);

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
    CreateSession( its::END_POINT_TYPE endType, int sd );


private:
    

    TlsFactoryClass(TLS_TYPE type);
    TlsFactoryClass();
    TlsFactoryClass(const TlsFactoryClass &);
    TlsFactoryClass & operator=(const TlsFactoryClass &);
    ~ TlsFactoryClass();
    bool debugFlag; 
    TLS_TYPE tlsType; 
    static TlsFactoryClass * tlsObj ;
    
};

#endif /* __TLS_SESSION_H__ */
