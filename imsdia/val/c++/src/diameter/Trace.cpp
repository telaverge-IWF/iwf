/********************************-*-CPP-*-***********************************
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
 * LOG: $Log: Trace.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:53:10  kamakshilk
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.4  2006/08/13 09:53:09  brianhu
 * LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
 * LOG:
 * LOG: Revision 1.3  2006/06/21 10:22:24  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.2  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Trace.cpp,v 3.1 2008/03/31 10:33:29 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: Trace.cpp,v 3.1 2008/03/31 10:33:29 nvijikumar Exp $"

#include <diameter/Trace.h>

#ifdef DEBUG
#ifdef DEBUG_VERBOSE

namespace diameter {

Trace Trace::null;
Trace::trace_table Trace::_streams;

void Trace::set(const std::string &subsystem, std::ostream &stream) {
    trace_table::iterator it = _streams.find(subsystem);
    if (it == _streams.end()) {
        _streams.insert(trace_table::value_type(subsystem, Trace(stream)));
    } else {
        it->second = Trace(stream);
    }
}

Trace &Trace::log(const std::string &subsystem) {
    trace_table::iterator it = _streams.find(subsystem);
    if (it == _streams.end()) {
        return Trace::null;
    } else {
        (*it->second._stream) << "-- ";
        return it->second;
    }
}


}

#endif//DEBUG_VERBOSE
#endif//DEBUG
