/*****************************************************************************
 *
 * tx4_swi.h - TX 4000 Switching Model Definitions
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _TX4_SWI_H
#define _TX4_SWI_H

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: pack on 1-byte boundaries
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack(1)
#endif
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
#ifdef _WINNT
#pragma pack(1)
#endif

/* ----- dependent includes ----- */
#include <txnuser.h>

/*****************************************************************************
 * TX 4000 LOCAL STREAM USAGE
 *****************************************************************************/
#define TX4_LS_COMM_A       0   /* local stream 0 maps to communication
                                 * processor connection A (i.e. 8260 TDMA) */
#define TX4_LS_COMM_B       1   /* local stream 1 maps to communication
                                 * processor connection B (i.e. 8260 TDMB) */
#define TX4_LS_FRAMER_A     2   /* local stream 2 maps to T1/E1 quad framer A
                                 * (Infineon QuadFALC T1/E1/J1 framer) */
#define TX4C_LS_FRAMER_A    2   /* local streams 2..5 map to */
#define TX4C_LS_FRAMER_B    3   /*   T1/E1 quad framers A..D */
#define TX4C_LS_FRAMER_C    4   /*   (infineon QuadFALC T1/E1/J1 framers) */
#define TX4C_LS_FRAMER_D    5

#define TX4_LS_COUNT        3   /* TX 4000 count of local streams in use */
#define TX4C_LS_COUNT       4   /* TX 4000C count of local streams in use */

#define TX4_LS_DELTA_TS     4   /* delta to apply to 1st device timeslot
                                 * to get next timeslot for given device */

#define TX4_LS_COMM_COUNT   32  /* count of communication processor
                                 * connections (timeslots) per COMM local stream */
#define TX4_LS_FRAMER_COUNT 32  /* count of framer connections (timeslots)
                                 * per FRAMER device */

/*****************************************************************************
 * TX 4000 LOCAL TIMESLOT USAGE (T1/E1 FRAMER #n)
 *
 * The TX 4000 uses byte interleaving, resulting in the following mapping
 * table used for each FRAMER local stream.
 *
 * EXAMPLES:
 *   TX 4000[C]: To map to framer #3's timeslot 1, connect to the following:
 *                     Local Stream: TX4_LS_FRAMER_A (local stream 2)
 *                   Timeslot on LS: TX4_LT_TE3_1    (timeslot 6)
 *
 *   TX 4000C:   To map to framer #7's timeslot 1, connect to the following:
 *                     Local Stream: TX4_LS_FRAMER_B (local stream 3)
 *                   Timeslot on LS: TX4_LT_TE3_1    (timeslot 6)
 *
 * NOTE: The TX 4000 board has a single FRAMER local stream (TX4_LS_FRAMER_A).
 *       The TX 4000C board has 4 FRAMER local streams (TX4C_LS_FRAMER_A..D).
 *
 * Literal name                                 Timeslot on local stream
 * ========================================     ========================
 * TX4_LT_TE<framer number>_<line timeslot>
 *****************************************************************************/
#define TX4_LT_TE1_0                            0
#define TX4_LT_TE1_1                            4
#define TX4_LT_TE1_2                            8
#define TX4_LT_TE1_3                            12
#define TX4_LT_TE1_4                            16
#define TX4_LT_TE1_5                            20
#define TX4_LT_TE1_6                            24
#define TX4_LT_TE1_7                            28
#define TX4_LT_TE1_8                            32
#define TX4_LT_TE1_9                            36
#define TX4_LT_TE1_10                           40
#define TX4_LT_TE1_11                           44
#define TX4_LT_TE1_12                           48
#define TX4_LT_TE1_13                           52
#define TX4_LT_TE1_14                           56
#define TX4_LT_TE1_15                           60
#define TX4_LT_TE1_16                           64
#define TX4_LT_TE1_17                           68
#define TX4_LT_TE1_18                           72
#define TX4_LT_TE1_19                           76
#define TX4_LT_TE1_20                           80
#define TX4_LT_TE1_21                           84
#define TX4_LT_TE1_22                           88
#define TX4_LT_TE1_23                           92
#define TX4_LT_TE1_24                           96
#define TX4_LT_TE1_25                           100
#define TX4_LT_TE1_26                           104
#define TX4_LT_TE1_27                           108
#define TX4_LT_TE1_28                           112
#define TX4_LT_TE1_29                           116
#define TX4_LT_TE1_30                           120
#define TX4_LT_TE1_31                           124

