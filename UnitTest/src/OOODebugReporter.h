#ifndef OOODebugReporter_H
#define OOODebugReporter_H

#include "OOOCode.h"
#include "OOOILog.h"
#include "OOOIReporter.h"

#define OOOClass OOODebugReporter
OOODeclare(OOOILog * iLog)
	OOOImplements
		OOOImplement(OOOIReporter)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
