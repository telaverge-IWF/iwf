/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: asn_sequence_of.c,v 9.1 2005/03/23 12:53:01 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

#include <asn_sequence_of.h>
#include <asn_desc_sequence_of.h>
#include <asn_length.h>

static int
ClassPartConstruct(ITS_Class subClass)
{
    if (ASN_SEQUENCE_OF_CLASS_GET_ELEMENTS(subClass) == ASN_SEQUENCE_OF_GET_ELEMENTS_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_GET_ELEMENTS(subClass) =
            ASN_SEQUENCE_OF_CLASS_GET_ELEMENTS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_ADD_ELEMENT(subClass) == ASN_SEQUENCE_OF_ADD_ELEMENT_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_ADD_ELEMENT(subClass) =
            ASN_SEQUENCE_OF_CLASS_ADD_ELEMENT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_GET_ELEMENT_AT(subClass) == ASN_SEQUENCE_OF_GET_ELEMENT_AT_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_GET_ELEMENT_AT(subClass) =
            ASN_SEQUENCE_OF_CLASS_GET_ELEMENT_AT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_REMOVE_ELEMENT(subClass) == ASN_SEQUENCE_OF_REMOVE_ELEMENT_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_REMOVE_ELEMENT(subClass) =
            ASN_SEQUENCE_OF_CLASS_REMOVE_ELEMENT(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_REMOVE_ALL_ELEMENTS(subClass) == ASN_SEQUENCE_OF_REMOVE_ALL_ELEMENTS_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_REMOVE_ALL_ELEMENTS(subClass) =
            ASN_SEQUENCE_OF_CLASS_REMOVE_ALL_ELEMENTS(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_GET_SIZE(subClass) == ASN_SEQUENCE_OF_GET_SIZE_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_GET_SIZE(subClass) =
            ASN_SEQUENCE_OF_CLASS_GET_SIZE(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_IS_EMPTY(subClass) == ASN_SEQUENCE_OF_IS_EMPTY_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_IS_EMPTY(subClass) =
            ASN_SEQUENCE_OF_CLASS_IS_EMPTY(ITS_CLASS_SUPERCLASS(subClass));
    }

    if (ASN_SEQUENCE_OF_CLASS_GET_UNIVERSAL_TAG(subClass) == ASN_SEQUENCE_OF_GET_UNIVERSAL_TAG_INHERIT)
    {
        ASN_SEQUENCE_OF_CLASS_GET_UNIVERSAL_TAG(subClass) =
            ASN_SEQUENCE_OF_CLASS_GET_UNIVERSAL_TAG(ITS_CLASS_SUPERCLASS(subClass));
    }

    return ITS_SUCCESS;
}

static void
ClassPartDestruct(ITS_Class subClass)
{
    /* Nothing to do. */
}

/*
 *  Forward declarations.
 */ 

static ASN_DescSequenceOf GetStaticDescription();
static void RemoveAllElements(ASN_SequenceOf object);
static size_t GetSize(const ASN_SequenceOf object);

static int
Construct(ITS_Object object, va_list args)
{
    ASN_DescSequenceOf description = NULL;

    ASN_C_REQUIRE(object != NULL);

    description = va_arg(args, ASN_DescSequenceOf);

    ASN_SEQUENCE_OF_ELEMENTS(object) = ASN_LinkedList_ConstructDefault();

    ASN_C_ENSURE(ASN_SEQUENCE_OF_ELEMENTS(object) != NULL);

    if (ASN_SEQUENCE_OF_ELEMENTS(object) == NULL)
    {
        return ITS_ENOMEM;
    }

    if (description == NULL)
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)GetStaticDescription();

        if (ASN_OBJECT_DESCRIPTION(object) == NULL)
        {
            if (ASN_SEQUENCE_OF_ELEMENTS(object) != NULL)
            {
                ASN_LinkedList_Destruct(ASN_SEQUENCE_OF_ELEMENTS(object));
                ASN_SEQUENCE_OF_ELEMENTS(object) = NULL;
            }

            return ITS_ENOMEM;
        }

        ASN_C_ASSERT(ASN_OBJECT_DESCRIPTION(object) != NULL);
    }
    else
    {
        ASN_OBJECT_DESCRIPTION(object) = (ASN_DescObject)description;
    }

    return ITS_SUCCESS;
}

static void
Destruct(ITS_Object object)
{
    ASN_C_REQUIRE(object != NULL);

    RemoveAllElements((ASN_SequenceOf)object);

    if (ASN_SEQUENCE_OF_ELEMENTS(object) != NULL)
    {
        ASN_LinkedList_Destruct(ASN_SEQUENCE_OF_ELEMENTS(object));
        ASN_SEQUENCE_OF_ELEMENTS(object) = NULL;
    }
}

static ITS_Object
Clone(ITS_Object object)
{
    ITS_Object result               = NULL;
    ASN_LinkedList elements         = NULL;
    ASN_LinkedList resultElements   = NULL;
    int res                         = ITS_SUCCESS;

    ASN_C_REQUIRE(object != NULL);

    result = (ITS_Object)calloc(1, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    if (result == NULL)
    {
        return result;
    }

    memcpy(result, object, ITS_CLASS_INSTANCE_SIZE(ITS_OBJ_CLASS(object)));

    ASN_SEQUENCE_OF_ELEMENTS(result) = ASN_LinkedList_ConstructDefault();

    ASN_C_ENSURE(ASN_SEQUENCE_OF_ELEMENTS(result) != NULL);

    if (ASN_SEQUENCE_OF_ELEMENTS(result) == NULL)
    {
        free(result);

        return NULL;
    }

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);
    ASN_C_ASSERT(elements != NULL);

    resultElements = ASN_SEQUENCE_OF_ELEMENTS(result);
    ASN_C_ASSERT(resultElements != NULL);

    ASN_LinkedList_CursorSetBegin(elements);

    while (!ASN_LinkedList_CursorIsEnd(elements))
    {
        ASN_Object clonedElement    = NULL;
        ASN_Object element          = NULL;

        element = (ASN_Object)ASN_LinkedList_CursorGetElement(elements);

        ASN_C_ASSERT(element != NULL);

        clonedElement = ASN_Object_Clone(element);

        ASN_C_ENSURE(clonedElement != NULL);

        if (clonedElement == NULL)
        {
            RemoveAllElements((ASN_SequenceOf)result);
            ASN_LinkedList_Destruct(resultElements);
            ASN_SEQUENCE_OF_ELEMENTS(result) = NULL;
            free(result);

            return NULL;
        }

        res = ASN_LinkedList_PushBack(resultElements, (ITS_Object)clonedElement);

        if (res != ITS_SUCCESS)
        {
            RemoveAllElements((ASN_SequenceOf)result);
            ASN_LinkedList_Destruct(resultElements);
            ASN_SEQUENCE_OF_ELEMENTS(result) = NULL;
            free(result);

            return NULL;
        }

        ASN_LinkedList_CursorForth(elements);
    }

    return result;
}

static ITS_BOOLEAN
Equals(ITS_Object object, ITS_Object other)
{
    size_t size                     = 0;
    ASN_LinkedList elements         = NULL;
    ASN_LinkedList otherElements    = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(other != NULL);

    if (ITS_OBJ_CLASS(object) != ITS_OBJ_CLASS(other))
    {
        return ITS_FALSE;
    }

    if (GetSize((ASN_SequenceOf)object) != GetSize((ASN_SequenceOf)other))
    {
        return ITS_FALSE;
    }

    size = GetSize((ASN_SequenceOf)object);

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);
    ASN_C_ASSERT(elements != NULL);

    otherElements = ASN_SEQUENCE_OF_ELEMENTS(other);
    ASN_C_ASSERT(otherElements != NULL);

    ASN_LinkedList_CursorSetBegin(elements);
    ASN_LinkedList_CursorSetBegin(otherElements);

    while (!ASN_LinkedList_CursorIsEnd(elements) && 
           !ASN_LinkedList_CursorIsEnd(otherElements))
    {
        ASN_Object element = (ASN_Object)ASN_LinkedList_CursorGetElement(elements);
        ASN_Object otherElement = (ASN_Object)ASN_LinkedList_CursorGetElement(otherElements);

        ASN_C_ASSERT(element != NULL);
        ASN_C_ASSERT(otherElement != NULL);

        if (!ASN_Object_Equals(element, otherElement))
        {
            return ITS_FALSE;
        }

        ASN_LinkedList_CursorForth(elements);
        ASN_LinkedList_CursorForth(otherElements);
    }

    return ITS_TRUE;
}

