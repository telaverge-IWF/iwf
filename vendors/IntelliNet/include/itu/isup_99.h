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
 *  ID: $Id: isup_99.h,v 9.1 2006/01/09 06:22:08 omayor Exp $
 *
 * LOG: $Log: isup_99.h,v $
 * LOG: Revision 9.1  2006/01/09 06:22:08  omayor
 * LOG: Added support for ITU ISUP 99.(skatta)
 * LOG:
 *    
 *****************************************************************************/

#ifndef _ITU_ISUP_99_H
#define _ITU_ISUP_99_H

#include <itu/isup_97.h>

#ifdef __cplusplus
extern "C"
{
#endif


/*
 * the ITU ISUP 99 Variant Class Record.
 */
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
}
ITU_ISUP_99_VARIANT_ClassRec, *ITU_ISUP_99_VARIANT_Class;

extern ITSSS7DLLAPI ITU_ISUP_99_VARIANT_ClassRec isupITU_99_ClassRec;
extern ITSSS7DLLAPI ITS_Class isupITU_99_Class;


/*
 * ITU ISUP 99 Variant Macros.
 */

#define ITU_ISUP_99_VARIANT_CLASS_NAME ISUP_ITU_GENERIC_99_STRING


/*
 * The set of messages supported for this variant is represented by a table of
 * 32 rows.
 * Each bit of this table is a msg supported indicator for the message type.
 * row 0 bit 1 will be the msg supported indicator for message type 0x01, and
 * row 31 bit 7 will be the msg supported indicator for message type 0xFF.
 *
 * The following table is the table for msgs supported in ituisup 99 variant:
 *
 *        bit 7  bit 6  bit 5  bit 4  bit 3  bit 2  bit 1  bit 0
 *       ---------------------------------------------------------
 * row 0 | CON  | ACM  | COT  | INF  | INR  | SAM  | IAM  | NULL |    
 *       ---------------------------------------------------------
 * row 1 | NULL | RES  | SUS  | REL  | NULL | NULL | ANM  | FOT  |    
 *       ---------------------------------------------------------
 * row 2 | GRS  | UBA  | BLA  | UBL  | BLO  | RSC  | CCR  | RLC  |    
 *       ---------------------------------------------------------
 * row 3 | FAR  | NULL | NULL | NULL | CGUA | CGBA | CGU  | CGB  |
 *       ---------------------------------------------------------
 * row 4 | NULL | NULL | NULL | LPA  | NULL | NULL | FRJ  | FAA  |
 *       ---------------------------------------------------------
 * row 5 | CFN  | UCIC | USR  | CPG  | CQR  | CQM  | GRA  | PAM  |
 *       ---------------------------------------------------------
 * row 6 | IRS  | IDR  | UPA  | UPT  | FAC  | NRM  | CRG  | OLM  |    
 *       ---------------------------------------------------------
 * row 7 | NULL | NULL | NULL | NULL | NULL | NULL | NULL | SGM  |
 *       ---------------------------------------------------------
 * row 8 | NULL | NULL | NULL | NULL | SDM  | PRI  | APM  | LOP  |    // APM, PRI, SDM added
 *       ---------------------------------------------------------
 * NULL: No msg or Reserved
 *
 */


/*
 * Message set addition in ITU ISUP 99.
 */
#define TABLE_MSG_SUPPORTED_ROW0_ITU_99  0xFEU /* 1111 1110 */
#define TABLE_MSG_SUPPORTED_ROW1_ITU_99  0x73U /* 0111 0011 */
#define TABLE_MSG_SUPPORTED_ROW2_ITU_99  0xFFU /* 1111 1111 */
#define TABLE_MSG_SUPPORTED_ROW6_ITU_99  0xFFU /* 1111 1111 */
#define TABLE_MSG_SUPPORTED_ROW8_ITU_99  0x0FU /* 0000 1111 */


/*
 * externs for messages - in ITU_99, differing from ITU97
 */
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_ACM_Desc; /* Address Complete */ 
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_ANM_Desc; /* Answer */
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_CPG_Desc; /* Call Progress */
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_CON_Desc; /* Connect */ 
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_IAM_Desc; /* Initial Address */  
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_REL_Desc; /* Release */ 
extern SS7DLLAPI ISUP_MSG_DESC ITU_99_ISUP_FAC_Desc; /* Facility */
			

/*
 * externs for messages - Specific to ITU_99; not in ITU97
 * 
 */

extern SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_SDM_Desc; /* Subsequent Delivery     */
extern SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_PRI_Desc; /* Pre-Release Information */
extern SS7DLLAPI ISUP_MSG_DESC   ITU_99_ISUP_APM_Desc; /* Application Transport   */

#ifdef __cplusplus
}
#endif


#endif /* #define _ITU_ISUP_99_H*/
