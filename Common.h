#ifndef _COMMON_
#define _COMMON_

#include <uchar.h>
#include <guiddef.h>
#include <windows.h>
#include <tchar.h>
#include <evntprov.h>
#include <evntcons.h>
#include <stdio.h>
#include <evntrace.h>

GUID StringToGuid(const char* str);

#endif