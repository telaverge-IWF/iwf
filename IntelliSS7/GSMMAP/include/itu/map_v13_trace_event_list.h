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


#if !defined(_MAP_V13_TRACE_EVENT_LIST_H_)
#define _MAP_V13_TRACE_EVENT_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBitString.h>

#include <map_v13_msc_s_event_list.h>
#include <map_v13_mgw_event_list.h>
#include <map_v13_sgsn_event_list.h>
#include <map_v13_ggsn_event_list.h>
#include <map_v13_bmsc_event_list.h>
#include <map_v13_mme_event_list.h>
#include <map_v13_sgw_event_list.h>
#include <map_v13_pgw_event_list.h>



namespace map_v13 {



class TraceEventList : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::MSC_S_EventList MSC_S_EventList;


        typedef map_v13::MGW_EventList MGW_EventList;


        typedef map_v13::SGSN_EventList SGSN_EventList;


        typedef map_v13::GGSN_EventList GGSN_EventList;


        typedef map_v13::BMSC_EventList BMSC_EventList;


        typedef map_v13::MME_EventList MME_EventList;


        typedef map_v13::SGW_EventList SGW_EventList;


        typedef map_v13::PGW_EventList PGW_EventList;


////////// End Nested Class(es) //////////

    TraceEventList() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    TraceEventList(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    TraceEventList(const TraceEventList& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    TraceEventList(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetMsc_s_ListStaticDescription();
    static its::AsnDescObject* GetMgw_ListStaticDescription();
    static its::AsnDescObject* GetSgsn_ListStaticDescription();
    static its::AsnDescObject* GetGgsn_ListStaticDescription();
    static its::AsnDescObject* GetBmsc_ListStaticDescription();
    static its::AsnDescObject* GetMme_ListStaticDescription();
    static its::AsnDescObject* GetSgw_ListStaticDescription();
    static its::AsnDescObject* GetPgw_ListStaticDescription();

public:

    virtual ~TraceEventList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TraceEventList(*this);
    }

    virtual std::string GetName() const
    { return "TraceEventList"; }

    void SetMsc_s_List(MSC_S_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsc_s_ListStaticDescription());
        AddElement(0, element);
    }

    void SetMsc_s_List(const MSC_S_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<MSC_S_EventList&>(element);
        asnObject.SetDescription(GetMsc_s_ListStaticDescription());
        AddElement(0, element);
    }

    bool OptionMsc_s_List() const
    {
        return Contains(0);
    }

    const MSC_S_EventList& GetMsc_s_List() const
    {
        ITS_REQUIRE(OptionMsc_s_List());
        return static_cast<const MSC_S_EventList&> (ElementAt(0));
    }

    void SetMgw_List(MGW_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMgw_ListStaticDescription());
        AddElement(1, element);
    }

    void SetMgw_List(const MGW_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<MGW_EventList&>(element);
        asnObject.SetDescription(GetMgw_ListStaticDescription());
        AddElement(1, element);
    }

    bool OptionMgw_List() const
    {
        return Contains(1);
    }

    const MGW_EventList& GetMgw_List() const
    {
        ITS_REQUIRE(OptionMgw_List());
        return static_cast<const MGW_EventList&> (ElementAt(1));
    }

    void SetSgsn_List(SGSN_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSgsn_ListStaticDescription());
        AddElement(2, element);
    }

    void SetSgsn_List(const SGSN_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<SGSN_EventList&>(element);
        asnObject.SetDescription(GetSgsn_ListStaticDescription());
        AddElement(2, element);
    }

    bool OptionSgsn_List() const
    {
        return Contains(2);
    }

    const SGSN_EventList& GetSgsn_List() const
    {
        ITS_REQUIRE(OptionSgsn_List());
        return static_cast<const SGSN_EventList&> (ElementAt(2));
    }

    void SetGgsn_List(GGSN_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGgsn_ListStaticDescription());
        AddElement(3, element);
    }

    void SetGgsn_List(const GGSN_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<GGSN_EventList&>(element);
        asnObject.SetDescription(GetGgsn_ListStaticDescription());
        AddElement(3, element);
    }

    bool OptionGgsn_List() const
    {
        return Contains(3);
    }

    const GGSN_EventList& GetGgsn_List() const
    {
        ITS_REQUIRE(OptionGgsn_List());
        return static_cast<const GGSN_EventList&> (ElementAt(3));
    }

    void SetBmsc_List(BMSC_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBmsc_ListStaticDescription());
        AddElement(4, element);
    }

    void SetBmsc_List(const BMSC_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<BMSC_EventList&>(element);
        asnObject.SetDescription(GetBmsc_ListStaticDescription());
        AddElement(4, element);
    }

    bool OptionBmsc_List() const
    {
        return Contains(4);
    }

    const BMSC_EventList& GetBmsc_List() const
    {
        ITS_REQUIRE(OptionBmsc_List());
        return static_cast<const BMSC_EventList&> (ElementAt(4));
    }

    void SetMme_List(MME_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMme_ListStaticDescription());
        AddElement(5, element);
    }

    void SetMme_List(const MME_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<MME_EventList&>(element);
        asnObject.SetDescription(GetMme_ListStaticDescription());
        AddElement(5, element);
    }

    bool OptionMme_List() const
    {
        return Contains(5);
    }

    const MME_EventList& GetMme_List() const
    {
        ITS_REQUIRE(OptionMme_List());
        return static_cast<const MME_EventList&> (ElementAt(5));
    }

    void SetSgw_List(SGW_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSgw_ListStaticDescription());
        AddElement(6, element);
    }

    void SetSgw_List(const SGW_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<SGW_EventList&>(element);
        asnObject.SetDescription(GetSgw_ListStaticDescription());
        AddElement(6, element);
    }

    bool OptionSgw_List() const
    {
        return Contains(6);
    }

    const SGW_EventList& GetSgw_List() const
    {
        ITS_REQUIRE(OptionSgw_List());
        return static_cast<const SGW_EventList&> (ElementAt(6));
    }

    void SetPgw_List(PGW_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPgw_ListStaticDescription());
        AddElement(7, element);
    }

    void SetPgw_List(const PGW_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<PGW_EventList&>(element);
        asnObject.SetDescription(GetPgw_ListStaticDescription());
        AddElement(7, element);
    }

    bool OptionPgw_List() const
    {
        return Contains(7);
    }

    const PGW_EventList& GetPgw_List() const
    {
        ITS_REQUIRE(OptionPgw_List());
        return static_cast<const PGW_EventList&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_TRACE_EVENT_LIST_H_)

