///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            Copyright 1999 - 2002 IntelliNet Technologies, Inc.            //
//                          All Rights Reserved.                             //
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
// LOG: $Log: asncc_ast.h,v $
// LOG: Revision 9.1  2005/03/23 12:54:13  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:52:58  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.2  2002/06/17 21:51:43  hdivoux
// LOG: Added processing for default ASN.1 values.
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
//  Abstract syntax type interfaces.
//

#if !defined(_ASNCC_ABSTRACT_SYNTAX_TYPES_H_)
#define _ASNCC_ABSTRACT_SYNTAX_TYPES_H_

#ident "$Id: asncc_ast.h,v 9.1 2005/03/23 12:54:13 cvsadmin Exp $"


#include <asncc.h>
#include <asncc_tag.h>
#include <asncc_visitor.h>
#include <asncc_assertion.h>

void yyerror(const char* str);


////////////////////////////////////////////////////////////////////////////////

class TypeDef;
class ValueSetTypeDef;
class Type;
class BitStringType;
class BooleanType;
class CharacterStringType;
class ChoiceType;
class EmbeddedPDVType;
class EnumeratedType;
class ExternalType;
class InstanceOfType;
class IntegerType;
class NullType;
class ObjectClassFieldType;
class ObjectIdentifierType;
class OctetStringType;
class BaseStringType;
class RealType;
class SequenceType;
class SequenceOfType;
class SetType;
class SequenceOfType;
class DefinedType;
class SelectionType;
class UsefulType;
class AnyType;
class AnyDefinedByType;
class DefinedType;

////////////////////////////////////////////////////////////////////////////////

class ValueDef;
class Value;
class BooleanValue;
class ChoiceValue;
class IntegerValue;
class RealValue;
class OctetStringValue;
class BitStringValue;
class NullValue;
class CharacterStringValue;
class ObjectIdentifierValue;
class MinValue;
class MaxValue;
class SequenceValue;
class DefinedValue;
class AnyValue;

////////////////////////////////////////////////////////////////////////////////

class NamedNumber;
class EnumerationItem;
class Constraint;
class ConstraintElement;
class ConstrainAllConstraintElement;
class ElementListConstraintElement;
class SingleValueConstraintElement;
class ValueRangeConstraintElement;
class ImportedModule;

////////////////////////////////////////////////////////////////////////////////

typedef std::list<TypeDef*> TypeDefList;
typedef std::list<ValueDef*> ValueDefList;

typedef std::list<Type*> TypeList;
typedef std::list<Value*> ValueList;

typedef std::list<NamedNumber*> NamedNumberList;
typedef std::list<EnumerationItem*> EnumerationItemList;
typedef std::list<ConstraintElement*> ConstraintElementList;
typedef std::list<ImportedModule*> ImportedModuleList;
typedef std::list<Constraint*> ConstraintList;

typedef std::list<Tag*> TagList;


////////////////////////////////////////////////////////////////////////////////
//
//  TypeDef interface.
//
//  TypeAssignment = TypeDef (type definition).
//

class TypeDef
{
public:

    TypeDef(const std::string& definedNameParam, Type* typeParam);
    virtual ~TypeDef() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    const std::string&
    GetDefinedName() const
    { return definedName; }

    Type*
    GetType()
    { return type; }

    void 
    SetParameterList(std::list<std::string*>* parameterListParam)
    { 
        parameterList = parameterListParam; 
        isParameterized = true;
    }

    bool 
    IsParameterized() const
    { return isParameterized; }

    std::list<std::string*>*
    GetParameterList() const
    { 
        REQUIRE(IsParameterized());
        return parameterList;
    }

    void
    SetConstraintElementList(ConstraintElementList* constraintElementListParam)
    {
        constraintElementList = constraintElementListParam;
        isValueSet = true;
    }

    bool
    IsValueSet() const
    { return isValueSet; }

    ConstraintElementList* 
    GetConstraintElementList() const
    {
        REQUIRE(IsValueSet());
        return constraintElementList;
    }

    void
    SetRecursive()
    { isRecursive = true; }

    bool 
    IsRecursive() const
    { return isRecursive; }

    void
    Mark()
    { isMarked = true; }

    void
    Unmark()
    { isMarked = false; }

    bool
    IsMarked()
    { return isMarked; }

    void
    SetExported()
    { isExported = true; }

    bool
    IsExported() const
    { return isExported; }

    long
    GetLocalRefCount() const
    { return localRefCount; }

    long
    GetImportRefCount() const
    { return importRefCount; }

    void
    IncLocalRefCount()
    { localRefCount++; }

    void
    IncImportRefCount()
    { importRefCount++; }

    virtual void Accept(Visitor* visitor);

    virtual std::string ToString() const;

    virtual void Print(std::ostream& os) const;

protected:

    std::string definedName;

    Type* type;

    bool isParameterized;

    std::list<std::string*>* parameterList;

    bool isValueSet;

    ConstraintElementList* constraintElementList;

    bool isRecursive;
    bool isMarked;
    bool isExported;

    long localRefCount;
    long importRefCount;
};


// TypeDef std::ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const TypeDef& type);


////////////////////////////////////////////////////////////////////////////////
//
// All concrete type classes.
//

enum {
    TYPE_BIT_STRING,
    TYPE_BOOLEAN,
    TYPE_CHARACTER_STRING,
    TYPE_CHOICE,
    TYPE_EMBEDDED_PDV,
    TYPE_ENUMERATED,
    TYPE_EXTERNAL,
    TYPE_INSTANCE_OF,
    TYPE_INTEGER,
    TYPE_NULL,
    TYPE_OBJECT_CLASS_FIELD,
    TYPE_OBJECT_IDENTIFIER,
    TYPE_OCTET_STRING,
    TYPE_BASE_STRING,
    TYPE_REAL,
    TYPE_SEQUENCE,
    TYPE_SEQUENCE_OF,
    TYPE_SET,
    TYPE_SET_OF,
    TYPE_IMPORTED,
    TYPE_DEFINED,
    TYPE_SELECTION,
    TYPE_USEFUL,
    TYPE_FROM_OBJECT,
    TYPE_SET_FROM_OBJECT_VALUE,
    TYPE_ANY,                       // Backward compatibility.
    TYPE_ANY_DEFINED_BY             // Backward compatibility.
};


////////////////////////////////////////////////////////////////////////////////
//
//  Type interface.
//

class Type
{
public:

    Type();
    virtual ~Type() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* Clone() const = 0;

    void 
    SetLineNumber(unsigned long lineNumberParam)
    {
        hasLineNumber = true;
        lineNumber = lineNumberParam;
    }

    bool 
    HasLineNumber() const
    { return hasLineNumber; }

    unsigned long 
    GetLineNumber() const
    {
        REQUIRE(HasLineNumber());
        return lineNumber;
    }

    virtual int GetType() const = 0; 

    virtual int GetIdentifierTokenContext() const;

    virtual int 
    GetBraceTokenContext() const
    { return '{'; }

    void
    SetName(const std::string& nameParam)
    {
        isNamed = true;
        name    = nameParam;
    }

    bool 
    IsNamed() const
    { return isNamed; }