static ASN_DescSequenceOf staticDescription = NULL;

static ASN_DescSequenceOf
GetStaticDescription()
{
    static ITS_BOOLEAN initialized      = ITS_FALSE;
    static ASN_DescSequenceOf result    = NULL;
    ASN_SequenceOf cloneForFactory      = NULL;
    ASN_Tag universalTag                = NULL;

    if (initialized)
    {
        ASN_C_ENSURE(result != NULL);

        return result;
    }

    ASN_Lock();

    if (initialized)
    {
        ASN_Unlock();

        ASN_C_ENSURE(result != NULL);

        return result;
    }
    else
    {
        ASN_C_ASSERT(result == NULL);

        staticDescription = ASN_DescSequenceOf_ConstructDefault();

        if (staticDescription == NULL)
        {
            ASN_Unlock();

            return NULL;
        }

        cloneForFactory = ASN_SequenceOf_ConstructWithDescription(staticDescription);

        if (cloneForFactory == NULL)
        {
            ASN_DescSequenceOf_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescSequenceOf_SetCloneForFactory(staticDescription, cloneForFactory);

        universalTag = ASN_SequenceOf_GetUniversalTag(cloneForFactory);

        if (universalTag == NULL)
        {
            ASN_DescSequenceOf_Destruct(staticDescription);
            staticDescription = NULL;

            ASN_Unlock();

            return NULL;
        }

        ASN_DescSequenceOf_TagAddLevel(staticDescription, universalTag);

        result = staticDescription;

        initialized = ITS_TRUE;

        ASN_Unlock();

        ASN_C_ENSURE(result != NULL);

        return result;
    }
}

static void
DestructStaticDescription()
{
    if (staticDescription != NULL)
    {
        ASN_DescSequenceOf_Destruct(staticDescription);
        staticDescription = NULL;
    }
}

/*
 *  Forward declarations.
 */ 

static size_t GetSize(const ASN_SequenceOf object);

static const ASN_LinkedList 
GetElements(const ASN_SequenceOf object)
{
    ASN_LinkedList result = NULL;

    ASN_C_REQUIRE(object != NULL);

    result = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static int
AddElement(ASN_SequenceOf object, ASN_Object element)
{
    ASN_LinkedList elements = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(element != NULL);

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    return ASN_LinkedList_PushBack(elements, (ITS_Object)element);
}

static const ASN_Object 
GetElementAt(const ASN_SequenceOf object, size_t index)
{
    ASN_Object result       = NULL;
    ASN_LinkedList elements = NULL;
    int i                   = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    ASN_LinkedList_CursorSetBegin(elements);

    for (i = 0; i < (int)index; i++)
    {
        ASN_LinkedList_CursorForth(elements);
    }

    ASN_C_ASSERT(!ASN_LinkedList_CursorIsEnd(elements));

    result = (ASN_Object)ASN_LinkedList_CursorGetElement(elements);

    ASN_C_ENSURE(result != NULL);

    return result;
}

static void 
RemoveElement(ASN_SequenceOf object, size_t index)
{
    ASN_Object element      = NULL;
    ASN_LinkedList elements = NULL;
    int i                   = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(index < GetSize(object));

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    ASN_LinkedList_CursorSetBegin(elements);

    for (i = 0; i < (int)index; i++)
    {
        ASN_LinkedList_CursorForth(elements);
    }

    ASN_C_ASSERT(!ASN_LinkedList_CursorIsEnd(elements));

    element = (ASN_Object)ASN_LinkedList_CursorGetElement(elements);

    ASN_C_ASSERT(element != NULL);

    ASN_Object_Destruct(element);

    ASN_LinkedList_CursorRemoveElement(elements);
}

static void 
RemoveAllElements(ASN_SequenceOf object)
{
    int i                   = 0;
    size_t size             = 0;
    ASN_LinkedList elements = NULL;

    ASN_C_REQUIRE(object != NULL);

    size = GetSize(object);

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    for (i = 0; i < (int)size; i++)
    {
        ASN_Object element = (ASN_Object)ASN_LinkedList_GetBack(elements);

        ASN_C_ASSERT(element != NULL);

        ASN_Object_Destruct(element);

        ASN_LinkedList_PopBack(elements);
    }
}

static size_t 
GetSize(const ASN_SequenceOf object)
{
    ASN_LinkedList elements = NULL;

    ASN_C_REQUIRE(object != NULL);

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    return ASN_LinkedList_GetSize(elements);
}

static ITS_BOOLEAN
IsEmpty(const ASN_SequenceOf object)
{
    ASN_LinkedList elements = NULL;

    ASN_C_REQUIRE(object != NULL);

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    return ASN_LinkedList_GetSize(elements) == 0;
}

static ASN_Tag
GetUniversalTag(const ASN_SequenceOf object)
{
    ASN_C_REQUIRE(object != NULL);

    return ASN_Tag_ConstructWithClassTypeNumber(
                                        TAG_CLASS_UNIVERSAL,
                                        TAG_PRIMITIVE,
                                        TAG_SEQUENCE);
}

static int 
Encode(ASN_Object object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{   
    typedef ITS_OCTET byte;

    ASN_DescSequenceOf description = NULL;

    ASN_Octets valOctets    = NULL;
    size_t size             = 0;
    ASN_LinkedList elements = NULL;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(encodeError != NULL);
    ASN_C_REQUIRE(*octets == NULL);
    ASN_C_REQUIRE(*encodeError == NULL);

    description = (ASN_DescSequenceOf)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    size = GetSize((ASN_SequenceOf)object);

    /* Encode check begin. */

    if (ASN_DescSequenceOf_IsClauseSize(description))
    {
        if (size > ASN_DescSequenceOf_GetMaxSize(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_SEQUENCE_OF_SIZE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
        
        if (size < ASN_DescSequenceOf_GetMinSize(description))
        {
            *encodeError = 
                ASN_CONSTRUCT_ENCODE_ERROR(
                    ASN_E_INVALID_SEQUENCE_OF_SIZE, 
                    object); 

            return ITS_E_ASN_ENCODE_ERROR;
        }
    }

    /* Encode check end. */

    valOctets = ASN_Octets_ConstructDefault();

    if (valOctets == NULL)
    {
        return ITS_ENOMEM;
    }

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    ASN_LinkedList_CursorSetBegin(elements);

    while (!ASN_LinkedList_CursorIsEnd(elements))
    {
        int res                     = ITS_SUCCESS;
        ASN_Octets elementOctets    = NULL;
        ASN_Object element          = (ASN_Object)ASN_LinkedList_CursorGetElement(elements);

        ASN_C_ASSERT(element != NULL);

        res = ASN_Object_Encode(element, &elementOctets, encodeError);

        if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(valOctets);

            return res;
        }

        res = ASN_Octets_Append(valOctets, elementOctets);

        if (res != ITS_SUCCESS)
        {
            ASN_Octets_Destruct(valOctets);
            ASN_Octets_Destruct(elementOctets);

            return res;
        }

        ASN_Octets_Destruct(elementOctets);

        ASN_LinkedList_CursorForth(elements);
    }

    *octets = ASN_Object_EncodeTagLengthValue((ASN_Object)object, valOctets);

    if (*octets == NULL)
    {
        ASN_Octets_Destruct(valOctets);

        return ITS_ENOMEM;
    }

    ASN_Octets_Destruct(valOctets);

    return ITS_SUCCESS;
}

static int
Decode(ASN_Object object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    typedef ITS_OCTET byte;

    int res                         = ITS_SUCCESS;
    ASN_DescSequenceOf description  = NULL;
    ASN_Tag tag                     = NULL;
    ASN_Length length               = NULL;
    size_t startOffset              = 0;
    ITS_BOOLEAN stop                = ITS_FALSE;
    size_t size                     = 0;

    ASN_C_REQUIRE(object != NULL);
    ASN_C_REQUIRE(octets != NULL);
    ASN_C_REQUIRE(decodeError != NULL);
    ASN_C_REQUIRE(*decodeError == NULL);

    description = (ASN_DescSequenceOf)ASN_OBJECT_DESCRIPTION(object);

    ASN_C_ASSERT(description != NULL);

    res = ASN_Object_DecodeRemoveExtraTagLength(
                                            object,
                                            octets,
                                            decodeError);

    if (res != ITS_SUCCESS)
    {
        return res;
    }

    tag = ASN_Tag_ConstructDefault();

    if (tag == NULL)
    {
        return ITS_ENOMEM;
    }

    res = ASN_Tag_Decode(tag, octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        ASN_Tag_Destruct(tag);

        return res;
    }

    ASN_Tag_Destruct(tag);
    tag = NULL;

    length = ASN_Length_ConstructDefault();

    if (length == NULL)
    {
        return ITS_ENOMEM;
    }

    res = ASN_Length_Decode(length, octets, decodeError);

    if (res != ITS_SUCCESS)
    {
        ASN_Length_Destruct(length);

        return res;
    }

    startOffset = ASN_Octets_GetOffset(octets);

    stop = ITS_FALSE;

    if (ASN_Length_GetLength(length) == 0)
    {
        stop = ITS_TRUE;
    }

    RemoveAllElements((ASN_SequenceOf)object);

    while (!stop)
    {
        size_t currentOffset    = 0;

        ASN_Tag elementTag = NULL;

        elementTag = ASN_Tag_ConstructDefault();

        if (elementTag == NULL)
        {
            ASN_Length_Destruct(length);

            return ITS_ENOMEM;
        }

        res = ASN_Tag_DecodePreserveOffset(elementTag, octets, decodeError);

        if (res != ITS_SUCCESS)
        {
            ASN_Length_Destruct(length);
            ASN_Tag_Destruct(elementTag);

            return res;
        }

        if (ASN_DescSequenceOf_Contains(description, elementTag))
        {
            ASN_DescObject elementDescription = 
                ASN_DescSequenceOf_GetElement(description);

            ASN_Object element = ASN_DescObject_Factory(elementDescription);

            if (element == NULL)
            {
                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);

                return ITS_ENOMEM;
            }

            res = ASN_Object_Decode(element, octets, decodeError);

            if (res != ITS_SUCCESS)
            {
                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);
                ASN_Object_Destruct(element);

                return res;
            }

            AddElement((ASN_SequenceOf)object, element);
        }
        else
        {
            *decodeError =
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_UNKNOWN_ELEMENT_IN_SEQUENCE_OF,
                    object,
                    octets);
            
            ASN_Length_Destruct(length);
            ASN_Tag_Destruct(elementTag);

            return ITS_E_ASN_DECODE_ERROR;
        }

        currentOffset = ASN_Octets_GetOffset(octets);

        if (!ASN_Length_IsIndefinite(length))
        {
            if (ASN_Length_GetLength(length) == (ITS_LONG)(currentOffset - startOffset))
            {
                stop = ITS_TRUE;
            }
            else if (ASN_Length_GetLength(length) > (ITS_LONG)(currentOffset - startOffset))
            {
                stop = ITS_FALSE;
            }
            else
            {
                *decodeError = 
                    ASN_CONSTRUCT_DECODE_ERROR(
                        ASN_E_INVALID_ELEMENT_LENGTH_IN_SEQUENCE_OF,
                        object,
                        octets);

                ASN_Length_Destruct(length);
                ASN_Tag_Destruct(elementTag);

                return ITS_E_ASN_DECODE_ERROR;
            }
        }
        else
        {
            if (ASN_Length_IsIndefiniteEndMark(length, octets))
            {
                ASN_Length_IndefiniteEndMarkIncOffset(length, octets);
                stop = ITS_TRUE;
            }
            else
            {
                stop = ITS_FALSE;
            }
        }

        ASN_Tag_Destruct(elementTag);
        elementTag = NULL;
    }

    ASN_Length_Destruct(length);

    size = GetSize((ASN_SequenceOf)object);

    /* Decode check begin. */

    if (ASN_DescSequenceOf_IsClauseSize(description) && 
        !ASN_Options_GlobalIsDecodeIgnoreSequenceOfSizeConstraint())
    {
        if (size > ASN_DescSequenceOf_GetMaxSize(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_SEQUENCE_OF_SIZE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
        
        if (size < ASN_DescSequenceOf_GetMinSize(description))
        {
            *decodeError = 
                ASN_CONSTRUCT_DECODE_ERROR(
                    ASN_E_INVALID_OCTET_STRING_SIZE, 
                    object,
                    octets); 

            return ITS_E_ASN_DECODE_ERROR;
        }
    }

    /* Decode check end. */

    return ITS_SUCCESS;
}

static const char*
GetName(const ASN_Object object)
{
    return "SEQUENCE_OF";
}

static const char*
GetBaseName(const ASN_Object object)
{
    return "SEQUENCE_OF";
}

/*
 *  Helper function to destruct a linked list of strings.
 */

static void
StringListDestruct(ASN_LinkedList stringList)
{
    ASN_C_REQUIRE(stringList != NULL);

    ASN_LinkedList_CursorSetBegin(stringList);

    while (!ASN_LinkedList_CursorIsEnd(stringList))
    {
        char* str = (char*)ASN_LinkedList_CursorGetElement(stringList);

        ASN_C_ASSERT(str != NULL);

        free(str);

        ASN_LinkedList_CursorForth(stringList);
    }

    ASN_LinkedList_Destruct(stringList);
}

static char*
ToString(const ASN_Object object)
{
    char* result                = NULL;
    char* buffer                = NULL;
    const char* nameStr         = ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))(object);
    const char* baseNameStr     = ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))(object);
    char* toString              = NULL;
    char* toStringLineShifted   = NULL;
    size_t maxStringSize        = 0;
    ASN_LinkedList stringList   = NULL;
    ITS_BOOLEAN first           = ITS_FALSE;
    ASN_LinkedList elements     = NULL;

    ASN_C_REQUIRE(object != NULL);

    stringList = ASN_LinkedList_ConstructDefault();

    if (stringList == NULL)
    {
        return NULL;
    }

    elements = ASN_SEQUENCE_OF_ELEMENTS(object);

    ASN_C_ASSERT(elements != NULL);

    ASN_LinkedList_CursorSetBegin(elements);

    while (!ASN_LinkedList_CursorIsEnd(elements))
    {

        ASN_Object element = (ASN_Object)ASN_LinkedList_CursorGetElement(elements);

        ASN_C_ASSERT(element != NULL);

        toString = ASN_Object_ToString(element);

        if (toString == NULL)
        {
            StringListDestruct(stringList);

            return NULL;
        }

        toStringLineShifted = ASN_AddLineShift(toString);

        if (toStringLineShifted == NULL)
        {
            StringListDestruct(stringList);
            free(toString);
            
            return NULL;
        }

        free(toString);

        ASN_LinkedList_PushBack(stringList, (ITS_Object)toStringLineShifted);

        ASN_LinkedList_CursorForth(elements);
    }

    maxStringSize = strlen(nameStr) + strlen(baseNameStr) + 32;

    ASN_LinkedList_CursorSetBegin(stringList);

    while (!ASN_LinkedList_CursorIsEnd(stringList))
    {
        char* str = (char*)ASN_LinkedList_CursorGetElement(stringList);

        maxStringSize += strlen(str) + 1;

        ASN_LinkedList_CursorForth(stringList);
    }

    result = (char*)calloc(maxStringSize, sizeof(char));

    if (result == NULL)
    {
        StringListDestruct(stringList);
    
        return NULL;
    }

    buffer = result;

    sprintf(
        buffer,
        "%s (%s)\n{\n",
        nameStr,
        baseNameStr);

    first = ITS_TRUE;

    ASN_LinkedList_CursorSetBegin(stringList);

    while (!ASN_LinkedList_CursorIsEnd(stringList))
    {
        char* str = (char*)ASN_LinkedList_CursorGetElement(stringList);

        ASN_C_ASSERT(str != NULL);

        if (!first)
        {
            strcat(buffer, "\n");
        }
        else
        {
            first = ITS_FALSE;
        }

        strcat(buffer, str);

        ASN_LinkedList_CursorForth(stringList);
    }

    strcat(buffer, "}\n");

    StringListDestruct(stringList);

    ASN_C_ASSERT(strlen(result) + 1 < maxStringSize);

    ASN_C_ENSURE(result != NULL);

    return result;
}

