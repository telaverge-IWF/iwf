#include <app_buildcap_msgs.h>

int Callflow1()
{
    //NOTE: Parsing of json should be done for all the messages related to this call flow
    BuildInitialDPArg();
    return 0;
}

int SendResponseForInitialCase(TCAP_Dialogue *dlg)
{
    switch(optionfromserver)
    {
        case 1:
            {
                SendEventReportBCSMArgInTcCont(dlg);
                SendApplyChargingReportArgInTcCont(dlg);
            }
        default:
            return -1;
    }
}

