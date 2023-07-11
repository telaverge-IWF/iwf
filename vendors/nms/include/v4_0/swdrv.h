/*****************************************************************************
*    File - SWDRV.H
*
*    Description - Header file containing public definitions for
*      using switch drivers.  This file should be included in all
*      MVIP switch drivers.  It should also be included in application
*      programs which call the drivers directly.
*
*
*    Copyright (c) 1991-2002 NMS Communications.  All rights reserved.
*****************************************************************************/

#ifndef __SWDRV_INCLUDED
#define __SWDRV_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

#ifdef FAR
  #undef FAR
#endif
#define FAR

#define DRVINT int

#ifndef DRVINT32
  #define DRVINT32
#endif

#ifndef SWPATH32
  #define SWPATH32
#endif


#if defined(unix)
  #ifdef SUNDDI
    #define DRVENTRY
  #endif

#elif defined (WIN32)
  #define DRVENTRY __stdcall
  #define INT int
  #pragma pack (4)

#endif

#if defined _Solaris64_ || defined __x86_64__
#define LONG          int       /* data type used for some driver parameters */
#else
#define LONG          long      /* data type used for some driver parameters */
#endif

#define REVERSE          8      /* beginning of the reversed streams         */
#define NETWORK         16      /* beginning of network connections          */

/************** Function prototype for driver entry point ******************/

#if !defined(unix) && !defined (WIN32)
  DRVINT DRVENTRY SwDevIOCtl( DRVINT sw, DRVINT funct, DRVINT FAR *p );
#endif

/********************** MVIP Driver Function Codes *************************/

#define RESET_SWITCH       0x00 /* Resets the switch block to a known state   */
#define QUERY_SWITCH_CAPS  0x01 /* Returns the switch block capabilities      */

#define SET_OUTPUT         0x10 /* Makes & Breaks connections                 */
#define QUERY_OUTPUT       0x11 /* Returns the state of each switch output    */
#define SAMPLE_INPUT       0x12 /* Returns the data of an input time slot     */
#define SET_VERIFY         0x13 /* Enables continuous verification of         */
                                /* making and breaking.                       */

#if defined(unix)
#define MONITOR_SIGNALBITS 0x14 /* Monitor input time slot A bit signal for   */
                                /* transition to desired level                */
#ifdef SLEEP
#undef SLEEP
#endif
#define SLEEP              0x15 /* Sleep                                      */
#endif

#define CONFIG_CLOCK       0x20 /* Initializes and configures MVIP clocking   */
                                /* options                                    */

#define CONFIG_CARRIER     0x30 /* Initializes and configures a T1/E1 carrier */
#define CONFIG_CHANNEL     0x31 /* Configures specific carrier channels       */
#define WAIT_ALARM         0x32 /* waits until the carrier indicates an alarm */
#define CARRIER_STATUS     0x33 /* Returns status information about a carrier */
#define SET_CONDITIONING   0x34 /* Modifies conditioning patterns             */
#define QUERY_CONDITIONING 0x35 /* Returns state of conditioning              */
#define START_MONITOR      0x36 /* Starts monitor thread (OS/2 only)          */
#define START_SUPV         0x37 /* Start Monitoring one channel's signaling   */
#define WAIT_SUPV          0x38 /* Wait for change on monitored channel       */
#define STOP_SUPV          0x39 /* Stop monitoring specified channel          */

#define CONFIG_DPHONE      0x40 /* initialize DPhone chip                     */
#define GENERATE_DTMF      0x41 /* generate DTMF using DPhone chip            */

#define CONFIG_GAIN        0x42 /* Changes gain of CODECs (ATI/ASI); equiv to */
#define CONFIG_LOCAL_DEV   0x42 /* Configure local device             (ag8sw) */
#define QUERY_LOCAL_CFG    0x43 /* Query local device configuration   (ag8sw) */
#define SET_LOCAL_IDLE     0x44 /* Set local idle                     (ag8sw) */
#define QUERY_LOCAL_IDLE   0x45 /* Query local idle                   (ag8sw) */
#define QUERY_LOCAL_DEV_ID 0x46 /* Query local device id              (ag8sw) */
#define FMIC_WRITE_CNTRL   0x47 /* Write an control register          (fmicsw)*/
#define FMIC_READ_CNTRL    0x48 /* Read FMIC control register         (fmicsw)*/

#define FREE_DRIVER        0x4F /* Release driver before close        (ag8sw) */

#define QUERY_DRV_INFO          0x50    /* Get generic driver info.     */
#define QUERY_BRD_INFO          0x51    /* Get info about the board.    */

