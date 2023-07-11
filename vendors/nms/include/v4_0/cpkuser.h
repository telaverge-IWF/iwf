/*****************************************************************************
 *
 * cpkuser.h - USER ACCESSABLE Kernel user interface definition file
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

#ifndef _CPKUSER_H
#define _CPKUSER_H

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

#ifdef _XCODE_
#define TX_LEGACY_68000     /* building for 68K so building for legacy TX board */
#endif /* _XCODE_ */

#ifndef TX_LEGACY_68000

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*
 * The include file 'cpkuser.h' is being phased out for the SS7 4.0 release.
 * The definitions once provided by cpkuser.h are now provided by the
 * following set of files.  For LEGACY SUPPORT, any include of this file
 * when not building for 68000-based target boards will be converted to
 * the set of includes listed below.  Future TX board-based code should
 * directly include the specific files needed.
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include <costask.h>
#include <cosnobj.h>
#include <coslog.h>
#include <cosinfo.h>

#else /* TX_LEGACY_68000 */

#include <txnuser.h>

/*
 *  68000 Condition codes
 */
#define CC_N		8               /* Condition Code Mask: Negative */
#define CC_Z		4               /* Condition Code Mask: Zero */
#define CC_V		2               /* Condition Code Mask: Overflow */
#define CC_C		1               /* Condition Code Mask: Carry */

/*
 * System Maximums
 */
#define MAXFNA		90              /* Maximum full file name size */
#define MAXSFN    16                /* Maximum simple file name size */
#define MAXCOM		256             /* Maximum command line size */
#define MAXVOLN   8                 /* Maximum logical volume name size */
#define MAXCPUID  7                 /* Maximum cpu identification index */
#define MAXSEG    4                 /* Maximum number of segments per load request */
#define MAXREFS   16                /* Maximum library references per module */
#define SECSIZE 	256             /* Bytes per disk sector */
#define MAXDESC   80                /* Maximum size of a FS file description */
#define MAXFPB		256             /* Maximum size of a FS handler param block */
#define MAXCODCOMM	80              /* Maximum size of the IDENT comment field */
#define MBDATESZ  6                 /* Number of bytes of build timestamp in ident */
#define MAXBRKPT  64                /* Maximum allowed breakpoints */

/*
 * Message Priority Queues
 */
#define CPKPRIO_MIN       0         /* Minimum priority [RESERVE FOR FUTURE USE] */
#define CPKPRIO_BKGROUND  1         /* Background operations */
#define CPKPRIO_LOW       2         /* Low priority messages */
#define CPKPRIO_STANDARD  3         /* Standard operations */
#define CPKPRIO_RAISED    4         /* Priority raised above standard */
#define CPKPRIO_HIGH      5         /* High priority messages [TIMER ticks] */
#define CPKPRIO_URGENT    6         /* Urgent messages [MEMORY limit notifs] */
#define CPKPRIO_MAX       7         /* Maximum priority */
#define CPKPRIO_COUNT     8         /* count of priority queues available */
#define CPKPRIO_MASK      0x07      /* mask to apply to force value to valid priority range */

/*
 *  TRAP packet options global to all services.
 */
#define GOP_AOE         (1<<0)      /* Global option  Abort On Error */
#define GOP_UNIQ        (1<<1)      /* Global option  Make pktname unique */
#define GOP_NMG         (1<<3)      /* Global option  Network management use bit */

#define GOP_P_BKGROUND  (CPKPRIO_BKGROUND<<4)   /* Background operations */
#define GOP_P_LOW       (CPKPRIO_LOW     <<4)   /* Low priority messages */
#define GOP_P_STANDARD  (CPKPRIO_STANDARD<<4)   /* Standard operations */
#define GOP_P_RAISED    (CPKPRIO_RAISED  <<4)   /* Priority raised above standard */
#define GOP_P_HIGH      (CPKPRIO_HIGH    <<4)   /* High priority messages [TIMER ticks] */
#define GOP_P_URGENT    (CPKPRIO_URGENT  <<4)   /* Urgent messages */
#define GOP_P_MAX       (CPKPRIO_MAX     <<4)   /* Maximum priority */


/*
 *  Completion mode selection indices
 */
#define CSLWAIT_	0               /* Wait */
#define CSLCOND_	1               /* Conditional */
#define CSLQUED_	2               /* Queued */

/*
 *  COMMS TRAP #4 function codes
 */
#define CTFARAQ_	1               /* Arm CP activity queue, AQ number in D1 */

/*
 * Special section identifiers
 */
#define DSECT_		11              /* "Dummy" section */

/*
 * Values use to identify fields in FS parameter buffer
 */
#define FPPEND_ 	0               /* End of parameter list */
#define FPPUID_ 	1               /* User ID field definition */
#define FPPNID_ 	2               /* Node ID field definition */
#define FPPCRTS_	3               /* Creation timestamp definition */
#define FPPCLTS_	4               /* Last close timestamp definition */
#define FPPWRTS_	5               /* Last written timestamp definition */
#define FPPBKTS_	6               /* Last backed up timestamp definition */
#define FPPRECT_	7               /* Record type definition */
#define FPPRECS_	8               /* Record size definition */
#define FPPRECC_	9               /* Record count definition */
#define FPPDESC_	10              /* File description definition */
#define FPPFLAG_	11              /* Flags and general properties */
#define FPPDTYP_	12              /* Data type */
#define FPPLCNT_	13              /* Link count */
#define FPPEOF_ 	14              /* EOF position */
#define FPPALOC_	15              /* Space allocated */
#define FPPTABS_	16              /* Text file tab spacing */
#define FPPFSE_ 	17              /* Text file editor private properties */
#define MAXFPP		17              /* Highest legal parameter type */

/*
 *	Predefined record types
 */
#define RECUNT_ 	0               /* Untyped records */
#define RECFIX_ 	1               /* Fixed size records */
#define RECVAR_ 	2               /* Variable size records <length><data> */
#define RECSTR_ 	3               /* Stream (single byte) data */

/*
 * TASK/DEBUG service indicies
 */
#define DBMON_		0               /* Register as debugger task */
#define DBUMON_ 	1               /* Un register as debugger task */
#define DBSETREG_	2               /* Set tasks registers */
#define DBSHOREG_	3               /* Show tasks registers */
#define DBSETBR_	4               /* Set breakpoints */
#define DBSHOBR_	5               /* Show breakpoints */
#define DBSTEP_ 	6               /* Set trace bit */
#define DBREAD_ 	7               /* Read task memory */
#define DBWRITE_	8               /* Write task memory */
#define DBGO_		9               /* Continue from breakpoint or trace */

/*
 *  Register Dump Block for TASK/DEBUG
 */

struct __reg
{
    U32   regmask;
    union
    {
        struct
        {
            U32   regd[8];
            U32   rega[7];
        }
        _r00;
        struct
        {
            U32   regd0;
            U32   regd1;
            U32   regd2;
            U32   regd3;
            U32   regd4;
            U32   regd5;
            U32   regd6;
            U32   regd7;
            U32   rega0;
            U32   rega1;
            U32   rega2;
            U32   rega3;
            U32   rega4;
            U32   rega5;
            U32   rega6;
            U32   regssp;
            U32   regusp;
            U32   regpc;
            U16  regsr;
        }
        _r01;
    }
    _r0u;
};

#define REGBLKSIZE sizeof(struct __reg)

/*
 * Registers defined  (regmask)
 */
#define RDF_D0		(1<<0)
#define RDF_D1		(1<<1)
#define RDF_D2		(1<<2)
#define RDF_D3		(1<<3)
#define RDF_D4		(1<<4)
#define RDF_D5		(1<<5)
#define RDF_D6		(1<<6)
#define RDF_D7		(1<<7)
#define RDF_A0		(1<<8)
#define RDF_A1		(1<<9)
#define RDF_A2		(1<<10)
#define RDF_A3		(1<<11)
#define RDF_A4		(1<<12)
#define RDF_A5		(1<<13)
#define RDF_A6		(1<<14)
#define RDF_SSP 	(1<<16)
#define RDF_USP 	(1<<17)
#define RDF_PC		(1<<18)
#define RDF_SR		(1<<19)

/*
 *  Breakpoint definition block for TASK/DEBUG
 */
struct __br
{
    U16     brnum;      /* Number of defined entries */
    U32     braddr[MAXBRKPT];   /* Breakpoint addresses */
};

#define BRBLKSIZE sizeof(struct __br)

/*
 *  Segment defintion table entry.
 */
struct __sdte
{
    U16     segmac;     /* Segment memory access type */
    U16     segctrs;    /* Segment counter inclusion bits */
    S8      segname[8]; /* Segment name (8 bytes) */
    void    *segstrt;    /* Segment starting address */
    U32     segleng;    /* Segment length in bytes */
};

#define SEGSIZ		sizeof(struct __sdte)

/*
 *  Handler dependent IO system service options
 */

/**** System wide ****/
#define HOP_RARM  (1<<15)           /* IO/INFO/READ_CP_QUEUE:  re-arm interrupt vector */
#define HOP_DSTA	(1<<0)          /* IO/MODE/SET_DEVICE_STATUS: set = online, reset = offline */

/**** File system ****/
#define HOP_AMO 	(1<<0)          /* IO/MOUNT -- alias mount, use pktfname */
#define HOP_DEST	(1<<0)          /* IO/CREATE (data file): Truncate if exists */
#define HOP_DCLO	(1<<1)          /* IO/CREATE/CLOSE (data file): Destroy on close */
#define HOP_BKUP	(1<<0)          /* IO/CLOSE -- set last backed up timestamp */
#define HOP_KCLO 	(1<<2)          /* IO/CLOSE (data file): Keep (do not destroy) */
#define HOP_UNIQ	(1<<3)          /* IO/OPEN  -- create and open a unique named file */
#define HOP_SYNC	(1<<4)          /* IO/OPEN  -- sync data structures on write */
#define HOP_RBLOC	(1<<5)          /* IO/OPEN  -- return multiple entries on read (dir) */
#define HOP_SEQ		(1<<6)          /* IO/OPEN  -- auto-update FPOS (PMD only) */
#define HOP_REFI	(1<<0)          /* IO/READ (dir file): Get file info with entry */

/**** Null handler ****/
#define HOP_BLOCK	(1<<0)          /* IO/MOUNT -- mount as a blocked entity */

/**** Intf (host) handler ****/
#define HOP_DAV 	(1<<0)          /* IO/MODE -- Define Attention Vector */
#define HOP_UAV 	(1<<1)          /* IO/MODE -- Undefine Attention Vector */

/**** Remote server handler ****/
#define HOP_SERV	(1<<1)          /* IO/OPEN -- inter-server connect request */
#define HOP_LOCAL	(1<<2)          /* IO/CREATE -- create node */
#define HOP_CNTX	(1<<3)          /* IO/WRITE -- include context */

/**** Disk handler ****/
#define HOP_NFSY	(1<<0)          /* IO/CREATE -- not file system device */
#define HOP_NECC	(1<<0)          /* IO/READ/WRITE -- disable controller ECC */
#define HOP_UNLD	(1<<0)          /* IO/MODE REWIND -- unload */
#define HOP_REV 	(1<<0)          /* IO/MODE SPACE -- reversed */
#define HOP_NRTY	(1<<1)          /* IO/READ/WRITE -- disable contr_ retries */
#define HOP_FIL 	(1<<1)          /* IO/MODE SPACE -- file */

/* INTERFACE Service
 *       ALL INTERFACE SERVICES [VIRTUAL PORTS] DEFINED IN VPDUSER.H
 */

/*
 *  IO INFO classes
 */
#define IOICSYS_	0               /* System class */
#define IOICNAM_	1               /* Name class */
#define IOICFIL_	2               /* Logical file class */

/*
 *  IO MODE classes
 */
#define IOMCSYS_	0               /* System class */
#define IOMCNAM_	1               /* Name class */
#define IOMCFIL_	2               /* Logical file class */

/*
 *  IO EXCHANGE classes
 */
#define	IOXCSYS_ 	0               /* System class */
#define	IOXCNAM_ 	1               /* Name class */
#define	IOXCFIL_ 	2               /* Logical file class */

/*
 *  IO Info type values
 *
 *  0 to 127 name and file related infos serviced by IO/ system
 */
#define IOIGFDT_	5               /* (cfil) Get file (name) device type */
#define IOIGLDT_	5               /* (cnam) Get (open logical) file device type */
#define IOIGDLV_	10              /* (csys) Get default logical volume */
#define IOIGLFN_	11              /* (csys) Get logical file names */
#define IOISHIE_	12              /* (csys) Get the status field of an HIE */
#define IOIGCD_ 	13              /* (csys) Get task's current directory */
#define IOIGXFN_	15              /* (cnam) Get expanded file name for name */
#define IOIGHAN_	17              /* (cnam) Get handler task name for an io entity */

/*
 *  128 to 159 - name and file related infos accepted by all handlers
 */
#define IOIREQU_	128             /* (csys) Read data from a CP activity queue */
#define IOIRECH_	129             /* (csys) Read data from a CP channel block */
#define IOIDEPR_	130             /* (cnam) Detailed entity properties */
#define IOIDFPR_	131             /* (cfil) Detailed file properties */
#define IOIFNAM_	132             /* (cfil) Entity name for file */
#define IOIGDST_	140             /* (cnam) Get device status */

/*
 *  160 to 255 - name and file related handler specific info
 */
#define IOINFIL_	161             /* (cnam) Get FS file extended info */
#define IOIFFIL_	161             /* (cfil) Get FS file extended info */
#define IOIVUNI_	162             /* (cnam) Get disk units for a FS volume */
#define IOIEFI_ 	163             /* (cnam&cfil) Get NEW format FS file extended info */
#define IOIDPAR_	163             /* (cnam&cfil) Get device configuration parameters */
#define IOIVSPA_	164             /* (cnam) Get volume space info (FS) */
#define IOIDSPA_	165             /* (cnam) Get space info (PMD use only) (FS) */
#define IOIGHIT_	170             /* (cnam) HAD: Get device HIT index */
#define IOICMDI_	174             /* (cname) $res: get module detailed info */
#define IOICDIR_	200             /* (cnam) oc: console configuration */
#define IOIHLNK_	201             /* (cnam) host: link user */
#define IOIHRPR_	202             /* (cnam) host: read startup parameters */
#define IOICTSK_	202             /* (cnam) oc: tasks open */

/*
 *  IO Mode type values
 */
#define IOMSDLV_  10                /* (csys) Set system default logical volume */
#define IOMIHCM_  22                /* (csys) Issue a HAD (EPROM) command */
#define IOMCHIE_  24                /* (csys) Create an HIE */
#define IOMDHIE_  25                /* (csys) Destroy an HIE */
#define IOMMHIE_  26                /* (csys) Modify the status field of an HIE */
#define IOMCRQU_	128             /* (csys) Create (claim) a CP queue */
#define IOMDEQU_	129             /* (csys) Destroy (give up) a CP queue */
#define IOMCRCH_	130             /* (csys) Create (claim) a CP channel */
#define IOMDECH_	131             /* (csys) Destroy (give up) a CP channel */
#define IOMWRCH_	132             /* (csys) Write data into a CP channel block */
#define IOMCTCP_	133             /* (csys) Control CP (enable, activate, etc.) */
#define IOMSDST_	140             /* (cnam) Set device on-line/off-line */
#define IOMLOCK_	141             /* (cfil) Dynamically lock an open file */
#define IOMUNLK_	142             /* (cfil) Unlock a file previously IOMLOCK'ed */
#define IOMDFMT_	160             /* (cfil) Format (prep) a disk volume */
#define IOMFLOCK_	170             /* (cnam) FS: set locked flag */
#define IOMFUNLK_	171             /* (cnam) FS: reset locked flag */
#define IOMCGCON_	200             /* (cfil & cnam) log: change destination file */
#define IOMSYNC_	200             /* (cfil) FS: sync data structures on disk */
#define IOMICAC_	205             /* (cnam) FS: create (or resize) FS cache */
#define IOMFPAR_	210             /* (cfil & cnam) FS: set file attributes */
#define IOMREW_ 	207             /* (cfil) HAD: rewind device */
#define IOMSPACE_	208             /* (cfil) HAD: space device */
#define IOMWRFM_	209             /* (cfil) HAD: write file mark */
#define IOMRALC_	209             /* (cnam) log: reset alarm condition */
#define IOMDHWD_	210             /* (cnam) log: disable hardware watchdog */
#define IOMEHWD_	220             /* (cnam) log: enable hardware watchdog */
#define IOMSRFS_	225             /* (cnam) log: set fs space reserved from pmd usage */
#define IOMFSMEM_	230             /* (cnam) log: free standalone memory */
#define IOMCBOOT_	240             /* (cnam) log: force coldstart on crash */
#define IOMCDEF_	221             /* (cnam) oc: console addition */
#define IOMCREM_	222             /* (cnam) oc: console deletion */
#define IOMCATN_	224             /* (cnam) oc: set attentive task */
#define IOMCDQS_	226             /* (cnam) oc: set device queue size */
#define IOMCTWS_	227             /* (cnam) oc: set task window size */
#define IOMCDDQ_	228             /* (cnam) oc: set default device queue size */
#define IOMCDTW_	229             /* (cnam) oc: set default task window size */
#define IOMCTWF_	230             /* (cnam) oc: suppress task window full error */
#define IOMHRCK_	231             /* (cnam) host: read H/W clock */
#define IOMHWCK_	232             /* (cnam) host: write H/W clock */
#define IOMHWPR_	233             /* (cnam) host: write startup parameters */
#define IOMCPAR_	234             /* (cnam) cons: configure options */

