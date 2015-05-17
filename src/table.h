#ifndef TABLE_H_
#define TABLE_H_

#include <string>
#include <vector>
#include <unordered_set>

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
 *  unordered_set equality check function
 */
 struct eqEntryF {
	/**
	 *  @param e1 as a state transition table entry
	 *  @param e2 as a state transition table entry
	 *  @return true if both are equal false otherwise
	 */
	 bool operator()(const Entry &e1, const Entry &e2) const {
	 	return (e1.getCurrentState() == e2.getCurrentState()
	 		&& e1.getCharacter() == e2.getCharacter());
	 }
	};

/**
 *  unordered_set compute hash function
 */
 struct hEntryF {
	/**
	 *  @param e is an entry input used to compute a unique hash
	 *  @return unique hash table index
	 */
	 int operator()(const Entry &e) const {
	 	return e.getCharacter() * 2654435761 + e.getCurrentState();
	 }
	};

/// state transition table
	typedef std::unordered_set<Entry, hEntryF, eqEntryF> hashTable;

#endif // TABLE_H_
