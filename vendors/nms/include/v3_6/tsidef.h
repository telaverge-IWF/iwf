/******************************************************************************
*
*                                  TSIDEF.H
*
*    Defines mnemonics, structures, and function prototypes used by the
*    telephony services interface (TSI) module which is part of CT Access
*    architecture.  
*
*    NMS does not support external use of this module.
*    Do not use this module within applications. This module is 
*    only shipped to customers to support the sample TIK Service.
*
*
* Copyright (c)1994-96 Natural Microsystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef TSIDEF_INCLUDED
#define TSIDEF_INCLUDED


#ifndef NMSTYPES_INCLUDED
  #include <nmstypes.h>
#endif

#ifdef UNIX
    #ifdef MULTITHREAD
        #include <thread.h>
    #endif
#endif

#ifdef __cplusplus
  extern "C" {
#endif



/*****************************************************************************
    Win32 types
*****************************************************************************/

#if defined (WIN32)

    typedef  unsigned long TIMEOUT ;
    typedef  void*         TSIMTXHDL;      /* Mutex Sem Handle             */
    typedef  void*         TSIEVNHDL;      /* Event Handle                 */

/*****************************************************************************
    UNIX types
*****************************************************************************/

#elif defined (UNIX)

    typedef  int           TIMEOUT ;
    typedef  unsigned int  TSIMTXHDL;      /* Mutex Sem Handle             */
    typedef  unsigned int  TSIEVNHDL;      /* Event Handle                 */

#endif /* OS2 ... UNIX */




unsigned NMSSTDCALL tsiSleepMs(
     unsigned msec );            /* time in milliseconds              */



/*----------------------------------------------------------------------------
  IPC object names.
  --------------------------------------------------------------------------*/
typedef void* TSIIPC_ACCEPTOR_HD;
typedef void* TSIIPC_STREAM_HD;
typedef void* TSIIPC_WAIT_OBJ_HD;

/*---------------------------------------------------------------------------
  The tsiIPCCommandStructure, which is used to get the results of 
  asynchronous operations.
  -------------------------------------------------------------------------*/
typedef struct
{
    /* Error code for a pending read operation, 
       and the number of bytes read. */
    int ReadError;
    int ReadBytes;

    /* Error code for a pending write operation, 
       and the number of bytes written. */
    int WrittenError;
    int WrittenBytes;
} 
TSIIPC_COMMAND_STATUS;

/*----------------------------------------------------------------------------
  Structure that is used to return information about a stream.
  --------------------------------------------------------------------------*/
typedef struct
{
    /* Bytes in structure that were set. */
    unsigned Size;
    /* Flags that define operation. */
    unsigned Flags;
    /* Port number used for communication. */
    WORD PortNumber;
}
TSIIPC_INFO;

/*----------------------------------------------------------------------------
  IPC communication endpoint creation flags.
  --------------------------------------------------------------------------*/

/* Perform asynchronous reads & writes.  If this flags is not set, all IPC
   operations will be sychronous. */
#define TSIIPC_ASYNCH                0x00000001

/* Causes all reads and writes to attempt to read all data that a buffer can
   hold or write all data that is in a buffer.  Without this flag specified,
   only synchronous writes attempt to actually write all the data that it is 
   given. */
#define TSIIPC_CHUNK_MODE            0x00000002

/*==========================================================================*/

/*----------------------------------------------------------------------------
  IPC return codes.
  --------------------------------------------------------------------------*/

/* Would block on function call if endpoint was opened in synchronous mode. */
#define TSIIPC_WOULD_BLOCK           ((DWORD)-1)

/* Some generic error has occurred. Call tsiIPCGetLastErrorString to get 
   more information. */
#define TSIIPC_ERROR                 ((DWORD)-2)

/* Invalid handle was passed to function. */
#define TSIIPC_INVALID_HANDLE        ((DWORD)-3)

/* Either you must be in asynchronous mode to use this function, or
   you're trying to get the results of a command that didn't happen. */
#define TSIIPC_BAD_COMMAND           ((DWORD)-4)

/* Out of memory.  System may become unusable soon. */
#define TSIIPC_OUT_OF_MEMORY         ((DWORD)-5)

/* Stream has been closed. */
#define TSIIPC_CLOSED_STREAM         ((DWORD)-6)

/* Command is still being completed. 
   Wait on the associated wait object again. */
#define TSIIPC_COMMAND_PROCEEDING    ((DWORD)-7)

/* Duplicate handle passed to function. */
#define TSIIPC_DUPLICATE_HANDLE      ((DWORD)-8)