/*
 *  The following two codes are here historically for WTI8 support.  If
 *  writing new code to read and write WTI8 SLACs, use WTI8_WRITE_SLAC and
 *  WTI8_READ_SLAC in \sw\include\swext.h instead.
 */

#define CONFIG_PORT             0x56
#define QUERY_PORT              0x57



#define DUMP_SWITCH        0x70 /* Returns the state of a specific switch     */
                                /* component, stream and time-slot.           */
#define SET_TRACE          0x71 /* Enables printing of diagnostic             */
                                /* information.                               */
#define TRISTATE_SWITCH    0x72 /* GLobally enables/disables an MVIP switch   */
                                /* block.                                     */
#define START_CONDITIONING 0x73 /* Simulates carrier down conditions          */
#define STOP_CONDITIONING  0x74 /* Simulates carrier recovery conditions      */
#define CHANGE_IOPORTS     0x75 /* Changes I/O port addresses                 */

/***************** 0x80-0xFF  Vendor-Specific Function Codes ******************/

                        /*----------------*\

   The MVIP-90 Standard designates the range 0x80 - 0xFF as vendor-specific
   command codes.  We subdivide this range as follows:

      0x80 - 0xBF  --  Vendor-specific commands that span multiple drivers
      0xC0 - 0xFF  --  Commands specific to a particular driver

   Codes for vendor-specific commands used in multiple drivers should be
   defined in this header file.  All device-specific driver function codes
   should be in the range of 0xC0 to 0xFF.  The driver specific codes need
   not be unique across drivers and should be placed in the individual driver
   header files, not in this file.

                        \*----------------*/

#define QUERY_TIMESLOT          0x82 /* Retrieve configuration data for S:T   */



/**************************** Error Returns ********************************/

                      /* Codes 20x: General Errors */

#define SUCCESS                    0 /* Driver successfully completed command */
#define MVIP_INVALID_COMMAND     200 /* Command code is not supported         */
#define MVIP_DLL_INVALID_DEVICE  201 /* (OS/2 DLL specific) The switch number */
                                     /* passed to driver DLL is out of range. */
#define MVIP_DEVICE_ERROR        202 /* An error was returned from a device   */
                                     /* driver called by this driver.         */
#if defined(unix)
#define MVIP_SLEEP_BUSY          203 /* Another process that has opened the   */
                                     /* device is sleeping                    */
#endif
#define MVIP_NO_RESOURCES        204 /* An internal driver rewource has been  */
                                     /* exhausted.                            */

                    /* Codes 21x: Parameter Errors */

#define MVIP_INVALID_STREAM      210 /* Stream number in parameter list is    */
                                     /* out of range.                         */
#define MVIP_INVALID_TIMESLOT    211 /* Time slot in parameter list is out    */
                                     /* of range.                             */
#define MVIP_MISSING_PARAMETERS  212 /* Not enough parameters provided to     */
                                     /* perform command.                      */
#define MVIP_INVALID_CLOCK_PARM  213 /* Invalid clock configuration parameter */
#define MVIP_INVALID_CARRIER     214 /* Incorrect carrier number in parameter */
                                     /* list.                                 */
#define MVIP_INVALID_CARRIER_PARM 215/* Incorrect carrier configuration in    */
                                     /* parameter list.                       */
#define MVIP_INVALID_MODE         216/* Incorrect SET_OUTPUT or QUERY_OUTPUT  */
                                     /* mode.                                 */
#define MVIP_INVALID_MINOR_SWITCH 217/* Minor (internal) switch error.        */
#define MVIP_INVALID_PARAMETER    218/* General invalid parameter error.      */

                      /* Codes 22x: Switch Errors */

#define MVIP_NO_PATH             220 /* Connection cannot be made due to      */
                                     /* blocking or other switch limitation   */
#define MVIP_SWITCH_VERIFY_ERROR 221 /* Verification of switch operation      */
                                     /* failed                                */
#define MVIP_INTERNAL_CONFLICT   222 /* More than one internal switch is in   */
                                     /* conflict.                             */
#define MVIP_CONNECTION_NOT_SUPPORTED  223


                 /* Codes 23x: Network Interface Errors */

#define MVIP_CARRIER_NOT_CONFIGURED 230 /* Carrier not configured             */
#define MVIP_ALARM_TIMEOUT          231 /* A timeout occurred while waiting   */
                                        /* for a change to the alarm state of */
                                        /* a carrier.                         */
#define MVIP_NO_TRUNK_CONNECTION    232 /* Promptus speficic                  */
#define MVIP_NO_MONITOR             233 /* Monitor thread not running (OS/2)  */
#define MVIP_ALARM_QUEUE_BUSY       234 /* Another process is waiting for a   */
                                        /* change to the alarm state of any   */
                                        /* of the carriers supported by the   */
                                        /* device.                            */