/*
 *  IO Exchange type values
 */

/*
 *  0 to 127 name and file related exchanges serviced by IO/ system
 */

/*
 *  128 to 159 - name and file related exchanges accepted by all handlers
 */
#define IOEXOLBC_	128             /* (cnam) pktparam has OLBC preamble */

/*
 *  160 to 255 - name and file related handler specific exchanges
 */

/*
 *  I/O exchange OLBC preamble revision code values
 */
#define IOEXRNUL_	0               /* OLBC preamble revision: null */

/*
 *  I/O exchange OLBC preamble function code values
 */
#define IOEXFQR_	0               /* OLBC preamble function: revision query */

/*
 *  Operator Communications handler structures.
 */

/*
 * Console configure options parameter buffer
 * also returned in handler dependant info of ioidepr. and ioidfpr. calls
 */
struct __conpar
{
    U8   conbch;     /* boot character */
    U8   concts;     /* 0= stay online on signal loss, else go offline */
    U16  conrto;     /* 0= no timeout, else read timeout in seconds */
    U16  conwct;     /* 0= retry forever, else retry #-1 times */
};

#define CONPRSZ		sizeof(struct __conpar)

/*
 *  OC/INFO/IOICDIR structure.
 */
struct __oc_info_ioicdir
{                               /* this doesn't exist in cpkuser.in */
    U16  size;       /* Byte length of IO entity name of Operator Terminal. */
    U16  oreq;       /* Number of outstanding IO requests for Operator Terminal. */
    U16  qreq;       /* Number of IO requests currently queued awaiting completion */
    /* of an IO/READ request to Operator Terminal. */
    U8   emask;      /* Exception mask */
    U8   etype;      /* Entity type */
    S8   ename[MAXFNA];  /* IO Entity name */
};

/*
 *  Host handler structures.
 */

/*
 *  HOST/INFO/IOIHLNK structure.
 */
struct __host_info_ioihlnk
{                               /* this doesn't exist in cpkuser.in */
    U16         size;       /* Byte length of name of file currently */
    /* being transferred via host link. */
    S8          taskname[8];    /* Name of task currently using host link */
    S8          filename[MAXFNA];   /* name of file currently being transferred */
    /* via host link. */
};

/*
 *  Disk handler structures.
 */

/*
 *  DISK/CREATE structure.
 */
struct __disk_create
{                               /* this doesn't exist in cpkuser.in */
    U32   cname;      /* controller name */
    U32   uname;      /* unit name */
    U16   unit;       /* unit number */
};

/*
 * IO/INFO return information buffer
 */

struct __ioi
{
    U16  ioibflag;   /* Definition flags */
    U8   ioibdevt;   /* Device type (TYPxxxx.) */
    U8   ioibdtyp;   /* Data type */
    union
    {
        struct
        {
            U32   ioibbsiz;   /* Block size (fixed block entities) */
            U32   ioibmblk;   /* Maximum number of blocks/transfer (fixed block) */
        }
        fixed;
        struct
        {
            U32   ioibmint;   /* Minimum read buffer size in bytes (variable) */
            U32   ioibmaxt;   /* Maximum transfer count in bytes     " " " */
        }
        variable;
    }
    sizes;
    union
    {
        U32   ioibhdef[2];    /* Handler defined info */
        struct
        {                       /* For FS data files */
            U8   ioibrmsv;   /* RMS version  (NOT USED) */
            U8   ioibrect;   /* record type  (0 = none) */
            U16  ioibrecs;   /* record size  (if ioibrect <> 0) */
            U32  ioibrecc;   /* record count (if ioibrect <> 0) */
        }
        FSdata;
    }
    Hdata;
};

#define IOIBSIZE	sizeof(struct __ioi)

/*
 *  ioibflag bit definitions
 */
#define IOP_DIR 	(1<<0)          /* Entity is a directory */
#define IOP_READ	(1<<1)          /* Entity supports READ requests */
#define IOP_WRITE	(1<<2)          /* Entity supports WRITE requests */
#define IOP_EXCL	(1<<3)          /* Entity supports exclusive access */
#define IOP_FIX 	(1<<4)          /* Set - fixed block entity, reset - variable */
#define IOP_POSI	(1<<5)          /* Entity supports use of FPOS */
#define IOP_TEXT	(1<<6)          /* Entity supports text standard */
#define IOP_PREAD	(1<<7)          /* Supports read w/prompt using secondary buffer */
#define IOP_STDN	(1<<8)          /* Entity supports standard names */
#define IOP_DYNAM	(1<<9)          /* Entity has dymanic file structure */
#define IOP_BDIR  (1<<10)           /* Entity supports block directory read */
#define IOP_OLBC 	(1<<11)         /* Entity supports OLBC */

/*
 *  I/O info block for File System file detailed info
 */
struct __iof
{
    U32  iofiflag;   /* Flags and general properties */
    U8   iofidtyp;   /* Data file data type */
    U8   iof_fil1;   /* ** filler ** */
    U16  iofilcnt;   /* File link count */
    U32  iofileof;   /* Data file End-of-file position (file size) */
    U32  iofialoc;   /* Data file allocated space */
    U16  ioficrts[5];    /* File creation timestamp */
    U16  ioficlts[5];    /* File last close timestamp */
    U16  iofiwrts[5];    /* File last written timestamp */
    U16  iofibuts[5];    /* File last back'ed up timestamp */
    S8   iofiuid[10];    /* User id of file creator */
    U8   iofirmsv;   /* RMS version (NOT used) */
    U8   iofirect;   /* record type (0 = none) */
    U16  iofirecs;   /* record size (if iofirect <> 0) */
    U32  iofirecc;   /* record count (if iofirect <> 0) */
    U8   iofires[14];    /* Reserved for future enhancements */
};

#define IOFIBSIZ	sizeof(struct __iof)

/*
 *  I/O status flags returned in PKTRVALU by IOIGDS. info call
 */
#define IOST_ON 	(1<<0)          /* Set if entity is "on-line" */
#define IOST_EXC	(1<<1)          /* Set if entity is currently exclusively open */
#define IOST_USE	(1<<2)          /* Set if entity is currently in use (open) */


/*
 *  I/O info block for ioivuni. call (per unit)
 */
struct __vent
{
    U16  ventseqn;   /* Volume entry sequence number */
    U16  ventnsiz;   /* Name size */
    S8            ventname[MAXVOLN + MAXSFN + 1]; /* Entry name */
};

#define VENTSIZE	sizeof(struct __vent)

/*
 *  I/O info block for module info (ioicmdi.)
 */
struct __rmseg
{
    S8    rmsnam[8];  /* Segment name */
    U32   rmssta;     /* Segment start */
    U32   rmssiz;     /* Segment length */
    U16   rmsmac;     /* Segment memory access */
};

struct __ioim
{
    S8              ioimidnt[12];   /* Module ident, only first 10 chars are meaningful */
    U8              ioimrevi;   /* Module revision */
    U8              ioimvers;   /* Module version */
    U32             ioimentry;  /* Module entry point */
    struct __rmseg  ioimsegs[MAXSEG];   /* Segment info */
};

#define IOIMSIZE	sizeof(struct __ioim)

/*
 *  FILE/INFO/IOIVSPA structure.
 */
struct __file_info_ioivspa
{                               /* this doesn't exist in cpkuser.in */
    U32   size;       /* Total volume size in sectors */
    U32   free;       /* Number of free sectors */
};

struct __timestamp
{                               /* this doesn't exist in cpkuser.in */
    U16  year;
    U8   month;
    U8   day;
    U8   hour;
    U8   min;
    U8   sec;
    S8   zone;
    U16  msec;
};

/*
 *  File system characteristics structures.
 */
struct __file_char
{                               /* this doesn't exist in cpkuser.in */
    S8                  uid[16];    /* User id of file creator */
    S8                  nid[16];    /* Node id */
    struct __timestamp  crts;    /* created */
    struct __timestamp  clts;    /* closed */
    struct __timestamp  wrts;    /* last written */
    struct __timestamp  bkts;    /* last backed up */
    U8                  rect;       /* record type */
    U8                  f1;         /* filler */
    U16                 recs;       /* record size */
    U32                 recc;       /* record count */
    S8                  desc[100];  /* file description */
    U32                 flag;       /* file system flags */
    U8                  dtyp;       /* data type */
    U8                  f2;         /* filler */
    U16                 lcnt;       /* link count */
    U32                 eof;        /* end of file position */
    U32                 aloc;       /* amount of space allocated */
    U8                  tabs;       /* fse tab setting */
    U8                  f3[103];    /* filler to max buffer size 300 */
};

#define IOIEFISIZE		sizeof(struct __file_char)

/*
 *   System standard logical file names
 */
#define LFNOPRM_	'$sys'          /* Operator interface logical file name MSH */
#define LFNOPRL_	'opr '          /* Operator interface logical file name LSH */
#define LFNSINM_	'$sys'          /* Standard input logical file name MSH */
#define LFNSINL_	'in  '          /* Standard input logical file name LSH */
#define LFNSOUM_	'$sys'          /* Standard output logical file name MSH */
#define LFNSOUL_	'out '          /* Standard output logical file name LSH */

/*
 *  CP high channel semaphore name
 */
#define TCPHCNM_	'$tcp'
#define TCPHCNL_	'hcsn'

/*
 *  Names of comms permanent shared regions
 */
#define ACQNMM_ 	'AQ  '          /* activity queues shared region name msh */
#define ACQNML_ 	'    '          /* activity queues shared region name lsh */
#define CHCBNMM_	'CCB '          /* channel control blocks shared region name msh */
#define CHCBNML_	'    '          /* channel control blocks shared region name lsh */

#define SCDNMM_ 	'SCD '          /* LES SCD table region name */
#define SCDNML_ 	'    '
#define SCCNMM_ 	'SCC '          /* LES SCC i/o space region name */
#define SCCNML_ 	'    '
#define BMDNMM_ 	'BMD '          /* LES baud/modem i/o space region name */
#define BMDNML_ 	'    '
#define MDMNMM_ 	'MDM '          /* LES modem i/o space region name */
#define MDMNML_ 	'    '

/*
 *   File name delimiters
 */
#define LVOLFLAG	':'             /* Logical volume flag */
#define LEVDELIM	'/'             /* File name level delimiter */
#define UPLEVEL 	'^'             /* Uplevel directory reference */
#define REMDELIM	'@'             /* Remote request delimiter */

/*
 * Memory info selection indicies
 */
#define MIRGNS_   0                 /* Return all shared regions in system */
#define MITRDS_   1                 /* Return all task regions for a given task */
#define MITASKS_  2                 /* Return all tasks using a given shared regions */
#define MINAME_   3                 /* Get name of region, given the owning task + addr */
#define MISTAT_   4                 /* Get info about region, given its name and task */
#define MIACCESS_ 5                 /* Get MCU access code for a given address */
#define MIFREMEM_ 6                 /* Get amount and largest contigous area of free mem */
#define MIFREBLK_ 7                 /* Return list of free memory blocks */
#define MITOTAL_  8                 /* Return count and total size for a task */
#define MITNAMES_ 9                 /* Return names of all regions for a task */
#define MIPAGES_  10                /* Return total # of memory pages & pages available */
#define MIMXINFO_ 11                /* Maximum index number + 1 */

#define MEMPAGESIZE 4096            /* 4K page size */

/*
 * Task monitor message status (MMGSTAT.B)
 */
#define MMSGOOD_	0               /* Successful completion of function */
#define MMSBAD_ 	1               /* Unsuccessful completion of function */

/*
 * Task monitor message type (MMGTYPE.B)
 */
#define MMTTKCR_	0               /* TASK CREATE completion separation from creator */
#define MMTTKLO_	1               /* TASK boot loading completion */
#define MMTTKSR_	2               /* TASK START completion */
#define MMTTKSP_	3               /* TASK STOP initiation */
#define MMTTKDE_	4               /* TASK DESTROY initiation */
#define MMTONLN_	5               /* Task is now going online */
#define MMTOFLN_	6               /* Task is now going offline */

/*
 *   Module information block (shared library, shared module, or local)
 */
struct __mib
{
    S8      mibname[8]; /* Name of module */
    S8      mibident[10];   /* Module ident */
    U8      mibdummy[2];    /* * alignment * (DO NOT DELETE!) */
    S32     mibdsoff;   /* Dsect initial offset (library only) */
    U32     mibdssiz;   /* Dsect size (library only) */
    U8      mibvers;    /* Module version */
    U8      mibrevi;    /* Module revision */
    U16     mibfnasz;   /* File name size */
    S8      mibfname[MAXFNA];   /* File name */
    U8      mibsegs[SEGSIZ * MAXSEG];   /* Segment table */
    U32     mibentry;   /* Entry point (non-library only) */
    U32     mibrefs[MAXREFS * 2];   /* Library reference list */
    U8      mibbdat[MBDATESZ];  /* module build timestamp */
    U16     mibcomsz;   /* module ident comment size */
    S8      mibcomm[MAXCODCOMM];    /* module ident comment */
};

#define MIBSIZE 	sizeof(struct __mib)

/*
 * Debug message type (DBMTYPE.b)
 */
#define DBMTRACE_	0               /* Trace completion */
#define DBMBRKPT_	1               /* Breakpoint (number in dbmaux) */
#define DBMEXCEP_	2               /* Other exception  (xt.??? in dbmaux) */

/*
 *  IO sub-service options
 */
#define MNT_FSE 	(1<<0)          /* Mount option - mounting a file system volume */

/*
 *  Memory status bits (memory service options=PKTMOPTS)
 */
#define MEM_UR		(1<<0)          /* Access : User read */
#define MEM_UW		(1<<1)          /* Access : User write */
#define MEM_UI		(1<<2)          /* Access : User instruction */
#define MEM_IOR 	(1<<3)          /* Access : IO device can read */
#define MEM_IOW 	(1<<4)          /* Access : IO device can write */
#define MEM_SR		(1<<5)          /* Access : Super read */
#define MEM_SW		(1<<6)          /* Access : Super write */
#define MEM_SI		(1<<7)          /* Access : Super instruction */
#define MEM_IOC 	(1<<8)          /* Access : IO device control */
#define MEMSHAR_	(1<<9)          /* Shared Region Type (3 bit field) */
#define MEMMASK_  (0x1FF)           /* Mask of MCU specific stat bits */
#define MSHMASK_  (0xE00)           /* Mask of shared mode type field */
                /* bit 12 is reserved (maps onto rgn.live) */
#define MEM_ABS   (1<<13)           /* MEMORY/CREATE : Absolute (internal use) */

#define MEM_STATIC  (1<<14)         /* MEMORY/CREATE: Prefer STATIC RAM (if available) */
#define MEM_DYNAMIC (1<<15)         /* MEMORY/CREATE: Prefer DYNAMIC RAM (if available) */

/*
 *  Values for MEMSHAR. field (in pktmopts)
 */
#define MSHPRIVAT_   0              /* Private (non-shared) memory */
#define MSHPERM_  1                 /* Permanent shared region */
#define MSHLATENT_   3              /* Latent shared region */
#define MSHDYNAM_ 5                 /* Dynamic shared region */

/*
 *  System Completion Codes for TRAP calls.
 */
