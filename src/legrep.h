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

static const int finiteAutomata = 0;
static const int naive = 1;

static int matchMode = finiteAutomata;
static int matches = 0;

static bool ignore_case;
static bool invert_match;
// static int before_context;
// static int after_context;

static Table table;

char* getCmdOption(char** begin, char** end, const string& option);
bool cmdOptionExists(char** begin, char** end, const string& option);
void readFile(const char* filePath);
void usage(bool status);

#endif // LEGREP_H_