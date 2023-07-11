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
 * LOG: $Log: itsdiameter.h,v $
 * LOG: Revision 3.22.2.1.2.5.6.1.4.1.4.1.2.2.4.1  2017/01/16 04:28:45  jkchaitanya
 * LOG: changes for ticket 1106,1111 increase in size for memory allocation for routerecord avp
 * LOG:
 * LOG: Revision 3.22.2.1.2.5.6.1.4.1.4.1.2.2  2014/08/26 10:27:38  pramana
 * LOG: Compilation warning fixes in imsdia
 * LOG:
 * LOG: Revision 3.22.2.1.2.5.6.1.4.1.4.1.2.1  2014/07/02 06:37:11  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.22.2.1.2.5.6.1.4.1.4.1  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.22.2.1.2.5.6.1.4.1  2013/07/31 07:32:15  vsarath
 * LOG: Fix for coverity warnings
 * LOG:
 * LOG: Revision 3.22.2.1.2.5.6.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.22.2.1.2.5  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.22.2.1.2.2.12.1  2012/11/20 10:28:35  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.22.2.1.2.3  2012/11/06 16:31:20  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.22.2.1.2.2.18.1  2012/11/05 13:01:20  mallikarjun
 * LOG: Bug 345 changes
 * LOG:
 * LOG: Revision 3.22.2.1.2.2  2012/10/03 15:08:43  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.22.2.1.2.1.2.2  2012/09/20 07:46:30  cprem
 * LOG: Added new utility function getAvpCount.
 * LOG:
 * LOG: Revision 3.22.2.1.2.1.2.1  2012/09/14 15:46:03  cprem
 * LOG: Generic AVP access API with support for multiple occurance AVP's.
 * LOG:
 * LOG: Revision 3.22.2.1.2.1  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.22.2.1.4.1  2012/08/21 05:35:29  jvikas
 * LOG: Added Blank COnstructors for BaseCommand and DiaMsgFlow to take only dictId
 * LOG:
 * LOG: Revision 3.22.2.1  2012/02/15 09:38:13  brajappa
 * LOG: Resolved linked error in gcc O2 option - template functions should be in header files
 * LOG:
 * LOG: Revision 3.22  2011/08/23 06:49:48  vkumara
 * LOG: New API DataToUApp included.
 * LOG:
 * LOG: Revision 3.21  2010/11/19 16:45:04  nvijikumar
 * LOG: Introduced containsExtra API with input index
 * LOG:
 * LOG: Revision 3.20  2010/10/11 05:08:57  nvijikumar
 * LOG: Motorola's changes incorporation for field compilation issue
 * LOG:
 * LOG: Revision 3.19  2010/09/22 05:30:02  nvijikumar
 * LOG: GlobalUniqueAddr based routing/distribution support
 * LOG:
 * LOG: Revision 3.18  2010/08/19 11:21:26  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.17.2.1  2010/06/17 04:58:05  rajeshak
 * LOG: Fix for HelpDesk Ticket-2383
 * LOG:
 * LOG: Revision 3.17  2009/12/08 06:42:03  sureshj
 * LOG: Missing AVP only provides print of offending AVP, but no
 * LOG: callback to application. Motorola ticket 2278.
 * LOG:
 * LOG: Revision 3.16  2009/09/07 10:28:16  rajeshak
 * LOG: Support for Printing Missing Avp
 * LOG:
 * LOG: Revision 3.15  2009/07/24 09:22:18  rajeshak
 * LOG: Changes done for IDC-IDS Heartbeat with Custom AVP in DWR.
 * LOG:
 * LOG: Revision 3.14  2009/07/14 04:17:10  nvijikumar
 * LOG: Modified UTF8Checker Class
 * LOG:
 * LOG: Revision 3.13  2009/03/19 16:23:08  ssaxena
 * LOG: Modification done to add Redirect Agent Application.
 * LOG:
 * LOG: Revision 3.12  2009/03/19 10:25:03  rajeshak
 * LOG: IssueID:1756
 * LOG: FeatureID:None
 * LOG: Description: (IDS dumping core while trying to remove entry from pending queue)
 * LOG: Pointer initialized.
 * LOG:
 * LOG: Revision 3.11  2009/03/03 11:18:43  rajeshak
 * LOG: Klockwork reported issue fix
 * LOG:
 * LOG: Revision 3.10  2009/02/19 09:34:56  nvijikumar
 * LOG: 1. Provided API to Set ptr for deletion of encoded buffer
 * LOG:
 * LOG: Revision 3.9  2009/02/03 10:15:56  ssaxena
 * LOG: Modifications done for Redirect Agent functionality.
 * LOG:
 * LOG: Revision 3.8  2009/01/06 10:35:10  nvijikumar
 * LOG: Introduced separate funcs to decode Grouped AVPs in BaseCommand
 * LOG:
 * LOG: Revision 3.7  2008/12/26 10:22:15  rajeshak
 * LOG: IssueID:1401
 * LOG: FeatureID:none
 * LOG: Description:
 * LOG: (FAILOVER:Client IDS is dumping core on getting the answer message for ACR)
 * LOG: Added explicit copy constructor for BaseCommand.
 * LOG:
 * LOG: Revision 3.6  2008/12/22 12:21:37  rajeshak
 * LOG: IssueID:1360
 * LOG: FeatureID:none
 * LOG: Description: Fix for Memory Leak.
 * LOG: (in error scenario encoded buffer was not getting deleted)
 * LOG:
 * LOG: Revision 3.5  2008/12/22 11:00:22  rajeshak
 * LOG: IssueID:none
 * LOG: FeatureID:none
 * LOG: Description: returning string reference.
 * LOG:
 * LOG: Revision 3.4  2008/12/12 17:49:49  rajeshak
 * LOG: Lightweight Decode for base AVPS
 * LOG: New Command class is introduced (BaseCommand)
 * LOG:
 * LOG: Revision 3.3  2008/12/11 14:32:10  rajeshak
 * LOG: Replaced stl string with own String class (Hemant,Rajesh)
 * LOG:
 * LOG: Revision 3.2  2008/03/31 13:17:13  hbhatnagar
 * LOG: Made changes for ticket 1850 raised by Bridgewater
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:31  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.19  2008/03/27 12:14:08  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.13.4.4  2008/01/24 10:36:35  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 1.13.4.3  2007/04/19 14:02:38  hbhatnagar
 * LOG: Enhancement: Provided API to add and remove AVPs.
 * LOG:
 * LOG: Revision 1.13.4.2  2007/03/23 12:36:41  nvijikumar
 * LOG: Fix for application hang if duplicate entries made in dictionary file
 * LOG:
 * LOG: Revision 1.13.4.1  2007/03/22 08:45:19  tpanda
 * LOG: ExtraAttributes creation based on avpCode and vendorId together
 * LOG:
 * LOG: Revision 1.13  2007/01/04 11:03:45  nvijikumar
 * LOG: Provided Acconting SM related API for ACR.
 * LOG:
 * LOG: Revision 1.12  2006/11/25 04:00:12  tpanda
 * LOG: Changes for Msg based redundancy
 * LOG:
 * LOG: Revision 1.11  2006/11/23 06:31:34  tpanda
 * LOG: getAvpValue api provided for dcca to work properly with no header file dependancy
 * LOG:
 * LOG: Revision 1.10  2006/11/13 14:47:04  tpanda
 * LOG: clientId,sessionIndex moved to implementation object
 * LOG:
 * LOG: Revision 1.9  2006/11/13 05:36:18  tpanda
 * LOG: dictionary extensible AVP encoding/decoding fix
 * LOG:
 * LOG: Revision 1.8  2006/10/30 05:28:54  tpanda
 * LOG: IPFilter rule implementation done
 * LOG:
 * LOG: Revision 1.7  2006/10/28 11:10:28  tpanda
 * LOG: Encoding for IPFilter rule
 * LOG:
 * LOG: Revision 1.6  2006/10/25 13:25:31  tpanda
 * LOG: For extensible AVP support
 * LOG:
 * LOG: Revision 1.5  2006/10/24 09:00:43  tpanda
 * LOG: Dictionary file related changes
 * LOG:
 * LOG: Revision 1.4  2006/10/17 17:04:08  tpanda
 * LOG: Fix to enable GenericCmd to work with IDS
 * LOG:
 * LOG: Revision 1.3  2006/10/05 06:14:41  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * ID: $Id: itsdiameter.h,v 3.22.2.1.2.5.6.1.4.1.4.1.2.2.4.1 2017/01/16 04:28:45 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: itsdiameter.h,v 3.22.2.1.2.5.6.1.4.1.4.1.2.2.4.1 2017/01/16 04:28:45 jkchaitanya Exp $"

