/*****************************************************************************
*                                  HSMDEF.h
*
*  This header file describes application HSM interface to HS Manager
*
*
* Copyright (c) 1997, 1998  Natural MicroSystems Corp.  All rights reserved.
*****************************************************************************/

#ifndef	__HSMDEF_H__
#define __HSMDEF_H__

#include "hscommon.h"
#include "hsmstate.h"
#include <stdio.h>

/* maximum size of the connection name including zero */
#define HSM_MAX_CONN_NAME_SIZE  16

#define HSM_MAX_MESSAGE_TYPES   128
typedef struct
{ /* HSM message mask */
  BYTE field[(HSM_MAX_MESSAGE_TYPES+7)/8];
} HSM_MASK_TYPE;

/* reset mask bits */
#define HSM_CLEAR_MASK(mask) {   \
    int hsm_i;                   \
    for(hsm_i = 0; hsm_i < sizeof(HSM_MASK_TYPE); hsm_i++) \
        (mask).field[hsm_i] = 0; \
}

/* set all mask bits */
#define HSM_SET_ALL_MASK(mask) { \
    int hsm_i;                   \
    for(hsm_i = 0; hsm_i < sizeof(HSM_MASK_TYPE); hsm_i++) \
        (mask).field[hsm_i] = (-1); \
}

/* set bit corresponding to the message code */
#define HSM_SET_BIT(mask, message_code) {    \
    int   a_byte = message_code/8;           \
    int   a_bit  = message_code%8;           \
    char *a_c = ((char *)&(mask)) + a_byte;  \
    *a_c |= (1 << a_bit);                    \
}

/* reset bit corresponding to the message code */
#define HSM_RESET_BIT(mask, message_code) {  \
    int   a_byte = message_code/8;           \
    int   a_bit  = message_code%8;           \
    char *a_c = ((char *)&(mask)) + a_byte;  \
    *a_c &= ~(1 << a_bit);                   \
}

/*///////////////////////////////////////////////////////////////////
// messages between HS participants and HS Manager
///////////////////////////////////////////////////////////////////*/

typedef enum _HSM_MESSAGE
{

    /* initialization messages */
    HSM_OPEN_CONNECTION  = 0,   /* Connect to HS Manager      */
    HSM_CLOSE_CONNECTION = 1,   /* Disconnect from HS Manager */

    /* messages coming to and from application        */
    /* responsible for the board software preparation */
    HSM_PREPARE_BOARD            = 2, /* request to prepare Board        */
        HSM_BOARD_PREPARED       = 3, /* reply - Board is prepared       */
        HSM_PREPARE_BOARD_FAILED = 4, /* reply - failed to prepare Board */
        HSM_FOREIGN_BOARD        = 5, /* reply - board is foreign        */

    HSM_UNPREPARE_BOARD          = 6, /* request to unprepare Board      */
        HSM_BOARD_UNPREPARED     = 7, /* reply - Board is unprepared     */

    /* messages coming to HSM aware application */
    HSM_BOARD_READY      =  8, /* Board is ready for application usage       */
    HSM_EXTRACT_PENDING  =  9, /* request to close handles to driver         */
    HSM_EXTRACT_CANCELED = 10, /* request to close handles to driver is 
                                  canceled                                   */
    HSM_BOARD_STOPPED    = 11, /* Board is unconfigured or removed. Application
                                * doesn't have any access to the board.      */

    /* action messages to HSM */
    HSM_INSERT_BOARD  = 12,  /* Request to HSM to process board insertion    */
    HSM_EXTRACT_BOARD = 13,  /* Request to HSM to process board extraction   */

    /* queries and commands to HS Manager */
    HSM_QUERY_HSM_STATE              = 14,/* query HS Manager state          */
        HSM_REPLY_HSM_STATE          = 15,/* reply to query HS Manager state */
    HSM_QUERY_SLOT_INFO              = 16,/* query logical slot information  */
        HSM_REPLY_SLOT_INFO          = 17,/* reply to query slot             */
    HSM_QUERY_SLOT_BY_IDENT_DATA     = 18,/* get logical slot by 
                                           * identification data             */
        HSM_REPLY_SLOT_BY_IDENT_DATA = 19,/* reply to query ident. data      */

    HSM_WRONG_CODE = 20,                  /* wrong message code */

    /*///////////////////////////////////////////////////////////////////
    // additional informational messages
    ///////////////////////////////////////////////////////////////////*/

    /* these messages cover all states coming from HS Driver */
    HSM_BOARD_PHYSICALLY_EXTRACTED    = 21,/* Board is physically extracted(P0)*/
    HSM_BOARD_PHYSICALLY_INSERTED     = 22,/* Board is physically inserted (S0)*/
    HSM_BOARD_CONFIGURED              = 23,/* Board is configured (S1)         */
    HSM_BOARD_CONFIGURE_FAILED        = 24,/* Failed to configure board (S1F)  */
    HSM_BOARD_EXTRACTION_CONFIGURED   = 25,/* "Configured Board" is in extraction state (S1E)  */
    HSM_BOARD_EXTRACTION_UNCONFIGURED = 26,/* "Unconfigured Board" is in extraction state (S0E)*/

    /* these messages come from Device Driver */
    HSM_DRIVER_NO_CHANNELS            = 27, /* All channels are closed */

    /* these messages cover all HS Manager state changes */
    HSM_P0_S0    = 28,  /* Board is inserted           */
    HSM_S0_P0    = 29,  /* Board is extracted          */
    HSM_S0_S1    = 30,  /* Board is configured         */
    HSM_S1_S1I   = 31,  /* Device instance is created  */
    HSM_S1_S1F   = 32,  /* Failed to start device      */
    HSM_S1I_S1B  = 33,  /* Board preparation requested */
    HSM_S1F_S0   = 34,  /* Extraction is authorized    */
    HSM_S1F_S1   = 35,  /* Insert board command        */
    HSM_S1B_S1U  = 36,  /* Extraction is authorized    */
    HSM_S1B_S2   = 37,  /* Board is ready              */
    HSM_S1B_S1BF = 38,  /* Failed to prepare board     */
    HSM_S1BF_S0  = 39,  /* Extraction is authorized    */
    HSM_S1BF_S1I = 40,  /* Insert board command        */
    HSM_S2_S2R   = 41,  /* Handle is opened            */
    HSM_S2R_S2   = 42,  /* Handle is closed            */
    HSM_S2R_S1U  = 43,  /* Board cleanup requested     */
    HSM_S1U_P0   = 44,  /* "Surprise extraction"       */
    HSM_S1U_S0   = 45,  /* Extraction is authorized    */

    /* 
     * A monitor application registered to this pseudo message
     * isn't treated as preparation applications by the HS Manager 
     */
    HSM_MONITOR,        /* Monitor pseudo message      */

    HSM_LAST_MESSAGE    /* this line must be the last  */
} HSM_MESSAGE;


