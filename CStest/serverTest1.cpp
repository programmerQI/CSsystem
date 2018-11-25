#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>

#define PORT 9999
#define IP_ADDR "127.0.0.1"

int main()
{
    // Create the socket with specific address format, communication style and default protocol
    int serverSocket = socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket<0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    std::cout << "The server socket has been created." << std::endl;

    // Configure IP address and port
    struct sockaddr_in serverSocketName;
    serverSocketName.sin_family=AF_INET;
    if(inet_pton(AF_INET,IP_ADDR,&serverSocketName.sin_addr)<0)
    {
        std::cout << "Invalid IP address!" << std::endl;
        exit(EXIT_FAILURE);
    }
    serverSocketName.sin_port = htons(PORT);
    std::cout << "Init server IP." << std::endl;

    // Bind the name to the socket
    socklen_t size_serverSocketName = sizeof(serverSocketName);
    if(bind(serverSocket, (struct sockaddr *)&serverSocketName, size_serverSocketName)<0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    std::cout << "Bind the name to server socket." << std::endl;

    // Listening
    if(listen(serverSocket,1)<0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cout << "Listening." << std::endl;

    // Waiting for connection
    int clientSocket;
    struct sockaddr_in clientSocketName;
    socklen_t size_clientSocketName;
    std::cout << "waiting for connection..." << std::endl;
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientSocketName,&size_clientSocketName);

    std::cout << "A client has connected." << std::endl;

    // Close the socket
    close(serverSocket);
    std::cout << "The server socket has been closed." << std::endl;

    return 0;
}
