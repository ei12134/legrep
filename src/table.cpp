#include "table.h"

Entry::Entry(int currentState, char character, int nextState) {
	this->currentState = currentState;
	this->character = character;
	this->nextState = nextState;
}

int Entry::getCurrentState() const {
	return currentState;
}

char Entry::getCharacter() const {
	return character;
}

int Entry::getNextState() const {
	return nextState;
}

Table::Table() {
	this->alphabetSize = 0;
}

Table::Table(size_t alphabetSize, size_t patternSize) {
	this->alphabetSize = alphabetSize;
	transitions.reserve(alphabetSize * patternSize);
}

void Table::insert(Entry e) {
	transitions.push_back(e);
}

int Table::find(int currentState, char character) const {
	size_t limit = (currentState + 1) * alphabetSize;

	// Time complexity O(E)
	for (size_t i = (currentState) * alphabetSize; i < limit; i++) {
		if (transitions[i].getCurrentState() == currentState
				&& transitions[i].getCharacter() == character)
			return transitions[i].getNextState();
	}
	return 0;
}
