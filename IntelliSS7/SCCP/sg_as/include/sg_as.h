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
 * Menu
 */
#define DISPLAY_MENU            0
#define SEND_SSA                1
#define SEND_SSP                2   
#define SEND_SST                3
#define SEND_UDT                4
#define SEND_UDTS               5
#define SEND_CR_PROTCLASS2      6
#define SEND_CR_PROTCLASS3      7
#define SEND_DT1                8
#define SEND_RLSD               9
#define SEND_ERR                10

#define SEND_SOR                11
#define SEND_SOG                12
#define SEND_SSC                13
#define SEND_XUDT               14
#define SEND_XUDTS              15
#define SEND_CC                 16
#define SEND_CREF               17
#define SEND_DT2                18
#define SEND_AK                 19
#define SEND_RLC                20
#define SEND_IT                 21


/*
 * Global varibales.
 */
extern ITS_UINT app_dpc;                /* Remote PC */
extern ITS_UINT app_opc;                /* Local PC  */
extern ITS_OCTET app_dssn;              /* Remote SSN */
extern ITS_OCTET app_ossn;              /* Local SSN  */

extern ITS_UINT srcLocalRef;            /* Source Local Reference */
extern ITS_UINT destLocalRef;           /* Destination Local Reference */
extern its::SCCP_MessageClass *recvMsg; /* Pointer to received SCCP message */

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
extern ITS_HDR shdr, rhdr;

ITS_INT APP_AddLinkForLocalRoute(ITS_HANDLE handle);

ITS_INT SGP_Main(its::ThreadPoolThread *thr);
ITS_INT ASP_Main(its::ThreadPoolThread *thr);

/* MML Consoles for SG and AS */
void SUA_AS_MMLConsole(DBC_Server *dbc, const char* cmd);
void SUA_SG_MMLConsole(DBC_Server *dbc, const char* cmd);


void menu();
void displayMenu();

int TEST_DecodeSCCPMsg(ITS_HDR &hdr, its::SCCP_MessageClass* cl);

/*
 * SCCP Message Send/Receive functions.
 */
ITS_INT SendUDT(ITS_OCTET sio, its::SCCP_ProtocolClass &protClass, 
                its::SCCP_CalledPartyAddr &cdp, 
                its::SCCP_CallingPartyAddr &cgp,
                its::SCCP_UserData &userData);

#endif // SG_AS_H

