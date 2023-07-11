/*****************************************************************************
*                                  MVIP95.H
*
*  This is the include file for MVIP-95 Compatible Structures, commands,
*  error codes.
*
*
* Copyright (c)1996-98 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef __MVIP95_INCLUDED
#define __MVIP95_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif

/*****************************************************************************/
/* MVIP-95 Driver Function Codes                                             */
/*****************************************************************************/

/*****************************************************************************/
/* MVIP-95 Switching Commands                                                */
/*****************************************************************************/
#define MVIP95_CMD_RESET_SWITCH           0x101
#define MVIP95_CMD_QUERY_SWITCH_CAPS      0x002
#define MVIP95_CMD_SET_OUTPUT             0x103
#define MVIP95_CMD_QUERY_OUTPUT           0x104
#define MVIP95_CMD_SAMPLE_INPUT           0x105

/*****************************************************************************/
/* MVIP-95 Clock Commands                                                    */
/*****************************************************************************/
#define MVIP95_CMD_CONFIG_BOARD_CLOCK     0x111
#define MVIP95_CMD_CONFIG_SEC8K_CLOCK     0x112
#define MVIP95_CMD_CONFIG_NETREF_CLOCK    0x113
#define MVIP95_CMD_QUERY_BOARD_CLOCK      0x114
#define MVIP95_CMD_QUERY_TIMING_REFERENCE 0x115


/*****************************************************************************/
/* MVIP-95 Diagnostic Commands                                               */
/*****************************************************************************/
#define MVIP95_CMD_DUMP_SWITCH            0x170
#define MVIP95_CMD_SET_SWITCH             0x172
#define MVIP95_CMD_SET_VERIFY             0x173

/*****************************************************************************/
/* H-MVIP Stream Configuration Commands                                      */
/*****************************************************************************/
#define MVIP95_CMD_CONFIG_STREAM_SPEED    0x11A
#define MVIP95_CMD_QUERY_STREAM_SPEED     0x11B

/*****************************************************************************/
/* MC1 Clock Commands                                                        */
/*****************************************************************************/
#define MVIP95_CMD_CONFIG_8KREF_CLOCK     0x122

/*****************************************************************************/
/* MVIP-95 Configuration Commands                                            */
/*****************************************************************************/
#define MVIP95_CMD_CONFIG_LOCAL_STREAM    0x1A0

#if (_MSC_VER == 600)
#define MVIP95CMD_CONFIG_LOCAL_TIMESLOT  0x1A1
#else
#define MVIP95_CMD_CONFIG_LOCAL_TIMESLOT  0x1A1
#endif

#define MVIP95_CMD_QUERY_BOARD_INFO       0x1A2
#define MVIP95_CMD_QUERY_DRIVER_INFO      0x1A3
#define MVIP95_CMD_QUERY_LOCAL_STREAM     0x1A4
#define MVIP95_CMD_QUERY_LOCAL_TIMESLOT   0x1A5


/*****************************************************************************/
/* MVIP-95 Driver Extensions                                                 */
/*****************************************************************************/
#define MVIP95_CMDEXT_CLOSE_SWITCH        0x201 /* NMS command for HOT_SWAP changes */

/*****************************************************************************/
/* Error Return Codes                                                        */
/*****************************************************************************/

/*****************************************************************************/
/* General Errors                                                            */
/*****************************************************************************/
#define MVIP95_SUCCESS                        0
#define MVIP95_ERR_INVALID_COMMAND          200
#define MVIP95_ERR_DLL_INVALID_DEVICE       201
#define MVIP95_ERR_DEVICE_ERROR             202
#define MVIP95_ERR_NO_RESOURCES             204

