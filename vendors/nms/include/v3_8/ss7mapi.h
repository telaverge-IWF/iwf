/****************************************************************************************************
                                         SS7MAPI.H

  This file contains definitions, etc. local to the SS7 Management API that need not be known to
  outside developers.
 ****************************************************************************************************/

#ifndef _SS7MAPI_H_
#define _SS7MAPI_H_

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_SS7_SOURCE_"; this is only for use
 * by the SS7 API source code itself.
 */

/* OS2: SS7 API is a DLL */
#ifdef __OS2__
#ifdef _TX_SS7_SOURCE_
    /* SS7 API source definition */
#define     TXSS7FUNC               extern _export _syscall
#else
    /* SS7 API caller's definition */
#define     TXSS7FUNC               _syscall
#endif  /* _TX_SS7_SOURCE_ */

/* WIN32: SS7 API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_SS7_SOURCE_
    /* SS7 API source definition */
#define     TXSS7FUNC               __declspec( dllexport ) WINAPI
#else
    /* SS7 API caller's definition */
#define     TXSS7FUNC               WINAPI
#endif  /* _TX_SS7_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXSS7FUNC
#endif

#ifdef UNIX
#define TRUE  1
#define FALSE 0
#endif


/* Error type returned by API functions */
typedef S16 SS7_STATUS;   /* redefine for portability */

/* Mgmt API return codes */
#define SS7_SUCCESS     0           /* Successful */
#define SS7_LNKTYPE     0x1001      /* Invalid link/switch type */
#define SS7_PARAM       0x1002      /* Invalid parameter */
#define SS7_BOARD       0x1004      /* board number out of range */
#define SS7_DRIVER      0x1005      /* CPI driver returned error        */
#define SS7_HANDLE      0x1006      /* Board not previously initialized */
#define SS7_TIMEOUT     0x1007      /* No response from board */
#define SS7_TOOMANY     0x1008      /* There are already too many handles open for this board */

SS7_STATUS  TXSS7FUNC   SS7MgmtInit     ( U8 board, U8 srcEnt, U8 srcInst, TX_HANDLE *handle );
SS7_STATUS  TXSS7FUNC   SS7MgmtTerm     ( U8 board, U8 srcEnt );

#endif      /* define _SS7MAPI_H_ */

