/********************************************************************
* FILENAME:     ipv6util.h
*
* DESCRIPTION:  Contains prototypes for IPv6 related utuility
*               functions
*
* Copyright 2002 by NMS Communications.  All rights reserved.
********************************************************************/

#ifndef IPv6UTIL_INCLUDED
#define IPV6UTIL_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IPV6ADDR
typedef union {
        unsigned char byByte[16];
        unsigned short byWord[8];
        unsigned int byLong[4];
} IPV6Addr;
#define IPV6ADDR
#endif

/* Redefine standard variables in order to allow to compile the application */
/* on the host platform which doesn't support IPv6.                         */
#define NMS_INET6_ADDRSTRLEN 46
#define NMS_AF_INET6         23

#define NetSwab32Unconditional(x)\
        ((x << 24) | (x << 8 & 0x00ff0000) |\
         (x >> 24 & 0x000000ff) | (x >> 8 & 0x0000ff00))

const char * nms_inet_ntop( int af, const void *src,
                           char *dst, size_t size);
int nms_inet_pton( int af, const char * src, void *dst);

#ifdef __cplusplus
}
#endif

#endif //IPV6UTIL_INCLUDED
