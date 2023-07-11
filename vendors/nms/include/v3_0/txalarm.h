/******************************************************************
 **
 **			   PROPRIETARY NOTICE
 **
 **			Copyright (c) 1995,1996
 **			    By TEKnique, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the 
 **  express written permission of TEKnique, Inc.
 **
 *****************************************************************/
#ifndef _TXALARM_H_
#define _TXALARM_H_

#define DEFAULTALARMCHAN	12
#define ANODENSIZE		8
#define ASTRSIZE		80
#define ALARM_MTU		1514

#pragma pack(1)

typedef struct txtimestamp {
	unsigned short	year;
	unsigned char	month;
	unsigned char	day;
	unsigned char	hour;
	unsigned char	min;
	unsigned char	sec;
	signed   char	zone;
	unsigned short	msec;
} txtimestamp_t;

typedef struct txalarm_hdr {
	txtimestamp_t	datetime;
	char		nodename[ANODENSIZE];
	unsigned short	nodenlen;
	unsigned char	board;
	unsigned char	hopsleft;
	unsigned short	datalen;
} txalarm_hdr_t;

typedef struct txalarm_buf {
	unsigned short	infalarm;
	unsigned short	infalms1;
	unsigned short	infalms2;
	unsigned long	infalmn0;
	unsigned long	infalmn1;
	unsigned long	infalmn2;
	char		infalmstr[ASTRSIZE];
} txalarm_buf_t;

typedef struct txalarm {
	txalarm_hdr_t	hdr;
	txalarm_buf_t	data;
} txalarm_t;

#pragma pack()

#endif /* _TXALARM_H_ */
