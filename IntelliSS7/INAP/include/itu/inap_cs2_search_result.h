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


#if !defined(_INAP_CS2_SEARCH_RESULT_H_)
#define _INAP_CS2_SEARCH_RESULT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSet.h>
#include <AsnSetOf.h>

#include <inap_cs2_search_info.h>
#include <inap_cs2_search_results.h>



namespace inap_cs2 {



class SearchResult : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::SearchInfo SearchInfo;


        typedef inap_cs2::SearchResults SearchResults;


////////// End Nested Class(es) //////////

    SearchResult() : its::AsnChoice(false)
    {
        Initialize();
    }

    SearchResult(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SearchResult(const SearchResult& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SearchResult(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SearchResult(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetSearchInfoStaticDescription();
    static its::AsnDescObject* GetUncorrelatedSearchInfoStaticDescription();

public:

    virtual ~SearchResult()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SearchResult(*this);
    }

    virtual std::string GetName() const
    { return "SearchResult"; }

    void SetChoiceSearchInfo(SearchInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSearchInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSearchInfo(const SearchInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<SearchInfo&>(choice);
        asnObject.SetDescription(GetSearchInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSearchInfo() const
    {
        return Contains(GetSearchInfoStaticDescription()->TagIdentity());
    }

    const SearchInfo& GetChoiceSearchInfo() const
    {
        ITS_REQUIRE(ChoiceSearchInfo());
        return static_cast<const SearchInfo&> (GetChoice());
    }

    void SetChoiceUncorrelatedSearchInfo(SearchResults* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetUncorrelatedSearchInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceUncorrelatedSearchInfo(const SearchResults& choice)
    {
        its::AsnObject& asnObject = const_cast<SearchResults&>(choice);
        asnObject.SetDescription(GetUncorrelatedSearchInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceUncorrelatedSearchInfo() const
    {
        return Contains(GetUncorrelatedSearchInfoStaticDescription()->TagIdentity());
    }

    const SearchResults& GetChoiceUncorrelatedSearchInfo() const
    {
        ITS_REQUIRE(ChoiceUncorrelatedSearchInfo());
        return static_cast<const SearchResults&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_SEARCH_RESULT_H_)