#define TX4_LT_TE2_0                            1
#define TX4_LT_TE2_1                            5
#define TX4_LT_TE2_2                            9
#define TX4_LT_TE2_3                            13
#define TX4_LT_TE2_4                            17
#define TX4_LT_TE2_5                            21
#define TX4_LT_TE2_6                            25
#define TX4_LT_TE2_7                            29
#define TX4_LT_TE2_8                            33
#define TX4_LT_TE2_9                            37
#define TX4_LT_TE2_10                           41
#define TX4_LT_TE2_11                           45
#define TX4_LT_TE2_12                           49
#define TX4_LT_TE2_13                           53
#define TX4_LT_TE2_14                           57
#define TX4_LT_TE2_15                           61
#define TX4_LT_TE2_16                           65
#define TX4_LT_TE2_17                           69
#define TX4_LT_TE2_18                           73
#define TX4_LT_TE2_19                           77
#define TX4_LT_TE2_20                           81
#define TX4_LT_TE2_21                           85
#define TX4_LT_TE2_22                           89
#define TX4_LT_TE2_23                           93
#define TX4_LT_TE2_24                           97
#define TX4_LT_TE2_25                           101
#define TX4_LT_TE2_26                           105
#define TX4_LT_TE2_27                           109
#define TX4_LT_TE2_28                           113
#define TX4_LT_TE2_29                           117
#define TX4_LT_TE2_30                           121
#define TX4_LT_TE2_31                           125

#define TX4_LT_TE3_0                            2
#define TX4_LT_TE3_1                            6
#define TX4_LT_TE3_2                            10
#define TX4_LT_TE3_3                            14
#define TX4_LT_TE3_4                            18
#define TX4_LT_TE3_5                            22
#define TX4_LT_TE3_6                            26
#define TX4_LT_TE3_7                            30
#define TX4_LT_TE3_8                            34
#define TX4_LT_TE3_9                            38
#define TX4_LT_TE3_10                           42
#define TX4_LT_TE3_11                           46
#define TX4_LT_TE3_12                           50
#define TX4_LT_TE3_13                           54
#define TX4_LT_TE3_14                           58
#define TX4_LT_TE3_15                           62
#define TX4_LT_TE3_16                           66
#define TX4_LT_TE3_17                           70
#define TX4_LT_TE3_18                           74
#define TX4_LT_TE3_19                           78
#define TX4_LT_TE3_20                           82
#define TX4_LT_TE3_21                           86
#define TX4_LT_TE3_22                           90
#define TX4_LT_TE3_23                           94
#define TX4_LT_TE3_24                           98
#define TX4_LT_TE3_25                           102
#define TX4_LT_TE3_26                           106
#define TX4_LT_TE3_27                           110
#define TX4_LT_TE3_28                           114
#define TX4_LT_TE3_29                           118
#define TX4_LT_TE3_30                           122
#define TX4_LT_TE3_31                           126

#define TX4_LT_TE4_0                            3
#define TX4_LT_TE4_1                            7
#define TX4_LT_TE4_2                            11
#define TX4_LT_TE4_3                            15
#define TX4_LT_TE4_4                            19
#define TX4_LT_TE4_5                            23
#define TX4_LT_TE4_6                            27
#define TX4_LT_TE4_7                            31
#define TX4_LT_TE4_8                            35
#define TX4_LT_TE4_9                            39
#define TX4_LT_TE4_10                           43
#define TX4_LT_TE4_11                           47
#define TX4_LT_TE4_12                           51
#define TX4_LT_TE4_13                           55
#define TX4_LT_TE4_14                           59
#define TX4_LT_TE4_15                           63
#define TX4_LT_TE4_16                           67
#define TX4_LT_TE4_17                           71
#define TX4_LT_TE4_18                           75
#define TX4_LT_TE4_19                           79
#define TX4_LT_TE4_20                           83
#define TX4_LT_TE4_21                           87
#define TX4_LT_TE4_22                           91
#define TX4_LT_TE4_23                           95
#define TX4_LT_TE4_24                           99
#define TX4_LT_TE4_25                           103
#define TX4_LT_TE4_26                           107
#define TX4_LT_TE4_27                           111
#define TX4_LT_TE4_28                           115
#define TX4_LT_TE4_29                           119
#define TX4_LT_TE4_30                           123
#define TX4_LT_TE4_31                           127

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack()
#endif
#ifdef _WINNT
#pragma pack()
#endif
#ifdef __HIGHC__
#pragma Pop_align_members
#endif

#endif  /* _TXSWI_H */