    const std::string&
    GetName() const
    { 
        REQUIRE(IsNamed());
        return name;
    }

    void
    SetDefaultValue(Value* defaultValueParam)
    { 
        hasDefaultValue = true;
        defaultValue    = defaultValueParam; 
    }

    bool
    HasDefaultValue() const
    { return hasDefaultValue; }

    Value*
    GetDefaultValue() const
    { 
        REQUIRE(HasDefaultValue());
        return defaultValue;
    }

    void
    SetDefaultValueWithCode(const std::string& defaultValueWithCodeParam)
    {
        hasDefaultValue         = true;
        hasDefaultValueWithCode = true;
        defaultValueWithCode    = defaultValueWithCodeParam;
    }

    bool
    HasDefaultValueWithCode() const
    { return hasDefaultValueWithCode; }

    const std::string&
    GetDefaultValueWithCode() const
    {
        REQUIRE(HasDefaultValueWithCode());
        return defaultValueWithCode;
    }

    void
    SetOptional()
    { isOptional = true; }

    bool
    IsOptional() const
    { return isOptional; }

    void
    SetComponentsOf()
    { isComponentsOf = true; }

    bool
    IsComponentsOf() const
    { return isComponentsOf; }

    void
    AddComponentToComponentsOfList(Type* component)
    {
        REQUIRE(IsComponentsOf());
        REQUIRE(component != NULL);

        componentsOfList.push_back(component);
    }

    TypeList*
    GetComponentsOfList()
    { 
        REQUIRE(IsComponentsOf());
        return &componentsOfList;
    }

    void
    SetFromComponentsOf()
    { isFromComponentsOf = true; }

    bool
    IsFromComponentsOf() const
    { return isFromComponentsOf; }

    void
    SetFromSelectionType()
    { isFromSelectionType = true; }

    bool
    IsFromSelectionType() const
    { return isFromSelectionType; }

    void
    SetComponentsOfOrigin(DefinedType* componentsOfOriginParam)
    {
        REQUIRE(componentsOfOriginParam != NULL);
        hasComponentsOfOrigin = true;
        componentsOfOrigin = componentsOfOriginParam;
    }

    bool
    HasComponentsOfOrigin() const
    { return hasComponentsOfOrigin; }

    DefinedType*
    GetComponentsOfOrigin() const
    {
        REQUIRE(HasComponentsOfOrigin());
        return componentsOfOrigin;
    }

    void
    SetSelectionTypeOrigin(SelectionType* selectionTypeOriginParam)
    {
        REQUIRE(selectionTypeOriginParam != NULL);
        hasSelectionTypeOrigin = true;
        selectionTypeOrigin = selectionTypeOriginParam;
    }

    bool
    HasSelectionTypeOrigin() const
    { return hasSelectionTypeOrigin; }

    SelectionType*
    GetSelectionTypeOrigin() const
    {
        REQUIRE(HasSelectionTypeOrigin());
        return selectionTypeOrigin;
    }

    Type* GetBaseType() const;

    virtual bool HasUniversalTag() const = 0;

    virtual Tag* GetUniversalTag() const = 0;

    void
    AddTag(Tag* tag)
    { tagList->push_front(tag); }

    TagList*
    GetTagList() const
    { return tagList; }

    virtual TagList* GetFullTagList() const;

    virtual TagList* GetAdjustedTagList() const;

    void 
    AddConstraint(Constraint* constraint)
    { constraintList->push_back(constraint); }

    ConstraintList*
    GetConstraintList() const
    { return constraintList; }

    void
    SetModule(Module* moduleParam)
    {
        REQUIRE(moduleParam != NULL);
        hasModule = true;
        module = moduleParam;
    }

    bool
    HasModule() const
    { return hasModule; }

    Module*
    GetModule() const
    { 
        REQUIRE(HasModule());
        return module;
    }

    virtual void Accept(Visitor* visitor);

    virtual std::string ToString() const;

    virtual void Print(std::ostream& os) const;

protected:

    bool isReferenced;
    bool isConstrained;
    bool isNamed;
    bool isOptional;
    bool isComponentsOf;
    bool isFromComponentsOf;
    bool isFromSelectionType;
    bool hasLineNumber;

    bool isParameterized; 

    std::string name;

    bool hasDefaultValue;
    bool hasDefaultValueWithCode;

    Value* defaultValue;
    std::string defaultValueWithCode;

    unsigned long lineNumber;

    TagList* tagList;

    ConstraintList* constraintList;

    std::list<std::string*>* parameterList;

    bool hasComponentsOfOrigin;
    bool hasSelectionTypeOrigin;
   
    DefinedType* componentsOfOrigin;
    SelectionType* selectionTypeOrigin;

    TypeList componentsOfList;

    bool hasModule;

    Module* module;

};


// Type std::ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const Type& type);


////////////////////////////////////////////////////////////////////////////////
//
//  DefinedType interface.
//

class DefinedType : public Type
{
public:

    DefinedType(const std::string& nameParam, bool notUsedParam = false);
    virtual ~DefinedType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new DefinedType(*this); }

    virtual int
    GetType() const
    { return TYPE_DEFINED; }

    const std::string&
    GetName() const
    { return name; }

    void
    SetLink(Type* linkParam, TypeDef* typeDefLinkParam)
    {
        REQUIRE(linkParam != NULL);
        REQUIRE(typeDefLinkParam != NULL);

        isLinked = true;
        link = linkParam;
        typeDefLink = typeDefLinkParam;
    }

    bool 
    IsLinked() const
    { return isLinked; }

    Type*
    GetLink() const
    {
        REQUIRE(IsLinked());
        return link;
    }

    TypeDef*
    GetTypeDefLink() const
    {
        REQUIRE(IsLinked());
        return typeDefLink;
    }

    virtual TagList* GetFullTagList() const;

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;

    bool isLinked;

    Type* link;

    TypeDef* typeDefLink;
};


////////////////////////////////////////////////////////////////////////////////
//
//  BitStringType interface.
//

class BitStringType : public Type
{
public:

    BitStringType();
    virtual ~BitStringType() {}

    BitStringType(NamedNumberList* namedNumberListParam);

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new BitStringType(*this); }

    virtual int
    GetType() const
    { return TYPE_BIT_STRING; }

    NamedNumberList*
    GetNamedNumberList() const
    { return namedNumberList; }

    bool
    HasNamedNumberList() const
    { return !(namedNumberList->empty()); }

    virtual int GetIdentifierTokenContext() const;

    virtual int GetBraceTokenContext() const;

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    NamedNumberList* namedNumberList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  BooleanType interface.
//

class BooleanType : public Type
{
public:

    BooleanType();
    virtual ~BooleanType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new BooleanType(*this); }

    virtual int
    GetType() const
    { return TYPE_BOOLEAN; }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  CharacterStringType interface.
//

class CharacterStringType : public Type
{
public:

    CharacterStringType();
    virtual ~CharacterStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new CharacterStringType(*this); }

    virtual int
    GetType() const
    { return TYPE_CHARACTER_STRING; }

    virtual int GetBraceTokenContext() const;

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  ChoiceType interface.
//

class ChoiceType : public Type
{
public:

    ChoiceType(TypeList* typeListParam);

