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
 * LOG: $Log: AVP.h,v $
 * LOG: Revision 3.4.6.4  2012/10/03 16:27:35  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.4.6.3  2012/10/01 09:01:04  rsanjay
 * LOG:  opendiameter code removal changes:bugzilla-id 300
 * LOG:
 * LOG: Revision 3.4.6.2.4.2  2012/09/20 07:41:25  cprem
 * LOG: Added a new function called getAvpCount to fetch number of times an AVP is present in a message.
 * LOG:
 * LOG: Revision 3.4.6.2.4.1  2012/09/14 15:43:05  cprem
 * LOG: Generic AVP Access API including support for multiple-occurance AVP's.
 * LOG:
 * LOG: Revision 3.4.6.2  2012/07/31 07:57:10  cprem
 * LOG: Review Commentsi addressed:Resetting the out stream to std::dec after appending hex values
 * LOG: using std::hex.
 * LOG:
 * LOG: Revision 3.4.6.1  2012/07/26 11:43:45  cprem
 * LOG: Added function formatforRE to format the Diameter Message AVP's that can be fed to Rule Engine as facts. The fact format is for CLIPS Rule Engine.
 * LOG:
 * LOG: Revision 3.4  2010/11/19 16:42:46  nvijikumar
 * LOG: Introduced containsExtra API with index as input parameter
 * LOG:
 * LOG: Revision 3.3  2008/12/11 14:22:45  rajeshak
 * LOG: Replaced stl string with own String class (Hemant,Rajesh)
 * LOG:
 * LOG: Revision 3.2  2008/03/31 13:09:29  hbhatnagar
 * LOG: Change in Signature for getAvpValue() API against ticket 1850.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.14  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.7.2.5  2008/01/24 10:34:11  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 2.7.2.4  2007/05/29 07:49:42  hbhatnagar
 * LOG: made changes in the print function for printing the characters in hex
 * LOG: if any non-printable character is encountered.
 * LOG:
 * LOG: Revision 2.7.2.3  2007/04/19 13:42:29  hbhatnagar
 * LOG: Enhancement: Provided API to add and remove AVPs.
 * LOG:
 * LOG: Revision 2.7.2.2  2007/03/22 08:52:19  nvijikumar
 * LOG: ExtraAttributes creation based on avpCode and vendorId together
 * LOG:
 * LOG: Revision 2.7.2.1  2007/03/22 07:36:53  nvijikumar
 * LOG: Provided customized AVP(PayloadAvp) for Bridgewater MS-VSA avp issue (Tushar).
 * LOG:
 * LOG: Revision 2.7  2007/03/02 06:04:09  nvijikumar
 * LOG: Reverting back the JAVA changes which are committed before Branch tag.
 * LOG:
 * LOG: Revision 2.6  2007/02/26 08:08:28  sumag
 * LOG: t
 * LOG: :q
 * LOG:
 * LOG: Revision 2.5  2006/11/29 20:22:46  tpanda
 * LOG: appId ,cmdcode removed for extensible AVP addition
 * LOG:
 * LOG: Revision 2.4  2006/11/13 05:30:07  tpanda
 * LOG: dictionary extensible AVP encoding/decoding fix
 * LOG:
 * LOG: Revision 2.3  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:50:43  tpanda
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.7  2006/10/05 05:39:58  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 2.6  2006/09/26 15:25:41  tpanda
 * LOG: Fix for crash for get method in derived AVP
 * LOG:
 * LOG: Revision 2.5  2006/09/20 05:08:42  tpanda
 * LOG: Fix for createCopy while encoding and encoding support for GenericCommand
 * LOG:
 * LOG: Revision 2.4  2006/09/19 06:04:51  tpanda
 * LOG: Val is splitted. Encoding/Decoding functionality moved to vendor
 * LOG:
 * LOG: Revision 2.3  2006/09/15 13:11:02  tpanda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.2  2006/09/14 15:23:53  tpanda
 * LOG: Optimising the code.. still a lot of things to do
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.7  2006/08/13 09:53:09  brianhu
 * LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
 * LOG:
 * LOG: Revision 1.6  2006/06/21 10:26:35  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.5  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: AVP.h,v 3.4.6.4 2012/10/03 16:27:35 cprem Exp $
 ****************************************************************************/

