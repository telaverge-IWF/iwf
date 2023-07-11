////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: TCAP Interface Module                                                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: tim_send.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
// LOG: $Log: tim_send.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 1.2  2003/03/28 21:12:49  rsonak
// LOG: Copied from PR6.1
// LOG:
// LOG: Revision 1.1.2.1  2002/09/26 17:54:10  pmandal
// LOG: simulators for WIN messages
// LOG:
// LOG: Revision 1.1.2.1  2002/09/23 15:51:47  pmandal
// LOG: Commit send/receive code
// LOG:
// LOG: Revision 1.1.2.4  2002/09/20 14:41:21  ngoel
// LOG: add support for ITU
// LOG:
// LOG: Revision 1.1.2.3  2002/09/20 13:40:30  ngoel
// LOG: add support for ITU TCAP
// LOG:
// LOG: Revision 1.1.2.2  2002/09/19 17:53:40  ngoel
// LOG: add response encode/decode
// LOG:
// LOG: Revision 1.1.2.1  2002/09/19 17:36:36  ngoel
// LOG: TCAP Interface Module
// LOG:
// LOG:
// LOG:
//
////////////////////////////////////////////////////////////////////////////////
//

#include <tim_api.h>
#include <tcap++.h>
#include <Asn.h>

using namespace std;
using namespace its;


extern TaskQueueTransport *timRcvQueue;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will send specified TCAP component and dialogue.
 *
 *  Input Parameters:
 *      None 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is always returned.
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
int
TimSend(int dlgType, ITS_USHORT dialogueID, ITS_OCTET invId, int operation)
{
    SCCP_CallingPartyAddr origAddr;
    SCCP_CalledPartyAddr  destAddr;
    ITS_USHORT instance = timRcvQueue->GetInstance();
    ITS_HANDLE handle = ISS7_Stack;


    if (dlgType == TCAP_BEGIN_TYPE)
    {
        TCAP_AllocateDialogueId(handle, &dialogueID);
        TCAP_Begin beginDlg;

        beginDlg.SetDialogueID(dialogueID);


        ITS_OCTET slsKey, priority;
        slsKey = 0;
        priority = 0;
        beginDlg.SetQualityOfService(QOSI_RET_OPT, slsKey, priority);

        origAddr.SetSSN(TIM_Api::GetLocalSSN());
        origAddr.SetPointCode(TIM_Api::GetLocalPC());
        origAddr.SetRouteByPCSSN(true);     // GTT in originating address     
#if defined(CCITT)
        origAddr.SetInternationalRouting(true);
#else
        origAddr.SetInternationalRouting(false);
#endif
                    
        beginDlg.SetOPC(TIM_Api::GetLocalPC());
        beginDlg.SetOrigAddr(origAddr);         
        
        //Set Dest Addr

        destAddr.SetSSN(TIM_Api::GetRemoteSSN());
        destAddr.SetPointCode(TIM_Api::GetRemotePC());
        destAddr.SetRouteByPCSSN(true);     // GTT in originating address     
#if defined(CCITT)
        destAddr.SetInternationalRouting(true);
#else
        destAddr.SetInternationalRouting(false);
#endif
        beginDlg.SetDPC(TIM_Api::GetRemotePC());
        beginDlg.SetDestAddr(destAddr);     

        TCAP_Invoke invokeCpt;

#if defined(CCITT)
        invokeCpt.SetOperation(DUMMY_OP);
        invokeCpt.SetClass(CLASS_1);
#else
        invokeCpt.SetOperation(true, TCPPN_OF_PARAMETER, TCPPN_OS_PROV_VAL);
#endif
        invokeCpt.SetTimeOut(3000);

        invokeCpt.SetInvokeID(TIM_INVOKE_ID);        
        vector <byte> encodedQueryArg = TIM_Encode();
        invokeCpt.SetParameter(encodedQueryArg);

        cout << endl;
	cout << "Sending Invoke with Begin Dialogue" << endl;
        cout << endl;

        TCAP_Component::Send(handle, &beginDlg, &invokeCpt);

        TCAP_Dialogue::Send(handle, &beginDlg);
        return ITS_SUCCESS;
    }
    else if (dlgType ==  TCAP_END_TYPE)
    {
        TCAP_End endDlg;

        endDlg.SetDialogueID(dialogueID);
        TCAP_Result resultCpt;

        resultCpt.SetInvokeID(invId);        
        vector <byte> encodedResponseArg = TIM_EncodeResponse();
#if defined(CCITT)
        resultCpt.SetOperation(DUMMY_OP);
#endif
        resultCpt.SetParameter(encodedResponseArg);
        TCAP_Component::Send(handle, &endDlg, &resultCpt);

        cout << endl;
	cout << "Sending Return Result Last with End Dialogue" << endl;
        cout << endl;

        TCAP_Dialogue::Send(handle, &endDlg);

        return ITS_SUCCESS;
    }
    else
    {
        return !ITS_SUCCESS;
    }


    return ITS_SUCCESS;
}
