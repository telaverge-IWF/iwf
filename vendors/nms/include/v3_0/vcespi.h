/*****************************************************************************
  NAME:  vcespi.h
  
  PURPOSE:

      This file contains macros and function prototypes that define the 
      SPI for the VCE sample service.

      Your service will be specified by the prefix 'vce' throughout all
      related template service source files.
  ****************************************************************************/

#ifndef VCESPI_INCLUDED
#define VCESPI_INCLUDED 


/* Standard CT Access include files. */
#include "nmstypes.h"
#include "ctadef.h"


/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
  VCE SPI Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed VCE service and clients of the VCE service. Clients can
      be another CT Access Service (which access VCE functionality
      via the VCE SPI).
    - Clients check this id value via CTAREQSVC_INFO structure
      passed with dispRegisterService in its service implementation
      of vceDefineService binding function.
    - SPI compatiblity level value should be incremented when the associated 
      source module changes in a non-backwards compatible way. Refer to the CT 
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define VCESPI_COMPATLEVEL                  0



/*-----------------------------------------------------------------------------
  Associated VCE Service SPI function prototypes.
    - For each API call, there is an associated SPI call which performs
      argument marshalling and invokes dispSendCommand() for processing.
    - Note that the only difference between the API signature and the SPI
      signature is the extra "source" argument.
    - Also note that if another service needed to call a this Service function,
      it would call the SPI function - NOT THE API FUNCTION!
  ---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
    ctahd:    Handle for CT Access context to start.
    arg1:     Some DWORD argument.  May be modified to any type of pass
              argument.
    arg2:     Some structure argument.  May be modified to any type of pass
              argument.
    source:   Service ID of calling service.  Either Application or Another
              CT Access compliant service.          
              

  Returns SUCCESS on successful execution, otherwise returns a CT Access
  or Service specific error code on failure.
  ---------------------------------------------------------------------------*/

/* SPI function for vceApi1 API. */
DWORD NMSAPI vceSpiOpenFile (CTAHD crhd,  const char *filename,
							 unsigned filetype, unsigned openmode,
							 unsigned encoding, VCEHD *pvh, WORD source);
DWORD NMSAPI vceSpiCreateFile(CTAHD crhd, const char *filename,
							  unsigned filetype, unsigned encoding,
							  const void *fileinfo, VCEHD *pvh, WORD source);
DWORD NMSAPI vceSpiClose (VCEHD vh, WORD source);
DWORD NMSAPI vceSpiAssignHandle (CTAHD crhd, int fileno, unsigned encoding,
								 VCEHD *pvh, WORD source);
DWORD NMSAPI vceSpiDefineMessages (VCEHD vh, const VCE_SEGMENT *segments,
								   unsigned msgcount, WORD source);
DWORD NMSAPI vceSpiOpenMemory (CTAHD crhd, BYTE *address, unsigned bytes,
							   unsigned encoding, VCEHD *pvh, WORD source);
DWORD NMSAPI vceSpiStop (CTAHD crhd, WORD source);
DWORD NMSAPI vceSpiPlay (CTAHD crhd, unsigned maxtime,
						 const VCE_PLAY_PARMS *parms, WORD source);
DWORD NMSAPI vceSpiPlayMessage (VCEHD vh, unsigned message,
								const VCE_PLAY_PARMS *parms, WORD source);
DWORD NMSAPI vceSpiPlayList (VCEHD vh, const unsigned *msglist, unsigned count,
							 const VCE_PLAY_PARMS *parms, WORD source);
DWORD NMSAPI vceSpiSetPlayGain  (CTAHD crhd, int db, WORD source);
DWORD NMSAPI vceSpiSetPlaySpeed   (CTAHD crhd, unsigned speed, WORD source);
DWORD NMSAPI vceSpiRecord (CTAHD crhd, unsigned maxtime, unsigned insertmode,
						   const VCE_RECORD_PARMS *parms, WORD source);
DWORD NMSAPI vceSpiRecordMessage (VCEHD vh, unsigned message, unsigned maxtime,
								  const VCE_RECORD_PARMS *parms, WORD source);
