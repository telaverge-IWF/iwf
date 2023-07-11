/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: sccp_pegs.h,v 9.3 2008/06/04 06:36:40 ssingh Exp $
 *
 * LOG: $Log: sccp_pegs.h,v $
 * LOG: Revision 9.3  2008/06/04 06:36:40  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 9.2  2007/01/10 11:15:02  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1.10.3  2006/12/23 09:45:06  randresol
 * LOG: Add definition for TTC pegs to allow TTC and CCITT stack to run in parallel
 * LOG:
 * LOG: Revision 9.1.10.2  2006/09/26 07:27:35  mshanmugam
 * LOG: Removed Q752 Compilation flag
 * LOG:
 * LOG: Revision 9.1.10.1  2006/08/18 12:12:49  mshanmugam
 * LOG: Added new PEG structures for Q.752 Implementation.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/06/22 12:59:35  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG:
 ****************************************************************************/

#ifndef _ITS_SCCP_PEGS_H_
#define _ITS_SCCP_PEGS_H_

#include <sccp_cmn.h>
/*
 *  SCCP Peg Public interface
 */

typedef struct 
{
    ITS_UINT userMsgsSent;
    ITS_UINT remoteMsgsRcvd;
    ITS_UINT routingFailure;
    ITS_UINT remoteGTTRequest;
    ITS_UINT remoteGTTSucc;
    ITS_UINT remoteGTTFail;
    ITS_UINT remoteMsgsDecodeErr;
    ITS_UINT userMsgsEncodeErr;
    ITS_UINT remoteReassembleErr;
    ITS_UINT hopCounterVilotionErr;
    ITS_UINT userSegmentationErr;
    ITS_UINT timerTiarExpiry;
    ITS_UINT userInitiatedRLSD;
    ITS_UINT userInitiatedReset;
    ITS_UINT remoteUDTRcvd;
    ITS_UINT remoteXUDTRcvd;
    ITS_UINT remoteUDTSRcvd; 
    ITS_UINT remoteXUDTSRcvd;
    ITS_UINT remoteLUDTRcvd;
    ITS_UINT remoteLUDTSRcvd;
    ITS_UINT userUDTSent;
    ITS_UINT userXUDTSent;
    ITS_UINT userUDTSSent;
    ITS_UINT userXUDTSSent;
    ITS_UINT userLUDTSent;
    ITS_UINT userLUDTSSent;
    ITS_UINT userCRSent;
    ITS_UINT sentCREFToRemote;
    ITS_UINT sentRSRToRemote;
    ITS_UINT sentERRToRemote;
    ITS_UINT remoteCRRcvd;
    ITS_UINT remoteCREFRcvd;
    ITS_UINT remoteRSRRcvd;
    ITS_UINT remoteERRRcvd;
    ITS_UINT remoteMsgsForLocalSSRcvd;
    ITS_UINT userDT1Sent;
    ITS_UINT remoteDT1Rcvd;
    ITS_UINT userDT2Sent;
    ITS_UINT remoteDT2Rcvd;
    ITS_UINT userEDSent;
    ITS_UINT remoteEDRcvd;
    ITS_UINT remoteSSPRcvd;
    ITS_UINT remoteSSARcvd;
    ITS_UINT remoteSSCRcvd;
    ITS_UINT localSSProhibited;
    ITS_UINT localSSAllowed;
    ITS_UINT localSSCongested;
}
SCCP_Pegs;



typedef struct
{
    ITS_UINT routingFailureNoTransAddr;          /* Routing Failure No translation for Address of such nature */
    ITS_UINT routingFailureNoTransSpecificAddr;  /* Routing Failure No translation for this specific address */
    ITS_UINT syntaxValueErrDetected;             /* Syntax Error Detected Value Error */                
    ITS_UINT syntaxConstructionErrDetected;      /* Syntax Error Detected Construction Error */
    ITS_UINT timerTreassExpiry;                  /* Reassembly error- Timer Treass expiry */
    ITS_UINT reassemblyErrSegRxOOS;              /* Reassembly error- Segment received out of sequence*/
    ITS_UINT reassemblyErrNoReassemblySpace;     /* Reassemly error- No reassembly space */
    ITS_UINT hopCounterViolationErr;             /* Hop counter violation (XUDT/XUDTS, LUDT, LUDTS and CR */          
    ITS_UINT timerTiarExpiry;                    /* Timer T(iar) expiry */
    ITS_UINT providerInitiatedResetConn;         /* Provider initiated reset of a connection */
    ITS_UINT providerInitiatedReleaseConn;       /* Provider initiated release of a connection */
    ITS_UINT userInitiatedResetConn;             /* User initiated reset of a connection */
    ITS_UINT userInitiatedReleaseConn;           /* User initiated release of a connection */
    ITS_UINT segmentationErrSegFailed;           /* Segmentation Error- Segmentation failed */
    ITS_UINT reassemblyErrReassemblyFailed;      /* Reassembly Error - Reassembly failed */
    ITS_UINT messageUDTSSent;                    /* Message UDTS sent */
    ITS_UINT messageUDTSRcvd;                    /* Message UDTS Received */
    ITS_UINT messageFromLocalSS;                 /* Message From Local Subsystem */
    ITS_UINT messageFromRemoteSS;                /* Message From Remote Subsystem */
    ITS_UINT messageForLocalSS;                  /* Message Intended for Local Subsystem */        
    ITS_UINT messageUDTSent;                     /* Message UDT Sent */
    ITS_UINT messageUDTRcvd;                     /* Message UDT Received */
    ITS_UINT messageCRSent;                      /* Message CR Sent */
    ITS_UINT messageCREFSent;                    /* Message CREF Sent */
    ITS_UINT messageCRRcvd;                      /* Message CR Received */
    ITS_UINT messageCREFRcvd;                    /* Message CREF Recieved */
    ITS_UINT messageRSRSent;                     /* Message RSR Sent */
    ITS_UINT messageRSRRcvd;                     /* Message RSR Recieved*/
    ITS_UINT messageErrSent;                     /* Message ERR Sent*/
    ITS_UINT messageErrRcvd;                     /* Message ERR recieved*/
    ITS_UINT messageXUDTSent;                    /* Message XUDT Sent*/
    ITS_UINT messageXUDTSSent;                   /* Message XUDTS Sent */         
    ITS_UINT messageXUDTRcvd;                    /* Message XUDTS Sent */
    ITS_UINT messageXUDTSRcvd;                   /* Message XUDTS Received*/
    ITS_UINT messageLUDTSent;                    /* Message LUDT Sent */
    ITS_UINT messageLUDTSSent;                   /* Message LUDTS Sent */
    ITS_UINT messageLUDTRcvd;                    /* Message  LUDT Recieved*/
    ITS_UINT messageLUDTSRcvd;                   /* Message LUDTS Received */
}
sccpGenPegs;

