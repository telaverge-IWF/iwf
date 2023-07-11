/*****************************************************************************
  NAME:  nccxcas.h
  
  PURPOSE:

      This is a common include file for all CAS protocols for the NCC service.
****************************************************************************/

#ifndef NCCXCAS_INCLUDED
#define NCCXCAS_INCLUDED 

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

#include "nccadi.h"
#define    NCC_SVCID    0x1C         
                                     
#define	NCC_ADI_CAS_PARMID	0x1C011E
/* #define    NCC_ADI_CAS_PLACECALL_PARMID    0x1C011e */
                                     
/* definition of the extended Place Call Argument to be used, if necessary  */
/* with "void * protcallparms" argument to nccPlaceCall()                   */
typedef struct
{
	DWORD	size;
	struct
	{
		DWORD	size;
		unsigned char	ANIpresentation[1];
		unsigned char	pad[1];
		WORD	satellitecircuit;
		char	redirectingaddr[33];
		char	carrierid[33];
		char	pad2[2];
		INT16	usercategory;
		INT16	tollcategory;
	}	placecall_ext;
}	NCC_ADI_CAS_PARMS;

extern const CTAPARM_DESC * const _nccParmDescTable[];

/* definition of the CAS Extended Call Status Structure                     */
typedef struct
{
    DWORD size;
    char ANIpresentation;     /* set if the ANI presentation is restricted  */
    char redirectingaddr [NCC_MAX_DIGITS+1];/* contains redirecting address information   */
    char redirectingreason;   /* contains the reason for redirection        */
    char usercategory;        /* contains the user category                 */
    char tollcategory;        /* contains the toll category                 */
    char carrierid [NCC_MAX_DIGITS+1];      /* contains the carrier ID information        */        
    WORD billingrate;         /* information passed with BILLING_SET event  */
} NCC_CAS_EXT_CALL_STATUS;

#define MF_SIGNALING            1
#define DECADIC_SIGNALING       2

#define TWO_WAY_TRUNK           0
#define TRUNK_INBOUND           1
#define TRUNK_OUTBOUND          2

#define NO_DIALTONE_ABANDON     0
#define NO_DIALTONE_PROCEED     1

#define DONT_PLAY_CLEARDOWN     0
#define PLAY_CLEARDOWN_DIALTONE 1
#define PLAY_CLEARDOWN_BUSY     2
#define PLAY_CLEARDOWN_FASBUSY  3


#define CAS_REJECT_PLAY_RINGTONE    1
#define CAS_REJECT_PLAY_BUSY        2
#define CAS_REJECT_PLAY_REORDER     3

#define R15_ANI_DIGIT 0x1

#define CALL_REANSWERED 0x400   /* Reanswer (used in MFC-R2) */

#ifdef __cplusplus
}
#endif


#endif /* NCCXCAS_INCLUDED */

