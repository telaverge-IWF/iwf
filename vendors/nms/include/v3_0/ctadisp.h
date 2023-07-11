/*****************************************************************************
*                                  CTADISP.H
*
*  Contains defines, macros, and prototypes used by the CT Access internals.
*  You must include this file to all CT Access Manager modules.
*
*  Copyright (c) 1996  Natural MicroSystems Corp.  All rights reserved.
*****************************************************************************/

#ifndef CTADISP_INCLUDED
#define CTADISP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
  #include <nmstypes.h>
#endif

#ifndef CTADEF_INCLUDED
  #include <ctadef.h>
#endif

#ifndef TSIDEF_INCLUDED
  #include <tsidef.h>
#endif

/* *******************************************
 *
 *  CTA constants
 *
 * *******************************************/
#define CTA_SVCMGRNAME_LEN   3
#define CTA_MAXSVCNAME_LEN   5
#define CTA_MAXSVCID         0x100

/*====== CTA DISPATCHER EVENTS ==============================================*/
/* These are internal events for services to send to the dispatcher */
#define CTAEVN_DISP_OPEN_SERVICE_DONE          0x10002111
#define CTAEVN_DISP_CLOSE_SERVICE_DONE         0x10002112
#define CTAEVN_DISP_OPEN_CHANNEL_CONTEXT_DONE  0x10002113
#define CTAEVN_DISP_CLOSE_CHANNEL_CONTEXT_DONE 0x10002114

#define CTAEVN_DESTROYING_QUEUE                0x10002015


/* *******************************************
 *
 *  CTA SW Development constants/macros
 *
 * *******************************************/

  /* All xxxProcessCommand binding functions must pass back
     either SUCCESS, SUCCESS_RESPONSE or an error code */
#define SUCCESS_RESPONSE 1     /* SUCCESS with an accompanying event */

#ifndef OS2DEF_INCLUDED
  #ifndef FALSE
    #define FALSE 0
  #endif
  #ifndef TRUE	
    #define TRUE  1
  #endif
#endif

  /* Define MIN/MAX macro's here if they haven't been defined already
     by an OS include file. */
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

/*---------------------------------------------------------------------------
 * Macros to convert long to 2 shorts and vice versa
 *--------------------------------------------------------------------------*/
#ifdef SOLARIS_SPARC
#define CTA_LOWORD(l)     ((WORD)((DWORD)l))
#define CTA_HIWORD(l)     (((WORD*)(void*)&(l))[0])
#else
#define CTA_LOWORD(l)     ((WORD)((DWORD)l))
#define CTA_HIWORD(l)     (((WORD*)(void*)&(l))[1])
#endif

#define CTA_PACK2(l, h)   ((DWORD)(((WORD)(l)) | ((DWORD)((WORD)(h))) << 16))

#define CTA_CODE_SVCID(e) CTA_HIWORD(e)
#define CTA_CODE_ID(e)    CTA_LOWORD(e)

extern CTA_ERROR_HANDLER ctaErrorhandler;

#define CTABEGIN( A ) static char funcname[] = A

/*
 *  CTAERROR() - Passes a CTAHD, error code, and funcname (ref BEGIN())
 *               along with source line and file to internal error logger.
 *  APIERROR() - Passes a CTAHD, error code, and funcname to error handler.
 */
#define CTAERROR(crhd, err) \
        dispError((crhd),(err),CTA_SYS_SVCID,funcname,__FILE__, __LINE__,NULL,0)
#define CTALOGERROR(crhd, err, svcid) \
        dispError((crhd),(err),(svcid),funcname, __FILE__, __LINE__, NULL, 1)
#define CTALOGERRORINFO(crhd, err, svcid, info) \
        dispError((crhd),(err),(svcid),funcname, __FILE__, __LINE__, info, 1)
#define CTAAPIERROR(crhd, err) dispApiError((crhd), (err), funcname, NULL)
#define CTAAPIERRORINFO(crhd, err, info) \
        dispApiError((crhd), (err), funcname, info)
#define CTAFATALERROR(msg) \
        dispError(NULL_CTAHD, CTAERR_FATAL, CTA_SYS_SVCID, \
                  funcname, __FILE__, __LINE__, msg, 1)

