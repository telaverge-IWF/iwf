/*****************************************************************************
  NAME:  ss7cpi.h

  PURPOSE:

      This file contains macros and function prototypes that define the API
      for the CPI service.

  Copyright (c)2001 NMS Communications Corporation. All rights reserved.
  ****************************************************************************/

#ifndef SS7CPI_INCLUDED
#define SS7CPI_INCLUDED

#include "dpruser.h"
#include "ctadef.h"

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_CONG_LVLS             4
#define MIN_POOL_SIZE             32
#define MAX_POOL_SIZE             1024

/*** RET_CODE values ***/
#define CPI_RET_SUCCESS           0x0000
#define CPI_RESOURCE_IN_USE       0x0003
#define CPI_RESOURCE_FULL         0x0005
#define CPI_INVALID_PARAMETER     0x0006
#define CPI_RESOURCE_NOT_FOUND    0x0007
#define CPI_ACCESS_DENIED         0x0008
#define CPI_GET_FAILED            0x0009
#define CPI_INVALID_DEST          0x000A
#define CPI_INVALID_LENGTH        0x0016

typedef struct  _CPI_STAT
{
    U32               succTx;      /* Success transmit       */
    U32               succRx;      /* Success receive        */
    U32               failTx;      /* Transmit failure       */
    DWORD             failTxErr;   /* Transmit failure error */
    U32               failRx;      /* Receive  failure       */
    DWORD             failRxErr;   /* Receive  failure error */
    U32               outStTx;     /* Msg sent queue         */
    U32               maxOutStTx;  /* Max on msg sent queue  */
    U32               quTx;        /* Queued msg             */
    U32               maxQuTx;     /* Max queued msg         */
    U8                congState;   /* Congestion state       */
} CPI_STAT;

/*** This is a redefinition of the mBuf structure (from SSI.X) for data  ***/
#define MAX_BUF_SIZE    1400
typedef struct                    /* NMS's definition of ss_buffer */
{
  DPRH  hdr;                      /* dual port ram header */
  S16   start;
  S16   end;
  unsigned char buffer[MAX_BUF_SIZE];
} Buffer;

typedef void* SS7CPIHD;

typedef void (*CALLBACK_RX_FN) (CTAQUEUEHD, CTA_WAITOBJ*, void*);
typedef void (*CALLBACK_NF_FN) (SS7CPIHD,   U8,           void*);

typedef CALLBACK_RX_FN  RCV_FN;
typedef CALLBACK_NF_FN  CONG_FN;

DWORD ss7CpiOpen          ( CTAHD ctahd, U8 board, U8 channel, U16 poolsize, RCV_FN rcvfunc, CONG_FN congfunc, void *userkey, SS7CPIHD *cpihd);
DWORD ss7CpiClose         ( CTAHD ctahd, SS7CPIHD cpihd );
DWORD ss7CpiSend          ( SS7CPIHD cpihd, Buffer *mBuf );
DWORD ss7CpiGetData       ( SS7CPIHD cpihd, Buffer *mBuf, short *len );
DWORD ss7CpiAllocateBuffer( SS7CPIHD cpihd, Buffer **mBuf );
DWORD ss7CpiGetStat       ( SS7CPIHD cpihd, CPI_STAT *stat, U8 reset );
DWORD ss7CpiStop          ( CTAHD    ctahd, SS7CPIHD cpihd );
DWORD ss7CpiStart         ( CTAHD    ctahd, SS7CPIHD cpihd );

#ifdef __cplusplus
}
#endif

#endif /* SS7CPI_INCLUDED */
