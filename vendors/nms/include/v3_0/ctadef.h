/*****************************************************************************
*                                  CTADEF.H
*
*  Header for CT Access library. To be included by all applications and
*  CT Access service managers and services.
*
*
*  Copyright (c) 1996-98  Natural MicroSystems Corp.  All rights reserved.
*****************************************************************************/

#ifndef CTADEF_INCLUDED
#define CTADEF_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif

#include <stddef.h>     /* For offsetof(), NULL */

/*====== CT ACCESS COMMON DEFINES ==========================================*/

#define CTA_SYS_SVCID        0x1000
#define CTA_APP_SVCID        0x2000
#define CTA_MAX_SVCID        0x7FFF

#define CTA_CODE_MASK        0xF000
#define CTA_CODE_ERROR       0x0000
#define CTA_CODE_REASON      0x1000
#define CTA_CODE_EVENT       0x2000
#define CTA_CODE_COMMAND     0x3000
#define CTA_CODE_TRACETAG    0x4000

#define CTA_IS_ERROR(code)      ((code) != SUCCESS &&\
                                  ((code) & CTA_CODE_MASK) == CTA_CODE_ERROR)
#define CTA_IS_REASON(code)     (((code) & CTA_CODE_MASK) == CTA_CODE_REASON)
#define CTA_IS_EVENT(code)      (((code) & CTA_CODE_MASK) == CTA_CODE_EVENT)
#define CTA_IS_COMMAND(code)    (((code) & CTA_CODE_MASK) == CTA_CODE_COMMAND)
#define CTA_IS_TRACETAG(code)   (((code) & CTA_CODE_MASK) == CTA_CODE_TRACETAG)

/* By convention done events have the 0x100 bit set */
#define CTA_CODE_DONE_EVENT     (CTA_CODE_EVENT | 0x100)
#define CTA_IS_DONE_EVENT(code) ((code & (CTA_CODE_MASK | 0x100)) \
                                 == CTA_CODE_DONE_EVENT)

/*
 * Macro to create a user event.
 * NOTE: valid range of user events is 0x20002000 to 0x20002FFF.
 */
#define CTA_USER_EVENT(code)    (((code) & 0x00000FFF) | 0x20002000)

/*====== CTA ERRORS AND REASONS ============================================*/
#ifndef CTAERR_INCLUDED
#include "ctaerr.h"
#endif

/*====== CTA EVENTS ========================================================*/

#define CTAEVN_NULL_EVENT                  0x10002000
#define CTAEVN_WAIT_TIMEOUT                0x10002004
#define CTAEVN_UPDATE_WAITOBJS             0x10002005

#define CTAEVN_DESTROY_CONTEXT_DONE        0x10002101
#define CTAEVN_OPEN_SERVICES_DONE          0x10002102
#define CTAEVN_CLOSE_SERVICES_DONE         0x10002103



/*======================= CTA STRUCTURE DEFINITIONS ========================*/

typedef DWORD CTAQUEUEHD;
typedef DWORD CTAHD;

/*   parameter management policy field - is made up of bits 0, 1 of parmflags
 *   member of CTA_INIT_PARM structure. Value 0x3 is reserved.  User should NOT
 *   set parm flag field to value 3.
 */

#define CTA_PARM_MGMT_LOCAL             0x0 /* Allow process to manage global
                                               parameter default              */

#define CTA_PARM_MGMT_SHARED            0x1 /* Process must takes shared
                                               memory sytem parameter default
                                               managed by CT Access ctdaemon. */

#define CTA_PARM_MGMT_SHARED_IF_PRESENT 0x2 /* When CT Access ctdaemon is
                                               present, application takes shared
                                               memory system parameter default
                                               managed by CT Access daemon.
                                               Otherwise, application manages
                                               global parameter default.      */



/* Trace flags - if initialized to 0 then tracing is disabled */
#define CTA_TRACE_ENABLE          0x1 /* enable tracing - immediate write
                                         to trace memory is default mode      */
#define CTA_TRACE_ON_ERROR        0x2 /* write trace memory on error only keep
                                         local trace memory for each context  */


/* CTA flags */
#define CTA_NOTIFY_UPDATE_WAITOBJS 0x1 /* notify application with an event
                                          CTAEVN_UPDATE_WAITOBJS when CT
                                          Access updates its internally
                                          managed list of mux handles         */

