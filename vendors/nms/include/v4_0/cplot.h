/*****************************************************************************
 *
 * cplot.h
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _CPLOT_H
#define _CPLOT_H

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: pack on 1-byte boundaries
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack(1)
#endif
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
#ifdef _WINNT
#pragma pack(1)
#endif

#include <txnuser.h>                /* include base TXN user interface */

/*****************************************************************************
 * TXLOAD_PARAMS - description of task for loading to all supported TX boards
 *****************************************************************************/
typedef struct
{
    S16           intno;      /* Software interrupt to CPI [NO LONGER USED] */
    S16           cp;         /* CP number */
    U32           dpbase;     /* dual port ram base [NO LONGER USED] */
    S8           *loadfile;   /* pointer to task/kernel load filename */
    S8           *descrip;    /* pointer to 80 byte array for description */
    S16           kernel;     /* kernel flag [NO LONGER USED] */
    S16           destroy;    /* destroy flag [NO LONGER USED] */
    S16           debug;      /* debug flag */
    U8            cpkfunc;    /* Special CPK Function flag */
    S8            cpkfunctyp; /* Special CPK Function type */
    S8            cpkmicro;   /* CPK Microcode type <C6.50> */
    U8            cpkq32cnt;  /* number of processors to put into QUICC32 mode */

    /* CPK options byte */
#define CPKOPTS_PACKED  (1<<7)  /* set = packed options in use */
#define CPKOPTS_SS7MC   (1<<6)  /* set = SS7 microcode to be loaded to all non-QUICC32 CPUs */
    /* low-order 3 bits indicate number of processors to operate in QUICC32 mode */

    /* Task Parameters */
    S8            name[10];   /* name of task */
    U32           exopts;     /* task execution options */
    S16           priority;   /* task priority */
#ifdef NMSTX_ALIGN_32
    U8            pad_1[2];   /* pad to natural alignment */
#endif
    U32           stack_size; /* task stack size */
    S16           autostart;  /* autostart flag */
#ifdef NMSTX_ALIGN_32
    U8            pad_2[2];   /* pad to natural alignment */
#endif
    TX_HANDLE     cpi_handle; /* handle to use talking to cpi lib */
    /* UNABLE TO PAD STRUCTURE SIZE TO NATURAL ALIGNMENT FOR ALL HOST OS TYPES */
}
LOADER_PARAMS;

#define TXLOADER_TASKNAME_SZ    16
#define TXLOADER_LOADFILE_SZ    128
#define TXLOADER_CMDLINE_SZ     128
#define TXLOADER_DESCRIP_SZ     128

/*****************************************************************************
 * TXLOADER_DESC - description of task for TX-based task loading
 *                 (legacy TX board types not supported)
 *****************************************************************************/
typedef struct
{
    /* ----- task description ----- */
    U8              debug;          /* debug level [what to display as printf's] */
    U8              priority;       /* task priority */
    U8              cp;             /* TX board (Communications Processor) to load task to */
    U8              avail[5];
    U32             exopts;         /* task execution options */
    U32             stack_size;     /* task stack size */
    S8              taskname[TXLOADER_TASKNAME_SZ];     /* name of task */
    S8              loadfile[TXLOADER_LOADFILE_SZ];     /* filename to be transferred to TX for loading */
    S8              cmdline[TXLOADER_CMDLINE_SZ];       /* ASCII command line string */

    /* ----- output fields ----- */
    S8              descrip[TXLOADER_DESCRIP_SZ];       /* place where task | error description held */
    U32             status;         /* status of operation */

    /* ----- reserved for future expansion ----- */
    U8              reserved[128];

} TXLOADER_DESC;

/*****************************************************************************
 * LIMIT DEFINITIONS
 *****************************************************************************/
#define MIN_STACK_SIZE      4096    /* minimum stack size in bytes */
#define MAX_STACK_SIZE      0x7FFFFFFF  /* maximum stack size */
#define DEFAULT_STACK_SIZE  4096    /* default stack size */
#define MIN_PRIO            0       /* minimum priority */
#define MAX_PRIO            31      /* maximum priority */
#define DEFAULT_PRIO        30      /* default priority */
#define DEFAULT_EXOPTS      0       /* default execution options */
#define MIN_CPN             1       /* minimum CP number */
#define MAX_CPN             16      /* maximum CP number */

