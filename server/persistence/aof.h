#ifndef AOF_H
#define AOF_H
using namespace std;
#include <string>

class AOF{
    public: 
    void append(const string &command);
    void load();
    void rewrite();
};

#endif