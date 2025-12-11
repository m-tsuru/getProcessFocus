package main

/*
#cgo CFLAGS: -x objective-c
#cgo LDFLAGS: -framework Foundation -framework Cocoa -framework ApplicationServices
#include "lib/macos.h"
#include <stdlib.h>
*/
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	// アクティブなウィンドウのタイトルを取得
	cTitle := C.getActiveWindowTitle()
	if cTitle == nil {
		fmt.Println("タイトルの取得に失敗しました")
		return
	}
	defer C.free(unsafe.Pointer(cTitle))

	title := C.GoString(cTitle)
	fmt.Printf("アクティブなウィンドウのタイトル: %s\n", title)
}
