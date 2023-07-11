/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: AttributeName.h,v $
 * LOG: Revision 3.6.42.1.12.1  2014/08/26 10:27:38  pramana
 * LOG: Compilation warning fixes in imsdia
 * LOG:
 * LOG: Revision 3.6.42.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.6  2010/10/11 05:12:56  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.5  2010/08/19 11:23:56  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported
 * LOG:
 * LOG: Revision 3.4.2.1  2010/06/17 04:47:47  rajeshak
 * LOG: Fix for HelpDesk Ticket-2383
 * LOG:
 * LOG: Revision 3.4  2009/09/07 10:26:23  rajeshak
 * LOG: Support for Printing Missing Avp
 * LOG:
 * LOG: Revision 3.3  2009/01/30 06:21:01  nvijikumar
 * LOG: Included virtual destructor to fix warnings
 * LOG:
 * LOG: Revision 3.2  2008/10/28 12:04:17  nvijikumar
 * LOG: IssueID: none
 * LOG: FeatureID: none
 * LOG: Description: Porting Performance changes from 3.0 branch
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.21  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.8.2.5  2008/01/24 10:34:11  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 2.8.2.4  2007/04/27 13:20:00  hbhatnagar
 * LOG: changes made to fix the GetIndex api for addAVP and removeAVP
 * LOG: using vendorId.
 * LOG:
 * LOG: Revision 2.8.2.3  2007/04/19 13:47:10  hbhatnagar
 * LOG: Enhancement: To support APIs for add and remove AVPs.
 * LOG:
 * LOG: Revision 2.8.2.2  2007/03/26 12:42:12  nvijikumar
 * LOG: Fix for Bridgewater issue reported on 26th March 07.
 * LOG: AVP Decode failure with OctetString value is empty.
 * LOG:
 * LOG: Revision 2.8.2.1  2007/03/22 08:52:19  nvijikumar
 * LOG: ExtraAttributes creation based on avpCode and vendorId together
 * LOG:
 * LOG: Revision 2.8  2007/03/02 06:04:09  nvijikumar
 * LOG: Reverting back the JAVA changes which are committed before Branch tag.
 * LOG:
 * LOG: Revision 2.7  2007/02/26 08:08:28  sumag
 * LOG: t
 * LOG: :q
 * LOG:
 * LOG: Revision 2.6  2006/11/13 05:30:07  tpanda
 * LOG: dictionary extensible AVP encoding/decoding fix
 * LOG:
 * LOG: Revision 2.5  2006/11/03 05:01:27  tpanda
 * LOG: Minor modification to avoid compilation error in solaris64
 * LOG:
 * LOG: Revision 2.4  2006/10/25 13:21:41  tpanda
 * LOG: For extensible AVP support
 * LOG:
 * LOG: Revision 2.3  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:50:43  tpanda
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.2  2006/10/05 05:39:58  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.4  2006/06/21 10:26:35  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.3  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: AttributeName.h,v 3.6.42.1.12.1 2014/08/26 10:27:38 pramana Exp $
 ****************************************************************************/
#ident "$Id: AttributeName.h,v 3.6.42.1.12.1 2014/08/26 10:27:38 pramana Exp $"

#ifndef _DIAMETER_ATTRIBUTENAME_H_
#define _DIAMETER_ATTRIBUTENAME_H_

//#include <diameter/Exceptions.h>
#include <diameter/Implementation.h>
#include <map>
#include <set>
#include <stdarg.h>
#include <cstring>