#if defined(unix)
#define MVIP_SIG_MONITOR_BUSY       235 /* Another process is monitoring the  */
                                        /* signalling bits of a T1 channel    */
                                        /* supported by the device.           */
#elif defined(WIN32)
#define MVIP_ALARM_REQUEST_PENDING  236 /* alarm request pending              */

#endif

                 /* Codes 24x: Supervision Monitor Errors */

#define MVIP_SUPV_MONITOR_TIMEOUT   240 /* WAIT_SUPV timed out with no change */
#define MVIP_SUPV_MONITOR_STOPPED   241 /* Another process or thread called   */
                                        /*  STOP_SUPV for the port monitored  */
#define MVIP_SUPV_MONITOR_FAILED    242 /* Monitor was aborted because of an  */
                                        /*  incompatible switch connection.   */
#define MVIP_NOT_IN_PATTERN_MODE    243 /* START_SUPV specified output        */
                                        /* pattern but port was connected or  */
                                        /* disabled.                          */
#define MVIP_INVALID_SUPV_HANDLE    244 /* Handle does not refer to an active */
                                        /* monitor.                           */
#define MVIP_INVALID_SUPV_TIMEOUT   245 /* Driver does not support non-zero   */
                                        /* timeout for WAIT_SUPV              */
#define MVIP_SUPV_REQUEST_PENDING   246 /* supv request pending (internal)    */

                 /* Codes 25x: Generic Device Specific codes */

#define MVIP_NO_SUCH_PHYSGROUP      250
#define MVIP_NO_SUCH_PORT           251
#define MVIP_NO_SUCH_DTYPE          252
#define MVIP_BUS_NOT_ENABLED        253 /* Board has been configured to be    */
                                        /* stand-alone.                       */

/********************** Data structures and defines ************************/

struct capabilities_parms /* parameter structure for QUERY_SWITCH_CAPS< */
{
    DRVINT size ;          /* size of this structure              */
    DRVINT revision ;      /* major.minor x 100                   */
    DRVINT domain;         /* mvip connectivity                   */
    DRVINT routing ;       /* half-duplex connectivity            */
    DRVINT blocking;       /* blocking limitations                */
    DRVINT networks;       /* total number of network connections */
    DRVINT channels[64];   /* channels per network connection     */
};

struct output_parms     /* parameter structure for SET_OUTPUT command */
{
    DRVINT output_stream;  /* output stream 0...                            */
    DRVINT output_slot;    /* output time slot 0...31                       */
    DRVINT mode;           /* mode (see below)                              */
    DRVINT input_stream;   /* input stream 0... (used in CONNECT_MODE only) */
    DRVINT input_slot;     /* input time slot 0...31 (CONNECT_MODE only)    */
    DRVINT message;        /* message (used in PATTERN_MODE only)           */
};

#define CONNECT_MODE 2  /* make connections                    */
#define PATTERN_MODE 1  /* send pattern (message mode)         */
#define DISABLE_MODE 0  /* break connections (tristate output) */

struct sample_parms     /* parameter structure for SAMPLE_INPUT command */
{
    DRVINT input_stream;   /* input stream 0...      */
    DRVINT input_slot;     /* input time slot 0...31 */
    DRVINT input_sample;   /* sampled data           */
};

struct start_supv_parms
{
    DRVINT stream ;        /* stream to monitor (0...)                      */
    DRVINT slot ;          /* slot to monitor (0..31)                       */
    DRVINT target_pattern; /* signal bit pattern to monitor for             */
    DRVINT output_pattern; /* bit pattern to assert when target detected    */
    DRVINT qualify_time;   /* time in ms that target pattern must persist   */
    LONG handle_ret ;      /* handle returned                               */
};

struct wait_supv_parms
{
    LONG handle ;       /* Handle returned by start_supv */
    LONG timeout;       /* Time to wait if blocking      */
};


/* Constants used for START_SUPV */
#define A_BIT_ON  0x0008
#define A_BIT_OFF 0x0080
#define B_BIT_ON  0x0004
#define B_BIT_OFF 0x0040

struct stop_supv_parms
{
    LONG handle ;       /* Handle returned by start_supv */
};

/* The following struct is used for the UNIX Version 1.00 T1 driver */
#if defined(unix)
struct monsigbits_parms /* parameter structure for MONITOR_SIGNALBITS command */
{
    DRVINT input_stream ;   /* input stream 0...                 */
    DRVINT input_slot ;     /* input time slot 0...31            */
    DRVINT origvalue ;      /* original value of signalling bits */
    DRVINT newvalue ;       /* new value of signalling bits      */
} ;

