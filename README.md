# Basic Windows Malware

# Building the Project
Both the server and client must be build on linux using gcc from MinGW
Client: 
`i686-w64-mingw32-gcc -o notmalware.exe backdoor.c -lwsock32 -lwininet`
Server:
gcc -o server server.c
