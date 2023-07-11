///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: AsnWholeNumber.h,v $
// LOG: Revision 9.1  2007/01/10 11:15:05  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 1.1.2.2  2005/10/06 12:13:52  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
// LOG:
// LOG: Revision 1.1.2.1  2005/09/06 09:18:10  mmanikandan
// LOG: Initial commit for PER.
// LOG:
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnWholeNumber.h,v 9.1 2007/01/10 11:15:05 yranade Exp $"

#include <Asn.h>
#include <AsnException.h>

namespace its
{

class AsnWN
{
public:
    static int EncodeNSNNWN(Octets& octs, ITS_UINT val, const AsnOptions& asnOptions = AsnOptions());
    static ITS_UINT DecodeNSNNWN(Octets& octs, const AsnOptions& asnOptions = AsnOptions());

    static int EncodeSCWN(Octets& octs, unsigned int val, const AsnOptions& asnOptions = AsnOptions());
    static unsigned int DecodeSCWN(Octets& octs, const AsnOptions& asnOptions = AsnOptions());

    static int EncodeCWN(Octets& octs, int lb, int ub, int eval, const AsnOptions& asnOptions = AsnOptions(),
                        bool _signedInt=true);
    static ITS_UINT DecodeCWN(Octets& octs, int lb, int ub, const AsnOptions& asnOptions, bool& _signedInt);
    static ITS_UINT DecodeCWN(Octets& octs, int lb, int ub, const AsnOptions& asnOptions = AsnOptions()); 

    static int EncodeUCWN(Octets& octs, int eval, const AsnOptions& asnOptions = AsnOptions());
    static int DecodeUCWN(Octets& octs, const AsnOptions& asnOptions);

    static int Encode2sComp(int val, std::vector<ITS_OCTET>& arr);
    static int Decode2sComp(std::vector<ITS_OCTET>& arr);
};

}
