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
 * LOG: $Log: Trace.h,v $
 * LOG: Revision 3.2  2010/09/20 06:32:49  nvijikumar
 * LOG: STLPORT4 support
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
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
 * LOG: Revision 1.7  2006/08/13 09:53:09  brianhu
 * LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
 * LOG:
 * LOG: Revision 1.6  2006/08/09 04:32:10  brianhu
 * LOG: Added a required null pointer check.
 * LOG:
 * LOG: Revision 1.5  2006/08/09 04:16:32  yranade
 * LOG: Updated for Sun CC 5.7
 * LOG:
 * LOG: Revision 1.4  2006/06/21 10:26:35  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.3  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Trace.h,v 3.2 2010/09/20 06:32:49 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: Trace.h,v 3.2 2010/09/20 06:32:49 nvijikumar Exp $"

#ifndef _TRACE_H_
#define _TRACE_H_

// Note: This file defines a simple debugging facility that is controlled by
// preprocessor definitions; This facility is not meant for production
// logging

#ifdef DEBUG

#ifdef DEBUG_VERBOSE

#include <iostream>
#include <string>
#include <map>
#include <iterator>

namespace diameter {

class Trace {
    typedef std::map<std::string, Trace> trace_table;
    friend Trace &endt(Trace &);

    std::ostream *_stream;

public:
    Trace(): _stream(0) {}

    Trace(std::ostream &stream): _stream(&stream) {}

    ~Trace() {
        if (_stream != 0) {
            _stream->flush();
        }
    }

    template <class T>
    Trace &operator<<(const T &ref) {
        if (_stream != 0) {
            (*_stream) << ref;
        }
        return *this;
    }

    Trace &operator<<(Trace &(*manip)(Trace &)) {
        return (*manip)(*this);
    }

    Trace &operator<<(std::ios_base &(*manip)(std::ios_base &)) {
        if (_stream != 0) (*manip)(*_stream);
        return *this;
    }

    static void set(const std::string &subsystem, std::ostream &stream);

    static Trace &log(const std::string &subsystem);

private:
    static Trace null;
    static trace_table _streams;
};

/**
 * End-of-trace manipulator
 */
inline Trace &endt(Trace &trace) {
    if (trace._stream != 0) {
        (*trace._stream) << " ...\n";
    }
    return trace;
}

}

#define DBG_LOG(x)    diameter::Trace::log x << diameter::endt
#define DBG_SET(x, s) diameter::Trace::set(x, s)

#else //!DEBUG_VERBOSE

#define DBG_LOG(x)
#define DBG_SET(x, s)

#endif//DEBUG_VERBOSE

#else //!DEBUG

#define DBG_LOG(x)
#define DBG_SET(x, s)

#endif//DEBUG

#endif//_TRACE_H_