#define SCCPKT_ 	1               /* Invalid packet address */
#define SCCSVN_ 	2               /* Invalid service number */
#define SCCSSN_ 	3               /* Invalid sub-service number */
#define SCCGOP_ 	4               /* Invalid or conflicting global options */
#define SCCNAME_	5               /* Illegal name format */
#define SCC1010_	6               /* Unregistered line 1010 emulator call */
#define SCC1111_	7               /* Unregistered line 1111 emulator call */
#define SCCILGL_	8               /* Illegal Instruction */
#define SCCADRR_	9               /* Exception:  Address Error */
#define SCCBUS_ 	10              /* Exception:  Bus Error . */
#define SCC0DIV_	11              /* Exception:  Zero Divide */
#define SCCPRV_ 	12              /* Exception:  Privilege Violation */
#define SCCCHK_ 	13              /* Exception:  CHK Instruction */
#define SCCTRPV_	14              /* Exception:  TRAPV Instruction */
#define SCCEXST_	15              /* Tried to create item that already exists */
#define SCCNXST_	16              /* Tried to reference non-existant item */
#define SCCEMPY_	17              /* Empty list */
#define SCCMEM_ 	18              /* Not enough memory to complete service */
#define SCCGLOB_	19              /* Local item also exists globally. */
#define SCCOPTN_	20              /* Illegal or conflicting options */
#define SCCIIAD_	21              /* Internal Address in packet points to garbage. */
#define SCCNTSK_	22              /* Task does not exist */
#define SCCETSK_	23              /* Task already exists */
#define SCCUSE_ 	24              /* Item is in use */
#define SCCINDX_	25              /* Selection index is invalid */
#define SCCSWPR_	26              /* Requestor is not software privileged */
#define SCCHWPR_	27              /* Requestor is not hardware privileged */
#define SCCPRI_ 	28              /* Invalid priority */
#define SCCNMON_	29              /* Monitor queue not found in system */
#define SCCSMON_	30              /* Monitor queue same as task name */
#define SCCLFAO_	31              /* Logical file already open */
#define SCCDNCA_	32              /* Destroy not currently allowed */
#define SCCCPU_ 	33              /* Requested CPU ID is invalid */
#define SCCSTAK_	34              /* Improper stack specification */
#define SCCSOP_ 	35              /* Invalid or conflicting service options */
#define SCCWIND_	36              /* IO window full */
#define SCCCQR_ 	37              /* Couldn't queue request (to handler) */
#define SCCSTRT_	38              /* Resource has not been START'ed */
#define SCCNCUR_	39              /* Request only valid for current task. */
#define SCCIQN_ 	40              /* Invalid queue name (not found in system) */
#define SCCIAM_ 	41              /* Invalid access mode (read or write not allowed) */
#define SCCOWN_ 	42              /* Requestor not owner of entity */
#define SCCISTA_	43              /* Queue in indeterminate state */
#define SCCAPMI_	44              /* No APM task ID available */
#define SCCPARM_	45              /* Parameter block pointer or contents are invalid */
#define SCCTVAL_	46              /* Invalid timer value specified on TIMER/START */
#define SCCEOF_ 	47              /* End of file detected (on IO/READ) */
#define SCCOK_		48              /* Item is OK (repair request not allowed) */
#define SCCISQ_ 	49              /* Service queue should not be a work queue */
#define SCCBUF_ 	50              /* User buffer too small to complete transfer */
#define SCCNSHR_	51              /* Item is not shared */
#define SCCFULL_	52              /* Internal table full */
#define SCCCFG_ 	53              /* Invalid configuration request */
#define SCCDER_ 	54              /* Device error */
#define SCCIODR_	55              /* IODONE, bad subservice in user packet */
#define SCCIODA_	56              /* IODONE, bad address for user packet */
#define SCCLVNF_	57              /* Logical volume not found */
#define SCCNQNE_	58              /* Bad service queue (QUEUE/WRITE to a work queue) */
#define SCCQDIS_	59              /* Queue disabled (QUEUE/WRITE) */
#define SCCOBQ_ 	60              /* Operation has been queued (in progress) */
#define SCCCCVN_	61              /* Cannot change logical volume name */
#define SCCHIE_ 	62              /* Handler internal error (bad Queue name, etc.) */
#define SCCMXTK_	63              /* Too many tasks at the same priority level */
#define SCCTCBA_	64              /* Supplied TCB address is invalid */
#define SCCNDEL_	65              /* Item is not deletable. */
#define SCCIAF_ 	66              /* Data movememt service : invalid access on from adr */
#define SCCNIF_ 	67              /* : from addr not in from task */
#define SCCIAT_ 	68              /* : invalid access on to addr */
#define SCCNIT_ 	69              /* : to addr not in to task */
#define SCCFNSP_	70              /* Function not supported (by handler) */
#define SCCSEG_ 	71              /* Segment table for loader is invalid */
#define SCCEXCL_	72              /* Item is currently under exclusive use */
#define SCCNDTS_	73              /* No device type specified on a MOUNT */
#define SCCDTNS_	74              /* Device type not supported */
#define SCCCRSQ_	75              /* Handler internal error (counldn't read SQ) */
#define SCCDENY_	76              /* Handler denied system resource during operation */
#define SCCNMSG_	77              /* No message entry available */
#define SCCBCNT_	78              /* Invalid byte count specified */
#define SCCARG_ 	79              /* Invalid argument (non-specific) */
#define SCCOICR_	80              /* Operation ignored due to CLOSE or RESET */
#define SCCOFF_ 	81              /* Device off-line */
#define SCCLIOP_	82              /* Loader I/O error on open of load module file */
#define SCCLIRE_	83              /* Loader I/O error on read of load module file */
#define SCCLICL_	84              /* Loader I/O error on close of load module file */
#define SCCLMCR_	85              /* Loader memory error on create of region */
#define SCCLMMO_	86              /* Loader memory error on mode of region */
#define SCCULRT_	87              /* Loader detected unsupported record type */
#define SCCTMSD_	88              /* Loader detected too many symbol definitions */
#define SCCLEXT_	89              /* Loader detected unresolved external reference */
#define SCCLUND_	90              /* Loader detected undefined load record type */
#define SCCLFMT_	91              /* Loader detected format error in load module record */
#define SCCOPOP_	92              /* Operator interface logical file open error */
#define SCCOPSI_	93              /* Standard input logical file open error */
#define SCCOPSO_	94              /* Standard output logical file open error */
#define SCCSTCD_	95              /* Set current directory returned error */
#define SCCAIT_ 	96              /* Abnormal I/O termination.  See return value. */
#define SCCCSL_ 	97              /* Improper completion mode for subservice */
#define SCCHREJ_	98              /* Handler rejects request */
#define SCCINSP_	99              /* Invalid name string pointer */
#define SCCAPMV_	100             /* Exception:  APM address violation */
#define SCCMCUV_	101             /* Exception:  MCU address violation */
#define SCCTRAC_	102             /* Exception:  Unregistered trace */
#define SCCFPOV_	103             /* Exception:  Floating point overflow */
#define SCCFPUN_	104             /* Exception:  Floating point underflow */
#define SCCTRAP_	105             /* Exception:  Unimplemented TRAP */
#define SCCABRT_	106             /* Exception:  Abort from other task */
#define SCCBUSY_	107             /* Resource is currently busy */
#define SCCIRES_	108             /* Invalid resource */
#define SCCSPA_ 	109             /* Out of space on disk */
#define SCCDLOK_	110             /* Semaphore deadlock detected */
#define SCCRES_ 	111             /* Reset in progress */
#define SCCCLOS_	112             /* Close in progress */
#define SCCHKE_ 	113             /* Handler key is in error */
#define SCCMDL_ 	114             /* Missing directory level in tree search */
#define SCCIDL_ 	115             /* Invalid directory level in tree search */
#define SCCDNE_ 	116             /* Directory file not empty for destroy */
#define SCCLREL_	117             /* Loader detected relocation size error */
#define SCCPOS_ 	118             /* Invalid file position */
#define SCCNDBG_	119             /* Module not debuggable */
#define SCCSHMOD_	120             /* Attempt to modify shared memory */
#define SCCNIMOD_	121             /* Breakpoint must be in executable memory */
#define SCCSTATE_	122             /* Task state inappropriate */
#define SCCNDBGR_	123             /* Not registered as debugger for task */
#define SCCABSE_	124             /* Absolute entry points not supported */
#define SCCLIBE_	125             /* Libraries cannot have entry points */
#define SCCDUPL_	126             /* Duplicate XDEF definition in library */
#define SCCTMLR_	127             /* Too many shared libs ref'ed in a load */
#define SCCLIBC_	128             /* Libraries cannot contain commons */
#define SCCNXD_ 	129             /* Shared library contained no XDEF's */
#define SCCUDWARN_ 130              /* Utility detected warning(s) */
#define SCCUDERR_	131             /* Utility detected error(s) */
#define SCCNET_ 	132             /* Network error */
#define SCCCONN_	133             /* Device connected */
#define SCCDISC_	134             /* Device disconnected */
#define SCCWRAP_	135             /* Channel failed wrap test */
#define SCCCARD_	136             /* Channel card not present */
#define SCCCRC_ 	137             /* CRC error on read request */
#define SCCPARI_	138             /* Parity error on read request */
#define SCCFRAM_	139             /* Framing error on read request */
#define SCCOVRF_	140             /* Receiver overflow on read request */
#define SCCUNDR_	141             /* Transmitter underrun on write request */
#define SCCCPNC_	142             /* No cp configured and running */
#define SCCMIP_ 	143             /* X25 merge in progress */
#define SCCVERS_	144             /* Incompatible program versions */
#define SCCCAN_ 	145             /* Operation ignored due to cancel */
#define SCCDSEC_	146             /* Invalid dummy section */
#define SCCLDIR_	147             /* Cannot link to a directory */
#define SCCLOCK_	148             /* Operation rejected, item is locked */
#define SCCBINI_	149             /* Initialization routine not allowed */
#define SCCMODI_	150             /* Module contained too many init routines */
#define SCCOPTO_	151             /* Operation timed out */
#define SCCPRIV_	152             /* Insufficient privilidge for request */
#define SCCDSQU_	153             /* library exceeds reserved dsect space */
#define SCCOLBC_	154             /* Handler does not support OLBC */
#define SCCHLNK_	155             /* Illegal operation on hard linked file */

/* ----- NMS Communications specific completion codes start at 200 */
#define SCCWAIT_  200               /* Wait before continuing */
#define SCCROUTE_ 201               /* No Ethernet Route available */
#define SCCIPADDR_ 202              /* Local IP Addr not available */

#define SCCANSIC_ 4096              /* Start of scc range reserved for ANSI C */
#define SCCANSICEND_	4127        /* End of scc range reserved for ANSI C */

/*
 *  KERNEL boot failure reasons
 *  (placed in Cold Boot Status Block [cbs_BootErr])
 *
 * $00      = No cold boot error indicated
 * $01..$0F = RESERVED FOR FUTURE USE
 * $10..$1F = Error while loading KERNEL [last phase of preboot]
 * $20      = RESERVED FOR FUTURE USE
 * $21..$7F = Error while KERNEL initializing
 * $80..$BF = Error while prebooting
 * $C0..$FF = RESERVED FOR FUTURE USE
 *
 *  NOTE: Boot error codes begin from $21 so in printable ASCII range
 */
#define CPBT_INTCTL   0x21          /* configuring interrupt controller */
#define CPBT_LOGGER   0x22          /* initializing KERNEL logger */
#define CPBT_EXCEPT   0x23          /* initializing exception table */
#define CPBT_MEMORY   0x24          /* initializing memory management */
#define CPBT_LIBRARY  0x25          /* initializing library handling */
#define CPBT_GPLIB    0x26          /* initializing KERNEL's GPLIB context */
#define CPBT_SYSINFO  0x27          /* initializing system information region */
#define CPBT_SUBPROC  0x28          /* initializing configured sub-processors */
#define CPBT_MICROCD  0x29          /* installing microcode */
#define CPBT_SS7      0x2A          /* initializing SS7 microcode handling */
#define CPBT_T1E1     0x2B          /* initializing T1/E1 handling */
#define CPBT_DMA      0x2C          /* initializing DMA controller */
#define CPBT_NAMEOBJ  0x2D          /* activating named object handling */
#define CPBT_TIMERS   0x2E          /* initializing timer management */
#define CPBT_TASKS    0x2F          /* initializing task dispatcher */
#define CPBT_DPRAM    0x30          /* initializing Dual Port Ram services */
#define CPBT_SCC      0x31          /* initializing Serial Communications management */
#define CPBT_CEBUS    0x32          /* initializing CEBus [CENODE] Communications management */
#define CPBT_MOBILE   0x33          /* initializing mobile [MobiPak] Communications management */
#define CPBT_ETHERNET 0x34          /* initializing Ethernet Communications management */
#define CPBT_TDM      0x35          /* initializing Time Division Multiplex handling */
#define CPBT_QUICC32  0x36          /* initializing QUICC32 handling */
#define CPBT_VPORTS   0x37          /* initializing Virtual Port handling */
#define CPBT_IOSYSTEM 0x38          /* initializing IO system */
#define CPBT_EEPROM   0x39          /* reading the EEPROM */
#define CPBT_EECHKSUM 0x3A          /* verifying the EEPROM checksum */
#define CPBT_FLASH    0x3B          /* enabling flash memory access */
#define CPBT_HWRES    0x3C          /* determining hardware resources */
#define CPBT_WRTLATCH 0x3D          /* setting write latches */
#define CPBT_PCI      0x3E          /* initializing PCI Bus Access */
#define CPBT_MAXCODE  0x7D          /* largest printable ASCII code */

/*
 *  Type codes for msg entries
 *  0..127 reserved for system internal use
 *  128..255 available to users
 */
#define MSGUSER_    0               /* User created entry */
#define MSGIOR_     1               /* System I/O request entry */
#define MSGINTR_    2               /* System INTERRUPT entry */
#define MSGION_     3               /* I/O notify entry (returned to caller) */
#define MSGMEMORY_  6               /* Memory state change message */
#define MSGTIME_    7               /* TIMER notification message */
#define MSGTCPI_    8               /* CP interrupt vector request */
#define MSGHEX_     9               /* Queue exception notification packet */
#define MSGMON_     10              /* Task monitor message */

/*
 * SYSTEM/DEFINE and UNDEFINE subfunction types (PKTSOPTS.L)
 */
#define SDESLM_ 	1               /* Define shared load module */
#define SDELIB_ 	2               /* Define shared library */
#define SDESLOG_	3               /* Define system-wide logical name */
#define SDENODE_	4               /* Node Name */
#define SDEXQUE_	5               /* Default quantum in MS (define only) */
#define SDEQWDW_	6               /* Default queue window */
#define SDEQPAM_	7               /* Default queue pre-allocated messages */

/*
 * SYSTEM/MODE subfunction types
 */
#define SMOCOLD_	0               /* Coldstart the system (incl health cks) */
#define SMOWARM_	1               /* Warmstart the system (excl health cks) */
#define SMOCRSH_	2               /* Crash the system (go to monitor) */

/*
 *  SYSTEM/INFO subfunction types
 */
#define SINLIBS_	1               /* Get names of shared libraries */
#define SINLIBI_	2               /* Get extended info on a library */
#define SINLIBX_	3               /* Get list of XDEFs in a given library */
#define SINSLMS_	4               /* Get names of shared modules */
#define SINSLMI_	5               /* Get extended info on a shared module */
#define SINLSLOG_	6               /* Get list of system logicals */
#define SINXSLOG_	7               /* Get expansion of a system logical */
#define SINNODE_	9               /* Get Node Name */
#define SINXQUE_	10              /* Default quantum in MS */
#define SINQWDW_	11              /* Default queue window */
#define SINQPAM_	12              /* Default queue pre-allocted messages */
#define SINBDEV_	13              /* Boot device descriptor */

/*
 * Semaphore packet options (PKTSOPTS)
 */
#define SEM_ORST	(1<<0)          /* Assert semaphore ok. */

/*
 * Sub-service options for KRNL TRAP packet
 */
