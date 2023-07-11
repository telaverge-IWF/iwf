/***************************************************************************\
 *
 *  nmshw.h - Definitions related to Natural MicroSystems' hardware.
 *
 *
 * Copyright (c)1996-2001 Natural MicroSystems Corporation. All rights reserved.
\***************************************************************************/
#ifndef __NMSHW_INCLUDED
#define __NMSHW_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif


/*---------------------------------------------------------------------------
 *  CG Board TYPE (EEPROM value) - this value is different for each bare board
 * variant
 *--------------------------------------------------------------------------*/

#define OAM_PRODUCT_NO_CG6000C               0x601  // This is the Compact PCI board
#define OAM_PRODUCT_NO_CG6000                0x603  // This is the Standard PCI board
#define OAM_PRODUCT_NO_CG6100C	             0x610

/*---------------------------------------------------------------------------
 *  AG Board TYPE (EEPROM value) - this value is different for each bare board
 * variant (although T1/E1 are no longer actually different)
 *--------------------------------------------------------------------------*/

#define AG_BOARDTYPE_DIGITAL 0x500
#define AG_BOARDTYPE_ANALOG  0x501   /* In AGMON board type ANALOG is */
#define AG_BOARDTYPE_AG8     0x501   /* akin to AG8    -IL            */
#define AG_BOARDTYPE_T1      0x502
#define AG_BOARDTYPE_E1      0x503
#define AG_BOARDTYPE_QT      0x504
#define AG_BOARDTYPE_QE      0x505
#define AG_BOARDTYPE_2000    0x506
#define AG_BOARDTYPE_CPCI_QT 0x507
#define AG_BOARDTYPE_CPCI_QE 0x508
#define AG_BOARDTYPE_4000T1  0x509
#define AG_BOARDTYPE_4000E1  0x50A
#define AG_BOARDTYPE_2000EM  0x50B
#define AG_BOARDTYPE_4000CT1 0x50C
#define AG_BOARDTYPE_4000CE1 0x50D
#define AG_BOARDTYPE_2000DPBX 0x50F  /* AG2000 + VTG CPM */
#define AG_BOARDTYPE_2000BRI 0x510   /* AG2000 + BRI */
#define AG_BOARDTYPE_2000C   0x511





/*---------------------------------------------------------------------------
 *  AG "subtype (EEPROM value).  This value is unique for each board variant.
 *
 *--------------------------------------------------------------------------*/
#define AG24_SUBTYPE          1
#define AG24PLUS_SUBTYPE      2
#define AG30_SUBTYPE          3
#define AG8_SUBTYPE           4
#define AGT1_SUBTYPE          5
#define AGE1_SUBTYPE          6
#define AG8F_SUBTYPE          7
#define AG_SUBTYPE_AVALON_T1  8
#define AG_SUBTYPE_AVALON_E1  9
#define AGQT_SUBTYPE          0xA
#define AGQE_SUBTYPE          0xB
#define AGQT_DUAL_SUBTYPE     0xC
#define AGQE_DUAL_SUBTYPE     0xD
#define AGQT_0DSP_SUBTYPE     0xE
#define AGQE_0DSP_SUBTYPE     0xF
#define AG_SUBTYPE_QT_HI_Z    0x10
#define AG_SUBTYPE_QE_HI_Z    0x11
#define AG_SUBTYPE_T1_300     0x12
#define AG_SUBTYPE_E1_300     0x13
#define AG_SUBTYPE_2000LS     0x14
#define AG_SUBTYPE_2000EM     0x15
#define AG_SUBTYPE_4000_1T    0x16
#define AG_SUBTYPE_4000_1E    0x17
#define AG_SUBTYPE_4000_2T    0x18
#define AG_SUBTYPE_4000_2E    0x19
#define AG_SUBTYPE_4000_4T    0x1A
#define AG_SUBTYPE_4000_4E    0x1B
#define AG_SUBTYPE_4000_NOLI  0x1D
#define AG_SUBTYPE_2000C      0x1F
#define AG_SUBTYPE_2000_BRI_2 0x20
#define AG_SUBTYPE_2000_BRI_4 0x21