typedef struct _CTA_INIT_PARMS
{
    DWORD size;                       /* size of structure                    */
    DWORD parmflags;                  /* bit mask of parm flags (see above)   */
    DWORD traceflags;                 /* bit mask of trace flags (see above)  */
    DWORD daemonflags;                /* Applications must set this to 0      */
    DWORD ctaflags;                   /* bit mask of cta flags (see above)    */
    char  *filename;                  /* filename to load [svc,svcmgr] sets   */
    DWORD ctacompatlevel;             /* required cta compatibility level     */
    DWORD reserved;                   /* Application must set this to 0.      */
} CTA_INIT_PARMS;

typedef struct _CTA_SERVICE_NAME
{
    char *svcname;                    /* service name (eg. "ADI", "SWI" ...)  */
    char *svcmgrname;                 /* service manager providing service    */
} CTA_SERVICE_NAME;

/* The following structure is reserved for future use */
typedef struct _CTA_SERVICE_ADDR
{
    char  addr[80];
    DWORD host;
    DWORD reserved;
} CTA_SERVICE_ADDR;

typedef struct _CTA_MVIP_ADDR
{
    DWORD board;                      /* board number                         */
    DWORD bus;                        /* MVIP bus type                        */
    DWORD stream;                     /* stream number                        */
    DWORD timeslot;                   /* timeslot                             */
    DWORD mode;                       /* open mode                            */
} CTA_MVIP_ADDR;

typedef struct _CTA_SERVICE_ARGS
{
    char  strarg[40];                 /* service specific string argument     */
    DWORD args[10];                   /* array of service specific args       */
} CTA_SERVICE_ARGS;

/* Compound structure passed to ctaOpenServices */
typedef struct _CTA_SERVICE_DESC
{
    CTA_SERVICE_NAME name;
    CTA_SERVICE_ADDR svcaddr;
    CTA_SERVICE_ARGS svcargs;
    CTA_MVIP_ADDR    mvipaddr;
} CTA_SERVICE_DESC;

/* The application event structure */
typedef struct
{
    DWORD    id;                /* Event code (and source service id)         */
    CTAHD    ctahd;             /* CT Access context handle                   */
    DWORD    timestamp;         /* timestamp                                  */
    DWORD    userid;            /* user id (defined by ctaCreateContext)      */
    DWORD    size;              /* size of buffer if buffer != NULL           */
    void     *buffer;           /* buffer pointer                             */
    DWORD    value;             /* Event status or event-specific data        */
    DWORD    reserved;          /* must be 0                                  */
} CTA_EVENT;
/*======================= PARAMETER STRUCTURES =============================*/

/*
 *  CTAPARM_FIELD - describes a single parameter field (e.g. gain, freq, )
 */

typedef struct
    {                       /* describes the fields in a structure:*/
    char *name;             /*  name of the field                  */
    DWORD offset;           /*  byte offset from base or number of */
                            /*    fields if recd 0 in array        */
    DWORD size;             /*  size of the field                  */
    DWORD format;           /*  format specifier                   */
    DWORD units;            /*  units specifier                    */
    } CTAPARM_FIELD;


/* A macro to build a row of an array of statically initialized CTAPARM_FIELDs:
 *   p - parm structure type                (e.g., CTARECORD_PARMS)
 *   f - field name                         (e.g., AGCenable)
 *   s - size (the xxx of CTA_FMT_xxx)      (e.g., DWORD)
 *   u - units (the xxx of CTA_UNITS_xxx)   (e.g., INTEGER)
*/
#define CTAFIELDDESC(p,f,s,u) \
            #f,offsetof(p,f),sizeof(((p *)0)->f),CTA_FMT_##s,CTA_UNITS_##u

/*
 *  CTAPARM_FIELDCNT()
 *
 *   Evaluates to the number of field definitions for a for a given parameter
 *   structure described with an array of CTAPARM_FIELD[].
 *   Subtract 2 because:
 *
 *   1.  The structure name occupies the first entry in the array and
 *   2.  A NULL field name terminates the array/strcuture def.
 *
 *
 *  NOTE: the combination of the structure name in the first record
 *        and a field name should not exceed MAXPARM_NAMESZ, which is
 *        defined in 'ctasys.h'.
 */

#define CTAPARM_FIELDCNT(_s_) ((sizeof(_s_)/sizeof(CTAPARM_FIELD))-2)

/* Use the following to access different parts of the parmid */
/* parmid 0 is reserved for CTA_NULL_PARMID */
#define CTA_PARM_SVCID(parmid) ((0xFFFF0000 & parmid) >> 16)
#define CTA_PARM_ID(parmid)    (0x00FF & parmid)
#define CTA_PARM_MAXID 0xFF    /* only allow 1-255 as valid parameter indices */

