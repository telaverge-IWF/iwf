/***************************************************************************\
*
* FILENAME:     isdndef.h
*
* DESCRIPTION:  Public definitions for ISDN interface.
*
* COMMENTS:
*
* Copyright 1995-1996 Natural Microsystems.  All rights reserved.
*
\***************************************************************************/

#ifndef ISDNDEF_INCLUDED
#define ISDNDEF_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------- */
/* -------------------------- Protocol Parms -------------------------------- */
/* -------------------------------------------------------------------------- */
#include "isdnparm.h"

/* -------------------------------------------------------------------------- */
/* -------------------------- ISDN Event Codes ------------------------------ */
/* -------------------------------------------------------------------------- */

/*
 * Event ID's which can result from a call to isdnProcessEvent.  Found
 * in the pevent->id field after an adiFetchAndProcess.
 */

#define ISDNEVN_BASE                0x00072000

#define ISDNEVN_START_PROTOCOL      0x00072001
#define ISDNEVN_STOP_PROTOCOL       0x00072002
#define ISDNEVN_SEND_MESSAGE        0x00072004
#define ISDNEVN_RCV_MESSAGE         0x00072020
#define ISDNEVN_SET_MSG_CAPTURE     0x00072082
#define ISDNEVN_ERROR               0x00072083

/* -------------------------------------------------------------------------- */
/* -------------------------- ISDN Error Codes ------------------------------ */
/* ---- pevent->value field of isdnProcessMessage for ISDNEVN_ERROR --------- */
/* -------------------------------------------------------------------------- */


#define ISDNERR_BASE                0x00071000


#define ISDNERR_BAD_NAI             0x00071001  /* Invalid nai specification */

#define ISDNERR_INVALID_PROTOCOL    0x00071011  /* Invalid protocol code */
#define ISDNERR_INVALID_OPERATOR    0x00071012  /* operator paramter is invalid */
#define ISDNERR_INVALID_PARTNER     0x00071013  /* Runfile does not support 
                                                ** the partner equipment 
                                                ** specified 
                                                */
#define ISDNERR_INVALID_COUNTRY     0x00071014  /* Country specified is 
                                                ** invalid for the operator
                                                ** specified
                                                */
#define ISDNERR_NAI_IN_USE              0x00071015  /* Nai is already configured */
#define ISDNERR_INVALID_HDLC_CHAN       0x00071016  /* Invalid HDLC channel specified */
#define ISDNERR_INCOMPATIBLE_LIB        0x00071017  /* Library used is incompatible */
#define ISDNERR_PROTOCOL_PH_FAILURE     0x0007101A
#define ISDNERR_PROTOCOL_DL_FAILURE     0x0007101B
#define ISDNERR_PROTOCOL_NS_FAILURE     0x0007101C
#define ISDNERR_PROTOCOL_CC_FAILURE     0x0007101D
#define ISDNERR_CHANNELIZED_ON_MULTIPLE_BOARDS 0x7101E
#define ISDNERR_NAI_CONFIG              0x0007101F
#define ISDNERR_RACE_STARTING_PROTOCOL  0x00071020 /* Starting the protocol before complete stop */

#define ISDNERR_NO_UP_BUFFER        0x00071021  /* No Up buffer to send event */
#define ISDNERR_BUFFER_TOO_BIG      0x00071022  /* outgoing Buffer is too big */
#define ISDNERR_RCV_BUFFER_TOO_BIG  0x00071023  /* incoming Buffer is too big */


#define ISDNERR_INTERNAL_1          0x00071101  
#define ISDNERR_INTERNAL_2          0x00071102 
#define ISDNERR_INTERNAL_3          0x00071103
#define ISDNERR_INTERNAL_4          0x00071104
#define ISDNERR_INTERNAL_5          0x00071105  
#define ISDNERR_INTERNAL_6          0x00071106 
#define ISDNERR_INTERNAL_7          0x00071107
#define ISDNERR_INTERNAL_8          0x00071108 
#define ISDNERR_INTERNAL_9          0x00071109
#define ISDNERR_INTERNAL_10         0x0007110A
#define ISDNERR_INTERNAL_11         0x0007110B
#define ISDNERR_INTERNAL_12         0x0007110C 


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
#define ISDNERR_INTERNAL_DLL_1      0x00070201  
#define ISDNERR_INTERNAL_DLL_2      0x00070202 
#define ISDNERR_INTERNAL_DLL_3      0x00070203  