#define SOP_SCLK	(1<<0)          /* SYSTEM/TIME:  '0 = get clock,  '1 = set clock */
#define SOP_HWCK	(1<<1)          /* SYSTEM/TIME:  read/write H/W clock */
#define SOP_PRIV  (1<<16)           /* SYSTEM/DEFINE: Load using HWPR memory */
#define SOP_TREE 	(1<<14)         /* TASK/CRE:  Create new task tree */
#define SOP_PROP 	(1<<13)         /* TASK/CRE:  Propagate tasks within tree by default */
#define SOP_3PM  	(1<<12)         /* TASK/CRE:  Third party monitor (sys only) */
#define SOP_QCTL  (1<<11)           /* TASK/CRE:  Queue control specified */
#define SOP_XQU   (1<<10)           /* TASK/CRE:  Execution quantum specified */
#define SOP_SMEM	(1<<9)          /* TASK/CRE:  Share memory protection */
#define SOP_CRIT	(1<<8)          /* TASK/CRE:  Define task as "critical" */
#define SOP_NUID	(1<<7)          /* TASK/CRE:  Don't inherit user id */
#define SOP_NLOG	(1<<6)          /* TASK/CRE:  Don't inherit logical list */
#define SOP_PMD   (1<<5)            /* TASK/CRE:  perform pm dump on abort */
#define SOP_DBG 	(1<<4)          /* TASK/CRE and LOAD: Make debuggable */
#define SOP_DUMP	(1<<3)          /* TASK/CRE:  dump abort info, even if monitored */
#define SOP_AUTO	(1<<2)          /* TASK/CRE:  START after CREATE */
#define SOP_HWPR	(1<<1)          /* TASK/CRE:  Hardware privileged H/W S=1 */
#define SOP_SWPR	(1<<0)          /* TASK/CRE:  Software privileged */
#define SOP_REGS	(1<<0)          /* TASK/EXCEPT:  A6 and SP values supplied */
#define SOP_LIB 	(1<<0)          /* TASK/LOAD: Load a shared library (sys only) */
#define SOP_ROOT	(1<<1)          /* TASK/LOAD: Task root load (sys only) */
#define SOP_WQ		(1<<0)          /* QUE/CREATE:  Create a WORK QUEUE */
#define SOP_CSP 	(1<<1)          /* QUE/WRITE:   Caller Specified Priority */
#define SOP_CST 	(1<<2)          /* QUE/WRITE:   Caller Specified Type */
#define SOP_CPE 	(1<<3)          /* QUE/WRITE:   Create Permanent Entry */
#define SOP_WAS 	(1<<5)          /* QUE/WRITE:   Write and stall (system only) */
#define SOP_OWS   (1<<6)            /* QUE/WRITE:  Overwrite window specification */
#define SOP_TPER	(1<<0)          /* TIMER/START:  Periodic notification timer */
#define SOP_EXCL	(1<<0)          /* IO/OPEN: Provide exclusive use */
#define SOP_ROK 	(1<<1)          /* IO/OPEN: Read access requested */
#define SOP_WOK 	(1<<2)          /* IO/OPEN: Write access requested */
#define SOP_NCS 	(1<<3)          /* IO (all name server operations) resolve */
                           /* name using context supplied in pktncsk */
#define SOP_CREAT	(1<<4)          /* IO/OPEN: create file and open it */
#define SOP_APND  (1<<15)           /* IO/OPEN: (VME) create or append if exists */
#define SOP_ALL 	(1<<0)          /* IO/CANCEL: cancel all requests */
#define SOP_NUP 	(1<<0)          /* IO/IODONE:  No user packet specified (FS only) */
#define SOP_STDN	(1<<1)          /* IO/IODONE: (MOUNT) Volume uses std_ names */
#define SOP_CANC	(1<<2)          /* IO/IODONE: (MOUNT) Volume accepts io/cancel */
#define SOP_FPOS	(1<<2)          /* IO/IODONE: (Read/Write) FPOS in pktdfpos */
#define SOP_REDIR	(1<<3)          /* IO/IODONE: (special) redirect open */
#define SOP_OLBC 	(1<<4)          /* IO/IODONE: (MOUNT) volume supports OLBC */
#define SOP_RII 	(1<<0)          /* IO/RESET: Reset in progress read */
#define SOP_RIO 	(1<<1)          /* IO/RESET: Reset in progress write */
#define SOP_RQI 	(1<<2)          /* IO/RESET: Reset queued reads */
#define SOP_RQO 	(1<<3)          /* IO/RESET: Reset queued writes */
#define SOP_DCHN	(1<<0)          /* IO/READ/WRITE: Data chained operation */
#define SOP_PRIO	(1<<1)          /* IO/WRITE: High priority write request */
#define SOP_HLNK	(1<<0)          /* IO/RENAME: Define hard link */
#define SOP_SLNK	(1<<1)          /* IO/RENAME: Define symbolic link */
#define SOP_XAO 	(1<<0)          /* MEMORY/EXTRACT: Extract all occurrences */
#define SOP_DSOFT	(1<<0)          /* INTERFACE/DESTROY: Soft destroy (channel) */

/*
 *  queue status bits
 */
#define QUE_WQ		(1<<0)          /* Associated service queue present */
#define QUE_NQ		(1<<1)          /* Queue is a service queue */
#define QUE_RO		(1<<2)          /* Read Outstanding on this queue */
#define QUE_DIS 	(1<<3)          /* Queue is disabled (prevents WRITE) */
#define QUE_INHN	(1<<4)          /* Inhibit notification queue write */
#define QUE_CRIT	(1<<5)          /* Critical queue */

/*
 *  queue info selection
 */
#define QUEIDET_	0               /* Return detailed info about one queue */
#define QUEINML_	1               /* Return name list */

/*
 *  queue mode selection
 */
#define QUEENA_	0                   /* Enable queue */
#define QUEWIN_	1                   /* Set window depth */
#define QUEDIS_	16                  /* Disable queue */

/*
 *  task stall bits
 */
#define STL_TIM 	(1<<0)          /* Waiting on TIMER to expire */
#define STL_TASK	(1<<1)          /* Wait mode task create */
#define STL_IOH 	(1<<3)          /* I/O Hold */
#define STL_HOLD	(1<<4)          /* Operator Hold */
#define STL_SLEEP	(1<<5)          /* Sleeping */
#define STL_LOAD	(1<<6)          /* Module load in progress */
#define STL_SEMW	(1<<8)          /* Waiting on user semaphore */
#define STL_QUE 	(1<<9)          /* Awaiting Queue read completion */
#define STL_DBG   (1<<12)           /* Waiting on GO */
#define STL_RUN   (1<<15)           /* Already running */

/*
 *  system identification codes
 */
#define SYSID2_ 	0               /* Series 2 */
#define SYSID1A_	1               /* Series 1A */
#define SYSIDP5_	2               /* Series .5 */
#define SYSID1_ 	3               /* Series 1 */

/*
 *  Task Info selection indices (PKTSOPTS.B)
 */
#define TAITCBA_	0               /* Return TCB address of task in PKTIADDR/PKTRVALU.L */
#define TAISTAT_	1               /* Return task status/stalls in PKTRVALU */
#define TAIOPTS_	2               /* Return task execution options in PKTRVALU.L */
#define TAIPRIO_	3               /* Return task current priority in PKTRVALU.B */
#define TAIMONI_	4               /* Return task monitor list entries */
#define TAIEXEC_	5               /* Return exceptions processed information */
#define TAISEGT_	6               /* Return segment table from initial body load */
#define TAILMFN_	7               /* Return initial load module file name string */
#define TAIWDFN_	8               /* Return working directory file name string */
#define TAICOML_	9               /* Return command line buffer (COMLINE) */
#define TAIIDNT_	10              /* Return IDNT, revs, vers of initial load module */
#define TAISIFN_	11              /* Return standard input file name string */
#define TAISOFN_	12              /* Return standard output file name string */
#define TAILIST_	13              /* Return all tasks in the system */
#define TAIPC_		14              /* Return usable PC of task */
#define TAIENT_ 	15              /* Return task entry point */
#define TAICPUI_	16              /* Return last cpu id used by task and selection mask */
#define TAIUTIL_	17              /* Return task utilization time */
#define TAIMODS_	18              /* Get names of task's loaded modules */
#define TAIMODI_	19              /* Get extended info on a loaded module */
#define TAILLLOG_	20              /* Get names of task local logical names */
#define TAILGLOG_	21              /* Get names of task group logical names */
#define TAIXLLOG_	22              /* Get expansion of task local logical name */
#define TAIXGLOG_	23              /* Get expansion of task group logical name */
#define TAIUID_ 	24              /* Get task's user id */
#define TAIXQU_ 	25              /* Get task's execution quantum */
#define TAIMCNT_	26              /* Get task's module count */
#define TAIXSTA_	27              /* Return task extended status PKTRVALU */
#define TAITREE_	28              /* Return all task trees in system */
#define TAISTEM_	29              /* Return task's stem tasks */
#define TAILEAF_	30              /* Return task's leaf tasks */

/*
 *  Task Mode selection indicies (PKTSOPTS.B)
 */
#define TAMCPRI_	0               /* Change task priority (PKTPRIOR) */
#define TAMSWPR_	1               /* Define state of software privilege (SOP_SWPRV) */
#define TAMMKSP_	2               /* Mark position of SSP for re-START's (PKTISTSZ) */
#define TAMMKUS_	3               /* Mark position of USP for re-START's (PKTISTSZ) */
#define TAMAMON_	4               /* Add a monitor to a task (PKTMONNM) */
#define TAMDMON_	5               /* Delete a monitor from a task (PKTMONNM) */
#define TAMONLN_	6               /* Task going online */
#define TAMOFLN_	7               /* Task going offline */
#define TAMCPUS_	8               /* Modify cpu selection mask */
#define TAMCRIT_	9               /* Change critical state */
#define TAMCDIR_	10              /* Set task's current directory */
#define TAMXQU_ 	11              /* Set task's execution quantum */
#define TAMCPMD_	12              /* Change state of PMD flag */

/*
 * TASK/DEFINE and UNDEFINE subfunction types (PKTSOPTS.L)
 */
#define TDELLOG_	1               /* Task local logical name */
#define TDEGLOG_	2               /* Task global logical name */

/*
 *  Task definition bits (TCBSTAT)
 */
#define TSK_DEST	(1<<0)          /* Task is being DESTROY'ed */
#define TSK_DUMP	(1<<1)          /* Abort info dump on abnormal exit */
#define TSK_DBG 	(1<<2)          /* Debug option specified on CREATE */
#define TSK_LIB 	(1<<3)          /* Task is doing a shared library load */
#define TSK_ONLN	(1<<4)          /* Task is online */
#define TSK_RERUN	(1<<5)          /* Force dispatcher rerun */
#define TSK_CRIT	(1<<6)          /* Service queue created as critical queue */
#define TSK_STRTD	(1<<7)          /* Task has been START'ed */
#define TSK_HWPRV	(1<<8)          /* Hardware privileged ( SR = $2000 ) */
#define TSK_SWPRV	(1<<9)          /* Software privileged */
#define TSK_RESID (1<<10)           /* Task body is supervisor memory resident */
#define TSK_TRACE (1<<11)           /* Task trace request is pending */
#define TSK_AUTO  (1<<12)           /* Task is to be auto-START'ed after CREATE'ed */
#define TSK_ABOREQ (1<<13)          /* Task abort requested on next context switch */
#define TSK_ABOINH (1<<14)          /* Inhibit pending task abort request until cleared */
#define TSK_SHAR  (1<<15)           /* Task code body is shared */

/*
 *  Task extended status flags (TCBXSTAT.B)
 */
#define	TSX_LOAD 	(1<<0)          /* Task is doing a load */
#define	TSX_PMD	 	(1<<1)          /* Perform PMD on task abort */
#define	TSX_INS	 	(1<<2)          /* OS body already inserted (for trap 5) */
#define	TSX_3PM	 	(1<<3)          /* Third party monitor */
#define	TSX_PROP 	(1<<4)          /* Propagate tasks within tree by default */
#define	TSX_TREE 	(1<<5)          /* Task is head of new task tree */
#define	TSX_FLSH 	(1<<7)          /* Flush cache when ctx switched away from */

/*
 *  Device type codes (in LFDTYPE and LVDTYPE)
 */
#define TYPNULL_       1            /* "Null" type device */
#define TYPDISK_       2            /* Disk device */
#define TYPDISC_       2            /* alternate spelling for above */
#define TYPFILE_       3            /* File system disc file */
#define TYPCART_       4            /* Cartridge streamer tape */
#define TYPTAPE_       5            /* 9 Track tape drive */
#define TYPCONS_       6            /* System console (local) */
#define TYPHOST_       7            /* Host device */
#define TYPTERM_       8            /* Standard asynch terminal (VMS type) */
#define TYPX25_        9            /* X25 device */
#define TYPMEM_       10            /* Memory device */
#define TYPDIR_       11            /* Directory (LVOL list or other) */
#define TYPCODE_      12            /* Resident code module */
#define TYPDLC_       13            /* Data link layer handler (HDLC/SDLC) */
#define TYPBSC_       14            /* Bisync link layer */
#define TYPREC_       15            /* Record managemt */
#define TYPLOG_       16            /* Logging device */
#define TYPVFE_       17            /* VAX front end */
#define TYPINF_       18            /* INF - Interactive Network Facilities */
#define TYPRIOS_      19            /* RIOS - Remote I/O server */
#define TYPFILL_      20            /* FILL - Remote fill handler */
#define TYPQMGR_      21            /* QUEUE MANAGER */
#define TYPDSP_       22            /* Display system protocol handler */
#define TYPFAIL_      23            /* Failover handler */
#define TYPCIT_       24            /* CIT handler */
#define TYPLGN_       25            /* Login monitor */
#define TYPINFBASE_   32            /* Base for non-OS managed type numbers */
#define TYPUSERBASE_ 128            /* Base for non-managed type numbers */

/*
 *  KERNEL TRAP packet definition (complete packet)
 */

typedef struct __pkt
{                               /* MAXIMUM PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U8      pktfiller[114]; /* filler to reach largest packet size */
}
_PKT           , P_PKT;

typedef struct SYSTEM_TIME
{                               /* SYSTEM/TIME PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U16     pktsyyea;   /* Dayclock - Year */
    U8      pktsymon;   /* Dayclock - Month */
    U8      pktsyday;   /* Dayclock - Day */
    U8      pktsyhou;   /* Dayclock - Hour */
    U8      pktsymin;   /* Dayclock - Minute */
    U8      pktsysec;   /* Dayclock - Second */
    S8      pktsyzon;   /* Dayclock - Time Zone */
    U16     pktsyms;    /* Dayclock - Milliseconds */
}
system_time    , *p_system_time;

typedef struct SYSTEM_INFO
{                               /* SYSTEM/INFO PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U16     pktsyiln;   /* INFO  buffer length */
    U32     pktsyipt;   /* INFO  buffer address */
}
system_info    , *p_system_info;

typedef struct SYSTEM_MODE
{                               /* SYSTEM/MODE PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
}
system_mode    , *p_system_mode;

typedef struct SYSTEM_STDERR
{                               /* SYSTEM/STDERR PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U32     pktpktas;   /* STDERR Packet Address */
    U16     pkteb1ln;   /* Error buffer #1  Length */
    U32     pkteb1pt;   /* Error buffer #2  Address */
    U16     pkteb2ln;   /* Error buffer #2  Length */
    U32     pkteb2pt;   /* Error buffer #2  Address */
}
system_stderr  , *p_system_stderr;

typedef struct SYSTEM_DEFINE
{                               /* SYSTEM/DEFINE PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U16     pktdfnsz;   /* File name size */
#define pktdxquo  pktdfnsz      /* Default Execution quantum */
#define pktdqwdw  pktdfnsz      /* Default queue window */
#define pktdqpam  pktdfnsz      /* Default queue pre-allocated messages */
    U32     pktdfna;    /* File name pointer */
    U16     pktdsegln;  /* Segment table length */
    U32     pktdseg;    /* Segment table pointer */
    U8      pktlogn[16];    /* Logical name */
}
system_define  , *p_system_define;

typedef struct SYSTEM_UNDEFINE
{                               /* SYSTEM/UNDEFINE PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U16     pktdfnsz;   /* File name size */
    U32     pktdfna;    /* File name pointer */
    U16     pktdsegln;  /* Segment table length */
    U32     pktdseg;    /* Segment table pointer */
    U8      pktlogn[16];    /* Logical name */
}
system_undefine, *p_system_undefine;

