/*****************************************************************************
 *
 * coseprom.h - TXEEPROM
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

#ifndef _COSEPROM_H
#define _COSEPROM_H

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
 * NMS Standard
 *****************************************************************************/
typedef struct
{
    U16 Family;                // Product family
    U16 TestLevel;             // Test Level – specified the exact board component
    U8  TestLevelRev;          // Test Level Revision – the number after the dash
    U8  SoftwareComp;          // Software compatibility revision – increment if a
                               // hardware change caused a software change
    U16 available;             // Available, must be zero
    U16 MFGYear;               // manufacture year
    U8  MFGWeek;               // manufacture week of the year
    U8  ATETestBit;            // set to 1 to signifies board passed the ATE test
    U32 SerialNum;             // Serial Number
    U32 reserved;              // reserved, must be zero
} EEPROM_BOARD_STD;

/*****************************************************************************
 * TX4000 - Board Specific
 *****************************************************************************/
typedef struct
{
    U16 AssemblyLevel;     // Assembly part number/level
    U16 AssemblyRev;       // Hardware assembly level
                           // MSB is PCB artwork level,
                           // Rev D.9 is coded as 0409
                           // Rev A.3 is coded as 0103
    U16 AssemblyYear;      // Assembly Year
    U8  AssemblyWeek;      // Assembly week
    U8  reserved;          // Reserved - must be zero
    U8  FlashSize;         // Size of Flash in MB
    U8  NumEthernet;       // Number of ethernets
    U16 CPUSpeed;          // CPU Speed in MHZ
    U8  NumTrunks;         // Number of T1/E1 Trunks
    U8  NumSS7Links;       // Number of SS7 Links supported
    U16 SDRAMSize;         // Size of SDRAM in MB
    U16 SRAMSize;          // Size of SRAM in MB
    U8  EthAddr1[6];       // NIC 1 Ethernet Address
    U8  EthAddr2[6];       // NIC 2 Ethernet Address
    U8  EthAddr3[6];       // NIC 3 Ethernet Address
    U8  EthAddr4[6];       // NIC 4 Ethernet Address
    U16 CPU2Speed;         // Speed of CPU #2 (8260)
    U16 SDRAM2Size;        // Size of SDRAM for CPU #2 in MB
    U8  SRAM2Size;         // Size of SRAM for CPU #2 in chunks of 64KB
    U8  Flash2Size;        // Size of Flash for CPU #2 in MB
    U8  L1ClockDiv;        // L1 Clock Divider
    U8  BusType;           // 0=PCI, 1=CPCI
#define EEPROM_TX4000_BUSTYPE_PCI   0
#define EEPROM_TX4000_BUSTYPE_CPCI  1

    U8  reserved2[14];     // Bring record size to 64 bytes (192 more bytes follow)
} EEPROM_TX4000_SPEC;

#define EEPROM_TX4000_SPEC_EXPAND   192     /* more area available beyond EEPROM_TX4000_SPEC */

/*****************************************************************************
 * TX4000 EEPROM Information
 *****************************************************************************/
typedef struct
{
   EEPROM_BOARD_STD     nmsStandard;    /* NMS EEProm Standard info */
   U32                  avail1[4];
   EEPROM_TX4000_SPEC   tx4_specific;   /* TX4000 Specific */
   U32                  avail2[4];
} TX4000_EEPROM;

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

#endif  /* _COSEPROM_H */