/*****************************************************************************
 * ERROR CODES
 *****************************************************************************/

/* Indicator of CPI error */
#define TXLDERR_CPI       0x10      /* CPI library returned an error */

/* Loader Errors */
#define TXLDERR_OPEN      0xC0      /* unable to open file */
#define TXLDERR_BOOTSTRAP 0xC1      /* unable to bootstrap KERNEL */
#define TXLDERR_TRUNC     0xC2      /* truncated file */
#define TXLDERR_INVALID   0xC3      /* invalid file */
#define TXLDERR_XFER      0xC4      /* failed transfer of code block */
#define TXLDERR_CPKSTART  0xC5      /* error starting KERNEL */
#define TXLDERR_EXISTS    0xC6      /* task already exists */
#define TXLDERR_CREATE    0xC7      /* unable to create task */
#define TXLDERR_LOTVER    0xC8      /* invalid version of LOT file */
#define TXLDERR_NOMEM     0xC9      /* insufficient memory on host */
#define TXLDERR_CPMEM     0xCA      /* error getting memory on CP */
#define TXLDERR_CLOSING   0xCB      /* error while closing file */
#define TXLDERR_TASKPC    0xCC      /* error setting task program counter */
#define TXLDERR_TDMCFG    0xCD      /* error performing TDM configuration */
#define TXLDERR_BADFUNC   0xCE      /* unknown KERNEL function requested */
#define TXLDERR_DRVINIT   0xCF      /* unable to access Dual Port Ram driver */
#define TXLDERR_CHANNEL   0xD0      /* unable to obtain loader channel */
#define TXLDERR_BADTYPE   0xD1      /* unknown type of CP reported */
#define TXLDERR_TASKNAME  0xD2      /* invalid task name specified */
#define TXLDERR_TSKSTART  0xD3      /* error starting task */
#define TXLDERR_TSKDEST   0xD4      /* error destroying task */
#define TXLDERR_MAXFRAG   0xD5      /* number of fragments exceeds maximum */
#define TXLDERR_FRAGHDR   0xD6      /* bad fragment header in load file */
#define TXLDERR_DPR       0xD7      /* anomaly detected in dual-port RAM */
#define TXLDERR_DIAG      0xD8      /* diagnostic message */
#define TXLDERR_CFGVER    0xD9      /* invalid version of config file */

/*****************************************************************************
 * MISCELLANEOUS DEFINITIONS
 *****************************************************************************/
#ifdef TXXPORT
#undef   TXXPORT
#endif

/* ----- Operating System Specific Area */

#ifdef WIN32                        /* 32 bit Windows OS */

#include    <windows.h>

/*
 * The following macro conditional is to ensure proper export of CPI
 * routines.
 */
#ifdef _TX_CPLOT_SOURCE_            /* Build library. */
#       define  TXXPORT         __declspec( dllexport )
#       define  TXCPLOTFUNC     WINAPI
#else   /* Use library. */
#       define  TXXPORT
#       define  TXCPLOTFUNC     WINAPI
#endif  /* _TX_CPLOT_SOURCE_ */

#endif  /* WIN32 */


#ifdef UNIX

#define TXCPLOTFUNC
#define TXXPORT

#endif  /* UNIX */

/* Interface to the load, destroy utility */
#ifdef __cplusplus
extern          "C"
{
#endif

    TXXPORT S16 TXCPLOTFUNC Loader(LOADER_PARAMS * lp);
    TXXPORT U32 TXCPLOTFUNC TxLoader( TXLOADER_DESC *desc );

#ifdef __cplusplus
}
#endif

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack()
#endif
#ifdef _WINNT
#pragma pack()
#endif
#ifdef __HIGHC__
#pragma Pop_align_members
#endif

#endif  /* _CPLOT_H */
