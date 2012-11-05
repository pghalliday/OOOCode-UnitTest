#ifndef OOOMockDebug_H
#define OOOMockDebug_H

#include "OOOCode.h"
#include "OOOIDebug.h"

#define OOOClass OOOMockDebug
OOODeclare()
	OOOImplements
		OOOImplement(OOOIDebug)
	OOOImplementsEnd
	OOOExports
		OOOExport(bool, check, char * szCompare, ...)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
