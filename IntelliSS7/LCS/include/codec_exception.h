//////////////////////////////////-*-h-*-/////////////////////////////////////
//                                                                          //
//     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    //
//             Manufactured in the United States of America.                //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                          //
//   This product and related documentation is protected by copyright and   //
//   distributed under licenses restricting its use, copying, distribution  //
//   and decompilation.  No part of this product or related documentation   //
//   may be reproduced in any form by any means without prior written       //
//   authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                          //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CONTRACT: INTERNAL                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
//   ID: $Id: codec_exception.h,v 1.1.2.2 2010/03/31 05:44:35 rajeshak Exp $
//
//   LOG: $Log: codec_exception.h,v $
//   LOG: Revision 1.1.2.2  2010/03/31 05:44:35  rajeshak
//   LOG: Changed Class name Error to ExceptionError (used in IPR SMLC code).
//   LOG:
//   LOG: Revision 1.1.2.1  2010/03/19 11:41:02  rajeshak
//   LOG: Removing IntelliSS7 dependency from Codec
//   LOG: 
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: codec_exception.h,v 1.1.2.2 2010/03/31 05:44:35 rajeshak Exp $"

#ifndef ITN_EXCEPTIONS_H
#define ITN_EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>

// VC++ pragma: exception specification is not supported yet.
#ifdef _WIN32
#pragma warning(disable : 4290)
#define typename
#endif

/**
 * Class Exception is the base class of various exception classes used by all
 * software components.  This abstract class contains an exception description
 * and the file name and the line number of the source code that throws this
 * exception.
 *
 * This is an abstract class. One should define specific exception classes
 * by deriving from this class.
 *
 * Four methods are provided to extract detail information from an Exception
 * object:
 *
 *        const char *what() returns the description of the exception.
 *
 *        const char *name() returns the name of the exception class.
 *
 *        const char *file() returns the file name of the source code that has
 *                           thrown this exception.
 *
 *        int line()         returns the line number of the source code that
 *                           has thrown this exception.
 *
 * Three macros are defined to facilitate exception handling.
 *
 *        ITN_THROW(Class, what) throws an exception of the given class,
 *                               providing the source file name and line
 *                               number implicitly.
 *
 *        ITN_CHECK(cond, Class) checks the given condition "cond", and throws
 *                               an exception of the given class if the
 *                               condition does not hold, providing the
 *                               description, source file name, and line number
 *                               implicitly.
 *
 *        ITN_DUMPX(stream, x)   dumps a caught exception to a trace stream.
 */
class Exception : public std::exception
{
public:
    explicit Exception(const char *f, int l, const char *i = (char *)0)
    : _filename(f), _linenumber(l), _what(i)
    {
    }

    ~Exception() throw() {}

    virtual const char* what() const throw()
    {
        return _what.c_str();
    }

    /**
     * Returns the name of this exception class.
     */
    virtual const char *name() const throw() = 0;

    /**
     * Returns the file name of the source code that throws this exception.
     */
    const char *file() const
    {
        return _filename;
    }

    /**
     * Returns the line number of the source code that throws this exception.
     */
    int line() const
    {
        return _linenumber;
    }

protected:
    const char *_filename;
    int _linenumber;
    std::string _what;
};

/**
 * An Error represents a severe runtime error condition that the application
 * should treat differently from other exceptions. This class defines a separate
 * exception hierarchy other than Exception.
 */
class ExceptionError : public std::exception
{
public:
    explicit ExceptionError(const char *f, int l, const char *i = (char *)0)
    : _filename(f), _linenumber(l), _what(i)
    {
    }

    ~ExceptionError() throw() {}

    virtual const char* what() const throw()
    {
        return _what.c_str();
    }

    /**
     * Returns the name of this error class.
     */
    virtual const char *name() const throw() = 0;

    /**
     * Returns the file name of the source code that throws this error.
     */
    const char *file() const
    {
        return _filename;
    }

    /**
     * Returns the line number of the source code that throws this error.
     */
    int line() const
    {
        return _linenumber;
    }

protected:
    const char *_filename;
    int _linenumber;
    std::string _what;
};


