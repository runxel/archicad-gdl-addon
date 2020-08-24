
// **************************************************************************
//
//         PUBLIC HEADER FILE OF THE GDL PARAMETER MANAGER FUNCTIONS
//
//
// Contact person: HK
//
// [somewhat SG compatible]
//
// **************************************************************************


#ifndef GDLPars_H_
#define GDLPars_H_

#pragma once

#include	"RealNumber.h"	//EPS
#include	"comProc.h"		// MessageProc
#include	"GDLExport.h"
#include	"Optional.hpp"
#include	"UniString.hpp"
#include	"Md5.hpp"

namespace GDL
{
class ParameterGetter;
class ParameterAccessor;
class Parameters;
}

class SymbolParametersSectionContent;


// **************************************************************************
//
//                             Helper macros
//
// **************************************************************************

#define INVALID_STORAGE_CATEGORY DBBREAK_STR ("Invalid storage type.")


short GetAddParHdlVersion (GSConstHandle addParHdl);



// **************************************************************************
//
//                              GDLIsIntType
//
// **************************************************************************
//
// The GDL variable types are grouped into three categories according to their corresponding C/C++ storage types:
// integer GDL types --> long			(use functions like: GDLModifyIntVar, GDLGetIntArrayVal, etc.)
// numeric GDL types --> double			(use functions like: GDLModifyNumVar, GDLGetNumArrayVal, etc.)
// ParT_CString      --> GS::UniString	(use functions like: GDLModifyUStrVar, GDLGetUStrArrayVal, etc.)
// ParT_Dictionary   --> GDL::Dictionary
// If we want to get or modify the value of a GDL variable, we have to call different handling functions according
// to the storage category of the type of the variable. GDLIsIntType returns true if the given GDL type is
// an integer type.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
bool		GDL_CALL	GDLIsIntType (short tp);
// ---------------------------------------------------------------------------
//	Arguments:
//		tp: the inquired GDL type
//
//	Return value:
//		true if tp is of integer type and such a value should be stored in a long variable.



// **************************************************************************
//
//                              GDLIsNumType
//
// **************************************************************************
//
// Checks if the passed GDL type is of numeric type and such a value must be held in a double variable.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
bool		GDL_CALL	GDLIsNumType (short tp);
// ---------------------------------------------------------------------------
//	Arguments:
//		tp: the inquired GDL type
//
//	Return value:
//		true if tp is of numeric type and such a value should be stored in a double variable.



GDL_DLL_EXPORT
bool		GDL_CALL	GDLIsStringType (short tp);

GDL_DLL_EXPORT
bool		GDL_CALL	GDLIsDictType (short tp);

// **************************************************************************
//
//                       Create a new variable handle
//
// **************************************************************************
//
// Creates a variable handle that holds the given number of variables. They are initialized to type ParT_RealNum and to value 0.0.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSHandle	GDL_CALL	GDLCreateVarHandle (Int32 nr);
// ---------------------------------------------------------------------------
//	Arguments:
//		nr: number of variables
//
//	Return value:
//		the new handle or nullptr if memory allocation failed.



// **************************************************************************
//
//                       Get the number of variables in the handle
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
Int32		GDL_CALL	GDLGetVarNumber (GSConstHandle varHdl);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl: handle holding GDL variables
//		varPtr: pointer to GDL variables
//
//	Return value:
//		the number of variables in the handle.



// **************************************************************************
//
//                       Get the number of fixed variables in the handle
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
Int32		GDL_CALL	GDLGetFixVarNumber (GSConstHandle varHdl);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl: handle holding GDL variables
//		varPtr: pointer to GDL variables
//
//	Return value:
//		the number of fixed variables in the handle.



// **************************************************************************
//
//                             Is variable fixed?
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
bool		GDL_CALL	GDLIsVarFix (GSConstHandle varHdl, Int32 index);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of variable (0 based)
//
//	Return value:
//		true if the specified variable is fixed

// **************************************************************************
//
//                             Set variable fixed
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErrCode	GDL_CALL	GDLSetVarFix (GSHandle varHdl, Int32 index, bool isFix);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of variable (0 based)
//
//	Return value:
//		GsErrorcode if the specified variable can't be fixed


// **************************************************************************
//
//                       Change the name of a variable
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr		GDL_CALL	GDLModifyVarName (GSHandle varHdl, Int32 index, const char* name);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of variable (0 based)
//		name:		new name of variable
//
//	Return value:
//		Error if
//			- index is out of bounds or,
//			- specified variable is fixed.



// **************************************************************************
//
//                       Get the name of a variable
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLGetVarName (GSConstHandle varHdl, Int32 index, char* name, Int32 buffSize);

const char*	GDL_CALL	GDLGetVarNameRef_Ptr (GSConstPtr varPtr, Int32 index);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of variable (0 based)
//		buffSize:	maximum number of characters to receive in 'name'.
//
//	Return arguments:
//		name:		pointer to buffer that receives the name of the specified variable
//
//	Return value:
//		Error if index is out of bounds.