/* Daughter board IDs: */
#define DBID_NONE      0x00     /* no board    */
#define DBID_AG2_16    0x03     /* AG2 16DSPs  */
#define DBID_AG2_24    0x04     /* AG2 24DSPs  */
#define DBID_AG2_32    0x05     /* AG2 32DSPs  */
#define DBID_AGRT2     0x06     /* AG-RT II    */
#define DBID_CHICKADEE 0x07     /* ethernet?   */
#define DBID_DIVA_IId  0x09     /* 4th DIVA II */
#define DBID_DIVA_IIc  0x0a     /* 3rd DIVA II */
#define DBID_DIVA_IIb  0x0b     /* 2nd DIVA II */
#define DBID_DIVA_IIa  0x0c     /* 1st DIVA II */
#define DBID_AGRT      0x0d     /* AG-RT       */
#define DBID_DB51      0x0f     /* 8 DSP board */
#define DBID_DB31      0x10     /* DIVA I      */
#define DBID_OAZ_DD4   0x11     /* OAZ DD4     */


/* EEPROM Bus types */
#define AG_BUSTYPE_MVIP90    0xffff
#define AG_BUSTYPE_H100      0
#define AG_BUSTYPE_H110      1


/*------------------------------------------------------------------*\
 *                                                                  *
 *                  Analog Line Interface Definitions               *
 *                                                                  *
 *                                                                  *
 *     There are multiple generations of line interface             *
 *     architecture.  ISA boards typically employ the               *
 *     AG Hybrid architecture.  These line interfaces are small     *
 *     (~1.5x10 cm) plug-in circuit boards inserted perpendicular   *
 *     to the parent AG board.  PCI boards typically employ         *
 *     the AG signaling module architecture.  These line            *
 *     interfaces are small (~4x9 cm) daughterboards attached       *
 *     parallel to the parent AG board.                             *
 *                                                                  *
 *     In the following definitions,                                *
 *                                                                  *
 *     class indicates hardware architecture generation             *
 *     type  indicates a kind of physical interface and, depending  *
 *           on class, may or may not include hardware revision     *
 *                                                                  *
\*------------------------------------------------------------------*/


      /*
       *   Definitions for the AG signaling module generation
       *   of analog line interfaces.
       *
       *
       */
    #define NMS_INTERFACE_AG_SIGNALING_MODULE      (0x01)   /*  class  */

    #define NMS_SIGNALING_MODULE_LOOP_START        (0x00)
    #define NMS_SIGNALING_MODULE_GROUND_START      (0x01)
    #define NMS_SIGNALING_MODULE_SUBSCRIBER_LOOP   (0x02)
    #define NMS_SIGNALING_MODULE_DID               (0x03)
    #define NMS_SIGNALING_MODULE_2W_EM             (0x04)
    #define NMS_SIGNALING_MODULE_4W_EM             (0x05)
    #define NMS_SIGNALING_MODULE_MONITOR           (0x06)
    #define NMS_SIGNALING_MODULE_PBX               (0x07)
    #define NMS_SIGNALING_MODULE_NOT_POPULATED     (0x0F)


      /*
       *   Definitions for the AG hybrid generation
       *   of analog line interfaces
       *
       */
    #define NMS_INTERFACE_AG_HYBRID  (0x00)           /*  class  */

                                      /* First run parts */
    #define HYBRID_ID_xLS     0x07    /*  Loop Start                     */
    #define HYBRID_ID_xLSGS   0x00    /*  Loop Start / Ground Start      */
    #define HYBRID_ID_xDID    0x08    /*  DID / E&M                      */
    #define HYBRID_ID_xMBLS   0x0F    /*  Make Busy Loop Start           */

                                      /* 2nd run parts */
    #define HYBRID_ID_LS      0x37    /*  Loop Start                     */
    #define HYBRID_ID_LSGS    0x30    /*  Loop Start / Ground Start      */
    #define HYBRID_ID_DID     0x38    /*  DID / E&M                      */
    #define HYBRID_ID_MBLS    0x3F    /*  Make Busy Loop Start           */

    #define HYBRID_ID_OWS     0x10    /*  Operator Work Station          */
    #define HYBRID_ID_OWSR    0x1F    /*  Operator Work Station w/ Ring  */
    #define HYBRID_ID_MON     0x18    /*  High Impedance Monitor         */
    #define HYBRID_ID_ATH     0x17    /*  Audio Tap Hybrid               */
    #define HYBRID_ID_ELS     0x78    /*  Enhanced loopstart             */
    #define HYBRID_ID_EM4WIRE 0x58    /*  (was 0x78 until 4/97)          */