DWORD NMSAPI vceSpiGetCurrentSize (CTAHD crhd, unsigned *rsize, WORD source);
DWORD NMSAPI vceSpiGetCurrentList (CTAHD crhd, VCE_MESSAGE *msglist,
								   unsigned maxcount, unsigned *pactualcount,
								   WORD source);
DWORD NMSAPI vceSpiGetEncodingInfo  (CTAHD crhd, unsigned encoding,
									 unsigned *framesize, unsigned *frametime,
									 WORD source);
DWORD NMSAPI vceSpiGetHighMessageNumber (VCEHD vh, unsigned *message,
										 WORD source);
DWORD NMSAPI vceSpiGetMessageSize (VCEHD vh, unsigned message, unsigned *size,
								   WORD source);
DWORD NMSAPI vceSpiGetOpenInfo (VCEHD vh, VCE_OPEN_INFO *info,
								unsigned usersize, WORD source);
DWORD NMSAPI vceSpiGetContextInfo (CTAHD crhd, VCE_CONTEXT_INFO *info,
								   unsigned size, WORD source);
DWORD NMSAPI vceSpiGetUniqueMessageNumber (VCEHD vh, unsigned *message,
										   WORD source);
DWORD NMSAPI vceSpiSetPosition (CTAHD crhd, int milliseconds,
								unsigned seekmode, unsigned *position,
								WORD source);
DWORD NMSAPI vceSpiSetCurrentMessage (VCEHD vh, unsigned message, WORD source);
DWORD NMSAPI vceSpiSetCurrentList (CTAHD crhd, VCE_MESSAGE msglist[],
								   unsigned count, WORD source);
DWORD NMSAPI vceSpiCopyMessage (VCEHD srcvh, unsigned  srcmsg, VCEHD destvh,
								unsigned  destmsg, WORD source);
DWORD NMSAPI vceSpiConvertMessage (VCEHD srcvh, unsigned  srcmsg, VCEHD destvh,
								   unsigned destmsg, int gain, WORD source);
DWORD NMSAPI vceSpiEraseMessage (VCEHD vh, unsigned  message, WORD source);
DWORD NMSAPI vceSpiErase (CTAHD crhd, unsigned msecs, unsigned *actualms,
						  WORD source);
DWORD NMSAPI vceSpiRead (CTAHD crhd, BYTE *buffer, unsigned bytes,
						 unsigned *bytesread, WORD source);
DWORD NMSAPI vceSpiWrite (CTAHD crhd, const BYTE *buffer, unsigned bytes,
						  unsigned mode, unsigned *byteswritten, WORD source);
DWORD NMSAPI vceSpiSetWaveInfo (CTAHD crhd, unsigned encoding,
								VCE_WAVE_INFO *info, WORD source);
DWORD NMSAPI vceSpiGetWaveInfo (CTAHD crhd, unsigned encoding,
								VCE_WAVE_INFO *info, unsigned infosize,
								WORD source);
DWORD NMSAPI vceSpiLoadPromptRules (CTAHD crhd, char *name,
									VCEPROMPTHD *prompthandle, WORD source);
DWORD NMSAPI vceSpiUnloadPromptRules (VCEPROMPTHD prompthandle, WORD source);
DWORD NMSAPI vceSpiBuildPromptList(VCEPROMPTHD prompthandle, unsigned method,
								   char *text, unsigned *list,
								   unsigned maxcount, unsigned *actualcount,
								   WORD source);
DWORD NMSAPI vceSpiCopyMessageText (VCEHD srcvh, unsigned  srcmsg,
									VCEHD destvh, unsigned  destmsg,
									WORD source);
DWORD NMSAPI vceSpiReadMessageText (VCEHD vh, unsigned message, void *buffer,
									unsigned bytes, unsigned *bytesread,
									WORD source);
DWORD NMSAPI vceSpiWriteMessageText (VCEHD vh, unsigned message, void *buffer,
									 unsigned bytes, WORD source);

                         

#ifdef __cplusplus
}
#endif


#endif /* VCESPI_INCLUDED */
