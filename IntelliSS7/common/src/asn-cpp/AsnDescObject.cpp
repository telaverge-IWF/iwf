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
// LOG: $Log: AsnDescObject.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:53:05  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:18  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/06/17 21:52:59  hdivoux
// LOG: Added processing for default ASN.1 values.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnDescObject.cpp,v 9.1 2005/03/23 12:53:05 cvsadmin Exp $"

//
// ASN.1 runtime AsnDescObject class implementation.
//

#include <Asn.h>
#include <AsnDescObject.h>
#include <AsnObject.h>

using namespace std;

namespace its {

AsnDescObject::~AsnDescObject()
{
    for (
        vector<Tag*>::iterator iter = _tagStack.begin();
        iter != _tagStack.end(); 
        iter++)
    {
        Tag* tag = (*iter);
        delete tag;
    }

    if (_cloneForFactory)
    {
        delete _cloneForFactory;
        _cloneForFactory = NULL;
    }

    if (_cloneForDefaultFactory)
    {
        delete _cloneForDefaultFactory;
        _cloneForDefaultFactory = NULL;
    }
}

AsnObject* 
AsnDescObject::Factory() const
{
    ITS_ASSERT(_cloneForFactory != NULL);
    return _cloneForFactory->Clone();
}

void 
AsnDescObject::SetCloneForFactory(AsnObject* clone)
{
    ITS_REQUIRE(clone != NULL);
    _cloneForFactory = clone;
    _cloneForFactory->SetDescription(this);
}

AsnObject* 
AsnDescObject::DefaultFactory() const
{
    ITS_ASSERT(_cloneForDefaultFactory != NULL);
    return _cloneForDefaultFactory->Clone();
}

void 
AsnDescObject::SetCloneForDefaultFactory(AsnObject* clone)
{
    ITS_REQUIRE(clone != NULL);
    _cloneForDefaultFactory = clone;
    _cloneForDefaultFactory->SetDescription(this);
}

void 
AsnDescObject::TagAddLevel(Tag* tag)
{
    ITS_REQUIRE(tag != NULL);

    if (_tagStack.size() == 0)
    {
        _tagStack.push_back(tag);
    }
    else
    {
        std::vector<Tag*>::iterator iter = _tagStack.begin();
        iter++; // Iterator point to first element.
        _tagStack.insert(iter, tag); // Insert before iterator.
    }
}

string 
AsnDescObject::GetName() const
{
    ITS_ASSERT(_cloneForFactory != NULL);
    return _cloneForFactory->GetName();
}

string 
AsnDescObject::GetBaseName() const
{
    ITS_ASSERT(_cloneForFactory != NULL);
    return _cloneForFactory->GetBaseName();
}

} // namespace its.