/*
 *  ASN_SequenceOf class record.
 */ 

ASN_SequenceOf_ClassRec itsASN_SequenceOf_ClassRec =
{
    /* Core part. */

    {
        (ITS_Class)&itsASN_Object_ClassRec,
        sizeof(ASN_SequenceOf_ObjectRec),    
        ITS_FALSE,                         
        0,                                 
        ASN_SEQUENCE_OF_CLASS_NAME,           
        ITS_CLASS_NO_INIT,                 
        ITS_CLASS_NO_DEST,  
        ClassPartConstruct,                
        ClassPartDestruct,                 
        Construct,                         
        Destruct,                          
        Clone,                             
        ITS_INST_PRINT_INHERIT,            
        ITS_INST_SERIAL_INHERIT,           
        Equals,                            
        ITS_INST_HASH_INHERIT,             
        NULL                               
    },

    /* ASN_Object class part. */

    {
        Encode,       
        Decode,       
        GetName,      
        GetBaseName,  
        ToString,     
        ASN_OBJECT_GET_ENCODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_GET_DECODE_EXTENDED_ERROR_TEXT_INHERIT,
        ASN_OBJECT_ENCODE_TAG_LENGTH_VALUE_INHERIT,
        ASN_OBJECT_DECODE_REMOVE_EXTRA_TAG_LENGTH_INHERIT
    },

    /* ASN_SequenceOf class part. */

    {
        GetStaticDescription,
        DestructStaticDescription,
        GetElements,
        AddElement,
        GetElementAt,
        RemoveElement,
        RemoveAllElements,
        GetSize,
        IsEmpty,
        GetUniversalTag
    }
};

