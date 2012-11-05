#ifndef OOOUnitTests_H
#define OOOUnitTests_H

#include "OOOCode.h"
#include "OOOIReporter.h"
#include "OOOIUnitTest.h"

#define OOOClass OOOUnitTests
OOODeclare(OOOIReporter * iReporter, OOOIUnitTest ** aTests)
	OOOImplements
	OOOImplementsEnd
	OOOExports
		OOOExport(void, run)
	OOOExportsEnd
OOODeclareEnd
#undef OOOClass

#endif