#ifndef _DIAMETER_AVP_H_
#define _DIAMETER_AVP_H_

#include <diameter/Exceptions.h>
#include <diameter/Implementation.h>
#include <diameter/AttributeName.h>
#include <diameter/Trace.h>
#include <map>
#include <vector>
#include <sstream>

#ifdef DEBUG
#ifdef DEBUG_VERBOSE
#define VALCPP   "val-c++"
#endif
#endif

namespace diameter {

/**
 * Attribute-Value Pair
 */
class AVP {
    friend std::ostream &operator<<(std::ostream &, const AVP &);

public:
    virtual const AttributeName &name() const = 0;

    virtual const AVPImpl &getImpl() const = 0;

    virtual int Decode(unsigned char*& buff, unsigned int size, DiaHeader& hdr)=0;
    virtual int Encode(String& str)=0;
    virtual AVP* createCopy() const=0;
    virtual ~AVP(){}
    virtual int GetType() const=0;
    /*#
     * Prints the contents of this AVP to the output stream in human readable format.
     */
    virtual std::ostream &print(std::ostream &) const = 0;
	//Added for Rule Engine.
	//Formats the content of AVP into CLIPS fact format.
	virtual std::stringstream &formatforRE(std::stringstream &) const = 0;
	virtual std::stringstream &formatforRE(std::stringstream & ,const char *) const = 0;

};

/**
 * Stream inserter for AVP
 */
inline std::ostream &operator<<(std::ostream &out, const AVP &avp) {
    return avp.print(out);
}

/**
 * AVPCache is used by AVPContainer to cache type-safe AVP objects on bahalf of ap
 */
class AVPCache: public std::map<AttributeInstance, const AVP *> {
    typedef std::map<AttributeInstance, const AVP *> Super;

public:
    ~AVPCache() {
        for (Super::iterator it = begin(); it != end(); ++it) {
            delete it->second;
        }
    }
};


/**
 * Derived Diameter AVP Types
 */
template <typename T, ValueDiscriminator D>
class DerivedAVP: public AVP {
public:
    /**
     * Copy constructor not enabled, but accessible for initializing ref to temporaries. [dcl.init.ref]
     */
    DerivedAVP(const DerivedAVP & avp): _name(avp._name),
    _managed(DerivedAVPImpl<T, D>::acquire(avp.value())), _inbound(*_managed)
    {} 

    int GetType() const { return D;}

    AVP* createCopy() const
    {
        return new DerivedAVP(*this);
    }
    virtual ~DerivedAVP() {

#ifdef DEBUG
#ifdef DEBUG_VAL
        std::cout << "DerivedAVP<T, D>{" << _name << "}: releasing DerivedAVPImpl @ 0x"
                  << std::hex << (unsigned long)_managed << std::dec << std::endl;
#endif
#endif
        DerivedAVPImpl<T, D>::release(_managed);
    }

    const AttributeName &name() const {
        return _name;
    }

    const T &value() const {
        return _inbound.get();
    }


