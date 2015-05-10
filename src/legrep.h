#ifndef LEGREP_H_
#define LEGREP_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "search.h"
#include "table.h"
using namespace std;


enum Modes { FINITE_AUTOMATA, NAIVE, KNUTH_MORRIS_PRATT };

static int matchMode = FINITE_AUTOMATA;
static int matches = 0;

static bool ignoreCase;
static bool invertMatch;
// static int beforeContext;
// static int afterContext;

void result();
char* getCmdOption(char** begin, char** end, const string& option);
bool cmdOptionExists(char** begin, char** end, const string& option);
void readFile(const char* filePath);
void usage(bool status);

#endif // LEGREP_H_