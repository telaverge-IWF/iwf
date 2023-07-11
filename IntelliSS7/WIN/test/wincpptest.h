////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
// CONTRACT: internal                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//ID: $Id: wincpptest.h,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
////////////////////////////////////////////////////////////////////////////////


#if !defined(WIN_TEST_H)
#define WIN_TEST_H



////////////////////////////////////////////////////////////////////////////////
//
//  Utilities.
//

//
//  Macro to get the size (count of items) of a fixed array.
//
#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))


//  Macro to convert fixed arrays (of bytes) to vectors.

#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))


//  Macro to convert fixed arrays (of booleans) to vectors.

#define FixedBooleanArrayToVector(array)   \
    (vector<bool>(array, array + FixedArraySize(array)))



#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace win;
#endif

// Functions for encoding and decoding

void EncodeMsg(AsnObject* p, Octets** octets);
void DecodeMsg(AsnObject* p, Octets* octets);

	
// Communication

ITS_Worker*     trin;
ITS_Worker*     trout;

ITS_Thread* recvMTP3Thread = NULL;
ITS_Thread* recvTCAPThread = NULL;


// TCAP containers

TCAP_Component* cpt = NULL;
TCAP_Dialogue* dlg = NULL;
int frID = 0;
int srID = 0;
int aiID = 0;
int fsaID = 0;
int sreID = 0;
int sdID = 0;
int tbID = 0;


// address indicator

#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)


SCCP_CallingPartyAddr origAddr;
SCCP_CalledPartyAddr destAddr;


#endif // !defined(WIN_TEST_H)