namespace diameter {

class AVP;

/**
 * AvpBuilder converts AVP data between the API and the implementation.
 */
struct AvpBuilder {
    virtual AVP *build(const AVPImpl *) const = 0;
    virtual ~AvpBuilder(){};
    const AttributeName* _name;
};

/**
 * ImpBuilder is used by implementation to build an abstraction implementation object from the actual implementation.
 */
class ImpBuilder;

/**
 * Type-safe, value-restricted attribute names.
 *
 * namespace base {
 *
 * class BaseAttributeName: public AttributeName {
 * public:
 *    static const BaseAttributeName AccountingRealtimeRequired;
 *    static const BaseAttributeName AccountingRecordNumber;
 *    ....
 * };
 *
 * const BaseAttributeName BaseAttributeName::AccountingRealtimeRequired("Accounting-Realtime-Required");
 * const BaseAttributeName BaseAttributeName::AccountingRecordNumber("Accounting-Record-Number");
 * ....
 * }
 */

class AttributeName {
    AttributeName &operator=(const AttributeName &);
    friend std::ostream &operator<<(std::ostream &out, const AttributeName &);

public:
    AttributeName (const AttributeName& name, unsigned int avpCode):
    _name(name._name), _abuilder(name._abuilder), _ibuilder(name._ibuilder),
    _avpCode(avpCode) 
    {}

    //Fixing No Non Virtual Destructor
    virtual ~AttributeName(){}

    static const AttributeName AVP;

    /**
     * Obtains the string value of this attribute name.
     */
    operator const char *() const {
        return _name;
    }

    /**
     * Returns the AVP builder corresponding to this attribute.
     */
    const AvpBuilder &getAvpBuilder() const {
          AvpBuilder& abuilder = (AvpBuilder&)_abuilder;
          abuilder._name = this;
          return _abuilder;
    }

    /**
     * Returns the AVP value parser corresponding to this attribute.
     */
    const ImpBuilder &getImpBuilder() const {
          return _ibuilder;
    }

protected:
    /*#
     * Constructs an AttributeName from a name, an AVP builder, and an AVP value parser.
     */
    explicit AttributeName(const char *name, const AvpBuilder &abuilder, const ImpBuilder &ibuilder)
    : _name(name), _abuilder(abuilder), _ibuilder(ibuilder), 
      _avpIndex(0), _avpCode(0), _mandatory(false),
      _encrypt(false), _vendorId(0), _baseProt(false){}


    static const AvpBuilder &AnyAvpBuilder;

public:
    static const ImpBuilder &AnyImpBuilder;
    static const ImpBuilder &OctetStringImpBuilder;
    static const ImpBuilder &Integer32ImpBuilder;
    static const ImpBuilder &Integer64ImpBuilder;
    static const ImpBuilder &Unsigned32ImpBuilder;
    static const ImpBuilder &Unsigned64ImpBuilder;
    /**
     * Added the references to Float32 and Float64 ImplBuilders
     */
    static const ImpBuilder &Float32ImpBuilder;
    static const ImpBuilder &Float64ImpBuilder;

    static const ImpBuilder &AddressImpBuilder;
    static const ImpBuilder &TimeImpBuilder;
    static const ImpBuilder &UTF8StringImpBuilder;
    static const ImpBuilder &IdentityImpBuilder;
    static const ImpBuilder &URIImpBuilder;
    static const ImpBuilder &IPFilterRuleImpBuilder;
    static const ImpBuilder &EnumeratedImpBuilder;
    static const ImpBuilder &GroupedImpBuilder;

private:
    const char *_name;
    const AvpBuilder &_abuilder;
    const ImpBuilder &_ibuilder;
protected:
    unsigned int _avpIndex;//Tushar
    unsigned int _avpCode;//Tushar
    bool _mandatory;
    bool _encrypt;
    unsigned int _vendorId;
    bool _baseProt;
public:
    explicit AttributeName(const char *name, const AvpBuilder &abuilder, 
          const ImpBuilder &ibuilder, unsigned int avpCode,unsigned int vendorId=0,
          bool mandatory=true, bool encrypt=true, bool baseProt=false)
    : _name(name), _abuilder(abuilder), _ibuilder(ibuilder), 
      _avpIndex(0), _avpCode(avpCode), _mandatory(mandatory),
      _encrypt(encrypt), _vendorId(vendorId), _baseProt(baseProt)
    {}//Tushar
    unsigned int GetIndex() const
    {
       return _avpIndex;
    }//Tushar
    void SetIndex(unsigned int index)
    {
       _avpIndex = index-1;
    }//Tushar
    unsigned int GetCode() const
    {
       return _avpCode;
    }
    unsigned int vendorId()const
    {
       return _vendorId;
    }
    bool ifMandatory() const
    { 
       return _mandatory;
    }
    bool ifEncrypt() const
    { 
       return _encrypt;
    }
    bool ifBase() const
    { 
       return _baseProt;
    }
};

class GroupedAttributeName : public AttributeName
{
public:
    GroupedAttributeName(const char *n, const AvpBuilder &m, const ImpBuilder &p,
    unsigned int avpCode, unsigned int vendorId=0, 
    bool mandatory=true, bool encrypt=true, bool baseProt=false):
    AttributeName(n, m, p, avpCode, vendorId, mandatory, encrypt, baseProt){}

