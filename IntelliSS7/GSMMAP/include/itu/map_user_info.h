/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2004, IntelliNet Technologies, Inc.                *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *  ID: $Id: map_user_info.h,v 1.2 2008/05/01 14:28:16 kramesh Exp $
 ****************************************************************************
 *
 *  LOG: $Log: map_user_info.h,v $
 *  LOG: Revision 1.2  2008/05/01 14:28:16  kramesh
 *  LOG: Added new map_user_info file after merging changes from Starhome & Sigvalue
 *  LOG: Branches for the issues 1311 & 1403.
 *  LOG:
 *  LOG: Revision 1.1.2.8  2006/09/19 19:22:26  omayor
 *  LOG: Fix for Validity Period Format (1:enhanced, 2:relative, 3:absolute).
 *  LOG:
 *  LOG: Revision 1.1.2.7  2004/12/20 12:54:49  mmanikandan
 *  LOG: Coding changes as per SigVal requirement.
 *  LOG:
 *  LOG: Revision 1.1.2.6  2004/09/08 04:39:51  mmanikandan
 *  LOG: Comments for initialize function are modified.
 *  LOG:
 *  LOG: Revision 1.1.2.5  2004/09/08 04:11:04  mmanikandan
 *  LOG: Support for user data header.
 *  LOG:
 *  LOG: Revision 1.1.2.4  2004/08/25 13:55:21  mmanikandan
 *  LOG: Optional parameters is status report message is added.
 *  LOG:
 *  LOG: Revision 1.1.2.3  2004/07/14 12:52:12  mmanikandan
 *  LOG: Encoding / Decoding for SMS Status Report is added.
 *  LOG:
 *  LOG: Revision 1.1.2.2  2004/06/11 11:50:43  mmanikandan
 *  LOG: Encoding / Decoding of SMSSubmit and SMSDeliver.
 *  LOG:
 *  LOG: Revision 1.1.2.1  2004/06/04 10:27:23  mmanikandan
 *  LOG: Initial commit for map user info encoding / decoding.
 *  LOG:
 *
 ***************************************************************************/

#include <its++.h>
#include <string>

#define MAX_USER_DATA_LEN        255 
#define MAX_DEST_ADDR_LEN        20
#define MAX_ORIG_ADDR_LEN        20
#define MAX_VALIDITY_PERIOD_LEN  7
#define MAX_SRV_CENTER_TS        7

// Macros to decode the Address Type

#define GET_TYPE_OF_NUMBER(x) (((x) & 0x70) >> 4)
#define GET_NUMBERING_PLAN(x) ((x) & 0x0f)

// Macros to decode the Data Coding Scheme
#define GET_CODING_GROUP(x) (((x) & 0xf0) >> 4)
#define GET_ALPHABET_USED(x) (((x) & 0x0C) >> 2)
#define GET_MSG_CLASS(x) ((x) & 0x03)

// Validity Period Formats
#define MAP_VP_FORMAT_ENHANCED        0x01
#define MAP_VP_FORMAT_RELEATIVE       0x02
#define MAP_VP_FORMAT_ABSOLUTE        0x03

typedef struct 
{
    ITS_OCTET day;
    ITS_OCTET month;
    ITS_OCTET year;
    ITS_OCTET hour;
    ITS_OCTET minute;
    ITS_OCTET second;
    ITS_OCTET timezone;
    ITS_UINT  tpvpValue;
}ValidityPeriod;
    
//
// It calcuates the validity period for the given validity 
// period format.
//    if validity period format is Relative Format
//       only tp-vpValue will get filled (in secs).
//    else except tp-vpValue all the remaining parameters
//       will be filled.
//
//  It returns ITS_SUCCESS on success 
//  -1 for Invalid Validity Period Format.
//  -2 for NULL memory
//

int CalculateValidityPeriod (ITS_OCTET vpFormat, 
                             ITS_OCTET* vpOctet, 
                             ValidityPeriod* vp);

