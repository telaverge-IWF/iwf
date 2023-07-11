/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1998                           **
**                      by Natural MicroSystems, Inc.                   **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/

/* --------------------------------------------------------------------------
 * sccpdefs.h
 *
 * This file containes constants and data types common between
 * the SS7 SSCP API and SS7 SCCP Management API subsystems.
 *
 * $Log: sccpdefs.h,v $
 * Revision 9.1  2005/03/23 12:55:46  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:55:08  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:10:51  mmiers
 * Begin PR6.2
 *
 * Revision 6.1  2002/02/28 16:14:54  mmiers
 * Begin PR7.
 *
 * Revision 1.1  2001/09/05 20:35:47  mmiers
 * Consolidate the NMS libraries.  Only the root library so far.
 *
 * Revision 5.1  2001/08/16 20:46:35  mmiers
 * Start PR6.
 *
 * Revision 4.1  2001/05/04 16:22:07  mmiers
 * Start PR5.
 *
 * Revision 3.1  2000/08/16 00:11:03  mmiers
 *
 * Begin round 4.
 *
 * Revision 1.1  2000/06/21 19:19:38  hxing
 * Add NMS vendor lib for version 2.01
 *
* 
* 1     8/19/98 2:48p Dodren
* Initial version of SCCP Management API files.  Note that SCCPDEFS.H now
* contains #defines that are shared between the protocol and management
* APIs.
 * $Nokeywords$
 * -------------------------------------------------------------------------- */

#if !defined( _SCCPDEFS_H_ )
#define _SCCPDEFS_H_

/* --------------------------------------------------------------------------
 * Return Status Values for SCCP API / SCCP Management API:
 * -------------------------------------------------------------------------- */

#define SCCP_SUCCESS       0      /* API completed successfully               */
#define SCCP_OVERRUN       0x1001 /* Data length too large to send            */
#define SCCP_UNDERRUN      0x1002 /* Received message too large               */
#define SCCP_UNBOUND       0x1003 /* Not bound to specified board             */
#define SCCP_BOARD         0x1004 /* Board number out of range                */
#define SCCP_DRIVER        0x1005 /* CPI driver reported an error             */
#define SCCP_NOMSG         0x1006 /* No event messages waiting                */
#define SCCP_NOTBOUND      0x1007 /* User failed to call SCCPBindTqst() first */
#define SCCP_RESOURCES     0x1008 /* Couldn't allocate msg buffer             */
#define SCCP_UNINIT        0x1009 /* User failed to call SccpMgmtInit() first */
#define SCCP_TOOMANY       0x100a /* Too many handles open for specified board*/
#define SCCP_INSTANCE      0x100b /* Instance ID out of range                 */
#define SCCP_TIMEOUT       0x100c /* No response from board                   */
#define SCCP_SWTYPE        0x100d /* Invalid switch type (i.e., protocol)     */
#define SCCP_PARAM         0x100e /* Invalid parameter                        */
#define SCCP_NOGENCFG      0x100f /* Board has not received SccpGenCfg yet    */
#define SCCP_NOTFOUND      0x1010 /* Specified address or route not found     */
#define SCCP_EXCEEDMAXCFG  0x1011 /* Insufficient resources allocated in gen  */
                                  /*   cfg for a USAP, NSAP, ROUTE or ADDRESS */
#define SCCP_INTERNAL      0x1012 /* An internal error occured.               */
#define SCCP_BUFLEN        0x1013 /* Address/mask too long to fit in buffer   */
                                  /*   or numConPc > conPcList array size     */
                                  /*   or numSsns > ssnList array size.       */
#define SCCP_BADDIGIT      0x1014 /* Address/mask contains an invalid digit   */
#define SCCP_MAXROUTES     0x1015 /* SccpGenCfg maxRtes is out of range       */
#define SCCP_NULLPTR       0x1016 /* A null pointer was passed as a parameter */
#define SCCP_TIMERVALUE    0x1017 /* An enabled timer has a value of 0        */
#define SCCP_HOPCOUNT      0x1018 /* Invalid hop count                        */
#define SCCP_POINTCODE     0x1019 /* Invalid point code                       */
#define SCCP_RANGE         0x101a /* An input field is out of range           */

/* --------------------------------------------------------------------------
 * SCCP Routing Type Values for Adresss Map Tables:
 * -------------------------------------------------------------------------- */

#define ROUTE_GLT       0x00    /* Route using global title only              */
#define ROUTE_PC_SN     0x01    /* Route usint point code + SSN               */

/* --------------------------------------------------------------------------
 * National/International Address Indicator Values for Address Translations:
 * -------------------------------------------------------------------------- */

#define ADDRIND_INT     0x00    /* International address indicator            */
#define ADDRIND_NAT     0x01    /* National address indicator                 */

/* --------------------------------------------------------------------------
 * Address Encoding Scheme Values:
 * -------------------------------------------------------------------------- */

#define ENC_UNKNOWN     0x00    /* Encoding unknown                           */
#define ENC_BCD_ODD     0x01    /* BCD, odd number of digits                  */
#define ENC_BCD_EVEN    0x02    /* BCD, even number of digits                 */

/* --------------------------------------------------------------------------
 * Numbering Plan Values:
 * -------------------------------------------------------------------------- */

#define NP_UNK          0x00    /* Unknown                                    */
#define NP_ISDN         0x01    /* ISDN/telephony - E.164/E.163               */
#define NP_TEL          0x02    /* Telephony numbering - E.163                */
#define NP_DATA         0x03    /* Data numbering - X.121                     */
#define NP_TELEX        0x04    /* Telex numbering - Recomm. F.69             */
#define NP_MARITIME     0x05    /* Maritime mobile numbering                  */
#define NP_LANDMOB      0x06    /* Land mobile numbering                      */
#define NP_ISDNMOB      0x07    /* ISDN/mobile numbering                      */
#define NP_NATIONAL     0x08    /* National standard numbering                */
#define NP_PRIVATE      0x09    /* Private numbering                          */
#define NP_EXT          0x0F    /* Reserved for extension                     */

/* --------------------------------------------------------------------------
 * Nature of Address Indicator Values:
 * -------------------------------------------------------------------------- */

#define NATIND_SUBS     0x01    /* Subscriber number                          */
#define NATIND_NATL     0x03    /* National number                            */
#define NATIND_INTNATL  0x04    /* International number                       */

#endif /* !defined( _SCCPDEFS_H_) */