#ifndef _ITSDIAMETER_H_
#define _ITSDIAMETER_H_
#include <iostream>

#include <its++.h>

#include <dia_cmn.h>
#include <diameter/Trace.h>
#include <diameter/Implementation.h>
#include <diameter/AVP.h>
#include <diameter/Command.h>
#include <diameter/base/BaseAVP.h>
#include <diameter/base/BaseGenericCommand.h>

#define ALLOC_SIZE   32
#define MAX_LEN      64
#define MAX_IP_STR_LEN   15
#define UTF8_BIT_CHECK 0x76
#define UTF8_MAX_CTRL_BITS 0x05

namespace diameter {
template<typename T>
class DataToAppToData
{
public:

    T DataToApp(unsigned char *d, int c = sizeof(T))
    {
        T  x = 0;
        int i;

        for (i = 0; i < c; i++)
        {
            x <<= 8;
            /*
             * for the first octet, make sure we sign-extend into
             * the upper bits.  Subsequent octets can just be OR'd
             * into the lower bytes after the shift.
             */
            if (i == 0)
            {
                x |= (signed char)d[i];
            }
            else
            {
                x |= d[i];
            }
        }
        return x;
    }

    T DataToUApp(unsigned char *d, int c = sizeof(T))
    {
        T  x = 0;
        int i;

        for (i = 0; i < c; i++)
        {
            x <<= 8;
            /*
             * for the first octet, make sure we sign-extend into
             * the upper bits.  Subsequent octets can just be OR'd
             * into the lower bytes after the shift.
             */
            if (i == 0)
            {
                x |= (unsigned char)d[i];
            }
            else
            {
                x |= d[i];
            }
        }
        return x;
    }


    void AppToData(char *d, T val, int c = sizeof(T))
    {
        for(int i=0; i< c; ++i)
        {
            d[i] = (val >> ((c-i-1)<<3)) & 0xFFU;
        }
    }

};

class ParserBase
{
public:
      virtual ~ParserBase(){}
      virtual int  Decode(const unsigned char* buff, int size, void* val)=0;
      virtual int Encode(String& str, void* val)=0;
};

class UTF8Validate
{
    public:
    UTF8Validate() {}

    /* Validate function verifies the input data and returns 0 if success
     * and -1 if validation fails.
     */
    int Validate(const char *data, unsigned len)
    {
        unsigned int indx = 0;

        if (data == NULL)
        {
            return -1;
        }
        while (indx  < len)
        {
            unsigned char c = data[indx++];

            /* If first bit is 0 continue */
            if ((c >> 7) == 0x00) 
            { 
                continue; 
            }  

            /* if UTF8_BIT_CHECK matches with first 7 bits then error */
            if ((c >> 1) == UTF8_BIT_CHECK) 
            { 
                return -1; 
            } 

            c <<= 1;
            /* Is it really counting number of '1'? 
             * Need to relook*/
            int bitCount = 0;
            for (bitCount=0; bitCount<UTF8_MAX_CTRL_BITS; bitCount++) 
            { 
                if ((c && 0x40) == 0) 
                {
                    break; 
                }
            }

            /* Error if the number of 1 count is zero */
            if (bitCount==0) 
            { 
                return -1; 
            }

            /* Remaining octet's first 2 bits should be '10'(0x02) */
            int j=0;
            while( j < bitCount)
            {
                if (indx >= len) 
                { 
                    return -1; 
                }
                if ((data[indx++] >> 6) != 0x02) 
                { 
                    return -1; 
                }
                j++;
            }
        }
        return 0;
    }
};

template<typename T>
class Parser : public ParserBase
{
public:
   virtual int  Decode(const unsigned char* buff, int size, void* val)
   {
      return 0;
   }
   virtual int Encode(String& str, void* val)
   {
      return 0;
   }
private:
};

class OctetStringParser : public Parser<std::string>
{
public:
      int Decode(const unsigned char* buff, int size, void* val);
      int Encode(String& str, void* val);
};

class Integer32Parser : public Parser<unsigned int>, public DataToAppToData<unsigned int>
{
public:
    int Decode(const unsigned char* buff, int size, void* val);
    int Encode(String& str, void* val);
};

class Integer64Parser : public Parser<unsigned long long>, public DataToAppToData<unsigned long long>
{
public:
    int Decode(const unsigned char* buff, int size, void* val);
    int Encode(String& str, void* val);
};

/**
 * Added Float32Parser class for Float32 type support
 */
class Float32Parser : public Parser<float>, public DataToAppToData<float>
{
    public:
        int Decode(const unsigned char* buff, int size, void* val);
        int Encode(String& str, void* val);
};

/**
 * Added Float64Parser class for Float64 type support
 */
class Float64Parser : public Parser<double>, public DataToAppToData<double>
{
    public:
        int Decode(const unsigned char* buff, int size, void* val);
        int Encode(String& str, void* val);
};

class URIParser : public Parser<URI>
{
public:
    int Decode(const unsigned char* inputBuff, int size, void* val);
    int Encode(String& str, void* val);
};

class UTF8StringParser : public Parser<UTF8String>
{
public:
    int Decode(const unsigned char* inputBuff, int size, void* val);
    int Encode(String& str, void* val);
};

class AddressParser : public Parser<Address>, public DataToAppToData<unsigned short>
{
public:
    int Decode(const unsigned char* inputBuff, int size, void* val);
    int Encode(String& str, void* val);
};

class IPFilterRuleParser : public Parser<IPFilterRule>
{
public:
    int Decode(const unsigned char* buff, int size, void* val);
    int Encode(String& str, void* val);
};

class AVPContainerDerivedEntry
{
public:
    AVPContainerDerivedEntry();
    AVPContainerDerivedEntry(AVP* avp);
    ~AVPContainerDerivedEntry();
    void releaseEntries();
    std::ostream &print(std::ostream &out) const;
    void add(AVP* avp);

    /*.implementation:public,AVPContainerDerivedEntry
     ****************************************************************************
     *  Purpose: This function removes particular AVP from entry for the
     *           multiple instance AVP as well as deallocate the memory associated
     *           with it. If the avpCount is zero it will free the avpList too.
     *           After removing the AVP it also shifts the position of remaining AVPs
     *           to one less than existing.
     *
     *  Input Parameters:
     *           const pointer to AVP object.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value: returns 0 on success and -1 on failure.
     *
     *  Notes:
     *
     *  See Also:
     ****************************************************************************/
    int  removeSpecificAvp(const AVP* avp);