    const AVPImpl &getImpl() const {
        return _inbound;
    }


protected:
    /*#
     * Constructs a derived AVP from a value.
     */
    explicit DerivedAVP(const AttributeName &name, const T &value)
    : _name(name)
    , _managed(DerivedAVPImpl<T, D>::acquire(value)), _inbound(*_managed) 
   {
#ifdef DEBUG
#ifdef DEBUG_VAL
        std::cout << "DerivedAVP<T, D>{" << _name << "}: acquired DerivedAVPImpl @ 0x"
                  << std::hex << (unsigned long)_managed << std::dec << std::endl;
#endif
#endif
    }
    /*#
     * Constructs a derived AVP from an implementation.
     */
    explicit DerivedAVP(const AttributeName &name, const AVPImpl *impl)
    : _name(name),  
      _managed(DerivedAVPImpl<T, D>::acquire()), _inbound(*_managed) 
    {
#ifdef DEBUG
#ifdef DEBUG_VAL
        std::cout << "DerivedAVP<T, D>{" << _name << "}: received DerivedAVPImpl @ 0x"
                  << std::hex << (unsigned long)&_inbound << std::dec << std::endl;
#endif
#endif
    }


/*#
 * Prints the contents of this AVP.
 * ( The AVP of OctetString or UTF8String is printed in Hex form if any
 * non-printable character is found in the string.)
 */
std::ostream &print(std::ostream &out) const
{
    if ((D == OctetStringType) ||( D == UTF8StringType))
    {
        std::string& t = (std::string &)_inbound.get();
        const char *val = t.c_str();
        out << '<' << _name << ':';
        int len = t.length();
        for (int i=0; i<len; i++)
        {
            if (!isprint(val[i]))
            {
                for ( int j =0; j<len;j++)
                {
                    out<<"0x"<<std::hex<<(int)val[j];
                    if (j != len-1)
                    {
                        out<<',';
                    }
                }
                out <<'>';
                return out;
            }
        }
        return out << std::dec <<_inbound.get() << '>';
    }
    else
    {
        return out << '<' << _name << ':' << std::dec <<_inbound.get() << '>';
    }
}

/*#
 * Populates the string stream with the contents of this AVP.
 * ( The AVP of OctetString or UTF8String is printed in Hex form if any
 * non-printable character is found in the string.)
 */
public:

std::stringstream &formatforRE(std::stringstream &out) const
{
    if ((D == OctetStringType) ||( D == UTF8StringType))
    {
        std::string& t = (std::string &)_inbound.get();
        const char *val = t.c_str();
        out << "(" << _name << " \"";
        int len = t.length();
        for (int i=0; i<len; i++)
        {
            if (!isprint(val[i]))
            {
                for ( int j =0; j<len;j++)
                {
                    out<<"0x"<<std::hex<<(int)val[j]<<std::dec;
                    if (j != len-1)
                    {
                        out<<",";
                    }
                }
                out << std::dec <<"\")";
                return out;
            }
        }
		out << std::dec <<_inbound.get() << "\")" ;
		
        return out;
    }
    else
    {
    	out << "(" << _name << " \"" << std::dec <<_inbound.get() << "\")";
        return out;
    }

}

std::stringstream &formatforRE(std::stringstream & out,const char *parent) const
{
    if ((D == OctetStringType) ||( D == UTF8StringType))
    {
        std::string& t = (std::string &)_inbound.get();
        const char *val = t.c_str();
        out << "(" << parent << "." << _name << " \"";
        int len = t.length();
        for (int i=0; i<len; i++)
        {
            if (!isprint(val[i]))
            {
                for ( int j =0; j<len;j++)
                {
                    out<<"0x"<<std::hex<<(int)val[j]<<std::dec;
                    if (j != len-1)
                    {
                        out<<",";
                    }
                }
                out << std::dec <<"\")";
                return out;
            }
        }
		out << std::dec <<_inbound.get() << "\")" ;
		
        return out;
    }
    else
    {
    	out << "(" << parent << "." << _name << " \"" << std::dec <<_inbound.get() << "\")";
        return out;
    }
}

    virtual int Decode(unsigned char*& buff, unsigned int size, DiaHeader& hdr)
    {
        return _inbound.Decode(buff, size);
    }
public:
    virtual int Encode(String& str)
    {
        return _inbound.Encode(str, _name);
    }
private:
    const AttributeName &_name;
    mutable DerivedAVPImpl<T, D> *_managed;
     DerivedAVPImpl<T, D> &_inbound;
};

/**
 * Both Commands and Grouped AVPs are AVP containers. This base class is to capture the common interface.
 */
class AVPContainer {

public:
    AVPContainer(const AVPContainer &);
    AVPContainer() {}

    virtual ~AVPContainer() {}

    /**
     * Adds an AVP.
     *
     * The caller must ensure that this operation is in compliance with the RFC.
     *
     * @param single - whether this AVP allows single or multiple instances.
     */
   
    /**
     * The return type of this function is changed from void to
     * const AVP& to facilitate addAVP.
     */  
    virtual const AVP& add(const AttributeName &name, const AVP &value, bool single = false) = 0;
    