// **************************************************************************
//
//                       Get the index of a variable name
//
// **************************************************************************
//
// Searches the index of the variable of the given name. If it's not found, returns a negative value.
// ---------------------------------------------------------------------------
Int32		GDL_CALL	GDLGetIndexOfName (GSConstHandle varHdl, const char* name, Int32 varIndex = -1,
										   bool forwardFromVarIndex = true);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		name:		name of the variable
//
//	Return value:
//		The index of the variable of the given name or a negative value if it doesn't exist in the handle.



// **************************************************************************
//
//                       Change the type of a variable
//
// **************************************************************************
//
// Changes the type of the given variable. In all cases the previous value(s) is/are lost and the variable's value is
// (or all the values in the array are) initialized to 0, 0.0, or "" depending on the type.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr		GDL_CALL	GDLModifyVarType (GSHandle varHdl, Int32 index, short type, bool isArray, Int32 dim1, Int32 dim2, bool keepPreviousArrayValues = false);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		index:		index of the variable (0 based)
//		type:		the new GDL type of the variable
//		isArray:	if true, the variable becomes an array, otherwise a simple (scalar) value.
//		dim1:		first dimension of array.
//		dim2:		second dimension of array or 0 if the array has one dimension.
//
//	Return value:
//		different from NoError if:
//			- memory allocation fails or,
//			- the index is out of bounds or,
//			- the specified variable is fixed or,
//			- isArray is true and dim1 is not positive.



// **************************************************************************
//
//                       Simple change in the type of a variable
//
// **************************************************************************
//
// A simple type change means that both the new and the old GDL types are numeric types, or both are integer
// types, or both are ParT_CString (this last means nothing's to be done).
// The old value is kept by the function, as well as the array, if it was an array.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyVarType_Simple (GSHandle varHdl, Int32 index, short newType);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		newType:	the new GDL type of the variable
//
//	Return value:
//		Error if
//			- the index is out of bounds or,
//			- the specified variable is fixed or,
//			- newType implies a non-simple type change, for example from ParT_RealNum to ParT_CString.


// **************************************************************************
//
//                       Change the dimensions of an array variable
//
// **************************************************************************
//
// Changes the dimensions of an array. Values are kept in rows and columns that are not diminished. Values in new columns and rows
// are initialized to the usual defaults (0, 0.0, ""). It is allowed to be used on fixed variables, as well.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyArrayDimensions (GSHandle varHdl, const Int32 index, Int32 newDim1, Int32 newDim2);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		index:		index of the variable (0 based)
//		newDim1:	the new first dimension of the array.
//		newDim2:	the new second dimension of the array or 0 if array has one dimension.
//
//	Return value:
//		different from NoError if:
//			- memory allocation fails or,
//			- the index is out of bounds or,
//			- the specified variable is not an array or newDim1 is not positive.