typedef struct
{
    ITS_OCTET ssn;                               /* Subsystem Number */
    ITS_UINT msgLargeForSeg;                     /* Message Too Large For Segmentation */
    ITS_UINT userUDTSentperClass0SSN;            /* Message UDT Sent Per Class0 */
    ITS_UINT userUDTSentperClass1SSN;            /* Message UDT Sent Per Class 1 */  
    ITS_UINT userXUDTSentperClass0SSN;           /* Message XUDT Sent Per Class0 */
    ITS_UINT userXUDTSentperClass1SSN;           /* Message XUDTS Sent Per Class 1 */               
    ITS_UINT userLUDTSentperClass0SSN;           /* Message LUDT Sent Per Class0 */
    ITS_UINT userLUDTSentperClass1SSN;           /* Message LUDT Sent Per Class1 */
    ITS_UINT userUDTRcvdperClass0SSN;            /* Message UDT Recieved Per Class 0 */     
    ITS_UINT userUDTRcvdperClass1SSN;            /* Message UDT Recieved Per Class 1 */
    ITS_UINT userXUDTRcvdperClass0SSN;           /* Message XUDT Received Per Class0 */
    ITS_UINT userXUDTRcvdperClass1SSN;           /* Message XUDT Received Per Class1 */
    ITS_UINT userLUDTRcvdperClass0SSN;           /* Message LUDT Received Per Class0 */                                    
    ITS_UINT userLUDTRcvdperClass1SSN;           /* Message LUDT Received Per Class1 */
    ITS_UINT messageSSCRcvd;                     /* Message Subsystem Congestion Received */
    ITS_UINT messageSSPRcvd;                     /* Message Subsystem Prohibited received */
    ITS_UINT DT1RcvdPerSinkSSN;                  /* Message DT1 Received Per from MTP Per SSN */
    ITS_UINT DT1SentPerSourceSSN;                /* Message DT1 Sent to MTP Per SSN */
    ITS_UINT DT2RcvdPerSinkSSN;                  /* Message DT2 Received Per from MTP Per SSN */
    ITS_UINT DT2SentPerSourceSSN;                /* Message DT2 Sent toMTP Per SSN */
    ITS_UINT EDSentPerSourceSSN;                 /* Message DT2 Sent toMTP Per SSN */
    ITS_UINT EDRcvdPerSinkSSN;                   /* Message ED Received Per from MTP Per SSN */
}
sccpSsnPegs;

typedef struct
{
  sccpSsnPegs SCCPSSNPegs[SCCP_MAX_SSN];
}
sccp_ssn_stat_table;

sccp_ssn_stat_table SsnOmImage[2];



typedef struct 
{
  sccpGenPegs SCCPGenPegs;
}
sccp_gen_stat_table; 

sccp_gen_stat_table SccpGenOmImage[2];
sccp_gen_stat_table SccpGenOmImage_TTC[2];
sccp_gen_stat_table SccpGenOmImage_PRC[2];


typedef struct
{
  ITS_OCTET activeOm;
  ITS_OCTET inactiveOm;
}
sccpOmBuffer;
  

typedef struct
{
  sccpGenPegs genPegStats;
} 
sccpGenData;

typedef struct 
{
   ITS_UINT count;
   sccpSsnPegs ssnPegStats[SCCP_MAX_SSN];    
}
sccpSsnData;

typedef struct
{
  SS7_Family  family;
  sccpGenData genStats;
  sccpSsnData ssnStats; 
}
sccpOm;

#ifdef __cplusplus
extern "C"
{
#endif


ITSSS7DLLAPI int SCCP_GetAllPegs(SCCP_Pegs *genPegs);

ITSSS7DLLAPI int SCCP_ClearAllPegs();

ITSSS7DLLAPI int SCCP_ClearPeg( ITS_UINT pegId);


#ifdef __cplusplus
}
#endif


#endif /*_ITS_SCCP_PEGS_H_*/
