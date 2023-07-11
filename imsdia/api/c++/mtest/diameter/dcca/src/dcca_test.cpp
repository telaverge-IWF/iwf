/*     copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dcca_test.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.5  2007/02/21 06:59:10  hbhatnagar
 * LOG: changed the value passed to ServiceIdentifier from string to unsigned int
 * LOG:
 * LOG: Revision 2.4  2006/11/24 20:13:08  hbhatnagar
 * LOG: Made changes as per the new application and interface independent Dcca
 * LOG: Module and cleanup
 * LOG:
 * LOG: Revision 2.3  2006/10/27 09:44:39  hbhatnagar
 * LOG: made changes for the AppId in STR and ASR(Hemant)
 * LOG:
 * LOG: Revision 2.2  2006/10/26 15:09:38  hbhatnagar
 * LOG: done cleanup and changes for CCFH (Hemant)
 * LOG:
 * LOG: Revision 2.1  2006/10/25 10:48:57  hbhatnagar
 * LOG: Integration with ITS_Diameter
 * LOG:
 * LOG: Revision 1.1.2.6  2006/09/27 15:13:22  hbhatnagar
 * LOG: Modified for bcgi demo (badri)
 * LOG:
 * LOG: Revision 1.1.2.5  2006/09/27 11:21:36  hbhatnagar
 * LOG: Cleaning and Fix for Bug ID: 4383 (badri)
 * LOG:
 * LOG: Revision 1.1.2.4  2006/09/16 12:08:22  nvijikumar
 * LOG: Modified the menu for DCCA test case (badri)
 * LOG:
 * LOG: Revision 1.1.2.3  2006/09/16 11:32:18  nvijikumar
 * LOG: Modified menu in the application to reflect DCCA test cases (badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/09/16 10:48:29  nvijikumar
 * LOG: Modified the test case menu (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/09/16 07:37:17  nvijikumar
 * LOG: DCCA mtest First Cut (badri)
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: dcca_test.cpp,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $"

#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>
#include <app.h>

#include <app_dcca.h>
#include <dcca_test.h>
#include <diameter/base/SessionTermination.h>
#include <diameter/base/AbortSession.h>

#include <dcca_defines.h>

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

/* this is Global array of structures 
 * used by all the events 
 */
SESSION_MAP sMap[64] = {0};

/*
 * This method gets the index of free slot (i.e between 0 and MAX_SESS_MAP)
 * in Session Map array else returns ERROR
 */
int
GetFreeSlot()
{
    for(int i = 0; i < MAX_SESS_MAP; i++)
    {
        if( !sMap[i].index )
        {
            return i;
        }
    }
    return ERROR;
}

int
GetSlotFromIndex( int index)
{
    for(int i = 0; i < MAX_SESS_MAP; i++)
    {
        if(sMap[i].index && (index == sMap[i].index))
        {
            return i;
        }
    }
    return ERROR;

}


// Global Object
CreditControlRequest ccrold(false,false);
int checkInitial = 0;
string sessIdString;
extern Event evt1;

int 
DisplaySession()
{
    string input;
    int ret = 0;
    
    cout <<"Available sessions: ";
    for(int i = 0; i < MAX_SESS_MAP; i++)
    {
        if(sMap[i].valid == 1 )
        {
            cout << sMap[i].index << " ";
        }
    }

    cout << endl;
    cin >> input;

    ret = atoi(input.c_str());
    return ret;
}

int 
DisplayDccaMenuTestServer(int *index)
{
    string input;
    int ret = 0;
    do
    {
        cout << endl << "Select Dcca Command"<<endl<<endl;
        cout <<" 1: Send CCA - with Success. "<<endl;
        cout <<" 2: Send CCA - with Limited Success. "<<endl;
        cout <<" 3: Send CCA - with Failure (Temporary and Permanent errors)."<<endl;
        cout <<" 4: Send ASR - Abort Session Request."<<endl;
        cout <<" 5: Send CCA - with Credit Control Failure Handling."<<endl;
        cout <<"6: Post dummy or 99: to Exit"<<endl;
        cin >> input;

        ret = atoi(input.c_str());
        
        if(ret == 1 || ret == 2 || ret == 3 || ret == 4 || ret == 5 )
        {
            *index = DisplaySession();
        }

    } while ((ret < 1 || ret > 6 ) && ret != 99  );    
   
    return ret;
}