/* If descriptor is an extension parameter (i.e. not standard service
   parameters) then set the 0x100 bit in the parmid */
#define CTA_PARM_EXT_MASK       0x100
#define CTA_IS_PARM_EXT(parmid) ((CTA_PARM_EXT_MASK & parmid) \
                                 == CTA_PARM_EXT_MASK)

/*
 *  CTAPARM_DESC - Structure used by ctapar.c to gain access to field
 *                 descriptors etc.
 */

typedef struct
{
    DWORD                 parm_id;
    void                 *parm;         /* pointer to defaults (binary)     */
    const CTAPARM_FIELD  *descr;        /* pointer to field descriptors     */
    DWORD                 fieldcnt;     /* number of fields in descr        */
} CTAPARM_DESC;

#ifdef OFFSETOF
  #undef OFFSETOF
#endif
#define OFFSETOF(s_name, s_member) (int)&(((s_name *)0)->s_member)



typedef DWORD (NMSSTDCALLPTR CTA_ERROR_HANDLER)
    (
    CTAHD   ctahd,                /*   CTA context handle                   */
    DWORD   error,                /*   CTA return code                      */
    char   *errtxt,               /*   error name                           */
    char   *func );               /*   name of function that received error */

#define  CTA_REPORT_ERRORS   ((CTA_ERROR_HANDLER) (1L))
#define  CTA_EXIT_ON_ERRORS  ((CTA_ERROR_HANDLER) (2L))

/*---------------------------------------------------------------------------
 * Misc Constants
 *--------------------------------------------------------------------------*/
#define NULL_CTAQUEUEHD      0xFFFFFFFF
#define NULL_CTAHD           0xFFFFFFFF

#define CTA_NULL_PARMID      0
#define CTA_NULL_SVCID       0

#define CTA_WAIT_FOREVER     0xFFFFFFFF

#ifdef _MAX_PATH
#define CTA_MAX_PATH         _MAX_PATH
#else
#define CTA_MAX_PATH         256
#endif

#define CTA_MAX_FORMAT_SIZE  400  /* Maximum size of buffer produced by
                                     ctaFormatEvent                         */
#define CTA_CONTEXT_NAME_LEN 12   /* Context name length including null term*/

/*---------------------------------------------------------------------------
 * Function prototypes
 *--------------------------------------------------------------------------*/
DWORD NMSAPI ctaInitialize(       /* Initializes CT Access process          */
    CTA_SERVICE_NAME  svcname[],  /* array of service name structures       */
    unsigned          nsvcs,      /* number of service name structures      */
    CTA_INIT_PARMS   *initparms); /* initialization parameter structure     */

DWORD NMSAPI ctaCreateQueue(      /* Creates an application event queue     */
    char       *mgrlist[],        /* list of service managers bound to queue*/
    unsigned    nmgrs,            /* number of managers in list             */
    CTAQUEUEHD *ctaqueuehd);      /* returned queue handle                  */

DWORD NMSAPI ctaDestroyQueue(     /* Destroys an application event queue    */
    CTAQUEUEHD ctaqueuehd);       /* queue hd returned by ctaCreateQueue    */

DWORD NMSAPI ctaCreateContext(    /* Creates a CTA context                  */
    CTAQUEUEHD ctaqueuehd,        /* queue that will receive events for cxt */
    unsigned   userid,            /* userid passed back in all events on cxt*/
    char      *contextname,       /* context name used in tracing           */
    CTAHD     *ctahd);            /* returned context handle                */

DWORD NMSAPI ctaDestroyContext(   /* Destroys a context and closes svcs     */
    CTAHD ctahd);                 /* context hd returned by ctaCreateContext*/

DWORD NMSAPI ctaOpenServices(     /* Opens services on a CTA context        */
    CTAHD             ctahd,      /* context hd returned by ctaCreateContext*/
    CTA_SERVICE_DESC  svclist[],  /* array of service descriptor structures */
    unsigned          nsvcs);     /* number of service desc structs in array*/

DWORD NMSAPI ctaCloseServices(    /* Closes services on a CTA context       */
    CTAHD    ctahd,               /* context hd returned by ctaCreateContext*/
    char    *svcname[],           /* list of services to close              */
    unsigned nsvcs);              /* number of services in list             */

