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
//  ID: $Id: tim_recv.cpp,v 9.1 2005/03/23 12:52:46 cvsadmin Exp $
//
// LOG: $Log: tim_recv.cpp,v $
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 1.2  2003/03/28 21:12:49  rsonak
// LOG: Copied from PR6.1
// LOG:
// LOG: Revision 1.1.2.1  2002/09/26 17:54:10  pmandal
// LOG: simulators for WIN messages
// LOG:
// LOG: Revision 1.1.2.2  2002/09/23 16:58:47  ngoel
// LOG: add error handling
// LOG:
// LOG: Revision 1.1.2.1  2002/09/23 15:51:47  pmandal
// LOG: Commit send/receive code
// LOG:
// LOG: Revision 1.1.2.5  2002/09/20 14:41:21  ngoel
// LOG: add support for ITU
// LOG:
// LOG: Revision 1.1.2.4  2002/09/20 13:40:30  ngoel
// LOG: add support for ITU TCAP
// LOG:
// LOG: Revision 1.1.2.3  2002/09/20 13:17:47  ngoel
// LOG: remove warning
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
 *      This function will receive TCAP component and dialogue. In this sample
 *  app receive function is registered as callback to Accelero work item in xml 
 *  configuration. Work item dispatched the Receive function to work item 
 * thread. After Receive function returns it is again dispatched to the same 
 * thread.
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
extern "C" int TIM_ReceiveProc(void *arg )
{
    ITS_Event ev;
    ITS_Event event;
    TCAP_Dialogue* dlg  = NULL;
    TCAP_Component* cpt = NULL;
    ITS_HANDLE  handle = ISS7_Stack;

    if ( timRcvQueue == NULL)
    {
         return ITS_SUCCESS;
    }

    timRcvQueue->GetNextEvent(ev); 


    if (TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_DLG)
    {
        

        int res = TCAP_Dialogue::Receive(handle, ev, &dlg);

        if (res != ITS_SUCCESS)
        {
            cout << "Receive Dilog Failed" << endl;
            delete dlg;
            delete cpt;
            return res;
        }

        // Must be a begin. 

        if (dlg->GetDialogueType() == TCAP_BEGIN_TYPE)
        {

            cout << "TCAP Begin Received" << endl;
            TCAP_Begin* beginDlg = static_cast<TCAP_Begin*>(dlg);
            ITS_USHORT dlgId = beginDlg->GetDialogueID();

            // Get the component.
    
            if (dlg->IsComponentPresent())
            {
                res = timRcvQueue->GetNextEvent(event);

                if (res != ITS_SUCCESS)
                {
                    cout << "GetNextEvent Failed" << endl;
                    delete dlg;
                    delete cpt;
                    return res;
                }
            }
            else
            {
                 TimSend(TCAP_END_TYPE, dlgId, 0, 0);
            }

            // Must be a component.

            if(TCAP_MSG_TYPE((&event.GetEvent())) == ITS_TCAP_CPT)
            {
                res = TCAP_Component::Receive(handle, event, dlg, &cpt);

                if (res != ITS_SUCCESS)
                {
                    cout << "Component Receive Failed";
                    delete dlg;
                }

                // Must be an invoke. 

                if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
                {

                    TCAP_Invoke* invokeCpt = static_cast<TCAP_Invoke*>(cpt);

                     cout << "Received TCAP Invoke" << endl;

                    // Retrieve the operation.

                   ITS_OCTET invokeId = invokeCpt->GetInvokeID(); 

#if defined(CCITT)
                    ITS_LONG       operation;
                   invokeCpt->GetOperation(operation);
#else
                    bool            isNational;
                    ITS_OCTET       family;
                    ITS_OCTET       operation;
                   invokeCpt->GetOperation(isNational, family, operation);
#endif

                   vector<byte> paramData;
                   invokeCpt->GetParameter(paramData);

                   TIM_Decode(paramData);
                   TimSend(TCAP_END_TYPE, dlgId, invokeId, 0);



                }
                else // Not an Invoke
                {
                    cout << "Received Componenet Not Invoke" << endl;
                    cout << "Not a valid TCAP Invoke Operation" << endl;
                }               
            }
            else // Not a Component
            {
                cout << "Did not Receive A Component";
                cout << "Response/Reject to a timed out Dialogue ?" << endl;
            }
         }
         else if (dlg->GetDialogueType() == TCAP_END_TYPE)
         {
            cout << "End Dialogue  Received" << endl;
            if (dlg->IsComponentPresent())
            {
                res = timRcvQueue->GetNextEvent(event);

                if (res != ITS_SUCCESS)
                {
                    cout << "GetNextEvent Failed" << endl;
                    delete dlg;
                    delete cpt;
                    return res;
                }
            }
            else
            {
                delete dlg;
                delete cpt;
                return ITS_SUCCESS;
            }

            // Must be a component.

            if(TCAP_MSG_TYPE((&event.GetEvent())) == ITS_TCAP_CPT)
            {
                res = TCAP_Component::Receive(handle, event, dlg, &cpt);

                if (res != ITS_SUCCESS)
                {
                    cout << "Component Receive Failed";
                    delete dlg;
                    delete cpt;
                    return res;
                }

                // Must be an invoke. 

                if (cpt->GetComponentType() == TCPPT_TC_RESULT_L)
                {

                    TCAP_Result* resultCpt = static_cast<TCAP_Result*>(cpt);

                     cout << "Received TCAP Result" << endl;

                     ITS_OCTET invokeId = resultCpt->GetInvokeID(); 

                   vector<byte> paramData;
                   resultCpt->GetParameter(paramData);

                   TIM_DecodeResponse(paramData);

                }
                else // Not an Result
                {
                    cout << "Received Not Result Last " << endl;
                }               
            }
            else // Not a Component
            {
                cout << "Did not Receive A Component";
            }

         }
         else
         {
             cout << "Received Unexpected TCAP Dialogue" << endl;
             delete dlg;
             delete cpt;
             return !ITS_SUCCESS;
         }
    }

     delete dlg;
     delete cpt;
    return ITS_SUCCESS;
}
