/******************************************************************************
* FILENAME:               nfxdef.h
*
* DESCRIPTION:
*        Exposed API, parm structures, etc for the FAX manager.
*
* CALLING FORMAT AND ARGUMENT DESCRIPTIONS:
*
* OTHER DATA ACCESS, OTHER ACTIONS:
*
*
* Copyright 1995-1998 by Natural Microsystems.  All rights reserved.
*****************************************************************************/

#ifndef __NFXDEF_INCLUDED__
#define __NFXDEF_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/* version of this header file */
#define NFX_MAJOR_REVISION_ID 3
#define NFX_MINOR_REVISION_ID 30

#define NFX_SVCID           0x05

/*-- parameter name definitions for nfxBindGetParm and nfxBindSetParm */
#define NFXPRM_DOC_SET      0x50001
#define NFXPRM_TRANSMIT     0x50002
#define NFXPRM_RECEIVE      0x50003
#define NFXPRM_CONVERT      0x50004

/*-- Data Rate Symbols for min rx rate and min tx rate */

/* Symbols for transmit_min_rate and rx_min_rate parameters */
#define NFX_BIT_RATE_2400           0
#define NFX_BIT_RATE_4800           1
#define NFX_BIT_RATE_7200           2
#define NFX_BIT_RATE_9600           3
#define NFX_BIT_RATE_12000          4
#define NFX_BIT_RATE_14400          5




/*-- Modem Type Symbols for receive_modem_type in NFX_RECEIVE_PARMS and
  transmit_modem_type in NFX_TRANSMIT_PARMS */
#define NFX_MODEM_TYPE_V27          0   /* v27 only              */
#define NFX_MODEM_TYPE_V29          1   /* v29 and v27           */
#define NFX_MODEM_TYPE_V33          2   /* v33, v29 and v27      */
#define NFX_MODEM_TYPE_V17          3   /* v17, v33, v29 and v27 */


/* Bad Line Actions */
#define NFX_BAD_LINE_ACTION_NONE    0   /* No action             */
#define NFX_BAD_LINE_ACTION_DROP    1   /* drop the bad line     */
#define NFX_BAD_LINE_ACTION_REPT    2   /* repeat the bad line   */
#define NFX_BAD_LINE_ACTION_TICK    3   /* mark the bad line in the margins */
                    
/* TIFF types */
#define NFX_ENCODE_1D               0
#define NFX_ENCODE_2D               1
#define NFX_ENCODE_MMR              2
#define NFX_ENCODE_BITMAP           3
#define NFX_ENCODE_TIFF_S           4

/* Resolution definitions */
#define NFX_RESOLUTION_LOW          0
#define NFX_RESOLUTION_HIGH         1
#define NFX_RESOLUTION_SUPER_HIGH   2

/* Page Width's */
#define NFX_PAGE_WIDTH_A4           0
#define NFX_PAGE_WIDTH_B4           1
#define NFX_PAGE_WIDTH_A3           2

/* booleans */
#define NFX_NO                      0
#define NFX_YES                     1
#define NFX_CUSTOM                  2

/* queue types */
#define NFX_DOC_INVALID             0
#define NFX_DOC_TRANSMIT            1
#define NFX_DOC_RECEIVE             2

/* on the fly mode values */
#define NFX_OTF_NEVER               0
#define NFX_OTF_ALWAYS              1
#define NFX_OTF_ONLY_IF_FAIL        2

/* file types for convert */
#define NFX_TIFF_F                  0
#define NFX_TIFF_S                  1

/* retrain actions */
#define NFX_RTN_NEXT_PAGE           0
#define NFX_RTN_REPEAT_PAGE         1

/* fax status modes */
#define NFX_MODE_IDLE               0  	/* Fax is waiting to detect a remote */
                                        /*   end FAX machine.                */
#define NFX_MODE_NEGOTIATING        1  	/* FAX has been detected and exchange*/
                                        /*   of capabilities is in progress  */
