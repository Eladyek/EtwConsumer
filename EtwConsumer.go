// package EtwConsumer
package main
import "fmt"

/*
#include <stdio.h>
extern void BeginC();
*/
import "C"

//export GoCallback
func GoCallback(n *C.char) {
	fmt.Printf("****  GoCallback ********\n");
	fmt.Println(C.GoString(n));
}

func Example() {
	C.BeginC()
}

func main() {
	Example()
}

