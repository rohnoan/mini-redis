#ifndef STORE_H
#define STORE_H
#include <unordered_map>
#include <string>
#include <mutex>
#include <ctime>
using namespace std;

class Store{
    public:
        string set(const string &key, const string & value,int ttl=-1);
        string get(const string &key);
        string del(const string &key);
    private:
        unordered_map<string,string>data;
        unordered_map<string,time_t>expiry;
        mutex mtx;

        bool is_expired(const string &key);
};

#endif