#define NFX_MODE_TRANSMITING        2  	/* FAX data is being transmitted     */
#define NFX_MODE_RECEIVING          3  	/* FAX data is being received        */
#define NFX_MODE_DISCONNECTING      4   /* FAX is in process of disconnect   */
                                        /*   and shutdown handshake          */
#define NFX_MODE_FINISHED           5   /* FAX processing has completed. Line*/
                                        /*   control has been returned to the*/
                                        /*   application.                    */
#define NFX_MODE_CONNECTING         6  	/* Tx:Waiting for DIS. Rx: Sent DIS  */

/*************************************************************
 This section defines sizes for a few objects of the NFX API. 
 These sizes should match corresponding sizes in the FAX layer */

#define         NFX_MAX_SUB         24  /* Sub-address string length   */
#define         NFX_MAX_SID         24  /* Subscriber ID string length */
#define         NFX_MAX_NSF         100 /* Nonstandard facilities string
                                              length */
#define         NFX_MAX_DIS         12
#define         NFX_MAX_DCS         12  /* MAX_DCS_LEN      9*/

#define         NFX_FILENAME_MAX    512
#define         NFX_MAX_HEADER      80

/***************************************************************
 This section identifies the structures and data types particular to the
FAX manager API. */

typedef void *NFX_QUEUE_HANDLE;


typedef struct 
{
    DWORD size;
        
    DWORD modemtype;        /* NFX_MODEM_TYPE_V17 or NFX_MODEM_TYPE_V33 or
                               NFX_MODEM_TYPE_V27 or NFX_MODEM_TYPE_V29 */
    DWORD minrate;          /* NFX_BIT_RATE_2400 or NFX_BIT_RATE_4800  or
                               NFX_BIT_RATE_7200 or NFX_BIT_RATE_9600   */
    DWORD resolution;       /* NFX_RESOLUTION_HIGH,NFX_RESOLUTION_LOW or
                               NFX_RESOLUTION_SUPER_HIGH                */
    DWORD encoding;         /* NFX_ENCODE_1D or NFX_ENCODE_2D or 
                               NFX_ENCODE_MMR                           */
    DWORD pagewidth;        /* NFX_PAGE_WIDTH_A4 or NFX_PAGE_WIDTH__B4 or  
                               NFX_PAGE_WIDTH_A3                        */
    DWORD OTFmode;          /* NFX_OTF_NEVER or NFX_OTF_ALWAYS or
                               NFX_OTF_ONLY_IF_FAIL                     */
    DWORD useECM;           /* NFX_YES or NFX_NO                        */
    DWORD useCNG;           /* NFX_YES or NFX_NO                        */
    DWORD PRIenabled;       /* NFX_YES or NFX_NO                        */
    DWORD timeout;          /* number of seconds to wait for receiver   */
    DWORD retrainaction;    /* NFX_RTN_REPEAT_PAGE or NFX_RTN_NEXT_PAGE */
    DWORD addheader;        /* NFX_YES, NFX_NO or NFX_CUSTOM            */
    INT32 level;            /* dBm level for transmission (-150 to -60) */
    INT32 threshold;        /* lowest dBm level for receive             */
    DWORD NSFlength;        /*  length of NSF field or 0 if none        */
    char SID[NFX_MAX_SID];  /* Subscriber ID string                     */
    BYTE NSF[NFX_MAX_NSF];  /* default NSF for session                  */
    char custom_header[NFX_MAX_HEADER]; 
                            /* customizable fax header                  */
    char SUB[NFX_MAX_SUB];  /* Sub-address string                       */
    DWORD useSUBADD;        /* NFX_YES or NFX_NO                        */
    DWORD txrate;           /* NFX_BIT_RATE_2400  or NFX_BIT_RATE_4800  or
                               NFX_BIT_RATE_7200  or NFX_BIT_RATE_9600  or
                               NFX_BIT_RATE_12000 or NFX_BIT_RATE_14400 */
    DWORD ForceRate;        /* NFX_YES or NFX_NO                        */
} NFX_TRANSMIT_PARMS;


