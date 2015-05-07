#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

static const int stateZero = 0;

/**
 * Entry Class
 * stores a state machine table entry
 */
class Entry {
private:
	int currentState;
	char character;
	int nextState;
public:
	/** Entry constructor that sets the current state,
	 * character and corresponding next state */
	Entry(int currentState, char character, int nextState);

	/**
	 * Gets the current machine state
	 * @return currentState
	 */
	int getCurrentState() const;

	/**
	 * Gets the transition character
	 * @return character
	 */
	char getCharacter() const;

	/**
	 * Gets the next valid state
	 * @return nextState
	 */
	int getNextState() const;
};

/**
 * Table Class
 * stores a machine possible state's table
 */
class Table {
private:
	vector<Entry> table;
public:
	/**
	 * Adds a new entry to the table
	 * @param e entry to add
	 */
	void addEntry(Entry e);

	/**
	 * Gets the state after the transition
	 * @param currentState is the actual state
	 * @param character is the new character input
	 * @return new state
	 */
	int transition(int currentState, char character) const;

	/**
	 * Gets the table
	 * @return table containing all the entries
	 */
	vector<Entry> getTable() const;

	/**
	 * Prints the table
	 */
	void print() const;
};

#endif // TABLE_H_
