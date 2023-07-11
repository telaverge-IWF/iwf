////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: win_cpp.h,v 9.1 2005/03/23 12:52:43 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  IntelliSS7 ANSI WIN C++ API common header (all versions of ANSI WIN). 
//
//  o   Constant declarations.
//

#if !defined(_WIN_CPP_H_)
#define _WIN_CPP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <Asn.h>

#if defined(ITS_NAMESPACE)
namespace win
{
#else // !defined(ITS_NAMESPACE)
//
// Alternative approach if namespaces are not supported by the C++ compiler.
//  
struct WIN
{
#endif  // defined(ITS_NAMESPACE)


////////////////////////////////////////////////////////////////////////////////
//
//  ANSI WIN general constants.
//

enum {
    MAP_SSN = 5,
    HLR_SSN = 6,
    VLR_SSN = 7,
    MSC_SSN = 8,
    EIR_SSN = 9,
    AC_SSN  = 10,
    SMS_SSN = 11
};


////////////////////////////////////////////////////////////////////////////////
//
//  MAP protocol constants.
//

//////////////////////////////////////////////
//
//  Operation codes.
//

enum { 
        
    OP_QualificationRequest                 =   6,      
    OP_RegistrationNotification             =   13,   
    OP_LocationRequest                      =   15,
    OP_RoutingRequest                       =   16,
    OP_FeatureRequest                       =   17,

    // Reserved value: 18.
    // Reserved value: 19.
    // Reserved value: 21.
                    
    OP_TransferToNumberRequest              =   23,
    OP_InterSystemPage                      =   32,
    OP_UnsolicitedResponse                  =   33,

    // Reserved value: 41.
    
    OP_InterSystemSetup                     =   46,
   	OP_OriginationRequest                   =   47,

	OP_AnalyzedInformation                  =   64,
	OP_ConnectionFailureReport              =   65,
	OP_ConnectResource                      =   66,
	OP_DisconnectResource                   =   67,
	OP_FacilitySelectedAndAvailable         =   68,
	OP_InstructionRequest                   =   69,
	OP_Modify                               =   70,
    OP_ResetTimer                           =   71,
	OP_Search                               =   72,
	OP_SeizeResource                        =   73,
	OP_SRFDirective                         =   74,
	OP_TBusy                                =   75,
	OP_TNoAnswer                            =   76,
	OP_ServiceRequest                       =   77

};


//////////////////////////////////////////////
//
//  Error codes.
//

enum {

    ERR_UnrecognizedMIN                     =   0x81U,
    ERR_UnrecognizedESN                     =   0x82U,
    ERR_MIN_HLRMismatch                     =   0x83U,
    ERR_OperationSequenceProblem            =   0x84U,
    ERR_ResourceShortage                    =   0x85U,
    ERR_OperationNotSupported               =   0x86U,
    ERR_TrunkUnavailable                    =   0x87U,
    ERR_ParameterError                      =   0x88U,
    ERR_SystemFailure                       =   0x89U,
    ERR_UnrecognizedParameterValue          =   0x8AU,
    ERR_FeatureInactive                     =   0x8BU,
    ERR_MissingParameter                    =   0x8CU

};



#if defined(ITS_NAMESPACE)
}
#else // !defined(ITS_NAMESPACE)
};
#endif // defined(ITS_NAMESPACE)


#endif // !defined(_WIN_CPP_H_)
