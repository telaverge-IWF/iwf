/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: dia_dict_parse.cpp,v $
 * LOG: Revision 3.4.6.4.6.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.4.6.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.4.28.2  2012/11/20 10:31:55  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.4  2010/07/07 08:24:46  nvijikumar
 * LOG: TCS compilation flags support
 * LOG:
 * LOG: Revision 3.3  2009/05/12 08:42:31  rajeshak
 * LOG: Klockwork reported Issue fix.
 * LOG:
 * LOG: Revision 3.2  2009/03/03 11:17:20  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.12  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.9.8.3  2008/01/24 10:37:45  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 1.9.8.2  2007/03/23 12:36:41  nvijikumar
 * LOG: Fix for application hang if duplicate entries made in dictionary file
 * LOG:
 * LOG: Revision 1.9.8.1  2007/03/22 08:41:40  tpanda
 * LOG: ExtraAttributes creation based on avpCode and vendorId together
 * LOG:
 * LOG: Revision 1.9  2006/12/05 07:06:04  tpanda
 * LOG: Checking is put for any missing closed tag in dictionary file
 * LOG:
 * LOG: Revision 1.8  2006/11/30 18:16:25  tpanda
 * LOG: Fix for multiple command addition bug(#4990)
 * LOG:
 * LOG: Revision 1.7  2006/11/29 16:23:24  nvijikumar
 * LOG: Extensibility bug fixes
 * LOG:
 * LOG: Revision 1.6  2006/11/14 09:09:17  tpanda
 * LOG: Fix for crash while exiting the application(using ctrl+c)
 * LOG:
 * LOG: Revision 1.5  2006/11/13 05:39:39  tpanda
 * LOG: dictionary extensible AVP encoding/decoding fix
 * LOG:
 * LOG: Revision 1.4  2006/11/07 11:18:01  tpanda
 * LOG: codec library separated from stack library
 * LOG:
 * LOG: Revision 1.3  2006/10/25 13:25:31  tpanda
 * LOG: For extensible AVP support
 * LOG:
 * LOG: Revision 1.2  2006/10/24 09:04:10  tpanda
 * LOG: Dictionary file related changes
 * LOG:
 * LOG: Revision 1.1  2006/10/05 06:07:53  tpanda
 * LOG: Enable dictionary parsing for extensible AVPs
 * LOG:
 ****************************************************************************/

#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <strings.h>
#include <signal.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

#include <its++.h>
#include <its_exception.h>
#include <its_exception_log.h>
#include <its_event_log.h>
#include <its_iniparse.h>

#include <expat.h>

#include <dia_dict_parse.h>
#include <itsdiameter.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace diameter;
#endif

diameter::CommandAttribute * cmdAttrb;
diameter::GroupedAttributeName *groupedAttObj;
unsigned int cmdCode, appId, avpIndex;

static ITS_BOOLEAN inCommand     = ITS_FALSE;
static ITS_BOOLEAN inAvp         = ITS_FALSE;
static ITS_BOOLEAN isRequest     = ITS_FALSE;
static ITS_BOOLEAN isAnswer      = ITS_FALSE;
static ITS_BOOLEAN isRequired    = ITS_FALSE;
static ITS_BOOLEAN isOptional    = ITS_FALSE;
static ITS_BOOLEAN isGrouped     = ITS_FALSE;

static XML_Parser   dictParser;
static ITS_BOOLEAN  inDictParser = ITS_FALSE;

#define DIA_DICT_PARSER_ASSERT(assertion)                                               \
    if (!(assertion))                                                              \
    {                                                                              \
        ITS_ASSERT_PRINT(assertion);                                               \
        if (inDictParser)                                                              \
        {                                                                          \
            fprintf(stderr, "At around line %d column %d in parsed text.\n",       \
                    XML_GetCurrentLineNumber(dictParser),                              \
                    XML_GetCurrentColumnNumber(dictParser));                           \
        }                                                                          \
        exit(0);                                                                   \
    }

DictAttributeList::DictAttributeList()
{
   _AttributeList = (AttributeName **) calloc 
                    (10,sizeof(AttributeName *));
   if (_AttributeList == NULL)
   {
       //calloc failed throw exception();
       throw "Error: memory allocation failed";
   }
   _noOfAttribute = 10;
}

DictAttributeList::~DictAttributeList()
{
   for(unsigned int i =0; 
      (i < _noOfAttribute) && _AttributeList[i]; 
      ++i)
   {
      const char* buff = (*_AttributeList[i]);
      free((char*)buff);
      delete _AttributeList[i];
   }
   free(_AttributeList);
   _AttributeList = NULL;
}

void
DictAttributeList::reArrange()
{
   unsigned int index = _avpCodeIndex.size();
   if (index && _AttributeList[index])
   {
      /* insert entry to _avpCodeindex variable*/
       unsigned long long key = _AttributeList[index]->vendorId();
       unsigned int avpCode = _AttributeList[index]->GetCode();
       key = ((key << 32) | avpCode);
       map<unsigned long long,unsigned int>::const_iterator it =
           _avpCodeIndex.find(key);
       DIA_DICT_PARSER_ASSERT (it == _avpCodeIndex.end());
       _avpCodeIndex[key]=index;
   }
}

AttributeName*& 
DictAttributeList::operator [](unsigned int index)
{
   unsigned int Idx = index;
   if(Idx && ((Idx%10) ==0) && (Idx >= _noOfAttribute))
   {
      int count= Idx/10;
      count++;
      _AttributeList = (AttributeName **) 
               realloc(_AttributeList,
               10*count*sizeof(AttributeName*));

      if (_AttributeList == NULL)
      {
         // realloc failed throw exception();
         throw "Error: memory allocation failed";
      }

      while(Idx < (10 * count))
      {
         _AttributeList[Idx]=NULL;
         Idx++;
      }
      _noOfAttribute = Idx;
   }
   DIA_DICT_PARSER_ASSERT(index <= _noOfAttribute);
   if (index > _avpCodeIndex.size()
       && _AttributeList[index-1])
   {
      /* insert entry to _avpCodeindex variable*/
       unsigned long long key = _AttributeList[index-1]->vendorId();
       unsigned int avpCode = _AttributeList[index-1]->GetCode();
       key = ((key << 32) | avpCode);
       map<unsigned long long,unsigned int>::const_iterator it =
          _avpCodeIndex.find(key);
       DIA_DICT_PARSER_ASSERT (it == _avpCodeIndex.end());
       _avpCodeIndex[key]=index-1;
   }
   return _AttributeList[index];
}

const AttributeName* 
DictAttributeList::getAttribute(unsigned int avp, unsigned int venId)
{
   const AttributeName* name=NULL;
   unsigned long long key = venId;
   key = ((key << 32) | avp);
   map<unsigned long long,unsigned int>::const_iterator it =
       _avpCodeIndex.find(key);
   if (it != _avpCodeIndex.end())
   {
       name = (*this)[(*it).second];
   }
   return name;
}

class DictAttributeList DictAttributeList::_dictAttributeList;

static struct OctetStringAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new OctetStringAvp(*_name, impl);
    }
} _OctetStringAvpBuilder;

