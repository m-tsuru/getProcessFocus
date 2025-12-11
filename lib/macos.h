#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <ApplicationServices/ApplicationServices.h>

const char* getActiveWindowTitle() {
    @autoreleasepool {
        NSRunningApplication *app = [[NSWorkspace sharedWorkspace] frontmostApplication];

        if (!app) {
            return strdup("");
        }

        // アクティブなウィンドウのタイトルを取得するために Accessibility APIを 使用
        pid_t pid = [app processIdentifier];
        AXUIElementRef appRef = AXUIElementCreateApplication(pid);

        if (!appRef) {
            return strdup("");
        }

        AXUIElementRef windowRef = NULL;
        AXError error = AXUIElementCopyAttributeValue(appRef, kAXFocusedWindowAttribute, (CFTypeRef*)&windowRef);

        if (error != kAXErrorSuccess || !windowRef) {
            CFRelease(appRef);
            return strdup("");
        }

        CFStringRef titleRef = NULL;
        error = AXUIElementCopyAttributeValue(windowRef, kAXTitleAttribute, (CFTypeRef*)&titleRef);

        CFRelease(windowRef);
        CFRelease(appRef);

        if (error != kAXErrorSuccess || !titleRef) {
            return strdup("");
        }

        // CFString を C 文字列に変換
        NSString *title = (__bridge_transfer NSString*)titleRef;
        const char* result = strdup([title UTF8String]);

        return result;
    }
}
