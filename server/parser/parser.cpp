#include "parser.h"
#include <sstream>
using namespace std;

vector<string> Parser::parse(const string &input){
    vector<string>tokens;
    int i=0;
    if(input[i]!='*')return tokens;
    i++;
    int count=0;
    while(i<input.size() && input[i]!='\r'){
        count=count*10+(input[i]-'0');
        i++;
    }
    i+=2;


    for(int k=0;k<count;k++){
        if(input[i]!='$')return tokens;
        i++;

        int len=0;
        while(i < input.size() && input[i] != '\r'){
            len=len*10+(input[i]-'0');
            i++;
        }
        i+=2;

        string word=input.substr(i,len);
        tokens.push_back(word);

        i+=len+2;
    }
    return tokens;
}


