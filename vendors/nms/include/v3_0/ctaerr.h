/*****************************************************************************
*                                  CTAERR.H
*
*  Header for CT Access generic errors and reasons.
*  To be included by all applications, CT Access service managers and
*  services and for compatibility with AG Access (adi.h).
*
*  Copyright (c) 1996-98  Natural MicroSystems Corp.  All rights reserved.
*****************************************************************************/

#ifndef CTAERR_INCLUDED
#define CTAERR_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


#define _TEXTCASE_(e) case e: return #e


/* GENERIC ERRORS                                                             */
#define SUCCESS                               0
#define CTAERR_RESERVED              0x00000001 /* Not an error - do not use  */
#define CTAERR_FATAL                 0x00000002 /* Internal error             */
#define CTAERR_BOARD_ERROR           0x00000003 /* Error returned from a board*/
#define CTAERR_INVALID_CTAQUEUEHD    0x00000004 /* Bad ctaqueuehd             */
#define CTAERR_INVALID_CTAHD         0x00000005 /* Bad ctahd                  */
#define CTAERR_OUT_OF_MEMORY         0x00000006 /* Malloc or Realloc error    */
#define CTAERR_BAD_ARGUMENT          0x00000007 /* Bad function argument      */
#define CTAERR_OUT_OF_RESOURCES      0x00000008 /* Out of internal resources  */
#define CTAERR_NOT_IMPLEMENTED       0x00000009 /* Function not implemented   */
#define CTAERR_NOT_FOUND             0x0000000A /* Requested item doesnt exist*/
#define CTAERR_BAD_SIZE              0x0000000B /* Bad size argument          */
#define CTAERR_INVALID_STATE         0x0000000C /* Invalid state for function */
#define CTAERR_FUNCTION_NOT_AVAIL    0x0000000D /* Function is not available  */
#define CTAERR_FUNCTION_NOT_ACTIVE   0x0000000E /* Function is not active     */
#define CTAERR_FUNCTION_ACTIVE       0x0000000F /* Function is already active */
#define CTAERR_SHAREMEM_ACCESS       0x00000010 /* Failed accessing shared mem*/
#define CTAERR_INCOMPATIBLE_REVISION 0x00000011 /* Incompatible revision level*/
#define CTAERR_RESOURCE_CONFLICT     0x00000012 /* Needed resource is in use  */
#define CTAERR_INVALID_SEQUENCE      0x00000013 /* Handshake/exchange error   */
#define CTAERR_DRIVER_OPEN_FAILED    0x00000014 /* Device driver open failed  */
#define CTAERR_DRIVER_VERSION        0x00000015 /* Incorrect driver version   */
#define CTAERR_DRIVER_RECEIVE_FAILED 0x00000016 /* Driver receive failed      */
#define CTAERR_DRIVER_SEND_FAILED    0x00000017 /* Driver send failed         */
#define CTAERR_DRIVER_ERROR          0x00000018 /* Other driver errors        */
#define CTAERR_TOO_MANY_OPEN_FILES   0x00000019 /* No more file handles       */
#define CTAERR_INVALID_BOARD         0x0000001A /* Invalid board in svc arg   */
#define CTAERR_OUTPUT_ACTIVE         0x0000001B /* Conflict on output str:slot*/
#define CTAERR_CREATE_MUTEX_FAILED   0x0000001C /* Create thread mutex failed */
#define CTAERR_LOCK_TIMEOUT          0x0000001D /* Timed out waiting for mutex*/
#define CTAERR_ALREADY_INITIALIZED   0x0000001E /* Already initialized        */
#define CTAERR_NOT_INITIALIZED       0x0000001F /* Not initialized            */
#define CTAERR_INVALID_HANDLE        0x00000020 /* Invalid svc specific handle*/
#define CTAERR_PATH_NOT_FOUND        0x00000022 /* File path not found        */
#define CTAERR_FILE_NOT_FOUND        0x00000021 /* File not found             */
#define CTAERR_FILE_ACCESS_DENIED    0x00000023 /* File access denied         */
#define CTAERR_FILE_EXISTS           0x00000024 /* File already exists        */
#define CTAERR_FILE_OPEN_FAILED      0x00000025 /* File open failed           */
#define CTAERR_FILE_CREATE_FAILED    0x00000026 /* File create failed         */
#define CTAERR_FILE_READ_FAILED      0x00000027 /* File read failed           */
#define CTAERR_FILE_WRITE_FAILED     0x00000028 /* File write failed          */
#define CTAERR_DISK_FULL             0x00000029 /* Disk full, cannot write    */
#define CTAERR_CREATE_EVENT_FAILED   0x0000002A /* Create event object failed */
#define CTAERR_EVENT_TIMEOUT         0x0000002B /* Timeout waiting for event  */
#define CTAERR_OS_INTERNAL_ERROR     0x0000002C /* OS specific error occured  */
#define CTAERR_INTERNAL_ERROR        0x0000002D /* CT Access internal error   */
#define CTAERR_DUPLICATE_WAITOBJ     0x0000002E /* duplicate wait object      */
#define CTAERR_NO_LICENSE            0x0000002F /* no license                 */
#define CTAERR_LICENSE_EXPIRED       0x00000030 /* license expired            */
#define CTAERR_INVALID_SYNTAX        0x00000031 /* syntax error               */
#define CTAERR_INVALID_KEYWORD       0x00000032 /* Invalid Keyword            */
#define CTAERR_SECTION_NOT_FOUND     0x00000033 /* section header not found   */
#define CTAERR_WRONG_COMPATLEVEL     0x00000034 /* app must be recompiled     */
#define CTAERR_PARAMETER_ERROR       0x00000035 /* parameter error            */