#ifdef DEBUG
  void NMSAPI dispAssert (char *info, char *file, unsigned line);
  #define ASSERT(A) \
        if(!(A)) dispAssert(#A,__FILE__, __LINE__ )
  #ifndef STATIC
        #define STATIC
  #endif
#else
  #define ASSERT(A)
  #ifndef STATIC
        #define STATIC static
  #endif
#endif

/*======================= SERVICE/DISPATCHER STRUCTURE DEFINITIONS ===========*/

typedef struct _MESSAGE_ADDR
{
    WORD source;                /* Source service id                          */
    WORD destination;           /* Destination service id                     */
} MESSAGE_ADDR;

typedef struct _DISP_EVENT
{
    DWORD    id;                /* Event code (and source service id)         */
    CTAHD    ctahd;             /* CT Access context handle                   */
    DWORD    timestamp;         /* timestamp                                  */
    DWORD    userid;            /* user id (defined by ctaCreateContext)      */
    DWORD    size;              /* size of buffer if buffer != NULL           */
    void     *buffer;           /* buffer pointer                             */
    DWORD    value;             /* Event status or event-specific data        */
    DWORD    extra;             /* Extra internal event field                 */
    DWORD    reserved;          /* must be 0                                  */
    MESSAGE_ADDR addr;          /* Source/Destination service id              */
} DISP_EVENT;

typedef struct _DISP_COMMAND
{
    DWORD    id;                /* Command id (and destination service id)    */
    CTAHD    ctahd;             /* CT Access context handle                   */
    DWORD    size1;             /* If dataptr1 != NULL => size1 is buffer
                                   size - else  message specific data         */
    void     *dataptr1;         /* Data pointer                               */
    DWORD    size2;             /* If dataptr2 != NULL => size2 is buffer
                                   size - else  message specific data         */
    void     *dataptr2;         /* Data pointer                               */
    DWORD    size3;             /* If dataptr3 != NULL => size3 is buffer
                                   size - else  message specific data         */
    void     *dataptr3;         /* Data pointer                               */
    DWORD    reserved;          /* must be 0                                  */
    MESSAGE_ADDR addr;          /* Source/Destination service id              */
} DISP_COMMAND;

/* This is used by the dispatcher and services to pass events and commands.
   The type of message is defined uniquely by the code in the id field.       */
typedef struct _DISP_MESSAGE
{
    DWORD    id;                /* Event code (and source service id)         */
    CTAHD    ctahd;             /* CT Access context handle                   */
    DWORD    specific[6];       /* Fields specific to event or command        */
    DWORD    reserved;          /* must be 0                                  */
    MESSAGE_ADDR addr;          /* Source/Destination service id              */
} DISP_MESSAGE;

/* A Bit mask to set/test the MSB of the size fields to indicate a
 * buffer submitted for return */
#define CTA_VIRTUAL_BUF    0x80000000L

typedef DWORD (NMSSTDCALLPTR PFUNC)();

typedef struct _CTASVCMGR_FNS
    {
    DWORD size;
    DWORD (NMSSTDCALLPTR xxxDefineService)(
        char *svcname);

    DWORD (NMSSTDCALLPTR xxxAttachServiceManager)(
        CTAQUEUEHD ctaqueuehd, unsigned mode, void **queuecontext);

    DWORD (NMSSTDCALLPTR xxxDetachServiceManager)(
        CTAQUEUEHD ctaqueuehd, void *queuecontext);

    DWORD (NMSSTDCALLPTR xxxOpenServiceManager)(
        CTAHD ctahd, void *queuecontext, void **mgrcontext);

    DWORD (NMSSTDCALLPTR xxxCloseServiceManager)(
        CTAHD ctahd, void *mgrcontext);

    DWORD (NMSSTDCALLPTR xxxOpenService)(
        CTAHD ctahd, void *mgrcontext, char *svcname,
        unsigned svcid, CTA_MVIP_ADDR *mvipaddr, CTA_SERVICE_ARGS *svcargs);

    DWORD (NMSSTDCALLPTR xxxCloseService)(
        CTAHD ctahd, void *mgrcontext, char *svcname, unsigned svcid);

    DWORD (NMSSTDCALLPTR xxxProcessEvent)(
        CTAHD ctahd, void *mgrcontext, DISP_EVENT *ctaevt);

    DWORD (NMSSTDCALLPTR xxxProcessCommand)(
        CTAHD ctahd, void *mgrcontext, DISP_COMMAND *ctaevt);



    /* xxxAddRTC() and xxxRemoveRTC() are reserved for future use
     */
    DWORD (NMSSTDCALLPTR xxxAddRTC)(
        CTAHD ctahd, void *mgrcontext,
        void *rtccondition, void *rtcaction);

    DWORD (NMSSTDCALLPTR xxxRemoveRTC)(
        CTAHD ctahd, void *mgrcontext,
        void *rtccondition, void *rtcaction);

    const char * (NMSSTDCALLPTR xxxGetText)(
        unsigned code);

    DWORD (NMSSTDCALLPTR xxxFormatMessage)(
        DISP_MESSAGE *pmsg, char *msgtext, unsigned size, char *indent);

    DWORD (NMSSTDCALLPTR xxxSetTraceLevel)(
        CTAHD ctahd, void *mgrcontext, unsigned svcid, unsigned tracemask);

    DWORD (NMSSTDCALLPTR xxxFormatTraceBuffer)(
        unsigned tracetag,
        void *inbuffer, unsigned insize,
        char *outbuffer, unsigned outsize);

    PFUNC (NMSSTDCALLPTR xxxGetFunctionPointer)(
        unsigned ordinal);

    } CTASVCMGR_FNS;

/* Is this portable or should we use defines ??? and DWORD as return value */
typedef enum {CTA_PASS_EVENT=1,
              CTA_CONSUME_EVENT,
              CTA_CONSUME_EVENT_UNREGISTER,
              CTA_CONSUME_EVENT_RETURN}
        EVENT_HANDLER_RETCODE;

typedef EVENT_HANDLER_RETCODE
              (NMSSTDCALLPTR EVENT_HANDLER)(CTAHD ctahd,
                                            DISP_EVENT *ctaevt,
                                            void *arg);

/*======================= REVISION STRUCTURES ==============================*/
#define DISP_COMPATLEVEL  1

typedef struct                     /* CTA internal revision info structure  */
{
    DWORD size;                    /* size of the returned structure        */
    DWORD majorrev;                /* major revision of service/manager     */
    DWORD minorrev;                /* minor revision of service/manager     */
    char  builddate [12];          /* build date, "Mmm dd yyyy\0"           */
    DWORD reqdisplevel;            /* Required compat level of Dispatcher   */
    DWORD expapilevel;             /* Exported compat level of Service API  */
    DWORD expspilevel;             /* Exported compat level of Service SPI  */
} CTAINTREV_INFO ;

typedef struct                     /* CTA required service info structure   */
{
    char  *svcname;                /* Name of required service              */
    DWORD svcid;                   /* Service id of required service        */
    DWORD reqspilevel;             /* Required compat level of Service SPI  */
} CTAREQSVC_INFO ;

#define CTAENTRY            /*  keep compilers happy */
#define CTATRACE( A )

/*--------------------------------------------------------------------------*/
/*  The CT Access trace structures                                          */
/*--------------------------------------------------------------------------*/
/* The trace message/buffer has a fixed size which is now 52 bytes -
   large enough to hold an AG message or a dispatcher event/command -
   if the data is larger than 1 DWORD then tracebuffers contains the number of
   CTA_TRACE_BUFFER structures that follow in the trace buffer - this keeps
   the circular trace mechanism simple and less expensive for all the writers
   at the expense of lost bytes when messages are small - and piecing together
   by the trace utility to recover multiple buffers. */
/* If tracebuffers is 0 then no buffers follow and tracesize may be
   used for the single trace value. */
typedef struct
{
    CTAHD              ctahd;        /* CT Access context handle             */
    char               ctahd_string[CTA_CONTEXT_NAME_LEN];
                                     /* context name string                  */
    DWORD              pid;          /* process id of ctahd                  */
    DWORD              tid;          /* thread id of writer if available     */
    DWORD              uid;          /* user assigned context id             */
    WORD               source;       /* source service id                    */
    WORD               severity;     /* CTA_TRACE_SEVERITY_INFO, ...         */
    DWORD              timestamp;    /* ctaLogTrace Timestamp                */
    WORD               mstime;       /* low word of ms ticks counter         */
    WORD               reserved;     /* Should be 0                          */
    DWORD              tracetag;     /* Generic or specific trace tag        */
    DWORD              tracebuffers; /* # of buffers following               */
    DWORD              tracesize;    /* valid size contained in buffers
                                        if tracebuffers=0 this is only value */
} CTA_TRACE_MESSAGE;

/* This must be the same size as a trace message and should be
   larger than most command and event structures */
typedef struct
{
    BYTE buffer[sizeof(CTA_TRACE_MESSAGE)];
} CTA_TRACE_BUFFER;

#define CTA_TRACE_MSGSIZE(msgptr) (sizeof(CTA_TRACE_MESSAGE) + \
        (((msgptr)->tracebuffers) * sizeof(CTA_TRACE_BUFFER)))