    GroupedAttributeName (const GroupedAttributeName& name, unsigned int avpCode):
    AttributeName(name, avpCode)
    {}
    
    std::map<unsigned int, AttributeName*>& GetMandAttMap()
    {
        return GroupedMandAttMap;
    }

    std::map<unsigned int, AttributeName*>& GetOptAttMap()
    {
        return GroupedOptAttMap;
    }
    const AttributeName* getAttributeName(unsigned int avpCode, 
                                         unsigned int& Index, bool& fMand) const
    {
        fMand = false;
        std::map<unsigned int, AttributeName*>::const_iterator
              it = GroupedMandAttMap.find(avpCode);
        if (it != GroupedMandAttMap.end())
        {
           Index = (*it).second->GetIndex();
           fMand = true;
           return (*it).second;
        }
        it = GroupedOptAttMap.find(avpCode);
        if (it != GroupedOptAttMap.end())
        {
           Index = (*it).second->GetIndex();
           fMand = false;
           return (*it).second;
        }
        return NULL;
    }

    const AttributeName* getAttributeName(const char* AVPName,
                                         unsigned int& Index, bool& fMand) const
    {
        if (AVPName == NULL)
        {
            return NULL;
        }

        fMand = false;
        std::map<unsigned int, AttributeName*>::const_iterator it;
        for (it = GroupedMandAttMap.begin(); it != GroupedMandAttMap.end(); it++)
        {
            if (strcmp(AVPName,*((*it).second))==0)
            {
                Index = (*it).second->GetIndex();
                fMand = true;
                return (*it).second;
            }
        }
        it = GroupedOptAttMap.begin();
        for (; it != GroupedOptAttMap.end(); it++)
        {
            if (strcmp(AVPName,*((*it).second))==0)
            {
                Index = (*it).second->GetIndex();
                fMand = false;
                return (*it).second;
            }
        }
        return NULL;
    }

    unsigned int GetAvpCode() { return _avpCode; }
    
private:
    std::map<unsigned int, AttributeName*> GroupedMandAttMap;
    std::map<unsigned int, AttributeName*> GroupedOptAttMap;
};//Tushar

class AttributeCodeMap
{
public:
    AttributeCodeMap(AttributeName* nameInst)
    {
       unsigned int oldIndex = AttributeMap.size();
       AttributeMap[nameInst->GetCode()]=nameInst;
       if(AttributeMap.size() != oldIndex)
          nameInst->SetIndex(AttributeMap.size());
    }
    static unsigned int GetNoOfAVPs(){return AttributeMap.size();}
    static std::map<unsigned int, AttributeName*> AttributeMap;//Tushar, only BaseAVPs
};

struct AttributeIndexPair
{
    const AttributeName* _name;
    unsigned int _Index;
};

class CommandAttribute
{

public:
      CommandAttribute(unsigned int appId, unsigned int cmdCode,
             const AttributeName* name,...): _AppId(appId), _CmdCode(cmdCode),
             _mandBaseBitMap(0)
      {
          va_list mark;
          va_start(mark, name);
          unsigned int Index = 0;
          bool fMand;
          bool fBase;
          unsigned int avpCode;
          while(name)
          {
             fMand = va_arg(mark, int);
             fBase = va_arg(mark, int);
             avpCode = va_arg(mark, int);
             if(fMand)
             {
                //if base mandatory avps
                if(fBase)
                {
                   _baseAVPs.insert(name);
                }
                else
                {
                   AttributeIndexPair attrIndxPair;
                   attrIndxPair._name = name;
                   attrIndxPair._Index = Index;
                   _mandAppAVPs.insert(std::pair<unsigned int, AttributeIndexPair>(avpCode, attrIndxPair));
                   Index ++;
                }
             }
             else 
             {
                 if(fBase == false)
                 {
                   AttributeIndexPair attrIndxPair;
                   attrIndxPair._name = name;
                   attrIndxPair._Index = Index;
                   _optAppAVPs.insert(std::pair<unsigned long long, AttributeIndexPair>(avpCode, attrIndxPair));
                   Index ++;
                 }
             }
             name = va_arg(mark, const AttributeName*);
          }
          _totalNoOfAVPs = 0;
          unsigned long long key=cmdCode;
          key = (key << 32) | appId;
          std::map<unsigned long long, CommandAttributePair>::iterator
               it = _CommandAttributeMap.find(key);
          if (it != _CommandAttributeMap.end())
          {
             (*it).second.ans = this;
          }
          else
          {
             _CommandAttributeMap[key]=CommandAttributePair(this);
          }
          va_end(mark);
      }

