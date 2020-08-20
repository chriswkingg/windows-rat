#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock, clientSock;
    char *buffer = malloc(sizeof(char) * 1024);
    char *response = malloc(sizeof(char) * 18384);
    struct sockaddr_in serverAddress, clientAddress;
    int optval = 1;
    socklen_t clientLength;

    sock = socket(AF_INET, SOCK_STREAM, 0); //use ipv4, use tcp for socket
    if(setsockopt(sock, SQL_SOCKET, SQL_REUSEADDR, &optval, sizeof(optval)) < 0) {
        //error
        printf("Error setting socket options\n");
        return 1;
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("192.168.0.61");
    serverAdress.sin_port = htons(789)

    //bind to port and listen
    bind(sock, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    listen(sock, 5); //takes in sock and max num of connections
    clientLength = sizeof(clientAddress);
    client_socket = accept(sock, (struct sockaddr *) &clientAddress, &clientLength);
}