/*.interface:MapUserInfo
 *****************************************************************************
 *  Interface:
 *      MapUserInfo_SMSSubmit
 *
 *  Purpose:
 *      This will encode / decode the SignalInfo, which is encoded as
 *      OCTET STRING in the MO_ForwardSMArg message.
 *
 *  Usage:
 *
 *      1. Create the MapUserInfo_SMSSubmit object.
 *      2. To decode call Decode function by giving the ITS_OCTET* and
 *         the length of the ITS_OCTET Array.
 *      3. To Encode set all the required parameters and call Encode
 *         by providing a ITS_OCTET Pointer and ITS_USHORT element to
 *         fill the encoded value and length.
 *****************************************************************************/

class MapUserInfo_SMSSubmit
{
public:
    //
    // Default Constructor. This will initialize the MapUserInfo object.
    //
    MapUserInfo_SMSSubmit ();

    //
    // Parameter Constructor. This will decode the given input and 
    // fills all the internal parameters. This is equivalent to
    // creating a MapUserInfo object and calling Decode function.
    //
    MapUserInfo_SMSSubmit (ITS_OCTET* usrInfo, ITS_USHORT usrInfoLen);

    // 
    // Sets the MessageIndicator value. 
    //
    void SetMessageIndicator (ITS_OCTET msgTypeInd);

    //
    // Returns the MessageIndicator value.
    //
    ITS_OCTET GetMessageIndicator () const;

    //
    // Sets the Reject Duplicates.
    //
    void SetRejectDuplicates (ITS_BOOLEAN rejDup);

    //
    // Returns the Reject Duplicates.
    //
    ITS_BOOLEAN GetRejectDuplicates () const;

    //
    // Sets the Validity Period Format.
    // 1 - Enhanced Format
    // 2 - Relative Format
    // 3 - Absolute Format
    //
    void SetValidityPeriodFormat (ITS_OCTET valPerFormat);

    //
    // Returns the Validity Period Format.
    //
    ITS_OCTET GetValidityPeriodFormat () const;

    //
    // Sets the Reply Path.
    //
    void SetReplyPath (ITS_BOOLEAN repPath);
    
    //
    // Returns the Reply Path.
    //
    ITS_BOOLEAN GetReplyPath () const;

    //
    // Sets the User Data Header Indicator.
    //
    void SetUserDataHdrInd (ITS_BOOLEAN usrDataHdrInd);

    //
    // Returns the User Data Header Indicator.
    //
    ITS_BOOLEAN GetUserDataHdrInd () const;

    // 
    // Sets the StatusReportRequest.
    //
    void SetStatusReportRequest (ITS_BOOLEAN statRepReq);

    //
    // Returns the StatusReportRequest.
    //
    ITS_BOOLEAN GetStatusReportRequest () const;

    //
    // Sets the Message Reference.
    //
    void SetMsgReference (ITS_OCTET msgRef);

    //
    // Returns the Message Reference.
    //
    ITS_OCTET GetMsgReference () const;

    //
    // Sets the Destination Address.
    //     destAddrLen = length of the Destination Address.
    //     destAddrType = Type of Destination Address.
    //     destAddr = Destination Address (e.g "1234567891")
    //
    void SetDestAddr (ITS_OCTET destAddrLen, 
                      ITS_OCTET destAddrType, 
                      std::string destAddr);

    //
    // Returns the Destination Address length, type and number.
    //
    void GetDestAddr (ITS_OCTET& destAddrLen,
                      ITS_OCTET& destAddrType,
                      std::string& destAddr);

    //
    // Sets the protocol id.
    //
    void SetProtocolId (ITS_OCTET protId);

    //
    // Returns the protocol id.
    //
    ITS_OCTET GetProtocolId () const;
   
    //
    // Sets the Data coding scheme.
    //
    void SetDataCodingScheme (ITS_OCTET dataCodeScheme);

    //
    // Returns the Data coding scheme.
    //
    ITS_OCTET GetDataCodingScheme () const; 

    // 
    // Set the Validity period.
    //    if Validity period format is relative then 
    //       the length of the Validity period is 1 octet.
    //    else 7 octets.
    //
    void SetValidityPeriod (ITS_OCTET* valPeriod);

    //
    // Returns the Validity period.
    //
    void GetValidityPeriod (ITS_OCTET* valPeriod) const; 
   