DWORD NMSAPI ctaWaitEvent(        /* Retrieves an event from an event queue */
    CTAQUEUEHD ctaqueuehd,        /* queue hd returned by ctaCreateQueue    */
    CTA_EVENT *event,             /* event structure to be filled           */
    unsigned   timeout);          /* time to wait for an event in ms        */

DWORD NMSAPI ctaGetQueueHandle(   /* Retrieves queue hd of the CTA context  */
    CTAHD       ctahd,            /* context hd returned by ctaCreateContext*/
    CTAQUEUEHD *ctaqueuehd);      /* queue that will receive events for cxt */

DWORD NMSAPI ctaQueueEvent(       /* Enqueues an application event          */
    CTA_EVENT *event);            /* enqueued event (context within event   */
                                  /* specifies destination queue)           */

DWORD NMSAPI ctaSetErrorHandler(  /* Sets the error handler                 */
    CTA_ERROR_HANDLER  handler,   /* user function, NULL, CTA_REPORT_ERRORS */
                                  /* or CTA_EXIT_ON_ERRORS                  */
    CTA_ERROR_HANDLER *oldhandler);  /* previously set error handler        */

DWORD NMSAPI ctaGetText(          /* Formats CT Access codes                */
    CTAHD    ctahd,               /* context hd or NULL_CTAHD               */
    DWORD    code,                /* passed error, reason, cmd or evt code  */
    char    *buffer,              /* returned formatted text string         */
    unsigned size);               /* size of buffer                         */

DWORD NMSAPI ctaFormatEvent(      /* Formats CT Access events               */
    char      *lineprefix,        /* string placed at start of each line    */
    CTA_EVENT *event,             /* event to format                        */
    char      *buffer,            /* returned formatted text string         */
    unsigned   size);             /* size of buffer                         */


#ifdef UNIX
#include <stropts.h>
#include <poll.h>
typedef struct pollfd CTA_WAITOBJ;

extern CTA_WAITOBJ CTA_NULL_WAITOBJ;
#else
typedef MUX_HANDLE CTA_WAITOBJ;
#define CTA_NULL_WAITOBJ NULL_MUXHDL
#endif

/* EPJ 98-08-28: The CTA_UNITS_HZ breaks because HZ is defined as a macro
                 in /usr/include/sys/param.h. Undefining it here to hide the
                 problem. ??? */
#ifdef HZ
#undef HZ
#endif

typedef DWORD (NMSSTDCALLPTR WAIT_FUNCTION)(CTAQUEUEHD ctaqueuehd,
                                            CTA_WAITOBJ *waitobj,
                                            void *arg);

typedef    WAIT_FUNCTION     CTA_WAITFN;
#define    CTA_NULL_WAITFN   ((CTA_WAITFN)NULL)

#define    CTA_PRIORITY_NORMAL 0
#define    CTA_PRIORITY_HIGH   1
DWORD NMSAPI ctaRegisterWaitObject( /* Register application wait object     */
    CTAQUEUEHD ctaqueuehd,          /* queue hd                             */
    CTA_WAITOBJ *waitobj,           /* user wait object                     */
    CTA_WAITFN waitfn,              /* function called when obj signalled   */
    void      *arg,                 /* arg to pass to function called       */
    unsigned   priority);           /* relative priority of wait object     */

DWORD NMSAPI ctaUnregisterWaitObject( /* Unregister wait object             */
    CTAQUEUEHD ctaqueuehd,            /* queue hd                           */
    CTA_WAITOBJ *waitobj);            /* wait object to unregister          */

DWORD NMSAPI ctaQueryWaitObjects(   /* Query CT Access managed wait objects */
    CTAQUEUEHD ctaqueuehd,          /* queue hd                             */
    CTA_WAITOBJ *waitobj,           /* array of wait objects to be returned */
    unsigned size,                  /* size of array passed in              */
    unsigned *count);               /* number of elements returned          */

/*====== PARAMETER MANAGEMENT ======================================*/

typedef struct
    {                             /* Describes the fields in a structure:   */
    char  structname[40];         /*   name of the structure                */
    char  fieldname[40];          /*   name of the field                    */
    DWORD offset;                 /*   byte offset from the base            */
    DWORD size;                   /*   size of the field                    */
    DWORD format;                 /*   format type (see below)              */
    DWORD units;                  /*   units type (see below)               */
    } CTA_PARM_INFO;

/* Definition of the 'format' field of CTA_PARM_INFO */
#define CTA_FMT_UNKNOWN     0
#define CTA_FMT_WORD        1
#define CTA_FMT_DWORD       2
#define CTA_FMT_INT16       3
#define CTA_FMT_INT32       4
#define CTA_FMT_STRING      5