/*****************************************************************************/
/* Parameter Errors                                                          */
/*****************************************************************************/
#define MVIP95_ERR_INVALID_STREAM           210
#define MVIP95_ERR_INVALID_TIMESLOT         211
#define MVIP95_ERR_MISSING_PARAMETER        212
#define MVIP95_ERR_INVALID_CLOCK_PARM       213
#define MVIP95_ERR_INVALID_SPEED            214
#define MVIP95_ERR_NOT_CONFIGURABLE         215
#define MVIP95_ERR_INVALID_MODE             216
#define MVIP95_ERR_INVALID_MINOR_SWITCH     217
#define MVIP95_ERR_INVALID_PARAMETER        218
/* #define MVIP95_ERR_INVALID_SPEED         219 see spec. (same name 214) different meanings*/
#define MVIP95_ERR_UNSUPPORTED_MODE         224

/*****************************************************************************/
/* Switch Errors                                                             */
/*****************************************************************************/
#define MVIP95_ERR_NO_PATH                  220
#define MVIP95_ERR_SWITCH_VERIFY_ERROR      221
#define MVIP95_ERR_INTERNAL_CONFLICT        222

#if (_MSC_VER == 600)
#define MV95ERR_CONECTION_NOT_SUPPORTED 223
#else
#define MVIP95_ERR_CONNECTION_NOT_SUPPORTED 223
#endif

/*****************************************************************************/
/* Data Structures and Constants                                             */
/*****************************************************************************/

/* MVIP-95 Bus types */
#define MVIP95_MVIP_BUS              0x00
#define MVIP95_LOCAL_BUS             0x01
#define MVIP95_MC1_BUS               0x04

/* Software standards */
#define MVIP95_STANDARD_MVIP95       0x01

/* Hardware standards */
#define MVIP95_STANDARD_MVIP90       0x01
#define MVIP95_STANDARD_HMVIP        0x03

/* output mode */
#define MVIP95_DISABLE_MODE          0x0
#define MVIP95_PATTERN_MODE          0x1
#define MVIP95_CONNECT_MODE          0x2
#define MVIP95_FRAMED_CONNECT_MODE   0x3

/* clock type values */
#define MVIP95_STD_CLOCKING          0x00
#define MVIP95_MC1_CLOCKING          0x01
#define MVIP95_MC2_CLOCKING          0x02
#define MVIP95_MC3_CLOCKING          0x03
#define MVIP95_MC4_CLOCKING          0x04
#define MVIP95_H100_CLOCKING         0x05
#define MVIP95_H100_MC1_CLOCKING     0x06

/* clock source values */
#define MVIP95_SOURCE_DISABLE        0x00
#define MVIP95_SOURCE_INTERNAL       0x01
#define MVIP95_SOURCE_SEC8K          0x02
#define MVIP95_SOURCE_MVIP           0x03
#define MVIP95_SOURCE_NETWORK        0x04
#define MVIP95_SOURCE_8KREF          0x05
#define MVIP95_SOURCE_MC1_LEFT       0x06
#define MVIP95_SOURCE_MC1_RIGHT      0x07
#define MVIP95_SOURCE_H100           0x08
#define MVIP95_SOURCE_H100_A         0x08
#define MVIP95_SOURCE_H100_B         0x09
#define MVIP95_SOURCE_H100_NETREF    0x0A
#define MVIP95_SOURCE_H110_NETREF_1  0x0A
#define MVIP95_SOURCE_H110_NETREF_2  0x0B

/* MC1 clock mode values */
#define MVIP95_MC1_SLAVE             0x00
#define MVIP95_MC1_MASTER_LEFT       0x01
#define MVIP95_MC1_MASTER_RIGHT      0x02
#define MVIP95_MC1_SLAVE_NO_MVIP_CLK 0x03

#define MVIP95_EXT_MC1_MASTER_LEFT_NO_MVIP_CLK 0xc4
#define MVIP95_EXT_MC1_MASTER_RIGHT_NO_MVIP_CLK 0xc5

/* MC1 auto fall back values */
#define MVIP95_MC1_DISABLE_AUTO_FB   0x00
#define MVIP95_MC1_ENABLE_AUTO_FB    0x01