    /** 
     * Two overladed pure virtual functions added for removal of 
     * of AVP.
     */ 
    /*.implementation:public,AVPContainerDerived
     ****************************************************************************
     *  Purpose: This function removes all the AVPs in  entry from the container.
     *           It frees the memory associated with each AVP.
     *
     *  Input Parameters:
     *           const reference to AttributeName Object.
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
    virtual int  remove(const AttributeName &name) = 0;

    /*.implementation:public,AVPContainerDerived
     ****************************************************************************
     *  Purpose: This function removes particular AVP in entry from the container.
     *           It frees the memory associated with that AVP. It checks if it is
     *           last instance than removes the entire entry list.
     *  Input Parameters:
     *           const reference to AttributeName and const reference to AVP
     *           Objects.
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
    virtual int  remove(const AttributeName &name, const AVP& avp) = 0;

    /**
     * Counts number of values with the given attribute name.
     *
     * The caller must ensure that this operation is in compliance with the RFC.
     */
    virtual int count(const AttributeName &name) const = 0;

    /**
     * Tests whether a value with the given attribute name exists.
     *
     * The caller must ensure that this operation is in compliance with the RFC.
     */
    virtual bool contains(const AttributeName &name) const = 0;

    /**
     * Counts number of values with the given attribute name in the "Any AVP" list.
     *
     * The caller must ensure that this operation is in compliance with the RFC.
     */
    virtual int countExtra(const AttributeName &name) const = 0;

    /**
     * Tests whether a value with the given attribute name exists in the "Any AVP" list.
     *
     * The caller must ensure that this operation is in compliance with the RFC.
     */
    virtual bool containsExtra(const AttributeName &name) const = 0;

    /**
     * Tests whether a value with exists in the AVP List at the given particular index.
     * Added due to ticket 2080 by Bridgewater.
     * The caller must ensure that this operation is in compliance with the RFC.
     */
    virtual bool containsExtra(unsigned int index) const = 0;


    /**
     * Gets an AVP with the given attribute name and index.
     *
     * @throw NoSuchAttributeException.
     */
    virtual const AVP &get(const AttributeName &name, unsigned index) const = 0;

    /**
     * Gets an AVP with the given attribute name and index in the "Any AVP" list.
     *
     * @throw NoSuchAttributeException.
     */
    virtual const AVP &getExtra(const AttributeName &name, unsigned index) const = 0;

    /*#
     * Prints all "any" AVPs in the message.
     */
    virtual const std::ostream &printExtras(std::ostream &) const = 0;
    /*#
     * similar to get function and no exception is thrown here
     */
    virtual const AVP* getPtr(const AttributeName &name, unsigned index) const
    {
       return NULL;
    }
    /**
     * The VendorId is added as the default  argument 
     */
    virtual int getAvpValue(unsigned int avpCode, void* val, 
                            ValueDiscriminator D, 
                            unsigned int vendorId=0)const =0;

    /**
     * Generic AVP Access API, index is added as the default  argument 
     */
    virtual int getAvpValue(unsigned int avpCode,unsigned int index, void* val, 
                            ValueDiscriminator D, 
                            unsigned int vendorId=0)const =0;

	virtual int getAvpCount(unsigned int avpCode, unsigned int venId=0) = 0;

    /**
     * Two Overloaded Pure virtual functions for the addition of AVPs
     */
    virtual const AVP&  addAVP(const char* name,unsigned int vendorId, 
                               void* val, bool single, ValueDiscriminator D)=0;

    virtual const AVP&  addAVP(int attrCode, unsigned int vendorId, 
                               void* val, bool single, ValueDiscriminator D)=0;
   
    /**
     * Two Overloaded Pure virtual functions for the removal of AVPs
     */ 
    virtual int removeAVP(const char* name, unsigned int vendorId)=0;
    virtual int removeAVP(int attrCode, unsigned int vendorId)=0;

};


class GroupedAVP: public AVP {
public:
    GroupedAVP(const GroupedAVP & avp):_name(avp._name),
    _managed(avp._managed->createCopy()), _inbound(*_managed)
    {}

public:
    virtual ~GroupedAVP() {

        if (_managed != 0) {
#ifdef DEBUG
#ifdef DEBUG_VAL
            std::cout << "GroupedAVP{" << _name << "}: releasing GroupedAVPImpl @ 0x"
                      << std::hex << (unsigned long)_managed << std::dec << std::endl;
#endif
#endif
            GroupedAVPImpl::release(_managed);
        }
    }

    virtual const AttributeName &name() const {
        return _name;
    }

