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
//   ID: $Id: releasecompletecause.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: releasecompletecause.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_RELEASECOMPLETECAUSE_H
#define BSSAPLE_IE_RELEASECOMPLETECAUSE_H


#include <bssaple/ie/infoelement.h>

#define MAX_DIAGNOSTIC_LEN 28

namespace bssaple
{

namespace ie
{


class ReleaseCompleteCause : public InfoElement
{

public:
        
/*
    enum CodingStandard
    {
        CCITT       =   0x00,
        RESERVED    =   0x01,
        NATIONAL    =   0x02,
        GSM_PLMNS   =   0x03
    };


    enum Location
    {
        USER                                =   0x00,    
        PRIVATE_NETWORK_SERVING_LOCAL_USER  =   0x01,
        PUBLINETWORK_SERVING_LOCAL_USER     =   0x02,
        TRANSIT_NETWORK                     =   0x03,
        PUBLINETWORK_SERVING_REMOTE_USER    =   0x04,
        PRIVATE_NETWORK_SERVING_REMOTE_USER =   0x05,
        INTERNATIONAL_NETWORK               =   0x07,
        NETWORK_BEYOND_INTERWORKING_POINT   =   0x10
    };
ÿ
    enum Class
    {
        NORMAL_EVENT1                        =   0x00,
        NORMAL_EVENT2                        =   0x01,
        RESOURCE_UNAVAILABLE                 =   0x02, 
        SERVICE_OR_OPTION_NOT_AVAILABLE      =   0x03,
        SERVICE_OR_OPTION_NOT_IMPLEMENTED    =   0x04,
        INVALID_MESSAGE                      =   0x05,
        PROTOCOL_ERROR                       =   0x06,
        INTERWORKING                         =   0x07
    };
*/

/*
    enum NormalEvent1Value
    {
        UNASSIGNED_NUMBER                       =   0x01,
        NO_ROUTE_TO_DESTINATION                 =   0x03,
        CHANNEL_UNACCEPTABLE                    =   0x06,
        OPERATOR_DETERMINED_BARRING             =   0x08
    };
        
    enum NormalEvent2Value
    {
        NORMAL_CALL_CLEARING        =   0x00,
        USER_BUSY                   =   0x01, 
        NO_USER_RESPONDING          =   0x02,
        USER_ALERTING               =   0x03,
        CALL_REJECTED               =   0x05,
        NUMBER_CHANGED              =   0x06,
        PRE_EMPTION                 =   0x09,
        NON_SELECTED_USER_CLEARING  =   0x0A, 
        DESTINATION_OUT_OF_ORDER    =   0x0B,
        INVALID_NUMBER_FORMAT       =   0x0C,
        FACILITY_REJECTED           =   0x0D,
        RESPONSE_TO_STATUS_ENQUIRY  =   0x0E,
        NORMAL_OR_UNSPECIFIED       =   0x0F
    };
*/

    enum CodingStandard
    {
        GSM_PLMNS = 0x03
    };

    enum Location
    {};

    enum Class
    {};

    enum Value
    {};
    

    enum ResourseUnavailableValue
    {};

        

    /**
     *  Purpose:
     *      This is contructor initailizes the type and
     *      default length of base class.
     *
     *  Input Parameters:
     *      optFlag - Set this flag to true if This IEs is optional
     *             parameter in the message.
     *
     *  Output parameters:
     *
     */
    ReleaseCompleteCause()
    :standard_location(0),
    recommendation(0),
    causeValue(0),
    dataLen(0),
    InfoElement(InfoElement::RELEASE_COMPLETE_CAUSE,sizeof(ITS_OCTET)*4)
    {}

    ~ReleaseCompleteCause()
    {}


    /**
     *  Purpose: Set the CodingStandard value
     *
     *  Input Parameters:
     *      val - value of CodingStandard
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetStandard(CodingStandard val)
    {
        standard_location |= ((ITS_OCTET)val << 4) & 0x60U;
    }


    /**
     *  Purpose: Get the CodingStandard value
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      CodingStandard value.      
     *
     */
    CodingStandard GetStandard(void)
    {
        return (CodingStandard)((standard_location >> 5) & 0x06U);
    }

    /**
     *  Purpose: Set the Location value
     *
     *  Input Parameters:
     *      loc - Location value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetLocation(Location loc)
    {
        standard_location |= (ITS_OCTET)loc & 0x0FU;
    }

    /**
     *  Purpose: Get the Location value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Location value
     *
     */
    Location GetLocation(void)
    {
        return Location(standard_location & 0x0FU);
    }

    /**
     *  Purpose: Set the Recommendation
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
    void SetRecommendation(ITS_OCTET rec)
    {
        recommendation = rec;
    }
    /**
     *  Purpose: Get Recommendation
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      recommendation value.
     *
     */
    ITS_OCTET GetRecommendation(void)
    {
        return recommendation;
    }

    /**
     *  Purpose: Set the CauseClas 
     *
     *  Input Parameters:
     *      cls - Class 
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetCauseClass(Class cls)
    {
        causeValue |= ((ITS_OCTET)cls << 4) & 0x70U;
    }
    
    /**
     *  Purpose: Get the CauseClas
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Class 
     *
     */
    Class GetCauseClass(void)
    {
        return (Class)((causeValue >> 4) & 0x07U);
    }

    /**
     *  Purpose: Set the CauseValue
     *
     *  Input Parameters:
     *      val - is CauseValue
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetCauseValue(Value val)
    {
        causeValue |= ((ITS_OCTET)val & 0x0FU);
    }

    /**
     *  Purpose: Get the CauseValue
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Value
     *
     */
    Value GetCauseValue(void)
    {
        return (Value)(causeValue & 0x0FU);
    }

    /**
     *  Purpose: Set the DiagnosticData
     *
     *  Input Parameters:
     *      data - octet string 
     *      len - is length of octet string.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetDiagnosticData(ITS_OCTET *data,int len)
    {
        memcpy(diagnosticData,data,len); 
        dataLen = len;
    }
        
    /**
     *  Purpose: Get the DiagnosticData
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      data - octet string
     *      len - is length of octet string.
     *
     *  Returns:
     *
     *
     */
    void GetDiagnosticData(ITS_OCTET *data,int &len)
    {
        memcpy(data,diagnosticData,dataLen);
        len = (int)dataLen;
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
     *      Throws EncodingException in case unsuccessful.
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new ReleaseCompleteCause(*this);
    }

    virtual void PrintIE(std::ostream &) const;

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
    ReleaseCompleteCause(const ITS_OCTET *buf,int len);

private:

    ITS_OCTET standard_location;
    ITS_OCTET recommendation;
    ITS_OCTET causeValue;
    ITS_OCTET diagnosticData[MAX_DIAGNOSTIC_LEN];
    ITS_OCTET dataLen;

    friend class InfoElement;
};

}

}

#endif

