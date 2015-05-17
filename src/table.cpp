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
