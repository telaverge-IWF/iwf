/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: sccp_pprint.cpp,v 1.1 2005/07/19 00:43:20 randresol Exp $
 *
 * LOG: $Log: sccp_pprint.cpp,v $
 * LOG: Revision 1.1  2005/07/19 00:43:20  randresol
 * LOG: Add SUA test programs for RFC Implementation
 * LOG:
 * LOG: Revision 1.1.2.9  2005/05/23 16:16:51  cbascon
 * LOG: check if the sccp message has the IE before trying to print it
 * LOG:
 * LOG: Revision 1.1.2.8  2005/05/23 16:08:04  cbascon
 * LOG: had wrong logic for printing spaces at the start of each line of printed
 * LOG: octets for user data
 * LOG:
 * LOG: Revision 1.1.2.7  2005/05/23 16:05:24  cbascon
 * LOG: and nore indents
 * LOG:
 * LOG: Revision 1.1.2.6  2005/05/23 16:02:20  cbascon
 * LOG: added more indents
 * LOG:
 * LOG: Revision 1.1.2.5  2005/05/23 15:58:57  cbascon
 * LOG: just added indentions for printing IEs
 * LOG:
 * LOG: Revision 1.1.2.4  2005/05/23 15:50:21  cbascon
 * LOG: added function to print the SCCP message string name
 * LOG:
 * LOG: Revision 1.1.2.3  2005/05/23 15:29:00  cbascon
 * LOG: fixed printing error
 * LOG:
 * LOG: Revision 1.1.2.2  2005/05/23 15:01:59  cbascon
 * LOG: added functions to print SCCP_IEClass ies for an SCCP_MessageClass
 * LOG:
 * LOG: Revision 1.1.2.1  2005/05/23 14:12:33  cbascon
 * LOG: added pretty print functions for SCCP parameters
 * LOG:
 *****************************************************************************/

#include <its++.h>
#include <sccp++.h>
#include <iostream>
#include <sccp_pprint.h>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif


void
PrintCredit(SCCP_Credit *credit)
{
    if (credit!=NULL)
    {
        cout << "Credit = "
             << (unsigned int)credit->GetCredit()
             << endl;
    }
    else
    {
        cout << "No credit" << endl;
    }
}

void
PrintReference(SCCP_RefNum* slr, char* which)
{
    if (slr != NULL)
    {
        cout << which
             << " Local Reference = "
             << slr->GetRefNum()
             << endl;
    }
    else 
    {
        cout << which << " Local Reference not found" << endl;
    }
}

void
PrintProtocolClass(SCCP_ProtocolClass *pc)
{
    if (pc != NULL)
    {
        cout << "Protocol Class = "
             << (unsigned int)pc->GetProtocolClass()
             << endl;
    }
    else 
    {
        cout << "No Protocol Class" << endl;
    }
}

void
PrintAddr(SCCP_Address* called_pa, char* which)
{
    cout << which << " Party Address:" << endl;

    if (called_pa != NULL)
    {
        if (called_pa->HasPointCode()) 
        {
            cout << "    Point Code = "
                 << called_pa->GetPointCode()
                 << endl;
        }
        else 
        {
            cout << "    No Point Code" << endl;
        }
        if (called_pa->HasSSN())
        {
            cout << "    Subsystem Number = "
                 << (unsigned int)called_pa->GetSSN()
                 << endl;
        }
        else
        {
            cout << "    No Subsystem Number" << endl;
        }
        if (called_pa->IsInternationalRouting())
        {
            cout << "    International Routed" << endl;
        }
        else
        {
            cout << "    National Routed" << endl;
        }
        if (called_pa->HasGlobalTitle())
        {
            cout << "    Has Global Title" << endl;
        }
        else
        {
            cout << "    No Global Title" << endl;
        }
    }
    else
    {
        cout << "    No address specified" << endl;
    }
}

void
PrintData(SCCP_UserData *ud)
{
    if (ud != NULL)
    {
        ITS_OCTET data[255];
        int len;

        cout << "UserData:" << endl;

        ud->GetUserData(data, len);
        if(len > 0)
        {
            for (int i = 0; i < len; i++)
            {
                if (i % 20 == 0)
                {
                    printf("    ");
                }

                printf("%02x ",data[i]);
                if (!((i+1) % 20))
                {
                    cout << endl;
                }
            }
            cout << endl;
        }
        else
        {
            cout << "Length = 0" << endl;
        }
    }
    else
    {
        cout << "No UserData" << endl;
    }
}

