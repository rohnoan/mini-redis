#include "server/server.h" 
using namespace std;
int main() {
    Server server(6379);
    server.start();
    return 0;
}