int
SendDccaMessageServer(int input, int index )
{
    bool flag = false;
    int i = (-2);        
    switch(input)
    {
        case 1:
        case 2:
        case 3:
        case 5:
            if ((i = GetSlotFromIndex(index)) != ERROR )
            {
                flag = true;
                if ( sMap[i].dMsg1 != NULL)
                {
                    flag = true;             
                    const diameter::CommandImpl* impl = 
                                        sMap[i].dMsg1->GetCommandImpl();

                    if (impl->getCommandCode() == DCCA_CC_MSG_CMD_CODE )    
                    {
                                
                        SendCreditControlAnswerTest(impl, input, index);
                        CreditControlRequest ccr(*impl);
                        const CCRequestType&  ccRequestType1 = ccr.getCCRequestType();
                        int val = ccRequestType1.value();

                        if ( (ccRequestType1.value() == CCRequestType::TERMINATION_REQUEST) ||
                             (ccRequestType1.value() == CCRequestType::EVENT_REQUEST ))
                        {
                            if (sMap[i].dMsg1)
                            {
                                delete sMap[i].dMsg1;
                                sMap[i].dMsg1 = NULL;
                            }
                        }
                        break;
                    }
                }
                else 
                {
                    cout <<endl<< " The Msg Ptr is Null" <<endl;    
                    return 0;
                }
            }    

        if ( flag == false)
        {
            cout<<endl<< "This session index is invalid."<<endl;
            return 0;    
        }
        break;
    
        case 4:
        SendAbortSessionRequest(sessIdString,index);
        break;
    
        case 6:
        cout<<endl<<"Dummy"<<endl;
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
    return 0;
}


ITS_UINT sIdx;
const char* x ="abc@xyz";

int 
SendCreditControlRequestTest( int requestType, int index)
{
    // [1] Create CreditControlRequest object.
    CreditControlRequest ccr(false,false);
    int num = 0;
    int i = (-2);
    try
    {
        if ( requestType == INITIAL || requestType == EVENT || requestType == 8 )
        {
            num = 0;
         
            DiaFrame *diaFrame = DiaFrame::GetDiaFrame();

            if (diaFrame->AllocateSessionIndex(DCCA_INTERFACE_APP_ID,
                sIdx, sessIdString)== ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("Successful Session Allocation"));
                APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s",
                       sIdx, sessIdString.c_str()));

                if( (i = GetFreeSlot())!= ERROR )
                {                
                    sMap[i].sessionid = sessIdString;
                    sMap[i].index  = sIdx;    
                    
                    if (requestType == 1 )
                        sMap[i].valid  = 1;
                    else 
                        sMap[i].valid  = 0;
                        
                }
                else 
                {
                    APP_TRACE_DEBUG(("sMap Allocation failed: no free slot"));
                }
            
                ccr.setSessionId(SessionId(sessIdString));
                ccr.setSessionIndex(sIdx);    
           }
           else
           {
                APP_TRACE_ERROR(("Failure in Session Allocation"));
               return (ITS_ESENDFAIL);
           }
      
        }
        else
        {
            if((i = GetSlotFromIndex( index))!= ERROR )
            {
                if ( requestType == TERMINATION )  
                    sMap[i].valid = 0;
  
                num = ++sMap[i].snum;
                ccr.setSessionId(SessionId(sMap[i].sessionid));
                ccr.setSessionIndex(sMap[i].index);
            }
        }

        OriginHost originHost(GetOriginHost());
        ccr.setOriginHost(originHost);
    
        OriginRealm originRealm(GetOriginRealm());
        ccr.setOriginRealm(originRealm);
        
        if (requestType == 7 ) 
        {
            DestinationRealm destinationRealm(x);        
            ccr.setDestinationRealm(destinationRealm);
        }
        else
        {
            DestinationRealm destinationRealm(GetDestinationRealm());
            ccr.setDestinationRealm(destinationRealm);
        }    

        AuthApplicationId authApplicationId(DCCA_INTERFACE_APP_ID);
        ccr.setAuthApplicationId(authApplicationId);

        ServiceContextId serviceContextId("123.0.91.7.32260@3gpp.org");
        ccr.setServiceContextId(serviceContextId);
     
        switch ( requestType )
        {
            case INITIAL:
            {
                CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;

            case UPDATE:
            case 7:
            {
                CCRequestType ccRequestType(CCRequestType::UPDATE_REQUEST);
                ccr.setCCRequestType(ccRequestType);    
            }
            break;

            case TERMINATION:
            {
                CCRequestType ccRequestType(CCRequestType::TERMINATION_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;

            case EVENT:
            case 8:
            {
                CCRequestType ccRequestType(CCRequestType::EVENT_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;
    
            default:
            cout << endl << "Invalid Request Type" << endl;

     }

        CCRequestNumber ccRequestNumber(num);
        ccr.setCCRequestNumber(ccRequestNumber);

        DestinationHost destinationHost(GetDestinationHost());
        ccr.setDestinationHost(destinationHost);

        UserName userName("sip:user@3gppnetwork.com");
        ccr.setUserName(userName);

        CCSubSessionId  cCSubSessionId(1234u);
        ccr.setCCSubSessionId ( cCSubSessionId  ); 

        ccr.setAcctMultiSessionId ( AcctMultiSessionId ( "5678" ));  
    
        OriginStateId originStateId(1);
        // API should be provided for getting the Origin-State-Id value.
        ccr.setOriginStateId(originStateId);

        EventTimestamp eventTimestamp(2006);
        ccr.setEventTimestamp(eventTimestamp);

        SubscriptionId subscriptionId1;
        SubscriptionIdType subscriptionIdType
                          (SubscriptionIdType::END_USER_SIP_URI);
        subscriptionId1.setSubscriptionIdType(subscriptionIdType);
        SubscriptionIdData subscriptionIdData("sip:alice@atlanta.com");
        subscriptionId1.setSubscriptionIdData(subscriptionIdData);
        ccr.addSubscriptionId(subscriptionId1);

        // The Type of ServiceIdentifier was previously UTFString 
        // now changed to Unsigned32.
        ccr.setServiceIdentifier(ServiceIdentifier(1501u));   
                              
        TerminationCause terminationCause(
                          TerminationCause::DIAMETER_USER_MOVED);
        ccr.setTerminationCause(terminationCause);

        RequestedServiceUnit requestedServiceUnit ; 
        PopulateRequestedServiceUnit( requestedServiceUnit);

    
     
        if ( requestType == 8)
        {
            RequestedAction requestedAction(RequestedAction::DIRECT_DEBITING);
            ccr.setRequestedAction(requestedAction);
        }

    
        UsedServiceUnit usedServiceUnit;  
        PopulateUsedServiceUnit(usedServiceUnit);  
        ccr.addUsedServiceUnit(usedServiceUnit);    

        MultipleServicesIndicator  multipleServicesIndicator(
                 MultipleServicesIndicator::MULTIPLE_SERVICES_SUPPORTED);

        ccr.setMultipleServicesIndicator(multipleServicesIndicator);

        MultipleServicesCreditControl  multipleServicesCC1;
        PopulateMultipleServicesCreditControl(multipleServicesCC1,true);
        ccr.addMultipleServicesCreditControl(multipleServicesCC1);
        
        ServiceParameterInfo  serviceParameterInfo;  
        serviceParameterInfo.setServiceParameterType( ServiceParameterType (2u)); 
        serviceParameterInfo.setServiceParameterValue( ServiceParameterValue ( "mno@pqr" ) );  
        ccr.addServiceParameterInfo( serviceParameterInfo ); 

        ccr.setCCCorrelationId( CCCorrelationId ("Corrdcca")); 

        UserEquipmentInfo userEquipInfo;
        UserEquipmentInfoType userEquipInfoType(UserEquipmentInfoType::IMEISV);
        userEquipInfo.setUserEquipmentInfoType(userEquipInfoType);

        UserEquipmentInfoValue userEquipInfoValue("123400001111222201");
        userEquipInfo.setUserEquipmentInfoValue(userEquipInfoValue);

        ccr.setUserEquipmentInfo(userEquipInfo);

    

        static int ind = 0;

        cout << ccr  << endl;
        //SendToStack(&ccr, sIdx);
        if(requestType == INITIAL || requestType == EVENT || requestType == 8)
        {
            SendToStack(&ccr, sIdx);
            ind = 1;
        }
        else
        {
            SendToStack(&ccr, index);
        }

    } //end try block
    catch(...)
    {
        cout << "Exception ,setting CCR AVP values." << endl;
    }// end catch block

    return ITS_SUCCESS;
}

int 
DisplayDccaMenuTest(int *index)
{
    string input;
    int ret = 0;
    do
    {
        cout << endl << "Select Dcca Command"<<endl<<endl;
        cout <<"1: CCR - Credit Control Request with  Initial "<<endl;
        cout <<"2: CCR - Credit Control Request with  Update"<<endl;
        cout <<"3: CCR - Credit Control Request with  Terminate"<<endl;
        cout <<"4: CCR - Credit Control Request Event Based "<<endl;
        cout <<"5: STR - Session Termination Request "<<endl;
        cout <<"8: CCR - Event request with Direct Debiting."<<endl;
        cout <<"6: to Post Dummy or 99: to Exit"<<endl;

        cin >> input;
        ret = atoi(input.c_str());

        if( ret == 2 || ret == 3 || ret == 5 || ret == 7 )
        {
            *index = DisplaySession();
        }

    } while((ret < 1 || ret > 8) && ret != 99 );


    return ret;
}


int 
SendCreditControlAnswerTest(const diameter::CommandImpl* impl, const int input, ITS_UINT index)
{
    // [1] Create CreditControlAnswer object.
    CreditControlAnswer cca(false,false);
    

    // [1.1] Create an instance of CreditControlRequest class with
    //        recived event
    CreditControlRequest ccr(*impl);

    try
    {
        // [2] Insert data in the created CreditControlAnswer object.
        // [2.1] Populate Mandatories.
        // [2.1.1] Populate Fixed Mandatories.
        // [2.1.1.1] Populate Fixed paramete "Session-Id".
        // Set the Session-Id AVP.
        // The data type of Session-Id is UTF8String.
        // This AVP is used to identify a specific session.
        // The Session-Id SHOULD appear immediately following the Diameter Header.
        // The Session-Id MUST be globally and eternally unique.
        // The AVP Code of Session-Id is 263.
    
        if (input == 4)
        {       
            string sIdString = "asdf";
            cca.setSessionId(SessionId(sIdString));
        }
        else
        {
            int i = (-2);
            if((i = GetSlotFromIndex(index)) != ERROR )
            {
                const CCRequestType&  ccRequestType1 = ccr.getCCRequestType(); 

                if ( (ccRequestType1.value() == CCRequestType::TERMINATION_REQUEST) || 
                     (ccRequestType1.value() == CCRequestType::EVENT_REQUEST ))
                {
                    sMap[i].valid = 0;
                }    
                    
                    
                cca.setSessionId(SessionId(sMap[i].sessionid));
                cca.setSessionIndex(sMap[i].index);
            }
        }

        switch(input)
        {
            case 1: 
            case 4:
            case 5:         
            {
                ResultCode resultCode(2001u);
                cca.setResultCode(resultCode);
                break;
            }

            case 2:
            {
                ResultCode resultCode(2002u);
                cca.setResultCode(resultCode);
                break;
            }
          
            case 3:
            {
                ResultCode resultCode(5000u);
                cca.setResultCode(resultCode);
                break;
            }
     
            default:
            APP_TRACE_DEBUG(("\nInvalid result code entered\n"));    
     
        } 
        
        if ( input == 4)
        {
           OriginHost originHost(x);
           cca.setOriginHost(originHost);
        }
        else
        {
            OriginHost originHost(GetOriginHost());
            cca.setOriginHost(originHost);
        }
    


        OriginRealm originRealm(GetOriginRealm());
        cca.setOriginRealm(originRealm);
        
        AuthApplicationId authApplicationId(DCCA_INTERFACE_APP_ID);
        cca.setAuthApplicationId(authApplicationId);

        const CCRequestType&  ccRequestType = ccr.getCCRequestType();
        cca.setCCRequestType(ccRequestType);

        const CCRequestNumber& ccRequestNumber = ccr.getCCRequestNumber(); 
        cca.setCCRequestNumber(ccRequestNumber);

        const UserName& userName = ccr.getUserName(); 
        cca.setUserName( userName ); 


        CCSessionFailover ccSessionFailover(
                      CCSessionFailover::FAILOVER_NOT_SUPPORTED);
        cca.setCCSessionFailover(ccSessionFailover);


        cca.setAcctMultiSessionId ( ccr.getAcctMultiSessionId () );       

        const OriginStateId&  originStateId = ccr.getOriginStateId ();  
        cca.setOriginStateId ( originStateId );  

        cca.setEventTimestamp ( ccr.getEventTimestamp() );  
    
        GrantedServiceUnit grantedServiceUnit;  
        PopulateGrantedServiceUnit ( grantedServiceUnit);
        cca.setGrantedServiceUnit ( grantedServiceUnit );  
      
        MultipleServicesCreditControl multipleServicesCC1;

        PopulateMultipleServicesCreditControl(multipleServicesCC1,false);
        cca.addMultipleServicesCreditControl(multipleServicesCC1);

        CostInformation costInfo;
        PopulateCostInformation(costInfo);
        cca.setCostInformation(costInfo);

        if ( input == 5 )
        {
            CreditControlFailureHandling ccFailureHandling(
                      CreditControlFailureHandling::TERMINATE);
            cca.setCreditControlFailureHandling(ccFailureHandling);
        }


        if ( ccr.containsRequestedAction())
        {
            DirectDebitingFailureHandling  ddfh ( 
                     DirectDebitingFailureHandling::CONTINUE); 
            cca.setDirectDebitingFailureHandling ( ddfh);  
        }
        ValidityTime validityTime(100);  
        cca.setValidityTime(validityTime); 

        // [3] Send object to stack
        cout << cca << endl;
        SendToStack(&cca, index);

    }// end try block
    catch(...)
    {
       cout << " Exception, setting CCA AVP values" << endl;
    } // end catch block


    return (ITS_SUCCESS);
}

int 
SendAbortSessionRequest( string sessId,ITS_UINT index )
{

    // [1] Create AbortSessionRequest object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
      AbortSessionRequest asr(false, false);

    int i = (-2);
    if(( i  = GetSlotFromIndex( index)) != ERROR )
    {
        sMap[i].valid = 0;
        asr.setSessionId(SessionId(sMap[i].sessionid));
    }

    OriginHost orig(GetOriginHost());
    asr.setOriginHost(orig);

    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    asr.setOriginRealm(origr);

    DestinationRealm destr(GetDestinationRealm());
    asr.setDestinationRealm(destr);

    DestinationHost desth(GetDestinationHost());
    asr.setDestinationHost(desth);

    AuthApplicationId authid((Unsigned32)4);
    asr.setAuthApplicationId(authid);

    UserName userName("sip:john.smith@india.internal.net");
    asr.setUserName(userName);

    OriginStateId org(41);
    asr.setOriginStateId(org);

    if (appMode == UNIT_TEST)
        std::cout << asr << std::endl;

    SendToStack(&asr , index);

    return (ITS_SUCCESS);
}


int 
SendAbortSessionAnswer(const CommandImpl* impl1)
{
    // [1] Create AbortSessionAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    AbortSessionAnswer asa(false, false);

    AbortSessionRequest com_req(*impl1);

    // The AVP Code of Session-Id is 263.
    const SessionId &sid1 = com_req.getSessionId();
    asa.setSessionId(sid1);

    ResultCode resCode(2001u);
    asa.setResultCode(resCode);

    const DestinationHost &dh1 = com_req.getDestinationHost();
    OriginHost orig(dh1.value());
    asa.setOriginHost(orig);

    // The AVP Code of Origin-Realm is 296.
    const DestinationRealm &dr1 = com_req.getDestinationRealm();
    OriginRealm origr(dr1.value());
    asa.setOriginRealm(origr);

    // The AVP Code of User-Name is 1.
    UserName userName("sip:john.smith@india.internal.net");
    asa.setUserName(userName);
    
    OriginStateId org(41);
    asa.setOriginStateId(org);

    if (appMode == UNIT_TEST)
        std::cout << asa << std::endl;

    SendToStack(&asa);

    return (ITS_SUCCESS);
}
   

int 
SendSessionTerminationRequest(string  sesId, int index) 
{

    SessionTerminationRequest str(false, false);
    int i = (-2);
    if( (i = GetSlotFromIndex( index)) != ERROR)
    {
        sMap[i].valid = 0;
        str.setSessionId(SessionId(sMap[i].sessionid));
    }

    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    str.setOriginHost(origh);

    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(GetOriginRealm());
    str.setOriginRealm(origr);

    // The AVP Code of Destination-Realm is 283.
    DestinationRealm desr(GetDestinationRealm());
    str.setDestinationRealm(desr);

    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authid((Unsigned32)4);
    str.setAuthApplicationId(authid);

    // The AVP Code of Termination-Cause is 295.
    TerminationCause termc(TerminationCause::DIAMETER_BAD_ANSWER);
    str.setTerminationCause(termc);

    // The AVP Code of User-Name is 1.
    UserName un("sip:john.smith@india.internal.net");
    str.setUserName(un);

    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    str.setDestinationHost(desh);

    // The AVP Code of Class is 25.
    Class class1("business");
    str.addClass(class1);
    Class class2("residential");
    str.addClass(class2);

    // by the application developers
    OriginStateId origsid(41);
    str.setOriginStateId(origsid);


    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        std::cout << str << std::endl;

    SendToStack(&str, index);

    return (ITS_SUCCESS);
}





int 
SendSessionTerminationAnswer(const CommandImpl *impl1)
{
    // [1] Create SessionTerminationAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    SessionTerminationAnswer sta(false, false);

    SessionTerminationRequest com_req(*impl1);

    const OriginHost& oh1 = com_req.getOriginHost();
    const OriginRealm& or1 = com_req.getOriginRealm();
    const DestinationRealm& dr1 = com_req.getDestinationRealm();

    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid1 = com_req.getSessionId();
    sta.setSessionId(sid1);

    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode rc(2001u);
    sta.setResultCode(rc);

    // The AVP Code of Origin-Host is 264.
    OriginHost origh(GetOriginHost());
    sta.setOriginHost(origh);

    // The AVP Code of Origin-Realm is 296.
    OriginRealm origr(dr1.value());
    sta.setOriginRealm(origr);

    // The AVP Code of User-Name is 1.
    UserName un("sip:john.smith@3gppnetwork.com");
    sta.setUserName(un);

    // access device.
    // The AVP Code of Class is 25.
    Class class1("business");
    sta.addClass(class1);

    // by the application developers
    
    OriginStateId origsid(41);
    sta.setOriginStateId(origsid);

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST) 
        std::cout << sta << std::endl;

    SendToStack(&sta, sIdx);

    return (ITS_SUCCESS);
}


     