struct sleep_parms            /* parameter structure for SLEEP command */
{
    DRVINT LSW_sleep_duration ;  /* least significant word of sleep period */
    DRVINT MSW_sleep_duration ;  /* most significant word of sleep period  */
} ;
#endif

/* The CONFIG_CLOCK command conforms to a version of the MVIP-90 Standard
 * prior to release 1.1. The values and parameters used are described here. */
                                    /* Defines used by CONFIG_CLOCK */
                                    /* clock reference sources */
#define CLOCK_REF_MVIP       0x000  /* Clock from MVIP. Not driven          */
#define CLOCK_REF_SEC8K      0x001  /* Clock from SEC8K. Drives MVIP clocks */
#define CLOCK_REF_OSC        0x002  /* Clock from OSC. Drives MVIP clocks   */
#define CLOCK_REF_NET1       0x003  /* Clock from T1a. Drives MVIP clocks   */
#define CLOCK_REF_NET2       0x004  /* Clock from T1b. Drives MVIP clocks   */
                                    /* clock outputs */
#define SEC8K_NOT_DRIVEN     0x000  /* SEC8K not driven by this card        */
#define SEC8K_DRIVEN_BY_OSC  0x200  /* SEC8K driven by OSC                  */
#define SEC8K_DRIVEN_BY_NET1 0x300  /* SEC8K driven by T1a                  */
#define SEC8K_DRIVEN_BY_NET2 0x400  /* SEC8K driven by T1b                  */

/* The least significant byte of the structure used by the CONFIG_CLOCK
 * command indicates the clock reference source. The next byte indicates
 * clock output */
struct clock_parms       /* parameter structure for CONFIG_CLOCK command */
{
    DRVINT clockparms ;  /* LSB is clock reference; next byte is clock output */
} ;

struct dump_parms       /* parameter structure for DUMP_SWITCH command */
{
    DRVINT size;           /* size of this structure   */
    DRVINT minor;          /* minor switch number 0... */
    DRVINT stream;         /* stream number 0...7      */
    DRVINT slot;           /* slot number 0...31       */
    DRVINT cmhi;           /* connection memory hi     */
    DRVINT cmlo;           /* connection memory lo     */
    DRVINT data;           /* data memory              */
};

#define TRACE_SWITCH_WRITE   0x0001
#define TRACE_SWITCH_READ    0x0002
#define TRACE_SWITCH_RW      0x0003
#define TRACE_SWITCH_ENTRIES 0x0004

struct trace_parms      /* parameter structure for SET_TRACE command */
{
  DRVINT code;                             /* tracing code (ON/OFF) */
  DRVINT (*printf)( const char *, ... );   /* printf function.      */
};

struct carrier_parms    /* parameter structure for CONFIG_CARRIER command */
{
    DRVINT size ;          /* size of this structure                       */
    DRVINT trunk ;         /* T1 unit on device                            */
    DRVINT frame;          /* see below                                    */
    DRVINT code ;          /* see below                                    */
    DRVINT debounce;       /* 1=chip does 6-9 ms debounce of recd A&B bits */
};

#define DT_D4     0     /* Values for CONFIG_DT 'frame' parameter */
#define DT_ESF    1
#define DT_CEPT   2

#define DT_AMI     0    /* Values for CONFIG_DT 'code' parameter */
#define DT_B8ZS    1
#define DT_AMI_ZCS 2
#define DT_HDB3    3    /* E1 Only */

struct channel_parms    /* Parameter structure for CONFIG_CHANNEL command */
{
    DRVINT size ;          /* size of this structure                      */
    DRVINT trunk ;         /* T1 unit on device                           */
    DRVINT channel ;       /* 0 - n-1                                     */
    DRVINT invert ;        /* 0 - no inversion; 1 - invert signal bits    */
    DRVINT loopback ;      /* 0 - normal;  1 - loop back channel          */
    DRVINT robbedbit;      /* 0 - clear channel; 1 - robbed bit signaling */
} ;

struct alarm_parms              /* Parameter structure for WAIT_ALARM command */
{
    DRVINT LSW_sleep_duration ; /* least significant word of maximum sleep    */
                                /* period                                     */
    DRVINT MSW_sleep_duration ; /* most significant word of maximum sleep     */
                                /* period                                     */
    DRVINT alarm_state ;        /* 0 - alarm off; 1 - alarm on                */
    DRVINT trunk_number ;       /* trunk number which had alarm state change  */
} ;

