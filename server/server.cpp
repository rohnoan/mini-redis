#include "server.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
using namespace std;
Server::Server(int port){
    this->port=port;
    this->server_fd=-1;
}
void Server::start(){
    //socket
    server_fd=socket(AF_INET,SOCK_STREAM,0);

    //address
    sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(port);

    //bind
    bind(server_fd,(struct sockaddr*)&address,sizeof(address));

    //listen
    listen(server_fd,3);

    std::cout<<"server running on port "<<port<<endl;

    //accept
    sockaddr_in client_addr;
    socklen_t  client_len = sizeof(client_addr);

    int client_socket=accept(server_fd,(struct sockaddr*)&client_addr, &client_lein);

    cout<<"client connected"<<endl;

    char buffer[1024];

    while(true){
        memset(buffer,0,sizeof(buffer));
        int bytes=recv(client_socket,buffer,sizeof(buffer),0);

        if(bytes<=0){
            cout<<"client disconnected"<<endl;
            break;
        }
        cout<<"received "<<buffer<<endl;

        send(client_socket,buffer,strlen(buffer),0);

        
    }
    close(client_socket);
    close(server_fd);
}