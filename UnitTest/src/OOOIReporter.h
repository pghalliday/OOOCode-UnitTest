#ifndef OOOIReporter_H
#define OOOIReporter_H

#include "OOOCode.h"

typedef enum
{
	OOOIReporter_LogLevel_Information,
	OOOIReporter_LogLevel_Warning,
	OOOIReporter_LogLevel_Error
}
OOOIReporter_LogLevel;

#define OOOInterface OOOIReporter
OOOVirtuals
	OOOVirtual(void, startReport)
	OOOVirtual(void, startTestReport, char * szName)
	OOOVirtual(void, log, OOOIReporter_LogLevel nLogLevel, char * szFile, int nLine, char * szMessage, ...)
	OOOVirtual(bool, check, bool bCondition, char * szFile, int nLine, char * szCondition)
	OOOVirtual(void, memoryLeak, char * szTest, size_t uBytesLost)
	OOOVirtual(void, memoryMagic, char * szTest, size_t uBytesGained)
	OOOVirtual(void, endTestReport)
	OOOVirtual(void, endReport)
OOOVirtualsEnd
#undef OOOInterface

#endif