    ChoiceType(TypeList* typeListParam, bool extendableParam);

    ChoiceType(
        TypeList* typeListParam, 
        bool extendableParam, 
        TypeList* extensionsParam);

    virtual ~ChoiceType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new ChoiceType(*this); }

    virtual int
    GetType() const
    { return TYPE_CHOICE; }

    TypeList*
    GetTypeList() const
    { return typeList; }

    bool
    IsExtendable() const
    { return extendable; }

    TypeList*
    GetExtensions() const
    { return extensions; }

    TypeList* GetFlattenedTypeList();

    void MakeNamedTypeTable();

    bool
    HasNamedType(const std::string& nameParam) const
    {
        return 
            namedTypeTable.find(nameParam) !=
                namedTypeTable.end();
    }

    Type*
    RetrieveNamedType(const std::string& nameParam) const
    { 
        REQUIRE(HasNamedType(nameParam));

        NamedTypeTable::const_iterator iter = 
            namedTypeTable.find(nameParam);

        return (*iter).second;
    }

    // Possible tag list can contain special tag any and duplicate tags.

    virtual TagList* GetPossibleTagList();    

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    TypeList* typeList;

    TypeList* extensions;

    bool extendable;

    TypeList flattenedTypeList;

    typedef std::map<std::string, Type*>    NamedTypeTable;

    NamedTypeTable namedTypeTable;
};


////////////////////////////////////////////////////////////////////////////////
//
//  EnumeratedType interface.
//

class EnumeratedType : public Type
{
public:

    EnumeratedType(
        NamedNumberList* namedNumberListParam, 
        bool extendableParam, 
        NamedNumberList* extensionsParam);

    virtual ~EnumeratedType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new EnumeratedType(*this); }

    virtual int
    GetType() const
    { return TYPE_ENUMERATED; }

    NamedNumberList*
    GetNamedNumberList() const
    { return namedNumberList; }

    bool
    IsExtendable() const
    { return extendable; }

    NamedNumberList*
    GetExtensions() const
    { return extensions; }

    void MakeNamedNumberTable();

    bool
    HasNamedNumber(const std::string& nameParam) const
    {
        return 
            namedNumberTable.find(nameParam) != 
                namedNumberTable.end();
    }

    NamedNumber*
    RetrieveNamedNumber(const std::string& nameParam) const
    {
        REQUIRE(HasNamedNumber(nameParam));

        NamedNumberTable::const_iterator iter = 
            namedNumberTable.find(nameParam);

        return (*iter).second;
    }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    NamedNumberList* namedNumberList;

    NamedNumberList* extensions;

    bool extendable;

    typedef std::map<std::string, NamedNumber*> NamedNumberTable;

    NamedNumberTable namedNumberTable;

};


////////////////////////////////////////////////////////////////////////////////
//
//  ExternalType interface.
//

class ExternalType : public DefinedType
{
public:

    ExternalType() : DefinedType("EXTERNAL")
    {}

    virtual ~ExternalType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  InstanceOfType interface.
//

class InstanceOfType : public Type
{
public:

    InstanceOfType();
    virtual ~InstanceOfType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new InstanceOfType(*this); }

    virtual int
    GetType() const
    { return TYPE_INSTANCE_OF; }

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  IntegerType interface.
//

class IntegerType : public Type
{
public:

    IntegerType();

    IntegerType(NamedNumberList* namedNumberListParam);

    virtual ~IntegerType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new IntegerType(*this); }

    virtual int
    GetType() const
    { return TYPE_INTEGER; }

    bool
    HasNamedNumberList() const
    { return !(namedNumberList->empty()); }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    NamedNumberList* namedNumberList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  NullType interface.
//

class NullType : public Type
{
public:

    NullType();

    virtual ~NullType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new NullType(*this); }

    virtual int
    GetType() const
    { return TYPE_NULL; }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectClassFieldType interface.
//

class ObjectClassFieldType : public Type
{
public:

    ObjectClassFieldType(
        const std::string& objectClassNameParam, 
        const std::string& objectClassFieldParam);

    virtual ~ObjectClassFieldType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new ObjectClassFieldType(*this); }

    virtual int
    GetType() const
    { return TYPE_OBJECT_CLASS_FIELD; }

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

    std::string objectClassName;
    std::string objectClassField;
};


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectIdentifierType interface.
//

class ObjectIdentifierType : public Type
{
public:

    ObjectIdentifierType();

    virtual ~ObjectIdentifierType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new ObjectIdentifierType(*this); }

    virtual int
    GetType() const
    { return TYPE_OBJECT_IDENTIFIER; }

    virtual int
    GetIdentifierTokenContext() const;

    virtual int 
    GetBraceTokenContext() const;

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  OctetStringType interface.
//

class OctetStringType : public Type
{
public:

    OctetStringType();

    virtual ~OctetStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new OctetStringType(*this); }

    virtual int
    GetType() const
    { return TYPE_OCTET_STRING; }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  BaseStringType interface.
//

class BaseStringType : public Type
{
public:

    BaseStringType();

    virtual ~BaseStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new BaseStringType(*this); }

    virtual int
    GetType() const
    { return TYPE_BASE_STRING; }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  RealType interface.
//

class RealType : public Type
{
public:

    RealType();

    virtual ~RealType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new RealType(*this); }

    virtual int
    GetType() const
    { return TYPE_REAL; }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceType interface.
//

class SequenceType : public Type
{
public:

    SequenceType(
        TypeList* typeListParam, 
        bool extendableParam, 
        TypeList* extensionsParam);

    virtual ~SequenceType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new SequenceType(*this); }

    virtual int
    GetType() const
    { return TYPE_SEQUENCE; }

    TypeList*
    GetTypeList() const
    { return typeList; }

    bool
    IsExtendable() const
    { return extendable; }

    TypeList*
    GetExtensions() const
    { return extensions; }

    TypeList* GetFlattenedTypeList();

    void MakeNamedTypeTable();

    bool
    HasNamedType(const std::string& nameParam) const
    {
        return 
            namedTypeTable.find(nameParam) !=
                namedTypeTable.end();
    }

    Type*
    RetrieveNamedType(const std::string& nameParam) const
    { 
        REQUIRE(HasNamedType(nameParam));

        NamedTypeTable::const_iterator iter = 
            namedTypeTable.find(nameParam);

        return (*iter).second;
    }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    TypeList* typeList;

    TypeList* extensions;

    bool extendable;

    TypeList flattenedTypeList;

    typedef std::map<std::string, Type*>    NamedTypeTable;

    NamedTypeTable  namedTypeTable;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceOfType interface.
//

class SequenceOfType : public Type
{
public:

    SequenceOfType(Type* typeParam, Constraint* constraintParam);

    virtual ~SequenceOfType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new SequenceOfType(*this); }

    virtual int
    GetType() const
    { return TYPE_SEQUENCE_OF; }

    Type*
    GetSequenceOfType() const
    { return type; };

    bool
    HasConstraint() const
    { return hasConstraint; }

    Constraint*
    GetConstraint() const
    { 
        REQUIRE(HasConstraint());
        return constraint;
    }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    Type* type;

    bool hasConstraint;

    Constraint* constraint;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SetType interface.
