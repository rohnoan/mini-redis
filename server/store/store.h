#ifndef STORE_H
#define STORE_H
#include <unordered_map>
#include <string>
using namespace std;

class Store{
    public:
        string set(const string &key, const string & value);
        string get(const string &key);
        string del(const string &key);
    private:
        unordered_map<string,string>data;
};

#endif