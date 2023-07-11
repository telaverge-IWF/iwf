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
 * LOG: $Log: Command.h,v $
 * LOG: Revision 3.2.30.4  2012/10/01 09:01:05  rsanjay
 * LOG:  opendiameter code removal changes:bugzilla-id 300
 * LOG:
 * LOG: Revision 3.2.30.3  2012/09/06 11:30:45  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 Sept6.
 * LOG:
 * LOG: Revision 3.2.30.2.2.1  2012/08/22 09:38:55  cprem
 * LOG: Added a new constructor for GenericCommand which takes in CommandImplementation as argument.
 * LOG: This is done for DTF.
 * LOG:
 * LOG: Revision 3.2.30.2  2012/08/06 16:03:29  cprem
 * LOG: Changed the declaration of function formDiameterMessageForRuleEngine to virtual.
 * LOG:
 * LOG: Revision 3.2.30.1  2012/07/26 11:47:30  cprem
 * LOG: Added function formDiameterMessageForRuleEngine to format the whole Diameter Message that can be fed to Rule Engine as facts. The fact format is for CLIPS Rule Engine. A new function definition for printHeaderForRuleEngine which would format header in Rule Engine format.
 * LOG:
 * LOG: Revision 3.2  2008/04/07 18:22:37  hbhatnagar
 * LOG: Fix for issue 699 in whizible. Handled _managed pointer properly to
 * LOG: resolve the core dumps.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.12  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.10.4.1  2007/04/19 13:55:23  hbhatnagar
 * LOG: Enhancement: Provided API to add and remove AVPs.
 * LOG:
 * LOG: Revision 2.10  2007/01/04 10:59:26  nvijikumar
 * LOG: Provoded Accountaing related APIs.
 * LOG:
 * LOG: Revision 2.9  2006/11/13 14:44:53  tpanda
 * LOG: clientId,sessionIndex moved to implementation object
 * LOG:
 * LOG: Revision 2.8  2006/11/09 14:05:45  tpanda
 * LOG: clientId variable added for IDS
 * LOG:
 * LOG: Revision 2.7  2006/10/30 14:18:55  yranade
 * LOG: Protected to public.
 * LOG:
 * LOG: Revision 2.6  2006/10/28 15:01:34  kamakshilk
 * LOG: Fix for IDC crash because of command change
 * LOG:
 * LOG: Revision 2.5  2006/10/28 10:54:41  tpanda
 * LOG: Memory leak fix for codec
 * LOG:
 * LOG: Revision 2.4  2006/10/24 08:57:15  tpanda
 * LOG: Changes to support extensible AVPs and SetRetained API deprecated
 * LOG:
 * LOG: Revision 2.3  2006/10/17 16:55:48  tpanda
 * LOG: Minnor correction in get and set SessIndex
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:50:43  tpanda
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.9  2006/10/16 07:21:40  tpanda
 * LOG: SetSessionIndex API added to Gen.Cmd
 * LOG:
 * LOG: Revision 2.8  2006/10/16 07:17:24  tpanda
 * LOG: GetSessionIndex made public-accessing via obj
 * LOG:
 * LOG: Revision 2.7  2006/10/13 15:58:59  tpanda
 * LOG: Exposed getSessionIndex in generiCommand
 * LOG:
 * LOG: Revision 2.6  2006/10/13 15:46:45  tpanda
 * LOG: proprietary change-facilitate setting session index
 * LOG:
 * LOG: Revision 2.5  2006/10/05 05:39:58  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 2.4  2006/09/20 05:08:42  tpanda
 * LOG: Fix for createCopy while encoding and encoding support for GenericCommand
 * LOG:
 * LOG: Revision 2.3  2006/09/19 06:04:51  tpanda
 * LOG: Val is splitted. Encoding/Decoding functionality moved to vendor
 * LOG:
 * LOG: Revision 2.2  2006/09/13 16:01:04  tpanda
 * LOG: Changes made to make application decoding working
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.8  2006/08/13 09:53:09  brianhu
 * LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
 * LOG:
 * LOG: Revision 1.7  2006/06/21 10:26:35  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.6  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: Command.h,v 3.2.30.4 2012/10/01 09:01:05 rsanjay Exp $
 ****************************************************************************/
#ident "$Id: Command.h,v 3.2.30.4 2012/10/01 09:01:05 rsanjay Exp $"

#ifndef _COMMAND_H_
#define _COMMAND_H_

#include <diameter/AVP.h>

namespace diameter {

class Command {
    friend std::ostream &operator<<(std::ostream &, const Command &);
public:

    Command(const Command &);
    virtual ~Command() {
#ifdef DEBUG
#ifdef DEBUG_VAL
        DBG_LOG((VALCPP) << "Command: releasing CommandImpl @ 0x" << std::hex << (unsigned long)_managed << std::dec);
#endif
#endif
        CommandImpl::release(_managed);
        /**
         * Making the _managed as NULL. changes 
         * required for Proxy Application.
         */
        _managed = NULL;      
    }

    /**
     * Returns a const reference to the internal CommandImpl object.
     */
    const CommandImpl &getImpl() const {
        return _inbound;
    }

    /**
     * Tests whether this command is a request.
     */
    bool isRequest() const {
        return _inbound.isRequest();
    }

    /**
     * Tests whether this command is proxyable.
     */
    bool isProxyable() const {
        return _inbound.isProxyable();
    }

    /**
     * Tests whether this command is an error report.
     */
    bool isError() const {
        return _inbound.isError();
    }

    /**
     * Tests whether this command is a retransmit.
     */
    bool isRetransmit() const {
        return _inbound.isRetransmit();
    }

