#include "TraceSession.h"

void(* callbackFunction)(char* n);

namespace
{
    VOID WINAPI EventRecordCallback(_In_ PEVENT_RECORD pEventRecord)
    {
        reinterpret_cast<ITraceConsumer*>(pEventRecord->UserContext)->OnEventRecord(pEventRecord, callbackFunction);
    }
}

TraceSession::TraceSession() : _szSessionName(_tcsdup(LPCTSTR("AD Core")))
{
	printf("new session\n");
}

TraceSession::~TraceSession(void)
{
	Close();
    delete[]_szSessionName;
    delete _pSessionProperties;
}

bool TraceSession::Start()
{
	 printf("starting!\n");
    if (!_pSessionProperties) {
		  delete _pSessionProperties;
	}
	printf("init session prop \n");
    const size_t buffSize = sizeof(EVENT_TRACE_PROPERTIES) + (_tcslen(_szSessionName) + 1) * sizeof(TCHAR);
    _pSessionProperties = reinterpret_cast<EVENT_TRACE_PROPERTIES*>(malloc(buffSize));
    ZeroMemory(_pSessionProperties, buffSize);
    _pSessionProperties->Wnode.BufferSize = buffSize;
    _pSessionProperties->Wnode.ClientContext = 1;
    _pSessionProperties->LogFileMode = EVENT_TRACE_REAL_TIME_MODE;
    _pSessionProperties->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);
	printf("StartingTrace\n");
    _status = StartTrace(&hSession, _szSessionName, _pSessionProperties);
	bool isSuccess = _status == ERROR_SUCCESS;
	printf("Status success is %b\n", isSuccess);
    return isSuccess;
}

bool TraceSession::EnableProvider(const GUID& providerId, UCHAR level, ULONGLONG anyKeyword)
{
	printf("Enabling Provider\n");
	_status = EnableTrace(EVENT_CONTROL_CODE_ENABLE_PROVIDER, anyKeyword, level, &providerId, hSession);
	bool isSuccess = _status == ERROR_SUCCESS;
	return isSuccess;
}

bool TraceSession::OpenTrace(ITraceConsumer* pConsumer)
{
    if (!pConsumer)
        return false;

    ZeroMemory(&_logFile, sizeof(EVENT_TRACE_LOGFILE));
    _logFile.LoggerName = _szSessionName;
    _logFile.ProcessTraceMode = PROCESS_TRACE_MODE_REAL_TIME | PROCESS_TRACE_MODE_EVENT_RECORD;
    _logFile.EventRecordCallback = &EventRecordCallback;
    _logFile.Context = pConsumer;

    _hTrace = ::OpenTrace(&_logFile);
    return (_hTrace != 0);
}



bool TraceSession::Process()
{
    _status = ProcessTrace(&_hTrace, 1, NULL, NULL);
    return (_status == ERROR_SUCCESS);
}

bool TraceSession::CloseTrace()
{
    _status = ::CloseTrace(_hTrace);
    return (_status == ERROR_SUCCESS);
}

bool TraceSession::DisableProvider(const GUID& providerId)
{
	                      
    _status = EnableTrace(EVENT_CONTROL_CODE_DISABLE_PROVIDER, 0, 0, &providerId, hSession);
    return (_status == ERROR_SUCCESS);
}

bool TraceSession::Stop()
{
    _status = ControlTrace(hSession, _szSessionName, _pSessionProperties, EVENT_TRACE_CONTROL_STOP);
    delete _pSessionProperties;
    _pSessionProperties = NULL;

    return (_status == ERROR_SUCCESS);
}

ULONG TraceSession::Status() const
{
    return _status;
}

LONGLONG TraceSession::PerfFreq() const
{
    return _logFile.LogfileHeader.PerfFreq.QuadPart;
}

void TraceSession::Close() 
{
	CloseTrace();
	printf("Closed Trace\n");
	DisableProvider(StringToGuid("{DAF0B914-9C1C-450A-81B2-FEA7244F6FFA}"));
	printf("Disabled Provider\n");
	Stop();
	printf("stopped\n");
}

int TraceSession::Consume()
{
    ITraceConsumer consumer = ITraceConsumer();
    printf("trace consumer was created!\n");

	if (Start()) {
		printf("trace session was started!  \n");
	}
	else {
		printf("trace session didnt start  \n");
		ULONG status = Status();
		printf("trace session status is: %d\n", status);

		if (status == ERROR_ALREADY_EXISTS) {
			if (Stop()) {
				printf("trace session was stopped!  \n");
				if (Start()) {
					printf("trace session was started!  \n");
				}
				else {
					printf("error trace session didnt start\n");
					return 1;
				}
			}
		}
		else {
			return 1;
		}
	}

    // EnableProvider(StringToGuid("{DAF0B914-9C1C-450A-81B2-FEA7244F6FFA}"), TRACE_LEVEL_VERBOSE,0); // office word
	EnableProvider(StringToGuid("{BB00E856-A12F-4AB7-B2C8-4E80CAEA5B07}"), TRACE_LEVEL_VERBOSE, 0); // office word2
	// EnableProvider(StringToGuid("{A1B69D49-2195-4F59-9D33-BDF30C0FE473}"), TRACE_LEVEL_VERBOSE,0); // office word3
	//EnableProvider(StringToGuid("{1C83B2FC-C04F-11D1-8AFC-00C04FC21914}"), TRACE_LEVEL_VERBOSE,0); // Active directory service : core
	printf("provider session was enabled!\n");

	OpenTraceA(&consumer);
	printf("trace session was opened!\n");
	bool b = Process();
	printf("trace session was proccessed!\n");
	return 0;
}
