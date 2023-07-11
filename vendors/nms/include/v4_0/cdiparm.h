/* **********************************************************************
 *
 * Auto Generated Source Module.
 * Manual edits will be lost when file is regenerated!!
 * UDP Compiler ( Version 1.1 )
 *
 ************************************************************************/


#ifndef CDIPARMPARM_DEFINED
#define CDIPARMPARM_DEFINED

#include "ctadef.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define	CDI_SVCID	0x1F

#define	CDI_TONE_PARMID	0x1F0001

typedef struct
{
	DWORD	size;
	DWORD	freq1;
	DWORD	freq2;
	INT32	ampl1;
	INT32	ampl2;
	DWORD	ontime;
	DWORD	offtime;
	DWORD	ontime2;
	DWORD	offtime2;
	INT32	iterations;
}	CDI_TONE_PARMS;

#define	CDI_RING_PARMID	0x1F0002

typedef struct
{
	DWORD	size;
	DWORD	cadence_type;
}	CDI_RING_PARMS;

#define	CDI_SIGNALDETECTOR_PARMID	0x1F0003

typedef struct
{
	DWORD	size;
	DWORD	timeon;
	DWORD	timeoff;
	DWORD	min_flash_hook;
	DWORD	max_flash_hook;
}	CDI_SIGNALDETECTOR_PARMS;

#define	CDI_DTMFDETECTOR_PARMID	0x1F0004

typedef struct
{
	DWORD	size;
	DWORD	onqualtime;
	DWORD	offqualtime;
	DWORD	DTMF_mode;
}	CDI_DTMFDETECTOR_PARMS;

#define	CDI_GLOBAL_PARMID	0x1F0005

typedef struct
{
	DWORD	size;
	DWORD	EnhancedMode;
}	CDI_GLOBAL_PARMS;

extern const CTAPARM_DESC * const _cdiParmDescTable[];


#ifdef __cplusplus
}
#endif

#endif
