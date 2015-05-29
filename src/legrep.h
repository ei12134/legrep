#ifndef LEGREP_H_
#define LEGREP_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <tuple>

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
WORD Attributes;

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

enum Modes { KNUTH_MORRIS_PRATT, FINITE_AUTOMATA, NAIVE };
int matchMode = KNUTH_MORRIS_PRATT;

int matches = 0;
bool ignoreCase;
bool invertMatch;
size_t beforeContext = 0;
size_t afterContext = 0;
vector<int> pi;
Table table;

struct compare {
    bool operator() (const pair<streampos, vector<int> > p1, const pair<streampos, vector<int> > p2) const{
        return p1.first < p2.first;
    }
};

set<pair<streampos, vector<int> >,compare> lines;

void setColor(const int fgColor, bool fgIntensity);
void resetColor();
void result(const string& filePath, const string& pattern);
void readFile(const string& filePath, const string& pattern);
char* getCmdOption(char** begin, char** end, const string& option);
bool cmdOptionExists(char** begin, char** end, const string& option);
void usage(bool status);

#endif // LEGREP_H_