static struct Integer32AvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new Integer32Avp(*_name,impl);
    }
} _Integer32AvpBuilder;

static struct Integer64AvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new Integer64Avp(*_name,impl);
    }
} _Integer64AvpBuilder;

/**
 * Added Float32AvpBuiler struct
 */
static struct Float32AvpBuilder: public diameter::AvpBuilder {
    AVP *build(const AVPImpl *impl) const {
        return new Float32Avp(*_name,impl);
    }
} _Float32AvpBuilder;

/**
 * Added Float64AvpBuiler struct
 */
static struct Float64AvpBuilder: public diameter::AvpBuilder {
    AVP *build(const AVPImpl *impl) const {
        return new Float64Avp(*_name,impl);
    }
} _Float64AvpBuilder;

static struct Unsigned32AvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new Unsigned32Avp(*_name,impl);
    }
} _Unsigned32AvpBuilder;

static struct Unsigned64AvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new Unsigned64Avp(*_name,impl);
    }
} _Unsigned64AvpBuilder;

static struct AddressAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new AddressAvp(*_name,impl);
    }
} _AddressAvpBuilder;

static struct TimeAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new TimeAvp(*_name,impl);
    }
} _TimeAvpBuilder;

static struct URIAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
     return new URIAvp(*_name,impl);
     }
} _URIAvpBuilder;

