/***********************************************************************
*  File - NMSTYPES.H
*
*  Description -
*
*   Contains GENERIC data types used in NMS products.
*
*   In your code, if you have compiler specific functions, use
*
*        #ifdef's on    MSVCPP2, etc.
*
*   If you need to write code OS specific, but compiler independent, use
*
*                UNIX, WIN32
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
*  Copyright (c) 2002  NMS Communications.  All rights reserved.
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

/* 062299 SS Added BOOL_DECLARED condition for BOOL */
#ifndef BOOL_DECLARED
#ifdef WIN32
  #ifndef _WINDOWS_
      typedef int                  BOOL;
      #define BOOL_DECLARED
  #endif
#endif
#endif

#ifdef _WINDEF_
  #define  WORD_DECLARED
  #define DWORD_DECLARED
  #define  BYTE_DECLARED
#endif

#ifndef NULL
#define NULL    0
#endif

/* --------------- MICROSOFT COMPILERS ----------------------------------- */

#if defined (_MSC_VER)
  #if (_MSC_VER >= 900)

/* ---------------  Microsoft VISUAL C++ ---------------------------------- */
  #define    MSVCPP2                  1

  #ifndef    WIN32
    #define  WIN32
  #endif

  #define    NMSAPI          __stdcall
  #define    NMSSTDCALL      __stdcall
  #define    NMSSTDCALLPTR   __stdcall *

  #ifndef UINT16
    typedef  unsigned short       UINT16;
  #endif
  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
    typedef  unsigned int        UINT32;
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

  #ifndef __cplusplus
    typedef  int   bool;
    #define  true  1
    #define  false 0
  #endif

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
    typedef  unsigned int        UINT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short      WORD;
    typedef  unsigned short      UINT16;
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

/* --------------- UNIXWARE and SOLARIS   UNIX COMPILERS  ------------------------ */

#elif defined (UNIX_SVR4) || defined (UNIXWARE) || defined (SOLARIS)
                                                  /* UNIX_SVR4 preferred */

  #define   UNIX_SVR4               1            /* if UNIXWARE def'd   */
  #ifndef UNIX
     #define    UNIX                    1
  #endif

  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
    typedef  unsigned int        UINT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short      WORD;
    typedef  unsigned short      UINT16;
  #endif
  #ifndef     DWORD_DECLARED
    #ifdef _Solaris64_
    typedef unsigned int         DWORD;
    #else
    typedef  unsigned long       DWORD;
    #endif
  #endif
  #ifndef     BYTE_DECLARED
  #ifdef BYTE
  #undef BYTE
  #endif
  typedef  unsigned char       BYTE;
  #endif
  /* 100699 VC added support for LONG_INTEGER */
  #ifndef LARGE_INT_DECLARED
    typedef union _LARGE_INTEGER {
        struct {
            DWORD LowPart;
            DWORD HighPart;
        } _ss ;
        long long QuadPart;
    } LARGE_INTEGER;
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


/* --------------- LINUX GNU (GCC) COMPILERS  ---------------------------------- */

#elif defined (LINUX)

  #ifndef UNIX
     #define    UNIX                    1
  #endif

  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
    typedef  unsigned int        UINT32;
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short      WORD;
    typedef  unsigned short      UINT16;
  #endif
  #ifndef     DWORD_DECLARED
    #ifdef __x86_64__
      typedef unsigned int       DWORD;
    #else
      typedef  unsigned long     DWORD;
    #endif
  #endif
  #ifndef     BYTE_DECLARED
    typedef  unsigned char       BYTE;
  #endif
  /* 100699 VC added support for LONG_INTEGER */
  #ifndef LARGE_INT_DECLARED
    typedef union _LARGE_INTEGER {
        struct {
            DWORD LowPart;
            DWORD HighPart;
        } _ss ;
        long long QuadPart;
    } LARGE_INTEGER;
  #endif

  /* 020199 BC Added support for BOOL */
  #ifndef BOOL_DECLARED
    typedef int                  BOOL;
    #define BOOL_DECLARED
  #endif

  typedef    int               NMSRET;

  typedef    int            DEV_HANDLE;
  #define    NULL_DEVHDL            -1

  typedef    DEV_HANDLE     MUX_HANDLE;
  #define    NULL_MUXHDL    NULL_DEVHDL

  typedef unsigned char      uchar_t;
  typedef unsigned long      ulong_t;
  typedef unsigned int       uint_t;
  typedef unsigned short     ushort_t;

  #if !defined(NMSTYPE_UNCHAR_DEFINED)
  typedef unsigned char      unchar;
  #endif

/* --------------- HIGH C COMPILERS ------------------------------- */
/* Also UltraC. (Added for Services customer.   -gs 2-Aug-00)       */
/* Also GCC when used to compile embedded software. -kday 17-Feb-04 */

#elif defined (__HIGHC__) || defined (_UCC) || defined (__ARMCPP__) || defined (EMBEDDED_GCC) || defined (_METAWARE)

  #define    NMSAPI
  #define    NMSSTDCALL
  #define    NMSSTDCALLPTR             *

  #ifndef     INT16_DECLARED
    typedef  short int           INT16;
  #endif
  #ifndef     INT32_DECLARED
    typedef  int                 INT32;
        /* under GCC for ppc, it treats unsigned int and unsigned long differently */
    #if defined (EMBEDDED_GCC) || defined (_METAWARE)
        typedef  unsigned int        UINT32;
    #else
        typedef  unsigned long        UINT32;
    #endif
  #endif
  #ifndef     WORD_DECLARED
    typedef  unsigned short      WORD;
    typedef  unsigned short      UINT16;
  #endif

  #ifndef     DWORD_DECLARED
    /* under GCC for ppc, it treats unsigned int and unsigned long differently */
    #if defined (EMBEDDED_GCC) || defined (_METAWARE)
        typedef  unsigned int        DWORD;
    #else
        typedef  unsigned long        DWORD;
    #endif
    #define  DWORD_DECLARED
  #endif

  #ifndef     BYTE_DECLARED
    typedef  unsigned char       BYTE;
    typedef  unsigned char       UINT8;
  #endif
  typedef    int                MUX_HANDLE;
  typedef    int                NMSRET;


  #ifndef BOOL_DECLARED
    typedef int                  BOOL;
    #define BOOL_DECLARED
  #endif

  #if defined(__HIGHC__) || !defined(__cplusplus)
    // Remove the following when Metaware complies with current C++ standards.
    // -- Actually, don't remove it, since we use it in C (not exactly standard either!) 
    typedef  int   bool;
    #define  true  1
    #define  false 0
  #endif

  #if defined(EMBEDDED_GCC) || defined(__HIGHC__)
    #ifndef     QWORD_DECLARED
      typedef  unsigned long long  QWORD;
    #endif
  #endif
     
    
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
  typedef   long            MUX_HANDLE;

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

typedef unsigned long        UINTPTR;

#endif          /* NMSTYPES_INCLUDED */