    unsigned int AvpCount(){return _avpCount;}
    const AVP* getAt(unsigned int index);
    int Encode(String& str);
private:
    AVP** avpList;
    unsigned int _avpCount;
};

class AVPBuff
{
   public:
   AVPBuff(unsigned char* buff, unsigned int Size, unsigned int offset,
             unsigned int avpCode, unsigned int vendorId, DiaHeader& hdr):_hdr(hdr)
   {
        _buffer = new unsigned char[Size];
        memcpy(_buffer, buff, Size);
       _size = Size;
       _avpcode = avpCode;
       _vendorId = vendorId;
       _offset   = offset;
   }
   ~AVPBuff()
   {
      delete []_buffer;
   }
   unsigned char *_buffer;
   unsigned int   _size;
   unsigned int   _avpcode;
   unsigned int   _vendorId;
   unsigned int   _offset;
   DiaHeader& _hdr;
};

class AVPContainerDerived : public AVPContainer
{
public:
   AVPContainerDerived();
   ~AVPContainerDerived();
   void releaseEntries();
   std::ostream &print(std::ostream &out) const;
   std::vector<int> missingAVPCodes;
   std::string origin_host, origin_realm; 
   void SetNameObj(const AttributeName* nameObj);
   AVPContainerDerived& SetCmdObj(const CommandAttribute* cmdnameObj);
   const AttributeName& GetNameObj()
   {
      return *_nameObj;
   }
   const CommandAttribute* GetCmdObj()
   {
      return _cmdnameObj;
   }
   /**
    * Changed the return type from void to const AVP&
    */
   const AVP& add(const AttributeName &name, const AVP &value, bool single);
   void add(const AttributeName &name, AVP *value);
   /**
    * This method removes all the instances if exists in the entry.
    * It is recommended to use this API for single instance AVPs.
    */
   int remove(const AttributeName &name);
   /**
    * This method removes specific instance in an entry.
    * It is recommended to use this API for multiple instances AVPs.
    */
   int remove(const AttributeName &name, const AVP& avp);

   int count(const AttributeName &name) const;
   bool contains(const AttributeName &name) const;
   int countExtra(const AttributeName &name) const;
   bool containsExtra(const AttributeName &name) const;
   /**
    * Added an Overloaded API to check whether AVP exists
    * at particular container or not. Added due to ticket
    * 2080 by Bridgewater.
    */
   bool containsExtra(unsigned int index) const;

   const AVP &get(const AttributeName &name, unsigned index) const;
   const AVP* getPtr(const AttributeName &name, unsigned index) const;
   const AVP &getExtra(const AttributeName &name, unsigned index) const;
   std::ostream &printExtras(std::ostream & out) const;
   void SetNoOfContEntry(unsigned int totalNo);
   AVPContainerDerivedEntry* &getAt(unsigned int index) const;
   AVPContainerDerivedEntry* &operator [](unsigned int index);
   inline void SetBaseMandBitMap(unsigned int index)
   {
      _baseMandBitMap |= 0x8000000000000000ull >> index;
   }

   inline void SetAppMandCounter(unsigned int mandAvpcnt=1)
   {
      //increment for each app.specific mand avp encountered
      _noOfMandAvp +=mandAvpcnt;
   }

   inline void setInstCnt()
   {
     _instCntr++;
   }
   
   inline unsigned int& getInstCnt(){return _instCntr;}

   inline void SetAppAVPBuff(unsigned char* buff, unsigned int Size,unsigned int offSet,
             unsigned int avpCode, unsigned int vendorId, DiaHeader& hdr);
   void DecodeAppAVP();
   int EncodeAppAVP(String& str);
   void operator = (AVPContainerDerived& entry)
   {copy(entry);}
   void copy(AVPContainerDerived& entry);
   unsigned int GetNoOfContEntry(){ return _totalContEntries;}
   unsigned int GetNoOfDictEntry(){return _dictEntries;}
   bool validateMand() const;
   void PrintMissingMandAvp();
   void PrintMissingMandAvp(AttributeName* name, unsigned int errType);

   /**
    * Changed the venId as default argument.
    * Adding the const to the signature 
    * (for ticket 1850)
    */
   int getAvpValue(unsigned int avpCode, void* val, 
                   ValueDiscriminator D, unsigned int venId=0) const;

   //New API to access multiple Occurance AVP's
   int getAvpValue(unsigned int avpCode, unsigned int index ,void* val, 
                   ValueDiscriminator D, unsigned int venId=0) const;

   //API to get count for multiple occurance AVP's
   int getAvpCount(unsigned int avpCode, unsigned int venId=0);

   /**
    * Added two overloaded funtions for adding the AVP
    * and two for removing the AVP
    */
    /*.implementation:public,AVPContainerDerived
     ****************************************************************************
     *  Purpose: This function adds the particular AVP in the container on the
     *           basis of AVP Code.
     *
     *  Input Parameters:
     *          AVP Code - The AVP code(or Attribute code)  of AVP being added.
     *          VendorId - unsigned int value  
     *          value    - The Actual Value(it can be basic as well as Grouped)
     *          single/multiple AVP - Boolean flag to determine whether single i
     *                     or Multiple AVP.( true = single, false = Multiple)
     *          type and size of value - The ValueDiscriminator
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value: const reference to AVP Object
     *
     *  Notes:
     *
     *  See Also:
     ***************************************************************************/

    const AVP&  addAVP(const char* name, unsigned int vendorId, void* val, 
                       bool single, ValueDiscriminator D);

    /*.implementation:public,itsdiameter
     ****************************************************************************
     *  Purpose: This function adds the particular AVP in the container on the
     *           basis of AVP name as defined in specs.
     *  Input Parameters:
     *           AVP Name - The AVP Name in const char* as defined in ABNF. 
     *           VendorId - unsigned int value
     *           value    - The Actual Value(it can be basic as well as Grouped)
     *           single/multiple AVP - Boolean flag to determine whether single 
     *                      or Multiple AVP. ( true = single, false = Multiple)
     *           type and size of value - The ValueDiscriminator 
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value: const reference to AVP Object
     *
     *  Notes:
     *
     *  See Also:
     ****************************************************************************/
    const AVP&  addAVP(int attrCode, unsigned int vendorId, void* val,
                       bool single, ValueDiscriminator D);

    /*.implementation:static
     ****************************************************************************
     *  Purpose: This function removes the all the instances of the AVP from
     *           container on the basis of AVP Code and vendorId
     *
     *  Input Parameters:
     *           AVP code - The AVP code(or Attribute code)  of AVP being added. 
     *           VendorId - unsigned int value.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value: returns 0 on success and -1 on failure.
     *
     *  Notes:
     *
     *  See Also:
     ****************************************************************************/
    int removeAVP(const char* name, unsigned int vendorId);

    /*.implementation:static
     ****************************************************************************
     *  Purpose: This function removes the all the instances of the AVP from
     *           container on the basis of AVP Code and vendorId.
     *
     *  Input Parameters:
     *           AVP Name - The AVP Name in const char* as defined in ABNF.
     *           VendorId - unsigned int value.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value: returns 0 on success and -1 on failure.
     *
     *  Notes:
     *
     *  See Also:
     ****************************************************************************/
    int removeAVP(int attrCode, unsigned int vendorId);

private:
      AVPContainerDerivedEntry** avpContDerivedEntryList;
      AVPBuff** appAVPBuffList;
      const AttributeName* _nameObj;
      const CommandAttribute* _cmdnameObj;
      unsigned int _noOfMandAvp;
      unsigned long long _baseMandBitMap;
      unsigned int _totalContEntries;
      unsigned int _totalappBuff;
      unsigned int _dictEntries;
      unsigned int _instCntr;
};

template <typename T, ValueDiscriminator D>
class DerivedAVPImplDerived : public DerivedAVPImpl<T,D>, public DataToAppToData<unsigned int>
{
public:
    DerivedAVPImplDerived():_val() {}
    DerivedAVPImplDerived(const T &value): _val(value) {}
    ~DerivedAVPImplDerived(){}
    virtual const T &get() const
    {
        return _val;
    }