ASN_SequenceOf 
ASN_SequenceOf_ConstructDefault()
{
    ASN_SequenceOf result = NULL;

    result = (ASN_SequenceOf)ITS_ConstructObject((ITS_Class)&itsASN_SequenceOf_ClassRec, NULL);

    ASN_C_ENSURE(result != NULL);

    return result;
}

ASN_SequenceOf 
ASN_SequenceOf_ConstructWithDescription(ASN_DescSequenceOf description)
{
    ASN_SequenceOf result = NULL;

    result = (ASN_SequenceOf)ITS_ConstructObject((ITS_Class)&itsASN_SequenceOf_ClassRec, description);

    ASN_C_ENSURE(result != NULL);

    return result;
}

void
ASN_SequenceOf_Destruct(ASN_SequenceOf object)
{
    ITS_DestructObject((ITS_Object)object);
}

ASN_SequenceOf 
ASN_SequenceOf_Clone(const ASN_SequenceOf object)
{
    return (ASN_SequenceOf)ITS_CLASS_CLONE(ITS_OBJ_CLASS(object))((ITS_Object)object);    
}

ITS_BOOLEAN 
ASN_SequenceOf_Equals(const ASN_SequenceOf object, const ASN_SequenceOf other)
{
    return ITS_CLASS_EQUALS(ITS_OBJ_CLASS(object))((ITS_Object)object, (ITS_Object)other);
}