    //
    // It sets the user data.
    //
    ITS_INT SetUserData (ITS_OCTET* usrData, ITS_UINT usrDataLen);

    //
    // It returns the user data.
    //
    ITS_INT GetUserData (ITS_OCTET* usrData, ITS_UINT* usrDataLen);

    //
    // This will encode the user info message and fills the
    // given buffer and returns the buffer length in the 
    // parameter dataLen.
    // 
    // If the return value is ITS_SUCCESS, then encoding is success.
    // else
    // Non zero value represents the size of buffer required to encode.
    // -1 represents the length of the Destination Address is exceeding the maximum.
    // -2 represents the Unknown character is available in the Destination Address.
    //
    int Encode (ITS_OCTET* data, ITS_USHORT& dataLen);

    //
    // It decodes the given the ITS_OCTET* and fills 
    // MapUserInfo object.
    //
    int Decode (ITS_OCTET* data, ITS_USHORT dataLen);

    //
    // Prints the MapUserInfo object. 
    // (This is for debugging purpose)
    //
    void Print();

private:

    //
    // This will initialize all the private members to their
    // initial values.
    // Initial Values are
    //     msgTypeInd_     = 0;
    //     rejDup_         = ITS_FALSE;
    //     valPerFormat_   = 0;
    //     repPath_        = ITS_FALSE;
    //     usrDtHdrInd_    = ITS_FALSE;
    //     statRepReq_     = ITS_FALSE;
    //     msgRef_         = 0;
    //     destAddrLen_    = 0;
    //     destAddrType_   = 0;
    //     destAddr_       = "";
    //     protId_         = 0;
    //     dataCodeScheme_ = 0;
    //     memset (valPeriod_, MAX_VALIDITY_PERIOD_LEN, 0);
    //
    void Initialize();

    ITS_OCTET    msgTypeInd_;                      // TP-MTI
    ITS_BOOLEAN  rejDup_;                          // TP-RD
    ITS_OCTET    valPerFormat_;                    // TP-VPF
    ITS_BOOLEAN  repPath_;                         // TP-RP
    ITS_BOOLEAN  usrDtHdrInd_;                     // TP-UDHI
    ITS_BOOLEAN  statRepReq_;                      // TP-SRR
    ITS_OCTET    msgRef_;                          // TP-MR
    ITS_OCTET    destAddrLen_;                     // TP-DA Octet 1
    ITS_OCTET    destAddrType_;                    // TP-DA Octet 2
    std::string  destAddr_;                        // TP-DA 
    ITS_OCTET    protId_;                          // TP-PID
    ITS_OCTET    dataCodeScheme_;                  // TP-DCS
    ITS_OCTET    valPeriod_[MAX_VALIDITY_PERIOD_LEN];    // TP-VP
    ITS_OCTET    usrDataStr_[MAX_USER_DATA_LEN];
    ITS_UINT     usrDataStrLen_;
};

/*.interface:MapUserInfo_SMSDeliver
 *****************************************************************************
 *  Interface:
 *      MapUserInfo_SMSDeliver
 *
 *  Purpose:
 *      This will encode / decode the SignalInfo, which is encoded as
 *      OCTET STRING in the MT_ForwardSMArg message.
 *
 *  Usage:
 *
 *      1. Create the MapUserInfo_SMSDeliver object.
 *      2. To decode call Decode function by giving the ITS_OCTET* and
 *         the length of the ITS_OCTET Array.
 *      3. To Encode set all the required parameters and call Encode
 *         by providing a ITS_OCTET Pointer and ITS_USHORT element to
 *         fill the encoded value and length.
 *****************************************************************************/

class MapUserInfo_SMSDeliver
{
public:
    //
    // Default Constructor. This will initialize the MapUserInfo object.
    //
    MapUserInfo_SMSDeliver ();

    //
    // Parameter Constructor. This will decode the given input and
    // fills all the internal parameters. This is equivalent to
    // creating a MapUserInfo object and calling Decode function.
    //
    MapUserInfo_SMSDeliver (ITS_OCTET* usrInfo, ITS_USHORT usrInfoLen);

    //
    // Sets the MessageIndicator value.
    //
    void SetMessageIndicator (ITS_OCTET msgTypeInd);

