/////////////////////////////////-/-H-/-//////////////////////////////////////
//                                                                          //
//     Copyright 2009 IntelliNet Technologies, Inc. All Rights Reserved.    //
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
//  ID: $Id: frequencylistrel8.h,v 1.1.2.1 2010/03/23 05:39:43 rajeshak Exp $
//
//  LOG:$Log: frequencylistrel8.h,v $
//  LOG:Revision 1.1.2.1  2010/03/23 05:39:43  rajeshak
//  LOG:Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: frequencylistrel8.h,v 1.1.2.1 2010/03/23 05:39:43 rajeshak Exp $"

#ifndef BSSLAP_IE_FREQUENCYLIST_REL8_H
#define BSSLAP_IE_FREQUENCYLIST_REL8_H

#include <bsslap/ie/infoelement.h>
#include <vector>

namespace bsslap {
namespace ie {

class FrequencyListRel8 : public InfoElement
{
    friend class InfoElement;

public :

    typedef std::vector<ITS_USHORT> ArfcnVector;
    typedef std::vector<ITS_USHORT> RrfcnVector;
    typedef std::vector<ITS_USHORT> FrequencyVector;

    enum Type
    {
        BITMAP          =   0x00U,
        NON_BITMAP      =   0x02U,
        RANGE512        =   0x04U,
        RANGE256        =   0x05U,
        RANGE128        =   0x06U,
        VARIABLE_BITMAP =   0x07U
    };
    
    FrequencyListRel8(ITS_OCTET lowId = 0xFFU,
                  ITS_OCTET highId = 0xFFU)
        :InfoElement(FREQUENCY_LIST_REL8),
        lowpart_formatID(lowId), 
        highpart_formatID(highId)
    {
    }

    /**
     *
     */
    void AddARFCN(ITS_OCTET value)
    {
        arfcn.push_back(value);
    }

    /**
     *  
     */
    ArfcnVector& GetARFCN()
    {
        return arfcn;
    }

    /**
     *
     */
    void AddRRFCN(ITS_OCTET value)
    {
        rrfcn.push_back(value);
    }

    /**
     *  
     */
    RrfcnVector& GetRRFCN()
    {
        return rrfcn;
    }

    /**
     *
     */
    void SetHighPartFormatID(ITS_OCTET value)
    {
        highpart_formatID = value;
    }

    /**
     *
     */
    ITS_OCTET GetHighPartFormatID() const
    {
        return highpart_formatID;
    }

    /**
     *
     */
    void SetLowPartFormatID(ITS_OCTET value)
    {
        lowpart_formatID = value;
    }

    /**
     *
     */
    ITS_OCTET GetLowPartFormatID() const
    {
        return lowpart_formatID;
    }

    /**
     * Get frequency
     */
    FrequencyVector& GetFrequencyList()
    {
        return frequencyList;
    }
    
    /**
     * Overload operator []
     * @param index
     */
    ITS_USHORT& operator[] (int index)
    {
        if ( index < GetSizeOfFrequencyList() )
        {
            return frequencyList[index];
        }
        else
        {
            ITN_THROW(IndexOutOfBoundsException, "Index of Bound");
        }
    }

    /**
     * Get frequencyList size
     */
    int GetSizeOfFrequencyList()
    {
        return frequencyList.size();
    }

    /**
     * Get size of RRFCN
     */
    int GetSizeOfRrfcn()
    {
        return rrfcn.size();
    }
protected :

    /**
     *
     */
    FrequencyListRel8(const ITS_OCTET* buf, int& len);

    /**
     *
     */
    virtual void Encode(ITS_OCTET *buf, int& len) const;

    /**
     *
     */
    InfoElement* Clone() const
    {
        return new FrequencyListRel8(*this);
    }   

    virtual void Print(std::ostream& out) const;

private :

    /*********************************************************
     *  Following utility function provide different format  *
     *  decode.                                              *
     *********************************************************/
    
    /**
     * For a RF channel with ARFCN = N belonging to the 
     * frequency list the bit is coded with a " 1 ", if
     * not code with a " 0 "; N = 1, 2, .... , 124
     */
    void DecodeBitMapFormat(const ITS_OCTET* buf, int& len);

    /**
     * Range 1024 format: W(1) to W(M). Due to octet boundaries,
     * some bits are not used at the end of the last octet,
     * these bits must set to 0.
     */
    void DecodeRange1024Format(const ITS_OCTET* buf, int& len);

    /**
     * Range 512 format: W(1) to W(M). Due to octet boundaries,
     * some bits are not used at the end of the last octet,
     * these bits must set to 0.
     */
    void DecodeRange512Format(const ITS_OCTET* buf, int& len);

    /**
     * Range 256 format: W(1) to W(M). Due to octet boundaries,
     * some bits are not used at the end of the last octet,
     * these bits must set to 0.
     */
    void DecodeRange256Format(const ITS_OCTET* buf, int& len);

    /**
     * Range 128 format: W(1) to W(M). Due to octet boundaries,
     * some bits are not used at the end of the last octet,
     * these bits must set to 0.
     */
    void DecodeRange128Format(const ITS_OCTET* buf, int& len);

    /**
     *  Following utility function provide different format
     *  decode.
     */
    void DecodeVariableBitMapFormat(const ITS_OCTET* buf, int& len);

    /**
     * This function is the sepcial algorithm for computing
     * Range 1024 format to Range 128 format ARFCN
     */
    void ComputeFrequency(int, ITS_USHORT*, int);

    /**
     * This overloaded function is to retrieve the values of each W(i)
     * on 1024 and 512 format
     */
    void RetreiveValueOfW(ITS_USHORT* W, const ITS_OCTET* byte_offset,
                              int M, int& bit_offset);

    /**
     * This function is get result of calculation of W(i)
     * of 1024 range format and 512 range format
     */
    ITS_USHORT GetCalculationOfW(int, const ITS_OCTET*, int&);


    /*************************************************************
     *               Data members                                *
     *************************************************************/

    ArfcnVector        arfcn;
    RrfcnVector        rrfcn;
    FrequencyVector    frequencyList;
    ITS_OCTET          highpart_formatID;
    ITS_OCTET          lowpart_formatID;
};

} // end of namespace ie 
} // end of namespace bsslap

#endif // !BSSLAP_IE_FREQUENCYLIST_H