/* Structure returned by the CARRIER_STATUS command.  This data is maintained */
/* by the driver's polling loop.                                              */

struct carrier_status
{
    DRVINT size;           /* Set by caller when requesting this structure */
    DRVINT trunk;          /*  ''                                          */
    DRVINT event_count;    /* incremented when anything changes            */
    DRVINT device;         /* device number (0-3)   (-1 => not configured) */
    DRVINT red_alarm ;     /* Red Alarm flag                               */
    DRVINT yellow_alarm ;  /* Yellow Alarm flag                            */
    DRVINT blue_alarm ;    /* Blue Alarm flag                              */
    DRVINT failed_seconds; /* failed seconds accumulator                   */
    DRVINT errored_seconds;/* errored seconds accumulator                  */
    DRVINT slips ;         /* slips accumulator                            */
    DRVINT bpvs;           /* BPV accumulator  (multiple of 64)            */
    LONG ltime ;           /* start time                                   */
    DRVINT sync ;          /* 0=> in sync; 1=blue; 2=no sync; 3=no SF sync */
};


struct e1_carrier_status
{
    DRVINT size;           /* Set by caller when requesting this structure */
    DRVINT trunk;          /*  ''                                          */
    DRVINT event_count;    /* incremented when anything changes            */
    DRVINT device;         /* device number (0-3)   (-1 => not configured) */
    DRVINT nf_alarm ;      /* No-frame alarm flag
                              1 = no frame
                              2 = loss of signal (AG-E1 only)
                              3 = bit error rate alarm (AG-E1 only) */
    DRVINT remote_alarm ;  /* Remote alarm detected
                              1 = remote no frame alarm indication
                              2 = remote no signaling multiframe alarm
                                  indication (AG-E1 only) */
    DRVINT ais_alarm  ;    /* All-ones alarm
                              1 = all ones alarm
                              2 = time slot 16 all ones alarm (AG-E1 only) */
    DRVINT failed_seconds; /* failed seconds accumulator                   */
    DRVINT errored_seconds;/* errored seconds accumulator                  */
    DRVINT slips ;         /* slips accumulator                            */
    DRVINT ber;            /* Bit error rate 1 = 10^4                      */
    LONG ltime ;           /* start time                                   */
    DRVINT sync ;          /* 0 = in sync
                              1 = All ones alarm
                              2 = No frame sync
                              3 = No Multiframe Sync
                              4 = Bit error rate too high (except AG-E1)
                              5 = No CRC Multiframe Sync (AG-E1 only) */


};



#define MAX_DESCRIPTION_SZ 80
#define MAX_REV_SZ  16
#define MAX_DATE_SZ 12

struct drv_info_parms  {
    unsigned LONG       size;                      /* Size of structure     */
    char        description[ MAX_DESCRIPTION_SZ ]; /* Null terminated ascii */
    char        rev[ MAX_REV_SZ ] ;                /* Version of DRIVER     */
    char        date[ MAX_DATE_SZ ];               /* yyyy/mm/dd            */
    char        vendor[ MAX_DESCRIPTION_SZ ];
    } ;


struct brd_info_parms  {
    unsigned LONG  size;
    char        description[ MAX_DESCRIPTION_SZ ]; /* Null terminated ascii  */
    char        rev[ MAX_REV_SZ ];                 /* Version of BOARD       */
    char        date[ MAX_DATE_SZ ];               /* yyyy/mm/dd             */
    char        serial[ MAX_DESCRIPTION_SZ ];  /*Serial number(vendor format)*/
    unsigned LONG       boardid;               /* Vendor specific boardid.   */
    } ;


/*----------------         defines and structures        --------------------*\
                                   for
\*----------------           QUERY_TIMESLOT              --------------------*/



  /*
   *   Configuration items available through the
   *   QUERY_TIMESLOT command.
   *
   */
#define  HYBRID_ID                0x00


  /*
   *    Data structure for QUERY_TIMESLOT commands
   *
   */
typedef struct _QUERY_TIMESLOT_PARMS
{
    DRVINT size ;            /*  Size of this buffer in bytes              */
    DRVINT stream ;          /*                                            */
    DRVINT timeslot ;        /*  S:T for which config info is desired      */
    DRVINT item ;            /*  Config item for which info is desired     */
                             /*  (codes defined above)                     */
    DRVINT buffer [1] ;      /*  Buffer to receive configuration item data */

} QUERY_TIMESLOT_PARMS ;





/*----------------  ------------------------------------  -------------------*/

#if defined (WIN32)
#pragma pack ()
#endif

#ifdef __cplusplus
}
#endif



#endif /* SWDRV_INCLUDED */

