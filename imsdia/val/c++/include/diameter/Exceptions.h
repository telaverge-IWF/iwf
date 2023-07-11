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
 * LOG: $Log: Exceptions.h,v $
 * LOG: Revision 3.5.6.1.26.1.12.1  2014/08/26 10:27:38  pramana
 * LOG: Compilation warning fixes in imsdia
 * LOG:
 * LOG: Revision 3.5.6.1.26.1  2013/02/27 08:49:07  jvikram
 * LOG: Warnings raised by Coverity have been fixed
 * LOG:
 * LOG: Revision 3.5.6.1  2012/10/01 09:01:06  rsanjay
 * LOG:  opendiameter code removal changes:bugzilla-id 300
 * LOG:
 * LOG: Revision 3.5  2010/09/20 06:32:49  nvijikumar
 * LOG: STLPORT4 support
 * LOG:
 * LOG: Revision 3.4  2010/08/19 11:23:56  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported
 * LOG:
 * LOG: Revision 3.3.2.1  2010/06/17 04:47:47  rajeshak
 * LOG: Fix for HelpDesk Ticket-2383
 * LOG:
 * LOG: Revision 3.3  2009/12/19 08:44:02  sureshj
 * LOG: OH , OR and SessionID provided to Application when CodecExceptionToApp
 * LOG: is thrown when mandatory AVPs missing.
 * LOG:
 * LOG: Revision 3.2  2009/12/08 06:44:21  sureshj
 * LOG: Missing AVP only provides print of offending AVP, but no
 * LOG: callback to app. Motorola ticket 2278.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.3.10.1  2007/05/30 13:39:07  nvijikumar
 * LOG: Enhanced CodecException to maintain Error Code.
 * LOG:
 * LOG: Revision 2.3  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:50:43  tpanda
 * LOG: Merging the itsval with val
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
 * ID: $Id: Exceptions.h,v 3.5.6.1.26.1.12.1 2014/08/26 10:27:38 pramana Exp $
 ****************************************************************************/
#ident "$Id: Exceptions.h,v 3.5.6.1.26.1.12.1 2014/08/26 10:27:38 pramana Exp $"

#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

/*
 * Exceptions
 */
#include <exception>
#include <string>
#include <vector>
#include <iterator>
#include <stdio.h>

namespace diameter {

class WrongCommandTypeException: public std::exception {
public:
    explicit WrongCommandTypeException(const char *f, int l, const char *m)
    : _filename(f), _linenumber(l), _what(m)
    {}

    ~WrongCommandTypeException() throw() {}

    /**
     * Returns a description about this exception.
     */
    virtual const char* what() const throw() { return _what.c_str(); }

    /**
     * Returns the name of this exception class.
     */
    const char *name() const throw() { return "WrongCommandTypeException"; }

    /**
     * Returns the file name of the source code that throws this exception.
     */
    const char *file() const throw() { return _filename; }

    /**
     * Returns the line number of the source code that throws this exception.
     */
    int line() const throw() { return _linenumber; }

private:
    const char *_filename;
    int _linenumber;
    std::string _what;
};

class NoSuchAttributeException: public std::exception {
public:
    explicit NoSuchAttributeException(const char *f, int l, const char *m, int index)
    : _filename(f), _linenumber(l), _what(m) {
        _what += ", ";
        char temp[10];
        //index refers to avpCode
        //Correcting calling risky function
        snprintf(temp, 9, "%d", index);
        _what += temp;
    }

    ~NoSuchAttributeException() throw() {}

    /**
     * Returns a description about this exception.
     */
    virtual const char* what() const throw() { return _what.c_str(); }

    /**
     * Returns the name of this exception class.
     */
    const char *name() const throw() { return "NoSuchAttributeException"; }

    /**
     * Returns the file name of the source code that throws this exception.
     */
    const char *file() const throw() { return _filename; }

    /**
     * Returns the line number of the source code that throws this exception.
     */
    int line() const throw() { return _linenumber; }

private:
    const char *_filename;
    int _linenumber;
    std::string _what;
};

class UnknownTypeException: public std::exception {
public:
    explicit UnknownTypeException(const char *f, int l, const char *m)
    : _filename(f), _linenumber(l), _what(m)
    {}

    ~UnknownTypeException() throw() {}

    /**
     * Returns a description about this exception.
     */
    virtual const char* what() const throw() { return _what.c_str(); }

    /**
     * Returns the name of this exception class.
     */
    const char *name() const throw() { return "UnknownTypeException"; }

    /**
     * Returns the file name of the source code that throws this exception.
     */
    const char *file() const throw() { return _filename; }

    /**
     * Returns the line number of the source code that throws this exception.
     */
    int line() const throw() { return _linenumber; }

private:
    const char *_filename;
    int _linenumber;
    std::string _what;
};

class CodecException: public std::exception {
public:
    explicit CodecException(const char *f, int l, const char *m,
                            int errcode = 0, int avpcode = 0)
    : _isGroupedAvp(false), _filename(f), _linenumber(l), _what(m),
       _errcode(errcode), _groupAvpCode(0), _avpCode(avpcode)
    {}

