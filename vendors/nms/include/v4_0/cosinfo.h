/*****************************************************************************
 *
 * cosinfo.h - CPKOS System Information Definitions
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2002
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _COSINFO_H
#define _COSINFO_H

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
#include <coseprom.h>

/* ----- well-known System Information name ----- */
#define NOBJ_MEMORY_SYSINFO     "System Information"

/* ----- System Utilization definitions ----- */
#define SYSUTIL_BUCKETS     16  /* number of utilization buckets maintained */
#define SYSUTIL_BUCKET_WRAP 0xF /* mask to apply when handling CPU bucket wrap */

/*****************************************************************************
 * System Utilization block - area used to compute CPU utilization
 *****************************************************************************/
typedef struct __sysutil
{
    U32         idle_count;     /* counter maintained by $idle task */
    U32         idle_peak;      /* peak value that idle_count has ever reached */
    U32         last_bucket;    /* last cpu_bucket that was updated */
    U32         cpu_bucket[SYSUTIL_BUCKETS];    /* per second history of idle_count */

    U32         avail[5];       /* room for future expansion */
} SYSUTIL;

/*****************************************************************************
 * System Time block - time of day / time passage handling area
 *****************************************************************************/
typedef struct __systimestamp
{
    U32  year;
    U32  month;
    U32  day;
    U32  hour;
    U32  min;
    U32  sec;
    S32  zone;
    U32  msec;
} SYSTIMESTAMP;

typedef struct __systime
{
    U32                 boot_msecs;     /* number of milliseconds since boot */
    U32                 epoch_secs;     /* number of seconds since epoch */
    U32                 bmsec_epoch;    /* number of msecs since boot when epoch secs were recorded */
    SYSTIMESTAMP        systime;        /* system time in timestamp format */

    U32                 avail[5];       /* room for future expansion */
} SYSTIME;

/*****************************************************************************
 * System CPU-Specific block - area defining CPU-specific OS features
 *****************************************************************************/
typedef struct __syscpu
{
    U32         idle_delay;     /* delay to approximate 1/2 sec of counting */
    U32         tclk_speed;     /* TCLK value, System Specific */
#define  TCLK_125MHZ    125000000
#define  TCLK_133MHZ    133000000

    U32         extranious_int; /* Count of extranious Interrupts */

    U32         avail[5];       /* room for future expansion */
} SYSCPU;

/*****************************************************************************
 * System Address block for Ethernets
 *****************************************************************************/
typedef struct __sysaddreth
{
    U32         eth_restype;    /* lower resource type */
    U8          eth_addr[6];    /* NIC Ethernet Address */
    U8          eth_avail[2];

} SYSADDRETH;
#define SYSADDRETH_MAX      4   /* max number of Ethernet interfaces available */

/*****************************************************************************
 * System General block - area defining general information
 *****************************************************************************/
typedef struct __sysgeneral
{
    U32         cpnum;          /* CP number */
    U32         sys_id;
#define TX_SYSID            0x5458L                 /* 'TX'   - TX series */
#define TX_SYSID_MASK       0xFFFFFF00              /* mask of all boards in same family */

#define TX3220_SYSID        (TX_SYSID<<16|0x3342)   /* 'TX3B' - TX 3220 system */

#define TX4_SYSID           (TX_SYSID<<16|0x3400)   /* 'TX4x' - TX 4000 series */
#define TX4000_SYSID        (TX4_SYSID|0x30)        /* 'TX40' - TX 4000 system */
#define TX4000C_SYSID       (TX4_SYSID|0x31)        /* 'TX41' - TX 4000C system */
#define TX4000_20_SYSID     (TX4_SYSID|0x32)        /* 'TX42' - TX 4000/20 system */
#define TX4000_20C_SYSID    (TX4_SYSID|0x33)        /* 'TX43' - TX 4000/20C system */

    U32         serial_num;     /* Board serial number */
    U32         sdram_size;     /* Size of SDRAM in megabytes */
    U32         num_ss7_links;  /* Number of SS7 Links */
    U32         eth_count;      /* number of ethernet interfaces on board */
    SYSADDRETH  eth[SYSADDRETH_MAX];    /* addressing info for each Ethernet */

    U32         avail[6];       /* room for future expansion */
} SYSGENERAL;

/*****************************************************************************
 * System Flash block - area providing flash information
 *****************************************************************************/
#define TX4_IPL_SIZE 0x8000
typedef struct __sysflash
{
    U32     type;           /* Flash Type */
    U32     algorithm;      /* AMD or Intel Programming algorithms */
    U32     size;           /* flash size in KB */
    U32     base_addr;      /* flash base address */
    U32     symtab_addr;    /* Address of Kernel Symbol Table in flash */
    U32     symsize;        /* Size of Kernel Symbol Table */

    U32     avail[8];       /* room for future expansion */
} SYSFLASH;

/*****************************************************************************
 * System EEPROM block - area providing EEprom information
 *****************************************************************************/