#define ISDNERR_PORT_BUSY           0x00070301  /* Port executing a command */
#define ISDNERR_INVALID_BUFFER      0x00070303  /* invalid buffer */
#define ISDNERR_DRIVER_ERROR        0x00070304  /* Driver error */




/* -------------------------------------------------------------------------- */
/* -------------------------- Function Prototypes --------------------------- */
/* -------------------------------------------------------------------------- */

/*-------------------------------------------------------------------------
 * isdnStartProtocol
 *
 * This function initializes a digital (ISDN) protocol on a previously-opened
 * channel.
 *
 * ctahd - The port handle from a prior adiOpenPort.
 *
 * protocol - ISDN_PROTOCOL_Q931CC, for Q.931 call control
 *            ISDN_PROTOCOL_LAPD, LAP-D Support
 *
 *
 * netoperator - Network operator to use: ISDN_OPERATOR_FT_ETSI, etc.
 *               (Only meaningful for ISDN_PROTOCOL_Q931_CC)
 *
 * country - Country for the operator: COUNTRY_USA, etc.
 *                   (Only meaningful for ISDN_PROTOCOL_Q931_CC)
 *
 * partner_equip - Equipment of the party we are connecting to.
 *                 EQUIPMENT_NT (if connected to a network)
 *                 EQUIPMENT_TE (if connected to a terminal)
 * 
 * nai - Network Access Identifier
 *
 * pdata - Pointer to a protocol-specific parameter structure.  Use the
 *         ISDN_PROTOCOL_PARMS_LAPD
 *         ISDN_PROTOCOL_PARMS_Q931CC
 *
 *-------------------------------------------------------------------------*/
DWORD NMSAPI isdnStartProtocol( CTAHD ctahd, 
                                unsigned protocol,
                                unsigned netoperator,
                                unsigned country,
                                unsigned partner_equip,
								unsigned nai, void *pdata );

/*-------------------------------------------------------------------------
 * isdnStopProtocol
 *
 * This functions shuts down a previously started ISDN protocol.  Doing so
 * releases all resources formerly used by the protocol.
 *
 * ctahd - The port handle from a prior adiOpenPort.
 *-------------------------------------------------------------------------*/
DWORD NMSAPI isdnStopProtocol( CTAHD ctahd );

/*-------------------------------------------------------------------------
 * isdnSendMessage
 *
 * This function sends a message to the ISDN manager.  The word "message"
 * in this case is a catch-all for _any_ information which must be communicated
 * to the ISDN manager; configuration, status query, outgoing data, outgoing
 * call management, etc.
 *
 * ctahd - The port handle from a prior adiOpenPort.
 *
 * message - pointer to a MESSAGE_INFO structure
 *
 * pdata - Optional data to send 
 *
 * size - size of the data buffer
 *
 *-------------------------------------------------------------------------*/
DWORD NMSAPI isdnSendMessage( CTAHD ctahd, ISDN_MESSAGE *message,
                              void *pdata, unsigned size );

/*-------------------------------------------------------------------------
 * isdnReleaseBuffer
 *
 * This function indicates that the application has finished processing an
 * event buffer described by the ADI_EVENT buffer and size fields and is
 * returning that buffer to the ISDN interface.  The application _must_
 * return every event buffer to the ISDN interface as soon as possible, or
 * the ISDN interface will starve and stop passing events to the application.
 *
 * ctahd - The port handle from a prior adiOpenPort.
 *
 * buffer - Pointer to the event buffer from the ADI_EVENT
 *-------------------------------------------------------------------------*/

DWORD NMSAPI isdnReleaseBuffer( CTAHD ctahd, void *buffer );


/*-------------------------------------------------------------------------
 * isdnSetMsgCapture
 *
 * Set the message capture enable/disable string
 *
 * ctahd - The port handle from a prior adiOpenPort.
 *
 * enable - TRUE (for enable) or FALSE (for disable) the entities in the
 *          entity_id_string
 *
 * nai - Network Access Identifier (T1/E1 trunk number)
 *
 * entity_id_string - A character string of the entities to enable/disable.
 * 
 * nfas_group - NFAS group number. This parameter is considered by the stack
 *           only if the multiple CCID configuration is defined in the 
 *           configuration file (ag.cfg)
 *           Otherwise the nai is used to set the capture mask.
 * 
 *-------------------------------------------------------------------------*/
DWORD NMSAPI isdnSetMsgCapture( CTAHD ctahd, DWORD enable, DWORD nai, 
                                char *entity_id_string, DWORD nfas_group );


#ifdef __cplusplus
}
#endif

#endif