/*======================= FUNCTION PROTOTYPES ==============================*/

DWORD NMSAPI dispError(
    CTAHD ctahd,
    DWORD errorcode,
    unsigned svcid,
    char *func,
    char *file,
    unsigned lineno,
    char *info,
    unsigned logerror);

DWORD NMSAPI dispApiError(
    CTAHD ctahd,
    DWORD errcode,
    char *func,
    char *info);

DWORD NMSAPI dispLogTrace(
    CTAHD              ctahd,            /* CTA context handle           */
    unsigned           tracesource,      /* source service id            */
    CTA_TRACE_SEVERITY traceseverity,    /* info, warning, error         */
    unsigned           tracetag,         /* CTA_TRACETAG_xxxx            */
    void              *tracevalue,       /* bytes of trace data          */
    unsigned           tracesize);       /* number of bytes of data      */

DWORD NMSAPI dispGetTracePointer(volatile DWORD **trace_pointer);

/* dispatcher functions available to service managers and services */
DWORD NMSAPI dispRegisterServiceManager(
    const char           *svcmgrname,
    CTASVCMGR_FNS        *svcmgrfns,
    const CTAINTREV_INFO *previnfo);

DWORD NMSAPI dispRegisterService(
    const char           *svcname,
    unsigned              svcid,
    const char           *svcmgrname,
    const CTAINTREV_INFO *previnfo,
    const CTAREQSVC_INFO  preqsvc[],
    unsigned              nreqsvcs,
    const CTAPARM_DESC  * const *stdparmdesc,
    const CTAPARM_DESC  * const *extparmdesc);

