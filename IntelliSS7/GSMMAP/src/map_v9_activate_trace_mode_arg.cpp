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


#include <map_v9_activate_trace_mode_arg.h>

#include <AsnDescSequence.h>
#include <AsnDescOctetString.h>
#include <AsnDescInteger.h>
#include <AsnDescBitString.h>


using namespace its;
using namespace map_v9;




////////// Begin Nested Class(es) //////////


// Type IMSI is a reference => no code generated.

// Type TraceReference is a reference => no code generated.

// Type TraceType is a reference => no code generated.

// Type AddressString is a reference => no code generated.

// Type ExtensionContainer is a reference => no code generated.

// Type TraceReference2 is a reference => no code generated.

// Type TraceDepthList is a reference => no code generated.

// Type TraceNE_TypeList is a reference => no code generated.

// Type TraceInterfaceList is a reference => no code generated.

// Type TraceEventList is a reference => no code generated.

////////// End Nested Class(es) //////////

AsnDescObject* ActivateTraceModeArg::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(10);

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

        staticDesc.SetCloneForFactory(new ActivateTraceModeArg(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_UNIVERSAL, Tag::ASN_CONSTRUCTED, 16));
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = GetImsiStaticDescription();
        staticDesc._elementVect[1] = GetTraceReferenceStaticDescription();
        staticDesc._elementVect[2] = GetTraceTypeStaticDescription();
        staticDesc._elementVect[3] = GetOmc_IdStaticDescription();
        staticDesc._elementVect[4] = GetExtensionContainerStaticDescription();
        staticDesc._elementVect[5] = GetTraceReference2StaticDescription();
        staticDesc._elementVect[6] = GetTraceDepthListStaticDescription();
        staticDesc._elementVect[7] = GetTraceNE_TypeListStaticDescription();
        staticDesc._elementVect[8] = GetTraceInterfaceListStaticDescription();
        staticDesc._elementVect[9] = GetTraceEventListStaticDescription();
        staticDesc.SetTypeName("ActivateTraceModeArg");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetImsiStaticDescription()
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
        staticDesc.SetCloneForFactory(new IMSI(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 0));
        staticDesc._clauseOptional = true;
        staticDesc.SetNamedTypeName("imsi");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceReferenceStaticDescription()
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
        staticDesc.SetCloneForFactory(new TraceReference(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 1));
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 2;
        staticDesc.SetNamedTypeName("traceReference");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceTypeStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new TraceType(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 2));
        staticDesc.SetNamedTypeName("traceType");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetOmc_IdStaticDescription()
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
        staticDesc.SetCloneForFactory(new AddressString(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 3));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 1;
        staticDesc._maxSize = 20;
        staticDesc.SetNamedTypeName("omc-Id");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetExtensionContainerStaticDescription()
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
        staticDesc.SetCloneForFactory(new ExtensionContainer(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 4));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = ExtensionContainer::GetPrivateExtensionListStaticDescription();
        staticDesc._elementVect[1] = ExtensionContainer::GetPcs_ExtensionsStaticDescription();
        staticDesc.SetNamedTypeName("extensionContainer");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceReference2StaticDescription()
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
        staticDesc.SetCloneForFactory(new TraceReference2(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 5));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 3;
        staticDesc._maxSize = 3;
        staticDesc.SetNamedTypeName("traceReference2");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceDepthListStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(6);

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
        staticDesc.SetCloneForFactory(new TraceDepthList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 6));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = TraceDepthList::GetMsc_s_TraceDepthStaticDescription();
        staticDesc._elementVect[1] = TraceDepthList::GetMgw_TraceDepthStaticDescription();
        staticDesc._elementVect[2] = TraceDepthList::GetSgsn_TraceDepthStaticDescription();
        staticDesc._elementVect[3] = TraceDepthList::GetGgsn_TraceDepthStaticDescription();
        staticDesc._elementVect[4] = TraceDepthList::GetRnc_TraceDepthStaticDescription();
        staticDesc._elementVect[5] = TraceDepthList::GetBmsc_TraceDepthStaticDescription();
        staticDesc.SetNamedTypeName("traceDepthList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceNE_TypeListStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

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
        staticDesc.SetCloneForFactory(new TraceNE_TypeList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_PRIMITIVE, 7));
        staticDesc._clauseOptional = true;
        staticDesc._clauseSize = true;
        staticDesc._minSize = 6;
        staticDesc._maxSize = 16;
        staticDesc.SetNamedTypeName("traceNE-TypeList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceInterfaceListStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(6);

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
        staticDesc.SetCloneForFactory(new TraceInterfaceList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 8));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = TraceInterfaceList::GetMsc_s_ListStaticDescription();
        staticDesc._elementVect[1] = TraceInterfaceList::GetMgw_ListStaticDescription();
        staticDesc._elementVect[2] = TraceInterfaceList::GetSgsn_ListStaticDescription();
        staticDesc._elementVect[3] = TraceInterfaceList::GetGgsn_ListStaticDescription();
        staticDesc._elementVect[4] = TraceInterfaceList::GetRnc_ListStaticDescription();
        staticDesc._elementVect[5] = TraceInterfaceList::GetBmsc_ListStaticDescription();
        staticDesc.SetNamedTypeName("traceInterfaceList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}

AsnDescObject* ActivateTraceModeArg::GetTraceEventListStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescSequence staticDesc(5);

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
        staticDesc.SetCloneForFactory(new TraceEventList(&staticDesc));
        staticDesc.TagAddLevel(new Tag(Tag::ASN_CLASS_CONTEXT_SPECIFIC, Tag::ASN_CONSTRUCTED, 9));
        staticDesc._clauseOptional = true;
        staticDesc._clauseExtensible = true;
        staticDesc._elementVect[0] = TraceEventList::GetMsc_s_ListStaticDescription();
        staticDesc._elementVect[1] = TraceEventList::GetMgw_ListStaticDescription();
        staticDesc._elementVect[2] = TraceEventList::GetSgsn_ListStaticDescription();
        staticDesc._elementVect[3] = TraceEventList::GetGgsn_ListStaticDescription();
        staticDesc._elementVect[4] = TraceEventList::GetBmsc_ListStaticDescription();
        staticDesc.SetNamedTypeName("traceEventList");
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        return result;
    }
}




