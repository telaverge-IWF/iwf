/*****************************************************************************
*                                  hsfstate.h
*
*  This header file describes states of Hot Swap driver
*
*
* Copyright (c) 1997, 1998  NMS Communications Corp.  All rights reserved.
*****************************************************************************/

#ifndef __HSFSTATE_H__
#define __HSFSTATE_H__

#define HSF_NO_DEV              0x00    /* Device is not present        */
#define HSF_EXIST               0x01    /* Device instance is created   */
#define HSF_EXIST_AND_PREPARED  0x02    /* Device instance is created,  */
                                        /* board is prepared            */
#define HSF_NOT_EXIST           0x04    /* Device instance is removed   */
#define HSF_CHANNELS_DISABLED   0x08    /* Opening new channels are disabled */
#define HSF_CHANNELS_CLOSED     0x10    /* All channels are closed.     */
                                        /* This bit is valid only when  */
                                        /* HSF_CHANNELS_DISABLED is set */


#endif  /* __HSFSTATE_H__ */