typedef struct 
{
    DWORD size;   
    DWORD modemtype;        /*  NFX_MODEM_TYPE_V27 or NFX_MODEM_TYPE_V29.  
                                Advertised capabilities for fax receiver  */
    DWORD minrate;          /*  NFX_BIT_RATE_2400  or NFX_BIT_RATE_4800  or 
                                NFX_BIT_RATE_7200  or  NFX_BIT_RATE_9600  */
    DWORD resolution;       /*  NFX_RESOLUTION_HIGH,NFX_RESOLUTION_LOW or
                                NFX_RESOLUTION_SUPER_HIGH                 */
    DWORD encoding;         /*  NFX_ENCODE_1D, NFX_ENCODE_2D, NFX_ENCODE_MMR,
                                or NFX_ENCODE_TIFF_S                      */
    DWORD pollingenabled;   /*  NFX_YES  or  NFX_NO                       */
    DWORD badlineaction;    /*  NFX_BAD_LINE_ACTION_NONE  or
                                NFX_BAD_LINE_ACTION_DROP  or
                                NFX_BAD_LINE_ACTION_REPT  or  
                                NFX_BAD_LINE_ACTION_TICK                  */
    DWORD pagewidth;        /*  NFX_PAGE_WIDTH_A4 or NFX_PAGE_WIDTH__B4 or  
                                NFX_PAGE_WIDTH_A3                         */
    DWORD OTFmode;          /*  NFX_OTF_NEVER or NFX_OTF_ALWAYS or
                                NFX_OTF_ONLY_IF_FAIL                      */
    DWORD useECM;           /*  NFX_YES or NFX_NO                         */
    DWORD lineerrors;       /*  % line errors before retrain negative     */
    INT32 level;            /*  dBm level for transmission (-150 to -60)  */
    INT32 threshold;        /*  lowest dBm level for receive              */
    DWORD NSFlength;        /*  Length of NSF field or 0 if none          */
    char SID[NFX_MAX_SID];  /*  Subscriber ID string                      */
    BYTE NSF[NFX_MAX_NSF];  /*  default NSF for session                   */
    char SUB[NFX_MAX_SUB];  /*  Sub-address string                        */
    DWORD useSUBADD;        /*  NFX_YES or NFX_NO                         */
} NFX_RECEIVE_PARMS;



typedef struct 
{
    DWORD size;
    DWORD docnum;                     /* Entry number in queue             */
    DWORD processedstatus;            /* Has this document been sent?      */
    DWORD lasterror;                  /* Last error code (if any) for doc  */
    DWORD pagecount;                  /* Number of pages (for receive)     */
    DWORD startpage;                  /* Page to start at (for retransmit) */
    DWORD lastpagesent;               /* Last page # successfully sent     */
    DWORD retranscount;               /* Number of retries                 */
    DWORD docencoding;                /* 1D (MH) or 2D (MR) or MMR         */
    DWORD docresolution;              /* Resolution: low, high, superhigh  */
    DWORD docwidth;                   /* Width: A4, A3, B4                 */
    DWORD negotiatedencoding;         /* Encoding used for transfer        */
    DWORD negotiatedrate;             /* Baud rate used for transfer       */
    DWORD negotiatedresolution;       /* Resolution used for transfer      */
    DWORD negotiatedwidth;            /* Page width used for transfer      */
    DWORD badlinecount;               /* Number of bad lines in doc received.
                                         Or,in ECM mode bad frames txed/rxed*/ 
    DWORD doctime;                    /* time document processing started  */
    DWORD duration;                   /* seconds elapsed processing doc    */
    char  filename[NFX_FILENAME_MAX]; /* filename arg from nfxEnqueueDoc   */
    DWORD modemtype;                  /* Modem used to transfer doc        */

} NFX_DOC_STATUS;