    ~CodecException() throw() {}

    /**
     * Returns a description about this exception.
     */
    virtual const char* what() const throw() { return _what.c_str(); }

    /**
     * Returns the name of this exception class.
     */
    const char *name() const throw() { return "CodecException"; }

    /**
     * Returns the file name of the source code that throws this exception.
     */
    const char *file() const throw() { return _filename; }

    /**
     * Returns the line number of the source code that throws this exception.
     */
    int line() const throw() { return _linenumber; }

    int errcode() const throw() { return _errcode; }

    void SetSessionId(std::string &sid) { _sessionId = sid; }

    void SetOriginHost(std::string &oh) { _origin_host = oh; }

    void SetOriginRealm(std::string &orgRlm) { _origin_realm = orgRlm; }

    const char *originHost() const throw() { return _origin_host.c_str(); }

    const char *originRealm() const throw() { return _origin_realm.c_str(); }

    const char *sessionId() const throw() { return _sessionId.c_str(); }

    bool isGroupedAvpError() { return _isGroupedAvp; }

    void setGroupedAvpError(bool flag) { _isGroupedAvp = flag; }

    unsigned int getGroupedAvpCode() { return _groupAvpCode; }

    void setGroupedAvpCode(unsigned int code) { _groupAvpCode = code; }

    void setAvpCode(unsigned int code) { _avpCode = code; }

    unsigned int getAvpCode() { return _avpCode; }

private:
    bool _isGroupedAvp;
    const char *_filename;
    int _linenumber;
    std::string _what;
    std::string _origin_host;
    std::string _origin_realm;
    std::string _sessionId;

    int _errcode;
    unsigned int _groupAvpCode;
    unsigned int _avpCode;
};


class CodecExceptionToApp: public  std::exception {
public:
    explicit CodecExceptionToApp(const char *f, int l, const char *m,
                                 std::vector<int>& misAvp, int errcode = 0)
    :_isGroupedAvp(false), _filename(f), _linenumber(l), _what(m), 
     _errcode(errcode), _groupAvpCode(0), _cmdCode(0)
    {
        for(unsigned int i=0; i<misAvp.size(); i++)
        {
            _missingAVP.push_back(misAvp[i]);
        }
    }

    explicit CodecExceptionToApp(const char *f, int l, const char *m,
                                 int errcode = 0 )
    :_isGroupedAvp(false), _filename(f), _linenumber(l), _what(m), 
     _errcode(errcode), _groupAvpCode(0), _cmdCode(0)
    {
    }

    ~CodecExceptionToApp() throw() {}

    void SetMissingAvpList(std::vector<int>& misAvp)
    {
        for(unsigned int i=0; i<misAvp.size(); i++)
        {
            _missingAVP.push_back(misAvp[i]);
        }
    }

    void SetMultiOccurrenceAvpList(std::vector<int>& multiAvp)
    {
        for(unsigned int i=0; i<multiAvp.size(); i++)
        {
            _multiOccurAVP.push_back(multiAvp[i]);
        }
    }
 
    void SetSessionId(std::string &sid)
    {
        _sessionId = sid;
    }
 
    void SetOriginHost(std::string &oh)
    {
        _origin_host = oh;
    }
    
    void SetOriginRealm(std::string &orgRlm)
    {
        _origin_realm = orgRlm;
    }
    
    /**
     * Returns a description about this exception.
     */
    virtual const char* what() const throw() { return _what.c_str(); }

    /**
     * Returns the name of this exception class.
     */
    const char *name() const throw() { return "MssingAVPException"; }

    /**
     * Returns the file name of the source code that throws this exception.
     */
    const char *file() const throw() { return _filename; }
    const char *originHost() const throw() { return _origin_host.c_str(); }
    const char *originRealm() const throw() { return _origin_realm.c_str(); }
    const char *sessionId() const throw() { return _sessionId.c_str(); }

    /**
     * Returns the line number of the source code that throws this exception.
     */
    int line() const throw() { return _linenumber; }

    int errcode() const throw() { return _errcode; }

    std::vector<int>  getMissingAVPList()
    {    
        return _missingAVP; 
    }

    std::vector<int>&  getMultiOccurrenceAVPList()
    {
        return _multiOccurAVP;
    }

    bool isGroupedAvpError() { return _isGroupedAvp; }

    void setGroupedAvpError(bool flag) { _isGroupedAvp = flag; }

    int getGroupedAvpCode() { return _groupAvpCode; }

    void setGroupedAvpCode(unsigned int code) { _groupAvpCode = code; }

    void setCmdCode(unsigned int val) { _cmdCode = val; }

    unsigned int getCmdCode() { return _cmdCode; }

private:
    bool _isGroupedAvp;
    const char *_filename;
    int _linenumber;
    std::string _what;
    std::vector<int> _missingAVP;
    std::vector<int> _multiOccurAVP;
    std::string _origin_host;
    std::string _origin_realm;
    std::string _sessionId;
    int _errcode;
    unsigned int _groupAvpCode;
    unsigned int _cmdCode;
};

}

#endif//_EXCEPTIONS_H_