/* H100 clock mode values */
#define MVIP95_H100_SLAVE             0x00
#define MVIP95_H100_MASTER_A          0x01
#define MVIP95_H100_MASTER_B          0x02
#define MVIP95_H100_STAND_ALONE	      0x03

/* H100 auto fall back values */
#define MVIP95_H100_DISABLE_AUTO_FB   0x00
#define MVIP95_H100_ENABLE_AUTO_FB    0x01

/* H100 netref clock mode values */
#define MVIP95_H100_NETREF_NONE       0x00
#define MVIP95_H100_NETREF            0x01
#define MVIP95_H100_NETREF_1          0x01
#define MVIP95_H100_NETREF_2          0x02


/* H100 netref clock speed values */
#define MVIP95_H100_NETREF_8KHZ       0x00
#define MVIP95_H100_NETREF_1544MHZ    0x01
#define MVIP95_H100_NETREF_2048MHZ    0x02

/* Clock Status Values */
#define MVIP95_CLOCK_STATUS_GOOD      0x00
#define MVIP95_CLOCK_STATUS_BAD       0x01
#define MVIP95_CLOCK_STATUS_UNKNOWN   0x02

/* Clock Fallback Status Values */
#define MVIP95_H100_NO_FALLBACK_OCCURRED  0x00
#define MVIP95_H100_FALLBACK_OCCURRED     0x01



/* Stream Speed Values */
#define MVIP95_2MBPS_STREAM_SPEED    0x00
#define MVIP95_4MBPS_STREAM_SPEED    0x01
#define MVIP95_8MBPS_STREAM_SPEED    0x02

/* Device Id Values */
#define MVIP95_T1_TRUNK_DEVICE       0X0000
#define MVIP95_E1_TRUNK_DEVICE       0X0001
#define MVIP95_ANALOG_LINE_DEVICE    0X0002
#define MVIP95_CONFERENCE_DEVICE     0X0003

/* Query Driver Info array sizes */
#define  SIZE_DESCRIPTION            80
#define  SIZE_REVISION               16
#define  SIZE_DATE                   12
#define  SIZE_VENDOR                 80

/* MVIP Timing Reference Status */
#define  MVIP95_TIMING_REFERENCE_STATUS_GOOD      0
#define  MVIP95_TIMING_REFERENCE_STATUS_BAD       1
#define  MVIP95_TIMING_REFERENCE_STATUS_UNKNOWN   2

/* MVIP Timing Reference Status Info */
#define  MVIP95_TIMING_REFERENCE_NO_ALARM         0
#define  MVIP95_TIMING_REFERENCE_RED_ALARM        1
#define  MVIP95_TIMING_REFERENCE_BLUE_ALARM       2
#define  MVIP95_TIMING_REFERENCE_YELLOW_ALARM     3


#define  MVIP95_TIMING_REFERENCE_AIS              4
#define  MVIP95_TIMING_REFERENCE_NO_FRM           5
#define  MVIP95_TIMING_REFERENCE_16_AIS           6
#define  MVIP95_TIMING_REFERENCE_FAULT            7
#define  MVIP95_TIMING_REFERENCE_NO_SMF           8



/*****************************************************************************/
/* Structure definitions                                                     */
/*****************************************************************************/

typedef  DWORD  MVIP95_SIZE ;
typedef  DWORD  MVIP95_RETURN ;


typedef struct
{
    DWORD  bus;
    DWORD  stream;
    DWORD  timeslot;

} MVIP95_TERMINUS ;


typedef struct
{
    MVIP95_TERMINUS  terminus;
    DWORD            mode;
    MVIP95_TERMINUS  connected_from;
    DWORD            pattern;

} MVIP95_OUTDESC ;


typedef struct
{
    MVIP95_TERMINUS  terminus;
    DWORD            pattern;

} MVIP95_INDESC ;