typedef struct 
{
    DWORD size;                 /* sizeof(NFX_DOC_PARMS)                  */
    DWORD resolution;           /* NFX_RESOLUTION_HIGH,NFX_RESOLUTION_LOW
                                   or NFX_RESOLUTION_SUPER_HIGH           */
    DWORD encoding;             /* NFX_ENCODE_1D or NFX_ENCODE_2D or 
                                   NFX_ENCODE_MMR                         */ 
    DWORD pagewidth;            /* NFX_PAGE_WIDTH_A4 or NFX_PAGE_WIDTH_B4 or
                                   NFX_PAGE_WIDTH_A3                      */
} NFX_DOC_PARMS;



typedef struct 
{
    DWORD size;
    DWORD type;                 /*  NFX_TIFF_F or NFX_TIFF_BI              */
    DWORD resolution;           /*  NFX_RESOLUTION_HIGH,NFX_RESOLUTION_LOW or 
                                    NFX_RESOLUTION_SUPER_HIGH              */
    DWORD encoding;             /*  NFX_ENCODE_1D or NFX_ENCODE_2D  or
                                    NFX_ENCODE_MMR                         */
    DWORD pagewidth;            /*  NFX_PAGE_WIDTH_A4 or NFX_PAGE_WIDTH_B4 or  
                                    NFX_PAGE_WIDTH_A3                      */
    DWORD badlineaction;        /*  NFX_BAD_LINE_ACTION_NONE  or 
                                    NFX_BAD_LINE_ACTION_DROP  or        
                                    NFX_BAD_LINE_ACTION_REPT  or  
                                    NFX_BAD_LINE_ACTION_TICK               */
} NFX_CONVERT_PARMS;


typedef struct 
{
    DWORD size;
    DWORD rate;            
    DWORD ecm;             /*  error correction mode NFX_YES or NFX_NO      */
    DWORD resolution;    
    DWORD encoding;         
    DWORD pagewidth;     
    DWORD mode;            /*  NFX_MODE_IDLE or NFX_MODE_NEGOTIATING or     */
                           /*  NFX_MODE_TRANSMITING or NFX_MODE_RECEIVING or*/
                           /*  NFX_MODE_DISCONNECTING or NFX_MODE_FINISHED  */
    DWORD error;           /*  Last error code generated                    */
    DWORD docnumber;       /*  Current document in progress                 */
    DWORD pagenumber;      /*  Current page of the document                 */
    DWORD badlines;        /*  Number of bad lines (or bad frames in 
                               ECM mode) during current session             */
    char filename[NFX_FILENAME_MAX]; /*  Name of current file processed     */
    char remoteSID[NFX_MAX_SID];     /*  Received SID from remote station   */
    BYTE remoteNSF[NFX_MAX_NSF];/*  Received NSF from remote station        */
                            /* Receive modem metrics                        */
    DWORD snr;              /* Signal to Noise Ratio                        */
    DWORD rx_training_zeros;/* Training zeros (in milliseconds)             */
    char remoteSUB[NFX_MAX_SUB];/* Received Sub-adreess string from remote  */
    DWORD sub_sent;         /* set if sub-address frame is sent to remote station */
    DWORD modemtype;        /* Modem used to transfer a doc                 */
} NFX_FAX_STATUS;



typedef struct 
{
    DWORD size;
    DWORD resolution;       
    DWORD encoding;         
    DWORD pagewidth;        
    DWORD lines;                /* number of lines on the page     */
    DWORD badlines;             /* number of bad lines on the page */
} NFX_CHECK_STATUS;





/***************************************************************************
 In this section, the function API is exposed including a brief description
of arguments and message packing with each function. */