    //
    // Returns the MessageIndicator value.
    //
    ITS_OCTET GetMessageIndicator () const;

    //
    // Sets the Reply Path.
    //
    void SetMoreMsgsToSend (ITS_BOOLEAN moreMsgsToSend);

    //
    // Returns the Reply Path.
    //
    ITS_BOOLEAN GetMoreMsgsToSend () const;

    //
    // Sets the Reply Path.
    //
    void SetReplyPath (ITS_BOOLEAN replyPath);

    //
    // Returns the Reply Path.
    //
    ITS_BOOLEAN GetReplyPath () const;

    //
    // Sets the User Data Header Indicator.
    //
    void SetUserDataHdrInd (ITS_BOOLEAN usrDataHdrInd);

    //
    // Returns the User Data Header Indicator.
    //
    ITS_BOOLEAN GetUserDataHdrInd () const;

    //
    // Sets the StatusReportRequest.
    //
    void SetStatusReportIndication (ITS_BOOLEAN statRepInd);

    //
    // Returns the StatusReportRequest.
    //
    ITS_BOOLEAN GetStatusReportIndication () const;

    //
    // Sets the Origination Address.
    //     origAddrLen = length of the Origination Address.
    //     origAddrType = Type of Origination Address.
    //     origAddr = Origination Address (e.g "1234567891")
    //
    void SetOrigAddr (ITS_OCTET origAddrLen,
                      ITS_OCTET origAddrType,
                      std::string origAddr);


    //
    // Returns the Origination Address length, type and number.
    //
    void GetOrigAddr (ITS_OCTET& origAddrLen,
                      ITS_OCTET& origAddrType,
                      std::string& origAddr) const;

    //
    // Sets the protocol id.
    //
    void SetProtocolId (ITS_OCTET protId);

    //
    // Returns the protocol id.
    //
    ITS_OCTET GetProtocolId () const;

    //
    // Sets the Data coding scheme.
    //
    void SetDataCodingScheme (ITS_OCTET dataCodeScheme);

    //
    // Returns the Data coding scheme.
    //
    ITS_OCTET GetDataCodingScheme () const;

    //
    // Set the Service center timestamp.
    //
    void SetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS);

    //
    // Returns the Service center timestamp.
    //
    void GetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS) const;

    //
    // It sets the user data.
    //
    ITS_INT SetUserData (ITS_OCTET* usrData, ITS_UINT usrDataLen);

    //
    // It returns the user data.
    //
    ITS_INT GetUserData (ITS_OCTET* usrData, ITS_UINT* usrDataLen);

    //
    // This will encode the user info message and fills the
    // given buffer and returns the buffer length in the
    // parameter dataLen.
    //
    // If the return value is ITS_SUCCESS, then encoding is success.
    // else
    // Non zero value represents the size of buffer required to encode.
    // -1 represents the length of the Destination Address is exceeding the maximum.
    // -2 represents the Unknown character is available in the Destination Address.
    //
    int Encode (ITS_OCTET* data, ITS_USHORT& dataLen);

    //
    // It decodes the given the ITS_OCTET* and fills
    // MapUserInfo object.
    //
    int Decode (ITS_OCTET* data, ITS_USHORT dataLen);

    //
    // Prints the MapUserInfo_SMSDeliver object.
    // (This is for debugging purpose)
    //
    void Print();
