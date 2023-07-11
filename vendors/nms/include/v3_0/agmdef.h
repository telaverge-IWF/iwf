/*****************************************************************************
*                                  AGMDEF.H
*
*  This is the include file for the AG Downloader/Monitor library (AGMLIB) API.
*
* Copyright (c)1996-98 Natural MicroSystems Corporation.  All rights reserved.
*****************************************************************************/

#ifndef AGMDEF_INCLUDED
#define AGMDEF_INCLUDED

#ifdef __cplusplus
  extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
  #include "nmstypes.h"
#endif

#if defined (WIN32) || defined (OS2)
  #define BOOL_DECLARED
#endif

#if !defined (BOOL) && !defined(BOOL_DECLARED)
 #if 0
  typedef unsigned short BOOL;
  #define BOOL_DECLARED
 #endif
  #define BOOL unsigned short
#endif

#ifdef WIN32
  #include <windows.h>
#endif

#define AGM_MAX_BOARDS     16
#define AGM_MAX_FILES      64     /* increase for AG2 */
#define AGM_MAX_FILESPEC  120

#define AGM_CALLBACK_ERROR           1
#define AGM_CALLBACK_WARNING         2
#define AGM_CALLBACK_INFORMATIONAL   3

#define AGMERR_FAILURE       1 /* Function failed; details via errorhandler. */
#define AGMERR_MALLOC_FAILED 2 /* An attempt to allocate memory failed.      */
#define AGMERR_OPEN_FAILED   3 /* An attempt to open a file failed.          */
#define AGMERR_BAD_ARG       4 /* The provided AGM handle was invalid.       */
#define AGMERR_NOMESSAGE     5 /* There was no valid AG message available.   */
#define AGMERR_SIGNALLED     6
#define AGMERR_QUEUE_EMPTY   7
#define AGMERR_TIMEOUT       8
#define AGMERR_DOWNLOAD_DONE 9

/* Modes of operation, to be bitwise ORed into a bitmask.
 * (Other modes may be added later.)
 */
#define AGM_MODE_PARALLEL       0x00001 /* Support parallel downloads       */
#ifdef UNIX
  #define AGM_MODE_DONT_UPDATE_DEV_LINKS 0x00002 /* Don't touch /dev symlinks */
#endif

typedef DWORD AGMHD;

/* A fake AGMHD for use with agmSignalMuxHandle() */
#define AGM_NULL_AGMHD  ((AGMHD)-1)


/* Optional parameters for agmOpen()
 * For each field, 0 means to use default. */
typedef struct {
    DWORD size;                 /* the size of the struct being provided */
    DWORD mode;                 /* AGM mode bits, e.g. AGM_PARALLEL_MODE */
    DWORD maxwait;              /* max time (secs) for download to complete */
    DWORD loadsize;             /* block size (bytes) for downloads */
    DWORD diagmask;             /* diagnostics level or bitmask */
    DWORD traceflags;           /* equivalent to agtrace (?) */
    DWORD testlevel;            /* diagnostics level */
    DWORD posttraceflags;       /* set trace flags after booting */
    DWORD reserved;
} AGM_OPTIONS;

/* The contents of an AG message */
typedef struct {
    WORD  message ;
    WORD  channel ;
    WORD  object ;
    BYTE  stream ;
    BYTE  instance ;
    DWORD time ;
    WORD  reserved ;
    BYTE  bufcnt ;
    BYTE  parmcnt ;

    WORD  parms[16];
} AGM_AGMSG;

/* Error handling callback */
typedef DWORD (NMSSTDCALLPTR AGM_ERROR_HANDLER) (
    AGMHD agmhd,                /* AGM handle                                 */
    int   boardnum,             /* board number (-1 if N/A)                   */
    DWORD severity,             /* AGM_CALLBACK_{ERROR,WARNING,INFORMATIONAL} */
    char *errtxt );             /* error text                                 */