typedef struct TASK_CREATE
{                               /* TASK/CREATE PACKET */
    U8      pktsvnum;   /* Trap packet  Service Number */
    U8      pktssnum;   /* Trap packet  Sub-Service Number */
    S16     pktccode;   /* Trap packet  Completion Code */
    U8      pktcmsel;   /* Completion mode selection */
    U8      pktgopts;   /* Trap packet  Global Options 8-bits */
    U32     pktsopts;   /* Service options */
    U32     pktiaddr;   /* Internal Address */
    U8      pktname[8]; /* User supplied name */
    U32     pktrvalu;   /* Returned Value */
    U32     pktcpuid;   /* CPU selection mask (-1 for all) */
    U8      pktprior;   /* Task priority in the range 1-254 */
    U8      pktfill01;  /* *** reserved *** */
    U32     pkttkopt;   /* Task execution options */
    U16     pktlmfln;   /* Length of following extension in bytes */
    U32     pktlmfpt;   /* Pointer to load module file name string */
    U16     pktwdrln;   /* Length of following extension in bytes */
    U32     pktwdrpt;   /* Pointer to working directory name string */
    U16     pktcomln;   /* Length of following extension in bytes */
    U32     pktcompt;   /* Pointer to command line */
    U16     pktsinln;   /* Length of following extension in bytes */
    U32     pktsinpt;   /* Pointer to standard input file string */
    U16     pktsouln;   /* Length of following extension in bytes */
    U32     pktsoupt;   /* Pointer to standard output file string */
    U16     pktmonpm;   /* Primary monitor messages filter mask */
    U16     pktmonmk;   /* Supplied monitor messages filter mask */
    U8      pktmonnm[8];    /* Name of queue for monitor messages */
    U32     pktpmkey;   /* Key for primary monitor messages */
    U32     pkttmkey;   /* Key for other(non-primary) monitor messages */
    U32     pktistsz;   /* Initial stack size in bytes */
    U16     pktsegln;   /* Length of following extension in bytes */
    U32     pktsegpt;   /* Segment table extension pointer */
    U8      pktident[10];   /* Program module IDNT */
    U8      pktrevsn;   /* Program module revision */
    U8      pktversn;   /* Program module version */
    U16     pktfill02;  /* used by pktuserid/pktxtern */
    U32     pktfill03;  /* " " " " " " " " " " " " "  */
#define	pktuserid 	pktident    /* Task's user id (16 bytes) */
    U8      pktshtsk[8];    /* Name of task whose apm id is to be shared */
    U16     pktxquo;    /* Task execution quantum in ms */
    U16     pktsqwdw;   /* Service queue control msg window */
    U16     pktsqthr;   /* Service queue control new msgs threshold */
    U16     pktsqpam;   /* Service queue control pre-allocated msgs */
#define pktxtern  pktident      /* Duplicate XDEF/missing XREF (32 bytes) */
    U16     pktiniln;   /* Length of following extension in bytes */
    U32     pktinipt;   /* Pointer to ini table (sop.boot only) */
    U32     pktdsecto;  /* Dsect offset in bytes (sop.boot only) */
}
task_create    , *p_task_create;

typedef struct TASK_DESTROY
{                               /* TASK/DESTROY PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktcpuid;   /* CPU selection mask (-1 for all) */
    U8   pktprior;   /* Task priority in the range 1-254 */
    U8   pktfill01;  /* *** reserved *** */
    U32  pkttkopt;   /* Task execution options */
    U16  pktlmfln;   /* Length of following extension in bytes */
    U32  pktlmfpt;   /* Pointer to load module file name string */
    U16  pktwdrln;   /* Length of following extension in bytes */
    U32  pktwdrpt;   /* Pointer to working directory name string */
    U16  pktcomln;   /* Length of following extension in bytes */
    U32  pktcompt;   /* Pointer to command line */
    U16  pktsinln;   /* Length of following extension in bytes */
    U32  pktsinpt;   /* Pointer to standard input file string */
    U16  pktsouln;   /* Length of following extension in bytes */
    U32  pktsoupt;   /* Pointer to standard output file string */
    U16  pktmonpm;   /* Primary monitor messages filter mask */
    U16  pktmonmk;   /* Supplied monitor messages filter mask */
    U8   pktmonnm[8];    /* Name of queue for monitor messages */
    U32  pktstops;   /* Status to be passed during STOP request */
}
task_destroy   , *p_task_destroy;

typedef struct TASK_STOP
{                               /* TASK/STOP PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktcpuid;   /* CPU selection mask (-1 for all) */
    U8   pktprior;   /* Task priority in the range 1-254 */
    U8   pktfill01;  /* *** reserved *** */
    U32  pkttkopt;   /* Task execution options */
    U16  pktlmfln;   /* Length of following extension in bytes */
    U32  pktlmfpt;   /* Pointer to load module file name string */
    U16  pktwdrln;   /* Length of following extension in bytes */
    U32  pktwdrpt;   /* Pointer to working directory name string */
    U16  pktcomln;   /* Length of following extension in bytes */
    U32  pktcompt;   /* Pointer to command line */
    U16  pktsinln;   /* Length of following extension in bytes */
    U32  pktsinpt;   /* Pointer to standard input file string */
    U16  pktsouln;   /* Length of following extension in bytes */
    U32  pktsoupt;   /* Pointer to standard output file string */
    U16  pktmonpm;   /* Primary monitor messages filter mask */
    U16  pktmonmk;   /* Supplied monitor messages filter mask */
    U8   pktmonnm[8];    /* Name of queue for monitor messages */
    U32  pktstops;   /* Status to be passed during STOP request */
}
task_stop      , *p_task_stop;

typedef struct TASK_EXCEPT
{                               /* TASK/EXCEPTION PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktexbad;   /* Address of exceptio information buffer */
    U32  pktexiad;   /* Exception vector */
    U8   pktexmsk[8];    /* Exception mask */
    U32  pktexa6;    /* Exception A6 address */
    U32  pktexsp;    /* Exception Stack Pointer */
}
task_except    , *p_task_except;

typedef struct TASK_DEBUG
{                               /* TASK/DEBUG PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktdbbuf;   /* buffer address */
    U16  pktdbbsz;   /* buffer size */
    U16  pktdbstep;  /* # of insts to step */
    U32  pktdbaddr;  /* Address in debugged task */
    U32  pktdbkey;   /* Debugger key */
}
task_debug     , *p_task_debug;


typedef struct TASK_DEFINE
{                               /* TASK/DEFINE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U16  pktdfnsz;   /* File name size */
    U32  pktdfna;    /* File name pointer */
    U16  pktdsegln;  /* Segment table length */
    U32  pktdseg;    /* Segment table pointer */
    U8   pktlogn[16];    /* Logical name */
}
task_define    , *p_task_define;

typedef struct TASK_UNDEFINE
{                               /* TASK/UNDEFINE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U16  pktdfnsz;   /* File name size */
    U32  pktdfna;    /* File name pointer */
    U16  pktdsegln;  /* Segment table length */
    U32  pktdseg;    /* Segment table pointer */
    U8   pktlogn[16];    /* Logical name */
}
task_undefine  , *p_task_undefine;

typedef struct TASK_HOLD
{                               /* TASK/HOLD PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
}
task_hold      , *p_task_hold;

typedef struct TASK_LOAD
{                               /* TASK/LOAD PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktcpuid;   /* CPU selection mask (-1 for all) */
    U8   pktprior;   /* Task priority in the range 1-254 */
    U8   pktfill01;  /* *** reserved *** */
    U32  pkttkopt;   /* Task execution options */
    U16  pktlmfln;   /* Length of following extension in bytes */
    U32  pktlmfpt;   /* Pointer to load module file name string */
    U16  pktwdrln;   /* Length of following extension in bytes */
    U32  pktwdrpt;   /* Pointer to working directory name string */
    U16  pktcomln;   /* Length of following extension in bytes */
    U32  pktcompt;   /* Pointer to command line */
    U16  pktsinln;   /* Length of following extension in bytes */
    U32  pktsinpt;   /* Pointer to standard input file string */
    U16  pktsouln;   /* Length of following extension in bytes */
    U32  pktsoupt;   /* Pointer to standard output file string */
    U16  pktmonpm;   /* Primary monitor messages filter mask */
    U16  pktmonmk;   /* Supplied monitor messages filter mask */
    U8   pktmonnm[8];    /* Name of queue for monitor messages */
    U32  pktpmkey;   /* Key for primary monitor messages */
    U32  pktresen;   /* Module entry point */
    U32  pktistsz;   /* Initial stack size in bytes */
    U16  pktsegln;   /* Length of following extension in bytes */
    U32  pktsegpt;   /* Segment table extension pointer */
    U8   pktident[10];   /* Program module IDNT */
    U8   pktrevsn;   /* Program module revision */
    U8   pktversn;   /* Program module version */
    U16  pktfill02;  /* used by pktuserid/pktxtern */
    U32  pktfill03;  /* " " " " " " " " " " " " "  */
    U8   pktshtsk[8];    /* Name of task whose apm id is to be shared */
    U16  pktxquo;    /* Task execution quantum in ms */
    U16  pktsqwdw;   /* Service queue control msg window */
    U16  pktsqthr;   /* Service queue control new msgs threshold */
    U16  pktsqpam;   /* Service queue control pre-allocated msgs */
    U16  pktiniln;   /* Length of following extension in bytes */
    U32  pktinipt;   /* Pointer to ini table (sop.boot only) */
    U32  pktdsecto;  /* Dsect offset in bytes (sop.boot only) */
}
task_load      , *p_task_load;

typedef struct TASK_UNLOAD
{                               /* TASK/UNLOAD PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
}
task_unload    , *p_task_unload;

typedef struct TASK_MODE
{                               /* TASK/MODE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktcpuid;   /* CPU selection mask (-1 for all) */
    U8   pktprior;   /* Task priority in the range 1-254 */
    U8   pktfill01;  /* *** reserved *** */
    U32  pkttkopt;   /* Task execution options */
    U16  pktlmfln;   /* Length of following extension in bytes */
    U32  pktlmfpt;   /* Pointer to load module file name string */
    U16  pktwdrln;   /* Length of following extension in bytes */
    U32  pktwdrpt;   /* Pointer to working directory name string */
    U16  pktcomln;   /* Length of following extension in bytes */
    U32  pktcompt;   /* Pointer to command line */
    U16  pktsinln;   /* Length of following extension in bytes */
    U32  pktsinpt;   /* Pointer to standard input file string */
    U16  pktsouln;   /* Length of following extension in bytes */
    U32  pktsoupt;   /* Pointer to standard output file string */
    U16  pktmonpm;   /* Primary monitor messages filter mask */
    U16  pktmonmk;   /* Supplied monitor messages filter mask */
    U8   pktmonnm[8];    /* Name of queue for monitor messages */
    U32  pktpmkey;   /* Key for primary monitor messages */
    U32  pktresen;   /* Module entry point */
    U32  pktistsz;   /* Initial stack size in bytes */
    U16  pktsegln;   /* Length of following extension in bytes */
    U32  pktsegpt;   /* Segment table extension pointer */
    U8   pktident[10];   /* Program module IDNT */
    U8   pktrevsn;   /* Program module revision */
    U8   pktversn;   /* Program module version */
    U16  pktfill02;  /* used by pktuserid/pktxtern */
    U32  pktfill03;  /* " " " " " " " " " " " " "  */
    U8   pktshtsk[8];    /* Name of task whose apm id is to be shared */
    U16  pktxquo;    /* Task execution quantum in ms */
    U16  pktsqwdw;   /* Service queue control msg window */
    U16  pktsqthr;   /* Service queue control new msgs threshold */
    U16  pktsqpam;   /* Service queue control pre-allocated msgs */
    U16  pktiniln;   /* Length of following extension in bytes */
    U32  pktinipt;   /* Pointer to ini table (sop.boot only) */
    U32  pktdsecto;  /* Dsect offset in bytes (sop.boot only) */
}
task_mode      , *p_task_mode;

typedef struct TASK_INFO
{                               /* TASK/INFO PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
    U32  pktcpuid;   /* CPU selection mask (-1 for all) */
    U8   pktprior;   /* Task priority in the range 1-254 */
    U8   pktfill01;  /* *** reserved *** */
    U32  pkttkopt;   /* Task execution options */
    U16  pktlmfln;   /* Length of following extension in bytes */
    U32  pktlmfpt;   /* Pointer to load module file name string */
    U16  pktwdrln;   /* Length of following extension in bytes */
    U32  pktwdrpt;   /* Pointer to working directory name string */
    U16  pktcomln;   /* Length of following extension in bytes */
    U32  pktcompt;   /* Pointer to command line */
    U16  pktsinln;   /* Length of following extension in bytes */
    U32  pktsinpt;   /* Pointer to standard input file string */
    U16  pktsouln;   /* Length of following extension in bytes */
    U32  pktsoupt;   /* Pointer to standard output file string */
    U16  pktmonpm;   /* Primary monitor messages filter mask */
    U16  pktmonmk;   /* Supplied monitor messages filter mask */
    U8   pktmonnm[8];    /* Name of queue for monitor messages */
    U32  pktpmkey;   /* Key for primary monitor messages */
    U32  pktresen;   /* Module entry point */
    U32  pktistsz;   /* Initial stack size in bytes */
    U16  pktsegln;   /* Length of following extension in bytes */
    U32  pktsegpt;   /* Segment table extension pointer */
    U8   pktident[10];   /* Program module IDNT */
    U8   pktrevsn;   /* Program module revision */
    U8   pktversn;   /* Program module version */
    U16  pktfill02;  /* used by pktuserid/pktxtern */
    U32  pktfill03;  /* " " " " " " " " " " " " "  */
    U8   pktshtsk[8];    /* Name of task whose apm id is to be shared */
    U16  pktxquo;    /* Task execution quantum in ms */
    U16  pktsqwdw;   /* Service queue control msg window */
    U16  pktsqthr;   /* Service queue control new msgs threshold */
    U16  pktsqpam;   /* Service queue control pre-allocated msgs */
    U16  pktiniln;   /* Length of following extension in bytes */
    U32  pktinipt;   /* Pointer to ini table (sop.boot only) */
    U32  pktdsecto;  /* Dsect offset in bytes (sop.boot only) */
}
task_info      , *p_task_info;

typedef struct TASK_RELEASE
{                               /* TASK/RELEASE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32  pktsopts;   /* Service options */
    U32  pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32  pktrvalu;   /* Returned Value */
}
task_release   , *p_task_release;

typedef struct TASK_START
{                               /* TASK/START PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Service options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
task_start     , *p_task_start;

typedef struct MEMORY_CREATE
{                               /* MEMORY/CREATE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktsopts;   /* Service Specificoptions */
    U16  pktmopts;   /* Memory Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktmsize;   /* Size in bytes */
}
memory_create  , *p_memory_create;

typedef struct MEMORY_DESTROY
{                               /* MEMORY/DESTROY PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktsopts;   /* Service Specificoptions */
    U16  pktmopts;   /* Memory Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
memory_destroy , *p_memory_destroy;

typedef struct MEMORY_EXTRACT
{                               /* MEMORY/EXTRACT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktsopts;   /* Service Specificoptions */
    U16  pktmopts;   /* Memory Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
memory_extract , *p_memory_extract;

typedef struct MEMORY_INFO
{                               /* MEMORY/INFO PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktsopts;   /* Service Specificoptions */
    U16  pktmopts;   /* Memory Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktmsize;   /* Size in bytes */
    U32   pktmaddr;   /* Addr of info buffer or absolute rqst */
    U8   pktmtask[8];    /* Task name for info service */
}
memory_info    , *p_memory_info;

typedef struct MEMORY_INSERT
{                               /* MEMORY/INSERT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktsopts;   /* Service Specificoptions */
    U16  pktmopts;   /* Memory Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
memory_insert  , *p_memory_insert;

typedef struct MEMORY_MODE
{                               /* MEMORY/MODE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktsopts;   /* Service Specificoptions */
    U16  pktmopts;   /* Memory Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
memory_mode    , *p_memory_mode;

typedef struct IO_MOUNT
{                               /* IO/MOUNT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U8   pktdvtyp;   /* Device Type */
    U8   pktmtopt;   /* Mount Options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U8   pktmtsqn[8];    /* Mount Service Queue Name */
}
io_mount       , *p_io_mount;


typedef struct IO_CREATE
{                               /* IO/CREATE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_create      , *p_io_create;

typedef struct IO_CRDIR
{                               /* IO/CRDIR PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_crdir       , *p_io_crdir;

typedef struct IO_DESTROY
{                               /* IO/DESTROY PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_destroy     , *p_io_destroy;

typedef struct IO_OPEN
{                               /* IO/OPEN PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_open        , *p_io_open;

typedef struct IO_MODE
{                               /* IO/MODE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U8   pktimtyp;   /* Info/Mode Type */
    U8   pktimopt;   /* Info/Mode options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_mode        , *p_io_mode;

typedef struct IO_INFO
{                               /* IO/INFO PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U8   pktimtyp;   /* Info/Mode Type */
    U8   pktimopt;   /* Info/Mode options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_info        , *p_io_info;

typedef struct IO_EXCHANGE
{                               /* IO/EXCHANGE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U8   pktextyp;   /* Exchange Type */
    U8   pktexopt;   /* Exchange options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
    U16  pktpbsz2;   /* Size of second param buffer (exchange) */
    U32   pktparm2;   /* Addr of second param buffer (exchange) */
}
io_exchange    , *p_io_exchange;

