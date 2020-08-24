// *********************************************************************************************************************
// Description:		Interface for file services without FileRef member
//
// Module:			GDL
// Namespace:		GDL
// Contact person:	TG
//
// SG compatible
// *********************************************************************************************************************

#if !defined (IFILE_HPP)
#define IFILE_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

#include	"GDLFile.h"
#include	"GDLDefs.h"
#include	"UniString.hpp"
#include	"Location.hpp"

// from GSRoot
#include	"Definitions.hpp"

namespace GS {
	class UniString;
	class UnID;
}

namespace IO {
	class Location;
}


namespace GDL {

	class IFileRef;


	class GDL_DLL_EXPORT IFileServices
	{

// --- Functions -------------------------------------------------------------------------------------------------------

		public:

			virtual	~IFileServices (void);

			virtual bool			IsValidName (const GS::UniString& name, bool isPicture = true, const GDL::IFileRef* callerFileRef = nullptr,
												 GS::UnID* unID = nullptr, bool dontCacheMissingMacros = false) = 0;

			virtual GDL::IFileRef*	Texture2File (const GS::UniString& name, short* msgind) = 0;
			virtual GDL::IFileRef*	Image3D2File (const GS::UniString& name, short* msgind) = 0;

			virtual GDL::IFileRef*	Macro2File (const GS::UniString& name, const GDL::IFileRef* callerFileRef,
												GSHandle* texthdl, short* msgind, GDL_ScriptType scriptType,
												GS::UnID* unID, bool dontCacheMissingMacros = false) = 0;

			virtual GSErr			Name2Location (const GS::UniString& name, IO::Location* loc) = 0;
			virtual GSErr			GetDataFolder (IO::Location* location) = 0;
			virtual GSErr			Init (const BinaryCachingMode& cachingMode) = 0;
			virtual void			Exit (void) = 0;
			virtual	void			Dispose (IFileRef** fileRef) = 0;

			static void				IFSGetCurrentTime (GSTime* dateTime);

	};

	class  GDL_DLL_EXPORT IFileServicesProvider
	{
	public:
		virtual ~IFileServicesProvider (void);

		virtual IFileServices* operator -> () = 0;
		operator IFileServices* () {
			return this->operator ->();
		}
	};

	GDL_DLL_EXPORT void						SetUIFileServices (IFileServicesProvider* provider);
	GDL_DLL_EXPORT IFileServicesProvider&	GetUIFileServices ();
}	// namespace GDL

#endif
