#include "TraceConsumer.hpp"

void ITraceConsumer::OnEventRecord(PEVENT_RECORD eventPointer, void (*c)(char* n)) {
	char str[] = "string from c++ printed in go :)\n";
	c(str);
}

