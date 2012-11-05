#include "OOODebugReporter.h"
#include "stdarg.h"

#define OOODebugReporter_LOG_MESSAGE_MAX_SIZE	4095

/* When printing to debug we want something easy to sed */
#define OOODebugReporter_DEBUG_OUTPUT_FORMAT	"BEGIN_UNIT_TEST_OUTPUT\n%s\nEND_UNIT_TEST_OUTPUT\n"

/* XML formats for different types of output */
#define OOODebugReporter_LOG_START_REPORT_FORMAT	"<?xml version \"1.0\"?><REPORT>"
#define OOODebugReporter_LOG_START_TEST_FORMAT		"<TEST name=\"%s\">"
#define OOODebugReporter_LOG_INFORMATION_FORMAT		"<INFORMATION file=\"%s\" line=\"%d\">%s</INFORMATION>"
#define OOODebugReporter_LOG_WARNING_FORMAT			"<WARNING file=\"%s\" line=\"%d\">%s</WARNING>"
#define OOODebugReporter_LOG_ERROR_FORMAT			"<ERROR file=\"%s\" line=\"%d\">%s</ERROR>"
#define OOODebugReporter_MEMORY_LEAK_FORMAT			"<MEMORY_LEAK test=\"%s\" bytes=\"%u\"/>"
#define OOODebugReporter_MEMORY_MAGIC_FORMAT		"<MEMORY_MAGIC test=\"%s\" bytes=\"%u\"/>"
#define OOODebugReporter_LOG_END_TEST_FORMAT		"</TEST>"
#define OOODebugReporter_LOG_END_REPORT_FORMAT		"</REPORT>"

#define OOOClass OOODebugReporter

OOOPrivateData
	OOOILog * iLog;
	char szLogMessage[OOODebugReporter_LOG_MESSAGE_MAX_SIZE + 1];
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, report, char * szText)
{
	/* At the moment we only write to debug in a format that is easy to sed */
	OOOICall(OOOF(iLog), print, OOODebugReporter_DEBUG_OUTPUT_FORMAT, szText);
}
OOOMethodEnd

OOOMethod(void, startReport)
{
	OOOC(report, OOODebugReporter_LOG_START_REPORT_FORMAT);
}
OOOMethodEnd

OOOMethod(void, startTestReport, char * szName)
{
	char * szText = O_dsprintf(OOODebugReporter_LOG_START_TEST_FORMAT, szName);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, log, OOOIReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;
	char * szText = NULL;

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOOF(szLogMessage), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OOODebugReporter_LOG_MESSAGE_MAX_SIZE);

	switch (nLogLevel)
	{
	case OOOIReporter_LogLevel_Information:
		szText = O_dsprintf(OOODebugReporter_LOG_INFORMATION_FORMAT, szFile, nLine, OOOF(szLogMessage));
		break;
	case OOOIReporter_LogLevel_Warning:
		szText = O_dsprintf(OOODebugReporter_LOG_WARNING_FORMAT, szFile, nLine, OOOF(szLogMessage));
		break;
	case OOOIReporter_LogLevel_Error:
		szText = O_dsprintf(OOODebugReporter_LOG_ERROR_FORMAT, szFile, nLine, OOOF(szLogMessage));
		break;
	}

	if (szText)
	{
		OOOC(report, szText);
		O_free(szText);
	}
}
OOOMethodEnd

OOOMethod(bool, check, bool bCondition, char * szFile, int nLine, char * szCondition)
{
	if (!bCondition)
	{
		OOOC(log, OOOIReporter_LogLevel_Error, szFile, nLine, "Failed check: %s", szCondition);
	}
	return bCondition;
}
OOOMethodEnd

OOOMethod(void, memoryLeak, char * szTest, size_t uBytesLost)
{
	char *szText = O_dsprintf(OOODebugReporter_MEMORY_LEAK_FORMAT, szTest, uBytesLost);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, memoryMagic, char * szTest, size_t uBytesGained)
{
	char *szText = O_dsprintf(OOODebugReporter_MEMORY_MAGIC_FORMAT, szTest, uBytesGained);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, endTestReport)
{
	OOOC(report, OOODebugReporter_LOG_END_TEST_FORMAT);
}
OOOMethodEnd

OOOMethod(void, endReport)
{
	OOOC(report, OOODebugReporter_LOG_END_REPORT_FORMAT);
}
OOOMethodEnd

OOOConstructor(OOOILog * iLog)
{
	#define OOOInterface OOOIReporter
	OOOMapVirtuals
		OOOMapVirtual(startReport)
		OOOMapVirtual(startTestReport)
		OOOMapVirtual(log)
		OOOMapVirtual(check)
		OOOMapVirtual(memoryLeak)
		OOOMapVirtual(memoryMagic)
		OOOMapVirtual(endTestReport)
		OOOMapVirtual(endReport)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd

	OOOF(iLog) = iLog;
}
OOOConstructorEnd

#undef OOOClass