#define CTA_GENERIC_ERRORS() \
        _TEXTCASE_(SUCCESS); \
        _TEXTCASE_(CTAERR_FATAL); \
        _TEXTCASE_(CTAERR_BOARD_ERROR); \
        _TEXTCASE_(CTAERR_INVALID_CTAQUEUEHD); \
        _TEXTCASE_(CTAERR_INVALID_CTAHD); \
        _TEXTCASE_(CTAERR_OUT_OF_MEMORY); \
        _TEXTCASE_(CTAERR_BAD_ARGUMENT); \
        _TEXTCASE_(CTAERR_OUT_OF_RESOURCES); \
        _TEXTCASE_(CTAERR_NOT_IMPLEMENTED); \
        _TEXTCASE_(CTAERR_NOT_FOUND); \
        _TEXTCASE_(CTAERR_BAD_SIZE); \
        _TEXTCASE_(CTAERR_INVALID_STATE); \
        _TEXTCASE_(CTAERR_FUNCTION_NOT_AVAIL); \
        _TEXTCASE_(CTAERR_FUNCTION_NOT_ACTIVE); \
        _TEXTCASE_(CTAERR_FUNCTION_ACTIVE); \
        _TEXTCASE_(CTAERR_SHAREMEM_ACCESS); \
        _TEXTCASE_(CTAERR_INCOMPATIBLE_REVISION); \
        _TEXTCASE_(CTAERR_RESOURCE_CONFLICT); \
        _TEXTCASE_(CTAERR_INVALID_SEQUENCE); \
        _TEXTCASE_(CTAERR_DRIVER_OPEN_FAILED); \
        _TEXTCASE_(CTAERR_DRIVER_VERSION); \
        _TEXTCASE_(CTAERR_DRIVER_RECEIVE_FAILED); \
        _TEXTCASE_(CTAERR_DRIVER_SEND_FAILED); \
        _TEXTCASE_(CTAERR_DRIVER_ERROR); \
        _TEXTCASE_(CTAERR_TOO_MANY_OPEN_FILES); \
        _TEXTCASE_(CTAERR_INVALID_BOARD) ; \
        _TEXTCASE_(CTAERR_OUTPUT_ACTIVE) ;\
        _TEXTCASE_(CTAERR_CREATE_MUTEX_FAILED); \
        _TEXTCASE_(CTAERR_LOCK_TIMEOUT); \
        _TEXTCASE_(CTAERR_ALREADY_INITIALIZED); \
        _TEXTCASE_(CTAERR_NOT_INITIALIZED); \
        _TEXTCASE_(CTAERR_INVALID_HANDLE); \
        _TEXTCASE_(CTAERR_PATH_NOT_FOUND); \
        _TEXTCASE_(CTAERR_FILE_NOT_FOUND); \
        _TEXTCASE_(CTAERR_FILE_ACCESS_DENIED); \
        _TEXTCASE_(CTAERR_FILE_EXISTS); \
        _TEXTCASE_(CTAERR_FILE_OPEN_FAILED); \
        _TEXTCASE_(CTAERR_FILE_CREATE_FAILED); \
        _TEXTCASE_(CTAERR_FILE_READ_FAILED); \
        _TEXTCASE_(CTAERR_FILE_WRITE_FAILED); \
        _TEXTCASE_(CTAERR_DISK_FULL); \
        _TEXTCASE_(CTAERR_CREATE_EVENT_FAILED); \
        _TEXTCASE_(CTAERR_EVENT_TIMEOUT); \
        _TEXTCASE_(CTAERR_OS_INTERNAL_ERROR); \
        _TEXTCASE_(CTAERR_INTERNAL_ERROR); \
        _TEXTCASE_(CTAERR_DUPLICATE_WAITOBJ); \
        _TEXTCASE_(CTAERR_NO_LICENSE); \
        _TEXTCASE_(CTAERR_LICENSE_EXPIRED); \
        _TEXTCASE_(CTAERR_INVALID_SYNTAX); \
        _TEXTCASE_(CTAERR_INVALID_KEYWORD); \
        _TEXTCASE_(CTAERR_SECTION_NOT_FOUND); \
        _TEXTCASE_(CTAERR_WRONG_COMPATLEVEL); \
        _TEXTCASE_(CTAERR_PARAMETER_ERROR)