private:
    //
    // This will initialize all the private members to their
    // initial values.
    // Initial Values are
    //     msgTypeInd_     = 0;
    //     moreMsgsToSend_ = ITS_FALSE;
    //     replyPath_      = ITS_FALSE;
    //     usrDataHdrInd_  = ITS_FALSE;
    //     statRepInd_     = ITS_FALSE;
    //     origAddrLen_    = 0;
    //     origAddrType_   = 0;
    //     origAddr_       = "";
    //     protId_         = 0;
    //     dataCodeScheme_ = 0;
    //     memset (srvCenterTS_, MAX_VALIDITY_PERIOD_LEN, 0);
    //
    void Initialize ();

    ITS_OCTET   msgTypeInd_;                       // TP-MTI
    ITS_BOOLEAN moreMsgsToSend_;                   // TP-MMS
    ITS_BOOLEAN replyPath_;                        // TP-RP
    ITS_BOOLEAN usrDataHdrInd_;                    // TP-UDHI
    ITS_BOOLEAN statRepInd_;                       // TP-SRI
    ITS_OCTET   origAddrLen_;                      // TP-OA Octet 1
    ITS_OCTET   origAddrType_;                     // TP-OA Octet 2
    std::string origAddr_;                         // TP-OA
    ITS_OCTET    protId_;                          // TP-PID
    ITS_OCTET    dataCodeScheme_;                  // TP-DCS
    ITS_OCTET    srvCenterTS_[MAX_SRV_CENTER_TS];  // TP-VP
    ITS_OCTET    usrDataStr_[MAX_USER_DATA_LEN];
    ITS_UINT     usrDataStrLen_;
};


/*.interface:MapUserInfo
 *****************************************************************************
 *  Interface:
 *      MapUserInfo_SMSStatusReport
 *
 *  Purpose:
 *      This will encode / decode the SignalInfo, which is encoded as
 *      OCTET STRING in the MO_ForwardSMArg message.
 *
 *  Usage:
 *
 *      1. Create the MapUserInfo_SMSStatusReport object.
 *      2. To decode call Decode function by giving the ITS_OCTET* and
 *         the length of the ITS_OCTET Array.
 *      3. To Encode set all the required parameters and call Encode
 *         by providing a ITS_OCTET Pointer and ITS_USHORT element to
 *         fill the encoded value and length.
 *****************************************************************************/

class MapUserInfo_SMSStatusReport
{
public:
    //
    // Default Constructor. This will initialize the MapUserInfo object.
    //
    MapUserInfo_SMSStatusReport ();

    //
    // Parameter Constructor. This will decode the given input and
    // fills all the internal parameters. This is equivalent to
    // creating a MapUserInfo object and calling Decode function.
    //
    MapUserInfo_SMSStatusReport (ITS_OCTET* usrInfo, ITS_USHORT usrInfoLen);

    //
    // Sets the MessageIndicator value.
    //
    void SetMessageIndicator (ITS_OCTET msgTypeInd);

    //
    // Returns the MessageIndicator value.
    //
    ITS_OCTET GetMessageIndicator () const;

    //
    // Sets the User Data Header Indicator.
    //
    void SetUserDataHdrInd (ITS_BOOLEAN usrDtHdrInd);

    //
    // Returns the User Data Header Indicator.
    //
    ITS_BOOLEAN GetUserDataHdrInd () const;

    //
    // Sets the More messages to send.
    //
    void SetMoreMsgsToSend (ITS_BOOLEAN moreMsgsToSend);

    //
    // Returns the More messages to send.
    //
    ITS_BOOLEAN GetMoreMsgsToSend () const;

    //
    // Sets the Status Report Qualifier.
    //
    void SetStatusReportQualifier (ITS_BOOLEAN statRepQul);

    //
    // Returns the Status Report Qualifier.
    //
    ITS_BOOLEAN GetStatusReportQualifier () const;

    //
    // Sets the Message Reference.
    //
    void SetMsgReference (ITS_OCTET msgRef);

    //
    // Returns the Message Reference.
    //
    ITS_OCTET GetMsgReference () const;

    //
    // Sets the Recipient Address.
    //     recAddrLen = length of the Recipient Address.
    //     recAddrType = Type of Recipient Address.
    //     recAddr = Recipient Address (e.g "1234567891")
    //
    void SetRecipientAddr (ITS_OCTET recAddrLen,
                           ITS_OCTET recAddrType,
                           std::string recAddr);

    //
    // Returns the Destination Address length, type and number.
    //
    void GetRecipientAddr (ITS_OCTET& recAddrLen,
                           ITS_OCTET& recAddrType,
                           std::string& recAddr);