//

class SetType : public SequenceType
{
public:

    SetType();

    SetType(SequenceType* sequenceTypeParam);

    SetType(
        TypeList* typeListParam, 
        bool extendableParam, 
        TypeList* extensionsParam);

    virtual ~SetType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new SetType(*this); }

    virtual int
    GetType() const
    { return TYPE_SET; }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:


};


////////////////////////////////////////////////////////////////////////////////
//
//  SetOfType interface.
//

class SetOfType : public Type
{
public:

    SetOfType(Type* typeParam, Constraint* constraintParam);

    virtual ~SetOfType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new SetOfType(*this); }

    virtual int
    GetType() const
    { return TYPE_SET_OF; }

    Type*
    GetSetOfType() const
    { return type; }

    bool
    HasConstraint() const
    { return hasConstraint; }

    Constraint*
    GetConstraint() const
    { 
        REQUIRE(HasConstraint());
        return constraint;
    }

    virtual bool
    HasUniversalTag() const
    { return true; }

    virtual Tag* GetUniversalTag() const;

    virtual void Accept(Visitor* visitor);

protected:

    Type* type;

    bool hasConstraint;

    Constraint* constraint;
};


////////////////////////////////////////////////////////////////////////////////
//
//  ImportedType interface.
//

class ImportedType : public Type
{
public:

    ImportedType(const std::string& nameParam, bool isParameterizedParam);

    virtual ~ImportedType() {}

    const std::string&
    GetName() const
    { return name; }

    void 
    SetImportModulePrefix(const std::string& modulePrefix)
    {
        name.insert(0, ".");
        name.insert(0, modulePrefix);
    }

    bool 
    IsParameterized()
    { return isParameterized; }

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new ImportedType(*this); }

    virtual int
    GetType() const
    { return TYPE_IMPORTED; }

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

    std::string name;
    bool        isParameterized;
};


////////////////////////////////////////////////////////////////////////////////
//
//  ParameterizedType interface.
//

class ParameterizedType : public DefinedType
{
public:

    ParameterizedType(const std::string& name, TypeList* typeListParam);

    virtual ~ParameterizedType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

protected:

    TypeList* typeList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SelectionType interface.
//

class SelectionType : public Type
{
public:

    SelectionType(const std::string& nameParam, Type* typeParam);

    virtual ~SelectionType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new SelectionType(*this); }

    virtual int
    GetType() const
    { return TYPE_SELECTION; }

    virtual TagList* GetFullTagList() const;

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

    std::string name;
    Type* type;
};


////////////////////////////////////////////////////////////////////////////////
//
//  UsefulType interface.
//

class UsefulType : public Type
{
public:

    UsefulType();

    virtual ~UsefulType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new UsefulType(*this); }

    virtual int
    GetType() const
    { return TYPE_USEFUL; }

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:


};


////////////////////////////////////////////////////////////////////////////////
//
//  AnyType interface.
//

class AnyType : public Type
{
public:

    AnyType();

    virtual ~AnyType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new AnyType(*this); }

    virtual int
    GetType() const
    { return TYPE_ANY; }

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  AnyDefinedByType interface.
//

class AnyDefinedByType : public Type
{
public:

    AnyDefinedByType(const std::string& nameParam);

    virtual ~AnyDefinedByType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual Type* 
    Clone() const
    { return new AnyDefinedByType(*this); }

    virtual int
    GetType() const
    { return TYPE_ANY_DEFINED_BY; }

    const std::string&
    GetName() const
    { return name; }

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;

};


////////////////////////////////////////////////////////////////////////////////
//
//  BMPStringType interface.
//

class BMPStringType : public DefinedType
{
public:

    BMPStringType() : DefinedType("BMPString")
    {}

    virtual ~BMPStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  EmbeddedPDVType interface.
//

class EmbeddedPDVType : public DefinedType
{
public:

    EmbeddedPDVType() : DefinedType("EMBEDDED PDV")
    {}

    virtual ~EmbeddedPDVType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  GeneralStringType interface.
//

class GeneralStringType : public DefinedType
{
public:

    GeneralStringType() : DefinedType("GeneralString")
    {}

    virtual ~GeneralStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  GraphicStringType interface.
//

class GraphicStringType : public DefinedType
{
public:

    GraphicStringType() : DefinedType("GraphicString")
    {}

    virtual ~GraphicStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  IA5StringType interface.
//

class IA5StringType : public DefinedType
{
public:

    IA5StringType() : DefinedType("IA5String")
    {}

    virtual ~IA5StringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  ISO646StringType interface.
//

class ISO646StringType : public DefinedType
{
public:

    ISO646StringType() : DefinedType("ISO646String")
    {}

    virtual ~ISO646StringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  NumericStringType interface.
//

class NumericStringType : public DefinedType
{
public:

    NumericStringType() : DefinedType("NumericString")
    {}

    virtual ~NumericStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  PrintableStringType interface.
//

class PrintableStringType : public DefinedType
{
public:

    PrintableStringType() : DefinedType("PrintableString")
    {}

    virtual ~PrintableStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  TeletexStringType interface.
//

class TeletexStringType : public DefinedType
{
public:

    TeletexStringType() : DefinedType("TeletexString")
    {}

    virtual ~TeletexStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  T61StringType interface.
//

class T61StringType : public DefinedType
{
public:

    T61StringType() : DefinedType("T61String")
    {}

    virtual ~T61StringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  UniversalStringType interface.
//

class UniversalStringType : public DefinedType
{
public:

    UniversalStringType() : DefinedType("UniversalString")
    {}

    virtual ~UniversalStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  UTF8StringType interface.
//

class UTF8StringType : public DefinedType
{
public:

    UTF8StringType() : DefinedType("UTF8String")
    {}

    virtual ~UTF8StringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  VideotexStringType interface.
//

class VideotexStringType : public DefinedType
{
public:

    VideotexStringType() : DefinedType("VideotexString")
    {}

    virtual ~VideotexStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  VisibleStringType interface.
//

class VisibleStringType : public DefinedType
{
public:

    VisibleStringType() : DefinedType("VisibleString")
    {}

    virtual ~VisibleStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  UnrestrictedCharacterStringType interface.
//

class UnrestrictedCharacterStringType : public DefinedType
{
public:

    UnrestrictedCharacterStringType() : DefinedType("CHARACTER STRING")
    {}

    virtual ~UnrestrictedCharacterStringType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  GeneralizedTimeType interface.
//

class GeneralizedTimeType : public DefinedType
{
public:

    GeneralizedTimeType() : DefinedType("GeneralizedTime")
    {}

    virtual ~GeneralizedTimeType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  UTCTimeType interface.
//

class UTCTimeType : public DefinedType
{
public:

    UTCTimeType() : DefinedType("UTCTime")
    {}

    virtual ~UTCTimeType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectDescriptorType interface.
//

class ObjectDescriptorType : public DefinedType
{
public:

    ObjectDescriptorType() : DefinedType("ObjectDescriptor")
    {}

    virtual ~ObjectDescriptorType() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual bool
    HasUniversalTag() const
    { return false; }