typedef struct {

    struct AGM_BOOTSTAT {
        WORD code;              /* Status code.                               */
        WORD count;             /* Number of data words.                      */
        WORD data[32];          /* Error-specific data.                       */
    } bootstat;

    struct AGM_EEPROM_DATA {
        WORD  boardtype;        /* Physical board type.                       */
        WORD  boardrev;         /* Hardware assembly level.                   */
        long  serial;           /* Serial number unique to each board.        */
        WORD  date;             /* Date of last full test.                    */
        WORD  min_sw_rev;       /* Minimum software revision level.           */
        WORD  dsps;             /* Total number of DSPs on mother board.      */
        WORD  cmemsize;         /* CMEM size in kilobytes.                    */
        WORD  dramsize;         /* DRAM size in kilobytes.                    */
        WORD  cpuspeed;         /* Co-processor speed in MHz.                 */
        WORD  dspspeed;         /* DSP processor speed in MHz.                */
        WORD  mvipproc_speed;   /* MVIP processor speed in MHz.               */
        WORD  atetest;          /* Non-zero if passed ATE test.               */
        WORD  busclkdiv;        /* Bus speed is 2 * cpuspeed / busclkdiv.     */
        WORD  sramsize;         /* SRAM size in kilobytes.                    */
        WORD  subtype;          /* 1=AG24 2=AG24+ 3=AG30 4=AG8 5=AGT1 6=AGE1. */
        WORD  confbrdg;         /* Number of conference bridges.              */
        WORD  board_specific;   /* Board specific information.                */
        WORD  bus_type;         /* 0xffff - MVIP-90 bus; 0 - H.100 bus        */
        WORD  spare [12];       /* Reserved.                                  */
        WORD  checksum;         /* EEPROM checksum.                           */
    } eeprom_data;

} AGM_BOOT_INFO;

typedef struct {

    int  count;

    struct AGM_FILE_STATS {
        BOOL  found;
        char  spec[AGM_MAX_FILESPEC];
        DWORD size;
        char  date[50];
    } file[AGM_MAX_FILES];

} AGM_FILE_INFO;

/*****************************************************************************
* Function - agmGetVersion
*
* Description -
*
* Returns -
* pointers to strings representing the library version and the build date.
*****************************************************************************/
DWORD NMSAPI agmGetVersion (
    const char **version,
    const char **builddate );

/*****************************************************************************
* Function - agmOpen
*
* Description -

* 1. Opens the specified report file for informational messages etc that
* the library generates.
*
* 2. Creates a context for the subsequent AGM Library calls and then
* opens and reads the specified configuration file to initialize the
* context.  The context structure is allocated within the library; only
* a handle (agmhd) is exposed.
*
* Sets all configured board states to INITIALIZED.
*
* The options argument may be used to specify various option parameters,
* listed in the definition of AGM_OPTIONS.  The size field must contain
* the size of the struct being passed in; for each other field, a zero
* indicates that the default should be used.
* The lowest bit of the mode field enables support for parallel downloading
* of boards; this causes MVIP clock slaves to wait for MVIP clock masters
* when booting; in sequential mode, this checking is disabled.
*
* Returns - SUCCESS/FAILURE.
* Also passes back a handle for the context, agmhd.
*****************************************************************************/
DWORD NMSAPI agmOpen (
    char *config_file,
    char *report_file,
    AGM_OPTIONS *options,
    AGM_ERROR_HANDLER errorhandler,
    AGMHD *agmhd );

/*****************************************************************************
* Function - agmLoadDriver
*
* Description -
*
* Initializes and starts the AG device drivers, using information in the
* specified context.
*
* Sets all configured board states to LOADED.
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmLoadDriver (
    AGMHD agmhd );

/*****************************************************************************
* Function - agmOpenDriver
*
* Description -
*
* Opens the AG device.
*
* Boards must not be in INITIALIZED state.
* Sets all configured board states to OPENED.
*
* Returns - SUCCESS/FAILURE.
* Also passes back major and minor version numbers for the device driver
* and a muxhandle that can be used to wait or test for the availability of
* AG messages from the driver.
*****************************************************************************/
DWORD NMSAPI agmOpenDriver (
    AGMHD agmhd,
    MUX_HANDLE *muxhd,
    unsigned *majorrev,
    unsigned *minorrev );

