#include "server.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cstring>
#include <thread>
#include "parser/parser.h"
#include "client_handler/handler.h"
#include "store/store.h"
#include "persistence/aof.h"

using namespace std;
Server::Server(int port){
    this->port=port;
    this->server_fd=-1;
} 
void Server::start(){
    //socket
    AOF aof;
    aof.load();
    server_fd=socket(AF_INET,SOCK_STREAM,0); //this creates tcp socket

    //address
    sockaddr_in address;
    address.sin_family=AF_INET; //ipv4
    address.sin_addr.s_addr=INADDR_ANY; //accept any ip
    address.sin_port=htons(port); //bind ip to port

    //bind
    if(bind(server_fd,(struct sockaddr*)&address,sizeof(address)) < 0){
        perror("bind failed");
        return;
    }
    bind(server_fd,(struct sockaddr*)&address,sizeof(address)); //simple binding function

    //listen
    listen(server_fd,3); //simple listen function

    std::cout<<"server running on port "<<port<<endl;

    while(true){
        sockaddr_in client_addr;
        socklen_t client_len =sizeof(client_addr);

        int client_socket=accept(server_fd,(struct sockaddr*)&client_addr, &client_len);

        if(client_socket<0){
            cout<<"accept failed"<<endl;
            continue;
        }
        cout<<"client connected"<<endl;

        thread t(handle_client,client_socket);
        t.detach();
    }
    close(server_fd);
}