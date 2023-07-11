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
// LOG: $Log: AsnChoice.cpp,v $
// LOG: Revision 9.3.64.1  2014/09/16 09:34:53  jsarvesh
// LOG: Changes done for removing warnings
// LOG:
// LOG: Revision 9.3.60.1  2014/09/15 07:20:41  jsarvesh
// LOG: Changes done for removing Warnings
// LOG:
// LOG: Revision 9.3  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.4  2005/10/24 12:59:38  dsatish
// LOG: Choice index problem fix (Althaf)
// LOG:
// LOG: Revision 9.1.10.3  2005/10/06 12:12:56  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
// LOG:
// LOG: Revision 9.1.10.2  2005/09/14 09:48:27  mmanikandan
// LOG: Unit Test Bugs.
// LOG:
// LOG: Revision 9.1.10.1  2005/09/06 09:17:20  mmanikandan
// LOG: Support for ASN.1 PER.
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:05  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:18  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.9  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.8  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.7  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.6  2002/01/07 22:58:37  hdivoux
// LOG: First shot at XER encoding.
// LOG:
// LOG: Revision 5.5  2002/01/04 15:58:32  hdivoux
// LOG: More update for XER support.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:23:03  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:05:03  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnChoice.cpp,v 9.3.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

//
// ASN.1 runtime AsnChoice class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnChoice.h>
#include <AsnException.h>
#include <AsnWholeNumber.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnChoice::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescChoice staticDesc;

    if (initialized)
    {
        ITS_ENSURE(result != NULL);
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
    else
    {
        ITS_ASSERT(result == NULL);
        staticDesc.SetCloneForFactory(new AsnChoice(&staticDesc));
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

AsnChoice& 
AsnChoice::operator=(const AsnChoice& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        if (rhs._choice != NULL)
        {
            if (_choice != NULL)
            {
                if (_deleteSubcomponentsAutomatically)
                {
                    delete _choice;
                }
            }

            if (rhs._deleteSubcomponentsAutomatically)
            {
                _choice = rhs._choice->Clone();
            }
            else
            {
                _choice = rhs._choice;
            }
        }
        else
        {
            if (_choice != NULL)
            {
                if (_deleteSubcomponentsAutomatically)
                {
                    delete _choice;
                }
            }

            _choice = NULL;
        }

        _choiceIndex = rhs._choiceIndex;
        Assign(rhs); // MUST not be done before.
        return *this;
    }
}

void 
AsnChoice::EncodeCheck(const AsnOptions& asnOptions)
{
    if (_choice == NULL)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_NO_CHOICE_PRESENT);
    }

    if (!GetDescription().
         Contains(_choice->GetPolymorphDescription().TagIdentity()))
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_CHOICE);
    }
}

Octets* 
AsnChoice::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    if (_description->TagLevelNumber() >= 2)
    {
        // Must follow ASN.1 TLTLTL..TLV format.
        Octets* choiceOctets = _choice->InternalEncodeBer(
                                        asnOptions,
                                        level + 1,
                                        _choice->GetPolymorphDescription());

        // Next call is valid since ASN.1 Object description tag stack is used
        // (contains one or more tags as description->TagLevelNumber() >= 2). 
        Octets* result = EncodeTagLengthValue(*choiceOctets, asnOptions);
        delete choiceOctets;
        ITS_ENSURE(result != NULL);
        return result;
    }
    else
    {
        Octets* result = _choice->InternalEncodeBer(
                                        asnOptions,
                                        level + 1,
                                        _choice->GetPolymorphDescription());
        return result;
    }
}

void 
AsnChoice::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (!GetDescription().
         Contains(_choice->GetPolymorphDescription().TagIdentity()))
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_CHOICE, octets);
    }
}

void 
AsnChoice::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag choiceTag;
    choiceTag.DecodePreserveOffset(octets, asnOptions);

    if (GetDescription().Contains(choiceTag))
    {
        const AsnDescObject& choiceDesc = GetDescription().ChoiceAt(choiceTag);
        AsnObject* choiceRetrieved = choiceDesc.Factory();
        choiceRetrieved->InternalDecodeBer(
                                        octets,
                                        asnOptions,
                                        level + 1,
                                        choiceDesc);

        if (_choice)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _choice;
            }
        }

        _choice = choiceRetrieved;
    }
    else
    {
        ASN_THROW_DECODE_ERROR(ASN_E_UNKNOWN_CHOICE, octets);
    }

    DecodeCheck(octets, asnOptions);
}