      unsigned int GetIndex(const AttributeName* name, bool &fMand) const
      {
          fMand=false;
          std::map<unsigned long long, AttributeIndexPair>::const_iterator lit;
          std::map<unsigned int, AttributeIndexPair>::const_iterator iit;
          if(name->ifBase())
          {
             return name->GetIndex();
          }
          iit = _mandAppAVPs.find(name->GetCode());
          if(iit !=  _mandAppAVPs.end())
          {
             fMand=true;
             return (*iit).second._Index + AttributeCodeMap::GetNoOfAVPs();
          }
          /**
           * Fix for addAVP and removeAVP.   
           * The order of finding is reversed. First finding the item with 
           * vendorId and commandcode. If it fails then finding with command 
           * code alone. Finally, throwing exception if nothing is found.
           */
          unsigned long long key = name->vendorId();
          key = ((key << 32) | name->GetCode());
          lit = _optAppAVPs.find(key);

          if (lit == _optAppAVPs.end())
          {
              lit = _optAppAVPs.find(name->GetCode());
          }
          if (lit == _optAppAVPs.end())
          {
              throw CodecException(__FILE__, __LINE__,"Wrong App.AVP is set");
          }

          return (*lit).second._Index + AttributeCodeMap::GetNoOfAVPs();
     }
     
     const AttributeName* GetAppAttributeObj(unsigned int avpCode, unsigned int venId,
           unsigned int& Index, bool& fMand) const
     {
          fMand = false;
          std::map<unsigned int, AttributeIndexPair>::const_iterator 
               it = _mandAppAVPs.find(avpCode);
          std::map<unsigned long long, AttributeIndexPair>::const_iterator 
               lit;
          if (it != _mandAppAVPs.end())
          {
               Index = (*it).second._Index + AttributeCodeMap::GetNoOfAVPs();
               fMand = true;
               return (*it).second._name;
          }
          lit = _optAppAVPs.find(avpCode);
          if (lit != _optAppAVPs.end())
          {
              if ((*lit).second._name->vendorId() != venId)
              {
                 unsigned long long key = venId;
                 key = ((key << 32) | avpCode);
                 lit = _optAppAVPs.find(key);
              }
          }
          else if(venId)
          {
              unsigned long long key = venId;
              key = ((key << 32) | avpCode);
              lit = _optAppAVPs.find(key);
          }
          if (lit != _optAppAVPs.end())
          {
             Index = (*lit).second._Index + AttributeCodeMap::GetNoOfAVPs();
             return (*lit).second._name;
          }
          std::map<unsigned int, AttributeName*>::const_iterator bit=
               AttributeCodeMap::AttributeMap.find(avpCode);
          if (bit != AttributeCodeMap::AttributeMap.end())
          {
             Index = (*bit).second->GetIndex();
             return (*bit).second;
          }
          return NULL;
     }