/* Definition of the 'units' field of CTA_PARM_INFO */
#define CTA_UNITS_INTERNAL  0
#define CTA_UNITS_INTEGER   1
#define CTA_UNITS_COUNT     2
#define CTA_UNITS_MASK      3
#define CTA_UNITS_HZ        4
#define CTA_UNITS_MS        5
#define CTA_UNITS_DB        6
#define CTA_UNITS_DBM       7
#define CTA_UNITS_IDU       8
#define CTA_UNITS_STRING    9
#define CTA_UNITS_PERCENT  10

DWORD NMSAPI ctaGetParms(         /* Fetches value of parameter (structure) */
    CTAHD            ctahd,       /*   CT Access context handle             */
    unsigned         parmid,      /*   parameter id                         */
    void            *buffer,      /*   pointer to your parameter memory     */
    unsigned         size );      /*   size of your memory area.            */

DWORD NMSAPI ctaGetParmByName(    /* Fetches value of parameter by fieldname*/
    CTAHD            ctahd,       /*   CT Access context handle             */
    char            *parmname,    /*   parameter field name                 */
    void            *buffer,      /*   pointer to your parameter memory     */
    unsigned         size );      /*   size of your memory area.            */

DWORD NMSAPI ctaSetParmByName(    /* Updates value of parameter field       */
    CTAHD            ctahd,       /*   CT Access context handle             */
    char            *parmname,    /*   parameter field name                 */
    void            *buffer,      /*   pointer to your parameter memory     */
    unsigned         size );      /*   size of your memory area.            */

DWORD NMSAPI ctaGetParmInfo(      /* Returns info about a parameter field   */
    unsigned         parmid,      /*   parameter id                         */
    char            *parname,     /*   parameter structure name or field    */
    unsigned         index,       /*   index of field                       */
    CTA_PARM_INFO   *buffer );    /*   passed array of field descriptors to */
                                  /*     be filled                          */

DWORD NMSAPI ctaRefreshParms(     /* Refresh CTA context parms              */
    CTAHD            ctahd);      /*   CT Access context handle             */

DWORD NMSAPI ctaGetParmId(        /* Fetchs parameter id by fieldname       */
    CTAHD            ctahd,       /*   CT Access context handle             */
    char             *parname,    /*   parameter field name                 */
    unsigned         *parmid );   /*   pointer to your parameter id         */

DWORD NMSAPI ctaGetParmIds(       /* Fetches parameter ids and/or service
                                     id by service name, and service
                                     manager(optional)                     */
    char *svcname,                /*   service name to find service id
                                       and/or parameter ids                */
    char *svcmgrname,             /*   optional service manager name       */
    unsigned *retsvcid,           /*   pointer to your service id          */
    unsigned *buffer,             /*   pointer to your array of parameter
                                       ids                                 */
    unsigned maxsize,             /*   size of your parameter ids array    */
    unsigned *retsize);           /*   count of all parameter ids returned
                                       in parameter ids array              */

DWORD NMSAPI ctaLoadParameterFile(/* Updates value of parameter fields
                                     specified in filename                 */
    CTAHD ctahd,                  /*   CT Access context handle            */
    char *filename );             /*   filename to get parameter fields    */

/*====== TRACING ===========================================================*/

typedef enum {CTA_TRACE_SEVERITY_INFO=0,
              CTA_TRACE_SEVERITY_WARNING,
              CTA_TRACE_SEVERITY_ERROR} CTA_TRACE_SEVERITY;

/*
 * These are the tracetags passed to the function ctaLogTrace which describe
 * the type of the traceval argument so it can be formatted properly.
 */
#define CTA_TRACETAG_DWORD             0x00004001 /* trace value is a DWORD  */
#define CTA_TRACETAG_INT32             0x00004002 /* trace value is an INT32 */
#define CTA_TRACETAG_STRING            0x00004003 /* trace value is a string */
#define CTA_TRACETAG_ERROR             0x00004004 /* CTA_TRACE_ERROR_INFO    */
#define CTA_TRACETAG_DISP_COMMAND      0x00004005 /* not for application use */
#define CTA_TRACETAG_DISP_EVENT        0x00004006 /* not for application use */
#define CTA_TRACETAG_API_EVENT         0x00004007 /* use this to send a
                                                     CTA_EVENT to the trace
                                                     log with ctaLogTrace    */

/*
 * These are the bits of the tracemask passed to the function
 * ctaSetTraceLevel and used to modify the global tracemask via ctdaemon.
 */
