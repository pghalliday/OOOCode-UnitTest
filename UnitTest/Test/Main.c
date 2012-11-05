#include "opentv.h"
#include "assert.h"
#include "OOODebugLog.h"
#include "OOODebugReporter.h"
#include "OOOUnitTestsRun.h"


void main(void)
{
	/* run the tests first */
	OOODebugLog * pDebugLog = OOOConstruct(OOODebugLog);
	OOODebugReporter * pReporter = OOOConstruct(OOODebugReporter, OOOCast(OOOILog, pDebugLog));
	OOOUnitTestsRun(OOOCast(OOOIReporter, pReporter));
	OOODestroy(pReporter);
	OOODestroy(pDebugLog);

	while (TRUE) {
		// Do nothing
	}
}
