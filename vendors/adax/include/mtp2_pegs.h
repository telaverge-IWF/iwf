/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: Daewoo testbed                                                 *
 *                                                                          *
 *     FILE: mtp2_pegs.h                                                   *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: mtp2_pegs.h,v 9.1 2005/03/23 12:55:25 cvsadmin Exp $
 *
 *
 ****************************************************************************/



#define ITS_MAX_MTP_BUF     32000

#define GLOBAL_PEGID_TO_TEXT(x)  \
   ((x == PEG_MTP2_GET_DATA_FAILED)      ? "PEG_MTP2_GET_DATA_FAILED" :     	\
   ((x == PEG_MTP2_SEND_DATA_FAILED)     ? "PEG_MTP2_SEND_DATA_FAILED" :     	\
   ((x == PEG_MTP2_LOCAL_PROC_DOWN)      ? "PEG_MTP2_LOCAL_PROC_DOWN" :     	\
   ((x == PEG_MTP2_LOCAL_PROC_UP)        ? "PEG_MTP2_LOCAL_PROC_UP" :     		\
   ((x == PEG_MTP2_REMOTE_PROC_DOWN)     ? "PEG_MTP2_REMOTE_PROC_DOWN" :     	\
   ((x == PEG_MTP2_REMOTE_PROC_UP)       ? "PEG_MTP2_REMOTE_PROC_UP" :     		\
   ((x == PEG_MTP2_STAT_IND)             ? "PEG_MTP2_STAT_IND" :     			\
   ((x == PEG_MTP2_SUERM_EXPIRY)         ? "PEG_MTP2_SUERM_EXPIRY" :     		\
   ((x == PEG_MTP2_INCORRECT_FIB_BSN)    ? "PEG_MTP2_INCORRECT_FIB_BSN" : 		\
   ((x == PEG_MTP2_CONG_DETECTED)        ? "PEG_MTP2_CONG_DETECTED" :     		\
   ((x == PEG_MTP2_CONG_RECOVERED)       ? "PEG_MTP2_CONG_RECOVERED" :     		\
   ((x == PEG_MTP2_MSU_TX)               ? "PEG_MTP2_MSU_TX" :     				\
   ((x == PEG_MTP2_MSU_RX)               ? "PEG_MTP2_MSU_RX" :     				\
   ((x == PEG_MTP2_T2_EXPIRED)           ? "PEG_MTP2_T2_EXPIRED" :     			\
   ((x == PEG_MTP2_T6_EXPIRED)           ? "PEG_MTP2_T6_EXPIRED" :     			\
   ((x == PEG_MTP2_T7_EXPIRED)           ? "PEG_MTP2_T7_EXPIRED" :     			\
   ((x == PEG_MTP2_T1_EXPIRED)           ? "PEG_MTP2_T1_EXPIRED" :     			\
   ((x == PEG_MTP2_T3_EXPIRED)           ? "PEG_MTP2_T3_EXPIRED" :     			\
   ((x == PEG_MTP2_REMOTE_CONG_DETECTED) ? "PEG_MTP2_REMOTE_CONG_DETECTED" :	\
   ((x == PEG_MTP2_REMOTE_CONG_RECOVERED)? "PEG_MTP2_REMOTE_CONG_RECOVERED" :  	\
   "UNKNOWN PEG ID"))))))))))))))))))))


#define ALL_MTP2_PEGS                   99

#define PEG_ADAX_MTP2_NUM_GLOBAL_PEGS   20

/* Global PEG Defines */
#define PEG_MTP2_GET_DATA_FAILED        0
#define PEG_MTP2_SEND_DATA_FAILED       1
#define PEG_MTP2_LOCAL_PROC_DOWN        2
#define PEG_MTP2_LOCAL_PROC_UP          3
#define PEG_MTP2_REMOTE_PROC_DOWN       4
#define PEG_MTP2_REMOTE_PROC_UP         5
#define PEG_MTP2_STAT_IND               6
#define PEG_MTP2_SUERM_EXPIRY           7
#define PEG_MTP2_INCORRECT_FIB_BSN      8
#define PEG_MTP2_CONG_DETECTED          9
#define PEG_MTP2_CONG_RECOVERED         10
#define PEG_MTP2_MSU_TX                 11
#define PEG_MTP2_MSU_RX                 12
#define PEG_MTP2_T2_EXPIRED             13
#define PEG_MTP2_T6_EXPIRED             14
#define PEG_MTP2_T7_EXPIRED             15

