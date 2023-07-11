/* Change History

   a4.26        jmd     07 mar 95       Add routines for caller to initialize and
   close cpi channel, primarily to avoid
   overhead of opening and closing channel
   for every task when loading from ICM.
 */
/*
   *-----------------------------------------------------------------------------
   * REV   DATE           WHO       $Log: cplot.h,v $
   * REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:46  cvsadmin
   * REV   DATE           WHO       Begin PR6.5
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:07  cvsadmin
   * REV   DATE           WHO       PR6.4.2 Source Propagated to Current
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:51  mmiers
   * REV   DATE           WHO       Begin PR6.2
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
   * REV   DATE           WHO       Begin PR7.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
   * REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:35  mmiers
   * REV   DATE           WHO       Start PR6.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
   * REV   DATE           WHO       Start PR5.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 3.1  2000/08/16 00:10:59  mmiers
   * REV   DATE           WHO
   * REV   DATE           WHO       Begin round 4.
   * REV   DATE           WHO
   * REV   DATE           WHO       Revision 1.1  2000/06/21 19:19:34  hxing
   * REV   DATE           WHO       Add NMS vendor lib for version 2.01
   * REV   DATE           WHO $NoKeywords: $
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

/* Loader Control Structure */
typedef struct {
	short intno;		/* Software interrupt to CPI [0x60-0x80] */
	short cp;		/* CP number [1-8] */
   unsigned long dpbase;  /* dual port ram base */
   char *loadfile;      /* pointer to task/kernel load filename */
	char *descrip;		/* pointer to 80 byte array for description */
	short kernel;		/* kernel flag */
	short destroy;		/* destroy flag */
	short debug;		/* debug flag */
   unsigned char cpkfunc;    /* Special CPK Function flag */
   char cpkfunctyp;          /* Special CPK Function type */
   char cpkmicro;            /* CPK Microcode type <C6.50> */
   unsigned char cpkq32cnt;  /* number of processors to put into QUICC32 mode */

  /* CPK options byte */
  #define CPKOPTS_PACKED  (1<<7)  /* set = packed options in use */
  #define CPKOPTS_SS7MC   (1<<6)  /* set = SS7 microcode to be loaded to all non-QUICC32 CPUs */
  /* low-order 3 bits indicate number of processors to operate in QUICC32 mode */

	/* Task Parameters */
	char name[10];		/* name of task */
	unsigned long exopts;	/* task execution options */
	short priority;		/* task priority */
	unsigned long stack_size;	/* task stack size */
	short autostart;	/* autostart flag */
	TX_HANDLE cpi_handle;	/* handle to use talking to cpi lib */
} LOADER_PARAMS;

#define MIN_STACK_SIZE      4096	/* minimum stack size in bytes */
#define MAX_STACK_SIZE      40960	/* maximum stack size */
#define DEFAULT_STACK_SIZE  4096	/* default stack size */
#define MIN_PRIO            0     /* minimum priority */
#define MAX_PRIO            31    /* maximum priority */
#define DEFAULT_PRIO        30    /* default priority */
#define DEFAULT_EXOPTS      0     /* default execution options */
#define MIN_CPN             1     /* minimum CP number */
#define MAX_CPN             8     /* maximum CP number */

#define LDR_OUTLINE_SIZ     80    /* min size of outline bfr for ldr_get_error_str */

/* Interface to the load, destroy utility */
#ifdef __cplusplus
extern "C" {
#endif

	short Loader(LOADER_PARAMS * lp);
  void ldr_get_error_str( short booterr, char *outline );
  short ldr_get_last_error( TX_HANDLE cpi_handle );

#ifdef __cplusplus
}

#endif