typedef struct __syseeprom
{
    union
    {
        TX4000_EEPROM   tx4000; /* EEPROM structure used by TX 4000 board family */

        U8              max_eeprom[192];    /* max space occupied by board EEPROM information */
    } txtype;

} SYSEEPROM;

/*****************************************************************************
 * System Kernel block - area providing kernel information
 *****************************************************************************/
typedef struct __syskernel
{
    U16     kernel_ver;         /* kernel version */
    U16     kernel_rev;         /* kernel revision */

    U32     avail[3];           /* room for future expansion */
} SYSKERNEL;

/*****************************************************************************
 * System Layout block - area providing hardware layout information
 *****************************************************************************/
typedef struct __syslayout
{
    U32     pci;                /* board PCI type information */
#define TXLO_PCI_IFACE  (1<<0)  /* set = board contains PCI interface */
#define TXLO_PCI_CPCI   (1<<1)  /* set = board contains CompactPCI interface */
#define TXLO_PCI_CPCI_REARIO   (1<<2)  /* set = REARIO Is Good */

    U32     networks;           /* number of network (T1/E1) interfaces */
    U32     ls_framers;         /* mask indicating local streams that map to framers */

    U32     avail[5];           /* room for future expansion */
} SYSLAYOUT;

/*****************************************************************************
 * System Clocking - area providing TDM clocking information
 *****************************************************************************/
#define SYSINFO_MAX_NETWORK  16  /* maximum network connection */

/* ----- clocking control signals ----- */
#define SYSCLK_CT_C8_A      0   /* H.100|H.110 A clocks */
#define SYSCLK_CT_C8_B      1   /* H.100|H.110 B clocks */
#define SYSCLK_CT_NETREF_1  2   /* H.100|H.110 NETREF[_1] signal */
#define SYSCLK_CT_NETREF_2  3   /* H.110 NETREF_2 signal */
#define SYSCLK_COMPAT       4   /* H.100|H.110 compatibility clocks */
#define SYSCLK_NETWORK      4   /* base... add network # (1..n) */
#define SYSCLK_MAX          (SYSCLK_NETWORK+SYSINFO_MAX_NETWORK)

/*--------------------------------------------------------------------------
 * Clocking Signal Information
 *--------------------------------------------------------------------------*/
typedef struct __sysclk_sig
{
    U32     sig_dir;    /* clock signal direction */
#define SYSCLK_DIR_NONE     0   /* direction not provided | not configured */
#define SYSCLK_DIR_INPUT    1   /* input signal */
#define SYSCLK_DIR_OUTPUT   2   /* output signal */

    U32     speed;      /* speed of clock [i.e. clock frequency (in Hz)] */
#define SYSCLK_FREQ_8KHZ        8000    /*      8 KHz */
#define SYSCLK_FREQ_1_5MHZ   1544000    /*  1.544 MHz */
#define SYSCLK_FREQ_2MHZ     2048000    /*  2.048 MHz */
#define SYSCLK_FREQ_4MHZ     4096000    /*  4.096 MHz */
#define SYSCLK_FREQ_8MHZ     8192000    /*  8.192 MHz */
#define SYSCLK_FREQ_16MHZ   16384000    /* 16.384 MHz */
#define SYSCLK_FREQ_64MHZ   65536000    /* 65.536 MHz */

    U32     avail[6];           /* room for future expansion */
} SYSCLK_SIG;

typedef struct __sysclock
{
    U32         intern_osc;             /* internal oscillator frequency (in Hz) */
    U32         netref_freq;            /* frequency (in Hz) of NETREF signal(s) [when known] */
    U32         main_fsc;               /* network # providing 8 KHz frame sync */
    U32         netref_fsc;             /* network # providing 8 KHz frame sync */

    SYSCLK_SIG  signal[SYSCLK_MAX+1];   /* information for all clocking signals */

    U32         avail[4];               /* room for future expansion */
} SYSCLOCK;

/*****************************************************************************
 * System Information block - TX board system level information
 *
 * locate using nobj_find( NOBJ_MEMORY, NOBJ_MEMORY_SYSINFO );
 *****************************************************************************/
typedef struct __sysinfo
{
    U32         sysinfo_id;
#define SYSINFO_ID  0x53595349L /* 'SYSI' */

    SYSUTIL     util;           /* system utilization area */
    SYSTIME     time;           /* time handling area */
    SYSCPU      cpu;            /* CPU-specific area */
    SYSGENERAL  general;        /* system General area */
    SYSKERNEL   kernel;         /* kernel information area */
    SYSFLASH    flash;          /* flash information area */
    SYSEEPROM   eeprom;         /* Interesting EEPROM info */
    SYSLAYOUT   layout;         /* hardware layout info */
    SYSCLOCK    clock;          /* TDM clocking information */

    U32         avail[8];       /* room for future expansion */
} SYSINFO;

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

#endif  /* _COSINFO_H */
