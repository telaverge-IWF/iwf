/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */
/* $Id: config_solaris.h,v 9.1 2007/01/10 11:14:58 yranade Exp $ */

#ifndef _CONFIG_H
#define _CONFIG_H

/* Comments for config.h.in file */
/* Generated automatically from acconfig.h by autoheader. */
/* Please make your changes there */


/* Define if you have the strftime function.  */
/* #undef HAVE_STRFTIME */

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

/* Define if your processor stores words with the most significant
   byte first (like Motorola and SPARC, unlike Intel and VAX).  */
#define WORDS_BIGENDIAN 1

/* Define if your system's struct sockaddr_un has a sun_len member */
/* #undef HAVE_SUN_LEN_IN_SOCKADDR_UN */

/* Define if your system defines sys_errlist[] */
/* #undef HAVE_SYS_ERRLIST */

/* Define if your system defines sys_nerr */
/* #undef HAVE_SYS_NERR */

/* Define if your snprintf is busted */
/* #undef BROKEN_SNPRINTF */

/* struct timeval */
#define HAVE_STRUCT_TIMEVAL 1

/* Define if libc defines __progname */
/* #undef HAVE___PROGNAME */

/* Data types */
/* #undef ARCH_PC_WIN95 */
/* #undef ARCH_SCATTER_NONE */
/* #undef ARCH_SCATTER_CONTROL */
#define ARCH_SCATTER_ACCRIGHTS 1
/* #undef HAVE_SOCKOPT_LEN_T */
#define HAVE_STRUCT_TIMEZONE 1
#define HAVE_U_INT 1
#define HAVE_INTXX_T 1
/* #undef HAVE_U_INTXX_T */
#define HAVE_UINTXX_T 1
#define HAVE_INT64_T 1
/* #undef HAVE_U_INT64_T */
#define HAVE_SOCKLEN_T 1
#define HAVE_SIZE_T 1
#define HAVE_SSIZE_T 1
#define HAVE_CLOCK_T 1
/* #undef HAVE_MODE_T */
#define HAVE_PID_T 1
#define HAVE_SA_FAMILY_T 1
#define HAVE_STRUCT_SOCKADDR_STORAGE 1
#define HAVE_STRUCT_ADDRINFO 1
#define HAVE_STRUCT_IN6_ADDR 1
#define HAVE_STRUCT_SOCKADDR_IN6 1

/* Fields in struct sockaddr_storage */
#define HAVE_SS_FAMILY_IN_SS 1
/* #undef HAVE___SS_FAMILY_IN_SS */

/* Specify location of spread.pid */
#define _PATH_SPREAD_PIDDIR "/var/run"

/* Specify location of spread.conf and other configuration files */
#define SPREAD_ETCDIR "/usr/local/etc"

/* The number of bytes in a char.  */
#define SIZEOF_CHAR 0

/* The number of bytes in a int.  */
#define SIZEOF_INT 0

/* The number of bytes in a long int.  */
#define SIZEOF_LONG_INT 0

/* The number of bytes in a long long int.  */
#define SIZEOF_LONG_LONG_INT 0

/* The number of bytes in a short int.  */
#define SIZEOF_SHORT_INT 0

/* Define if you have the bcopy function.  */
/* #undef HAVE_BCOPY */

/* Define if you have the gettimeofday function.  */
/* #undef HAVE_GETTIMEOFDAY */

/* Define if you have the inet_aton function.  */
/* #undef HAVE_INET_ATON */

/* Define if you have the inet_ntoa function.  */
/* #undef HAVE_INET_NTOA */

/* Define if you have the inet_ntop function.  */
/* #undef HAVE_INET_NTOP */

/* Define if you have the lrand48 function.  */
/* #undef HAVE_LRAND48 */

/* Define if you have the memmove function.  */
/* #undef HAVE_MEMMOVE */

/* Define if you have the setsid function.  */
/* #undef HAVE_SETSID */

/* Define if you have the snprintf function.  */
/* #undef HAVE_SNPRINTF */

/* Define if you have the strerror function.  */
/* #undef HAVE_STRERROR */

/* Define if you have the time function.  */
/* #undef HAVE_TIME */

/* Define if you have the <arpa/inet.h> header file.  */
#define HAVE_ARPA_INET_H 1

/* Define if you have the <assert.h> header file.  */
#define HAVE_ASSERT_H 1

/* Define if you have the <errno.h> header file.  */
#define HAVE_ERRNO_H 1

/* Define if you have the <grp.h> header file.  */
#define HAVE_GRP_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <netdb.h> header file.  */
#define HAVE_NETDB_H 1

/* Define if you have the <netinet/in.h> header file.  */
#define HAVE_NETINET_IN_H 1

/* Define if you have the <netinet/tcp.h> header file.  */
#define HAVE_NETINET_TCP_H 1

/* Define if you have the <process.h> header file.  */
/* #undef HAVE_PROCESS_H */

/* Define if you have the <pthread.h> header file.  */
#define HAVE_PTHREAD_H 1

/* Define if you have the <pwd.h> header file.  */
#define HAVE_PWD_H 1

/* Define if you have the <signal.h> header file.  */
#define HAVE_SIGNAL_H 1

/* Define if you have the <stdarg.h> header file.  */
#define HAVE_STDARG_H 1

/* Define if you have the <stdint.h> header file.  */
/* #undef HAVE_STDINT_H */

/* Define if you have the <stdio.h> header file.  */
#define HAVE_STDIO_H 1

/* Define if you have the <stdlib.h> header file.  */
#define HAVE_STDLIB_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <sys/filio.h> header file.  */
#define HAVE_SYS_FILIO_H 1

/* Define if you have the <sys/inttypes.h> header file.  */
#define HAVE_SYS_INTTYPES_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/param.h> header file.  */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/socket.h> header file.  */
#define HAVE_SYS_SOCKET_H 1

/* Define if you have the <sys/stat.h> header file.  */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/timeb.h> header file.  */
#define HAVE_SYS_TIMEB_H 1

/* Define if you have the <sys/types.h> header file.  */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <sys/uio.h> header file.  */
#define HAVE_SYS_UIO_H 1

/* Define if you have the <sys/un.h> header file.  */
#define HAVE_SYS_UN_H 1

/* Define if you have the <time.h> header file.  */
#define HAVE_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the <windows.h> header file.  */
/* #undef HAVE_WINDOWS_H */

/* Define if you have the <winsock.h> header file.  */
/* #undef HAVE_WINSOCK_H */

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the posix4 library (-lposix4).  */
/* #undef HAVE_LIBPOSIX4 */

/* Define if you have the pthread library (-lpthread).  */
/* #undef HAVE_LIBPTHREAD */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */

/* Define if you have the thread library (-lthread).  */
/* #undef HAVE_LIBTHREAD */

/* ******************* Shouldn't need to edit below this line ************** */

#include "defines.h"

#endif /* _CONFIG_H */
