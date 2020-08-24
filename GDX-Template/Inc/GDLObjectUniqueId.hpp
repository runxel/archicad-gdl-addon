#if !defined GDL_GDLOBJECTUNIQUEID_HPP
#define GDL_GDLOBJECTUNIQUEID_HPP

#include "GDLExport.h"

namespace GDL
{

template<typename T>
struct RuntimeUniqueId
{
	UInt32	index = 0xFFFFFFFF;
	GS_DEBUG_ONLY ( const T* referredObjectForDebug = nullptr; )

	inline bool operator == (const RuntimeUniqueId<T>& other) const { return index == other.index; }
	inline bool operator != (const RuntimeUniqueId<T>& other) const { return index != other.index; }
};

}

namespace GS
{

template<typename T>
ULong	GenerateHashValue (const GDL::RuntimeUniqueId<T>& target)
{
	return GenerateHashValue (target.index);
}

}


#endif