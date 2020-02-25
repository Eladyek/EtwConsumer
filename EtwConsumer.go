package EtwConsumer
// #cgo LDFLAGS: C:/Users/eyekutiel/Go/src/github.com/Eladyek/EtwConsumer/libEtwConsumer.a
// #include "EtwConsumer.h"
import "C"

type GoTraceSession struct {
	traceSession C.myTraceSession
}

func New() GoTraceSession {
	var ret GoTraceSession
	ret.traceSession = C.TraceSessionInit()
	return ret
}
func (tr GoTraceSession) Free() {
	C.TraceSessionFree(tr.traceSession)
}
func (tr GoTraceSession) Consume() {
	C.TraceSessionConsume(tr.traceSession)
}

func (tr GoTraceSession) Close() {
	C.TraceSessionClose(tr.traceSession)
}