DWORD NMSAPI dispRegisterWaitObject(
    CTAQUEUEHD ctaqueuehd,
    CTA_WAITOBJ *waitobj,
    CTA_WAITFN waitfn,
    void      *arg);

DWORD NMSAPI dispUnregisterWaitObject(
    CTAQUEUEHD ctaqueuehd,
    CTA_WAITOBJ *waitobj);

DWORD NMSAPI dispFindWaitObject(CTAQUEUEHD ctaQueueHd,
                                CTA_WAITOBJ* pWaitObj,
                                CTA_WAITOBJ** ppWaitObjFound);

DWORD NMSAPI dispGetQueueHandle(
    CTAHD       ctahd,
    CTAQUEUEHD *ctaqueuehd);

DWORD NMSAPI dispQueueEvent(
    DISP_EVENT *ctaevt);

DWORD NMSAPI dispQueueCommand(
    DISP_COMMAND *ctacmd);

DWORD NMSAPI dispSendCommand(
    DISP_COMMAND *ctacmd);

DWORD NMSAPI dispMakeAndQueueEvent(
    CTAHD    ctahd,
    unsigned id,
    unsigned value,
    unsigned source,
    unsigned destination);

DWORD NMSAPI dispSetParmByName( /* Modifies the value of a default parm     */
    CTAHD    ctahd,             /* CT Access context handle                 */
    char    *parmname,          /* parameter name, or parameter field       */
    void    *buffer,            /* pointer to your parameter memory         */
    unsigned size);             /* size of your memory area                 */

DWORD NMSAPI dispGetParmByName( /* Retrieves the value of a default parm    */
    CTAHD    ctahd,             /* CT Access context handle                 */
    char    *parmname,          /* parameter name, or parameter field       */
    void    *buffer,            /* pointer to your parameter memory         */
    unsigned size);             /* size of your memory area                 */

DWORD NMSAPI dispCheckParmByName( /* Verifies the existence of and retrieves
                                     the value of a default parm  */
    CTAHD    ctahd,             /* CT Access context handle                 */
    char    *parmname,          /* parameter name, or parameter field       */
    void    *buffer,            /* pointer to your parameter memory         */
    unsigned size);             /* size of your memory area                 */

DWORD NMSAPI dispGetParms(      /* Returns values of call resource parms    */
    CTAHD    ctahd,             /* CT Access context handle                 */
    unsigned parmid,            /* parameter id                             */
    void    *buffer,            /* pointer to your parameter memory         */
    unsigned size);             /* size of your memory area                 */

DWORD NMSAPI dispGetText(       /* Returns text for err, reason, cmd, evt   */
    DWORD    code,              /* passed code                              */
    char    *buffer,            /* returned text                            */
    unsigned size);             /* passed max text size                     */

/* dispatcher functions to help manage API side handles */
DWORD NMSAPI dispCreateHandle(
    CTAHD     ctahd,
    unsigned  svcid,
    unsigned  value,
    unsigned *hd);

DWORD NMSAPI dispDestroyHandle(
    unsigned hd);

DWORD NMSAPI dispGetHandleValue(
    unsigned  hd,
    CTAHD    *ctahd,
    unsigned *value);

DWORD NMSAPI dispSetHandleValue(
    unsigned hd,
    unsigned value);

/*----------------------- [eof] --------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif
