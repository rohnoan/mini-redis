#ifndef GLOBAL_H
#define GLOBAL_H

#include "../parser/parser.h"
#include "../store/store.h"
#include "../persistence/aof.h"

extern Parser parser;
extern Store store;
extern AOF aof;

#endif