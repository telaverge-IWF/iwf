
/*-------------------------------------------------------------------------*
 *                       M O D U L E   H E A D E R
 *
 * filename - imgtsvc.h
 *
 * IMGT service primitive data structure
 *
 *-------------------------------------------------------------------------*/

#ifndef _IMGTSVC_H_
#define _IMGTSVC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "nmstypes.h"


/*--------------------------------------------------------------------------*
 *  Primitives sent and received to/from Management by a application
 *--------------------------------------------------------------------------*/

#define IMGT_SERVICE_RQ             '0' /* SERVICE message request          */
#define IMGT_SERVICE_IN             '1' /* SERVICE message indication       */
#define IMGT_SERVICE_CO             '2' /* SERVICE message confirmation     */
                              
#define IMGT_RESTART_IN             '4' /* RESTART indication               */

#define IMGT_B_CHANNEL_STATUS_RQ    '6' /* B channel status request         */
#define IMGT_B_CHANNEL_STATUS_CO    '7' /* B channel status indication      */

#define IMGT_SET_MASK_RQ            '8' /* set mask request                 */
#define IMGT_SET_MASK_CO            '9' /* mask confirmation                */

#define	IMGT_D_CHANNEL_STATUS_RQ    '>' /* D channel status request         */
#define	IMGT_D_CHANNEL_STATUS_IN    '<' /* D channel status indication      */
#define	IMGT_D_CHANNEL_STATUS_CO    '^' /* D channel status confirmation    */

#define IMGT_REPORT_IN              '~' /* REPORT indication                */


/*--------------------------------------------------------------------------*
 *  Data structures used with Primitives
 *--------------------------------------------------------------------------*/

/*   data structure for IMGT_SERVICE_XX and for IMGT_B_CHANNEL_STATUS_XX    */

struct imgt_service
    {
    BYTE type;              /* either TRUNK or BCHANNEL                     */
    BYTE nai;               /* NAI for SERVICE message                      */
    BYTE BChannel;          /* BChannel for SERVICE message                 */
    BYTE status;            /* either IN_SERVICE or OUT_OF_SERVICE          */
    };


/*    defines for "status" element of imgt_service                          */

#define        IMGT_IN_SERVICE          0
#define        IMGT_MAINTENANCE         1
#define        IMGT_OUT_OF_SERVICE      2



/*   data structure for IMGT_RESTART_XX                                     */

struct imgt_restart
    {
    BYTE type;              /* indicates either restart for 
                               the entire trunk or a individual BChannel    */
    BYTE nai;               /* NAI for RESTART indication or confirmation   */
    BYTE BChannel;          /* BChannel for RESTART message                 */
    BYTE bpad;
    };


/*    defines for "type" element of imgt_restart or imgt_service            */

#define        PREFERENCE_TRUNK            0
#define        PREFERENCE_BCHANNEL         1


/*   data structure for IMGT_D_CHANNEL_STATUS_XX                            */

struct imgt_d_channel_status {
    BYTE status;    /* status (Released/Established/Awaiting Establishment) */
    BYTE bpad[3];
};

#define IMGT_D_CHANNEL_STATUS_RELEASED      0    /* data link released      */
#define IMGT_D_CHANNEL_STATUS_ESTABLISHED   1    /* data link established   */
#define IMGT_D_CHANNEL_STATUS_AWAITING      7    /* awaiting establishment  */


/*  data structures for IMGT_REPORT_IN                                       */

/* common header */
struct imgt_report_hdr
{
    BYTE OperationID;    /* specify the operation                           */
    BYTE pad[3];
};

/* defines of OperationID */
#define        IMGT_OP_ID_SET_CALL_TAG         1
#define        IMGT_OP_ID_TRFD_CALL_CLEARING   2

/* data structure for 
    IMGT_OP_ID_SET_CALL_TAG and IMGT_OP_ID_TRFD_CALL_CLEARING               */

struct imgt_report_CallTag
{
    struct  imgt_report_hdr hdr;
    BYTE    Slot;           /* identify the call associated with the report */
    BYTE    pad[3];
    DWORD   CallTag;
};


/*   data structure for IMGT_SET_MASK_XX */

typedef struct IMGT_CONFIG
{
    DWORD size;             /* size of data structure                       */
    DWORD imgt_mask;        /* service messages                             */
    DWORD trap_mask;        /* trap events                                  */
    DWORD mon_mask;         /* monitoring                                   */
    WORD  nfas_group;       /* NFAS group number if duplicate NAI values */
    BYTE  bpad[6];
} IMGT_CONFIG;

/*    defines for imgt_mask element of imgt_restart                         */

#define IMGT_SERVICE_MASK       0x00000001  /* get service message          */
#define IMGT_RESTART_MASK       0x00000002  /* get restart message          */
#define IMGT_D_CHANNEL_STATUS_MASK 0x00000004  /* get d-channel status      */

#define IMGT_REPORT_MASK        0x00010000  /* report events/messages       */

#ifdef __cplusplus
}
#endif
#endif

