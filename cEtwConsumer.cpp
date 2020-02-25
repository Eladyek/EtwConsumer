#include "EtwConsumer.hpp"
#include "EtwConsumer.h"

myTraceSession TraceSessionInit() {
	TraceSession * ret = new TraceSession();
	return (void*)ret;
}

void TraceSessionFree(myTraceSession ts) {
	TraceSession * traceSession = (TraceSession*)ts;
	traceSession->Close();
	delete traceSession;
}

void TraceSessionConsume(myTraceSession ts) {
	TraceSession * traceSession = (TraceSession*)ts;
	traceSession->Consume();
}

void TraceSessionClose(myTraceSession ts) {
	TraceSession * traceSession = (TraceSession*)ts;
	traceSession->Close();
}