typedef struct
{
    MVIP95_SIZE   size;
    BYTE          description [80];
    BYTE          revision [16];
    BYTE          date [12];
    BYTE          vendor [80];
    BYTE          serial_number [80];
    DWORD         board_id;
    DWORD         base_port_address;

} MVIP95_QUERY_BOARD_INFO_PARMS ;


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         clock_type;
    DWORD         clock_source;
    DWORD         network;
#if (_MSC_VER == 600)
} MVIP95CFG_STD_BOARD_CLOCK_PARMS ;
#else
} MVIP95_CONFIG_STD_BOARD_CLOCK_PARMS ;
#endif


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         clock_type;
    DWORD         clock_source;
    DWORD         network;
    DWORD         mc1_clock_mode;
    DWORD         auto_fall_back;
#if (_MSC_VER == 600)
} MVIP95CFG_MC1_BOARD_CLOCK_PARMS ;
#else
} MVIP95_CONFIG_MC1_BOARD_CLOCK_PARMS ;
#endif

typedef struct
{
    MVIP95_SIZE   size;
    DWORD         clock_type;
    DWORD         clock_source;
    DWORD         network;
    DWORD         h100_clock_mode;
    DWORD         auto_fall_back;
    DWORD         netref_clock_speed;
    DWORD         fall_back_master_clock_source;
    DWORD         fall_back_master_network;

#if (_MSC_VER == 600)
} MVIP95CFG_H100_BOARD_CLOCK_PARMS ;
#else
} MVIP95_CONFIG_H100_BOARD_CLOCK_PARMS ;
#endif

typedef struct
{
    MVIP95_SIZE   size;
    DWORD         network;
    DWORD         netref_clock_mode;
    DWORD         netref_clock_speed;

#if (_MSC_VER == 600)
} MVIP95CFG_NETREF_CLOCK_PARMS ;
#else
} MVIP95_CONFIG_NETREF_CLOCK_PARMS ;
#endif


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         reference_source;
    DWORD         network;
    DWORD         status;
    DWORD         status_info;

} MVIP95_QUERY_TIMING_REFERENCE ;





typedef struct
{
    DWORD  clock_source;
    DWORD  network;

} MVIP95_CONFIG_SEC8K_CLOCK_PARMS;


typedef struct
{
    DWORD  clock_source;
    DWORD  network;

} MVIP95_MC1_8KREF_CLOCK_PARMS;



typedef struct
{
    MVIP95_SIZE   size;
    DWORD         clock_type;
    DWORD         clock_source;
    DWORD         network;

} MVIP95_QUERY_HMVIP_BOARD_CLOCK_PARMS ;


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         clock_type;
    DWORD         clock_source;
    DWORD         network;
    DWORD         h100_clock_mode;
    DWORD         auto_fall_back;
    DWORD         fall_back_occurred;
    DWORD         h100_a_clock_status;
    DWORD         h100_b_clock_status;
    DWORD         netref_1_clock_status;
    DWORD         netref_2_clock_status;

} MVIP95_QUERY_H100_BOARD_CLOCK_PARMS ;



typedef struct
{
    MVIP95_SIZE  size;
    BYTE         description [SIZE_DESCRIPTION];
    BYTE         revision    [SIZE_REVISION];
    BYTE         date        [SIZE_DATE];
    BYTE         vendor      [SIZE_VENDOR];

} MVIP95_QUERY_DRIVER_INFO_PARMS;

#if defined (__HIGHC__)
  #pragma Align_members(4);
#endif


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         local_stream;
    DWORD         device_id;
    DWORD         parameter_id;
    BYTE          buffer [1];

} MVIP95_LOCAL_STREAM_PARMS;

