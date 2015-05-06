#ifndef LEGREP_H_
#define LEGREP_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "search.h"
using namespace std;


void readFile(const char *filePath);
void printNoArgs();

template <class T>
void clear(T &s){
	s.str(std::string());
	s.clear();
}

#endif // LEGREP_H_