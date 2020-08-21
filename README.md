# Basic Windows RAT
This is a simple windows remote access tool with a linux server. I AM NOT RESPONSIBLE FOR WHAT YOU DO WITH THIS SOFTWARE.
# Building the Project
Both the server and client must be build on linux using gcc from MinGW  
Client:
`i686-w64-mingw32-gcc -o notmalware.exe backdoor.c -lwsock32 -lwininet`  
Server:
`gcc -o server server.c`  
