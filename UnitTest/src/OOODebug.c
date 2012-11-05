#include "OOODebug.h"
#include "OOOCode.h"
#include "stdarg.h"

#define OOODebug_LOG_MESSAGE_MAX_SIZE	4095

#define OOOClass OOODebug

OOOPrivateData
	char szLogMessage[OOODebug_LOG_MESSAGE_MAX_SIZE + 1];
OOOPrivateDataEnd

OOODestructor
{
}
OOODestructorEnd

OOOMethod(void, print, char * szMessage, ...)
{
	va_list aArgs;
	int nMessageLength = 0;

	va_start(aArgs, szMessage);
	nMessageLength = O_vsprintf(OOOF(szLogMessage), szMessage, aArgs);
	va_end(aArgs);

	/* There is a fixed size buffer for formatting the
	 * message - must ensure we haven't overrun it (no
	 * nicer way of doing this as far as i know) */
	assert(nMessageLength < OOODebug_LOG_MESSAGE_MAX_SIZE);

	O_debug(OOOF(szLogMessage));
}
OOOMethodEnd

OOOConstructor()
{
	#define OOOInterface OOOIDebug
	OOOMapVirtuals
		OOOMapVirtual(print)
	OOOMapVirtualsEnd
	#undef OOOInterface

	OOOMapMethods
	OOOMapMethodsEnd
}
OOOConstructorEnd

#undef OOOClass
