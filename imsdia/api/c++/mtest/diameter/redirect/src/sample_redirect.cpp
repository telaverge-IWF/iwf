/********************************-*-CPP-*-***********************************
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
 *
 * ID: $Id: sample_redirect.cpp,v 1.2 2010/04/29 06:52:13 nvijikumar Exp $
 ****************************************************************************/

#include <app.h>
#include <dia_defines.h>
#include <redirect_defines.h>

#include <strstream>
#include <sys/timeb.h>
#include <dia_stats.h>

#include <diameter/base/PROXYABLEERROR.h>
#include <diameter/base/BaseGenericCommand.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;


ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function handle the Redirect request message received from 
 *  the base diameter stack. It prepare Redirect answer message by using the 
 *  inforamtion available in request message. It adds the information where
 *  to send this message, how to use this information in future and for how
 *  much duration this information is valid.
 *
 *  Input Parameters:
 *      impl - Pointer to diameter::CommandImpl
 *      sIdx - Session Index
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 * 
 * Note1: Application Id, SessionId, OriginHost, OriginRealm, DestinationHost,
 * and DestinationRealm may be used to decide RedirectHost AVPs,
 * RedirectHostUsage AVP and RedirectHostMaxCacheTime AVP.
 *
 * Note2: Result code are already added by diameter stack.
 *
 *  See Also:
 ****************************************************************************/