    virtual void set(const T & val) {_val=val;}
    ParserBase* getParseType();
    virtual int Decode(unsigned char*& inputBuff, unsigned int size);
    virtual int Encode(String& str, const AttributeName& _name);
private:
    T _val;
};

class GroupedAVPImplDerived : public GroupedAVPImpl, public DataToAppToData<unsigned int>
{
public:
     GroupedAVPImplDerived(const AttributeName* nameObj)
     {
        avpContPtrObj = new AVPContainerDerived();
        avpContPtrObj->SetNameObj(nameObj);
     }
     ~GroupedAVPImplDerived();
     GroupedAVPImplDerived(const GroupedAVPImplDerived& implObj);
     virtual const AVPContainer &getContainer() const
     {
        return *avpContPtrObj;
     }

     virtual AVPContainer &getContainer()
     {
        return *avpContPtrObj;
     }
     bool validate() const
     {
         if (!avpContPtrObj->validateMand())
         {
             avpContPtrObj->PrintMissingMandAvp();
             return false;
         }
         return true;
     }
     std::ostream &print(std::ostream &out) const
     {
         return avpContPtrObj->print(out);
     }      
     virtual int Decode(unsigned char*& inputBuff, unsigned int size, DiaHeader& hdr);
     virtual int Encode(String& str);
     virtual GroupedAVPImpl* createCopy() const;
     //void operator =(const GroupedAVPImplDerived& cImpl);
     GroupedAVPImplDerived& operator =(const GroupedAVPImplDerived& cImpl);
private:
   std::vector<int> missingAVPCodes;
    AVPContainerDerived* avpContPtrObj;
};

class CommandImplDerived : public CommandImpl, public DataToAppToData<unsigned int>
{
public:
    CommandImplDerived(bool request, bool proxyable, bool error, bool retrans, CommandCode code, ApplicationId appId);
    CommandImplDerived(const unsigned char *buffer, int size, const CommandAttribute* descObj);
    CommandImplDerived(Command* cmd);
    CommandImplDerived(const CommandImplDerived& cImpl);
    void copy(const CommandImplDerived& cImpl);
    void operator = (const CommandImplDerived& cImpl)
    {
       copy(cImpl);
    }
    void  SetCmdAttribute(const CommandAttribute* cmdnameObj);
    ~CommandImplDerived();
    DiaHeader& getHeader(){ return hdr;}
    virtual bool isRequest() const { return hdr.flags.r;}
    virtual bool isProxyable() const { return hdr.flags.p;}
    virtual bool isError() const { return hdr.flags.e;}
    virtual bool isRetransmit() const { return hdr.flags.t;}
    virtual const char *getCommandName() const {return "CommandName";}
    virtual CommandCode getCommandCode() const { return hdr.code;}
    virtual ApplicationId getApplicationId() const { return hdr.appId;}
    virtual const AVPContainer &getContainer() const
    {
       return *avpContPtrObj;
    }
    virtual AVPContainer &getContainer()
    {
       return *avpContPtrObj;
    }
    virtual int encode(unsigned char *&, int&);
    void validateApp(const CommandAttribute* descObj=NULL);
    virtual CommandImpl* createCopy() const;
    virtual unsigned int& getSessionIndex(){return _sessIndex;}
    virtual unsigned int& getClientId(){return _clientId;}
 
    // Accounting Statemachine specific
    virtual bool& IsStorageSpaceAvailable()
    {
        return _storageSpaceAvailable;
    }
    virtual bool& IsLastRecordInStorage()
    {
        return _lastRecordInStorage;
    }

    //following APIs are purely used by stack and hence not exposed by Command
    int getAvpValue(unsigned int avpCode, void* val, ValueDiscriminator D,
                    unsigned int venId=0) const;

	//Added a new API to access multi-Occurance AVP's
    int getAvpValue(unsigned int avpCode,unsigned int index,
			void* val, ValueDiscriminator D,unsigned int venId=0) const;

	int getAvpCount(unsigned int avpCode, unsigned int venId=0);

    //any user data can be in the command, deletion is user's responsibility
    void setUserData(void* userData){_userData = userData;}
    void* getUserData(){return _userData;}
    void setEncodedBuf(void* enBuf){_enBuf = enBuf;}
    void* getEncodedBuf(){return _enBuf;}
    void setEncodedBufLen(unsigned short enBufLen){_enBufLen = enBufLen;}
    unsigned short getEncodedBufLen(){return _enBufLen;}