ASN_DescSequenceOf 
ASN_SequenceOf_GetStaticDescription()
{
    return GetStaticDescription();
}

void ASN_SequenceOf_DestructStaticDescription()
{
    DestructStaticDescription();
}

const ASN_LinkedList
ASN_SequenceOf_GetElements(const ASN_SequenceOf object)
{
    return ASN_SEQUENCE_OF_CLASS_GET_ELEMENTS(ITS_OBJ_CLASS(object))(object);
}

int
ASN_SequenceOf_AddElement(ASN_SequenceOf object, ASN_Object element)
{
    return ASN_SEQUENCE_OF_CLASS_ADD_ELEMENT(ITS_OBJ_CLASS(object))(object, element);
}

const ASN_Object 
ASN_SequenceOf_GetElementAt(const ASN_SequenceOf object, size_t index)
{
    return ASN_SEQUENCE_OF_CLASS_GET_ELEMENT_AT(ITS_OBJ_CLASS(object))(object, index);
}

void 
ASN_SequenceOf_RemoveElement(ASN_SequenceOf object, size_t index)
{
    ASN_SEQUENCE_OF_CLASS_REMOVE_ELEMENT(ITS_OBJ_CLASS(object))(object, index);
}

void 
ASN_SequenceOf_RemoveAllElements(ASN_SequenceOf object)
{
    ASN_SEQUENCE_OF_CLASS_REMOVE_ALL_ELEMENTS(ITS_OBJ_CLASS(object))(object);
}