#define CTA_TRACEMASK_DRIVER_COMMANDS  0x00000001 /* trace cmds to devices   */
#define CTA_TRACEMASK_DRIVER_EVENTS    0x00000002 /* trace evts from devices */
#define CTA_TRACEMASK_DISP_COMMANDS    0x00000004 /* trace svc->svc cmds     */
#define CTA_TRACEMASK_DISP_EVENTS      0x00000008 /* trace svc->svc evts     */
#define CTA_TRACEMASK_API_COMMANDS     0x00000010 /* trace application cmds  */
#define CTA_TRACEMASK_API_EVENTS       0x00000020 /* trace application evts  */
#define CTA_TRACEMASK_API_ERRORS       0x00000040 /* trace application errors*/
#define CTA_TRACEMASK_SVC_ERRORS       0x00000080 /* trace internal svc errs */
#define CTA_TRACEMASK_DEBUG_BIT0       0x00000100 /* trace svc specific msgs */
#define CTA_TRACEMASK_DEBUG_BIT1       0x00000200 /* trace svc specific msgs */
#define CTA_TRACEMASK_DEBUG_BIT2       0x00000400 /* trace svc specific msgs */
#define CTA_TRACEMASK_DEBUG_BIT3       0x00000800 /* trace svc specific msgs */

#define CTA_TRACEMASK_ALL_COMMANDS     0x00000015
#define CTA_TRACEMASK_ALL_EVENTS       0x0000002A
#define CTA_TRACEMASK_ALL              0x00000F7F

/*
 * Fill in this structure and pass it to ctaLogTrace in order to log an
 * error message to the CT Access trace log.  Use CTA_TRACETAG_ERROR as
 * the tracetag argument to ctaLogTrace and the error will be formatted
 * correctly by the trace utility.
 */
typedef  struct
    {
    CTAHD    ctahd;                      /* CT Access context handle     */
    DWORD    code;                       /* Error code                   */
    DWORD    data1;                      /* assocated data               */
    DWORD    data2;                      /* additional associated data   */
    DWORD    line;                       /* line number                  */
    char     file[40];                   /* file name                    */
    char     func[48];                   /* function name                */
    char     errtext[48];                /* error text                   */
    } CTA_TRACE_ERROR_INFO;

DWORD NMSAPI ctaSetTraceLevel(
    CTAHD    ctahd,                      /* CTA context handle           */
    char    *svcname,                    /* name of service              */
    unsigned tracemask);                 /* tracemask for service        */

DWORD NMSAPI ctaLogTrace(
    CTAHD              ctahd,            /* CTA context handle           */
    CTA_TRACE_SEVERITY traceseverity,    /* info, warning, error         */
    unsigned           tracetag,         /* CTA_TRACETAG_xxxx            */
    void              *tracevalue,       /* bytes of trace data          */
    unsigned           tracesize);       /* number of bytes of data      */

DWORD NMSAPI ctaFindFile(
    char *filename,                      /* filename of file to find     */
    char *extension,                     /* extension to append          */
    char *envvar,                        /* path to search for file      */
    char *fullname,                      /* returned complete filename   */
    unsigned size);                      /* size of fullname             */




/*---------------------------------------------------------------------------
 * Version info and compatibilty level.  The compatibility level will be
 * increased if any release includes changes that require applications
 * to be re-compiled.
 *--------------------------------------------------------------------------*/
#define CTA_COMPATLEVEL  1

typedef struct                     /* CTA/Service revision info structure   */
    {
    DWORD size;                    /* size of the returned structure        */
    DWORD majorrev;                /* major revision of service/manager     */
    DWORD minorrev;                /* minor revision of service/manager     */
    char  builddate [12] ;         /* build date, "Mmm dd yyyy\0"           */
    DWORD compatlevel ;            /* Compatibility level of API            */
    } CTA_REV_INFO ;

DWORD NMSAPI ctaGetVersion (       /* Get CT Access version, build date,
                                      compat level                          */
  CTA_REV_INFO *info,              /*   pointer to your memory area         */
  DWORD         size );            /*   size of your data structure         */

DWORD NMSAPI ctaGetServiceVersion (/* Get version, build date,compat level
                                      of an initialized service.            */
    CTA_SERVICE_NAME *svcname,  /* Name of service to retrieve version info.*/
    CTA_REV_INFO     *info,     /* Reference to store service version info. */
    DWORD             size );   /* Size of reference buffer.                */

#ifdef __cplusplus
}
#endif

#endif