    /**
     * Returns the command name.
     */
    virtual const char *getCommandName() const {
        return _inbound.getCommandName();
    }

    /**
     * Returns the command code.
     */
    CommandCode getCommandCode() const {
        return _inbound.getCommandCode();
    }

    /**
     * Returns the application id.
     */
    ApplicationId getApplicationId() const {
        return _inbound.getApplicationId();
    }

    /**
     * Writes the encoded message as a byte stream into the provided buffer. Returns the number of bytes written.
     */
    virtual int encode(unsigned char *&buffer, int& size) {
        return ((CommandImpl&)_inbound).encode(buffer, size);
    }

    /*#
     * Constructs a Command from raw bytes.
     */
    explicit Command(const unsigned char *buffer, int size, const CommandAttribute* descObj=NULL) : 
    _managed(CommandImpl::decode(buffer, size,descObj)), _inbound(*_managed){}

    /*#
     * Constructs a Command from a transfered CommandImpl (from a GenericCommand).
     */
    explicit Command(CommandImpl *message):
    _managed(message), _inbound(*message)
    {
       message->validateApp();
    }

    /*#
     * Constructs a Command from an incoming message.
     */
    explicit Command(const CommandImpl &message, const CommandAttribute* descObj=NULL): 
    _managed(0), _inbound(message)
    {
        CommandImpl& mesg = (CommandImpl&)message;
        mesg.validateApp(descObj);
    }

    /*#
     * Constructs a new Command.
     */
    explicit Command(bool request, bool proxyable, bool error, bool retrans, CommandCode code, ApplicationId id);

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
        return ((CommandImpl&)_inbound).getContainer();
    }

    /*#
     * Prints this message to the output stream.
     */
    virtual std::ostream &print(std::ostream &) const = 0;

    std::ostream &printHeader(std::ostream &) const;

public:
	//Added for Rule Engine
	std::stringstream &printHeaderForRuleEngine(std::stringstream &) const ;

	virtual std::stringstream &formDiameterMessageForRuleEngine(std::stringstream &) const ;
	
    void SetCmdAttribute(const CommandAttribute* descObj)
    {
       ((CommandImpl&)_inbound).SetCmdAttribute(descObj);
    }

    //must be used carefully, with proper understanding
    //specific to stack
    unsigned int getSessionIndex();
    void setSessionIndex(unsigned int index); 

    /**
     * These API used for Accounting State machine
     */
    bool IsStorageSpaceAvailable();
    void setStorageSpaceAvailable(bool flag);

    /**
     * These API used for Accounting State machine
     */
    bool IsLastRecordInStorage();
    void setLastRecordInStorage(bool flag);

    /**
     * APIs used for adding and getting AVPs based on name and avp-code
     */
    int getAvpValue(unsigned int avpCode, void* val, ValueDiscriminator D, unsigned int venId=0)
    {
        return getContainer().getAvpValue(avpCode, val, D, venId);
    }

    /*.implementation:inline,public,Command
     ****************************************************************************
     *  Purpose: This function adds AVP in Command inside the container.
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
     *                stored in the Container of the Command. 
     *  Notes:
     *
     *  See Also:
     ****************************************************************************/
    const AVP& addAVP(AVP& avp, bool single)
    {
        return (getContainer().add(avp.name(), avp, single));
    }

    /*.implementation:inline,public,Command
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
        return (getContainer().remove(avp.name(), avp));
    }
    /**
     * May have performance issues as compared to other API
     */
    /**
     * Two Overloaded functions for the addition of AVPs
     */
    const AVP&  addAVP(const char* name,unsigned int vendorId, void* val, bool single, ValueDiscriminator D)
    {
        return getContainer().addAVP(name,vendorId, val, single, D);
    }
    const AVP&  addAVP(int attrCode, unsigned int vendorId, void* val, bool single, ValueDiscriminator D)
    {
        return getContainer().addAVP(attrCode, vendorId, val, single, D);
    }
    /**
     * Two Overloaded functions for the removal of AVPs
     */
    int removeAVP(const char* name, unsigned int vendorId)
    {
        return getContainer().removeAVP(name, vendorId);
    }
    int removeAVP(int attrCode, unsigned int vendorId)
    {
        return getContainer().removeAVP(attrCode, vendorId);
    }

protected:
    CommandImpl *_managed;
    const CommandImpl &_inbound;
};


inline std::ostream &operator<<(std::ostream &out, const Command &command) {
    return command.print(out);
}


class GenericCommand: public Command {
public:
    GenericCommand(const unsigned char *buffer, int size):Command(buffer, size){}

    std::ostream &print(std::ostream &out) const {
        return out;
    }
  

    CommandImpl *transfer(const CommandAttribute* descObj=NULL) {
        /**
         * calling setCmdAttribute directly in case
         * of managed being NULL. Changes required for the 
         * Proxy application.
         */
        if (_managed) 
            _managed->SetCmdAttribute(descObj);
        else
            SetCmdAttribute(descObj); 
        CommandImpl *m = _managed;
        _managed = 0;

        /**
         * Returning address of inbound if m is NULL.
         * Changes required for the Proxy application.
         */
        if (m == NULL)
            m = (CommandImpl*)&(_inbound);

        return m;
    }
protected:
    explicit GenericCommand(GenericCommand& cmd):Command(cmd.transfer()->createCopy())
    {
        CommandImpl& impl = (CommandImpl&)cmd.getImpl();
        cmd._managed = &impl;
    }

	explicit GenericCommand(CommandImpl &impl):Command( impl.createCopy())
	{
	}

};

}

#endif//_COMMAND_H_
