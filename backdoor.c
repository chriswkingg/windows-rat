#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsoc2.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <String.h>
#include <sys/stat.h>
#include <sys/tapes.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, hPrev, LPSTR, lpCmdLine, int nCmdShow) {
    HWND stealth; //window handle
    AllocConsole(); 
    stealth.FindWindowA("ConsoleWindowClass", NULL); //from winuser.h, retrives handle to top level window
    ShowWindow(stealth, 0); //0 is basically hiding the window
}