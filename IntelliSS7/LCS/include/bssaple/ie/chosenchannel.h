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
//   ID: $Id: chosenchannel.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: chosenchannel.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_CHOSENCHANNEL_H
#define BSSAPLE_IE_CHOSENCHANNEL_H 

#include <bssaple/ie/infoelement.h>


namespace bssaple
{

namespace ie
{

static void TEST_CHOSEN_CHANNEL(void);

struct ChosenChannelStruct
{
    enum Mode
    {
        MODE_NO_CHANNEL_MODE_INDICATION  =   0x00U,
        MODE_SPEECH_MODE                 =   0x09U,
        MODE_DATA_MODE_14_5KBIT          =   0x0EU,
        MODE_DATA_MODE_12_0KBIT          =   0x0BU,
        MODE_DATA_MODE_6_0KBIT           =   0x0CU,
        MODE_DATA_MODE_3_6KBIT           =   0x0DU,
        MODE_SIGNALLING_ONLY             =   0x08U
    };

    enum Channel
    {
        CHANNEL_NONE                =   0x00,
        CHANNEL_SDCCH               =   0x01,
        CHANNEL_1_FULL_RATE_TCH     =   0x08,
        CHANNEL_1_HALF_RATE_TCH     =   0x09,
        CHANNEL_2_FULL_RATE_TCHS    =   0x0A,
        CHANNEL_3_FULL_RATE_TCHS    =   0x0B,
        CHANNEL_4_FULL_RATE_TCHS    =   0x0C,
        CHANNEL_5_FULL_RATE_TCHS    =   0x0D,
        CHANNEL_6_FULL_RATE_TCHS    =   0x0E,
        CHANNEL_7_FULL_RATE_TCHS    =   0x0F,
        CHANNEL_8_FULL_RATE_TCHS    =   0x04
    };

    Mode mode;
    Channel channel;
};


/**
 * ChosenChannel identifiers a type of radio interface channel.
 */
class ChosenChannel: public InfoElement, public ChosenChannelStruct
{
public:

    /**
     *  Purpose:
     *      This is default contructor initailizes the type and
     *      default length.
     *
     *  Input Parameters:
     *
     *  Output parameters:
     *
     */
    ChosenChannel()
    : InfoElement(InfoElement::CHOSEN_CHANNEL, sizeof(ITS_OCTET))
    {
        mode = MODE_NO_CHANNEL_MODE_INDICATION;
        channel = CHANNEL_NONE;
    }

    /**
     * Constructs a ChosenChannel from a ChosenChannel::Struct
     */
/**
    explicit ChosenChannel(const Struct &ccs)
    : InfoElement(InfoElement::CHOSEN_CHANNEL, sizeof(ITS_OCTET)), _s(ccs)
    {}
**/

    /**
     * Returns ChosenChannel as a ChosenChannel::Struct
     */
    const ChosenChannelStruct &GetAsStruct() const
    {
        return *static_cast<const ChosenChannelStruct *>(this);
    }

    /**
     *  Purpose: SetChannelMode.
     *
     *  Input Parameters:
     *      val - Channel mode value.
     *
     *  OutPut Parameters:
     *
     */
    void SetChannelMode(Mode val)
    {
        mode = val;
    }

    /**
     *  Purpose: Returns the channel mode of the chosen channel.
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      
     *  Returns:
     *      Channel Mode.
     *
     */
    Mode GetChannelMode() const
    {
        return mode;
    }

    /**
     *  Purpose: GetChannel value
     *
     *  Input Parameters:
     *      
     *  OutPut Parameters:
     *
     *  Returns:
     *      Channel Value.
     *
     */
    Channel GetChannel() const
    {
        return channel;
    }

    /**
     *  Purpose: Set Channel value.
     *
     *  Input Parameters:
     *      val - Channel value.
     *
     *  OutPut Parameters:
     *
     */
    void SetChannel(Channel val)
    {
        channel = val;
    }

protected:

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    ChosenChannel(const ITS_OCTET * buf,int len);

    virtual void PrintIE(std::ostream &) const;

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into.
     *
     *  Output Parameters:
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful.
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {       
        return new ChosenChannel(*this);
    }

private:
    friend class InfoElement;
    friend void TEST_CHOSEN_CHANNEL(void);
};


} // namespace ie
} // namespace bssaple


#endif

