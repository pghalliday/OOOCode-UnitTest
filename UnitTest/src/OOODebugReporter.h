#ifndef OOODebugReporter_H
#define OOODebugReporter_H

#include "OOOCode.h"
#include "OOOIDebug.h"
#include "OOOIReporter.h"

#define OOOClass OOODebugReporter
OOODeclare(OOOIDebug * iDebug)
	OOOImplements
		OOOImplement(OOOIReporter)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
