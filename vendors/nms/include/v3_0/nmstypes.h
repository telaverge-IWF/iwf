/***********************************************************************
*  File - NMSTYPES.H
*
*  Description -
*
*   Contains GENERIC data types used in NMS products.
*
*   In your code, if you have compiler specific functions, use
*
*        #ifdef's on    MSC6, IBMC, SCO, MSVCPP2, etc.
*
*   If you need to write code OS specific, but compiler independent, use
*
*                OS2, UNIX, WIN32 or NETWARE
*
*   BYTE, INT16, INT32, WORD and DWORD include SPECIFIC NUMBER OF BITS.
*   NMSRET, DEV_HANDLE are COMPILER DEPENDENT.
*
*   For linkage support:
*     NMSAPI         linkage convention for NMS DLLs
*     NMSSTDCALL     linkage convention for NMS static call (e.g. callback)
*     NMSSTDCALLPTR  convenient modifier to hide '* XX' vs 'XX *'
*
*                      **** IMPORTANT NOTE ****
*
*   If you run into a problem with duplicate WORD, DWORD, BYTE, etc., typedefs,
*   include in your code:
*
*        #define  WORD_DECLARED
*        #define DWORD_DECLARED
*        #define  BYTE_DECLARED
*        #define INT32_DECLARED
*        #define INT16_DECLARED
*
*   respectively just before including any NMS headers.
*
*
*   Copyright (c) 1994-98  Natural MicroSystems Corp.  All rights reserved.
***********************************************************************/

#ifndef NMSTYPES_INCLUDED
#define NMSTYPES_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TRUE
  #define TRUE 1
#endif
#ifndef FALSE
  #define FALSE 0
#endif

#ifdef WIN32
  #ifndef _WINDOWS_
  typedef int                  BOOL;
  #endif
#endif

#ifdef OS2DEF_INCLUDED
  #define BYTE_DECLARED
#endif

#ifdef _WINDEF_
  #define  WORD_DECLARED
  #define DWORD_DECLARED
  #define  BYTE_DECLARED
#endif

/* --------------- OS/2 IBM 32-bit COMPILERS ---------------------------- */

#if (defined (__IBMC__) || defined (__IBMCPP__)) && defined(__32BIT__)
                                               /* IBM C/C++ 32-bits */

  #define    IBMC                    1
  #define    OS2                     1
  #define    NMSAPI            _System
  #define    NMSSTDCALL        _System
  #define    NMSSTDCALLPTR   * _System

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef    int               NMSRET;

  typedef    unsigned long  DEV_HANDLE;
  #define    NULL_DEVHDL             0

  typedef    unsigned long  MUX_HANDLE;   /* OS/2 type MUX_HANDLE (== HEV) */
  #define    NULL_MUXHDL             0

/*-------------- BORLAND C/C++ OS/2 32-bit COMPILER ----------------------- */

#elif defined (__BORLANDC__)  && !defined(__WIN32__)

  #define    OS2                     1
  #define    NMSAPI           _syscall
  #define    NMSSTDCALL       _syscall
  #define    NMSSTDCALLPTR    _syscall *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef    int               NMSRET;

  typedef    unsigned long  DEV_HANDLE;
  #define    NULL_DEVHDL             0

  typedef    unsigned long  MUX_HANDLE;   /* OS/2 type MUX_HANDLE (== HEV) */
  #define    NULL_MUXHDL             0

/* --------------- MICROSOFT COMPILERS ----------------------------------- */

#elif defined (_MSC_VER)

  #if (_MSC_VER == 600)

/* --------------- Microsoft C 6.0A for OS/2, 16-bits -------------------- */
  #define    MSC6   1

  #define    OS2                     1
  #define    NMSAPI                     /*xx- _pascal-xx*/
  #define    NMSSTDCALL     far _cdecl
  #define    NMSSTDCALLPTR  far _cdecl *

  #ifndef     INT16_DECLARED
    typedef  int                 INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  long                INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef    int               NMSRET;
  typedef    int            DEV_HANDLE;
  #define    NULL_DEVHDL             0

  typedef    DEV_HANDLE     MUX_HANDLE;
  #define    NULL_MUXHDL   NULL_DEVHDL

  #elif (_MSC_VER >= 900)

/* ---------------  Microsoft VISUAL C++ ---------------------------------- */
  #define    MSVCPP2                  1

  #ifndef    WIN32
    #define  WIN32
  #endif

  #define    NMSAPI          __stdcall
  #define    NMSSTDCALL      __stdcall
  #define    NMSSTDCALLPTR   __stdcall *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef int                  NMSRET;

  typedef void             *DEV_HANDLE;      /* == Win32 type HANDLE */
  #define    NULL_DEVHDL    0xFFFFFFFF

  typedef void             *MUX_HANDLE;      /* == Win32 type HEVENT */
  #define    NULL_MUXHDL          NULL

  #else
    #error Unknown Microsoft compiler type
  #endif

