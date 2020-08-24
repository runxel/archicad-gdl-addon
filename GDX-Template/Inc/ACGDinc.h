/*==========================================================================**
**								ACGDinc.h									**
**																			**
**					HEADER FILE FOR EXTENSION DEVELOPMENT					**
**==========================================================================*/

#ifndef	__ACGDINC_H_
#define	__ACGDINC_H_

#if defined (WINDOWS)
#if !defined (WINBASIC_H)
#include "Win32Interface.hpp"
#endif
#endif

#include	"GSRoot.hpp"
#include	"TRANMAT.h"		// TRANMAT
#include 	"GDLProc.h"
#include	"IFileServices.hpp"

#ifndef	GDLEXPORT_H
	#include	"GDLExport.h"
#endif


namespace IO {
	class Location;
}


/*****************************************************************************
**																			**
**					Functions implemented in the extension					**
**																			**
*****************************************************************************/
/*
**	Following functions must be implemented in each extension.
**	They are called from ARCHICAD.
**	For detailed description refer to the enclosed documentation.
*/

#if defined (ACExtension) && !defined (_ACGDLIB_TRANSL_)
#pragma export on
#endif

GSErr __GDLEXT_CALL	Initialize (void);

GSErr __GDLEXT_CALL	GetAddonInfo (Int32 channel, const GS::UniString& filename, const GS::UniString& paramstring,
								  bool* isDeterministicAddOn);

GSErr __GDLEXT_CALL	OpenDataFile (Int32 channel, const GS::UniString& filename, const GS::UniString& paramstring, GSHandle *optionhdl);

GSErr __GDLEXT_CALL	InputFromDataFile (Int32 channel, const GS::UniString& recordID, const GS::UniString& fieldID, Int32 nrvals, Int32 *retValue,
									   GDLRequestResult& values);

GSErr __GDLEXT_CALL	OutputToDataFile (Int32 channel, const GS::UniString& recordID, const GS::UniString& fieldID,
										const GDLRequestResult& values);


GSErr __GDLEXT_CALL	CloseDataFile (Int32 channel);

GSErr __GDLEXT_CALL	FreeData (void);

#if defined (ACExtension) && !defined (_ACGDLIB_TRANSL_)
#pragma export off
#endif

/*****************************************************************************
**																			**
**					Function supported by the library						**
**																			**
*****************************************************************************/
/*
**	Following functions are supported by the ACGD library.
**	For detailed description refer to the enclosed documentation.
*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
System specific support
*/

#if defined (WINDOWS)
__ACGDEXPORT HINSTANCE __GDLEXT_CALL	AC_GetExtensionInstance (void);
__ACGDEXPORT HWND __GDLEXT_CALL		AC_GetMainWindow (void);
__ACGDEXPORT bool __GDLEXT_CALL	AC_IsNewShell (void);
#endif


/*----------------------------------------------------------------------------
Generator & GDL environment
*/

__ACGDEXPORT void __GDLEXT_CALL	ACGD_GetGdlEnv (GDLEnv *gdlEnv);

__ACGDEXPORT const TRANMAT	* __GDLEXT_CALL	ACGD_GetTranMat (void);

__ACGDEXPORT	short	__GDLEXT_CALL ACGD_GetactPen (void);

__ACGDEXPORT	GSAttributeIndex	__GDLEXT_CALL ACGD_GetactLayer (void);

__ACGDEXPORT	short	__GDLEXT_CALL ACGD_GetactDrwIndex (void);

__ACGDEXPORT short	__GDLEXT_CALL ACGD_GetactGlima (void);

__ACGDEXPORT GSAttributeIndex	__GDLEXT_CALL ACGD_GetactGltyp (void);

__ACGDEXPORT GSAttributeIndex	__GDLEXT_CALL ACGD_GetactGlfil (void);

__ACGDEXPORT short	__GDLEXT_CALL ACGD_GetactStyle (void);

__ACGDEXPORT	Int32	__GDLEXT_CALL ACGD_GetSmoothness (double r);


/*----------------------------------------------------------------------------
Resource handling
*/

__ACGDEXPORT GSResModule __GDLEXT_CALL	AC_GetOwnResModule (void);

__ACGDEXPORT void __GDLEXT_CALL			AC_GetOwnLocation (IO::Location *ownFDef);

__ACGDEXPORT GSErr __GDLEXT_CALL		ACGD_Macro2File (const GS::UniString& name, IO::Location *macfile);

__ACGDEXPORT GSErr __GDLEXT_CALL		ACGD_GetDataFolder (IO::Location *location);

__ACGDEXPORT GDL::IFileServices* __GDLEXT_CALL		ACGD_GetFileServices ();


/*----------------------------------------------------------------------------
Progress bars / Report handling
*/
__ACGDEXPORT void __GDLEXT_CALL			AC_WriteReport (char *msg, bool asError, bool flushIt);

__ACGDEXPORT void __GDLEXT_CALL			ACGD_WriteError (char *msg);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif	/* __ACGDINC_H_ */
