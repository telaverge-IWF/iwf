/*****************************************************************************
*                                  PPXDEF.H
*
*  This is the include file for the Point-to-Point Switching Manager (PPX) API.
*
* 03/17/99 PPX_SVCID changed from 0xD to 0x17
*
* Copyright (c)1998 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef PPXDEF_INCLUDED
#define PPXDEF_INCLUDED 1

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NMSTYPES_INCLUDED
#include <nmstypes.h>
#endif
    
#ifndef CTADEF_INCLUDED
#include <ctadef.h>
#endif
    
#include <mvip95.h>
    
/*====== COMMON DEFINES AND STRUCTURES =====================================*/
    
#define PPX_SVCID 0x17
    typedef DWORD PPXHD;
    
    typedef DWORD PPXPT;
#define NULL_PPXPT 0xFFFFFFFF
    
    typedef enum {PPX_NONE, PPX_SIMPLEX, PPX_DUPLEX, PPX_QUAD} PPX_CX_MODE;
    
    typedef struct _PPX_HANDLE_PARMS
    {
        DWORD size;
        BYTE  default_pattern;
        DWORD *reservation_key;
    } PPX_HANDLE_PARMS;
    
    typedef struct _PPX_MVIP_ADDR
    {
        DWORD switch_number; /* switch number specified in config file */
        DWORD bus;           /* MVIP bus type                          */
        DWORD stream;        /* stream number                          */
        DWORD timeslot;      /* timeslot                               */
    } PPX_MVIP_ADDR;

/* Array limit in single call to ppxAddListeners */
#define PPX_MAX_COUNT 22

/*-----------------------------------------------------------------------------
  Initialization defines and structures
  ---------------------------------------------------------------------------*/
    typedef void * PPX_SWITCHHD;
    typedef void * PPX_BUSHD;

/* Switch Types supported: */    
#define PPX_FMIC_SWITCH 0x1
#define PPX_HMIC_SWITCH 0x2
#define PPX_ATI_SWITCH  0x3

    typedef struct _PPX_SWITCH_PARMS
    {
        DWORD size;
        DWORD switch_number;
        DWORD switch_type;
        char  device_name[24];
        DWORD device_number;
        DWORD hw_standard;
        DWORD sw_standard;
        DWORD enabled;
        DWORD internal[1];
    } PPX_SWITCH_PARMS;
    
    typedef struct _PPX_STREAM_DEFINITION
    {
        MVIP95_TERMINUS low_bound;
        MVIP95_TERMINUS high_bound;
        
        /* timeslots to skip, e.g. if low_bound timeslot
         * is 0, and high_bound is timeslot is 7, and increment is 1,
         * then the actual timelots will be bus:stream:0, bus:stream:2,
         * bus:stream:4, bus:stream:6.
     */
        DWORD timeslot_increment; 
    } PPX_STREAM_DEFINITION;
    
    typedef struct _PPX_MVIP_DOMAIN_PARMS
    {
        DWORD count;
        PPX_STREAM_DEFINITION points[1];
    } PPX_MVIP_DOMAIN_PARMS;
    
    typedef PPX_MVIP_DOMAIN_PARMS PPX_MVIP_BUS_PARMS;
    
/*-----------------------------------------------------------------------------
 Connection Handle functions
-----------------------------------------------------------------------------*/

/*****************************************************************************
 * Function - ppxCreateConnection
 *
 * Description -
 *
 *      Creates a connection block and returns a handle to it.
 *
 * Returns -
 * 
 *      SUCCESS
 *      CTAERR_OUT_OF_MEMORY             - malloc or realloc error
 *      PPXERR_COMM_FAILURE              - Problems encountered communicating with 
 *                                         server
 *      PPXERR_CONNECTION_ALREADY_EXISTS - There is already a connection in 
 *                                         the PPX connection database with the
 *                                         specified "name". See:
 *                                            ppxDestroyNamedConnection().
 *****************************************************************************/
DWORD NMSAPI ppxCreateConnection( CTAHD ctahd,
                                  char *name,
                                  PPX_HANDLE_PARMS *parms,
                                  PPXHD *ppxhd );