     const AttributeName* GetAppAttributeObj(const char* AVPName, 
              unsigned int venId, unsigned int& Index, bool& fMand) const
     {
          if (AVPName == NULL)
          {
              return NULL;
          }

          fMand = false;
          std::map<unsigned int, AttributeIndexPair>::const_iterator it;
          for (it = _mandAppAVPs.begin();it != _mandAppAVPs.end(); it++)
          {
              if (strcmp(AVPName,(const char *)*((*it).second._name))==0)
              {
                  Index = (*it).second._Index + AttributeCodeMap::GetNoOfAVPs();
                  fMand = true;
                  return (*it).second._name;
              }
          }

          std::map<unsigned long long, AttributeIndexPair>::const_iterator itll;
          for (itll = _optAppAVPs.begin();itll != _optAppAVPs.end(); itll++ )
          {
              if (strcmp(AVPName,(const char* )*((*itll).second._name))==0 && 
                                 ((*itll).second._name->vendorId() == venId))
              {
                  Index = (*itll).second._Index + AttributeCodeMap::GetNoOfAVPs();
                  return (*itll).second._name;
              }
          }

          std::map<unsigned int, AttributeName*>::const_iterator bit;
          for (bit = AttributeCodeMap::AttributeMap.begin(); bit !=
               AttributeCodeMap::AttributeMap.end(); bit++)
          {
             if (strcmp(AVPName,(const char* )*((*bit).second))==0)
             {
                 Index = (*bit).second->GetIndex();
                 return (*bit).second;
             }
          }
          return NULL;
     }

     std::set<const AttributeName*>& GetMandBaseAvpList() 
     {
         return _baseAVPs;
     }

     std::map<unsigned int, AttributeIndexPair>& GetMandAppAvpList()
     {
         return _mandAppAVPs;
     }

     const unsigned long long& GetMandBaseBitMap() const 
     {
          if(_mandBaseBitMap)
          {
             return _mandBaseBitMap;
          }
          unsigned long long& mandBaseBitMap = (unsigned long long&)_mandBaseBitMap;
          std::set<const AttributeName*>::const_iterator it = _baseAVPs.begin();
          for(; it != _baseAVPs.end(); ++it)
          {
             const AttributeName* name = (*it);
             mandBaseBitMap |= 0x8000000000000000ull >> name->GetIndex();
          }
          return mandBaseBitMap;
     }
     unsigned int GetNoOfAppMandAVPs() const
     {
        return _mandAppAVPs.size();
     }

     unsigned int GetNoOfBaseMandAVPs() const
     {
        //specific to the command
        return _baseAVPs.size();
     }

     unsigned int GetTotalNoOfAVPs() const
     {
        //including All base and application specific
        if (_totalNoOfAVPs == 0)
        {
           _totalNoOfAVPs = AttributeCodeMap::GetNoOfAVPs() + 
                            _mandAppAVPs.size() + _optAppAVPs.size();
        }
        return _totalNoOfAVPs;
     }

     static const AttributeName* findAttribute(unsigned int appId, unsigned int cmdCode,
                           unsigned int avpCode, unsigned int venId)
     {
        unsigned long long key=cmdCode;
        key = (key << 32) | appId;
        std::map<unsigned long long, CommandAttributePair>::iterator
             it = _CommandAttributeMap.find(key);
        if (it != _CommandAttributeMap.end())
        {
           return (*it).second.findAttribute(avpCode, venId);
        }
        return NULL;
     }
     
    static const CommandAttribute* getCmdAttribute(unsigned int appId, unsigned int cmdCode, bool isReq)
    {
        unsigned long long key=cmdCode;
        key = (key << 32) | appId;
        std::map<unsigned long long, CommandAttributePair>::iterator
                                it = _CommandAttributeMap.find(key);
        if (it != _CommandAttributeMap.end())
        {
            if (isReq)
            {
                return (*it).second.req;
            }
            else
            {
                return (*it).second.ans;
            }
        }
        return NULL;
    }