void
PrintCause(SCCP_Cause* rc, char* which)
{
    if (rc != NULL) 
    {
        cout << which
             << " Cause = "
             << (unsigned int)rc->GetCause()
             << endl;
    }
    else
    {
        cout << which << " Cause not specified";
    }
}

void
PrintHopCount(SCCP_HopCount* hc)
{
    if (hc != NULL)
    {
        cout << "Hop Counter = "
             << (unsigned int)hc->GetHopCount()
             << endl;
    }
    else
    {
        cout << "No Hop Counter" << endl;
    }
}

void
PrintSegmentReassem(SCCP_SegmentReassem* sr)
{
    if (sr!=NULL) 
    {
        cout << "Segmenting/Reassembling = "
             << (unsigned int)sr->GetSegmentReassem()
             << endl;
    }
    else
    {
        cout << "Not exist" << endl;
    }
}

void
PrintSequenceSegment(SCCP_SequenceSegment* ss)
{
    if (ss != NULL)
    {
        cout << "Transmit Sequence = "
             << (unsigned int)ss->GetTransmitSequenceNumber()
             << endl;
        cout << "Receive Sequence  = "
             << (unsigned int)ss->GetReceiveSequenceNumber()
             << endl;
        cout << "Have more data    = "
             << (unsigned int)ss->GetHaveMore()
             << endl;
    }
    else
    {
        cout << "Sequence is not exist";
    }
}

void
PrintRSN(SCCP_ReceiveSequenceNum* ss)
{
    if (ss != NULL)
    {
        cout << "Receive Sequence  = "
             << (unsigned int)ss->GetReceiveSequenceNumber()
             << endl;
        cout << "Have more data    = "
             << (unsigned int)ss->GetHaveMore()
             << endl;
    }
    else 
    {
        cout << "RSN not included" << endl;
    }
}

void
PrintSCCPIE(const SCCP_IEClass *ie)
{
    if (ie == NULL) return;

    switch (ie->GetID())
    {
    case SCCP_PRM_EOP:
        break;
    case SCCP_PRM_DEST_LOCAL_REF:
        PrintReference((SCCP_RefNum*) ie, "Destination");
        break;
    case SCCP_PRM_SRC_LOCAL_REF:
        PrintReference((SCCP_RefNum*) ie, "Source");
        break;
    case SCCP_PRM_CALLED_PARTY_ADDR:
        PrintAddr((SCCP_Address*) ie, "Called");
        break;
    case SCCP_PRM_CALLING_PARTY_ADDR:
        PrintAddr((SCCP_Address*) ie, "Calling");
        break;
    case SCCP_PRM_PROTOCOL_CLASS:
        PrintProtocolClass((SCCP_ProtocolClass*)ie);
        break;
    case SCCP_PRM_SEGMENT_REASSEM:
        PrintSegmentReassem((SCCP_SegmentReassem*) ie);
        break;
    case SCCP_PRM_RCV_SEQ_NUM:
        PrintRSN((SCCP_ReceiveSequenceNum*) ie);
        break;
    case SCCP_PRM_SEQUENCE_SEGMENT:
        PrintSequenceSegment((SCCP_SequenceSegment*) ie);
        break;
    case SCCP_PRM_CREDIT:
        PrintCredit((SCCP_Credit*)ie);
        break;
    case SCCP_PRM_RELEASE_CAUSE:
        PrintCause((SCCP_Cause*) ie, "Release");
        break;
    case SCCP_PRM_RETURN_CAUSE:
        PrintCause((SCCP_Cause*) ie, "Return");
        break;
    case SCCP_PRM_RESET_CAUSE:
        PrintCause((SCCP_Cause*) ie, "Reset");
        break;
    case SCCP_PRM_ERROR_CAUSE:
        PrintCause((SCCP_Cause*) ie, "Error");
        break;
    case SCCP_PRM_REFUSAL_CAUSE:
        PrintCause((SCCP_Cause*) ie, "Refusal");
        break;
    case SCCP_PRM_DATA:
        PrintData((SCCP_UserData*) ie);
        break;
    case SCCP_PRM_SEGMENTATION:
        
        break;
    case SCCP_PRM_HOP_COUNTER:
        PrintHopCount((SCCP_HopCount*) ie);
        break;
    case SCCP_PRM_IMPORTANCE:
        break;
    case SCCP_PRM_LONG_DATA:
        break;
    case SCCP_PRM_ISNI:
        break;
    case SCCP_PRM_ROUTING_LABEL:
        break;
    }
}

