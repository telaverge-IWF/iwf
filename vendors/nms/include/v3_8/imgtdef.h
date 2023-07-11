/***************************************************************************\
*
* FILENAME:     imgtdef.h
*
* DESCRIPTION:  Definitions for IMGT (ISDN Management) interface.
*
* Copyright 1996 by Natural Microsystems.  All rights reserved.
*
\***************************************************************************/

#ifndef _IMGTDEF_H_
#define _IMGTDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif

#include "ctadef.h"
#include "imgtsvc.h"    
/* -------------------------------------------------------------------------*
 *  IMGT Event Codes
 * -------------------------------------------------------------------------*/

#define IMGTEVN_BASE                0x00182000
#define IMGTEVN_STARTED             0x00182001 /* configuration finished    */
#define IMGTEVN_STOPPED             0x00182002 /* reset configuration       */
#define IMGTEVN_SEND_MESSAGE        0x00182003
#define IMGTEVN_RCV_MESSAGE         0x00182005 /* receive msg from the trunk*/
#define IMGTEVN_RCV_MON             0x00182006 /* monitoring msg received   */
#define IMGTEVN_RCV_TRAP            0x00182007 /* trap message received     */

#define IMGTEVN_ERROR               0x00182013 /* error report              */
/* -------------------------------------------------------------------------*
 *  IMGT Error Codes
 * -------------------------------------------------------------------------*/
                                                                            
#define IMGTERR_BASE                0x00181000
#define IMGTERR_BAD_NAI             0x00181001 /* Invalid nai specification */
#define IMGTERR_INVALID_CONFIG      0x00181002 /* Invalid IMGT_CONFIG field */
#define IMGTERR_NO_UP_BUFFER        0x00181003
#define IMGTERR_BUFFER_TOO_BIG      0x00181004 /* Buffer is too big         */
#define IMGTERR_RCV_BUFFER_TOO_BIG  0x00181005 /* Incoming buffer is too big*/
#define IMGTERR_NAI_IN_USE          0x00181006 /* Nai is already configured */
#define IMGTERR_DRIVER_ERROR        0x00181007 /* Driver error              */
#define IMGTERR_INVALID_BUFFER      0x00181008
#define IMGTERR_ISDN_NOT_STARTED    0x00181015 /* ISDN stack isnt started   */
#define IMGTERR_IMGT_NOT_STARTED    0x00181016 /* IMGT isnt started         */


#define IMGTERR_INTERNAL_1          0x00181101 /* Cannot get Bricks msg
                                                  buffer                    */
#define IMGTERR_INTERNAL_2          0x00181102 /* Cannot get Bricks data
                                                  buffer                    */
#define IMGTERR_INTERNAL_5          0x00181105 /* mgetx failed              */
#define IMGTERR_INTERNAL_6          0x00181106 /* Too many submitted buffers*/
#define IMGTERR_INTERNAL_7          0x00181107 /* Cannot allocate memory    */
#define IMGTERR_INTERNAL_12         0x0018110C /* mgetx in appli failed     */

/*---------------------------------------------------------------------------*
 *  API Structures
 *---------------------------------------------------------------------------*/

typedef struct IMGT_MESSAGE
{
    BYTE nai;                           /*  Network access interface index   */
    BYTE code;                          /*  Primitive code                   */
    WORD nfas_group;                    /*  NFAS group number, needed        */
                                        /*  for multiple CCID configurations */
} IMGT_MESSAGE;

typedef struct IMGT_MSG_PACKET
{
    WORD data_size;                     /*  Size of data to follow           */
    WORD pad;
    IMGT_MESSAGE message;
    BYTE databuff[4];                   /* Data included in packet >=0       */
} IMGT_MSG_PACKET;

typedef unsigned DATACODE;

/*---------------------------------------------------------------------------*/

//#define IMGT_BUFFERS                15  /* for service/restart messages    */
//#define TRAP_BUFFERS                0   /* trap events                     */
//#define MON_BUFFERS                 0   /* monitoring                      */
#define MAX_IMGT_SUBMITTED_BUFFERS  15 //(IMGT_BUFFERS + TRAP_BUFFERS + MON_BUFFERS)

#define MAX_IMGT_BUFFER_SIZE        350

/*--------------------------------------------------------------------------*
 *                      Function Prototypes
 *--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*
 *  imgtStart
 *
 *  Configures the range of events that the application wants to receive
 *  Submits appropriate number of buffers based on configuration
 *  (this function doesn't start the service that's started at open service 
 *  time, one per trunk)
 * 
 *  CTAHD ctahd - The port handle from a prior ctaCreateContext
 *
 *  unsigned nai - Network Access Identifier (T1/E1 trunk number)
 *
 *  IMGT_CONFIG *pconfig - pointer to a IMGT_CONFIG structure
 *
 *--------------------------------------------------------------------------*/

DWORD NMSAPI imgtStart( CTAHD ctahd, unsigned nai, IMGT_CONFIG *pconfig );

/*--------------------------------------------------------------------------*
 *  imgtStop
 *
 *  Stops a managment session initiated with imgtStart
 *  Releases all resources formerly submitted,but doesn't close service.
 * 
 *  CTAHD ctahd - The port handle from a prior ctaCreateContext
 *
 *--------------------------------------------------------------------------*/

DWORD NMSAPI imgtStop( CTAHD ctahd );

/*--------------------------------------------------------------------------*
 *  imgtGetData
 *
 *  Retrieves a data structure, the type of which is determined by
 *  datacode
 *
 *  CTAHD ctahd - The port handle from a prior ctaCreateContext
 *
 *  DATACODE datacode
 *
 *  unsigned size - size of optional data buffer
 *
 *  void *pbuff - pointer to optional data buffer
 *
 *--------------------------------------------------------------------------*/

DWORD NMSAPI imgtGetData( CTAHD ctahd, DATACODE datacode,
                          unsigned size, void *pbuff );

/*--------------------------------------------------------------------------*
 *  imgtSendMessage
 *
 *  Sends a message to the IMGT manager.
 *
 *  CTAHD ctahd - The port handle from a prior ctaCreateContext
 *
 *  IMGT_MESSAGE *pmessage - pointer to a IMGT_MESSAGE structure
 *
 *  unsigned size - size of optional data buffer
 *
 *  void *pbuff - pointer to optional data buffer
 *
 *--------------------------------------------------------------------------*/

DWORD NMSAPI imgtSendMessage( CTAHD ctahd, IMGT_MESSAGE *pmessage,
                              unsigned size, void *pbuff );

/*--------------------------------------------------------------------------*
 *  imgtReleaseBuffer
 *
 *  Releases a buffer after the application has finished processing it.
 *
 *  CTAHD ctahd - The port handle from a prior ctaCreateContext
 *
 *  void * buffer - Pointer to the event buffer from the ADI_EVENT
 *
 *--------------------------------------------------------------------------*/

DWORD NMSAPI imgtReleaseBuffer( CTAHD ctahd, void *buffer );


#ifdef __cplusplus
}
#endif

#endif;

