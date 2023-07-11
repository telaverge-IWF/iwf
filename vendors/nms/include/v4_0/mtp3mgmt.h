

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1996                           **
**                          by TEKnique, Inc.                           **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of TEKnique, Inc.                                **
**                                                                      **
*************************************************************************/
/*
 *
 *   mtp3mgmt.h
 *
 *      Constants used with the MTP3 Management API
 *
 */
#ifndef _MTP3MGMT_H_
#define _MTP3MGMT_H_

/* Configuration Request codes */
#define MTP3_GEN_CFG     1           /* general Parameters */
#define MTP3_NSAP_CFG    3           /* network SAP */
#define MTP3_DLSAP_CFG   5           /* data link SAP */
#define MTP3_ROUT_CFG    10          /* route configuration*/
#define MTP3_ROUT_DEL    30          /* delete route */
#define MTP3_LNKSET_CFG  33          /* link set configuration */

/* Control Request codes */
#define MTP3_CTRL_ALARM_ENA		101	/* Enable Alarms */
#define MTP3_CTRL_ALARM_DIS		102	/* Disable Alarms */
#define MTP3_CTRL_FLOWCTL_ON	103	/* Start flow control */
#define MTP3_CTRL_FLOWCTL_OFF	104	/* Flow Control off */
#define MTP3_CTRL_EMERG_ON      105 /* Emergency condition on */
#define MTP3_CTRL_EMERG_OFF     106 /* Emergency condition off */
#define MTP3_CTRL_LPO_ENA       107 /* Start local processor outage */
#define MTP3_CTRL_LPO_DIS       108 /* End local processor outage */
#define MTP3_CTRL_TRACE_ON      109 /* Start trace data */
#define MTP3_CTRL_TRACE_OFF     110 /* Trace Data off */

#define MTP3_CTRL_LINK_ENA		111	/* Enable Link */
#define MTP3_CTRL_LINK_DIS		112	/* Disable Link */
#define MTP3_CTRL_LINK_INH		113	/* Inhibit Link */
#define MTP3_CTRL_LINK_UNINH	114	/* Uninhibit Link */
#define MTP3_CTRL_LINK_SPRST	115	/* SP Restart Request for Link */

#define MTP3_CTRL_LINKSET_ENA	121	/* Enable Linkset */
#define MTP3_CTRL_LINKSET_DIS	122	/* Disable Linkset */

#define MTP3_CTRL_LINK_TRCON    123 /* Start Link trace data */
#define MTP3_CTRL_LINK_TRCOFF   124 /* Link Trace Data off */

/* Status Requests */
#define MTP3_GEN_STATUS			131	/* general SP status */
#define MTP3_NSAP_STATUS		132	/* network SAP status*/
#define MTP3_DLSAP_STATUS		133	/* data link SAP status*/
#define MTP3_ROUTE_STATUS		134	/* route status */
#define MTP3_LNKSET_STATUS		135	/* link set status */

/* Statistics Requests */
#define MTP3_GEN_STATS			141	/* general SP statistics - don't zero */
#define MTP3_DLSAP_STATS		143	/* data link statistics - don't zero */
#define MTP3_ROUTE_STATS		144	/* route statistics - don't zero */
#define MTP3_LNKSET_STATS		145	/* link set statistics - don't zero */

#define MTP3_GEN_STATS_Z		151	/* general SP statistics - zero after reading */
#define MTP3_DLSAP_STATS_Z		153	/* data link statistics - zero after reading */
#define MTP3_ROUTE_STATS_Z		154	/* route statistics - zero after reading */
#define MTP3_LNKSET_STATS_Z		155	/* link set statistics - zero after reading */

/* constants */
#define MTP3LNKTSTMAX   16      /* Max size of link test pattern */
#define MTP3MAXMASKS    8       /* Max number of routing masks */
#define MTP3MAXCMBLNK   256     /* Max number of combined link sets - <3.5> Increased from 16 */

/* Selector value for MTP3 upper (user) interface */
#define MTP3_SEL_LC     0               /* loose coupling */

/* Signalling point types */
#define MTP3TYPE_SP     0       /* signalling point without transfer function */
#define MTP3TYPE_STP    1       /* signalling transfer point */

/* link types */
#define MTP3LNK_DEFAULT           0   /* link type for management message */
#define MTP3LNK_ANSI              1   /* link type ANSI */
#define MTP3LNK_CCITT             2   /* link type CCITT */
#define MTP3LNK_ANSI88            3   /* link type ANSI 88 */
#define MTP3LNK_CHINA             4   /* link type CHINA */
#define MTP3LNK_BICI              5   /* link type BICI */
#define MTP3LNK_SINGAPORE         6   /* link type SINGAPORE */

/* subservice selections */
#define MTP3SSF_INTL              0       /* international */
#define MTP3SSF_SPARE             1       /* spare */
#define MTP3SSF_NAT               2       /* national */
#define MTP3SSF_RES               3       /* reserved */

/* routing directions */
#define MTP3_RTE_DN             1   /* down / outbound route */
#define MTP3_RTE_UP             2   /* up   / inbound route  */


#define MTP3_MGMPRI               3   /* mtp 3 management priority highest */


#endif
