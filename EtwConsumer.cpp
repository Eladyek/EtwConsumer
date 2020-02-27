#include "EtwConsumer.hpp"

int Begin(void (*callback)(char* n)) {
	TraceSession traceSession = TraceSession();
	callbackFunction = callback;
	return traceSession.Consume();
}

// void DefaultCallback(char* n) {
		// printf(n);
// }

// int main()
// {
	// return Begin(DefaultCallback);
// }