/*///////////////////////////////////////////////////////////////////
// Usually used initialization masks
///////////////////////////////////////////////////////////////////*/

/* HS application mask */
#define HSM_SET_APP_MESSAGE_MASK(mask) {                   \
    HSM_SET_BIT((mask),HSM_BOARD_READY);                   \
    HSM_SET_BIT((mask),HSM_EXTRACT_PENDING);               \
    HSM_SET_BIT((mask),HSM_EXTRACT_CANCELED);              \
    HSM_SET_BIT((mask),HSM_BOARD_STOPPED);                 \
}

/* Board preparation application mask */
#define HSM_SET_BOARD_PREPARE_MESSAGE_MASK(mask) {  \
    HSM_SET_BIT((mask),HSM_PREPARE_BOARD);          \
    HSM_SET_BIT((mask),HSM_UNPREPARE_BOARD);        \
    HSM_SET_BIT((mask),HSM_BOARD_STOPPED);          \
}

typedef enum _HSM_CODE
{	/* code returned by HS Manager functions */
    HSMC_OK = 0,          /* operation is OK */

    HSMC_TIMEOUT,         /* timeout */

    HSMC_NO_MESSAGE,      /* no message (from hsmGetMessage) */

    HSMC_WRONG_HANDLE,    /* NULL or wrong HSM_HANDLE        */

    HSMC_WRONG_PARAMETER, /* wrong function argument (usually NULL pointer)   */

    HSMC_NO_RESOURCES,    /* server resources are not available               */
                          /* (can't open mutex or shared memory, or no queue) */
    HSMC_NO_MEMORY,       /* no free conventional or shared memory            */

    HSMC_ABANDONED,       /* other side abandoned                             */
                          /* (no other side queue or event object)            */
    HSMC_FAIL             /* operation failed for some other reason           */

} HSM_CODE;

/* HS Manager state diagram */
typedef enum
{
    HSM_DIAG_BOARD = 0,             /* board level initiated */
    HSM_DIAG_MANAGEMENT,            /* management  initiated */
    HSM_DIAG_NIKE                   /* extended              */

} HSM_DIAGRAM;

typedef void *HSM_HANDLE;           /* HS Manager handle */

typedef struct
{
    WORD        size;               /* message size */
    PCI_SLOT	pci_slot;           /* PCI address  */
    HSM_MESSAGE message_code;       /* message code */
    long     	queue;              /* sender queue number (filled by HSM) */

} HSM_BASE;