    virtual Tag* 
    GetUniversalTag() const
    {
        REQUIRE(HasUniversalTag());
        return NULL; // Not reached.
    }

protected:

};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  ValueDef interface.
//
//  ValueAssignment = ValueDef (value definition).
//

class ValueDef
{
public:

    ValueDef(
        const std::string& definedNameParam, 
        Type* typeParam, 
        Value* valueParam);

    virtual ~ValueDef() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    const std::string&
    GetDefinedName() const
    { return definedName; }

    Type*
    GetType() const
    { return type; }

    Value*
    GetValue() const
    { return value; }

    void
    SetRecursive()
    { isRecursive = true; }

    bool 
    IsRecursive() const
    { return isRecursive; }

    void
    Mark()
    { isMarked = true; }

    void
    Unmark()
    { isMarked = false; }

    bool
    IsMarked()
    { return isMarked; }

    void
    SetExported()
    { isExported = true; }

    bool
    IsExported() const
    { return isExported; }

    long
    GetLocalRefCount() const
    { return localRefCount; }

    long
    GetImportRefCount() const
    { return importRefCount; }

    void
    IncLocalRefCount()
    { localRefCount++; }

    void
    IncImportRefCount()
    { importRefCount++; }

    virtual void Accept(Visitor* visitor);

    virtual std::string ToString() const;

    virtual void Print(std::ostream& os) const;

protected:

    std::string definedName;

    Type* type;

    Value* value;

    bool isRecursive;
    bool isMarked;
    bool isExported;

    long localRefCount;
    long importRefCount;
};


// ValueDef std::ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const ValueDef& value);


////////////////////////////////////////////////////////////////////////////////
//
//  
//

enum {
    VALUE_BIT_STRING,
    VALUE_BOOLEAN,
    VALUE_CHARACTER_STRING,
    VALUE_CHOICE,
    VALUE_EMBEDDED_PDV,
    VALUE_ENUMERATED,
    VALUE_EXTERNAL,
    VALUE_INSTANCE_OF,
    VALUE_INTEGER,
    VALUE_NULL,
    VALUE_OBJECT_CLASS_FIELD,
    VALUE_OBJECT_IDENTIFIER,
    VALUE_OCTET_STRING,
    VALUE_REAL,
    VALUE_SEQUENCE,
    VALUE_SEQUENCE_OF,
    VALUE_SET,
    VALUE_SET_OF,
    VALUE_MIN,
    VALUE_MAX,
    VALUE_DEFINED,
    VALUE_ANY           // Backward compatibility.
};


////////////////////////////////////////////////////////////////////////////////
//
//  Value interface.
//

class Value
{
public:

    Value();

    virtual ~Value() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    void 
    SetLineNumber(unsigned long lineNumberParam)
    {
        hasLineNumber = true;
        lineNumber = lineNumberParam;
    }

    bool 
    HasLineNumber() const
    { return hasLineNumber; }

    unsigned long 
    GetLineNumber() const
    {
        REQUIRE(HasLineNumber());
        return lineNumber;
    }

    virtual int GetValueType() const = 0; 

    void
    SetName(const std::string& nameParam)
    {
        isNamed = true;
        name    = nameParam;
    }

    bool IsNamed() const
    { return isNamed; }

    const std::string&
    GetName() const
    { 
        REQUIRE(IsNamed());
        return name;
    }

    Value* GetBaseValue() const;

    void
    SetModule(Module* moduleParam)
    {
        REQUIRE(moduleParam != NULL);
        hasModule = true;
        module = moduleParam;
    }

    bool
    HasModule() const
    { return hasModule; }

    Module*
    GetModule() const
    { 
        REQUIRE(HasModule());
        return module;
    }

    void
    SetAssociatedType(Type* typeParam)
    {
        REQUIRE(typeParam != NULL);
        hasAssociatedType = true;
        associatedType = typeParam;
    }

    bool
    HasAssociatedType() const
    { 
        if (hasAssociatedType)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
        
    Type*
    GetAssociatedType() const
    {
        REQUIRE(HasAssociatedType());
        return associatedType;
    }

    virtual void Accept(Visitor* visitor);

    virtual std::string ToString() const;

    virtual void Print(std::ostream& os) const;

protected:

    bool isNamed;
    bool hasLineNumber;

    std::string name;

    unsigned long lineNumber;

    bool hasModule;

    Module* module;

    bool hasAssociatedType;

    Type* associatedType;

};


// Value std::ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const Value& value);


////////////////////////////////////////////////////////////////////////////////
//
//  BooleanValue interface.
//

class BooleanValue : public Value
{
public:

    BooleanValue(bool valueParam);

    virtual ~BooleanValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_BOOLEAN; }

    bool
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    bool value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  ChoiceValue interface.
//

class ChoiceValue : public Value
{
public:

    ChoiceValue(const std::string& nameParam, Value* valueParam);

    virtual ~ChoiceValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_CHOICE; }

    const std::string&
    GetName() const
    { return name; }

    Value*
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;

    Value* value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  EnumeratedValue interface.
//

class EnumeratedValue : public Value
{
public:

    EnumeratedValue(const std::string& nameParam);

    virtual ~EnumeratedValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_ENUMERATED; }

    const std::string&
    GetName() const
    { return name; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;
};


////////////////////////////////////////////////////////////////////////////////
//
//  IntegerValue interface.
//

class IntegerValue : public Value
{
public:

    IntegerValue(long valueParam);

    virtual ~IntegerValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_INTEGER; }

    long
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:
    
    long value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  RealValue interface.
//

class RealValue : public Value
{
public:

    RealValue(double valueParam);

    virtual ~RealValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_REAL; }

    double
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    double value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  OctetStringValue interface.
//

class OctetStringValue : public Value
{
public:

    OctetStringValue();

    OctetStringValue(const std::string& valueParam);

    virtual ~OctetStringValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_OCTET_STRING; }

    const std::string& 
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  BitStringValue interface.
//

class BitStringValue : public Value
{
public:

    BitStringValue();

    BitStringValue(const std::string& valueParam);

    BitStringValue(std::list<std::string*>* listParam);

    virtual ~BitStringValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_BIT_STRING; }

    const std::string&
    GetValue() const
    {  return value; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  NullValue interface.
//

class NullValue : public Value
{
public:

    NullValue();

    virtual ~NullValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_NULL; }

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  CharacterStringValue interface.
//

class CharacterStringValue : public Value
{
public:

    CharacterStringValue();
    CharacterStringValue(const std::string& valueParam);
    CharacterStringValue(std::list<std::string*>* listParam);

    virtual ~CharacterStringValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_CHARACTER_STRING; }

    const std::string&
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string value;
};


////////////////////////////////////////////////////////////////////////////////
//
//  ObjectIdentifierValue interface.
//

class ObjectIdentifierValue : public Value
{
public:

    ObjectIdentifierValue(const std::string& valueParam);

    virtual ~ObjectIdentifierValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_OBJECT_IDENTIFIER; }

    const std::string&
    GetValue() const
    { return value; }

    const std::list<long>&
    GetComponentList() const
    { return componentList; }

    void MakeComponentList();

