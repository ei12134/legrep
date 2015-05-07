#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

static const int stateZero = 0;

class Entry {
private:
	int currentState;
	char character;
	int nextState;
public:
	Entry(int currentState, char character, int nextState);
	int getCurrentState() const;
	char getCharacter() const;
	int getNextState() const;
};

class Table {
private:
	vector<Entry> table;
public:
	void addEntry(Entry e);
	int transition(int currentState, char character) const;
	vector<Entry> getTable() const;
	void print() const;
};

#endif // TABLE_H_