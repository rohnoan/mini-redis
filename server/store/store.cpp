#include "store.h"
using namespace std;

bool Store::is_expired(const string &key){
    if(expiry.find(key)==expiry.end())return false;
    time_t now=time(0);
    if(now>expiry[key]){
        data.erase(key);
        expiry.erase(key);
        return true;
    }
    return false;
}

string Store::set(const string &key,const string &value,int ttl){
    lock_guard<mutex>lock(mtx);

    data[key]=value;
    if(ttl!=-1)expiry[key]=time(0)+ttl;
    else expiry.erase(key);
    return "OK";
}

string Store::get(const string &key){
    lock_guard<mutex>lock(mtx);

    if(data.find(key)==data.end())return "NULL";

    if(is_expired(key))return "NULL";

    return data[key];
}

string Store::del(const string &key){
    lock_guard<mutex>lock(mtx);

    expiry.erase(key);
    if(data.erase(key))return "1";
    return "0";
}