/*
nfxSendFax
    ctahd                   TSA system port identifier
    send_queue_handle       queue of documents to send
    ptr_transmit_parms      points to parameters for sending FAX documents
    receive_queue_handle    queue to receive polled documents or NULL if none
    ptr_receive_parms       points to parameters for receiving FAX documents

*/
extern DWORD NMSAPI nfxSendFax(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE send_queue_handle,
    NFX_TRANSMIT_PARMS *ptr_transmit_parms,
    NFX_QUEUE_HANDLE receive_queue_handle,
    NFX_RECEIVE_PARMS *ptr_receive_parms  
    );



/*
nfxReceiveFax
    ctahd                   TSA system port identifier
    receive_queue_handle    queue to receive docuements
    ptr_receive_parms       points to parameters for receiving FAX documents

*/
extern DWORD NMSAPI nfxReceiveFax(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE receive_queue_handle,
    NFX_RECEIVE_PARMS *ptr_receive_parms  
    );


/*
nfxAnswerFaxPoll
    ctahd                   TSA system port identifier
    send_queue_handle       queue of documents to send
    ptr_send_parms          points to parameters for sending FAX documents
*/
extern DWORD NMSAPI nfxAnswerFaxPoll(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE send_queue_handle,
    NFX_TRANSMIT_PARMS *ptr_transmit_parms 
    );


/*
nfxStopSession
    ctahd                   TSA system port identifier

*/
extern DWORD NMSAPI nfxStopSession(
    CTAHD ctahd 
    );


/*
nfxGetLicense
    ctahd                   TSA system port identifier
NOTE: This API is obsolete and is included for backward compatibility
      with versions prior to NaturalFax 3.2
*/
extern DWORD NMSAPI nfxGetLicense(
    CTAHD ctahd  
    );


/*
nfxReleaseLicense
    ctahd                   TSA system port identifier
NOTE: This API is obsolete and is included for backward compatibility
      with versions prior to NaturalFax 3.2
*/
extern DWORD NMSAPI nfxReleaseLicense(
    CTAHD ctahd  );


/*
nfxCreateQueue
    ctahd                   TSA system port identifier
    queue_type              set to NFX_RCV_QUEUE or NFX_SEND_QUEUE
    ptr_queue_handle        points to a location to receive a valid queue 
                                handle on a successful return
*/
extern DWORD NMSAPI nfxCreateQueue(
    CTAHD ctahd,
    int queue_type,
    NFX_QUEUE_HANDLE *ptr_queue_handle 
    );


/*
nfxEnqueueDoc
    ctahd                   TSA system port identifier
    queue_handle            identifies a valid queue to receive the new 
                                document
    file_name               name of existing file to send or file to create
                                on receive
    ptr_doc_parms           points to structure of parms with document info
    ptr_doc_number          points to a location to receive a valid document
                              doc number on a successful return
*/
extern DWORD NMSAPI nfxEnqueueDoc(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE queue_handle,
    char *file_name,
    NFX_DOC_PARMS *ptr_doc_parms,
    DWORD *ptr_doc_number  
    );


/*
nfxDestroyQueue
    ctahd                   TSA system port identifier
    queue_handle            identifies the queue to be freed
*/
extern DWORD NMSAPI nfxDestroyQueue(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE queue_handle  
    );


/*
nfxResetQueue
    ctahd                   TSA system port identifier
    queue_handle            identifies which queue to reset
*/
extern DWORD NMSAPI nfxResetQueue(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE queue_handle  
    );


/*
nfxCheckTiff
    ctahd                   TSA system port identifier
    file_name               name of existing file to check for TIFF format
    found_pages             points to place to return number of pages found
    tracked_pages           indicates number of NFX_CHECK_STATUS structures in
                                page_array to be filled; maybe zero
    page_array              returned information about each page
*/
extern DWORD NMSAPI nfxCheckTIFF(
    CTAHD ctahd,
    char *file_name,
    DWORD *found_pages,
    DWORD tracked_pages,
    NFX_CHECK_STATUS *page_array
    );