    virtual void Accept(Visitor* visitor);

protected:

    std::string value;

    std::list<long> componentList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  MinValue interface.
//

class MinValue : public Value
{
public:

    MinValue();

    virtual ~MinValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_MIN; }

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  MaxValue interface.
//

class MaxValue : public Value
{
public:

    MaxValue();

    virtual ~MaxValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_MAX; }

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceValue interface.
//

class SequenceValue : public Value
{
public:

    SequenceValue();

    SequenceValue(ValueList* valueListParam);

    virtual ~SequenceValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return polymorphValueType; }

    void
    SetPolymorphValueTypeSequence() 
    { polymorphValueType = VALUE_SEQUENCE; }

    void
    SetPolymorphValueTypeSequenceOf()
    { polymorphValueType = VALUE_SEQUENCE_OF; }

    void
    SetPolymorphValueTypeSet()
    { polymorphValueType = VALUE_SET; }

    void
    SetPolymorphValueTypeSetOf()
    { polymorphValueType = VALUE_SET_OF; }

    ValueList*
    GetValueList() const
    { return valueList; }

    void MakeNamedValueTable();

    bool 
    HasNamedValue(const std::string& nameParam) const
    {
        return 
            namedValueTable.find(nameParam) != 
                namedValueTable.end();
    }

    Value*
    RetrieveNamedValue(const std::string& nameParam) const
    {
        REQUIRE(HasNamedValue(nameParam));

        NamedValueTable::const_iterator iter = 
            namedValueTable.find(nameParam);

        return (*iter).second;
    }

    void
    SetHasNamedValue() 
    { hasNamedValue = true; }

    bool
    HasNamedValue() const
    { return hasNamedValue; }

    void
    SetHasUnnamedValue()
    { hasUnnamedValue = true; }

    bool
    HasUnnamedValue() const
    { return hasUnnamedValue; }

    virtual void Accept(Visitor* visitor);

protected:

    ValueList* valueList;

    int polymorphValueType;

    typedef std::map<std::string, Value*>   NamedValueTable;

    NamedValueTable namedValueTable;

    bool hasUnnamedValue;

    bool hasNamedValue;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SequenceOfValue interface.
//

class SequenceOfValue : public Value
{
public:

    SequenceOfValue(ValueList* valueListParam);

    virtual ~SequenceOfValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_SEQUENCE_OF; }

    virtual void Accept(Visitor* visitor);

protected:

    ValueList* valueList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SetValue interface.
//

class SetValue : public Value
{
public:

    SetValue(ValueList* valueListParam);

    virtual ~SetValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_SET; }

    virtual void Accept(Visitor* visitor);

protected:

    ValueList* valueList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SetOfValue interface.
//

class SetOfValue : public Value
{
public:

    SetOfValue(ValueList* valueListParam);

    virtual ~SetOfValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_SET_OF; }

    virtual void Accept(Visitor* visitor);

protected:

    ValueList* valueList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  DefinedValue interface.
//

class DefinedValue : public Value
{
public:

    DefinedValue(const std::string& nameParam);

    virtual ~DefinedValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_DEFINED; }

    const std::string&
    GetName() const
    { return name; }

    void
    SetLink(Value* linkParam, ValueDef* valueDefLinkParam)
    {
        REQUIRE(linkParam != NULL);
        REQUIRE(valueDefLinkParam != NULL);

        isLinked = true;
        link = linkParam;
        valueDefLink = valueDefLinkParam;
    }

    bool
    IsLinked() const
    { return isLinked; }

    Value*
    GetLink() const
    {
        REQUIRE(IsLinked());
        return link;
    }

    ValueDef*
    GetValueDefLink() const
    {
        REQUIRE(IsLinked());
        return valueDefLink;
    }

    void
    SetEnumeratedValue()
    { isEnumeratedValue = true; }

    bool
    IsEnumeratedValue() const
    { return isEnumeratedValue; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;

    bool isLinked;

    Value* link;

    ValueDef* valueDefLink;

    bool isEnumeratedValue;
};


////////////////////////////////////////////////////////////////////////////////
//
//  AnyValue interface.
//

class AnyValue : public Value
{
public:

    AnyValue(Type* typeParam, Value* valueParam);

    virtual ~AnyValue() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual int
    GetValueType() const
    { return VALUE_ANY; }

    Type* 
    GetType() const
    { return type; }

    Value*
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    Type* type;

    Value* value;

};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  NamedNumber interface.
//

class NamedNumber
{
public:

    NamedNumber(const std::string& nameParam);
    NamedNumber(const std::string& nameParam, long numberParam);
    NamedNumber(const std::string& nameParam, DefinedValue* definedValueParam);

    virtual ~NamedNumber() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    const std::string&
    GetName() const
    { return name; }

    void
    SetNumber(long numberParam)
    {
        hasNumber = true;
        number = numberParam;
    }

    bool
    HasNumber() const
    { return hasNumber; }

    long
    GetNumber() const
    {
        REQUIRE(HasNumber());
        return number;
    }

    bool
    HasDefinedValue() const
    { return hasDefinedValue; }

    DefinedValue*
    GetDefinedValue() const
    {
        REQUIRE(HasDefinedValue());
        return definedValue;
    }

    void
    SetAutoNumber()
    { isAutoNumber = true; }

    bool
    IsAutoNumber() const
    { return isAutoNumber; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;
    long number;
    DefinedValue* definedValue;

    bool hasNumber;
    bool hasDefinedValue;
    bool isAutoNumber;
};


////////////////////////////////////////////////////////////////////////////////
//
//  Constraint interface.
//

class Constraint
{
public:

    Constraint(
        ConstraintElement* constraintElementParam);

    Constraint(
        ConstraintElementList* constraintElementListParam, 
        bool isExtendableParam, 
        ConstraintElementList* extensionsParam);

    virtual ~Constraint() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    ConstraintElementList*
    GetConstraintElementList() const
    { return constraintElementList; }

    bool
    IsExtendable() const
    { return isExtendable; }

    void
    SetExtensions(ConstraintElementList* extensionsParam)
    {
        REQUIRE(extensionsParam != NULL);
        hasExtensions = true;
        extensions = extensionsParam; 
    }

    bool 
    HasExtensions() const
    { return hasExtensions; }

    ConstraintElementList*
    GetExtensions() const
    { 
        REQUIRE(HasExtensions());
        return extensions;
    }

    virtual void Accept(Visitor* visitor);

    virtual std::string ToString() const;

    virtual void Print(std::ostream& os) const;

protected:

    ConstraintElementList*  constraintElementList;
    bool                    isExtendable;
    bool                    hasExtensions;
    ConstraintElementList*  extensions;
};


////////////////////////////////////////////////////////////////////////////////
//
//  ConstraintElement interface.
//

class ConstraintElement
{
public:

    ConstraintElement();

    virtual ~ConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    void 
    SetExclusions(ConstraintElement* exclusionsParam) 
    { 
        REQUIRE(exclusionsParam != NULL);
        hasExclusions = true;
        exclusions = exclusionsParam; 
    }

    bool
    HasExclusions() const
    { return hasExclusions; }