void
PrintSCCPMessage(SCCP_MessageClass *msg)
{
    if (msg == NULL)
    {
        cout << "PrintSCCPMessage: SCCP_MessageClass is null" << endl;
    }

    SCCP_MSG_DESC *desc = SCCP_GetDescriptor(msg->GetMsgType());

    cout << "***************************************************" << endl;
    PrintSCCPMessageString(msg);

    /* print fixed mandatory parameters */
    for (int i = 0; i < desc->nmArgs; ++i)
    {
        if (msg->FindIE(desc->mArgs[i]) != NULL)
        {
            cout << "  ";
            PrintSCCPIE(msg->FindIE(desc->mArgs[i]));
        }
    }

    /* print variable mandatory parameters */
    for (int i = 0; i < desc->nvArgs; ++i)
    {
        if (msg->FindIE(desc->vArgs[i]) != NULL)
        {
            cout << "  ";
            PrintSCCPIE(msg->FindIE(desc->vArgs[i]));
        }
    }

    /* print fixed mandatory parameters */
    for (int i = 0; i < desc->noArgs; ++i)
    {
        if (msg->FindIE(desc->oArgs[i]) != NULL)
        {
            cout << "  ";
            PrintSCCPIE(msg->FindIE(desc->oArgs[i]));
        }
    }

    cout << "***************************************************" << endl;
}

void
PrintSCCPMessageString(its::SCCP_MessageClass *msg)
{
    if (msg == NULL)
    {
        cout << __FILE__ << ": " << __LINE__ << ": ";
        cout << "PrintSCCPMessageString: SCCP_MessageClass is null" << endl;
        return;
    }

    cout << "SCCP Msg: ";

    switch (msg->GetMsgType())
    {
    case SCCP_MSG_CR:
        cout << "ConnectionRequest" << endl;
        break;
    case SCCP_MSG_CC:
        cout << "ConnectionConfirm" << endl;
        break;
    case SCCP_MSG_CREF:
        cout << "ConnectionRefused" << endl;
        break;
    case SCCP_MSG_RLSD:
        cout << "Released" << endl;
        break;
    case SCCP_MSG_RLC:
        cout << "ReleaseComplete" << endl;
        break;
    case SCCP_MSG_DT1:
        cout << "DataForm1" << endl;
        break;
    case SCCP_MSG_DT2:
        cout << "DataForm2" << endl;
        break;
    case SCCP_MSG_AK:
        cout << "DataAcknowledgement" << endl;
        break;
    case SCCP_MSG_UDT:
        cout << "Unitdata" << endl;
        break;
    case SCCP_MSG_XUDT:
        cout << "ExtendedUnitdata" << endl;
        break;
    case SCCP_MSG_UDTS:
        cout << "UnitdataService" << endl;
        break;
    case SCCP_MSG_XUDTS:
        cout << "ExtendedUnitdataService" << endl;
        break;
    case SCCP_MSG_ED:
        cout << "ExpeditedData" << endl;
        break;
    case SCCP_MSG_EA:
        cout << "ExpeditedDataAcknowledgement" << endl;
        break;
    case SCCP_MSG_RSR:
        cout << "ResetRequest" << endl;
        break;
    case SCCP_MSG_RSC:
        cout << "ResetConfirm" << endl;
        break;
    case SCCP_MSG_ERR:
        cout << "Error" << endl;
        break;
    case SCCP_MSG_IT:
        cout << "InactivityTest" << endl;
        break;
    case SCCP_MSG_NOTICE:
        cout << "Notice" << endl;
        break;
    case SCCP_MSG_LUDT:
        cout << "LongUnitdata" << endl;
        break;
    case SCCP_MSG_LUDTS:
        cout << "LongUnitdataService" << endl;
        break;
    }
}