size_t 
ASN_SequenceOf_GetSize(const ASN_SequenceOf object)
{
    return ASN_SEQUENCE_OF_CLASS_GET_SIZE(ITS_OBJ_CLASS(object))(object);
}

ITS_BOOLEAN
ASN_SequenceOf_IsEmpty(const ASN_SequenceOf object)
{
    return ASN_SEQUENCE_OF_CLASS_IS_EMPTY(ITS_OBJ_CLASS(object))(object);
}

ASN_Tag 
ASN_SequenceOf_GetUniversalTag(const ASN_SequenceOf object)
{
    return ASN_SEQUENCE_OF_CLASS_GET_UNIVERSAL_TAG(ITS_OBJ_CLASS(object))(object);
}

int 
ASN_SequenceOf_Encode(ASN_SequenceOf object, ASN_Octets* octets, ASN_EncodeError* encodeError)
{
    return ASN_OBJECT_CLASS_ENCODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, encodeError);
}

int 
ASN_SequenceOf_Decode(ASN_SequenceOf object, ASN_Octets octets, ASN_DecodeError* decodeError)
{
    return ASN_OBJECT_CLASS_DECODE(ITS_OBJ_CLASS(object))((ASN_Object)object, octets, decodeError);
}

const char* 
ASN_SequenceOf_GetName(const ASN_SequenceOf object)
{
    return ASN_OBJECT_CLASS_GET_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

const char* 
ASN_SequenceOf_GetBaseName(const ASN_SequenceOf object)
{
    return ASN_OBJECT_CLASS_GET_BASE_NAME(ITS_OBJ_CLASS(object))((ASN_Object)object);
}

void 
ASN_SequenceOf_Print(const ASN_SequenceOf object)
{
    ITS_CLASS_PRINT(ITS_OBJ_CLASS(object))((ITS_Object)object);
}

char* 
ASN_SequenceOf_ToString(const ASN_SequenceOf object)
{
    return ASN_OBJECT_CLASS_TO_STRING(ITS_OBJ_CLASS(object))((ASN_Object)object);
}



