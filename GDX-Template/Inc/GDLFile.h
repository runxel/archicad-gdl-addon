/*==========================================================================**
**									GDLFile.h								**
**																			**
**					TYPES AND PROTOTYPES FOR THE GDL FILE-HANDLER			**
**==========================================================================*/

#ifndef GDLFile_H
#define GDLFile_H

#pragma once


#include	"GSRoot.hpp"
#include	"GDLExport.h"
#include	"GDLDefs.h"
#include	"ISymbol2D.hpp"
#include	"SharedObject.hpp"

namespace GS {
	class UniString;
	class UniChar;
	class UnID;
	class ProcessControl;
}

namespace GDL {
	class IFileServices;
}

class GDL_DLL_EXPORT BinCode : public GS::SharedObject {
private:
	GSHandle binCode;

	BinCode (const BinCode&);
	BinCode& operator = (const BinCode&);

public:

	BinCode (const GSHandle binCode) : binCode (binCode) {}

	GSConstHandle GetBinCode () const { return binCode; }

	virtual ~BinCode ();
};

typedef GS::SharedPtr<BinCode> BinCodePtr;
typedef GS::ConstSharedPtr<BinCode> ConstBinCodePtr;

#endif
