/******************************************************************************************************
                                        MTPERR.H
        This file contains error defines and prototypes common to MTP user applications.
 ******************************************************************************************************/

/*
 * Mtp error codes.  Note these are dup'd from GEN.H.  Must keep in sync.
 */
#define MTP_ERR_BADHDR    20      /* Error in Mgmt packet header */
#define MTP_ERR_CFGDUP    21      /* Duplicate General Configuration Request */
#define MTP_ERR_MAXSAPS   22      /* Configured maxSaps exceeds maximum */
#define MTP_ERR_BADPARAM  23      /* Parameter out of range (see alarm log) */
#define MTP_ERR_NOMEM     24      /* Unable to allocate sufficient memory */
#define MTP_ERR_RESOURCE  25      /* Internal resource error (see alarm log) */
#define MTP_ERR_BADSAP    26      /* Invalid/undefined SAP ID */
#define MTP_ERR_BADENT    27      /* Invalid/undefined Entity ID */
#define MTP_ERR_BADINST   28      /* Invalid/undefined Instance ID */
#define MTP_ERR_NOGENCFG  29      /* General configuration must be first */
#define MTP_ERR_BADLNK    30      /* Invalid/undefined link number */
#define MTP_ERR_BADLNKSET 31      /* Invalid/undefined linkset number */
#define MTP_ERR_BADROUTE  32      /* Invalid/undefined route ID */
#define MTP_ERR_MAXLINKS  33      /* Configured links exceeds maximum */
#define MTP_ERR_BADACT    34      /* Invalid action/subaction in control rqst */
#define MTP_ERR_BADPORT   35      /* Invalid serial or TDM port number specified */
#define MTP_ERR_BADSTATE  36      /* Task is in invalid state for request */

