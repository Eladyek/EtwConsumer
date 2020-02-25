#ifndef _MY_PACKAGE_ETWCONSUMER_H_
#define _MY_PACKAGE_ETWCONSUMER_H_

#ifdef __cplusplus
extern "C" {
#endif

	typedef void* myTraceSession;
	myTraceSession TraceSessionInit(void);
	void TraceSessionFree(myTraceSession);
	void TraceSessionConsume(myTraceSession);
	void TraceSessionClose(myTraceSession);

#ifdef __cplusplus
}
#endif

#endif
