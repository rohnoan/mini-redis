#include "handler.h" 
#include <sys/socket.h>
#include "../parser/parser.h"
#include "../store/store.h"
#include "../utils/global.h"
#include "../persistence/aof.h"
#include <unistd.h>
#include <iostream>

using namespace std;

void handle_client(int client_socket){
    char temp[1024];
    string client_buffer;

    while(true){
        int bytes = recv(client_socket, temp, sizeof(temp), 0);

        if(bytes <= 0){
            cout << "client disconnected\n";
            break;
        }

        // append incoming data
        client_buffer.append(temp, bytes);

        // try processing as many commands as possible
        while(true){
            auto tokens = parser.parse(client_buffer);

            if(tokens.empty()){
                // incomplete RESP → wait for more data
                break;
            }

            string command = tokens[0];
            string response;

            if (command == "SET") {
                if(tokens.size()==3){
                    store.set(tokens[1],tokens[2]);
                    aof.append(client_buffer);
                    response="+OK\r\n";
                }
                else if(tokens.size()==5 && tokens[3]=="EX"){
                    int ttl=stoi(tokens[4]);
                    store.set(tokens[1],tokens[2],ttl);
                    aof.append(client_buffer);
                    response="+OK\r\n";
                }else response="-ERROR\r\n";
            }
            else if (command == "GET" && tokens.size() == 2) {
                string val = store.get(tokens[1]);
                if(val=="NULL") response="$-1\r\n";
                else response="$"+to_string(val.size())+"\r\n"+val+"\r\n";
            }
            else if (command == "DEL" && tokens.size() == 2) {
                string res = store.del(tokens[1]);
                aof.append(client_buffer);
                response=":"+res+"\r\n";
            }
            else if (command == "REWRITE") {
                aof.rewrite();
                response = "+OK\r\n";
            }
            else {
                response = "-ERROR\r\n";
            }

            send(client_socket, response.c_str(), response.size(), 0);

            // TEMP SIMPLIFICATION: clear buffer
            client_buffer.clear();
        }
    }

    close(client_socket);
}