#include "store.h"
using namespace std;

string Store::set(const string &key,const string &value){
    data[key]=value;
    return "OK";
}
string Store::get(const string &key){
    if(data.find(key)==data.end())return "NULL";
    return data[key];
}
string Store::del(const string &key){
    if(data.erase(key))return "1";
    return "0";
}