     static bool addAttribute(unsigned int appId, unsigned int cmdCode, 
            AttributeName& name, bool fReq=true)
     {
        unsigned long long key=cmdCode;
        key = (key << 32) | appId;
        std::map<unsigned long long, CommandAttributePair>::iterator
             it = _CommandAttributeMap.find(key);
        if (it != _CommandAttributeMap.end())
        {
            CommandAttribute* cmdAttr;
            cmdAttr = fReq ? (*it).second.req : (*it).second.ans;
            if (cmdAttr->_mandAppAVPs.find(name.GetCode()) !=
                cmdAttr->_mandAppAVPs.end())
            {
                std::cout<<std::endl<<"********Attribute exists,add failed********"<<std::endl;
                return false;
            }
            std::map<unsigned long long, AttributeIndexPair>::iterator
                 it = cmdAttr->_optAppAVPs.find(name.GetCode());
            if ( it !=
                cmdAttr->_optAppAVPs.end())
            {
                if (name.vendorId() == (*it).second._name->vendorId())
                {
                   std::cout<<std::endl<<"********Attribute exists,add failed********"<<std::endl;
                   return false;
                }
            }
            if (cmdAttr->_totalNoOfAVPs == 0)
            {
               cmdAttr->_totalNoOfAVPs = AttributeCodeMap::GetNoOfAVPs() + 
                            cmdAttr->_mandAppAVPs.size() + 
                            cmdAttr->_optAppAVPs.size();
            }
            AttributeIndexPair attrIndxPair;
            attrIndxPair._name  = &name;
            attrIndxPair._Index = cmdAttr->_mandAppAVPs.size() + 
                                  cmdAttr->_optAppAVPs.size();
            unsigned long long key = name.vendorId();
            key = ((key << 32) | name.GetCode());
            cmdAttr->_optAppAVPs[key]=attrIndxPair;
            return true;
        }
        std::cout<<std::endl<<"********No command instance for the application********"<<std::endl;
        return false;
     }
        
struct CommandAttributePair
{
   CommandAttribute* req;
   CommandAttribute* ans;
   CommandAttributePair(CommandAttribute* cmdAtt):req(cmdAtt),ans(NULL){}
   CommandAttributePair():req(NULL),ans(NULL){}
   const AttributeName* findAttribute(unsigned int avpCode, unsigned int venId)
   {
       unsigned int temp;
       bool fMand;
       const AttributeName* name = req->GetAppAttributeObj(avpCode, venId, temp,fMand); 
       if(name == NULL && ans)
       {
           name = ans->GetAppAttributeObj(avpCode, venId, temp,fMand);
       }
       return name;
   }
};
private:
      mutable unsigned int _totalNoOfAVPs;
      unsigned int _AppId;
      unsigned int _CmdCode;
      unsigned long long _mandBaseBitMap;
      std::map<unsigned int, AttributeIndexPair> _mandAppAVPs;
      std::map<unsigned long long, AttributeIndexPair> _optAppAVPs;
      std::set<const AttributeName*> _baseAVPs;
      static std::map<unsigned long long, CommandAttributePair> _CommandAttributeMap;
};


/**
 * Comparison operator on AttributeName objects
 */
inline int operator<(const AttributeName &a, const AttributeName &b) {
    return std::strcmp(a, b);
}

/**
 * Stream inserter for AttributeName
 */
inline std::ostream &operator<<(std::ostream &out, const AttributeName &name) {
    return out << name._name;
}

/**
 * AttributeInstance
 */
class AttributeInstance {
public:
    const AttributeName &name;
    int index;

    AttributeInstance(const AttributeName &n, int i)
    : name(n), index(i) {}
};

/**
 * Comparison operator on AttributeInstance objects
 */
inline int operator<(const AttributeInstance &a, const AttributeInstance &b) {
    int c = std::strcmp(a.name, b.name);
    if (c == 0) {
        c = a.index < b.index ? -1 : (a.index > b.index ? 1 : 0);
    }
    return c;
}

}

#endif//_DIAMETER_ATTRIBUTENAME_H_
