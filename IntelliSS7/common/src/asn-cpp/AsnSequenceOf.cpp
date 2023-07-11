///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
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
// LOG: $Log: AsnSequenceOf.cpp,v $
// LOG: Revision 9.3.64.1  2014/09/16 09:34:53  jsarvesh
// LOG: Changes done for removing warnings
// LOG:
// LOG: Revision 9.3.60.1  2014/09/15 07:20:41  jsarvesh
// LOG: Changes done for removing Warnings
// LOG:
// LOG: Revision 9.3  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
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
// LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:20  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
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

#ident "$Id: AsnSequenceOf.cpp,v 9.3.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

//
// ASN.1 runtime AsnSequenceOf class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnSequenceOf.h>
#include <AsnException.h>
#include <AsnWholeNumber.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnSequenceOf::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequenceOf staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnSequenceOf(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

AsnSequenceOf& 
AsnSequenceOf::operator=(const AsnSequenceOf& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    else
    {
        RemoveAllElements();

        Assign(rhs); // MUST not be done before.

        for (list<AsnObject*>::const_iterator iter = rhs.ElementsBegin();
             iter != rhs.ElementsEnd(); iter++)
        {
            AsnObject* element = *iter;

            if (rhs._deleteSubcomponentsAutomatically)
            {
                AsnObject* clonedElement = element->Clone();
                _elementList.push_back(clonedElement);
            }
            else
            {
                _elementList.push_back(element);
            }
        }        
        
        return *this;
    }
}

void 
AsnSequenceOf::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsEncodeIgnoreSequenceOfSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE);
        }
        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE);
        }
    }
}

Octets* 
AsnSequenceOf::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    Octets valOctets;

    for (list<AsnObject*>::const_iterator iter = ElementsBegin();
         iter != ElementsEnd(); iter++)
    {
        AsnObject* element = *iter;
        Octets* elementOctets = element->InternalEncodeBer(
                                    asnOptions,
                                    level + 1,
                                    element->GetPolymorphDescription());
        valOctets += *elementOctets;
        delete elementOctets;
    }

    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnSequenceOf::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreSequenceOfSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE, octets);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE, octets);
        }
    }
}

void 
AsnSequenceOf::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    Length length(octets, asnOptions);
    long startOffset = octets.GetOffset();
    bool stop = false;
    if (length.GetLength() == 0)
    {
        stop = true;
    }

    RemoveAllElements();

    while (!stop)
    {
        Tag elementTag;
        elementTag.DecodePreserveOffset(octets, asnOptions);

        if (GetDescription().Contains(elementTag))
        {
            const AsnDescObject& elementDesc = GetDescription().GetElement();
            AsnObject* element = elementDesc.Factory();
            element->InternalDecodeBer(
                                    octets,
                                    asnOptions,
                                    level + 1,
                                    elementDesc);
            AddElement(element);
        }
        else
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF,
                octets);
        }

        long currentOffset = octets.GetOffset();

        if (!length.IsIndefinite())
        {
            if (length.GetLength() == currentOffset - startOffset)
            {
                stop = true;
            }
            else if (length.GetLength() > currentOffset - startOffset)
            {
                stop = false;
            }
            else
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE_OF,
                    octets);
            }
        }
        else
        {
            if (length.IsIndefiniteEndMark(octets))
            {
                length.IndefiniteEndMarkIncrementOffset(octets);
                stop = true;
            }
            else
            {
                stop = false;
            }
        }
    }

    DecodeCheck(octets, asnOptions);
}

int
AsnSequenceOf::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    unsigned int i = 0;
    unsigned long lb = 0;
    unsigned long ub = 0;
    
    lb = GetDescription().GetMinSize();
    ub = GetDescription().GetMaxSize();
    long cntSize = _elementList.size() - lb;

    if (GetDescription().IsClauseExtensible())
    {
        extBit = (ub !=0 && (_elementList.size() > ub)) ? true : false;
        octs.SetBit(extBit);
    }

    if((_elementList.size() < lb) ||
       ((ub !=0) && (extBit == false) && (_elementList.size() > ub)))
    {
	ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE);
    }    

    if (!extBit)
    {
        if ((lb == ub) && (ub != 0))
        {
            if (ub != _elementList.size())
            {
                return !ITS_SUCCESS;
            }
        }
        else
        {
            if ((lb != ub) && (ub != 0))
            {
                AsnWN::EncodeCWN(octs, lb, ub, 
                            _elementList.size(), asnOptions);
            }
            else 
            {
                Length leng(cntSize);
                
                Octets* lenocts = leng.Encode(asnOptions);
                std::vector<ITS_OCTET> oarr;

                if (lenocts)
                {
                    oarr = lenocts->GetArray();
                    delete lenocts;
                    lenocts = NULL; 
                }

                for (i = 0; i < oarr.size(); i++)
                {
                    octs.SetOctet(oarr[i]);
                }
            }
        }
    }
    else
    {
        Length leng(cntSize);

        Octets* lenocts = leng.Encode(asnOptions);
        std::vector<ITS_OCTET> oarr;

        if (lenocts)
        {
            oarr = lenocts->GetArray();
            delete lenocts;
            lenocts = NULL;
        }

        for (i = 0; i < oarr.size(); i++)
        {
            octs.SetOctet(oarr[i]);
        }
    }

    std::list<AsnObject*>::iterator biter = _elementList.begin();
    std::list<AsnObject*>::iterator eiter = _elementList.end();

    while (biter != eiter)
    {
        AsnObject* element = *biter;
        element->EncodeAPER(octs, asnOptions, 
                         element->GetPolymorphDescription());
        biter++;
    }
    return ITS_SUCCESS;
}