/*****************************************************************************
 * Function - ppxOpenConnection
 *
 * Description -
 *
 * Open a previously created named connection and returns a handle it.
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_BAD_ARGUMENT   - "name" parameter is either NULL or is a pointer
 *                              to a string of zero length
 *      CTAERR_NOT_FOUND      - "name"d connection can not be found in the PPX
 *                              connection database
 *      CTAERR_OUT_OF_MEMORY  - malloc or realloc error
 *      PPXERR_COMM_FAILURE   - Problems encountered communicating with server 
 *****************************************************************************/
DWORD NMSAPI ppxOpenConnection( CTAHD ctahd,
                                char *name,
                                PPX_HANDLE_PARMS *parms,
                                PPXHD *ppxhd );

/*****************************************************************************
 * Function - ppxCloseConnection
 *
 * Description -
 *
 * Closes a connection block. If unnamed, in addition to freeing all client 
 * owned resources for the connection, all connections outputs also
 * become disabled.  
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_INVALID_HANDLE - ppxhd is not a valid connection handle
 *      CTAERR_OUT_OF_MEMORY  - malloc or realloc error
 *      PPXERR_COMM_FAILURE   - Problems encountered communicating with server
 *****************************************************************************/
DWORD NMSAPI ppxCloseConnection( PPXHD ppxhd );


/*****************************************************************************
 * Function - ppxDestroyNamedConnection
 *
 * Description -
 *
 * Frees all resources and disables outputs to all points for a named 
 * connection. 
 * 
 *        Note: Any open handles to the named connection immediately
 *              become invalid, in all applications.
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_INVALID_HANDLE - ppxhd is not a valid connection handle
 *      CTAERR_NOT_FOUND      - name of connection (referenced through the
 *                              "ppxhd" parameter) can not be found in the PPX
 *                              connection database
 *      CTAERR_OUT_OF_MEMORY  - malloc or realloc error
 *      PPXERR_COMM_FAILURE   - Problems encountered communicating with server
 *****************************************************************************/
DWORD NMSAPI ppxDestroyNamedConnection( PPXHD ppxhd );
 
/*-----------------------------------------------------------------------------
 Initialization functions
-----------------------------------------------------------------------------*/

/*****************************************************************************
 * Function - ppxRestoreConnections
 *
 * Description -
 *
 * At application exit, this causes the server to re-establish any of the 
 * initial ppx.cfg connections that were modified by the application during
 * its execution.  
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_INVALID_CTAHD
 *      CTAERR_OUT_OF_MEMORY - malloc or realloc error
 *      PPXERR_COMM_FAILURE  - Problems encountered communicating with server
 *****************************************************************************/
DWORD NMSAPI ppxRestoreConnections( CTAHD ctahd );


    
/*****************************************************************************
 * Function - ppxShowDB
 *
 * Description -
 *
 * This function causes the PPX server to output its runtime database to 
 * a text file.
 *
 * Returns -
 *
 * SUCCESS
 * CTAERR_INVALID_CTAHD
 * CTAERR_OUT_OF_MEMORY
 * PPXERR_COMM_FAILURE  - Problems encountered communicating with server
 *****************************************************************************/
DWORD NMSAPI ppxShowDB( CTAHD ctahd ) ;



/*-----------------------------------------------------------------------------
 Switching functions
-----------------------------------------------------------------------------*/

