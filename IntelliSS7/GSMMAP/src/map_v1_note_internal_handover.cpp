//
// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).
//
// Do not edit!
//
//
//
// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.
//
//


#include <map_v1_note_internal_handover.h>

#include <AsnDescSequence.h>
#include <AsnDescEnumerated.h>
#include <AsnDescOctetString.h>


using namespace its;
using namespace map_v1;




////////// Begin Nested Class(es) //////////


// Type HandoverType is a reference => no code generated.

// Type GlobalCellId is a reference => no code generated.

// Type ExternalSignalInfo is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* NoteInternalHandover::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(3);

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        if (CheckLicense(ITS_LIC_CAP_GSMMAP) != ITS_TRUE)
        {
            Asn::Unlock();
            exit(0);
        }

        staticDesc.SetCloneForFactory(new NoteInternalHandover(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._elementVect[0] = GetHandoverTypeStaticDescription();
        staticDesc._elementVect[1] = GetTargetCellIdStaticDescription();
        staticDesc._elementVect[2] = GetChannedIdStaticDescription();
        staticDesc.SetTypeName("NoteInternalHandover");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteInternalHandover::GetHandoverTypeStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        staticDesc.SetCloneForFactory(new HandoverType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_PRIMITIVE, 10));
        staticDesc._valueSet.insert(0);
        staticDesc._valueSet.insert(1);
        static AsnDescEnumerated::NamedNumber namedNumberList[] = {{"interBSS", 0}, {"intraBSS", 1}, {NULL, 0}};
        staticDesc.SetNamedNumberList(namedNumberList);
        staticDesc.SetNamedTypeName("handoverType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteInternalHandover::GetTargetCellIdStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        staticDesc.SetCloneForFactory(new GlobalCellId(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 5;
        staticDesc._maxSize = 7;
        staticDesc.SetNamedTypeName("targetCellId");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* NoteInternalHandover::GetChannedIdStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(2);

    if (initialized)
    {
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        return result;
    }
    else
    {
        staticDesc.SetCloneForFactory(new ExternalSignalInfo(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 2));
        staticDesc._clauseOptional = true;
        staticDesc._elementVect[0] = ExternalSignalInfo::GetProtocolIdStaticDescription();
        staticDesc._elementVect[1] = ExternalSignalInfo::GetSignalInfoStaticDescription();
        staticDesc.SetNamedTypeName("channedId");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}