/*
nfxGetLicenseStatus
    ctahd                   TSA system port identifier
    ptr_max_configured      points to a location to receive the maximum 
                            number of FAX ports authorized for the system
    ptr_number_in_use       points to a location to receive a count of FAX 
                            ports in use

NOTE: This API is obsolete and is included for backward compatibility
      with versions prior to NaturalFax 3.2
*/
extern DWORD NMSAPI nfxGetLicenseStatus(
    CTAHD ctahd,
    DWORD *ptr_max_configured,
    DWORD *ptr_number_in_use  
    );


/*
nfxGetDocStatus
    ctahd                   TSA system port identifier
    doc_number              number of document in queue
    doc_status              points to a structure to receive the current
                              internal documenbt status
*/
extern DWORD NMSAPI nfxGetDocStatus(
    CTAHD ctahd,
    NFX_QUEUE_HANDLE queue_handle,
    DWORD doc_number,
    NFX_DOC_STATUS *doc_status
    );


/*
nfxGetSessionStatus
    ctahd              TSA system port identifier
    ptr_fax_status           points to a structure to receive the current
                              internal status
*/
extern DWORD NMSAPI nfxGetSessionStatus(
    CTAHD ctahd,
    NFX_FAX_STATUS *ptr_fax_status  
    );


/*
nfxConvertFileDirect
    ctahd                   TSA system port identifier
    input_file              Existing file in a variety of formats input to the
                            conversion
    output_file             Name of file to be created to receive the 
                            conversion output
    ptr_convert_parms       Points to a structure of parameters which 
                            identifies the expected input format and 
                            selections options for the output format
    ptr_converted_pages     Points to a location to receive a count of pages
                            converted
*/
extern DWORD NMSAPI nfxConvertFileDirect(
    CTAHD ctahd,
    char *input_file,
    char *output_file,
    NFX_CONVERT_PARMS *ptr_convert_parms,
    DWORD *ptr_converted_pages  
    );


/*
nfxSplitFile
    ctahd                   TSA system port identifier
    input_file              Existing file in a variety of formats input to the
                            conversion
    number_out              The number of output files to split into
    output_files            Names of files to be created to receive the pages
    found_pages             Points to a location to receive a count of pages
                            processed
*/
extern DWORD NMSAPI nfxSplitFile(
    CTAHD ctahd,
    char *input_file,
    DWORD number_out,
    char *output_files[],
    DWORD *found_pages 
    );


/*
nfxMergeFile
    ctahd              TSA system port identifier
    output_file              file to be created and filled with all pages
    number_in                the number of input files to merge from
    input_files              names of files from which pages are read in order
    found_pages              points to a location to receive a count of pages
                              processed
*/
extern DWORD NMSAPI nfxMergeFile(
    CTAHD ctahd,
    char *output_file,
    DWORD number_in,
    char *input_files[],
    DWORD *found_pages 
    );


/*********************************************************
    Parameters for nfxSetTraceMask
*********************************************************/
#define NFX_TRACE_DEFAULT           0x000c00
#define NFX_TRACE_ALL               0x000f00


/*********************************************************
 In this next section, the message type codes for each of the FAX commands
is exposed.  Each consists of a common FAX manager ID in the upper 16 bits
with a simple sequential code assignment in the lower 16. 
**********************************************************/


#define NFXMGR_ID                   0x05
#define NFXCMD                      ((NFXMGR_ID << 16) + 0x3000)

