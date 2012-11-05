#include "OOOUnitTestDefines.h"

#include "OOOMockDebug.h"

OOOTest(OOOMockDebug)
{
	OOOMockDebug * pOutput = OOOConstruct(OOOMockDebug);
	OOOIDebug * iOutput = OOOCast(OOOIDebug, pOutput);

	/* 1 print */
	OOOICall(iOutput, print, "Hello, %s\n", "World");
	OOOCheck(OOOCall(pOutput, check, "Hello, World\n"));

	/* 2 prints */
	OOOICall(iOutput, print, "Goodbye, %s\n", "World");
	OOOICall(iOutput, print, "Numbers, %d, %d, %d\n", 1, 2, 3);
	OOOCheck(OOOCall(pOutput, check,
			"Goodbye, World\n"
			"Numbers, 1, 2, 3\n"
			));

	/* 1 argument substitution in check */
	OOOICall(iOutput, print, "Hello, World\n");
	OOOICall(iOutput, print, "Numbers, 1, 2, 3\n");
	OOOCheck(OOOCall(pOutput, check,
			"Hello, %s\n"
			"Numbers, 1, 2, 3\n",
			"World"
			));

	/* multiple argument substitutions in check */
	OOOICall(iOutput, print, "Hello, World\n");
	OOOICall(iOutput, print, "Numbers, 1, 2, 3\n");
	OOOCheck(OOOCall(pOutput, check,
			"Hello, %s\n"
			"Numbers, %d, %d, %d\n",
			"World",
			1, 2, 3
			));

	/* last argument is a macro with arguments */
#define TEST_MACRO(X, Y) (X + Y)
	OOOICall(iOutput, print, "Hello, World\n");
	OOOICall(iOutput, print, "Numbers, 1, 2, 3\n");
	OOOCheck(OOOCall(pOutput, check,
			"Hello, %s\n"
			"Numbers, %d, %d, %d\n",
			"World",
			1, 2, TEST_MACRO(1, 2)
			));

	OOODestroy(pOutput);
}