typedef struct
{
    HSM_MASK_TYPE     message_mask; /* mask of favored messages     */
    HSM_DIAGRAM       diagram;      /* required state diagram       */
    long              id;           /* connection id (queue number) */
    char              conn_name[HSM_MAX_CONN_NAME_SIZE];
                                    /* connection name */
} HSM_OPEN_CONN;


typedef struct
{   /* this structure is filled up only in reply message hsmNegotiationState */
    HSM_STATE state;                /* HS Manager state */

} HSM_STATE_INFO;

/* HS_BOARD_INFO structure is filled up only in reply message hsmQuerySlotInfo */
/* for wrong slot number all fields are -1 */

typedef struct
{
    HSM_BASE	base;                            /* basic message data */
    union
    {
        HS_BOARD_INFO       slot_info;           /* slot information structure */
        HSM_STATE_INFO      state_info;          /* HS Manager state structure */
        HSM_OPEN_CONN       open_connection;     /* open connection  structure */

    } overlay;

} HSM_STRUCT;

#define HSM_SHORT_MSG_SIZE   sizeof(HSM_BASE)       /* short message (without parameters) size */
#define HSM_SLOT_MSG_SIZE    sizeof(HSM_STRUCT)     /* HS_BOARD_INFO message size */
#define HSM_STATE_MSG_SIZE   sizeof(HSM_STRUCT)     /* HS_STATE_INFO message size */
#define HSM_OPEN_MSG_SIZE    sizeof(HSM_STRUCT)     /* HS_OPEN_CONN  message size */

/*///////////////////////////////////////////////////////////////////
// basic user functions for connection to HS Manager
///////////////////////////////////////////////////////////////////*/
#ifdef __cplusplus
extern "C" {
#endif

/*///////////////////////////////////////////////////////////////////
// data exchange functions
///////////////////////////////////////////////////////////////////*/

/* initialize connection to HS Manager */
/* handle  - the function puts created HSM_HANDLE into the pointed field */
/* mask - mask for desired incoming messages */
HSM_CODE hsmInitialize       (char          *name,
                              HSM_HANDLE    *handle,
                              HSM_MASK_TYPE *message_mask,
                              HSM_DIAGRAM    diagram);

/* close connection to HS Manager */
HSM_CODE hsmClose            (HSM_HANDLE handle);

/* Get message from HS Manager */
HSM_CODE hsmGetMessage       (HSM_HANDLE handle, HSM_STRUCT *message, DWORD timeout);

/*///////////////////////////////////////////////////////////////////
// user level functions
///////////////////////////////////////////////////////////////////*/

/* Replies from application responsible for Board configuration (preparation) */
HSM_CODE hsmBoardPrepared      (HSM_HANDLE handle, PCI_SLOT pci_slot);
HSM_CODE hsmBoardUnprepared    (HSM_HANDLE handle, PCI_SLOT pci_slot);
HSM_CODE hsmPrepareBoardFailed (HSM_HANDLE handle, PCI_SLOT pci_slot);
HSM_CODE hsmForeignBoard       (HSM_HANDLE handle, PCI_SLOT pci_slot);

/* Get HS Manager state */
HSM_CODE hsmQueryNegotiationState (HSM_HANDLE   handle,
                                   PCI_SLOT     pci_slot,
                                   HSM_STRUCT * info);
/* Get slot information */
HSM_CODE hsmQuerySlotInfo         (HSM_HANDLE   handle,
                                   PCI_SLOT     pci_slot,
                                   HSM_STRUCT * info);
/* Get slot by identification data */
HSM_CODE hsmQuerySlotByIdentData  (HSM_HANDLE   handle,
                                   IDENT_DATA * p_identData,
                                   PCI_SLOT   * p_pciSlot);

/* Send message to HS Manager to activate board insertion */
HSM_CODE hsmInsertBoard        (HSM_HANDLE handle, PCI_SLOT pci_slot);
/* Send message to HS Manager to activate board extraction */
HSM_CODE hsmExtractBoard       (HSM_HANDLE handle, PCI_SLOT pci_slot);

/*///////////////////////////////////////////////////////////////////
// service functions
///////////////////////////////////////////////////////////////////*/

/* Print HSM_STRUCT structure in stdout */
void  hsmPrintMessage          (char *comment, HSM_STRUCT *message);

/* Specify output file, if NULL the output is stdout */
void  hsmSetOutput             (FILE *output);

/* Return string meaning of HSM_CODE */
char *hsmGetErrorText          (HSM_CODE hsm_code);

/* Get string meaning of the message */
char *hsmGetMessageName        (HSM_MESSAGE message_code);

/* Get string meaning of the HSM state */
char *hsmGetStateName          (HSM_STATE state);


#ifdef __cplusplus
}
#endif

#endif	/* __HSMDEF_H__ */
