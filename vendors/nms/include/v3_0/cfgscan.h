/* cfgscan.h
 *
 * Constants, data types, function prototypes needed to interface
 * with the config file scanner utility.
 */

#ifndef _CFGSCAN_H_
#define _CFGSCAN_H_

#include "ss7type.h"

/* data types that can be converted by the scanner */
#define CFGT_INT        0               /* long (32 bits) integer */
#define CFGT_INTPAIR    1               /* pair of long integers */
#define CFGT_STRING     2               /* null terminated string */
#define CFGT_PC         3               /* SS7 point code (ULONG) */
#define CFGT_BOOL       4               /* BOOLEAN (0 or 1) */
#define CFGT_PORT       5               /* Port type + number */
#define CFGT_PCPRI      6               /* pointcode, priority pair */
#define CFGT_LINK       7               /* Either Port type + number or just number */

#define NEW_LINK_TYPE   0x00FF0000      /* Or'd with link number if new link type specified */

/* Max length of string types - caller's buffer must be at least this long */
#define CFGT_MAXSTR     80

/* set this to 1 in calling program for lots of debugging output */
extern int CDebug;

/* current setting for point code display format, as read from the current
 * config file at file open/initialization time
 */
extern U8 CfgPcDispFmt;

/* Port type definitions */
#define PORT_TYPE_SERIAL        0       /* Must be 0 for kernel */
#define PORT_TYPE_REMOTE        1
#define PORT_TYPE_TDM           4       /* Must be 4 for kernel */

/* function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

long getcfgval( char *pKeywd, int vType, void *pValue, long from );
int initcfg( char *cfgfile );
void endcfg( void );

/* useful routines for formatting and scanning point codes; both of
 * these can be called by any application without first calling initcfg().
 */
char *CfgFmtPc( U32 pc, U8 pcLen, U8 pcDispFmt );
short CfgScanPc( char *pStr, U32 *pPc, U8 pcDispFmt );

#ifdef __cplusplus
}
#endif

#endif
