#ifndef SMSC_H
#define SMSC_H
/*
#if defined(__cplusplus)
extern "C"
{
#endif
*/

#include <stdio.h>
#include <iostream.h>
#include <its++.h>
#include <engine.h>
#include <its_dsm_gcs.h>
#include <its_dsm_stub.h>

#include <ss7_mgmt.h>

//ITS_MUTEX    statsGate;

void TestCases_TTC(DBC_Server *dbc, const char *cmdLine);
void TestCases_CCITT(DBC_Server *dbc, const char *cmdLine);

#define TCAP_RECEIVE_QUEUE_ID_CCITT   501 
#define TCAP_RECEIVE_QUEUE_ID_TTC     502 


typedef struct
{
    ITS_BOOLEAN beginReceived;
    ITS_BOOLEAN continueReceived; 
    ITS_UINT    timestamp; /* in ms */
}
TrContext;

extern "C" ITS_USHORT  
ApplicationSelector(ITS_HDR *h, ITS_EVENT *ev);

//extern its::TaskQueueTransport *tcapEventQueue_CCITT;
extern its::TaskQueueTransport *tcapEventQueue_TTC;
/*
#if defined(__cplusplus)
}
#endif

*/

#endif

