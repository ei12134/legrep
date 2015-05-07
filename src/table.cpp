#include "table.h"

Entry::Entry(int currentState, char character, int nextState)
{
	this->currentState = currentState;
	this->character = character;
	this->nextState = nextState;
}

int Entry::getCurrentState() const
{
	return currentState;
}

char Entry::getCharacter() const
{
	return character;
}

int Entry::getNextState() const
{
	return nextState;
}

void Table::addEntry(Entry e)
{
	table.push_back(e);
}

int Table::transition(int currentState, char character) const
{
	for (size_t i = 0; i < table.size(); i++) {
		if (table[i].getCurrentState() == currentState && table[i].getCharacter() == character)
			return table[i].getNextState();
	}
	return stateZero;
}

void Table::print() const
{
	cout << "S\tC\tT\n";
	for (size_t i = 0; i < table.size(); i++) {
		cout << table[i].getCurrentState() << "\t";
		cout << table[i].getCharacter() << "\t";
		cout << table[i].getNextState() << "\n";
	}
}

vector<Entry> Table::getTable() const
{
	return table;
}
