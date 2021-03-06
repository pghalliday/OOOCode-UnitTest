#include "OOOUnitTestDefines.h"

#include "OOOBufferedLog.h"
#include "OOOLogReporter.h"

OOOTest(OOOLogReporter)
{
	OOOBufferedLog * pLog = OOOConstruct(OOOBufferedLog);
	OOOLogReporter * pReporter = OOOConstruct(OOOLogReporter, OOOCast(OOOILog, pLog));
	OOOIReporter * iReporter = OOOCast(OOOIReporter, pReporter);

	OOOICall(iReporter, startReport);
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n<?xml version \"1.0\"?><REPORT>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOICall(iReporter, startTestReport, "My Test");
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n<TEST name=\"My Test\">\nEND_UNIT_TEST_OUTPUT\n"));

	OOOICall(iReporter, log, OOOIReporter_LogLevel_Information, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n<INFORMATION file=\"My File\" line=\"10\">Test Information: Hello: 55</INFORMATION>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOICall(iReporter, log, OOOIReporter_LogLevel_Warning, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n<WARNING file=\"My File\" line=\"10\">Test Information: Hello: 55</WARNING>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOICall(iReporter, log, OOOIReporter_LogLevel_Error, "My File", 10, "Test Information: %s: %d", "Hello", 55);
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Test Information: Hello: 55</ERROR>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOCheck(OOOICall(iReporter, check, TRUE, "My File", 10, "TRUE"));
	OOOCheck(OOOCall(pLog, check, NULL));

	OOOCheck(!OOOICall(iReporter, check, FALSE, "My File", 10, "FALSE"));
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n<ERROR file=\"My File\" line=\"10\">Failed check: FALSE</ERROR>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOICall(iReporter, endTestReport);
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n</TEST>\nEND_UNIT_TEST_OUTPUT\n"));

	OOOICall(iReporter, endReport);
	OOOCheck(OOOCall(pLog, check, "BEGIN_UNIT_TEST_OUTPUT\n</REPORT>\nEND_UNIT_TEST_OUTPUT\n"));

	OOODestroy(pReporter);
	OOODestroy(pLog);
}