/*****************************************************************************
 * Function - ppxSetTalker
 *
 * Description -
 *
 * Sets a talker for a connection  (input terminus)
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_DRIVER_ERROR      - The underlying driver retrieved an unrecog-
 *                                 nized error. Call swiGetLastError to retrieve
 *                                 the MVIP device error code.
 *      CTAERR_INVALID_HANDLE    - ppxhd is not a valid handle to a connection
 *                                 in the PPX connection database
 *      CTAERR_NOT_FOUND         - the specified "talker" is not defined 
 *                                 within the PPX database (per ppx.cfg)
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_DRIVER_OPEN_FAILED- Either the driver open failed or the driver
 *                                 dynamic link library or device was not found
 *      PPXERR_INVALID_SWITCH    - Switch number specified is inaccessible
 *                                 from the specified bus:stream:timelslot.
 *      PPXERR_NO_PATH           - Could not find a path from the "talker" to
 *                                 one of the "listeners" assigned to the 
 *                                 connection
 *      PPXERR_NOT_TALKER        - The specified "talker" is incapable of 
 *                                 driving the output for the connection
 *      SWIERR_INVALID_PARAMETER - A board-specific clock parameter value 
 *                                 was invalid.  
 *      SWIERR_INVALID_STREAM    - One or more of the streams specified is 
 *                                 invalid
 *      SWIERR_INVALID_TIMESLOT  - One or more of the timeslots specified is
 *                                 invalid.    
 *
 *        Note: The SWIERR_* errors and CTAERR_DRIVER_ERROR may be returned
 *              from calls made by PPX to:
 *
 *                swiSendPattern(), swiDisableOutput(), or swiMakeConnection().
 *
 *              If these occur, validate that the bus streams and timeslots 
 *              defined within the ppx.cfg file are accurate in both the bus
 *              definition(s) and within the switch definition for INPUTS and
 *              OUTPUTS.
 *
 *              If PPXERR_DRIVER_OPEN_FAILED, validate that the "DeviceName" 
 *              and "DeviceNumber" fields are accurate in the ppx.cfg switch
 *              definitions.
 *           
 *****************************************************************************/
DWORD NMSAPI ppxSetTalker( PPXHD ppxhd,
                           PPX_MVIP_ADDR *talker );

/*****************************************************************************
 * Function - ppxAddListeners
 *
 * Description -
 *
 * Adds listeners to a connection (output terminus)
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_DRIVER_ERROR      - The underlying driver retrieved an unrecog-
 *                                 nized error. Call swiGetLastError to retrieve
 *                                 the MVIP device error code.
 *      CTAERR_INVALID_HANDLE    - ppxhd is not a valid handle to a connection
 *                                 in the PPX connection database
 *      CTAERR_NOT_FOUND         - the specified "listener" is not defined 
 *                                 within the PPX database (per ppx.cfg)
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error

 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_DRIVER_OPEN_FAILED- Either the driver open failed or the driver
 *                                 dynamic link library or device was not found
 *      PPXERR_INVALID_COUNT     - The number of suppplied listeners is less
 *                                 than the number indicated by "count"
 *      PPXERR_INVALID_SWITCH    - Switch number specified is inaccessible
 *                                 from the specified bus:stream:timelslot.
 *      PPXERR_LISTENER_BUSY     - "listener" point is already assigned to 
 *                                 another connection.
 *      PPXERR_NO_PATH           - Could not find a path from the "talker" to
 *                                 one of the "listeners" assigned to the 
 *                                 connection
 *      PPXERR_NOT_LISTENER      - The specified "listener" is incapable of 
 *                                 receiving output from the connection
 *      SWIERR_INVALID_PARAMETER - A board-specific clock parameter value 
 *                                 was invalid.  
 *      SWIERR_INVALID_STREAM    - One or more of the streams specified is 
 *                                 invalid
 *      SWIERR_INVALID_TIMESLOT  - One or more of the timeslots specified is
 *                                 invalid.    
 *
 *        Note: The SWIERR_* and CTAERR_DRIVER_ERROR errors may be returned
 *              from calls made by PPX to:
 *
 *                swiSendPattern(), swiDisableOutput(), or swiMakeConnection().
 *
 *              If these occur, validate that the bus streams and timeslots 
 *              defined within the ppx.cfg file are accurate, in both the bus
 *              definition(s) and within the switch definition for INPUTS and
 *              OUTPUTS.
 *               
 *              If PPXERR_DRIVER_OPEN_FAILED is returned, validate that the
 *              "DeviceName" and "DeviceNumber" fields are accurate in the 
 *              ppx.cfg switch definitions.
 *
 *****************************************************************************/
DWORD NMSAPI ppxAddListeners( PPXHD ppxhd,
                              PPX_MVIP_ADDR listeners[],
                              unsigned count);

