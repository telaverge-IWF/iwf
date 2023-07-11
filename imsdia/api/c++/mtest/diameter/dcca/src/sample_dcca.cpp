/**********************************-CPP-*************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: sample_dcca.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/11/24 20:13:08  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.3  2006/10/27 13:59:36  hbhatnagar
 * LOG: Done clean up and made changes in indentation. (Hemant)
 * LOG:
 * LOG: Revision 2.2  2006/10/27 09:46:11  hbhatnagar
 * LOG: made changes to send  the ASA and STA from application. (hemant)
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:48:57  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.4  2006/09/27 15:13:22  hbhatnagar
 * LOG: Modified for bcgi demo (badri)
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/27 09:41:17  hbhatnagar
 * LOG: Fix for Bug ID: 4383 and cleaning (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/16 11:32:18  nvijikumar
 * LOG: Modified menu in the application to reflect DCCA test cases (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:18  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: sample_dcca.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $"

#include <dia_defines.h>
#include <dia_frame.h>

#include <app_trace.h>
#include <app.h>
#include <diameter/Exceptions.h>

#include <app_dcca.h>
#include <dcca_test.h>
#include <dcca_defines.h>

#include <diameter/base/AbortSession.h>
#include <diameter/base/SessionTermination.h>

using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;

#ifdef _BCGI
using namespace diameter::bcgi;
#else
using namespace diameter::dcca;
#endif

int HandleDccaDiaMessage(its::ITS_Event& ev);

extern ITS_UINT sIdx;
extern string sessIdString;
extern SESSION_MAP sMap[];
extern int GetFreeSlot();
extern int GetSlotFromIndex(int);
Event evt1;



/*  implementation: public
 ****************************************************************************
 *  Purpose: Thread Function that handles messages received from the
 *      stack with AppId = DCCA_INTERFACE_APP_ID
 *
 *  Input Parameters:
 *      ThreadPoolThread* thr: ThreadPoolThread 
 *      void* arg: Arguments(if any)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern "C"
void 
DccaThreadFunc(ThreadPoolThread* thr, void* arg)
{
    int ret;
    engine::Worker* work = (engine::Worker *)thr;

    ITS_HANDLE handle = NULL;

    ITS_USHORT inst = work->GetInstance();
    Event evt; 

    while (!work->GetExit())
    {
        /* 
         * Wait For Event from the event queue.
         * GetNextEvent is a BlockingCall that returns
         * when an Event is posted onto the associated worker 
         * taskqueue
         */
        if (work->GetNextEvent(evt) == ITS_SUCCESS)
        {
            APP_TRACE_DEBUG(("Charging:Received an event on Instance %d", inst));

            // If the event source is from the diameter stack,
            // handle that event. Else display error.
            switch (evt.GetSource())
            {
            case ITS_DIA_SRC:
                 APP_TRACE_DEBUG(("Recv Event from IST Diameter Stack "));
                 evt1 = evt ;
                 HandleDccaDiaMessage(evt);
                 break;
            default:
                 APP_TRACE_ERROR(("Unknown Event Received"));
                 break;
            }
        }
    }
}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function handles the message received from the base
 *      diameter stack. This identifies the commands
 *      in the message and processes that command.
 *
 *  Input Parameters:
 *      ITS_Event& ev: ITS_Event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int 