    //std::vector<int> multiOccurAVPCodes;
    private:
    DiaHeader hdr;
    AVPContainerDerived* avpContPtrObj;
    unsigned int _sessIndex;
    unsigned int _clientId;
    bool _storageSpaceAvailable;
    bool _lastRecordInStorage;
    void* _userData;
    /* Encoded Buffer */
    void* _enBuf;
    unsigned short _enBufLen;
};

class DictAttributeList
{
public:
    DictAttributeList();
    ~DictAttributeList();
    AttributeName* &operator [](unsigned int index);
    const AttributeName* getAttribute(unsigned int avp, unsigned int venId);
    static DictAttributeList _dictAttributeList;
    void reArrange();
private:
    AttributeName** _AttributeList;
    unsigned int _noOfAttribute;
    std::map<unsigned long long, unsigned int> _avpCodeIndex;
};

typedef enum _baseCmdAvpCode
{
    SESSID_AVP_CODE           = 263,
    OHOST_AVP_CODE            = 264,
    OREALM_AVP_CODE           = 296,
    DHOST_AVP_CODE            = 293,
    DREALM_AVP_CODE           = 283,
    OSTATEID_AVP_CODE         = 278,
    RCODE_AVP_CODE            = 268,
    /* Auth Specific */
    AUTH_SSTATE_AVP_CODE      = 277,
    AUTH_LTIME_AVP_CODE       = 291,
    AUTH_GPTIME_AVP_CODE      = 276,
    AUTH_SESSTIME_AVP_CODE    = 27,
    /* Acct Specific */
    ACCT_RECTYPE_AVP_CODE     = 480,
    ACCT_REALTIME_AVP_CODE    = 483,
    ACCT_INTERIM_AVP_CODE     = 85,
    ACCT_SESSTIME_AVP_CODE    = 46,
    /* vendor specific */
    VENDOR_ID_AVP_CODE        = 266,
    AUTH_APP_ID_AVP_CODE      = 258,
    ACCT_APP_ID_AVP_CODE      = 259,
    VENDOR_SPECIFIC_APP_ID_AVP_CODE = 260,
    /* Relay & Proxy */
    ROUTE_RECORD_AVP_CODE     = 282,
    PROXY_INFO_AVP_CODE       = 284,
    PROXY_HOST_AVP_CODE       = 280,
    PROXY_STATE_AVP_CODE      = 33,
    /* DCCA Specific */
    CC_REQUEST_TYPE_AVP_CODE  = 416,
    CCFH_AVP_CODE             = 427,
    REQUESTED_ACTION_AVP_CODE = 436,
    /* Redirect Specific */
    RD_HOST_AVP_CODE          = 292,
    RD_HOST_USAGE_AVP_CODE    = 261,
    RD_HOST_CACHE_AVP_CODE    = 262,
    IDC_IDS_HB_AVP_CODE       = 555,

    /* Global Uniq Addr */
    GLOBAL_UNIQ_ADDR_AVP_CODE = 300, 
    FRAMED_IP_ADDR_AVP_CODE = 8 
}BASE_AVP_CODE;

typedef enum _baseAvpBitMap
{
    SESSID_AVP_BIT        = (1<<0),
    OHOST_AVP_BIT         = (1<<1),
    OREALM_AVP_BIT        = (1<<2),
    DHOST_AVP_BIT         = (1<<3),
    DREALM_AVP_BIT        = (1<<4),
    OSTATEID_AVP_BIT      = (1<<5),
    RCODE_AVP_BIT         = (1<<6),
    /* Auth Specific */
    AUTH_SSTATE_AVP_BIT   = (1<<7),
    AUTH_LTIME_AVP_BIT    = (1<<8),
    AUTH_GPTIME_AVP_BIT   = (1<<9),
    AUTH_SESSTIME_AVP_BIT = (1<<10),
    /* Acct Specific */
    ACCT_RECTYPE_AVP_BIT  = (1<<11),
    ACCT_REALTIME_AVP_BIT = (1<<12),
    ACCT_INTERIM_AVP_BIT  = (1<<13),
    ACCT_SESSTIME_AVP_BIT = (1<<14),
    /* Relay & Proxy */
    ROUTE_RECORD_AVP_BIT  = (1<<15),
    PROXY_INFO_AVP_BIT    = (1<<16),
    /* Vendor specific */
    VENDOR_ID_AVP_BIT     = (1<<17),
    VENDOR_SPEC_AVP_BIT   = (1<<18),
    /* DCCA */
    CC_REQ_TYPE_AVP_BIT   = (1<<19),
    CCFH_AVP_BIT          = (1<<20),
    REQ_ACTION_AVP_BIT    = (1<<21),
    /* Redirect Specific */
    RD_HOST_AVP_BIT       = (1<<22),
    RD_HOST_USAGE_AVP_BIT = (1<<23),
    RD_HOST_CACHE_AVP_BIT = (1<<24),
    IDC_IDS_HB_AVP_BIT    = (1<<25),
    /* Global Uniq Addr */
    GLOBAL_UNIQ_ADDR_AVP_BIT    = (1<<26)

}BASE_AVP_BIT_MAP;

typedef struct _avpString
{
    std::string &value(){return data;}
    std::string data;
}AVP_STRING;


typedef struct _avpInt
{
    unsigned int& value(){return data;}
    unsigned int data;

    _avpInt(){data = 0;};
}AVP_UINT;
typedef struct _avpShort
{
    unsigned short& value(){return data;}
    unsigned short data;

    _avpShort(){data = 0;};
}AVP_USHORT;

typedef enum
{
    AUTH_APP =0,
    ACCT_APP
} APP_TYPE;

typedef struct
{
    AVP_UINT vendorId;
    AVP_UINT appId;
    APP_TYPE type;
    int vendorIdCount;
    
    bool containsAuthApplicationId()
    {
        if(type == AUTH_APP)
            return true;

        return false;
    }

    bool containsAcctApplicationId()
    {
        if(type == ACCT_APP)
            return true;

        return false;
    }
    
    int countVendorId()
    {
        return vendorIdCount;
    }

    AVP_UINT getVendorId(int index)
    {
        return vendorId;
    }

    AVP_UINT getAuthApplicationId()
    {
        return appId;
    }

    AVP_UINT getAcctApplicationId()
    {
        return appId;
    }
} VENDOR_SPEC_APP_ID;

typedef struct
{
    AVP_STRING pxyHost;
    AVP_STRING pxyState;

    AVP_STRING* getProxyHost()
    {
        return &pxyHost;
    }

    AVP_STRING* getProxyState()
    {
        return &pxyState;
    }
} PROXY_INFO;
/* Redirect Host's Enums*/
typedef enum
{
    AAA = 0,
    AAAS
} URI_SCHEME;
 
typedef enum
{
    TCP = 0,
    SCTP,
    UDP
} URI_TRANSPORT;
 
typedef enum
{
    DIAMETER = 0,
    RADIUS,
    TACACSPLUS
} URI_PROTOCOL;
 
/* Redirect Host AVP struct*/
typedef struct
{
    URI_SCHEME scheme;
    AVP_STRING fqdn;
    AVP_USHORT port;
    URI_TRANSPORT transport;
    URI_PROTOCOL protocol;
} AVP_URI;

class BaseCommand : public DataToAppToData<unsigned int>
{
public:
    BaseCommand (const unsigned char *buff, int len);

    BaseCommand (diameter::base::BaseGenericCommand* cmd);

    BaseCommand ():
        _sessIndex(0),
        _clientId(0),
        _storageSpaceAvailable(true),
        _lastRecordInStorage(false),
        _ptrRouteRecord(NULL),
        _routeRecCount(0),
        _routeRecTotalCount(0),
        _ptrProxyInfo(NULL),
        _proxyCount(0),
        _pxyTotalCount(0),
        _vendorSpecAppIdCount(0),
        _ptrRdHost(NULL),
        _rdHostCount(0),
        _rdHostTotalCount(0),
        _idcIdsHb(0),
        _globalUniqAddr({0}),
        _userData(NULL),
        _enBuf(NULL),
        _bufToDel(NULL),
        _enBufLen(0),
        _avpBitMap(0)
        {
        }
 

    ~BaseCommand() 
    { 
        if (_bufToDel != NULL)
        {
            free(_bufToDel);
            _bufToDel = NULL;
        }
        else if(_enBuf != NULL) 
        {
            ITS_OCTET* ptr = (ITS_OCTET*) _enBuf;
            if (ptr != NULL)
            {
                free(ptr);
            }
            _enBuf = NULL;
        }
        
        if (_ptrRouteRecord)
        {
            delete [] _ptrRouteRecord;
        }

        if (_ptrProxyInfo)
        {
            delete [] _ptrProxyInfo;
        }

        if (_ptrRdHost)
        {
            delete [] _ptrRdHost;
        }

    }

