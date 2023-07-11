#ifndef HMAPI_INCLUDED
#define HMAPI_INCLUDED

#include "nmstypes.h"
#include "ctadef.h"
#include "ss7type.h"

#include "hmidef.h"

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
  HM Service API function prototypes.
  ---------------------------------------------------------------------------*/

DWORD NMSAPI hmiStatusReq  (CTAHD ctahd, HmStatsData *stats, U8 reset);
DWORD NMSAPI hmiReset      (CTAHD ctahd);
DWORD NMSAPI hmiShutdown   (CTAHD ctahd);
DWORD NMSAPI hmiStop       (CTAHD ctahd);
DWORD NMSAPI hmiStart      (CTAHD ctahd);
DWORD NMSAPI hmiPrimary    (CTAHD ctahd);
DWORD NMSAPI hmiBackup     (CTAHD ctahd);
DWORD NMSAPI hmiStandalone (CTAHD ctahd);
DWORD NMSAPI hmiLoadBoard  (CTAHD ctahd);
DWORD NMSAPI hmiHaltBoard  (CTAHD ctahd);

#ifdef __cplusplus
}
#endif

#endif