static struct UTF8StringAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new UTF8StringAvp(*_name,impl);
    }
} _UTF8StringAvpBuilder;

static struct IdentityAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new IdentityAvp(*_name,impl);
    }
} _IdentityAvpBuilder;

static struct IPFilterRuleAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new IPFilterRuleAvp(*_name,impl);
    }
} _IPFilterRuleAvpBuilder;

static struct EnumeratedAvpBuilder: public diameter::AvpBuilder {
AVP *build(const AVPImpl *impl) const {
    return new EnumeratedAvp(*_name,impl);
    }
} _EnumeratedAvpBuilder;

static struct GroupedAvpBuilder: public diameter::AvpBuilder {
    AVP *build(const AVPImpl *impl) const {
        return new DerivedGroupedAVP(*_name, impl);
    }
} _GroupedAvpBuilder;


//Warning Fix - control reaches end of non-void function
diameter::AvpBuilder& GetTypeAvp(unsigned int dictType)
{
    switch (dictType)
    {
    case OctetStringType:
        return  _OctetStringAvpBuilder;
    case Integer32Type:
        return _Integer32AvpBuilder;
    case Integer64Type:
        return _Integer64AvpBuilder;
    case Unsigned32Type:
        return _Unsigned32AvpBuilder;
    case Unsigned64Type:
        return _Unsigned64AvpBuilder;
    case Float32Type:
        return _Float32AvpBuilder;
    case Float64Type:
        return _Float64AvpBuilder;
    case AddressType:
        return _AddressAvpBuilder;
    case TimeType:
        return _TimeAvpBuilder;
    case URIType:
        return _URIAvpBuilder;
    case UTF8StringType:
        return _UTF8StringAvpBuilder;
    case IdentityType:
        return _IdentityAvpBuilder;
    case IPFilterRuleType:
        return _IPFilterRuleAvpBuilder;
    case EnumeratedType:
        return _EnumeratedAvpBuilder;
    }

    //Warning Fix - KLUDGE: Need to correct this later.
    //Adding return statement to remove compilation warning
    //Adding return with _OctetStringAvpBuilder will not harm
    //the existing code. 
    return _OctetStringAvpBuilder;
}


static void
HandleCommand(const char *el, const char **attr)
{
    inCommand = ITS_TRUE;

    while (*attr)
    {
        const char *tattr = *attr;
        attr++;

        if (strcmp(tattr, DIA_DICT_CODE_STRING) == 0)
        {
             cmdCode = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_APPID_STRING) == 0)
        {
             appId = RESFILE_ParseNum(*attr);
        }
        attr++;
    }
}