    ConstraintElement*
    GetExclusions() const
    { 
        REQUIRE(HasExclusions());
        return exclusions; 
    }

    virtual void Accept(Visitor* visitor) = 0;

protected:

    bool hasExclusions;

    ConstraintElement* exclusions;

};


////////////////////////////////////////////////////////////////////////////////
//
//  ConstraintAllConstraintElement interface.
//

class ConstrainAllConstraintElement : public ConstraintElement
{
public:

    ConstrainAllConstraintElement(ConstraintElement* exclusionsParam);

    virtual ~ConstrainAllConstraintElement() {}

    // Default copy constructor ok.

    // Default destructor ok (no memory management).

    // Default assignment operator ok.

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  ElementListConstraintElement interface.
//

class ElementListConstraintElement : public ConstraintElement
{
public:

    ElementListConstraintElement(
        ConstraintElementList* constraintElementListParam);

    virtual ~ElementListConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    ConstraintElementList*
    GetConstraintElementList() const
    { return constraintElementList; }

    virtual void Accept(Visitor* visitor);

protected:

    ConstraintElementList* constraintElementList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SingleValueConstraintElement interface.
//

class SingleValueConstraintElement : public ConstraintElement
{
public:

    SingleValueConstraintElement(Value* valueParam);

    virtual ~SingleValueConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    Value*
    GetValue() const
    { return value; }

    virtual void Accept(Visitor* visitor);

protected:

    Value* value;

};


////////////////////////////////////////////////////////////////////////////////
//
//  ValueRangeConstraintElement interface.
//

class ValueRangeConstraintElement : public ConstraintElement
{
public:

    ValueRangeConstraintElement(Value* lowerParam, Value* upperParam);

    virtual ~ValueRangeConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    Value*
    GetLower() const
    { return lower; }

    Value*
    GetUpper() const
    { return upper; }

    virtual void Accept(Visitor* visitor);

protected:

    Value* lower;
    Value* upper;

};


////////////////////////////////////////////////////////////////////////////////
//
//  NestedConstraintConstraintElement interface.
//

class NestedConstraintConstraintElement : public ConstraintElement
{
public:

    NestedConstraintConstraintElement(Constraint* constraint);

    virtual ~NestedConstraintConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    Constraint*
    GetConstraint() const
    { return constraint; }

    virtual void Accept(Visitor* visitor);

protected:

    Constraint* constraint;
};


////////////////////////////////////////////////////////////////////////////////
//
//  SizeConstraintElement interface.
//

class SizeConstraintElement : public NestedConstraintConstraintElement
{
public:

    SizeConstraintElement(Constraint * constraint);

    virtual ~SizeConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  FromConstraintElement interface.
//

class FromConstraintElement : public NestedConstraintConstraintElement
{
public:

    FromConstraintElement(Constraint * constraint);

    virtual ~FromConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    virtual void Accept(Visitor* visitor);

protected:

};


////////////////////////////////////////////////////////////////////////////////
//
//  WithComponentConstraintElement interface.
//

class WithComponentConstraintElement : public NestedConstraintConstraintElement
{
public:

    WithComponentConstraintElement(
                    const std::string& nameParam, 
                    Constraint* constraintParam, 
                    int presenceParam);

    virtual ~WithComponentConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    enum {
      COMPONENT_PRESENT,
      COMPONENT_ABSENT,
      COMPONENT_OPTIONAL,
      COMPONENT_DEFAULT
    };

    virtual void Accept(Visitor* visitor);

protected:

    std::string name;
    int         presence;

};


////////////////////////////////////////////////////////////////////////////////
//
//  InnerTypeConstraintElement interface.
//

class InnerTypeConstraintElement : public ElementListConstraintElement
{
public:

    InnerTypeConstraintElement(
                ConstraintElementList* constraintElementListParam, 
                bool partialParam);

    virtual ~InnerTypeConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    bool 
    IsPartial() const
    { return partial; }

    virtual void Accept(Visitor* visitor);

protected:

    bool partial;

};


////////////////////////////////////////////////////////////////////////////////
//
//  UserDefinedConstraintElement interface.
//

class UserDefinedConstraintElement : public ConstraintElement
{
public:

    UserDefinedConstraintElement(TypeList* typeListParam);

    virtual ~UserDefinedConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    TypeList*
    GetTypeList() const
    { return typeList; }

    virtual void Accept(Visitor* visitor);

protected:
   
    TypeList* typeList;

};


////////////////////////////////////////////////////////////////////////////////
//
//  SubTypeConstraintElement interface.
//

class SubTypeConstraintElement : public ConstraintElement
{
public:

    SubTypeConstraintElement(Type* typeParam);

    virtual ~SubTypeConstraintElement() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    Type*
    GetSubtype() const
    { return subtype; }

    virtual void Accept(Visitor* visitor);

protected:
    
    Type* subtype;

};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//
//  ImportedModule interface.
//

class ImportedModule
{
public:

    ImportedModule(
                const std::string& nameParam, 
                TypeList* importedSymbolListParam);

    virtual ~ImportedModule() {}

    // Default copy constructor ok.

    // Default destructor ok (no memory management).

    // Default assignment operator ok.

    const std::string&
    GetName() const
    { return name; }

    TypeList*
    GetImportedSymbolList() const
    { return importedSymbolList; }

    virtual void Accept(Visitor* visitor);

protected:

    std::string     name;
    TypeList*       importedSymbolList;
};


////////////////////////////////////////////////////////////////////////////////
//
//  Module interface.
//

class Module
{
public:

    Module(
        const std::string& nameParam,
        std::list<std::string*>* definitiveIdParam, 
        Tag::TagMode defaultTagModeParam);

    virtual ~Module() {}

    // Default copy constructor ok.

    // Default assignment operator ok.

    enum ModuleError {
        MODULE_PARSE_ERROR,
        MODULE_LINK_ERROR,
        MODULE_RECURSIVE_ERROR,
        MODULE_COMPONENTS_OF_ERROR,
        MODULE_SEMANTIC_ERROR,
        MODULE_EVALUATE_ERROR
    };

    void
    AddError(ModuleError moduleError)
    { errorMultiset.insert(moduleError); }

    bool
    HasErrors() const
    { return !(errorMultiset.empty()); }

    bool
    HasParseErrors()
    { 
        return 
            errorMultiset.find(MODULE_PARSE_ERROR) !=
                errorMultiset.end();
    }

    bool
    HasLinkErrors()
    {
        return
            errorMultiset.find(MODULE_LINK_ERROR) !=
                errorMultiset.end();
    }

    bool
    HasRecursiveErrors()
    {
        return
            errorMultiset.find(MODULE_RECURSIVE_ERROR) !=
                errorMultiset.end();
    }

    bool
    HasComponentsOfErrors()
    {
        return
            errorMultiset.find(MODULE_COMPONENTS_OF_ERROR) !=
                errorMultiset.end();
    }

    bool
    HasSemanticErrors()
    {
        return
            errorMultiset.find(MODULE_SEMANTIC_ERROR) !=
                errorMultiset.end();
    }

    bool
    HasEvaluateErrors()
    {
        return
            errorMultiset.find(MODULE_EVALUATE_ERROR) !=
                errorMultiset.end();
    }

