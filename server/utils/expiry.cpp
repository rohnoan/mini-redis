#include "expiry.h"
#include "../store/store.h"
#include "../utils/global.h"
#include <thread>
#include <chrono>
using namespace std; 

void expiry_worker(){
    while(true){
        store.cleanup_expired();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void start_expiry_thread(){
    thread t (expiry_worker);
    t.detach();
}