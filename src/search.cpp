#include "table.h"
#include "search.h"

vector<int> naive(const string& text, const string& pattern) {
	vector<int> indexes;
	int ts = text.size(); // |T|
	int ps = pattern.size(); // |P|

	// Time complexity O((|T|-|P|+1).|T|) or O(|T||P|)
	for (int i = 0; i <= (ts - ps); i++) {
		if (text.substr(i, ps) == pattern) // hidden for loop
			indexes.push_back(i);
	}
	return indexes;
}

string getAlphabet(const string& s) {
	string alphabet;
	for (int i = 0; i < (int) s.size(); i++) {
		if (alphabet.find(s[i]) >= string::npos)
			alphabet += s[i];
	}
	return alphabet;
}

Table computeStateTransitionTable(const string& pattern) {
	string alphabet = getAlphabet(pattern);
	int as = alphabet.size(); // |E|
	int ps = pattern.size(); // |P|
	Table table(alphabet.size(), pattern.size());
	vector<int> pi = computePrefixFunction(pattern);

	// Time complexity O(|P|.|E|)
	for (int state = -1; state < ps; state++) {
		for (int i = 0; i < as; i++) {
			int k;
			if (alphabet[i] != pattern[state])
				k = pi[state + 1] + 1;
			else
				k = state + 1;

			Entry e = Entry(state, alphabet[i], k);
			table.insert(e);
		}
	}
	return table;
}

vector<int> finiteAutomaton(const string& text, const string& pattern,
		const Table& table) {
	vector<int> indexes;
	int ts = text.size();
	int ps = pattern.size();
	int state = 0;

	// Time complexity O(|T|)
	for (int i = 0; i < ts; i++) {
		state = table.find(state, text[i]);
		if (state == ps) {
			indexes.push_back(i - ps + 1);
			state = 0;
		}
	}

	return indexes;
}

vector<int> computePrefixFunction(const string& pattern) {
	int k = -1;
	int ps = pattern.size();
	vector<int> pi(pattern.size(), -1);

	for (int q = 1; q < ps; q++) {
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = pi[k];
		if (pattern[k + 1] == pattern[q])
			k++;
		pi[q] = k;
	}
	return pi;
}

vector<int> knuthMorrisPratt(const string& text, const string& pattern,
		const vector<int>& pi) {
	vector<int> indexes;
	int ts = text.size();
	int k = -1;

	for (int q = 0; q < ts; q++) {
		while (k > -1 && pattern[k + 1] != text[q])
			k = pi[k];
		if (text[q] == pattern[k + 1])
			k++;
		if (k == ((int) pattern.size() - 1))
			indexes.push_back(q - pattern.size() + 1);
	}
	return indexes;
}
