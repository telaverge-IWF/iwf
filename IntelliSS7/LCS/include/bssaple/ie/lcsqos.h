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
//   ID: $Id: lcsqos.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: lcsqos.h,v $
//   LOG: Revision 1.1.2.3  2010/03/26 11:48:05  rajeshak
//   LOG: GetHexBuff function signature changes
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/25 06:32:32  rajeshak
//   LOG: API to get the Hex dump after encode/decode (for TDR).
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_LCSQOS_H
#define BSSAPLE_IE_LCSQOS_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_LCSQOS(void);

struct LCSQoSStruct
{
private:
    enum VerticalIndicator
    {
        VERT_NOT_REQUESTED = 0x00,
        VERT_IS_REQUESTED  = 0x01
    };

    enum AccuracyIndicator
    {
        ACCURACY_INDICATOR = 0x80
    };

public:
    enum ResponseTimeIndicator
    {
        NOT_SPECIFIED  = 0x00,
        LOW_DELAY      = 0x01,
        DELAY_TOLERANT = 0x02
    };

    /**
     *  Purpose: Sets that vertical coordinate flag.
     *
     *  Input Parameters:
     *      required - boolean flag(true or flase)
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetVerticalCoordinateRequired(bool required)
    {
        verticalIndicator = required ? VERT_IS_REQUESTED : VERT_NOT_REQUESTED;
    }

    /**
     *  Purpose: Returns vertical coordinate flag
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    bool IsVerticalCoordinateRequired() const
    {
        return (bool)verticalIndicator;
    }

    /**
     *  Purpose: Sets horizontal accuracy requirement.
     *
     *  Input Parameters:
     *      val - value of horizontal accuracy
     *
     *  OutPut Parameters:
     *      
     *
     *  Returns:
     *
     *
     */
    void SetHorizontalAccuracy(ITS_OCTET val)
    {
        ha_horizontalAccuracy = val | ACCURACY_INDICATOR;
    }

    /**
     *  Purpose: Returns whether horizontal accuracy flag
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      horizontal accuracy flag
     *
     */
    bool HasHorizontalAccuracy() const
    {
        return (ha_horizontalAccuracy & ACCURACY_INDICATOR) != 0;
    }

    /**
     *  Purpose: Returns horizontal accuracy requirement value
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      value of horizontal accuracy requirement
     *
     */
    ITS_OCTET GetHorizontalAccuracy() const
    {
        return ha_horizontalAccuracy & ~ACCURACY_INDICATOR;
    }

    /**
     *  Purpose: Unsets horizontal accuracy requirement
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void RemoveHorizontalAccuracy()
    {
        ha_horizontalAccuracy &= ~ACCURACY_INDICATOR;
    }

    /**
     *  Purpose: Sets vertical accuracy requirement
     *
     *  Input Parameters:
     *     val - value of vertical accuracy requirement 
     *
     *  OutPut Parameters:
     *      
     *
     *  Returns:
     *
     *
     */
    void SetVerticalAccuracy (ITS_OCTET val)
    {
        va_verticalAccuracy = val | ACCURACY_INDICATOR;
    }

    /**
     *  Purpose: Returns vertical accuracy requirement flag
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      vertical accuracy requirement flag
     *
     */
    bool HasVerticalAccuracy()
    { 
        return (va_verticalAccuracy & ACCURACY_INDICATOR) != 0;
    }

    /**
     *  Purpose: Returns vertical accuracy requirement value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      vertical accuracy requirement value
     *
     */
    ITS_OCTET GetVerticalAccuracy () const
    {
        return va_verticalAccuracy & ~ACCURACY_INDICATOR;
    }

    /**
     *  Purpose: Unsets vertical accuracy requirement.
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void RemoveVerticalAccuracy()
    {
        va_verticalAccuracy &= ~ACCURACY_INDICATOR;
    }

    /**
     *  Purpose: Sets response time indicator
     *
     *  Input Parameters:
     *      val - is the vlaue ResponseTimeIndicator 
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetResponseTimeIndicator(ResponseTimeIndicator val)
    {
        responseTime = (val << 6) & 0xC0U;
    }

    /**
     *  Purpose: Returns response time indicator
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      response time indicator value
     *
     */
    ResponseTimeIndicator GetResponseTimeIndicator() const
    {
        return (ResponseTimeIndicator)(responseTime >> 6);
    }

protected:
    ITS_OCTET verticalIndicator;
    ITS_OCTET ha_horizontalAccuracy;
    ITS_OCTET va_verticalAccuracy;
    ITS_OCTET responseTime;
};

/**
 * LCSQoS defines the Quality of Service for a location request.
 */
class LCSQoS : public InfoElement, public LCSQoSStruct
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
    LCSQoS()
    : InfoElement(InfoElement::LCS_QOS, sizeof(ITS_OCTET)*3)
    {}

/*
    LCSQoS(const Struct &qos)
    : InfoElement(InfoElement::LCS_QOS, sizeof(ITS_OCTET)*3), _s(qos)
    {}
*/

    const LCSQoSStruct &GetAsStruct() const
    {
        return *static_cast<const LCSQoSStruct *>(this);
    }

        /**
     *  Purpose: Get Hex Buff (This can be used after IE decode only)
     *
     *  Input Parameters:
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Hex Buff
     *
     */
    const ITS_OCTET* GetHexBuff() const
    {
        return hexBuff;
    }

protected:

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer
     *      len - is lenght of encoded bufer
     *
     *  Output Parameters:
     *
     */
    LCSQoS(const ITS_OCTET *buf,int len);

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new LCSQoS(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private:
    ITS_OCTET hexBuff[15];
    friend class InfoElement;
    friend void TEST_LCSQOS(void);
    LCSQoS & operator=(const LCSQoS &right);
};

} // namespace ie    
} // namespace bssaple    


#endif

