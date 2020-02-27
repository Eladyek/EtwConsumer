#ifndef _TRACE_SESSION_
#define _TRACE_SESSION_

#include "Common.h"
#include "TraceConsumer.hpp"

extern void(* callbackFunction)(char* n);

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
	int Consume();
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

#endif