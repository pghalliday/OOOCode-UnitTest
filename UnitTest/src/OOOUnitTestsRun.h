#ifndef OOOUnitTestsRun_H
#define OOOUnitTestsRun_H

#include "OOOPastingAndQuoting.h"

#include "OOOUnitTests.h"
#include "OOOIReporter.h"

OOOIReporter * iOOOReporter;

/* Declare the test classes */
#define OOOTest(NAME) \
	_OOODeclare(OOOPaste(OOOUnitTest_,NAME)) \
		OOOImplements \
			OOOImplement(OOOIUnitTest) \
		_OOOImplementsEnd(OOOPaste(OOOUnitTest_,NAME)) \
		_OOOExports(OOOPaste(OOOUnitTest_,NAME)) \
		_OOOExportsEnd(OOOPaste(OOOUnitTest_,NAME)) \
	_OOODeclareEnd(OOOPaste(OOOUnitTest_,NAME))
#include "OOOTests.h"
#undef OOOTest

static void OOOUnitTestsRun(OOOIReporter * iReporter)
{
	OOOIUnitTest * aTests[] =
	{
		/* add the test instances */
#define OOOTest(NAME) OOOCast(OOOIUnitTest, OOOConstruct(OOOPaste(OOOUnitTest_,NAME))),
#include "OOOTests.h"
#undef OOOTest
		NULL
	};
	OOOIUnitTest ** pTest = aTests;
	OOOUnitTests * pTests = OOOConstruct(OOOUnitTests, iReporter, aTests);
	iOOOReporter = iReporter;
	OOOCall(pTests, run);
	OOODestroy(pTests);

	/* Destroy the test instances */
	while (*pTest)
	{
		OOOIDestroy(*pTest);
		pTest++;
	}
}

#endif