int
AsnChoice::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    long lb = 0;
    long ub = 0;

    if (_choice == NULL)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_NO_CHOICE_PRESENT);
    }

    if (GetDescription().IsClauseExtensible())
    {
        extBit = IsExtension();
        octs.SetBit(extBit);
    }

    if (!extBit)
    {
        lb = 0;
        ub = GetDescription().GetSize();

        const AsnDescObject* choiceDesc = GetDescription().ChoiceAt(_choiceIndex);

        if (ub > 1)
        {
            ub--;
            AsnWN::EncodeCWN(octs, lb, ub, _choiceIndex, asnOptions);
        }
        _choice->EncodeAPER(octs, asnOptions, *choiceDesc);
    }
    else
    {
        //choice index >=64 is unlikely outside the root
        if(_choiceIndex >=64)
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_CHOICE);
        }
        AsnWN::EncodeNSNNWN(octs, _choiceIndex, asnOptions);
        octs.AddPaddingBits();

        const AsnDescObject* choiceDesc = GetDescription().ChoiceExtAt(_choiceIndex);

        Octets chOcts;

        if (choiceDesc)
        {
            _choice->EncodeAPER(chOcts, asnOptions, *choiceDesc);
        }

        std::vector<ITS_OCTET> arr = chOcts.GetArray();

        Length leng(arr.size());
        Octets* anyOcts = leng.EncodeAPER(asnOptions);
        
        std::vector<ITS_OCTET> larr = anyOcts->GetArray();

        if (anyOcts)
        {
            delete anyOcts;
            anyOcts = NULL;
        }

        unsigned int i = 0;

        for (i = 0; i < larr.size(); i++)
        {
            octs.SetOctet(larr[i]);
        } 

        for (i = 0; i < arr.size(); i++)
        {
            octs.SetOctet(arr[i]);
        }
    }

    return ITS_SUCCESS;
}

int 
AsnChoice::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    long lb = 0;
    long ub = 0;

    if (GetDescription().IsClauseExtensible())
    {
        extBit = octs.GetNextBit();
        SetExtension(extBit);
    }

    if (!extBit)
    {
        lb = 0;
        ub = GetDescription().GetSize();

        if (ub > 1)
        {
            ub--;
            _choiceIndex = AsnWN::DecodeCWN(octs, lb, ub, asnOptions);
        }

        const AsnDescObject* choiceDesc = GetDescription().ChoiceAt(_choiceIndex);

	if(choiceDesc == NULL)
	{
            ASN_THROW_DECODE_ERROR(ASN_E_UNKNOWN_CHOICE, octs);
	    return !ITS_SUCCESS;
	}

        AsnObject* choiceRetrieved = choiceDesc->Factory();
	try
	{
	    choiceRetrieved->DecodeAPER(octs, asnOptions, *choiceDesc);
	}
	catch(...)
	{
	    delete choiceRetrieved;
	    throw;
	}
        _choice = choiceRetrieved;
    }
    else
    {
        _choiceIndex = AsnWN::DecodeNSNNWN(octs, asnOptions);
        //choice index >=64 is unlikely for outside the root
        if(_choiceIndex >= 64)
        {
           ASN_THROW_DECODE_ERROR(ASN_E_INVALID_CHOICE, octs);
        }

        octs.SkipPaddingBits();

        Length leng(octs, asnOptions);

        Octets chOcts;

        int len = leng.GetLength();

        for (int cnt = 0; cnt < len; cnt++)
        {
            chOcts.SetOctet(octs.GetNextOctet());
        }

        const AsnDescObject* choiceDesc = GetDescription().ChoiceExtAt(_choiceIndex);

        if (choiceDesc != NULL)
        {
            AsnObject* choiceRetrieved = choiceDesc->Factory();
	    try
	    {
		choiceRetrieved->DecodeAPER(chOcts, asnOptions, *choiceDesc);
	    }
	    catch(...)
	    {
		delete choiceRetrieved;
		throw;
	    }
            _choice = choiceRetrieved;
        }
    }

    return ITS_SUCCESS;
}