static void
HandleAvp(const char *el, const char **attr)
{
    const char* name = NULL;
    //Initializing Uninitialized Scalar Variable
    unsigned int type = 0, venId = 0, code = 0;
    ITS_BOOLEAN mand = false, encr = false;
    ImpBuilder* impBuilder    =NULL;
    while (*attr)
    {
        const char *tattr = *attr;
        attr++;
        if (strcmp(tattr, DIA_DICT_AVPINDEX_STRING) == 0)
        {
            avpIndex = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_NAME_STRING) == 0)
        {
            //fix for coverity issue CID 10586
            if(NULL != name)
            {
                free((char*)name);
                name = NULL;
            }
            name = strdup(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_CODE_STRING) == 0)
        {
            code = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_MAND_STRING) == 0)
        {
            mand = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_ENCR_STRING) == 0)
        {
            encr = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_TYPE_STRING) == 0)
        {
            type = RESFILE_ParseNum(*attr);
        }
        else if (strcmp(tattr, DIA_DICT_VENID_STRING) == 0)
        {
            venId = RESFILE_ParseNum(*attr);
        }
        attr++;
    }
    if ( type == 20)
    {
        groupedAttObj= new  GroupedAttributeName(name,_GroupedAvpBuilder, *impBuilder, code,
                                      venId, ((mand == 1)? true:false),
                                      ((encr == 1)? true:false), false);
        isGrouped=ITS_TRUE;
    } 
    else
    {
        AttributeName *attObj = new AttributeName(name,GetTypeAvp(type), *impBuilder, code,
                                      venId, ((mand == 1)? true:false),
                                      ((encr == 1)? true:false), false);
        if (DictAttributeList::_dictAttributeList[avpIndex-1])
        {
           delete DictAttributeList::_dictAttributeList[avpIndex-1];
           DictAttributeList::_dictAttributeList[avpIndex-1] = NULL;
        }
        DictAttributeList::_dictAttributeList[avpIndex-1]=attObj;
    }
}