    //
    // Set the Service center timestamp.
    //
    void SetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS);

    //
    // Returns the Service center timestamp.
    //
    void GetServiceCenterTimeStamp (ITS_OCTET* srvCenterTS) const;

    //
    // Set the discharge time.
    //
    void SetDischargeTime (ITS_OCTET* disTime);

    //
    // Returns the discharge time.
    //
    void GetDischargeTime (ITS_OCTET* disTime) const;

    //
    // Sets the TP-Status
    //
    void SetStatus (ITS_OCTET status);

    //
    // Returns the TP-Status
    //
    ITS_OCTET GetStatus () const;

    //
    // Set the parameter indicator.
    //
    void SetParameterInd (ITS_OCTET paramInd);

    //
    // Return the parameter indication.
    //
    ITS_OCTET GetParameterInd () const;

    //
    // Sets the protocol id.
    //
    void SetProtocolId (ITS_OCTET protId);

    //
    // Returns the protocol id.
    //
    ITS_OCTET GetProtocolId () const;

    //
    // Sets the Data coding scheme.
    //
    void SetDataCodingScheme (ITS_OCTET dataCodeScheme);

    //
    // Returns the Data coding scheme.
    //
    ITS_OCTET GetDataCodingScheme () const;

    //
    // It sets the user data.
    //
    ITS_INT SetUserData (ITS_OCTET* usrData, ITS_UINT usrDataLen);

    //
    // It returns the user data.
    //
    ITS_INT GetUserData (ITS_OCTET* usrData, ITS_UINT* usrDataLen);

    //
    // This will encode the user info message and fills the
    // given buffer and returns the buffer length in the
    // parameter dataLen.
    //
    // If the return value is ITS_SUCCESS, then encoding is success.
    // else
    // Non zero value represents the size of buffer required to encode.
    // -1 represents the length of the Destination Address is exceeding the maximum.
    // -2 represents the Unknown character is available in the Destination Address.
    //
    int Encode (ITS_OCTET* data, ITS_USHORT& dataLen);

    //
    // It decodes the given the ITS_OCTET* and fills
    // MapUserInfo object.
    //
    int Decode (ITS_OCTET* data, ITS_USHORT dataLen);

    //
    // Prints the MapUserInfo object.
    // (This is for debugging purpose)
    //
    void Print();

private:

    //
    // This will initialize all the private members to their
    // initial values.
    // Initial Values are
    //     msgTypeInd_     = 0;
    //     usrDtHdrInd_    = ITS_FALSE;
    //     moreMsgsToSend_ = ITS_FALSE;
    //     statRepQul_     = ITS_FALSE;
    //     msgRef_         = 0;
    //     recAddrLen_     = 0;
    //     recAddrType_    = 0;
    //     recAddr_        = "";
    //     memset (srvCenterTS_, MAX_VALIDITY_PERIOD_LEN, 0);
    //     memset (disTime_, MAX_VALIDITY_PERIOD_LEN, 0);
    //     status_         = 0;
    //     paramInd_       = 0;
    //     protId_         = 0;
    //     dataCodeScheme_ = 0;
    //     paramIndPresent_   = ITS_FALSE;
    //     protIdPresent_     = ITS_FALSE;
    //     dataCodeSchemePresent_ = ITS_FALSE;
    //     usrDataPresent_ = ITS_FALSE;
    //
    void Initialize();

    ITS_OCTET   msgTypeInd_;
    ITS_BOOLEAN usrDtHdrInd_;
    ITS_BOOLEAN moreMsgsToSend_;
    ITS_BOOLEAN statRepQul_;
    ITS_OCTET   msgRef_;
    ITS_OCTET   recAddrLen_;
    ITS_OCTET   recAddrType_;
    std::string recAddr_;
    ITS_OCTET   srvCenterTS_[MAX_VALIDITY_PERIOD_LEN];
    ITS_OCTET   disTime_[MAX_VALIDITY_PERIOD_LEN];
    ITS_OCTET   status_;
    ITS_OCTET   paramInd_;
    ITS_OCTET   protId_;
    ITS_OCTET   dataCodeScheme_;
    ITS_OCTET   usrDataStr_[MAX_USER_DATA_LEN];
    ITS_UINT     usrDataStrLen_;

    ITS_BOOLEAN paramIndPresent_;
    ITS_BOOLEAN protIdPresent_;
    ITS_BOOLEAN dataCodeSchemePresent_;
    ITS_BOOLEAN usrDataPresent_;
};
