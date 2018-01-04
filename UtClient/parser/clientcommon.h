#ifndef COMMON_H
#define COMMON_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <iostream>
#include "clientcomgrammer.h"
#include "clientcomvocab.yy.h"
#include "clientparse.h"
#include "clientcomvocab.yy.h"

void* ParseClientAlloc(void* (*allocProc)(size_t));
void ParseClient(void* parser, int token, const char* tokenInfo, ClientParse* valid);
void ParseClientFree(void* parser, void(*freeProc)(void*));
void ParseClientTrace(FILE *TraceFILE, char *zTracePrompt);

#endif // COMMON_H