Characters* 
AsnChoice::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    ITS_ASSERT(_description->TagLevelNumber() >= 1);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    XmlWriteNewLine(str, asnOptions);

    AsnDescObject* choiceDesc = NULL;

    for (
        vector<AsnDescObject*>::const_iterator iter = 
            static_cast<const AsnDescChoice&>(description).ChoicesBegin();
        iter != static_cast<const AsnDescChoice&>(description).ChoicesEnd();
        iter++)
    {
        if ((*iter)->IsNamedType() && 
            _choice->GetPolymorphDescription().IsNamedType())
        {
            // Identify choice description by name of named type (preferred).
            if ((*iter)->GetNamedTypeName() == 
                _choice->GetPolymorphDescription().GetNamedTypeName())
            {
                choiceDesc = *iter;
                break;
            }
        }
        else
        {
            // Identify choice description by type name (default).
            if ((*iter)->GetName() == _choice->GetName())
            {
                choiceDesc = *iter;
                break;
            }
        }
    }

    if (choiceDesc != NULL)
    {
        Characters* choiceCharacters = 
            _choice->InternalEncodeToXml(
                asnOptions, 
                level + 1,
                *choiceDesc);
        str += choiceCharacters->GetString();
        delete choiceCharacters;
    }
    else
    {
        Characters* choiceCharacters = 
            _choice->InternalEncodeToXml(
                asnOptions,
                level + 1,
                _choice->GetPolymorphDescription());
        str += choiceCharacters->GetString();
        delete choiceCharacters;
    }
        
    XmlWriteNewLine(str, asnOptions);

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnChoice::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (!GetDescription().
         Contains(_choice->GetPolymorphDescription().TagIdentity()))
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_INVALID_CHOICE, 
            characters);
    }
}

void 
AsnChoice::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlStartTag choiceStartTag(*this);
    choiceStartTag.DecodePreserveOffset(characters, asnOptions);

    AsnDescObject* choiceDesc = NULL;

    for (
        vector<AsnDescObject*>::const_iterator iter = 
            static_cast<const AsnDescChoice&>(description).ChoicesBegin();
        iter != static_cast<const AsnDescChoice&>(description).ChoicesEnd();
        iter++)
    {
        
        if ((*iter)->IsNamedType())
        {
            // Identify choice description by name of named type (preferred).
            if ((*iter)->GetNamedTypeName() == choiceStartTag.GetName())
            {
                choiceDesc = *iter;
                break;
            }
        }
        else
        {
            // Identify choice description by type name (default).
            if ((*iter)->GetName() == choiceStartTag.GetName())
            {
                choiceDesc = *iter;
                break;
            }
        }
    }

    if (choiceDesc != NULL)
    {
        AsnObject* choiceRetrieved = choiceDesc->Factory();
        choiceRetrieved->InternalDecodeFromXml(
                                        characters,
                                        asnOptions,
                                        level + 1,
                                        *choiceDesc);
        
        if (_choice)
        {
            if (_deleteSubcomponentsAutomatically)
            {
                delete _choice;
            }
        }

        _choice = choiceRetrieved;
    }
    else
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_UNKNOWN_CHOICE,
            characters);
    }
            
    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnChoice::Equals(const AsnObject& rhs) const
{ 
    const AsnChoice* other = static_cast<const AsnChoice*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (_choice == NULL && other->_choice == NULL)
    {
        return true;
    }
    else if (_choice == NULL && other->_choice != NULL)
    {
        return false;
    }
    else if (_choice != NULL && other->_choice == NULL)
    {
        return false;
    }
    else
    {
        return _choice->Equals(*(other->_choice));
    }    
}

void 
AsnChoice::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "{" << endl;

    if (_choice != NULL)
    {
        _choice->Print(os, level + 1);
    }
    else
    {
        os << endl;
    }

    os << levelShift;
    os << "}" << endl;
}

} // namespace its.


