#include "handler.h" 
#include <sys/socket.h>
#include "../parser/parser.h"
#include "../store/store.h"
#include "../persistence/aof.h"
#include <unistd.h>
#include <iostream>
#include <cstring>
using namespace std;
AOF aof;
Parser parser;
Store store;

void handle_client(int client_socket){
    char buffer[1024];

    while(true){
        memset(buffer,0,sizeof(buffer));
        int bytes=recv(client_socket,buffer,sizeof(buffer),0);

        if(bytes<=0){
            cout<<"client disconnected"<<endl;
            break;
        }

        string input(buffer);
        auto tokens=parser.parse(input);

        if(tokens.empty())continue;

        string command=tokens[0];
        string response;

        if (command == "SET") {
            if(tokens.size()==3){
                response=store.set(tokens[1],tokens[2]);
                aof.append(input);
            }
            else if(tokens.size()==5 && tokens[3]=="EX"){
                int ttl=stoi(tokens[4]);
                response=store.set(tokens[1],tokens[2],ttl);
                aof.append(input);
            }else response="ERROR";
        }
        else if (command == "GET" && tokens.size() == 2) {
            response = store.get(tokens[1]);
        }
        else if (command == "DEL" && tokens.size() == 2) {
            response = store.del(tokens[1]);
            aof.append(input);
        }
        else {
            response = "ERROR";
        }

        send(client_socket, response.c_str(), response.size(), 0);
    
    }
}