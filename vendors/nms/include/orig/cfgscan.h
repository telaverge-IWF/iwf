/* cfgscan.h
 *
 * Constants, data types, function prototypes needed to interface
 * with the config file scanner utility.
 */

#ifndef _CFGSCAN_H_
#define _CFGSCAN_H_

/* data types that can be converted by the scanner */
#define CFGT_INT        0               /* long (32 bits) integer */
#define CFGT_INTPAIR    1               /* pair of long integers */
#define CFGT_STRING     2               /* null terminated string */
#define CFGT_PC         3               /* SS7 point code (ULONG) */
#define CFGT_BOOL       4               /* BOOLEAN (0 or 1) */
#define CFGT_PORT       5               /* Port type + number */
#define CFGT_PCPRI      6               /* pointcode, priority pair */

/* Max length of string types - caller's buffer must be at least this long */
#define CFGT_MAXSTR     80

/* set this to 1 in calling program for lots of debugging output */
extern int CDebug;

/* function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

long getcfgval( char *pKeywd, int vType, void *pValue, long from );
int initcfg( char *cfgfile );
void endcfg( void );

#ifdef __cplusplus
}
#endif

#endif