    /*#
     * Returns the internal AVP container list for reading.
     */
    virtual const AVPContainer &getContainer() const {
        return _inbound.getContainer();
    }

    /*#
     * Returns the internal AVP container list for update.
     */
    virtual AVPContainer &getContainer() {
        return _inbound.getContainer();
    }

    const AVPImpl &getImpl() const {
        return _inbound;
    }

    int getAvpValue(unsigned int avpCode, void* val, ValueDiscriminator D, unsigned int venId=0)
    {
        return getContainer().getAvpValue(avpCode, val, D, venId);
    }

	//API for Generic AVP Access to multiple Occurance AVP.
    int getAvpValue(unsigned int avpCode,unsigned int index, void* val, ValueDiscriminator D, unsigned int venId=0)
    {
        return getContainer().getAvpValue(avpCode, index, val, D, venId);
    }

	int getAvpCount(unsigned int avpCode, unsigned int venId=0)
	{
		return getContainer().getAvpCount(avpCode, venId);
	}

    /*.implementation:inline,public, GroupedAVP
     ****************************************************************************
     *  Purpose: This function adds AVP in Grouped inside the container.
     *  Input Parameters:
     *           reference to AVP - reference of object populated by application.
     *           single/Multiple - Boolean value to determine whether it is single
     *                             or multiple.( true = single, false = Multiple)
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value: returns const reference to AVP - reference of actual object
     *                stored in the Container of the GroupedAVP.
     *  Notes:
     *
     *  See Also:
     ****************************************************************************/
    const AVP&  addAVP(AVP& avp, bool single)
    {
        return (getContainer().add(avp.name(), avp, single));
    }

    /*.implementation:inline,public,GroupedAVP
     ****************************************************************************
     *  Purpose: This function removes particular AVP in entry from the container.
     *           It frees the memory associated with that AVP. It checks if it is
     *           last instance than removes the entire entry list.
     *  Input Parameters:
     *           const reference to AVP Object - reference returned by
     *                                           addAVP function.
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
    int removeAVP(const AVP& avp)
    {
        return (getContainer().remove(avp.name(),avp));
    }
    /**
     * May have performance issues as compared to other API
     */
    /**
     * Two Overloaded funcitions for addition
     * of AVPs
     */
    const AVP& addAVP(const char* name,unsigned int vendorId, void* val, bool single, ValueDiscriminator D)
    {
        return getContainer().addAVP(name,vendorId, val, single, D);
    }
    /**
     * The return value is changed from int to const AVP&.
     */
    const AVP& addAVP(int attrCode, unsigned int vendorId, void* val, bool single, ValueDiscriminator D)
    {
        return getContainer().addAVP(attrCode, vendorId, val, single, D);
    }

    /**
     * Two overloaded functions to remove the AVPs.
     */
    int removeAVP(const char* name ,unsigned int vendorId)
    {
        return getContainer().removeAVP(name,vendorId);
    }
    int removeAVP(int attrCode, unsigned int vendorId)
    {
        return getContainer().removeAVP(attrCode, vendorId);
    }

    virtual int Decode(unsigned char*& inputBuff, unsigned int size, DiaHeader& hdr)
    {
       return _inbound.Decode(inputBuff, size, hdr);
    }
protected:

    /*#
     * Constructs an empty grouped AVP.
     */
    GroupedAVP(const AttributeName &name)
    : _name(name)
      ,_managed(GroupedAVPImpl::acquire(&name)), _inbound(*_managed) 
    {
#ifdef DEBUG
#ifdef DEBUG_VAL
        std::cout << "GroupedAVP{" << _name << "}: acquired GroupedAVPImpl @ 0x"
                  << std::hex << (unsigned long)_managed << std::dec << std::endl;
#endif
#endif
    }

/*    const AVPImpl &getImpl() const {
        return _inbound;
    }
*/

    /*#
     * Constructs a grouped AVP from a container entry.
     */
    GroupedAVP(const AttributeName &name, const AVPImpl *impl)
    : _name(name)
    ,_managed(GroupedAVPImpl::acquire(&name)),_inbound(*_managed)
    {}


