#ifndef SEARCH_H_
#define SEARCH_H_

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "table.h"
using namespace std;

bool naiveMatch(string& text, string& pattern);

string getAlphabet(string& s);
bool finiteAutomatonMatch(Table table, string& text, string& pattern);
Table computeTransition(string& pattern);

#endif // SEARCH_H_