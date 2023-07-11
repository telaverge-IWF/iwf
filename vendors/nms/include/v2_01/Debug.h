/*****************************************************************************
******************************************************************************
**
**   debug.h
**      miscellaneous macros for debugging the api, use at will
**
**   Revision History:
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: Debug.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:46  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:06  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:51  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
* REV   DATE           WHO       Begin PR7.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
* REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:35  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:10:57  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2000/06/21 19:19:31  hxing
* REV   DATE           WHO       Add NMS vendor lib for version 2.01
* REV   DATE           WHO $NoKeywords: $
* 
* 5     3/11/98 5:24p Build
* Build 13
* 
* 1     8/14/97 4:43p Vince
* miscellaneous macros for debugging the api
*
-----------------------------------------------------------------------------
******************************************************************************
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                    by Natural MicroSystems, Inc.                     **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/
#ifndef DEBUG_H
#define DEBUG_H

#  ifndef DEBUGOFF
#    define dbg_show(x,c) fprintf(stderr, #x " = %" #c "\n", (x))
#  else
#    define dbg_show(x,c)
#  endif
#endif