/*
 * Throws an exception of the given type with the given description
 */
#define ITN_THROW(ExceptionClass, info) \
    throw ExceptionClass(__FILE__, __LINE__, info);

/*
 * Checks condition, throws an exception of the given type if fail.
 */
#define ITN_CHECK(cond, ExceptionClass) \
    if (!(cond)) ITN_THROW(ExceptionClass, "Failed to satisfy (" #cond ")");
   
#define _ITN_X_PARAMS(x) \
    "%s: %s\n\tthrown by %s, %d\n\tcaught by " __FILE__ ", %d", \
    x.name(), x.what(), x.file(), x.line(), __LINE__

/*
 * Reports a caught exception by dumping it to an output stream.
 */
#define ITN_DUMPX(out, x) \
    out.put(_ITN_X_PARAMS(x));

inline std::ostream &operator<<(std::ostream &out, const Exception &x)
{
    out << x.name() << ":\"" << x.what()
        << "\" from (" << x.file() << ", " << x.line() << ')';
    return out;
}

/**
 * Class RuntimeException is a subclass of Exception. This class serves to
 * further partition the exception space into various categories.
 *
 * This is an abstract class. One should define "runtime" exception classes
 * by deriving from this class.
 */
struct RuntimeException : public Exception
{
    RuntimeException(const char *f, int l, const char *i = (char *)0)
    : Exception(f, l, i) {}
};


/*
* This is a convenience macro for subclassing exceptions.
*/
#define ITN_DEFINE_EXCEPTION(ExceptionName, ExceptionClass) \
class ExceptionName : public ExceptionClass \
{ \
public: \
    explicit ExceptionName(const char *f, int l, const char *i = (char *)0) \
    : ExceptionClass(f, l, i) {} \
    const char *name() const throw() { return #ExceptionName; } \
}


/*
* Commonly Used Error Classes
* ---------------------------
*/
ITN_DEFINE_EXCEPTION(RuntimeError, ExceptionError);
ITN_DEFINE_EXCEPTION(AssertionFailedException, ExceptionError);

/*
* Commonly Used Exception Classes
* -------------------------------
*/
ITN_DEFINE_EXCEPTION(UnknownException, Exception);


ITN_DEFINE_EXCEPTION(AccessDeniedException, RuntimeException);
ITN_DEFINE_EXCEPTION(BufferOverflowException, RuntimeException);
ITN_DEFINE_EXCEPTION(BufferUnderflowException, RuntimeException);
ITN_DEFINE_EXCEPTION(IllegalArgumentException, RuntimeException);
ITN_DEFINE_EXCEPTION(IllegalStateException, RuntimeException);
ITN_DEFINE_EXCEPTION(IndexOutOfBoundsException, RuntimeException);
ITN_DEFINE_EXCEPTION(InvalidInstanceException, RuntimeException);
ITN_DEFINE_EXCEPTION(MissingParameterException, Exception);
ITN_DEFINE_EXCEPTION(NoSuchElementException, RuntimeException);
ITN_DEFINE_EXCEPTION(NullPointerException, RuntimeException);
ITN_DEFINE_EXCEPTION(NumberFormatException, RuntimeException);
ITN_DEFINE_EXCEPTION(OutOfResourceException, RuntimeException);
ITN_DEFINE_EXCEPTION(StackFrameException, RuntimeException);
ITN_DEFINE_EXCEPTION(StackOverflowException, RuntimeException);
ITN_DEFINE_EXCEPTION(StackUnderflowException, RuntimeException);

/*
* Network Protocol Related Exception Classes
* ------------------------------------------
*/

ITN_DEFINE_EXCEPTION(ProtocolException, RuntimeException);

ITN_DEFINE_EXCEPTION(EncodeException, ProtocolException);
ITN_DEFINE_EXCEPTION(DecodeException, ProtocolException);
ITN_DEFINE_EXCEPTION(InvalidData,Exception);


#endif//ITN_EXCEPTIONS_H