static void
HandleAvpRule(const char *el, const char **attr)
{ 
    int avpIndex = 1;
    while(*attr)
    {
        const char *tattr = *attr;
        attr++;
        if (strcmp(tattr, DIA_DICT_AVPINDEX_STRING) == 0)
        {
            avpIndex=RESFILE_ParseNum(*attr);
        }
        attr++;
    }
    if(DictAttributeList::_dictAttributeList[avpIndex-1])
    {
        if(inCommand && isRequest)
        {
            DIA_DICT_PARSER_ASSERT(DictAttributeList::_dictAttributeList[avpIndex-1]);
            CommandAttribute::addAttribute(appId, cmdCode, 
            *DictAttributeList::_dictAttributeList[avpIndex-1]);
        }
        else if(inCommand && isAnswer)
        {
            DIA_DICT_PARSER_ASSERT(DictAttributeList::_dictAttributeList[avpIndex-1]);
            CommandAttribute::addAttribute(appId, cmdCode, 
            *DictAttributeList::_dictAttributeList[avpIndex-1], false);
        }
        else if(isGrouped && isRequired)
        {
            DIA_DICT_PARSER_ASSERT(DictAttributeList::_dictAttributeList[avpIndex-1]);
            std::map<unsigned int, AttributeName *> &dictGrpMandAvp = 
                 groupedAttObj->GetMandAttMap();
            AttributeName* Name = DictAttributeList::_dictAttributeList[avpIndex-1];
            dictGrpMandAvp[Name->GetCode()]=Name;
            Name->SetIndex(dictGrpMandAvp.size() +
                            groupedAttObj->GetOptAttMap().size());
        }
        else if(isGrouped && isOptional)
        {
            DIA_DICT_PARSER_ASSERT(DictAttributeList::_dictAttributeList[avpIndex-1]);
            std::map<unsigned int, AttributeName *> &dictGrpOptAvp =
                 groupedAttObj->GetOptAttMap();
            AttributeName* Name = DictAttributeList::_dictAttributeList[avpIndex-1];
            dictGrpOptAvp[Name->GetCode()]=Name;
            Name->SetIndex(dictGrpOptAvp.size() +
                            groupedAttObj->GetMandAttMap().size());
        }
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element start function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
DictElementStart(void *data, const char *el, const char **attr)
{
    if (strcmp(el, DIA_DICT_STRING) == 0 )
    {
       attr++;
    }
    else if (strcmp(el, DIA_DICT_AVP_STRING) == 0)
    {
        //check previous AVPs are closed with closedtag
        DIA_DICT_PARSER_ASSERT(inAvp == ITS_FALSE);
        inAvp=ITS_TRUE;
        HandleAvp(el, attr);
    }
    else if(strcmp(el, DIA_DICT_AVPRULE_STRING) == 0)
    {
        HandleAvpRule(el, attr);
    }
    else if (strcmp(el, DIA_DICT_CMD_STRING) == 0)
    {
        //check if command are closed with closedtag
        DIA_DICT_PARSER_ASSERT(inCommand == ITS_FALSE);
        inCommand = ITS_TRUE;
        HandleCommand(el, attr);
    }
    else if (strcmp(el, DIA_DICT_REQ_STRING) == 0)
    {
        //check if previous request tag is closed
        DIA_DICT_PARSER_ASSERT(isRequest == ITS_FALSE);
        isRequest = ITS_TRUE;
    }
    else if (strcmp(el, DIA_DICT_ANS_STRING) == 0)
    {
        //check if previous answer tag is closed
        DIA_DICT_PARSER_ASSERT(isAnswer == ITS_FALSE);
        isAnswer = ITS_TRUE;
    }
    else if (strcmp(el, DIA_DICT_REQUIRED_STRING) == 0)
    {
        //check if previous required tag is closed
        DIA_DICT_PARSER_ASSERT(isRequired == ITS_FALSE);
        isRequired = ITS_TRUE;
    }
    else if (strcmp(el, DIA_DICT_OPTIONAL_STRING) == 0)
    {
        //check if previous optional tag is closed
        DIA_DICT_PARSER_ASSERT(isOptional == ITS_FALSE);
        isOptional = ITS_TRUE;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element end function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
static void
DictElementEnd(void *data, const char *el)
{
    if (strcmp(el, DIA_DICT_STRING) == 0 )
    {
       DictAttributeList::_dictAttributeList.reArrange();
    }
    else if (strcmp(el, DIA_DICT_AVP_STRING) == 0)
    {
        inAvp=ITS_FALSE;
        if(isGrouped)
        {
            if (DictAttributeList::_dictAttributeList[avpIndex-1])
            {
               delete DictAttributeList::_dictAttributeList[avpIndex-1];
               DictAttributeList::_dictAttributeList[avpIndex-1] = NULL;
            }
            DictAttributeList::_dictAttributeList[avpIndex-1]=groupedAttObj;
            isGrouped=ITS_FALSE;
        }
    }
    else if (strcmp(el, DIA_DICT_CMD_STRING) == 0)
    {
        inCommand = ITS_FALSE;
    }
    else if (strcmp(el, DIA_DICT_REQ_STRING) == 0)
    {
        isRequest = ITS_FALSE;
    }
    else if (strcmp(el, DIA_DICT_ANS_STRING) == 0)
    {
        isAnswer = ITS_FALSE;
    }
    else if (strcmp(el, DIA_DICT_REQUIRED_STRING) == 0)
    {

        isRequired = ITS_FALSE;
    }
    else if (strcmp(el, DIA_DICT_OPTIONAL_STRING) == 0)
    {
        isOptional = ITS_FALSE;
    }
}

void
DiaDictParserInitialize(const char* fileName)
{
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;

    buf = NULL;
    size = 0;

    dictParser = XML_ParserCreate(NULL);
    DIA_DICT_PARSER_ASSERT(dictParser != NULL);

    /* set the token functions */
    XML_SetElementHandler(dictParser, 
                          (XML_StartElementHandler)DictElementStart, 
                          (XML_EndElementHandler)DictElementEnd);

    xml = fopen(fileName, "r");
    if (xml == NULL)
    {
       //No dictionary file present, hence return
       return;
    }

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    DIA_DICT_PARSER_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    DIA_DICT_PARSER_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = (char *)malloc(size);
    DIA_DICT_PARSER_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    DIA_DICT_PARSER_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NULL */
    buf[size - 1] = 0;

    inDictParser = ITS_TRUE;
    parseSuccessful = XML_Parse(dictParser, buf, size, ITS_TRUE);
    DIA_DICT_PARSER_ASSERT(parseSuccessful == 0);

    /* clean up */
    if (buf)
    {
        free(buf);
    }

}

