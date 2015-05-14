#include "table.h"
#include "search.h"

bool naive(string& text, string& pattern) {
	int ts = text.size(); // |T|
	int ps = pattern.size(); // |P|

	// Temporal complexity O((|T|-|P|+1).|T|) or O(|T||P|)
	for (int i = 0; i <= (ts - ps); i++) {
		if (text.substr(i, ps) == pattern) // hidden for loop
			return true;
	}
	return false;
}

bool knuthMorrisPratt(string& text, string& pattern) {
	// em pseudo codigo index de array vao de 1 a size()
	vector<int> pi = compute_prefix_function(pattern);
	// index 0 vai ser -1 e 1 -> 0 ... pois no algoritmo de baixo fazemos + 1

	int k = -1;
	for (unsigned int q = 0; q < text.size(); q++) {
		while (k > -1 && pattern[k + 1] != text[q])
			k = pi[k];
		if (text[q] == pattern[k + 1])
			k++;
		if (k == ((int)pattern.size() - 1))
			return true;
	}
	return false;
}

vector<int> compute_prefix_function(string& pattern){
	vector<int> pi(pattern.size(), -1);
	int k = -1;
	for (unsigned int q = 1; q < pattern.size(); q++) {
		while (k > -1 && pattern[k + 1] != pattern[q])
			k = pi[k];
		if (pattern[k + 1] == pattern[q])
			k++;
		pi[q] = k;
	}
	return pi;
}

string getAlphabet(string& s) {
	string alphabet;
	for (int i = 0; i < (int) s.size(); i++) {
		if (alphabet.find(s[i]) >= string::npos)
			alphabet += s[i];
	}
	return alphabet;
}

Table computeTransition(string& pattern) {
	Table t;
	string alphabet = getAlphabet(pattern);
	int as = alphabet.size(); // |E|
	int ps = pattern.size(); // |P|

	// Temporal complexity O(|P|.|P|.|P|.|E|)
	for (int state = 0; state < ps; state++) {
		for (int i = 0; i < as; i++) {
			int k = min(ps, state + 1);
			string suffix = pattern.substr(0, state) + alphabet[i];

			for (int z = 0; k > 0 && z < (int) suffix.size(); z++, k--) {
				if (pattern.substr(0, suffix.substr(z).size()) == suffix.substr(z))
					break;
			}

			Entry e = Entry(state, alphabet[i], k);
			t.addEntry(e);
		}
	}
	return t;
}

bool finiteAutomaton(Table table, string& text, string& pattern) {
	int ts = text.size();
	int ps = pattern.size();
	int state = 0;

	// Temporal complexity O(|T|)
	for (int i = 0; i < ts; i++) {
		state = table.transition(state, text[i]);
		if (state == ps)
			return true;
	}

	return false;
}