/*------------------------------------------------------------------*\
 *                                                                  *
 *        Parameter ID and data structure definitions for           *
 *        local device configuration through switching.             *
 *                                                                  *
\*------------------------------------------------------------------*/


      /*
       *  NMS defined device_id s
       *
       */
    #define NMS_ISDN_HDLC_DEVICE            0x80000001
    #define NMS_TASK_PROCESSOR_DEVICE       0x80000002
    #define NMS_NULL_DEVICE                 0xFFFFFFFF

      /*
       *  NMS defined parameter_id s
       *
       */
    #define NMS_FRAMER_CONFIG               0x80000001 /* configure trunks and    */
    #define NMS_CHANNEL_CONFIG              0x80000002 /* channels on AGQT/QE     */
    #define NMS_QSLAC_CONFIG                0x80000003 /* QSLAC read/write        */
    #define NMS_ANALOG_INTERFACE_TYPE       0x80000004
    #define NMS_QSLAC_REVISION              0x80000005 /* hardware diagnostic     */
    #define NMS_EPLD_LOOPBACK               0x80000006 /* hardware diagnostic     */

    #define MVIP95_INPUT_GAIN               0x80000008  /* Rx line gain           */
    #define MVIP95_OUTPUT_GAIN              0x80000009  /* Tx line gain           */

    #define NMS_CONF_GET_SEAT_PARAMETER     0x80000010  /* Get param for stream:timeslot      */
    #define NMS_CONF_SET_SEAT_PARAMETER     0x80000011  /* Set param for stream:timeslot      */
    #define NMS_CONF_GET_CONF_DEFAULT       0x80000012  /* Get default applied to new seats   */
    #define NMS_CONF_SET_CONF_DEFAULT       0x80000013  /* Set default applied to new seats   */
    #define NMS_CONF_GET_SWITCH_DEFAULT     0x80000014  /* Get default applied to new confs   */
    #define NMS_CONF_SET_SWITCH_DEFAULT     0x80000015  /* Set default applied to new confs   */
    #define NMS_CONF_RELEASE_SEAT           0x80000016  /* Disconnect and free seat resources */
    #define NMS_CONF_RELEASE_CONF           0x80000017  /* Disconnect and free conf resources */
    #define NMS_CONF_GET_SWITCH_STATUS      0x80000018  /* Get info on switch's conf streams  */
    #define NMS_CONF_GET_CONF_STATUS        0x80000019  /* Get info on a conf stream          */


    /* Structure and defines for NMS_FRAMER_CONFIG */
    typedef struct nms_config_framer_parms {
            DWORD   size;
            DWORD   trunk;
            DWORD   frame_type;
            DWORD   line_code;
            DWORD   debounce;
    } NMS_CONFIG_FRAMER_PARMS ;

    /* Values for frame_type */
    #define DT_D4 0
    #define DT_ESF 1
    #define DT_CEPT 2
    #define DT_ESF_4KHZ 1   /* should be equivalent to DT_ESF */
    #define DT_ESF_2KHZ_A 4 /* use frames 3, 7, 11, 15, 19, 23 */
    #define DT_ESF_2KHZ_B 5 /* use frames 1, 5, 9, 13, 17, 21 */
    #define DT_SLC96 6
    #define DT_T1DM 7 /* R bit unaffected or FDL data replaces R bit (see XBAS)*/
    #define DT_CEPT_CCS 8

    /* Values for line_code */
    #define DT_AMI      0
    #define DT_B8ZS     1
    #define DT_AMI_ZCS  2
    #define DT_AMI_BELL DT_AMI_ZCS
    #define DT_HDB3     3 /* E1 only */
    #define DT_AMI_DDS  4
    #define DT_AMI_GTE  5


    /* Structure for NMS_CHANNEL_CONFIG */
    typedef struct nms_config_channel_parms {
            DWORD   size;
            DWORD   trunk;
            DWORD   channel;
            DWORD   invert;
            DWORD   loopback;
            DWORD   robbedbit;
    } NMS_CONFIG_CHANNEL_PARMS ;


     /*
      *    structure for determining a network port's line interface type.
      *
      *   bit field     meaning
      *    31..24  -  reserved
      *    23..16  -  reserved
      *    15..08  -  line interface class (hardware architecture)
      *    07..00  -  line interface type
      *
      *
      */

    typedef struct
    {
        DWORD type ;

    } NMS_ANALOG_INTERFACE_TYPE_PARMS ;


     /*
      *   Macros for extracting line interface class and type.
      *
      *
      *   Ex:
      *   {
      *       NMS_ANALOG_INTERFACE_TYPE_PARMS  port ;
      *       SWI_LOCALTIMESLOT_ARGS           args ;
      *       BYTE                             class ;
      *       BYTE                             type ;
      *
      *       args.localstream   = 0 ;
      *       args.localtimeslot = 7 ;
      *       args.deviceid      = MVIP95_ANALOG_LINE_DEVICE ;
      *       args.parameterid   = NMS_ANALOG_INTERFACE_TYPE ;
      *
      *       swiGetLocalTimeslotInfo (          swihd,
      *                                        & args,
      *                                (void*) & port,
      *                                (sizeof)  port) ;
      *
      *       class = GET_ANALOG_INTERFACE_CLASS(port.type) ;
      *       type  = GET_ANALOG_INTERFACE_TYPE(port.type) ;
      *   }
      */
    #define GET_ANALOG_INTERFACE_CLASS(p)  (((p) & 0x0000FF00) >> 8)
    #define GET_ANALOG_INTERFACE_TYPE(p)    ((p) & 0x000000FF)



      /*
       *  NMS gain control
       *
       *  Multiply gain in dB by 1000.
       *  Example: for -3 dB, set x.gain = -3000
       *
       *  parameterid:      MVIP95_INPUT_GAIN
       *                           or
       *                    MVIP95_OUTPUT_GAIN
       *
       */
    typedef struct NMS_LINE_GAIN_PARMS
    {
        INT32  gain ;

    }   NMS_LINE_GAIN_PARMS ;

      /*
       *  NMS epld diagnostic mode
       *  (for internal NMS use)
       *
       */
    typedef struct
    {
        #define EPLD_LOOPBACK_ON     0
        #define EPLD_LOOPBACK_OFF    1

        DWORD loopback_mode ;

    } NMS_EPLD_PARMS ;


      /*
       *  NMS QSLAC device revision
       *  (for internal NMS use)
       *
       */
    typedef struct
    {
        DWORD revision ;

    } NMS_QSLAC_REVISION_PARMS ;


      /*
       *  NMS QSLAC configuration
       *  (for internal NMS use)
       *
       */
    #define NMS_MAX_QSLAC_COMMAND_LENGTH    (20)  /*  in bytes     */
    #define NMS_MAX_NUMBER_QSLAC_COMMANDS   (32)  /*  24 commands  */
    #define NMS_MAX_QSLAC_BUFFER_LENGTH (   NMS_MAX_QSLAC_COMMAND_LENGTH \
                                          * NMS_MAX_NUMBER_QSLAC_COMMANDS)

    typedef struct
    {
        char buffer[NMS_MAX_QSLAC_BUFFER_LENGTH] ;

    }  NMS_QSLAC_CONFIG_PARMS ;


#ifdef __cplusplus
    }
#endif

#endif



