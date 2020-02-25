package main
// #cgo LDFLAGS: ./libEtwConsumer.a
// #include "EtwConsumer.h"
import "C"
// import "time"
// import "fmt"

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

func main() {
	traceSession := New()
	//traceSession.Close()
	traceSession.Consume()
	// time.Sleep(3 * time.Second)
	// fmt.Printf("***********************************************************\n")
	// fmt.Printf("*********************************   Going   To   Free   **************************\n")
	// fmt.Printf("***********************************************************\n")
	traceSession.Close()
	traceSession.Free()
}