HandleDccaDiaMessage(ITS_Event& ev)
{
    APP_TRACE_DEBUG(("Received Dcca Command: Event->Length = %d\n", ev.GetLength()));
    int input = 0;
    int ret = 0 ; 

    /* 
     * Access the diameter stack HANDLE 
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    if (diaFrame)
    {
        DiaMsg *dMsg;
        // Receive the message from the event received
        // if (diaFrame->Receive(ev, &dMsg) != ITS_SUCCESS)
        if(ReceiveMessageFromEvent(ev,dMsg)!= ITS_SUCCESS) 
        {
            APP_TRACE_ERROR(("Failed to Receive Diameter Message"));
            return -1;
        }
      
        switch (dMsg->GetMessageType())
        {
            // If the message is the indication from the stack, 
            // Handle the Indication. In this case, we simply update
            // the indication statistics.
        case ITS_DIA_MSG_TYPE_IND:
            APP_TRACE_DEBUG(("Received Indication from Stack %d\n", 
            dMsg->GetIndication()));
            if(dMsg->IsIndication())
            {
                if ( dMsg->GetIndication() == 0x77 )
                {     
                    APP_TRACE_DEBUG(("Tx Timer Expired"));
                }
 
                if ( dMsg->GetIndication() == 0x88 )
                    APP_TRACE_DEBUG(("Tcc Timer Expired")) ;

                if ( dMsg->GetIndication() == DISCONECT_IND_FROM_STACK )
                    APP_TRACE_DEBUG(("Received DISCONECT_IND_FROM_STACK"));

                if ( dMsg->GetIndication() == TIME_OUT_IND_FROM_STACK )
                    APP_TRACE_DEBUG(("Received TIME_OUT_IND_FROM_STACK"));

                if ( dMsg->GetIndication() == AUTH_LIFE_TIME_OUT_IND_FROM_STACK )
                    APP_TRACE_DEBUG((" Received AUTH_LIFE_TIME_OUT_IND_FROM_STACK"));

                if( dMsg->GetIndication() == AUTH_GRACE_TIME_OUT_IND_FROM_STACK )
                    APP_TRACE_DEBUG(("Received AUTH_GRACE_TIME_OUT_IND_FROM_STACK"));

            }
            break;
            // If not the one of the indications from the stack, then
           // it will be the commands to handle.
    
        case ITS_DIA_MSG_TYPE_DATA:case ITS_DIA_MSG_TYPE_IND_WITH_DATA:
        {
            APP_TRACE_DEBUG(("dMsg->GetAppId = %d", dMsg->GetApplicationId()));
            APP_TRACE_DEBUG(("dMsg->GetSessionIndex = %d", dMsg->GetSessionIndex()));

            const diameter::CommandImpl* impl = dMsg->GetCommandImpl();
            
            ITS_BOOLEAN isReq = impl->isRequest() ? ITS_TRUE:ITS_FALSE;
            try
            {
                if(impl->isError())
                {
                    HandleErrorResponse(impl);
                }
                else
                {
                    switch (impl->getCommandCode())
                    {
                    case DCCA_CC_MSG_CMD_CODE:
                        if(impl->isRequest())
                        {
                            CreditControlRequest ccreq(*impl);
                            APP_TRACE_DEBUG(("Received CCR"));
                            cout << "ccreq" << ccreq << endl;

                            CreditControlRequest ccr(*impl);
                            const CCRequestType&  ccRequestType = 
                                                  ccr.getCCRequestType();
                            int val = ccRequestType.value();
                            
                             // below is to get the current SessionId
                             ///of present event  
                            int indcheck = dMsg->GetSessionIndex();

                            int i = (-2);
                            if(val == CCRequestType::INITIAL_REQUEST || 
                               val == CCRequestType::EVENT_REQUEST )
                            {
                                if( (i = GetFreeSlot()) != ERROR )
                                {
                                    sMap[i].index = dMsg->GetSessionIndex();
                                    const SessionId& sessionId = ccr.getSessionId();
                                    sMap[i].sessionid = sessionId.value();
                                    sMap[i].valid = 1;
                            
                                }
                                else
                                {
                                    APP_TRACE_DEBUG(("NO FREE SLOT"));//NO FREE SLOT
                                }  
                            }

                            i =(-2);
                            if ( (i = GetSlotFromIndex(indcheck)) != ERROR )
                            {
                                if ( sMap[i].dMsg1 )
                                {
                                    delete sMap[i].dMsg1;
                                    sMap[i].dMsg1 = NULL ;        
                                }
                                sMap[i].dMsg1 = dMsg ;
                            }
                        }
                        else
                        {
                            CreditControlAnswer ccans(*impl);
                            const CCRequestType&  ccrt = ccans.getCCRequestType();
                            int ret = ccrt.value();
    
                            APP_TRACE_DEBUG((" Received CCA "));    
                            cout << "ccrsp" << ccans << endl;
    
                        }
                        break;
            
                    case BASE_ST_MSG_CMD_CODE:
                        if (impl->isRequest())
                        {
                            SessionTerminationRequest stReq(*impl);
                            APP_TRACE_DEBUG((" Received STR "));
                            cout << "STRequest" << stReq << endl;
                            SendSessionTerminationAnswer(impl);
                            int indcheck = dMsg->GetSessionIndex();
                            int i =(-2);
                            if ( (i = GetSlotFromIndex(indcheck)) != ERROR )
                            {
                                if ( sMap[i].dMsg1 )
                                {
                                    delete sMap[i].dMsg1;
                                    sMap[i].dMsg1 = NULL ;
                                }
                                sMap[i].valid = 0; 
                            }

                        }
                        else
                        {
                            SessionTerminationAnswer stAns(*impl);
                            APP_TRACE_DEBUG(("Received STA "));
                            cout << "STAnswer" << stAns << endl;
                            int indcheck = dMsg->GetSessionIndex();
                            int i =(-2);
                            if ( (i = GetSlotFromIndex(indcheck)) != ERROR )
                            {
                                if ( sMap[i].dMsg1 )
                                {
                                    delete sMap[i].dMsg1;
                                    sMap[i].dMsg1 = NULL ;
                                }
                                sMap[i].valid = 0;
                            }

                        }
                        break;
        

                    case BASE_AS_MSG_CMD_CODE:
                        if (impl->isRequest())
                        {
                            AbortSessionRequest asReq(*impl);
                            APP_TRACE_DEBUG((" Received ASR "));
                            cout << "ASRequest" << asReq<< endl;
                            SendAbortSessionAnswer(impl);
                        }
                        else
                        {
                            AbortSessionAnswer asAns(*impl);
                            APP_TRACE_DEBUG(("Received ASA "));
                            cout << "ASAnswer" << asAns<< endl;
                        }
                        break;


                    default:
                        //HandleBaseMessages(impl);//base protocol handling
                        break;
                    }
                }
            }
            catch (NoSuchAttributeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", e.name(), e.what()));
            }
            catch (WrongCommandTypeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", e.name(), e.what()));
            }
            catch (UnknownTypeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",  e.name(), e.what()));
            }
            catch (CodecException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", e.name(), e.what()));
            }
            catch (...)
            {
                APP_TRACE_ERROR(("Unknown Exception Caught"));
            }
           break;
        }

        default:
            APP_TRACE_ERROR(("Unknown Message Type from Stack"));
            break;
        }
     
       //  if (dMsg)
       //     delete dMsg; 
         if (dMsg)
        dMsg = NULL;    
    }
}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the request to the diameter
 *      stack based on the option selected in the menu.
 *
 *  Input Parameters:
 *      int input: Request to send.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int 
SendDccaMessage(int input, int index)
{
    try
    {
        switch(input)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 7:
            case 8:            
                SendCreditControlRequestTest(input, index); 
                break;

            case 5:
                SendSessionTerminationRequest(sessIdString, index );
                break;     

            case 6:
                cout<<"Dummy"<<endl;
                break;        
            case 99:
            {
                DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
                if (diaFrame)
                {
                    diaFrame->Terminate();
                }
                exit(EXIT_SUCCESS);
            }
            default:
                cout << endl << "please enter the correct choice";
                break;
        }

    }
    catch (...)
    {
        APP_TRACE_ERROR(("Unknown Exception Caught"));
    }
    return 0;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Multiple-Services-Credit-Control
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      MultipleServicesCreditControl object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      MultipleServicesCreditControl &multipleServicesCC: Reference to the 
 *      MultipleServicesCreditControl object, grouped AVPs of which needs 
 *      to be set.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateMultipleServicesCreditControl(MultipleServicesCreditControl 
        &multipleServicesCC , bool isRequest=true)
{
    // [1] Populate "Multiple-Services-Credit-Control" grouped AVPs. 

    if(isRequest)
    {
        // [1.1] Populate optional parameter Requested-Service-Unit 
        // Set the Requested-Service-Unit AVP.
        // The data type Requested-Service-Unit is Grouped.
        // This contains amount of requested units specified by the Diameter
        // credit-control client. The server si not required to implement all
        // the unit types, and it must treat unknown or unsupported unit 
        // types as invalid AVPs. 
        // The AVP Code of Requested-Service-Unit is 437.
        RequestedServiceUnit requestedServiceUnit;

        // [1.1.1] Populate "Requested-Service-Unit" grouped AVPs. 
        PopulateRequestedServiceUnit(requestedServiceUnit);

        // [1.1.2] Set "Requested-Service-Unit" AVP in
        //                  Multiple-Services-Credit-Control object. 
        multipleServicesCC.setRequestedServiceUnit(requestedServiceUnit);
    } // end if(isRequest)
    else
    {
        // [1.1] Populate optional parameter Granted-Service-Unit 
        // Set the Granted-Service-Unit AVP.
        // The data type Granted-Service-Unit is Grouped.
        // This contains amount of requested units specified by the Diameter
        // credit-control client. The server si not required to implement all
        // the unit types, and it must treat unknown or unsupported unit 
        // types as invalid AVPs. 
        // The AVP Code of Granted-Service-Unit is 437.
        GrantedServiceUnit grantedServiceUnit;

        // [1.1.1] Populate "Granted-Service-Unit" grouped AVPs. 
        PopulateGrantedServiceUnit(grantedServiceUnit);

        // [1.1.2] Set "Granted-Service-Unit" AVP in
        //                  Multiple-Services-Credit-Control object. 
        multipleServicesCC.setGrantedServiceUnit(grantedServiceUnit);
    } // end else (answer)

    // [1.2] Populate optional(multiple occurence) parameter 
    //                Used-Service-Unit 
    // Set the Used-Service-Unit AVP.
    // The data type Used-Service-Unit is Grouped.
    // This contains the amount of used units measured from the point when 
    // the service became active or, if interim interrogations are used during
    // the session, from the point when the previous measurement ended.
    // The AVP Code of Used-Service-Unit is 446.
    UsedServiceUnit usedServiceUnit1;

    // [1.2.1] Populate "Used-Service-Unit" grouped AVPs. 
    PopulateUsedServiceUnit(usedServiceUnit1);

    // [1.2.2] Add "Used-Service-Unit" AVP to Multiple-Services-Credit
    //                   -Control object. 
    multipleServicesCC.addUsedServiceUnit(usedServiceUnit1);

    // [1.3] Populate optional parameter Rating-Group 
    // Set the Rating-Group AVP.
    // The data type Rating-Group is Unsigned32.
    // This contains the identifer of a rating group.
    // The AVP Code of Rating-Group is 432.
    RatingGroup ratingGroup(3);
    multipleServicesCC.setRatingGroup(ratingGroup);

    if(isRequest)
    {
    } // end if(isRequest)
    else
    {
        // [1.4] Populate optional parameter Validity-Time
        // Set the Validity-Time AVP.
        // The data type Validity-Time is Unsigned32.
        // This is sent from the credit-control server to the credit-control
        // client. The AVP contains the validity time of the granted service
        // units. The measurement of the Validity-Time is started upon receipt
        // of the Credit-Control-Answer Message containing this AVP.If the 
        // granted service units have not been consumed within the validity 
        // time specified in this AVP, the credit-control client MUST send a 
        // CCR message to server,with CC-Request-Type set to UPDATE_REQUEST. 
        // The value field of the Validity-Time AVP is given in seconds.
        // The AVP Code of Validity-Time is 448.
        ValidityTime validityTime(100);
        multipleServicesCC.setValidityTime(validityTime);

        // [1.5] Populate optional parameter Final-Unit-Indication
        // Set the Final-Unit-Indication AVP.
        // The data type Final-Unit-Indication is Grouped.
        // This indicates that the Granted-Service-Unit AVP in the CCA, or in
        // the AA answer,contains the final units for the service. After these
        // units have expired, the Diameter credit-control client is 
        // responsible for executing the action indicated in the
        // Final-Unit-Action AVP.
        // The AVP Code of Final-Unit-Indication is 430.
        FinalUnitIndication finalUnitInd;
        PopulateFinalUnitIndication(finalUnitInd); 
        multipleServicesCC.setFinalUnitIndication(finalUnitInd);

    } // end else(answer)

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Requested-Service-Unit grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      RequestedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      RequestedServiceUnit &requestedServiceUnit: Reference to the
 *      RequestedServiceUnit object, grouped AVPs of which needs to be set.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateRequestedServiceUnit(RequestedServiceUnit &requestedServiceUnit)
{
    // [1] Populate "Requested-Service-Unit" grouped AVPs. 

    // [1.1] Populate optional parameter CC-Time 
    // Set the CC-Time AVP.
    // The data type CC-Time is Unsigned32.
    // This indicates the length of requested,granted or used time in seconds.
    // The AVP Code of CC-Time is 420.
    CCTime ccTime(3600);
    requestedServiceUnit.setCCTime(ccTime);

    // [1.2] Populate optional parameter CC-Money 
    // Set the CC-Money AVP.
    // The data type CC-Money is Grouped.
    // This contains amount of requested units specified by the Diameter
    // The AVP Code of CC-Money is 413.
    CCMoney ccMoney;

    // [1.2.1] Populate "CC-Money" grouped AVPs. 

    // [1.2.1.1] Populate mandatory parameter Unit-Value 
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;

    // [1.2.1.1.1] Populate "Unit-Value" grouped AVPs. 

    // [1.2.1.1.1.1] Populate mandatory parameter Value-Digits 
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(5);
    unitValue.setValueDigits(valueDigits);

    // [1.2.1.1.1.2] Populate optional parameter Exponent 
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);

    // [1.2.1.1.2] Set "Unit-Value" AVP in CC-Money. 
    ccMoney.setUnitValue(unitValue);

    // [1.2.1.2] Populate optional parameter Currency-Code 
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    ccMoney.setCurrencyCode(currencyCode);

    // [1.2.2] Set "CC-Money" AVP in Requested-Service-Unit. 
    requestedServiceUnit.setCCMoney(ccMoney);

    // [1.3] Populate optional parameter CC-Total-Octets 
    // Set the CC-Total-Octets AVP.
    // The data type CC-Total-Octets is Unsigned64.
    // This contains total number of requested,granted or used octets 
    // regardless of direction sent or received.
    // The AVP Code of CC-Total-Octets is 421.
    CCTotalOctets ccTotalOctets(6000);
    requestedServiceUnit.setCCTotalOctets(ccTotalOctets);

    // [1.4] Populate optional parameter CC-Input-Octets 
    // Set the CC-Input-Octets AVP.
    // The data type CC-Input-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // received from end user.
    // The AVP Code of CC-Input-Octets is 412.
    CCInputOctets ccInputOctets(6000);
    requestedServiceUnit.setCCInputOctets(ccInputOctets);

    // [1.5] Populate optional parameter CC-Output-Octets 
    // Set the CC-Output-Octets AVP.
    // The data type CC-Output-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // sent to end user.
    // The AVP Code of CC-Output-Octets is 414.
    CCOutputOctets ccOutputOctets(6000);
    requestedServiceUnit.setCCOutputOctets(ccOutputOctets);

    // [1.6] Populate optional parameter CC-Service-Specific-Units 
    // Set the CC-Service-Specific-Units AVP.
    // The data type CC-Service-Specific-Units is Unsigned64.
    // This contains number of service specific units (eg: number of events,
    // points) given in a selected service.
    // The AVP Code of CC-Service-Specific-Units is 417.
    CCServiceSpecificUnits ccServiceSpecificUnits(20);
    requestedServiceUnit.setCCServiceSpecificUnits(ccServiceSpecificUnits);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Granted-Service-Unit grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      RequestedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      GrantedServiceUnit &grantedServiceUnit: Reference to the
 *      GrantedServiceUnit object, grouped AVPs of which needs to be set
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateGrantedServiceUnit(GrantedServiceUnit &grantedServiceUnit)
{
    // [1] Populate "Granted-Service-Unit" grouped AVPs. 

    // [1.1] Populate optional parameter CC-Time 
    // Set the CC-Time AVP.
    // The data type CC-Time is Unsigned32.
    // This indicates the length of requested,granted or used time in seconds.
    // The AVP Code of CC-Time is 420.
    CCTime ccTime(3600);
    grantedServiceUnit.setCCTime(ccTime);

    // [1.2] Populate optional parameter CC-Money 
    // Set the CC-Money AVP.
    // The data type CC-Money is Grouped.
    // This contains amount of requested units specified by the Diameter
    // The AVP Code of CC-Money is 413.
    CCMoney ccMoney;

    // [1.2.1] Populate "CC-Money" grouped AVPs. 

    // [1.2.1.1] Populate mandatory parameter Unit-Value 
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;

    // [1.2.1.1.1] Populate "Unit-Value" grouped AVPs. 

    // [1.2.1.1.1.1] Populate mandatory parameter Value-Digits 
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(5);
    unitValue.setValueDigits(valueDigits);

    // [1.2.1.1.1.2] Populate optional parameter Exponent 
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);

    // [1.2.1.1.2] Set "Unit-Value" AVP in CC-Money. 
    ccMoney.setUnitValue(unitValue);

    // [1.2.1.2] Populate optional parameter Currency-Code 
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    ccMoney.setCurrencyCode(currencyCode);

    // [1.2.2] Set "CC-Money" AVP in Requested-Service-Unit. 
    grantedServiceUnit.setCCMoney(ccMoney);

    // [1.3] Populate optional parameter CC-Total-Octets 
    // Set the CC-Total-Octets AVP.
    // The data type CC-Total-Octets is Unsigned64.
    // This contains total number of requested,granted or used octets 
    // regardless of direction sent or received.
    // The AVP Code of CC-Total-Octets is 421.
    CCTotalOctets ccTotalOctets(6000);
    grantedServiceUnit.setCCTotalOctets(ccTotalOctets);

    // [1.4] Populate optional parameter CC-Input-Octets 
    // Set the CC-Input-Octets AVP.
    // The data type CC-Input-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // received from end user.
    // The AVP Code of CC-Input-Octets is 412.
    CCInputOctets ccInputOctets(6000);
    grantedServiceUnit.setCCInputOctets(ccInputOctets);

    // [1.5] Populate optional parameter CC-Output-Octets 
    // Set the CC-Output-Octets AVP.
    // The data type CC-Output-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // sent to end user.
    // The AVP Code of CC-Output-Octets is 414.
    CCOutputOctets ccOutputOctets(6000);
    grantedServiceUnit.setCCOutputOctets(ccOutputOctets);

    // [1.6] Populate optional parameter CC-Service-Specific-Units 
    // Set the CC-Service-Specific-Units AVP.
    // The data type CC-Service-Specific-Units is Unsigned64.
    // This contains number of service specific units (eg: number of events,
    // points) given in a selected service.
    // The AVP Code of CC-Service-Specific-Units is 417.
    CCServiceSpecificUnits ccServiceSpecificUnits(20);
    grantedServiceUnit.setCCServiceSpecificUnits(ccServiceSpecificUnits);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Used-Service-Unit grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      UsedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      UsedServiceUnit &usedServiceUnit: Reference to the
 *      UsedServiceUnit object, grouped AVPs of which needs to be set
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateUsedServiceUnit(UsedServiceUnit &usedServiceUnit)
{
    // [1] Populate "Used-Service-Unit" grouped AVPs. 

    // [1.1] Populate optional parameter CC-Time 
    // Set the CC-Time AVP.
    // The data type CC-Time is Unsigned32.
    // This indicates the length of requested,granted or used time in seconds.
    // The AVP Code of CC-Time is 420.
    CCTime ccTime(3600);
    usedServiceUnit.setCCTime(ccTime);

    // [1.2] Populate optional parameter CC-Money 
    // Set the CC-Money AVP.
    // The data type CC-Money is Grouped.
    // This contains amount of requested units specified by the Diameter
    // The AVP Code of CC-Money is 413.
    CCMoney ccMoney;

    // [1.2.1] Populate "CC-Money" grouped AVPs. 

    // [1.2.1.1] Populate mandatory parameter Unit-Value 
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;

    // [1.2.1.1.1] Populate "Unit-Value" grouped AVPs. 

    // [1.2.1.1.1.1] Populate mandatory parameter Value-Digits 
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(5);
    unitValue.setValueDigits(valueDigits);

    // [1.2.1.1.1.2] Populate optional parameter Exponent 
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);

    // [1.2.1.1.2] Set "Unit-Value" AVP in CC-Money. 
    ccMoney.setUnitValue(unitValue);

    // [1.2.1.2] Populate optional parameter Currency-Code 
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    ccMoney.setCurrencyCode(currencyCode);

    // [1.2.2] Set "CC-Money" AVP in Requested-Service-Unit. 
    usedServiceUnit.setCCMoney(ccMoney);

    // [1.3] Populate optional parameter CC-Total-Octets 
    // Set the CC-Total-Octets AVP.
    // The data type CC-Total-Octets is Unsigned64.
    // This contains total number of requested,granted or used octets 
    // regardless of direction sent or received.
    // The AVP Code of CC-Total-Octets is 421.
    CCTotalOctets ccTotalOctets(6000);
    usedServiceUnit.setCCTotalOctets(ccTotalOctets);

    // [1.4] Populate optional parameter CC-Input-Octets 
    // Set the CC-Input-Octets AVP.
    // The data type CC-Input-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // received from end user.
    // The AVP Code of CC-Input-Octets is 412.
    CCInputOctets ccInputOctets(6000);
    usedServiceUnit.setCCInputOctets(ccInputOctets);

    // [1.5] Populate optional parameter CC-Output-Octets 
    // Set the CC-Output-Octets AVP.
    // The data type CC-Output-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // sent to end user.
    // The AVP Code of CC-Output-Octets is 414.
    CCOutputOctets ccOutputOctets(6000);
    usedServiceUnit.setCCOutputOctets(ccOutputOctets);

    // [1.6] Populate optional parameter CC-Service-Specific-Units 
    // Set the CC-Service-Specific-Units AVP.
    // The data type CC-Service-Specific-Units is Unsigned64.
    // This contains number of service specific units (eg: number of events,
    // points) given in a selected service.
    // The AVP Code of CC-Service-Specific-Units is 417.
    CCServiceSpecificUnits ccServiceSpecificUnits(20);
    usedServiceUnit.setCCServiceSpecificUnits(ccServiceSpecificUnits);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Cost-Information grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      CostInformation object passed as a reference to this function.
 *
 *  Input Parameters:
 *      CostInformation &costInfo: Reference to the CostInformation 
 *      object, grouped AVPs of which needs to be set.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateCostInformation(CostInformation &costInfo)
{
    // [1] Populate "Cost-Information" grouped AVPs. 

    // [1.1] Populate mandatory parameter Unit-Value
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;
                                                                                                                             
    // [1.1.1] Populate "Unit-Value" grouped AVPs.
                                                                                                                             
    // [1.1.1.1] Populate mandatory parameter Value-Digits
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(3);
    unitValue.setValueDigits(valueDigits);
                                                                                                                             
    // [1.1.1.2] Populate optional parameter Exponent
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);
                                                                                                                             
    // [1.1.2] Set "Unit-Value" AVP in Cost-Information object.
    costInfo.setUnitValue(unitValue);

    // [1.2] Populate mandatory parameter Currency-Code
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    costInfo.setCurrencyCode(currencyCode);
                                                                                                                             
    // [1.3] Populate optional parameter Cost-Unit
    // Set the Cost-Unit AVP.
    // The data type Cost-Unit is UTF8String.
    // This specifies the applicable unit to Cost-Information when the service
    // cost is a cost per unit.Eg: cost of service is $1 per minute.
    // The AVP Code of Cost-Unit is 424.
    CostUnit costUnit("hours");
    costInfo.setCostUnit(costUnit);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Final-Unit-Indication grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      RequestedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      FinalUnitIndication &finalUnitInd: Reference to the
 *      FinalUnitIndication object, grouped AVPs of which needs to be set.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateFinalUnitIndication(FinalUnitIndication &finalUnitInd)
{
    // [1] Populate "Final-Unit-Indication" grouped AVPs.
                                                                                                                             
    // [1.1] Populate mandatory AVPs

    // [1.1.1] Populate mandatory parameter Final-Unit-Action
    // Set the Final-Unit-Action AVP.
    // The data type Final-Unit-Action is Enumerated.
    // This indicates to the credit-control client the action to be taken when
    // the user's account cannot cover the service cost.
    // The AVP Code of Final-Unit-Action is 449.
    FinalUnitAction finalUnitAction(FinalUnitAction::REDIRECT);
    finalUnitInd.setFinalUnitAction(finalUnitAction);

    // [1.2] Populate optional AVPs

    // [1.2.1] Populate optional(multiple occurence) parameter 
    //         Restriction-Filter-Rule
    // Set the Restriction-Filter-Rule AVP.
    // The data type Restriction-Filter-Rule is IpFilterRule.
    // This provides filter rules corresponding to services that are to remain
    // accessible even if there are no more service units granted. The access 
    // device has to configure the specified filter rules for the subscriber
    // and MUST drop all the packets not matching these filter.
    // The AVP Code of Restriction-Filter-Rule is 438.
    IPFilterRule ipFltRule;
    PopulateIPFilterRule(ipFltRule);
    RestrictionFilterRule restrictFltrRule(ipFltRule);
    finalUnitInd.addRestrictionFilterRule(restrictFltrRule);

    // [1.2.2] Populate optional(multiple occurence) parameter 
    //         Filter-Id
    // Set the Filter-Id AVP.
    // The data type Filter-Id is UTF8String.
    // This contains the name of the filter list for this user.
    // Zero or more Filter-Id AVPs MAY be sent in an authorisation answer.
    // The AVP Code of Filter-Id is 11.
    FilterId filterId("filterlist1"); // not clear
    finalUnitInd.addFilterId(filterId);

    // [1.2.3] Populate optional parameter Redirect-Server
    // Set the Redirect-Server AVP.
    // The data type Redirect-Server is Grouped.
    // This contains the address information of the redirect server 
    // (e.g., HTTP redirect server, SIP Server) with which the end user is to
    // be connected when the account cannot cover the service cost.It MUST be
    // present when the Final-Unit-Action AVP is set to REDIRECT.
    // The AVP Code of Redirect-Server is 434.
    RedirectServer redirectServer; 

    // [1.2.3.1] Populate Redirect-Server grouped AVPs

    // [1.2.3.1.1] Populate optional parameter Redirect-Address-Type
    // Set the Redirect-Address-Type AVP.
    // The data type Redirect-Address-Type is Enumerated.
    // This defines the address type of the address given in the 
    // Redirect-Server-Address AVP.
    // The AVP Code of Redirect-Address-Type is 433.
    RedirectAddressType redirectAddrType(RedirectAddressType::IPv4_Address); 
    redirectServer.setRedirectAddressType(redirectAddrType);

    // [1.2.3.1.2] Populate optional parameter Redirect-Server-Address
    // Set the Redirect-Server-Address AVP.
    // The data type Redirect-Server-Address is UTF8String.
    // This defines the address of the redirect server (eg: HTTP redirect 
    // server,SIP server) wih which the end user is to be connected when the 
    // account cannot cover the service cost.
    // The AVP Code of Redirect-Server-Address is 435.
    RedirectServerAddress redirectSvrAddr("192.168.4.2");
    redirectServer.setRedirectServerAddress(redirectSvrAddr);

    // [1.2.3.2] Set Redirect-Server in Final-Unit-Indication object 
    finalUnitInd.setRedirectServer(redirectServer);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the IPFilterRule object.
 *      This sets the values in the IPFilterRule object passed as a 
 *      reference to this function.
 *
 *  Input Parameters:
 *      IPFilterRule &ipFltRule: Reference to the IPFilterRule object
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void 
PopulateIPFilterRule(IPFilterRule &ipFltRule)
{
    // [1] Populate "IPFilterRule" object fields. 

    ipFltRule.action = IPFilterRule::PERMIT;
    ipFltRule.dir = IPFilterRule::IN;
    ipFltRule.proto = 0;
        // Value 0 means wildcard number that matches any IP protocol
        // If representation is exact only ipno is used
    IPFilterRule::SrcDst srcSam(IPFilterRule::SrcDst::EXACT,"192.168.9.2",0);
    IPFilterRule::SrcDst dstSam(IPFilterRule::SrcDst::EXACT,"192.168.9.3",0);
    ShortRange srcPortRng(5000,5005), dstPortRng(5006,5010);
    srcSam.portRangeList.push_front(srcPortRng);
    dstSam.portRangeList.push_front(dstPortRng);
    ipFltRule.src = srcSam;
    ipFltRule.dst = dstSam;
    ipFltRule.frag = false;
    ipFltRule.established = false;
    ipFltRule.setup = false;
    ipFltRule.ipOptionList.push_front(4);
    ipFltRule.tcpOptionList.push_front(1);
    ipFltRule.tcpOptionList.push_front(3);
    ipFltRule.tcpOptionList.push_front(4);
    ipFltRule.tcpFlagList.push_front(2);
    ipFltRule.tcpFlagList.push_front(3);
    ipFltRule.tcpFlagList.push_front(4);

}

