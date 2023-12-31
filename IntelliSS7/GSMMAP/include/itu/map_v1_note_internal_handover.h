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


#if !defined(_MAP_V1_NOTE_INTERNAL_HANDOVER_H_)
#define _MAP_V1_NOTE_INTERNAL_HANDOVER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnOctetString.h>

#include <map_v1_handover_type.h>
#include <map_v1_global_cell_id.h>
#include <map_v1_external_signal_info.h>



namespace map_v1 {



class NoteInternalHandover : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::HandoverType HandoverType;


        typedef map_v1::GlobalCellId GlobalCellId;


        typedef map_v1::ExternalSignalInfo ExternalSignalInfo;


////////// End Nested Class(es) //////////

    NoteInternalHandover() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    NoteInternalHandover(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    NoteInternalHandover(const NoteInternalHandover& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    NoteInternalHandover(its::AsnDescObject* description) : its::AsnSequence(3, description)
    {
        // Nothing to do.
    }

protected:

    void Initialize()
    {
        _description = GetStaticDescription();
    }

public:

    static its::AsnDescObject* GetStaticDescription();

    static its::AsnDescObject* GetHandoverTypeStaticDescription();
    static its::AsnDescObject* GetTargetCellIdStaticDescription();
    static its::AsnDescObject* GetChannedIdStaticDescription();

public:

    virtual ~NoteInternalHandover()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NoteInternalHandover(*this);
    }

    virtual std::string GetName() const
    { return "NoteInternalHandover"; }

    void SetHandoverType(HandoverType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHandoverTypeStaticDescription());
        AddElement(0, element);
    }

    void SetHandoverType(const HandoverType& element)
    {
        its::AsnObject& asnObject = const_cast<HandoverType&>(element);
        asnObject.SetDescription(GetHandoverTypeStaticDescription());
        AddElement(0, element);
    }

    const HandoverType& GetHandoverType() const
    {
        return static_cast<const HandoverType&> (ElementAt(0));
    }

    void SetTargetCellId(GlobalCellId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetCellIdStaticDescription());
        AddElement(1, element);
    }

    void SetTargetCellId(const GlobalCellId& element)
    {
        its::AsnObject& asnObject = const_cast<GlobalCellId&>(element);
        asnObject.SetDescription(GetTargetCellIdStaticDescription());
        AddElement(1, element);
    }

    bool OptionTargetCellId() const
    {
        return Contains(1);
    }

    const GlobalCellId& GetTargetCellId() const
    {
        ITS_REQUIRE(OptionTargetCellId());
        return static_cast<const GlobalCellId&> (ElementAt(1));
    }

    void SetChannedId(ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChannedIdStaticDescription());
        AddElement(2, element);
    }

    void SetChannedId(const ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetChannedIdStaticDescription());
        AddElement(2, element);
    }

    bool OptionChannedId() const
    {
        return Contains(2);
    }

    const ExternalSignalInfo& GetChannedId() const
    {
        ITS_REQUIRE(OptionChannedId());
        return static_cast<const ExternalSignalInfo&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_NOTE_INTERNAL_HANDOVER_H_)

