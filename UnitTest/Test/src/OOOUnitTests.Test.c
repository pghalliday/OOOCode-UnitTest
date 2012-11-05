#include "OOOUnitTestDefines.h"

#include "OOOMockDebug.h"
#include "OOODebugReporter.h"
#include "OOOUnitTests.h"

#define OOOClass ReportTest

OOODeclare()
	OOOImplements
		OOOImplement(OOOIUnitTest)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, run)
{
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "My Test";
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIUnitTest
	OOOMapVirtuals
		OOOMapVirtual(run)
		OOOMapVirtual(getName)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass

#define OOOClass MemoryLeakTest

OOODeclare()
	OOOImplements
		OOOImplement(OOOIUnitTest)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	void * pMemoryLeak;
OOOPrivateDataEnd

OOODestructor
{
	if (OOOF(pMemoryLeak))
	{
		O_free(OOOF(pMemoryLeak));
	}
}
OOODestructorEnd

OOOMethod(void, run)
{
	OOOF(pMemoryLeak) = O_malloc(10000);
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "My Test";
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIUnitTest
	OOOMapVirtuals
		OOOMapVirtual(run)
		OOOMapVirtual(getName)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass

#define OOOClass MemoryMagicTest

OOODeclare(void * szMemoryMagic)
	OOOImplements
		OOOImplement(OOOIUnitTest)
	OOOImplementsEnd
	OOOExports
	OOOExportsEnd
OOODeclareEnd

OOOPrivateData
	void * pMemoryMagic;
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, run)
{
	O_free(OOOF(pMemoryMagic));
}
OOOMethodEnd

OOOMethod(char *, getName)
{
	return "My Test";
}
OOOMethodEnd

OOOConstructor(void * pMemoryMagic)
{
	#define OOOInterface OOOIUnitTest
	OOOMapVirtuals
		OOOMapVirtual(run)
		OOOMapVirtual(getName)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(pMemoryMagic) = pMemoryMagic;
}
OOOConstructorEnd

#undef OOOClass

OOOTest(OOOUnitTests)
{
	OOOMockDebug * pMockDebug = OOOConstruct(OOOMockDebug);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOIDebug, pMockDebug));
	ReportTest * pReportTest = OOOConstruct(ReportTest);
	MemoryLeakTest * pMemoryLeakTest = OOOConstruct(MemoryLeakTest);
	void * pMemoryMagic = O_malloc(10000);
	MemoryMagicTest * pMemoryMagicTest = OOOConstruct(MemoryMagicTest, pMemoryMagic);
	OOOIUnitTest * aTests[] =
	{
		OOOCast(OOOIUnitTest, pReportTest),
		OOOCast(OOOIUnitTest, pMemoryLeakTest),
		OOOCast(OOOIUnitTest, pMemoryMagicTest),
		NULL
	};
	OOOUnitTests * pTests = OOOConstruct(OOOUnitTests, OOOCast(OOOIReporter, pReporter), aTests);

	OOOCall(pTests, run);

	assert(OOOCall(pMockDebug, check,
			"BEGIN_UNIT_TEST_OUTPUT\n<?xml version \"1.0\"?><REPORT>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<MEMORY_LEAK test=\"My Test\" bytes=\"10004\"/>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n<MEMORY_MAGIC test=\"My Test\" bytes=\"10004\"/>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"
			"BEGIN_UNIT_TEST_OUTPUT\n</REPORT>\nEND_UNIT_TEST_OUTPUT\n"
			));

	OOODestroy(pTests);
	OOODestroy(pReportTest);
	OOODestroy(pMemoryLeakTest);
	OOODestroy(pMemoryMagicTest);
	OOODestroy(pReporter);
	OOODestroy(pMockDebug);
}

