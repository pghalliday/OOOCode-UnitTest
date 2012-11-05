#include "OOOUnitTests.h"

#define OOOClass OOOUnitTests

OOOPrivateData
	OOOIReporter * iReporter;
	OOOIUnitTest ** aTests;
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, run)
{
	size_t uHeapAvailableBefore = 0;
	size_t uHeapAvailableAfter = 0;
	OOOIUnitTest ** pTest = OOOF(aTests);

	OOOICall(OOOF(iReporter), startReport);

	while (*pTest)
	{
		OOOICall(OOOF(iReporter), startTestReport, OOOICall(*pTest, getName));

		uHeapAvailableBefore = O_heap_available();
		OOOICall(*pTest, run);
		uHeapAvailableAfter = O_heap_available();

		if (uHeapAvailableBefore > uHeapAvailableAfter)
		{
			OOOICall(OOOF(iReporter), memoryLeak, OOOICall(*pTest, getName), uHeapAvailableBefore - uHeapAvailableAfter);
		}
		else if (uHeapAvailableAfter > uHeapAvailableBefore)
		{
			OOOICall(OOOF(iReporter), memoryMagic, OOOICall(*pTest, getName), uHeapAvailableAfter - uHeapAvailableBefore);
		}

		OOOICall(OOOF(iReporter), endTestReport);
		pTest++;
	}
	OOOICall(OOOF(iReporter), endReport);
}
OOOMethodEnd

OOOConstructor(OOOIReporter * iReporter, OOOIUnitTest ** aTests)
{
	OOOMapMethods
		OOOMapMethod(run)
	OOOMapMethodsEnd

	OOOF(iReporter) = iReporter;
	OOOF(aTests) = aTests;
}
OOOConstructorEnd

#undef OOOClass
