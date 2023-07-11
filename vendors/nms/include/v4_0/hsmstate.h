/*****************************************************************************
*                                  HSMState.h
*
*  This header file describes HS Manager states
*
*
* Copyright (c) 1998, 1999  NMS Communications Corp.  All rights reserved.
*****************************************************************************/

#ifndef	__HSMSTATE_H__
#define __HSMSTATE_H__

/*/////////////////////////////////////////////////////////////////*/
/* HS Manager states */
typedef enum {

	/* states related to hardware level */
	HSMS_P0 = 0, /* no board in this slot */
	HSMS_S0,     /* board is present, not configured */

	/* states related to system level */
	HSMS_S1,     /* board is configured */
	HSMS_S1I,    /* device instance is created (on insertion) */
	HSMS_S1B,    /* wait for preparing board (boot, download) (on insertion) */
	HSMS_S1F,    /* failed to start device */
	HSMS_S1BF,   /* failed to prepare board */

	/* states related to user level */
	HSMS_S2,     /* board can be used by application */
	HSMS_S2R,    /* Extract pending (on extraction)  */
	HSMS_S1U,    /* wait for unpreparing board (close handles to driver 
                  *                             on extraction) 
                  */
	HSMS_NO      /* no slot */
} HSM_STATE;

#endif	/* __HSMSTATE_H__ */

