#include <engine++.h>
#include <dbc_server.h>

#include <sg_as.h>
#include <sua_sccp_test.h>
#include <sccp_pprint.h>

#include <iostream>
#include <iomanip>

using namespace its;
using namespace std;

static ITS_BOOLEAN startSender = ITS_FALSE;

/*
 * Global variables.
 */
ITS_UINT app_dpc   = 1;
ITS_UINT app_opc   = 2;
ITS_OCTET app_dssn = 5;
ITS_OCTET app_ossn = 6;

APPLICATION_MODE appMode = ASP_MODE;

ITS_INT 
APP_DecodeSCCPPacket(its::Event &event);

its::SCCP_MessageClass *recvMsg = NULL;
its::SCCP_MessageClass *pCR = NULL;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
static int
WriteStdout(RINGBUF_Manager *rb, char *string, ITS_UINT len)
{
    return printf("%*.*s", (ITS_INT)len, (ITS_INT)len, string);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
class OAMServer : public its::DbcServer
{
    public:
        OAMServer() : DbcServer(std::string("OAMServer"))
        {}
        ~OAMServer() {}

        void DoCommand(std::istream &cmdLine)
        {
            std::cout << "test" << std::endl;
            return;
        }
};

OAMServer dbc;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
extern "C" ITS_INT
APP_Selector(ITS_HDR *hdr, ITS_EVENT* evt)
{
    return 1;
}

/*
 * Dispatch Application Threads.
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
extern "C" void
APP_PreFunc()
{
   ITS_INT  numThreads = 2;
   ITS_INT  ret = 0;

   cout << "APP_PreFunc:" << endl;

   for(int i = 0; i < numThreads; i++)
   {
       its::ThreadPoolEntry ent;

       if(engine::workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
       {
           engine::Worker* work = (engine::Worker *)ent.GetThread();

           if(work != NULL)
           {
               ret =
                 engine::workerPool->DispatchOnThread(ent,
                                        DISP_Dispatch_USER_CPP,
                                        (void*) work->GetCallbackStruct());
           }

           TIMERS_Sleep(1);
       }
   }

   return;
}

void APP_SetStopper()
{
}

/*
 * TQUEUE PostInit function. This function is invoke after
 * calling ITS_Initialize() in engine.
 * if ITS_Initialize return's failure this function will not
 * be called.
 */
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
extern "C" ITS_INT
APP_PostInit(its::ThreadPoolThread * thr, ITS_HANDLE handle)
{
    int ret = 0;

    cout << "APP_PostInit: handle " << handle << endl;                                                                                         
    if (TRANSPORT_INSTANCE(handle) != 1)
    {
        switch (appMode)
        {
            case ASP_MODE:
                ASP_Main(thr);
                break;

            case SGP_MODE:
                SGP_Main(thr);
                break;

            default:
                break;
        }
    }

    if (!startSender)
    {
        startSender = ITS_TRUE;
        /* Only receiver gets to this point. */
        APP_AddLinkForLocalRoute(handle);
    }

    /*
     * handle Get Next event
     * while (GetNextEvent())
     * {
     *      SGP_PostNextEvent();
     * }
     */

    return ret;
}


/*
 * TQUEUE (WorkerPool thread) Post next event.
 * This is invoked after calling GetNextEvent in engine.
 */
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
extern "C" ITS_INT
APP_PostNextEvent(its::ThreadPoolThread * thr, its::Event &event)
{
    printf("%s: %d: APP_PostNextEvent\n", __FILE__, __LINE__);
    cout << "APP_PostNextEvent:" << endl;

     /*
      * 1. Decode SCCP packet
      */
    APP_DecodeSCCPPacket(event);
                                                                                         
    return 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
ITS_INT 
APP_AddLinkForLocalRoute(ITS_HANDLE handle)
{
    ITS_INT        ret  = 0;
    ITS_USHORT     inst = TRANSPORT_INSTANCE(handle);
    SS7_Link       link;
    SS7_LinkSetPtr linkSet;
    ITS_INT        localLS = 0;

    cout << "APP_AddLinkForLocalRoute:" << endl;
                           
    memset(&link, 0, sizeof(SS7_Link));
                                                                                         
    linkSet = LINKSET_FindLinkSet(localLS); /* Find linkset for localroute */
                                                                                         
    link.initActive = ITS_TRUE; /* activate when link set activates */
    link.localLink  = ITS_TRUE; /* link is on local node */
    link.linkCode   = 0; /* start from zero */
    link.priority   = 0;
    link.id         = inst;
    link.isUp       = ITS_TRUE;
    link.isAllowed  = ITS_TRUE;
    link.family     = FAMILY_ANSI;
    /* link.linkSet    = linkSet; */
                                                                                         
    cout << "APP_AddLinkForLocalRoute():" << endl;
                                                                                         
    if( (ret = LINK_AddLink(localLS, &link)) == ITS_SUCCESS)
    {
        SS7_LinkPtr lp = NULL;

        cout << "Added link for local route to Transport Inst 1:" << endl;

        lp = LINK_FindLink(localLS, link.linkCode);

        if(lp != NULL)
        {
            LINK_AddLinkInfoToTransport((TRANSPORT_Control *)handle, lp);
        }

        LINK_SetLinkState(lp, ITS_TRUE);

        LINKSET_SetLinkSetState(LINKSET_FindLinkSet(localLS), ITS_TRUE);
    }
    else
    {
        cout << "ERROR: Failed to add link:" << endl;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This 
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
ITS_INT 
APP_DecodeSCCPPacket(its::Event &event)
{
    int ret = 0;
    int len = event.GetLength();
    ITS_EVENT evt = event.GetEvent();

    ret = SCCP_MessageClass::Receive(ISS7_Stack, &rhdr, event,
                                     &recvMsg);
    if (ret == ITS_SUCCESS)
    {
        printf("%s: %d: Decoded SCCP Msg 0x%x.\n", __FILE__, __LINE__,
               SCCP_MSG_TYPE(&evt));
        PrintSCCPMessage(recvMsg);
        displayMenu();
    }
    else
    {
        printf("%s: %d: SCCP_Decode failed. err %0x\n", __FILE__, __LINE__, ret);
    }

    TEST_DecodeSCCPMsg(rhdr, recvMsg);

    return ret;
}

void
displayMenu()
{
    cout << "******************* SCCP Messages ********************" << endl;
    cout << setiosflags (ios_base::left);
    cout << setw(2)  << SEND_SSA << " - " << setw(25) << "SSA"
         << setw(2)  << SEND_SOR << " - " << setw(25) << "SOR"
         << endl;
    cout << setw(2)  << SEND_SSP << " - " << setw(25) << "SSP"
         << setw(2)  << SEND_SOG << " - " << setw(25) << "SOG"
         << endl;
    cout << setw(2)  << SEND_SST << " - " << setw(25) << "SST"
         << setw(2)  << SEND_SSC << " - " << setw(25) << "SSC"
         << endl;
    cout << endl;

    cout << setw(2)  << SEND_UDT << " - " << setw(25) << "UDT"
         << setw(2)  << SEND_XUDT << " - " << setw(25) << "XUDT"
         << endl;
    cout << setw(2)  << SEND_UDTS << " - " << setw(25) << "UDTS"
         << setw(2)  << SEND_XUDTS << " - " << setw(25) << "XUDTS"
         << endl;
    cout << endl;

    cout << setw(2)  << SEND_CR_PROTCLASS2 << " - "
         << setw(25) << "CR (ProtClass 2)"
         << setw(2)  << SEND_CC << " - " << setw(25) << "CC"
         << endl;
    cout << setw(2)  << SEND_CR_PROTCLASS3 << " - "
         << setw(25) << "CR (ProtClass 3)"
         << setw(2)  << SEND_CREF << " - " << setw(25) << "CREF"
         << endl;
    cout << setw(2)  << SEND_DT1 << " - " << setw(25) << "DT1 (ProtClass 2)"
         << setw(2)  << SEND_DT2 << " - " << setw(25) << "DT2 (ProtClass 3)"
         << endl;
    cout << setw(5)  << " " << setw(25) << " "
         << setw(2)  << SEND_AK << " - " << setw(25) << "AK"
         << endl;
    cout << setw(2)  << SEND_RLSD << " - " << setw(25) << "RLSD"
         << setw(2)  << SEND_RLC  << " - " << setw(25) << "RLC"
         << endl;
    cout << setw(2)  << SEND_ERR << " - " << setw(25) << "ERR"
         << setw(2)  << SEND_IT  << " - " << setw(25) << "IT"
         << endl;
    cout << "******************************************************" << endl;
}

void menu()
{
    int cmd;

    displayMenu();
    cout << "->> ";
    cin  >> cmd;

    switch (cmd)
    {
        case DISPLAY_MENU:
            displayMenu();
            break;

        case SEND_SSA:
            TEST_SendSCMG(SCCP_SCMG_SS_ALLOWED);
            break;

        case SEND_SSP:
            TEST_SendSCMG(SCCP_SCMG_SS_PROHIBIT);
            break;

        case SEND_SST:
            TEST_SendSCMG(SCCP_SCMG_SS_STATUS_TEST);
            break;

        case SEND_UDT:
            TEST_SendUDT();
            break;

        case SEND_UDTS:
            TEST_SendUDTS(recvMsg);
            break;

        case SEND_CR_PROTCLASS2:
            TEST_SendCR(SCCP_PCLASS_2);
            break;

        case SEND_CR_PROTCLASS3:
            TEST_SendCR(SCCP_PCLASS_3);
            break;

        case SEND_DT1:
            TEST_SendDT1(recvMsg);
            break;

        case SEND_RLSD:
            TEST_SendRLSD(recvMsg);
            break;

        case SEND_ERR:
            TEST_SendERR(recvMsg);
            break;

        case SEND_SOR:
            TEST_SendSCMG(SCCP_SCMG_SS_OOS_REQ);
            break;

        case SEND_SOG:
            TEST_SendSCMG(SCCP_SCMG_SS_OOS_GRANT);
            break;

        case SEND_SSC:
            TEST_SendSCMG(SCCP_SCMG_SS_CONGESTED);
            break;

        case SEND_XUDT:
            TEST_SendXUDT();
            break;

        case SEND_XUDTS:
            TEST_SendXUDTS(recvMsg);
            break;

        case SEND_CC:
            TEST_SendCC(recvMsg);
            break;

        case SEND_CREF:
            TEST_SendCREF(recvMsg);
            break;

        case SEND_DT2:
            TEST_SendDT2(recvMsg);
            break;

        case SEND_AK:
            TEST_SendAK(recvMsg);
            break;

        case SEND_RLC:
            TEST_SendRLC(recvMsg);
            break;

        case SEND_IT:
            TEST_SendIT();
            break;

        default:
            break;
    }
}

