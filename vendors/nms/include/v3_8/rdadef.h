/*****************************************************************************
  NAME:  rdadef.h
  
  PURPOSE:

      Provides the headers of API calls for the Repeat Dial Attempt limitations 
      embedded inside NCC.
  ****************************************************************************/

#ifndef RDADEF_INCLUDED
#define RDADEF_INCLUDED

#include "tsidef.h"

/*---------------------------------------------------------------------
 *    System Includes
 *-------------------------------------------------------------------*/
#ifndef NMSTYPES_INCLUDED
  #include <nmstypes.h>
#endif


/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/*---------------------------------------------------------------------
 *    Constants
 *-------------------------------------------------------------------*/

#define RDA_LIBRARY_NAME "rda"

/*---------------------------------------------------------------------
 *    RDA implementation API function prototypes.
 *-------------------------------------------------------------------*/

DWORD rdaAttach( void *extparms );
DWORD rdaClearLog( char *address, void *extparms );
DWORD rdaDetach( void *extparms );
DWORD rdaLoadLibrary( void *extparms );
DWORD rdaLogCall( char *address, void *extparms );
DWORD rdaRequestCall( char *address, void *extparms );
DWORD rdaUnloadLibrary( void *extparms );


#ifdef __cplusplus
}
#endif


#endif /* RDADEF_INCLUDED */


