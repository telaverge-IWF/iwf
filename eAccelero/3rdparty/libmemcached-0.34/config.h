/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Enable big endian byteorder */
/* #undef BYTEORDER_BIG_ENDIAN */

/* Enable little endian byteorder */
#define BYTEORDER_LITTLE_ENDIAN 1

/* Define to 1 if you have the <assert.h> header file. */
#define HAVE_ASSERT_H 1

/* Define to 1 if you have the <boost/shared_ptr.hpp> header file. */
#define HAVE_BOOST_SHARED_PTR_HPP 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Enables DTRACE Support */
/* #undef HAVE_DTRACE */

/* Enables hsieh hashing support */
/* #undef HAVE_HSIEH_HASH */

/* Have ntohll */
/* #undef HAVE_HTONLL */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `c_p' library (-lc_p). */
/* #undef HAVE_LIBC_P */

/* Define if you have the innodb library. */
/* #undef HAVE_LIBINNODB */

/* Enables libmemcachedutil Support */
#define HAVE_LIBMEMCACHEDUTIL 1

/* Define to 1 if you have the `mtmalloc' library (-lmtmalloc). */
/* #undef HAVE_LIBMTMALLOC */

/* Define to 1 if you have the `tcmalloc' library (-ltcmalloc). */
/* #undef HAVE_LIBTCMALLOC */

/* Define to 1 if you have the `tcmalloc-minimal' library
   (-ltcmalloc-minimal). */
/* #undef HAVE_LIBTCMALLOC_MINIMAL */

/* Define to 1 if you have the `umem' library (-lumem). */
/* #undef HAVE_LIBUMEM */

/* Define to 1 if your system has a GNU libc compatible `malloc' function, and
   to 0 otherwise. */
#define HAVE_MALLOC 1

/* Define to 1 if you have the <memory> header file. */
#define HAVE_MEMORY 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Define to 1 if you have a working SO_RCVTIMEO */
#define HAVE_RCVTIMEO 1

/* Define to 1 if your system has a GNU libc compatible `realloc' function,
   and to 0 otherwise. */
#define HAVE_REALLOC 1

/* Define to 1 if you have a working SO_SNDTIMEO */
#define HAVE_SNDTIMEO 1

/* Define if g++ supports C++0x features. */
/* #undef HAVE_STDCXX_0X */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <tr1/memory> header file. */
#define HAVE_TR1_MEMORY 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 or 0, depending whether the compiler supports simple visibility
   declarations. */
#define HAVE_VISIBILITY 1

/* CPU of Build System */
#define HOST_CPU "x86_64"

/* OS of Build System */
#define HOST_OS "linux-gnu"

/* Vendor of Build System */
#define HOST_VENDOR "unknown"

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Name of the memcached binary used in make test */
#define MEMCACHED_BINARY "/usr/bin/memcached"

/* Define to 1 if assertions should be disabled. */
/* #undef NDEBUG */

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "libmemcached"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://tangent.org/552/libmemcached.html"

/* Define to the full name of this package. */
#define PACKAGE_NAME "libmemcached"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "libmemcached 0.34"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "libmemcached"

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.34"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* The namespace in which SHARED_PTR can be found */
#define SHARED_PTR_NAMESPACE std::tr1

/* Define if ISO C++ 1998 header files are present. */
#define STDCXX_98_HEADERS /**/

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* CPU of Target System */
#define TARGET_CPU "x86_64"

/* OS of Target System */
#define TARGET_OS "linux-gnu"

/* Whether we are building for FreeBSD */
/* #undef TARGET_OS_FREEBSD */

/* Whether we build for Linux */
#define TARGET_OS_LINUX 1

/* Whether we build for OSX */
/* #undef TARGET_OS_OSX */

/* Whether we are building for Solaris */
/* #undef TARGET_OS_SOLARIS */

/* Vendor of Target System */
#define TARGET_VENDOR "unknown"

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "0.34"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Cause Sun Studio to not be quite so strict with standards conflicts */
/* #undef _STLP_NO_NEW_C_HEADERS */

/* Workaround for bug in FreeBSD headers */
/* #undef __APPLE_CC__ */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif

/* Define to rpl_malloc if the replacement function should be used. */
/* #undef malloc */

/* Define to rpl_realloc if the replacement function should be used. */
/* #undef realloc */

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#define restrict __restrict
/* Work around a bug in Sun C++: it does not support _Restrict, even
   though the corresponding Sun C compiler does, which causes
   "#define restrict _Restrict" in the previous line.  Perhaps some future
   version of Sun C++ will work with _Restrict; if so, it'll probably
   define __RESTRICT, just as Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to empty if the keyword `volatile' does not work. Warning: valid
   code using `volatile' can become incorrect without. Disable with care. */
/* #undef volatile */
