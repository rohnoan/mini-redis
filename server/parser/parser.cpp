#include "parser.h"
#include <sstream>
using namespace std;

vector<string> Parser::parse(const string &input){
    vector<string>tokens;
    stringstream ss(input);
    string word;

    while(ss>>word)tokens.push_back(word);
    return tokens;
}


