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
    // Create a client socket
    int clientSocket = socket(AF_INET,SOCK_STREAM,0);
    if(clientSocket<0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    std::cout << "The client socket has been created." << std::endl;

    // Configure the server address
    struct sockaddr_in serverSocketName;
    serverSocketName.sin_family=AF_INET;
    if(inet_pton(AF_INET, IP_ADDR, &serverSocketName.sin_addr)<1)
    {
        std::cout << "Invalid IP address!" << std::endl;
        exit(EXIT_FAILURE);
    }
    serverSocketName.sin_port=htons(PORT);
    std::cout << "Init server IP." << std::endl;

    // Connecting to the server
    socklen_t size_serverSocketName = sizeof(serverSocketName);
    if(connect(clientSocket,(struct sockaddr *)&serverSocketName,size_serverSocketName)<0)
    {
        perror("socket(client)");
        exit(EXIT_FAILURE);
    }
    std::cout << "Connection success!" << endl;

    close(clientSocket);

    return 0;
}