/*****************************************************************************
 * Function - ppxRemoveListeners
 *
 * Description -
 *
 * Removes listeners from a connection
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_DRIVER_ERROR       - The underlying driver retrieved an unrecog-
 *                                  nized error. Call swiGetLastError to retrieve
 *                                  the MVIP device error code
 *      CTAERR_INVALID_HANDLE     - ppxhd is not a valid handle to a connection
 *                                  in the PPX connection database
 *      CTAERR_NOT_FOUND          - the specified "listener" is not defined 
 *                                  within the PPX database (per ppx.cfg)
 *      CTAERR_OUT_OF_MEMORY      - malloc or realloc error
 *      PPXERR_COMM_FAILURE       - Problems encountered communicating with 
 *                                  server
 *      PPXERR_DRIVER_OPEN_FAILED - Either the driver open failed or the driver
 *                                  dynamic link library or device was not found
 *      PPXERR_INVALID_COUNT      - The number of suppplied listeners is less
 *                                  than the number indicated by "count"
 *      PPXERR_INVALID_SWITCH     - Switch number specified is inaccessible
 *                                  from the specified bus:stream:timelslot.
 *      PPXERR_NOT_CONNECTED      - The specified "listener" is not  
 *                                  receiving output on this connection
 *      PPXERR_NOT_LISTENER       - The specified "listener" is incapable of 
 *                                  receiving output from the connection
 *      SWIERR_INVALID_STREAM     - One or more of the streams specified is 
 *                                  invalid
 *      SWIERR_INVALID_TIMESLOT   - One or more of the timeslots specified is
 *                                  invalid.    
 *
 *        Note: The SWIERR_* and CTAERR_DRIVER_ERROR errors may be returned
 *              from calls made by PPX to:
 *
 *                swiSendPattern(), swiDisableOutput(), or swiMakeConnection().
 *
 *              If these occur, validate that the bus streams and timeslots 
 *              defined within the ppx.cfg file are accurate in both the bus
 *              definition(s) and within the switch definition for INPUTS and
 *              OUTPUTS.
 *               
 *              If PPXERR_DRIVER_OPEN_FAILED is returned, validate that the 
 *              "DeviceName" and "DeviceNumber" fields are accurate in the 
 *              ppx.cfg switch definitions.
 *****************************************************************************/
DWORD NMSAPI ppxRemoveListeners( PPXHD ppxhd,
                                 PPX_MVIP_ADDR listeners[],
                                 unsigned count);

/*****************************************************************************
 * Function - ppxSetDefaultPattern
 *
 * Description -
 *
 * Sets the default pattern for a connection
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_DRIVER_ERROR      - The underlying driver retrieved an unrecog-
 *                                 nized error. Call swiGetLastError to retrieve
 *                                 the MVIP device error code.
 *      CTAERR_INVALID_HANDLE    - ppxhd is not a valid handle to a connection
 *                                 in the PPX connection database
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_DRIVER_OPEN_FAILED- Either the driver open failed or the driver
 *                                 dynamic link library or device was not found 
 *      SWIERR_INVALID_PARAMETER - A board-specific clock parameter value 
 *                                 was invalid.  
 *      SWIERR_INVALID_STREAM    - One or more of the streams specified is 
 *                                 invalid
 *      SWIERR_INVALID_TIMESLOT  - One or more of the timeslots specified is
 *                                 invalid.    
 *
 *        Note: The SWIERR_* errors and CTAERR_DRIVER_ERROR may be returned
 *              from calls made by PPX to:
 *
 *                swiSendPattern(), swiDisableOutput(), or swiMakeConnection().
 *
 *              If these occur, validate that the bus streams and timeslots 
 *              defined within the ppx.cfg file are accurate in both the bus
 *              definition(s) and within the switch definition for INPUTS and
 *              OUTPUTS.
 *               
 *              If PPXERR_DRIVER_OPEN_FAILED occurs, validate that the 
 *              "DeviceName" and "DeviceNumber" fields are accurate in the 
 *              ppx.cfg switch definitions.
 *****************************************************************************/
DWORD NMSAPI ppxSetDefaultPattern( PPXHD ppxhd,
                                   BYTE pattern);