/* ADAX Specific Global Pegs */
#define PEG_MTP2_T1_EXPIRED             16
#define PEG_MTP2_T3_EXPIRED             17
#define PEG_MTP2_REMOTE_CONG_DETECTED   18
#define PEG_MTP2_REMOTE_CONG_RECOVERED  19


#define LINK_PEGID_TO_TEXT(x)  \
   ((x == PEG_MTP2_LINK_FAIL_ALL_REASON)    ? "PEG_MTP2_LINK_FAIL_ALL_REASON" :		\
   ((x == PEG_MTP2_LINK_SUERM_EXPIRY)     	? "PEG_MTP2_LINK_SUERM_EXPIRY" :    	\
   ((x == PEG_MTP2_LINK_INCORRECT_FIB_BSN)  ? "PEG_MTP2_LINK_INCORRECT_FIB_BSN" :	\
   ((x == PEG_MTP2_LINK_T6_EXPIRED)        	? "PEG_MTP2_LINK_T6_EXPIRED" :     		\
   ((x == PEG_MTP2_LINK_T7_EXPIRED)     	? "PEG_MTP2_LINK_T7_EXPIRED" :     		\
   ((x == PEG_MTP2_LINK_PROV_ALIGN_FAILED)  ? "PEG_MTP2_LINK_PROV_ALIGN_FAILED" :   \
   ((x == PEG_MTP2_LINK_ERR_SU)             ? "PEG_MTP2_LINK_ERR_SU" :     			\
   ((x == PEG_MTP2_LINK_NEG_ACK)   		    ? "PEG_MTP2_LINK_NEG_ACK" :     		\
   ((x == PEG_MTP2_LINK_MSU_TX)    			? "PEG_MTP2_LINK_MSU_TX" : 				\
   ((x == PEG_MTP2_LINK_MSU_RX)        		? "PEG_MTP2_LINK_MSU_RX" :     			\
   ((x == PEG_MTP2_LINK_SIF_SIO_OCTET_TX)	? "PEG_MTP2_LINK_SIF_SIO_OCTET_TX" :    \
   ((x == PEG_MTP2_LINK_SIF_SIO_OCTET_RX)   ? "PEG_MTP2_LINK_SIF_SIO_OCTET_RX" :    \
   ((x == PEG_MTP2_LINK_OCTET_RTX)          ? "PEG_MTP2_LINK_OCTET_RTX" :     		\
   ((x == PEG_MTP2_LINK_MSU_RTX)           	? "PEG_MTP2_LINK_MSU_RTX" :     		\
   ((x == PEG_MTP2_LINK_T2_T3_EXPIRED)      ? "PEG_MTP2_LINK_T2_T3_EXPIRED" :     	\
   ((x == PEG_MTP2_LINK_SIB_TX)           	? "PEG_MTP2_LINK_SIB_TX" :     			\
   ((x == PEG_MTP2_LINK_SIB_RX)           	? "PEG_MTP2_LINK_SIB_RX" :     			\
   "UNKNOWN PEG ID")))))))))))))))))

#define PEG_ADAX_MTP2_NUM_LINK_PEGS    		17

/* Link PEG Defines */
#define PEG_MTP2_LINK_FAIL_ALL_REASON       0
#define PEG_MTP2_LINK_SUERM_EXPIRY       	1
#define PEG_MTP2_LINK_INCORRECT_FIB_BSN		2
#define PEG_MTP2_LINK_T6_EXPIRED         	3
#define PEG_MTP2_LINK_T7_EXPIRED      		4
#define PEG_MTP2_LINK_PROV_ALIGN_FAILED    	5
#define PEG_MTP2_LINK_ERR_SU              	6
#define PEG_MTP2_LINK_NEG_ACK           	7
#define PEG_MTP2_LINK_MSU_TX      			8
#define PEG_MTP2_LINK_MSU_RX          		9
#define PEG_MTP2_LINK_SIF_SIO_OCTET_TX      10
#define PEG_MTP2_LINK_SIF_SIO_OCTET_RX      11
#define PEG_MTP2_LINK_OCTET_RTX             12

/* ADAX Specific Link Pegs */
#define PEG_MTP2_LINK_MSU_RTX             	13
#define PEG_MTP2_LINK_T2_T3_EXPIRED         14
#define PEG_MTP2_LINK_SIB_TX   				15
#define PEG_MTP2_LINK_SIB_RX   				16
