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
//   ID: $Id: positioningdata.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: positioningdata.h,v $
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

#ifndef BSSAPLE_IE_POSITIONINGDATA_H
#define BSSAPLE_IE_POSITIONINGDATA_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_POSITIONING_METHOD(void);

const int MAX_POSITIONING_METHODS =32;

/**
*    Class: PositioningData
*    This is a variable length
*    positioning data as
*    unsuccessful
*    locatiomn attempt for a target MS.
*/
class PositioningData : public InfoElement 
{
public:
    enum PositioningDiscriminator
    {
        POSITIONING_DATA_DISCRIMINATOR  = 0x00
    };

    enum PositioningMethod
    {
        TIMING_ADVANCE        =   0x00,
        TOA                   =   0x01,
        AOA                   =   0x02,
        MOBILE_ASSISTED_EOTD  =   0x03,
        MOBILE_BASED_EOTD     =   0x04,
        MOBILE_ASSISTED_GPS   =   0x05,
        MOBILE_BASED_GPS      =   0x06,
        CONVENTIONAL_GPS      =   0x07,
        CELL_ID               =   0X0C
    };

    enum Usage
    {
        UNSUCCESSFUL_FAILURE_OR_INTERRUPTION            =   0x00,
        SUCCESSFUL_RESULTS_NOT_USED                     =   0x01,
        SUCCESSFUL_RESULTS_USED_TO_VERIFY               =   0x02,
        SUCCESSFUL_RESULTS_USED_TO_GENERATE_LOCATION    =   0x03,
        METHODS_CANNOT_BE_DETERMINED                    =   0x04
    };

    struct  MethodAndUsage
    {
        PositioningMethod _type;
        Usage _usage;
    };

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
    PositioningData():InfoElement(InfoElement::POSITIONING_DATA,
                                                     sizeof(ITS_OCTET))
    {}

    /**
    *    Destructor 
    */
    ~PositioningData()
    {}

    /**
     *  Purpose: Sets Discriminator
     *
     *  Input Parameters:
     *      val - value of PositioningDiscriminator
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetDiscriminator(PositioningDiscriminator val)
    {
        positioningDisc = val;
    }


    /**
     *  Purpose: Returns Discriminator
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      vlaue of PositioningDiscriminator
     *
     */
    PositioningDiscriminator GetDiscriminator () const
    {
        return (PositioningDiscriminator) positioningDisc;
    }

    /**
     *  Purpose: Set PositioningMethod value
     *
     *  Input Parameters:
     *      method -  MethodAndUsage array.
     *      len - size of the array.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *  Note:
     *      MethodAndUsage is structure containing method and usage
     *
     */
    void SetPositioningMethodAndUsage (MethodAndUsage *method,int len);

    /**
     *  Purpose:  Get PositioningMethods
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      method - MethodAndUsage array.
     *      index -  size of array.
     *
     *  Returns:
     *
     *
     */
    void GetPositioningMethodAndUsage (MethodAndUsage *method,int& index) const;

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
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new PositioningData(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    PositioningData(const ITS_OCTET *buf,int len);

    virtual void PrintIE(std::ostream &) const;

private: 
    mutable ITS_OCTET hexBuff[15];

    /*
    *   Data memmber describes the positioningDataDiscriminator
    */
    ITS_OCTET positioningDisc;

    /*
    *   Data member whitch contains both positioning method and usage.
    *   This variable length and declared to its max length.
    */
    ITS_OCTET postioningMethod_usage[MAX_POSITIONING_METHODS ];

    /**
    *    Assignment Operation 
    */
    PositioningData & operator=(const PositioningData &right);
    
    friend class InfoElement;
    friend void TEST_POSITIONING_METHOD(void);
};


} // namespace ie
} // namespace bssaple


#endif