    const std::multiset<ModuleError>&
    GetModuleErrorMultiset() const
    { return errorMultiset; }


    const std::string&
    GetName() const
    { return name; }

    std::list<std::string*>* 
    GetDefinitiveId() const
    { return definitiveId; }

    Tag::TagMode 
    GetDefaultTagMode() const 
    { return defaultTagMode; }

    void 
    SetExportAll()
    { exportAll = true; }

    bool
    ExportAll() const
    { return exportAll; }

    void 
    SetExportedSymbolList(TypeList* exportedSymbolListParam)
    { exportedSymbolList = exportedSymbolListParam; }

    TypeList*
    GetExportedSymbolList() const
    { return exportedSymbolList; }

    void
    AddImportedModule(ImportedModule* importedModule)
    { importedModuleList->push_back(importedModule); }

    ImportedModuleList*
    GetImportedModuleList() const
    { return importedModuleList; }

    void
    AddTypeDef(TypeDef* typeDef)
    { typeDefList->push_back(typeDef); }

    void
    AddValueDef(ValueDef* valueDef)
    { valueDefList->push_back(valueDef); }

    virtual void Accept(Visitor* visitor);

    virtual std::string ToString() const;

    virtual void Print(std::ostream& os) const;

    virtual void PrintFlattened(std::ostream& os) const;

    ////////////////////////////////////////////////////////////////////////////

    void 
    SetAsn1SrcFileName(const std::string& asn1SrcFileNameParam)
    { asn1SrcFileName = asn1SrcFileNameParam; }

    const std::string&
    GetAsn1SrcFileName() const
    { return asn1SrcFileName; }

    void MakeTypeDefTable();

    void MakeValueDefTable();

    void MakeExportedTypeDefTable();

    void MakeExportedValueDefTable();

    void MakeImportedSymbolTable();

    bool 
    HasTypeDef(const std::string& definedName) const
    { 
        return 
            typeDefTable.find(definedName) != 
                typeDefTable.end(); 
    }

    TypeDef* 
    RetrieveTypeDef(const std::string& definedName) const
    {
        REQUIRE(HasTypeDef(definedName));

        TypeDefTable::const_iterator iter = 
            typeDefTable.find(definedName);

        return (*iter).second;
    }

    bool 
    HasValueDef(const std::string& definedName) const
    { 
        return 
            valueDefTable.find(definedName) != 
                valueDefTable.end(); 
    }

    ValueDef* 
    RetrieveValueDef(const std::string& definedName) const
    {
        REQUIRE(HasValueDef(definedName));

        ValueDefTable::const_iterator iter = 
            valueDefTable.find(definedName);

        return (*iter).second;
    }

    bool 
    HasExportedTypeDef(const std::string& definedName) const
    { 
        return 
            exportedTypeDefTable.find(definedName) != 
                exportedTypeDefTable.end();
    }

    TypeDef* 
    RetrieveExportedTypeDef(const std::string& definedName) const
    {
        REQUIRE(HasExportedTypeDef(definedName));

        TypeDefTable::const_iterator iter = 
            exportedTypeDefTable.find(definedName);

        return (*iter).second;
    }

    bool 
    HasExportedValueDef(const std::string& definedName) const
    {
        return
            exportedValueDefTable.find(definedName) !=
                exportedValueDefTable.end();
    }


    ValueDef* 
    RetrieveExportedValueDef(const std::string& definedName) const
    {
        REQUIRE(HasExportedValueDef(definedName));

        ValueDefTable::const_iterator iter = 
            exportedValueDefTable.find(definedName);

        return (*iter).second;
    }


    bool
    HasImportedSymbol(const std::string& symbolName) const
    {
        return
            importedSymbolTable.find(symbolName) !=
                importedSymbolTable.end();
    }


    const std::string&
    RetrieveImportedFromModuleName(const std::string& symbolName) const
    {
        REQUIRE(HasImportedSymbol(symbolName));

        ImportedSymbolTable::const_iterator iter = 
            importedSymbolTable.find(symbolName);

        return (*iter).second;
    }


    bool 
    HasObjectClassReference(const std::string& reference)
    { 
        return objectClassReferenceSet.find(reference) !=
            objectClassReferenceSet.end();
    }


    void
    InsertObjectClassReference(const std::string& reference)
    {
        REQUIRE(!HasObjectClassReference(reference));

        objectClassReferenceSet.insert(reference);
    }


    bool 
    HasObjectReference(const std::string& reference)
    { 
        return objectReferenceSet.find(reference) !=
            objectReferenceSet.end();
    }


    void
    InsertObjectReference(const std::string& reference)
    {
        REQUIRE(!HasObjectReference(reference));

        objectReferenceSet.insert(reference);
    }


    bool 
    HasObjectSetReference(const std::string& reference)
    { 
        return objectSetReferenceSet.find(reference) !=
            objectSetReferenceSet.end();
    }


    void
    InsertObjectSetReference(const std::string& reference)
    {
        REQUIRE(!HasObjectSetReference(reference));

        objectSetReferenceSet.insert(reference);
    }


    virtual void Link(AsnCC& asnCC);

    virtual void NormalizeComponentsOf(AsnCC& asnCC);

    virtual void MarkRecursive(AsnCC& asnCC);

    virtual void CheckSemantic(AsnCC& asnCC);

    virtual void Normalize(AsnCC& asnCC);

    virtual void Evaluate(AsnCC& asnCC);

    virtual void GenerateCpp(AsnCC& asnCC);

    virtual void GenerateCppXmlDoc(AsnCC& asnCC);

    virtual void GenerateC(AsnCC& asnCC);

    virtual void GenerateCXmlDoc(AsnCC& asnCC);

protected:

    std::string                 name;
    std::list<std::string*>*    definitiveId;

    Tag::TagMode        defaultTagMode;

    bool                exportAll;
    TypeList*           exportedSymbolList; // Must be ImportedType only list.

    ImportedModuleList* importedModuleList; // Must be consistent.

    TypeDefList*        typeDefList;
    ValueDefList*       valueDefList;

    std::multiset<ModuleError>  errorMultiset;

    ////////////////////////////////////////////////////////////////////////////

    std::string         asn1SrcFileName;

    typedef std::map<std::string, TypeDef*>     TypeDefTable;
    typedef std::map<std::string, ValueDef*>    ValueDefTable;
    typedef std::map<std::string, std::string>  ImportedSymbolTable;

    TypeDefTable        typeDefTable;
    ValueDefTable       valueDefTable;
    TypeDefTable        exportedTypeDefTable;
    ValueDefTable       exportedValueDefTable;
    ImportedSymbolTable importedSymbolTable;

    ////////////////////////////////////////////////////////////////////////////

    typedef std::set<std::string> ReferenceSet;
    
    ReferenceSet objectClassReferenceSet;
    ReferenceSet objectReferenceSet;
    ReferenceSet objectSetReferenceSet;
    
};


// Module std::ostream operator<< declaration.
std::ostream& operator<< (std::ostream& os, const Module& module);



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


extern Module* moduleG;

#endif // !defined(_ASNCC_ABSTRACT_SYNTAX_TYPES_H_)
