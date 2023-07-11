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
 * LOG: $Log: Command.cpp,v $
 * LOG: Revision 3.1.30.4  2012/10/01 09:01:09  rsanjay
 * LOG:  opendiameter code removal changes:bugzilla-id 300
 * LOG:
 * LOG: Revision 3.1.30.3  2012/08/06 16:03:55  cprem
 * LOG: Modified function comments.
 * LOG:
 * LOG: Revision 3.1.30.2  2012/07/31 07:57:58  cprem
 * LOG: Fixed indentation. Also added dummy implementation for formDiameterMessageForRuleEngine.
 * LOG:
 * LOG: Revision 3.1.30.1  2012/07/26 11:49:00  cprem
 * LOG: A new function for printHeaderForRuleEngine which would format header in Rule Engine format.The fact format is for CLIPS Rule Engine.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.7  2007/01/04 11:01:05  nvijikumar
 * LOG: Provided Accounting related APIs for ACR.
 * LOG:
 * LOG: Revision 2.6  2006/11/14 08:59:57  tpanda
 * LOG: fix for crash while getting sessionIndex for dcca
 * LOG:
 * LOG: Revision 2.5  2006/11/13 14:44:53  tpanda
 * LOG: clientId,sessionIndex moved to implementation object
 * LOG:
 * LOG: Revision 2.4  2006/11/09 14:10:25  tpanda
 * LOG: clientId added for IDS
 * LOG:
 * LOG: Revision 2.3  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:53:10  kamakshilk
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.3  2006/10/05 05:54:02  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 2.2  2006/09/19 06:04:51  tpanda
 * LOG: Val is splitted. Encoding/Decoding functionality moved to vendor
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.5  2006/08/13 09:53:09  brianhu
 * LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
 * LOG:
 * LOG: Revision 1.4  2006/06/21 10:22:24  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.3  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Command.cpp,v 3.1.30.4 2012/10/01 09:01:09 rsanjay Exp $
 ****************************************************************************/
#ident "$Id: Command.cpp,v 3.1.30.4 2012/10/01 09:01:09 rsanjay Exp $"

#include <diameter/Command.h>

namespace diameter {


Command::Command(bool request, bool proxyable, bool error, bool retrans, CommandCode code, ApplicationId appId):
_managed(CommandImpl::acquire(request, proxyable, error, retrans, code, appId)), _inbound(*_managed) {
    DBG_LOG((VALCPP) << "Command: acquired CommandImpl @ 0x" << std::hex << _managed << std::dec);
}

std::ostream &Command::printHeader(std::ostream &out) const {
    return out << '<' << getCommandCode() << ", [r:" << isRequest()
               << ",p:" << isProxyable()
               << ",e:" << isError()
               << ",t:" << isRetransmit()
               << "], " << getApplicationId() << '>';
}

/*
 *  Added for Rule Engine
 *  This function format's the command header in a format that can be fed to
 *  CLIPS Rule Engine.
 */
std::stringstream &Command::printHeaderForRuleEngine(std::stringstream &out) const {
	out << "(Command-Code " << getCommandCode() << ")";
	out << "(Request " << isRequest() << ")";
	out << "(Proxiable " << isProxyable() << ")";
	out << "(Error " << isError() << ")";
	out << "(PotentiallyRetransmitted " << isRetransmit() << ")";
	out << "(Application-ID " << getApplicationId() << ")";
    return out;
}

/*
 * Added as part of review comments.
 */
std::stringstream &Command::formDiameterMessageForRuleEngine(std::stringstream &out) const {
	return out;
}


void
Command::setSessionIndex(unsigned int index)
{
   CommandImpl& impl = (CommandImpl&)_inbound;
   unsigned int& sessIndex = impl.getSessionIndex();
   sessIndex = index;
}

unsigned int
Command::getSessionIndex()
{
   CommandImpl& impl = (CommandImpl&)_inbound;
   return impl.getSessionIndex();
}

void
Command::setStorageSpaceAvailable(bool flag)
{
   CommandImpl& impl = (CommandImpl&)_inbound;
   bool& storageSpaceAvailable = impl.IsStorageSpaceAvailable();
   storageSpaceAvailable = flag;
}

bool
Command::IsStorageSpaceAvailable()
{
   CommandImpl& impl = (CommandImpl&)_inbound;
   return impl.IsStorageSpaceAvailable();
}

void
Command::setLastRecordInStorage(bool flag)
{
   CommandImpl& impl = (CommandImpl&)_inbound;
   bool& lastRecordInStorage = impl.IsLastRecordInStorage();
   lastRecordInStorage = flag;
}

bool
Command::IsLastRecordInStorage()
{
   CommandImpl& impl = (CommandImpl&)_inbound;
   return impl.IsLastRecordInStorage();
}


}
