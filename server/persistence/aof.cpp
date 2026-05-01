#include "aof.h"
#include <fstream>
#include <iostream>
#include "../store/store.h"
#include "../parser/parser.h"

using namespace std;

extern Store store;
extern Parser parser;

void AOF::append(const string&command){
    ofstream file("appendonly.aof",ios::app);
    file<<command<<endl;
    file.close();
}

void AOF::load(){
    ifstream file("appendonly.aof");

    if(!file.is_open())return;

    string line;

    while(getline(file,line)){
        auto tokens=parser.parse(line);
        if(tokens.empty())continue;

        string cmd=tokens[0];

        if(cmd=="SET" && tokens.size()==3){
            store.set(tokens[1],tokens[2]);
        }else if(cmd=="DEL" && tokens.size()==2){
            store.del(tokens[1]);
        }
    }
    file.close();
}