#ifndef _TRACE_CONSUMER_
#define _TRACE_CONSUMER_

#include "Common.h"

struct ITraceConsumer{
	public:
		void OnEventRecord(PEVENT_RECORD eventPointer, void (*c)(char* n));
};

#endif