int 
AsnSequenceOf::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    int len = 0, i = 0;
    long lb = 0;
    long ub = 0;

    if (GetDescription().IsClauseExtensible())
    {
        extBit = octs.GetNextBit();
        SetExtension(extBit);
    }

    if (!extBit)
    {
        lb = GetDescription().GetMinSize();
        ub = GetDescription().GetMaxSize();

        if ((lb == ub) && (ub != 0) && (ub < K64))
        {
            len = ub;
        }
        else
        {
            if ((ub != 0) && (ub < K64))
            {
                len = AsnWN::DecodeCWN(octs, lb, ub, asnOptions);
                if(len > ub)
		{
		    ASN_THROW_DECODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE, octs);
		}
            }
            else
            {
                Length leng(octs, asnOptions);
                len = leng.GetLength();
		//for semi constraint type when lb !=0
		len +=lb;
            }
        }
    }
    else
    {
        Length leng(octs, asnOptions);
        len = leng.GetLength();
    }

    if(len >= K16)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_SEQUENCE_OF_SIZE, octs);
    }

    for (i = 0; i < len; i++)
    {
        const AsnDescObject& elementDesc = GetDescription().GetElement();
        AsnObject* element = elementDesc.Factory();
        try
	{
	    element->DecodeAPER(octs, asnOptions, elementDesc);
	}
	catch(...)
	{
	    delete element;
	    throw;
	}
        AddElement(element);
    }

    return ITS_SUCCESS;
}

Characters* 
AsnSequenceOf::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    if (GetSize() > 0)
    {
        XmlWriteNewLine(str, asnOptions);
    }

    for (list<AsnObject*>::const_iterator iter = ElementsBegin();
         iter != ElementsEnd(); iter++)
    {
        AsnObject* element = *iter;
        const AsnDescObject& elementDesc =
            static_cast<const AsnDescSequenceOf&>(description).GetElement();
        Characters* elementCharacters = 
            element->InternalEncodeToXml(asnOptions, level + 1, elementDesc);
        str += elementCharacters->GetString();
        delete elementCharacters;

        XmlWriteNewLine(str, asnOptions);
    }

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnSequenceOf::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreSequenceOfSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_SEQUENCE_OF_SIZE, 
                characters);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_SEQUENCE_OF_SIZE, 
                characters);
        }
    }
}

void 
AsnSequenceOf::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    XmlStartTag startTag(*this);
    startTag.DecodePreserveOffset(characters, asnOptions);

    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    bool stop = false;

    RemoveAllElements();

    while (!stop)
    {
        XmlStartTag elementStartTag(*this);
        elementStartTag.DecodePreserveOffset(characters, asnOptions);

        const AsnDescObject& elementDesc = GetDescription().GetElement();

        string elementDescName;

        if (elementDesc.HasTypeName())
        {
            elementDescName = elementDesc.GetTypeName();
        }
        else
        {
            elementDescName = 
                XmlReplaceUnderscoreByDash(elementDesc.GetName());
        }
        
        if (elementDescName == elementStartTag.GetName())
        {
            AsnObject* element = elementDesc.Factory();
            element->InternalDecodeFromXml(
                                    characters,
                                    asnOptions,
                                    level + 1,
                                    elementDesc);
            AddElement(element);
        }
        else
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF,
                characters);
        }

        XmlEndTag endTag(*this);
        endTag.TryDecodePreserveOffset(characters, asnOptions);

        if (startTag.GetName() == endTag.GetName())
        {
            stop = true;
        }
        else
        {
            stop = false;
        }
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnSequenceOf::Equals(const AsnObject& rhs) const
{ 
    const AsnSequenceOf* other = static_cast<const AsnSequenceOf*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (GetSize() != other->GetSize())
    {
        return false;
    }

    list<AsnObject*>::const_iterator iter = ElementsBegin();
    list<AsnObject*>::const_iterator iterOther = other->ElementsBegin();

    while (iter != ElementsEnd() && iterOther != ElementsEnd())
    {
        AsnObject* element = *iter;
        AsnObject* elementOther = *iterOther;

        ITS_ASSERT(elementOther != NULL);

        if (!element->Equals(*elementOther))
        {
            return false;
        }
    }

    return true;
}

void 
AsnSequenceOf::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "{" << endl;

    bool first = true;

    for (list<AsnObject*>::const_iterator iter = ElementsBegin();
         iter != ElementsEnd(); iter++)
    {
        AsnObject* element = *iter;

        if (!first)
        {
            os << endl;
        }
        else
        {
            first = false;
        }

        element->Print(os, level + 1);
    }

    os << levelShift;
    os << "}" << endl;
}

} // namespace its.