/*****************************************************************************
 * Function - ppxConnect
 *
 * Description -
 *
 * Connects an input to an output.
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_DRIVER_ERROR      - The underlying driver retrieved an unrecog-
 *                                 nized error. Call swiGetLastError to retrieve
 *                                 the MVIP device error code.
 *      CTAERR_NOT_FOUND         - either the specified "listener" or "talker"
 *                                 is not defined within the PPX database 
 *                                 (per ppx.cfg)
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_DRIVER_OPEN_FAILED- Either the driver open failed or the driver
 *                                 dynamic link library or device was not found
 *      PPXERR_INVALID_SWITCH    - Switch number specified is inaccessible
 *                                 from the specified bus:stream:timelslot.
 *      PPXERR_LISTENER_BUSY     - "listener" point is already assigned to 
 *                                 another connection.
 *      PPXERR_NO_PATH           - Unable to find a path from the "talker" to
 *                                 the "listener"
 *      PPXERR_NOT_TALKER        - The specified "talker" is incapable of 
 *                                 driving the output for the connection
 *      PPXERR_NOT_LISTENER      - The specified "listener" is incapable of 
 *                                 receiving output from the connection

 *      SWIERR_INVALID_STREAM    - One or more of the streams specified is 
 *                                 invalid
 *      SWIERR_INVALID_TIMESLOT  - One or more of the timeslots specified is
 *                                 invalid.    
 *
 *        Note: The SWIERR_* errors and CTAERR_DRIVER_ERROR may be returned
 *              from calls made by PPX to:
 *
 *                swiSendPattern(), swiDisableOutput(), or swiMakeConnection().
 *
 *              If these occur, validate that the bus streams and timeslots 
 *              defined within the ppx.cfg file are accurate in both the bus
 *              definition(s) and within the switch definition for INPUTS and
 *              OUTPUTS.
 *               
 *              If PPXERR_DRIVER_OPEN_FAILED, validate that the "DeviceName" 
 *              and "DeviceNumber" fields are accurate in the ppx.cfg switch
 *              definitions.
 *****************************************************************************/
DWORD NMSAPI ppxConnect( CTAHD ctahd,
                         PPX_MVIP_ADDR *from,
                         PPX_MVIP_ADDR *to,
                         PPX_CX_MODE mode );
                                   
/*****************************************************************************
 * Function - ppxDisconnect
 *
 * Description -
 *
 *   Disconnects an output from an input.
 *
 * Note:
 *
 *   If the "talker" parameter is passed as a NULL, the output will be
 *   disabled regardless to which point it is connected. That is, provided
 *   the calling application owns the "listener" point, i.e., established
 *   the original connection. 
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_NOT_FOUND         - either the specified "listener" or "talker"
 *                                 is not defined within the PPX database 
 *                                 (per ppx.cfg)
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *      CTAERR_INVALID_HANDLE    - ppxhd is not a valid handle to a connection
 *                                 in the PPX connection database
 *      CTAERR_DRIVER_ERROR      - The underlying driver retrieved an unrecog-
 *                                 nized error. Call swiGetLastError to retrieve
 *                                 the MVIP device error code.
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_CONN_OWNERSHIP    - The "listener" point is in a connection 
 *                                 not owned by the calling application, or
 *                                 the connection was nailed up at initiali-
 *                                 zation via the ppx.cfg file.
 *      PPXERR_DRIVER_OPEN_FAILED- Either the driver open failed or the driver
 *                                 dynamic link library or device was not found
 *      PPXERR_INVALID_SWITCH    - Switch number specified is inaccessible
 *                                 from the bus:stream:timelslot.
 *      PPXERR_NOT_CONNECTED     - The specified "listener" is not re- 
 *                                 ceiving output from the specified "talker"
 *      PPXERR_NOT_LISTENER      - The specified "listener" is incapable of 
 *                                 receiving output from a connection
 *      PPXERR_NOT_TALKER        - The specified "talker" is incapable of 
 *                                 driving the output for the connection
 *      SWIERR_INVALID_PARAMETER - A board-specific clock parameter value 
 *                                 was invalid.  
 *      SWIERR_INVALID_STREAM    - One or more of the streams specified is 
 *                                 invalid
 *      SWIERR_INVALID_TIMESLOT  - One or more of the timeslots specified is
 *                                 invalid.    
 *
 *        Note: The SWIERR_* errors and CTAERR_DRIVER_ERROR may be returned
 *              from calls made by PPX to:
 *
 *                swiSendPattern(), swiDisableOutput(), or swiMakeConnection().
 *
 *              If these occur, validate that the bus streams and timeslots 
 *              defined within the ppx.cfg file are accurate in both the bus
 *              definition(s) and within the switch definition for INPUTS and
 *              OUTPUTS.
 *               
 *              If PPXERR_DRIVER_OPEN_FAILED, validate that the "DeviceName" 
 *              and "DeviceNumber" fields are accurate in the ppx.cfg switch
 *              definitions. 
 *****************************************************************************/
