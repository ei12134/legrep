#ifndef LEGREP_H_
#define LEGREP_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>
#include <sstream>
#include <string>
#include <set>

#include "search.h"
#include "table.h"
using namespace std;

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <wincon.h>
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN BLUE | GREEN
#define RED 4
#define YELLOW GREEN | RED
#define MAGENTA BLUE | RED
#define GRAY BLUE | GREEN | RED
HANDLE hConsoleOutput;

#else // Other OS's
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW GREEN | RED
#define BLUE 4
#define MAGENTA BLUE | RED
#define CYAN BLUE | GREEN
#define GRAY BLUE | GREEN | RED
#endif

enum Modes { FINITE_AUTOMATA, NAIVE, KNUTH_MORRIS_PRATT };

static int matchMode = FINITE_AUTOMATA;
static int matches = 0;

static bool ignoreCase;
static bool invertMatch;
static int beforeContext = 0;
static int afterContext = 0;


// std::ostream & operator <(const Pair<int,int> &p1, const Pair<int,int> &p2){
// 	return p1.first < p2.first;
// }

/// lines to print
static set<pair<int,int>> lines;

void setColor(const int fgColor, bool fgIntensity);
void resetColor();
void result(string& filePath, string& pattern);
void readFile(string& filePath, string& pattern);
char* getCmdOption(char** begin, char** end, const string& option);
bool cmdOptionExists(char** begin, char** end, const string& option);
void usage(bool status);

#endif // LEGREP_H_