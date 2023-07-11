/* Change History

   a4.26        jmd     07 mar 95       Add routines for caller to initialize and
   close cpi channel, primarily to avoid
   overhead of opening and closing channel
   for every task when loading from ICM.
 */
/*
   *-----------------------------------------------------------------------------
   * REV   DATE           WHO       $Log: cplot.h,v $
   * REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:48  cvsadmin
   * REV   DATE           WHO       Begin PR6.5
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:13  cvsadmin
   * REV   DATE           WHO       PR6.4.2 Source Propagated to Current
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:52  mmiers
   * REV   DATE           WHO       Begin PR6.2
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
   * REV   DATE           WHO       Begin PR7.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
   * REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:39  mmiers
   * REV   DATE           WHO       Start PR6.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
   * REV   DATE           WHO       Start PR5.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 3.1  2000/08/16 00:11:21  mmiers
   * REV   DATE           WHO
   * REV   DATE           WHO       Begin round 4.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 1.4  2000/06/09 22:02:23  randresol
   * REV   DATE           WHO       Adding file to current tree
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 1.1.2.1  2000/05/16 21:17:17  randresol
   * REV   DATE           WHO       Add include files for SS7 Version 3 software for TX3220
   * REV   DATE           WHO $NoKeywords: $
* 
* 14    5/26/99 6:12p Jrego
* Migrating to new Core Group source control system
* 
* 13    2/09/99 2:53p Vvirgilio
* Decrease MAX_CPN to 16. We're not THAT scaleable.
* 
* 12    2/04/99 4:25p Vvirgilio
* Increase MAX_CPN to 256.
* 
* 11    1/07/99 5:02p Vvirgilio
* Removed extra unix-specific macros.
* 
* 10    1/07/99 2:49p Vvirgilio
* Duh. Fix define of macro in unix section. Change from ...CPI... to
* ...CPLOT....
* 
* 9     1/07/99 2:41p Vvirgilio
* Add OS-specific regions for macro definitions used in prototypes.
* 
* 8     12/28/98 1:44p Jeffr
* Use the TXXPORT #defines, and also use them in the source code.
*
* 6     12/28/98 8:43a Sdalal
* changes made to create dll
*
* 5     12/19/97 5:30p Vince
* Added checksums and a more detailed way of exception reporting.
*
* 4     6/23/97 9:39a Adam
* Change DPBase to a long, so that it can take a %x scanf.  Also keeps
* the loader struct the same size with the elimination of the quiet flag.
*
* 3     5/12/97 10:49a Jeffr
* Packing of SS7 microcode option and number of 360s in QUICC32 mode
*
* 2     12/11/96 1:32p Maf
* Updated for UNIX
   *
   * 1     12/02/96 4:47p Dan
   *
   * 2     9/17/96 4:31p Jeffr
   * Repaired Log Header
   *
   * 1     9/12/96 4:49p Adam
   * Initial Recovery Checkin
   *
   * 4     6/05/96 12:20p Adam
   * Add TX5000 loading capability and Loading under Windows NT.
   *
   * 3     4/29/96 1:52p Adam
   * Add TDM Config capabilities in addition to MVIP Config, also add SS
   * header.
   *-----------------------------------------------------------------------------
 */

#ifndef _CPLOT_H_
#define _CPLOT_H_

/* Loader Control Structure */
typedef struct {
	short intno;            /* Software interrupt to CPI [0x60-0x80] */
	short cp;               /* CP number [1-8] */
   unsigned long dpbase;  /* dual port ram base */
   char *loadfile;      /* pointer to task/kernel load filename */
	char *descrip;          /* pointer to 80 byte array for description */
	short kernel;           /* kernel flag */
	short destroy;          /* destroy flag */
	short debug;            /* debug flag */
   unsigned char cpkfunc;    /* Special CPK Function flag */
   char cpkfunctyp;          /* Special CPK Function type */
   char cpkmicro;            /* CPK Microcode type <C6.50> */
   unsigned char cpkq32cnt;  /* number of processors to put into QUICC32 mode */

  /* CPK options byte */
  #define CPKOPTS_PACKED  (1<<7)  /* set = packed options in use */
  #define CPKOPTS_SS7MC   (1<<6)  /* set = SS7 microcode to be loaded to all non-QUICC32 CPUs */
  /* low-order 3 bits indicate number of processors to operate in QUICC32 mode */

	/* Task Parameters */
	char name[10];          /* name of task */
	unsigned long exopts;   /* task execution options */
	short priority;         /* task priority */
	unsigned long stack_size;       /* task stack size */
	short autostart;        /* autostart flag */
	TX_HANDLE cpi_handle;   /* handle to use talking to cpi lib */
} LOADER_PARAMS;

#define MIN_STACK_SIZE      4096        /* minimum stack size in bytes */
#define MAX_STACK_SIZE      40960       /* maximum stack size */
#define DEFAULT_STACK_SIZE  4096        /* default stack size */
#define MIN_PRIO            0     /* minimum priority */
#define MAX_PRIO            31    /* maximum priority */
#define DEFAULT_PRIO        30    /* default priority */
#define DEFAULT_EXOPTS      0     /* default execution options */
#define MIN_CPN             1     /* minimum CP number */
#define MAX_CPN             16     /* maximum CP number */

#define LDR_OUTLINE_SIZ     80    /* min size of outline bfr for ldr_get_error_str */

#ifdef TXXPORT
#undef   TXXPORT
#endif

/* ----- Operating System Specific Area */

#ifdef WIN32      /* 32 bit Windows OS */

#include    <windows.h>
/*
 * The following macro conditional is to ensure proper export of CPI
 * routines.
 */
#ifdef _TX_CPLOT_SOURCE_        /* Build library. */
#       define  TXXPORT         __declspec( dllexport )
#       define  TXCPLOTFUNC     WINAPI
#else                           /* Use library. */
#       define  TXXPORT
#       define  TXCPLOTFUNC     WINAPI
#endif /* _TX_CPLOT_SOURCE_ */

#endif /* WIN32 */


#ifdef UNIX

#define TXCPLOTFUNC
#define TXXPORT

#endif /* UNIX */

/* Interface to the load, destroy utility */
#ifdef __cplusplus
extern "C" {
#endif

TXXPORT short   TXCPLOTFUNC Loader(LOADER_PARAMS *lp);
TXXPORT void    TXCPLOTFUNC ldr_get_error_str(short booterr, char *outline);
TXXPORT short   TXCPLOTFUNC ldr_get_last_error(TX_HANDLE cpi_handle);
TXXPORT short   TXCPLOTFUNC LoadTX2CPK(LOADER_PARAMS *lp);
TXXPORT short   TXCPLOTFUNC LoadTX3CPK(LOADER_PARAMS *lp);
TXXPORT CPIPKT *TXCPLOTFUNC txld_ldr_rxbuf(void);
TXXPORT short   TXCPLOTFUNC txld_got_one(void);
TXXPORT void    TXCPLOTFUNC txld_set_got_one(short val);

#ifdef __cplusplus
}
#endif

#endif