    std::ostream &printHeader(std::ostream &out) const {
        return out << '<' << _name << '>';
    }

public:
    virtual int Encode(String& str)
    {
       return _inbound.Encode(str);
    }
	/*
	 * For Rule Engine:
	 *  The function formats the Grouped AVP into CLIPS facts format.
	 */
    const char *getHeaderforRE() const {
        return _name;
    }
	
	/*
	 * For Rule Engine:
	 *  The function formats the Grouped AVP into CLIPS facts format.
	 */
	std::stringstream &formatforRE(std::stringstream &out) const
	{
		return out;
	}

	std::stringstream &formatforRE(std::stringstream &out,const char* parent) const
	{
		return out;
	}

protected:
    int GetType() const { return GroupedType;}

private:

    AVP* createCopy() const
    {
        if(_inbound.validate() == false)
        {
           throw CodecException(__FILE__, __LINE__,"Mandatory AVP Missing");
        }
        return new GroupedAVP(*this);
    }

    std::ostream &print(std::ostream &out) const 
    { 
        printHeader(out);
        out << '{' << std::endl;
        _inbound.print(out);
        out << '}' << std::endl;
        return out;
    }

protected:
    const AttributeName &_name;
    mutable GroupedAVPImpl *_managed;
     GroupedAVPImpl &_inbound;
};

//new definations
class OctetStringAvp : public DerivedAVP<OctetString, OctetStringType>
{
public:
      OctetStringAvp(const AttributeName &name, const AVPImpl *impl):
          DerivedAVP<OctetString, OctetStringType>(name, impl){}

      OctetStringAvp(const AttributeName &name, const OctetString& value):
          DerivedAVP<OctetString, OctetStringType>(name, value){}

      OctetStringAvp (unsigned int avpCode, unsigned int venId, 
                      const OctetString& value);

};

class Integer32Avp : public DerivedAVP<Integer32, Integer32Type>
{
public:
      Integer32Avp(const AttributeName &name, const AVPImpl *impl):
          DerivedAVP<Integer32, Integer32Type>(name, impl){}

      Integer32Avp(const AttributeName &name, const Integer32& value):
          DerivedAVP<Integer32, Integer32Type>(name, value){}

      Integer32Avp(unsigned int avpCode, unsigned int venId,
                   const Integer32& value);
};

class Integer64Avp : public DerivedAVP<Integer64, Integer64Type>
{
public:
      Integer64Avp(const AttributeName &name, const AVPImpl *impl):
          DerivedAVP<Integer64, Integer64Type>(name, impl){}

      Integer64Avp(const AttributeName &name, const Integer64& value):
          DerivedAVP<Integer64, Integer64Type>(name, value){}

      Integer64Avp(unsigned int avpCode, unsigned int venId,
                   const Integer64& value);
};

class Unsigned32Avp : public DerivedAVP<Unsigned32, Unsigned32Type>
{
public:
      Unsigned32Avp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<Unsigned32, Unsigned32Type>(name, impl){}

      Unsigned32Avp(const AttributeName &name, const Unsigned32& value):
         DerivedAVP<Unsigned32, Unsigned32Type>(name, value){}

      Unsigned32Avp(unsigned int avpCode, unsigned int venId,
                    const Unsigned32& value);
};

class Unsigned64Avp : public DerivedAVP<Unsigned64, Unsigned64Type>
{
public:
      Unsigned64Avp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<Unsigned64, Unsigned64Type>(name, impl){}

      Unsigned64Avp(const AttributeName &name, Unsigned64& value):
         DerivedAVP<Unsigned64, Unsigned64Type>(name, value){}

      Unsigned64Avp(unsigned int avpCode, unsigned int venId,
                    const Unsigned64& value);
};

/**
 * Added new class for Float32 and constructors to it
 */
class Float32Avp : public DerivedAVP<Float32, Float32Type>
{
    public:
        Float32Avp(const AttributeName &name, const AVPImpl *impl):
            DerivedAVP<Float32, Float32Type>(name, impl){}

        Float32Avp(const AttributeName &name, const Float32& value):
            DerivedAVP<Float32, Float32Type>(name, value){}

        Float32Avp(unsigned int avpCode, unsigned int venId,
                const Float32& value);
};

/**
 * Added new class for Float64 and constructors to it
 */
class Float64Avp : public DerivedAVP<Float64, Float64Type>
{
    public:
        Float64Avp(const AttributeName &name, const AVPImpl *impl):
            DerivedAVP<Float64, Float64Type>(name, impl){}