/* --------------- SCO 32-bit UNIX COMPILERS ----------------------------- */

#elif defined (SCO)                  /* Might need to add compiler version */

  #ifndef UNIX
     #define    UNIX                    1
  #endif
  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR            *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef    int               NMSRET;
  typedef    int            DEV_HANDLE;
  #define    NULL_DEVHDL            -1

  typedef    DEV_HANDLE     MUX_HANDLE;
  #define    NULL_MUXHDL   NULL_DEVHDL

/* --------------- UNIXWARE UNIX COMPILERS ------------------------------- */

#elif defined (UNIX_SVR4) || defined (UNIXWARE) || defined (SOLARIS)
                                                  /* UNIX_SVR4 preferred */

  #define    UNIX_SVR4               1            /* if UNIXWARE def'd   */
  #ifndef UNIX
     #define    UNIX                    1
  #endif
  /* #define    UNIX                    1*/
  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  /* 020199 BC Added support for BOOL */
  #ifndef BOOL_DECLARED
    typedef int                  BOOL;
    #define BOOL_DECLARED
  #endif

  typedef    int               NMSRET;
  typedef    int            DEV_HANDLE;
  #define    NULL_DEVHDL            -1

  typedef    DEV_HANDLE     MUX_HANDLE;  /* poll() uses fd */
  #define    NULL_MUXHDL   NULL_DEVHDL

/* --------------- HIGH C COMPILERS ------------------------------- */

#elif defined (__HIGHC__)

  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif
  typedef    int                MUX_HANDLE;
  typedef    int                NMSRET;

  // Remove the following when Metaware complies with current C++ standards.
  typedef  int   bool;
  #define  true  1
  #define  false 0


/* --------------- NETWARE           ------------------------------- */

#elif defined (__NETWARE_386__)

  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef    int               NMSRET;
  typedef    int            DEV_HANDLE;
  typedef   long            MUX_HANDLE;  /* Netware manifestation of device  */

/*-------------- Borland C++ 32 bit compiler for Windows ------------------ */

/* __BORLANDC__ and __WIN32__ are produced by compiler */

#elif defined (__BORLANDC__) && defined (__WIN32__)

  #define    NMSAPI         PASCAL _export
  #define    NMSSTDCALL     PASCAL _export
  #define    NMSSTDCALLPTR   PASCAL _export*

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif

  typedef    int               NMSRET;

  typedef    unsigned long  DEV_HANDLE;
  #define    NULL_DEVHDL             0

  typedef    unsigned long  MUX_HANDLE;
  #define    NULL_MUXHDL             0
  #include <windows.h>

/* --------------- QNX ----------------------------------------------------- */
#elif defined (__QNX__)

  #define    NMSAPI
  /*
  ** This is normally defined in /usr/include/sys/types.h
  ** however QNX does not do it. therefore define it here.
  */

  typedef    unsigned short     ushort;
  typedef    unsigned char      unchar;
  typedef    unsigned long      ulong;

  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short       WORD;
  #endif
  #ifndef     DWORD_DECLARED
    typedef  unsigned long       DWORD;
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char        BYTE;
  #endif
  #ifndef BOOL_DECLARED
    typedef unsigned short  BOOL ;
    #define BOOL_DECLARED
  #endif
  typedef    int               NMSRET;
  typedef    int            DEV_HANDLE;
  typedef   long            MUX_HANDLE;  /* Netware manifestation of device  */

  #define    NULL_DEVHDL            -1
  #define    NULL_MUXHDL   NULL_DEVHDL

#else
  #error Unknown Compiler Type
#endif

/* --------------- COMPILER INDEPEDENT TYPEDEFs -------------------------- */

#ifndef SUCCESS
  #define SUCCESS                            0
#endif

#define  REPORT_ERRORS  ((ERROR_HANDLER) (1L))
#define  EXITON_ERRORS  ((ERROR_HANDLER) (2L))

typedef int (NMSSTDCALLPTR ERROR_HANDLER)  ( NMSRET error, char *errtxt,
                                                  char *info );
typedef void (NMSSTDCALLPTR TRACE_HANDLER) ( unsigned type, char *info );

/*
     Event Multiplexing structures
*/
typedef union
    {
    DWORD type;         /* The tag showing what the handle is working on */
    struct
        {
        WORD port;      /* The port for this handle (0 if many ports/handle) */
        WORD mgr;       /* Manager for this handle (0 for dispatcher handles)*/
        } id;
    } MUX_ID;

typedef struct
    {
    MUX_HANDLE muxhd;   /* The OS specific handle to use in waiting */
    MUX_ID muxid;       /* The ID showing what this handle is for */
    } MUX_RECORD;

#ifdef __cplusplus
}
#endif

#endif          /* NMSTYPES_INCLUDED */
