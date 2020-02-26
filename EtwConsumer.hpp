#ifndef _MY_PACKAGE_ETWCONSUMER_HPP_
#define _MY_PACKAGE_ETWCONSUMER_HPP_

#pragma once

#include <uchar.h>
#include <guiddef.h>
#include <windows.h>
#include <evntrace.h>
#include <iostream>
#include <tchar.h>
#include <evntprov.h>
#include <evntcons.h>

struct ITraceConsumer;

int C(int n);
class TraceSession
{

public:
    TraceSession();
    ~TraceSession();

public:
    bool Start();
    bool EnableProvider(const GUID& providerId, UCHAR level, ULONGLONG anyKeyword = 0);
    bool OpenTrace(ITraceConsumer* pConsumer);
    bool Process();
    bool CloseTrace();
    bool DisableProvider(const GUID& providerId);
    bool Stop();
    void Close();
	int Consume(/*int (*c)(int n)*/);
    ULONG Status() const;
    LONGLONG PerfFreq() const;

private:
    LPTSTR _szSessionName;
    ULONG _status;
    EVENT_TRACE_PROPERTIES* _pSessionProperties;
    TRACEHANDLE hSession;
    EVENT_TRACE_LOGFILE _logFile;
    TRACEHANDLE _hTrace;

};

int Begin(void (*c)(char* n));

#endif