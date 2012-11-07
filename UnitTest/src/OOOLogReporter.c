#include "OOOLogReporter.h"
#include "OOO_vprintf.h"
#include "stdarg.h"

/* When printing to debug we want something easy to sed */
#define OOOLogReporter_DEBUG_OUTPUT_FORMAT	"BEGIN_UNIT_TEST_OUTPUT\n%s\nEND_UNIT_TEST_OUTPUT\n"

/* XML formats for different types of output */
#define OOOLogReporter_LOG_START_REPORT_FORMAT	"<?xml version \"1.0\"?><REPORT>"
#define OOOLogReporter_LOG_START_TEST_FORMAT	"<TEST name=\"%s\">"
#define OOOLogReporter_LOG_INFORMATION_FORMAT	"<INFORMATION file=\"%s\" line=\"%d\">%s</INFORMATION>"
#define OOOLogReporter_LOG_WARNING_FORMAT		"<WARNING file=\"%s\" line=\"%d\">%s</WARNING>"
#define OOOLogReporter_LOG_ERROR_FORMAT			"<ERROR file=\"%s\" line=\"%d\">%s</ERROR>"
#define OOOLogReporter_MEMORY_LEAK_FORMAT		"<MEMORY_LEAK test=\"%s\" bytes=\"%u\"/>"
#define OOOLogReporter_MEMORY_MAGIC_FORMAT		"<MEMORY_MAGIC test=\"%s\" bytes=\"%u\"/>"
#define OOOLogReporter_LOG_END_TEST_FORMAT		"</TEST>"
#define OOOLogReporter_LOG_END_REPORT_FORMAT	"</REPORT>"

#define OOOClass OOOLogReporter

OOOPrivateData
	OOOILog * iLog;
OOOPrivateDataEnd

OOODestructor
OOODestructorEnd

OOOMethod(void, report, char * szText)
{
	/* At the moment we only write to debug in a format that is easy to sed */
	OOOICall(OOOF(iLog), print, OOOLogReporter_DEBUG_OUTPUT_FORMAT, szText);
}
OOOMethodEnd

OOOMethod(void, startReport)
{
	OOOC(report, OOOLogReporter_LOG_START_REPORT_FORMAT);
}
OOOMethodEnd

OOOMethod(void, startTestReport, char * szName)
{
	char * szText = O_dsprintf(OOOLogReporter_LOG_START_TEST_FORMAT, szName);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, log, OOOIReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...)
{
	va_list aArgs;
	char * szText = NULL;

	va_start(aArgs, szMessage);
	OOO_vprintf(szMessage, aArgs);
	va_end(aArgs);

	switch (nLogLevel)
	{
	case OOOIReporter_LogLevel_Information:
		szText = O_dsprintf(OOOLogReporter_LOG_INFORMATION_FORMAT, szFile, nLine, OOO_vprintf_szBuffer);
		break;
	case OOOIReporter_LogLevel_Warning:
		szText = O_dsprintf(OOOLogReporter_LOG_WARNING_FORMAT, szFile, nLine, OOO_vprintf_szBuffer);
		break;
	case OOOIReporter_LogLevel_Error:
		szText = O_dsprintf(OOOLogReporter_LOG_ERROR_FORMAT, szFile, nLine, OOO_vprintf_szBuffer);
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
	char *szText = O_dsprintf(OOOLogReporter_MEMORY_LEAK_FORMAT, szTest, uBytesLost);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, memoryMagic, char * szTest, size_t uBytesGained)
{
	char *szText = O_dsprintf(OOOLogReporter_MEMORY_MAGIC_FORMAT, szTest, uBytesGained);
	OOOC(report, szText);
	O_free(szText);
}
OOOMethodEnd

OOOMethod(void, endTestReport)
{
	OOOC(report, OOOLogReporter_LOG_END_TEST_FORMAT);
}
OOOMethodEnd

OOOMethod(void, endReport)
{
	OOOC(report, OOOLogReporter_LOG_END_REPORT_FORMAT);
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