/*****************************************************************************
* Function - agmCheckConfig
*
* Description -
*
* Checks the configuration information against the hardware present on the
* system. Probes the hardware, and adds information to the configuration in
* the context if necessary.
*
* Also reads into all required run files, dsp files and tcp files into
* the configuration, returning information about them in the supplied
* FILE_INFO struct.
*
* Requires affected boards to be in OPENED state.
* For each board that passes the config check, sets state to CHECKED.
*
* Returns - SUCCESS/FAILURE.
* Also passes back a DWORD boardmask such that (boardmask & (1<<k))
* indicates whether board k checked out successfully.
*****************************************************************************/
DWORD NMSAPI agmCheckConfig(
    AGMHD agmhd,
    DWORD *boardmask,
    AGM_FILE_INFO *fileinfo );

/*****************************************************************************
* Function - agmBootBoard
*
* Description -
*
* Resets, bootstraps, and runs diagnostics on a board, using information
* from the specified context.
*
* Requires board to be in CHECKED state; sets it to BOOTED.
*
* Returns - SUCCESS/FAILURE.  Also passes back a struct with the board's
* boot status and related information.
*****************************************************************************/
DWORD NMSAPI agmBootBoard (
    AGMHD agmhd,
    DWORD board,
    AGM_BOOT_INFO *bootinfo );

/*****************************************************************************
* Function - agmDownloadBoard
*
* Description -
*
* Loads the run file, DSP overlays and TCP files that the specified
* context indicates are part of that board's configuration.
*
* Requires board to be in BOOTED state; sets it to LIVE.
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmDownloadBoard (
    AGMHD agmhd,
    DWORD board );

/*****************************************************************************
* Function - agmGetAGMessage
*
* Description -
*
* Receives the next board event, provided one is pending.
* agmWaitEvent should have been used to wait for an event to arrive.
*
* Requires board to be in LIVE state.
*
* Returns - SUCCESS/FAILURE/AGM_SIGNALLED/AGM_QUEUE_EMPTY.
* (AGM_SIGNALLED indicates that the mux handle was signalled using
* agmSignalMuxHandle)
*****************************************************************************/
DWORD NMSAPI agmGetAGMessage (
    AGMHD      agmhd,
    AGM_AGMSG *msg );

/*****************************************************************************
* Function - agmFormatAGMessage
*
* Description -
*
* Formats an AG message received from the board into a character string for
* printing.
*
* Requires board to be in LIVE state.
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmFormatAGMessage (
    AGM_AGMSG *msg,
    char      *buffer,
    int        buffersize );

/*****************************************************************************
* Function - agmClose
*
* Description -
*
* Frees the context information associated with the handle passed in
* and invalidates the handle.
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmClose (
    AGMHD agmhd );

/*****************************************************************************
* Function - agmSignalMuxHandle
*
* Description -
*
* Causes the driver to send up a special message that will signal a mux
* handle returned by agmOpenDriver() (even in another process) and cause
* agmGetAGMessage() to return AGM_SIGNALLED when it returns that message.
* The 'code' argument will show up as parms[0] of that message, the
* board argument as parms[1].
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmSignalMuxHandle ( AGMHD agmhd, WORD code, WORD board );

#ifdef UNIX
/*****************************************************************************
* Function - agmHoldStreams
*
* Description -
*
* Causes the library to fork a detached process that holds the unix
* streams links between the agsw, agmx and aghw drivers.
* This process is killed by agmKillStreams and on every call to
* agmOpenDriver except when open for monitor only.
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmHoldStreams ( AGMHD agmhd );

/*****************************************************************************
* Function - agmKillStreams
*
* Description -
*
* Kills the detached process created by agmHoldStreams.
*
* Returns - SUCCESS/FAILURE.
*****************************************************************************/
DWORD NMSAPI agmKillStreams ( AGMHD agmhd );
#endif

#ifdef __cplusplus
  }
#endif

#endif  /* ifndef AGMDEF_INCLUDED */