#if (_MSC_VER == 600)
typedef   MVIP95_LOCAL_STREAM_PARMS   MVIP95_CFG_LOCAL_STREAM_PARMS ;
#else
typedef   MVIP95_LOCAL_STREAM_PARMS   MVIP95_CONFIG_LOCAL_STREAM_PARMS ;
#endif
typedef   MVIP95_LOCAL_STREAM_PARMS   MVIP95_QUERY_LOCAL_STREAM_PARMS ;


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         local_stream;
    DWORD         local_timeslot;
    DWORD         device_id;
    DWORD         parameter_id;
    BYTE          buffer [1];

} MVIP95_LOCAL_TIMESLOT_PARMS;

#if (_MSC_VER == 600)
typedef   MVIP95_LOCAL_TIMESLOT_PARMS   MVIP95_CFG_LOCAL_TIMESLOT_PARMS ;
#else
typedef   MVIP95_LOCAL_TIMESLOT_PARMS   MVIP95_CONFIG_LOCAL_TIMESLOT_PARMS ;
#endif

#if (_MSC_VER == 600)
typedef   MVIP95_LOCAL_TIMESLOT_PARMS   MVIP95QUERYLOCAL_TIMESLOT_PARMS ;
#else
typedef   MVIP95_LOCAL_TIMESLOT_PARMS   MVIP95_QUERY_LOCAL_TIMESLOT_PARMS ;
#endif

#if defined (__HIGHC__)
  #pragma Align_members(2);
#endif


typedef struct
{
    MVIP95_SIZE     size;
    MVIP95_OUTDESC  output[1];

} MVIP95_OUTPUT_PARMS;

typedef  MVIP95_OUTPUT_PARMS  MVIP95_SET_OUTPUT_PARMS;
typedef  MVIP95_OUTPUT_PARMS  MVIP95_QUERY_OUTPUT_PARMS;


typedef struct
{
    DWORD  timeslots;
    DWORD  device_id;

} MVIP95_LOCAL_DEVICE_DESC;


typedef struct
{
    MVIP95_SIZE               size;
    DWORD                     dvr_revision;
    DWORD                     domain;
    DWORD                     routing;
    DWORD                     blocking;
    DWORD                     sw_standard;
    DWORD                     sw_std_revision;
    DWORD                     hw_standard;
    DWORD                     hw_std_revision;
    DWORD                     num_local_streams;
    MVIP95_LOCAL_DEVICE_DESC  local_devs[1];

} MVIP95_QUERY_SWITCH_CAPS_PARMS;


typedef struct
{
    MVIP95_SIZE    size;
    MVIP95_INDESC  input[1];

} MVIP95_SAMPLE_INPUT_PARMS;


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         speed;
    DWORD         stream [1];

} MVIP95_STREAM_SPEED_PARMS;

#if (_MSC_VER == 600)
typedef   MVIP95_STREAM_SPEED_PARMS   MVIP95_CFG_STREAM_SPEED_PARMS;
#else
typedef   MVIP95_STREAM_SPEED_PARMS   MVIP95_CONFIG_STREAM_SPEED_PARMS;
#endif

typedef   MVIP95_STREAM_SPEED_PARMS   MVIP95_QUERY_STREAM_SPEED_PARMS;


typedef struct
{
    MVIP95_SIZE   size;
    DWORD         minorsw;
    DWORD         stream;
    DWORD         timeslot;
    DWORD         cmhi;
    DWORD         cmlo;
    DWORD         data;

} MVIP95_DUMP_PARMS;


typedef struct
{
    DWORD  reserved;

} MVIP95_RESET_SWITCH_PARMS;



typedef struct
{
    DWORD  bus_enable_state;

} MVIP95_SET_SWITCH_PARMS;



typedef struct
{
    DWORD  verify;

} MVIP95_SET_VERIFY_PARMS;





/**********************************************************************************/
/* Parameter_ids and structures for CONFIG_LOCAL_STREAM and CONFIG_LOCAL_TIMESLOT */
/**********************************************************************************/
 /*
  *   Hardware related definitions have been moved to nmshw.h
  *
  *
  */

#ifdef __cplusplus
    }
#endif

#endif



