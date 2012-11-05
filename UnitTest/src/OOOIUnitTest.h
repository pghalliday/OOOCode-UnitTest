#ifndef OOOIUnitTest_H
#define OOOIUnitTest_H

#include "OOOCode.h"
#include "OOOIReporter.h"

#define OOOInterface OOOIUnitTest
OOOVirtuals
	OOOVirtual(void, run)
	OOOVirtual(char *, getName)
OOOVirtualsEnd
#undef OOOInterface

#endif
