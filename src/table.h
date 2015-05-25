#ifndef TABLE_H_
#define TABLE_H_

#include <string>
#include <vector>

/**
 * Entry Class
 * stores a state transition table entry
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
	 * Gets the current state
	 * @return currentState
	 */
	int getCurrentState() const;

	/**
	 * Gets the transition character
	 * @return character
	 */
	char getCharacter() const;

	/**
	 * Gets the next state
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
	std::vector<Entry> transitions;
	size_t alphabetSize;

public:
	/**
	 * Default empty constructor
	 */
	Table();

	/*
	 * Allocates minimum amount of space needed to store transitions
	 * @param alphabetSize size of the alphabet
	 * @param patternSize size of the pattern
	 */
	Table(size_t alphabetSize, size_t patternSize);

	/**
	 * Adds a new entry to the table
	 * @param e entry to add
	 */
	void insert(Entry e);

	/**
	 * Gets the new state after the transition
	 * @param currentState is the actual state
	 * @param character is the input character that triggers a transition
	 * @return new state
	 */
	int find(int currentState, char character) const;

};

#endif // TABLE_H_
