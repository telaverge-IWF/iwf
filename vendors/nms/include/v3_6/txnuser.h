/******************************************************************************
*
*       txnuser.h - TXn000 Base User Interface File
*
* This file provides the base definitions used to interface to the
* TXn000 operating system KERNEL (or CPK).
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: txnuser.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:57  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:22  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:59  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.2  2002/05/16 15:53:32  hcho
* REV   DATE           WHO       Modifications for v3_6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1.2.1  2001/12/21 21:25:25  hcho
* REV   DATE           WHO       Initialize v3.6 build.
* REV   DATE           WHO $NoKeywords: $
* 
* 5     4/14/:0 4:51p Raranas
* Merging PR333 to rel_5_0/Mainline.
* 
* 9     4/10/:0 2:42p Jrego
* gerenalized DEC native short/long handling [LITTLE ENDIAN] accesses
*
* 8     4/10/:0 2:29p Jrego
* Added macros that convert between generic host and little endian format
*
* 7     4/07/:0 3:02p Jrego
* NMSTX_HOST_BIGENDIAN (and resulting conversion macros) added
*
* 6     4/07/:0 1:45p Jrego
*
* 4     3/16/:0 12:35p Jrego
* Merging PR311 from rel_4_2 to rel_5_0/Mainline.
*
* 5     3/15/:0 11:35a Jrego
* using NMSTX_ALIGN_32 to control natural alignment
*
* 4     3/15/:0 11:22a Jrego
*
* 2     5/26/99 10:07a Jrego
* Migrating to new Core Group source control system
*
* 1     5/26/98 4:38p Jeffr
* Base TXn000 Interface definitions
*-----------------------------------------------------------------------------
******************************************************************************/

#ifndef TX_TXNUSER
#define TX_TXNUSER

/*===========================================================================
 * Base Variable Types
 *
 * The following base variable types are used to build all other structure
 * definitions used to access TXn000 APIs.
 *===========================================================================*/
#ifndef U32
#define U32 unsigned long
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef S32
#define S32 long
#endif

#ifndef S16
#define S16 short
#endif

#ifndef S8
#define S8 char
#endif

/*===========================================================================
 * Structure Alignment Control
 *
 * NMSTX_ALIGN_32 - structures should use the following alignment rules:
 *                  * shorts aligned to even 16-bit boundary
 *                  * longs aligned to even 32-bit boundary
 *                  * structures always begin on even 32-bit boundary
 *                    (structures padded to even 32-bit size to aid alignment)
 *
 *===========================================================================*/

#ifdef __sparc
#define NMSTX_ALIGN_32
#endif

/*===========================================================================
 * Short / Long Byte Ordering Control
 *
 * TX board is BIG ENDIAN (most significant byte stored in lowest byte address)
 *
 * HOSTS can be BIG ENDIAN or LITTLE ENDIAN
 *
 * NMSTX_HOST_BIGENDIAN - the host uses a BIG ENDIAN based processor
 *
 *===========================================================================*/

#ifdef __sparc
#define NMSTX_HOST_BIGENDIAN
#endif

/*****************************************************************************
 * The following definitions allow a short or long to be converted from
 * one type of processor's native storage format to another.
 *
 * NOTE:  The NMSTX_SWABLONG and NMSTX_SWABSHORT definitions should NOT be used
 *        directly.  Use the macros derived from these SWAB macros to ensure
 *        proper host processor independence.
 *****************************************************************************/

#define NMSTX_SWABLONG(longval) (\
(long) (\
   ( ( ((long)(longval)) & 0x000000ff) << 24) | \
   ( ( ((long)(longval)) & 0x0000ff00) << 8) | \
   ( ( ((long)(longval)) & 0x00ff0000) >> 8) | \
   ( ( ((long)(longval)) & 0xff000000) >> 24) \
       ) \
)

#define NMSTX_SWABSHORT(shortval) (\
(short) (\
   (( ((short)(shortval)) & 0x00ff) << 8) | ( (((short)(shortval)) & 0xff00) >> 8) \
        )\
)

/*****************************************************************************
 * The following definitions are derived from the platform control
 * definitions above (NMSTX_xxx).
 *
 * These macros allow developers to create host-independent code that can
 * be used to access TX interface structures regardless of the type of
 * platform that the code is executing on.
 *
 * NOTE:  Modifications / extensions to the following macros should be made
 *        with care.  These macros are used by applications, APIs, and drivers.
 *
 * Use CPTOH / HTOCP macros when converting shorts and longs used between
 * the host and tasks running on the TX board (or CP).
 *
 * Use LE2H / H2LE macros when accessing certain TX hardware interfaces
 * (such as the DEC 21554 PCI bridge) that use LITTLE ENDIAN storage format.
 * Use of LE2H / H2LE is usually restricted to driver level accesses.
 *
 *****************************************************************************/
#ifdef NMSTX_HOST_BIGENDIAN

/* ----- BIG ENDIAN host ----- */
#define NMSTX_CPTOH_S(x) ((short)(x))
#define NMSTX_CPTOH_L(x) ((long)(x))
#define NMSTX_HTOCP_S(x) ((short)(x))
#define NMSTX_HTOCP_L(x) ((long)(x))

#define NMSTX_LE2H_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_LE2H_L(x) NMSTX_SWABLONG(x)
#define NMSTX_H2LE_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_H2LE_L(x) NMSTX_SWABLONG(x)

#else

/* ----- LITTLE ENDIAN host ----- */

#define NMSTX_CPTOH_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_CPTOH_L(x) NMSTX_SWABLONG(x)
#define NMSTX_HTOCP_S(x) NMSTX_SWABSHORT(x)
#define NMSTX_HTOCP_L(x) NMSTX_SWABLONG(x)

#define NMSTX_LE2H_S(x) ((short)(x))
#define NMSTX_LE2H_L(x) ((long)(x))
#define NMSTX_H2LE_S(x) ((short)(x))
#define NMSTX_H2LE_L(x) ((long)(x))

#endif /* NMSTX_HOST_BIGENDIAN */

#endif /* TX_TXNUSER */