/* SPECIFIC ERRORS                                                            */
/* THESE ARE CT ACCESS DISPATCHER FUNCTION ERROR CODES - NOT FOR GENERAL USE  */
#define CTAERR_INCOMPATIBLE_PARMS    0x10000001 /* Std parms did not match    */
#define CTAERR_DUPLICATE_EXTPARMS    0x10000002 /* Ext parms must be unique   */
#define CTAERR_WAIT_PENDING          0x10000003 /* Already a waiter on queue  */
#define CTAERR_WAIT_FAILED           0x10000004 /* OS specific wait failed    */
#define CTAERR_INVALID_ADDRESS       0x10000005 /* Invalid cmd/evt address    */
#define CTAERR_SERVICE_NOT_AVAILABLE 0x10000006 /* Service not available      */
#define CTAERR_SERVICE_ERROR         0x10000007 /* Error in service; bad evt  */
#define CTAERR_SERVICE_IN_USE        0x10000008 /* Service already open       */
#define CTAERR_ALREADY_DEFINED       0x10000009 /* Service/service manager
                                                   already defined            */
#define CTAERR_TRACE_NOT_ENABLED     0x1000000A /* Tracing was not enabled    */
#define CTAERR_INCOMPATIBLE_SERVICE  0x1000000B /* Incompatible dependent 
                                                   service initialized.       */


/* GENERIC REASONS */
#define CTA_REASON_FINISHED    0x00001001 /* Ran to completion.               */
#define CTA_REASON_STOPPED     0x00001002 /* Stopped short by request.        */
#define CTA_REASON_TIMEOUT     0x00001003 /* Record time limit or digit       */
                                          /* collection inter-digital timeout.*/
#define CTA_REASON_DIGIT       0x00001004 /* Abort due to touch tone or       */
                                          /* collection ended due to          */
                                          /* terminating digit.               */
#define CTA_REASON_NO_VOICE    0x00001005 /* No voice ever detected (only     */
                                          /* silence)                         */
#define CTA_REASON_VOICE_END   0x00001006 /* Silence-hangup (silence after    */
                                          /* voice).                          */
#define CTA_REASON_RELEASED    0x00001007 /* Abort because call released.     */
#define CTA_REASON_RECOGNITION 0x00001008 /* Speech recognition event occurred*/

#define CTA_GENERIC_REASONS() \
        _TEXTCASE_(CTA_REASON_FINISHED); \
        _TEXTCASE_(CTA_REASON_STOPPED); \
        _TEXTCASE_(CTA_REASON_TIMEOUT); \
        _TEXTCASE_(CTA_REASON_DIGIT); \
        _TEXTCASE_(CTA_REASON_NO_VOICE); \
        _TEXTCASE_(CTA_REASON_VOICE_END); \
        _TEXTCASE_(CTA_REASON_RELEASED); \
        _TEXTCASE_(CTA_REASON_RECOGNITION)

#ifdef __cplusplus
}
#endif

#endif
