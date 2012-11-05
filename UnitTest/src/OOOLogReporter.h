#ifndef OOOLogReporter_H
#define OOOLogReporter_H

#include "OOOCode.h"
#include "OOOILog.h"
#include "OOOIReporter.h"

#define OOOClass OOOLogReporter
OOODeclare(OOOILog * iLog)
	OOOImplements
		OOOImplement(OOOIReporter)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