        Float64Avp(const AttributeName &name, Float64& value):
            DerivedAVP<Float64, Float64Type>(name, value){}

        Float64Avp(unsigned int avpCode, unsigned int venId,
                const Float64& value);
};


class AddressAvp : public DerivedAVP<Address, AddressType>
{
public:
      AddressAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<Address, AddressType>(name, impl){}

      AddressAvp(const AttributeName &name, const Address& value):
         DerivedAVP<Address, AddressType>(name, value){}

      AddressAvp(unsigned int avpCode, unsigned int venId,
                 const Address& value);
};

class TimeAvp : public DerivedAVP<Time, TimeType>
{
public:
      TimeAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<Time, TimeType>(name, impl){}

      TimeAvp(const AttributeName &name, const Time& value):
         DerivedAVP<Time, TimeType>(name, value){}

      TimeAvp(unsigned int avpCode, unsigned int venId,
              const Time& value);
};

class UTF8StringAvp : public DerivedAVP<UTF8String, UTF8StringType>
{
public:
      UTF8StringAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<UTF8String, UTF8StringType>(name, impl){}

      UTF8StringAvp(const AttributeName &name, const UTF8String& value):
         DerivedAVP<UTF8String, UTF8StringType>(name, value){}

      UTF8StringAvp(unsigned int avpCode, unsigned int venId,
                    const UTF8String& value);
};

class IdentityAvp : public DerivedAVP<Identity, IdentityType>
{
public:
      IdentityAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<Identity, IdentityType>(name, impl){}

      IdentityAvp(const AttributeName &name, const Identity& value):
         DerivedAVP<Identity, IdentityType>(name, value){}

      IdentityAvp(unsigned int avpCode, unsigned int venId,
                  const Identity& value);
};

class URIAvp  : public DerivedAVP<URI, URIType>
{
public:
      URIAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<URI, URIType>(name, impl){}

      URIAvp(const AttributeName &name, const URI& value):
         DerivedAVP<URI, URIType>(name, value){}

      URIAvp(unsigned int avpCode, unsigned int venId,
             const URI& value);
};

class IPFilterRuleAvp : public DerivedAVP<IPFilterRule, IPFilterRuleType>
{
public:
      IPFilterRuleAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<IPFilterRule, IPFilterRuleType>(name, impl){}

      IPFilterRuleAvp(const AttributeName &name, const IPFilterRule& value):
         DerivedAVP<IPFilterRule, IPFilterRuleType>(name, value){}

      IPFilterRuleAvp(unsigned int avpCode, unsigned int venId,
                      const IPFilterRule& value);
};

class EnumeratedAvp : public DerivedAVP<Enumerated, EnumeratedType>
{
public:
      EnumeratedAvp(const AttributeName &name, const AVPImpl *impl):
         DerivedAVP<Enumerated, EnumeratedType>(name, impl){}

      EnumeratedAvp(const AttributeName &name, const Enumerated& value):
         DerivedAVP<Enumerated, EnumeratedType>(name, value){}

      EnumeratedAvp(unsigned int avpCode, unsigned int venId,
                    const Enumerated& value);
};

class DerivedGroupedAVP : public GroupedAVP
{
public:
      DerivedGroupedAVP(const AttributeName &name, const AVPImpl *impl):
           GroupedAVP(name, impl){}

      DerivedGroupedAVP(unsigned int avpCode, unsigned int venId);
      //added for new API- Tushar 
      DerivedGroupedAVP():GroupedAVP(AttributeName::AVP){}

      void add(const AVP& avp)
      {
         getContainer().add(avp.name(), avp, false);
      }
      // added for new API- Tushar
      virtual const AttributeName &name() const;

};

class PayloadAVP : public GroupedAVP
{
public:
      PayloadAVP();
      void add(const AVP& avp)
      {
         getContainer().add(avp.name(), avp, false);
      }
      int Decode(unsigned char*& inputBuff, unsigned int size);
      int Encode(String& str);
      int countExtra();
      const AVP& getExtra(unsigned int index);
};

}

#endif//_DIAMETER_AVP_H_
