/* 
 * File:   CommonDefs.h
 * Author: adey
 *
 * Created on December 20, 2012, 5:44 PM
 */

#ifndef COMMONDEFS_H
#define	COMMONDEFS_H

#include <pthread.h>
#include <event.h>
#include <evutil.h>
#include <stdint.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>
#include <map>

#include <ssg_defines.h>
#include <ssg_trace.h>
#include <ssg_utils.h>
#include <ssg_configuration.h>

#include <diameter/Command.h>
#include <diameter/Implementation.h>
#include <diameter/base/BaseGenericCommand.h>
#include <diameter/Types.h>
#include <dia_cmn.h>
#include <dia_msg_flow.h>

#include <map_cpp.h>
#include <cap_cpp.h>

#define FSM_CLEANUP_TIME                300

#define OPC                             2057

#define DPC                             4114

#define OSSN                            0x95    //149

#define DSSN                            0x6     //6

#define MAX_STATES 6
#define IWF_MAX_EVENTS 10

#define MAX_STATE_NAME_LEN 256

#define WILDCARD_SERVICE_KEY (-42);
enum States {
    CLOSED,
    UPSTRM_REQ_SENT,
    UPSTRM_RESP_SENT,
    DNSTRM_REQ_SENT,
    DNSTRM_INTRM_REQ_SENT,
    UPSTRM_INTRM_REQ_SENT
};

static const char* s_stateNames[] = {
    "CLOSED",
    "UPSTRM_REQ_SENT",
    "UPSTRM_RESP_SENT",
    "DNSTRM_REQ_SENT",
    "DNSTRM_INTRM_REQ_SENT",
    "UPSTRM_INTRM_REQ_SENT"
};

enum Events {
    RECV_UPSTRM_REQ,
    RECV_DNSTRM_REQ,
    RECV_DNSTRM_RESP,
    RECV_CBDNSTRM_RESP,
    RECV_UPSTRM_RESP,
    RECV_INTRM_DNSTRM_RESP,
    RECV_INTRM_UPSTRM_RESP,
    RECV_INTRM_DNSTRM_REQ,
    TIMEOUT,
    ERROR
};

static const char* s_eventNames[] = {
    "RECV_UPSTRM_REQ",
    "RECV_DNSTRM_REQ",
    "RECV_DNSTRM_RESP",
    "RECV_CBDNSTRM_RESP",
    "RECV_UPSTRM_RESP",
    "RECV_INTRM_DNSTRM_RESP",
    "RECV_INTRM_UPSTRM_RESP",
    "RECV_INTRM_DNSTRM_REQ",
    "TIMEOUT",
    "ERROR"
};

#if 0
enum Protocol {
    DIAMETER_S6A,
    DIAMETER_RO,
    MAP_GR,
    CAP_GE
};
#endif

static const char* s_protocolNames[] = {
    "DIAMETER_S6A",
    "DIAMETER_RO",
    "MAP_GR",
    "CAP_GE"
};

#endif	/* COMMONDEFS_H */