    DiaHeader& getHeader(){ return hdr;}
    bool containsIDCIDSHeartbeat() 
    {
        if ( (_avpBitMap & IDC_IDS_HB_AVP_BIT) == IDC_IDS_HB_AVP_BIT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    unsigned int getIdcIdsHBValue() const
    {
        if ( (_avpBitMap & IDC_IDS_HB_AVP_BIT) == IDC_IDS_HB_AVP_BIT)
        {
            return _idcIdsHb;
        }
        else
        {
            return 0;
        }
    }

    bool containsGlobalUniqAddr() 
    {
        if ( (_avpBitMap & GLOBAL_UNIQ_ADDR_AVP_BIT)==GLOBAL_UNIQ_ADDR_AVP_BIT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    unsigned char* getGlobalUniqAddr() const
    {
        if ( (_avpBitMap & GLOBAL_UNIQ_ADDR_AVP_BIT)== GLOBAL_UNIQ_ADDR_AVP_BIT)
        {
            return (unsigned char*)_globalUniqAddr;
        }
        else
        {
            return 0;
        }
    }

    bool isRequest() const { return hdr.flags.r;}
    bool isProxyable() const { return hdr.flags.p;}
    bool isError() const { return hdr.flags.e;}
    bool isRetransmit() const { return hdr.flags.t;}
    unsigned int getCommandCode() const { return hdr.code;}
    unsigned int getApplicationId() const { return hdr.appId;}
    unsigned int& getSessionIndex(){return _sessIndex;}
    unsigned int& getClientId(){return _clientId;}
    void setSessionIndex(unsigned int sIndx){_sessIndex=sIndx;}
    void setClientId(unsigned int cId){_clientId=cId;}

    unsigned int countRouteRecord() { return _routeRecCount;}

    AVP_STRING* getRouteRecord(unsigned int index)
    {
        if (((_avpBitMap & ROUTE_RECORD_AVP_BIT) == ROUTE_RECORD_AVP_BIT)
                    && (index < _routeRecCount)) 
        {
            return &_ptrRouteRecord[index];
        }
        else
        {
            return NULL;
        }
    }

    AVP_STRING* getSessionId()  
    { 
        if ((_avpBitMap & SESSID_AVP_BIT) == SESSID_AVP_BIT)
        { 
            return &_sessId; 
        }
        else
        {
            return NULL;
        }
    }
    AVP_STRING* getOriginHost()
    { 
        if ((_avpBitMap & OHOST_AVP_BIT) == OHOST_AVP_BIT)
        {
            return &_originHost; 
        }
        else
        {
            return NULL;
        }
    }

    AVP_STRING* getDestinationHost() 
    { 
        if ((_avpBitMap & DHOST_AVP_BIT) == DHOST_AVP_BIT)
        {
            return &_destHost; 
        }
        else
        {
            return NULL;
        }
    }
    AVP_STRING* getOriginRealm() 
    { 
        if ((_avpBitMap & OREALM_AVP_BIT) == OREALM_AVP_BIT)
        {
            return &_originRealm;
        }
        else
        {
            return NULL;
        }
    }
    AVP_STRING* getDestinationRealm() 
    { 
        if ((_avpBitMap & DREALM_AVP_BIT) == DREALM_AVP_BIT)
        {
            return &_destRealm;
        }
        else
        {
            return NULL;
        }
    }
    AVP_UINT* getAuthApplicationId()
    {
        return &_appId;
    }
    AVP_UINT* getAcctApplicationId()
    {
        return &_appId;
    }

    AVP_UINT* getOriginStateId() 
    {
        if ((_avpBitMap & OSTATEID_AVP_BIT) == OSTATEID_AVP_BIT)
        {
            return &_originStateId;
        }
        else
        {             
            return NULL;
        }
    }

    void setOriginStateId(unsigned int orgStateId) 
    { 
        _originStateId.data = orgStateId;
    }

    /* Answer specific */
    AVP_UINT* getResultCode() 
    { 
        if ((_avpBitMap & RCODE_AVP_BIT) == RCODE_AVP_BIT)
        {
            return &_resultCode; 
        }
        else
        {             
            return NULL;
        }
    }

    /* Accounting specific */
    AVP_USHORT* getAuthSessionState() 
    { 
        if ((_avpBitMap & AUTH_SSTATE_AVP_BIT) == AUTH_SSTATE_AVP_BIT)
        {
            return &_authSessState; 
        }
        else
        {
            return NULL;
        }
    }

    AVP_UINT* getAuthorizationLifetime(int index = 0) 
    {
        if ((_avpBitMap & AUTH_LTIME_AVP_BIT) == AUTH_LTIME_AVP_BIT)
        {
            return &_authLifetime;
        }
        else
        {
            return NULL;
        }
    }

    AVP_UINT*getAuthGracePeriod(int index = 0) 
    {
        if ((_avpBitMap & AUTH_GPTIME_AVP_BIT) == AUTH_GPTIME_AVP_BIT)
        {
            return &_authGracePeriod;
        }
        else
        {
            return NULL;
        }
    }

    AVP_UINT* getSessionTimeout(int index = 0) 
    {
        if((_avpBitMap &AUTH_SESSTIME_AVP_BIT) == AUTH_SESSTIME_AVP_BIT)
        {
            return &_authSessTime;
        }
        else
        {
            return NULL;
        }
    }

    /* Accounting specific */
    AVP_USHORT* getAccountingRecordType() 
    {
        if ((_avpBitMap & ACCT_RECTYPE_AVP_BIT) == ACCT_RECTYPE_AVP_BIT)
        {
            return &_acctRecType; 
        }
        else
        {
            return NULL;
        }
    }
    
    /* TODO - rajesh check this function */
    int countAccountingRealtimeRequired()
    {
        if ((_avpBitMap &ACCT_REALTIME_AVP_BIT) == ACCT_REALTIME_AVP_BIT)
        {
           return 1;
        }
        else
        {
            return 0;
        }
    }

    AVP_USHORT* getAccountingRealtimeRequired() 
    { 
        if ((_avpBitMap &ACCT_REALTIME_AVP_BIT) == ACCT_REALTIME_AVP_BIT)
        {
           return &_acctRealTime; 
        }
        else
        {
            return NULL;
        }
    }
    AVP_UINT* getAcctInterimInterval()
    {
        if ((_avpBitMap & ACCT_INTERIM_AVP_BIT) == ACCT_INTERIM_AVP_BIT)
        {
            return &_acctInterimInvl; 
        }
        else
        {
            return NULL;
        }
    }

    AVP_UINT* getAcctSessionTime() 
    {
        if ((_avpBitMap &ACCT_SESSTIME_AVP_BIT) == ACCT_SESSTIME_AVP_BIT)
        {
            return &_acctSessTime; 
        }
        else
        {
            return NULL;
        }
    }

    int getAvpValue(unsigned int avpCode, int* val, 
                                    diameter::ValueDiscriminator type)
    {
        if ((avpCode == CC_REQUEST_TYPE_AVP_CODE) && 
                                (_avpBitMap & CC_REQ_TYPE_AVP_BIT))
        {
            *val = _ccReqType.value();
        }
        else if ((avpCode == REQUESTED_ACTION_AVP_CODE) && 
                                (_avpBitMap & REQ_ACTION_AVP_BIT))
        {
            *val = _reqAction.value();
        }
        else if ((avpCode == CCFH_AVP_CODE) && (_avpBitMap & CCFH_AVP_BIT))
        {
            *val = _ccFaultHandling.value();
        }
        else 
        {
            return 1;
        }
 
        return 0;
    }
    
    AVP_UINT* getVendorId() 
    { 
        if ((_avpBitMap & VENDOR_ID_AVP_BIT) == VENDOR_ID_AVP_BIT)
        {
            return &_vendorId; 
        }
        else
        {
            return NULL;
        }
    }
    
    VENDOR_SPEC_APP_ID* getVendorSpecificApplicationId(unsigned int index=0)
    {
        if ((index <_vendorSpecAppIdCount) && 
                    ((_avpBitMap & VENDOR_SPEC_AVP_BIT) == VENDOR_SPEC_AVP_BIT))
        {
            return &_vendorSpecificAppId[index];
        }
        else
        {
            return NULL;
        }
    }

    /* Redirect Specific*/
    bool containsRedirectHost()
    {
        if ( (_avpBitMap & RD_HOST_AVP_BIT) == RD_HOST_AVP_BIT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
 
    AVP_URI* getRedirectHost(unsigned int index) const
    {
        if ( (_avpBitMap & RD_HOST_AVP_BIT) == RD_HOST_AVP_BIT &&
             (index < _rdHostCount) )
        {
            return &_ptrRdHost[index];
        }
        else
        {
            return NULL;
        }
    }
 
    unsigned int countRedirectHost()
    {
        return _rdHostCount;
    }
 
    bool containsRedirectMaxCacheTime()
    {
        if ( (_avpBitMap & RD_HOST_CACHE_AVP_BIT) == RD_HOST_CACHE_AVP_BIT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
 
    AVP_UINT* getRedirectMaxCacheTime()
    {
        if ( (_avpBitMap & RD_HOST_CACHE_AVP_BIT) == RD_HOST_CACHE_AVP_BIT)
        {
            return &_rdHostCache;
        }
        else
        {
            return NULL;
        }
    }
 
    bool containsRedirectHostUsage()
    {
        if ( (_avpBitMap & RD_HOST_CACHE_AVP_BIT) == RD_HOST_CACHE_AVP_BIT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
 
    AVP_UINT* getRedirectHostUsage()
    {
        if ( (_avpBitMap & RD_HOST_USAGE_AVP_BIT) == RD_HOST_USAGE_AVP_BIT)
        {
            return &_rdHostUsage;
        }
        else
        {
            return NULL;
        }
    }

    int addAvpBuf(const char* buff, int len)
    {
        //allocate new buffer 
        unsigned char* pBuff =  (unsigned char*)malloc(_enBufLen+len);

        memcpy(pBuff, _enBuf, _enBufLen);     //copy the previous buffer
        memcpy(&pBuff[_enBufLen], buff, len); //now copy the new avp buff

        ITS_OCTET* ptr = (ITS_OCTET*) _enBuf;
        if (_bufToDel != NULL)
        {
            free(_bufToDel);
            _bufToDel = NULL;
        }
        else if(_enBuf != NULL)
        {
            if (ptr != NULL)
            {
                free(ptr);
            }
            _enBuf = NULL;
        }
        _enBuf = pBuff;
        _enBufLen+=len;	                      //update the buffer length

        AppToData((char*)&pBuff[1], _enBufLen, 3); //update msg length in buff
        hdr.length = _enBufLen;

        return 0;
    }

    int setResultCode(int rCode)
    {
        int ret = 1;
        unsigned char* buffer = (unsigned char *)_enBuf;
        unsigned char* end    = (unsigned char*)(buffer+_enBufLen);

        buffer +=20;

        while((unsigned long)(buffer+8) <= (unsigned long)end)//parse AVPs
        {
            //unsigned char* startBuff = buffer;
            unsigned int offset      = 8;
            unsigned int avpCode = DataToApp(buffer, 4);
            buffer+=4;
            unsigned int avpLen = DataToApp(buffer+1, 3);
            //unsigned int vendorId = 0;

            if(*buffer & 0x80)
            {
              //with vendorId
              buffer +=4;
              avpLen -=4;
              offset +=4;
            }

            buffer +=4;
            avpLen -=8;
            if (avpCode)
            {
                switch(avpCode)
                {
                case RCODE_AVP_CODE:
                    {
                        char temp[4];
                        AppToData(temp, rCode);
                        memcpy(buffer, temp, 4);
                        //also update the result code variable
                        _resultCode.data = rCode;
                        return 0;
                    }
                    break;
                }
            }
            buffer +=avpLen;
            //align buffer to word byte
            avpLen = (avpLen % 4);
            if(avpLen)
            {
               buffer +=(4-avpLen);
            }
        }
        return ret;
    }
    
    unsigned int countProxyInfo()
    {
        return _proxyCount;
    }

    PROXY_INFO* getProxyInfo(unsigned int index)
    {
        if (((_avpBitMap & PROXY_INFO_AVP_BIT) == PROXY_INFO_AVP_BIT) 
                                    && (index<_proxyCount))
        {
            return &_ptrProxyInfo[index];
        }
        else
        {
            return NULL;
        }
    }

    void setStorageSpaceAvailable(bool index) 
    {
        _storageSpaceAvailable = index; 
    }

    void setLastRecordInStorage(bool index) 
    {
        _lastRecordInStorage = index; 
    }

    bool& IsStorageSpaceAvailable() 
    { 
        return _storageSpaceAvailable; 
    }

    bool& IsLastRecordInStorage() 
    {
        return _lastRecordInStorage; 
    }

    /* Encoded Buffer */
    void setUserData(void* userData){_userData = userData;}
    void setPtrToFreeBuf(void* data){_bufToDel = data;}
    void* getUserData(){return _userData;}
    void setEncodedBuf(void* enBuf){_enBuf = enBuf;}
    void* getEncodedBuf(){return _enBuf;}
    void setEncodedBufLen(unsigned short enBufLen){_enBufLen = enBufLen;}
    unsigned short getEncodedBufLen(){return _enBufLen;}

    void DecodeProxyInfoAvp(const unsigned char *buffer, int len);
    void DecodeVendorSpecificAvp(const unsigned char *buffer, int len);
    void DecodeRouteRecordAvp(const unsigned char *buffer, int len);
    void DecodeRedirectHostAvp(const unsigned char *buffer, int len);
    int removeAVP(unsigned int code);
    void PrintAVPURI(AVP_URI *uri);
    void DecodeGlobalUniqAddrAvp(const unsigned char *buffer, int len);
    int validateComandCodeandAppId(unsigned int aAppId, unsigned int aCode);
    void operator = (BaseCommand& bCmd)
    {
        copy(bCmd);
    }

    BaseCommand(BaseCommand& bCmd)
    {
        copy(bCmd);
    }
    
    void copyHeader(const DiaHeader& srcHdr)
    {
        hdr.ver = srcHdr.ver;
        hdr.length = srcHdr.length;
        hdr.code = srcHdr.code;
        hdr.appId = srcHdr.appId;
        hdr.hh = srcHdr.hh;
        hdr.ee = srcHdr.ee;
        hdr.flags.r = srcHdr.flags.r;
        hdr.flags.p = srcHdr.flags.p;
        hdr.flags.e = srcHdr.flags.e;
        hdr.flags.t = srcHdr.flags.t;
        hdr.flags.rsvd = srcHdr.flags.rsvd;
    }
    
    void copy(const BaseCommand& baseCmd)
    {
        copyHeader(baseCmd.hdr);

        _ptrProxyInfo = NULL;
        _ptrRouteRecord = NULL;
        _userData = NULL;
        _enBuf = NULL;
        _ptrRdHost = NULL;
        _bufToDel  = NULL; 

        _sessIndex       = baseCmd._sessIndex;
        _clientId        = baseCmd._clientId;
        _appId.data      = baseCmd._appId.data;
        _sessId.data     = baseCmd._sessId.data;
        _originHost.data = baseCmd._originHost.data;
        _destHost.data   = baseCmd._destHost.data;
        _destRealm.data  = baseCmd._destRealm.data; 
        _originRealm.data= baseCmd._originRealm.data;
        _resultCode.data = baseCmd._resultCode.data;
        _authSessState.data = baseCmd._authSessState.data;
        _authLifetime.data  = baseCmd._authLifetime.data;
        _authGracePeriod.data = baseCmd._authGracePeriod.data;
        _authSessTime.data = baseCmd._authSessTime.data;
        _acctRecType.data = baseCmd._acctRecType.data;
        _acctRealTime.data = baseCmd._acctRealTime.data;
        _acctInterimInvl.data = baseCmd._acctInterimInvl.data;

        _acctSessTime.data = baseCmd._acctSessTime.data;
        _storageSpaceAvailable = baseCmd._storageSpaceAvailable;
        _lastRecordInStorage = baseCmd._lastRecordInStorage;

        //copy route record
        _routeRecCount = baseCmd._routeRecCount;
        _routeRecTotalCount = _routeRecCount;
        if(_routeRecCount > 0)
        {
            _ptrRouteRecord = new AVP_STRING[_routeRecCount];
        }

        for (unsigned int i = 0; i<_routeRecCount; i++)
        {
            _ptrRouteRecord[i].data = baseCmd._ptrRouteRecord[i].data;
        }

        //copy proxy info
        _proxyCount = baseCmd._proxyCount;
        _pxyTotalCount = _proxyCount;
        if(_proxyCount > 0)
        {
            _ptrProxyInfo = new PROXY_INFO[_proxyCount];
        }

        for (unsigned int i = 0; i<_proxyCount; i++)
        {
            _ptrProxyInfo[i].pxyHost.data = 
                                baseCmd._ptrProxyInfo[i].pxyHost.data;
            _ptrProxyInfo[i].pxyState.data = 
                                baseCmd._ptrProxyInfo[i].pxyState.data;
        }

        //copy vendor specific app id
        _vendorId.data = baseCmd._vendorId.data;
        _vendorSpecAppIdCount = baseCmd._vendorSpecAppIdCount;

        for (unsigned int i; i<_vendorSpecAppIdCount; i++)
        {
            _vendorSpecificAppId[i].vendorId.data = 
                            baseCmd._vendorSpecificAppId[i].vendorId.data;

            _vendorSpecificAppId[i].appId.data = 
                            baseCmd._vendorSpecificAppId[i].appId.data;

            _vendorSpecificAppId[i].vendorIdCount = 
                            baseCmd._vendorSpecificAppId[i].vendorIdCount;

            _vendorSpecificAppId[i].type = 
                            baseCmd._vendorSpecificAppId[i].type;
        }

        /* Copy Redirect Host */
        _rdHostCount = baseCmd._rdHostCount;
        _rdHostTotalCount = _rdHostCount;
 
        if(_rdHostCount > 0)
        {
            _ptrRdHost = new AVP_URI[_rdHostCount];
        }
 
        for (unsigned int i = 0; i<_rdHostCount; i++)
        {
            _ptrRdHost[i].scheme = baseCmd._ptrRdHost[i].scheme;
            _ptrRdHost[i].fqdn.data = baseCmd._ptrRdHost[i].fqdn.data;
            _ptrRdHost[i].port.data = baseCmd._ptrRdHost[i].port.data;
            _ptrRdHost[i].transport = baseCmd._ptrRdHost[i].transport;
            _ptrRdHost[i].protocol =  baseCmd._ptrRdHost[i].protocol;
        }
 
        /* Copy Redirect-Host-Usage */
            _rdHostUsage.data =  baseCmd._rdHostUsage.data;
 
        /* Copy Redirect-Host-Max-Cache-Time */
            _rdHostCache.data = baseCmd._rdHostCache.data;

        //dcca
        _ccReqType.data = baseCmd._ccReqType.data;
        _reqAction.data = baseCmd._reqAction.data;
        _ccFaultHandling.data = baseCmd._ccFaultHandling.data;

        //copy bitmap
        _avpBitMap = baseCmd._avpBitMap;
        
        if (baseCmd._userData)
        {
            ITS_EVENT* evt = (ITS_EVENT*)baseCmd._userData;
            int evtLen = evt->len;

            ITS_EVENT* pNewEvt = new ITS_EVENT;
            pNewEvt->len = evtLen;
            //pNewEvt->data = (ITS_OCTET*) malloc(evtLen);
            pNewEvt->data = new unsigned char [evtLen];
            memcpy(pNewEvt->data, evt->data, evtLen);

            _userData = (void*) pNewEvt;
        }

        _enBufLen = baseCmd._enBufLen;

        if( _enBufLen > 0)
        {
            void* srcPtr = baseCmd._enBuf;
            _enBuf = malloc(_enBufLen);
            memcpy(_enBuf, srcPtr, _enBufLen);
        }
    }

    void setSessionId(const std::string& sessId)
    {
        _sessId.data = sessId;
    }

    void setSessionId(const std::string& sessId, bool avpBitMap=false)
    {
        if (avpBitMap)
        {
            _avpBitMap |= SESSID_AVP_BIT;
        }
        _sessId.data = sessId;
    }

    void setOriginHost(const std::string& ohost)
    {
        _originHost.data = ohost;
    }
    void setDestinationHost(const std::string& dhost)
    {
        // Destination Host may not have been present in the original message
        // So set the BIT no matter what
        _avpBitMap |= DHOST_AVP_BIT;
        _destHost.data = dhost;
    }
    void setOriginRealm(const std::string& orealm)
    {
        _originRealm.data = orealm;
    }
    void setDestinationRealm(const std::string& drealm)
    {
        _destRealm.data = drealm;
    }
    void clearDestinationHost()
    {
        _avpBitMap &= ~DHOST_AVP_BIT;
    }
    void clearProxyInfo()
    {
        if (_ptrProxyInfo)
        {
            delete [] _ptrProxyInfo;
            _ptrProxyInfo = NULL;
            _proxyCount = 0;
            _pxyTotalCount = 0;
            _avpBitMap &= ~PROXY_INFO_AVP_BIT;
        }
    }
    void clearRouteRecord()
    {
        if (_ptrRouteRecord)
        {
            delete [] _ptrRouteRecord;
            _ptrRouteRecord = NULL;
            _routeRecCount = 0;
            _routeRecTotalCount = 0;
            _avpBitMap &= ~ROUTE_RECORD_AVP_BIT;
        }
    }

    void reencode(diameter::base::BaseGenericCommand* bcmd)
    {
        // not cathcing the exception here, expecting the upper layers to take
        // care of it
        if (_bufToDel)
        {
            free(_bufToDel);
            _bufToDel = NULL;
        }
        else if (_enBuf)
        {
            free(_enBuf);
            _enBuf = NULL;
            _enBufLen = 0;
        }
        uint8_t* buf;
        int len;
        bcmd->encode(buf, len);
        _enBuf = buf;
        _enBufLen = (unsigned short)len;
    }
    
private:
    /* generic members */
    DiaHeader hdr;
    unsigned int _sessIndex;
    unsigned int _clientId;
    AVP_UINT     _appId;

    AVP_STRING   _sessId;
    AVP_STRING   _originHost;
    AVP_STRING   _destHost;
    AVP_STRING   _originRealm;
    AVP_STRING   _destRealm;
    AVP_UINT     _originStateId;
    
    /* Answer Message */
    AVP_UINT     _resultCode;
   
    /* Accounting  specific */
    AVP_USHORT   _authSessState;
    AVP_UINT     _authLifetime;
    AVP_UINT     _authGracePeriod;
    AVP_UINT     _authSessTime;

    /* Accounting  specific */
    AVP_USHORT   _acctRecType;
    AVP_USHORT   _acctRealTime;
    AVP_UINT     _acctInterimInvl;
    AVP_UINT     _acctSessTime;
    bool         _storageSpaceAvailable;
    bool         _lastRecordInStorage;

    /* Proxy*/
    AVP_STRING*  _ptrRouteRecord;
    unsigned int _routeRecCount;
    unsigned int _routeRecTotalCount;   //Allocated size

    PROXY_INFO*   _ptrProxyInfo;
    unsigned int  _proxyCount;
    unsigned int  _pxyTotalCount;       //Allocated size

    AVP_UINT     _vendorId;
    VENDOR_SPEC_APP_ID   _vendorSpecificAppId[MAX_LEN];
    unsigned int _vendorSpecAppIdCount;

    /* Redirect*/
    AVP_UINT     _rdHostUsage;
    AVP_UINT     _rdHostCache;
 
    AVP_URI*       _ptrRdHost;
    unsigned int   _rdHostCount;
    unsigned int   _rdHostTotalCount;
    /* DCCA */
    AVP_USHORT   _ccReqType;
    AVP_USHORT   _reqAction;
    AVP_USHORT   _ccFaultHandling;

    /* HB AVP */
    unsigned int _idcIdsHb;

    /* Global Uniq Addr */   
    unsigned char  _globalUniqAddr[MAX_IP_STR_LEN];

    /* Encoded Buf */
    void*          _userData;
    void*          _enBuf;
    void*          _bufToDel;
    unsigned short _enBufLen;
    /* bit Map */
    unsigned int _avpBitMap;
};

}
#endif