typedef struct IO_RENAME
{                               /* IO/RENAME PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktnnsiz;   /* New Name buffer size */
    U32   pktnname;   /* New Name string pointer */
    U16  pktibufo;   /* Offset into info buffer */
    U16  pktiwdw;    /* Requested input window size */
    U16  pktowdw;    /* Requested output window size */
    U32   pktuskey2;  /* Second User key field */
}
io_rename      , *p_io_rename;

typedef struct IO_READ
{                               /* IO/READ PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U32   pktbytct;   /* Requested byte count */
    U32   pktbufad;   /* Primary buffer address */
    U32   pktretct;   /* Actual returned byte count */
    U32   pktfpos;    /* Requested File Position */
    U32   pktfposm;   /* File Position Modifier */
    U32   pktbf2ct;   /* Secondary buffer byte count */
    U32   pktbf2ad;   /* Secondary buffer address */
    U16  pktdpbsz;   /* Device dependent parameter block size */
    U32   pktdpbad;   /* Device dependent parameter block addr */
}
io_read        , *p_io_read;

typedef struct IO_WRITE
{                               /* IO/WRITE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U32   pktbytct;   /* Requested byte count */
    U32   pktbufad;   /* Primary buffer address */
    U32   pktretct;   /* Actual returned byte count */
    U32   pktfpos;    /* Requested File Position */
    U32   pktfposm;   /* File Position Modifier */
    U32   pktbf2ct;   /* Secondary buffer byte count */
    U32   pktbf2ad;   /* Secondary buffer address */
    U16  pktdpbsz;   /* Device dependent parameter block size */
    U32   pktdpbad;   /* Device dependent parameter block addr */
}
io_write       , *p_io_write;

typedef struct IO_DONE
{                               /* IO/DONE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktdssk;    /* System key (caller's TCB address) */
    U16  pktducc;    /* Completion code (to be returned) */
    U32   pktdurv;    /* Return value */
    U32   pktdupa;    /* User packet address */
    U32   pktdatc;    /* Actual returned byte count */
    U32   pktdfpos;   /* File Position */
    U8   pktdsqn[8]; /* Service queue name */
    U8   pktdiqn[8]; /* Input queue name */
    U8   pktdoqn[8]; /* Output queue name */
    U8   pktdlfn[8]; /* LFN to be redirected (sop.redir) */
}
io_done        , *p_io_done;

typedef struct IO_DONE_OPEN
{                               /* IO/DONE for OPEN PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktdssk;    /* System key (caller's TCB address) */
    U16  pktducc;    /* Completion code (to be returned) */
    U32   pktdurv;    /* Return value */
    U32   pktdupa;    /* User packet address */
    U32   pktdhsp;    /* Handler specified key */
    U16  pktdiws;    /* Input window size */
    U16  pktdows;    /* Output window size */
    U8   pktdsqn[8]; /* Service queue name */
    U8   pktdiqn[8]; /* Input queue name */
    U8   pktdoqn[8]; /* Output queue name */
    U8   pktdlfn[8]; /* LFN to be redirected (sop.redir) */
}
io_done_open   , *p_io_done_open;

typedef struct IO_CANCEL
{                               /* IO/CANCEL PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
}
io_cancel      , *p_io_cancel;

typedef struct IO_CLOSE
{                               /* IO/CLOSE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
}
io_close       , *p_io_close;

typedef struct IO_DISMOUNT
{                               /* IO/DISMOUNT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
}
io_dismount    , *p_io_dismount;

typedef struct IO_INTERRUPT
{                               /* IO/INTERRUPT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
}
io_interrupt   , *p_io_interrupt;

typedef struct IO_RESET
{                               /* IO/RESET PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U16  pktssopt;   /* Service Specific options */
    U16  pkthsopt;   /* Handler specific Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktuskey;   /* User key field */
    U16  pktfnsiz;   /* File name buffer size */
    U32   pktfname;   /* File name string pointer */
    U16  pktpbsiz;   /* Parameter block size */
    U32   pktparam;   /* Parameter block address */
}
io_reset       , *p_io_reset;

typedef struct QUEUE_CREATE
{                               /* QUEUE/CREATE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U8   pktnqnam[8];    /* Service queue  Name */
    U16  pktquewdw;  /* Control: depth limit */
    U16  pktquethr;  /* Control: new message threshold */
    U16  pktquepam;  /* Control: pre-allocated messages */
    U32   pktqdata[8];    /* Data Buffer */
}
queue_create   , *p_queue_create;

typedef struct QUEUE_DESTROY
{                               /* QUEUE/DESTROY PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
queue_destroy  , *p_queue_destroy;

typedef struct QUEUE_INFO
{                               /* QUEUE/INFO PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U8   pktqionm[8];    /* Owner Name */
    U16  pktqista;   /* Status (que.xxx) */
    U32   pktqinqa;   /* Service Queue Address */
    U8   pktqinqn[8];    /* Service Queue Name */
    U32   pktqimct;   /* Message Count */
    U16  pktsnlln;   /* Name list length */
    U32   pktsnlpt;   /* Name list pointer */
    U16  pktqiwdw;   /* Window size */
    U16  pktqithr;   /* Threshold */
}
queue_info     , *p_queue_info;

typedef struct QUEUE_MODE
{                               /* QUEUE/MODE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U8   pktnqnam[8];    /* Service queue  Name */
    U16  pktquewdw;  /* Control: depth limit */
}
queue_mode     , *p_queue_mode;

typedef struct QUEUE_WRITE
{                               /* QUEUE/WRITE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16           pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U8   pktqprio;   /* Priority of queue entry */
    U8   pktqtype;   /* Type of queue entry */
    U16  pktqueop;   /* Sub-service options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pktqfill[3];    /* Filler */
    U32   pktqdata[8];    /* Data Buffer */
}
queue_write    , *p_queue_write;

typedef struct QUEUE_READ
{                               /* QUEUE/READ PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U32   pktqdata[8];    /* Data Buffer */
}
queue_read     , *p_queue_read;

typedef struct QRD_ION
{                               /* QUEUE/READ IO NOTIFICATION PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U8   ionsvnum;   /* Service number */
    U8   ionssnum;   /* Sub-service number */
    S16  ionccode;   /* Completion code */
    U32   ionrvalu;   /* Returned value */
    U32   ionupkta;   /* User packet address */
    U32   ionuskey;   /* User specified key */
    U32   ionatcnt;   /* Actual transfered byte count (R/W) */
    U16  ioniwind;   /* Actual input window size  (open) */
    U16  ionowind;   /* Actual output window size (open) */
}
qr_ion         , *p_qrd_ion;

typedef struct QRD_IOR
{                               /* QUEUE/READ IO REQUEST PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U8   iorssnum;   /* Subservice number */
    U8   iorflags;   /* Packet flags */
    U32   iorupkad;   /* User packet address */
    U32   iorsskey;   /* System supplied key */
    union
    {
        struct
        {
            U32   iorhskey;   /* Handler specified key */
            U32   iorfpos;    /* File position */
            U32   iorbfad;    /* Buffer address */
            U32   iorbcnt;    /* Requested byte count */
            U16  iorhsopt;   /* Handler specified options */
            U16  iorfiller;  /* ** alignment ** */
        }
        file;
        struct
        {
            U8   iorvolnm[8];    /* Logical volume name */
            U16  iorfnasz;   /* File name buffer size */
            U32   iorfnapt;   /* File name buffer pointer */
            U16  iorfn2sz;   /* New file name buffer size (for RENAME) */
            U32   iorfn2pt;   /* New file name buffer pointer */
        }
        name;
    }
    fn;
    union
    {
        U16  iorssopt;   /* Subservice options */
        struct
        {
            U8   iorimtyp;   /* Info/Mode type field */
            U8   iorimopt;   /* Info/Mode options/class in bits 0-1 */

        }
        infmode;

    }
    im;
}
qr_ior         , *p_qrd_ior;

typedef struct QRD_EXCEPT
{                               /* QUEUE/READ EXCEPTION PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U32   hexupkta;   /* User packet address */
    U32   hexuskey;   /* User specified key */
    U8   hextype;    /* Exception type */
    U8   hexvalu[2]; /* Exception return value */
    U8   hexhand;    /* Originating handler */
    U8   hexsname[16];   /* Simple file name */
    U32   hexdata;    /* Handler defined data word */
}
qrd_except     , *p_qrd_except;

typedef struct QRD_TASKMON
{                               /* QUEUE/READ TASK MONITOR PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U8   mmgtype;    /* Monitor   Message type (MMT****.) */
    U8   mmgstat;    /* Monitor   Message status (MMS****.) */
    U8   mmgsvnum;   /* Monitor   Associated service number */
    U8   mmgssnum;   /* Monitor   Associated sub-service number */
    U16  mmgccode;   /* Monitor   Associated completion code */
    U32   mmgrvalu;   /* Monitor   Associated returned value */
    U8   mmgname[8]; /* Monitor   Associated name */
    U32   mmgkey;     /* Monitor   Associated key */
    U32   mmgutil;    /* Monitor   Utilization (destroy only) (sys only) */
}
qr_taskmon     , *p_qrd_taskmon;

typedef struct QRD_DEBUG
{                               /* QUEUE/READ DEBUG PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U8   dbmtype;    /* Debug   Message type (DBM****.) */
    U8   dbmaux;     /* Debug      Aux info */
    U16  dbmsr;      /* Debug      Status register */
    U32   dbmpc;      /* Debug      Program counter */
    U32   dbmkey;     /* Debug      Debugger specified key */
    U32   dbmaddr;    /* Debug   Type 0 violation addr */
    U16  dbminst;    /* Debug   Type 0 instction */
    U16  dbmfunct;   /* Debug      Type 0 function code */
}
qr_debug       , *p_qrd_debug;

typedef struct QRD_NOTIFY
{                               /* QUEUE/READ GENERIC NOTIFY PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U8   notsvnum;   /* NOTIFY     Service number */
    U8   notssnum;   /* NOTIFY     Sub-service number */
    U16  notccode;   /* NOTIFY     Completion code */
    U32   notrvalu;   /* NOTIFY     Return value */
    U32   notpktad;   /* NOTIFY     Request packet address */
    U32   notuskey;   /* NOTIFY     Possible user supplied key */
}
qr_notify      , *p_qrd_notify;

typedef struct QRD_CPABORT
{                               /* QUEUE/READ CP ABORT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U16  tmaabst;    /* CP ABORT  CP abort status */
    U16  tmachan;    /* CP ABORT  Simplex channel number */
    U32   tmakey;     /* CP ABORT  User key from CHCB create */
}
qr_cpabort     , *p_qrd_cpabort;

typedef struct QRD_CPINTER
{                               /* QUEUE/READ CP INTERRUPT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U32   tmivect;    /* CP INTERRUPT  CP vector number */
    U32   tmistat;    /* CP INTERRUPT  CP status at time of int */
    U32   tmichan;    /* CP INTERRUPT  Simplex channel number */
    U32   tmikey;     /* CP INTERRUPT  User key from AQ create */
}
qr_cpinter     , *p_qrd_cpinter;

typedef struct QRD_CPAQM
{                               /* QUEUE/READ CP ACTIVITY QUEUE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16           pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U32   tmqeidi;    /* CP QUEUE  EI/DI entry from queue */
    U32   tmqkey;     /* CP QUEUE  User key from CHCB create */
}
qr_cpaqm       , *p_qrd_cpaqm;

typedef struct QRD_SEMABORT
{                               /* QUEUE/READ SEMAPHORE ABORT PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U8   pktqrpri;   /* Incoming message  Priority */
    U8   pktqrtyp;   /* Incoming message  Type */
    U16  pktqrmct;   /* Outstanding message count */
    U8   pktqrqnm[8];    /* Reply queue  Name */
    U32   pktqrqad;   /* Reply queue  Address */
    U8   semname[8]; /* Name of semaphore owned by task */
    U8   semtskn[8]; /* Name of task that own semaphore */
}
qr_semabort    , *p_qrd_semabort;

#ifndef UNIX
#ifndef _WINNT
/* NOTE: Timer structures cannot be defined when building host-based code
 *       due to redefinition conflicts with host-specific timer libraries
 */
typedef struct TIMER_CREATE
{                               /* TIMER/CREATE PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
timer_create   , *p_timer_create;

typedef struct TIMER_DESTROY
{                               /* TIMER/DESTROY PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
timer_destroy  , *p_timer_destroy;

typedef struct TIMER_START
{                               /* TIMER/START PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
    U32   pkttival;   /* Timer initial value */
    U32   pkttikey;   /* User supplied key */
}
timer_start    , *p_timer_start;

typedef struct TIMER_STOP
{                               /* TIMER/STOP PACKET */
    U8   pktsvnum;   /* Trap packet  Service Number */
    U8   pktssnum;   /* Trap packet  Sub-Service Number */
    S16  pktccode;   /* Trap packet  Completion Code */
    U8   pktcmsel;   /* Completion mode selection */
    U8   pktgopts;   /* Trap packet  Global Options 8-bits */
    U32   pktsopts;   /* Trap packet  Service Options */
    U32   pktiaddr;   /* Internal Address */
    U8   pktname[8]; /* User supplied name */
    U32   pktrvalu;   /* Returned Value */
}
timer_stop     , *p_timer_stop;
#endif /* _WINNT */
#endif /* UNIX */

typedef union
{
    _PKT            pkt;        /* Minimum Kernel Packet */
    system_time     systemTime; /* SYSTEM/TIME PACKET */
    system_info     systemInfo; /* SYSTEM/INFO PACKET */
    system_mode     systemMode; /* SYSTEM/MODE PACKET */
    system_define   systemDefine;   /* SYSTEM/DEFINE PACKET */
    system_undefine systemUndefine; /* SYSTEM/UNDEFINE PACKET */
    system_stderr   systemStderr;   /* SYSTEM/STDERR PACKET */
    task_create     taskCreate; /* TASK/CREATE PACKET */
    task_destroy    taskDestroy;    /* TASK/DESTROY PACKET */
    task_stop       taskStop;   /* TASK/STOP PACKET */
    task_except     taskExcept; /* TASK/EXCEPTION PACKET */
    task_define     taskDefine; /* TASK/DEFINE PACKET */
    task_undefine   taskUndefine;   /* TASK/UNDEFINE PACKET */
    task_hold       taskHold;   /* TASK/HOLD PACKET */
    task_load       taskLoad;   /* TASK/LOAD PACKET */
    task_unload     taskUnload; /* TASK/UNLOAD PACKET */
    task_mode       taskMode;   /* TASK/MODE PACKET */
    task_info       taskInfo;   /* TASK/INFO PACKET */
    task_debug      taskDebug;  /* TASK/DEBUG PACKET */
    task_release    taskRelease;    /* TASK/RELEASE PACKET */
    task_start      taskStart;  /* TASK/START PACKET */
    memory_create   memoryCreate;   /* MEMORY/CREATE PACKET */
    memory_destroy  memoryDestroy;  /* MEMORY/DESTROY PACKET */
    memory_extract  memoryExtract;  /* MEMORY/EXTRACT PACKET */
    memory_info     memoryInfo; /* MEMORY/INFO PACKET */
    memory_insert   memoryInsert;   /* MEMORY/INSERT PACKET */
    memory_mode     memoryMode; /* MEMORY/MODE PACKET */
    io_mount        ioMount;    /* IO/MOUNT PACKET */
    io_create       ioCreate;   /* IO/CREATE PACKET */
    io_crdir        ioCrdir;    /* IO/CRDIR PACKET */
    io_destroy      ioDestroy;  /* IO/DESTROY PACKET */
    io_open         ioOpen;     /* IO/OPEN PACKET */
    io_mode         ioMode;     /* IO/MODE PACKET */
    io_info         ioInfo;     /* IO/INFO PACKET */
    io_exchange     ioExchange; /* IO/EXCHANGE PACKET */
    io_rename       ioRename;   /* IO/RENAME PACKET */
    io_read         ioRead;     /* IO/READ PACKET */
    io_write        ioWrite;    /* IO/WRITE PACKET */
    io_done         ioDone;     /* IO/DONE PACKET */
    io_done_open    ioDoneOpen; /* IO/DONE for OPEN PACKET */
    io_cancel       ioCancel;   /* IO/CANCEL PACKET */
    io_close        ioClose;    /* IO/CLOSE PACKET */
    io_dismount     ioDismount; /* IO/DISMOUNT PACKET */
    io_interrupt    ioInterrupt;    /* IO/INTERRUPT PACKET */
    io_reset        ioReset;    /* IO/RESET PACKET */
    queue_create    queueCreate;    /* QUEUE/CREATE PACKET */
    queue_destroy   queueDestroy;   /* QUEUE/DESTROY PACKET */
    queue_info      queueInfo;  /* QUEUE/INFO PACKET */
    queue_mode      queueMode;  /* QUEUE/MODE PACKET */
    queue_write     queueWrite; /* QUEUE/WRITE PACKET */
    queue_read      queueRead;  /* QUEUE/READ PACKET */
    qr_ion          qrdIONotif; /* QUEUE/READ IO Notification PACKET */
    qr_ior          qrdIORequest;   /* QUEUE/READ IO Request PACKET */
    qrd_except      qrdExcept;  /* QUEUE/READ Exception PACKET */
    qr_taskmon      qrdTaskmon; /* QUEUE/READ Task Monitor PACKET */
    qr_debug        qrdDebug;   /* QUEUE/READ Debug PACKET */
    qr_cpabort      qrdCPAbort; /* QUEUE/READ CP Abort PACKET */
    qr_cpinter      qrdCPInter; /* QUEUE/READ CP Interrupt PACKET */
    qr_cpaqm        qrdCPAqm;   /* QUEUE/READ CP AQM PACKET */
    qr_semabort     qrdSemAbort;    /* QUEUE/READ Semaphore Abort PACKET */
#ifndef UNIX
#ifndef _WINNT
/* NOTE: Timer structures cannot be defined when building host-based code
 *       due to redefinition conflicts with host-specific timer libraries
 */
    timer_create    timerCreate;    /* TIMER/CREATE PACKET */
    timer_destroy   timerDestroy;   /* TIMER/DESTROY PACKET */
    timer_start     timerStart; /* TIMER/START PACKET */
    timer_stop      timerStop;  /* TIMER/STOP PACKET */
#endif /* _WINNT */
#endif /* UNIX */
}
krnl_pkt       , *p_krnl_pkt;