// **************************************************************************
//
//                       Get the type of a variable
//
// **************************************************************************
//
// Returns the GDL type of the given GDL variable, as well as the array's parameters if it is an array variable.
// ---------------------------------------------------------------------------
short		GDL_CALL	GDLGetVarType (GSConstHandle varHdl, Int32 index, bool* isArray = nullptr, Int32* dim1 = nullptr, Int32* dim2 = nullptr,
									   GSErr* err = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		isArray:	receives true if variable is an array. Can be nullptr to indicate that it is ignored.
//		dim1:		first dimension of array or 0 if variable is scalar. Can be nullptr to indicate that it is ignored.
//		dim2:		second dimension of array or 0 if array has only one dimension or variable is scalar. Can be nullptr to indicate that it is ignored.
//		err:		receives Error if index is out of bounds. Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		the GDL type of the variable.



// **************************************************************************
//
//                       Change the flags of a variable
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyVarFlags (GSHandle varHdl, Int32 index, unsigned char flags);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		flags:		the new value of variable flags
//
//	Return value:
//		Error if index is out of bounds.



// **************************************************************************
//
//                       Set bits of the variable flags to 1
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLSetVarFlagBits (GSHandle varHdl, Int32 index, unsigned char bits);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		bits:		the bits that are to be OR-ed to the current value of variable flags.
//
//	Return value:
//		Error if index is out of bounds.



// **************************************************************************
//
//                       Clear (zero out) bits of the variable flags
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLClearVarFlagBits (GSHandle varHdl, Int32 index, unsigned char bits);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		bits:		the bits that are to be zerod out from the current value of variable flags.
//
//	Return value:
//		Error if index is out of bounds.



// **************************************************************************
//
//                       Get the flags of a variable
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
unsigned char	GDL_CALL	GDLGetVarFlags (GSConstHandle varHdl, Int32 index, GSErr* err = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		err:		receives Error if index is out of bounds. Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		The flags of the specified variable.



// **************************************************************************
//
//                       Change the value of an integer variable
//
// **************************************************************************
//
// Changes the value of a scalar, integer type GDL variable.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr		GDL_CALL	GDLModifyIntVar (GSHandle varHdl, Int32 index, Int32 intVal, const GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		intVal:		new value of variable
//
//	Return value:
//		Error if
//			- index is out of bounds or,
//			- variable's type is not integer or,
//			- variable is an array.



// **************************************************************************
//
//                       Change the value of a numeric variable
//
// **************************************************************************
//
// Changes the value of a scalar, numeric type GDL variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyNumVar (GSHandle varHdl, Int32 index, double numVal, const GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		numVal:		new value of variable
//
//	Return value:
//		Error if
//			- index is out of bounds or,
//			- variable's type is not numeric or,
//			- variable is an array.



// **************************************************************************
//
//                       Change the value of a Boolean variable
//
// **************************************************************************
//
// Changes the value of a scalar, Boolean type GDL variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyBoolVar (GSHandle varHdl, Int32 index, bool boolVal);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		boolVal:	new value of variable
//
//	Return value:
//		Error if
//			- index is out of bounds or,
//			- variable's type is not integer or,
//			- variable is an array.



// **************************************************************************
//
//                       Change the value of a string variable
//
// **************************************************************************
//
// Changes the value of a scalar, string type GDL variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyUStrVar (GSHandle varHdl, Int32 index, const GS::UniString& strVal);

class GDLString;
GSErr		GDL_CALL	GDLModifyUStrVar (GSHandle varHdl, Int32 index, const GDLString& strVal);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		index:		index of the variable (0 based)
//		strVal:		the new string value of variable
//
//	Return value:
//		different from NoError if:
//			- memory allocation fails or,
//			- index is out of bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is an array.



// **************************************************************************
//
//                       Get the value of an integer variable
//
// **************************************************************************
//
// Returns the value of a scalar, integer type GDL variable.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
Int32		GDL_CALL	GDLGetIntVar (GSConstHandle varHdl, Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		err:		receives Error if
//						- index is out of bounds or,
//						- variable's type is not integer or,
//						- variable is an array.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		current value of the specified variable.



// **************************************************************************
//
//                       Get the value of a numeric variable
//
// **************************************************************************
//
// Returns the value of a scalar, numeric type GDL variable.
// ---------------------------------------------------------------------------
double		GDL_CALL	GDLGetNumVar (GSConstHandle varHdl, Int32 index, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		err:		receives Error if
//						- index is out of bounds or,
//						- variable's type is not numeric or,
//						- variable is an array.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		current value of the specified variable.



// **************************************************************************
//
//                       Get the value of an Boolean variable
//
// **************************************************************************
//
// Returns the value of a scalar, Boolean type GDL variable.
// ---------------------------------------------------------------------------
bool		GDL_CALL	GDLGetBoolVar (GSConstHandle varHdl, Int32 index, GSErr* err = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		err:		receives Error if
//						- index is out of bounds or,
//						- variable's type is not integer or,
//						- variable is an array.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		current value of the specified variable.



// **************************************************************************
//
//                       Get the value of a string variable
//
// **************************************************************************
//
// Returns the value of a scalar, string type GDL variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLGetUStrVar (GSConstHandle varHdl, Int32 index, GS::UniString& retVal);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		maxCh:		maximum number of characters to receive in strVal
//
//	Return arguments:
//		strVal:		pointer to buffer that receives the variable's value.
//		retVal:		receive the string in Unicode format.
//
//	Return value:
//		Error if
//			- memory allocation fails or,
//			- index is out of bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is an array.



// **************************************************************************
//
//                       Get the pointer to the value of a string variable
//
// **************************************************************************
//
// Returns a pointer to the value of a scalar, string type GDL variable. The pointer points into the variable handle, so
// it remains valid as long as the handle is not changed or destroyed.
// ---------------------------------------------------------------------------
const GS::UniChar::Layout*	GDL_CALL	GDLGetUStrVarRef (GSConstHandle varHdl, Int32 index);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return value:
//		pointer to the value of the variable (inside the handle), or nullptr if
//			- index is out of bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is an array.



// **************************************************************************
//
//                       Change all values of an integer array variable
//
// **************************************************************************
//
// Change all values of an integer array GDL variable. The values must be passed in a 'long[d1][d2]' type
// C/C++ array, where d1 and d2 are the dimensions of the array variable. If it has only one dimension, the type becomes
// 'long[d1]'.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyIntArray (GSHandle varHdl, Int32 index, const Int32* intVals, const GS::UniChar::Layout *arrayDescription = nullptr);

GSErr		GDL_CALL	GDLModifyIntArray (GSHandle varHdl, Int32 index, const GS::Array<Int32>& intVals);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		intVals:	array holding new values of the variable.
//
//	Return value:
//		Error if
//			- index is out of bounds or,
//			- variable's type is not integer or,
//			- variable is not an array.



// **************************************************************************
//
//                       Change all values of a numeric array variable
//
// **************************************************************************
//
// Change all values of a numeric array GDL variable. The values must be passed in a 'double[d1][d2]' type
// C/C++ array, where d1 and d2 are the dimensions of the array variable. If it has only one dimension, the type becomes
// 'double[d1]'.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyNumArray (GSHandle varHdl, Int32 index, const double* numVals, const GS::UniChar::Layout *arrayDescription = nullptr);


GSErr		GDL_CALL	GDLModifyOneDimensionNumArray (GSHandle varHdl, Int32 index, const double* numVals, UInt32 elemCount);


GSErr		GDL_CALL	GDLModifyOneDimensionNumArray (GSHandle varHdl, Int32 index, const GS::Array<double>& numVals);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		numVals:	array holding new values of the variable.
//
//	Return value:
//		Error if
//			- index is out of bounds or,
//			- variable's type is not numeric or,
//			- variable is not an array.



// **************************************************************************
//
//                       Change all values of a string array variable
//
// **************************************************************************
//
// Change all values of a string array GDL variable. In the passed buffer the strings of the array must follow each other in
// a way that the consecutive string starts right after the ending 0 character of the previous string. In a two dimensional array
// as we go through the strings the second index increases first and the first index increases when the second index reaches
// the dimension limit (just like in a long[d1][d2] C array).
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyUStrArray (GSHandle varHdl, Int32 index, const GS::UniChar::Layout *strVals);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		index:		index of the variable (0 based)
//		strVals:	buffer holding new values of the variable
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- index is out of bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is not an array.


// **************************************************************************
//
//                       Get all values of an array variable
//
// **************************************************************************
//
// The function allocates and returns a GSPtr that contains all values (or descriptions) of the array variable. The format of the returned buffer depends
// on the type of the GDL variable and is described in the explanation of functions GDLModifyIntArray, GDLModifyNumArray and
// GDLModifyStrArray. The returned pointer must be freed be the caller.
// GDLGetUArrayVar  returns strings in Unicode format - a series of uchar_t-s.
// ---------------------------------------------------------------------------
GSPtr		GDL_CALL	GDLGetUArrayVar (GSConstHandle varHdl, Int32 index, Int32 *len = nullptr, short *type = nullptr, Int32 *dim1 = nullptr,
										 Int32 *dim2 = nullptr);


GSPtr		GDL_CALL	GDLGetUArrayDescription (GSConstHandle varHdl, Int32 index, Int32 *len = nullptr, short *type = nullptr, Int32 *dim1 = nullptr,
										 Int32 *dim2 = nullptr);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		len:		receives the length of array. Can be nullptr to indicate that it is ignored.
//		type:		receives the GDL type of the variable. Can be nullptr to indicate that it is ignored.
//		dim1:		receives the first dimension of array. Can be nullptr to indicate that it is ignored.
//		dim2:		receives the second dimension of array or 0 if array has only one dimension. Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		pointer to the buffer that must be freed by the caller (using BMpFree) or nullptr if
//			- memory allocation fails or,
//			- index is out of bounds or,
//			- variable is not an array.



// **************************************************************************
//
//                       Get pointer to all values of an array variable
//
// **************************************************************************
//
// This function is similar to the GDLGetUArrayVar function, however it does NOT allocate new memory, but returns the pointer
// of the array's values inside the passed GSHandle. This means that it remains valid as long as the handle is not changed or destroyed.
// Strings are in Unicode format.
// ---------------------------------------------------------------------------
const void*		GDL_CALL	GDLGetUArrayRef (GSConstHandle varHdl, Int32 index, MemSize* len = nullptr);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//
//	Return arguments:
//		len:		receives the length of the buffer in bytes that contains the values. Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		pointer to the values or nullptr if
//			- index is out of bounds or,
//			- variable is not an array.



// **************************************************************************
//
//                       Get a value in an integer array variable
//
// **************************************************************************
//
// Returns the value of the given element in the given integer type array variable.
// ---------------------------------------------------------------------------
Int32		GDL_CALL	GDLGetIntArrayVal (GSConstHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//
//	Return arguments:
//		err:		receives Error if
//						- index, ind1 or ind2 is out bounds or,
//						- variable's type is not integer or,
//						- variable is not an array.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		value of the specified element in the array.



// **************************************************************************
//
//                       Get a value in a numeric array variable
//
// **************************************************************************
//
// Returns the value of the given element in the given numeric type array variable.
// ---------------------------------------------------------------------------
double		GDL_CALL	GDLGetNumArrayVal (GSConstHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr, GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//
//	Return arguments:
//		err:		receives Error if
//						- index, ind1 or ind2 is out bounds or,
//						- variable's type is not numeric or,
//						- variable is not an array.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		value of the specified element in the array.



// **************************************************************************
//
//                       Get a value in a Boolean array variable
//
// **************************************************************************
//
// Returns the value of the given element in the given Boolean type array variable.
// ---------------------------------------------------------------------------
bool		GDL_CALL	GDLGetBoolArrayVal (GSConstHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, GSErr* err = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//
//	Return arguments:
//		err:		receives Error if
//						- index, ind1 or ind2 is out bounds or,
//						- variable's type is not integer or,
//						- variable is not an array.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		value of the specified element in the array.



// **************************************************************************
//
//                       Get a value in a string array variable
//
// **************************************************************************
//
// Returns the value of the given element in the given string type array variable. The value is copied
// into the buffer provided by the caller.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLGetUStrArrayVal (GSConstHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, GS::UniString& retVal);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//		maxCh:		maximum number of characters that can be copied into strVal
//
//	Return arguments:
//		retVal:		receive the string in Unicode format.
//
//	Return value:
//		Error if
//			- memory allocation fails or,
//			- index, ind1 or ind2 is out bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is not an array.



// **************************************************************************
//
//                       Get the pointer to a value in a string array variable
//
// **************************************************************************
//
// Returns a pointer to the value of the given element in the given string type array variable. The pointer points
// to the string inside the GSHandle, so it remains valid as long as the handle is not changed or destroyed.
// The string is in Unicode format.
// ---------------------------------------------------------------------------
const GS::UniChar::Layout*	GDL_CALL	GDLGetUStrArrayValRef (GSConstHandle varHdl, Int32 index, Int32 ind1, Int32 ind2);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//
//	Return value:
//		pointer to string or nullptr if
//			- index, ind1 or ind2 is out bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is not an array.



// **************************************************************************
//
//                       Get a value in a numeric, integer or string array variable (in ANSI format)
//
// **************************************************************************
//
// Returns the value of the given element in the given numeric, integer or string type array variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLGetArrayUVal (GSConstHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, double* numVal, GS::UniString& strVal, GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//		maxCh:		maximum number of characters that can be copied into strVal.
//
//	Return arguments:
//		numVal:		receives the value if variable is numeric or integer.
//		strVal:		receives the value if variable is ParT_CString. The string is UniString.
//
//	Return value:
//		Error if
//			- index, ind1 or ind2 is out bounds or,
//			- variable is not an array.



// **************************************************************************
//
//                       Change a value in an integer array variable
//
// **************************************************************************
//
// Change the value of the given element in the given integer type array variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyIntArrayVal (GSHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, Int32 intVal, const GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//		intVal:		new value of the specified element of the variable
//
//	Return value:
//		Error if
//			- index, ind1 or ind2 is out bounds or,
//			- variable's type is not integer or,
//			- variable is not an array.



// **************************************************************************
//
//                       Change a value in a numeric array variable
//
// **************************************************************************
//
// Change the value of the given element in the given numeric type array variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyNumArrayVal (GSHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, double numVal, const GS::UniString* numValDescription = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//		numVal:		new value of the specified element of the variable
//
//	Return value:
//		Error if
//			- index, ind1 or ind2 is out bounds or,
//			- variable's type is not numeric or,
//			- variable is not an array.



// **************************************************************************
//
//                       Change a value in a Boolean array variable
//
// **************************************************************************
//
// Change the value of the given element in the given Boolean type array variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyBoolArrayVal (GSHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, bool boolVal);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//		boolVal:	new value of the specified element of the variable
//
//	Return value:
//		Error if
//			- index, ind1 or ind2 is out bounds or,
//			- variable's type is not integer or,
//			- variable is not an array.



// **************************************************************************
//
//                       Change a value in a string array variable
//
// **************************************************************************
//
// Change the value of the given element in the given string type array variable.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyUStrArrayVal (GSHandle varHdl, Int32 index, Int32 ind1, Int32 ind2, const GS::UniString& strVal);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		index:		index of the variable (0 based)
//		ind1:		first dimension index of the element (1 based)
//		ind2:		second dimension index of the element (1 based)
//		strVal:		new value of the specified element of the variable
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- index, ind1 or ind2 is out bounds or,
//			- variable's type is not ParT_CString or,
//			- variable is not an array.



// **************************************************************************
//
//                       Get value of the "A" parameter
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
double		GDL_CALL	GDLGetParamA (GSConstHandle varHdl, GSErr* err = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//
//	Return arguments:
//		err:		receives Error if
//						- the "A" parameter is not found.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		value of the "A" parameter.



// **************************************************************************
//
//                       Get value of the "B" parameter
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
double		GDL_CALL	GDLGetParamB (GSConstHandle varHdl, GSErr* err = nullptr);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//
//	Return arguments:
//		err:		receives Error if
//						- the "B" parameter is not found.
//					Can be nullptr to indicate that it is ignored.
//
//	Return value:
//		value of the "B" parameter.



// **************************************************************************
//
//                       Change value of the "A" parameter
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyParamA (GSHandle varHdl, double val);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		val:		new value of the "A" parameter
//
//	Return value:
//		Error if
//			- the "A" parameter is not found.



// **************************************************************************
//
//                       Change value of the "B" parameter
//
// **************************************************************************
//
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLModifyParamB (GSHandle varHdl, double val);

// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		varPtr:		pointer to GDL variables
//		val:		new value of the "B" parameter
//
//	Return value:
//		Error if
//			- the "B" parameter is not found.



// **************************************************************************
//
//                       Create handle with simple parameters
//
// **************************************************************************
//
// The function allocates a new variable handle and fills it with parameters from 'A' to 'Z' (26 params).
// Their values are initialized from the incoming params array and their type will be ParT_RealNum.
// ---------------------------------------------------------------------------
GSHandle	GDL_CALL	GDLParamsToVarHdl (const double *params);
// ---------------------------------------------------------------------------
//	Arguments:
//		params: an array containing 26 doubles holding the initial values of the parameters. If
//				nullptr, parameters are initialized to 0.0.
//
//	Return value:
//		the new handle or nullptr if memory allocation fails.



// **************************************************************************
//
//                       Delete variables from a handle
//
// **************************************************************************
//
// Delete a range of variables from the handle. A zero length range (firstInd > lastInd) is accepted in which
// case nothing happens. Otherwise negative indexes are no longer allowed to indicate 'until last element'.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLDropVarsFromHdl (GSHandle varHdl, Int32 firstInd, Int32 lastInd);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		firstInd:	index of the first variable to delete. (0 based)
//		lastInd:	index of the last variable to delete. (0 based)
//
//	Return value:
//		Error if
//			- indexes are out of bounds, except if firstInd > lastInd (--> no operation) or,
//			- there is at least one fixed variable in the specified range.



// **************************************************************************
//
//                       Insert variables of a handle into another
//
// **************************************************************************
//
// Insert a range of variables from sourceHdl into destHdl. All old variables of both handles are kept.
// Fixed variables of the source handle become regular variables in the destination handle.
// A zero length range (firstInd > lastInd) is accepted in which case nothing happens.
// Otherwise negative indexes are no longer allowed to indicate 'until last element'.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLInsertVarsIntoHdl (GSHandle destHdl, GSConstHandle sourceHdl, Int32 firstInd, Int32 lastInd, Int32 destInd);

// ---------------------------------------------------------------------------
//	Arguments:
//		destHdl:	variables are inserted into this handle
//		sourceHdl:	variables are inserted from this handle. This handle remains unchanged.
//		firstInd:	index of the first variable in sourceHdl to insert. (0 based)
//		lastInd:	index of the last variable in sourceHdl to insert. (0 based)
//		destInd:	specifies the new index in destHdl of the first inserted variable. (0 based) It can exceed the valid index numbers
//						of destHdl by 1 (that is it can equal to the number of variables in destHdl), in which case new variables
//						are appended to the end of destHdl.
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- indexes are out of bounds, except if firstInd > lastInd (--> no operation) or
//				destInd == number of variables in destHdl (--> append).



// **************************************************************************
//
//                       Insert a new variable into a handle
//
// **************************************************************************
//
// A new variable is inserted into a handle. All old variables are kept. The value of the new variable (or all its values if it is
// an array) is/are initialized to 0, 0.0 or "" depending on the variable's type.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLInsertNewVar (GSHandle destHdl, Int32 destInd, const char* name, short type, bool isArray, Int32 dim1, Int32 dim2);
// ---------------------------------------------------------------------------
//	Arguments:
//		destHdl:	new variable is inserted into this handle
//		destInd:	specifies the new index in destHdl of the inserted variable. (0 based) It can exceed the valid index numbers
//						of destHdl by 1 (that is it can equal to the number of variables in destHdl), in which case the new variable
//						is added as last variable of destHdl.
//		name:		name of the variable
//		type:		GDL type of the variable
//		isArray:	specifies if new variable is array or simple (scalar).
//		dim1:		first dimension of array.
//		dim2:		second dimension of array or 0 if array has only one dimension.
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- destInd is out of bounds, except if destInd == number of variables in destHdl (--> append).
//			- isArray is true and dim1 is not positive.



// **************************************************************************
//
//                       Add a new variable to a handle
//
// **************************************************************************
//
// A new variable is added as last variable of a handle. The value of the new variable (or all its values if it is
// an array) is/are initialized to 0, 0.0 or "" depending on the variable's type.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLAddVarToHdl (GSHandle varHdl, const char* name, short type, bool isArray, Int32 dim1, Int32 dim2);
// ---------------------------------------------------------------------------
//	Arguments:
//		destHdl:	new variable is added to this handle
//		name:		name of the variable
//		type:		GDL type of the variable
//		isArray:	specifies if new variable is array or simple (scalar).
//		dim1:		first dimension of array.
//		dim2:		second dimension of array or 0 if array has only one dimension.
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- isArray is true and dim1 is not positive.



// **************************************************************************
//
//                       Create new handle from a range of variables
//
// **************************************************************************
//
// Allocates a new handle to hold a range of variables from a source handle.
// Fixed variables of the source handle become regular in the new handle.
// A zero length range (firstInd > lastInd) is accepted in which case a handle containing no variables is returned (not a nullptr handle).
// Otherwise negative indexes are no longer allowed to indicate 'until last element'.
// ---------------------------------------------------------------------------
GSHandle	GDL_CALL	GDLCreatePartialCopy (GSConstHandle fromHdl, Int32 firstInd, Int32 lastInd);
// ---------------------------------------------------------------------------
//	Arguments:
//		fromHdl:	variables are copied from this handle. This handle remains unchanged.
//		fromPtr:	pointer to source variables.
//		firstInd:	index of the first variable in sourceHdl to copy. (0 based)
//		lastInd:	index of the last variable in sourceHdl to copy. (0 based)
//
//	Return value:
//		the new handle or nullptr if
//			- memory allocation fails or,
//			- indexes are out of bounds, except if firstInd > lastInd (--> empty variable handle created)



// **************************************************************************
//
//                       Create copy of a handle
//
// **************************************************************************
//
// Allocates a new handle and copies the variables of a source handle into it.
// ---------------------------------------------------------------------------
GSHandle	GDL_CALL	GDLCreateCopy (GSConstHandle fromHdl);
// ---------------------------------------------------------------------------
//	Arguments:
//		fromHdl:	variables are copied from this handle. This handle remains unchanged.
//
//	Return value:
//		the new handle or nullptr if
//			- memory allocation fails.



// **************************************************************************
//
//                 Copy a range of variables of a handle into another
//
// **************************************************************************
//
// Copy a range of variables from sourceHdl into destHdl. Old values in the range are overwritten in destHdl, others are kept.
// New variables are appended to destHdl if the range reaches beyond the end of destHdl.
// Fixed variables in the source handle become regular variables in the destination handle.
// A zero length range (firstInd > lastInd) is accepted in which case nothing happens.
// Otherwise negative indexes are no longer allowed to indicate 'until last element'.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLCopyVarsIntoHdl (GSHandle destHdl, GSConstHandle sourceHdl, Int32 firstInd, Int32 lastInd, Int32 destInd);
// ---------------------------------------------------------------------------
//	Arguments:
//		destHdl:	variables are copied into this handle. Old variables in the range are overwritten.
//		sourceHdl:	variables are copied from this handle. This handle remains unchanged.
//		firstInd:	index of the first variable in sourceHdl to copy. (0 based)
//		lastInd:	index of the last variable in sourceHdl to copy. (0 based)
//		destInd:	specifies the new index in destHdl of the first copied variable. (0 based) It can exceed the valid index numbers
//						of destHdl by 1 (that is it can equal to the number of variables in destHdl), in which case new variables
//						are appended to the end of destHdl.
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- indexes are out of bounds, except if firstInd > lastInd (--> no operation) or
//				destInd == number of variables in destHdl (--> append) or,
//			- there is at least one fixed variable in the specified range in destHdl



// **************************************************************************
//
//              Change the position of a variable inside a handle
//
// **************************************************************************
//
// The variable is replaced to a new index in the handle. A fixed variable remains
// fixed at the new index, too.
// ---------------------------------------------------------------------------
GSErr		GDL_CALL	GDLReplaceVarInHdl (GSHandle varHdl, Int32 oldIndex, Int32 newIndex);
// ---------------------------------------------------------------------------
//	Arguments:
//		varHdl:		handle holding GDL variables
//		oldIndex:	index of the variable before the replace. (0 based)
//		newIndex:	index of the variable after the replace. (0 based)
//
//	Return value:
//		different from NoError if
//			- memory allocation fails or,
//			- indexes are out of bounds.



// **************************************************************************
//
//                        Check consistency of variable handle
//
// **************************************************************************
//
// Useful when variable handles are read in from file, network or uncertain sources. That's why it is not even the handle that is passed,
// but instead the variables' starting position in memory and the memory length.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
bool		GDL_CALL	GDLIsAddParPtrCorrect (const char* addParPtr, Int32 varHdlSize);
// ---------------------------------------------------------------------------
//	Arguments:
//		vars:		starting position of memory buffer containing variables.
//		sz:			length of memory buffer containing variables.
//
//	Return value:
//		true if consistency test is passed, false if failed.


// **************************************************************************
//
//                         Swap parameter handle
//
// **************************************************************************
//
// Swap the platform of the given parameter handle.
// --------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr	GDL_CALL	GDLSwapAddParHdl	(GS::PlatformSign	inplatform,
										 GSHandle			addParHdl,
										 short				version,
										 GS::PlatformSign	toplatform);
// --------------------------------------------------------------------------
// Arguments:
//		addParHdl:	the parameter handle,
//		version:	version number of the parameter handle,
//		platform:	the new platform.



// --------------------------------------------------------------------------
// Arguments:
//		addParHdl:	the parameter handle,
//		width:		the A parameter. There are old versions of the handle which do not contain this parameter.
//					It can be given with this parameter,
//		height:		the B parameter. There are old versions of the handle which do not contain this parameter.
//					It can be given with this parameter,
//		version:	version number of the old parameter handle,



// **************************************************************************
//
//             Compare types of parameter handles without the values
//
// **************************************************************************
//
// Compare two parameter handles.
// --------------------------------------------------------------------------
GDL_DLL_EXPORT
bool	GDL_CALL	GDLCompareAddParHdls (const GDL::ParameterGetter&	defAddParHdl,
										  GDL::ParameterAccessor&		oldAddParHdl,
										  bool*							modifOldPar);
// --------------------------------------------------------------------------
// Arguments:
//		defAddParHdl:	the default handle,
//		oldAddParHdl:	the original handle, this contains the original parameters.
//	Return argument:
//		modifOldPar:	if the original handle came from old file it will be modified,
//						this parameter shows it.
//	Return value:		true if the handles are the same.


// **************************************************************************
//
//           		Calc the checksum of a parameter handle
//
// **************************************************************************
//
// Calcs the checksum of a parameter handle.
// --------------------------------------------------------------------------
enum class CheckSumMode {
	SkipScriptControlledParamFlags,
	IncludeScriptControlledParamFlags
};

GDL_DLL_EXPORT
Int32	GDL_CALL				GDLCalcInt32CheckSumAddParHdl (const GDL::ParameterGetter& addParHdl, CheckSumMode checkSumMode = CheckSumMode::SkipScriptControlledParamFlags);
GDL_DLL_EXPORT
MD5::FingerPrint	GDL_CALL	GDLCalcMD5CheckSumAddParHdl (const GDL::ParameterGetter& addParHdl, 
															 GS::Optional<double> discretizationEps = EPS,
															 CheckSumMode checkSumMode = CheckSumMode::SkipScriptControlledParamFlags);


// --------------------------------------------------------------------------
// Arguments:
//		addParHdl:		the parameter handle
//		sumVars:		if it is not nullptr, the summarized numeric values
//	Return value:		the checksum.


// **************************************************************************
//
//           Compare two parameters of two handles; name, type and value must be the same
//
// **************************************************************************
//
// --------------------------------------------------------------------------

GDL_DLL_EXPORT
bool	GDL_CALL	GDLEqualAddParEntries  (const GDL::ParameterGetter&	addParPtr_1, const Int32 parIndex_1,
                                            const GDL::ParameterGetter&	addParPtr_2, const Int32 parIndex_2, const double eps = EPS);

// --------------------------------------------------------------------------
// Arguments:
//		addParHdl_1 and addParHdl_2 : the two parameter handles
//		parIndex_1 and parIndex_2 :   the index of corresponding parameters to be compared 
//		eps :						  is used to compare real numbers
//	Return value:		true if the two parameters are equal.


// **************************************************************************
//
//           Compare parameter handles with the values of parameters
//
// **************************************************************************
//
// Compare two parameter handles.
// --------------------------------------------------------------------------

GDL_DLL_EXPORT
bool	GDL_CALL	GDLEqualAddPars		(const GDL::ParameterGetter&	defAddParHdl,
										 const GDL::ParameterGetter&	actAddParHdl);

// --------------------------------------------------------------------------
// Arguments:
//		defAddParHdl,
//		actAddParHdl:	the two parameter handles
//	Return value:		true if the handles are equal.


// **************************************************************************
//
//                            Merge parameter handles
//
// **************************************************************************
//
// Merges two parameter handles and makes a new one.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr	GDL_CALL	GDLMergeAddParHdls	(const GDL::Parameters& defAddParHdl,
										 const GDL::Parameters& oldAddParHdl,
										 GDL::Parameters&	newAddParHdl);


enum class MergeAddParHdlsToCurrentResult {
	UseDefault,
	UseNew
};

GDL_DLL_EXPORT
MergeAddParHdlsToCurrentResult	GDL_CALL	GDLMergeAddParHdlsToCurrentCreate (	const GDL::ParameterGetter&	defAddParHdl,
																				const GDL::ParameterGetter&	oldAddParHdl,
																				GDL::Parameters&			newAddParHdl);

GDL_DLL_EXPORT
GSErr	GDL_CALL	GDLOverrideExistingParHdl (const GDL::ParameterGetter&	oldAddParHdl,
											   const GDL::ParameterGetter&	overrideAddParHdl,
											   GDL::Parameters&				newAddParHdl);

// ---------------------------------------------------------------------------
// Arguments:
//		defAddParHdl:	the default parameter handle,
//		oldAddParHdl:	the original handle, this contains the original parameters.
//	Return value:
//		Error if memory error



// **************************************************************************
//
//                 Append parameters to an existing other handle
//
// **************************************************************************
//
// Appends parameters to an existing handle only if it does not already contain
// them.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
GSErr	GDL_CALL	GDLAppendDiffVars (const GDL::ParameterGetter& oldParams, GDL::Parameters& newParams);
// ---------------------------------------------------------------------------
//	Arguments:
//		oldParHdl:  the parameters to append
//		newParHdl:	the new handle, containing as a result the appended values from
//					oldParHdl
//	Return value:
//		Error if memory error



// **************************************************************************
//
//                 Dump variable to the specified output
//
// **************************************************************************
//
// Dumps the variable of the handle at index to the specified output via the given MessageProc.

GDL_DLL_EXPORT
void	GDL_CALL	GDLDumpVariable (const GDL::ParameterGetter& parameters, Int32 index, MessageProc_UStr* messageProc);

// **************************************************************************
//
//                 Dump variable handle to the specified output
//
// **************************************************************************
//
// Dumps the variable handle to the specified output via the given MessageProc.
// ---------------------------------------------------------------------------
GDL_DLL_EXPORT
void	GDL_CALL	GDLDumpVariableHdl (const GDL::ParameterGetter& variableHdl, MessageProc_UStr* messageProc);

// ---------------------------------------------------------------------------
// Arguments:
//		variableHdl:	the variable handle.
//		variablePtr:	pointer to variables.
//		messageProc:	callback for the output. If it is nullptr, the default
//						procedure will be called (OUDebug)

// I don't know, I guess this shouldn't be here...
GDL_DLL_EXPORT
void	GDL_CALL	SetRatioOrSize (const SymbolParametersSectionContent* syParSect, bool* useXYFixSize, double* xRatioOrSize, double* yRatioOrSize);

#endif