DWORD NMSSTDCALL tsiIPCCreateAcceptor(WORD PortNumber, 
                                      unsigned Flags,
                                      TSIIPC_ACCEPTOR_HD* phIPCAcceptor);

DWORD NMSSTDCALL tsiIPCDestroyAcceptor(TSIIPC_ACCEPTOR_HD hIPCAcceptor);

DWORD NMSSTDCALL tsiIPCCreateAcceptorStream(TSIIPC_ACCEPTOR_HD hIPCAcceptor,
                                            int Timeout,
                                            TSIIPC_STREAM_HD* phIPCStream);

DWORD NMSSTDCALL tsiIPCCommandComplete(void* hIPCObject, 
                                       TSIIPC_COMMAND_STATUS* pCommandStatus); 

DWORD NMSSTDCALL tsiIPCDestroyStream(TSIIPC_STREAM_HD hIPCStream);

DWORD NMSSTDCALL tsiIPCCreateConnectorStream(char* DestinationName,
                                             WORD PortNumber,
                                             int Flags,
                                             int Timeout,
                                             TSIIPC_STREAM_HD* phIPCStream);

DWORD NMSSTDCALL tsiIPCReadStream(TSIIPC_STREAM_HD hIPCStream, 
                                  void* Buffer, 
                                  int Size, 
                                  int Timeout,
                                  int* pRead);
    
DWORD NMSSTDCALL tsiIPCWriteStream(TSIIPC_STREAM_HD HIPCStream, 
                                   void* Buffer, 
                                   int Size,
                                   int Timeout,
                                   int* pWritten);

DWORD NMSSTDCALL tsiIPCGetLastErrorString(void* hIPCObject, 
                                          char* Buffer, 
                                          int Size);

DWORD NMSSTDCALL tsiIPCGetInfo(void* hIPCObject,
                               TSIIPC_INFO* pInfo,
                               int Size);

DWORD NMSSTDCALL tsiIPCGetWaitObject(void* hIPCObject,
                                     TSIIPC_WAIT_OBJ_HD* pWaitObject);
    
DWORD NMSSTDCALL
      tsiIPCRegisterWaitObjectCopy(void* hIPCObject,
                                   TSIIPC_WAIT_OBJ_HD hWaitObject);

/******************** [TSIIPC: IPC wait functions] *************************/

/* Wait object list type name. */
typedef void* TSIIPC_WAIT_OBJ_LIST_HD; 

/*---------------------------------------------------------------------------
  Maximum number of wait objects that can be contained in a list. 
  -------------------------------------------------------------------------*/

#ifdef WIN32
#define TSIIPC_WAIT_LIST_MAX 64

#elif defined(OS2)
#define TSIIPC_WAIT_LIST_MAX 64

/* This will cause 96KB of memory to be statically allocated. */
#elif defined(UNIX)
#define TSIIPC_WAIT_LIST_MAX 8192

#endif

/*-------------------------------------------------------------------------*/

DWORD NMSSTDCALL tsiIPCWait(TSIIPC_WAIT_OBJ_HD hWaitObject, 
                            int Timeout);

DWORD NMSSTDCALL 
      tsiIPCCreateWaitObjectList(TSIIPC_WAIT_OBJ_LIST_HD* phWaitObjectList);
                               
DWORD NMSSTDCALL 
      tsiIPCDestroyWaitObjectList(TSIIPC_WAIT_OBJ_LIST_HD hWaitObjectList);
 
DWORD NMSSTDCALL 
      tsiIPCWaitObjectListAdd(TSIIPC_WAIT_OBJ_LIST_HD hWaitObjectList,
                              TSIIPC_WAIT_OBJ_HD hWaitObject);
 
DWORD NMSSTDCALL 
      tsiIPCWaitObjectListDetach(TSIIPC_WAIT_OBJ_LIST_HD hWaitObjectList,
                                 TSIIPC_WAIT_OBJ_HD hWaitObject);

DWORD NMSSTDCALL 
      tsiIPCWaitObjectListFind(TSIIPC_WAIT_OBJ_LIST_HD hWaitObjectList,
                              TSIIPC_WAIT_OBJ_HD hWaitObject, unsigned* dwIndex);

DWORD NMSSTDCALL 
      tsiIPCWaitObjectListWait(TSIIPC_WAIT_OBJ_LIST_HD hWaitObjectList,
                               int Timeout,
                               TSIIPC_WAIT_OBJ_HD* phWaitObject);



#ifdef __cplusplus
}
#endif

#endif  /* ifndef TSIDEF_INCLUDED */