#define PKTSIZE 26                  /* Trap packet MINIMUM size */
#define PKTIOMSZ (PKTSIZE+4)        /* Minimal IO packet size */
#define PKTSZSYS 0x36               /* size of system packet */
#define PKTSZTAS 0x8c               /* size of task packet */
#define PKTSZMEM 0x2a               /* size of memory packet */
#define PKTSZIO  0x50               /* size of IO packet */
#define PKTSZQUE 0x46               /* size of queue packet */
#define PKTSZSEM 0x22               /* size of semaphore packet */
#define PKTSZTIM 0x22               /* size of timer packet */
#define PKTSZINT 0x34               /* size of interface packet */

/*
 *  IO request packet to handler flag values:
 */
#define IOR_NAME	(1<<0)          /* Name server type IOR message */
#define IOR_OLBC 	(1<<1)          /* OLBC request */

/*
 *  Valid values for hexhand:
 */
#define HEXHASY_	1               /* Async */
#define HEXHX25_	2               /* X_25 */
#define HEXHDLC_	3               /* Data link handler (HDLC/SDLC) */
#define HEXHBSC_	4               /* Bisync link handler */
#define HEXVFE_ 	5               /* VAX front end */
#define HEXRIOS_	6               /* RIOS - Remote I/O Server */
#define HEXALARM_	7               /* Alarm handler exception */

/*
 *  System internal event message data
 */
struct __sie
{
    U8   sietype;    /* System event message type (sitxxxx.) */
    U8   ___filie;   /* *** alignment *** */
    void           *sieaddr;    /* Associated address */
    U32   siecont;    /* Control register at time of exception */
    U32   siedata;    /* Data register at time of exception */
};

#define SIESIZE 	sizeof(struct __sie)

/*
 *  SYSTEM/INFO/SINLIBS structure.
 */
struct __system_info_sinlibs
{                               /* this doesn't exist in cpkuser.in */
    S8            libname[8]; /* Shared library name */
};

/*
 *  SYSTEM/INFO/SINLIBX structure.
 */
struct __system_info_sinlibx
{                               /* this doesn't exist in cpkuser.in */
    S8            xdefname[10];   /* Xdef name */
    void           *xdefaddr;   /* Xdef address */
};

/*
 *  SYSTEM/INFO/SINSLMS structure.
 */
struct __system_info_sinslms
{                               /* this doesn't exist in cpkuser.in */
    S8            libname[8]; /* Shared library name */
};

/*
 *  SYSTEM/INFO/SINLSLOG structure.
 */
struct __system_info_sinlslog
{                               /* this doesn't exist in cpkuser.in */
    S8            libname[16];    /* System level logical name */
};

/*
 *  MEMORY/INFO/MIRGNS return structure.
 */
struct __memory_info_mirgns
{                               /* this doesn't exist in cpkuser.in */
    S8            name[8];    /* Shared region name */
    U16  accessmask; /* Access/sharing type mask. */
    void           *region;     /* Region's starting address. */
    U32   size;       /* Size of memory region. */
};

/*
 *  MEMORY/INFO/MITASKS return structure.
 */
struct __memory_info_mitasks
{                               /* this doesn't exist in cpkuser.in */
    S8            name[8];    /* Shared region name */
};

/*
 *  MEMORY/INFO/MIFREBLK return structure.
 */
struct __memory_info_mifreblk
{                               /* this doesn't exist in cpkuser.in */
    void           *region;     /* Region's starting address. */
    U32   size;       /* Size of memory region. */
};

/*
 *  KRNL System Service and Sub-service call numbers
 */

#define KRNLTRAP	10              /* 68000 TRAP number used for KRNL services */

/*  Service numbers
 */
#define SYSTEM_      1
#define TASK_        2
#define MEMORY_      3
#define IO_          4
#define QUEUE_       5
#define SEMAPHORE_   6
#define TIMER_       7
#define INTERFACE_   8
#define SESSION_     9

/*  Sub-service numbers
 */
#define INFO_       0               /* All services */
#define TIME_       1               /* SYSTEM get/set system time and date */
#define CREATE_     1               /* All services */
#define DESTROY_    2               /* All services */
#define HOLD_       3               /* TASK */
#define WAIT_       3               /* SEMAPHORE - wait for use of a semaphore */
#define STDERR_     3               /* SYSTEM - get standard error text */
#define CANCEL_     3               /* IO - request cancellation of NS operations */
#define RELEASE_    4               /* TASK - allow a 'held' task to run */
#define SIGNAL_     4               /* SEMAPHORE - release use of the sempahore */
#define EXCHANGE_   4               /* IO - bidirectional INFO call */
#define START_      5               /* TASK - Put existing task into execution */
                      /* TIMER - Start a count down timer */
#define INTER_      5               /* IO - out of band request to handler */
#define STOP_       6               /* TASK - Discontinue execution of a task */
                      /* TIMER - Stop timer and get remaining time */
#define RESET_      6               /* IO - request cancellation of DS operations */
#define MODE_       7               /* All services */
#define OPEN_       8               /* IO - Allow access to a file or device */
#define INSERT_     8               /* MEMORY - All access to a shared memory region */
#define LOAD_       8               /* TASK - Have code body of task loaded in memory */
                      /* INTERFACE - load a ?CP device */
#define CLOSE_      9               /* IO - Disallow further reference to file or device */
#define EXTRACT_    9               /* MEMORY -Disallow further reference to shared memory */
#define UNLOAD_     9               /* TASK - Unload a code body */
#define READ_      10               /* IO, QUEUE - Read from file, device/queue */
#define VPORTCFG_  10               /* INTERFACE - Virt Port Config */
#define WRITE_     11               /* IO, QUEUE - Write to file, device or queue */
#define TXCHK_     12               /* INTERFACE [INTERNAL] - Check TX Queue for sends */
#define RXSTART_   13               /* INTERFACE [INTERNAL] - RX notification handler starting */
#define EXCEPTION_ 14               /* TASK - define exceptions to be processed by a task */
#define DISMOUNT_  14               /* IO - Make a volume inaccessable */
#define MOUNT_     15               /* IO - Make a volume accessable */
#define DEBUG_     15               /* TASK - Debug subservices */
#define RENAME_    16               /* IO - Change the name of a file */
#define VRDEF_     16               /* INTERFACE - Virt Res Define */
#define VRCFG_     17               /* INTERFACE - Virt Res Config */
#define NVCREATE_  18               /* INTERFACE - Named Vport Create */
#define SETCD_     18               /* IO - Set current directory */
#define NVDELETE_  19               /* INTERFACE - Named Vport Destroy */
#define CRDIR_     19               /* IO - Create a directory in the system */
#define NVATTACH_  20               /* INTERFACE - Named Vport Attach */
#define IODONE_    20               /* IO - Signal completion of a logical operation */
#define DEFINE_    21               /* SYSTEM, TASK */
#define UNDEFINE_  22               /* SYSTEM, TASK */

/*
 *  Execptions that can be registered for
 *	TASK/EXCEPTION
 */
#define XT_BUSERR    (1<<0)         /* Bus Error (Not on series 1) */
#define XT_ADDRESS	(1<<1)          /* Address error */
#define XT_APMVIOL	(1<<2)          /* APM violation */
#define XT_MCUVIOL	(1<<3)          /* MCU violation */
#define XT_ILLEGAL	(1<<4)          /* Illegal insruction */
#define XT_PRIV      (1<<5)         /* Privledge violation */
#define XT_ZERODIV	(1<<7)          /* Division by zero */
#define XT_CHK       (1<<10)        /* CHK */
#define XT_TRAPV     (1<<11)        /* TRAPV */
#define XT_LINEA     (1<<12)        /* $Axxx instruction trap */
#define XT_LINEF     (1<<13)        /* $Fxxx instruction trap */
#define XT_TRAP0     (1<<14)        /* TRAP #0 */
#define XT_TRAP1     (1<<15)        /* TRAP #1 */
#define XT_TRAP2     (1<<16)        /* TRAP #2 */
#define XT_TRAP3     (1<<17)        /* TRAP #3 */
#define XT_TRAP4     (1<<18)        /* TRAP #4 */
#define XT_TRAPB     (1<<23)        /* TRAP #11 */
#define XT_TRAPC     (1<<24)        /* TRAP #12 */
#define XT_TRAPD     (1<<25)        /* TRAP #13 */
#define XT_TRAPE     (1<<26)        /* TRAP #14 */
#define XT_TRAPF     (1<<27)        /* TRAP #15 */

/*
 * Exception block for receiving exception info
 */
struct __exb
{
    void           *exbpc;      /* PC at exception time */
    U8   exbccr;     /* CCR at exception time */
    U8   exbtype;    /* Exception type */

    /* The folowing is returned for group 0 exceptions only */
    void           *exbaddr;    /* Address reference that caused exception */
    U16  exbfunct;   /* Function codes */
    U16  exbinstr;   /* Instruction */
    U32   exba6ret;   /* Value of a6 at exception (if sop.regs) */
    U32   exbspret;   /* Value of sp at exception */
};

#define EXBSIZE 	sizeof(struct __exb)

/*
 * System info page definitions
 */
#define SYSINFMSH_   '$Sys'         /* Name of shared region */
#define SYSINFLSH_	'Info'

/* TX1000 Configuration EEPROM contents */

/* The National Semiconductor NM93C06 EEPROM has 16 register of 16 bits each */
typedef struct
{
    U16  signrev;    /*  1: Signature */
#define TX1000_FORMAT_0 'T0'    /* REV 0 Format */

    U16  ethaddr0;   /*  2: Ethernet address - most-sign word */
    U16  ethaddr1;   /*  3:  */
    U16  ethaddr2;   /*  4: Ethernet address - least-sign word */

    U8   sn12;       /*     Serial Number digits 1 & 2 */
    U8   board_info; /*  5: Board Info: high nyb=type;low nyb=Rev */
#define TX1000_AT_20 1

    U8   sn56;       /*     Serial Number digits 5 & 6 */
    U8   sn34;       /*  6: Serial Number digits 3 & 4 */

    U8   sn90;       /*     Serial Number digits 9 & 10 */
    U8   sn78;       /*  7: Serial Number digits 7 & 8 */

    U8   bus_adapter;    /*     Bus    Adapters Installed */
#define TX1000_ETH_10BASE2 01
#define TX1000_ETH_10BASE5 02
#define TX1000_ETH_10BASET 03

    U8   serial_adapter; /*  8: Serial Adapters Installed */
#define TX1000_NONE     00
#define TX1000_V24      01
#define TX1000_V35      02
#define TX1000_V24EXT   03

/* Currently unused area */
    U16  avail1;     /*  9:  */
    U16  avail2;     /* 10:  */
    U16  avail3;     /* 11:  */
    U16  avail4;     /* 12:  */
    U16  avail5;     /* 13:  */
    U16  avail6;     /* 14:  */
    U16  avail7;     /* 15:  */

    U16  checksum;   /* 16:  */
}
_INF10EE;

typedef struct
{
    _INF10EE        tx1eeprom;
    U8   tx1hwsavail[56];
}
_TX1HWSPEC;

/* TX2000/TX500 Configuration EEPROM contents <D0> */
typedef struct
{
    U16  signrev;    /*  1: Signature */
#define TX2000_FORMAT_0 'T0'    /* REV 0 Format */
#define TX2000_FORMAT_1 'T1'    /* REV 1 Format */
#define TX2000_FORMAT_2 'T2'    /* REV 2 Format */

    U16  ethaddr0;   /*  2: Ethernet address - most-sign word */
    U16  ethaddr1;   /*  3:  */
    U16  ethaddr2;   /*  4: Ethernet address - least-sign word */

    U8   sn12;       /*     Serial Number digits 1 & 2 */
    U8   board_info; /*  5: Board Info: high nyb=type;low nyb=Rev */
#define TX2000_AT_20    (1<<0)  /*     bit 0: set for all TX2000s */
#define TX2000_MAIN_Q32 (1<<1)  /*     bit 1: set if MAIN 360 to be in QUICC32 mode */

    U8   sn56;       /*     Serial Number digits 5 & 6 */
    U8   sn34;       /*  6: Serial Number digits 3 & 4 */

    U8   sn90;       /*     Serial Number digits 9 & 10 */
    U8   sn78;       /*  7: Serial Number digits 7 & 8 */

    U8   bus_adapter;    /*     Bus    Adapters Installed */
#define TX2000_NONE        00
#define TX2000_ETH_10BASE2 01
#define TX2000_ETH_10BASE5 02
#define TX2000_ETH_10BASET 03
#define TX2000_SERIAL      04

    U8   serial_adapter; /*  8: Serial Adapters Installed */

/*#define TX2000_NONE   00 */
#define TX2000_V24      01
#define TX2000_V35      02
#define TX2000_V24EXT   03
#define TX2000_CENMOB   04

    U8   mvip_adapter;   /*     MVIP Adapter Installed */

/*#define TX2000_NONE      00 */
#define TX2000_MV_BASIC    01
#define TX2000_MV_SLV360   02
#define TX2000_MV_QUICC32  03

    U8   t1_adapter; /*  9: T1/E1 Adapters Installed <D1.79> */

/*#define TX2000_NONE      00 *//* <D1.79> */
#define TX2000_T1_SINGLE   01   /* <D1.79> */
#define TX2000_T1_DUAL     02   /* <D1.79> */
#define TX2000_E1_SINGLE   03   /* <D1.79> */
#define TX2000_E1_DUAL     04   /* <D1.79> */
#define TX2000_E1_REV2     05   /* Dual E1 with EU Telco certification mods */

    U16  flsh_siz;   /* 10: Size of FLASH memory (in K)    <D1.82> */
    U16  flsh_min;   /* 11: Minimal Writable/Erasable unit (in K) <D1.82> */

    U8   dram_speed; /* 12: DRAM Speed, 0 = default (70ns) */
    U8   soft_auth;  /* 12: Software authorization bits */
#define TX2000_SS7_MTP   0x01   /* If Bit 0 clear, MTP authorized, else not */
#define TX2000_SS7_SCCP  0x02   /* If Bit 1 clear, SCCP authorized, else not */
#define TX2000_SS7_ISUP  0x04   /* If Bit 2 clear, ISUP authorized, else not */
#define TX2000_SS7_TCAP  0x08   /* If Bit 3 clear, TCAP authorized, else not */
#define TX2000_X25       0x10   /* If Bit 4 clear, X25 authorized, else not */
#define TX2000_TPX       0x20   /* If Bit 5 clear, TPX authorized, else not */
#define TX2000_SS7_TUP   0x40   /* If Bit 6 clear, TUP authorized, else not */

#define TX2000_SA_VALID  0x80   /* If bit 7 set, this info is valid, else not */

    U8   avail4;     /* 13: available !!!!! WITH FOLLOWING EXCEPTIONS: !!!!
                                 *     BIT: (1<<2) Once used as ISUP redundancy authorization... DO NOT RE-USE
                                 *     BIT: (1<<3) Once used as TCAP redundancy authorization... DO NOT RE-USE */
    U8   avail5;     /*     available !!!!! WITH FOLLOWING EXCEPTION: !!!!!
                                 *     BIT: (1<<0) Once used as NTT Variant authorization... DO NO RE-USE */

/* Currently unused area */
    U16  avail6;     /* 14:  */
    U16  avail7;     /* 15:  */

    U16  checksum;   /* 16:  */
}
_INF20EE;