DWORD NMSAPI ppxDisconnect( CTAHD ctahd,
                            PPX_MVIP_ADDR *talker,
                            PPX_MVIP_ADDR *listener,
                            PPX_CX_MODE mode );

/*****************************************************************************
 * Function - ppxBegin
 *
 * Description -
 *
 * Begins the collection of PPX commands to be sent to the server when the
 * ppxSubmit function is called.
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_INVALID_COMMAND   - a ppxBegin() is already active
 *****************************************************************************/
DWORD NMSAPI ppxBegin( CTAHD ctahd );

/*****************************************************************************
 * Function - ppxCancelBegin
 *
 * Description -
 *
 * Cancels the collection of PPX commands started by ppxBegin() and releases
 * any resources associated with the collected commands.
 *
 * Returns -
 *
 *      SUCCESS
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_INVALID_COMMAND   - a ppxBegin() was not called
 *****************************************************************************/
DWORD NMSAPI ppxCancelBegin( CTAHD ctahd );

/*****************************************************************************
 * Function - ppxSubmit
 *
 * Description -
 * Submit a series of PPX commands to the server. 
 *
 * Returns -
 *  
 *   Immediate returns:
 *
 *      SUCCESS
 *      CTAERR_OUT_OF_MEMORY     - malloc or realloc error
 *      PPXERR_COMM_FAILURE      - Problems encountered communicating with 
 *                                 server
 *      PPXERR_INVALID_COMMAND   - a ppxBegin() was not called.
 *
 *   An asynchronous PPX event: PPXEVN_SUBMIT_COMPLETE
 *   will be generated when all commands issued since the ppxBegin() have been
 *   processed. The event will contain the first non-SUCCESS return issued
 *   by these commands. 
 *
 *   If an error is encountered, the state of the PPX connection database and 
 *   the state of the switches will be restored to their states at the time of
 *   the ppxBegin()  being issued. Refer to the individual commands for an
 *   understanding of the particular error value returned within the event.
 *****************************************************************************/
DWORD NMSAPI ppxSubmit( CTAHD ctahd );

/*-----------------------------------------------------------------------------
  Point to Point Switching Manager Error Codes
  ---------------------------------------------------------------------------*/
    
/*-----------------------------------------------------------------------------
  General Errors
  ---------------------------------------------------------------------------*/
#define PPXERR_INVALID_COMMAND           0x170000
#define PPXERR_LISTENER_BUSY             0x170001
#define PPXERR_CONNECTION_ALREADY_EXISTS 0x170002
#define PPXERR_UNKNOWN_SWITCHTYPE        0x170003    
#define PPXERR_CFG_FAILED                0x170004
#define PPXERR_NO_PATH                   0x170005
#define PPXERR_INCOMPLETE                0x170006
#define PPXERR_NOT_LISTENER              0x170007
#define PPXERR_NOT_TALKER                0x170008
#define PPXERR_INVALID_COUNT             0x170009
#define PPXERR_COMM_FAILURE              0x17000A
#define PPXERR_INVALID_SWITCH            0x17000B
#define PPXERR_DRIVER_OPEN_FAILED        0x17000C
#define PPXERR_NOT_CONNECTED             0x17000D
#define PPXERR_CONN_OWNERSHIP            0x17000E
#define PPXERR_DISABLED                  0x17000F


/*----------------------------------------------------------------------------
  Generic Errors
  --------------------------------------------------------------------------*/
#define PPXERR_UNKNOWN_ERROR             0x170013
    
/*-----------------------------------------------------------------------------
  EVENT CODES
  ---------------------------------------------------------------------------*/
#define PPXEVN_BASE             ((PPX_SVCID << 16) + CTA_CODE_EVENT)    
#define PPXEVN_SUBMIT_COMPLETE  (PPXEVN_BASE + 1)
    

#ifdef __cplusplus
    }
#endif

#endif
