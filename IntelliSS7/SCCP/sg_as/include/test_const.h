#ifndef SG_AS_H
#define SG_AS_H

#include <engine++.h>
#include <sccp++.h>
#include <vframe.h>

#if defined(CCITT)
#define ISS7_Stack    ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack    ISS7_ANSI_Stack
#endif

/*
 * Global varibales.
 */
extern ITS_UINT app_dpc;    /* Remote PC */
extern ITS_UINT app_opc;    /* Local PC  */
extern ITS_OCTET app_dssn;  /* Remote SSN */
extern ITS_OCTET app_ossn;  /* Local SSN  */

typedef enum
{
    ASP_MODE = 0,
    SGP_MODE
}
APPLICATION_MODE;

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)

extern "C" void APP_SetStopper();
extern APPLICATION_MODE appMode;

ITS_INT TEST_AddLinkForLocalRoute(ITS_HANDLE handle);

ITS_INT SGP_Main(its::ThreadPoolThread *thr);
ITS_INT ASP_Main(its::ThreadPoolThread *thr);

/*
 * SCCP Message Send/Receive functions.
 */
ITS_INT SendUDT(ITS_OCTET sio, SCCP_ProtocolClass &protClass, 
                SCCP_CalledPartyAddr &cdp, SCCP_CallingPartyAddr &cgp,
                SCCP_UserData &userData);

#endif // SG_AS_H