/* TX3000 Configuration EEPROM contents */
typedef struct
{
    U16  signrev;    /*  1: Signature */
#define TX3000_FORMAT_0 'T0'    /* REV 0 Format */

    U16  ethaddr0;   /*  2: Ethernet address - most-sign word */
    U16  ethaddr1;   /*  3:  */
    U16  ethaddr2;   /*  4: Ethernet address - least-sign word */

    U8   sn12;       /*     Serial Number digits 1 & 2 */
    U8   board_info; /*  5: Board Info: high nyb=type;low nyb=Rev */
#define TX3000_INFO_1   (1<<0)  /*     bit 0: set for all TX3000s */
#define TX3000_MVIP     (1<<1)  /*     bit 1: MVIP adapter (FMIC) available */
#define TX3000_MAIN_Q32 (1<<2)  /*     bit 2: set if MAIN 360 to be in QUICC32 mode */
#define TX3000_SUBS_Q32 (1<<3)  /*     bit 3: set if SUB 360(s) to be in QUICC32 mode */

    U8   sn56;       /*     Serial Number digits 5 & 6 */
    U8   sn34;       /*  6: Serial Number digits 3 & 4 */

    U8   sn90;       /*     Serial Number digits 9 & 10 */
    U8   sn78;       /*  7: Serial Number digits 7 & 8 */

    U8   bus_adapter;    /*     Bus    Adapters Installed */
#define TX3000_NONE        00
#define TX3000_ETH_10BASE2 01
#define TX3000_ETH_10BASE5 02
#define TX3000_ETH_10BASET 03
#define TX3000_SERIAL      04

    U8   serial_adapter; /*  8: Serial Adapters Installed */

/*#define TX3000_NONE   00 */
#define TX3000_V24      01
#define TX3000_V35      02
#define TX3000_V24EXT   03
#define TX3000_CENMOB   04

    U8   t1_adapter; /*  9: T1/E1 Adapters Installed */

/*#define TX3000_NONE      00 */
#define TX3000_T1_SINGLE   01
#define TX3000_T1_DUAL     02
#define TX3000_E1_SINGLE   03
#define TX3000_E1_DUAL     04
#define TX3000_E1_REV2     05   /* Dual E1 with EU Telco certification mods */

    U8   avail5;

    U16  flsh_siz;   /* 10: Size of FLASH memory (in K) */
    U16  flsh_min;   /* 11: Minimal Writable/Erasable unit (in K) */

    U8   dram_speed; /* 12: DRAM Speed, 0 = default (70ns) */
    U8   soft_auth;  /* 12: Software authorization bits */
#define TX3000_SS7_MTP   0x01   /* If Bit 0 clear, MTP authorized, else not */
#define TX3000_SS7_SCCP  0x02   /* If Bit 1 clear, SCCP authorized, else not */
#define TX3000_SS7_ISUP  0x04   /* If Bit 2 clear, ISUP authorized, else not */
#define TX3000_SS7_TCAP  0x08   /* If Bit 3 clear, TCAP authorized, else not */
#define TX3000_X25       0x10   /* If Bit 4 clear, X25 authorized, else not */
#define TX3000_TPX       0x20   /* If Bit 5 clear, TPX authorized, else not */
#define TX3000_SS7_TUP   0x40   /* If Bit 6 clear, TUP authorized, else not */

#define TX3000_SA_VALID  0x80   /* If bit 7 set, this info is valid, else not */

    U8   slave_360s; /* Number of slave 360s */

    U8   cpu_mhz;    /* 13: CPU type (high nibble) and Megahertz (low nibble) */
#define TX3000_CPU40     0x0    /*     68040 processor (high nibble) */
#define TX3000_CPU60     0x1    /*     68060 processor (high nibble) */

#define TX3000_25MHZ     0x0    /*     25 Megahertz (low nibble) */
#define TX3000_33MHZ     0x1    /*     33 Megahertz (low nibble) */
#define TX3000_50MHZ     0x2    /*     50 Megahertz (low nibble) */
#define TX3000_66MHZ     0x3    /*     66 Megahertz (low nibble) */

    U8   avail8;     /* 14: available !!!!! WITH FOLLOWING EXCEPTIONS: !!!!
                                 *     BIT: (1<<2) Once used as ISUP redundancy authorization... DO NOT RE-USE
                                 *     BIT: (1<<3) Once used as TCAP redundancy authorization... DO NOT RE-USE */
    U8   avail9;     /*     available !!!!! WITH FOLLOWING EXCEPTION: !!!!!
                                 *     BIT: (1<<0) Once used as NTT Variant authorization... DO NO RE-USE */

/* Currently unused area */
    U16  avail7;     /* 15:  */

    U16  checksum;   /* 16:  */
}
_INF30EE;

/* Hardware-specific extensions to EAROM [fields in infhwspec block] */
typedef struct
{
    _INF20EE        tx2eeprom;
    U16  tx2hws_WL0;
    U16  tx2hws_WL1;
    U8   tx2s360;    /* 0 means no Slave 360 */
    U8   tx2mvipmap; /* mapping index indicating MVIP SCC assignments */
    U8   tx2hwsavail[50];
}
_TX2HWSPEC;

typedef struct
{
    _INF30EE        tx3eeprom;
    U16  tx3hws_WL0;
    U16  tx3hws_WL1;
    U8   tx3s360;    /* # of 360's  */
    U8   tx3mvipmap; /* mapping index indicating MVIP SCC assignments */
    U8   tx3hwsavail[50];
}
_TX3HWSPEC;

typedef struct
{
    U8   tx3s360;    /* # of 360's  */
    U8   tx3mvipmap; /* mapping index indicating MVIP SCC assignments */
    U8   tx32mvip90; /* 0 means H.100, else MVIP 90 compatability mode */
    U8   tx32layout; /* hardware layout differences across TX32xx boards */
#define TX32_COMPACT_PCI  (1<<0)    /* bit set = CompactPCI board */

    U8   tx3hwsavail[84];
}
_TX32HWSPEC;

typedef struct __inf
{
    U32   infmilisec; /* Miliseconds since boot */
    U16  infhbusmaxdata; /* Max DATA part of HBUS pkt */
    U8   infmaxcp;   /* Max DPR destination CP number    <D0> */
    U8   infnumscc;  /* Number of SCC channels available <D0> */
    U8   infnumeth;  /* Number of ETHERNET chans avail   <D0> */
    U8   infnummvip; /* Number of MVIP Chans available */
    U8   infnumcen;  /* Number of CENODE channels available */
    U8   infnummob;  /* Number of MOBIPAK channels available */
    U16  infflashsize;   /* Size of flash (in K) [max 64 Meg]<D1.82> */
    U16  infflashunit;   /* min writable/erasable size (in K)<D1.82> */
    U8   infnumdbg;  /* Number of DEBUG channels available */
    U8   infbasescc; /* Base number hardware SCC ports assigned from */
    U8   infnumqchan;    /* Number of QUICC32 channels available */
    U8   infq32mode; /* Indicator of whether each processor is in QUICC32 mode */
#define QUICC32_MAIN    (1<<0)  /* bit set = MAIN processor operating in QUICC32 mode */
#define QUICC32_SUB1    (1<<1)  /* bit set = SUB processor #1 operating in QUICC32 mode */
#define QUICC32_SUB2    (1<<2)  /* bit set = SUB processor #2 operating in QUICC32 mode */
#define QUICC32_SUB3    (1<<3)  /* bit set = SUB processor #3 operating in QUICC32 mode */

    U8   infethaddr[6];  /* Hardware address of Ethernet Interface (if exists) */
    U16  infhbusmaxtx;   /* maximum transmits to HBUS interface */
    U8   infeth2addr[6]; /* Hardware address of 2nd Ethernet Interface (if Exists) */
    U8   inft1adapter;   /* T1/E1 Adapters Installed */
#define TXN_T1_NONE        00
#define TXN_T1_SINGLE   01
#define TXN_T1_DUAL     02
#define TXN_E1_SINGLE   03
#define TXN_E1_DUAL     04

    U8   kernel_ver; /* Kernel Version Number */
    U8   kernel_rev; /* Kernel Revision Number */

    U8   infavail1[27];  /* Space available for future expansion <D0> */
    U16  infnonvolcpk;   /* Number of bytes of non-volatile RAM reserved for KERNEL */
    U16  infnonvoluser;  /* Number of bytes of non-volatile RAM available to users */
    U16  inftimeofday[5];    /* Time of day in normal timestamp format */
    U8   infsoftauth;    /* Software authorization code */
    U8   infmicrocd; /* Type of Microcode Installed (0 = none) <D0> */
#define MICROCD_SS7     0x37    /* Signaling System 7               <D0> */

    U8   infhwres;   /* Indicators of Hardware Resources avail. <D0> */
#define HWRES_TIN1      (1<<0)  /* Bit 0 set = TIN1 type timer handling    <D0> */

    U8   infboardnum;    /* board number of this CPU */
    union
    {
        U8   ___infil[88];   /* Hardware Specific Region */
        _TX1HWSPEC      tx1hwspec;  /* TX1000 EEPROM and HW Specific info */
        _TX2HWSPEC      tx2hwspec;  /* TX2000 EEPROM and HW Specific info */
        _TX3HWSPEC      tx3hwspec;  /* TX3000 EEPROM and HW Specific info */
        _TX32HWSPEC     tx32hwspec; /* TX32xx HW Specific info */
    }
    infhwspec;

    U8   infbootscrp[MAXFNA];    /* Boot Script File Name              <D1.82> */
    U8   infbootlog[138];    /* Boot Log                           <D1.82> */
    U16  infbooterr; /* Boot Error                         <D1.82> */
    U32   infsysid;   /* System identification */
#define TX_SYSID        0x5458L /* 'TX'   - TX series       <D0> */
#define TX1000_SYSID    (TX_SYSID<<16|0x3130)   /* 'TX10' - TX 1000 system */
#define TX2000_SYSID    (TX_SYSID<<16|0x3230)   /* 'TX20' - TX 2000 system */
#define TX3000_SYSID    (TX_SYSID<<16|0x3330)   /* 'TX30' - TX 3000 system */
#define TX3210_SYSID    (TX_SYSID<<16|0x3341)   /* 'TX3A' - TX 3210 system */
#define TX3220_SYSID    (TX_SYSID<<16|0x3342)   /* 'TX3B' - TX 3220 system */
#define TX5000_SYSID    (TX_SYSID<<16|0x3530)   /* 'TX50' - TX 5000 system */

    U32   infoscfreq; /* Oscillation Frequency of clock src <D0> */
    U32   infmaxbaud; /* Maximum baud rate (SYNC)           <D0> */
    U32   infminbaud; /* Minimum baud rate (SYNC)           <D0> */
    U32   infeepled;  /* mask of EEPROM-driven LED usage */

    U32   infsecsepoch;      /* Seconds since epoch */
    U32   infmbootepoch;     /* msecs since boot */

    U8   infavail4[34];  /* Space available for future expansion <D0> */

} CPK_SYSINFO;

/* CP types
 */
#define TCPISTCP_	1               /* Tcp installed */
#define TCPISNCP_	2               /* Ncp installed */

/* Apm types
 */
#define APMISAPM_	1               /* Apm installed */
#define APMISAPA_	2               /* Apa installed */

/* Had types
 */
#define HADISHAD_	1               /* Had installed */
#define HADISHAT_	2               /* Hat installed */

/* Cache status bits
 */
#define CAC_HSRFAIL	(1<<0)          /* High speed ram failure */
#define CAC_CACFAIL	(1<<1)          /* Cache failure */

/* Remote status bits
 */
#define REMVAX_ 	1               /* Remote connected to Vax */

/* Remote fill status
 */
#define FILLBOO_	1               /* Remote fill in boot (using ICA) */
#define FILLRUN_	2               /* Remote fill in run (using X.25) */

/*  Memory controller types
 */
#define MCTLISMCU_	0               /* Memory controller is MCU */
#define MCTLISSBM_	1               /* Memory controller is SBM */
#define MCTLISSBX_	2               /* Memory controller is SBX */

/*  System types
 */
#define SYSISLES	1               /* System is a LES */
#define SYSISSTP	2               /* System is a Stack Pack */

/*  System codes (subtypes of above)
*/
#define UNKNOWNSYS	0               /* Unknown system type code */

/* for system type StackPack, defines CPU board type */
#define SYSISCPU	1               /* Non-enhanced CPU (obsoleted) */
#define SYSISCPX	2               /* Enhanced CPU (large EPROM) */
#define SYSISCPA	3               /* Advanced CPU (SP supportive) */
#define SYSISGPU	4               /* GPU (cache/68020) */

/* for system type LES, defines system type */
#define SYSISS100	1               /* S100 */
#define SYSISS200	2               /* S200 */
#define SYSISS240	3               /* S240 */

/*
 *	Task initial register contents are stored by the runtime
 *	library into a global array of 15 longs called _regs[].
 *	See the KERNEL REFERENCE MANUAL for a description of these
 *	values. The following are symbolic indices for the
 *	registers as in:  _regs[D4]
 */
#define D0	0
#define D1	1
#define D2	2
#define D3	3
#define D4	4
#define D5	5
#define D6	6
#define D7	7
#define A0	8
#define A1	9
#define A2	10
#define A3	11
#define A4	12
#define A5	13
#define A6	14

/*
 *  getenv() definitions.
 */
#define MAXENV      6               /* Maximum number of environment list entries. */
#define MAXENVSZ  256               /* Maximum length of environment variable value. */
#define MAXTTY      7               /* Maximum number of terminal types. */

/* ----- General 'C' Constants */
#ifndef NULL
#define NULL	(void *)0
#endif

/* ----- cpk_serv Service Numbers */
#define SERV_GETCURRTCB   1         /* Get current task's tcb */
#define SERV_DPSETVEC     2         /* Set DPRAM type handler vector */
#define SERV_DPSENDNOTF   4         /* Send packet to PC via DPRAM with notify */
#define SERV_SCCSETVEC    5         /* Set SCC type handler vector */
#define SERV_ETHSETVEC    6         /* Set Ethernet type handler vector */
#define SERV_DEBUGSERV    13        /* Debug TRAP services */

/* ---- service queue information structure ----*/
typedef struct __svcqinfo
{
    U8   task_priority;  /* task's priority */
#define TASK_PRIO_MAX   31          /* maximum task priority */

    U8   task_inprq; /* non-zero = in priority run queue */
    U16  task_state; /* state of task */
#define T_CREATED    1          /* has been created but never ran */
#define T_STALLED    2          /* task is not executing */
#define T_WAITING    3          /* waiting on IO */
#define T_BLOCKED    4          /* waiting for higher priority task */
#define T_RUNNING    5          /* task is currently executing */
#define T_HOLDING    6          /* hold is in effect */
#define T_DESTROYING 7          /* task is being destroyed */

    U32   svcq_depth; /* number of structures in list */
    U32   svcq_peak;  /* largest value svcq_depth has reached */
    U32   svcq_max;   /* max service queue depth */
    U32   svcq_overflow;  /* count of service queue overflows */
    U8   reserved[16];   /* reserved for future use */
}
SVCQINFO;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CPK FUNCTION PROTOTYPES
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
S16             cpk_trap(krnl_pkt * pkt);
void            LogErrTrace(U32 p1, U32 p2, U32 p3, U32 p4);
S16           svcq_info(void *tcb, SVCQINFO * info);
void            vled_set(U8 vlednum);
void            vled_clr(U8 vlednum);

/*+++++ Prototypes for message-processing functions provided by KERNEL +++++*/
void            vpd_intr(queue_read * sqread);  /* MSGINTR_   handler */

/*   mem_intr     [see gpluser.h]            * MSGMEMORY_ handler */

/*   tim_qrd      [see gpluser.h]            * MSGTIME_   handler */
void            aqm_intr(queue_read * sqread);  /* MSGTCPI_   handler */

#endif /* TX_LEGACY_68000 */

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

#endif /* _CPKUSER_H */
