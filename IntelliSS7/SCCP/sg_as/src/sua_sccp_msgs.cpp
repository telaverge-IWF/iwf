#include <sg_as.h>
#include <iostream>

using namespace its;
using namespace std;

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
ITS_INT SendUDT()
{
    SCCP_UnitData         udt;
    //ITS_SCCP_IE           ie;
    ITS_HDR               hdr;
    
    SCCP_ProtocolClass    protClass(SCCP_PCLASS_0);
    SCCP_CalledPartyAddr  cdp;
    SCCP_CallingPartyAddr cgp;
    SCCP_UserData         userData;

    ITS_OCTET             data[40];
    int                   len = 40;
    ITS_INT               ret = 0;

    printf("******** opc = %d\n", app_opc);
    printf("******** ossn = %d\n", app_ossn);
    printf("******** dpc = %d\n", app_dpc);
    printf("******** dssn = %d\n", app_dssn);
    
    /*
     * TODO: Set Global title for GTT based routing.
     */

    cdp.SetPointCode(app_dpc);
    cdp.SetSSN(app_dssn);
    cdp.SetRouteByPCSSN(true);

    cgp.SetPointCode(app_opc);
    cgp.SetSSN(app_ossn);
    cgp.SetRouteByPCSSN(true);

    udt.AddIE(&cdp);
    udt.AddIE(&cgp);
    udt.AddIE(&protClass);

    udt.SetSIO(0x03);

    for (int i = 0; i < 40; i++)
    {
        data[i] = i;
    }

    userData.SetUserData(data, len);
    udt.AddIE(&userData);

    ret = SCCP_MessageClass::Send(ISS7_Stack, &hdr, &udt);
    if (ret == ITS_SUCCESS)
    {
        cout << "UDT send success." << endl;
    }
    else
    {
        cout << "Failed to send UDT." << endl;
    }

    return ret;
}