#define NFXCMD_SEND_FAX             NFXCMD+1
#define NFXCMD_RECEIVE_FAX          NFXCMD+2
#define NFXCMD_ANSWER_FAX_POLL      NFXCMD+3
#define NFXCMD_STOP_SESSION         NFXCMD+4
#define NFXCMD_GET_LICENSE          NFXCMD+5
#define NFXCMD_RELEASE_LICENSE      NFXCMD+6
#define NFXCMD_CREATE_QUEUE         NFXCMD+7
#define NFXCMD_ENQUEUE_DOC          NFXCMD+8
#define NFXCMD_DESTROY_QUEUE        NFXCMD+9
#define NFXCMD_RESET_QUEUE          NFXCMD+10
#define NFXCMD_CHECK_TIFF           NFXCMD+11
#define NFXCMD_GET_LICENSE_STATUS   NFXCMD+12
#define NFXCMD_GET_SESSION_STATUS   NFXCMD+13
#define NFXCMD_CONVERT_FILE_DIRECT  NFXCMD+14
#define NFXCMD_GET_DOC_STATUS       NFXCMD+15
#define NFXCMD_SPLIT_FILE           NFXCMD+16
#define NFXCMD_MERGE_FILE           NFXCMD+17


#define NFXEVN                      ((NFXMGR_ID << 16) + 0x2000)
#define NFXEVN_PAGE_BEGIN           NFXEVN+1
#define NFXEVN_PAGE_END             NFXEVN+2
#define NFXEVN_DOC_BEGIN            NFXEVN+3
#define NFXEVN_DOC_END              NFXEVN+4
#define NFXEVN_POLLED               NFXEVN+5
#define NFXEVN_PROCEDURE_INTERRUPT  NFXEVN+6
#define NFXEVN_CANNOT_OPEN_FILE     NFXEVN+7
#define NFXEVN_SEND_STARTED         NFXEVN+8
#define NFXEVN_RECEIVE_STARTED      NFXEVN+9
#define NFXEVN_REMOTE_IDENTIFIED    NFXEVN+10
#define NFXEVN_SESSION_DONE         NFXEVN+11


/* NFXEVN_DOC_END values on receive */
#define NFX_T30_EOM                     1
#define NFX_T30_EOP                     2

/* NFXERR_ definitions */
#define NFXERR                          ((NFXMGR_ID << 16) + 0x200)
#define NFXERR_CONNECT_FAILED           0x050201
#define NFXERR_NEGOTIATION_FAILED       0x050202
#define NFXERR_NO_MORE_LICENSES         0x050203
#define NFXERR_NO_LICENSE               0x050204
#define NFXERR_LICENSE_ALREADY_ALLOC    0x050205
#define NFXERR_QUEUE_EMPTY              0x050206
#define NFXERR_BAD_FILE_FORMAT          0x050207
#define NFXERR_QUEUE_TOO_LATE           0x050208
#define NFXERR_SESSION_FAILED           0x050209
#define NFXERR_OPEN_QUEUE_FAILED        0x05020a
#define NFXERR_BAD_PAGE_SIZE            0x05020b
#define NFXERR_CONVERSION_REQUIRED      0x05020c
#define NFXERR_CHECK_BAD_LINES          0x05020d
#define NFXERR_CHECK_DIFF_ATTRIB        0x05020e
#define NFXERR_NO_MORE_DOCUMENTS        0x05020f
#define NFXERR_RATE_TOO_LOW             0x050210
#define NFXERR_BUFFER_UNDERRUN          0x050211
#define NFXERR_NO_MODEMS                0x050213
#define NFXERR_NO_PPM                   0x050214
#define NFXERR_NO_PPM_RESPONSE          0x050215
#define NFXERR_INCOMPATIBLE_RECEIVER    0x050216
#define NFXERR_PROTOCOL_ERROR           0x050217
#define NFXERR_FAX_SERVICE              0x050219
#define NFXERR_FXM_SERVICE              0x05021a
#define NFXERR_REMOTE_DCN               0x05021b
#define NFXERR_NO_REMOTE                0x05021c
#define NFXERR_CARRIER_LOST             0x05021d
#define NFXERR_RETRAIN_NEGATIVE         0x05021e
#define NFXERR_T5_TIMEOUT				0x05021f 


#define NFXERR_INTERNAL_ERROR_LO        0x058000
#define NFXERR_INTERNAL_ERROR_HI        0x05ffff
#define NFXERR_INTERNAL_ERROR           0x058000

#ifdef __cplusplus
}
#endif

#endif