int HandleDiaAppMsg(const diameter::CommandImpl *impl, unsigned int &sIdx)
{

    printf("\n\n Redirect Application : Inside HandleDiaAppMsg\n\n");
    try
    {
        // Find the generic command form CommandImpl for request processing.
        PROXYABLEERROR ReqMsg(*impl);
        Command *cmd = (Command *) &ReqMsg;
        diameter::base::BaseGenericCommand *gCmd =
                                (diameter::base::BaseGenericCommand *) cmd;

        // Get AVP values from Request Message to set it to the 
        // Answer and to decide redirect information.
        std::string oHost = gCmd->getOriginHost()->value();
        std::string oRealm = gCmd->getOriginRealm()->value();
        std::string dRealm = gCmd->getDestinationRealm()->value();
        std::string dHost;
 
        // Get Destination if it is Present in Msg. 
        if (gCmd->getDestinationHost())
        {
            dHost = gCmd->getDestinationHost()->value();
        }
        // Get AppId and SessId from Msg. 
        std::string sessId = gCmd->getSessionId()->value();
        unsigned int appId = gCmd->getApplicationId();

        // Modifying Header Flag's value for Sending Redirected Answer
        diameter::DiaHeader &hdr = (diameter::DiaHeader&)gCmd->getHeader();
        hdr.flags.r = 0;
        hdr.flags.e = 1;
 
        // Below is the example that how an application use this 
        // information to fill Redirect Info in Ans Msg. 

        // Process the Msg based on the application Id.
        switch (appId)
        {
            case BASE_INTERFACE_APP_ID:
            {
               // Based on information available at Redirect Agent,
               // add Redirect information in Ans Msg.

                // Process the Msg based on the Destination Realm.
                if (strcmp(dRealm.c_str(), "india.internal.net1") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server1", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server2", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server3", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(100);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else if (strcmp(dRealm.c_str(), "india.internal.net5") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server3", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server4", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server5", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(500);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else
                {
                    APP_TRACE_ERROR(("Realm not configured for Redirection."));
                }
                break;
            }
            case BASE_ACCOUNTING_APP_ID:
            {
               // Based on information available at Redirect Agent,
               // add Redirect information in Ans Msg.

                // Process the Msg based on the Destination Realm.
                if (strcmp(dRealm.c_str(), "india.internal.net4") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server3", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server4", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server5", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(100);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else if (strcmp(dRealm.c_str(), "india.internal.net5") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server3", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server4", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server5", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(500);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else
                {
                    APP_TRACE_ERROR(("Realm not configured for Redirection."));
                }
                break;
            }
            case SH_INTERFACE_APP_ID:
            {
               // Based on information available at Redirect Agent,
               // add Redirect information in Ans Msg.

                // Process the Msg based on the Destination Realm.
                if (strcmp(dRealm.c_str(), "india.internal.net4") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server1", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server2", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(100);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else if (strcmp(dRealm.c_str(), "india.internal.net5") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server3", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server4", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server5", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(500);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else
                {
                    APP_TRACE_ERROR(("Realm not configured for Redirection."));
                }
                break;
            }
            case CXDX_INTERFACE_APP_ID:
            {
               // Based on information available at Redirect Agent,
               // add Redirect information in Ans Msg.

                // Process the Msg based on the Destination Realm.
                if (strcmp(dRealm.c_str(), "india.internal.net4") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server1", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);

                    URI uri2("Server2", URI::AAA, 3880, URI::TCP, URI::RADIUS);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(100);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else if (strcmp(dRealm.c_str(), "india.internal.net5") == 0)
                {
                    // Adding Redirect Host AVPs
                    URI uri("Server3", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh(uri);
                    gCmd->getContainer().add(rh.name(), rh, false);
 
                    URI uri1("Server4", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh1(uri1);
                    gCmd->getContainer().add(rh1.name(), rh1, false);
 
                    URI uri2("Server5", URI::AAA, 3880, URI::TCP, URI::DIAMETER);
                    RedirectHost rh2(uri2);
                    gCmd->getContainer().add(rh2.name(), rh2, false);
 
                    // Adding Redirect Host Usage AVP
                    RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
                    gCmd->getContainer().add(rhu.name(), rhu, false);
 
                    // Adding Redirect Host Max Cache Time AVP
                    RedirectMaxCacheTime rmct(500);
                    gCmd->getContainer().add(rmct.name(), rmct, false);
                }
                else
                {
                    APP_TRACE_ERROR(("Realm not configured for Redirection."));
                }
                break;
            }
            default :
            {
                APP_TRACE_ERROR(("Application not supported by Redirect Agent."));
            }
        }
        // Send Redirected Answer to Stack
        APP_TRACE_DEBUG(("Sending Redirect Ans to Stack"));
        SendDiaAppMsg((diameter::Command &)*cmd, sIdx);
    }
    catch (NoSuchAttributeException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                         e.name(), e.what()));
    }
    catch (WrongCommandTypeException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                         e.name(), e.what()));
    }
    catch (UnknownTypeException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                         e.name(), e.what()));
    }
    catch (CodecException e)
    {
        APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                         e.name(), e.what()));
    }
    catch (...)
    {
        APP_TRACE_ERROR(("Unknown Exception Caught"));
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: 
 *      This function displays the menu options for the Cxdx interface
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      input - User choice of type integer.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int DisplayAppMenu()
{
    string input;
    int ret = 0;

    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select options" <<endl << endl;
            cout << "1: To Send Base Protocol Messages " << endl;
            cout << "99: To Previous Menu" << endl;

            cin >> input;

            ret=atoi(input.c_str());

        } while (ret != 1 && ret != 99);

        try
        {
            switch (ret)
            {
                case 1:
                    DisplayBaseMenuToApp();
                    break;
                case 99:
                    k=0;
                    break;
                default:
                    cout << endl << "please enter the correct choice";
                    break;
            }
        }
        catch (NoSuchAttributeException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (WrongCommandTypeException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (UnknownTypeException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (CodecException e)
        {
            APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ",
                                     e.name(), e.what()));
        }
        catch (...)
        {
            APP_TRACE_ERROR(("Unknown Exception Caught"));
        }
    }
    
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose: This is the main function.
 *
 *  Input Parameters:
 *      None.
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
int main(int argc, const char** argv)
{
    AppInitialize(REDIRECT_APP_ID);
    AppMain(argc,argv);

    return ITS_SUCCESS;
}

// Function with dummy defination. TODO:Update Statstics.
void StopTraffic(){}
void ResetStats(){}
void PrintStats(std::ostream& oss){}
void StratTraffic(std::ostream& oss , int duration, int burstSize, int slpTime){}
void UpdateIndications(unsigned int i){}
void CalculateTPS(std::ostrstream& os){}

int GenerateLoad()
{
 return (ITS_SUCCESS);
}




